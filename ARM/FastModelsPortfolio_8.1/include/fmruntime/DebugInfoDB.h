/*
 * $Id: DebugInfoDB.h 29787 2013-03-01 10:40:01Z brifol01 $
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

#ifndef DEBUGINFODB_H
#define DEBUGINFODB_H

#include "MxTypes.h"

#include "DebugLineInfo.h"
#include "DebugFunctionInfo.h"
#include "DebugCoffSymbols.h"
#include "DebugDWARFCallFrameInfo.h"
#include "DebugDWARFInfo.h"


#define DEBUGINFODB_VERSION 3

namespace DebugInfoDB
{
    class DebugInfoRoot
    {
    public:
        // NOTE: Never ever reorder the first two virtual functions in the declaration!!!
        virtual ~DebugInfoRoot();
        // NOTE: Never ever reorder the first two virtual functions in the declaration!!!
        virtual MxU32 GetVersion() const { return DEBUGINFODB_VERSION; }
        // NOTE: Never ever reorder the first two virtual functions in the declaration!!!

        // default constructor, costructs an object containing all kinds of debug info (none of the pointers will be NULL)
        DebugInfoRoot();

        // constructor, which constructs an object points to foreign parts of the debug info
        // (this object will not allocate/free anything passed to this constructor)
        DebugInfoRoot(LineInfoDB *lineInfo_, CoffDebugSymbolsDB *coffDebugSymbols = 0,FunctionInfoDB *functionInfo_ = 0, DWARFCallFrameInfoDB *dwarfCallFrameInfo_ = 0, DWARFInfoDB *dwarfInfo_ = 0);

        // public methods
        void Clear();

        // access functions:

        // get line info
        LineInfoDB *GetLineInfo() { return lineInfo; }
        const LineInfoDB *GetLineInfo() const { return lineInfo; }


        // get COFF Debug Symbols
        CoffDebugSymbolsDB *GetCoffDebugSymbols() { return coffDebugSymbols; }
        void SetCoffDebugSymbols(CoffDebugSymbolsDB *symbols){coffDebugSymbols = symbols;}
//      const CoffDebugSymbolsDB *GetCoffDebugSymbols() {return coffDebugSymbols ;}

        // get function info
        FunctionInfoDB *GetFunctionInfo() { return functionInfo; }
        const FunctionInfoDB *GetFunctionInfo() const { return functionInfo; }

        // get DWARF call frame info
        DWARFCallFrameInfoDB *GetDWARFCallFrameInfo() { return dwarfCallFrameInfo; }
        const DWARFCallFrameInfoDB *GetDWARFCallFrameInfo() const { return dwarfCallFrameInfo; }

        // get DWARF debug info
        DWARFInfoDB *GetDWARFInfo() { return dwarfInfo; }
        const DWARFInfoDB *GetDWARFInfo() const { return dwarfInfo; }

        void SetDWARFInfo(DWARFInfoDB *dwarfInfo_){dwarfInfo=dwarfInfo_;}
        void SetFramePointerID(MxU32 id){framePointerID=id;}
        MxU32 GetFramePointerID(){return framePointerID;}
        // convenience access functions:

        // get function name for address
        // (uses various sources of information to locate the function:
        //  1. FunctionInfoDB
        //  2. Symbol Table)
        // return empty string if no function found
        const string GetFunctionName(MxU64 address) const;

        // put functions in debug info into the FunctionInfoDB
        void PutDebugInfoFunctionsIntoFunctionInfoDB(const DWARFInfoTreeNode *node = 0);

        void SetQuiet(bool quiet);

        // get/set ELF characteristics
#define EM_MACHINE_TYPE_NOT_SET 0xffffffff /* this is an invalid ELF machine type since the ELF machine type is 16 bit */
        MxU32 GetELFMachineType() const { return elfMachineType; }
        void SetELFMachineType(MxU16 elfMachineType_) { elfMachineType = elfMachineType_; }
        bool HasELFEndianness() const { return hasELFEndianness; }
        bool IsELFEndiannessBigEndian() { return elfEndiannessBigEndian; }
        void SetELFEndiannessBigEndian(bool elfEndiannessBigEndian_) { elfEndiannessBigEndian = elfEndiannessBigEndian_; hasELFEndianness = true; }
        MxU64 GetApplicationEntryPoint() { return applicationEntryPoint; }
        void SetApplicationEntryPoint (MxU64 entryPoint) { applicationEntryPoint = entryPoint; }

    private:
        // data containers
        LineInfoDB *lineInfo;
        CoffDebugSymbolsDB *coffDebugSymbols;
        FunctionInfoDB *functionInfo;
        DWARFCallFrameInfoDB *dwarfCallFrameInfo;
        DWARFInfoDB *dwarfInfo;

        // these pointers are used to delete debug info allocated by this object
        LineInfoDB *lineInfoToDelete;
        CoffDebugSymbolsDB *coffDebugSymbolsToDelete;
        FunctionInfoDB *functionInfoToDelete;
        DWARFCallFrameInfoDB *dwarfCallFrameInfoToDelete;
        DWARFInfoDB *dwarfInfoToDelete;

        // other data
        MxU32 elfMachineType;
        bool hasELFEndianness;
        bool elfEndiannessBigEndian;
        MxU32 framePointerID;
        MxU64 applicationEntryPoint;
    };
}

#endif

