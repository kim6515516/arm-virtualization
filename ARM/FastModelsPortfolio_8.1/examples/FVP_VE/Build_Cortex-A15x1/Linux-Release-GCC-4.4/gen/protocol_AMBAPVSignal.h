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
 * Abstract interface class protocol_AMBAPVSignal for protocol AMBAPVSignal.
 */

#ifndef protocol_AMBAPVSignal_h_
#define protocol_AMBAPVSignal_h_

// Includes from the 'includes' section of this protocol
#line 20 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/AMBAPVSignalProtocol.lisa"

        #include <amba_pv.h>
    
#line 25 "./Linux-Release-GCC-4.4/gen/protocol_AMBAPVSignal.h"


// Abstract interface for protocol AMBAPVSignal
class protocol_AMBAPVSignal
{
public:
        virtual ~protocol_AMBAPVSignal() {}
        // Abstract protocol members
	virtual void set_state(int export_id, const bool& state) = 0;

};

#endif /* protocol_AMBAPVSignal_h_ */

