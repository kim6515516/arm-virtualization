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
 * Abstract interface class protocol_TimerCallback64 for protocol TimerCallback64.
 */

#ifndef protocol_TimerCallback64_h_
#define protocol_TimerCallback64_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol TimerCallback64
class protocol_TimerCallback64
{
public:
        virtual ~protocol_TimerCallback64() {}
        // Abstract protocol members
	virtual uint64_t signal() = 0;

};

#endif /* protocol_TimerCallback64_h_ */

