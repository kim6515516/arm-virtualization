/*!
 * \file    SGSchedulerControlInterface.h
 * \brief   Abstract interface used by the simulation engine/framework to instantiate and control the standalone scheduler.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

#ifndef SGSCHEDULERCONTROLINTERFACE_H
#define SGSCHEDULERCONTROLINTERFACE_H

#include "eslapi/CAInterface.h"
#include "sg/SGstdint.h"

namespace scx
{
    class scx_simcallback_if;
}

namespace sg
{
    /*! base class for asynchronous events
     * the events are responsible for deleting themselves
     * Legacy: should be removed. Do not use in new code.
     */
    class AsyncEvent
    {
    public:
        virtual ~AsyncEvent(){};
        
    public:
        /*! action performed by an event, should return true to break processing loop */
        virtual bool processEvent() = 0;  
        /*! action performed when event is rejected */
        virtual void rejectEvent() = 0; 
    };
    

    /*! base class for idle cycle action handler
     * Legacy: should be removed. Do not use in new code.
     */
    class AsyncIdler
    {
    public:
        virtual ~AsyncIdler(){};
        
    public:
        /*! action performed at idle cycle*/
        virtual void idle() = 0;  
        /*! returns timeout in milliseconds between idle cycles */
        virtual unsigned getIdlePeriod() = 0; 
    };
    
    
    /*! SchedulerControlInterface:
     * This interface is used by the simulation engine or simulation framework to control the scheduler.
     * This interface is usually only used by the owner of the scheduler.
     * This interface is usually not used by components.
     * This interface is only implemented by the standalone scheduler.
     * This interface is not available for (not implemented by) the scheduler adaptation towards SystemC.
     * An instance of the standalone scheduler can be created using the global function createStandaloneScheduler().
     */
    class SchedulerControlInterface: public eslapi::CAInterface
    {
    public:
        // CAInterface related stuff
        static eslapi::if_name_t IFNAME() { return "sg.SchedulerControlInterface"; }
        static eslapi::if_rev_t IFREVISION() { return 0; }
        virtual eslapi::CAInterface *ObtainInterface(eslapi::if_name_t ifName, eslapi::if_rev_t minRev, eslapi::if_rev_t *actualRev) = 0;
        
        // --- main interface, used by simulation engine or simulation framework (owner of the scheduler). ---

        /*! Run scheduler until something stops it using stop().
         * This may only be called from the simulation thread and is not reentrant (i.e.
         * go() should not be called from within go() in any way.
         */
        virtual void go() = 0;
        
        /*! Stop the simulation as soon as possible.
         * This may be called from the simulation thread and from any other host thread.
         */
        virtual void stop() = 0;
        
        /*! Registers call-backs with the simulation controller.
         * A client should call this function to register with the simulation
         * controller a call-backs object that will handle notifications from
         * the simulation.
         */
        virtual void add_callback(scx::scx_simcallback_if * callback_obj) = 0;

        /*! Removes call-backs from the simulation controller.
         * A client should call this function to un-register any call-backs
         * object it might have previously register with the simulation.
         */
        virtual void remove_callback(scx::scx_simcallback_if * callback_obj) = 0;
        
        /*! Use this to destroy the scheduler (for example to destroy the standalone scheduler created with createStandaloneScheduler()).
         */
        virtual ~SchedulerControlInterface() {}
        
        // --- legacy stuff below this line -------------------------------------------------------------
        // The following stuff should ideally be removed but currently the CTModels and the
        // standalone and the SystemC simulation engine depend on this to marshal CADI calls onto the
        // simulation thread.
        
        /*! Start the main loop to process asynchronous events.*/
        virtual void mainEventLoop() = 0;
        
        /*! Stop the running scheduler and exit main event loop*/
        virtual void shutdown() = 0;

        /*! Push asynchronous event into event queue for processing in scheduler's thread*/
        virtual void pushAsyncEvent(AsyncEvent* ) = 0;

        /*! process all events in the queue by calling AsyncEvent::processEvent() in a loop*/
        /* should be only called from scheduler's thread  */
        virtual void processAsyncEvents() = 0;

        /*! Set handler to process idle cycle actions in mainEventLoop() when asynchronous event queue is empty
         * Should be removed. Components should use SchedulerInterfaceForComponents::addCallback() instead.
         */
        virtual void setAsyncIdler(AsyncIdler* ) = 0;
    };

    /*! Create standalone scheduler instance.
     * This function automatically creates a 'scheduler' component in the component registry below globalInterfaceOwner->ObtainInterface()
     * and registers all scheduler interfaces.
     * This standalone scheduler is only used when Fast Models are used standalone. 
     * This is not used in the SystemC context where the native SystemC scheduler is used instead.
     * 
     * \param globalInterfaceOwner
     *        createStandaloneScheduler() will register the SchedulerControlInterface, SchedulerTestInterface and the SchedulerInterfaceForComponents with the
     *        globalComponentRegistry (ComponentRegistry interface) object registered underneath globalInterfaceOwner.
     * \returns a newly created standalone scheduler instance. Destroy with delete.
     */
    SchedulerControlInterface *createStandaloneScheduler(eslapi::CAInterface *globalInterfaceOwner);

} // namespace sg

#endif
