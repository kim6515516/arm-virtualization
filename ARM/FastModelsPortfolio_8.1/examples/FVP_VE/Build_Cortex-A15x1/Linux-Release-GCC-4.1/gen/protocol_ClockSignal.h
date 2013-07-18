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
 * Abstract interface class protocol_ClockSignal for protocol ClockSignal.
 */

#ifndef protocol_ClockSignal_h_
#define protocol_ClockSignal_h_

// Includes from the 'includes' section of this protocol
#line 52 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/ClockSignalProtocol.lisa"

        #include "sg/SGSchedulerInterfaceForComponents.h"
    
#line 25 "./Linux-Release-GCC-4.1/gen/protocol_ClockSignal.h"


// Abstract interface for protocol ClockSignal
class protocol_ClockSignal
{
public:
        virtual ~protocol_ClockSignal() {}
        // Abstract protocol members
	virtual void setClock(sg::FrequencySource* ) = 0;
	virtual sg::FrequencySource* getClock() = 0;
	virtual double rateInHz() = 0;
	virtual uint64_t currentTicks() = 0;

};

#endif /* protocol_ClockSignal_h_ */

