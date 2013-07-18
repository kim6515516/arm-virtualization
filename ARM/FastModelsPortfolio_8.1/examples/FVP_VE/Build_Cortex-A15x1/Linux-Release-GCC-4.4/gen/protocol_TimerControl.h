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
 * Abstract interface class protocol_TimerControl for protocol TimerControl.
 */

#ifndef protocol_TimerControl_h_
#define protocol_TimerControl_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol TimerControl
class protocol_TimerControl
{
public:
        virtual ~protocol_TimerControl() {}
        // Abstract protocol members
	virtual void cancel() = 0;
	virtual void set(uint32_t ticks) = 0;
	virtual bool isSet() = 0;
	virtual uint32_t remaining() = 0;

};

#endif /* protocol_TimerControl_h_ */

