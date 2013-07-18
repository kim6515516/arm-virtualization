/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2005 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Class definition for protocol FVP_VE_Cortex_A15x1__CADIProtocol.
 */

#ifndef FVP_VE_Cortex_A15x1__CADIProtocol_ClassDef_h_
#define FVP_VE_Cortex_A15x1__CADIProtocol_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_CADIProtocol.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__CADIProtocol;

// Abstract interface implementation for port
class protocol_CADIProtocol__Implementation: public protocol_CADIProtocol
{
public:
    protocol_CADIProtocol__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__CADIProtocol *port) { thisPort = port; }

    // Protocol members
	inline eslapi::CADIReturn_t CADIBptGetList(uint32_t , uint32_t , uint32_t* , eslapi::CADIBptDescription_t* );
	inline eslapi::CADIReturn_t CADIBptRead(eslapi::CADIBptNumber_t , eslapi::CADIBptRequest_t* );
	inline eslapi::CADIReturn_t CADIBptSet(eslapi::CADIBptRequest_t* , eslapi::CADIBptNumber_t* );
	inline eslapi::CADIReturn_t CADIBptClear(eslapi::CADIBptNumber_t );
	inline eslapi::CADIReturn_t CADIBptConfigure(eslapi::CADIBptNumber_t , eslapi::CADIBptConfigure_t );
	inline eslapi::CADIReturn_t CADIModifyTargetFeatures(eslapi::CADITargetFeatures_t* );
	inline eslapi::CADIDisassembler* CADIGetDisassembler();
	inline eslapi::CADIReturn_t CADIExecSingleStep(uint32_t instructionCount, int8_t stepCycle, int8_t stepOver);
	inline void callbackModeChange(uint32_t newMode, eslapi::CADIBptNumber_t bptNumber);
	inline eslapi::CADIReturn_t CADIGetInstructionCount(uint64_t& instructionCount);
	inline eslapi::CADIReturn_t CADIGetCycleCount(uint64_t& instructionCount, bool systemCycles);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__CADIProtocol *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__CADIProtocol: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< eslapi::CADIReturn_t (uint32_t,uint32_t,uint32_t*,eslapi::CADIBptDescription_t*) > CADIBptGetList;
	sg::SlaveConnector< eslapi::CADIReturn_t (eslapi::CADIBptNumber_t,eslapi::CADIBptRequest_t*) > CADIBptRead;
	sg::SlaveConnector< eslapi::CADIReturn_t (eslapi::CADIBptRequest_t*,eslapi::CADIBptNumber_t*) > CADIBptSet;
	sg::SlaveConnector< eslapi::CADIReturn_t (eslapi::CADIBptNumber_t) > CADIBptClear;
	sg::SlaveConnector< eslapi::CADIReturn_t (eslapi::CADIBptNumber_t,eslapi::CADIBptConfigure_t) > CADIBptConfigure;
	sg::SlaveConnector< eslapi::CADIReturn_t (eslapi::CADITargetFeatures_t*) > CADIModifyTargetFeatures;
	sg::SlaveConnector< eslapi::CADIDisassembler* (void) > CADIGetDisassembler;
	sg::SlaveConnector< eslapi::CADIReturn_t (uint32_t,int8_t,int8_t) > CADIExecSingleStep;
	sg::SlaveConnector< void (uint32_t,eslapi::CADIBptNumber_t) > callbackModeChange;
	sg::SlaveConnector< eslapi::CADIReturn_t (uint64_t&) > CADIGetInstructionCount;
	sg::SlaveConnector< eslapi::CADIReturn_t (uint64_t&,bool) > CADIGetCycleCount;


    FVP_VE_Cortex_A15x1__CADIProtocol()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(CADIBptGetList);
		define_behaviour(CADIBptRead);
		define_behaviour(CADIBptSet);
		define_behaviour(CADIBptClear);
		define_behaviour(CADIBptConfigure);
		define_behaviour(CADIModifyTargetFeatures);
		define_behaviour(CADIGetDisassembler);
		define_behaviour(CADIExecSingleStep);
		define_behaviour(callbackModeChange);
		define_behaviour(CADIGetInstructionCount);
		define_behaviour(CADIGetCycleCount);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_CADIProtocol__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_CADIProtocol *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIBptGetList(uint32_t param0__, uint32_t param1__, uint32_t* param2__, eslapi::CADIBptDescription_t* param3__)
{
	return thisPort->CADIBptGetList(param0__, param1__, param2__, param3__);
}

inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIBptRead(eslapi::CADIBptNumber_t param0__, eslapi::CADIBptRequest_t* param1__)
{
	return thisPort->CADIBptRead(param0__, param1__);
}

inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIBptSet(eslapi::CADIBptRequest_t* param0__, eslapi::CADIBptNumber_t* param1__)
{
	return thisPort->CADIBptSet(param0__, param1__);
}

inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIBptClear(eslapi::CADIBptNumber_t param0__)
{
	return thisPort->CADIBptClear(param0__);
}

inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIBptConfigure(eslapi::CADIBptNumber_t param0__, eslapi::CADIBptConfigure_t param1__)
{
	return thisPort->CADIBptConfigure(param0__, param1__);
}

inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIModifyTargetFeatures(eslapi::CADITargetFeatures_t* param0__)
{
	return thisPort->CADIModifyTargetFeatures(param0__);
}

inline eslapi::CADIDisassembler* protocol_CADIProtocol__Implementation::CADIGetDisassembler()
{
	return thisPort->CADIGetDisassembler();
}

inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIExecSingleStep(uint32_t instructionCount, int8_t stepCycle, int8_t stepOver)
{
	return thisPort->CADIExecSingleStep(instructionCount, stepCycle, stepOver);
}

inline void protocol_CADIProtocol__Implementation::callbackModeChange(uint32_t newMode, eslapi::CADIBptNumber_t bptNumber)
{
	return thisPort->callbackModeChange(newMode, bptNumber);
}

inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIGetInstructionCount(uint64_t& instructionCount)
{
	return thisPort->CADIGetInstructionCount(instructionCount);
}

inline eslapi::CADIReturn_t protocol_CADIProtocol__Implementation::CADIGetCycleCount(uint64_t& instructionCount, bool systemCycles)
{
	return thisPort->CADIGetCycleCount(instructionCount, systemCycles);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort)
class FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__CADIProtocol
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort(MxU32 inFirst,
                                                 MxU32 inLast,
                                                 MxU32 outFirst,
                                                 MxU32 outLast):
    inFirst__(inFirst),
    inLast__(inLast),
    outFirst__(outFirst),
    outSize__(outLast - outFirst + 1)
    {
    }

    bool isCovered__(MxU32 address) const
    {
        return (address >= inFirst__) && (address <= inLast__);
    }

    void remapAddress__(MxU32 &address) const
    {
        if(outSize__)
            address = ((address - inFirst__) % outSize__) + outFirst__;
    }

private:
    MxU32 inFirst__;
    MxU32 inLast__;
    MxU32 outFirst__;
    MxU32 outSize__;
};


// Addressable protocol class definition
class FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort: public FVP_VE_Cortex_A15x1__CADIProtocol
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
        {
            if ((*it)->isCovered__(addr)) {
                (*it)->remapAddress__(addr);
                return *it;
            }
        }
        return defaultOutPort__;
    }

    sg::Port* mapRange__(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast)
    {
        FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->CADIBptGetList.connectTo(&masterPort->CADIBptGetList);
		this->CADIBptRead.connectTo(&masterPort->CADIBptRead);
		this->CADIBptSet.connectTo(&masterPort->CADIBptSet);
		this->CADIBptClear.connectTo(&masterPort->CADIBptClear);
		this->CADIBptConfigure.connectTo(&masterPort->CADIBptConfigure);
		this->CADIModifyTargetFeatures.connectTo(&masterPort->CADIModifyTargetFeatures);
		this->CADIGetDisassembler.connectTo(&masterPort->CADIGetDisassembler);
		this->CADIExecSingleStep.connectTo(&masterPort->CADIExecSingleStep);
		this->callbackModeChange.connectTo(&masterPort->callbackModeChange);
		this->CADIGetInstructionCount.connectTo(&masterPort->CADIGetInstructionCount);
		this->CADIGetCycleCount.connectTo(&masterPort->CADIGetCycleCount);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort*)port);
        if(defaultOutPort__ == port)
        {
            delete defaultOutPort__;
            defaultOutPort__ = 0;
        }
    }

    bool isMapped__(MxU64 addr)
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
        {
            if ((*it)->isCovered__(static_cast<MxU32>(addr)))
                return true;
        }
        return false;
    }

    // Wrapper functions for protocol behaviors


private:
    typedef std::list<FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__CADIProtocol__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

