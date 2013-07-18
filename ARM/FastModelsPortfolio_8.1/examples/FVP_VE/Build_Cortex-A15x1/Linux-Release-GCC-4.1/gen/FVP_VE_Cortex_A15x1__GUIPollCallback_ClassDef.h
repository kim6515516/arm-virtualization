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
 * Class definition for protocol FVP_VE_Cortex_A15x1__GUIPollCallback.
 */

#ifndef FVP_VE_Cortex_A15x1__GUIPollCallback_ClassDef_h_
#define FVP_VE_Cortex_A15x1__GUIPollCallback_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_GUIPollCallback.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__GUIPollCallback;

// Abstract interface implementation for port
class protocol_GUIPollCallback__Implementation: public protocol_GUIPollCallback
{
public:
    protocol_GUIPollCallback__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__GUIPollCallback *port) { thisPort = port; }

    // Protocol members
	inline void gui_callback();


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__GUIPollCallback *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__GUIPollCallback: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< void (void) > gui_callback;


    FVP_VE_Cortex_A15x1__GUIPollCallback()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(gui_callback);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_GUIPollCallback__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_GUIPollCallback *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline void protocol_GUIPollCallback__Implementation::gui_callback()
{
	return thisPort->gui_callback();
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort)
class FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__GUIPollCallback
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort: public FVP_VE_Cortex_A15x1__GUIPollCallback
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->gui_callback.connectTo(&masterPort->gui_callback);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__GUIPollCallback__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

