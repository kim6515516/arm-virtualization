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
 * Class definition for protocol FVP_VE_Cortex_A15x1__CounterInterface.
 */

#ifndef FVP_VE_Cortex_A15x1__CounterInterface_ClassDef_h_
#define FVP_VE_Cortex_A15x1__CounterInterface_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_CounterInterface.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__CounterInterface;

// Abstract interface implementation for port
class protocol_CounterInterface__Implementation: public protocol_CounterInterface
{
public:
    protocol_CounterInterface__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__CounterInterface *port) { thisPort = port; }

    // Protocol members
	inline uint64_t getCounterValue();
	inline void requestSignalUpdate(uint64_t at);
	inline void signalUpdate();
	inline void setEnabled(bool );
	inline void requestEventUpdate(uint64_t at);
	inline void eventUpdate();


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__CounterInterface *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__CounterInterface: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::MasterConnector< uint64_t (void) > getCounterValue;
	sg::MasterConnector< void (uint64_t) > requestSignalUpdate;
	sg::SlaveConnector< void (void) > signalUpdate;
	sg::SlaveConnector< void (bool) > setEnabled;
	sg::MasterConnector< void (uint64_t) > requestEventUpdate;
	sg::SlaveConnector< void (void) > eventUpdate;


    FVP_VE_Cortex_A15x1__CounterInterface()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(getCounterValue);
		define_behaviour(requestSignalUpdate);
		define_behaviour(signalUpdate);
		define_behaviour(setEnabled);
		define_behaviour(requestEventUpdate);
		define_behaviour(eventUpdate);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_CounterInterface__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_CounterInterface *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline uint64_t protocol_CounterInterface__Implementation::getCounterValue()
{
	return thisPort->getCounterValue();
}

inline void protocol_CounterInterface__Implementation::requestSignalUpdate(uint64_t at)
{
	return thisPort->requestSignalUpdate(at);
}

inline void protocol_CounterInterface__Implementation::signalUpdate()
{
	return thisPort->signalUpdate();
}

inline void protocol_CounterInterface__Implementation::setEnabled(bool param0__)
{
	return thisPort->setEnabled(param0__);
}

inline void protocol_CounterInterface__Implementation::requestEventUpdate(uint64_t at)
{
	return thisPort->requestEventUpdate(at);
}

inline void protocol_CounterInterface__Implementation::eventUpdate()
{
	return thisPort->eventUpdate();
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort)
class FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__CounterInterface
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort: public FVP_VE_Cortex_A15x1__CounterInterface
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->getCounterValue.connectTo(&masterPort->getCounterValue);
		this->requestSignalUpdate.connectTo(&masterPort->requestSignalUpdate);
		this->signalUpdate.connectTo(&masterPort->signalUpdate);
		this->setEnabled.connectTo(&masterPort->setEnabled);
		this->requestEventUpdate.connectTo(&masterPort->requestEventUpdate);
		this->eventUpdate.connectTo(&masterPort->eventUpdate);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__CounterInterface__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

