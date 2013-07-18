/*!
 * \file    SGSchedulerInterfaceForComponents.h
 * \brief   Abstract scheduler interface used by modelling components to create threads and timers etc.
 * \date    Copyright 2011-2013 ARM Limited. All rights reserved.
 */

#ifndef SGSCHEDULERINTERFACEFORCOMPONENTS_H
#define SGSCHEDULERINTERFACEFORCOMPONENTS_H

#include "eslapi/CAInterface.h"
#include "sg/SGstdint.h"
#include "sg/SGTicks.h" // ticks_t is factored out to keep visibility of header files low

namespace sg
{
class FrequencySource;

/*! Base class for all scheduler objects and interfaces. */
class SchedulerObject
{
public:
    /*! Get instance name of the instance which implements this interface.
     * This name is not guaranteed to be unique or hierarchical, but including (or using) the
     * hierarchical component name is suggested. It is intended for debugging purposes.
     * The caller must not free/delete the returned string. The string is owned by this object.
     * The pointer will be valid as long as the object implementing this interface exists.
     * If the caller cannot track the lifetime of this object and wants to remember the name it must make a copy of it.
     * \returns Instance name of this object. */
    virtual const char *getName() const = 0;

protected:
    /*! Protected virtual destructor: Do not allow to destroy instances through this interface. */
    virtual ~SchedulerObject() {}
};

/*! FrequencyObserver: abstract base class for objects which want to receive notification messages from
 * FrequencySource objects when the clock frequency changed.
 */
class FrequencyObserver: public SchedulerObject
{
public:
    /*! Notify this object that the observed frequency source changed.
     * The object should query the new clock frequency using frequencySource->getFrequency()
     * and adapt its behavior accordingly.
     * The object must not cause the the FrequencySource to change its frequency again from within
     * this callback.
     * \param frequencySource FrequencySource object which changed and which issues this notification.
     *        This is the object where this FrequencyObserver registered with registerFrequencyObserver()
     *        previously. This is never NULL.
     */
    virtual void notifyFrequencyChanged(FrequencySource *frequencySource) = 0;

    /*! Notify this object that the observed frequency source is about to be destroyed.
     * It is valid to access frequencySource from within this function.
     * It is valid but not required to call frequencySource->unregisterFrequencyObserver() from within this function.
     * frequencySource may no longer be accessed after returning from this function.
     * \param frequencySource: FrequencySource object which is about to be destroyed and which issues this notification.
     *        This is the object where this FrequencyObserver registered with registerFrequencyObserver() previously.
     */
    virtual void notifyFrequencySourceDestroyed(FrequencySource *frequencySource) = 0;

protected:
    /*! Protected virtual destructor: Do not allow to destroy instances through this interface. */
    virtual ~FrequencyObserver() {}
};

/*! Frequency source: Provides a clock frequency.
 * The clock frequency can be queried (getFrequency()) and the object can also notify
 * other objects about clock frequency changes (register/unregisterFrequencyObserver()).
 */
class FrequencySource: public SchedulerObject
{
public:
    /*! Register another observer which wants to be notified whenever this objects changes.
     * This object must not call FrequencyObserver::notifyFrequencyChanged() from within registerFrequencyObserver().
     * Calling this with an already registered observer or 0 is allowed and will be ignored.
     */
    virtual void registerFrequencyObserver(FrequencyObserver *observer) = 0;

    /*! Unregister an observer which no longer wants to be notified about changes.
     * This object must not call FrequencyObserver::notifyFrequencyChanged() from within unregisterFrequencyObserver().
     * Calling this with an unknown, already unregistered or 0 observer is allowed and will be ignored.
     */
    virtual void unregisterFrequencyObserver(FrequencyObserver *observer) = 0;

    /*! Get frequency in Hz of this clock source. */
    virtual double getFrequency() = 0;

protected:
    /*! Notify all registered observers that this object changed.
     * This function is not part of the public interface and is merely an implementation guide line
     * for implementers of this class.
     */
    virtual void notifyFrequencyObservers() = 0;

    /*! Protected virtual destructor: Do not allow to destroy instances through this interface. */
    virtual ~FrequencySource() {}
};

/*! TimerCallback:
 * Callback base class for timers created through SchedulerInterfaceForComponents::createTimer().
 */
class TimerCallback: public SchedulerObject
{
public:
    /*! Timer callback function.
     * Called whenever the timer expires.
     * \returns 0 for a one-shot timer, t to be signaled again in t ticks time
     */
    virtual ticks_t timerCallback() = 0;

protected:
    /*! Protected virtual destructor: Do not allow to destroy instances through this interface. */
    virtual ~TimerCallback() {}
};

/*! Interface of timers. Instances of objects implementing this
 *  interface are created using the createTimer() method on SchedulerInterfaceForComponents.
 */
class Timer: public SchedulerObject
{
public:
    /*! Sets the specified frequency source clock for this timer.
     * This will set the initial or override the existing frequency source for this timer.
     * Setting a new frequency source must not alter the state of the timer as much as possible.
     * In particular the timer should not be restarted and the remaining ticks (not the time!) until the timer
     * expires should be preserved when changing the frequency.
     * Specifying a NULL frequency source is valid and will cancel the timer.
     * This object must register/unregister a FrequencyObserver to observe and respond to any frequency changes.
     * \param frequencySource New or initial frequency source for this timer.
     */
    virtual void setFrequency(FrequencySource* frequencySource) = 0;

    /*! Unsets the timer; causing it to no longer be set and will no longer fire.
     *  Has no effect if the timer is not currently set.
     */
    virtual void cancel() = 0;

    /*! Set a timer to be signalled after 'ticks' ticks of the clock. When
     *  this happens the user callback function will be called. If the user
     *  callback returns 0 the timer will act as a one-shot, else it will
     *  reoccur after n ticks; where n is the callback return value.
     *
     *  If the timer was already set and has not yet expired it will be re-set as
     *  if the old set() had never occurred.
     *
     *  \param ticks The number of ticks in the future to set the timer to fire.
     *  \returns false if the timer couldn't be scheduled (ticks too big).
     */
    virtual bool set(ticks_t ticks) = 0;

    /*! Return whether a timer is set and queued for callback.
     * This function is side effect free.
     *
     *  \returns True if the timer is set; else false.
     */
    virtual bool isSet() = 0;

    /*! Get the remaining clock ticks before a timer will be triggered. This
     * may return 0 if the timer is about to be triggered. This will return 0
     * if the timer is not set.
     * This function is side effect free.
     *
     * \returns The number of remaining ticks before the timer will be triggered.
     */
    virtual ticks_t remaining() = 0;
};

/*! Interface of threads (runnable side): These objects are created and implemented by the modelling components and
 * a pointer to such an interface is passed to SchedulerInterfaceForComponents::createThread().
 * The scheduler uses this interface to run the thread and control the thread execution.
 */
class SchedulerRunnable: public SchedulerObject
{
public:
    /*! Main thread function. Thread entry point.
     * When this function returns the thread will no longer be run and threadProc() will never be called again
     * for this SchedulerThread instance.
     * The thread usually does not return from this function while the thread is running.
     * The threadProc() is supposed to call SchedulerInterfaceForComponents::wait(0, ...) after it completed its
     * initialisation code.
     * The threadProc() is supposed to call SchedulerInterfaceForComponents::wait(t>=0, ...) after it completed t ticks
     * worth of work.
     * Within the context of this function one should not create/destroy any other threads or scheduler objects.
     */
    virtual void threadProc() = 0;

    /*! Break the current quantum in ticks time (relative to the start of the quantum) or soon after that.
     * Ticks is always measured relative to the start of the current quantum, not the current
     * time inside the current quantum.
     * At the end of the broken quantum the thread must call wait(total_ticks) where
     * total_ticks is the number of ticks it executed since the last return from wait().
     * Breaking the quantum means calling wait().
     * breakQuantum(0) always means: Break as soon as possible.
     * Ticks are interpreted relative to the frequency set with SchedulerThread::setFrequency().
     * This function can be used to set the size of the next quantum when it is called from within wait() by the
     * scheduler.
     * When this function is called from within wait() it will set the size of the next
     * quantum which will start when wait() returns. The default quantum size will not
     * be used and not be relevant in this case.
     * This function can also be called in the middle of a quantum (i.e. not from wait()). If ticks
     * specifies a time which has already passed by the threads local time the thread should break
     * the quantum as soon as possible. If ticks specifies a time which has not yet passed the thread
     * should break at the specified time or soon after the specified time has passed.
     * Calling this function again with a different value in the same quantum will overwrite the previous value.
     * The previous value will then have no effect at all.
     * This function is only called by the code implementing the SchedulerInterfaceForComponents. It will not be called
     * by peripherals.
     * Peripherals must use the function SchedulerInterfaceForComponents::addSynchronisationPoint() instead which will
     * in turn make use of this function.
     *
     * \param ticks Requested quantum end point in the future relative to the start of the current quantum (inside
     * wait(): size of the next quantum) in ticks.
     *        The ticks are relative to the frequency set with SchedulerThread::setFrequency().
     *
     * \warning This function is deprecated. Any implementation of SchedulerInterfaceForComponents must use
     *          QuantumKeeper::sync() instead.
     */
    virtual void breakQuantum(ticks_t ticks = 0) = 0;

    /*! Stop (pause) request: Set stop request flag.
     * Request the simulation of the whole system to pause as soon as possible such that this runnable is in a useful
     * state for inspection through a debugger for example (e.g. at an instruction boundary for a CPU component).
     * This function may be called from any host thread. It may be called while the simulation is
     * running (in fact, this is the very purpose of this function). This function will always immediately
     * return before the simulation is stopped. This function will not block the caller until the
     * simulation is stopped.
     * The simulation will stop as soon as possible in response to this call depending on the syncLevel
     * of this runnable.
     * In response to this call the simulation will call the function SchedulerInterfaceForComponents::stopAcknowledge()
     * which in turn then must block the simulation thread while the simulation should be paused.
     * This function must not call stopAcknowledge() directly but should only set up a state
     * such that the simulation knows it needs to stop at the very next sync point defined by the
     * syncLevel of this runnable. This state should be reset by the stopAcknowledge()
     * function by calling clearStopRequest().
     * This function is used by modelling components to stop the simulation from within the simulation thread
     * (external breakpoints etc) and also asynchronously from debuggers from the debugger thread.
     * Calling this function again (from any host thread) before stopAcknowledge() has reset the
     * stop request using SchedulerRunnable::clearStopRequest() is harmless and will only stop the
     * simulation once.
     * Returns true when the runnable is accepting the stop request and will stop later on.
     * Returns false when the runnable is not accepting the stop request. In this case the scheduler
     * needs to stop the simulation when the runnable returns control to the scheduler (wait() etc).
     */
    virtual bool stopRequest() = 0;

    /*! Clear stop request flag.
     * This function is only ever called from SchedulerInterfaceForComponents::stopAcknowledge().
     * This means it will always be called from the simulation thread.
     * It must clear the stop request flag.
     */
    virtual void clearStopRequest() = 0;

    /*! Set/get thread property.
     * Configure detailed aspects of temporally decoupled threads, that is which do work in quantums.
     */
    enum ThreadProperty
    {
        // scheduler configures runnable:
        TP_BREAK_QUANTUM,             // set: the next quantum will be of this size, get: last value set
                                      // NOTE: this is deprecated, the next quantum size is given by
                                      // QuantumKeeper::getNextSyncPoint()
        TP_DEFAULT_QUANTUM_SIZE,      // set: when wait() returns the next quantum will be of this size, unless
                                      // breakQuantum() was called from that wait(), get: current default quantum size
                                      // NOTE: this is deprecated, the global quantum is set/get via
                                      // QuantumKeeper::set/getGlobalQuantum()
        TP_COMPILER_LATENCY,          // set: set compiler latency (max interval in which generated straight line code
                                      // checks for signals and the end of the quantum), get: current compiler latency
        TP_MIN_SYNC_LATENCY,          // set: set synchronization latency (min interval between generated straigt line code
                                      // synchronization points), get: current synchronization latency
        TP_MIN_SYNC_LEVEL,            // set: make sure that the syncLevel is at least N (0..3), get: last min syncLevel
        TP_CPI_MUL,                   // set: multiplier for calculating CPI (Cycle Per Instruction) used when updating
                                      // local time of associated QuantumKeeper, get: last value set
        TP_CPI_DIV,                   // set: divider for calculating CPI, get: last value set

        // runnable configures scheduler:
        // stack size:
        // get: must return the desired stack size for the thread in bytes. If this returns false
        //      or a low value this will use the default stack size determined by the scheduler.
        //      Not all schedulers may make use of this field.
        //      If a scheduler supports setting the stack size it will request this from within
        //      SchedulerInterfaceForComponents::createThread/createCoreThread()
        //      and/or SchedulerThread::start(). Should return a constant value.
        // set: should always return false and ignore the value, should never be called by a scheduler
        TP_STACK_SIZE = 0x80,
    };
    virtual bool setThreadProperty(ThreadProperty property, uint64_t value) = 0;
    virtual bool getThreadProperty(ThreadProperty property, uint64_t &valueOut) = 0;

protected:
    /*! Protected virtual destructor: Do not allow to destroy instances through this interface.
     * Modelling components control the lifetime of this object. It must live at least as long as
     * the corresponding SchedulerThread object exists.
     */
    virtual ~SchedulerRunnable() {}
};

/*! Modified version of SchedulerRunnable interface class: getName() is renamed here to getRunnableName().
 * The sole reason for the existence of this class is to disambiguate this from other classes which might
 * have a getName() method with a different prototype or different semantics which then defeats multiple
 * inheritance.
 * The rest of the interface and semantics of this class is identical to class SchedulerRunnable.
 */
class SchedulerRunnableWithGetRunnableName: public SchedulerRunnable
{
private:
    // hide original method name by making it private and call renamed method
    virtual const char *getName() const { return getRunnableName(); }
public:
    // publish renamed method
    virtual const char *getRunnableName() const = 0;
};

/*! Interface that provides a set of methods for managing and interacting with the time quantum of temporally decoupled
 * threads.
 * These objects are accessed using the SchedulerThread::getQuantumKeeper() function.
 * Modelling components use this interface to talk to the scheduler.
 */
class QuantumKeeper: public SchedulerObject
{
public:
    /*! Sets the value of the global quantum interpreted relative to the frequency set with
     * SchedulerThread::setFrequency() of the associated thread.
     * The global quantum is the maximum time a thread can run ahead of simulation time.
     * All threads must synchronize on timing points that are multiples of the global quantum.
     */
    virtual void setGlobalQuantum(ticks_t ticks) const = 0;

    /*! Returns the value of the global quantum interpreted relative to the frequency set with
     * SchedulerThread::setFrequency() of the associated thread.
     */
    virtual ticks_t getGlobalQuantum() const = 0;

    /*! Sets the value of the local time to the value passed as an argument.
     * \param ticks local time value interpreted relative to the frequency set with SchedulerThread::setFrequency() of
     * the associated thread.
     */
    virtual void setLocalTime(ticks_t ticks) = 0;

    /*! Increments the value of the local time by the value passed as an argument.
     * \param ticks local time value interpreted relative to the frequency set with SchedulerThread::setFrequency() of
     * the associated thread.
     */
    virtual void incLocalTime(ticks_t ticks) = 0;

    /*! Returns the value of the local time interpreted relative to the frequency set with
     * SchedulerThread::setFrequency() of the associated thread.
     */
    virtual ticks_t getLocalTime() const = 0;

    /*! Returns the value of the current time, that is the current simulated time plus the local time.
     */
    virtual ticks_t getCurrentTime() const = 0;

    /*! The method getNextSyncPoint() returns the absolute time of the next global synchronisation point.
     *
     * \return Next global synchronisation point interpreted relative to the frequency set with
     * SchedulerThread::setFrequency() of the associated thread.
     */
    virtual ticks_t getNextSyncPoint() = 0;

    /*! Checks whether a synchronisation is required.
     *
     * \return \c true when the current time is greater than the next global synchronisation point.
     */
    virtual bool needSync() = 0;

    /*! The method sync() must call SchedulerInterfaceForComponents::wait(local_time, ...) to suspend the thread until
     * simulation time equals current time, effectively triggering a local synchronisation, and then call reset().
     */
    virtual void sync() = 0;

    /*! The method reset() might calculate the next global synchronisation point later returned by getNextSyncPoint().
     * It must then set the local time back to zero.
     */
    virtual void reset() = 0;

protected:
    /*! Protected virtual destructor: Do not allow to destroy instances through this interface.
     * The scheduler implementation controls the lifetime of this object.
     * It must live at least as long as the corresponding SchedulerThread object exists.
     */
    virtual ~QuantumKeeper() {}
};

/*! Interface of threads (thread instance/scheduler side).
 * These objects are created using the SchedulerInterfaceForComponents::createThread() function.
 * The modelling component uses this interface to talk to the scheduler.
 */
class SchedulerThread: public SchedulerObject
{
public:
    /*! Destructor: May or may not kill the thread, depending on whether the underlying
     * scheduler implementation supports killing threads or not. Note that killing threads
     * without their cooperation is always unclean as it may leak resources. The only clean
     * way to end a thread is to signal the thread to return from its threadProc() function,
     * for example by using an exception which is caught in the threadProc() function.
     * Destroying this object before start() was called should never start the thread.
     * Destroying this object after start() was called may kill the thread immediately or
     * may leave the thread running until it returns from its threadProc().
     */
    virtual ~SchedulerThread() {}

    /*! Sets/resets the specified frequency source to be the parent clock for this thread.
     * This clock is used to interpret the ticks parameter of breakQuantum().
     * Specifying 0 is valid and will be ignored.
     * This object must register/unregister a FrequencyObserver to observe and respond to any frequency changes.
     *
     * \param frequencySource A pointer to the new frequency source.
     */
    virtual void setFrequency(FrequencySource* frequencySource) = 0;

    /*! Start thread.
     * This calls threadProc() immediately which in turn must call wait(0, ...)
     * after the initialisation is done in order for start() to return.
     * Start will only run the threadProc() function of the associated thread and no other threads.
     * Calling start() on an already started thread has no effect.
     * Calling start() on a thread which already terminated (threadProc() returned) has no effect.
     */
    virtual void start() = 0;

    /*! Returns the quantum keeper of this thread.
     * The qantum keeper is used for a temporally decoupled thread only.
     */
    virtual QuantumKeeper * getQuantumKeeper() = 0;

    // See also: SchedulerInterfaceForComponents::wait(ticks_t, FrequencySource*)
};

/*! ThreadSignal:
 * A non schedulable but waitable event on which many threads may wait.
 * When the event is signalled all waiting threads are scheduled to run.
 */
class ThreadSignal: public SchedulerObject
{
public:
    /*! Use destructor to destroy thread signals.
     * Destroying this object while threads are waiting for it will leave the threads unscheduled.
     */
    virtual ~ThreadSignal() {}

    /*! Notify the event, waking up any waiting threads.
     * This may be called from any threadProc() and also from outside threadProc().
     * Calling this when no thread is waiting on this signal is allowed. Then this call is ignored.
     */
    virtual void notify() = 0;

    // See also: SchedulerInterfaceForComponents::wait(ThreadSignal*)
};

/*! SchedulerCallback:
 * Callback base class for callbacks registered with for SchedulerInterfaceForComponents::addCallback/removeCallback().
 */
class SchedulerCallback: public SchedulerObject
{
public:
    /*! Callback function.
     * Always called on the simulation thread as soon as possible after the callback was registered with
     * SchedulerInterfaceForComponents::addCallback().
     * Callbacks automatically remove themselves after they were called. It is not necessary (nor allowed) to call
     * SchedulerInterfaceForComponents::removeCallback(this) from within the callback.
     * It is not allowed to call SchedulerInterfaceForComponents::add/removeCallback() from within this callback.
     */
    virtual void schedulerCallback() = 0;

protected:
    /*! Protected virtual destructor: Do not allow to destroy instances through this interface. */
    virtual ~SchedulerCallback() {}
};

/*! SchedulerInterfaceForComponents:
 * This interface is used by modelling components to create threads, timers etc.
 * This interface is usually not used by the owner of the scheduler. Every simulation framework must implement this
 * interface and can put any kind of scheduler behind this interface.
 * Modelling components usually use this to get access to this interface:
 * \code
 * sg::obtainComponentInterfacePointer<sg::SchedulerInterfaceForComponents>(simulationContext->getGlobalInterface(),
 *                                                                          "scheduler")
 * \endcode
 * \see sg/SGComponentRegistry.h
 */
class SchedulerInterfaceForComponents: public eslapi::CAInterface
{
public:
    // CAInterface related stuff
    static eslapi::if_name_t IFNAME() { return "sg.SchedulerInterfaceForComponents"; }
    static eslapi::if_rev_t IFREVISION() { return 0; }
    virtual eslapi::CAInterface *ObtainInterface(eslapi::if_name_t ifName,
                                                 eslapi::if_rev_t minRev,
                                                 eslapi::if_rev_t *actualRev) = 0;

    // Main interface, used by modelling components
    //
    // Note: Modelling components which want to use these scheduler objects should generally use the generic
    // scheduler related modelling components instead of using the functionality of this module directly:
    // - Use ClockTimer and ClockTimer64 instead of using createTimer() directly.
    // - Use AsyncSignal instead of using addCallback() and removeCallback() directly.
    // - Use MasterClock and ClockDivider to create clock trees instead of using FrequencySource and FrequencyObserver
    //   directly.

    /*! Creates a new Timer object with the specified name and callback object.
     * When the Timer fires TimerCallback::timerCallback() will be called.
     * If callback is NULL this call returns NULL and is ignored.
     * Used by: ClockTimer, ClockTimer64
     * \param name The instance name of the timer. If name is NULL it gets the name '(anonymous timer)'.
     *        This function will make a copy on name.
     * \param callback Timer callback function (called when the timer expires).
     * \returns An object implementing Timer. (Always != NULL except when callback == 0.)
     */
    virtual Timer* createTimer(const char* name, TimerCallback *callback) = 0;

    /*! Create a new thread.
     * See also related classes SchedulerThread and SchedulerRunnable.
     * This function does not yet start the new thread. To start the new thread call SchedulerThread::start().
     * Destroying the returned object may or may not kill the thread, see SchedulerThread destructor.
     * If runnable is NULL this call returns NULL and is ignored.
     * Used by: CT cores
     * \param name The instance name of the thread. Ideally the hierarchical name of the modelling component which owns
     *        the thread is included in the name.
     *        If name is NULL it gets the name '(anonymous thread)'. This function will make a copy of name.
     * \param runnable Object which implements the SchedulerRunnable interface. This is the object which contains the
     *        actual thread functionality.
     *        The returned thread will use this interface to communicate with the thread implementation in the modelling
     *        component.
     * \returns An object implementing SchedulerThread. (Always != NULL except when runnable was NULL.)
     */
    virtual SchedulerThread *createThread(const char* name, SchedulerRunnable *runnable) = 0;

    /*! Create a thread signal.
     * A thread signal is a non schedulable but waitable event on which many threads may wait.
     * When the event is signalled all threads which wait on this events are scheduled to run.
     * Destroying the returned object while threads are waiting for it will leave the threads unscheduled.
     * Used by: CT cores
     * \param name The instance name of the thread signal. Ideally the hierarchical name of the modelling component
     *        which owns the thread is included in the name.
     *        If name is NULL it gets the name '(anonymous thread signal)'. This function will make a copy on name.
     * \returns A pointer to an object implementing the ThreadSignal.
     */
    virtual ThreadSignal* createThreadSignal(const char* name) = 0;

    /*! Wait: Block current thread and run other threads for some time.
     * This function should only be called from within a SchedulerRunnable::threadProc() context.
     * Calling this from a context outside of a threadProc() is valid and has no effect.
     * It will block the currently running thread for the specified amount of time and let
     * other threads run.
     * This function blocks while the other threads etc are running and returns
     * when the calling thread should continue to run. This is the coroutine switching point.
     * Typically a thread calls wait(n) in its loop each time it completed n ticks of work.
     * n is called a quantum.
     * ticks may also be 0: This means that the current thread is potentially blocked and other callbacks which
     * are pending (if any) are run, but no time is advanced for this thread and this thread is most likely
     * scheduled again immediately.
     * A timebase of NULL is valid and will result in this call being ignored.
     * A timebase frequency of 0.0 is valid and will result in this call being ignored.
     * The time to wait for should be calculated as 'ticks / timebase->getFrequency()'.
     * \param ticks Time to wait for. This is relative to the frequency specified by 'timebase'.
     * \param timebase Specifies how to interpret ticks in terms of time.
     */
    virtual void wait(ticks_t ticks, FrequencySource *timebase) = 0;

    /*! Wait on thread signal.
     * Blocks the current thread indefinitely until threadSignal->notify() is called.
     * This function should be called from within a SchedulerRunnable::threadProc() context.
     * Calling this from a context outside of a threadProc() is valid and has no effect.
     * Calling this with threadSignal NULL will have no effect.
     * This function returns as soon as the calling thread can continue to run.
     * \param threadSignal Thread signal object which should be waited on.
     */
    virtual void wait(ThreadSignal *threadSignal) = 0;

    /*! Sets the value of the global quantum.
     * The global quantum is the maximum time a thread can run ahead of simulation time.
     * All threads must synchronize on timing points that are multiples of the global quantum.
     * \param ticks global quantum value measured in timebase units.
     *        The value should be calculated as 'ticks / timebase->getFrequency()'.
     * \param timebase Specifies how to interpret ticks in terms of time.
     */
    virtual void setGlobalQuantum(ticks_t ticks, FrequencySource * timebase) = 0;

    /*! Returns the value of the global quantum in seconds.
     */
    virtual double getGlobalQuantum() = 0;

    /*! Add future global synchronisation point in time.
     * Modelling components can call this function to provide a hint to the scheduler implementation
     * when a potentially useful global synchronisation point will occur in the future.
     * The scheduler uses this information to determine the quantum sizes of threads as
     * they get scheduled.
     * Calling this function again will add another global synchronisation point.
     * Synchronisation points automatically vanish when the time is reaching them.
     * \param ticks Time relative to the start of the current quantum (for threads) or relative
     *        to the current scheduler time (now) for all other callbacks. Measured in timebase units.
     *        The time in the future should be calculated as 'ticks / timebase->getFrequency()'.
     * \param timebase Specifies how to interpret ticks in terms of time.
     */
    virtual void addSynchronisationPoint(ticks_t ticks, FrequencySource *timebase) = 0;

    /*! Return the next future global synchronisation point in time.
     * Modelling components can call this function to get a hint for when a potentially useful global synchronisation
     * point will occur in the future.
     * The quantum keeper uses this information to determine when core threads need to synchronize.
     * \return next global synchronisation point in seconds, relative to the current simulated time.
     */
    virtual double getNextSyncPoint() = 0;

    /*! Schedule a callback in the simulation thread.
     * This method may be called from any host thread and is thread safe.
     * The callback function (callback->schedulerCallback()) will always be called from the simulation thread (host
     * thread which runs the simulation).
     * It will be called as soon as the scheduler has a chance to respond to the addCallback() function.
     * Multiple callbacks may be pending any point in time.
     * The scheduler can call these callbacks in any order.
     * It is not allowed to call addCallback()/removeCallback() from within the callback function.
     * A callback is automatically removed once it was called.
     * It is generally not necessary to remove callbacks unless a pending callback which was not yet called should be
     * canceled for example when the object implementing the callback function gets destroyed.
     * When callback is NULL this call is ignored.
     * Used by: AsyncSignal
     * \param callback The callback object to call.
     */
    virtual void addCallback(SchedulerCallback *callback) = 0;

    /*! Remove all callbacks scheduled using addCallback() for this callback object.
     * This may be called from any host thread and is thread safe.
     * When callback is NULL or is an unknown callback object or a callback which was already called
     * (or is currently being called) this call is ignored.
     * The specified callback will no longer be called after this function returned.
     * It may, however, be called while execution control is inside this function.
     * It is generally not necessary to remove callbacks unless a pending callback which was not yet called should be
     * canceled for example when the object implementing the callback function gets destroyed.
     * Used by: AsyncSignal
     * \param callback The callback object to remove.
     */
    virtual void removeCallback(SchedulerCallback *callback) = 0;

    /*! Get current elapsed simulated time in seconds since the scheduler was created.
     * The granularity of this clock is determined by the timers and their
     * expiry intervals and by the intervals of the wait() statements.
     * It always accurately reflects the time on the last timer callback invocation or
     * the last return from SchedulerThread::wait(), whichever occurred last.
     * The return values are guaranteed to monotonically increase over (real or simulated) time.
     * Used by: ClockDivider and MasterClock (ClockSignalProtocol::currentTicks())
     * \returns Current simulated time in seconds.
     */
    virtual double getCurrentSimulatedTime() = 0;

    /* Retrieve local time of currently running temporally decoupled thread.
     * Returns Local time in seconds.
     *
     * WARNING! This private and undocumented function is not intended to be
     * supported and will definitely change.
     */
    virtual double getCurrentLocalTime() = 0;

    /* Set local time of currently running temporally decoupled thread.
     *
     * WARNING! This private and undocumented function is not intended to be
     * supported and will definitely change.
     */
    virtual void setCurrentLocalTime(ticks_t ticks, FrequencySource *timebase) = 0;

    /*! Stop (pause) request: Request the simulation of the whole system to pause.
     * This function may be called from any host thread. It may be called while the simulation is
     * running (in fact, this is the very purpose of this function). This function will always immediately
     * return before the simulation is stopped. This function will not block the caller until the
     * simulation is stopped.
     * The simulation will stop as soon as possible in response to this call depending on the syncLevels
     * of the threads in the system.
     * In response to this call the simulation will call the function stopAcknowledge() which
     * in turn then must block the simulation thread while the simulation should be paused.
     * This function must not call stopAcknowledge() directly but should only set up a state
     * such that the simulation knows it needs to stop at the very next sync point defined by the
     * syncLevels in the system. This state should later be reset by the stopAcknowledge()
     * function by calling SchedulerRunnable::clearStopRequest().
     * This function is used by modelling components to stop the simulation from within the simulation thread
     * (breakpoints etc) and also asynchronously from debuggers from the debugger thread.
     * Calling this function again (from any host thread) before stopAcknowledge() has reset the
     * stop request using SchedulerRunnable::clearStopRequest() is harmless and will only stop the
     * simulation once.
     * Note that the simulation may also stop (i.e. call stopAcknowledge()) spontaneously without
     * a previous stopRequest(). This happens for example when a modelling component hits a breakpoint.
     * A stopRequest() is sufficient, but not necessary, to stop the simulation.
     * The scheduler implementation of this function should generally try forward this stopRequest()
     * to the currently running runnable (see SchedulerRunnable::stopRequest()) (only when stopRequest()
     * is called from the simulation thread). When the runnable accepted the stopRequest()
     * (SchedulerRunnable::stopRequest() returned true) the scheduler does not need to
     * do anything in addition as the runnable will eventually respond with a stopAcknowledge() call.
     * If the runnable did not accept the stopRequest() (SchedulerRunnable::stopRequest() returned false) or
     * if this function is called outside of the context of any runnable (e.g. from a callback function) or
     * from a non-simulation host thread then the scheduler is responsible for handling the stopRequest() itself
     * by calling stopAcknowledge() as soon as possible.
     * The entire stop handling mechanism should not change the scheduling order or model behavior in any way
     * (non-intrusive debugging).
     * Used by: CT cores, peripherals, debuggers
     */
    virtual void stopRequest() = 0;

    /*! Block simulation thread until being told to resume.
     * This function is being called from within the simulation thread in response to a call to
     * stopRequest() or also spontaneously (breakpoint hit, debugger stop etc).
     * It will always be called from the simulation thread.
     * The scheduler must block inside this function.
     * This function must return as soon as the simulation should be resumed.
     * The scheduler usually implements a thread safe mechanism in this function which allows the simulation
     * thread to be blocked and resumed from another host thread (usually the debugger thread).
     * Calling this function from a non-simulation host thread is wrong by design and is forbidden.
     * This function must clear the stop request which lead to calling this function by calling
     * runnable->clearStopRequest().
     * This function should not have any side effects except than blocking the simulation thread.
     * Used by: CT cores.
     * \param runnable Pointer to the runnable instance which called this function or NULL when not called from a
     *        runnable. If not NULL this function will call runnable->clearStopRequest() once it is safe to do so (with
     *        respect to non-simulation host threads).
     */
    virtual void stopAcknowledge(SchedulerRunnable *runnable) = 0;
};

// see also scx/scx_simcontrol_if.h: scx::scx_create_default_scheduler_mapping(scx::scx_simcontrol_if *simcontrol);

} // namespace sg

#endif
