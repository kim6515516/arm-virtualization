/*
 * my_simulation_controller.cpp - custom dummy simulation controller, provides
 * a custom scheduler mapping, uses the default simulation controller internally
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include "my_simulation_controller.h"
#include "my_scheduler_mapping.h"

/* Constructor and destructor */
my_simulation_controller::my_simulation_controller(): m_scheduler_mapping(0)
{
}

my_simulation_controller::~my_simulation_controller() 
{ 
    delete m_scheduler_mapping; 
}
    
/* scx::scx_simcontrol_if implementation (mostly forwarding to the default
 * implementation) */

/* Override scheduler creation to create custom scheduler adapter */
eslapi::CAInterface * my_simulation_controller::get_scheduler()
{
    if (!m_scheduler_mapping) {
        m_scheduler_mapping = new my_scheduler_mapping(scx::scx_get_default_simcontrol()->get_scheduler()->ObtainPointer<sg::SchedulerInterfaceForComponents>());
    }
    return m_scheduler_mapping;
}

scx::scx_report_handler_if * my_simulation_controller::get_report_handler()
{
    return scx::scx_get_default_simcontrol()->get_report_handler();
}

void my_simulation_controller::run()
{
    scx::scx_get_default_simcontrol()->run();
}
 
void my_simulation_controller::stop()
{
    scx::scx_get_default_simcontrol()->stop();
}

bool my_simulation_controller::is_running()
{
    return scx::scx_get_default_simcontrol()->is_running();
}
 
void my_simulation_controller::stop_acknowledge(sg::SchedulerRunnable * runnable)
{
    scx::scx_get_default_simcontrol()->stop_acknowledge(runnable);
}

void my_simulation_controller::process_idle()
{
    scx::scx_get_default_simcontrol()->process_idle();
}

void my_simulation_controller::shutdown()
{
    scx::scx_get_default_simcontrol()->shutdown();
}
 
void my_simulation_controller::add_callback(scx::scx_simcallback_if * callback_obj)
{
    scx::scx_get_default_simcontrol()->add_callback(callback_obj);
}

void my_simulation_controller::remove_callback(scx::scx_simcallback_if * callback_obj)
{
    scx::scx_get_default_simcontrol()->remove_callback(callback_obj);
}
    
