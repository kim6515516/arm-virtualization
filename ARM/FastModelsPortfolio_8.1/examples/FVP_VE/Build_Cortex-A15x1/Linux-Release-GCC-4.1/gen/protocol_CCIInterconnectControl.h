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
 * Abstract interface class protocol_CCIInterconnectControl for protocol CCIInterconnectControl.
 */

#ifndef protocol_CCIInterconnectControl_h_
#define protocol_CCIInterconnectControl_h_

// Includes from the 'includes' section of this protocol
#line 114 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PVCache.lisa"

        namespace CCIInterconnect { class control_if; }
    
#line 25 "./Linux-Release-GCC-4.1/gen/protocol_CCIInterconnectControl.h"


// Abstract interface for protocol CCIInterconnectControl
class protocol_CCIInterconnectControl
{
public:
        virtual ~protocol_CCIInterconnectControl() {}
        // Abstract protocol members
	virtual CCIInterconnect::control_if* getControlIf() = 0;

};

#endif /* protocol_CCIInterconnectControl_h_ */

