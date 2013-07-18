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
 * Abstract interface class protocol_StateSignal for protocol StateSignal.
 */

#ifndef protocol_StateSignal_h_
#define protocol_StateSignal_h_

// Includes from the 'includes' section of this protocol
#line 33 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SignalProtocol.lisa"

        #include "sg/SGSignal.h"
    
#line 25 "./Linux64-Release-GCC-4.4/gen/protocol_StateSignal.h"


// Abstract interface for protocol StateSignal
class protocol_StateSignal
{
public:
        virtual ~protocol_StateSignal() {}
        // Abstract protocol members
	virtual void setValue(sg::Signal::State ) = 0;
	virtual sg::Signal::State getValue() = 0;

};

#endif /* protocol_StateSignal_h_ */

