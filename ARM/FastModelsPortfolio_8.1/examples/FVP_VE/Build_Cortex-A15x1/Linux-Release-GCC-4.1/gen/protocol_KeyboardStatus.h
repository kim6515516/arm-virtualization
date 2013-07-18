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
 * Abstract interface class protocol_KeyboardStatus for protocol KeyboardStatus.
 */

#ifndef protocol_KeyboardStatus_h_
#define protocol_KeyboardStatus_h_

// Includes from the 'includes' section of this protocol
#line 11 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/KeyboardStatusProtocol.lisa"

        #include "components/KeyCode.h"
    
#line 25 "./Linux-Release-GCC-4.1/gen/protocol_KeyboardStatus.h"


// Abstract interface for protocol KeyboardStatus
class protocol_KeyboardStatus
{
public:
        virtual ~protocol_KeyboardStatus() {}
        // Abstract protocol members
	virtual void keyDown(ATKeyCode code) = 0;
	virtual void keyUp(ATKeyCode code) = 0;

};

#endif /* protocol_KeyboardStatus_h_ */

