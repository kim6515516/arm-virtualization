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
 * Abstract interface class protocol_AMBAPVValueState for protocol AMBAPVValueState.
 */

#ifndef protocol_AMBAPVValueState_h_
#define protocol_AMBAPVValueState_h_

// Includes from the 'includes' section of this protocol
#line 52 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/AMBAPVValueProtocol.lisa"

        #include <amba_pv.h>
        #include <sg/SGstdint.h>
    
#line 26 "./Linux-Release-GCC-4.1/gen/protocol_AMBAPVValueState.h"


// Abstract interface for protocol AMBAPVValueState
class protocol_AMBAPVValueState
{
public:
        virtual ~protocol_AMBAPVValueState() {}
        // Abstract protocol members
	virtual void set_state(int export_id, const uint32_t& value) = 0;
	virtual uint32_t get_state(int export_id, tlm::tlm_tag<uint32_t> * t) = 0;

};

#endif /* protocol_AMBAPVValueState_h_ */

