/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2007 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Abstract interface class protocol_PVBus for protocol PVBus.
 */

#ifndef protocol_PVBus_h_
#define protocol_PVBus_h_

// Includes from the 'includes' section of this protocol
#line 50 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PVBusProtocol.lisa"

#include "pv/PVTransaction.h"

struct DeviceAccess;

namespace pv
{
    template <typename Direction> class DownstreamRequest;
    typedef DownstreamRequest<AccessRead> ReadRequest;
    typedef DownstreamRequest<AccessWrite> WriteRequest;
}

namespace DVM
{
    class UpstreamVisitor;
    class DownstreamVisitor;
}

namespace ACE
{
    class SnoopRequest;
}
    
#line 45 "./Linux-Release-GCC-4.1/gen/protocol_PVBus.h"


// Abstract interface for protocol PVBus
class protocol_PVBus
{
public:
        virtual ~protocol_PVBus() {}
        // Abstract protocol members
	virtual pv::Tx_Result read(pv::ReadTransaction tx) = 0;
	virtual pv::Tx_Result write(pv::WriteTransaction tx) = 0;
	virtual pv::Tx_Result debugRead(pv::ReadTransaction tx) = 0;
	virtual pv::Tx_Result debugWrite(pv::WriteTransaction tx) = 0;
	virtual void busMapChanging(pv::bus_addr_t base, pv::bus_addr_t size) = 0;
	virtual void busMapChanged(pv::bus_addr_t base, pv::bus_addr_t size) = 0;
	virtual void discoverDownstreamChildDVMNodes(DVM::DownstreamVisitor* ) = 0;
	virtual void discoverUpstreamParentDVMNodes(DVM::UpstreamVisitor* ) = 0;
	virtual void aceSnoopRequest(ACE::SnoopRequest* ) = 0;
	virtual void debugACESnoopRequest(ACE::SnoopRequest* ) = 0;
	virtual pv::Tx_Result doReadAccess(pv::ReadRequest* ) = 0;
	virtual pv::Tx_Result doWriteAccess(pv::WriteRequest* ) = 0;

};

#endif /* protocol_PVBus_h_ */

