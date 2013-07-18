/*
 * @SOURCE_HEADER@
 *
 * @This_is_a_template_file___Feel_free_to_edit@
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef SCX_SCHEDULER_MAPPING__H
#define SCX_SCHEDULER_MAPPING__H

/* Includes */
#include "GlobalDefs.h"

#include <systemc>
#include <list>
#include <map>
#include <queue>

#include <sg/SGSchedulerInterfaceForComponents.h>
#include <sg/Thread.h>
#include <eslapi/CAInterfaceRegistry.h>
#include <TxLib/TxMutex.h>

/* Forwards */
namespace eslapi
{
class CAInterface;
};

namespace scx
{

/* Internal classes */
class scheduler_mapping_Timer;
class scheduler_mapping_sc_thread;
class scheduler_mapping_Thread;
class scheduler_mapping_ThreadSignal;
class clear_stop_request_proxy_class;

// Simulation controller interface
class scx_simcontrol_if;

/* Datatypes */

/*
 * Scheduler implementation.
 */
class scheduler_mapping:
    public sg::SchedulerInterfaceForComponents,
    public sc_core::sc_module
{

// Constructor and destructor
public:
    explicit scheduler_mapping(scx_simcontrol_if *);
    virtual ~scheduler_mapping();

// CAInterface Implementation
    virtual eslapi::CAInterface * ObtainInterface(eslapi::if_name_t, eslapi::if_rev_t, eslapi::if_rev_t *);

// sg::SchedulerInterfaceForComponents interface, used by components
    virtual sg::Timer * createTimer(const char *, sg::TimerCallback *);
    virtual sg::SchedulerThread * createThread(const char *, sg::SchedulerRunnable *);
    virtual sg::ThreadSignal * createThreadSignal(const char *);
    virtual void wait(sg::ticks_t, sg::FrequencySource *);
    virtual void wait(sg::ThreadSignal *);
    virtual void setGlobalQuantum(sg::ticks_t, sg::FrequencySource *);
    virtual double getGlobalQuantum();
    virtual void addSynchronisationPoint(sg::ticks_t, sg::FrequencySource *);
    virtual double getNextSyncPoint();
    virtual void addCallback(sg::SchedulerCallback *);
    virtual void removeCallback(sg::SchedulerCallback *);
    virtual double getCurrentSimulatedTime();
    virtual double getCurrentLocalTime();
    virtual void setCurrentLocalTime(sg::ticks_t, sg::FrequencySource *);
    virtual void stopRequest();
    virtual void stopAcknowledge(sg::SchedulerRunnable *);

// Internal interface towards internal timer, thread and thread signal implementations

    // get verbose level
    // verbose variable is set by env var SCX_EVS_VERBOSE
    enum VerboseFlags // these need to be ored together
    {
        V_ALL     = 0x0001,         // all messages
        V_SYSTEMC = 0x0002,         // SystemC function calls
        V_GENERAL = 0x0004,         // general adapter messages
        V_TIMER   = 0x0010,         // timer calls
        V_THREAD  = 0x0020,         // thread calls
        V_THREAD_SIGNAL = 0x0040,   // thread signal calls
        V_ASYNC_CALLBACK = 0x0080,  // addCallback/removeCallback() calls
        V_EXEC    = 0x0100,         // execution control (stopRequest(), stopAcknowledge())
        V_OTHER   = 0x0800,         // addSynchronisationPoint(), getCurrentSimulationTime() calls
        V_SIMCONTROL = 0x1000       // simcontroller messages (see tpl_scx_simcontrol.h/cpp)
    };
    unsigned int get_verbose() const
    {
        return verbose;
    }

    /// called by Timer destructor when timer gets destroyed
    void remove_timer(scheduler_mapping_Timer *);

    /// called by Thread destructor when thread gets destroyed
    void remove_thread(scheduler_mapping_Thread *);

    /// called by ThreadSignal destructor when timer gets destroyed
    void remove_thread_signal(scheduler_mapping_ThreadSignal *);

    /// return current scheduler_mapping_sc_thread object or NULL if not in any threadProc() call
    scheduler_mapping_sc_thread *get_current_sc_thread();

    /// called by scheduler_mapping_sc_thread constructor when sc_threads get created/started
    void add_sc_thread(scheduler_mapping_sc_thread *);

    /// called by scheduler_mapping_sc_thread destructor when sc_threads get destroyed
    void remove_sc_thread(scheduler_mapping_sc_thread *);

    /// return true if there are potentially async callbacks pending
    /// (this function is inherently racy and it only used as a hint to make stuff efficient)
    bool has_pending_async_callbacks() const
    {
        return (! async_callbacks.empty());
    }

    /// process any potentially pending async callbacks
    void process_async_callbacks();

    /// process any potentially pending idle activity
    void process_idle();

    /// call stopAcknowledge() for async stops (block simulation)
    void stop_acknowledge_from_async_stop_callback();

    /// clear stop request flag
    void clear_stop_request();

    /// push async stop request
    void async_stop_request();

/* Implementation */
private:

    // sc_module override-ables
    virtual void before_end_of_elaboration();
    virtual void end_of_elaboration();
    virtual void start_of_simulation();
    virtual void end_of_simulation();

    // member variables

    // verbose level
    unsigned int verbose;

    // list of timers
    std::list<scheduler_mapping_Timer *> timers;

    // list of threads
    std::list<scheduler_mapping_Thread *> threads;

    // list of thread signals
    std::list<scheduler_mapping_ThreadSignal *> thread_signals;

    // map from SystemC process objects onto scheduler_mapping_Threads
    typedef std::map<sc_core::sc_object *, scheduler_mapping_sc_thread *> ThreadMap;
    ThreadMap sc_thread_map;

    // async event queue (addCallback()/removeCallback())
    typedef std::list<sg::SchedulerCallback *> AsyncCallbacksList;
    AsyncCallbacksList async_callbacks;

    // mutex for async event queue
    TxMutex async_callbacks_mutex;

    // thread ID of the currently running thread when inside processAsyncCallbacks(), else 0
    sg::threadId_t async_callbacks_processing_thread;

    // simulation controller (for stopAcknowledge)
    scx_simcontrol_if * simcontroller;

    // stop request flag for asynchronous stop requests (set by stopRequest(), cleared by
    // clear_stop_request_proxy/stopAcknowledge())
    bool stop_request;

    // forward clearStopRequest() calls from stopAcknowledge to the scheduler adapter itself
    clear_stop_request_proxy_class * clear_stop_request_proxy;

    // thread ID of the simulation thread
    sg::threadId_t simulation_thread_id;

    // scheduler interface registry
    eslapi::CAInterfaceRegistry schedulerInterfaceRegistry;

    /* Future synchronization points priority queue, expressed in absolute simulated time */
    std::priority_queue<double> m_sync_points;
};

}   // namespace scx

#endif  /* defined(SCX_SCHEDULER_MAPPING__H) */
