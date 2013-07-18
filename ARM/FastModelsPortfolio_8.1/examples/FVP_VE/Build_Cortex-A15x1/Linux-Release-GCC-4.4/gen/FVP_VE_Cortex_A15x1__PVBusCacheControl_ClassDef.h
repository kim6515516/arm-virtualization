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
 * Class definition for protocol FVP_VE_Cortex_A15x1__PVBusCacheControl.
 */

#ifndef FVP_VE_Cortex_A15x1__PVBusCacheControl_ClassDef_h_
#define FVP_VE_Cortex_A15x1__PVBusCacheControl_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_PVBusCacheControl.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__PVBusCacheControl;

// Abstract interface implementation for port
class protocol_PVBusCacheControl__Implementation: public protocol_PVBusCacheControl
{
public:
    protocol_PVBusCacheControl__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__PVBusCacheControl *port) { thisPort = port; }

    // Protocol members
	inline pv::TransactionGenerator* createTransactionGenerator(unsigned output_port);
	inline void revokeRoutingDecisions();
	inline pv::Tx_Result passThroughRead(unsigned output_port, pv::ReadTransaction tx);
	inline pv::Tx_Result passThroughWrite(unsigned output_port, pv::WriteTransaction tx);
	inline pv::Tx_Result readFromLine(pv::ReadTransaction tx, unsigned hit_line_index);
	inline pv::Tx_Result writeToLine(pv::WriteTransaction tx, unsigned hit_line_index);
	inline pv::Tx_Result writeToLineAndPassThrough(pv::WriteTransaction tx, unsigned hit_line_index, unsigned output_port);
	inline void invalidateLineHit(unsigned hit_line_index, pv::CacheRevocation revoke_type);
	inline char* getLineContentsForWrite(unsigned line_index);
	inline const char* getLineContentsForRead(unsigned line_index);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__PVBusCacheControl *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__PVBusCacheControl: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< pv::TransactionGenerator* (unsigned) > createTransactionGenerator;
	sg::SlaveConnector< void (void) > revokeRoutingDecisions;
	sg::SlaveConnector< pv::Tx_Result (unsigned,pv::ReadTransaction) > passThroughRead;
	sg::SlaveConnector< pv::Tx_Result (unsigned,pv::WriteTransaction) > passThroughWrite;
	sg::SlaveConnector< pv::Tx_Result (pv::ReadTransaction,unsigned) > readFromLine;
	sg::SlaveConnector< pv::Tx_Result (pv::WriteTransaction,unsigned) > writeToLine;
	sg::SlaveConnector< pv::Tx_Result (pv::WriteTransaction,unsigned,unsigned) > writeToLineAndPassThrough;
	sg::SlaveConnector< void (unsigned,pv::CacheRevocation) > invalidateLineHit;
	sg::SlaveConnector< char* (unsigned) > getLineContentsForWrite;
	sg::SlaveConnector< const char* (unsigned) > getLineContentsForRead;


    FVP_VE_Cortex_A15x1__PVBusCacheControl()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(createTransactionGenerator);
		define_behaviour(revokeRoutingDecisions);
		define_behaviour(passThroughRead);
		define_behaviour(passThroughWrite);
		define_behaviour(readFromLine);
		define_behaviour(writeToLine);
		define_behaviour(writeToLineAndPassThrough);
		define_behaviour(invalidateLineHit);
		define_behaviour(getLineContentsForWrite);
		define_behaviour(getLineContentsForRead);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_PVBusCacheControl__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_PVBusCacheControl *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline pv::TransactionGenerator* protocol_PVBusCacheControl__Implementation::createTransactionGenerator(unsigned output_port)
{
	return thisPort->createTransactionGenerator(output_port);
}

inline void protocol_PVBusCacheControl__Implementation::revokeRoutingDecisions()
{
	return thisPort->revokeRoutingDecisions();
}

inline pv::Tx_Result protocol_PVBusCacheControl__Implementation::passThroughRead(unsigned output_port, pv::ReadTransaction tx)
{
	return thisPort->passThroughRead(output_port, tx);
}

inline pv::Tx_Result protocol_PVBusCacheControl__Implementation::passThroughWrite(unsigned output_port, pv::WriteTransaction tx)
{
	return thisPort->passThroughWrite(output_port, tx);
}

inline pv::Tx_Result protocol_PVBusCacheControl__Implementation::readFromLine(pv::ReadTransaction tx, unsigned hit_line_index)
{
	return thisPort->readFromLine(tx, hit_line_index);
}

inline pv::Tx_Result protocol_PVBusCacheControl__Implementation::writeToLine(pv::WriteTransaction tx, unsigned hit_line_index)
{
	return thisPort->writeToLine(tx, hit_line_index);
}

inline pv::Tx_Result protocol_PVBusCacheControl__Implementation::writeToLineAndPassThrough(pv::WriteTransaction tx, unsigned hit_line_index, unsigned output_port)
{
	return thisPort->writeToLineAndPassThrough(tx, hit_line_index, output_port);
}

inline void protocol_PVBusCacheControl__Implementation::invalidateLineHit(unsigned hit_line_index, pv::CacheRevocation revoke_type)
{
	return thisPort->invalidateLineHit(hit_line_index, revoke_type);
}

inline char* protocol_PVBusCacheControl__Implementation::getLineContentsForWrite(unsigned line_index)
{
	return thisPort->getLineContentsForWrite(line_index);
}

inline const char* protocol_PVBusCacheControl__Implementation::getLineContentsForRead(unsigned line_index)
{
	return thisPort->getLineContentsForRead(line_index);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort)
class FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__PVBusCacheControl
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort: public FVP_VE_Cortex_A15x1__PVBusCacheControl
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->createTransactionGenerator.connectTo(&masterPort->createTransactionGenerator);
		this->revokeRoutingDecisions.connectTo(&masterPort->revokeRoutingDecisions);
		this->passThroughRead.connectTo(&masterPort->passThroughRead);
		this->passThroughWrite.connectTo(&masterPort->passThroughWrite);
		this->readFromLine.connectTo(&masterPort->readFromLine);
		this->writeToLine.connectTo(&masterPort->writeToLine);
		this->writeToLineAndPassThrough.connectTo(&masterPort->writeToLineAndPassThrough);
		this->invalidateLineHit.connectTo(&masterPort->invalidateLineHit);
		this->getLineContentsForWrite.connectTo(&masterPort->getLineContentsForWrite);
		this->getLineContentsForRead.connectTo(&masterPort->getLineContentsForRead);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__PVBusCacheControl__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

