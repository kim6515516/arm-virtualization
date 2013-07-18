/*
 * $Id: DebugCoffSymbols.h 29787 2013-03-01 10:40:01Z brifol01 $
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

#ifndef COFFDEBUGSYMBOLS_H
#define COFFDEBUGSYMBOLS_H

#include "MxTypes.h"

#include <map>
#include <string>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

#include "Coff.h"
#include "DebugDWARFInfo.h"
#include "Dwarf2Constants.h"


namespace DebugInfoDB
{
#define nameLength 1024
    struct filenamePos
    {
        string filename;
        MxU32 address;
    };
    class SymbolEntry
    {

    public:
        void Print();
        // container for CoffArchSyment
        struct COFFArchSyment coffArchSyment;

        // add alternative symbol table entries here
        // ...
        list <union COFFAuxent *> AuxEntries;
        MxU32 address;
    };

    class CoffDebugSymbol
    {
    };

    class CoffVariableInfo
    {
    public:
        // constructor
        CoffVariableInfo();
        ~CoffVariableInfo();
        CoffVariableInfo(const CoffVariableInfo &variableInfo);
        MxU32 type;
        string name;
        bool isStackVariable;
        bool isRegParam;
        MxS32 indexOrOffset;

    };
    class CoffBlockInfo
    {

    public:
        // constructor
        CoffBlockInfo();
        ~CoffBlockInfo();
        CoffBlockInfo(const CoffBlockInfo &blockInfo);
        list<CoffVariableInfo> variableList;
        MxU64 startAddress;
        MxU64 endAddress;
        string functionName;
    };

    class CoffFunctionInfo
    {

    public:
        // constructor
        CoffFunctionInfo();
        ~CoffFunctionInfo();
        CoffFunctionInfo(const CoffFunctionInfo &functionInfo);
        list <CoffBlockInfo> basicBlockList;
        list<CoffVariableInfo> variableList;
        MxU64 startAddress;
        MxU64 endAddress;
        string functionName;
    };



    // The set of all Debug Symbols in one file is stored in the CoffDebugSymbols
    class CoffDebugSymbols
    {
    public:
        CoffDebugSymbols();
        string GetFilename(){return filename;}

        // get a list of all symbols for one storage class
        list<SymbolEntry *> &GetSymbols(MxU8 storageClass);
        void Print();

    protected:

        friend class CoffDebugSymbolsDB;
    private:

        // access functions
        MxU32 GetWordFromCharArray(const MxU8 data[], MxU32 pos, bool bigendian);
         MxU16 GetShortFromCharArray(const MxU8 data[], MxU32 pos, bool bigendian);
        void AddNewCoffDebugSymbols(const MxU8 data[], const MxU8 strings[],MxU32 &currentPos, MxU32 size,MxU32 stringSize,bool bigendian,string &sectionFileName, DWARFInfoDB *dwarfInfo,list<filenamePos> &coffFilesInSegment);
        void InsertSymbolTableEntryIncludingAuxEntries(const MxU8 data[], const MxU8 strings[], MxU32 &currentPos, MxU32 size,MxU32 stringSize,bool bigendian, bool &filenameDetected,string &sectionFileName,list<filenamePos> &coffFilesInSegment);
        void ProcessFunctionsAndVariables(DWARFInfoDB *dwarfInfo,RCPointer<DWARFInfoTreeNode> insertionPoint,map<MxU32,RCPointer<DWARFInfoTreeNode> > &typeMap,MxU64 &start, MxU64 &end);
        void ProcessGlobalVariables(DWARFInfoDB *dwarfInfo,RCPointer<DWARFInfoTreeNode> insertionPoint,map<MxU32,RCPointer<DWARFInfoTreeNode> > &typeMap);
        void AddVariable(DWARFInfoDB *dwarfInfo,list<CoffVariableInfo>::iterator &varIt,RCPointer<DWARFInfoTreeNode> &newFunction,MxU64 startAddress,MxU64 endAddress,map<MxU32,RCPointer<DWARFInfoTreeNode> > &typeMap);
        void InitializeBasicTypeTable(map<MxU32,RCPointer<DWARFInfoTreeNode> > &typeMap,DWARFInfoDB *dwarfInfo,RCPointer<DWARFInfoTreeNode> insertionPoint);

        void PrintArchelonHeader(COFF_ASCNHDR &SectionHeader);
        void PrintSectionHeader(COFF_SCNHDR &sectionHeader);
        string GetTypeAsString(MxU32 type);
        void SetFramePointerID(MxU32 id){framePointerID=id;}
        MxU32 GetFramePointerID(){return framePointerID;}

        list<CoffFunctionInfo> &GetFunctionInfo(){return functionInfo;}

        void SetVerbose(bool verbose_){verbose=verbose_;}

        // list to store function definitions
        // ----------------------------------------
        // final list only consisting of complete functions
        list<CoffFunctionInfo> functionInfo;
        // used for nested loops
        list<CoffFunctionInfo> functionInfoStack;

        // list to store basic block definitions
        list<CoffBlockInfo> blockInfo;
        // intermediate data structure to put blocks on the stack
        list<CoffBlockInfo> blockInfoStack;

        list<CoffVariableInfo> globalList;
        // iterators to handle lists
        list<CoffFunctionInfo>::iterator functionInfoPos;
        list<CoffBlockInfo>::iterator blockInfoPos;

        MxU32 nestingLevel;
        // private members
        string filename;
        string lastKnownSymbol;
        bool verbose;
        list <SymbolEntry *> symEntries;
        map<MxU32,RCPointer<DWARFInfoTreeNode> > treeNodeMap;
        MxU32 framePointerID;

    };






    // For debug purposes:
    ostream &operator << (ostream &ostr, const CoffDebugSymbols &debugSymbols);

    class CoffDebugSymbolsDB
    {
    public:
        CoffDebugSymbolsDB();
        ~CoffDebugSymbolsDB();

        // copy constructor
        CoffDebugSymbolsDB(const CoffDebugSymbolsDB &a);

        // assignment
        const CoffDebugSymbolsDB &operator=(const CoffDebugSymbolsDB& a);

        void LoadCoffDebugStrings(const MxU8 strings[], MxU32 size);
        void LoadCoffDebugSymbols(const MxU8 data[], MxU32 size,string &sectionFileName);
        void ProcessDebugInfo(bool bigendian,string &sectionFileName,DWARFInfoDB *dwarfInfo);
        list<filenamePos> &GetCoffFilesInSegment(){return coffFilesInSegment;}

        void Clear();
        void PrintRawData(const MxU8 data[], MxU32 size);
        list <CoffDebugSymbols *> debugSymbols;
        void SetVerbose(bool _verbose){verbose=_verbose;}
        void SetFramePointerID(MxU32 id){framePointerID=id;}
        MxU32 GetFramePointerID(){return framePointerID;}
        bool containsInfo;



    private:
        // for every '.file' entry we have exactly one 'CoffDebugSymbols' entry
        MxU8 *symInfo;
        MxU8 *stringInfo;
        MxU32 stringSize;
        MxU32 symSize;
        bool verbose;
        list<filenamePos> coffFilesInSegment;
        MxU32 framePointerID;

    };
}

#endif
