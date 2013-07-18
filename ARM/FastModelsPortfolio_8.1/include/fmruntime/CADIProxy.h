/*!
 * \file    CADIProxy.h
 * \brief   transparent, overridable CADI proxy interface
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * Impplements an CADI interface that forwards all calls to another interface
 * All methods can be overridden to alter the behaviour
 */

#ifndef CADI_PROXY_H
#define CADI_PROXY_H

#include <list>

#include "TxLib/TxLib.h"

#include "eslapi/CADI.h"

class CADIProxy : public eslapi::CADI, public eslapi::CADICallbackObj
{
    struct callback_t
    {
        // owner
        eslapi::CADICallbackObj* callbackObj;

        // enable flags for callback object
        char enable[eslapi::CADI_CB_Count];
    };

    // combined enable state presented to underlying interface
    char combined_enable[eslapi::CADI_CB_Count];

    // count of how many callbacks are enabled
    int enable_count[eslapi::CADI_CB_Count];

    // the actual interface
    eslapi::CADI* cadi;

    // has the proxy been disconnected from the cadi interface
    bool unconnected;

    // list of standard callbacks objects
    std::list<callback_t> callback;

    // Mutex to protect callback structures
    TxMutex mutex;

protected:
    // reference count managed by CADIXfaceAddRef and CADIXfaceRelease
    uint16_t reference_count;

    // defines the return type when cadi has been killed.
    eslapi::CADIReturn_t unconnected_error() { return eslapi::CADI_STATUS_TargetNotResponding; }


public:

    //// constructor/destructor

    CADIProxy(eslapi::CADI*);
    virtual ~CADIProxy();

    // stop any _new_ cadi calls being made. This doesn't synchronise with
    // any calls in flight from other threads. This could be done with
    // yet another mutex.
    void disconnect();

    // release references to the underlying interface. The caller must make
    // sure there are no calls still in flight from other threads
    virtual void release();

    //// overrideable callback interface

    virtual uint32_t appliOpen(const char *sFileName, const char *mode);
    //virtual void appliInput(uint32_t streamId, uint32_t maxNumOfWords, uint32_t *actualNumOfWords, uint32_t *buffer);
    //virtual void appliOutput(uint32_t streamId, uint32_t count, uint32_t *actualCount, uint32_t *buffer);
    virtual void appliInput(uint32_t streamId, uint32_t count, uint32_t *actualCount, char *buffer);
    virtual void appliOutput(uint32_t streamId, uint32_t count, uint32_t *actualCount, const char *buffer);
    virtual uint32_t appliClose(uint32_t streamID);
    virtual void doString(const char *stringArg);
    virtual void modeChange(uint32_t newMode, eslapi::CADIBptNumber_t bptNumber);
    virtual void reset(uint32_t resetLevel);
    virtual void cycleTick(void);

    // killInterface should not be blocked
    virtual void killInterface(void);

    virtual uint32_t bypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    virtual uint32_t lookupSymbol(uint32_t symbolLength, const char *symbol, uint32_t maxResponseLength, char *response);

    virtual void refresh(uint32_t /* refreshReason */);

    //// overrideable CADI interface
    CAInterface* ObtainInterface(eslapi::if_name_t /*ifName*/, eslapi::if_rev_t /*minRev*/, eslapi::if_rev_t * /* actualRev*/);
        
    virtual eslapi::CADIReturn_t CADIXfaceGetFeatures (eslapi::CADITargetFeatures_t *features);
    virtual eslapi::CADIReturn_t CADIXfaceGetError (uint32_t maxMessageLength, uint32_t *actualMessageLength, char *errorMessage);

    virtual eslapi::CADIReturn_t CADIXfaceAddCallback (eslapi::CADICallbackObj *callbackObj, char enable[eslapi::CADI_CB_Count]);
    virtual eslapi::CADIReturn_t CADIXfaceRemoveCallback (eslapi::CADICallbackObj *callbackObj);
    virtual eslapi::CADIReturn_t CADIXfaceBypass (uint32_t /*commandLength*/, const char * /*command*/, uint32_t /*maxResponseLength*/, char * /*response*/);

    virtual eslapi::CADIReturn_t CADIRegGetGroups    (uint32_t groupIndex, uint32_t desiredNumOfRegGroups, uint32_t* actualNumOfRegGroups, eslapi::CADIRegGroup_t* reg);
    virtual eslapi::CADIReturn_t CADIRegGetMap        (uint32_t groupID, uint32_t regIndex, uint32_t registerSlots, uint32_t* registerCount, eslapi::CADIRegInfo_t* reg);        
    virtual eslapi::CADIReturn_t CADIRegGetCompound    (uint32_t reg, uint32_t componentIndex, uint32_t desiredNumOfComponents, uint32_t *actualNumOfcomponents, uint32_t *components);
    virtual eslapi::CADIReturn_t CADIRegWrite        (uint32_t regCount, eslapi::CADIReg_t* reg, uint32_t* numRegsWritten, uint8_t doSideEffects);
    virtual eslapi::CADIReturn_t CADIRegRead        (uint32_t regCount, eslapi::CADIReg_t* reg, uint32_t* numRegsRead, uint8_t doSideEffects);

    virtual eslapi::CADIReturn_t CADIMemGetSpaces (uint32_t startMemSpaceIndex, uint32_t desiredNumOfMemSpaces, uint32_t *actualNumOfMemSpaces, eslapi::CADIMemSpaceInfo_t *memSpaces);
    virtual eslapi::CADIReturn_t CADIMemGetBlocks (uint32_t memorySpace, uint32_t memBlockIndex, uint32_t desiredNumOfMemBlocks, uint32_t *actualNumOfMemBlocks, 
                                           eslapi::CADIMemBlockInfo_t *memBlocks);
    virtual eslapi::CADIReturn_t CADIMemWrite (eslapi::CADIAddrComplete_t startAddress, uint32_t unitsToWrite, uint32_t unitSizeInBytes, const uint8_t *data, 
                                       uint32_t *actualNumOfUnitsWritten, uint8_t doSideEffects);
    virtual eslapi::CADIReturn_t CADIMemRead (eslapi::CADIAddrComplete_t startAddress, uint32_t unitsToRead, uint32_t unitSizeInBytes, uint8_t *data, uint32_t *actualNumOfUnitsRead, 
                                      uint8_t doSideEffects);
    virtual eslapi::CADIReturn_t CADIExecSingleStep (uint32_t instructionCount, int8_t stepCycle, int8_t stepOver);
    virtual eslapi::CADIReturn_t CADIExecReset (uint32_t resetLevel);
    virtual eslapi::CADIReturn_t CADIExecContinue ();
    virtual eslapi::CADIReturn_t CADIExecStop ();


    virtual eslapi::CADIReturn_t CADIBptGetList (uint32_t startIndex, uint32_t desiredNumOfBpts, uint32_t *actualNumOfBpts, eslapi::CADIBptDescription_t *breakpoints);
    virtual eslapi::CADIReturn_t CADIBptSet (eslapi::CADIBptRequest_t *request, eslapi::CADIBptNumber_t *breakpoint);
    virtual eslapi::CADIReturn_t CADIBptClear (eslapi::CADIBptNumber_t breakpointId);
    virtual eslapi::CADIReturn_t CADIBptConfigure (eslapi::CADIBptNumber_t breakpointId, eslapi::CADIBptConfigure_t configuration);
    virtual eslapi::CADIReturn_t CADIBptRead (eslapi::CADIBptNumber_t /*breakpointId*/, eslapi::CADIBptRequest_t * /*requestOut*/);


    virtual eslapi::CADIReturn_t CADIExecGetModes (uint32_t /*startModeIndex*/, uint32_t /*desiredNumOfModes*/, uint32_t * /*actualNumOfModes*/, eslapi::CADIExecMode_t * /*execModes*/);
    virtual eslapi::CADIReturn_t CADIExecGetResetLevels (uint32_t /*startResetLevelIndex*/, uint32_t /*desiredNumOfResetLevels*/, uint32_t * /*actualNumOfResetLevels*/, eslapi::CADIResetLevel_t * /*resetLevels*/);
    virtual eslapi::CADIReturn_t CADIExecSetMode (uint32_t /*execMode*/);
    virtual eslapi::CADIReturn_t CADIExecGetMode (uint32_t * /*execMode*/);
    //CADI 5.0: 

    virtual eslapi::CADIReturn_t CADIExecGetExceptions (uint32_t /*startExceptionIndex*/, uint32_t /*desiredNumOfExceptions*/, uint32_t * /*actualNumOfExceptions*/, eslapi::CADIException_t * /*exceptions*/);
    virtual eslapi::CADIReturn_t CADIExecAssertException (uint32_t /*exception*/, eslapi::CADIExceptionAction_t /*action*/);
    virtual eslapi::CADIReturn_t CADIExecGetPipeStages (uint32_t /*startPipeStageIndex*/, uint32_t /*desiredNumOfPipeStages*/, uint32_t * /*actualNumOfPipeStages*/, eslapi::CADIPipeStage_t * /*pipeStages*/);
    virtual eslapi::CADIReturn_t CADIExecLoadApplication (const char * /*filename*/, bool /*loadData*/, bool /*verbose*/, 
                                                  const char * /*parameters*/);
    virtual eslapi::CADIReturn_t CADIExecUnloadApplication (const char * /*filename*/);
    virtual eslapi::CADIReturn_t CADIExecGetLoadedApplications (uint32_t /*startIndex*/, uint32_t /*desiredNumberOfApplications*/, 
                                                        uint32_t * /*actualNumberOfApplicatiosReturnedOut*/, 
                                                        char * /*filenamesOut*/, uint32_t /*filenameLength*/, char * /*parametersOut*/, 
                                                        uint32_t /*parametersLength*/);

 
    virtual eslapi::CADIReturn_t CADIMemGetOverlays (
        uint32_t /*activeOverlayIndex*/,
        uint32_t /*desiredNumOfActiveOverlays*/, 
        uint32_t * /*actualNumOfActiveOverlays*/, 
        eslapi::CADIOverlayId_t * /*overlays*/);

    virtual eslapi::CADIReturn_t CADIGetCacheInfo(    uint32_t /*memSpaceID*/, 
                                            eslapi::CADICacheInfo_t* /*cacheInfo*/);
    virtual eslapi::CADIReturn_t CADICacheRead(    eslapi::CADIAddr_t /*addr*/,     // address including memspace-id
                                        uint32_t /*linesToRead*/, 
                                        uint8_t* /*data*/,            // lines * lineSize bytes
                                        uint8_t* /*tags*/,            // lines * tagbits/8 bytes
                                        bool* /*is_dirty*/,        // one per line
                                        bool* /*is_valid*/,        // one per line
                                        uint32_t* /*numLinesRead*/,
                                        bool /*doSideEffects*/);// read from underlying memory ?
    virtual eslapi::CADIReturn_t CADICacheWrite(eslapi::CADIAddr_t /*addr*/,         // address including memspace-id
                                        uint32_t /*linesToWrite*/, 
                                        const uint8_t* /*data*/,        // lines * lineSize bytes
                                        const uint8_t* /*tags*/,        // lines * tagbits/8 bytes
                                        const bool* /*is_dirty*/,    // one per line
                                        const bool* /*is_valid*/,    // one per line
                                        uint32_t* /*numLinesWritten*/,
                                        bool /*doSideEffects*/);    // write through ?
    virtual eslapi::CADIDisassembler* CADIGetDisassembler();
    virtual eslapi::CADIReturn_t CADIGetParameters(uint32_t, uint32_t, uint32_t*, eslapi::CADIParameterInfo_t*) ;
    virtual eslapi::CADIReturn_t CADISetParameters(uint32_t, eslapi::CADIParameterValue_t*, eslapi::CADIFactoryErrorMessage_t*);
    virtual eslapi::CADIReturn_t CADIGetParameterValues (uint32_t /*parameterCount*/, uint32_t * /*actualNumOfParamsRead*/, 
                                                 eslapi::CADIParameterValue_t * /*paramValuesOut*/);
    virtual eslapi::CADIReturn_t CADIGetParameterInfo (const char * /*parameterName*/, eslapi::CADIParameterInfo_t * /*param*/); 

    virtual eslapi::CADIReturn_t CADIExecGetPipeStageFields(uint32_t, uint32_t, uint32_t*, eslapi::CADIPipeStageField_t*);
    virtual eslapi::CADIReturn_t CADIGetInstructionCount(uint64_t&);
    virtual eslapi::CADIReturn_t CADIGetCycleCount(uint64_t&, bool);
    virtual uint64_t CADIGetPC();
    virtual uint64_t CADIGetPC(bool*);
    virtual eslapi::CADIAddrComplete_t VirtualToPhysical(eslapi::CADIAddrComplete_t) ;
    virtual eslapi::CADIAddrComplete_t PhysicalToVirtual(eslapi::CADIAddrComplete_t) ;

    virtual eslapi::CADIReturn_t CADIGetTargetInfo (eslapi::CADITargetInfo_t * /*targetInfo*/);
        
        
    virtual eslapi::CADIReturn_t CADIGetCommitedPCs (int /*startIndex*/, int /*desiredCount*/, int * /*actualCount*/, uint64_t * /*pcs*/);
        
};
#endif // CADI_PROXY_H
