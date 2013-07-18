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
 * Class definition for protocol FVP_VE_Cortex_A15x1__PVBusMapperControl.
 */

#ifndef FVP_VE_Cortex_A15x1__PVBusMapperControl_ClassDef_h_
#define FVP_VE_Cortex_A15x1__PVBusMapperControl_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_PVBusMapperControl.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__PVBusMapperControl;

// Abstract interface implementation for port
class protocol_PVBusMapperControl__Implementation: public protocol_PVBusMapperControl
{
public:
    protocol_PVBusMapperControl__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__PVBusMapperControl *port) { thisPort = port; }

    // Protocol members
	inline unsigned remap(pv::RemapRequest& req_);
	inline void allBusMapChanging();
	inline DVM::error_response_t handleDownstreamDVMMessageFromUpstream(unsigned upstream_port_index_, void* arc_within_port_, DVM::Message* message_);
	inline DVM::error_response_t handleUpstreamDVMMessageFromDownstream(unsigned downstream_port_index_, void* arc_within_port_, DVM::Message* message_);
	inline bool getDVMNodesCanSendTo(std::vector<pv::DVMNodeRecord> & upstream_nodes_, std::vector<pv::DVMNodeRecord> & downstream_nodes_);
	inline void* getMyArcIdentifier();
	inline void printDVMNodes(std::ostream& , const std::string& indent_);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__PVBusMapperControl *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__PVBusMapperControl: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< unsigned (pv::RemapRequest&) > remap;
	sg::MasterConnector< void (void) > allBusMapChanging;
	sg::SlaveConnector< DVM::error_response_t (unsigned,void*,DVM::Message*) > handleDownstreamDVMMessageFromUpstream;
	sg::SlaveConnector< DVM::error_response_t (unsigned,void*,DVM::Message*) > handleUpstreamDVMMessageFromDownstream;
	sg::MasterConnector< bool (std::vector<pv::DVMNodeRecord> &,std::vector<pv::DVMNodeRecord> &) > getDVMNodesCanSendTo;
	sg::MasterConnector< void* (void) > getMyArcIdentifier;
	sg::MasterConnector< void (std::ostream&,const std::string&) > printDVMNodes;


    FVP_VE_Cortex_A15x1__PVBusMapperControl()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(remap);
		define_behaviour(allBusMapChanging);
		define_behaviour(handleDownstreamDVMMessageFromUpstream);
		define_behaviour(handleUpstreamDVMMessageFromDownstream);
		define_behaviour(getDVMNodesCanSendTo);
		define_behaviour(getMyArcIdentifier);
		define_behaviour(printDVMNodes);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_PVBusMapperControl__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_PVBusMapperControl *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline unsigned protocol_PVBusMapperControl__Implementation::remap(pv::RemapRequest& req_)
{
	return thisPort->remap(req_);
}

inline void protocol_PVBusMapperControl__Implementation::allBusMapChanging()
{
	return thisPort->allBusMapChanging();
}

inline DVM::error_response_t protocol_PVBusMapperControl__Implementation::handleDownstreamDVMMessageFromUpstream(unsigned upstream_port_index_, void* arc_within_port_, DVM::Message* message_)
{
	return thisPort->handleDownstreamDVMMessageFromUpstream(upstream_port_index_, arc_within_port_, message_);
}

inline DVM::error_response_t protocol_PVBusMapperControl__Implementation::handleUpstreamDVMMessageFromDownstream(unsigned downstream_port_index_, void* arc_within_port_, DVM::Message* message_)
{
	return thisPort->handleUpstreamDVMMessageFromDownstream(downstream_port_index_, arc_within_port_, message_);
}

inline bool protocol_PVBusMapperControl__Implementation::getDVMNodesCanSendTo(std::vector<pv::DVMNodeRecord> & upstream_nodes_, std::vector<pv::DVMNodeRecord> & downstream_nodes_)
{
	return thisPort->getDVMNodesCanSendTo(upstream_nodes_, downstream_nodes_);
}

inline void* protocol_PVBusMapperControl__Implementation::getMyArcIdentifier()
{
	return thisPort->getMyArcIdentifier();
}

inline void protocol_PVBusMapperControl__Implementation::printDVMNodes(std::ostream& param0__, const std::string& indent_)
{
	return thisPort->printDVMNodes(param0__, indent_);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort)
class FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__PVBusMapperControl
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort(MxU32 inFirst,
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
class FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort: public FVP_VE_Cortex_A15x1__PVBusMapperControl
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
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
        FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->remap.connectTo(&masterPort->remap);
		this->allBusMapChanging.connectTo(&masterPort->allBusMapChanging);
		this->handleDownstreamDVMMessageFromUpstream.connectTo(&masterPort->handleDownstreamDVMMessageFromUpstream);
		this->handleUpstreamDVMMessageFromDownstream.connectTo(&masterPort->handleUpstreamDVMMessageFromDownstream);
		this->getDVMNodesCanSendTo.connectTo(&masterPort->getDVMNodesCanSendTo);
		this->getMyArcIdentifier.connectTo(&masterPort->getMyArcIdentifier);
		this->printDVMNodes.connectTo(&masterPort->printDVMNodes);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort*)port);
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
    typedef std::list<FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__PVBusMapperControl__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

