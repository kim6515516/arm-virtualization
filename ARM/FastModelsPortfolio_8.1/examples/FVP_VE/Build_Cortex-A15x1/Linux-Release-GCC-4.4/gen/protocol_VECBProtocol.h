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
 * Abstract interface class protocol_VECBProtocol for protocol VECBProtocol.
 */

#ifndef protocol_VECBProtocol_h_
#define protocol_VECBProtocol_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol VECBProtocol
class protocol_VECBProtocol
{
public:
        virtual ~protocol_VECBProtocol() {}
        // Abstract protocol members
	virtual bool read(const uint8_t function, const uint16_t device, uint32_t* data) = 0;
	virtual bool write(const uint8_t function, const uint16_t device, const uint32_t data) = 0;

};

#endif /* protocol_VECBProtocol_h_ */

