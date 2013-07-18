// ===========================================================================
// Description : CADIDisassembler declaration.
//
// Author      : ARM
// Release     : 2.0.0
//
// Copyright (c) 2006-2008 ARM. All rights reserved.
//
// ============================================================================
//
#ifndef CADI2Disassembler_h
# define CADI2Disassembler_h

# include "eslapi/CADICommon.h"
# include "eslapi/CADITypes.h"

namespace eslapi
{
    enum CADIDisassemblerType
    {
        CADI_DISASSEMBLER_TYPE_STANDARD,      ///< disassembly supporting a PC and lookahead
        CADI_DISASSEMBLER_TYPE_SOURCELEVEL=2, ///< source level assembly / C
        CADI_DISASSEMBLER_TYPE_INTERPRETER    ///< interpreter window (e.g. for scripts)
    };

    enum CADIDisassemblerStatus
    {
        CADI_DISASSEMBLER_STATUS_OK,              ///< disassembling completed successfully
        CADI_DISASSEMBLER_STATUS_NO_INSTRUCTION,  ///< current address points to illegal instructions/data
        CADI_DISASSEMBLER_STATUS_ILLEGAL_ADDRESS, ///< address out of range (memory read failed)
        CADI_DISASSEMBLER_STATUS_ERROR            ///< other error
    };

    enum CADIDisassemblerInstructionType
    {
        CADI_DISASSEMBLER_INSTRUCTION_TYPE_NOCALL,  ///< The instruction is not a call, so for example an ALU instruction, memory access, or a jump
        CADI_DISASSEMBLER_INSTRUCTION_TYPE_CALL     ///< The instruction is a call into a subroutine. Program flow is expected to return after the subroutine has finished.
    };

    /// This callback class must be implemented by the disassembly frontend/window
    class CADI_WEXP CADIDisassemblerCB :
        public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADIDisassemblerCB2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }


        /// This callback is triggered by CADIDisassembler::GetModeNames()
        virtual void ReceiveModeName(uint32_t mode, const char *modename) =0;

        /// This callback is triggered by calling CADIDisassembler::GetSourceReferenceForAddress(...)
        virtual void ReceiveSourceReference(const CADIAddr_t &addr, const char *sourceFile, uint32_t sourceLine) =0;

        /// This callback is triggered by calling CADIDisassembler::GetDisassembly(...)
        virtual void ReceiveDisassembly(const CADIAddr_t &addr, const char *opcodes, const char *disassembly) =0;
    };

    /// This class defines the interface for a disassembler module
    class CADI_WEXP CADIDisassembler :
        public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADIDisassembler2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        /// @name Member Functions
        ///
        //@{
        /// @docinclude CADIDisasmType
        /// @docinclude CADIDisasmStatus
        /// @docinclude CADIDisasmCB

        /// Distinguish different types of disassembly
        virtual CADIDisassemblerType GetType() const =0;

        /// Support for multiple modes (e.g. 32bit versus 16bit mode - see ARM Thumb mode)
        /// <p>Valid modes start at "1" - mode "0" is don't care / no modes.
        /// @return How many modes available.
        virtual uint32_t GetModeCount() const = 0;

        /// Query names of all modes. Triggers callbacks to CADIDisassemblerCB::ReceiveModeName(), once for every mode.
        virtual void GetModeNames(CADIDisassemblerCB *callback) = 0;

        /// Get current execution mode. If modes are not supported by this target return 0. If modes are supported returns 0 < x <= GetModeCount().
        /// @return  The current execution mode.
        virtual uint32_t GetCurrentMode() = 0;

        /// Retrieves source-level information. Triggers a call of CADIDisassemblerCB::ReceiveSourceReference().
        /// @param[in]  addr        The requested address.
        /// @return     Return if the call successfully able to find a source reference.
        virtual CADIDisassemblerStatus GetSourceReferenceForAddress(CADIDisassemblerCB *callback,
                                                                    const CADIAddr_t &address) =0;

        /// @return First address corresponding generated for the given source line.
        /// @param[in]  sourceFile  A null terminated C string containing the source file name.
        /// @param[in]  sourceLine  The line number of that source file, first line is line #1.
        /// @param[out] address     The address of the first instruction belonging to that code.
        /// @return     Return if an address has successfully been found.
        virtual CADIDisassemblerStatus GetAddressForSourceReference(const char *sourceFile, 
                                                                    uint32_t sourceLine,
                                                                    CADIAddr_t &address) =0;

        /// Function for standard type disassembly
        /// @param[in]  addr
        ///               Used to pass the address of the instruction to
        ///               disassemble and to return the address of the next valid instruction.
        /// @param[out] nextAddr
        ///               Returns the address of the next instruction after those which have been disassembled.
        ///               Mandatory also if return value is CADIDISASM_NO_INSTRUCTION or
        ///               CADIDISASM_ILLEGAL_ADDRESS: nextAddr must be a hint to the next address which might 
        ///               result in successfull disassembly.
        /// @param[in]  mode
        ///               Contains the execution mode - if 0 then use current execution mode the core is in.
        /// @param[in]  desiredCount
        ///               Can be used to disassemble a sequence of instructions. Triggers up to desiredCount calls to 
        ///               CADIDisassemblerCB::ReceiveDisassembly(). First instruction will be the instruction pointed
        ///               to by 'address'. Further instructions will be instructions following without gap. The sequence
        ///               of disassembled instructions stops when there is an error (no instrucion, illegal address)
        ///               trying to disassemble an instruction.
        /// @return     Indicates status of last instruction successfully or unsuccessfully disassembled.
        virtual CADIDisassemblerStatus GetDisassembly(CADIDisassemblerCB *callback,
                                                      const CADIAddr_t &address,
                                                      CADIAddr_t &nextAddr,
                                                      const uint32_t mode,
                                                      uint32_t desiredCount = 1) =0;

        /// Query if an instruction is a call instruction
        /// @param[in]  addr
        ///               Used to pass the address of the instruction to
        ///               check if it is a call
        /// @param[out] isCall
        ///               Return if instruction is a call instruction.
        virtual CADIDisassemblerStatus GetInstructionType(const CADIAddr_t &address,
                                                          CADIDisassemblerInstructionType &insn_type) =0;
        
        /// @brief A default minimum implementation, to provide backwards-compatiblity with legacy code.
        /// This implementation assumes that there will be no other interfaces implemented on the component providing CADIDisassembler.
        virtual CAInterface * ObtainInterface(if_name_t    ifName,
                                              if_rev_t     minRev,
                                              if_rev_t *   actualRev)
        {
            if((strcmp(ifName,IFNAME()) == 0) && // if someone is asking for the matching interface
               (minRev <= IFREVISION())) // and the revision of this interface implementation is
                // at least what is being asked for
            {
                if (actualRev) // make sure this is not a NULL pointer
                {
                    *actualRev = IFREVISION();
                }
                //DuplicateRef();
                return this;
            }
            if((strcmp(ifName, CAInterface::IFNAME()) == 0) &&
                minRev <= CAInterface::IFREVISION())
            {
                if (actualRev != NULL)
                {
                    *actualRev = CAInterface::IFREVISION();
                }
                //DuplicateRef();
                return this;
            }
            return NULL;
        }

        //@}
    }; // class CADIDisassembler

} // namespace eslapi

#endif // #ifndef CADI2Disassembler_h

// end of file CADIDisassembler.h
