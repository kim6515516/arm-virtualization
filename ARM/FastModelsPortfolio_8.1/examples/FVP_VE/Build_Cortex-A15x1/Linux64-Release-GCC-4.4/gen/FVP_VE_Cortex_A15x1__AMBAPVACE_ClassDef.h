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
 * Class definition for protocol FVP_VE_Cortex_A15x1__AMBAPVACE.
 */

#ifndef FVP_VE_Cortex_A15x1__AMBAPVACE_ClassDef_h_
#define FVP_VE_Cortex_A15x1__AMBAPVACE_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_AMBAPVACE.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__AMBAPVACE;

// Abstract interface implementation for port
class protocol_AMBAPVACE__Implementation: public protocol_AMBAPVACE
{
public:
    protocol_AMBAPVACE__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__AMBAPVACE *port) { thisPort = port; }

    // Protocol members
	inline void b_transport(int socket_id, amba_pv::amba_pv_transaction& trans, sc_core::sc_time& t);
	inline unsigned int transport_dbg(int socket_id, amba_pv::amba_pv_transaction& trans);
	inline bool get_direct_mem_ptr(int socket_id, amba_pv::amba_pv_transaction& trans, tlm::tlm_dmi& dmi_data);
	inline void b_snoop(int socket_id, amba_pv::amba_pv_transaction& trans, sc_core::sc_time& t);
	inline unsigned int snoop_dbg(int socket_id, amba_pv::amba_pv_transaction& trans);
	inline void invalidate_direct_mem_ptr(int socket_id, sc_dt::uint64 start_range, sc_dt::uint64 end_range);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__AMBAPVACE *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__AMBAPVACE: public sg::Port
{
private:
    unsigned int default_transport_dbg(int socket_id, amba_pv::amba_pv_transaction& trans)
{

 return 0;
 
}
bool default_get_direct_mem_ptr(int socket_id, amba_pv::amba_pv_transaction& trans, tlm::tlm_dmi& dmi_data)
{

 dmi_data.allow_read_write();
 dmi_data.set_start_address(0x0);
 dmi_data.set_end_address(sc_dt::uint64(-1));
 return false;
 
}
void default_b_snoop(int socket_id, amba_pv::amba_pv_transaction& trans, sc_core::sc_time& t)
{

 
}
unsigned int default_snoop_dbg(int socket_id, amba_pv::amba_pv_transaction& trans)
{

 return 0;
 
}
void default_invalidate_direct_mem_ptr(int socket_id, sc_dt::uint64 start_range, sc_dt::uint64 end_range)
{

 
}

public:
    // Resources


    // Connector instances
	sg::SlaveConnector< void (int,amba_pv::amba_pv_transaction&,sc_core::sc_time&) > b_transport;
	sg::SlaveConnector< unsigned int (int,amba_pv::amba_pv_transaction&) > transport_dbg;
	sg::SlaveConnector< bool (int,amba_pv::amba_pv_transaction&,tlm::tlm_dmi&) > get_direct_mem_ptr;
	sg::MasterConnector< void (int,amba_pv::amba_pv_transaction&,sc_core::sc_time&) > b_snoop;
	sg::MasterConnector< unsigned int (int,amba_pv::amba_pv_transaction&) > snoop_dbg;
	sg::MasterConnector< void (int,sc_dt::uint64,sc_dt::uint64) > invalidate_direct_mem_ptr;


    FVP_VE_Cortex_A15x1__AMBAPVACE()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(b_transport);
		define_behaviour(transport_dbg);
		define_behaviour(get_direct_mem_ptr);
		define_behaviour(b_snoop);
		define_behaviour(snoop_dbg);
		define_behaviour(invalidate_direct_mem_ptr);

transport_dbg.bind_default_behaviour( this, &FVP_VE_Cortex_A15x1__AMBAPVACE::default_transport_dbg);get_direct_mem_ptr.bind_default_behaviour( this, &FVP_VE_Cortex_A15x1__AMBAPVACE::default_get_direct_mem_ptr);b_snoop.bind_default_behaviour( this, &FVP_VE_Cortex_A15x1__AMBAPVACE::default_b_snoop);snoop_dbg.bind_default_behaviour( this, &FVP_VE_Cortex_A15x1__AMBAPVACE::default_snoop_dbg);invalidate_direct_mem_ptr.bind_default_behaviour( this, &FVP_VE_Cortex_A15x1__AMBAPVACE::default_invalidate_direct_mem_ptr);
    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_AMBAPVACE__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_AMBAPVACE *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline void protocol_AMBAPVACE__Implementation::b_transport(int socket_id, amba_pv::amba_pv_transaction& trans, sc_core::sc_time& t)
{
	return thisPort->b_transport(socket_id, trans, t);
}

inline unsigned int protocol_AMBAPVACE__Implementation::transport_dbg(int socket_id, amba_pv::amba_pv_transaction& trans)
{
	return thisPort->transport_dbg(socket_id, trans);
}

inline bool protocol_AMBAPVACE__Implementation::get_direct_mem_ptr(int socket_id, amba_pv::amba_pv_transaction& trans, tlm::tlm_dmi& dmi_data)
{
	return thisPort->get_direct_mem_ptr(socket_id, trans, dmi_data);
}

inline void protocol_AMBAPVACE__Implementation::b_snoop(int socket_id, amba_pv::amba_pv_transaction& trans, sc_core::sc_time& t)
{
	return thisPort->b_snoop(socket_id, trans, t);
}

inline unsigned int protocol_AMBAPVACE__Implementation::snoop_dbg(int socket_id, amba_pv::amba_pv_transaction& trans)
{
	return thisPort->snoop_dbg(socket_id, trans);
}

inline void protocol_AMBAPVACE__Implementation::invalidate_direct_mem_ptr(int socket_id, sc_dt::uint64 start_range, sc_dt::uint64 end_range)
{
	return thisPort->invalidate_direct_mem_ptr(socket_id, start_range, end_range);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort)
class FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__AMBAPVACE
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort: public FVP_VE_Cortex_A15x1__AMBAPVACE
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->b_transport.connectTo(&masterPort->b_transport);
		this->transport_dbg.connectTo(&masterPort->transport_dbg);
		this->get_direct_mem_ptr.connectTo(&masterPort->get_direct_mem_ptr);
		this->b_snoop.connectTo(&masterPort->b_snoop);
		this->snoop_dbg.connectTo(&masterPort->snoop_dbg);
		this->invalidate_direct_mem_ptr.connectTo(&masterPort->invalidate_direct_mem_ptr);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__AMBAPVACE__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

