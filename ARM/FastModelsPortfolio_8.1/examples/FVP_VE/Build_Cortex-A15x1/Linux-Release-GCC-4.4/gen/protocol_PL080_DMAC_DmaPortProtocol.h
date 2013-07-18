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
 * Abstract interface class protocol_PL080_DMAC_DmaPortProtocol for protocol PL080_DMAC_DmaPortProtocol.
 */

#ifndef protocol_PL080_DMAC_DmaPortProtocol_h_
#define protocol_PL080_DMAC_DmaPortProtocol_h_

// Includes from the 'includes' section of this protocol
#line 14 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL080_DMAC_DmaPortProtocol.lisa"


    // Not all versions of the tool support enums in include sections, or include guards
    
    #if 0
            
        // request signal bits
    
        enum PL080_DMAC_Request
        {
            PL080_REQ_BURST   = 1,
            PL080_REQ_SINGLE  = 2,
            PL080_REQ_LBURST  = 4,
            PL080_REQ_LSINGLE = 8,
            
            PL080_REQ_MASK = 0xf
        };
        
        // response signal bits
        
        enum PL080_DMA_Response
        {
            PL080_RES_TC  = 1,
            PL080_RES_CLR = 2,
            
            PL080_RES_MASK = 0xf
        };
        
    #else
    
        // request signal bits
        
        #define PL080_REQ_BURST   1
        #define PL080_REQ_SINGLE  2
        #define PL080_REQ_LBURST  4
        #define PL080_REQ_LSINGLE 8
            
        #define PL080_REQ_MASK 0xf

        // response signal bits

        #define PL080_RES_TC  1
        #define PL080_RES_CLR 2
            
        #define PL080_RES_MASK 0xf

    #endif
    
#line 70 "./Linux-Release-GCC-4.4/gen/protocol_PL080_DMAC_DmaPortProtocol.h"


// Abstract interface for protocol PL080_DMAC_DmaPortProtocol
class protocol_PL080_DMAC_DmaPortProtocol
{
public:
        virtual ~protocol_PL080_DMAC_DmaPortProtocol() {}
        // Abstract protocol members
	virtual void request(uint32_t request) = 0;
	virtual void response(uint32_t response) = 0;

};

#endif /* protocol_PL080_DMAC_DmaPortProtocol_h_ */

