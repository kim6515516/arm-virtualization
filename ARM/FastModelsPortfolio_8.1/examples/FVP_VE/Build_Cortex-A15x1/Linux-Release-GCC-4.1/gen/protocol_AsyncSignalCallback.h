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
 * Abstract interface class protocol_AsyncSignalCallback for protocol AsyncSignalCallback.
 */

#ifndef protocol_AsyncSignalCallback_h_
#define protocol_AsyncSignalCallback_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol AsyncSignalCallback
class protocol_AsyncSignalCallback
{
public:
        virtual ~protocol_AsyncSignalCallback() {}
        // Abstract protocol members
	virtual void signal() = 0;

};

#endif /* protocol_AsyncSignalCallback_h_ */

