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
 * Abstract interface class protocol_GICv3Comms for protocol GICv3Comms.
 */

#ifndef protocol_GICv3Comms_h_
#define protocol_GICv3Comms_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol GICv3Comms
class protocol_GICv3Comms
{
public:
        virtual ~protocol_GICv3Comms() {}
        // Abstract protocol members
	virtual void sendTowardsCPU(uint8_t len, const uint8_t* data) = 0;
	virtual void sendTowardsTopLevel(uint8_t len, const uint8_t* data) = 0;
	virtual void setAXIMasterID(uint32_t master_id) = 0;

};

#endif /* protocol_GICv3Comms_h_ */

