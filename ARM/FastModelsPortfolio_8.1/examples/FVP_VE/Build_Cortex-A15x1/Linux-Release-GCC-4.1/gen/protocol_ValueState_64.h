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
 * Abstract interface class protocol_ValueState_64 for protocol ValueState_64.
 */

#ifndef protocol_ValueState_64_h_
#define protocol_ValueState_64_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol ValueState_64
class protocol_ValueState_64
{
public:
        virtual ~protocol_ValueState_64() {}
        // Abstract protocol members
	virtual void setValue(uint64_t value) = 0;
	virtual uint64_t getValue() = 0;

};

#endif /* protocol_ValueState_64_h_ */

