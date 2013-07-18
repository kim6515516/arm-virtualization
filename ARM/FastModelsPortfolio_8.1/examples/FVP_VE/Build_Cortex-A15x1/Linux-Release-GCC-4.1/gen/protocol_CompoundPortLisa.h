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
 * Abstract interface class protocol_CompoundPortLisa for protocol CompoundPortLisa.
 */

#ifndef protocol_CompoundPortLisa_h_
#define protocol_CompoundPortLisa_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol CompoundPortLisa
class protocol_CompoundPortLisa
{
public:
        virtual ~protocol_CompoundPortLisa() {}
        // Abstract protocol members
	virtual void connectFromExternalSlavePort(const std::string& name, sg::Port* ) = 0;
	virtual void connectToExternalMasterPort(const std::string& name, sg::Port* ) = 0;
	virtual void disconnectFromExternalSlavePort(const std::string& name, sg::Port* ) = 0;
	virtual void disconnectToExternalMasterPort(const std::string& name, sg::Port* ) = 0;

};

#endif /* protocol_CompoundPortLisa_h_ */

