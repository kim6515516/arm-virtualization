/*
 * my_simulation_controller.h - custom dummy simulation controller, provides a
 * custom scheduler mapping, uses the default simulation controller internally
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef MY_SIMULATION_CONTROLLER_H
#define MY_SIMULATION_CONTROLLER_H

/* Includes */
#include <scx/scx.h>

/* Forward declarations */
class my_scheduler_mapping;

/* Custom implementation of the simulation controller using our custom scheduler
 * adapter */
class my_simulation_controller: public scx::scx_simcontrol_if {
public:
    /* Constructor and destructor */
    my_simulation_controller();
    ~my_simulation_controller();
    
    /* scx::scx_simcontrol_if implementation (mostly forwarding to the default
     * implementation) */
    virtual eslapi::CAInterface * get_scheduler();
    virtual scx::scx_report_handler_if * get_report_handler();
    virtual void run();
    virtual void stop();
    virtual bool is_running();
    virtual void stop_acknowledge(sg::SchedulerRunnable * runnable);
    virtual void process_idle();
    virtual void shutdown();
    virtual void add_callback(scx::scx_simcallback_if * callback_obj);
    virtual void remove_callback(scx::scx_simcallback_if * callback_obj);
    
    /* Private data */
private:
    my_scheduler_mapping *m_scheduler_mapping;
};

#endif

