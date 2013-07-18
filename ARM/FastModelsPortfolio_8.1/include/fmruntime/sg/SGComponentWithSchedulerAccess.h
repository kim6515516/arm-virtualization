/*!
 * \file    SGComponentWithSchedulerAccess.h
 * \brief   Utility base class which simplifies/provide access to the SchedulerInterfaceForComponents and makes sure this is available.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

#ifndef SGCOMPONENTWITHSCHEDULERACCESS_H
#define SGCOMPONENTWITHSCHEDULERACCESS_H

#include "sg/SGComponent.h"

namespace sg
{
    class SchedulerInterfaceForComponents;
    class SimulationContext;

    /*! Utility class which provides (simplifies) access to the SchedulerInterfaceForComponents 
     * which is passed into components as part of the sg:SimulationContext upon instantiation.
     * 
     */
    class ComponentWithSchedulerAccess: public Component
    {
    public:        
        // constructor, obtains the SchedulerInterfaceForComponents from the simulation context
        ComponentWithSchedulerAccess(std::string const& name, sg::SimulationContext *context);
        
        // get the SchedulerInterfaceForComponents
        SchedulerInterfaceForComponents *getSchedulerInterfaceForComponents() const { return schedulerInterfaceForComponents; }
        
        // get the SimulationContext
        sg::SimulationContext *getSimulationContext() const { return simulationContext; }
        
    private:
        // private data
        
        // pointer to SchedulerInterfaceForComponents
        SchedulerInterfaceForComponents *schedulerInterfaceForComponents;
        // pointer to SimulationContext
        sg::SimulationContext *simulationContext;
    };
    
    /*! get SchedulerInterfaceForComponents pointer or NULL from SimulationContext
     * helper function in cases where deriving from Component is undesirable:
     * contextStr and instanceName are only used for error messages
     */
    SchedulerInterfaceForComponents *getSchedulerInterfaceForComponents(sg::SimulationContext *simulationContext, const char *contextStr, const std::string& instanceName);

} // namespace sg

#endif // SGCOMPONENTWITHSCHEDULERACCESS_H

