/*
 * $Id: DebugDWARFInfo.h 29787 2013-03-01 10:40:01Z brifol01 $
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

#ifndef DEBUGDWARFINFO_H
#define DEBUGDWARFINFO_H

#include "MxTypes.h"

#include <string>
#include <vector>
#include <set>
#include <map>

#include "Dwarf2Constants.h"
#include "ReferenceCounting.h"

using namespace std;

namespace DebugInfoDB
{
    class DWARFInfoDB;
    struct DWARFInfoAttributeSettingContext;

    // simple byte block
    struct DWARFInfoByteBlock
    {
        DWARFInfoByteBlock(const MxU8 *block_, MxU32 len_): block(block_), len(len_) {}
        DWARFInfoByteBlock(): block(0), len(0) {}
        const MxU8 *block;
        MxU32 len;
        vector<MxU8> vect() const { return vector<MxU8>(block, block + len); }
    };


    // location list entry
    struct DWARFInfoLocationListEntry
    {
        MxU64 start;
        MxU64 end;
        MxU64 base;     // base address which needs to be added to start and end if relative == true
        bool relative;  // hint whether this are absolute or relative addresses (the documentation says clearly that these addresses are always relative to base, but many compilers just put absolute addresses in here)
        DWARFInfoByteBlock location; // location expression
    };


    // find location list entry for a specific PC
    // use heuristics to determine whether addresses are relative or absolute (try both)
    // returns 0 if no matching entry is found
    const DWARFInfoLocationListEntry *FindLocationListEntry(MxU64 pc, const vector<DWARFInfoLocationListEntry>& location);


    // ranges entry
    struct DWARFInfoRangesEntry
    {
        DWARFInfoRangesEntry(MxU64 start_ = 0, MxU64 end_ = 0, MxU64 base_ = 0, bool relative_ = false): start(start_), end(end_), base(base_), relative(relative_) {}
        MxU64 start;
        MxU64 end;
        MxU64 base;     // base address which needs to be added to start and end if relative == true
        bool relative;  // hint whether this are absolute or relative addresses (the documentation says clearly that these addresses are always relative to base, but many compilers just put absolute addresses in here)
    };

    // base class for all items in the debug info tree structure
    class DWARFInfoTreeNode: public RCObject
    {
    public:
        enum
        {
            DEFAULT_DW_AT_decl_file = 0xffffffff,
            DEFAULT_DW_AT_decl_line = 0xffffffff,
            DEFAULT_DW_AT_decl_column = 0xffff,
            DEFAULT_DW_AT_start_scope = 0xffffffff
        };

        // constructor and destructor
        DWARFInfoTreeNode():
            tag(0),
            offsetInDebugInfoSection(0),
            locationListOffset(0),
            flags(0),
            rangesOffset(0),
            db(0),
            abbrevCode(0),
            name(""),
            byte_size(0),
            coffMode(false),
            addressTypeSize(4),
            visibility(0),
            decl_file(DEFAULT_DW_AT_decl_file),
            decl_line(DEFAULT_DW_AT_decl_line),
            decl_column(DEFAULT_DW_AT_decl_column),
            accessibility(0),
            declaration(false),
            start_scope(DEFAULT_DW_AT_start_scope)
        {
            hasFlags[0] = hasFlags[1] = hasFlags[2] = 0;
        }

        virtual ~DWARFInfoTreeNode();

        // get children of this node
        const vector<RCPointer<DWARFInfoTreeNode> > &GetChildren() const; // logical constness
        // get children of this node, do not load compilation units
        // (never use this function, always use GetChildren())
        const vector<RCPointer<DWARFInfoTreeNode> > &GetChildrenButDoNotLoadCompilationUnits() const { return children; }
        // add child
        void AddChild(RCPointer<DWARFInfoTreeNode> child);
        // clear children
        void ClearChildren();

        // these functions need to be reimplemented in a derived class
        // (the functions in the derived class must not call the implementation of the base class)
        inline virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        enum { PRF_LIKEREADELF = 1 };
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        void PrintRecursive(MxU32 flags, int level, bool recursive = true) const;

        // check whether a given address is in 'ranges' (or low_pc/high_pc)
        // returns false if no address range specified in this object
        bool IsAddressInRanges(MxU64 address) const;
        // returns true if no address range specified in this object
        bool IsAddressInRangesOrNoRange(MxU64 address) const;
        // returns true is we have at least one address range
        bool HasAddressRange() const { return !GetRanges().empty(); }

        // set TAG attribute
        void SetTag(MxU32 tag_){tag=tag_;}



        // check whether this node has a certain attribute: (only in this node)
        bool HasAttributeNonRecursive(MxU32 attr) const
        {
            if(attr < 96) return (hasFlags[attr >> 5] & (1 << (attr & 31))) != 0;
            else if(attr == DW_AT_MIPS_linkage_name) return (hasFlags[2] & (1 << 31)) != 0;
            else return false;
        }

        // check whether this node has a certain attribute: (also in abtract_origin)
        // (abstract_origin is not followed recursively)
        bool HasAttribute(MxU32 attr) const
        {
            if(HasAttributeNonRecursive(attr))
                return true;
            else if(abstract_origin)
                return abstract_origin->HasAttributeNonRecursive(attr);
            else
                return false;
        }

        // set a 'has' flag for a specific attribute
        void SetAttributeFlag(MxU32 attr)
        {
            if(attr < 96)
                hasFlags[attr >> 5] |= (1 << (attr & 31));
            else if(attr == DW_AT_MIPS_linkage_name)
                hasFlags[2] |= (1 << 31);
        }


    private:
        // this private function is here so it can be inlined
        // return either this object or the abstract_origin if the given attribute is missing in this
        // (abstract_origin is not followed recursively)
        const DWARFInfoTreeNode *GetInstanceContainingAttribute(MxU32 attr) const { if((!HasAttributeNonRecursive(attr)) && abstract_origin) return abstract_origin.GetPtr(); else return this; }
    public:
        // get minimum range start
        MxU64 GetMinimumRangeStart();

        // attribute read functions:
        // attributes present in this base class:
        virtual MxU16 GetVisibility() const { return GetInstanceContainingAttribute(DW_AT_visibility)->visibility; }
        virtual const char *GetName() const { return GetInstanceContainingAttribute(DW_AT_name)->name; }
        virtual MxU16 GetDeclColumn() const { return GetInstanceContainingAttribute(DW_AT_decl_column)->decl_column; }
        virtual MxU32 GetDeclFile() const { return GetInstanceContainingAttribute(DW_AT_decl_file)->decl_file; }
        virtual MxU32 GetDeclLine() const { return GetInstanceContainingAttribute(DW_AT_decl_line)->decl_line; }
        virtual MxU8 GetAccessibility() const { return GetInstanceContainingAttribute(DW_AT_accessibility)->accessibility; }
        virtual bool GetDeclaration() const { return GetInstanceContainingAttribute(DW_AT_declaration)->declaration; }
        virtual const DWARFInfoTreeNode *GetAbstractOrigin() const { return GetInstanceContainingAttribute(DW_AT_abstract_origin)->abstract_origin.GetPtr(); }
        virtual const DWARFInfoTreeNode *GetType() const { return GetInstanceContainingAttribute(DW_AT_type)->type.GetPtr(); }
        virtual MxU32 GetByteSize() const { return GetInstanceContainingAttribute(DW_AT_byte_size)->byte_size; }
        virtual const vector<DWARFInfoRangesEntry>& GetRanges() const { if(ranges.empty() && abstract_origin) return abstract_origin->ranges; else return ranges; }
        virtual vector<DWARFInfoRangesEntry>& GetRanges() { if(ranges.empty() && abstract_origin) return abstract_origin->ranges; else return ranges; }
        // for GetLowPc() please use GetRanges
        // for GetHighPc() please use GetRanges
        virtual MxU32 GetStartScope() const { return GetInstanceContainingAttribute(DW_AT_start_scope)->start_scope; }

        // attributes present in derived classes (just return a default value here)
        virtual const vector<DWARFInfoLocationListEntry>& GetLocation() const { static const vector<DWARFInfoLocationListEntry> l; return l; }
        virtual vector<DWARFInfoLocationListEntry>& GetLocationList()    { static vector<DWARFInfoLocationListEntry> l; return l; }
        virtual vector<DWARFInfoLocationListEntry>& GetFrameBaseList()   { static vector<DWARFInfoLocationListEntry> l; return l; }
        virtual const vector<DWARFInfoLocationListEntry>& GetSegment() const { static const vector<DWARFInfoLocationListEntry> l; return l; }
        virtual MxU64 GetConstValue() const { return 0; }
        virtual const char *GetConstStringValue() const { return 0; }
        virtual bool GetExternal() const { return false; }
        virtual bool GetArtificial() const { return false; }
        virtual const char *GetLinkageName() const { return ""; }
        virtual MxS32 GetBitOffset() const { return 0; }
        virtual MxU32 GetBitSize() const { return 0; }
        virtual MxS32 GetStmtList() const { return 0; }
        virtual MxU32 GetLanguage() const { return 0; }
        virtual const char *GetCompDir() const { return ""; }
        virtual RCPointer<DWARFInfoTreeNode> GetContainingType() const { return 0; }
        virtual MxU32 GetUpperBound() const { return 0; }
        virtual MxU32 GetEncoding() const { return 0; }
        virtual const vector<DWARFInfoLocationListEntry>& GetDataMemberLocation() const { static const vector<DWARFInfoLocationListEntry> l; return l; }
        virtual RCPointer<DWARFInfoTreeNode> GetSpecification() const { return 0; }
        virtual MxU16 GetInline() const { return 0; }
        virtual const char *GetProducer() const { return ""; }
        virtual bool GetPrototyped() const { return 0; }
        virtual MxS32 GetMacroInfo() const { return 0; }
        virtual const vector<DWARFInfoLocationListEntry>& GetFrameBase() const { static const vector<DWARFInfoLocationListEntry> l; return l; }
        virtual MxU8 GetVirtuality() const { return 0; }
        virtual MxU32 GetStrideSize() const { return 0; }
        virtual void SetRangesList( vector<DWARFInfoRangesEntry> ranges_){ranges=ranges_;}

#if 0
        virtual MxU32 GetOrdering() const { return 0; }
        virtual MxU32 GetDiscr() const { return 0; }
        virtual MxU32 GetDiscrValue() const { return 0; }
        virtual MxU32 GetImport() const { return 0; }
        virtual MxU32 GetStringLength() const { return 0; }
        virtual MxU32 GetCommonReference() const { return 0; }
        virtual MxU32 GetDefaultValue() const { return 0; }
        virtual MxU32 GetIsOptional() const { return 0; }
        virtual MxU32 GetLowerBound() const { return 0; }
        virtual MxU32 GetReturnAddr() const { return 0; }
        virtual MxU32 GetAddressClass() const { return 0; }
        virtual MxU32 GetBaseTypes() const { return 0; }
        virtual MxU32 GetCallingConvention() const { return 0; }
        virtual MxU32 GetCount() const { return 0; }
        virtual MxU32 GetDiscrList() const { return 0; }
        virtual MxU32 GetFriend() const { return 0; }
        virtual MxU32 GetIdentifierCase() const { return 0; }
        virtual MxU32 GetNamelistItem() const { return 0; }
        virtual MxU32 GetPriority() const { return 0; }
        virtual MxU32 GetStaticLink() const { return 0; }
        virtual MxU32 GetUseLocation() const { return 0; }
        virtual MxU32 GetVariableParameter() const { return 0; }
        virtual MxU32 GetVtableElemLocation() const { return 0; }
        virtual MxU32 GetAssociated() const { return 0; }
        virtual MxU32 GetDataLocation() const { return 0; }
        virtual MxU32 GetStride() const { return 0; }
        virtual MxU32 GetEntryPc() const { return 0; }
        virtual MxU32 GetUseUtf8() const { return 0; }
        virtual MxU32 GetExtension() const { return 0; }
        virtual MxU32 GetTrampoline() const { return 0; }
        virtual MxU32 GetCallColumn() const { return 0; }
        virtual MxU32 GetCallFile() const { return 0; }
        virtual MxU32 GetCallLine() const { return 0; }
        virtual MxU32 GetDescription() const { return 0; }
#endif

    protected:
        // helpers used by SetAttribute()
        inline const char * ReadStringValue   (MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        inline MxU64        ReadIntValue      (MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        inline DWARFInfoByteBlock ReadBlockValue(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        inline void         ReadReferenceValue(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context, RCPointer<DWARFInfoTreeNode> *referenceToResolve);
        // read a location expression or a location list
        // a simple location expression (provided as form=block) will result in a location list with a single entry having the start and end addresses set to 0..MAXADDR
        inline vector<DWARFInfoLocationListEntry> ReadLocationValue(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        inline vector<DWARFInfoRangesEntry> ReadRangesValue(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        // printing helpers
        string PrintReference(const RCPointer<DWARFInfoTreeNode>& ref) const;
        void PrintLocation(const string& prefix, const string& attr, const vector<DWARFInfoLocationListEntry>& locationList) const;

    public:
        // public data
        MxU32 tag;                                      // one of the DW_TAG_* constants
        RCPointer<DWARFInfoTreeNode> parent;            // pointer to parent node (NULL means: this is the root node)
        MxU32 offsetInDebugInfoSection;                 // offset of this node in debug_info section, for printout and references
        MxU32 locationListOffset;                       // offset in debug_loc section, only used for readelf printout
        MxU32 flags;                                    // misc flags:
        enum { REFERENCE_IS_ABSOLUTE = (1 << 0), CHILDREN_NOT_FULLY_LOADED = (1 << 1) };
        MxU32 rangesOffset;                             // offset in debug_ranges section, only used for readelf printout
        DWARFInfoDB *db;                                // pointer to main debug info class
        MxU32 abbrevCode;                               // only used for readelf printout
        const char *name;                               // value of DW_AT_name attribute (if present)
        RCPointer<DWARFInfoTreeNode> type;              // value of DW_AT_type attribute (if present)
        MxU32 byte_size;                                // value of DW_AT_byte_size attribute (if present)
        bool  coffMode;                                 // 'true', if DWARF structures were generated from COFF origin
        MxU32 addressTypeSize;                          // size of addresses, pointers

    private:
        // private data
        MxU32 hasFlags[3];                              // flags which indicate which attributes are present
        vector<RCPointer<DWARFInfoTreeNode> > children; // children


    protected:
        // some attributes are in the base class since they are common to a lot of debug entry types
        MxU32 visibility;                               // value of DW_AT_visibility attribute (if present)
        MxU32 decl_file;                                // value of DW_AT_decl_file attribute (if present)
        MxU32 decl_line;                                // value of DW_AT_decl_line attribute (if present)
        MxU16 decl_column;                              // value of DW_AT_decl_column attribute (if present)
        MxU8 accessibility;                             // value of DW_AT_accessibility attribute (if present)
        bool declaration:1;                             // value of DW_AT_declaration attribute (if present)
        RCPointer<DWARFInfoTreeNode> abstract_origin;   // value of DW_AT_abstract_origin attribute (if present)
        vector<DWARFInfoRangesEntry> ranges;            // value of DW_AT_ranges attribute (if present), or of low_pc/high_pc attribute
        MxU32 start_scope;                              // value of DW_AT_start_scope attribute (if present)
    };


    // unresolved references during parsing of the .debug_info section
    struct DWARFInfoUnresolvedReference
    {
        RCPointer<DWARFInfoTreeNode> *referenceToResolve;
        MxU32 targetOffsetInDebugInfoSection;
    };


    // attribute setting context
    struct DWARFInfoAttributeSettingContext
    {
        vector<DWARFInfoUnresolvedReference> unresolvedReferences;
        const MxU8 *compilation_unit_end;
        MxU32 offsetOfCompilationUnitInDebugInfoSection;
        MxU64 baseAddressOfCompilationUnit; // base address of the current compilation unit
        MxU32 version; // DWARF version (2 or 3 or so)
    };

    // simplify the declaration of member functions which automatically access the abstract_origin if the attribute is missing in the current instance
#define GetAttributeAbstractOrigin(cattr,attr,class,rtype) \
        rtype Get##cattr() const { if((!HasAttributeNonRecursive(DW_AT_##attr)) && abstract_origin && dynamic_cast<const TreeNode_DW_TAG_##class*>(abstract_origin.GetPtr())) \
                return reinterpret_cast<const TreeNode_DW_TAG_##class*>(abstract_origin.GetPtr())->attr; else return attr; }

    // DW_TAG_compile_unit
    class TreeNode_DW_TAG_compile_unit: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_compile_unit(): comp_dir(""), producer(""), language(0), macro_info(-1), stmt_list(-1), compilation_unit_start(0), compilation_unit_end(0) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        const char *GetCompDir() const { return comp_dir; }
        const char *GetProducer() const { return producer; }
        MxU32 GetLanguage() const { return language; }
        MxS32 GetMacroInfo() const { return macro_info; }
        MxS32 GetStmtList() const { return stmt_list; }

        // get/set the offset/size of the outer compilation unit (not compile_unit node)
        MxU32 GetCompilationUnitStart() const { return compilation_unit_start; }
        MxU32 GetCompilationUnitEnd  () const { return compilation_unit_end  ; }
        void  SetCompilationUnitStart(MxU32 start) { compilation_unit_start = start; }
        void  SetCompilationUnitEnd  (MxU32 end  ) { compilation_unit_end   = end  ; }

    private:
        // private data
        const char *comp_dir;
        const char *producer;
        MxU32 language;
        MxS32 macro_info;
        MxS32 stmt_list;

        MxU32 compilation_unit_start;
        MxU32 compilation_unit_end;
    };

    // DW_TAG_partial_unit
    class TreeNode_DW_TAG_partial_unit :
        public TreeNode_DW_TAG_compile_unit
    {
    public:
        TreeNode_DW_TAG_partial_unit() :
            TreeNode_DW_TAG_compile_unit()
        {
        }
    };

    // DW_TAG_base_type
    class TreeNode_DW_TAG_base_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_base_type(): bit_size(0),bit_offset(-1),  encoding(0) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        MxS32 GetBitOffset() const { return bit_offset; }
        void  SetBitOffset(MxS32 bit_offset_){bit_offset=bit_offset_; }
        MxU32 GetBitSize() const { return bit_size; }
//      void  SetBitSize() (MxU32 bit_size_){bit_size=bit_size_;}
        MxU32 GetEncoding() const { return encoding; }
        MxU32 bit_size;
        void  SetEncoding(MxU32 encoding_)  { encoding=encoding_;}

    private:
        // private data
        MxS32 bit_offset;
        MxU32 encoding;
    };

    // DW_TAG_enumeration_type
    class TreeNode_DW_TAG_enumeration_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_enumeration_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };

    // DW_TAG_enumerator
    class TreeNode_DW_TAG_enumerator: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_enumerator(): const_value(0) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        MxU64 GetConstValue() const { return const_value; }

    private:
        // private data
        MxU64 const_value;
    };

    // DW_TAG_typedef
    class TreeNode_DW_TAG_typedef: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_typedef() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };

    // DW_TAG_array_type
    class TreeNode_DW_TAG_array_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_array_type(): stride_size(0) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        GetAttributeAbstractOrigin(StrideSize,stride_size,array_type,MxU32);

        virtual MxU32 GetByteSize() const;

    private:
        // private data
        MxU32 stride_size;
    };

    // DW_TAG_subrange_type
    class TreeNode_DW_TAG_subrange_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_subrange_type(): upper_bound(0) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        GetAttributeAbstractOrigin(UpperBound,upper_bound,subrange_type,MxU32);

    private:
        // private data
        MxU32 upper_bound;
    };

    // DW_TAG_structure_type
    class TreeNode_DW_TAG_structure_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_structure_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        GetAttributeAbstractOrigin(ContainingType,containing_type,structure_type,RCPointer<DWARFInfoTreeNode>);
        GetAttributeAbstractOrigin(Specification,specification,structure_type,RCPointer<DWARFInfoTreeNode>);

    private:
        // private data
        RCPointer<DWARFInfoTreeNode> containing_type;
        RCPointer<DWARFInfoTreeNode> specification;
    };

    // DW_TAG_union_type
    class TreeNode_DW_TAG_union_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_union_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        GetAttributeAbstractOrigin(ContainingType,containing_type,union_type,RCPointer<DWARFInfoTreeNode>);
        GetAttributeAbstractOrigin(Specification,specification,union_type,RCPointer<DWARFInfoTreeNode>);

    private:
        // private data
        RCPointer<DWARFInfoTreeNode> containing_type;
        RCPointer<DWARFInfoTreeNode> specification;
    };

    // DW_TAG_pointer_type
    class TreeNode_DW_TAG_pointer_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_pointer_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };

    // DW_TAG_const_type
    class TreeNode_DW_TAG_const_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_const_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };

    // DW_TAG_reference_type
    class TreeNode_DW_TAG_reference_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_reference_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };

    // DW_TAG_volatile_type
    class TreeNode_DW_TAG_volatile_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_volatile_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };

    // DW_TAG_unspecified_parameters
    class TreeNode_DW_TAG_unspecified_parameters: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_unspecified_parameters() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };

    // DW_TAG_label
    class TreeNode_DW_TAG_label: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_label() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };

    // DW_TAG_member
    class TreeNode_DW_TAG_member: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_member(): bit_offset(-1), bit_size(0), artificial(false) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        const vector<DWARFInfoLocationListEntry>& GetDataMemberLocation() const { return data_member_location; }
        MxS32 GetBitOffset() const { return bit_offset; }
        MxU32 GetBitSize() const { return bit_size; }
        bool GetArtificial() const { return artificial; }

    private:
        // private data
        vector<DWARFInfoLocationListEntry> data_member_location;
        MxS32 bit_offset;
        MxU32 bit_size;
        bool artificial;
    };

    // DW_TAG_inheritance
    class TreeNode_DW_TAG_inheritance: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_inheritance():virtuality(0) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        const vector<DWARFInfoLocationListEntry>& GetDataMemberLocation() const { return data_member_location; }
        MxU8 GetVirtuality() const { return virtuality; }

    private:
        // private data
        vector<DWARFInfoLocationListEntry> data_member_location;
        MxU32 virtuality;
    };

    // DW_TAG_variable
    class TreeNode_DW_TAG_variable: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_variable() :
            MIPS_linkage_name(""),
            const_value(0),
            const_string_value(0),
            external(false),
            artificial(false)
        {}

        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        GetAttributeAbstractOrigin(Location,location,variable,const vector<DWARFInfoLocationListEntry>&);
        GetAttributeAbstractOrigin(Segment,segment,variable,const vector<DWARFInfoLocationListEntry>&);
        GetAttributeAbstractOrigin(LinkageName,MIPS_linkage_name,variable,const char *);
        GetAttributeAbstractOrigin(ConstValue,const_value,variable,MxU64);
        GetAttributeAbstractOrigin(External,external,variable,bool);
        GetAttributeAbstractOrigin(Artificial,artificial,variable,bool);
        virtual vector<DWARFInfoLocationListEntry>& GetLocationList() {return location; }
        virtual void SetLocationList(vector<DWARFInfoLocationListEntry> list){location=list;}
        virtual const char *GetConstStringValue() const { return const_string_value; }

    private:
        // private data
        vector<DWARFInfoLocationListEntry> location;
        vector<DWARFInfoLocationListEntry> segment;
        const char *MIPS_linkage_name;
        MxU64 const_value;
        const char *const_string_value;
        bool external:1;
        bool artificial:1;
    };

    // DW_TAG_formal_parameter
    class TreeNode_DW_TAG_formal_parameter: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_formal_parameter():artificial(false) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        GetAttributeAbstractOrigin(Location,location,formal_parameter,const vector<DWARFInfoLocationListEntry>&);
        GetAttributeAbstractOrigin(Segment,segment,formal_parameter,const vector<DWARFInfoLocationListEntry>&);
        GetAttributeAbstractOrigin(Artificial,artificial,formal_parameter,bool);

    private:
        // private data
        vector<DWARFInfoLocationListEntry> location;
        vector<DWARFInfoLocationListEntry> segment;
        bool artificial:1;
    };

    // DW_TAG_subprogram
    class TreeNode_DW_TAG_subprogram: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_subprogram():MIPS_linkage_name(""), inlined(0), external(false), prototyped(false), artificial(false), virtuality(0) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        GetAttributeAbstractOrigin(FrameBase,frame_base,subprogram,const vector<DWARFInfoLocationListEntry>&);
        GetAttributeAbstractOrigin(Artificial,artificial,subprogram,bool);
        GetAttributeAbstractOrigin(External,external,subprogram,bool);
        GetAttributeAbstractOrigin(Prototyped,prototyped,subprogram,bool);
        GetAttributeAbstractOrigin(LinkageName,MIPS_linkage_name,subprogram,const char *);
        #define inline inlined
        GetAttributeAbstractOrigin(Inline,inline,subprogram,MxU16);
        #undef inline
        GetAttributeAbstractOrigin(Virtuality,virtuality,subprogram,MxU8);
        GetAttributeAbstractOrigin(VtableElemLocation,vtable_elem_location,subprogram,const vector<DWARFInfoLocationListEntry>&);
        GetAttributeAbstractOrigin(ContainingType,containing_type,subprogram,RCPointer<DWARFInfoTreeNode>);
        GetAttributeAbstractOrigin(Specification,specification,subprogram,RCPointer<DWARFInfoTreeNode>);

        vector<DWARFInfoLocationListEntry> &GetFrameBaseList(){return frame_base;}
        void SetFrameBaseList(vector<DWARFInfoLocationListEntry> list_){frame_base=list_;}
    private:
        // private data
        vector<DWARFInfoLocationListEntry> frame_base;
        const char *MIPS_linkage_name;
        MxU16 inlined;
        bool external:1;
        bool prototyped:1;
        bool artificial:1;
        MxU8 virtuality;
        vector<DWARFInfoLocationListEntry> vtable_elem_location;
        RCPointer<DWARFInfoTreeNode> containing_type;
        RCPointer<DWARFInfoTreeNode> specification;
    };

    // DW_TAG_subroutine_type
    class TreeNode_DW_TAG_subroutine_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_subroutine_type():prototyped(false) {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;

        GetAttributeAbstractOrigin(Prototyped,prototyped,subroutine_type,bool);

    private:
        // private data
        bool prototyped:1;
    };

    // DW_TAG_lexical_block
    class TreeNode_DW_TAG_lexical_block: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_lexical_block() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };


    // DW_TAG_inlined_subroutine
    class TreeNode_DW_TAG_inlined_subroutine: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_inlined_subroutine() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };


    // DW_TAG_namespace
    class TreeNode_DW_TAG_namespace: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_namespace() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };


    // DW_TAG_class_type
    class TreeNode_DW_TAG_class_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_class_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };


    // DW_TAG_template_type_param
    class TreeNode_DW_TAG_template_type_param: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_template_type_param() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };


    // DW_TAG_ptr_to_member_type
    class TreeNode_DW_TAG_ptr_to_member_type: public DWARFInfoTreeNode
    {
    public:
        TreeNode_DW_TAG_ptr_to_member_type() {}
        virtual void SetAttribute(MxU32 attribute, MxU32 form, const MxU8 *&debug_info, DWARFInfoAttributeSettingContext *context);
        virtual void PrintTAGSpecificAttributes(MxU32 flags, const string& prefix) const;
    };


    // main DebugInfo class
    class DWARFInfoDB
    {
    public:
        // public methods
        DWARFInfoDB();
        ~DWARFInfoDB();
        void Clear();
        void LoadDWARF(const MxU8 debug_info[], MxU32 debug_info_size,
                       const MxU8 debug_abbrev[], MxU32 debug_abbrev_size,
                       const MxU8 debug_loc[], MxU32 debug_loc_size,
                       const MxU8 debug_str[], MxU32 debug_str_size,
                       const MxU8 debug_ranges[], MxU32 debug_ranges_size,
                       bool isBigEndian_, MxU32 addressTypeSize_, bool onlyCompilationUnits = false);
        void PrintRecursive(MxU32 flags);
        void SetVerbose(bool verbose);
        void SetQuiet(bool quiet);
        // main API function
        DWARFInfoTreeNode *GetRoot() { return &root; }
        const DWARFInfoTreeNode *GetRoot() const { return &root; }
        // get endianness and address type size
        bool IsBigEndian() const { return isBigEndian; }
        MxU32 GetAddressTypeSize() const { return addressTypeSize; }
        void DumpDebugLoc();

        // convenience function which returns the 'producer' field of the first compilation unit found (or empty string if no compilation unit contains a non-empty producer entry)
        // (parameter should never be specified)
        const char *GetProducer(const DWARFInfoTreeNode *node = 0) const;
        // get a list of all procducers separated by linefeeds, format 'Producer: $producer\n'
        // (reset by LoadDWARF())
        const string& GetProducers() const { return producers; }
        // get human readable info about loaded info (including producers)
        // (reset by LoadDWARF())
        string GetHRInfo() const;
        // get number of compilation units currently being loaded (they are loaded on demand)
        MxU32 GetNumberOfCompilationUnitsLoaded() const { return numCompilationUnitsLoaded; }
        // get number of total compilation units
        MxU32 GetNumberOfCompilationUnitsTotal() const { return numCompilationUnitsTotal; }
        // force load all compilation units
        // (this may take very long for large amounts of debug info/1 minuet for 45MB of data, data will also be expanded by a factor of 15!)
        // (never use this function)
        void ForceLoadAllCompilationUnits();
        // get all (top level) compilation units
        const vector<RCPointer<DWARFInfoTreeNode> >& GetCompilationUnits();

        // get the value of an enum symbol regardless of scope
        // Note: We do not want to trigger loading of all compilation units if there are so many that this would take
        // a minute to load, so we only look up the symbols in the units we already have loaded anyway. This means that
        // this function behaves differently even when called with the same parameters, depending on what other functions
        // have already been called on this db. The effect is that this works well for requests which are to some degree
        // local enough to the modules which are currectly being debugged.
        bool GetEnumSymbolValue(const char *name, MxU64 &uval, MxS64 &sval, const DWARFInfoTreeNode *node = 0) const;
        // get the outermost subprogram which contains pc
        const DWARFInfoTreeNode *FindOuterMostSubprogram(MxU64 pc, const DWARFInfoTreeNode *node = 0) const;
        // get the innermost subprogram which contains pc
        const DWARFInfoTreeNode *FindInnerMostSubprogram(MxU64 pc, const DWARFInfoTreeNode *node = 0) const;
        // create a new debug info node (also used by DebugCoffSymbol)
        RCPointer<DWARFInfoTreeNode> CreateTreeNodeForTAG(MxU32 tag, MxU32 offsetInDebugInfo = 0xffffffff);


    private:
        // private data
        DWARFInfoTreeNode root;
        MxU32 addressTypeSize;
        bool isBigEndian:1;
        bool verbose:1;
        bool quiet:1;
        MxU32 version;
        string producers; // reset by LoadDWARF()
        string hrInfo; // reset by LoadDWARF()

        // global context
        const MxU8 *data_debug_info;
        const MxU8 *data_debug_info_end;
        MxU32       data_debug_info_size;
        const MxU8 *data_debug_abbrev;
        const MxU8 *data_debug_abbrev_end;
        MxU32       data_debug_abbrev_size;
        const MxU8 *data_debug_str;
        const MxU8 *data_debug_str_end;
        const MxU8 *data_debug_loc;
        const MxU8 *data_debug_loc_end;
        MxU32       data_debug_loc_size;
        const MxU8 *data_debug_ranges;
        const MxU8 *data_debug_ranges_end;
        // current abbreviation table
        MxU32 abbrevCode2IdxLimit;
        MxU32 *abbrevCode2Idx;
        MxU32 abbrevTableLimit;
        MxU32 abbrevTableSize;
        MxU32 *abbrevTable;
        MxU32 abbrevTableLastBase;
        MxU32 numErroneousLocalVarsRelocated;
        std::set<std::string> producerSet;
        MxU32 numCompilationUnitsLoaded;
        MxU32 numCompilationUnitsTotal;
        MxU32 numTreeNodes;
        std::map<MxU32,DWARFInfoTreeNode *> offset2compileUnitNode; // offset is the byte offset of the inner compile_unit node in the .debug_info section

        // private offset2node cache (used to resolve unresolved references
        class Offset2NodeCache
        {
        public:
            Offset2NodeCache(DWARFInfoDB *db_): compileUnit(0), compileUnitNextIndex(0), offset2node(0), db(db_) {}
            ~Offset2NodeCache() { delete[] offset2node; }
            DWARFInfoTreeNode *Lookup(MxU32 offsetInDebugInfoSection);

        private:
            void InitRecursive(DWARFInfoTreeNode *compileUnit, MxU32 compilationUnitStart);
            TreeNode_DW_TAG_compile_unit *compileUnit;
            MxU32 compileUnitNextIndex;
            DWARFInfoTreeNode **offset2node;
            DWARFInfoDB *db;
        };

        // private helpers:
        inline const MxU8 *copyMemAndAddZeroBytes(const MxU8 *debug_sect, MxU32 size, const char *name, const MxU8 *& endOut);
        void ClearDataPointers();
        void LoadCompilationUnit(MxU32 compilationUnitStart, bool onlyCompileUnits);

        // friend classes
        friend class DWARFInfoTreeNode;
    };

}

#endif
