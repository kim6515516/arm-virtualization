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
 * Abstract interface class protocol_PL330_DMAC_DmaPortProtocol for protocol PL330_DMAC_DmaPortProtocol.
 */

#ifndef protocol_PL330_DMAC_DmaPortProtocol_h_
#define protocol_PL330_DMAC_DmaPortProtocol_h_

// Includes from the 'includes' section of this protocol
#line 14 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL330_DMAC_DmaPortProtocol.lisa"


    // Not all versions of the tool support enums in include sections, or include guards
    
        // request signal bits
        
        #define PL330_REQ_BURST   1
        #define PL330_REQ_SINGLE  2
        #define PL330_REQ_LBURST  4
        #define PL330_REQ_LSINGLE 8
            
        #define PL330_REQ_MASK 0xf

        // response signal bits

        #define PL330_RES_TC  1
        #define PL330_RES_CLR 2
            
        #define PL330_RES_MASK 0xf

    
#line 43 "./Linux-Release-GCC-4.4/gen/protocol_PL330_DMAC_DmaPortProtocol.h"


// Abstract interface for protocol PL330_DMAC_DmaPortProtocol
class protocol_PL330_DMAC_DmaPortProtocol
{
public:
        virtual ~protocol_PL330_DMAC_DmaPortProtocol() {}
        // Abstract protocol members
	virtual void request(uint32_t request) = 0;
	virtual void response(uint32_t response) = 0;

};

#endif /* protocol_PL330_DMAC_DmaPortProtocol_h_ */

