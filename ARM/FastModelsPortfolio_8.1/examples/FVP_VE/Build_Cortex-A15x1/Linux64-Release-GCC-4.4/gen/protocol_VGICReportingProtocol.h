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
 * Abstract interface class protocol_VGICReportingProtocol for protocol VGICReportingProtocol.
 */

#ifndef protocol_VGICReportingProtocol_h_
#define protocol_VGICReportingProtocol_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol VGICReportingProtocol
class protocol_VGICReportingProtocol
{
public:
        virtual ~protocol_VGICReportingProtocol() {}
        // Abstract protocol members
	virtual void logWarnings(const char* buffer_) = 0;
	virtual void logErrors(const char* buffer_) = 0;
	virtual void logFatal(const char* buffer_) = 0;
	virtual uint32_t setEnables(uint32_t new_enable_) = 0;

};

#endif /* protocol_VGICReportingProtocol_h_ */

