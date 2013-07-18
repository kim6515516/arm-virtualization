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
 * Class definition for protocol FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol.
 */

#ifndef FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol_ClassDef_h_
#define FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_v8EmbeddedCrossTrigger_controlprotocol.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol;

// Abstract interface implementation for port
class protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation: public protocol_v8EmbeddedCrossTrigger_controlprotocol
{
public:
    protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol *port) { thisPort = port; }

    // Protocol members
	inline void init(unsigned number_of_triggers, unsigned intack_mask, unsigned number_of_claim_bits);
	inline uint32_t reg_read(bool is_memory_mapped, uint32_t addr);
	inline void reg_write(bool is_memory_mapped, uint32_t addr, uint32_t data);
	inline void setValue_inputTrigger(unsigned index, sg::Signal::State state);
	inline void setValue_outputTrigger(unsigned index, sg::Signal::State state);
	inline uint8_t getPeripheralIdByte(unsigned pidn);
	inline uint8_t getComponentIdByte(unsigned pidn);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< void (unsigned,unsigned,unsigned) > init;
	sg::SlaveConnector< uint32_t (bool,uint32_t) > reg_read;
	sg::SlaveConnector< void (bool,uint32_t,uint32_t) > reg_write;
	sg::SlaveConnector< void (unsigned,sg::Signal::State) > setValue_inputTrigger;
	sg::MasterConnector< void (unsigned,sg::Signal::State) > setValue_outputTrigger;
	sg::MasterConnector< uint8_t (unsigned) > getPeripheralIdByte;
	sg::MasterConnector< uint8_t (unsigned) > getComponentIdByte;


    FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(init);
		define_behaviour(reg_read);
		define_behaviour(reg_write);
		define_behaviour(setValue_inputTrigger);
		define_behaviour(setValue_outputTrigger);
		define_behaviour(getPeripheralIdByte);
		define_behaviour(getComponentIdByte);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_v8EmbeddedCrossTrigger_controlprotocol *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline void protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation::init(unsigned number_of_triggers, unsigned intack_mask, unsigned number_of_claim_bits)
{
	return thisPort->init(number_of_triggers, intack_mask, number_of_claim_bits);
}

inline uint32_t protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation::reg_read(bool is_memory_mapped, uint32_t addr)
{
	return thisPort->reg_read(is_memory_mapped, addr);
}

inline void protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation::reg_write(bool is_memory_mapped, uint32_t addr, uint32_t data)
{
	return thisPort->reg_write(is_memory_mapped, addr, data);
}

inline void protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation::setValue_inputTrigger(unsigned index, sg::Signal::State state)
{
	return thisPort->setValue_inputTrigger(index, state);
}

inline void protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation::setValue_outputTrigger(unsigned index, sg::Signal::State state)
{
	return thisPort->setValue_outputTrigger(index, state);
}

inline uint8_t protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation::getPeripheralIdByte(unsigned pidn)
{
	return thisPort->getPeripheralIdByte(pidn);
}

inline uint8_t protocol_v8EmbeddedCrossTrigger_controlprotocol__Implementation::getComponentIdByte(unsigned pidn)
{
	return thisPort->getComponentIdByte(pidn);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort)
class FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort: public FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->init.connectTo(&masterPort->init);
		this->reg_read.connectTo(&masterPort->reg_read);
		this->reg_write.connectTo(&masterPort->reg_write);
		this->setValue_inputTrigger.connectTo(&masterPort->setValue_inputTrigger);
		this->setValue_outputTrigger.connectTo(&masterPort->setValue_outputTrigger);
		this->getPeripheralIdByte.connectTo(&masterPort->getPeripheralIdByte);
		this->getComponentIdByte.connectTo(&masterPort->getComponentIdByte);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__v8EmbeddedCrossTrigger_controlprotocol__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

