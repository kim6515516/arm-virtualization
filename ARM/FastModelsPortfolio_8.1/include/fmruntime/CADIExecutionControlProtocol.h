/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   CADIExecutionControlProtocol.h
 *  \brief  Simulation Engine CADI execution control protocol
 *  \date   Copyright ARM Limited 2002 All Rights Reserved.
 *          Copyright ARM Limited 2012-2013 All Rights Reserved.
 *  
 */

#ifndef _CADIExecutionControlProtocol_h_
#define _CADIExecutionControlProtocol_h_

#include <string>
#include "MxTypes.h"
#include "sg/SGPort.h"
#include <eslapi/CADITypes.h>
#include "MxIDataStream.h"
#include "MxODataStream.h"

namespace eslapi
{
    class CADI;
}

namespace sg
{
    // This class defines the interface of a Runnable object as passed to the runRunnable behaviour.
    // The sim engine will call the Runnable's run() method from the simulation thread. The 
    // call to runRunnable will not return until the run() method has exited.
    class Runnable
    {
    public:
        Runnable() {}
        virtual ~Runnable() {}
        virtual void run() = 0;
    };

    class CADIExecutionControlProtocolSystemGenerator: public Port
{
public:
    // connector instances
    
    // the slave behaviors are always called from the GUI/debugger thread
    SlaveConnector< eslapi::CADIReturn_t (void) > run;
    SlaveConnector< eslapi::CADIReturn_t (MxU64) > stepCycle;
    SlaveConnector< eslapi::CADIReturn_t (void) > stop;
    SlaveConnector< eslapi::CADIReturn_t (MxU32) > reset;
    SlaveConnector< eslapi::CADIReturn_t (MxODataStream&) > save;
    SlaveConnector< eslapi::CADIReturn_t (MxIDataStream&) > restore;
    SlaveConnector< std::string (const std::string&) > getSystemProperty; // propertyNameIn
    SlaveConnector< eslapi::CADIReturn_t (eslapi::CADI*, eslapi::CADITargetInfo_t *) > getTargetInfo;
    SlaveConnector< uint32_t (void) > getExecMode;
    SlaveConnector< void* () > lockSimState;
    SlaveConnector< void (void*) > releaseSimState;
    SlaveConnector< eslapi::CADIReturn_t (Runnable&) > runRunnable;
    SlaveConnector< bool (void) > getProxyingOK;
    // the master behaviors are always called from the simulator thread
    MasterConnector< void (void) > callbackModeChangeRun;
    MasterConnector< void (void) > callbackModeChangeStop;
    MasterConnector< void (MxU32) > callbackReset;
    MasterConnector< void (void) > callbackKillInterface;
    MasterConnector< void (const std::string&) > callbackMessage; // general purpose message shown to the user in the debugger
    
    // constructor
    CADIExecutionControlProtocolSystemGenerator()
    {
        define_behaviour(run);
        define_behaviour(stepCycle);
        define_behaviour(stop);
        define_behaviour(reset);
        define_behaviour(save);
        define_behaviour(restore);
        define_behaviour(getSystemProperty);        
        define_behaviour(getTargetInfo);
        define_behaviour(getExecMode);
        define_behaviour(lockSimState);
        define_behaviour(releaseSimState);
        define_behaviour(runRunnable);
        define_behaviour(getProxyingOK);
        define_behaviour(callbackModeChangeRun);
        define_behaviour(callbackModeChangeStop);
        define_behaviour(callbackReset);
        define_behaviour(callbackKillInterface);
        define_behaviour(callbackMessage);
    }

    // The following class is a wrapper class for CADIExecutionControlProtocolSystemGenerator. It automatically releases the simulation state 
    // by calling CADIExecutionControlProtocolSystemGenerator::releaseSimState() on destruction
    class SimStateLock
    {
    public:
        SimStateLock(CADIExecutionControlProtocolSystemGenerator* port_) : port(port_), locked(false), lockSimStateReturnPointer(0) {}

        ~SimStateLock() 
        { 
            if (!port->releaseSimState.empty() && locked)
                port->releaseSimState(lockSimStateReturnPointer); 
        }

        // copy constructor to transfer mutex ownership to caller's SimStateLock object
        SimStateLock(const SimStateLock& orig): port(orig.port), locked(orig.locked), lockSimStateReturnPointer(orig.lockSimStateReturnPointer) {}

        // cast operator 
        operator bool()
        {
            return locked;
        }

        // lock mutext if not already done. Returns true if mutex is locked
        bool acquire()
        {
            if (locked)
                return true;

            if (!port->lockSimState.empty())
            {
                lockSimStateReturnPointer = port->lockSimState();
                if (lockSimStateReturnPointer)
                    locked = true;
            }
            return locked;
        }
        
    private:
        CADIExecutionControlProtocolSystemGenerator* port;
        bool locked;
        void *lockSimStateReturnPointer;
    };
};

    
}

#endif /* ifndef _CADIExecutionControlProtocol_h_ */

