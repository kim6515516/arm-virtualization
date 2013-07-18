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
 * Abstract interface class protocol_PVBusSlaveControl for protocol PVBusSlaveControl.
 */

#ifndef protocol_PVBusSlaveControl_h_
#define protocol_PVBusSlaveControl_h_

// Includes from the 'includes' section of this protocol
#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PVBusSlaveControlProtocol.lisa"

#include "pv/PVBusSlave.h"
    
#line 25 "./Linux64-Release-GCC-4.4/gen/protocol_PVBusSlaveControl.h"


// Abstract interface for protocol PVBusSlaveControl
class protocol_PVBusSlaveControl
{
public:
        virtual ~protocol_PVBusSlaveControl() {}
        // Abstract protocol members
	virtual void setFillPattern(uint32_t fill1, uint32_t fill2) = 0;
	virtual void setAccess(pv::bus_addr_t base, pv::bus_addr_t top, pv::accessType type, pv::accessMode mode) = 0;
	virtual const uint8_t* getReadStorage(pv::bus_addr_t address, pv::bus_addr_t* limit) = 0;
	virtual uint8_t* getWriteStorage(pv::bus_addr_t address, pv::bus_addr_t* limit) = 0;
	virtual void provideReadStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, const uint8_t* storage) = 0;
	virtual void provideWriteStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, uint8_t* storage) = 0;
	virtual void provideReadWriteStorage(pv::bus_addr_t device_base, pv::bus_addr_t device_limit, uint8_t* storage) = 0;
	virtual void configure(pv::slave_config_t* ) = 0;

};

#endif /* protocol_PVBusSlaveControl_h_ */

