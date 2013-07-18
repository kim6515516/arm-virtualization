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
 * Abstract interface class protocol_PMUEvent for protocol PMUEvent.
 */

#ifndef protocol_PMUEvent_h_
#define protocol_PMUEvent_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol PMUEvent
class protocol_PMUEvent
{
public:
        virtual ~protocol_PMUEvent() {}
        // Abstract protocol members
	virtual void fire() = 0;

};

#endif /* protocol_PMUEvent_h_ */

