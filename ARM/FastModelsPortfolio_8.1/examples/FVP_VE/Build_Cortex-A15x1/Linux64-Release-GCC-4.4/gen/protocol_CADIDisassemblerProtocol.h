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
 * Abstract interface class protocol_CADIDisassemblerProtocol for protocol CADIDisassemblerProtocol.
 */

#ifndef protocol_CADIDisassemblerProtocol_h_
#define protocol_CADIDisassemblerProtocol_h_

// Includes from the 'includes' section of this protocol
#line 14 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/CADIDisassemblerProtocol.lisa"

        #include "eslapi/CADIDisassembler.h"
    
#line 25 "./Linux64-Release-GCC-4.4/gen/protocol_CADIDisassemblerProtocol.h"


// Abstract interface for protocol CADIDisassemblerProtocol
class protocol_CADIDisassemblerProtocol
{
public:
        virtual ~protocol_CADIDisassemblerProtocol() {}
        // Abstract protocol members
	virtual eslapi::CADIDisassemblerType GetType() = 0;
	virtual uint32_t GetModeCount() = 0;
	virtual void GetModeNames(eslapi::CADIDisassemblerCB* callback_) = 0;
	virtual uint32_t GetCurrentMode() = 0;
	virtual eslapi::CADIDisassemblerStatus GetSourceReferenceForAddress(eslapi::CADIDisassemblerCB* callback_, const eslapi::CADIAddr_t& address) = 0;
	virtual eslapi::CADIDisassemblerStatus GetAddressForSourceReference(const char* sourceFile, uint32_t sourceLine, eslapi::CADIAddr_t& address) = 0;
	virtual eslapi::CADIDisassemblerStatus GetDisassembly(eslapi::CADIDisassemblerCB* callback_, const eslapi::CADIAddr_t& address, eslapi::CADIAddr_t& nextAddr, const uint32_t mode, uint32_t desiredCount) = 0;
	virtual eslapi::CADIDisassemblerStatus GetInstructionType(const eslapi::CADIAddr_t& address, eslapi::CADIDisassemblerInstructionType& insn_type) = 0;

};

#endif /* protocol_CADIDisassemblerProtocol_h_ */

