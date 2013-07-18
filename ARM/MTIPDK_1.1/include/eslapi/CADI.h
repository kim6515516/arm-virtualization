// ===========================================================================
// Description : CADI interface declaration.
//
// Author      : ARM
// Release     : 2.0.0
//
// Copyright (c) 2006-2009 ARM. All rights reserved.
//
// ============================================================================
//
#ifndef CADI2_h
# define CADI2_h

# include "eslapi/CADICommon.h"
# include "eslapi/CADITypes.h"

namespace eslapi
{
    class CADIDisassembler;

    /// Base class for CADI callbacks
    class CADI_WEXP CADICallbackObj : public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADICallbackObj2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        /// @name Semihosting API
        //@{

        /// See also CADIStreamId for valid stream ids.

        /// Deprecated. Do not use.
        virtual uint32_t appliOpen(const char *sFileName,
                                   const char *mode) = 0;

        /// The target can call this function to request interactive console input from the debugger.
        /// The target should call this function only on the first debugger in the list of registered
        /// callback objects which implement this function and ignore the callbacks for all following
        /// connected debuggers which implement this function. This is in contrast to appliOutput
        /// which is always broadcast to all connected debuggers.
        /// The streamId supplied must be CADI_STREAMID_STDIN for 'stdin'.
        /// @param[in]  streamId    Represents the stream ID. Must be CADI_STREAMID_STDIN.
        /// @param[in]  count       Number of characters requested.
        /// @param[out] actualCount Number of characters supplied. This number should never be greater
        ///                         than the number requested. If this number is equal to the number of
        ///                         requested, the caller may repeat the call to request more input.
        ///                         A return value of 0 indicates end of file and a return of ~uint32(0)
        ///                         indicates an error, for example, an invalid stream ID.
        /// @param[out] buffer      The supplied character stream.  The buffer will \e not be NUL terminated.
        virtual void appliInput(uint32_t streamId,
                                uint32_t count,
                                uint32_t *actualCount,
                                char *buffer) = 0;

        /// Print console output in all connected debuggers which implement this callback function.
        /// @param[in]  streamId    Must be CADI_STREAMID_STDOUT or CADI_STREAMID_STDERR.
        /// @param[in]  count       Number of characters to output.
        /// @param[out] actualCount The number of characters output to the file. A return value of 0
        ///                         indicates end of file and a return of ~uint32_t(0) indicates an error.
        /// @param[in] buffer       The characters to output. This buffer may contain NUL characters and is
        ///                         not NUL terminated.
        virtual void appliOutput(uint32_t streamId,
                                 uint32_t count,
                                 uint32_t * actualCount,
                                 const char *buffer) = 0;

        /// Deprecated. Do not use.
        virtual uint32_t appliClose(uint32_t streamID) = 0;

        /// @param[in] stringArg  A string the debugger should output as non-semihosting output (e.g. error
        ///                       messages from the target).
        virtual void doString(const char *stringArg) = 0;

        //@}

        /// @name Execution API
        //@{

        /// @param[in] newMode    One of the CADI_EXECMODE_* constants. For an explaination of the specific
        ///                       meanings of the modeChange() callbacks please see the documentation of the
        ///                       individual CADI_EXECMODE_* constants.
        /// @param[in] bptNumber  Breakpoint number, in cases where the debugger has some action associated
        ///                       with that particular breakpoint. For example, temporary breakpoints, run a
        ///                       script after the breakpoint was hit.
        virtual void modeChange(uint32_t newMode,
                                CADIBptNumber_t bptNumber) = 0;


        /// The reset() callback is sent by a target once a CADI reset has been finished.
        /// It is identical to the modeChange(CADI_EXECMODE_ResetDone) callback. Though
        /// targets have to support both callbacks for backwards compatibility reasons,
        /// clients should favour the modeChange(CADI_EXECMODE_ResetDone) callback over
        /// this one as it will be deprecated in future CADI versions.
        virtual void reset(uint32_t resetLevel) = 0;

        /// Deprecated. Do not use.
        virtual void cycleTick(void) = 0;

        /// Deprecated. Do not use.
        virtual void killInterface(void) = 0;

        //@}


        /// @name Extension API
        //@{

        virtual uint32_t bypass(uint32_t commandLength,
                                const char * command,
                                uint32_t maxResponseLength,
                                char *response) =0;

        virtual uint32_t lookupSymbol (uint32_t symbolLength,
                                       const char *symbol,
                                       uint32_t maxResponseLength,
                                       char *response) =0;

        //@}

        /// A target can notify a debugger to update it's display for certain reasons.
        /// The reason is a combination of the CADI_REFRESH_REASON_* constants. This
        /// callback should be called whenever the state of a target changes
        /// spontaneously when the model is in state 'stopped', but not together with
        /// a modeChange(Stop), modeChange(Error) or modeChange(ResetDone) callback.
        /// For example, when a register value changes in the target because it was
        /// edited by some debugger then the target notifies other debuggers using a
        /// refresh(REGISTERS) callback. Bt when a target hits a breakpoint and stops
        /// then it would only call the neccessary modeChange() callbacks and no
        /// additional refresh() callbacks. Please take a look the documentation of the
        /// CADI_EXECMODE_* constants to see which modeChange() callbacks imply which
        /// refresh() callbacks.
        /// A target should not call this function while the simulation is running.
        ///
        /// @param[in] refreshReason  A combination of CADI_REFRESH_REASON_* bits.
        virtual void refresh(uint32_t refreshReason) = 0;
    };

    /// The Cycle Accurate Debug Interface.

    /// This interface is comprised of an object with a set of member function calls.
    /// Each debuggable object in a target system should expose a CADI interface.
    ///
    /// No function except for CADIExecStop() should ever be called while the target is running
    /// unless a specific simulation environment explicitly allows it anyway.

    class CADI_WEXP CADI : public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADI2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        /// @name Interface-Specific Data Types
        ///
        //@{
        /// @docinclude CADIReturn_t
        //@}

        /// @name Setup API
        /// CADI setup interface.
        //@{

        /// A target's debugger shall call this function when it attaches to a target.
        /// This function is typically called once per target.
        /// The debugger is free to call it more often , if needed.
        /// This call is used to determine the features supported by the target.
        /// @param[out] features The caller allocates and de-allocates memory for this parameter.
        /// @return Return value.
        virtual CADIReturn_t CADIXfaceGetFeatures(CADITargetFeatures_t *features) = 0;

        /// When an error is detected, this routine is called to get the error message.
        ///
        /// @param[in] maxMessageLength The max length of errorMessage array.
        ///                             The target shall not fill more than this number of characters
        ///                             in the array.
        /// @param[out] actualMessageLength This is the actual length of the message in the buffer.
        ///                                 If this is equal to MaxMessageLength the call can be repeated
        ///                                 to get the rest of the message.
        /// @param[out] errorMessage The caller allocates space for this parameter.
        ///                          It is big enough to hold the requested number of characters.
        /// @return Return value.
        virtual CADIReturn_t CADIXfaceGetError(uint32_t maxMessageLength,
                                               uint32_t *actualMessageLength,
                                               char *errorMessage) = 0;

        /// A target's debugger should call this to establish with the target a callback object
        /// that will handle asynchronous information from the target. The callback routines should
        /// not make calls to the target. It is possible for a debugger to receive a callback while
        /// in the middle of a call (for example, receiving a modeChange callback from within a
        /// CADIExecStop call).
        /// <p>This is the interface exposed by the debugger to a CADI object.
        /// @param[in] callbackObj  A pointer to the object whose member functions
        ///                         will be called as callbacks.
        /// @param[in] enable       The elements of this array enable or disable specific
        ///                         callbacks. The caller must always check if the callbacks
        ///                         are enabled or not and these should not be called if they
        ///                         are disabled. The target may not want to be called in
        ///                         certain cases.
        ///                         <p> The values in the array should be from CADICallbackType_t.
        /// @return         Return value.
        virtual CADIReturn_t CADIXfaceAddCallback(CADICallbackObj *callbackObj,
                                                  char enable[CADI_CB_Count]) = 0;

        /// A debugger should call this to remove any callback objects it might have added.
        /// @param[in] callbackObj  A pointer to the callback object.
        ///                         The target should not use this object any more.
        /// @return                 Return value.
        virtual CADIReturn_t CADIXfaceRemoveCallback(CADICallbackObj *callbackObj) = 0;

        /// Targets will sometimes have specialized commands. This command is designed to allow
        /// the debugger to pass a string containing one of these commands to a target. The target
        /// is free to interpret this command in any way that it wishes. This command is called
        /// whenever the debugger wants to perform one of the commands, here.
        /// @param[in]  commandLength      The length of (including the terminating NULL) command.
        ///                                This is meant to help networked versions of the interface know
        ///                                how much space to allocate for command.
        /// @param[in]  command            This is the entire command with all arguments. At the very least,
        ///                                a target should support the command 'help', the response to which
        ///                                is a list of commands supported.
        /// @param[in]  maxResponseLength  The length of the response array. The target shall truncate
        ///                                the response to fit it into the array.
        /// @param[out] response           This is a zero-terminated string returned by the target.
        ///                                The debugger should display this string to the user.
        /// @return                        Return value.
        virtual CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command,
                                             uint32_t maxResponseLength, char *response) = 0;

        /// Return the targetInfo for this model. To be filled by the model (currently filled by SoCDesigner on behalf of CADIFactory).
        /// @param[out] targetInfo  The target info returned by this call. To be allocated by caller.
        virtual CADIReturn_t CADIGetTargetInfo (CADITargetInfo_t * targetInfo) = 0;


        //@}
        /// @name Parameter API
        /// CADI parameter interface.
        //@{
        /// Get list of supported parameters and parameter information.
        virtual CADIReturn_t CADIGetParameters(uint32_t startIndex,
                                               uint32_t desiredNumOfParams,
                                               uint32_t *actualNumOfParams,
                                               CADIParameterInfo_t *params) = 0;

        /// Get parameter info for a specific parameter name.
        /// param[in] parameterName
        ///           Name of the parameter to be retrieved. This is the 'local' name in the model, not the global hierarchical name.
        /// param[out] param
        ///           Points to a single CADIParameterInfo_t buffer which should be preinitialized by the caller and filled with data by the callee.
        virtual CADIReturn_t CADIGetParameterInfo(const char *parameterName,
                                                  CADIParameterInfo_t *param) = 0;

        /// Get current parameter values.
        /// @param[in] parameterCount
        ///            Length of array paramValuesOut.
        /// @param[out] actualNumOfParamsRead
        ///            Number of valid entries in paramValuesOut. Should be initialized to 0 by caller. If an error is returned
        ///            and this is > 0 then the first actualNumOfParams entries are valid and caused no error. In this case the
        ///            entry paramValuesOut[actualNumOfParamsRead] caused the error.
        /// @param[out] paramValuesOut
        ///            Output buffer of parameter values.
        virtual CADIReturn_t CADIGetParameterValues(uint32_t parameterCount,
                                                    uint32_t *actualNumOfParamsRead,
                                                    CADIParameterValue_t *paramValuesOut) = 0;

        /// Set current parameter values.
        virtual CADIReturn_t CADISetParameters(uint32_t parameterCount,
                                               CADIParameterValue_t *parameters,
                                               CADIFactoryErrorMessage_t *error) = 0;

        //@}

        /// @name Execution API
        /// These APIs modify the execution state of the target. Note that most everything here returns
        /// before the target completes the requested action. For example, a run or even a single step
        /// returns before the target stops. The debugger is notified via callback about the completion of
        /// the request.
        /// <p>The exec mode calls are intended to provide an extension to execution modes like
        /// "run and breakpoint" for targets that have other modes. If a target does not have other modes,
        /// then these calls are redundant (and probably should not be used).
        /// <p>The execution mode array (see CADIExecGetModes) requires that certain modes have specific
        /// positions in the array. These are define in CADITypes.h like this:
        /// <code>
        ///   <br>CADI_EXECMODE_Stop = 0
        ///   <br>CADI_EXECMODE_Run = 1
        ///   <br>CADI_EXECMODE_Bpt = 2
        ///   <br>CADI_EXECMODE_Error = 3
        ///   <br>CADI_EXECMODE_HighLevelStep = 4
        ///   <br>CADI_EXECMODE_RunUnconditionally = 5
        /// </code>
        //@{

        /// Many processors have more than just a run state and a breakpoint state. This call allows the
        /// debugger to determine what these states are.
        /// @param[in]  startModeIndex     The index into the target's buffer of execution modes
        /// @param[in]  desiredNumOfModes  This is the requested number of modes This call can be repeated
        ///                                with index + count as the index
        /// @param[out] actualNumOfModes   This is the number of modes returned by the target
        /// @param[out] execModes          The caller allocates (and, if applicable, deallocates) space.
        ///                                The number of elements should be the same as actualNumOfModes.
        virtual CADIReturn_t CADIExecGetModes(uint32_t startModeIndex,
                                              uint32_t desiredNumOfModes,
                                              uint32_t *actualNumOfModes,
                                              CADIExecMode_t *execModes) = 0;

        /// Many targets have more than just one reset level.
        /// This call allows the debugger to determine what these levels are.
        /// @param[in]  startResetLevelIndex     The index into the target's buffer of reset levels.
        /// @param[in]  desiredNumOfResetLevels  This is the number of levels desired by the caller.
        ///                                      It is the number of reset levels desired by the caller.
        /// @param[out] actualNumOfResetLevels   This is the total number returned.
        /// @param[out] resetLevels              The caller allocates space. The number of elements should
        ///                                      be the same as the actualNumOfResetLevels. Reset level 0
        ///                                      has specific semantics which must be implemented by every
        ///                                      model. This reset level is referred to as "Hard Reset".
        ///                                      The semantics of this reset are that the simulation platform
        ///                                      has to be brought back into the state it had immediately
        ///                                      after instantiation. This includes reinitialization of
        ///                                      registers and memories to their initial values. This shall
        ///                                      enable a deterministic and reproducible behavior of an
        ///                                      application running on the platform.
        ///                                      Reset levels other than 0 can be used for custom CADI resets.
        ///                                      These may differ from model to model. The reset level number
        ///                                      is only supposed to serve as an identifier. There is for
        ///                                      example NO ordering by severity.
        virtual CADIReturn_t CADIExecGetResetLevels(uint32_t startResetLevelIndex,
                                                    uint32_t desiredNumOfResetLevels,
                                                    uint32_t *actualNumOfResetLevels,
                                                    CADIResetLevel_t *resetLevels) = 0;

        /// This is a way to set to the target's execution modes. This call will return immediately,
        /// possibly before the target execution mode has been reached.
        /// <p>This call is, for a subset of the execution modes, actually redundant with other APIs.
        /// A call to CADIExecSetMode (CADI_EXECMODE_Run) is equivalent to a call to CADIExecContinue.
        /// A call to CADIExecSetMode (CADI_EXECMODE_Stop) is equivalent to a call to CADIExecStop.
        /// @param[in] execMode  This number must be less than the value nrExecModes received
        ///                      by CADIXfaceGetFeatures or
        virtual CADIReturn_t CADIExecSetMode(uint32_t execMode) = 0;

        /// This call allows the debugger to determine the execution state of the target.
        /// @param[out] execMode  This number corresponds to the values received from the
        ///                       CADIExecGetModes call.
        virtual CADIReturn_t CADIExecGetMode(uint32_t *execMode) = 0;

        /// This function returns immediately and a separate notification informs the debugger
        /// that the execution state has changed. Typically this call would result in the 'modeChange'
        /// callback (if enabled) for CADI_EXECMODE_Run followed by CADI_EXECMODE_Stop.
        /// <p>The same callback is possible with CADI_EXECMODE_Bpt in case of the target hitting
        /// a breakpoint, or CADI_EXECMODE_Error in the case of target errors during it's execution.
        /// @param[in] instructionCount  This is the number of instructions requested. Some targets may not
        ///                              step a specific number of instructions safely (into a delay slot,
        ///                              for example). The target may step more instructions so that it stops
        ///                              at a safe place
        /// @param[in] stepCycle         For targets that have exposed multiple pipe stages, this argument
        ///                              specifies whether the step should merely clock the device
        ///                              (stepCycle == yes) or whether the step should flush the pipe
        ///                              (stepCycle == no). For other kinds of targets, this argument is
        ///                              ignored (stepCycle = no is assumed).
        /// @param[in] stepOver          This allows the target to handle stepping over a call. It is
        ///                              especially useful on an emulator with no available breakpoints -
        ///                              the target will have to step until the call returns or a breakpoint
        ///                              is hit.
        /// @return                      Since this call returns immediately, the return
        ///                              value indicates whether the target believes that it can perform the
        ///                              operation - not whether the operation was completed successfully.
        virtual CADIReturn_t CADIExecSingleStep(uint32_t instructionCount,
                                                int8_t stepCycle,
                                                int8_t stepOver) = 0;

        /// Upon receipt of this call, the target will reset its execution related internal state, as well
        /// as reset its registers and memories to a predefined state, but it will not change breakpoints
        /// or callbacks.
        /// <p>This call offers a generic reset interface that is independent from the actual model
        /// implementation. For example, a debugger may use this call to reset the simulation of a model,
        /// system or subsystem that do not implement an explicit simulation-level reset mechanism.
        /// @param[in] resetLevel  This should be one of the numbers provided in the resetLevels array
        ///                        from the CADIExecGetResetLevels call.
        /// The list of reset levels is target specific. There is one reset level (reset level 0) which has
        /// fixed semantics and needs to be implemented by every target. This reset level has to bring back
        /// the simulation platform into the same state as immediately after instantiation. This state has
        /// to be known in order to allow a deterministic behavior of the platform after each reset.
        /// All reset levels different from 0 are model specific.
        /// CADIExecReset() is an asynchronous call. Once the reset has been finished, the target sends a
        /// modeChange(CADI_EXECMODE_ResetDone) callback (and for backwards compatibility reasons a reset()
        /// callback) to all connected debuggers. The reset may well be finished at the time that
        /// CADIExecReset() returns.
        virtual CADIReturn_t CADIExecReset(uint32_t resetLevel) = 0;

        /// This function returns immediately and a separate notification informs the debugger when
        /// execution state has changed.
        /// @return Since this call returns immediately, the return value indicates
        ///         whether the target believes that it can perform the operation - not whether the operation
        ///         was completed successfully.
        virtual CADIReturn_t CADIExecContinue(void) = 0;

        /// This causes the target's execution to stop.
        /// @return Keep in mind that, since this call returns immediately, the return value indicates
        /// whether the target believes that it can perform the operation - not whether the operation
        /// was completed successfully.
        virtual CADIReturn_t CADIExecStop(void) = 0;

        /// This gets the list of the target's exception vectors.
        /// @param[in]  startExceptionIndex     The index into the targets list of exceptions.
        /// @param[in]  desiredNumOfExceptions  The number of slots in the exception array. The target shall
        ///                                     not fill more than this number of characters in the array.
        /// @param[out] actualNumOfExceptions   This is the total number of returned exceptions. If this is
        ///                                     less than desired count, the call can be repeated with a
        ///                                     different set of parameters.
        /// @param[out] exceptions              This is list of exceptions. The array is allocated
        ///                                     (and deallocated, if applicable) by the caller to be filled
        ///                                     by the target. This buffer should be big enough to hold the
        ///                                     desired count of exceptions.
        virtual CADIReturn_t CADIExecGetExceptions(uint32_t startExceptionIndex,
                                                   uint32_t desiredNumOfExceptions,
                                                   uint32_t *actualNumOfExceptions,
                                                   CADIException_t *exceptions) = 0;

        /// CADIExecAssertException
        /// @param[in] exception  The exception number
        /// @param[in] action     The exception action to be taken
        virtual CADIReturn_t CADIExecAssertException(uint32_t exception,
                                                     CADIExceptionAction_t action) = 0;

        /// This is used to expose the pipe simulated inside of a cycle-accurate simulation.
        /// @param[in]  startPipeStageIndex     The index into the target's list of pipe stages
        /// @param[in]  desiredNumOfPipeStages  The number of spaces available to fill. The target shall not
        ///                                     fill more than this number of elements in the pipestage array.
        /// @param[out] actualNumOfPipeStages   Number of stages actually returned to the caller.
        /// @param[out] pipeStages              The list of pipestages in order of execution for a single
        ///                                     instruction. pipestage[0] should contain the first stage executed
        ///                                     for any single instruction.
        ///                                     The array is allocated (and deallocated, if applicable) by
        ///                                     the caller to be filled by the target.
        virtual CADIReturn_t CADIExecGetPipeStages(uint32_t startPipeStageIndex,
                                                   uint32_t desiredNumOfPipeStages,
                                                   uint32_t *actualNumOfPipeStages,
                                                   CADIPipeStage_t *pipeStages) = 0;

        /// This is used to expose the fields of the pipe simulated inside of a cycle-accurate simula tion.
        /// @param[in]  startPipeStageFieldIndex        The index into the target's list of pipe stage fields
        /// @param[in]  desiredNumOfPipeStageFieldes    The number of spaces available to fill. The target shall not
        ///                                             fill more than this number of elements in the pipestagefields array.
        ///                                             The function shall not return less than this number of fields
        ///                                             if there are still fields left to deliver.
        /// @param[out] actualNumOfPipeStageFields      Number of fields actually returned to the caller.
        /// @param[out] pipeStageFields                 The list of pipe stage fields. They may but must not be sorted according to the
        ///                                             pipeline stages.
        ///                                             The array is allocated (and deallocated, if applicable) by
        ///                                             the caller to be filled by the target.
        virtual CADIReturn_t CADIExecGetPipeStageFields(uint32_t startPipeStageFieldIndex,
                                                        uint32_t desiredNumOfPipeStageFields,
                                                        uint32_t *actualNumOfPipeStageFields,
                                                        CADIPipeStageField_t *pipeStageFields) = 0;

        /// Load application.
        /// @param[in] loadData
        ///            If set to false, the target does not reload the application code into the target's program memory.
        ///            This can be used, for example, in order to forward information about applications which are loaded
        ///            by a different platform component. Another example is changing command line parameters set through
        ///            a previous CADIExecLoadApplication() call without having to write the application to the target again.
        /// @param[in] verbose
        ///            If true print verbose messages while loading a file (a target ultimately decides whether it can do that).
        /// @param[in] parameters
        ///            If different from NULL, the command line parameters to be passed to the loaded application call. The
        ///            forwarded character string might contain whitespaces and must be 0 terminated.
        ///            In case of a model not supporting this argument but receiving command line parameters, this model
        ///            must return CADI_STATUS_ArgNotSupported.
        virtual CADIReturn_t CADIExecLoadApplication(const char *filename,
                                                     bool loadData,
                                                     bool verbose,
                                                     const char *parameters) = 0;

        /// Remove the symbol information of a specific image which has been loaded previously.
        /// @param[in] filename
        ///            The contents of this C string must be exactly the same as was specified for CADIExecLoadApplication().
        /// -# A target ultimately decides whether it can do that at all.
        virtual CADIReturn_t CADIExecUnloadApplication(const char *filename) = 0;

        /// Get list of image filenames currently loaded in target. This list shall be preserved until calling CADIExecReset(0)
        /// or until a custom CADI reset is called with CADIExecReset() that clears the program memory.
        /// @param[in] startIndex
        ///            Starting index in list of filenames.
        /// @param[in] desiredNumberOfApplications
        ///            Desired number of applications (filename + parameters).
        /// @param[in] actualNumberOfApplicationsReturnedOut
        ///            Number of applicatiosn (filenames + parameters) which are valid in filenamesOut and parametersOut.
        /// @param[out] FilenamesOut
        ///             A buffer of length [desiredNumberOfFilenames * filenamLength], the Nth filename returned starts at offset N*filenameLength.
        /// @param[in] filenameLength
        ///            Maximum length of a single filename including terminating 0, filenames which are longer are truncated.
        /// -# All returned filenames must always be 0 terminated.
        /// -# If one of the returned filenames has the length filenameLength-1 then filenameLength was too short and should be redone.
        /// -# A target ultimately decides whether it can keep information of more than one file at all.
        /// @param[out] parametersOut
        ///             A buffer of length [desiredNumberOfApplications * parametersLength], the Nth filename returned starts at offset N*parametersLength.
        /// @param[in] parametersLength
        ///            Maximum length of a single parameters string including terminating 0, parameters which are longer are truncated.
        /// -# All returned parameters must always be 0 terminated.
        /// -# If one of the returned parameters has the length parametersLength-1 then parametersLength was too short and should be redone.
        /// -# A target ultimately decides whether it can keep information of more than one file at all.
        virtual CADIReturn_t CADIExecGetLoadedApplications(uint32_t startIndex,
                                                           uint32_t desiredNumberOfApplications,
                                                           uint32_t *actualNumberOfApplicatiosReturnedOut,
                                                           char *filenamesOut,
                                                           uint32_t filenameLength,
                                                           char *parametersOut,
                                                           uint32_t parametersLength) = 0;

        /// Get currrent instruction count of the specific target this interface is connectwed to.
        /// @prama[out] instructionCount
        ///             Instruction count. Should be always pre-initialized by the caller and always assigned by the callee.
        virtual CADIReturn_t CADIGetInstructionCount(uint64_t &instructionCount) = 0;

        /// Get cycle count.
        /// @param[out] cycleCount
        ///             Cycle count. Should be always pre-initialized by the caller and always assigned by the callee.
        /// @param[in] systemCycles
        ///             If true return the system cycle count. If false return the target specific cycle count.
        virtual CADIReturn_t CADIGetCycleCount(uint64_t &cycleCount,
                                               bool systemCycles) = 0;

        //@}




        /// @name Register API
        /// These functions are used to access the target's registers.
        //@{
        /// @docinclude CADIRegAccessAttribute_t
        /// @docinclude CADIReg_t

        /// This call is used to retrieve register groups from the target.
        /// @param[in]  groupIndex
        ///               This is the index into the target's list of register groups. It is NOT groups ID's.
        /// @param[in]  desiredNumOfRegGroups
        ///               This is the total number of register groups desired by the caller. The caller
        ///               allocates a buffer size that is as big as the number requested.
        /// @param[out] actualNumOfRegGroups
        ///               This is the number of groups returned by the target. If this is less than the
        ///               number requested, the call may be repeated.
        /// @param[out] reg
        ///               This is the register group information The array is allocated (and deallocated,
        ///               if applicable) by the caller to be filled by the target. The amount of space allocated
        ///               should be enough to hold the number of groups desired. If the count is greater than
        ///               the targets number of register groups, the target should just return all the groups.
        virtual CADIReturn_t CADIRegGetGroups (uint32_t groupIndex,
                                               uint32_t desiredNumOfRegGroups,
                                               uint32_t *actualNumOfRegGroups,
                                               CADIRegGroup_t *reg) = 0 ;

        /// A target's debugger should call this once after connecting to the target. All registers should be
        /// reported even if they are a piece of a compound register. All register numbers must be unique,
        /// even with respect to registers in other groups.
        /// @param[in]  groupID
        ///               This identifies the ID of the group whose map is requested. If the value is
        ///               CADI_REG_ALLGROUPS, all registers are returned.
        /// @param[in]  startRegisterIndex
        ///               This is the index into the target's list of registers. It is NOT register numbers.
        /// @param[in]  desiredNumOfRegisters
        ///               This is the total number of registers desired by the caller. The caller allocates
        ///               a buffer size that is as big as the number requested.
        /// @param[out] actualNumOfRegisters
        ///               This is the number of registers returned by the target.
        /// @param[out] reg
        ///               This is the register information. The array is allocated (and deallocated,
        ///               if applicable) by the caller to be filled by the target. The amount of space
        ///               allocated should be enough to hold the number of registers requested. If the count
        ///               is greater than the targets number of registers, the target should just return all
        ///               the registers.
        virtual CADIReturn_t CADIRegGetMap (uint32_t groupID,
                                            uint32_t startRegisterIndex,
                                            uint32_t desiredNumOfRegisters,
                                            uint32_t *actualNumOfRegisters,
                                            CADIRegInfo_t *reg) = 0;

        /// This call gets the information about a compound register (as reported by a CADIRegGetMap call).
        /// A model _may_ expose a set of registers in such a way that they form a Directed Acyclic Graph
        /// (DAG), it _must not_ form a cyclic graph.  A debugger _must_ be able to cope with an acyclic
        /// graph, it _may_ detect a cyclic graph and report an error.
        /// @param[in]  reg
        ///
        /// @param[in]  componentIndex
        ///               The index into the this register's (reg) component array.
        /// @param[in]  desiredNumOfComponents
        ///               This is the total number of child registers desired by the caller, starting at
        ///               componentRegIndex.
        /// @param[out] actualNumOfcomponents
        ///               This is the number of components returned by the target.
        /// @param[out] components
        ///               This is the list of component registers where componentRegNums[0] contains the least
        ///               significant register number in compound register. The array is allocated (and
        ///               deallocated, if applicable) by the caller to be filled by the target. The amount
        ///               of space allocated should be big enough to hold the number requested.
        virtual CADIReturn_t CADIRegGetCompound (uint32_t reg,
                                                 uint32_t componentIndex,
                                                 uint32_t desiredNumOfComponents,
                                                 uint32_t *actualNumOfcomponents,
                                                 uint32_t *components) = 0;

        /// This function writes a register.
        /// Writes should never trigger breakpoints directly themselves. However, it is
        /// target implementation-defined whether it recognises a modify-triggered breakpoint when
        /// the simulation starts again.
        /// @param[in]  regCount
        ///               The number of registers in the reg array.
        /// @param[in]  reg
        ///               This is an array of structures each holding the number (as gathered from the
        ///               CADIRegGetMap call) and value of an individual register. The number of bytes
        ///               allocated for each register is available from the CADIRegGetMap call.
        /// @param[out] numOfRegsWritten
        ///               The number of registers that are actually written.
        /// @param[in]  doSideEffects
        ///               Indicates whether operation should incur side-effects.
        virtual CADIReturn_t CADIRegWrite (uint32_t regCount,
                                           CADIReg_t *reg,
                                           uint32_t *numOfRegsWritten,
                                           uint8_t doSideEffects) = 0;

        /// This function reads the values of the target's registers.
        /// @param[in]  regCount
        ///               The number of registers in the reg array.
        /// @param[in,out] reg
        ///               This is a pointer to an array of structures each holding the number (as gathered
        ///               from the CADIRegGetMap call) and value of an individual register.
        ///               The debugger allocates the array and the bytes for each register. The number of bytes
        ///               allocated for each register is available from the CADIRegGetMap call.
        /// @param[out] numRegsRead
        ///               This is the number of registers actually read. It can be less than the number of
        ///               registers in 'reg'.
        /// @param[in]  doSideEffects
        ///               Indicates whether operation should incur side-effects.
        virtual CADIReturn_t CADIRegRead (uint32_t regCount,
                                          CADIReg_t *reg,
                                          uint32_t *numRegsRead,
                                          uint8_t doSideEffects) = 0;

        virtual uint64_t CADIGetPC() = 0;

        virtual uint64_t CADIGetPC(bool* is_virtual) = 0;


        /// Get commmited PCs. Returns the list of all commited PCs in the current cycle (e.g., for multi-issue processors)
        /// Implementing this method is not required for single-issue processors and may result in simulation slowdowns in certain situations.
        /// @param[in] startIndex
        ///             Start index in list of PCs
        /// @param[in] desiredCount
        ///             Desired number of PCs
        /// @param[out] actualCount
        ///             Actual number of PCs returned
        /// @param[in] pcs
        ///             List of PCs returned. To be allocated by caller with at least desiredCount elements.
        virtual CADIReturn_t CADIGetCommitedPCs (int startIndex,
                                                  int desiredCount,
                                                  int * actualCount,
                                                  uint64_t * pcs) = 0;
        //@}



        /// @name Memory API
        /// These APIs are used to access the target memory.
        //@{
        /// @docinclude CADIMemSpace_t
        /// @docinclude CADIOverlayId_t
        /// @docinclude CADIAddrSimple_t
        /// @docinclude CADIAddr_t
        /// @docinclude CADIAddrComplete_t


        /// A target's debugger should call this once after connecting to the target but before accessing
        /// memory. This gets the number of independent address spaces available on the target. Different
        /// memory spaces should be used to separate distinct memory areas with overlapping address values
        /// (like program and data memory in a Harvard architecture).
        /// @param[in]  startMemSpaceIndex      The index into the target's buffer of memory spaces
        /// @param[in]  desiredNumOfMemSpaces   The desired number of memory spaces.
        /// @param[out] actualNumOfMemSpaces    This is the total number of memory spaces returned by the target.
        /// @param[out] memSpaces               This is list of memory spaces. The array is allocated (and
        ///                                     deallocated, if applicable) by the caller to be filled by the
        ///                                     target. This space should be big enough to hold the desired
        ///                                     number of spaces.
        virtual CADIReturn_t CADIMemGetSpaces (uint32_t startMemSpaceIndex,
                                               uint32_t desiredNumOfMemSpaces,
                                               uint32_t *actualNumOfMemSpaces,
                                               CADIMemSpaceInfo_t *memSpaces) = 0;

        /// A target's debugger should call this once for each memory space specified by CADIMemGetSpaces
        /// before accessing memory in that space. This should return the layout of the memory in a single
        /// address space. No two blocks with the same parent should overlap. This call returns existing
        /// memory blocks only. The caller can assume that any memory not in a block is a hole or invalid
        /// memory.
        /// @param[in]  memorySpace             This is the memory space for which the caller wants a block list.
        /// @param[in]  memBlockIndex           The index into the target's buffer of memory blocks for the
        ///                                     specified memory space
        /// @param[in]  desiredNumOfMemBlocks   The desired number of memory blocks
        /// @param[out] actualNumOfMemBlocks    This is the total number of blocks returned by the target.
        ///                                     It may be less than the number requested.
        /// @param[out] memBlocks               Space is allocated (and deallocated, if applicable) for memBlock
        ///                                     by the caller. This buffer should be big enough to hold the
        ///                                     desired number of CADIMemBlockInfo_t structures.
        virtual CADIReturn_t CADIMemGetBlocks (uint32_t memorySpace,
                                               uint32_t memBlockIndex,
                                               uint32_t desiredNumOfMemBlocks,
                                               uint32_t *actualNumOfMemBlocks,
                                               CADIMemBlockInfo_t *memBlocks) = 0;

        /// This causes the target's memory to get new values. If the write spans a hole in memory,
        /// the target should stop writing at the beginning of the hole and reflect the discrepancy
        /// in the numUnitsWritten.
        /// Writes to memory should never trigger breakpoints directly themselves. However, it is
        /// target implementation-defined whether it recognises a modify-triggered breakpoint when
        /// the simulation starts again.
        /// @param[in]  startAddress
        ///               The starting address to begin writing from. If startAddress.overlay is CADI_NO_OVERLAY,
        ///               it refers to the current overlay.
        /// @param[in]  unitsToWrite
        ///               This is the number of units of size unitSizeInBytes  to write.
        /// @param[in]  unitSizeInBytes
        ///               This is the unit size of the addresses specified in bytes.
        /// @param[in]  data
        ///               Data buffer holding the values to be written.
        ///               This contains target data, encoded in little endian format.
        /// @param[out] actualNumOfUnitsWritten
        ///               The number of units actually written to target.
        /// @param[in]  doSideEffects
        ///               Indicates whether operation should incur any side effects associated with accessing
        ///               this memory.
        /// @return       On error, CADIMemWrite shall return the error position in actualNumOfUnits*;
        ///               Data is assumed valid up to this position.
        virtual CADIReturn_t CADIMemWrite (CADIAddrComplete_t startAddress,
                                           uint32_t unitsToWrite,
                                           uint32_t unitSizeInBytes,
                                           const uint8_t *data,
                                           uint32_t *actualNumOfUnitsWritten,
                                           uint8_t doSideEffects) = 0;

        /// This causes memory to be read from the target. If the read spans a hole in memory, the target should
        /// stop reading at the beginning of the hole and reflect the discrepancy in the numUnitsRead.
        /// @param[in]  startAddress
        ///               The starting address to read from. If startAddress.overlay is CADI_NO_OVERLAY, it
        ///               refers to the current overlay.
        /// @param[in]  unitsToRead
        ///               This is the number of units of size unitSizeInBytes to read.
        /// @param[in]  unitSizeInBytes
        ///               This is the unit size of the addresses specified in bytes.
        /// @param[out] data
        ///               Data buffer, allocated by the caller, should be big enough to hold the requested
        ///               number of addresses.
        ///               This contains target data, encoded in little endian format.
        /// @param[out] actualNumOfUnitsRead
        ///               This is the actual number of units read. It can be less than the number of units requested.
        /// @param[in]  doSideEffects
        ///               Indicates whether operation should incur side-effects.
        /// @return       On error, CADIMemRead shall return the error position in actualNumOfUnits*.
        ///               Data is assumed valid up to this position.
        virtual CADIReturn_t CADIMemRead (CADIAddrComplete_t startAddress,
                                          uint32_t unitsToRead,
                                          uint32_t unitSizeInBytes,
                                          uint8_t *data,
                                          uint32_t *actualNumOfUnitsRead,
                                          uint8_t doSideEffects) = 0;

        /// The debugger calls this when it wants to get the list of active overlays. This would typically be done
        /// when a breakpoint is hit.
        /// <p><b>Language Domain Requirement.</b> When overlays are implemented, some overlay ID needs to be
        /// stored in the symbol table and in the target software. The symbol table should store the starting
        /// address, memory space, and byte count for each overlay. This will allow the ID to be sent to the host
        /// when an overlay happens and allow the host to understand what it means.
        /// @param[in]  activeOverlayIndex
        ///               The start index into the target's buffer of overlays.
        /// @param[in]  desiredNumOfActiveOverlays
        ///               This is the desired number of overlays.
        /// @param[out] actualNumOfActiveOverlays
        ///               This is the number of overlay structures returned by the target.
        /// @param[out] overlays
        ///               This is the list of overlays that are currently memory resident (i.e., swapped-in).
        ///               The array is allocated (and deallocated, if applicable) by the caller to be filled by
        ///               the target.
        virtual CADIReturn_t CADIMemGetOverlays (uint32_t activeOverlayIndex,
                                                 uint32_t desiredNumOfActiveOverlays,
                                                 uint32_t *actualNumOfActiveOverlays,
                                                 CADIOverlayId_t *overlays) = 0;
        //@}



        /// @name Breakpoint API
        /// These functions are used to manipulate breakpoints in the target.
        //@{
        /// @docinclude CADIBptNumber_t
        /// @docinclude CADIBptType_t
        /// @docinclude CADIBptConditionOperator_t
        /// @docinclude CADIBptCondition_t
        /// @docinclude CADIBptRequest_t
        /// @docinclude CADIBptDescription_t
        /// @docinclude CADIBptConfigure_t

        /// If the debugger attaches to a target that already has breakpoints set,
        /// this is a way for the debugger to find out what they are.
        /// @param[in]  startIndex        The index into the target's buffer of breakpoints.
        /// @param[in]  desiredNumOfBpts  The desired number of breakpoints
        /// @param[out] actualNumOfBpts   The number of breakpoints that are returned in the buffer.
        /// @param[out] breakpoints       The array of breakpoints. The array is allocated (and deallocated,
        ///                               if applicable) by the caller to be filled by the target. It should
        ///                               be big enough to hold 'desiredBptCount' entries.
        /// @return                       Return value
        virtual CADIReturn_t CADIBptGetList(uint32_t startIndex,
                                            uint32_t desiredNumOfBpts,
                                            uint32_t *actualNumOfBpts,
                                            CADIBptDescription_t *breakpoints) = 0;

        /// Read a breakpoint for a specific breakpoint ID.
        /// This can be used to retrieve the current ignoreCount of a specific breakpoint.
        /// @param[in] breakpointId
        ///            Breakpoint ID of the breakpoint to be read.
        /// @param[out] requestOut
        ///            Buffer for a single breakpoint.
        virtual CADIReturn_t CADIBptRead(CADIBptNumber_t breakpointId,
                                         CADIBptRequest_t *requestOut) = 0;

        /// This sets a, possibly complex, breakpoint in the target.
        /// The breakpoint will be initially enabled or disabled depending on the value of 'request->enabled'.
        /// @param[in]  request     The requested breakpoint
        /// @param[out] breakpoint  The resulting breakpoint ID (zero if the breakpoint was not set).
        virtual CADIReturn_t CADIBptSet(CADIBptRequest_t *request,
                                        CADIBptNumber_t *breakpoint) = 0;

        /// This function removes a breakpoint from the target.
        /// @param[in] breakpointId The requested breakpoint
        virtual CADIReturn_t CADIBptClear(CADIBptNumber_t breakpointId) = 0;

        /// This function enables or disables a breakpoint on the target. This only makes sense when
        /// the target supports enabling and disabling of hardware breakpoints. Otherwise, this sort
        /// of breakpoint management must be done in the host.
        /// @param[in] breakpointId   The requested breakpoint
        /// @param[in] configuration  The requested configuration
        virtual CADIReturn_t CADIBptConfigure(CADIBptNumber_t breakpointId,
                                              CADIBptConfigure_t configuration) = 0;
        //@}



        /// @name Cache API
        /// These functions are used to access the target's cache memories.
        //@{
        /// @docinclude CADICacheInfo_t

        /// This call is used to get the cache information for a memory space.
        /// @param[in]  memSpaceID
        ///               The memory space.
        /// @param[out] cacheInfo
        ///               The cache information.
        virtual CADIReturn_t CADIGetCacheInfo(uint32_t memSpaceID,
                                              CADICacheInfo_t* cacheInfo) = 0;

        /// This call is used to perform a cache read.
        /// @param[in]  addr            This is the address to be read, including memspace-id.
        /// @param[in]  linesToRead     Number of cache lines to read.
        /// @param[out] data            lines * line_size bytes, encoded in little endian format.
        /// @param[out] tags            lines * tagsbits/8 bytes.
        /// @param[out] is_dirty        One per line.
        /// @param[out] is_valid        One per line.
        /// @param[out] numLinesRead    Number of cache lines actually read.
        /// @param[in]  doSideEffects   If true, then read from underlying memory.
        virtual CADIReturn_t CADICacheRead(CADIAddr_t addr,
                                           uint32_t linesToRead,
                                           uint8_t* data,
                                           uint8_t* tags,
                                           bool* is_dirty,
                                           bool* is_valid,
                                           uint32_t* numLinesRead,
                                           bool doSideEffects) = 0;

        /// This call is used to perform a cache write.
        /// @param[in]  addr            This is the address to be written, including memspace-id.
        /// @param[in]  linesToWrite    Number of cache lines to write.
        /// @param[out] data            lines * line_size bytes, encoded in little endian format.
        /// @param[out] tags            lines * tagsbits/8 bytes.
        /// @param[out] is_dirty        One per line.
        /// @param[out] is_valid        One per line.
        /// @param[out] numLinesWritten Number of cache lines actually writeen.
        /// @param[in]  doSideEffects   If true, then write through.
        virtual CADIReturn_t CADICacheWrite(CADIAddr_t addr,
                                            uint32_t linesToWrite,
                                            const uint8_t* data,
                                            const uint8_t* tags,
                                            const bool* is_dirty,
                                            const bool* is_valid,
                                            uint32_t* numLinesWritten,
                                            bool doSideEffects) = 0;
        //@}




        /// @name Disassembly API
        /// These functions are used to access the target's disassembly feature.
        //@{

        /// This call is used to retrieve the disassembler for a target.
        virtual CADIDisassembler * CADIGetDisassembler(void) = 0;

        //@}



        /// @name Virtual Memory API
        //@{

        /// This function translates a virtual address to a physical one.
        /// @param[in]  vaddr
        ///               The virtual address to be converted.
        /// @return       The resulting physical address.
        virtual CADIAddrComplete_t VirtualToPhysical(CADIAddrComplete_t vaddr) = 0;

        /// This function translates a physical address to a virtual one.
        /// @param[in]  paddr
        ///               The physical address to be converted.
        /// @return       The resulting virtual address.
        virtual CADIAddrComplete_t PhysicalToVirtual(CADIAddrComplete_t paddr) = 0;

        //@}


    };

} // namespace eslapi

#endif // #ifndef CADI_h

// end of file CADI.h
