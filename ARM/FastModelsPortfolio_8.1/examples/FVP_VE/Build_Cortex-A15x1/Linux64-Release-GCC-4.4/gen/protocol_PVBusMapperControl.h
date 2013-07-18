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
 * Abstract interface class protocol_PVBusMapperControl for protocol PVBusMapperControl.
 */

#ifndef protocol_PVBusMapperControl_h_
#define protocol_PVBusMapperControl_h_

// Includes from the 'includes' section of this protocol
#line 32 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PVBusMapper.lisa"

        #include "pv/TransactionAttributes.h"
        #include "pv/PVBusMapper.h"
        #include "pv/DVM.h"
        #include "pv/RemapRequest.h"
        #include "pv/DVMNodeRecord.h"
    
#line 29 "./Linux64-Release-GCC-4.4/gen/protocol_PVBusMapperControl.h"


// Abstract interface for protocol PVBusMapperControl
class protocol_PVBusMapperControl
{
public:
        virtual ~protocol_PVBusMapperControl() {}
        // Abstract protocol members
	virtual unsigned remap(pv::RemapRequest& req_) = 0;
	virtual void allBusMapChanging() = 0;
	virtual DVM::error_response_t handleDownstreamDVMMessageFromUpstream(unsigned upstream_port_index_, void* arc_within_port_, DVM::Message* message_) = 0;
	virtual DVM::error_response_t handleUpstreamDVMMessageFromDownstream(unsigned downstream_port_index_, void* arc_within_port_, DVM::Message* message_) = 0;
	virtual bool getDVMNodesCanSendTo(std::vector<pv::DVMNodeRecord> & upstream_nodes_, std::vector<pv::DVMNodeRecord> & downstream_nodes_) = 0;
	virtual void* getMyArcIdentifier() = 0;
	virtual void printDVMNodes(std::ostream& , const std::string& indent_) = 0;

};

#endif /* protocol_PVBusMapperControl_h_ */

