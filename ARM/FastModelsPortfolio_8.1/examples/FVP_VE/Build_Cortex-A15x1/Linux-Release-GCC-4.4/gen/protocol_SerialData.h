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
 * Abstract interface class protocol_SerialData for protocol SerialData.
 */

#ifndef protocol_SerialData_h_
#define protocol_SerialData_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol SerialData
class protocol_SerialData
{
public:
        virtual ~protocol_SerialData() {}
        // Abstract protocol members
	virtual void dataTransmit(uint16_t data) = 0;
	virtual uint16_t dataReceive() = 0;
	virtual void signalsSet(uint8_t signal) = 0;
	virtual uint8_t signalsGet() = 0;

};

#endif /* protocol_SerialData_h_ */

