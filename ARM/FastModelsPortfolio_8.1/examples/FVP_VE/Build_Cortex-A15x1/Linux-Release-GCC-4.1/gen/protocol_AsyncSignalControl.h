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
 * Abstract interface class protocol_AsyncSignalControl for protocol AsyncSignalControl.
 */

#ifndef protocol_AsyncSignalControl_h_
#define protocol_AsyncSignalControl_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol AsyncSignalControl
class protocol_AsyncSignalControl
{
public:
        virtual ~protocol_AsyncSignalControl() {}
        // Abstract protocol members
	virtual void signal() = 0;

};

#endif /* protocol_AsyncSignalControl_h_ */

