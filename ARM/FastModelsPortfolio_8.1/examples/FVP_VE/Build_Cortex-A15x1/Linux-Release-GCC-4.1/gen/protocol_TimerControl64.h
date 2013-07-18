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
 * Abstract interface class protocol_TimerControl64 for protocol TimerControl64.
 */

#ifndef protocol_TimerControl64_h_
#define protocol_TimerControl64_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol TimerControl64
class protocol_TimerControl64
{
public:
        virtual ~protocol_TimerControl64() {}
        // Abstract protocol members
	virtual void cancel() = 0;
	virtual void set(uint64_t ticks) = 0;
	virtual bool isSet() = 0;
	virtual uint64_t remaining() = 0;

};

#endif /* protocol_TimerControl64_h_ */

