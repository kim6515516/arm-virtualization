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
 * Abstract interface class protocol_ICS307Configuration for protocol ICS307Configuration.
 */

#ifndef protocol_ICS307Configuration_h_
#define protocol_ICS307Configuration_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol ICS307Configuration
class protocol_ICS307Configuration
{
public:
        virtual ~protocol_ICS307Configuration() {}
        // Abstract protocol members
	virtual void setConfiguration(uint32_t vdw, uint32_t rdw, uint32_t od) = 0;

};

#endif /* protocol_ICS307Configuration_h_ */

