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
 * Abstract interface class protocol_MessageBoxProtocol for protocol MessageBoxProtocol.
 */

#ifndef protocol_MessageBoxProtocol_h_
#define protocol_MessageBoxProtocol_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol MessageBoxProtocol
class protocol_MessageBoxProtocol
{
public:
        virtual ~protocol_MessageBoxProtocol() {}
        // Abstract protocol members
	virtual void begin_msg(void** bufferp, uint32_t reserve_len) = 0;
	virtual void end_msg(uint32_t actual_len) = 0;
	virtual void cancel_msg() = 0;
	virtual int32_t handle_message(const void* data, uint32_t len) = 0;

};

#endif /* protocol_MessageBoxProtocol_h_ */

