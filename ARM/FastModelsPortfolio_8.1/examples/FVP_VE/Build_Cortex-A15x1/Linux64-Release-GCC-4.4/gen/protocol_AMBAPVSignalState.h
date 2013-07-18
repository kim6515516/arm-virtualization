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
 * Abstract interface class protocol_AMBAPVSignalState for protocol AMBAPVSignalState.
 */

#ifndef protocol_AMBAPVSignalState_h_
#define protocol_AMBAPVSignalState_h_

// Includes from the 'includes' section of this protocol
#line 43 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/AMBAPVSignalProtocol.lisa"

        #include <amba_pv.h>
    
#line 25 "./Linux64-Release-GCC-4.4/gen/protocol_AMBAPVSignalState.h"


// Abstract interface for protocol AMBAPVSignalState
class protocol_AMBAPVSignalState
{
public:
        virtual ~protocol_AMBAPVSignalState() {}
        // Abstract protocol members
	virtual void set_state(int export_id, const bool& state) = 0;
	virtual bool get_state(int export_id, tlm::tlm_tag<bool> * t) = 0;

};

#endif /* protocol_AMBAPVSignalState_h_ */

