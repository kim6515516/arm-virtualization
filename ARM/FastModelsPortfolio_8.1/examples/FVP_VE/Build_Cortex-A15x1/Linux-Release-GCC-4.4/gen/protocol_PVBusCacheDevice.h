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
 * Abstract interface class protocol_PVBusCacheDevice for protocol PVBusCacheDevice.
 */

#ifndef protocol_PVBusCacheDevice_h_
#define protocol_PVBusCacheDevice_h_

// Includes from the 'includes' section of this protocol
#line 92 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PVBusCache.lisa"

        #include "pv/PVBus.h"
        #include "pv/PVBusCache.h"
    
#line 26 "./Linux-Release-GCC-4.4/gen/protocol_PVBusCacheDevice.h"


// Abstract interface for protocol PVBusCacheDevice
class protocol_PVBusCacheDevice
{
public:
        virtual ~protocol_PVBusCacheDevice() {}
        // Abstract protocol members
	virtual pv::Tx_Result cacheRead(unsigned in_port, pv::ReadTransaction tx) = 0;
	virtual pv::Tx_Result cacheWrite(unsigned in_port, pv::WriteTransaction tx) = 0;
	virtual pv::CacheRoutingDecision routeTransaction(unsigned in_port, pv::Transaction tx) = 0;

};

#endif /* protocol_PVBusCacheDevice_h_ */

