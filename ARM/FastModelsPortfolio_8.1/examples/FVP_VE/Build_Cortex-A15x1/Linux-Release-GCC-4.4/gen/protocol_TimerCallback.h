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
 * Abstract interface class protocol_TimerCallback for protocol TimerCallback.
 */

#ifndef protocol_TimerCallback_h_
#define protocol_TimerCallback_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol TimerCallback
class protocol_TimerCallback
{
public:
        virtual ~protocol_TimerCallback() {}
        // Abstract protocol members
	virtual uint32_t signal() = 0;

};

#endif /* protocol_TimerCallback_h_ */

