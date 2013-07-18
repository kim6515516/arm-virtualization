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
 * Abstract interface class protocol_ValueState for protocol ValueState.
 */

#ifndef protocol_ValueState_h_
#define protocol_ValueState_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol ValueState
class protocol_ValueState
{
public:
        virtual ~protocol_ValueState() {}
        // Abstract protocol members
	virtual void setValue(uint32_t value) = 0;
	virtual uint32_t getValue() = 0;

};

#endif /* protocol_ValueState_h_ */

