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
 * Abstract interface class protocol_AMBAPVValue for protocol AMBAPVValue.
 */

#ifndef protocol_AMBAPVValue_h_
#define protocol_AMBAPVValue_h_

// Includes from the 'includes' section of this protocol
#line 29 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/AMBAPVValueProtocol.lisa"

        #include <amba_pv.h>
        #include <sg/SGstdint.h>
    
#line 26 "./Linux-Release-GCC-4.1/gen/protocol_AMBAPVValue.h"


// Abstract interface for protocol AMBAPVValue
class protocol_AMBAPVValue
{
public:
        virtual ~protocol_AMBAPVValue() {}
        // Abstract protocol members
	virtual void set_state(int export_id, const uint32_t& value) = 0;

};

#endif /* protocol_AMBAPVValue_h_ */

