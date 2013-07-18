// ===========================================================================
// Description : CADI2 Proxy which allow overloading single CADI 2 methods
// of a given CADI 2 pointer 
//
// Author      : ARM
// Release     : 2.0.0
//
// Copyright (c) 2006-2008 ARM Ltd. All rights reserved.
//
// ============================================================================
//

#ifndef CADI2Proxy_h
#define CADI2Proxy_h

// CADI 2.0 header:
#include <eslapi/CADI.h>

namespace eslapi {


class CADI_WEXP CADI2Proxy : public CADI
{
protected: // data
    CADI* m_cadi; 

public: // members
    CADI2Proxy(CADI *cadi) : m_cadi(cadi) {}

    virtual ~CADI2Proxy() {}

    /// Return the CAInterface name for this interface.
    static if_name_t IFNAME() { return "eslapi.CADI2"; }
    
    /// Specify the current minor revision for this interface.
    static if_rev_t IFREVISION() { return 0; }

    CAInterface* ObtainInterface (if_name_t ifName, if_rev_t minRev, if_rev_t *actualRev);

    // CADI 2.0 methods
    virtual CADIReturn_t CADIGetParameters (uint32_t startIndex, uint32_t desiredNumOfParams, uint32_t *actualNumOfParams, 
                                    CADIParameterInfo_t *params);
    virtual CADIReturn_t CADIGetParameterInfo (const char *parameterName, CADIParameterInfo_t *param);
    virtual CADIReturn_t CADIGetParameterValues (uint32_t parameterCount, uint32_t *actualNumOfParamsRead, 
                                                 CADIParameterValue_t *paramValuesOut);
    virtual CADIReturn_t CADISetParameters (uint32_t parameterCount, CADIParameterValue_t *parameters,
                                    CADIFactoryErrorMessage_t *error);
// Class Setup API
    virtual CADIReturn_t CADIXfaceGetFeatures (CADITargetFeatures_t *features);
    virtual CADIReturn_t CADIXfaceGetError (uint32_t maxMessageLength, uint32_t *actualMessageLength, char *errorMessage);
    virtual CADIReturn_t CADIXfaceAddCallback (CADICallbackObj *callbackObj, char enable[CADI_CB_Count]);
    virtual CADIReturn_t CADIXfaceRemoveCallback (CADICallbackObj *callbackObj);
    virtual CADIReturn_t CADIXfaceBypass (uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    virtual CADIReturn_t CADIGetTargetInfo (CADITargetInfo_t *targetInfo);
// Breakpoint API
    virtual CADIReturn_t CADIBptGetList (uint32_t startIndex, uint32_t desiredNumOfBpts, uint32_t *actualNumOfBpts, 
                                         CADIBptDescription_t *breakpoints);
    virtual CADIReturn_t CADIBptRead (CADIBptNumber_t breakpointId, CADIBptRequest_t *requestOut);
    virtual CADIReturn_t CADIBptSet (CADIBptRequest_t *request, CADIBptNumber_t *breakpoint);
    virtual CADIReturn_t CADIBptClear (CADIBptNumber_t breakpointId);
    virtual CADIReturn_t CADIBptConfigure (CADIBptNumber_t breakpointId, CADIBptConfigure_t configuration);
// Execution API
    virtual CADIReturn_t CADIExecGetModes (uint32_t startModeIndex, uint32_t desiredNumOfModes, uint32_t *actualNumOfModes, 
                                   CADIExecMode_t *execModes);
    virtual CADIReturn_t CADIExecGetResetLevels (uint32_t startResetLevelIndex, uint32_t desiredNumOfResetLevels,
                                         uint32_t *actualNumOfResetLevels, CADIResetLevel_t *resetLevels);
    virtual CADIReturn_t CADIExecSetMode (uint32_t execMode);
    virtual CADIReturn_t CADIExecGetMode (uint32_t *execMode);
    virtual CADIReturn_t CADIExecSingleStep (uint32_t instructionCount, int8_t stepCycle, int8_t stepOver);
    virtual CADIReturn_t CADIExecReset (uint32_t resetLevel0);
    virtual CADIReturn_t CADIExecContinue ();
    virtual CADIReturn_t CADIExecStop ();
    virtual CADIReturn_t CADIExecGetExceptions (uint32_t startExceptionIndex, uint32_t desiredNumOfExceptions,
                                        uint32_t *actualNumOfExceptions, CADIException_t *exceptions);
    virtual CADIReturn_t CADIExecAssertException (uint32_t exception, CADIExceptionAction_t action);
    virtual CADIReturn_t CADIExecGetPipeStages (uint32_t startPipeStageIndex, uint32_t desiredNumOfPipeStages, 
                                        uint32_t *actualNumOfPipeStages, CADIPipeStage_t *pipeStages);
    virtual CADIReturn_t CADIExecGetPipeStageFields (uint32_t startPipeStageFieldIndex, uint32_t desiredNumOfPipeStageFields,
                                             uint32_t *actualNumOfPipeStageFields, CADIPipeStageField_t *pipeStageFields);
    virtual CADIReturn_t CADIExecLoadApplication (const char *filename, bool loadData, bool verbose, const char *parameters);
    virtual CADIReturn_t CADIExecUnloadApplication (const char *filename);
    virtual CADIReturn_t CADIExecGetLoadedApplications (uint32_t startIndex, uint32_t desiredNumberOfApplications,
                                                uint32_t *actualNumberOfApplicatiosReturneWriteut, char *filenamesOut,
                                                uint32_t filenameLength, char *parametersOut, uint32_t parametersLength);
    virtual CADIReturn_t CADIGetInstructionCount (uint64_t &instructionCount);
    virtual CADIReturn_t CADIGetCycleCount (uint64_t &cycleCount, bool systemCycles);
    virtual CADIReturn_t CADIGetCommitedPCs (int startIndex, int desiredCount, int *actualCount, uint64_t *pcs);
// Register API
    virtual CADIReturn_t CADIRegGetGroups (uint32_t groupIndex, uint32_t desiredNumOfRegGroups, uint32_t *actualNumOfRegGroups,
                                   CADIRegGroup_t *reg);
    virtual CADIReturn_t CADIRegGetMap (uint32_t groupID, uint32_t startRegisterIndex, uint32_t desiredNumOfRegisters,
                                uint32_t *actualNumOfRegisters, CADIRegInfo_t *reg);
    virtual CADIReturn_t CADIRegGetCompound (uint32_t reg, uint32_t componentIndex, uint32_t desiredNumOfComponents, uint32_t *actualNumOfcomponents,
                                     uint32_t *components);
    virtual CADIReturn_t CADIRegWrite (uint32_t regCount, CADIReg_t *reg, uint32_t *numOfRegsWritten, uint8_t WriteSideEffects);
    virtual CADIReturn_t CADIRegRead (uint32_t regCount, CADIReg_t *reg, uint32_t *numRegsRead, uint8_t WriteSideEffects);
    virtual uint64_t CADIGetPC ();
    virtual uint64_t CADIGetPC (bool *is_virtual);
// Memory API
    virtual CADIReturn_t CADIMemGetSpaces (uint32_t startMemSpaceIndex, uint32_t desiredNumOfMemSpaces, uint32_t *actualNumOfMemSpaces,
                                   CADIMemSpaceInfo_t *memSpaces);
    virtual CADIReturn_t CADIMemGetBlocks (uint32_t memorySpace, uint32_t memBlockIndex, uint32_t desiredNumOfMemBlocks, 
                                   uint32_t *actualNumOfMemBlocks, CADIMemBlockInfo_t *memBlocks);
    virtual CADIReturn_t CADIMemWrite (CADIAddrComplete_t startAddress, uint32_t unitsToWrite, uint32_t unitSizeInBytes, 
                               const uint8_t *data, uint32_t *actualNumOfUnitsWritten, uint8_t WriteSideEffects);
    virtual CADIReturn_t CADIMemRead (CADIAddrComplete_t startAddress, uint32_t unitsToRead, uint32_t unitSizeInBytes, 
                              uint8_t *data, uint32_t *actualNumOfUnitsRead, uint8_t WriteSideEffects);
// Virtual Memory API
    virtual CADIAddrComplete_t VirtualToPhysical (CADIAddrComplete_t vaddr);
    virtual CADIAddrComplete_t PhysicalToVirtual (CADIAddrComplete_t paddr);
// Disassembler API
    virtual CADIDisassembler* CADIGetDisassembler();

    // not yet supported
    virtual CADIReturn_t CADIMemGetOverlays (uint32_t activeOverlayIndex, uint32_t desiredNumOfActiveOverlays,
                                             uint32_t *actualNumOfActiveOverlays, CADIOverlayId_t *overlays); 
    virtual CADIReturn_t CADIGetCacheInfo (uint32_t memSpaceID, CADICacheInfo_t* cacheInfo);
    virtual CADIReturn_t CADICacheRead (CADIAddr_t addr, uint32_t linesToRead, uint8_t *data, uint8_t *tags,
                                bool *is_dirty, bool *is_valid, uint32_t *numLinesRead, 
                                bool doSideEffects);
    virtual CADIReturn_t CADICacheWrite (CADIAddr_t addr, uint32_t linesToWrite, const uint8_t *data, 
                                 const uint8_t *tags, const bool *is_dirty, const bool *is_valid, 
                                 uint32_t *numLinesWritten, bool doSideEffects);

};

}
#endif // CADI2Proxy_h
