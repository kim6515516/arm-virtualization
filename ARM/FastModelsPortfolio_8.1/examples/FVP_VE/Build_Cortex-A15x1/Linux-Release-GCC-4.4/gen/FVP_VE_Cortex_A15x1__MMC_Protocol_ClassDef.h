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
 * Class definition for protocol FVP_VE_Cortex_A15x1__MMC_Protocol.
 */

#ifndef FVP_VE_Cortex_A15x1__MMC_Protocol_ClassDef_h_
#define FVP_VE_Cortex_A15x1__MMC_Protocol_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_MMC_Protocol.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__MMC_Protocol;

// Abstract interface implementation for port
class protocol_MMC_Protocol__Implementation: public protocol_MMC_Protocol
{
public:
    protocol_MMC_Protocol__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__MMC_Protocol *port) { thisPort = port; }

    // Protocol members
	inline mmc_resp_t cmd(mmc_cmd_t cmd, uint32_t arg, void* resp);
	inline bool Rx(const uint8_t* block, uint32_t len);
	inline void Rx_rdy();
	inline bool Tx(uint8_t* block, uint32_t len);
	inline void Tx_done();
	inline const char* cmd_name(mmc_cmd_t cmd);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__MMC_Protocol *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__MMC_Protocol: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< mmc_resp_t (mmc_cmd_t,uint32_t,void*) > cmd;
	sg::MasterConnector< bool (const uint8_t*,uint32_t) > Rx;
	sg::SlaveConnector< void (void) > Rx_rdy;
	sg::MasterConnector< bool (uint8_t*,uint32_t) > Tx;
	sg::SlaveConnector< void (void) > Tx_done;
	sg::SlaveConnector< const char* (mmc_cmd_t) > cmd_name;


    FVP_VE_Cortex_A15x1__MMC_Protocol()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(cmd);
		define_behaviour(Rx);
		define_behaviour(Rx_rdy);
		define_behaviour(Tx);
		define_behaviour(Tx_done);
		define_behaviour(cmd_name);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_MMC_Protocol__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_MMC_Protocol *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline mmc_resp_t protocol_MMC_Protocol__Implementation::cmd(mmc_cmd_t cmd, uint32_t arg, void* resp)
{
	return thisPort->cmd(cmd, arg, resp);
}

inline bool protocol_MMC_Protocol__Implementation::Rx(const uint8_t* block, uint32_t len)
{
	return thisPort->Rx(block, len);
}

inline void protocol_MMC_Protocol__Implementation::Rx_rdy()
{
	return thisPort->Rx_rdy();
}

inline bool protocol_MMC_Protocol__Implementation::Tx(uint8_t* block, uint32_t len)
{
	return thisPort->Tx(block, len);
}

inline void protocol_MMC_Protocol__Implementation::Tx_done()
{
	return thisPort->Tx_done();
}

inline const char* protocol_MMC_Protocol__Implementation::cmd_name(mmc_cmd_t cmd)
{
	return thisPort->cmd_name(cmd);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort)
class FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__MMC_Protocol
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort: public FVP_VE_Cortex_A15x1__MMC_Protocol
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->cmd.connectTo(&masterPort->cmd);
		this->Rx.connectTo(&masterPort->Rx);
		this->Rx_rdy.connectTo(&masterPort->Rx_rdy);
		this->Tx.connectTo(&masterPort->Tx);
		this->Tx_done.connectTo(&masterPort->Tx_done);
		this->cmd_name.connectTo(&masterPort->cmd_name);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__MMC_Protocol__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

