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
 * Abstract interface class protocol_PVDevice for protocol PVDevice.
 */

#ifndef protocol_PVDevice_h_
#define protocol_PVDevice_h_

// Includes from the 'includes' section of this protocol
#line 52 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PVDeviceProtocol.lisa"

#include "pv/PVBus.h"
    
#line 25 "./Linux-Release-GCC-4.1/gen/protocol_PVDevice.h"


// Abstract interface for protocol PVDevice
class protocol_PVDevice
{
public:
        virtual ~protocol_PVDevice() {}
        // Abstract protocol members
	virtual pv::Tx_Result read(pv::ReadTransaction tx) = 0;
	virtual pv::Tx_Result write(pv::WriteTransaction tx) = 0;
	virtual pv::Tx_Result debugRead(pv::ReadTransaction tx) = 0;
	virtual pv::Tx_Result debugWrite(pv::WriteTransaction tx) = 0;

};

#endif /* protocol_PVDevice_h_ */

