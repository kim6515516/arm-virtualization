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
 * Abstract interface class protocol_Value for protocol Value.
 */

#ifndef protocol_Value_h_
#define protocol_Value_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol Value
class protocol_Value
{
public:
        virtual ~protocol_Value() {}
        // Abstract protocol members
	virtual void setValue(uint32_t value) = 0;

};

#endif /* protocol_Value_h_ */

