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
 * Class definition for protocol FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol.
 */

#ifndef FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol_ClassDef_h_
#define FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_CADIDisassemblerProtocol.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol;

// Abstract interface implementation for port
class protocol_CADIDisassemblerProtocol__Implementation: public protocol_CADIDisassemblerProtocol
{
public:
    protocol_CADIDisassemblerProtocol__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol *port) { thisPort = port; }

    // Protocol members
	inline eslapi::CADIDisassemblerType GetType();
	inline uint32_t GetModeCount();
	inline void GetModeNames(eslapi::CADIDisassemblerCB* callback_);
	inline uint32_t GetCurrentMode();
	inline eslapi::CADIDisassemblerStatus GetSourceReferenceForAddress(eslapi::CADIDisassemblerCB* callback_, const eslapi::CADIAddr_t& address);
	inline eslapi::CADIDisassemblerStatus GetAddressForSourceReference(const char* sourceFile, uint32_t sourceLine, eslapi::CADIAddr_t& address);
	inline eslapi::CADIDisassemblerStatus GetDisassembly(eslapi::CADIDisassemblerCB* callback_, const eslapi::CADIAddr_t& address, eslapi::CADIAddr_t& nextAddr, const uint32_t mode, uint32_t desiredCount);
	inline eslapi::CADIDisassemblerStatus GetInstructionType(const eslapi::CADIAddr_t& address, eslapi::CADIDisassemblerInstructionType& insn_type);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< eslapi::CADIDisassemblerType (void) > GetType;
	sg::SlaveConnector< uint32_t (void) > GetModeCount;
	sg::SlaveConnector< void (eslapi::CADIDisassemblerCB*) > GetModeNames;
	sg::SlaveConnector< uint32_t (void) > GetCurrentMode;
	sg::SlaveConnector< eslapi::CADIDisassemblerStatus (eslapi::CADIDisassemblerCB*,const eslapi::CADIAddr_t&) > GetSourceReferenceForAddress;
	sg::SlaveConnector< eslapi::CADIDisassemblerStatus (const char*,uint32_t,eslapi::CADIAddr_t&) > GetAddressForSourceReference;
	sg::SlaveConnector< eslapi::CADIDisassemblerStatus (eslapi::CADIDisassemblerCB*,const eslapi::CADIAddr_t&,eslapi::CADIAddr_t&,const uint32_t,uint32_t) > GetDisassembly;
	sg::SlaveConnector< eslapi::CADIDisassemblerStatus (const eslapi::CADIAddr_t&,eslapi::CADIDisassemblerInstructionType&) > GetInstructionType;


    FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(GetType);
		define_behaviour(GetModeCount);
		define_behaviour(GetModeNames);
		define_behaviour(GetCurrentMode);
		define_behaviour(GetSourceReferenceForAddress);
		define_behaviour(GetAddressForSourceReference);
		define_behaviour(GetDisassembly);
		define_behaviour(GetInstructionType);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_CADIDisassemblerProtocol__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_CADIDisassemblerProtocol *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline eslapi::CADIDisassemblerType protocol_CADIDisassemblerProtocol__Implementation::GetType()
{
	return thisPort->GetType();
}

inline uint32_t protocol_CADIDisassemblerProtocol__Implementation::GetModeCount()
{
	return thisPort->GetModeCount();
}

inline void protocol_CADIDisassemblerProtocol__Implementation::GetModeNames(eslapi::CADIDisassemblerCB* callback_)
{
	return thisPort->GetModeNames(callback_);
}

inline uint32_t protocol_CADIDisassemblerProtocol__Implementation::GetCurrentMode()
{
	return thisPort->GetCurrentMode();
}

inline eslapi::CADIDisassemblerStatus protocol_CADIDisassemblerProtocol__Implementation::GetSourceReferenceForAddress(eslapi::CADIDisassemblerCB* callback_, const eslapi::CADIAddr_t& address)
{
	return thisPort->GetSourceReferenceForAddress(callback_, address);
}

inline eslapi::CADIDisassemblerStatus protocol_CADIDisassemblerProtocol__Implementation::GetAddressForSourceReference(const char* sourceFile, uint32_t sourceLine, eslapi::CADIAddr_t& address)
{
	return thisPort->GetAddressForSourceReference(sourceFile, sourceLine, address);
}

inline eslapi::CADIDisassemblerStatus protocol_CADIDisassemblerProtocol__Implementation::GetDisassembly(eslapi::CADIDisassemblerCB* callback_, const eslapi::CADIAddr_t& address, eslapi::CADIAddr_t& nextAddr, const uint32_t mode, uint32_t desiredCount)
{
	return thisPort->GetDisassembly(callback_, address, nextAddr, mode, desiredCount);
}

inline eslapi::CADIDisassemblerStatus protocol_CADIDisassemblerProtocol__Implementation::GetInstructionType(const eslapi::CADIAddr_t& address, eslapi::CADIDisassemblerInstructionType& insn_type)
{
	return thisPort->GetInstructionType(address, insn_type);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort)
class FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort: public FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->GetType.connectTo(&masterPort->GetType);
		this->GetModeCount.connectTo(&masterPort->GetModeCount);
		this->GetModeNames.connectTo(&masterPort->GetModeNames);
		this->GetCurrentMode.connectTo(&masterPort->GetCurrentMode);
		this->GetSourceReferenceForAddress.connectTo(&masterPort->GetSourceReferenceForAddress);
		this->GetAddressForSourceReference.connectTo(&masterPort->GetAddressForSourceReference);
		this->GetDisassembly.connectTo(&masterPort->GetDisassembly);
		this->GetInstructionType.connectTo(&masterPort->GetInstructionType);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__CADIDisassemblerProtocol__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

