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
 * Abstract interface class protocol_v8EmbeddedCrossTrigger_controlprotocol for protocol v8EmbeddedCrossTrigger_controlprotocol.
 */

#ifndef protocol_v8EmbeddedCrossTrigger_controlprotocol_h_
#define protocol_v8EmbeddedCrossTrigger_controlprotocol_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol v8EmbeddedCrossTrigger_controlprotocol
class protocol_v8EmbeddedCrossTrigger_controlprotocol
{
public:
        virtual ~protocol_v8EmbeddedCrossTrigger_controlprotocol() {}
        // Abstract protocol members
	virtual void init(unsigned number_of_triggers, unsigned intack_mask, unsigned number_of_claim_bits) = 0;
	virtual uint32_t reg_read(bool is_memory_mapped, uint32_t addr) = 0;
	virtual void reg_write(bool is_memory_mapped, uint32_t addr, uint32_t data) = 0;
	virtual void setValue_inputTrigger(unsigned index, sg::Signal::State state) = 0;
	virtual void setValue_outputTrigger(unsigned index, sg::Signal::State state) = 0;
	virtual uint8_t getPeripheralIdByte(unsigned pidn) = 0;
	virtual uint8_t getComponentIdByte(unsigned pidn) = 0;

};

#endif /* protocol_v8EmbeddedCrossTrigger_controlprotocol_h_ */

