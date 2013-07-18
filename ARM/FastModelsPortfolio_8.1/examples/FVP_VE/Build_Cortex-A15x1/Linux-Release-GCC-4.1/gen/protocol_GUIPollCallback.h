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
 * Abstract interface class protocol_GUIPollCallback for protocol GUIPollCallback.
 */

#ifndef protocol_GUIPollCallback_h_
#define protocol_GUIPollCallback_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol GUIPollCallback
class protocol_GUIPollCallback
{
public:
        virtual ~protocol_GUIPollCallback() {}
        // Abstract protocol members
	virtual void gui_callback() = 0;

};

#endif /* protocol_GUIPollCallback_h_ */

