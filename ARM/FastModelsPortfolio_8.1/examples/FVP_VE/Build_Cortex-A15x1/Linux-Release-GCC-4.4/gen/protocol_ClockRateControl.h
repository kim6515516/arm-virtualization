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
 * Abstract interface class protocol_ClockRateControl for protocol ClockRateControl.
 */

#ifndef protocol_ClockRateControl_h_
#define protocol_ClockRateControl_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol ClockRateControl
class protocol_ClockRateControl
{
public:
        virtual ~protocol_ClockRateControl() {}
        // Abstract protocol members
	virtual void set(uint32_t mul, uint32_t div) = 0;

};

#endif /* protocol_ClockRateControl_h_ */

