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
 * Abstract interface class protocol_PVBusCacheControl for protocol PVBusCacheControl.
 */

#ifndef protocol_PVBusCacheControl_h_
#define protocol_PVBusCacheControl_h_

// Includes from the 'includes' section of this protocol
#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PVBusCache.lisa"

        #include "pv/PVBusCache.h"
        #include "pv/PVBusMaster.h"
    
#line 26 "./Linux-Release-GCC-4.1/gen/protocol_PVBusCacheControl.h"


// Abstract interface for protocol PVBusCacheControl
class protocol_PVBusCacheControl
{
public:
        virtual ~protocol_PVBusCacheControl() {}
        // Abstract protocol members
	virtual pv::TransactionGenerator* createTransactionGenerator(unsigned output_port) = 0;
	virtual void revokeRoutingDecisions() = 0;
	virtual pv::Tx_Result passThroughRead(unsigned output_port, pv::ReadTransaction tx) = 0;
	virtual pv::Tx_Result passThroughWrite(unsigned output_port, pv::WriteTransaction tx) = 0;
	virtual pv::Tx_Result readFromLine(pv::ReadTransaction tx, unsigned hit_line_index) = 0;
	virtual pv::Tx_Result writeToLine(pv::WriteTransaction tx, unsigned hit_line_index) = 0;
	virtual pv::Tx_Result writeToLineAndPassThrough(pv::WriteTransaction tx, unsigned hit_line_index, unsigned output_port) = 0;
	virtual void invalidateLineHit(unsigned hit_line_index, pv::CacheRevocation revoke_type) = 0;
	virtual char* getLineContentsForWrite(unsigned line_index) = 0;
	virtual const char* getLineContentsForRead(unsigned line_index) = 0;

};

#endif /* protocol_PVBusCacheControl_h_ */

