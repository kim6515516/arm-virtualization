/*
 * $Id: DebugLineInfo.h 29787 2013-03-01 10:40:01Z brifol01 $
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

#ifndef DEBUGLINEINFO_H
#define DEBUGLINEINFO_H

#include "MxTypes.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "Coff.h"
#include "DebugCoffSymbols.h"

// offset of line number in Auxiliary entry in COFF symbol table entries (only Archelon generated files)
#define LINENO_OFFSET_AUX 46

namespace DebugInfoDB
{
    class LineInfo
    {
    public:
        LineInfo(MxU64 address,
                 MxU16 srcfileIdx,
                 MxU32 line,
                 MxU16 column,
                 bool is_stmt,
                 bool basic_block = false,
                 bool end_sequence = false);
        MxU64 GetAddress() const         { return address; }
        MxU16 GetSourceFileIndex() const { return srcFileIdx; }
        MxU32 GetLine() const            { return line; }
        MxU16 GetColumn() const          { return column; }
        bool  IsStatement() const        { return is_stmt; }
        bool  IsBasicBlock() const       { return basic_block; }
        bool  IsEndSequence() const      { return end_sequence; }

        inline bool operator < (const LineInfo &b) const
        { return (address < b.address); }

        bool operator == (const LineInfo &b) const
        { return (address == b.address) &&
                AlmostEqual(*this, b); }

        static inline bool LessBySourceReference(const LineInfo &a, const LineInfo &b)
        {
            if (a.srcFileIdx < b.srcFileIdx) return true;
            else if (a.srcFileIdx > b.srcFileIdx) return false;

            else if (a.line < b.line) return true;
            else if (a.line > b.line) return false;

            else return (a.column < b.column);
        }

        // Checks if all info is equal (doesn't compare address)
        static bool AlmostEqual(const LineInfo &a, const LineInfo &b)
        {
            return
                (a.srcFileIdx == b.srcFileIdx) &&
                (a.line == b.line) &&
                (a.column == b.column) &&
                (a.is_stmt == b.is_stmt) &&
                (a.basic_block == b.basic_block) &&
                (a.end_sequence == b.end_sequence);
        }

    protected:
        MxU64 address;        // 8 byte
        MxU32 line;            // 4 byte
        MxU16 srcFileIdx;    // 2 byte
        MxU16 column;        // 2 byte
        bool  is_stmt      : 1;    // 1 byte
        bool  basic_block  : 1;
        bool  end_sequence : 1;
        // total size of class = 20 bytes

        friend class LineInfoDB;
    };

    // For debug purposes:
    ostream &operator << (ostream &ostr, const LineInfo &lineInfo);

    class LineInfoDB
    {
    public:
        LineInfoDB();
        ~LineInfoDB();

        // copy constructor
        LineInfoDB(const LineInfoDB &a);

        // assignment
        const LineInfoDB &operator=(const LineInfoDB& a);

        void Clear();

        // This returns the index for an existing or newly added source file name
        unsigned int GetSourceFileIndex(const string &filename);

        // This returns the index for an existing source file. If the source file could not be found it will return -1.
        // If allowPatrialMatch is false the filename will only be found if it matches exactly one filename in the DB,
        // else it will also be found if in filename some parent directories have not been specified (do not use unless absolutely necessary).
        unsigned int LookupSourceFileIndex(const string &filename, bool allowPartialMatch = false) const;

        // This is the reverse operation, return the source file name for an index
        const string &GetSourceFile(unsigned int srcFileIndex) const;

        // This can be used to derive the highest valid source file index.
        unsigned int GetNumberOfSourceFiles() const { return (unsigned int)sourceFiles.size(); }

        // add a single line info element
        // jo: AddLineInfo is somewhat performance critical, keep it simple, this used to do insertion sort, now it does almost nothing
        void AddLineInfo(const LineInfo &newInfo) {    lineInfos.push_back(newInfo); lineInfosIsUnclean = true; }

        // get number of line infos
        MxU32 GetNumberOfLineInfos() const { UpdateLineInfos(); return (MxU32)lineInfos.size(); }
        // get specific line info (id is not the address but an id in the range [0..GetNumberOfLineInfos()-1])
        const LineInfo *GetLineInfo(MxU32 id) const { UpdateLineInfos(); return (id < lineInfos.size()) ? &lineInfos[id] : 0; }

        /* Find the info which is valid for this address (address of
           info found is lower or equal). If no valid info could be
           found a NULL pointer is returned. */
        const LineInfo *Find(MxU64 addr) const;

        // return all address ranges covered by the statement surrounding addr
        // for each element of the list:
        //    first: start address of the range
        //    second: size of the range
        vector<pair<MxU64,MxU64> > GetAddressRangesForStatement(MxU64 addr) const;

        // return all address ranges not covered by line info
        vector<pair<MxU64,MxU64> > GetAddressRangesNotCoveredByLineInfo() const;

        // sort address ranges (sort to start address)
        static void SortAddressRanges(vector<pair<MxU64,MxU64> >& ranges);

        // invert address ranges
        // ranges needs to be sorted and ranges may not overlap
        static void InvertAddressRanges(vector<pair<MxU64,MxU64> >& ranges);

            /** Find the highest line number of a source file which
            produced debug line info. If source file did not produce
            any code 0 will be returned. */
        MxU32 GetLastSourceLine(MxU16 sourceFileIndex) const;

        /** Find the line infos of the first instruction of each code
            sequence generated from a certain source line. Due to
            inlining and code reordering because of optimization there
            might be multiple sequences of instructions generated by
            one source line. This is why the function might return
            multiple addresses. If no such instructions are found an
            empty vector is returned. (Typical application is to
            acquire all addresses to set a source level breakpoint on a
            certain source line.) Parameter 'sourceFileIndex' must be lower than
            GetNumberOfSourceFiles() which is checked by an
            assertion. If 'line' is too big (beyond the end of the
            source file) it will just result in an empty vector. The
            pointers to the LineInfos returned must not be freed in
            any case ! */
        const vector<const LineInfo *> FindFirstInstructionsOfSourceLine(MxU16 sourceFileIndex, MxU32 line) const;
        /** Returns true if the previous function returns non-empty vector.
            Implemented for performance reasons. */
        bool  SourceLineHasInstructions(MxU16 sourceFileIndex, MxU32 line) const;

        /** This will find all line-infos which belong to a certain *
            source line. This means you will get the addresses of all
            * instructions which were generated from a source
            line. Due * to inlining and optimizations there might be
            multiple * sequences of instructions from one source
            line. Parameter 'sourceFileIndex' must be lower than
            GetNumberOfSourceFiles() which is checked by an
            assertion. If 'line' is too big (beyond the end of the
            source file) it will just result in an empty vector. The
            pointers to the LineInfos returned must not be freed in
            any case ! */
        const vector<const LineInfo *> FindAllInstructionsOfSourceLine(MxU16 sourceFileIndex, MxU32 line) const;

        // add offset to all addresses - e.g. used by linker
        void Relocate(MxU64 offset);

        void AddForeignSourceFilename(const string &srcFileName, MxU64 foreignIdx);

        // old method
        void LoadCOFF(const MxU8 data[], MxU32 size, bool bigendian);

        void LoadCoffSymbolInfo(const MxU8 data[], MxU32 size, bool bigendian);

        void PrintSectionHeader(COFF_SCNHDR &sectionHeader);

        void PrintArchelonHeader(COFF_ASCNHDR &archelonHeader);

        void PrintRawData(const MxU8 data[], MxU32 size,MxU32 start);

        MxU32 GetWordFromCharArray(const MxU8 data[], MxU32 pos, bool bigendian);


        // new method which uses Archelon generated Debug info
        void LoadCOFFDebugLineInfo(const MxU8 data[], MxU32 size,const MxU8 symboldata[], MxU32 symbolsize, bool bigendian,string sectionFileName,list<filenamePos> &coffFilesInSegment);

        // load .debug_line section
        // additional sections are only used to analyze, where line info is present in the file
        void LoadDWARF(const MxU8 debug_line[], MxU32 debug_line_size,
                       const MxU8 debug_info[], MxU32 debug_info_size,
                       const MxU8 debug_abbrev[], MxU32 debug_abbrev_size,
                       const MxU8 debug_loc[], MxU32 debug_loc_size,
                       const MxU8 debug_str[], MxU32 debug_str_size,
                       const MxU8 debug_ranges[], MxU32 debug_ranges_size,
                       bool isBigEndian, MxU32 addressTypeSize);

        // load line info for a single compilation unit:
        // debug_line points to the start of the data somewhere inside the
        // .debug_line section and debug_line_size is the remaining available
        // data in the .debug_line section
        void LoadDWARFCompilationUnit(const MxU8 debug_line[], MxU32 debug_line_size,
                                      bool isBigEndian, MxU32 address_size);

        // get extended address shift
        // (always 0 for .debug_line and >= 0 for .debug_line_ext)
        // (this allows fine grain line info with a finer granularity than real addresses)
        MxU32 GetExtendedAddressShift() const { return extendedAddressShift; }

        // set extended address shift
        // (used by the loader to set the extended address shift which is characteristic to the data loaded by LoadDWARF())
        // (this value is stored in ELF files in the absolute symbol debug_line_ext_shift_value__)
        void SetExtendedAddressShift(MxU32 shift) { extendedAddressShift = shift; }

        void Merge(const LineInfoDB &other);

        // convert this database from extended addresses (as defined by extendedAddressShift) to
        // real addresses (comparable to the PC)
        void ConvertExtendedToRealAddresses();

        // If possible avoid using this method:
        const vector<LineInfo> &GetDB() const { UpdateLineInfos(); return lineInfos; }

        // For debugging
        void Dump(ostream &ostr) const;




    private:
        // private types
        class SourceFile
        {
        public:
            SourceFile(const string &filename = string(), MxU64 foreignIndex = MxU64(-1));
            ~SourceFile();

            string filename;

            typedef vector<vector<const LineInfo *> > ReverseLookupT;
            mutable ReverseLookupT *srcLine2addresses; // (cache)table for faster reverse lookup (line => addresses)

            MxU64  foreignIndex;    // used for COFF format line info
        };
        typedef vector<SourceFile> sourceFilesT;
        typedef vector<LineInfo> lineInfosT;


        // private methods

        // get source file index for symbol index (see AddCOFFSourceFilename)
        MxU32 GetSourceFileIndexForForeignIndex(MxU64 foreignIndex) const;

        // This must be called internally if some change of the data (e.g. AddLineInfo()) occurs
        void InvalidateCaches() const;

        // this must be called internally before 'lineInfos' is used
        void UpdateLineInfos() const;

        // This gives back a reverse lookup table for a source
        // file. It will create such a table if no such table has been
        // created so far.
        const SourceFile::ReverseLookupT *GetReverseLookupTable(MxU16 sourceFileIndex) const;


        // private data
        sourceFilesT sourceFiles;
        lineInfosT lineInfos;
        bool lineInfosIsUnclean; // jo: set by AddLineInfo and reset by UpdateLineInfos()
        const string emptyString; // used to return references to empty strings

        // extended address shift: to get real addresses (addresses comparable to the PC) the addresses in this
        // container need to be shifted right by this)
        // (this variable is not used in the algorithms in this class, it is just a container so that anyone who
        // has access to this LineInfo has access to this value)
        MxU32 extendedAddressShift;
    };
}

#endif
