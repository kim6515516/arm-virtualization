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
 * Abstract interface class protocol_VisEventRecorderProtocol for protocol VisEventRecorderProtocol.
 */

#ifndef protocol_VisEventRecorderProtocol_h_
#define protocol_VisEventRecorderProtocol_h_

// Includes from the 'includes' section of this protocol
#line 19 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorderProtocol.lisa"

#include "components/Visualisation.h" // for struct VisEvent;
    
#line 25 "./Linux-Release-GCC-4.1/gen/protocol_VisEventRecorderProtocol.h"


// Abstract interface for protocol VisEventRecorderProtocol
class protocol_VisEventRecorderProtocol
{
public:
        virtual ~protocol_VisEventRecorderProtocol() {}
        // Abstract protocol members
	virtual bool getEvent(VisEvent* event) = 0;
	virtual void putEvent(const VisEvent* event) = 0;
	virtual void registerVisRegion(VisRegion* region, const char* regionName) = 0;
	virtual void processEvents() = 0;

};

#endif /* protocol_VisEventRecorderProtocol_h_ */

