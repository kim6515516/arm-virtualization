/*
 * @SOURCE_HEADER@
 *
 * @This_is_a_template_file___Feel_free_to_edit@
 *
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

#ifndef SCX_SIMULATION_CONTROLLER__H
#define SCX_SIMULATION_CONTROLLER__H

/* Includes */
#include "GlobalDefs.h"

#include <systemc>
#include <list>

#include <TxLib/TxLib.h>
#include <scx/scx.h>

/* Forward declarations */
namespace eslapi
{
    class CAInterface;
}
namespace scx
{
    class scheduler_mapping;
}

/* Namespaces */

/*
 * SystemC eXport support namespace.
 */
namespace scx {

/* Datatypes */

/*
 * Default simulation controller.
 */
class scx_simcontroller: public scx_simcontrol_if, public sc_core::sc_module {

    /* Construction */
    public:
        explicit scx_simcontroller(sc_core::sc_module_name);
        virtual ~scx_simcontroller();

    /* scx_simcontrol_if interface */

    /* Scheduler creation */
        virtual eslapi::CAInterface* get_scheduler();

    /* Report handler creation */
        virtual scx::scx_report_handler_if * get_report_handler();

    /* Simulation requests */
        virtual void run();
        virtual void stop();
        virtual bool is_running();
        virtual void shutdown();

    /* Simulation call-backs */
        virtual void add_callback(scx_simcallback_if * callback_obj);
        virtual void remove_callback(scx_simcallback_if * callback_obj);

    /* Simulation stop implementation */
        virtual void stop_acknowledge(sg::SchedulerRunnable *runnable);

    /* Simulation idle implementation */
        virtual void process_idle();

    /* Implementation */
    private:

        /* Typedefs */
        enum status_t { /* Simulation statuses */
            SCX_SHUTDOWN,
            SCX_RUNNING,
            SCX_STOPPED
        };

        /* Member variables */
        sc_core::sc_event m_stop_event;
            /* Event for stop simulation request */
        TxEvent m_run_event;    /* Signals run simulation requested */
        status_t m_status;      /* Simulation status */
        TxMutex m_status_mutex; /* Mutex for simulation status */
        std::list<scx_simcallback_if *> m_callbacks;
            /* List of registered simulation call-backs */
        TxMutex m_callbacks_mutex;
            /* Mutex for list of registered simulation call-backs */
        eslapi::CAInterface* m_scheduler;
            /* Scheduler interface */
        bool m_clearStopRequest;    /* To not ignore run simulation request */
        unsigned int m_idle_period; /* Idle period while simulation stopped */
        bool m_disable_idle;        /* Idle processing disabled? */

        /* Call-backs handling */
        void notify_stopped_all();
        void notify_running_all();
        void notify_idle_all();

        /* Send stop request to scheduler */
        void scheduler_stop_request();
};

}   /* namespace scx */

#endif  /* defined(SCX_SIMULATION_CONTROLLER__H) */
