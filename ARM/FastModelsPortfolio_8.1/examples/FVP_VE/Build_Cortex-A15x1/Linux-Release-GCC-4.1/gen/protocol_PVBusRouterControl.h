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
 * Abstract interface class protocol_PVBusRouterControl for protocol PVBusRouterControl.
 */

#ifndef protocol_PVBusRouterControl_h_
#define protocol_PVBusRouterControl_h_

// Includes from the 'includes' section of this protocol
#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PVBusRouter.lisa"

        #include "pv/TransactionAttributes.h"
        #include "pv/PVBusMapper.h"

        enum PVBusRouter_RouteOption
        {
            PVBUSROUTER_ABORT  = PVBUSMAPPER_ABORT,
            PVBUSROUTER_IGNORE = PVBUSMAPPER_IGNORE
        };
    
#line 32 "./Linux-Release-GCC-4.1/gen/protocol_PVBusRouterControl.h"


// Abstract interface for protocol PVBusRouterControl
class protocol_PVBusRouterControl
{
public:
        virtual ~protocol_PVBusRouterControl() {}
        // Abstract protocol members
	virtual unsigned filter(const pv::TransactionAttributes* attributes_, pv::bus_addr_t page_base_, bool is_read_) = 0;

};

#endif /* protocol_PVBusRouterControl_h_ */

