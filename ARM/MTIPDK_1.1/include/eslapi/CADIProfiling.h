// ===========================================================================
// Description : CADI interface declaration.
//
// Author      : ARM
// Release     : 2.0.0
//
// Copyright (c) 2006-2008 ARM. All rights reserved.
//
// ============================================================================
//
#ifndef CADI2Profiling_h
# define CADI2Profiling_h

#include "eslapi/CADICommon.h"

namespace eslapi
{
    // ------------------------------------------------------------------------
    //    Profiling Interface
    // ------------------------------------------------------------------------
    //
    /// This allows the target to specify whether the results represent a percentage of the whole or
    /// a total count.
    enum CADIProfileResultType_t
    {
        CADI_PROF_RESULT_Percentage,
        CADI_PROF_RESULT_Count
    };

    /// This data type contains the results of a profiling session.
    class CADIProfileResults_t
    {
    public: // methods
        CADIProfileResults_t(uint32_t regionNumber_par = 0,
                             uint32_t accesses_par = 0) :
            regionNumber(regionNumber_par),
            accesses(accesses_par)
        {
        }

    public: // data
        uint32_t   regionNumber;
        uint32_t   accesses;
    };

    /// Profiled memory range.

    /// Objects of this type describe a memory range to be profiled. A region is part of a group of one
    /// or more regions. If addressesAreValid is not true, then the object refers to the entire memory
    /// space that is not included by another region. Note that two overlays for the same memory addresses
    /// do not constitute a shared memory space.
    class CADIProfileRegion_t
    {
    public: // methods
        CADIProfileRegion_t(int32_t addressesAreValid_par = false,
                            CADIOverlayId_t overlay_par = 0,
                            CADIMemSpace_t memorySpace_par = 0,
                            CADIAddrSimple_t start_par = 0,
                            CADIAddrSimple_t finish_par = 0) :
            addressesAreValid(addressesAreValid_par),
            overlay(overlay_par),
            memorySpace(memorySpace_par),
            start(start_par),
            finish(finish_par)
        {
        }

    public: // data
        int32_t               addressesAreValid;
        CADIOverlayId_t       overlay;
        CADIMemSpace_t        memorySpace;
        CADIAddrSimple_t  start;
        CADIAddrSimple_t  finish;
    };

    /// This determines the type of profiling to which the region definition applies.
    enum CADIProfileType_t
    {
        CADI_PROF_TYPE_Execution,
        CADI_PROF_TYPE_Memory,  /// Used with CADIProfileGetMemory.
        CADI_PROF_TYPE_Trace    /// Used with CADIProfileGetTrace.
    };

    /// This describes action this call is trying to apply to the target profiling mechanism.
    enum CADIProfileControl_t
    {
        CADI_PROF_CNTL_Start,
        CADI_PROF_CNTL_Stop,
        CADI_PROF_CNTL_Reset
    };

    class CADIRegProfileResults_t
    {
    public: // methods
        CADIRegProfileResults_t(uint32_t regID_par = 0,
                                uint64_t readAccesses_par = 0,
                                uint64_t writeAccesses_par = 0) :
            regID(regID_par),
            readAccesses(readAccesses_par),
            writeAccesses(writeAccesses_par)
        {
        }

    public: // data
        uint32_t   regID;
        uint64_t   readAccesses;
        uint64_t   writeAccesses;
    };

    class CADIMemProfileResults_t
    {
    public: // methods
        CADIMemProfileResults_t(CADIAddrSimple_t address_par = 0,
                                uint64_t readAccesses_par = 0,
                                uint64_t writeAccesses_par = 0) :
            address(address_par),
            readAccesses(readAccesses_par),
            writeAccesses(writeAccesses_par)
        {
        }

    public: // data
        CADIAddrSimple_t address;
        uint64_t   readAccesses;
        uint64_t   writeAccesses;
    };

    class CADIInstructionProfileResults_t
    {
    public: // methods
        CADIInstructionProfileResults_t(uint32_t FID_par = 0,
                                        const char *name_par = "",
                                        const char *pathToInstructionInLISASource_par = "",
                                        uint64_t executionCount_par = 0) :
            FID(FID_par),
            executionCount(executionCount_par)
        {
            AssignString(name, name_par, sizeof(name));
            AssignString(pathToInstructionInLISASource, pathToInstructionInLISASource_par, sizeof(pathToInstructionInLISASource_par));
        }

    public: // data
        uint32_t FID;
        char     name[CADI_DESCRIPTION_SIZE];
        char     pathToInstructionInLISASource[CADI_DESCRIPTION_SIZE];
        uint64_t executionCount;
    };

    enum CADIProfileResourceAccessType_t
    {
        CADI_PROF_ACCESS_READ,
        CADI_PROF_ACCESS_WRITE,
        CADI_PROF_ACCESS_READ_OR_WRITE
    };

    enum CADIProfileHazardTypes_t
    {
        CADI_PROF_HAZARD_RESOURCE_MAX_ACCESS,
        CADI_PROF_HAZARD_RESOURCE_MIN_ACCESS,
        CADI_PROF_HAZARD_RESOURCE_MAX_WRITE_ACCESS,
        CADI_PROF_HAZARD_RESOURCE_MAX_READ_ACCESS,
        CADI_PROF_HAZARD_RESOURCE_READ_AFTER_WRITE,
        CADI_PROF_HAZARD_RESOURCE_WRITE_AFTER_READ,
        CADI_PROF_HAZARD_CONTROL,
        CADI_PROF_HAZARD_OTHER
    };

    class CADIProfileHazardDescription_t
    {
    public: // methods
        CADIProfileHazardDescription_t(CADIProfileHazardTypes_t type_par = CADI_PROF_HAZARD_RESOURCE_MAX_ACCESS,
                                       uint32_t numberOfAccesses_par = 0,
                                       uint32_t originInstructionFID_par = 0,
                                       uint32_t affectedInstructionFID_par = 0,
                                       const char *resource_par = "",
                                       const char *messages_par = "") :
            type(type_par),
            numberOfAccesses(numberOfAccesses_par),
            originInstructionFID(originInstructionFID_par),
            affectedInstructionFID(affectedInstructionFID_par)
        {
            AssignString(resource, resource_par, sizeof(resource));
            AssignString(message, messages_par, sizeof(message));
        }

    public: // data
        CADIProfileHazardTypes_t type;
        uint32_t    numberOfAccesses;           // number of accesses to affected resource
        uint32_t    originInstructionFID;       // FID of the originator resource/instruction
        uint32_t    affectedInstructionFID;     // name of the affected resource/instruction
        char        resource[CADI_DESCRIPTION_SIZE];
        char        message[CADI_DESCRIPTION_SIZE];  // hazard message
    };



    class CADI_WEXP CADIProfilingCallbacks :
        public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADIProfilingCallbacks2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }
        

        /// @param[in] name
        /// @param[in] accessType
        virtual void profileResourceAccess(const char * name,
                                           CADIProfileResourceAccessType_t accessType) = 0;

        /// @param[in] desc
        virtual void profileRegisterHazard(CADIProfileHazardDescription_t * desc) = 0;
    };

    class CADI_WEXP CADIProfiling :
        public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADIProfiling2"; }
        
        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }


        /// @name Profiling API
        /// These APIs are used to access execution and memory profiling for a processor.
        //@{
        /// @docinclude CADIProfileResultType_t
        /// @docinclude CADIProfileResults_t

        /// This informs the target of the memory regions that are to be instrumented. This only needs to be
        /// called once for any number of calls to CADIProfileControl (start) and CADIProfileControl (stop).
        /// <p>The return value should be CADI_STATUS_IllegalArgument if any of the following are true:
        /// - any region spans unpopulated memory
        /// - any region spans illegal memory
        /// - any region overlaps another region
        /// - the address space of a region is not consistent with the profiling type.
        ///
        /// @docmove CADIProfileRegion_t
        /// @docmove CADIProfileType_t
        /// @param[in] type         The type of profiling (execution addresses or data access) to which these
        ///                         regions apply.
        /// @param[in] regionCount  The number of regions.
        /// @param[in] region       This contains the memory areas being instrumented. The caller allocates
        ///                         all memory.
        virtual CADIReturn_t CADIProfileSetup (CADIProfileType_t type,
                                               uint32_t regionCount,
                                               CADIProfileRegion_t *region) = 0;

        /// This starts, stops, and resets profiling.
        /// @docmove CADIProfileControl_t
        /// @param[in] control
        ///               Defines profiling behavior. Enables three actions: start profiling, stop profiling,
        ///               or act as though we stopped and immediately started profiling.
        ///               Starting profiling resets any information that was saved though
        ///               stopping should not.
        virtual CADIReturn_t CADIProfileControl (CADIProfileControl_t control) = 0;

        /// This starts, stops, and resets execution trace capture.
        /// @docmove CADITraceControl_t
        /// @docmove CADITraceBufferControl_t
        /// @docmove CADITraceOverlayControl_t
        /// @param[in] bufferArg
        /// @param[in] control
        ///               What should happen when the buffer is full. Only valid on some sort of start trace.
        /// @param[in] overlay
        ///               If CADI_TRACE_OVERLAY_Memory, overlay events should be included in the trace output
        ///               at the expense of not being able to see inside the trace manager. If
        ///               CADI_TRACE_OVERLAY_Manager the trace data should include the overlay manager code
        ///               at the expense of not knowing details about memory regions being overlayed.
        virtual CADIReturn_t CADIProfileTraceControl (CADITraceBufferControl_t bufferArg,
                                                      CADITraceControl_t control,
                                                      CADITraceOverlayControl_t overlay) = 0;

        /// This gets the results of a profiling session for executable code. If called before profiling is
        /// stopped or before a legal set of regions have been established, this call should return
        /// CADI_STATUS_GeneralError.
        /// @param[out] type
        ///               This tells the caller whether percentage statistics or an absolute count is being
        ///               returned
        /// @param[in]  regIndex
        ///               The index into the target buffer.
        /// @param[in]  regionSlots
        ///               The number of spaces requested to be filled. The target shall not fill more than
        ///               this number of elements in the region array.
        /// @param[out] regionCount
        ///               This is the actual number of regions setup by CADIProfileSetup plus 1 for the "other"
        ///               category.
        /// @param[out] region
        ///               Regions correspond to the ones setup by CADIProfileSetup. The array is allocated (and
        ///               deallocated, if applicable) by the caller to be filled by the target.
        virtual CADIReturn_t CADIProfileGetExecution (CADIProfileResultType_t *type,
                                                      uint32_t regIndex,
                                                      uint32_t regionSlots,
                                                      uint32_t *regionCount,
                                                      CADIProfileResults_t *region) = 0;

        /// This gets the results of a profiling session for memory access. If called before profiling is stopped
        /// or before a legal set of profiling regions has been established, this call should return
        /// CADI_STATUS_GeneralError.
        /// <p>CADIProfileGetMemory is a separate call from CADIProfileGetExecution as a hedge
        /// against the two call signatures diverging. The requirement is a new feature in the ARM ESL
        /// debug interfaces. As such, some details may change in future versions of he specification.
        /// @param[out] type
        ///               This tells the caller whether percentage statistics or an absolute count is being
        ///               returned.
        /// @param[in]  regIndex
        ///               The index into the target buffer.
        /// @param[in]  regionSlots
        ///               The number of spaces requested to be filled. The target shall not fill more than
        ///               this number of elements in the region array.
        /// @param[out] regionCount
        ///               This is the actual number of regions setup by CADIProfileSetup plus 1 for the "other"
        ///               category.
        /// @param[out] region
        ///               Regions correspond to the ones setup by CADIProfileSetup. The array is allocated (and
        ///               deallocated, if applicable) by the caller to be filled by the target.
        virtual CADIReturn_t CADIProfileGetMemory (CADIProfileResultType_t *type,
                                                   uint32_t regIndex,
                                                   uint32_t regionSlots,
                                                   uint32_t *regionCount,
                                                   CADIProfileResults_t *region) = 0;

        /// This gets the results of a trace session - it returns PC values that have been executed by the target.
        /// @docmove CADITraceBlockType_t
        /// @docmove CADITraceBlock_t
        /// @param[in]  blockIndex
        ///               The start index of the trace block
        /// @param[in]  blockSlots
        ///               The number of spaces available to fill. The target shall not fill more than this
        ///               number of elements in the block array.
        /// @param[out] blockCount
        ///               Number of samples being returned.
        /// @param[out] block
        ///               The list of executed addresses and overlay events in time sequential order.
        ///               The blocks in the array should be sorted by time executed and block[0] should contain
        ///               the most recently executed address or event. If multiple program memory spaces exist
        ///               and execution transitions from one space to another, separate blocks should exist
        ///               for each memory space.
        ///               The array is allocated (and deallocated, if applicable) by the caller to be filled by
        ///               the target.
        virtual CADIReturn_t CADIProfileGetTrace (uint32_t blockIndex,
                                                  uint32_t blockSlots,
                                                  uint32_t *blockCount,
                                                  CADITraceBlock_t *block) = 0;

        /** Reads the number of read/write accesses for 'numberOfRegs'
         registers, starting with register index 'startReg'. After the
         call 'reg' will contain the results, 'actualNumberOfRegs'
         contains the number of registers the profiling data was
         actually read for. Note that 'reg' must point to an array of
         objects of type CADIResourceProfileResults_t with size
         'numberOfRegs'
         @docmove CADIRegProfileResults_t
         */
        virtual CADIReturn_t CADIProfileGetRegAccesses(uint32_t startRegID,
                                                       uint32_t numberOfRegs,
                                                       CADIRegProfileResults_t *reg,
                                                       uint32_t &actualNumberOfRegs) = 0;

        /** Writes the number of read/write accesses for 'numberOfRegs'
         registers according to values saved in 'reg', starting with
         register index 'startReg'. After the call 'actualNumberOfRegs'
         contains the number of updated registers. Note that 'reg' must
         point to an array of objects of type
         CADIResourceProfileResults_t with size 'numberOfRegs' */
        virtual CADIReturn_t CADIProfileSetRegAccesses(uint32_t startRegID,
                                                       uint32_t numberOfRegs,
                                                       CADIRegProfileResults_t *reg,
                                                       uint32_t &actualNumberOfRegs) = 0;

        /** Reads the number of read/write accesses for 'numberOfUnits' memory
         units, starting with memory unit at address
         'startAddress'. After the call 'mem' will contain the results, 'actualNumberOfUnits' contains the number of memory units the
         profiling data was actually read for. Note that 'mem' must
         point to an array of objects of type
         CADIResourceProfileResults_t with size 'numberOfUnits'.
         @docmove CADIMemProfileResults_t
         */
        virtual CADIReturn_t CADIProfileGetMemAccesses(CADIAddrComplete_t startAddress,
                                                       uint32_t numberOfUnits,
                                                       CADIMemProfileResults_t *mem,
                                                       uint32_t &actualNumberOfUnits) = 0;

        /** Writes the number of read/write accesses for 'numberOfUnits'
         memory units according to values saved in 'mem', starting with
         memory unit at address 'startAddress'. After the call
         'actualNumberOfUnits' contains the number of memory updated
         units. Note that 'mem' must point to an array of objects of
         type CADIResourceProfileResults_t with size
         'numberOfUnits'. */
        virtual CADIReturn_t CADIProfileSetMemAccesses(CADIAddrComplete_t startAddress,
                                                       uint32_t numberOfUnits,
                                                       CADIMemProfileResults_t *mem,
                                                       uint32_t &actualNumberOfUnits) = 0;

        /** Reads the execution frequency for 'numberOfAddr' disassembly
         addresses, starting with address 'startAddr'. After the call
         'freq' contains the results, 'actualNumberOfAddr' contains the
         number of addresses the frequency was read for. Note that
         'freq' must point to an array of uint32_t with size
         'numberOfAddr'. */
        virtual CADIReturn_t CADIProfileGetAddrExecutionFrequency(uint64_t startAddr,
                                                                  uint32_t numberOfAddr,
                                                                  uint64_t *freq,
                                                                  uint32_t &actualNumberOfAddr) = 0;

        /** Writes the execution frequency for 'numberOfAddr' disassembly
         addresses according to values saved in 'freq', starting with
         address 'startAddr'. After the call 'actualNumberOfAddr'
         contains the number of updated addresses. Note that 'freq'
         must point to an array of uint32_t with size 'numberOfAddr'. */
        virtual CADIReturn_t CADIProfileSetAddrExecutionFrequency(uint64_t startAddr,
                                                                  uint32_t numberOfAddr,
                                                                  uint64_t *freq,
                                                                  uint32_t &actualNumberOfAddr) = 0;

        /// Returns number of instructions of the target.
        virtual CADIReturn_t CADIGetNumberOfInstructions(uint32_t *num_instructions) = 0;

        /** This method prepares given array 'instructions' by setting
         'FID', 'name' and 'pathToInstructionInLISASource'. While
         'numberOfInstructions' defines the desired number of array
         entries to be prepared, 'actualNumberOfInstructions' contains
         the number of array entries actually prepared which might
         differ from 'numberOfInstructions'.
         @docmove CADIInstructionProfileResults_t
         */
        virtual CADIReturn_t CADIProfileInitInstructionResultArray(uint32_t numberOfInstructions,
                                                                   CADIInstructionProfileResults_t *instructions,
                                                                   uint32_t &actualNumberOfInstructions) = 0;

        /** Reads the execution counts for 'numberOfInstructions'
         instructions by setting the appropriate 'executionCount' entry
         in array 'instructions'. After the call
         'actualNumberOfInstructions' contains the number of
         instructions the counts were read for. */
        virtual CADIReturn_t CADIProfileGetInstructionExecutionFrequency(uint32_t  numberOfInstructions,
                                                                         CADIInstructionProfileResults_t *instructions,
                                                                         uint32_t  &actualNumberOfInstructions ) = 0;

        /** Writes the execution counts for 'numberOfInstructions'
         instructions according to values in 'instructions'. After the
         call 'actualNumberOfInstructions' contains the number of
         instructions the counts were read for. */
        virtual CADIReturn_t CADIProfileSetInstructionExecutionFrequency(uint32_t  numberOfInstructions,
                                                                         CADIInstructionProfileResults_t *instructions,
                                                                         uint32_t  &actualNumberOfInstructions ) = 0;

        /** Registers given resource access callback called if resource
        'name' is accessed as specified by 'accessType'.
        @docmove CADIProfileResourceAccessType_t
        */
        virtual CADIReturn_t CADIRegisterProfileResourceAccess(const char * name,
                                                               CADIProfileResourceAccessType_t accessType) = 0;
        
        /// Unregisters the profile hazard callback.
        virtual CADIReturn_t CADIUnregisterProfileResourceAccess(const char * name) = 0;
        

        /// @brief Registers the profile hazard callbacks.
        ///
        /// @docmove CADIProfileHazardTypes_t
        /// @docmove CADIProfileHazardDescription_t
        /// @docmove CADIProfileHazardCallBack_t
        virtual CADIReturn_t CADIProfileRegisterCallBack(CADIProfilingCallbacks *callbackObject) = 0;
        
        /// Unregisters given hazard callback.
        virtual CADIReturn_t CADIProfileUnregisterCallBack(CADIProfilingCallbacks *callbackObject) = 0;

        //@}
    };

} // namespace eslapi

#endif // #ifndef CADIProfiling_h

// end of file CADI.h
