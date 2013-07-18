/*
 * $Id: DebugFunctionInfo.h 29787 2013-03-01 10:40:01Z brifol01 $
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

#ifndef DEBUGFUNCTIONINFO_H
#define DEBUGFUNCTIONINFO_H

#include "MxTypes.h"

#include <vector>
#include <string>
using namespace std;

namespace DebugInfoDB
{
    class FunctionInfoDB;

    class FunctionInfo
    {
    public:
        FunctionInfo(const string &name_, MxU64 lowPC_, MxU64 highPC_, bool inlined_=false);

        const string GetName() const { return name; }
        MxU64 GetLowPC() const { return lowPC; }
        MxU64 GetHighPC() const { return highPC; }
        MxU64 GetSize() const { return highPC - lowPC; }
        bool InRange(MxU64 pc) const { return (lowPC <= pc) && (pc < highPC); }
        bool IsInlined() const { return inlined; }
                bool IsThumb () const {return isThumb;}

                // adjust ordering to make enclosed ranges 'greater', ensuring they appear after the enclosers
                inline bool operator < (const FunctionInfo &b) const
                {
                    if (lowPC != b.lowPC)
                    {
                        return lowPC < b.lowPC;
                    }
                    else
                    {
                        // enclosing range < enclosed range
                        return b.highPC < highPC;
                    }
                }

    protected:
        string name;
        MxU64 lowPC, highPC;
        bool inlined;
                bool isThumb;

                // used to create the enclosing tree structure. unsafe after sortings.
                FunctionInfo * parent;

        friend class FunctionInfoDB;
                // for a given lowPC, with highPC == lowPC, this is the 'greatest' range
                // thus upper bound will always return ranges with lowPC > this.lowPC
        FunctionInfo(MxU64 lowPC_) : lowPC(lowPC_), highPC (lowPC_) {}
    };

    class FunctionInfoDB
    {
    public:
        enum { INVALID_ID = 0xffffffff };

        FunctionInfoDB();

        void Clear();

        unsigned int GetNumberOfFunctions() const;

        vector<string> GetAllFunctionNames() const;

        // get function information for an Id (ids go from 0 to N-1, where N == GetNumberOfFunctions())
        const FunctionInfo *GetFunctionInfoForId(size_t id) const;

        // get function id for a function name (yet slow)
        size_t GetFunctionInfoIdForName(const string& name) const;

        // Tries to find a function which contains a certain PC, else return NULL -- fast !
        inline const FunctionInfo *
        FindFunctionInfo(MxU64 pc) const
        {
            if (lastFunctionInfoFound &&
                lastFunctionInfoFound->InRange(pc))
            {
                return lastFunctionInfoFound;
            }
            else
            {
                return lastFunctionInfoFound = FindFunctionInfoInternal(pc);
            }
        }

        // same as above but return the id of the function info
        // may return INVALID_ID if pc is not in any function
        inline size_t FindFunctionInfoId(MxU64 pc) const
        {
            const FunctionInfo *fi = FindFunctionInfo(pc);
            if(fi)
                return fi - &(db[0]);
            else
                return INVALID_ID;
        }

        // add a function
        void AddFunctionInfo(const FunctionInfo &func);

        // add a section (sections are only used by GuessSizeForZeroSizeFunctions())
        void AddSectionInfo(const FunctionInfo &func);

                // set this if the core has Thumb mode
                // it controls the low bit of the start address, which is set to 1 for Thumb functions
                void AdjustThumbFunctions ();

                // set this if you want to allow overlapped functions, default false
                // it may happen when LOCAL symbols are loaded
                void AllowOverlappedFunctions (bool allow);

        // call this to guess sizes for all functions which have a zero size
        void GuessSizeForZeroSizeFunctions ();

                // local symbols may show up inside already existing function ranges (enclosed)
                // two strategies to deal with this problem:

                // a. speedup the search in presence of enclosed functions by using the holes search structure
                void PrepareHoles (int stepsBeforeSearchingHoles);
                // computes fully qualified name for enclosed functions for better display
                void ComputeFullEnclosedNames ();

                // b. completely eliminate functions appearing within other functions (enclosed)
                // this permits using the simple/fast search algorithm
                // can be used prior to guessing the size for zero size functions (only outer functions this time)
                void EliminateEnclosedFunctions ();

        private:
                // computes parent pointers according to enclosusre structure
                // assumes parents show up before childrent in dbT
                // parents pointers are invalidated by (during) sorting
                void ComputeParents () const;

    protected:
        typedef vector<FunctionInfo> dbT;
        dbT db; // this is the main database
        dbT sections; // this is only used by GuessSizeForZeroSizeFunctions()
        bool unclean; // db and sections may only be accessed if this is false, if its true Update() will set it to false
                // keeps track of holes between functions. speed up FindFunctionInfo when function is unknown
                // needed only when GuessSizeForZeroSizeFunctions is used.
                dbT holesdb;
                // if we GuessSizeForZeroSizeFunctions without EliminateEnclosedFunctions -> we need a moire complex search algorithm
                bool overlappingAllowed;
                // if >=1 and disjunct ranges then holes will not be searched. tunes up the hole searching process and offers a clean fallback to original range search algorithm
                // if -1, no holes machinery is used
                int stepsBeforeSearchingHoles;
                bool eliminatedEnclosedFunctions;

        mutable const FunctionInfo *lastFunctionInfoFound;

        const FunctionInfo *FindFunctionInfoInternal(MxU64 pc) const;

        // mark containers as 'unclean'
        void SetUnclean();

        // this must be called internally before 'db' is used
        // if unclean is true sort functions and then set unclean to false
        void Update() const;

#ifdef UNIT_TEST
public:
                void Prepare () const {Update ();}
                const vector <FunctionInfo> & holes () {return holesdb;}
#endif
    };
}

#endif
