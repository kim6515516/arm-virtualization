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
 * Abstract interface class protocol_CADIProtocol for protocol CADIProtocol.
 */

#ifndef protocol_CADIProtocol_h_
#define protocol_CADIProtocol_h_

// Includes from the 'includes' section of this protocol
#line 16 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/CADIProtocol.lisa"

        #include "eslapi/CADITypes.h"
    
#line 25 "./Linux-Release-GCC-4.4/gen/protocol_CADIProtocol.h"


// Abstract interface for protocol CADIProtocol
class protocol_CADIProtocol
{
public:
        virtual ~protocol_CADIProtocol() {}
        // Abstract protocol members
	virtual eslapi::CADIReturn_t CADIBptGetList(uint32_t , uint32_t , uint32_t* , eslapi::CADIBptDescription_t* ) = 0;
	virtual eslapi::CADIReturn_t CADIBptRead(eslapi::CADIBptNumber_t , eslapi::CADIBptRequest_t* ) = 0;
	virtual eslapi::CADIReturn_t CADIBptSet(eslapi::CADIBptRequest_t* , eslapi::CADIBptNumber_t* ) = 0;
	virtual eslapi::CADIReturn_t CADIBptClear(eslapi::CADIBptNumber_t ) = 0;
	virtual eslapi::CADIReturn_t CADIBptConfigure(eslapi::CADIBptNumber_t , eslapi::CADIBptConfigure_t ) = 0;
	virtual eslapi::CADIReturn_t CADIModifyTargetFeatures(eslapi::CADITargetFeatures_t* ) = 0;
	virtual eslapi::CADIDisassembler* CADIGetDisassembler() = 0;
	virtual eslapi::CADIReturn_t CADIExecSingleStep(uint32_t instructionCount, int8_t stepCycle, int8_t stepOver) = 0;
	virtual void callbackModeChange(uint32_t newMode, eslapi::CADIBptNumber_t bptNumber) = 0;
	virtual eslapi::CADIReturn_t CADIGetInstructionCount(uint64_t& instructionCount) = 0;
	virtual eslapi::CADIReturn_t CADIGetCycleCount(uint64_t& instructionCount, bool systemCycles) = 0;

};

#endif /* protocol_CADIProtocol_h_ */

