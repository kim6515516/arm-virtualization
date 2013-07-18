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
 * Class definition for protocol FVP_VE_Cortex_A15x1__PVCacheMaintenance.
 */

#ifndef FVP_VE_Cortex_A15x1__PVCacheMaintenance_ClassDef_h_
#define FVP_VE_Cortex_A15x1__PVCacheMaintenance_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_PVCacheMaintenance.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__PVCacheMaintenance;

// Abstract interface implementation for port
class protocol_PVCacheMaintenance__Implementation: public protocol_PVCacheMaintenance
{
public:
    protocol_PVCacheMaintenance__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__PVCacheMaintenance *port) { thisPort = port; }

    // Protocol members
	inline void clean_all();
	inline void clean_by_addr(pv::bus_addr_t addr, bool is_non_secure);
	inline void clean_by_set_way(uint32_t set, uint32_t way, bool is_non_secure);
	inline void invalidate_all();
	inline void invalidate_by_addr(pv::bus_addr_t addr, bool is_non_secure);
	inline void invalidate_by_set_way(uint32_t set, uint32_t way, bool is_non_secure);
	inline pv::Tx_Result preload(const pv::MemoryAttributes& memory_attributes_, pv::bus_addr_t address_, bool make_unique_);
	inline void setLockDown(uint32_t lock);
	inline uint32_t getLockDown();
	inline void setIsInner(bool is_inner);
	inline bool getEnabled(bool is_non_secure);
	inline void setEnabled(bool enabled, bool is_non_secure);
	inline void enableUpstreamAcceptsSnoopRequests(unsigned upstream_port_, bool on_);
	inline void enableUpstreamAcceptsDVM(unsigned upstream_port_, bool on_);
	inline void enableLocalDVMMessageProcessing(bool on_);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__PVCacheMaintenance *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__PVCacheMaintenance: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< void (void) > clean_all;
	sg::SlaveConnector< void (pv::bus_addr_t,bool) > clean_by_addr;
	sg::SlaveConnector< void (uint32_t,uint32_t,bool) > clean_by_set_way;
	sg::SlaveConnector< void (void) > invalidate_all;
	sg::SlaveConnector< void (pv::bus_addr_t,bool) > invalidate_by_addr;
	sg::SlaveConnector< void (uint32_t,uint32_t,bool) > invalidate_by_set_way;
	sg::SlaveConnector< pv::Tx_Result (const pv::MemoryAttributes&,pv::bus_addr_t,bool) > preload;
	sg::SlaveConnector< void (uint32_t) > setLockDown;
	sg::SlaveConnector< uint32_t (void) > getLockDown;
	sg::SlaveConnector< void (bool) > setIsInner;
	sg::SlaveConnector< bool (bool) > getEnabled;
	sg::SlaveConnector< void (bool,bool) > setEnabled;
	sg::SlaveConnector< void (unsigned,bool) > enableUpstreamAcceptsSnoopRequests;
	sg::SlaveConnector< void (unsigned,bool) > enableUpstreamAcceptsDVM;
	sg::SlaveConnector< void (bool) > enableLocalDVMMessageProcessing;


    FVP_VE_Cortex_A15x1__PVCacheMaintenance()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(clean_all);
		define_behaviour(clean_by_addr);
		define_behaviour(clean_by_set_way);
		define_behaviour(invalidate_all);
		define_behaviour(invalidate_by_addr);
		define_behaviour(invalidate_by_set_way);
		define_behaviour(preload);
		define_behaviour(setLockDown);
		define_behaviour(getLockDown);
		define_behaviour(setIsInner);
		define_behaviour(getEnabled);
		define_behaviour(setEnabled);
		define_behaviour(enableUpstreamAcceptsSnoopRequests);
		define_behaviour(enableUpstreamAcceptsDVM);
		define_behaviour(enableLocalDVMMessageProcessing);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_PVCacheMaintenance__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_PVCacheMaintenance *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline void protocol_PVCacheMaintenance__Implementation::clean_all()
{
	return thisPort->clean_all();
}

inline void protocol_PVCacheMaintenance__Implementation::clean_by_addr(pv::bus_addr_t addr, bool is_non_secure)
{
	return thisPort->clean_by_addr(addr, is_non_secure);
}

inline void protocol_PVCacheMaintenance__Implementation::clean_by_set_way(uint32_t set, uint32_t way, bool is_non_secure)
{
	return thisPort->clean_by_set_way(set, way, is_non_secure);
}

inline void protocol_PVCacheMaintenance__Implementation::invalidate_all()
{
	return thisPort->invalidate_all();
}

inline void protocol_PVCacheMaintenance__Implementation::invalidate_by_addr(pv::bus_addr_t addr, bool is_non_secure)
{
	return thisPort->invalidate_by_addr(addr, is_non_secure);
}

inline void protocol_PVCacheMaintenance__Implementation::invalidate_by_set_way(uint32_t set, uint32_t way, bool is_non_secure)
{
	return thisPort->invalidate_by_set_way(set, way, is_non_secure);
}

inline pv::Tx_Result protocol_PVCacheMaintenance__Implementation::preload(const pv::MemoryAttributes& memory_attributes_, pv::bus_addr_t address_, bool make_unique_)
{
	return thisPort->preload(memory_attributes_, address_, make_unique_);
}

inline void protocol_PVCacheMaintenance__Implementation::setLockDown(uint32_t lock)
{
	return thisPort->setLockDown(lock);
}

inline uint32_t protocol_PVCacheMaintenance__Implementation::getLockDown()
{
	return thisPort->getLockDown();
}

inline void protocol_PVCacheMaintenance__Implementation::setIsInner(bool is_inner)
{
	return thisPort->setIsInner(is_inner);
}

inline bool protocol_PVCacheMaintenance__Implementation::getEnabled(bool is_non_secure)
{
	return thisPort->getEnabled(is_non_secure);
}

inline void protocol_PVCacheMaintenance__Implementation::setEnabled(bool enabled, bool is_non_secure)
{
	return thisPort->setEnabled(enabled, is_non_secure);
}

inline void protocol_PVCacheMaintenance__Implementation::enableUpstreamAcceptsSnoopRequests(unsigned upstream_port_, bool on_)
{
	return thisPort->enableUpstreamAcceptsSnoopRequests(upstream_port_, on_);
}

inline void protocol_PVCacheMaintenance__Implementation::enableUpstreamAcceptsDVM(unsigned upstream_port_, bool on_)
{
	return thisPort->enableUpstreamAcceptsDVM(upstream_port_, on_);
}

inline void protocol_PVCacheMaintenance__Implementation::enableLocalDVMMessageProcessing(bool on_)
{
	return thisPort->enableLocalDVMMessageProcessing(on_);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort)
class FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__PVCacheMaintenance
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort: public FVP_VE_Cortex_A15x1__PVCacheMaintenance
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->clean_all.connectTo(&masterPort->clean_all);
		this->clean_by_addr.connectTo(&masterPort->clean_by_addr);
		this->clean_by_set_way.connectTo(&masterPort->clean_by_set_way);
		this->invalidate_all.connectTo(&masterPort->invalidate_all);
		this->invalidate_by_addr.connectTo(&masterPort->invalidate_by_addr);
		this->invalidate_by_set_way.connectTo(&masterPort->invalidate_by_set_way);
		this->preload.connectTo(&masterPort->preload);
		this->setLockDown.connectTo(&masterPort->setLockDown);
		this->getLockDown.connectTo(&masterPort->getLockDown);
		this->setIsInner.connectTo(&masterPort->setIsInner);
		this->getEnabled.connectTo(&masterPort->getEnabled);
		this->setEnabled.connectTo(&masterPort->setEnabled);
		this->enableUpstreamAcceptsSnoopRequests.connectTo(&masterPort->enableUpstreamAcceptsSnoopRequests);
		this->enableUpstreamAcceptsDVM.connectTo(&masterPort->enableUpstreamAcceptsDVM);
		this->enableLocalDVMMessageProcessing.connectTo(&masterPort->enableLocalDVMMessageProcessing);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__PVCacheMaintenance__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

