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
 * Class definition for protocol FVP_VE_Cortex_A15x1__PVBusSlaveControl.
 */

#ifndef FVP_VE_Cortex_A15x1__PVBusSlaveControl_ClassDef_h_
#define FVP_VE_Cortex_A15x1__PVBusSlaveControl_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_PVBusSlaveControl.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__PVBusSlaveControl;

// Abstract interface implementation for port
class protocol_PVBusSlaveControl__Implementation: public protocol_PVBusSlaveControl
{
public:
    protocol_PVBusSlaveControl__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__PVBusSlaveControl *port) { thisPort = port; }

    // Protocol members
	inline void setFillPattern(uint32_t fill1, uint32_t fill2);
	inline void setAccess(pv::bus_addr_t base, pv::bus_addr_t top, pv::accessType type, pv::accessMode mode);
	inline const uint8_t* getReadStorage(pv::bus_addr_t address, pv::bus_addr_t* limit);
	inline uint8_t* getWriteStorage(pv::bus_addr_t address, pv::bus_addr_t* limit);
	inline void provideReadStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, const uint8_t* storage);
	inline void provideWriteStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, uint8_t* storage);
	inline void provideReadWriteStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, uint8_t* storage);
	inline void configure(pv::slave_config_t* );


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__PVBusSlaveControl *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__PVBusSlaveControl: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< void (uint32_t,uint32_t) > setFillPattern;
	sg::SlaveConnector< void (pv::bus_addr_t,pv::bus_addr_t,pv::accessType,pv::accessMode) > setAccess;
	sg::SlaveConnector< const uint8_t* (pv::bus_addr_t,pv::bus_addr_t*) > getReadStorage;
	sg::SlaveConnector< uint8_t* (pv::bus_addr_t,pv::bus_addr_t*) > getWriteStorage;
	sg::SlaveConnector< void (pv::bus_addr_t,pv::bus_addr_t,const uint8_t*) > provideReadStorage;
	sg::SlaveConnector< void (pv::bus_addr_t,pv::bus_addr_t,uint8_t*) > provideWriteStorage;
	sg::SlaveConnector< void (pv::bus_addr_t,pv::bus_addr_t,uint8_t*) > provideReadWriteStorage;
	sg::SlaveConnector< void (pv::slave_config_t*) > configure;


    FVP_VE_Cortex_A15x1__PVBusSlaveControl()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(setFillPattern);
		define_behaviour(setAccess);
		define_behaviour(getReadStorage);
		define_behaviour(getWriteStorage);
		define_behaviour(provideReadStorage);
		define_behaviour(provideWriteStorage);
		define_behaviour(provideReadWriteStorage);
		define_behaviour(configure);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_PVBusSlaveControl__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_PVBusSlaveControl *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline void protocol_PVBusSlaveControl__Implementation::setFillPattern(uint32_t fill1, uint32_t fill2)
{
	return thisPort->setFillPattern(fill1, fill2);
}

inline void protocol_PVBusSlaveControl__Implementation::setAccess(pv::bus_addr_t base, pv::bus_addr_t top, pv::accessType type, pv::accessMode mode)
{
	return thisPort->setAccess(base, top, type, mode);
}

inline const uint8_t* protocol_PVBusSlaveControl__Implementation::getReadStorage(pv::bus_addr_t address, pv::bus_addr_t* limit)
{
	return thisPort->getReadStorage(address, limit);
}

inline uint8_t* protocol_PVBusSlaveControl__Implementation::getWriteStorage(pv::bus_addr_t address, pv::bus_addr_t* limit)
{
	return thisPort->getWriteStorage(address, limit);
}

inline void protocol_PVBusSlaveControl__Implementation::provideReadStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, const uint8_t* storage)
{
	return thisPort->provideReadStorage(device_base, device_limit, storage);
}

inline void protocol_PVBusSlaveControl__Implementation::provideWriteStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, uint8_t* storage)
{
	return thisPort->provideWriteStorage(device_base, device_limit, storage);
}

inline void protocol_PVBusSlaveControl__Implementation::provideReadWriteStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, uint8_t* storage)
{
	return thisPort->provideReadWriteStorage(device_base, device_limit, storage);
}

inline void protocol_PVBusSlaveControl__Implementation::configure(pv::slave_config_t* param0__)
{
	return thisPort->configure(param0__);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort)
class FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__PVBusSlaveControl
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort: public FVP_VE_Cortex_A15x1__PVBusSlaveControl
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->setFillPattern.connectTo(&masterPort->setFillPattern);
		this->setAccess.connectTo(&masterPort->setAccess);
		this->getReadStorage.connectTo(&masterPort->getReadStorage);
		this->getWriteStorage.connectTo(&masterPort->getWriteStorage);
		this->provideReadStorage.connectTo(&masterPort->provideReadStorage);
		this->provideWriteStorage.connectTo(&masterPort->provideWriteStorage);
		this->provideReadWriteStorage.connectTo(&masterPort->provideReadWriteStorage);
		this->configure.connectTo(&masterPort->configure);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__PVBusSlaveControl__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

