/*
 * @SOURCE_HEADER@
 *
 * @This_is_a_template_file___Feel_free_to_edit@
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 *
 * Concrete implementation of the abstract scheduler interface for SystemC export (EVS).
 */

/* Includes */
#include "GlobalDefs.h"

#include <systemc>
#include <tlm.h>
#include <cstring>
#include <cmath>

#include <scx/scx.h>
#include <TxLib/TxCriticalSection.h>
#include <sg/SGSimpleComponentRegistry.h>
#include <sg/MSCFixes.h>

#include "scx_scheduler_mapping.h"

// helpers

// strdup which accepts NULL pointers and converts them into empty strings
static const char *safe_strdup(const char *str)
{
    return strdup(str ? str : "");
}

// like FrequencySource::getFrequency() plus returns 0.0 for NULL pointers
static double safe_getFrequency(sg::FrequencySource *f)
{
    return f ? f->getFrequency() : 0.0;
}

// like SchedulerObject::getName() but handling NULL pointers
static const char *safe_getName(sg::SchedulerObject *obj)
{
    if (!obj)
        return "(NULL)";
    const char *name = obj->getName();
    if (!name)
        return "(NULL)";
    return name;
}

// macro for verbose messages (redefined below)
#define if_verbose(message_class) \
    if (owner->get_verbose() & ((scx::scheduler_mapping::message_class) | scx::scheduler_mapping::V_ALL))

namespace scx
{

// --- asynchronous callback which handles asynchonous stop events ---
class async_stop_callback: public sg::SchedulerCallback
{
public:

    /*! Constructor. */
    async_stop_callback(scheduler_mapping * owner_):
    owner(owner_)
    {
        assert(owner);
    }
    virtual const char * getName() const
    {
        return "scheduler_mapping/async_stop_callback";
    }

    /*! Callback function. */
    virtual void schedulerCallback()
    {

        // block simulation in the async event processing loop
        owner->stop_acknowledge_from_async_stop_callback();
    }

/* Implementation */
private:

    // member variables
    scheduler_mapping * owner;
};

// clear_stop_request_proxy_class:
// This class is used as a pseudo runnable to forward clearStopRequest() calls from the scheduler to the scheduler when
// the scheduler called stopAcknowledge() in contrast to threads calling stopAcknowledge().
// The clearStopRequest() function is the only function of this interface which is used.
class clear_stop_request_proxy_class: public sg::SchedulerRunnable
{
public:

    // constructor and destructor
    clear_stop_request_proxy_class(scheduler_mapping *owner_):
    owner(owner_)
    {
        assert(owner);
    }
    virtual const char *getName() const
    {
        return "scheduler_mapping/clear_stop_request_proxy_class";
    }

    // these functions should never be called
    virtual void threadProc() {}
    virtual void threadProcExitRequest() {}
    virtual void breakQuantum(sg::ticks_t) {}
    virtual bool stopRequest()
    {
        return false;
    }
    virtual bool setThreadProperty(ThreadProperty, uint64_t)
    {
        return false;
    }
    virtual bool getThreadProperty(ThreadProperty, uint64_t &)
    {
        return false;
    }

    /*! Clear stop request flag.
     * Forward to scheduler.
     */
    virtual void clearStopRequest()
    {
        owner->clear_stop_request();
    }

/* Implementation */
private:

    // member variables
    scheduler_mapping *owner;
};

// Abstract 'runnable' interface for scheduler_mapping_sc_thread objects
class scheduler_mapping_sc_thread_runnable
{
public:

    /*! Get name of underlying thread (not of SchedulerRunnable). */
    virtual const char * get_name() const = 0;

    /*! Main thread function. Returning from this terminates the thread. */
    virtual void thread_proc() = 0;

#if defined(FM_SCX_ENABLE_TA)
    /*! Checks whether a synchronisation is required.
     */
    virtual bool need_sync() = 0;

    /*! Triggers a synchronisation.
     */
    virtual void do_sync() = 0;

    /* Retrieve local time of currently running temporally decoupled thread.
     * Returns Local time in seconds.
     */
    virtual double get_local_time() = 0;

    /* Set local time of currently running temporally decoupled thread.
     */
    virtual void set_local_time(double local_time) = 0;

#else
    /*! Set default quantum size. */
    virtual void set_default_quantum_size(double quantum_sec) = 0;

    /*! Break quantum in the underlying SchedulerRunnable. Ignored for timers. */
    virtual void break_quantum(double quantum_sec) = 0;

    /*! Set next quantum size. */
    virtual void set_next_quantum_size(double quantum_sec) = 0;
#endif  /* defined(FM_SCX_ENABLE_TA) */

    /*! Stop simulation request. */
    virtual bool stop_request() = 0;

    /*! Tell runnable that the sc_thread has terminated. */
    virtual void thread_terminated() = 0;

    /*! Get SchedulerRunnable (if available for this runnable). */
    virtual sg::SchedulerRunnable * get_scheduler_runnable()
    {
        return 0;
    }

/* Implementation */
protected:

    // protected destructor: do not allow to destry objects through this interface
    virtual ~scheduler_mapping_sc_thread_runnable() {}
};

// SystemC sc_event abstraction
// This object represents a SystemC sc_event and can be notified any time, also during elaboration
class scheduler_mapping_sc_event
{
public:

    // constructor and destructor
    scheduler_mapping_sc_event(scheduler_mapping *owner_, const char *name_):
    owner(owner_),
    name(safe_strdup(name_)),
    was_notified_(false)
    {
    }
    ~scheduler_mapping_sc_event()
    {
        free((void *) name);
    }

    /*! This is the equivalent of the sc_event::notify() function.
     * In contrast to sc_event::notify() this function may be called _any_ time, also during elaboration.
     * (This is the primary motivation for the existence of this class.)
     */
    void notify()
    {
        was_notified_ = true;
        if (sc_core::sc_is_running())
        {
            if_verbose(V_SYSTEMC)
                SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping_sc_event", "notify('%s): sc_event::notify()", name);
            event.notify();
        }
    }

    /*! Returns true if this event was notified after the last call to clear_notify() or since event creation. */
    bool was_notified() const
    {
        return was_notified_;
    }

    /*! Clear 'was_notified()' flag after event was notified to be able to detect a new notification. */
    void clear_notified()
    {
        was_notified_ = false;
    }

    /*! Get SystemC event object. */
    sc_core::sc_event & get_event()
    {
        return event;
    }

private:

    // private data
    scheduler_mapping * owner; /// parent scheduler API implementation (never NULL)
    const char * name;         /// string owned by this object (never NULL)
    bool was_notified_;        /// true if this event was notified since the last clear_notified() or since object
                               /// creation (this is important when during the elaboration phase where
                               /// sc_event::notify() cannot be used)
    sc_core::sc_event event;   /// SystemC event
};

// --- SystemC thread abstraction ---
// This object represents a SystemC thread (not a Fast Models scheduler API thread).
class scheduler_mapping_sc_thread
{
public:
    enum { DEFAULT_THREAD_STACK_SIZE = 128*1024 };

    /*! constructor and destructor */
    scheduler_mapping_sc_thread(scheduler_mapping *owner_,
                                scheduler_mapping_sc_thread_runnable *runnable_,
                                bool is_timer_):
    owner(owner_),
    runnable(runnable_),
    is_timer(is_timer_),
    thread_kill_event(owner_, "thread_kill_event")
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_sc_thread",
                                 "scheduler_mapping_sc_thread() name=%s",
                                 get_name());
        assert(owner);
        assert(runnable);

        // start thread_proc() thread
        int stack_size = get_stack_size();
        if_verbose(V_SYSTEMC)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_sc_thread",
                                 "scheduler_mapping_sc_thread('%s'): sc_core::sc_spawn(thread_proc, stack_size=%d)",
                                 get_name(),
                                 stack_size);
        sc_core::sc_spawn_options spawn_options;
        spawn_options.set_stack_size(stack_size);
        process_handle = sc_core::sc_spawn(sc_bind(& scheduler_mapping_sc_thread::thread_proc, this),
                                           0,
                                           & spawn_options);
        owner->add_sc_thread(this);
    }

    ~scheduler_mapping_sc_thread()
    {
        owner->remove_sc_thread(this);
    }

    /*! get stack size for this thread from runnable (or use the default stack size) */
    int get_stack_size()
    {
        // ask runnable
        uint64_t stack_size = DEFAULT_THREAD_STACK_SIZE;
        bool value_ok = false;
        if (runnable && runnable->get_scheduler_runnable())
            value_ok = runnable->get_scheduler_runnable()->getThreadProperty(sg::SchedulerRunnable::TP_STACK_SIZE,
                                                                             stack_size);

        // if:
        // - we do not have a runnable or
        // - the runnable does support TP_STACK_SIZE or
        // - the runnable request a very small stack:
        // -> use default stack size
        if ((!value_ok) || (stack_size < DEFAULT_THREAD_STACK_SIZE))
            stack_size = DEFAULT_THREAD_STACK_SIZE;

        // round up to 4k page and return stack size
        stack_size = (stack_size + 0xfff) & ~0xfffull;
        return int(stack_size);
    }

    /*! kill thread */
    void kill()
    {
        thread_kill_event.notify();
        runnable = 0;
    }

    /*! get name of thread */
    const char *get_name() const
    {
        return runnable ? runnable->get_name() : "(zombie)";
    }

    /*! get associated scheduler API thread object (may return NULL) */
    scheduler_mapping_sc_thread_runnable *get_runnable() const
    {
        return runnable;
    }

    /*! Get thread_kill_event event object. */
    scheduler_mapping_sc_event &get_thread_kill_event()
    {
        return thread_kill_event;
    }

    /*! Return SystemC process object for the started SystemC thread or NULL if the thread was not yet started. */
    sc_core::sc_object *get_process_object() const
    {
        return process_handle.get_process_object();
    }

#if defined(FM_SCX_ENABLE_TA)
    /*! Checks whether a synchronisation is required.
     */
    bool need_sync()
    {
        // this is meanigless if we have no runnable attached or if this is a timer
        if ((! runnable) || is_timer)
            return false;
        return runnable->need_sync();
    }

    /*! Triggers a synchronisation.
     */
    void do_sync()
    {
        // this is meanigless if we have no runnable attached or if this is a timer
        if ((! runnable) || is_timer)
            return;
        runnable->do_sync();
    }

    /* Retrieve local time of currently running temporally decoupled thread.
     * Returns Local time in seconds.
     */
    double get_local_time()
    {
        // this is meanigless if we have no runnable attached or if this is a timer
        if ((! runnable) || is_timer)
            return 0.0;
        return runnable->get_local_time();
    }

    /* Set local time of currently running temporally decoupled thread.
     */
    void set_local_time(double local_time)
    {
        // this is meanigless if we have no runnable attached or if this is a timer
        if ((! runnable) || is_timer)
            return;
        runnable->set_local_time(local_time);
    }

#else
    /*! Calculate and set default quantum size */
    void set_default_quantum_size()
    {
        // this is meanigless if we have no runnable attached or if this is a timer
        if ((!runnable) || is_timer)
            return;
        // get size of default quantum (global quantum)
        double quantum_sec = tlm::tlm_global_quantum::instance().get().to_seconds();
        if_verbose(V_SYSTEMC)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_sc_thread",
                                 "set_default_quantum_size() name=%s: tlm::tlm_global_quantum::instance().get()=%.9fs",
                                 get_name(),
                                 quantum_sec);
        // push size of default quantum into runnable
        runnable->set_default_quantum_size(quantum_sec);
    }

    /*! Calculate and set next quantum size */
    void set_next_quantum_size()
    {
        // this is meanigless if we have no runnable attached or if this is a timer
        if ((!runnable) || is_timer)
            return;
        // get size of next quantum (local quantum)
        double quantum_sec = owner->getNextSyncPoint();
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_sc_thread",
                                 "set_next_quantum_size() name=%s: scheduler_mapping::getNextSyncPoint()=%.9fs",
                                 get_name(),
                                 quantum_sec);
        // push size of next quantum into runnable
        runnable->set_next_quantum_size(quantum_sec);
    }

    /*! Break quantum */
    void break_quantum(double quantum_sec)
    {
        // this is meanigless if we have no runnable attached or if this is a timer
        if ((!runnable) || is_timer)
            return;
        if_verbose(V_SYSTEMC)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_sc_thread",
                                 "break_quantum(%.9fs) name=%s",
                                 get_name(),
                                 quantum_sec);
        // push size of next quantum into runnable
        runnable->break_quantum(quantum_sec);
    }
#endif  /* defined(FM_SCX_ENABLE_TA) */

private:
    // private helper

    /* main thread function */
    void thread_proc()
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_sc_thread",
                                 "thread_proc() name=%s: enter",
                                 get_name());
        try
        {
#if ! defined(FM_SCX_ENABLE_TA)
            // initialize first quantum size in runnable
            set_default_quantum_size();
#endif  /* ! defined(FM_SCX_ENABLE_TA) */
            // run thread
            if (runnable)
                runnable->thread_proc();
            // when thread_proc() returns the thread terminates
            if_verbose(V_THREAD)
                SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                     "scheduler_mapping_sc_thread",
                                     "thread_proc() name=%s: thread terminated because thread function returned",
                                     get_name());
        }
        catch(...)
        {
            // we catch all exceptions which end up here and terminate the thread
            if_verbose(V_THREAD)
                SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                     "scheduler_mapping_sc_thread",
                                     "thread_proc() name=%s: thread terminated because an unknown exception was thrown",
                                     get_name());
        }
        thread_terminated();
    }

    /* called when the thread terminated */
    void thread_terminated()
    {
        if (runnable)
            runnable->thread_terminated();
        delete this;
    }

    // private data
    scheduler_mapping *owner;                       // parent scheduler API implementation (never NULL)
    scheduler_mapping_sc_thread_runnable *runnable; // pointer to the associated scheduler API runnable
    bool is_timer;                                  // true: this is a Timer thread, false: this is a Thread thread
    scheduler_mapping_sc_event thread_kill_event;   // event which is triggered when the thread should exit
                                                    // immediately. This always aborts the current wait() call.
    sc_core::sc_process_handle process_handle;      // process handle for timer_loop() thread
};

// --- Timer implementation ---
class scheduler_mapping_Timer:
    public sg::Timer,
    public sg::FrequencyObserver,
    public scheduler_mapping_sc_thread_runnable,
    public sg::SchedulerRunnable
{
public:
    // constructor and destructor
    scheduler_mapping_Timer(const char *name_, scheduler_mapping *owner_, sg::TimerCallback *callback_):
    name(safe_strdup(name_)),
    owner(owner_),
    frequency_source(0),
    current_frequency(0.0),
    callback(callback_),
    timer_interval_sec(0.0),
    new_timer_interval_sec(0.0),
    last_timer_callback_time(0.0),
    timer_loop_event(owner_, "timer_loop_event"),
    sc_thread(0),
    is_terminated(false),
    stop_request_(false)
    {
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping_Timer", "scheduler_mapping_Timer() name=%s", name_);
        assert(owner);
        assert(callback);

        // start timer_loop() thread
        sc_thread = new scheduler_mapping_sc_thread(owner, this, true /* is_timer */);
    }

    virtual ~scheduler_mapping_Timer()
    {
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping_Timer", "~scheduler_mapping_Timer() name=%s", name);
        // terminate timer loop thread (if running)
        if (sc_thread)
            sc_thread->kill();
        // unregister from frequency source
        if (frequency_source)
            frequency_source->unregisterFrequencyObserver(this);
        // notify parent that we got destroyed
        owner->remove_timer(this);
        free((void*)name);
    }

    // --- Timer implementation ---

    /*! Get Name. */
    virtual const char *getName() const
    {
        return name;
    }

    /*! Sets the specified frequency source clock for this timer. */
    virtual void setFrequency(sg::FrequencySource* new_frequency_source)
    {
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Timer",
                                 "setFrequency(%s:%.1fHz) name=%s",
                                 safe_getName(new_frequency_source),
                                 safe_getFrequency(new_frequency_source),
                                 name);

        // unregister from old frequency source
        if (frequency_source)
            frequency_source->unregisterFrequencyObserver(this);

        // update frequency
        frequency_source = new_frequency_source;
        update_frequency();

        // register for frequency source
        if (frequency_source)
            frequency_source->registerFrequencyObserver(this);
    }

    /*! Unsets the timer; causing it to no longer be set and will no longer fire.
     *  Has no effect if the timer is not currently set.
     */
    virtual void cancel()
    {
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping_Timer", "cancel() name=%s", name);
        if (!is_set_internal())
            return;
        timer_interval_sec = 0.0;
        new_timer_interval_sec = 0.0;
        timer_loop_event.notify();
    }

    /*! Set a timer to be signalled after ticks' ticks of the parent clock. When
     *  this happens the user callback function will be called. If the user
     *  callback returns 0 the timer will act as a one-shot, else it will be
     *  reoccur after n ticks; where n is the callback return value.
     *
     *  If the timer was already set and has not yet expired it will be re-set as
     *  if the old set() had never occurred.
     *
     *  \param ticks The number of ticks in the future to set the timer to fire.
     *  \returns false if the timer couldn't be scheduled (ticks too big).
     */
    virtual bool set(sg::ticks_t ticks)
    {
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Timer",
                                 "set(ticks=%llu)=%d name=%s",
                                 (long long unsigned) ticks,
                                 true,
                                 name);
        set_internal(ticks);
        return true;
    }

    /*! Return whether a timer is set and queued for callback.
     *
     *  \returns True if the timer is set; else false.
     */
    virtual bool isSet()
    {
        bool is_set = is_set_internal();
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Timer",
                                 "isSet()=%d name=%s (timer_interval_sec=%f, new_timer_interval_sec=%f)",
                                 is_set,
                                 name,
                                 timer_interval_sec,
                                 new_timer_interval_sec);
        return is_set;
    }

    /*! Get the remaining clock ticks before a timer will be triggered. This
     * may return 0 if the timer is about to be triggered. This will return 0
     * if the timer is not set.
     *
     * \returns The number of remaining ticks before the timer will be triggered.
     */
    virtual sg::ticks_t remaining()
    {
        sg::ticks_t r = remaining_internal();
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Timer",
                                 "remaining()=%llu name=%s",
                                 (long long unsigned)r,
                                 name);
        return r;
    }

    // --- FrequencyObserver implementation ---

    /*! Notify this object that the observed frequency source changed. */
    virtual void notifyFrequencyChanged(sg::FrequencySource *frequency_source_)
    {
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Timer",
                                 "notifyFrequencyChanged(%s:%.1fHz) name=%s",
                                 safe_getName(frequency_source),
                                 safe_getFrequency(frequency_source),
                                 name);
        update_frequency();
    }

    /*! Notify this object that the observed frequency is about to be destroyed. */
    virtual void notifyFrequencySourceDestroyed(sg::FrequencySource *frequency_source_)
    {
        if_verbose(V_TIMER)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Timer",
                                 "notifyFrequencySourceDestroyed(%s:%.1fHz) name=%s",
                                 safe_getName(frequency_source),
                                 safe_getFrequency(frequency_source),
                                 name);
        frequency_source = 0;
        update_frequency();
    }

    // --- scheduler_mapping_sc_thread_runnable implementation ---

    /*! Get name of unerlying thread (not of SchedulerRunnable). */
    virtual const char *get_name() const {
        return getName();
    }

    /*! Main thread function. Returning from this terminates the thread.
     * All timed timer functionality is implemented by this thread.
     */
    virtual void thread_proc()
    {
        // keep a few member variables in local stack variables because the object around this function may disappear
        // while we are still in the scope of this function (upon thread kill/destruction of this object)
        scheduler_mapping_sc_thread *local_sc_thread = sc_thread;
        scheduler_mapping *local_owner = owner;
        char local_name[80];
        strncpy(local_name, name, sizeof(local_name));
        local_name[sizeof(local_name) - 1] = 0;

        // endless loop
        for (;;) // destructor will tell us to terminate thread through scheduler_mapping_sc_thread::kill()
        {
            if (timer_interval_sec)
            {
                // timer is set: wait on timeout and on other timer events (cancel, set, ...)
                if ((!timer_loop_event.was_notified()) && (!sc_thread->get_thread_kill_event().was_notified()))
                {
                    if_verbose(V_SYSTEMC)
                        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                             "scheduler_mapping_Timer",
                                             "thread_proc('%s'): sc_core::wait(%.9fs, timer_loop_event|thread_kill_event)",
                                             name,
                                             timer_interval_sec);
                    sc_core::wait(timer_interval_sec,
                                  sc_core::SC_SEC,
                                  timer_loop_event.get_event() | sc_thread->get_thread_kill_event().get_event());
                }

                // check for kill event
                if (local_sc_thread->get_thread_kill_event().was_notified())
                    return; // return terminates thread

                // clear timer_loop_event
                timer_loop_event.clear_notified();

                // call timer callback (only if timer is still set)
                if (timer_interval_sec)
                {
                    // call callback and calc next interval
                    last_timer_callback_time = owner->getCurrentSimulatedTime(); // remember current time for remaining
                    try
                    {
                        // reset timer before calling callback to ensure remaing() returns 0
                        timer_interval_sec = 0;
                        sg::ticks_t ticks = callback->timerCallback();

                        // check for kill event (just in case somebody destroyed the timer from within the timer
                        // callback function)
                        if (local_sc_thread->get_thread_kill_event().was_notified())
                            return; // return terminates thread
                        timer_interval_sec = ticks_to_interval(ticks);

                        /* This is a synchronisation point */
                        if (timer_interval_sec)
                            owner->addSynchronisationPoint(ticks, frequency_source);
                    }
                    catch(...)
                    {
                        // any exception thrown will be handled like 'return 0' which will cancel the timer
                        // (this will allow the timer to be re-set() in the future while not catching exceptions here
                        // will terminate the sc_thread which would render the timer non-functional for all time in the
                        // future)
                        if (local_owner->get_verbose()
                            & (scx::scheduler_mapping::V_TIMER | scx::scheduler_mapping::V_ALL))
                            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                                 "scheduler_mapping_Timer",
                                                 "thread_proc() name=%s: timer thread: "
                                                 "ignoring unknown exception, cancelling timer",
                                                 local_name);

                        // check for kill event (just in case somebody destryed the timer from within the timer callback
                        // function and _after_ that throws a random exception)
                        if (local_sc_thread->get_thread_kill_event().was_notified())
                            return; // return terminates thread
                        timer_interval_sec = 0;
                    }
                }
            }
            else
            {
                // timer is not set: wait on timer event (cancel, set, ...)
                if ((!timer_loop_event.was_notified()) && (!sc_thread->get_thread_kill_event().was_notified()))
                {
                    if_verbose(V_SYSTEMC)
                        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                             "scheduler_mapping_Timer",
                                             "timer_loop('%s'): sc_core::wait(timer_loop_event|thread_kill_event)",
                                             name);
                    sc_core::wait(timer_loop_event.get_event() | sc_thread->get_thread_kill_event().get_event());
                }

                // check for kill event
                if (local_sc_thread->get_thread_kill_event().was_notified())
                    return; // return terminates thread

                // clear timer_loop_event
                timer_loop_event.clear_notified();
            }

            // handle incoming new timer.set()
            if (new_timer_interval_sec)
            {
                timer_interval_sec = new_timer_interval_sec;
                new_timer_interval_sec = 0.0;
                last_timer_callback_time = owner->getCurrentSimulatedTime(); // remember current time for remaining()
            }

            // handle async events
            // (this has nothing to do with timer behavior, we simply hook into all SystemC threads to check for async
            // events)
            if (owner->has_pending_async_callbacks())
                owner->process_async_callbacks();
            else
                owner->process_idle();

            // handle stop requests
            if (stop_request_)
                owner->stopAcknowledge(this);
        }
    }

#if defined(FM_SCX_ENABLE_TA)
    /*! Checks whether a synchronisation is required.
     */
    virtual bool need_sync()
    {
        // ignored: timers never need to sync
        return false;
    }

    /*! Triggers a synchronisation.
     */
    virtual void do_sync()
    {
        // ignored: timers never need to sync
    }

    /* Retrieve local time of currently running temporally decoupled thread.
     * Returns Local time in seconds.
     */
    double get_local_time()
    {
        // ignored: this is meanigless for timers
        return 0.0;
    }

    /* Set local time of currently running temporally decoupled thread.
     */
    void set_local_time(double local_time)
    {
        // ignored: this is meanigless for timers
    }

#else
    /*! Set default quantum size has no semantics for timers because timers never do work in quantums. */
    virtual void set_default_quantum_size(double quantum_sec)
    {
        // ignored: timers do not do anything during a quantum
    }

    /*! Break quantum has no semantics for timers because timers never do work in quantums. */
    virtual void break_quantum(double quantum_sec)
    {
        // ignored: timers do not do anything during a quantum
    }

    /*! Set next quantum size has no semantics for timers because timers never do work in quantums. */
    virtual void set_next_quantum_size(double quantum_sec)
    {
        // ignored: timers do not do anything during a quantum
    }
#endif  /* defined(FM_SCX_ENABLE_TA) */

    /*! Stop simulation request. */
    virtual bool stop_request()
    {
        stop_request_ = true;
        return true;
    }

    /*! Tell runnable that the sc_thread has terminated. */
    virtual void thread_terminated()
    {
        sc_thread = 0;
        is_terminated = true;
    }

    // --- SchedulerRunnable implementation ---
    // (only for clearStopRequest() from stopAcknowledge())

    // these functions should never be called
    virtual void threadProc() {}
    virtual void threadProcExitRequest() {}
    virtual void breakQuantum(sg::ticks_t ticks) {}
    virtual bool stopRequest()
    {
        return false;
    }
    virtual bool setThreadProperty(ThreadProperty property, uint64_t value)
    {
        return false;
    }
    virtual bool getThreadProperty(ThreadProperty property, uint64_t &valueOut)
    {
        return false;
    }

    /*! Clear stop request flag. */
    virtual void clearStopRequest()
    {
        stop_request_ = false;
    }


private:
    // internal implementation

    /*! Get timer interval in seconds for number of ticks.
     * /returns interval in seconds. Returns 0.0 if current frequency or ticks is 0. */
    double ticks_to_interval(sg::ticks_t ticks)
    {
        return current_frequency ? (ticks / current_frequency) : 0.0;
    }

    /*! Get timer ticks for timer interval in seconds.
     * \return timer ticks. Returns 0 if current frequency or interval is 0.0. */
    sg::ticks_t interval_to_ticks(double interval_sec)
    {
        if (interval_sec < 0.0)
            return 0;
        return sg::ticks_t(interval_sec * current_frequency + 0.5);
    }

    /*! Get remaining time in seconds until the timer fires next.
     * \return time in seconds until next timer fires. Returns 0.0 if the timer is not set. */
    double get_remaining_sec()
    {
        double interval = new_timer_interval_sec ? new_timer_interval_sec : timer_interval_sec;
        if (interval == 0.0)
            return 0.0;
        double r = last_timer_callback_time + interval - owner->getCurrentSimulatedTime();
        return r >= 0.0 ? r : 0.0;
    }

    /*! Update internal state because the timer frequency changed. */
    void update_frequency()
    {
        double new_frequency = safe_getFrequency(frequency_source);
        if (new_frequency == current_frequency)
            return; // avoid spurious updates

        // remember the old state
        bool was_set = is_set_internal();
        sg::ticks_t remaining_ticks = remaining_internal();
        // handle corner case: timer is about to fire, and is set, remaining_ticks is 0: setting a timer to expire in 0
        // ticks is not possible with our internal and external semantics, so we choose 1 ticks
        if (was_set && (remaining_ticks == 0))
            remaining_ticks++;

        // get new frequency
        current_frequency = new_frequency;

        // restore the old state: keep the remaining number of ticks constant (not the remaining time)
        if (was_set)
            set_internal(remaining_ticks);
    }

    /*! Set timer. Cancels timer if frequency is 0.0. Correctly overrides currently set timer. */
    void set_internal(sg::ticks_t ticks)
    {
        timer_interval_sec = 0.0;
        new_timer_interval_sec = ticks_to_interval(ticks);
        timer_loop_event.notify();

        /* This is a synchronisation point */
        if (new_timer_interval_sec)
            owner->addSynchronisationPoint(ticks, frequency_source);
    }

    /*! Return true if and only if the timer is set. */
    bool is_set_internal()
    {
        return (timer_interval_sec != 0.0) || (new_timer_interval_sec != 0.0);
    }

    /*! Get the remaining clock ticks before a timer will be triggered. This
     * may return 0 if the timer is about to be triggered. This will return 0
     * if the timer is not set.
     *
     * \returns The number of remaining ticks before the timer will be triggered.
     */
    sg::ticks_t remaining_internal()
    {
        sg::ticks_t r = 0;
        if (is_set_internal())
            r = interval_to_ticks(get_remaining_sec());
        return r;
    }

    // private data
    const char *name;                       // string owned by this object (never NULL)
    scheduler_mapping *owner;               // parent scheduler API implementation (never NULL)
    sg::FrequencySource *frequency_source;  // current frequency source of this timer (may be NULL)
    double current_frequency;               // current frequency from the current frequency source, may be 0.0
    sg::TimerCallback *callback;

    // timer loop state machine:
    double timer_interval_sec;              // timer interval for next and current timer interval while timer is set
    double new_timer_interval_sec;          // timer interval for first timer interval while timer is being set with
                                            // 'set()'
    double last_timer_callback_time;        // absolute time (no specific base) when the last timer callback
                                            // was called or when the timer was started with set()
    scheduler_mapping_sc_event timer_loop_event;
        // event which is triggered whenever the timer loop needs to respond to changed circumstances (_not_ when the
        // timer triggers)
    scheduler_mapping_sc_thread *sc_thread; // associated sc_thread (if any), NULL when thread does not run
    bool is_terminated;                     // true: thread was started and also has terminated already
    bool stop_request_;
};

// --- Thread implementation ---
// This object represents one thread of the Fast Models scheduler API (not an sc_thread).
class scheduler_mapping_Thread:
    public sg::SchedulerThread,
    public sg::FrequencyObserver,
    public sg::QuantumKeeper,
    public scheduler_mapping_sc_thread_runnable
{
public:
    // constructor and destructor
    scheduler_mapping_Thread(const char *name_, scheduler_mapping *owner_, sg::SchedulerRunnable *runnable_):
    name(safe_strdup(name_)),
    owner(owner_),
    frequency_source(0),
    current_frequency(0.0),
    runnable(runnable_),
    sc_thread(0),
    is_terminated(false),
    local_time(0)
    {
        assert(owner);
        assert(runnable);
    }

    virtual ~scheduler_mapping_Thread()
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping_Thread", "~scheduler_mapping_Thread() name=%s", name);
        // terminate thread (if running)
        if (sc_thread)
            sc_thread->kill();
        // unregister from frequency source
        if (frequency_source)
            frequency_source->unregisterFrequencyObserver(this);
        // notify parent that we got destroyed
        owner->remove_thread(this);
        free((void*)name);
    }

    // --- sg::SchedulerThread implementation ---

    /*! Get Name. */
    virtual const char *getName() const { return name; }

    /*! Sets/resets the specified frequency source to be the parent clock for this thread. */
    virtual void setFrequency(sg::FrequencySource* new_frequency_source)
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Thread",
                                 "setFrequency(%s:%.1fHz) name=%s",
                                 safe_getName(new_frequency_source),
                                 safe_getFrequency(new_frequency_source),
                                 name);

        // unregister from old frequency source
        if (frequency_source)
            frequency_source->unregisterFrequencyObserver(this);

        // update frequency
        frequency_source = new_frequency_source;
        update_frequency();

        // register for frequency source
        if (frequency_source)
            frequency_source->registerFrequencyObserver(this);
    }

    /*! Start thread. */
    virtual void start()
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping_Thread", "start() name=%s", name);
        if ((sc_thread != 0) || is_terminated)
            return; // ignore start() when: 1) thread was started already and also when 2) thread has terminated

#if ! defined(FM_SCX_ENABLE_TA)
        // get size of global quantum
        double quantum_sec = tlm::tlm_global_quantum::instance().get().to_seconds();
        if_verbose(V_SYSTEMC)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Thread",
                                 "set_default_quantum_size() name=%s: tlm::tlm_global_quantum::instance().get()=%.9fs",
                                 get_name(),
                                 quantum_sec);

        // push size of global quantum into runnable
        set_default_quantum_size(quantum_sec);
#endif  /* ! defined(FM_SCX_ENABLE_TA) */

        // start thread
        sc_thread = new scheduler_mapping_sc_thread(owner, this, false /* is_timer */);
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping_Thread", "start() name=%s returned", name);
    }

    /*! Returns the quantum keeper of this thread. */
    sg::QuantumKeeper * getQuantumKeeper()
    {
        return this;
    }

    // --- FrequencyObserver implementation ---

    /*! Notify this object that the observed frequency source changed. */
    virtual void notifyFrequencyChanged(sg::FrequencySource *frequency_source_)
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Thread",
                                 "notifyFrequencyChanged(%s:%.1fHz) name=%s",
                                 safe_getName(frequency_source),
                                 safe_getFrequency(frequency_source),
                                 name);
        update_frequency();
    }

    /*! Notify this object that the observed frequency is about to be destroyed. */
    virtual void notifyFrequencySourceDestroyed(sg::FrequencySource *frequency_source_)
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Thread",
                                 "notifyFrequencySourceDestroyed(%s:%.1fHz) name=%s",
                                 safe_getName(frequency_source),
                                 safe_getFrequency(frequency_source),
                                 name);
        frequency_source = 0;
        update_frequency();
    }

    // --- QuantumKeeper implementation ---

    /*! Sets the value of the global quantum in ticks interpreted relative to the frequency set with
     * SchedulerThread::setFrequency() of the associated thread.
     */
    virtual void setGlobalQuantum(sg::ticks_t ticks) const
    {
        owner->setGlobalQuantum(ticks, frequency_source);
    }

    /*! Returns the value of the global quantum in ticks interpreted relative to the frequency set with
     * SchedulerThread::setFrequency() of the associated thread.
     */
    virtual sg::ticks_t getGlobalQuantum() const
    {
        return sg::ticks_t(owner->getGlobalQuantum() * current_frequency + 0.5);
    }

    /*! Sets the value of the local time to the value passed as an argument.
     */
    virtual void setLocalTime(sg::ticks_t ticks)
    {
        local_time = ticks;
    }

    /*! Increments the value of the local time by the value passed as an argument.
     */
    virtual void incLocalTime(sg::ticks_t ticks)
    {
        local_time += ticks;
    }

    /*! Returns the value of the local time in ticks interpreted relative to the frequency set with
     * SchedulerThread::setFrequency() of the associated thread.
     */
    virtual sg::ticks_t getLocalTime() const
    {
        return local_time;
    }

    /*! Returns the value of the current time, that is the current simulation time plus the local time.
     */
    virtual sg::ticks_t getCurrentTime() const
    {
        return sg::ticks_t(owner->getCurrentSimulatedTime() * current_frequency + 0.5) + local_time;
    }

    /*! The method getNextSyncPoint() returns the next synchronisation point.
     */
    virtual sg::ticks_t getNextSyncPoint()
    {
        return sg::ticks_t((owner->getCurrentSimulatedTime() + owner->getNextSyncPoint()) * current_frequency + 0.5);
    }

    /*! Checks whether a synchronisation is required.
     */
    virtual bool needSync()
    {
        return (local_time >= sg::ticks_t(owner->getNextSyncPoint() * current_frequency + 0.5));
    }

    /*! The method sync() must call SchedulerInterfaceForComponents::wait(local_time, ...) to suspend the thread until
     * simulation time equals current time, effectively triggering a synchronisation, and must then call reset().
     */
    virtual void sync()
    {
        owner->wait(local_time, frequency_source);
        reset();
    }

    /*! The method reset() might calculate the next synchronisation point later returned by getNextSyncPoint() and must
     * then set the local time back to zero.
     */
    virtual void reset()
    {
        local_time = 0;
    }

    // --- scheduler_mapping_sc_thread_runnable implementation ---

    /*! Get name of unerlying thread (not of SchedulerRunnable). */
    virtual const char *get_name() const
    {
        return getName();
    }

    /*! Main thread function. Returning from this terminates the thread. */
    virtual void thread_proc()
    {
        runnable->threadProc();
    }

#if defined(FM_SCX_ENABLE_TA)
    /*! Checks whether a synchronisation is required.
     */
    virtual bool need_sync()
    {
        return needSync();
    }

    /*! Triggers a synchronisation.
     */
    virtual void do_sync()
    {
        sync();
    }

    /* Retrieve local time of currently running temporally decoupled thread.
     * Returns Local time in seconds.
     */
    double get_local_time()
    {
        return (current_frequency? double(getLocalTime()) / current_frequency: 0.0);
    }

    /* Set local time of currently running temporally decoupled thread.
     */
    void set_local_time(double local_time)
    {
        // this is meanigless if we have no runnable attached or if this is a timer
        setLocalTime(sg::ticks_t(local_time * current_frequency + 0.5));
    }

#else
    /*! Set default quantum size in the underlying SchedulerRunnable. */
    virtual void set_default_quantum_size(double quantum_sec)
    {
        // convert time in seconds into time in ticks
        sg::ticks_t quantum_ticks = 0;
        if (quantum_sec)
        {
            // if current_frequency == 0.0 then quantum_ticks will become 1
            quantum_ticks = (sg::ticks_t)ceil(quantum_sec * current_frequency);
            // make sure we advance time by at least one tick if quantum_sec > 0. to avoid convergence against 0.0
            if (quantum_ticks == 0)
                quantum_ticks = 1;
        }
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Thread",
                                 "set_default_quantum_size(%.9fs) name=%s: "
                                 "runnable->setThreadProperty(TP_DEFAULT_QUANTUM_SIZE, ticks=%llu)",
                                 quantum_sec,
                                 name,
                                 (long long unsigned)quantum_ticks);
        // push default quantum size into runnable
        runnable->setThreadProperty(sg::SchedulerRunnable::TP_DEFAULT_QUANTUM_SIZE, quantum_ticks);
    }

    /*! Break quantum in the underlying SchedulerRunnable. */
    virtual void break_quantum(double quantum_sec)
    {
        // convert time in seconds into time in ticks
        sg::ticks_t quantum_ticks = 0;
        if (quantum_sec)
        {
            // if current_frequency == 0.0 then quantum_ticks will become 1
            quantum_ticks = (sg::ticks_t)ceil(quantum_sec * current_frequency);
            // make sure we advance time by at least one tick if quantum_sec > 0. to avoid convergence against 0.0
            if (quantum_ticks == 0)
                quantum_ticks = 1;
        }
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Thread",
                                 "break_quantum(%.9fs) name=%s: runnable->breakQuantum(ticks=%llu)",
                                 quantum_sec,
                                 name,
                                 (long long unsigned) quantum_ticks);
        // push next quantum size into runnable
        runnable->breakQuantum(quantum_ticks);
    }

    /*! Set next quantum size in the underlying SchedulerRunnable. */
    virtual void set_next_quantum_size(double quantum_sec)
    {
        // convert time in seconds into time in ticks
        sg::ticks_t quantum_ticks = 0;
        if (quantum_sec)
        {
            // if current_frequency == 0.0 then quantum_ticks will become 1
            quantum_ticks = (sg::ticks_t)ceil(quantum_sec * current_frequency);
            // make sure we advance time by at least one tick if quantum_sec > 0. to avoid convergence against 0.0
            if (quantum_ticks == 0)
                quantum_ticks = 1;
        }
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_Thread",
                                 "set_next_quantum_size(%.9fs) name=%s: "
                                 "runnable->setThreadProperty(TP_BREAK_QUANTUM, ticks=%llu)",
                                 quantum_sec,
                                 name,
                                 (long long unsigned)quantum_ticks);
        // push next quantum size into runnable
        runnable->setThreadProperty(sg::SchedulerRunnable::TP_BREAK_QUANTUM, quantum_ticks);
    }
#endif  /* defined(FM_SCX_ENABLE_TA) */

    /*! Stop simulation request. */
    virtual bool stop_request()
    {
        return runnable->stopRequest();
    }

    /*! Tell runnable that the sc_thread has terminated. */
    virtual void thread_terminated()
    {
        sc_thread = 0;
        is_terminated = true;
    }

    /*! Get SchedulerRunnable (if available for this runnable). */
    virtual sg::SchedulerRunnable *get_scheduler_runnable()
    {
        return runnable;
    }

private:
    // private helper

    // freqency changed
    void update_frequency()
    {
        double new_frequency = safe_getFrequency(frequency_source);
        if (new_frequency == current_frequency)
            return; // avoid spurious updates

        // get new frequency
        current_frequency = new_frequency;
    }

    // private data
    const char *name;                   // string owned by this object (never NULL)
    scheduler_mapping *owner;           // parent scheduler API implementation (never NULL)
    sg::FrequencySource *frequency_source;
        // current frequency source of this thread (may be NULL) (for breakQuantum() only)
    double current_frequency;           // current frequency from the current frequency source, may be 0.0
    sg::SchedulerRunnable *runnable;    // pointer to the associated scheduler API runnable
    scheduler_mapping_sc_thread *sc_thread;
        // associated sc_thread (if any), NULL when thread does not run
    bool is_terminated;                 // true: thread was started and also has terminated already
    sg::ticks_t local_time;             // local time within the quantum of this temporally decoupled thread
};

// --- ThreadSignal implementation ---
class scheduler_mapping_ThreadSignal: public sg::ThreadSignal
{
public:
    // constructor and destructor
    scheduler_mapping_ThreadSignal(const char *name_, scheduler_mapping *owner_):
    name(safe_strdup(name_)),
    owner(owner_),
    thread_signal(owner_, "thread_signal")
    {
    }

    virtual ~scheduler_mapping_ThreadSignal()
    {
        if_verbose(V_THREAD_SIGNAL)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping_ThreadSignal",
                                 "~scheduler_mapping_ThreadSignal() name=%s",
                                 name);
        // notify parent that we got destroyed
        owner->remove_thread_signal(this);
        free((void*)name);
    }

    /*! Get Name. */
    virtual const char *getName() const
    {
        return name;
    }

    /*! Notify the event, waking up any waiting threads. */
    virtual void notify()
    {
        if_verbose(V_THREAD_SIGNAL)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping_ThreadSignal", "notify() name=%s", name);
        thread_signal.notify();
    }

    // --- private interface towards scheduler_mapping class ---

    /*! Get SystemC event object. */
    scheduler_mapping_sc_event &get_event()
    {
        return thread_signal;
    }

private:

    // private data
    const char *name;                           // string owned by this object (never NULL)
    scheduler_mapping *owner;                   // parent scheduler API implementation (never NULL)
    scheduler_mapping_sc_event thread_signal;   // this event implements the notify()/wait() mechanism
};

// --- class scheduler_mapping implementation ---

// macro for verbose messages (redefinition)
#undef if_verbose
#define if_verbose(message_class) \
    if (verbose & ((scx::scheduler_mapping::message_class) | scx::scheduler_mapping::V_ALL))

// constructor and destructor
scheduler_mapping::scheduler_mapping(scx_simcontrol_if * controller):
sc_core::sc_module(sc_core::sc_module_name("scheduler_mapping_pseudo_module")),
verbose(0),
async_callbacks_processing_thread(0),
stop_request(false),
clear_stop_request_proxy(0),
simulation_thread_id(0),
schedulerInterfaceRegistry("scheduler_mapping::schedulerInterfaceRegistry", false)
{
    // enable verbose messages
    if (getenv("SCX_EVS_VERBOSE"))
        verbose = strtoul(getenv("SCX_EVS_VERBOSE"), 0, 0);
    if (verbose)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "scheduler_mapping(): enabled verbose messages (flags 0x%04X)",
                             verbose);

    // get access to simulation controller
    simcontroller = controller;
    assert(simcontroller);

    // create clear_stop_request_proxy
    clear_stop_request_proxy = new clear_stop_request_proxy_class(this);

    // set simulation thread id to be able to determine whether calls come from this thread or from other threads
    simulation_thread_id = sg::thread_self();

    // register SchedulerInterfaceForComponents
    schedulerInterfaceRegistry.RegisterInterface(sg::SchedulerInterfaceForComponents::IFNAME(),
                                                 sg::SchedulerInterfaceForComponents::IFREVISION(),
                                                 static_cast<sg::SchedulerInterfaceForComponents*>(this));

    /* Enable support for timing annotation as needed */
#if defined(FM_SCX_ENABLE_TA)
    setenv("FASTSIM_DISABLE_TA", "0", 1);
#else
    setenv("FASTSIM_DISABLE_TA", "1", 1);
#endif  /* defined(FM_SCX_ENABLE_TA) */
}

scheduler_mapping::~scheduler_mapping()
{
    // Note: We cannot call SCX_REPORT...() from here since scx_default_report_handler may be already deconstructed
    // when we come here (global destructors)
    //if_verbose(V_GENERAL)
    //   SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "~scheduler_mapping()");
    delete clear_stop_request_proxy;
}

// CAInterface related stuff
eslapi::CAInterface *scheduler_mapping::ObtainInterface(eslapi::if_name_t ifName,
                                                        eslapi::if_rev_t minRev,
                                                        eslapi::if_rev_t *actualRev)
{
    return schedulerInterfaceRegistry.ObtainInterface(ifName, minRev, actualRev);
}

// main interface, used by components
sg::Timer* scheduler_mapping::createTimer(const char* name, sg::TimerCallback *callback)
{
    if (!name)
        name = "(anonymous timer)";
    if (!callback)
        return 0;
    if_verbose(V_TIMER)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "createTimer(name=%s)", name);
    scheduler_mapping_Timer *timer = new scheduler_mapping_Timer(name, this, callback);
    timers.push_front(timer);
    return timer;
}

sg::SchedulerThread *scheduler_mapping::createThread(const char* name, sg::SchedulerRunnable *runnable)
{
    if (!name)
        name = "(anonymous thread)";
    if (!runnable)
        return 0;
    if_verbose(V_THREAD)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "createThread(name=%s, runnable=%s)",
                             name,
                             safe_getName(runnable));
    scheduler_mapping_Thread *thread = new scheduler_mapping_Thread(name, this, runnable);
    threads.push_front(thread);
    return thread;
}

sg::ThreadSignal* scheduler_mapping::createThreadSignal(const char* name)
{
    if (!name)
        name = "(anonymous thread signal)";
    if_verbose(V_THREAD_SIGNAL)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "createThreadSignal(name=%s)", name);
    scheduler_mapping_ThreadSignal *thread_signal = new scheduler_mapping_ThreadSignal(name, this);
    thread_signals.push_front(thread_signal);
    return thread_signal;
}

void scheduler_mapping::wait(sg::ticks_t ticks, sg::FrequencySource *timebase)
{
    if_verbose(V_THREAD)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "wait(%llu, timebase=%s:%.1fHz)",
                             (long long unsigned)ticks,
                             safe_getName(timebase),
                             safe_getFrequency(timebase));
    double frequency = safe_getFrequency(timebase);

    // handle async events
    // (this has nothing to do with thread or wait(), we simply hook into all SystemC threads to check for any pending
    // async events)
    if (has_pending_async_callbacks())
        process_async_callbacks();
    else
        process_idle();

    // wait for timeout
    double timeout = 0.0;
    if (frequency)
        timeout = ticks / frequency;
    if_verbose(V_SYSTEMC)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "wait(): sc_core::wait(%.9fs)", timeout);
    sc_core::wait(timeout, sc_core::SC_SEC);

#if ! defined(FM_SCX_ENABLE_TA)
    // calc and set next quantum size
    scheduler_mapping_sc_thread *sc_thread = get_current_sc_thread();
    if (sc_thread)
    {
        sc_thread->set_next_quantum_size();
    }
    else
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping",
                                 "wait(): not setting next quantum size because not in one of our sc_threads");
    }
#endif  /* ! defined(FM_SCX_ENABLE_TA) */
}

void scheduler_mapping::wait(sg::ThreadSignal *thread_signal)
{
    if_verbose(V_THREAD_SIGNAL)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "wait(threadSignal=%s)",
                             safe_getName(thread_signal));
    if (!thread_signal)
        return;

    // handle async events
    // (this has nothing to do with thread or wait(), we simply hook into all SystemC threads to check for any pending
    // async events)
    if (has_pending_async_callbacks())
        process_async_callbacks();
    else
        process_idle();

    // wait for notify event
    scheduler_mapping_ThreadSignal *our_thread_signal = static_cast<scheduler_mapping_ThreadSignal*>(thread_signal);
    if_verbose(V_SYSTEMC)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "wait(): sc_core::wait(thread_signal_event)");
    sc_core::wait(our_thread_signal->get_event().get_event());
#if ! defined(FM_SCX_ENABLE_TA)

    // calc and set next quantum size
    scheduler_mapping_sc_thread *sc_thread = get_current_sc_thread();
    if (sc_thread)
    {
        sc_thread->set_next_quantum_size();
    }
    else
    {
        if_verbose(V_THREAD)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping",
                                 "wait(): not setting next quantum size because not in one of our sc_threads");
    }
#endif  /* ! defined(FM_SCX_ENABLE_TA) */
}

/*! Sets the value of the global quantum.
 * The global quantum is the maximum time a thread can run ahead of simulation time.
 * All threads must synchronize on timing points that are multiples of the global quantum.
 */
void scheduler_mapping::setGlobalQuantum(sg::ticks_t ticks, sg::FrequencySource * timebase)
{
    double q = 0.0;

    if_verbose(V_OTHER)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "setGlobalQuantum(ticks=%llu, timebase=%s:%.1fHz)",
                             (long long unsigned) ticks,
                             safe_getName(timebase),
                             safe_getFrequency(timebase));
    if ((ticks != 0) && (safe_getFrequency(timebase) != 0.0))
    {
        q = double(ticks) / safe_getFrequency(timebase);
    }
    tlm::tlm_global_quantum::instance().set(sc_core::sc_time(q, sc_core::SC_SEC));
}

/*! Returns the value of the global quantum in seconds.
 */
double scheduler_mapping::getGlobalQuantum()
{
    return tlm::tlm_global_quantum::instance().get().to_seconds();
}

void scheduler_mapping::addSynchronisationPoint(sg::ticks_t ticks, sg::FrequencySource *timebase)
{
    double next_sync = 0.0;

    if_verbose(V_OTHER)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "addSynchronisationPoint(ticks=%llu, timebase=%s:%.1fHz)",
                             (long long unsigned)ticks,
                             safe_getName(timebase),
                             safe_getFrequency(timebase));

    // next sync point
    if ((ticks != 0) && (safe_getFrequency(timebase) != 0.0))
    {
        next_sync = double(ticks) / safe_getFrequency(timebase);

        /* Add future sync point to priority queue */
        m_sync_points.push(getCurrentSimulatedTime() + next_sync);
#if defined(FM_SCX_ENABLE_TA)

        /* Trigger synchronization as needed */
        scheduler_mapping_sc_thread * sc_current_thread = get_current_sc_thread();
        if (sc_current_thread && sc_current_thread->need_sync())
        {
            sc_current_thread->do_sync();
        }
    }
#else
    }

    // modify quantum of all non running threads
    scheduler_mapping_sc_thread * sc_current_thread = get_current_sc_thread();
    for (ThreadMap::const_iterator i = sc_thread_map.begin(); (i != sc_thread_map.end()); i ++)
    {
        if (i->second && (i->second != sc_current_thread))
        {
            i->second->set_next_quantum_size();
        }
    }

    // notify running thread so it knows we would like it to stop ASAP
    if (sc_current_thread)
    {
        sc_current_thread->break_quantum(std::min(next_sync, getNextSyncPoint()));
    }
#endif  /* defined(FM_SCX_ENABLE_TA) */
}

/*!
 * \brief   Returns the next synchronization point.
 *
 * This version of the method returns the earliest of the local quantum and the next synchronisation point, expressed
 * relatively to the current simulated time.
 */
double scheduler_mapping::getNextSyncPoint()
{
    double now = getCurrentSimulatedTime();

    /* Calculate local quantum as needed */
    double q = tlm::tlm_global_quantum::instance().compute_local_quantum().to_seconds();

    if_verbose(V_SYSTEMC)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "getNextSyncPoint(): tlm::tlm_global_quantum::instance().compute_local_quantum()=%.9fs",
                             q);

    /* Remove old sync points */
    while ((! m_sync_points.empty()) && (m_sync_points.top() <= now))
    {
        m_sync_points.pop();
    }

    /* Return earliest of next sync point and local quantum */
    if (! m_sync_points.empty())
    {
        if (m_sync_points.top() <= (now + q))
        {
            return (m_sync_points.top() - now);
        }
    }
    return (q);
}

void scheduler_mapping::addCallback(sg::SchedulerCallback *callback)
{
    if (sg::thread_equal(async_callbacks_processing_thread, sg::thread_self()))
    {
        // we are adding a callback from within a callback function: OK, must not lock mutex to avoid deadlock
        // this is OK as we are implicitly synchronized with processAsyncCallbacks() (same thread) and
        // process_async_callbacks() can deal with adding elements in the middle of the processing loop
        if_verbose(V_ASYNC_CALLBACK)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping",
                                 "addCallback() (from simulation thread: no need to lock mutex)");
        async_callbacks.push_back(callback);
    }
    else
    {
        // we are adding a callback function from:
        // - any non-simulation thread
        // - the simulation thread, but outside of processAsyncCallbacks()
        // we therefore need to lock the mutex
        TxCriticalSection lock(async_callbacks_mutex); // automatically lock/unlock mutext in an exception safe way
        if_verbose(V_ASYNC_CALLBACK)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping",
                                 "addCallback() (from non-simulation thread or outside of process_async_callbacks(): "
                                 "locked mutex)");
        async_callbacks.push_back(callback);
    }
}

void scheduler_mapping::removeCallback(sg::SchedulerCallback *callback)
{
    if_verbose(V_ASYNC_CALLBACK)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "removeCallback()");
    if (sg::thread_equal(async_callbacks_processing_thread, sg::thread_self()))
    {
        // we are removing a callback from within a callback function: OK, must not lock mutex to avoid deadlock
        // this is OK as we are implicitly synchronized with processAsyncCallbacks() (same thread) and
        // process_async_callbacks() can deal with removing elements in the middle of the processing loop
        if_verbose(V_ASYNC_CALLBACK)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping",
                                 "removeCallback() (from simulation thread: no need to lock mutex)");
        async_callbacks.remove(callback);
    }
    else
    {
        // we are removing a callback function from:
        // - any non-simulation thread
        // - the simulation thread, but outside of processAsyncCallbacks()
        // we therefore need to lock the mutex
        TxCriticalSection lock(async_callbacks_mutex); // automatically lock/unlock mutext in an exception safe way
        if_verbose(V_ASYNC_CALLBACK)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping",
                                 "removeCallback() (from non-simulation thread or outside of process_async_callbacks():"
                                " locked mutex)");
        async_callbacks.remove(callback);
    }
}

double scheduler_mapping::getCurrentSimulatedTime()
{
    return sc_core::sc_time_stamp().to_seconds();
}

double scheduler_mapping::getCurrentLocalTime()
{
#if defined(FM_SCX_ENABLE_TA)
    scheduler_mapping_sc_thread * sc_current_thread = get_current_sc_thread();
    if (!sc_current_thread)
        return 0.0;
    return sc_current_thread->get_local_time();
#else
    return 0.0;
#endif  /* defined(FM_SCX_ENABLE_TA) */
}

void scheduler_mapping::setCurrentLocalTime(sg::ticks_t ticks, sg::FrequencySource *timebase)
{
#if defined(FM_SCX_ENABLE_TA)
    scheduler_mapping_sc_thread * sc_current_thread = get_current_sc_thread();
    if (!sc_current_thread)
        return;

    double local_time = 0.0;

    if ((ticks != 0) && (safe_getFrequency(timebase) != 0.0))
    {
        local_time = double(ticks) / safe_getFrequency(timebase);
    }
    sc_current_thread->set_local_time(local_time);
#endif  /* defined(FM_SCX_ENABLE_TA) */
}

// the models call this function to request a system wide simulation stop
void scheduler_mapping::stopRequest()
{
    if (sg::thread_equal(simulation_thread_id, sg::thread_self()))
    {
        // we are in the simulation thread

        // get currently running thread runnable or NULL if no runnable is currently running
        scheduler_mapping_sc_thread_runnable *current_runnable = 0;
        scheduler_mapping_sc_thread *current_sc_thread = get_current_sc_thread();
        if (current_sc_thread)
            current_runnable = current_sc_thread->get_runnable();

        if_verbose(V_EXEC)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping",
                                 "stopRequest() from simulation thread (sending stop request to %s)",
                                 current_runnable ? "current runnable" : "scheduler adapter itself");

        if (current_runnable)
        {
            // if we are in a thread which has a runnable tell that runnable to stop at a useful point
            // (this may be a scheduler thread or a timer)
            if (!current_runnable->stop_request())
                async_stop_request();
                    // if the runnable does not accept our stop request we have to stop the simulation ourselves in the
                    // scheduler
        }
        else
        {
            // if we are not in a thread (e.g. async callback) we will just push an async stop event
            async_stop_request();
        }
    }
    else
    {
        // we are not in the simulation thread
        if_verbose(V_EXEC)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "stopRequest() from non-simulation thread");

        // note that coming here will be a rare case: CADI interfaces will call stopRequest() on the runnable they are
        // attached to directly
        async_stop_request();
    }
}

// the models call this function to acknowledge a stop requested by requestStop():
// the models expect this function to block until the simulation is resumed
void scheduler_mapping::stopAcknowledge(sg::SchedulerRunnable *runnable)
{
    if_verbose(V_EXEC)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "stopAcknowledge(runnable->getName()=%s) enter (pausing (blocking) simulation)",
                             safe_getName(runnable));
    simcontroller->stop_acknowledge(runnable);
    if_verbose(V_EXEC)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "stopAcknowledge(runnable->getName()=%s) leave (resuming simulation)",
                             safe_getName(runnable));
}

// private internal API towards scheduler objects (timer, thread and thread signal)

/// called by Timer destructor when timer gets destroyed
void scheduler_mapping::remove_timer(scheduler_mapping_Timer *timer)
{
    if_verbose(V_THREAD)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "remove_timer()");
    timers.remove(timer);
}

/// called by Thread destructor when thread gets destroyed
void scheduler_mapping::remove_thread(scheduler_mapping_Thread *thread)
{
    if_verbose(V_THREAD)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "remove_thread()");
    threads.remove(thread);
}

/// called by ThreadSignal destructor when thread signal gets destroyed
void scheduler_mapping::remove_thread_signal(scheduler_mapping_ThreadSignal *thread_signal)
{
    if_verbose(V_THREAD)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "remove_thread_signal()");
    thread_signals.remove(thread_signal);
}

/// return current scheduler_mapping_sc_thread object or NULL if not in any threadProc() call
scheduler_mapping_sc_thread *scheduler_mapping::get_current_sc_thread()
{
    // get current SystemC process handle
    sc_core::sc_process_handle proc_h = sc_core::sc_get_current_process_handle();
    // find associated scheduler_mapping_Thread object
    ThreadMap::const_iterator i = sc_thread_map.find(proc_h.get_process_object());
    if (i == sc_thread_map.end())
    {
#if 0
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "get_current_sc_thread(): sc_get_current_process_handle()=%p",
                             proc_h.get_process_object());
        for (ThreadMap::const_iterator j = sc_thread_map.begin(); j != sc_thread_map.end(); j++)
            SCX_REPORT_INFO_VERB(SCX_DEBUG,
                                 "scheduler_mapping",
                                 "get_current_sc_thread(): sc_thread_map[%p] -> %p",
                                 j->first,
                                 j->second);
#endif
        return 0; // not found
    }
    return i->second;
}

/// called by scheduler_mapping_sc_thread constructor when sc_threads get created/started
void scheduler_mapping::add_sc_thread(scheduler_mapping_sc_thread *sc_thread)
{
    if_verbose(V_THREAD)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "add_sc_thread(): sc_thread_map[%p] -> %p",
                             sc_thread->get_process_object(),
                             sc_thread);
    // add map entry
    sc_thread_map[sc_thread->get_process_object()] = sc_thread;
}

/// called by scheduler_mapping_sc_thread destructor when sc_threads get destroyed
void scheduler_mapping::remove_sc_thread(scheduler_mapping_sc_thread *sc_thread)
{
    if_verbose(V_THREAD)
        SCX_REPORT_INFO_VERB(SCX_DEBUG,
                             "scheduler_mapping",
                             "remove_sc_thread(): erasing sc_thread_map[%p] -> %p",
                             sc_thread->get_process_object(),
                             sc_thread);
    // remove map entry
    sc_thread_map.erase(sc_thread->get_process_object());
}

/// process any potentially pending async callbacks
void scheduler_mapping::process_async_callbacks()
{
    TxCriticalSection lock(async_callbacks_mutex);   // automatically lock/unlock mutext in an exception safe way
    if_verbose(V_ASYNC_CALLBACK)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "process_async_callbacks()");
    async_callbacks_processing_thread = sg::thread_self();
    while(!async_callbacks.empty())
    {
        sg::SchedulerCallback *callback = async_callbacks.front();
        async_callbacks.pop_front();
        // the callback may add other callbacks and remove this and other callbacks
        // therefore we use an interator free loop here
        callback->schedulerCallback();
    }
    async_callbacks_processing_thread = 0;
}

/// process any potentially pending idle activity
void scheduler_mapping::process_idle()
{
    if_verbose(V_EXEC)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "process_idle()");
    simcontroller->process_idle();
}

/// call stopAcknowledge() for async stops (block simulation)
void scheduler_mapping::stop_acknowledge_from_async_stop_callback()
{
    if_verbose(V_EXEC)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "stop_acknowledge_from_async_stop_callback()");
    stopAcknowledge(clear_stop_request_proxy);
}

/// clear stop request flag
void scheduler_mapping::clear_stop_request()
{
    if_verbose(V_EXEC)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "clear_stop_request()");
    stop_request = false;
}

/// Push async stop request.
/// Called by stopRequest() to stop the simulation from async requests or for other fallback cases.
/// Note: This just happens in rare cases and is not the usual stop mechanism.
/// This is just a fallback for asynchronous stops and whenever we have no current runnable we could stop or if the
/// runnable does not accept the stopRequest().
void scheduler_mapping::async_stop_request()
{
    // this will stop us during the current or next async event processing which will be soon enough
    if (!stop_request)
    {
        if_verbose(V_EXEC)
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "async_stop_request(): adding async_stop_callback()");
        stop_request = true;
        addCallback(new async_stop_callback(this));
    }
}

// --- sc_module override-ables ---
void scheduler_mapping::before_end_of_elaboration()
{
    if_verbose(V_GENERAL)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "before_end_of_elaboration()");
}

void scheduler_mapping::end_of_elaboration()
{
    if_verbose(V_GENERAL)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "end_of_elaboration()");
}

void scheduler_mapping::start_of_simulation()
{
    if_verbose(V_GENERAL)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "start_of_simulation()");
}

void scheduler_mapping::end_of_simulation()
{
    if_verbose(V_GENERAL)
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scheduler_mapping", "end_of_simulation()");
}

/*!
 * \brief   Returns a pointer to a new instance of the default implementation of the scheduler mapping provided with
 * Fast Models.
 */
sg::SchedulerInterfaceForComponents *scx_create_default_scheduler_mapping(scx_simcontrol_if *simcontrol)
{
    if (simcontrol)
        return new scheduler_mapping(simcontrol);
    else
        return 0;
}

} // namespace scx

