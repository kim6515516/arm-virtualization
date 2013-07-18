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
 * Abstract interface class protocol_v7_VGIC_Configuration_Protocol for protocol v7_VGIC_Configuration_Protocol.
 */

#ifndef protocol_v7_VGIC_Configuration_Protocol_h_
#define protocol_v7_VGIC_Configuration_Protocol_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol v7_VGIC_Configuration_Protocol
class protocol_v7_VGIC_Configuration_Protocol
{
public:
        virtual ~protocol_v7_VGIC_Configuration_Protocol() {}
        // Abstract protocol members
	virtual unsigned getNumberOfCores() = 0;
	virtual bool setMasterIdToCoreNumberMapping(uint32_t master_id_, uint32_t master_id_mask_, unsigned cpu_interface_number_, unsigned inout_cluster_number_, unsigned inout_cpu_number_in_cluster_) = 0;

};

#endif /* protocol_v7_VGIC_Configuration_Protocol_h_ */

