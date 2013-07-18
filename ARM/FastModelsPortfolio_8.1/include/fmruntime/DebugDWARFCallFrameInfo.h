/*
 * $Id: DebugDWARFCallFrameInfo.h 29787 2013-03-01 10:40:01Z brifol01 $
 *
 * Project: Debug Info Database
 * $Author: brifol01 $
 * $Date: 2013-03-01 10:40:01 +0000 (Fri, 01 Mar 2013) $
 * $Revision: 29787 $
 *
 * Copyright (c) 2004 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */

#ifndef DEBUGDWARFCALLFRAMEINFO_H
#define DEBUGDWARFCALLFRAMEINFO_H

#include "MxTypes.h"

#include <string>
#include <vector>
using namespace std;
#include "Dwarf2Constants.h"

using namespace std;

namespace DebugInfoDB
{
    // common information entry
    struct DWARFCallFrameInfoCIE
    {
        string augmentation;
        MxU32 code_alignment_factor;
        MxS32 data_alignment_factor;
        vector<MxU8> initial_instructions; // DW_CFA_ opcodes
        MxU8 version;
        MxU8 return_address_register;
    };

    // frame description entry
    struct DWARFCallFrameInfoFDE
    {
        MxU64 initial_location;
        MxU64 end_location;  // this is initial_location + address_range - 1
        MxU32 CIE_pointer; // index into cieList array
        vector<MxU8> instructions; // DW_CFA_ opcodes
    };

    // return value of GetRegisterRulesForPreviousFrame(): a rule how to get the previous value for a register
    struct DWARFCallFrameInfoRegisterRule
    {
        DWARFCallFrameInfoRegisterRule(MxU32 rule_ = DW_CFA_RR_unspecified, MxS32 n_ = 0): rule(rule_), n(n_) {}
        MxU32 rule; // see DW_CFA_RR_ constants (undefined/same value/offset/register)
        MxS32 n; // either a signed offset or a register number
    };


    // main DebugInfo class
    class DWARFCallFrameInfoDB
    {
    public:
        // public methods
        DWARFCallFrameInfoDB(): isBigEndian(false), addressTypeSize(4), cfaOffsetIsFactoredOffset(false), restoreStateAlsoRestoresCFA(false), adjustCfaOffset(false) {}
        void Clear();
        void LoadDWARF(const MxU8 data[], MxU32 size, bool isBigEndian, MxU32 addressTypeSize);
        void DumpLikeReadELF();
        // this is the main API function: call this repeatedly and execute the register rules on a virtual register set to get the call stack
        bool GetRegisterRulesForPreviousFrame(MxU64 pc, MxU32 &cfaRegisterNumber_out, MxS32 &cfaOffset_out, MxU32 &returnAddressRegisterNumber_out, vector<DWARFCallFrameInfoRegisterRule> &registerRules_out);
        // get endianness
        bool IsBigEndian() const { return isBigEndian; }
        MxU32 GetAddressTypeSize() const { return addressTypeSize; }
        void SetFeatures(bool cfaOffsetIsFactoredOffset_, bool restoreStateAlsoRestoresCFA_, bool adjustCfaOffset_ = false)
        {
            cfaOffsetIsFactoredOffset = cfaOffsetIsFactoredOffset_;
            restoreStateAlsoRestoresCFA = restoreStateAlsoRestoresCFA_;
            adjustCfaOffset = adjustCfaOffset_;
        }

    private:
        // private helpers:
        void ExecuteCallFrameInstructions(const vector<MxU8>& instructions, MxU64 startPC, MxU64 pc, MxU32 code_alignment_factor,
                                          MxS32 data_alignment_factor, const vector<DWARFCallFrameInfoRegisterRule>& initialRules, bool print,
                                          MxU32 &cfaRegisterNumber_out, MxS32 &cfaOffset_out, vector<DWARFCallFrameInfoRegisterRule> &registerRules_out);

        // private data
        vector<DWARFCallFrameInfoCIE> cieList;
        vector<DWARFCallFrameInfoFDE> fdeList;
        bool isBigEndian;
        MxU32 addressTypeSize;
        bool cfaOffsetIsFactoredOffset;
        bool restoreStateAlsoRestoresCFA;
        bool adjustCfaOffset;
    };

}

#endif
