// ===========================================================================
// Description : CADI types declaration.
//
// Author      : ARM
// Release     : 2.0.0
//
// Copyright (c) 2006-2009 ARM. All rights reserved.
//
// ============================================================================
//

#ifndef CADI2Types_h
# define CADI2Types_h

#include "eslapi/CADICommon.h"

# include <cstring> // for std::strncpy, memset, memcpy

namespace eslapi
{
    enum { CADI_REG_ALLGROUPS = ~0U };
    enum { CADI_MEMBLOCK_ROOT = -1 };

    enum { CADI_NAME_SIZE = 1024 };
    enum { CADI_DESCRIPTION_SIZE = 1024 };
    enum { CADI_ERROR_MESSAGE_SIZE = 16384 };

    enum { CADI_DESCRIPTION = CADI_DESCRIPTION_SIZE }; // for compatibility

    /** Invalid register ID
     *  (e.g. for register ID fields in CADITargetFeatures_t) */
    enum { CADI_INVALID_REGISTER_ID = ~0U };

    inline void AssignString(char *dst, const char *src, size_t len)
    {
        if (src == 0)
        {
            dst[0] = 0;
            return;
        }
        std::strncpy(dst, src, len - 1);
        dst[len - 1] = 0;       // ensure that string is zero terminated
    }

    // ------------------------------------------------------------------------
    //    CADI Simulation Access
    // ------------------------------------------------------------------------
    //
    /// @brief Simulation Info
    ///
    /// This data informs about a simulation
    struct CADISimulationInfo_t
    {
    public: // methods
        CADISimulationInfo_t(uint32_t id_par = 0,
                             const char *name_par = "",
                             const char *description_par = "") :
            id(id_par)
        {
            AssignString(name, name_par, sizeof(name));
            AssignString(description, description_par, sizeof(description));
        }

    public: // data
        uint32_t   id;                         /// Used for identification
        char name[CADI_NAME_SIZE];             /// name of simulation
        char description[CADI_DESCRIPTION_SIZE];    /// description of the simulation
    };


    // ------------------------------------------------------------------------
    //    CADI Target Access
    // ------------------------------------------------------------------------

    enum CADIValueDataType_t
    {
        CADI_PARAM_INVALID,
        CADI_PARAM_STRING,
        CADI_PARAM_BOOL,
        CADI_PARAM_INT,
        CADI_PARAM_ENUM_MAX = 0xFFFFFFFF
    };

    struct CADIParameterInfo_t
    {
    public: // methods
        CADIParameterInfo_t(uint32_t id_par = 0,
                            const char *name_par = "",
                            CADIValueDataType_t dataType_par = CADI_PARAM_INVALID,
                            const char *description_par = "",
                            uint32_t isRunTime_par = 0,
                            int64_t minValue_par = 0,
                            int64_t maxValue_par = 0,
                            int64_t defaultValue_par = 0,
                            const char *defaultString_par = "") :
            id(id_par),
            dataType(dataType_par),
            isRunTime(isRunTime_par),
            minValue(minValue_par),
            maxValue(maxValue_par),
            defaultValue(defaultValue_par)
        {
            AssignString(name, name_par, sizeof(name));
            AssignString(description, description_par, sizeof(description));
            AssignString(defaultString, defaultString_par, sizeof(defaultString));
        }

    public: // data
        uint32_t   id;                         // Used for identification
        char  name[CADI_NAME_SIZE];           // Name of the parameter
        CADIValueDataType_t dataType;         // Data type for interpretation purposes of the debugger
        char  description[CADI_DESCRIPTION_SIZE];  // Parameter description
        uint32_t   isRunTime;                  /* If equals to 0, then the parameter is instantiation-time only.
                                                If equals to 1, then the parameter can be changed at run-time */
        int64_t   minValue;                   // minimum admissible value
        int64_t   maxValue;                   // maximum admissible value
        int64_t   defaultValue;               // default value if parameter is type bool/int
        char  defaultString[CADI_DESCRIPTION_SIZE];// default string if parameter is type CADI_PARAM_STRING
    };

    struct CADIParameterValue_t
    {
    public: // methods
        CADIParameterValue_t(uint32_t parameterID_par = static_cast<uint32_t>(-1),
                             CADIValueDataType_t dataType_par = CADI_PARAM_INVALID,
                             int64_t intValue_par = 0,
                             const char *stringValue_par="") :
            parameterID(parameterID_par),
            dataType(dataType_par),
            intValue(intValue_par)
        {
            AssignString(stringValue, stringValue_par, sizeof(stringValue));
        }


    public: // data
        uint32_t   parameterID;                // Refers to the id of respective CADIParameterInfo_t.
        CADIValueDataType_t dataType;         // Data type.
        int64_t   intValue;                   // This also contains the BOOL (0 = false, 1 = true).
        char  stringValue[CADI_DESCRIPTION_SIZE];  // String value if type is value is type string.
    };

    struct CADITargetInfo_t
    {
    public: // methods
        CADITargetInfo_t(uint32_t id_par = 0,
                         const char *targetName_par = "",
                         const char *instanceName_par = "",
                         const char *version_par = "",
                         const char *description_par = "",
                         const char *componentType_par = "",
                         uint32_t numberOfParameters_par = 0,
                         bool executesSoftware_par = false,
                         uint32_t isHardwareModel_par = 0,
                         const char *systemName_par = "",
                         uint32_t systemID_par = 0,
                         const char *systemDescription_par = "",
                         bool canRunInBackground_par = false) :
            id(id_par),
            numberOfParameters(numberOfParameters_par),
            executesSoftware(executesSoftware_par),
            isHardwareModel(isHardwareModel_par),
            systemID(systemID_par),
            canRunInBackground(canRunInBackground_par)
        {
            AssignString(targetName, targetName_par, sizeof(targetName));
            AssignString(instanceName, instanceName_par, sizeof(instanceName));
            AssignString(version, version_par, sizeof(version));
            AssignString(description, description_par, sizeof(description));
            AssignString(componentType, componentType_par, sizeof(componentType));
            AssignString(systemName, systemName_par, sizeof(systemName));
            AssignString(systemDescription, systemDescription_par, sizeof(systemDescription));
        }

    public: // data
        uint32_t   id;                         // Used for identification.
        char  targetName[CADI_NAME_SIZE];     // Name of the target, i.e. the "type", not the instance name.
        char  instanceName[CADI_NAME_SIZE];   // Name of the CADI target instance.
        char  version[CADI_DESCRIPTION_SIZE];      // Version string.
        char  description[CADI_DESCRIPTION_SIZE];  // Target description.
        char  componentType[CADI_NAME_SIZE];  // Classification of the target into a user-defined group.
        uint32_t   numberOfParameters;         // Number of parameters supported.
        bool  executesSoftware;               /* If false, then the target does not execute programs.
                                               If true, then the target executes software.*/
        uint32_t   isHardwareModel;            /* If equal to 0, then the target is a software model.
                                                If equal to 1, then the target is a hardware model.*/
        char  systemName[CADI_NAME_SIZE];     /* Name of the system the target belongs to.
                                               Is empty for single-core standalone models.*/
        uint32_t   systemID;                   // system id
        char  systemDescription[CADI_DESCRIPTION_SIZE]; // descirption of the system
        bool canRunInBackground;               // target can run with no debugger connected
    };

    enum CADIFactoryErrorCode_t
    {
        CADIFACT_ERROR_OK,                                  // no error at all, message is empty
        // license checking
        CADIFACT_ERROR_LICENSE_FOUND_BUT_EXPIRED,
        CADIFACT_ERROR_LICENSE_NOT_FOUND,
        CADIFACT_ERROR_LICENSE_COUNT_EXCEEDED,
        CADIFACT_ERROR_CANNOT_CONTACT_LICENSE_SERVER,
        CADIFACT_ERROR_WARNING_LICENSE_WILL_EXPIRE_SOON,        // always warning = true
        CADIFACT_ERROR_GENERAL_LICENSE_ERROR,               // for all other license errors
        // info: the parameter which caused this error is indicated in erroneousParameterId
        CADIFACT_ERROR_PARAMETER_TYPE_MISMATCH,         // dataType != dataType
        CADIFACT_ERROR_PARAMETER_VALUE_OUT_OF_RANGE,
        CADIFACT_ERROR_PARAMETER_VALUE_INVALID,         // not out of range but still invalid
        CADIFACT_ERROR_UNKNOWN_PARAMETER_ID,
        CADIFACT_ERROR_GENERAL_PARAMETER_ERROR,         // for all other errors concerning a specific parameter
        // other
        CADIFACT_ERROR_GENERAL_ERROR,                   // for everything else which prevented the CADI interface
        // from beening created
        CADIFACT_ERROR_GENERAL_WARNING,                 // always warning = true, for everything else which still
        // allowed the CADI interface to be created
        CADIFACT_ERROR_MAX = 0xFFFFFFFF                 // FORCE this to be at least 32 bit, never used
    };

    // <p>The severity code is redundant to the error code above
    // it allows easy detection of errors and warnings
    enum CADIFactorySeverityCode_t
    {
        CADIFACT_SEVERITY_OK,                           // no error at all, model created
        CADIFACT_SEVERITY_WARNING,                      // only a warning, model still created
        CADIFACT_SEVERITY_ERROR,                        // error, model not created
        CADIFACT_SEVERITY_MAX = 0xFFFFFFFF              // FORCE this to be at least 32 bit, never used
    };

    struct CADIFactoryErrorMessage_t
    {
    public: // methods
        CADIFactoryErrorMessage_t(CADIFactoryErrorCode_t errorCode_par = CADIFACT_ERROR_OK,
                                  uint32_t erroneousParameterId_par = ~0U,
                                  const char *message_par = "",
                                  CADIFactorySeverityCode_t severity_par = CADIFACT_SEVERITY_OK) :
            errorCode(errorCode_par),
            erroneousParameterId(erroneousParameterId_par),
            severity(severity_par)
        {
            AssignString(message, message_par, sizeof(message));
        }

    public: // data
        CADIFactoryErrorCode_t    errorCode;    // error code
        uint32_t   erroneousParameterId;         // id of the parameter provoking the error
        char  message[CADI_ERROR_MESSAGE_SIZE]; // error message
        CADIFactorySeverityCode_t severity;     // severity code
    };



    /// This is the result returned by most calls and it is a general indication of
    /// the status of the call.
    /// <p>When an error is detected, the debugger can call the CADIXfaceGetError API
    /// to retrieve an error message in text form.
    enum CADIReturn_t
    {

        CADI_STATUS_OK,                     ///< The call was successful.
        CADI_STATUS_GeneralError,           /**< This indicates an error that isn't sufficiently explained
                                                 by one of the other error status values.*/
        CADI_STATUS_UnknownCommand,         ///< The command is not recognized.
        CADI_STATUS_IllegalArgument,        ///< An argument value is illegal.
        CADI_STATUS_CmdNotSupported,        ///< The command is recognized but not supported.
        CADI_STATUS_ArgNotSupported,        /**< An argument to the command is recognized but
                                                 not supported. For example, the target does not support
                                                 a particular type of complex breakpoint.*/
        CADI_STATUS_InsufficientResources,  /**< Not enough memory or other resources exist to fulfill
                                                 the command.*/
        CADI_STATUS_TargetNotResponding,    /**< A timeout has occurred across the CADI interface -
                                                 the target did not respond to the command. */
        CADI_STATUS_TargetBusy,             /**< The target received a request, but is unable to
                                                 process the command. The caller can try this
                                                 call again after some time.*/
        CADI_STATUS_BufferSize,             ///< Buffer too small (for char* types)
        CADI_STATUS_SecurityViolation,      ///< Request has not been fulfilled due to a security violation
        CADI_STATUS_PermissionDenied,       ///< Request has not been fulfilled since the permission was denied
        CADI_STATUS_ENUM_MAX = 0xFFFFFFFF   ///< Max enum value.
    };

    /// This type is used by the get features API call.
    struct CADITargetFeatures_t
    {
    public: // methods
        CADITargetFeatures_t(const char *targetName_par = "",
                             const char *targetVersion_par = "",
                             uint32_t nrBreakpointsAvailable_par = 0,
                             uint8_t fOverlaySupportAvailable_par = 0,
                             uint8_t fProfilingAvailable_par = 0,
                             uint32_t nrResetLevels_par = 0,
                             uint32_t nrExecModes_par = 0,
                             uint32_t nrExceptions_par = 0,
                             uint32_t nrMemSpaces_par = 0,
                             uint32_t nrRegisterGroups_par = 0,
                             uint32_t nrPipeStages_par = 0,
                             uint32_t nPCRegNum_par = CADI_INVALID_REGISTER_ID,
                             uint16_t handledBreakpoints_par = 0,
                             uint32_t nrOfHWThreads_par = 0,
                             uint32_t nExtendedTargetFeaturesRegNum_par = CADI_INVALID_REGISTER_ID,
                             char const* canonicalRegisterDescription_par = "",
                             char const* canonicalMemoryDescription_par = "",
                             uint8_t canCompleteMultipleInstructionsPerCycle_par = 0
            ) :
            nrBreakpointsAvailable(nrBreakpointsAvailable_par),
            fOverlaySupportAvailable(fOverlaySupportAvailable_par),
            fProfilingAvailable(fProfilingAvailable_par),
            nrResetLevels(nrResetLevels_par),
            nrExecModes(nrExecModes_par),
            nrExceptions(nrExceptions_par),
            nrMemSpaces(nrMemSpaces_par),
            nrRegisterGroups(nrRegisterGroups_par),
            nrPipeStages(nrPipeStages_par),
            nPCRegNum(nPCRegNum_par),
            handledBreakpoints(handledBreakpoints_par),
            nrOfHWThreads(nrOfHWThreads_par),
            nExtendedTargetFeaturesRegNumValid(nExtendedTargetFeaturesRegNum_par != CADI_INVALID_REGISTER_ID),
            nExtendedTargetFeaturesRegNum(nExtendedTargetFeaturesRegNum_par),
            canCompleteMultipleInstructionsPerCycle (canCompleteMultipleInstructionsPerCycle_par)
        {
            AssignString(targetName, targetName_par, sizeof(targetName));
            AssignString(targetVersion, targetVersion_par, sizeof(targetVersion));
            AssignString(canonicalRegisterDescription,
                         canonicalRegisterDescription_par,
                         sizeof(canonicalRegisterDescription));
            AssignString(canonicalMemoryDescription,
                         canonicalMemoryDescription_par,
                         sizeof(canonicalMemoryDescription));
        }

    public: // data
        char targetName[CADI_NAME_SIZE];      /**< Target name.
                                               This should agree with the name element of the target's CADITarget_t.*/

        char targetVersion[CADI_NAME_SIZE];   /**< Version of the target.
                                               This is just the version of the target - it is displayed by the debugger.*/

        uint32_t   nrBreakpointsAvailable;     ///< Number of code breakpoints available

        uint8_t    fOverlaySupportAvailable;   ///< Indicates whether the target has an overlay mode or not

        uint8_t    fProfilingAvailable;        ///< Helps decide if the debugger should call profiling functions.

        uint32_t   nrResetLevels;              /**< This is the number of reset levels the target provides.
                                                This must be greater than zero.
                                                This can include warm and cold resets as well as communication link resets.
                                                <p>If nrResetLevels is greater than 1, then the debugger should
                                                call the CADIExecGetResetLevels API to get the complete list.*/

        uint32_t   nrExecModes;                /**< If nrExecModes is greater than 2, then the debugger should
                                                call the CADIExecGetModes API to get the complete list.*/

        uint32_t   nrExceptions;               ///< The number of exceptions the target has.

        uint32_t   nrMemSpaces;                ///< The number of memory spaces (e.g., code and data) the target has.

        uint32_t   nrRegisterGroups;           ///< The number of register groups the target is reporting to the debugger.

        uint32_t   nrPipeStages;               /**< The number of pipe stages being exposed to the debugger.
                                                This should only have a value other than one for cycle accurate simulators.*/

        uint32_t   nPCRegNum;                  /**< This value denotes the register-number that is to be used
                                                as the PC of the target. The PC is supposed to point to the *next*
                                                instruction to be executed. If a target has multiple PCs of which only one is
                                                active at a time this should point to a register which always contains the
                                                current PC. If a target has multiple independent PCs which are valid at the
                                                same time these units should get independent CADI interfaces with one PC each.
                                                If a target has no PC this should be set to CADI_INVALID_REGISTER_ID. */

        uint16_t   handledBreakpoints;         /**< This is 0 if no breakpoints are handled by the target.
                                                <p>Combinations of:
                                                -# CADI_TARGET_FEATURE_BPT_PROGRAM,
                                                -# CADI_TARGET_FEATURE_BPT_MEMORY,
                                                -# CADI_TARGET_FEATURE_BPT_REGISTER
                                                -# CADI_TARGET_FEATURE_BPT_INST_STEP,
                                                -# CADI_TARGET_FEATURE_BPT_PROGRAM_RANGE,
                                                -# CADI_TARGET_FEATURE_BPT_EXCEPTION,
                                                otherwise.*/

        uint32_t   nrOfHWThreads;              ///< Number of HW threads in the target
        bool       nExtendedTargetFeaturesRegNumValid; ///< true if and only if the field nExtendedTargetFeaturesRegNum is valid
        uint32_t   nExtendedTargetFeaturesRegNum; /**< Register ID of a string register which contains a static string
                                                   * consisting of colon separated tokens or aribtrary non-colon-ASCII chars.
                                                   * Example "FOO:BAR:ANSWER=42:STARTUP=0xe000"
                                                   * The set and semantics of supported tokens are out of scope of the CADI
                                                   * interface itself. There is no length restriction on this feature string.
                                                   * Having such a string register is optional. Models which do not provide it
                                                   * must set nExtendedTargetFeaturesRegNumValid to false. In this case the value
                                                   * of this fiedl must be ignored. Having no such register and having a
                                                   * string register which provides an empty string is equivalent.
                                                   *
                                                   * The following tokens are defined for CADI 2.0:
                                                   * (n denotes a decimal unsigned 32 bit integer)
                                                   * PC_MEMSPACE_REGNUM=n:
                                                   *    Register ID of the a register which contains the memory space ID of the current PC described in nPCRegNum.
                                                   * SP_REGNUM=n:
                                                   *    Register ID of the stack pointer (or a register with similar semantics).
                                                   * LR_REGNUM=n:
                                                   *    Register ID of the link register (or a register with similar semantics).
                                                   * STACK_MEMSPACE_ID=n:
                                                   *    CADI memory space id used for stack unwinding
                                                   * LOCALVAR_MEMSPACE_ID=n:
                                                   *    CADI memory space id used for local variables
                                                   * GLOBALVAR_MEMSPACE_ID=n:
                                                   *    CADI memory space id used for global vars
                                                   *
                                                   * Targets which do not have one of the features described above simply will not expose such a token.
                                                   */

        /// canonicalRegisterDescription is a string that describes the contents
        /// of the canonicalRegisterNumber field of CADIRegInfo_t.  Canonical
        /// register numbers are intended to be target-specific numbers to identify
        /// registers in the device by some scheme other than the DWARF index.  The
        /// format of this field is 'domain_name/string'.  The domain_name is that
        /// of the organisation specifying the scheme.  The string part is upto the
        /// organisation to specify.  An example would be 'arm.com/my/reg/numbers'.
        char      canonicalRegisterDescription[CADI_DESCRIPTION_SIZE];

        /// canonicalMemoryDescription is a string that describes the contents
        /// of the canonicalMemoryNumber field of CADIMemSpaceInfo_t.  Canonical
        /// memory numbers are intended to be target-specific numbers to
        /// identify memory spaces in the device by some scheme other than the
        /// DWARF index.  The format of this field is 'domain_name/string'.  The
        /// domain_name is that of the organisation specifying the scheme.  The
        /// string part is upto the organisation to specify.  An example would
        /// be 'arm.com/my/mem/numbers'.
        char      canonicalMemoryDescription[CADI_DESCRIPTION_SIZE];
        // True if target can complete multiple instructions in a single simulation cycle
        uint8_t    canCompleteMultipleInstructionsPerCycle;
    };

    /// Identifies different callback functions.
    enum CADICallbackType_t
    {
        CADI_CB_AppliOpen       =  0, /**< This call opens the specified filename and returns a streamID
                                       that the AppliInput and Applioutput functions can use.*/
        CADI_CB_AppliInput      =  1, ///< This is used for input. Data travels from the host to the target.
        CADI_CB_AppliOutput     =  2, ///< This is used for output. Data travels from the target to the host.
        CADI_CB_AppliClose      =  3, ///< This closes the stream specified by streamID.
        CADI_CB_String          =  4, /**< The target system calls this to have the debugger display a string.
                                           Among other things, it can be used for things like hazard and stall
                                           indication.*/
        CADI_CB_ModeChange      =  5, /**< Call this when the target changes execution modes as defined by
                                           CADIExecGetModes. The bptNumber parameter is ignored if the mode is
                                           not CADI_EXECMODE_Bpt.*/
        CADI_CB_Reset           =  6, /**< This callback indicates the end of a CADI reset. It is identical to
                                           the modeChange(CADI_EXECMODE_ResetDone) callback. Though targets have
                                           to support this callback for backwards compatibility reasons, clients
                                           should favour the modeChange() callback over the reset() callback as
                                           the latter one will be deprecated in future CADI versions.*/
        CADI_CB_CycleTick       =  7, /**< This callback, when installed, is called after every cycle that is
                                           executed by the target.*/
        CADI_CB_KillInterface   =  8, /**< This call must ALWAYS be enabled. This is called when the target is
                                           dying. No further communication with the target is allowed after
                                           this callback is made. */
        CADI_CB_Bypass          =  9, /**< Callback to bypass the interface, to allow any string-based
                                           communication with the debugger.*/
        CADI_CB_LookupSymbol    = 10, ///< Lookup a symbol from the debugger
        CADI_CB_DisasmNotifyModeChange = 11, ///< Target mode was changed.
        CADI_CB_DisasmNotifyFileChange = 12, ///< Target file was changed.
        CADI_CB_Refresh         = 13, ///< Used to notify debugger that it needs to refresh its state (e.g., register values changed)
        CADI_CB_ProfileResourceAccess = 14, ///< Profile resource callback
        CADI_CB_ProfileRegisterHazard = 15, ///< Register hazard callback
        CADI_CB_Count           = 16,
        CADI_CB_ENUM_MAX = 0xFFFFFFFF
    };

    /// Identifies different simulation callback functions.
    enum CADISimulationCallbackType_t
    {
        CADI_SIM_CB_Message     = 0, /// This callback is called when the simulation issues a system-wide messages
        CADI_SIM_CB_Shutdown    = 1, /// This signals that the simulation wants to shut down
        CADI_SIM_CB_Kill        = 2, /// The simulation signals that it is killed and is not responsive any more
        CADI_SIM_CB_Count       = 3,
        CADI_SIM_ENUM_MAX       = 0xFFFFFFFF
    };

    /// These values can be found in the register described by CADIPipeStage_t::contentInfoRegisterId
    enum CADIPipeStageContentInfo_t
    {
        CADI_PIPESTAGE_Invalid,         ///< This pipe stage is empty or invalid, nothing is displayed.
        CADI_PIPESTAGE_OpcodeOnly,      ///< An instruction is in this stage, only the opcode is valid.
        CADI_PIPESTAGE_DisassemblyOnly, ///< An instruction is in this stage, only the disassembly is valid.
        CADI_PIPESTAGE_Instruction,     /**< An instruction is in this stage, both the opcode and
                                             the disassembly are valid.*/
        CADI_PIPESTAGE_ENUM_COUNT,
        CADI_PIPESTAGE_MAX = 0xFFFFFFFF
    };


    /// Register associated to a certain pipe stage
    struct CADIPipeStageField_t
    {
    public: // methods
        CADIPipeStageField_t(uint32_t pipeStageId_par = 0,
                             uint32_t registerId_par = CADI_INVALID_REGISTER_ID) :
            pipeStageId(pipeStageId_par),
            registerId(registerId_par)
        {
        }

    public: // data
        uint32_t pipeStageId;
        uint32_t registerId;
    };

    /// This describes a single pipe stage.
    struct CADIPipeStage_t
    {
    public: // methods
        CADIPipeStage_t(uint32_t id_par = 0,
                        const char *name_par = "",
                        uint32_t pc_par = CADI_INVALID_REGISTER_ID,
                        uint32_t contentInfoRegisterId_par = CADI_INVALID_REGISTER_ID) :
            id(id_par),
            pc(pc_par),
            contentInfoRegisterId(contentInfoRegisterId_par)
        {
            AssignString(name, name_par, sizeof(name));
        }

    public: // data
        uint32_t   id;                  ///<
        char  name[CADI_NAME_SIZE];
        uint32_t   pc;                  ///< Register id that holds the addr of the instruction
        uint32_t contentInfoRegisterId; ///< Register id that holds the current content info for this pipe stage.
        ///< The values of this register correspond to the CADIPipeStageContentInfo_t enum.
    };

    /// This is a memory location inside a memory space and overlay. It is the most basic type of
    /// memory address.
    typedef uint64_t CADIAddrSimple_t;

    /// This is a numeric designation for the memory space (code and data space, for example).
    /// Remember that each memory space has its own address space.
    typedef uint32_t CADIMemSpace_t;
    const CADIMemSpace_t CADI_MEM_SPACE_NOTSUPPORTED = 0xFFFFFFFF;

    /// This data type represents the complete identification of a specific memory image that can
    /// share a region of memory with other memory images.
    /// <p> A memory overlay during in-sequence target software data collection (e.g., program flow
    /// tracing or profiling) can ruin the integrity of the data. An object of this type can be inserted
    /// into a data collection stream to fix the problem.
    typedef uint32_t CADIOverlayId_t;

    const CADIOverlayId_t CADI_NO_OVERLAY = 0;

    /// This type describes a basic address with the memory space associated with the address.
    struct CADIAddr_t
    {
    public: // methods
        CADIAddr_t(CADIMemSpace_t space_par = 0,
                   CADIAddrSimple_t addr_par = 0) :
            space(space_par),
            addr(addr_par)
        {
        }
        bool operator == (const CADIAddr_t &other) const { return (space == other.space) && (addr == other.addr); }

    public: // data
        CADIMemSpace_t   space;   ///< Numeric designation of the memory space (uint32_t)
        CADIAddrSimple_t addr;    ///< The actual memory addess (uint32_t)
    };

    /// This type adds overlay information for an address specification.

    /// Variables of this type fully specify a single memory location in the target device.
    struct CADIAddrComplete_t
    {
    public: // methods
        CADIAddrComplete_t(CADIOverlayId_t overlay_par = 0,
                           CADIAddr_t location_par = CADIAddr_t() ) :
            overlay(overlay_par),
            location(location_par)
        {
        }

        bool operator == (const CADIAddrComplete_t &other) const { return (overlay == other.overlay) && (location == other.location); }

    public: // data
        CADIOverlayId_t overlay;  // Identification of a memory image that can share a region
        // of memory with other memory images (uint32_t)
        CADIAddr_t     location;  // The memory address (space ID + numeric address)
    };



    // ------------------------------------------------------------------------
    //    Execution Control Interface
    // ------------------------------------------------------------------------
    enum
    {
        CADI_BPT_TRIGGER_ON_READ = 1,
        CADI_BPT_TRIGGER_ON_WRITE = 2,
        CADI_BPT_TRIGGER_ON_MODIFY = 4
    };

    enum { CADI_BPT_CLEAR_ALL_TEMPORARY_BPTS = ~0U };    // Use this flag as argument to CADIBptClear(bptid)
    // to delete all temporary breakpoints

    /// This identifies a breakpoint that has been set.
    typedef uint32_t CADIBptNumber_t;

    /// Possible breakpoint types.
    enum CADIBptType_t
    {
        CADI_BPT_PROGRAM,               ///< PC == breakpoint address.
        CADI_BPT_MEMORY,                ///< Breakpoint on memory location: break if memory is read, written or modified.
        CADI_BPT_REGISTER,              ///< Breakpoint on register: break if register is  read, written or modified.
        CADI_BPT_INST_STEP,             ///< Instruction step breakpoint, inverted program execution breakpoint. Break if PC != breakpoint address
        CADI_BPT_PROGRAM_RANGE,         /**< Break if PC enters a range of program addresses,
                                             sizeOfAddressRange is the length of the address range */
        CADI_BPT_EXCEPTION,             ///< Break just after an exception occurs.
        CADI_BPT_USER_DEFINED = 0x8000  ///< Reserved
    };

    /// Flags for the handledBreakpoints field in CADITargetFeatures_t
    enum {
        CADI_TARGET_FEATURE_BPT_PROGRAM       = (1 << CADI_BPT_PROGRAM),
        CADI_TARGET_FEATURE_BPT_MEMORY        = (1 << CADI_BPT_MEMORY),
        CADI_TARGET_FEATURE_BPT_REGISTER      = (1 << CADI_BPT_REGISTER),
        CADI_TARGET_FEATURE_BPT_INST_STEP     = (1 << CADI_BPT_INST_STEP),
        CADI_TARGET_FEATURE_BPT_PROGRAM_RANGE = (1 << CADI_BPT_PROGRAM_RANGE),
        CADI_TARGET_FEATURE_BPT_EXCEPTION     = (1 << CADI_BPT_EXCEPTION)
    };

    /// Possible conditional breakpoint types
    enum CADIBptConditionOperator_t
    {
        CADI_BPT_COND_UNCONDITIONAL,                     ///< Normal breakpoint, always break, no additional condition.
        CADI_BPT_COND_EQUALS,                            ///< Only break if value == comparisionValue (unsigned comparison)
        CADI_BPT_COND_NOT_EQUALS,                        ///< Only break if value != comparisionValue (unsigned comparison)

        // signed comparison
        CADI_BPT_COND_GREATER_THAN_SIGNED,               ///< Only break if value >  comparisionValue (signed comparison)
        CADI_BPT_COND_GREATER_THAN_OR_EQUALS_SIGNED,     ///< Only break if value >= comparisionValue (signed comparison)
        CADI_BPT_COND_LESS_THAN_SIGNED,                  ///< Only break if value <  comparisionValue (signed comparison)
        CADI_BPT_COND_LESS_THAN_OR_EQUALS_SIGNED,        ///< Only break if value <= comparisionValue (signed comparison)

        // unsigned comparison
        CADI_BPT_COND_GREATER_THAN_UNSIGNED,             ///< Only break if value >  comparisionValue (unsigned comparison)
        CADI_BPT_COND_GREATER_THAN_OR_EQUALS_UNSIGNED,   ///< Only break if value >= comparisionValue (unsigned comparison)
        CADI_BPT_COND_LESS_THAN_UNSIGNED,                ///< Only break if value <  comparisionValue (unsigned comparison)
        CADI_BPT_COND_LESS_THAN_OR_EQUALS_UNSIGNED,      ///< Only break if value <= comparisionValue (unsigned comparison)

        CADI_BPT_COND_ENUM_COUNT,                        ///< Not a valid condition operator

        // legacy support, same as signed comparison
        CADI_BPT_COND_GREATER_THAN = CADI_BPT_COND_GREATER_THAN_SIGNED,
        CADI_BPT_COND_GREATER_THAN_OR_EQUALS = CADI_BPT_COND_GREATER_THAN_OR_EQUALS_SIGNED,
        CADI_BPT_COND_LESS_THAN = CADI_BPT_COND_LESS_THAN_SIGNED,
        CADI_BPT_COND_LESS_THAN_OR_EQUALS = CADI_BPT_COND_LESS_THAN_OR_EQUALS_SIGNED,

        CADI_BPT_COND_THREADID = 0x80000000,  ///< Thread aware breakpoint

        // these are no breakpoint cconditions:
        CADI_BPT_COND_ENUM_MAX = 0xFFFFFFFF
    };

    /// Breakpoint condition data.
    ///
    /// Breakpoint \e comparison operations only apply to CADI_BPT_MEMORY and
    /// CADI_BPT_REGISTER breakpoints.  Other breakpoints should always specify
    /// CADI_BPT_COND_UNCONDITIONAL as conditionOperator.  Breakpoint conditions
    /// are always applied as a secondary condition after the primary condition
    /// of the breakpoint which depends on the breakpoint type and the trigger
    /// type.
    ///
    /// CADI_BPT_PROGRAM, CADI_BPT_PROGRAM_RANGE, CADI_BPT_INST_STEP,
    /// CADI_BPT_EXCEPTION \e should obey the ignoreCount if the
    /// useFormalCondition is set.  However, the debugger must ensure that
    /// conditionOperator is CADI_BPT_COND_UNCONDITIONAL, otherwise the
    /// behaviour is undefined.
    struct CADIBptCondition_t
    {
    public: // methods
        CADIBptCondition_t(CADIBptConditionOperator_t conditionOperator_par = CADI_BPT_COND_UNCONDITIONAL,
                           int64_t comparisonValue_par = 0,
                           uint32_t threadID_par = 0,
                           uint32_t ignoreCount_par = 0,
                           uint32_t bitwidth_par = 0) :
            conditionOperator(conditionOperator_par),
            comparisonValue(comparisonValue_par),
            threadID(threadID_par),
            ignoreCount(ignoreCount_par),
            bitwidth(bitwidth_par)
        {
        }

    public: // data
        CADIBptConditionOperator_t    conditionOperator;  /**< Operator for condition (CADI_BPT_REGISTER and CADI_BPT_MEMORY breakpoints
                                                           *   only), otherwise should be set to CADI_BPT_COND_UNCONDITIONAL. */
        int64_t                       comparisonValue;    /**< Value to compare against.
                                                            *
                                                            *   CADI_BPT_REGISTER and CADI_BPT_MEMORY only
                                                            *
                                                            *   How the comparison works:
                                                            *   -------------------------
                                                            *   1. The length L of the resource value is calculated as
                                                            *      L = min(bitwidth, resource_bitwidth)
                                                            *   2. The resource value (register or memory) is read and truncated to L bits
                                                            *   3. The value is zero or sign extended from L to 64 bits
                                                            *   4. The value is compared against comparisonValue
                                                            *
                                                            *   A target may or may not support breakpoints with bitwidth != 64.
                                                            *   Unsupported breakpoints must fail ArgNotSupported at CADIBptSet().
                                                            *
                                                            *   A debugger is always responsible for providing a usefully sign
                                                            *   or zero extended comparisionValue. A target leaves this untouched.
                                                            *   If comparisionValue is out of range or wrongly sign-extened the
                                                            *   results are undefined.
                                                            *
                                                            *   Conditional breakpoints can not be set on resources wider than 64 bits.
                                                            *   Only unconditional, equal and unequal conditions can be used on string registers.
                                                            *
                                                            *   For MODIFY and WRITE breakpoints, targets always use the new value
                                                            *   as the value of the resource to compare against after it has been
                                                            *   modified or written. For reads it is simply the value of the resource
                                                            *   at the time the read happens.
                                                            *
                                                            *   The formalCondition described here is ANDed together with the
                                                            *   trigger type. All brekpoint conditions (the primary condition (breakpoint type),
                                                            *   the trigger type and the formal condition) need to be satified at once to make the
                                                            *   breakpoint hit.
                                                            *
                                                            *   For the interaction with debug writes, also see the comments for:
                                                            *      CADI::CADIMemWrite(CADIAddrComplete_t,uint32_t,uint32_t,uint8_t const*,uint32_t *,uint8_t)
                                                            *      CADI::CADIRegWrite(uint32_t, CADIReg_t *, uint32_t *, uint8_t)
                                                            */
        uint32_t                      threadID;           ///< Reserved.
        uint32_t                      ignoreCount;       /**< If greater that zero this counter is counted down by the target each time the
                                                           *   breakpoint is hit and the target does not report this hit to the debugger and
                                                           *   the simulation is not stopped (the breakpoint is effectively ignored).
                                                           *   If this is 0 and the breakpoint is hit the target reports the breakpoint to
                                                           *   the debugger and the simulation is stopped. This is 0 for normal breakpoints. */
        uint32_t                      bitwidth;          /**< Bitwidth of the comparision value, see explaination for comparisionValue. */
    };

    /// Breakpoint request data

    /// The breakpoint request provides the PC address at which a breakpoint should occur and a string
    /// that describes the condition of the breakpoint. The format of the string is TBD but, ultimately,
    /// the target decides whether it can implement the breakpoint conditions.
    struct CADIBptRequest_t
    {
    public: // methods
        CADIBptRequest_t(const CADIAddrComplete_t address_par = CADIAddrComplete_t(),
                         uint64_t sizeOfAddressRange_par = 0,
                         int32_t enabled_par = 0,
                         const char *conditions_par = "",
                         bool useFormalCondition_par = 1,
                         CADIBptCondition_t formalCondition_par = CADIBptCondition_t(),
                         CADIBptType_t type_par = CADI_BPT_PROGRAM,
                         uint32_t regNumber_par = 0,
                         int32_t temporary_par = false,
                         uint8_t triggerType_par = 0,
                         uint32_t continueExecution_par = false) :
            address(address_par),
            sizeOfAddressRange(sizeOfAddressRange_par),
            enabled(enabled_par),
            useFormalCondition(useFormalCondition_par),
            formalCondition(formalCondition_par),
            type(type_par),
            regNumber(regNumber_par),
            temporary(temporary_par),
            triggerType(triggerType_par),
            continueExecution(continueExecution_par)
        {
            AssignString(conditions, conditions_par, sizeof(conditions));
        }

    public: // data
        CADIAddrComplete_t  address;           ///< The PC or memory address at which the breakpoint should occur.
        uint64_t            sizeOfAddressRange; /**< Used only if type = CADI_BPT_PROGRAM_RANGE or CADI_BPT_MEMORY. 
                                                 *   Size of the address range in addresses (in bytes for a byte addressable memory).
                                                 *   A size of 0 must be treated as a size of 1 by targets for type = CADI_BPT_MEMORY.
                                                 */
        int32_t             enabled;            ///< Status of the breakpoint (enabled/disabled). Also initial state of the breakpoint for CADIBptSet().
        char                conditions[CADI_DESCRIPTION_SIZE]; /**< The breakpoint condition. Ultimately the target
                                                      decides if it can implement breakpoint conditions.*/
        bool                useFormalCondition;     /**< 0 = use free-form "conditions",
                                                         1 = use "formalCondition"*/
        CADIBptCondition_t  formalCondition;    ///< Formal conditions
        CADIBptType_t       type;               ///< Type
        uint32_t            regNumber;          ///< For type = CADI_BPT_REGISTER only
        int32_t             temporary;          ///< Temporary breakpoint

        uint8_t             triggerType;        /**< Allow breakpoints that trigger only on read/write/modify
                                                 *   This only has meaning for CADI_BPT_REGISTER and
                                                 *   CADI_BPT_MEMORY breakpoints.  The debugger should set this to zero
                                                 *   for other breakpoint types.  Setting this to zero for
                                                 *   CADI_BPT_REGISTER and CADI_BPT_MEMORY results in undefined
                                                 *   behaviour and must not be done.
                                                 */
        uint32_t            continueExecution;  /**< 1 = Continue execution after breakpoint has been hit
                                                 *   \note This field should be obeyed by \e types of breakpoints,
                                                 *         including CADI_BPT_INST_STEP, etc.
                                                 */
    };

    /// Breakpoint description data.
    struct CADIBptDescription_t
    {
    public: // methods
        CADIBptDescription_t(CADIBptNumber_t bptNumber_par = 0,
                             CADIBptRequest_t bptInfo_par = CADIBptRequest_t()) :
            bptNumber(bptNumber_par),
            bptInfo(bptInfo_par)
        {
        }

    public: // data
        CADIBptNumber_t     bptNumber;    ///< The breakpoint number (uint32_t).
        CADIBptRequest_t  bptInfo;        ///< The breakpoint information (address, condition, etc.).
    };

    /// Configure breakpoint.
    enum CADIBptConfigure_t
    {
        CADI_BPT_Disable,
        CADI_BPT_Enable
    };

    /** Execution control
     *
     * These codes are passed in the 'newMode' parameter of the 'modeChange()' callback.
     *
     * Some of the modeChange() callbacks imply certain refresh() callbacks. This means that
     * certain modeChange() callbacks should trigger a refresh of certain resources implicitly
     * without having an explicit call of refresh().
     */
    enum CADI_EXECMODE_t {
        /// modeChange(CADI_EXECMODE_Stop) means: The simulation was in state 'running' and has now stopped.
        /// This is always the last callback in a sequence of callbacks when the simulation stopped. If the
        /// stop was because one or more breakpoints have been hit then this callback is preceeded by one or
        /// more modeChange(CADI_EXECMODE_Bpt, num) callbacks where 'num' specified the breakpoint(s) being
        /// hit. CADIExecStop() eventually results in a modeChange(CADI_EXECMODE_Stop) callback.
        /// This callback implies a refresh(REGISTERS|MEMORY) callback which means that a debugger should
        /// assume registers and memory to have changed.
        CADI_EXECMODE_Stop = 0,
        /// modeChange(CADI_EXECMODE_Run) means: The simulation was in state 'stopped' and is now running.
        /// CADIExecContinue() and CADIExecSingleStep() eventually result in a modeChange(CADI_EXECMODE_Run)
        /// callback.
        CADI_EXECMODE_Run = 1,
        /// modeChange(CADI_EXECMODE_Bpt, num) means: A specific breakpoint was hit. The breakpoint number
        /// 'num' of the breakpoint being hit is passed as the second parameter in the modeChaneg callback.
        /// This callback may be called several times in a straight sequence if multiple breakpoints have
        /// been hit at the same time. A modeChange(CADI_EXECMODE_Stop) callback is allways following and
        /// terminating this sequence, except when 'continueExecution' was true for all breakpoints being
        /// hit. This callback does *not* mean that the simulation stopped. It may be followed by more
        /// modeChange(CADI_EXECMODE_Bpt, num) callbacks. The final modeChange(CADI_EXECMODE_Stop) is
        /// responsible for signaling that the simulation stopped.
        CADI_EXECMODE_Bpt = 2,
        /// modeChange(CADI_EXECMODE_Error) means: Same as modeChange(CADI_EXECMODE_Stop), but the model
        /// is in a state 'stopped and error' after this callback. This means that all execution control
        /// functions are disabled. CADIExecReset() needs to be called first to enable them again. This
        /// callback is not followed by another modeChange(CADI_EXECMODE_Stop) callback, it implies
        /// modeChange(CADI_EXECMODE_Stop).
        /// This callback implies a refresh(REGISTERS|MEMORY) callback which means that a debugger should
        /// assume registers and memory to have changed.
        CADI_EXECMODE_Error = 3,
        /// Reserved for future use.
        CADI_EXECMODE_HighLevelStep = 4,
        /// Reserved for future use.
        CADI_EXECMODE_RunUnconditionally = 5,
        /// modeChange(CADI_EXECMODE_ResetDone) means: The CADIExecReset() request recently requested by a
        /// debugger is now complete. This is always the last callback in a sequence of callbacks caused
        /// by a CADIExecReset(). A modeChange(CADI_EXECMODE_Stop) might happen before this callback if the
        /// model was running when CADIExecReset() was issued. Since CADIExecReset() is an asynchronous call,
        /// each debugger connected to a target, including the caller of the reset, receives this callback
        /// after the simulation has finished the reset.
        /// This callback implies a refresh(REGISTERS|MEMORY) callback which means that a debugger should
        /// assume registers and memory to have changed.
        /// The handling of the modeChange(CADI_EXECMODE_ResetDone) has to be identical to the one of the
        /// reset() callback. Though targets have to support both callbacks for backwards compatibility
        /// reasons, clients should favour modeChange(CADI_EXECMODE_ResetDone) over the reset() callback
        /// as the latter one will be deprecated in future CADI versions.
        CADI_EXECMODE_ResetDone = 5,
        CADI_EXECMODE_ENUM_MAX = 0xFFFFFFFF
    };

    /// Execution mode data

    /// Mode number CADI_EXECMODE_Stop must be in stop mode.
    /// <br>Mode number CADI_EXECMODE_Run must be run mode.
    /// <br>Mode number CADI_EXECMODE_Bpt must be breakpoint mode.
    /// <p>CADI_EXECMODE_Error should be used if the target encounters errors and is not in a CADI call.
    struct CADIExecMode_t
    {
    public: // methods
        CADIExecMode_t(uint32_t number_par = 0,
                       const char *name_par = "") :
            number(number_par)
        {
            AssignString(name, name_par, sizeof(name));
        }

    public: // data
        uint32_t   number;
        char  name[CADI_NAME_SIZE];
    };

    /// Reset level data
    struct CADIResetLevel_t
    {
    public: // methods
        CADIResetLevel_t(uint32_t number_par = 0,
                         const char *name_par = "") :
            number(number_par)
        {
            AssignString(name, name_par, sizeof(name));
        }

    public: // data
        uint32_t   number;
        char  name[CADI_NAME_SIZE];
    };

    /// Exception data
    struct CADIException_t
    {
    public: // methods
        CADIException_t(uint32_t number_par = 0,
                        const char *name_par = "",
                        CADIAddr_t vector_par = CADIAddr_t()) :
            number(number_par),
            vector(vector_par)
        {
            AssignString(name, name_par, sizeof(name));
        }

    public: // data
        uint32_t   number;
        char  name[CADI_NAME_SIZE];
        CADIAddr_t vector;
    };

    /// Exception action data
    enum CADIExceptionAction_t
    {
        CADI_EXCEPTION_Raise,       ///< For targets that can raise an exception ...
        CADI_EXCEPTION_Lower,       ///< ... and leave it raised
        CADI_EXCEPTION_Pulse,
        CADI_EXCEPTION_ENUM_MAX = 0xFFFFFFFF
    };


    // ------------------------------------------------------------------------
    //    Register Interface
    // ------------------------------------------------------------------------
    //

    /// Register access attribute values
    enum CADIRegAccessAttribute_t
    {
        CADI_REG_READ_WRITE,
        CADI_REG_READ_ONLY,
        CADI_REG_WRITE_ONLY,
        CADI_REG_READ_WRITE_RESTRICTED,
        CADI_REG_READ_ONLY_RESTRICTED,
        CADI_REG_WRITE_ONLY_RESTRICTED,
        CADI_REG_ATTR_MAX = 0xffffffff ///< To force the enum to 32bits, not used
    };

    /// @brief Register data
    ///
    /// This data buffer is used to read and write register values.
    ///
    /// The register data is packed, byte-by-byte, into the bytes array.
    /// Data is always encoded in little endian mode. For example, the lowest address
    /// in the bytes array contains the least significant value of the register.
    struct CADIReg_t
    {
    public: // methods
        CADIReg_t(uint32_t regNumber_par = 0,
                  uint64_t bytes_par = 0,
                  uint16_t offset128_par = 0,
                  bool isUndefined_par = false,
                  CADIRegAccessAttribute_t attribute_par = CADI_REG_READ_WRITE) :
            regNumber(regNumber_par),
            offset128(offset128_par),
            isUndefined(isUndefined_par),
            attribute(attribute_par)
        {
            for(int i=0; i < 8; ++i)
                bytes[i] = uint8_t(bytes_par >> (i * 8));

            for(int i=8; i < 16; ++i)
                bytes[i] = 0;
        }

    public: // data
        uint32_t   regNumber; /**< From debugger to target:
                               * Register ID to be read/written.
                               */
        uint8_t    bytes[16]; /**< From target to debugger for reads, from debugger to target for writes:
                               *   Value to be read/written in little endian (regardless of the endianness
                               *   of the host or the target).
                               */
        uint16_t   offset128; /**< From debugger to target:
                               *   Specify which part of the register value to read/write for
                               *   long registers > 128 bits. Measured in multiples of 128 bits,
                               *    e.g. 1 means bytes[0..15] contain bits 128..255). The actual bitwidth of
                               *   non-string registers is determined by the 'bitsWide' field in CADIRegInfo_t.
                               *
                               *   Similarly for string registers, specify the offset in units of 16 chars into the
                               *   string which is to be read or written, e.g. offset128=1 means read/write str[16..31].
                               *   Reads to offsets beyond the length of the string are explicltly allowed and need to
                               *   result in bytes[0..15] being all zero.
                               *   Writes may make the string longer by writing nonzero data to offsets greater than the
                               *   current length of a string. Writes may make a string shorter by writing data
                               *   containing at least one zero byte to a specific offset. Write sequences always write
                               *   lower offsets before higher offsets and must always be terminated by at least one
                               *   write containing at least one zero byte.
                               *   Unused chars in bytes[0..15] (after the terminating zero byte) shoud be set to zero.
                               *   The 'bitsWide' field in CADIRegInfo_t is ignored for string registers.
                               */
        bool  isUndefined;    /**< From target to debugger: If true the value of the register is completely undefined.
                               *   Bytes[0..15] should be ignored.
                               */
        CADIRegAccessAttribute_t attribute; /**< Undefined for CADI2.0. Targets and Debuggers should set this to 0. */
    };

    /// @brief Register group description
    ///
    /// All fields are target to debugger fields.
    struct CADIRegGroup_t
    {
    public: // methods
        CADIRegGroup_t(uint32_t groupID_par = 0,
                       const char *description_par = "",
                       uint32_t numRegsInGroup_par = 0,
                       const char *name_par = "",
                       bool isPseudoRegister_par = false) :
            groupID(groupID_par),
            numRegsInGroup(numRegsInGroup_par),
            isPseudoRegister(isPseudoRegister_par)
        {
            AssignString(description, description_par, sizeof(description));
            AssignString(name, name_par, sizeof(name));
        }

    public: // data
        uint32_t   groupID;
        char  description[CADI_DESCRIPTION_SIZE];

        /// This is the \e total number of registers in the group, including any
        /// registers that are not direct children of this group.
        uint32_t   numRegsInGroup;
        char  name[CADI_NAME_SIZE];
        bool  isPseudoRegister; /**< True means that this register group is not displayed in the register window in the debugger.
                                 * The registers in this group are probably serving other purposes such as
                                 * pipeline stage fields or other special purpose registers (like the PC memory space). */
    };

    /// Register display values
    /// This defines the best way for a debugger to display a register value by default.
    /// A debugger may display the value in any format upon user request. Only
    /// CADI_REGTYPE_STRING is special since in this case the bitsWide field in CADIRegInfo_t
    /// is ignored and the debugger retrieves as many ASCII chars until it receives a NUL char.
    enum CADIRegDisplay_t
    {
        CADI_REGTYPE_HEX,       ///< Hex display (for addresses, etc) - default.
        CADI_REGTYPE_UINT,      ///< Unsigned integer.
        CADI_REGTYPE_INT,       ///< Signed integer.
        CADI_REGTYPE_BOOL,      ///< Boolean (must be one bit).
        CADI_REGTYPE_FLOAT,     ///< Floating point display (see details).
        CADI_REGTYPE_SYMBOL,    ///< Symbolic values only.
        CADI_REGTYPE_STRING,    ///< Strings.
        CADI_REGTYPE_PC,        ///< Program counter => can be used for disassembly display.
        CADI_REGTYPE_BIN,       ///< Binary format
        CADI_REGTYPE_OCT        ///< Octal format
    };

    /// @brief Array of symbolic values
    ///
    /// Example: register "counter-type", "forward", "backward", "circular"
    struct CADIRegSymbols_t
    {
    public: // methods
        CADIRegSymbols_t(uint32_t numSymbols_par = 0,
                         char **Symbols_par = 0) :
            numSymbols(numSymbols_par),
            Symbols(Symbols_par)
        {
        }

    public: // data
        uint32_t   numSymbols;
        char**    Symbols;
    };

    /// Printf float format specifier
    struct CADIRegFloatFormat_t
    {
    public: // methods
        CADIRegFloatFormat_t(const char *format_par = "")
        {
            AssignString(format, format_par, sizeof(format));
        }

    public: // data
        char  format[CADI_NAME_SIZE];     ///< Printf float format specifier.
    };

    /// Possible register types
    enum CADIRegType_t
    {
        CADI_REGTYPE_Simple,    ///< Register has no sub-registers
        CADI_REGTYPE_Compound   ///< Register has sub-registers (see CADIRegGetCompound())
    };

    /// Register details data
    struct CADIRegDetails_t
    {
    public: // methods
        CADIRegDetails_t(CADIRegType_t type_par = CADI_REGTYPE_Simple,
                         uint32_t count_par = 0) :
            type(type_par)
        {
            u.compound.count = count_par;
        }

    public: // data
        CADIRegType_t type;
        union
        {
            struct
            {
                uint32_t count; /// < Number of sub-registers for CADI_REGTYPE_Compound
            } compound; ///< Only valid for CADI_REGTYPE_Compound.
        } u;          /**< remains a union to leave room for
                       any other register types we might have
                       in the future. */

    };

    /// Register info data
    struct CADIRegInfo_t
    {
    public: // methods
        CADIRegInfo_t(const char *name_par = "",
                      const char *description_par = "",
                      uint32_t regNumber_par = 0,
                      uint32_t bitsWide_par = 0,
                      int32_t hasSideEffects_par = 0,
                      CADIRegDetails_t details_par = CADIRegDetails_t(),
                      CADIRegDisplay_t display_par = CADI_REGTYPE_HEX,
                      CADIRegSymbols_t symbols_par = CADIRegSymbols_t(),
                      CADIRegFloatFormat_t fpFormat_par = CADIRegFloatFormat_t(),
                      uint32_t lsbOffset_par = 0,
                      uint32_t dwarfIndex_par = ~0U,
                      bool isProfiled_par = false,
                      bool isPipeStageField_par = false,
                      uint32_t threadID_par = 0,
                      CADIRegAccessAttribute_t attribute_par = CADI_REG_READ_WRITE,
                      uint32_t canonicalRegisterNumber_par = 0):
            regNumber(regNumber_par),
            bitsWide(bitsWide_par),
            hasSideEffects(hasSideEffects_par),
            details(details_par),
            display(display_par),
            symbols(symbols_par),
            fpFormat(fpFormat_par),
            lsbOffset(lsbOffset_par),
            dwarfIndex(dwarfIndex_par),
            isProfiled(isProfiled_par),
            isPipeStageField(isPipeStageField_par),
            threadID(threadID_par),
            attribute(attribute_par),
            canonicalRegisterNumber(canonicalRegisterNumber_par)
        {
            AssignString(name, name_par, sizeof(name));
            AssignString(description, description_par, sizeof(description));
        }

    public: // data
        char              name[CADI_NAME_SIZE];
        char              description[CADI_DESCRIPTION_SIZE];
        uint32_t               regNumber; ///< Register ID. Used by read/write functions to identify the register.
        uint32_t               bitsWide; /**< Bitwidth of non-string register. Ignored for string registers (targets should specify 0 for string registers). */
        int32_t               hasSideEffects; ///< Reserved. Targets should set this to 0.
        CADIRegDetails_t  details;        ///< Sub-register info
        CADIRegDisplay_t  display;        ///< Default is "HEX".
        CADIRegSymbols_t  symbols;        ///< For type "symbolic" only.
        CADIRegFloatFormat_t  fpFormat;   ///< For type "float" only.
        uint32_t               lsbOffset;  /**< Offset of the least signifcant bit relative to bit 0
                                            in the parent register (or 0 if there is no parent).*/
        enum { CADI_REGINFO_NO_DWARF_INDEX = 0xffffffff };
        uint32_t               dwarfIndex; /**< DWARF register index (CADI_REGINFO_NO_DWARF_INDEX
                                            if register has no DWARF register index).*/
        bool              isProfiled;     ///< Profiling info is available for this register
        bool              isPipeStageField; /**< Is pipe stage field, also true for pc and
                                             contentInfoRegisterId in CADIPipeStage_t. */
        uint32_t               threadID;   ///< Hardware thread ID (semantics not yet fully defined). Always set to 0.
        CADIRegAccessAttribute_t attribute; ///< Register access attributes.

        uint32_t          canonicalRegisterNumber; /**< The canonical register number as defined
                                                      by the scheme specified in
                                                      CADITargetFeatures_t::canonicalRegisterDescription.
                                                      If the scheme is the empty string then no
                                                      meaning can be ascribed to this field.
                                                   */

    };



    // ------------------------------------------------------------------------
    //    Memory Interface
    // ------------------------------------------------------------------------
    enum { CADI_MAU_MULTIPLES_LIST_SIZE = 32 };

    /// Memory space info data

    /// Each memory space (program and data, for example) in the system has a separate set of addresses.
    /// Any location in the memory of a device can be fully specified with no less than an indication of
    /// the memory space and the address within that space. Only one space can have the 'isProgramMemory'
    /// flag set.
    struct CADIMemSpaceInfo_t
    {
    public: // methods
        CADIMemSpaceInfo_t(const char *memSpaceName_par = "",
                           const char *description_par = "",
                           uint32_t memSpaceId_par = 0,
                           uint32_t bitsPerMau_par = 0,
                           CADIAddrSimple_t maxAddress_par = 0,
                           uint32_t nrMemBlocks_par = 0,
                           int32_t isProgramMemory_par = false,
                           CADIAddrSimple_t minAddress_par = 0,
                           int32_t isVirtualMemory_par = false,
                           uint32_t isCache_par = false,
                           uint8_t endianness_par = 0,
                           uint8_t invariance_par = 0,
                           uint32_t dwarfMemSpaceId_par = NO_DWARF_ID) :
            memSpaceId(memSpaceId_par),
            bitsPerMau(bitsPerMau_par),
            maxAddress(maxAddress_par),
            nrMemBlocks(nrMemBlocks_par),
            isProgramMemory(isProgramMemory_par),
            minAddress(minAddress_par),
            isVirtualMemory(isVirtualMemory_par),
            isCache(isCache_par),
            endianness(endianness_par),
            invariance(invariance_par),
            dwarfMemSpaceId(dwarfMemSpaceId_par)
        {
            AssignString(memSpaceName, memSpaceName_par, sizeof(memSpaceName));
            AssignString(description, description_par, sizeof(description));
        }

    public: // data
        char      memSpaceName[CADI_NAME_SIZE];   ///< Memory space name.
        char      description[CADI_DESCRIPTION_SIZE];  ///< Memory space description.
        uint32_t   memSpaceId;                     ///< Memory space ID.
        uint32_t   bitsPerMau;                     ///< Bits per Minimum Addressable Unit (e.g., 8 for byte).
        CADIAddrSimple_t maxAddress;              ///< Maximum address of this memory space.
        uint32_t   nrMemBlocks;                    ///< Number of memory blocks.
        int32_t   isProgramMemory;                ///< Only one space can have the isProgramMemory flag set.
        CADIAddrSimple_t minAddress;              ///< Minimum address of this memory space.
        int32_t   isVirtualMemory;                ///< This memory space is a Virtual/Physical space.
        uint32_t   isCache;                        ///< This memory space is a cache.

        uint8_t    endianness; ///< endianness, 0=mono-endian (arch defined), 1=LE, 2=BE
        uint8_t    invariance; ///< unit of invariance in bytes, 0=fixed invariance (arch defined)
        enum { NO_DWARF_ID = 0xffffffff };
        uint32_t   dwarfMemSpaceId; /**< DWARF memory space ID (NO_DWARF_ID
                                     if memory space has no DWARF memory space ID). */

        uint32_t   canonicalMemoryNumber; /**< The canonical memory number as defined
                                             by the scheme specified in
                                             CADITargetFeatures_t::canonicalMemoryDescription.
                                             If the scheme is the empty string then no
                                             meaning can be ascribed to this field.
                                          */
    };

    /// This signifies the read and write status for a block of memory.
    enum CADIMemReadWrite_t
    {
        CADI_MEM_ReadOnly,
        CADI_MEM_WriteOnly,
        CADI_MEM_ReadWrite,
        CADI_MEM_ENUM_MAX = 0xFFFFFFFF
    };

    /// Memory block info data

    /// This is a single block of memory addresses (inside a single memory space) that all have the same
    /// properties. For example, different memory blocks in the same memory space may be read-only. Blocks
    /// can be nested within one another. Blocks at the root level have CADI_MEMBLOCK_ROOT as the parent ID.
    /// <p>Name is used to give the user an idea of the type of memory ("off chip", for example).
    /// If cyclesToAccess is 0, the number is unknown or irrelevant.
    struct CADIMemBlockInfo_t
    {
    public: // methods
        CADIMemBlockInfo_t(const char *name_par = "",
                           const char *description_par = "",
                           uint16_t id_par = 0,
                           uint16_t parentID_par = 0,
                           CADIAddrSimple_t startAddr_par = 0,
                           CADIAddrSimple_t endAddr_par = 0,
                           uint32_t cyclesToAccess_par = 0,
                           CADIMemReadWrite_t readWrite_par = CADI_MEM_ReadWrite,
                           uint32_t *supportedMultiplesOfMAU_par = 0,
                           uint32_t endianness_par = 0,
                           uint32_t invariance_par = 0) :
            id(id_par),
            parentID(parentID_par),
            startAddr(startAddr_par),
            endAddr(endAddr_par),
            cyclesToAccess(cyclesToAccess_par),
            readWrite(readWrite_par),
            endianness(endianness_par),
            invariance(invariance_par)
        {
            AssignString(name, name_par, sizeof(name));
            AssignString(description, description_par, sizeof(description));
            if (supportedMultiplesOfMAU_par)
                std::memcpy(supportedMultiplesOfMAU, supportedMultiplesOfMAU_par, sizeof(supportedMultiplesOfMAU));
            else
                std::memset(supportedMultiplesOfMAU, 0, sizeof(supportedMultiplesOfMAU));
        }

    public: // data
        char              name[CADI_NAME_SIZE];       ///< Memory block name.
        char              description[CADI_DESCRIPTION_SIZE];  ///< Memory block description.
        uint16_t           id;                         ///< Memory block ID.
        uint16_t           parentID;                   ///< The ID of the parent. MXDI_MEMBLOCK_ROOT if no parent.
        CADIAddrSimple_t  startAddr;                  ///< The start address of this memory block.
        CADIAddrSimple_t  endAddr;                    ///< The end address of this memory block.
        uint32_t           cyclesToAccess;             ///< Number of cycles needed for an access to this block.
        CADIMemReadWrite_t readWrite;                 ///< The read/write type of this block
        uint32_t           supportedMultiplesOfMAU[CADI_MAU_MULTIPLES_LIST_SIZE];
        ///< Allowed multiples of the bits per mau, measured in bits

        uint8_t    endianness;  ///< endianness, 0=same as owning memory space, 1=LE, 2=BE
        uint8_t    invariance;  ///< unit of invariance in bytes, 0=same as owning memory space
    };


    /// Cache info data
    struct CADICacheInfo_t
    {
    public: // methods
        CADICacheInfo_t(uint16_t cacheLineSize_par = 0,
                        uint16_t cacheTagBits_par = 0,
                        uint16_t associativity_par = 0,
                        bool writeThrough_par = false) :
            cacheLineSize(cacheLineSize_par),
            cacheTagBits(cacheTagBits_par),
            associativity(associativity_par),
            writeThrough(writeThrough_par)
        {
        }

    public: // data
        uint16_t       cacheLineSize;  ///< Size of a cacheline in bytes.
        uint16_t       cacheTagBits;   ///< Size of a tag in bits.
        uint16_t       associativity;  ///< 1,2,4,8-way associative.
        bool          writeThrough;   ///< If true, then the dirty flag is not used.
    };



    /// This describes the type of control being exerted on the trace mechanism.
    enum CADITraceControl_t
    {
        CADI_TRACE_CNTL_StartContinuous,
        CADI_TRACE_CNTL_StartDiscontinuity,
        CADI_TRACE_CNTL_Stop
    };

    /// This describes the type of control being exerted on the trace mechanism.
    enum CADITraceBufferControl_t
    {
        CADI_TRACE_BUFF_Wrap,
        CADI_TRACE_BUFF_StopOnFull
    };

    /// This describes the type of control being exerted on the trace mechanism.
    enum CADITraceOverlayControl_t
    {
        CADI_TRACE_OVERLAY_Manager,
        CADI_TRACE_OVERLAY_Memory
    };

    /// This describes the type of data in a CADITraceBlock_t.
    enum CADITraceBlockType_t
    {
        CADI_TRACE_BLK_Address,
        CADI_TRACE_BLK_Overlay
    };

    /// This describes a single piece of trace data that either contains an overlay ID or an address.
    struct CADITraceBlock_t
    {
    public: // methods
        CADITraceBlock_t(CADITraceBlockType_t blockType_par = CADI_TRACE_BLK_Address,
                         CADIAddr_t address_par = CADIAddr_t(),
                         CADIOverlayId_t overlay_par = CADIOverlayId_t()) :
            blockType(blockType_par)
        {
            u.address = address_par;
            u.overlay = overlay_par;
        }

    public: // data
        CADITraceBlockType_t blockType;
        struct
        {
            CADIAddr_t      address;
            CADIOverlayId_t overlay;
        } u;
    };


    /// Reverse semihosting (for interupts from the debugger towards the target)
    enum CADISemiHostingInputChannelType_t
    {
        CADI_INPUT_KEYBOARD,
        CADI_INPUT_POINTING_DEVICE
    };


    /// Reverse semihosting (for interupts from the debugger towards the target)
    struct CADISemiHostingInputChannel_t
    {
    public: // methods
        CADISemiHostingInputChannel_t(uint32_t ID_par = 0,
                                      const char *name_par = "",
                                      CADISemiHostingInputChannelType_t type_par = CADI_INPUT_KEYBOARD) :
            ID(ID_par),
            type(type_par)
        {
            AssignString(name, name_par, sizeof(name));
        }

    public: // data
        uint32_t ID;
        char name[CADI_NAME_SIZE];
        CADISemiHostingInputChannelType_t type;
    };


    /// Reverse semihosting for interupts from the debugger towards the target.
    struct CADIConsoleChannel_t
    {
    public: // methods
        CADIConsoleChannel_t(uint32_t streamID_par,
                             const char *name_par = "",
                             bool blocking_par = false,
                             bool characterInput_par = false) :
            streamID(streamID_par),
            blocking(blocking_par),
            characterInput(characterInput_par)
        {
            AssignString(name, name_par, sizeof(name));
        }

    public: // data
        uint32_t streamID;
        char name[CADI_NAME_SIZE];
        bool blocking;              ///< If true, then the console is blocking for the appliInput() function
        bool characterInput;        /**< If true, then the notify/return from call is on a per character basis.
                                     If false, then the notify/return from call is on a or per line basis. */
    };

    ///
    /// This set of streamIds are reserved for special purposes to
    ///  CADICallbackObj::appliInput( uint32_t, uint32_t, uint32_t*, char*)
    /// and
    ///  CADICallbackObj::appliOutput( uint32_t, uint32_t, uint32_t*, char const*)
    /// They should automatically exists and no special action is need to use them.
    ///
    /// Attempting to CADICallbackObj::appliClose( uint32_t ) these handles will
    /// result in undefined behaviour and should not be done.
    ///
    enum CADIStreamId
    {
        CADI_STREAMID_STDIN = 0,
        CADI_STREAMID_STDOUT = 1,
        CADI_STREAMID_STDERR = 2
    };

    // ------------------------------------------------------------------------
    //    CADI Refresh Reasons
    // ------------------------------------------------------------------------

    enum CADIRefreshReason_t
    {
        CADI_REFRESH_REASON_MEMORY      = 1,
        CADI_REFRESH_REASON_REGISTERS   = 2,  ///< also for CADIGetInstructionCount/CADIGetCycleCount
        CADI_REFRESH_REASON_BREAKPOINTS = 4,
        CADI_REFRESH_REASON_PARAMETERS  = 8,
        CADI_REFRESH_REASON_OTHER       = (1 << 31),  ///< something changed which is not one of the above
        CADI_REFRESH_REASON_ALL         = 0xFFFFFFFF  ///< all of the above at the same time
    };


} // namespace eslapi

#endif // CADITypes_h

// end of file CADITypes.h
