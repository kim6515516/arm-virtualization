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
 * Abstract interface class protocol_Builtin__MxDIExecutionControl for protocol Builtin__MxDIExecutionControl.
 */

#ifndef protocol_Builtin__MxDIExecutionControl_h_
#define protocol_Builtin__MxDIExecutionControl_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol Builtin__MxDIExecutionControl
class protocol_Builtin__MxDIExecutionControl
{
public:
        virtual ~protocol_Builtin__MxDIExecutionControl() {}
        // Abstract protocol members
	virtual void run() = 0;
	virtual void step(MxU32 cycles) = 0;
	virtual void stop() = 0;
	virtual void modeChangeRun() = 0;
	virtual void modeChangeStop() = 0;
	virtual void modeChangeStopAndBreakpoint(MxU32 bptId) = 0;

};

#endif /* protocol_Builtin__MxDIExecutionControl_h_ */

