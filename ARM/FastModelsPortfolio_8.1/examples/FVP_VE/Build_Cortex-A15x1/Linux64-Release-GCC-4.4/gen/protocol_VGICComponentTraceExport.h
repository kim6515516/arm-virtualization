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
 * Abstract interface class protocol_VGICComponentTraceExport for protocol VGICComponentTraceExport.
 */

#ifndef protocol_VGICComponentTraceExport_h_
#define protocol_VGICComponentTraceExport_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol VGICComponentTraceExport
class protocol_VGICComponentTraceExport
{
public:
        virtual ~protocol_VGICComponentTraceExport() {}
        // Abstract protocol members
	virtual void exportTrace(void* ) = 0;

};

#endif /* protocol_VGICComponentTraceExport_h_ */

