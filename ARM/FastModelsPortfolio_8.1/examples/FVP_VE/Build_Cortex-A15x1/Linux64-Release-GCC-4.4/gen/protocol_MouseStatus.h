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
 * Abstract interface class protocol_MouseStatus for protocol MouseStatus.
 */

#ifndef protocol_MouseStatus_h_
#define protocol_MouseStatus_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol MouseStatus
class protocol_MouseStatus
{
public:
        virtual ~protocol_MouseStatus() {}
        // Abstract protocol members
	virtual void mouseMove(int dx, int dy) = 0;
	virtual void mouseButton(uint8_t button, bool down) = 0;

};

#endif /* protocol_MouseStatus_h_ */

