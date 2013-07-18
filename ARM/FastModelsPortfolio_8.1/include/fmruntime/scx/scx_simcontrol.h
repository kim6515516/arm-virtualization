/*
 * SCX: scx_simcontrol.h - SystemC eXport support: simulation control
 *                         interfaces definitions.
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef ARM_SCX_SIMCONTROL__H
#define ARM_SCX_SIMCONTROL__H

/*!
 * \file    scx_simcontrol.h
 * \brief   Simulation control interface definitions.
 * \date    Copyright 2011-2012 ARM Limited. All rights reserved.
 *
 * SystemC eXport support simulation control interface definitions.
 */

/* Includes */

/* Forwards */
namespace eslapi {
class CAInterface;
}
namespace sg {
class SchedulerRunnable;
}

/* Namespaces */

/*!
 * \brief   SystemC eXport support namespace.
 */
namespace scx {

/* Forwards */
class scx_report_handler_if;

/* Datatypes */

/*!
 * \brief   Base class for simulation control call-backs.
 *
 * This interface is implemented by the simulation engine and used by the
 * simulation controller to notify changes in the simulation state.
 */
class scx_simcallback_if {

    /* Notifications */
    public:

        /*!
         * \brief   Notifies that simulation is running.
         *
         * The simulation controller calls this function to notify that the
         * simulation is running and debuggers can be notified of the same.
         */
        virtual void notify_running() = 0;

        /*!
         * \brief   Notifies that simulation has stopped.
         *
         * The simulation controller calls this function to notify that the
         * simulation has stopped and debuggers can be notified of the same.
         */
        virtual void notify_stopped() = 0;

        /*!
         * \brief   Notifies that simulation is idle.
         *
         * The simulation controller periodically calls this function to notify
         * that the simulation is idle, typically while the simulation is
         * stopped, to allow clients to process idle activity, like for instance
         * GUI events processing and redrawing.
         */
        virtual void notify_idle() = 0;

    /* Implementation */
    protected:

        /*!
         * \brief   Destructor.
         *
         * This version of the function does not allow destroying instance
         * through this interface.
         */
        virtual ~scx_simcallback_if() {
        };
};

/*!
 * \brief   Simulation control interface.
 *
 * This interface must be implemented by the simulation controller, which
 * interacts with the simulation engine.
 * This interface is used by the simulation engine to access current
 * implementations of the scheduler and report handler, as well as to request
 * changes to the simulation state.
 *
 * All simulation requests provided by this interface are asynchronous and are
 * thus expected to return immediately, whether the corresponding operation has
 * completed or not.
 * Once the operation has been performed, the corresponding notification must
 * be sent back to the simulation that in turn notifies back all connected
 * debuggers accordingly to allow them to update their state.
 *
 * An implementation of this interface must be thread-safe, that is it must not
 * make assumptions about threads from which simulation requests are issued.
 */
class scx_simcontrol_if {

    /* Scheduler creation */
    public:

        /*!
         * \brief   Returns a pointer to the current implementation of the
         *          simulation scheduler.
         *
         * The get_scheduler() function is called by the simulation engine
         * to retrieve the scheduler implementation for the simulation at
         * construction time.
         *
         * \note    An implementation of this function does not need to be
         *          thread-safe.
         */
        virtual eslapi::CAInterface * get_scheduler() = 0;

    /* Report handler creation */

        /*!
         * \brief   Returns a pointer to the current implementation of the
         *          report handler.
         *
         * The get_report_handler() function is called by scx_initialize()
         * to retrieve the report handler implementation for the simulation at
         * construction time.
         *
         * \note    An implementation of this function does not need to be
         *          thread-safe.
         */
        virtual scx_report_handler_if * get_report_handler() = 0;


    /* Simulation requests */

        /*!
         * \brief   Requests to run the simulation.
         *
         * The run() function is called by the simulation engine upon receipt
         * of a CADI run request from a debugger.
         */
        virtual void run() = 0;

        /*!
         * \brief   Requests to stop the simulation as soon as possible, that
         *          is at the next \c wait().
         *
         * The stop() function is called by the simulation engine upon receipt
         * of a CADI stop request from a debugger, a component, or when a
         * breakpoint is hit.
         */
        virtual void stop() = 0;

        /*!
         * \brief   Returns whether the simulation is running.
         * \return  \c true when the simulation is running, \c false when it is
         *          paused or stopped.
         *
         * The is_running() function is called by the simulation engine upon
         * receipt of a CADI request from a debugger needing to know whether the
         * simulation is running.
         */
        virtual bool is_running() = 0;

        /*!
         * \brief   Blocks the simulation while the simulation is stopped.
         * \param   runnable specifies a pointer to the scheduler thread
         *          calling stop_acknowledge().
         *
         * This function is called by the scheduler thread to effectively stop
         * the simulation, as a side-effect of calling stop() to request the
         * simulation to be stopped.
         *
         * An implementation of this function must call clearStopRequest() on
         * the given \a runnable (when not \c NULL).
         */
        virtual void stop_acknowledge(sg::SchedulerRunnable * runnable) = 0;

        /*!
         * \brief   Process idle activity while the simulation is stopped.
         *
         * This function is called by the scheduler thread whenever idle to
         * enable idle activity to be processed.
         *
         * An implementation of this function might simply call
         * scx_simcallback_if::notify_idle() on all registered clients.
         */
        virtual void process_idle() = 0;

        /*!
         * \brief   Requests to shutdown the simulation.
         *
         * The shutdown() function is called by the simulation engine to notify
         * it wants the simulation to shutdown.
         *
         * Once the simulation has shut down it cannot be ran again.
         *
         * \note    There are no call-backs associated with shutdown().
         */
        virtual void shutdown() = 0;

    /* Call-backs */

        /*!
         * \brief   Registers call-backs with the simulation controller.
         * \param   callback_obj specifies a pointer to the object whose member
         *          functions will be called as call-backs.
         *
         * A client should call this function to register with the simulation
         * controller a call-backs object that will handle notifications from
         * the simulation.
         */
        virtual void add_callback(scx_simcallback_if * callback_obj) = 0;

        /*!
         * \brief   Removes call-backs from the simulation controller.
         * \param   callback_obj specifies a pointer to the object to remove.
         *
         * A client should call this function to un-register any call-backs
         * object it might have previously register with the simulation.
         */
        virtual void remove_callback(scx_simcallback_if * callback_obj) = 0;

    /* Implementation */
    protected:

        /*!
         * \brief   Destructor.
         *
         * This version of the function does not allow destroying instance
         * through this interface.
         */
        virtual ~scx_simcontrol_if() {
        };
};

/* Functions */

/*!
 * \brief   Returns a pointer to the default implementation of the simulation
 *          controller provided with Fast Models.
 */
extern scx_simcontrol_if *
scx_get_default_simcontrol();

}   /* namespace scx */

#endif  /* defined(ARM_SCX_SIMCONTROL__H) */
