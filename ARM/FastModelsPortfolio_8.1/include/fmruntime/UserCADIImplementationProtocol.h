/*!
 * \file    CustomerCADIProtocol.h
 * \date    Copyright ARM Limited 2002-2009 All Rights Reserved.
 *
 */

#ifndef _UserCADIImplementationProtocol_h_
#define _UserCADIImplementationProtocol_h_

#include "sg/SGPort.h"
#include <eslapi/CADITypes.h>

namespace eslapi
{
    class CADI;
    class CADIDisassembler;
}


namespace sg
{
    // IMPORTANT: If you add new behaviours to the protocol add the same to LISA/Builtin__Protocols.lisa!
    class UserCADIImplementationProtocol: public Port
    {
public:
        // CADI Breakpoint API 
        SlaveConnector< eslapi::CADIReturn_t (uint32_t, uint32_t, uint32_t *, eslapi::CADIBptDescription_t *) > CADIBptGetList;
        SlaveConnector< eslapi::CADIReturn_t (eslapi::CADIBptNumber_t, eslapi::CADIBptRequest_t *) > CADIBptRead;
        SlaveConnector< eslapi::CADIReturn_t (eslapi::CADIBptRequest_t *, eslapi::CADIBptNumber_t *) > CADIBptSet;
        SlaveConnector< eslapi::CADIReturn_t (eslapi::CADIBptNumber_t) > CADIBptClear;
        SlaveConnector< eslapi::CADIReturn_t (eslapi::CADIBptNumber_t, eslapi::CADIBptConfigure_t) > CADIBptConfigure;

        // The following method allows to modify the default target features provided by CADI Base. Note that this method is not 
        // part of the CADI specification. 
        SlaveConnector< eslapi::CADIReturn_t (eslapi::CADITargetFeatures_t *) > CADIModifyTargetFeatures;
        
        // disassembly (this implements both, CADIGetDisassembler() and also ObtainInterface("eslapi.CADIDisassembler2"))
        SlaveConnector< eslapi::CADIDisassembler* (void) > CADIGetDisassembler;
        
        // single stepping needs support from the individual model (run and stop are always handled globally)
        SlaveConnector< eslapi::CADIReturn_t (uint32_t instructionCount, int8_t stepCycle, int8_t stepOver) > CADIExecSingleStep;

        // forward all modeChange() callbacks to the target component
        // (the target should generally ignore all of these except when implementing CADIExecSingleStep())
        SlaveConnector< void (uint32_t newMode, eslapi::CADIBptNumber_t bptNumber) > callbackModeChange;
        
        // get instruction/cycle count
        SlaveConnector< eslapi::CADIReturn_t (uint64_t &instructionCount) > CADIGetInstructionCount;
        SlaveConnector< eslapi::CADIReturn_t (uint64_t &instructionCount, bool systemCycles) > CADIGetCycleCount;


        // constructor
        UserCADIImplementationProtocol()
        {
            define_behaviour(CADIBptGetList);
            define_behaviour(CADIBptRead);
            define_behaviour(CADIBptSet);
            define_behaviour(CADIBptClear);
            define_behaviour(CADIBptConfigure);
            define_behaviour(CADIModifyTargetFeatures);
            define_behaviour(CADIGetDisassembler);
            define_behaviour(CADIExecSingleStep);
            define_behaviour(callbackModeChange);
            define_behaviour(CADIGetInstructionCount);
            define_behaviour(CADIGetCycleCount);
        }
    };
}



#endif
