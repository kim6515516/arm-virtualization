/*!
 * \file    SGSimulationContext.h
 * \brief   Container for opaque references to 'global' objects.
 * \date    Copyright 2006,2011 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_SIMULATIONCONTEXT_H
#define ARM_SG_SIMULATIONCONTEXT_H

namespace eslapi { class CAInterface; }

namespace sg
{
class ComponentBase;    
class SimulationContext
{
public:
    // Note: Do not extend this class. Only extend the components and interfaces exposed through getGlobalInterface().
    // See getGlobalInterface() below.
    
    // virtual destructor
    virtual ~SimulationContext() {}
    
    // used by components to wire themselves up (and their CADI interfaces) to the 
    // 'simExec', 'cadiExec' and 'systemControl' ports of the simulation engine
    virtual ComponentBase *getSimulationEngine() { return 0; }
    
    // All new global interfaces are exposed only through getGlobalInterface()->ObtainInterface(sg::ComponentRegistry::IFNAME(), ...)...:
    // 
    // To lookup interface I of global component instance C do:
    // getGlobalInterface()
    //     ->ObtainInterface(sg::ComponentRegistry::IFNAME(), sg::ComponentRegistry::IFREVISION(), 0)
    //     ->lookupComponent(C)
    //     ->ObtainInterface(I::IFNAME(), I::IFREVISION(), 0);
    // 
    // The following global components with the following interfaces are defined:
    //
    // Global 'scheduler' component:
    // - SchedulerInterfaceForComponents, rev=0: Create new scheduler objects like threads, timers.
    //   This interface is valid immediately in the component constructor.
    // - SchedulerControlInterface, rev=0: Only available when using the standalone scheduler (i.e. not for SystemC)
    //   This is the interface used to control the standalone scheduler (_not_ the standalone simulation engine).
    //   This interface is usually never used by any component, only by the standalone simulation engine.
    // - SchedulerTestInterface, rev=0: Only available when using the standalone scheduler (i.e. not for SystemC)
    //   This interface is usually never used by any component, only by the tests which test the standalone scheduler.
    // 
    // Global 'mtiRegistry' component:
    // - SystemTraceInterface1, rev=0: Get a list of all trace sources available in the system. 
    //   This interface is only valid in the first 'reset()' phase (not valid in init()) because it requires all other 
    //   components to be initialized first.
    // 
    // Global 'cadiSimulation' component:
    // - eslapi.CADISimulation2, rev=0: Get list of all components in the system which have a CADI interface.
    //   This interface is only valid in the first 'reset()' phase (not valid in init()) because it requires all other 
    //   components to be initialized first.
    // 
    // Global 'systemComponentRegistry' component:
    // - ComponentRegistry, rev=0: Get list of all system components in the system, regardless of the types interfaces the offer.
    //   This component list completes the incomplete component lists provided through the SystemTraceInterface1 and eslapi.CADISimulation2
    //   interfaces which both list only components which expose the related type of interface (trace or CADI, respectively).
    //   This is not yet implemented.
    //
    virtual eslapi::CAInterface *getGlobalInterface() { return 0; }
};
    
} // namespace sg

#endif // ARM_SG_SIMULATIONCONTEXT_H
