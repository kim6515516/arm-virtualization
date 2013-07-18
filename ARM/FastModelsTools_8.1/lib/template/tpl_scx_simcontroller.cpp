/*
 * @SOURCE_HEADER@
 *
 * @This_is_a_template_file___Feel_free_to_edit@
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include "GlobalDefs.h"
#include "scx_simcontroller.h"

#include <cstdlib>
#include <algorithm>
#include <cassert>

#include <sg/SGSchedulerInterfaceForComponents.h>

/* Namespaces */

/*
 * SystemC eXport support namespace.
 */
namespace scx {

/* Globals - Simulation controller */

/* Pointer to unique instance of simulation controller. */
static scx_simcontrol_if * default_simcontrol_ptr = NULL;

/* Functions */

/*
 * Constructs a new simulation controller.
 */
scx_simcontroller::scx_simcontroller(sc_core::sc_module_name name):
    sc_core::sc_module(name),
    m_run_event(0, 0),
    m_status(SCX_RUNNING),
    m_scheduler(NULL),
    m_clearStopRequest(false),
    m_idle_period(20),
    m_disable_idle(std::getenv("FM_SCX_DISABLE_IDLE") != NULL) {

    /* Process environmental settings */
    const char * idle_period_str = std::getenv("FM_SCX_IDLE_PERIOD");

    if (idle_period_str != NULL) {
        m_idle_period = std::max(1, std::atoi(idle_period_str));
    }
}

/*
 * Destructs this simulation controller.
 */
scx_simcontroller::~scx_simcontroller() {
    delete m_scheduler;
    m_scheduler = NULL;
    default_simcontrol_ptr = NULL;
}

/*
 * Returns a pointer to the current implementation of the simulation scheduler.
 */
eslapi::CAInterface *
scx_simcontroller::get_scheduler() {
    if (m_scheduler == NULL) {
        m_scheduler = scx_create_default_scheduler_mapping(this);
    }
    return (m_scheduler);
}

/*
 * Returns a pointer to the current implementation of the report handler.
 *
 * This version of the function returns the default implementation provided with
 * Fast Models.
 */
scx_report_handler_if *
scx_simcontroller::get_report_handler() {
    return (scx_get_default_report_handler());
}

/*
 * Requests to run the simulation.
 */
void
scx_simcontroller::run() {
    SCX_REPORT_INFO_VERB(SCX_DEBUG, "scx_simcontroller", "run()");

    /* Run simulation requested */
    TxCriticalSection lock(m_status_mutex);

    if (m_status == SCX_STOPPED) {
        m_run_event.SetEvent();
    } else if (m_status == SCX_RUNNING) {

        /* Clear previous stop request, else run() could be ignored */
        m_clearStopRequest = true;
    }
}

/*
 * Requests to stop the simulation as soon as possible, that is at the next
 * \c wait().
 */
void
scx_simcontroller::stop() {
    SCX_REPORT_INFO_VERB(SCX_DEBUG, "scx_simcontroller", "stop()");

    /* Stop simulation requested */
    TxCriticalSection lock(m_status_mutex);

    if (m_status == SCX_RUNNING) {
        scheduler_stop_request();

        /* Do not clear previous stop request, else stop() could be ignored */
        m_clearStopRequest = false;
    }
}

/*
 * Returns whether the simulation is running.
 */
bool
scx_simcontroller::is_running() {
    status_t status;

    /* Retrieve status */
    {
        TxCriticalSection lock(m_status_mutex);

        status = m_status;
    }
#if SYSTEMC_VERSION >= 20060505
    return (sc_core::sc_is_running() && (status == SCX_RUNNING));
#else
    return (sc_core::sc_get_curr_simcontext()->is_running()
            && (status == SCX_RUNNING));
#endif  /* SYSTEMC_VERSION */
}

/*
 * Requests to shutdown the simulation.
 */
void
scx_simcontroller::shutdown() {
    SCX_REPORT_INFO_VERB(SCX_DEBUG, "scx_simcontroller", "shutdown()");

    /* Shutdown simulation requested */
    TxCriticalSection lock(m_status_mutex);

    /* Stops SystemC simulation if not stopped already */
    if (m_status != SCX_SHUTDOWN) {

        /* Issue a stop request first, otherwise it could be ignored */
        if (m_status == SCX_RUNNING) {
            scheduler_stop_request();
        }

        /* Run next, otherwise it could deadlock */
        if (m_status == SCX_STOPPED) {
            m_run_event.SetEvent();
        }

        /* Shutdown... */
        m_status = SCX_SHUTDOWN;

        /* Disable the warning about sc_stop() being already called.
         * (We do this as we have no means to test whether something else,
         * for instance a slave, has already called sc_stop() and we are thus
         * called as part of the end_of_simulation() call-backs.) */
        sc_core::sc_actions a = sc_core::sc_report_handler::set_actions(
                sc_core::SC_ID_SIMULATION_STOP_CALLED_TWICE_,
                sc_core::SC_DO_NOTHING);
        sc_core::sc_stop();
        sc_core::sc_report_handler::set_actions(
                sc_core::SC_ID_SIMULATION_STOP_CALLED_TWICE_,
                a);
    }
}

/*
 * Registers call-backs with this simulation controller.
 */
void
scx_simcontroller::add_callback(scx_simcallback_if * callback_obj) {
    if (callback_obj != NULL) {
        TxCriticalSection lock(m_callbacks_mutex);

        m_callbacks.push_back(callback_obj);
    }
}

/*
 * Removes call-backs from this simulation controller.
 */
void
scx_simcontroller::remove_callback(scx_simcallback_if * callback_obj) {
    TxCriticalSection lock(m_callbacks_mutex);

    m_callbacks.remove(callback_obj);
}

/*
 * Block simulation while simulation is stopped.
 */
void
scx_simcontroller::stop_acknowledge(sg::SchedulerRunnable * runnable) {
    SCX_REPORT_INFO_VERB(SCX_DEBUG,
                         "scx_simcontroller",
                         "stop_acknowledge(runnable=%p)",
                         runnable);

    m_status_mutex.lock();

    /* Simulation running? */
    if (m_status == SCX_RUNNING) {

        /* Update status */
        m_status = SCX_STOPPED;

        /* Notify all clients
         * Unless stop request cleared by a simulation run request */
        if (! m_clearStopRequest) {
            m_status_mutex.unlock();
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scx_simcontroller", "stopped");
            notify_stopped_all();
            m_status_mutex.lock();
        }
    }

    /* Clear stop request (1) */
    m_status_mutex.unlock();
    if (runnable != NULL) {
        runnable->clearStopRequest();
    }
    m_status_mutex.lock();

    /* Simulation stopped? */
    if (m_status == SCX_STOPPED) {

        /* Wait for run simulation request
         * Unless stop request cleared by a simulation run request */
        if (! m_clearStopRequest) {
            m_status_mutex.unlock();
            if (! m_disable_idle) {

                /* Allow processing of potentially pending idle activity */
                while (m_run_event.TimedWait(m_idle_period)) {
                    process_idle();
                }
            } else {
                m_run_event.Wait();
            }
            SCX_REPORT_INFO_VERB(SCX_DEBUG, "scx_simcontroller", "running");
            m_status_mutex.lock();
        }

        /* Update status */
        if (m_status == SCX_STOPPED) {
            m_status = SCX_RUNNING;

            /* Notify all clients */
            m_status_mutex.unlock();
            notify_running_all();
            m_status_mutex.lock();
        }
    }

    /* Clear stop request (2) */
    m_clearStopRequest = false;

    /* Simulation shutdown? */
    if (m_status == SCX_SHUTDOWN) {
        SCX_REPORT_INFO_VERB(SCX_DEBUG, "scx_simcontroller", "shutdown");

        /* Issue a wait(0) so the SystemC scheduler gets a chance to pick up
         * the sc_stop().
         * (If we do not do this the models will just keep on calling
         * stop_ackowledge() in an endless loop if they do not wait() in the
         * meantime by chance.) */
        m_status_mutex.unlock();
        sc_core::wait(sc_core::SC_ZERO_TIME);
        return;
    }
    m_status_mutex.unlock();
}

/*
 * Process any potentially pending idle activity.
 */
void
scx_simcontroller::process_idle() {
    if (! m_disable_idle) {
        notify_idle_all();
    } else {
        static bool info_idle_disabled = true;

        if (info_idle_disabled) {
            info_idle_disabled = false;
            SCX_REPORT_INFO("scx_simcontroller",
                            "process_idle() disabled as FM_SCX_DISABLE_IDLE "
                            "was defined");
        }
    }
}

/*
 * Notify all clients simulation has stopped.
 */
void
scx_simcontroller::notify_stopped_all() {
    std::list<scx_simcallback_if *> tmpCallbacks;

    /* 1) Take a copy of call-backs list */
    {
        TxCriticalSection lock(m_callbacks_mutex);

        tmpCallbacks = m_callbacks;
    }

    /* 2) Use copy to notify clients */
    std::list<scx_simcallback_if *>::iterator i;

    for (i = tmpCallbacks.begin(); (i != tmpCallbacks.end()); i ++) {
        (* i)->notify_stopped();
    }
}

/*
 * Notify all clients simulation is running.
 */
void
scx_simcontroller::notify_running_all() {
    std::list<scx_simcallback_if *> tmpCallbacks;

    /* 1) Take a copy of call-backs list */
    {
        TxCriticalSection lock(m_callbacks_mutex);

        tmpCallbacks = m_callbacks;
    }

    /* 2) Use copy to notify clients */
    std::list<scx_simcallback_if *>::iterator i;

    for (i = tmpCallbacks.begin(); (i != tmpCallbacks.end()); i ++) {
        (* i)->notify_running();
    }
}

/*
 * Notify all clients simulation is idle.
 */
void
scx_simcontroller::notify_idle_all() {
    std::list<scx_simcallback_if *> tmpCallbacks;

    /* 1) Take a copy of call-backs list */
    {
        TxCriticalSection lock(m_callbacks_mutex);

        tmpCallbacks = m_callbacks;
    }

    /* 2) Use copy to notify clients */
    std::list<scx_simcallback_if *>::iterator i;

    for (i = tmpCallbacks.begin(); (i != tmpCallbacks.end()); i ++) {
        (* i)->notify_idle();
    }
}

/*
 * Send stopRequest() to scheduler.
 */
void
scx_simcontroller::scheduler_stop_request()
{
    sg::SchedulerInterfaceForComponents * scheduler =
        get_scheduler()->ObtainPointer<sg::SchedulerInterfaceForComponents>();

    if (scheduler) {
        scheduler->stopRequest();
    }
}

/*
 * Returns a pointer to the default implementation of the simulation controller
 * provided with Fast Models.
 */
scx_simcontrol_if * scx_get_default_simcontrol() {
    if (default_simcontrol_ptr == NULL) {
        static scx_simcontroller default_simcontroller("default_simcontroller");

        default_simcontrol_ptr = & default_simcontroller;
    }
    return (default_simcontrol_ptr);
}

}   /* namespace scx */
