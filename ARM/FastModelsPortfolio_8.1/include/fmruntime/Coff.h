/*
 * $Id: Coff.h,v 1.1 2005/11/21 10:39:40 aropers Exp $
 *
 * $Author: aropers $
 * $Date: 2005/11/21 10:39:40 $
 * $Revision: 1.1 $
 *
 * Copyright (c) 2005 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */
/** \file
  * COFF V2 constants
  */

#ifndef _Coff_h_
#define _Coff_h_


// These structures represent the 'Archelon' Coff debug format which we currently support.
// perhaps there will be some kind of legacy support for the 'standard' whatsoever formats in
// the future, but as these formats are not properly defined anyhow we stick to the 'Archelon'
// one for the meantime


#define COFF_FILEHDR    struct COFFFileHeader
#define COFF_FILHSZ     sizeof(COFF_FILEHDR)

#define COFF_OPTHDR struct COFFOpthdr
#define COFF_OPTHSZ sizeof(OPTHDR)

#define COFF_SCNHDR struct COFFScnhdr
#define COFF_SCNHSZ sizeof(COFF_SCNHDR)

// Magic Numbers

// ARCHELON
#define ARCH_F_MAGIC        ( (unsigned short) 0xC0FF )
#define ARCH_O_MAGIC        ( (short) 0xFFFF )

// Archelon tool version
#define O_VSTAMP            ( (short) 0xAC05 )

// Flags

#define COFF_F_RELFLAG      0x1         // The Coff File does not contain relocation info
#define COFF_F_EXEC         0x2         // The Coff File is executable
#define COFF_F_LNNO         0x4         // Line numbers have been stripped
#define COFF_F_LSYMS            0x8         // Local Symbols have been stripped
// For Archelon COFF format
#define COFF_F_AEHDRS       0x4000      /* Archelon Extended headers */
#define COFF_F_AESYMS       0x8000      /* Archelon Extended symbols */

// s_flags bits

#define COFF_STYP_REG       0x00  // regular section, either text, data, bss, info or lib type
#define COFF_STYP_DSECT     0x01  // a dummy section type created by the assembler
#define COFF_STYP_NOLOAD    0x02  // "noload" section: allocated, relocated, not loaded
#define COFF_STYP_GROUP     0x04  // "grouped" section: formed of input sections
#define COFF_STYP_PAD       0x08  // Aligmnet spacing between regular sections: not allocated, not relocated, loaded
#define COFF_STYP_COPY      0x10  // "copy" section: for decision function used by field update
                              // not allocated, not relocated, loaded
                              // reloc & lineno entries processed normally

#define COFF_STYP_TEXT      0x20  // Text section: allocated, relocated and loaded
#define COFF_STYP_DATA      0x40  // Data section: allocated, relocated and loaded
#define COFF_STYP_BSS       0x80  // Bss sections are only allocated
#define COFF_STYP_ABS       0x100 // section contains abs only
#define COFF_STYP_INFO      0x200 // comment section : not allocated not relocated, not loaded
#define COFF_STYP_OVER      0x400 // overlay section : relocated not allocated or loaded
#define COFF_STYP_LIB       0x800 // for .lib section : same as INFO
#define COFF_STYP_VENDOR        0x1000// vendor-specific section

struct COFFFileHeader
{
    unsigned short  f_magic;    // Environment identifying version number
    unsigned short  f_nscns;    // Number of Sections
    long            f_timdat;   // Unix format time stamp
    long            f_symptr;   // File pointer to start of symbol table
    long            f_nsyms;    // Number of symbol table entries
    unsigned short  f_opthdr;   // Size of optional header in bytes
    unsigned short  f_flags;    // File status flags
};


// standard COFF optional header

struct COFFOpthdr {
    short magic;        // Runtime status magic number
    short vstamp;       // Optinal version stamp
    long  tsize;        // size in bytes of text
    long  dsize;        // size in bytes of initialized data
    long  bsize;        // size in bytes of uninitialized data
    long  entry;        // starting address of program execution
    long  text_start;   // Runtime startung address of machine code
    long  data_start;   // Runtime startung address of program data
};


// standard COFF section headers

struct COFFScnhdr {
    char            s_name[8]; // Section's name
    long            s_paddr;   // Physical address
    long            s_vaddr;   // Virtual address
    long            s_size;    // Sections's size in bytes
    long            s_scnptr;  // Filepointer to sections raw data
    long            s_relptr;  // Filepointer to sections relocation address
    long            s_lnnoptr; // Filepointer to sections line numbers
    unsigned short  s_nreloc;  // Number of relocation entries
    unsigned short  s_nlnno;   // Number of line number entries
    long            s_flags;   // Section type and content flag
};




// ================ Archelon headers ================

// Archelon optional header

#define COFF_TARGET_SZ      8

struct COFFAopthdr {
    struct COFFOpthdr   ao_header;      // std COFF opt hdr stuff
    char                ao_target[COFF_TARGET_SZ];  // target id
    unsigned long       ao_numaux;      // number of aux entries
};

#define COFF_AOPTHDR    struct COFFAopthdr
#define COFF_AOPTHSZ    sizeof(COFF_AOPTHDR)

/* Archelon section headers */
/* we write one for each section, describing those features */
/* of a section not included in the COFF section header. */

struct COFFAscnhdr {
    unsigned short      as_bits;        // bits per word
    unsigned short      as_bytes;       // bytes per word
    unsigned char       as_inc;         // location counter increment
    unsigned char       as_memtype;     // memory type for this sect
    unsigned long       as_entry;       // entry address this sect
    unsigned long       as_numaux;      // number of aux entries
};

#define COFF_ASCNHDR    struct COFFAscnhdr
#define COFF_ASCNHSZ    sizeof(COFF_ASCNHDR)


// ================ Archelon auxiliary entries ================

struct COFF_file_aux_entry
{
    unsigned char       buffer[COFF_AOPTHSZ];       // aux entry for entire file
};

struct COFF_section_aux_entry
{
    unsigned char       buffer[COFF_ASCNHSZ]; // aux entry for a single section
};


// ================ symbol table entries ================

// symbol table entry

#define COFF_SYMNMLEN           8       /* max chars in a symbol name */
#define COFF_FILNMLEN           14      /* max chars in a file name */
#define COFF_DIMNUM             4       /* max array dims in aux entry */

#define COFF_ARCH_SYMENT struct arch_syment
#define COFF_ARCH_SYMESZ sizeof(COFF_ARCH_SYMENT)

struct COFFArchSyment {
    union {
        char        _n_name[COFF_SYMNMLEN]; // name, or ... */
        struct {
            long    _n_zeroes;          // if _n_zeroes == 0, then
            long    _n_offset;          // offset in string table
        } _n_n;
        char        *_n_nptr[2];    // offset use declaration
    } _n;
    long            n_value;        // symbol's value
    unsigned long   n_type;         // symbol's type and derived type
    short           n_scnum;        // symbol's section number
    char            n_sclass;       // symbol's storage class
    char            n_numaux;       // number of auxiliary entries
};


struct COFFStdSyment
{
    union {
        char        _n_name[COFF_SYMNMLEN]; /* name, or ... */
        struct {
            long    _n_zeroes;          /* if _n_zeroes == 0, then */
            long    _n_offset;          /* offset in string table */
        } _n_n;
        char        *_n_nptr[2];    /* offset use declaration */
    } _n;
    long            n_value;        /* symbol's value */
    short           n_scnum;        /* symbol's section number */
    unsigned short  n_type;         /* symbol's type and derived type */
    char            n_sclass;       /* symbol's storage class */
    char            n_numaux;       /* number of auxiliary entries */
    unsigned short  n_not_used;     /* two unused bytes ! */
};

#define COFF_n_name     _n._n_name
#define COFF_n_nptr     _n._n_nptr[1]
#define COFF_n_zeroes   _n._n_n._n_zeroes
#define COFF_n_offset   _n._n_n._n_offset

/*
 * just for a while ...
 */

#define COFF_SYMENT COFF_ARCH_SYMENT
#define COFF_SYMESZ sizeof(COFF_SYMENT)


/*
 * CSE (COFF Symbol Entry) macros
 * for accessing any field of a SYMENT
 */
#define COFF_CSE_name   COFF_n_name
#define COFF_CSE_zeroes COFF_n_zeroes
#define COFF_CSE_offset COFF_n_offset
#define COFF_CSE_nptr   COFF_n_nptr
#define COFF_CSE_value  COFF_n_value
#define COFF_CSE_type   COFF_n_type
#define COFF_CSE_scnum  COFF_n_scnum
#define COFF_CSE_sclass COFF_n_sclass
#define COFF_CSE_numaux COFF_n_numaux

// Clear an entire COFF_SYMENT
#define COFF_clear_CSE(x)   (void) memset( (void *) (x), 0, COFF_SYMESZ )
#define COFF_EF     ".ef"

/* Archelon COFF type packing constants */

#define COFF_ARCH_BT_BITS           5       // basic type bits
#define COFF_ARCH_DT_BITS           3       // derived type bits
#define COFF_ARCH_MAX_DT            9       // max derived types

#define COFF_ARCH_BT_MASK       \
    ( ( 1 << COFF_ARCH_BT_BITS ) - 1 )

#define COFF_ARCH_DT_MASK       \
    ( ( ( 1 << COFF_ARCH_DT_BITS ) - 1 ) << COFF_ARCH_BT_BITS )


// Standard COFF type packing constants

#define STD_BT_BITS             4       // basic type bits
#define STD_DT_BITS             2       // derived type bits
#define STD_MAX_DT              6       // max derived types

#define COFF_STD_BT_MASK        \
    ( ( 1 << STD_BT_BITS ) - 1 )

#define COFF_STD_DT_MASK        \
    ( ( ( 1 << STD_DT_BITS ) - 1 ) << COFF_STD_BT_BITS )

// Obsolescent type packing constants

#define COFF_N_BT_BITS              5       // basic type bits
#define COFF_N_DT_BITS              3       // derived type bits
#define COFF_MAX_DERIVED_TYPES      9

#define COFF_N_BTMASK       ( ( 1 << COFF_N_BT_BITS ) - 1 )
#define COFF_N_DTMASK       ( ( ( 1 << COFF_N_DT_BITS ) - 1 ) << COFF_N_BT_BITS )


// Archelon symbol-manipulation macros

// basic type of x
#define COFF_BTYPE(x)           ((x) & COFF_N_BTMASK)
#define COFF_DTYPE(x)           ((x) & COFF_N_DTMASK)

// is x a function?
#define COFF_IS_FUNCTION(x)     ((COFF_DTYPE(x)) == (COFF_DT_FCN << COFF_N_BT_BITS))

// is x an array?
#define COFF_IS_ARRAY(x)            ((COFF_DTYPE(x)) == (COFF_DT_ARY << COFF_N_BT_BITS))

// is x a pointer to the code memory ?
#define COFF_IS_CODEPTR(x)      ((COFF_DTYPE(x)) == (COFF_DT_CODEPTR << COFF_N_BT_BITS))

// is x a pointer to the first data memory ?
#define COFF_IS_PTR1(x)         ((COFF_DTYPE(x)) == (COFF_DT_PTR << COFF_N_BT_BITS))

// is x a pointer to the second data memory ?
#define COFF_IS_PTR2(x)         ((COFF_DTYPE(x)) == (COFF_DT_PTR2 << COFF_N_BT_BITS))

// is x a pointer to the third data memory ?
#define COFF_IS_PTR3(x)         ((COFF_DTYPE(x)) == (COFF_DT_PTR3 << COFF_N_BT_BITS))

// is x a pointer to the fourth data memory ?
#define COFF_IS_PTR4(x)         ((COFF_DTYPE(x)) == (COFF_DT_PTR4 << COFF_N_BT_BITS))

// is x any kind of a pointer?
#define COFF_IS_POINTER(x)      ( COFF_IS_PTR1(x) || COFF_IS_PTR2(x) || COFF_IS_PTR3(x) \
                                  || COFF_IS_PTR4(x)|| COFF_IS_CODEPTR(x) )

// arbitrary section titles for COFF sections
// these names are used in the "extra" symbols
// which are inserted by the linker for each module


#define COFF_NAMED_SECTIONS     8
#define COFF_SEC_0_TITLE            ".mem_0"
#define COFF_SEC_1_TITLE            ".mem_1"
#define COFF_SEC_2_TITLE            ".mem_2"
#define COFF_SEC_3_TITLE            ".mem_3"
#define COFF_SEC_4_TITLE            ".mem_4"
#define COFF_SEC_5_TITLE            ".mem_5"
#define COFF_SEC_6_TITLE            ".mem_6"
#define COFF_SEC_7_TITLE            ".mem_7"

/* auxiliary entry */

union COFFAuxent {
    struct {
        long                    x_tagndx;   // str, un or enum tag index
        union {
            struct {
                unsigned short  x_lnno;     // declaration line number
                unsigned short  x_size;     // str, un or array size
            } x_lnsz;
            long                x_fsize;    // size of function
        } x_misc;
        union {
            struct {                        // if ISFCN, tag or .bb
                long            x_lnnoptr;  // ptr to function line #
                long            x_endndx;   // entry ndx past block end
            } x_fcn;
            struct {                        // if ISARY, up to 4 dimen.
                unsigned short  x_dimen[COFF_DIMNUM];
            } x_ary;
        } x_fcnary;
        unsigned short          x_tvndx;    // tv index
    } x_sym;
    struct {
        char                    x_fname[COFF_FILNMLEN];
    } x_file;
    struct {
        long                    x_scnlen;   // section length
        unsigned short          x_nreloc;   // number of reloc entries
        unsigned short          x_nlinno;   // number of line numbers
    } x_scn;
    struct {
        long                    x_tvfill;   // tv fill value
        unsigned short          x_tvlen;    // length of .tv
        unsigned short          x_tvran[2]; // tv range
    } x_tv;
    struct {
        unsigned long           x_part1;
        unsigned long           x_part2;
        unsigned long           x_location;
        unsigned long           x_ts;
    } x_part;
    struct {
        unsigned long           x_pad[5];   // not used
    } x_not_used;
};

#define COFF_AUXENT union COFFAuxent
#define COFF_AUXESZ sizeof(COFF_AUXENT)



// CSA (COFF Symbol Auxiliary) macros
// for accessing any field of an AUXENT
#define COFF_CSA_tagndx     x_sym.x_tagndx
#define COFF_CSA_lnno       x_sym.x_misc.x_lnsz.x_lnno
#define COFF_CSA_size       x_sym.x_misc.x_lnsz.x_size
#define COFF_CSA_fsize      x_sym.x_misc.x_fsize
/* if fname in string table fword0 == 0, fword1 -> string tbl. rpg 971217 */
#define COFF_CSA_fword0     x_part.x_part1
#define COFF_CSA_fword1     x_part.x_part2
#define COFF_CSA_lnnoptr        x_sym.x_fcnary.x_fcn.x_lnnoptr
#define COFF_CSA_endndx     x_sym.x_fcnary.x_fcn.x_endndx
#define COFF_CSA_dimen      x_sym.x_fcnary.x_ary.x_dimen
#define COFF_CSA_tvndx      x_sym.x_tvndx
#define COFF_CSA_fname      x_file.x_fname
#define COFF_CSA_scnlen     x_scn.x_scnlen
#define COFF_CSA_nreloc     x_scn.x_nreloc
#define COFF_CSA_nlinno     x_scn.x_nlinno
#define COFF_CSA_tvfill     x_tv.x_tvfill
#define COFF_CSA_tvlen      x_tv.x_tvlen
#define COFF_CSA_tvran      x_tv.x_tvran
#define COFF_CSA_ts         x_part.x_ts
#define COFF_CSA_location   x_part.x_location

/* or to clear an entire AUXENT */
#define COFF_CLEAR_CSA(x)   (void) memset( (void *) (x), 0, COFF_AUXESZ )

/* ================ relocation and line number entries ================ */

/* relocation entries */

struct CoffReloc {
    long            r_vaddr;  // address of reference
    long            r_symndx; // index into symbol table
    unsigned short  r_type;   //  relocation type
};

#define COFF_RELOC  struct CoffReloc
#define COFF_RELSZ  sizeof(COFF_RELOC)


// CRI (COFF Reloc Info) macros
// for accessing any field of a RELOC

#define COFF_CRI_VADDR      r_vaddr
#define COFF_CRI_SYMNDX     r_symndx
#define COFF_CRI_TYPE       r_type

/* line number entries */

struct COFFLineno {
    union {
        long        l_symndx;       // index into symbol table
        long        l_paddr;        // or a physical address
    } l_addr;
    unsigned short  l_lnno;         // line number : if 0 use l_symndx
};

#define COFF_LINENO struct COFFLineno
#define COFF_LINESZ 6       // {unpadded} sizeof(LINENO)
#define COFF_LNNO_MASK      0xffff  // max value for l_lnno
#define COFF_LNNO_BITS      16      // number of bits in l_lnno


// CLN (COFF Line Number) macros
// for accessing any field of a LINENO

#define COFF_CLN_symndx     l_addr.l_symndx
#define COFF_CLN_paddr      l_addr.l_paddr
#define COFF_CLN_lnno       l_lnno

#endif // Coff.h
