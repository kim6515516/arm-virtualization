
/*
 * $Id: Elf.h 29787 2013-03-01 10:40:01Z brifol01 $
 *
 * Project:  LISA Simulator Generator
 * $Author: brifol01 $
 * $Date: 2013-03-01 10:40:01 +0000 (Fri, 01 Mar 2013) $
 * $Revision: 29787 $
 *
 * Copyright (c) 2002 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */

/** \file
 * ELF specific defines
 */

#ifndef _ELF_H
#define _ELF_H 1

#include "MxTypes.h"


typedef MxU16 Elf32_Half;
typedef MxU32 Elf32_Word;
typedef MxS32 Elf32_Sword;
typedef MxU32 Elf32_Addr;
typedef MxU32 Elf32_Off;
typedef MxU16 Elf32_Section;

typedef MxU16 Elf64_Half;
typedef MxU32 Elf64_Word;
typedef MxS32 Elf64_Sword;
typedef MxU64 Elf64_Xword;
typedef MxS64 Elf64_Sxword;
typedef MxU64 Elf64_Addr;
typedef MxU64 Elf64_Off;

#define EI_NIDENT (16)

typedef struct
{
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half    e_type;
  Elf32_Half    e_machine;
  Elf32_Word    e_version;
  Elf32_Addr    e_entry;
  Elf32_Off             e_phoff;
  Elf32_Off             e_shoff;
  Elf32_Word    e_flags;
  Elf32_Half    e_ehsize;
  Elf32_Half    e_phentsize;
  Elf32_Half    e_phnum;
  Elf32_Half    e_shentsize;
  Elf32_Half    e_shnum;
  Elf32_Half    e_shstrndx;
} Elf32_Ehdr;

typedef struct
{
  // order of elements matches Elf32_Ehdr
  unsigned char e_ident[EI_NIDENT];
  Elf64_Half    e_type;
  Elf64_Half    e_machine;
  Elf64_Word    e_version;
  Elf64_Addr    e_entry;        // 64
  Elf64_Off             e_phoff;        // 64
  Elf64_Off             e_shoff;        // 64
  Elf64_Word    e_flags;
  Elf64_Half    e_ehsize;
  Elf64_Half    e_phentsize;
  Elf64_Half    e_phnum;
  Elf64_Half    e_shentsize;
  Elf64_Half    e_shnum;
  Elf64_Half    e_shstrndx;
} Elf64_Ehdr;

// e_ident:
#define EI_MAG0         0
#define EI_MAG1         1
#define EI_MAG2         2
#define EI_MAG3         3

#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define EI_CLASS        4
#define ELFCLASSNONE    0
#define ELFCLASS32      1
#define ELFCLASS64      2

#define EI_DATA         5
#define ELFDATANONE     0
#define ELFDATA2LSB     1
#define ELFDATA2MSB     2

#define EI_VERSION      6
#define EV_NONE         0
#define EV_CURRENT      1


#define EI_OSABI        7               /* OS ABI identification */
#define ELFOSABI_NONE           0       /* UNIX System V ABI */
#define ELFOSABI_SYSV           0       /* Alias.  */
#define ELFOSABI_HPUX           1       /* HP-UX */
#define ELFOSABI_NETBSD         2       /* NetBSD.  */
#define ELFOSABI_LINUX          3       /* Linux.  */
#define ELFOSABI_SOLARIS        6       /* Sun Solaris.  */
#define ELFOSABI_AIX            7       /* IBM AIX.  */
#define ELFOSABI_IRIX           8       /* SGI Irix.  */
#define ELFOSABI_FREEBSD        9       /* FreeBSD.  */
#define ELFOSABI_TRU64          10      /* Compaq TRU64 UNIX.  */
#define ELFOSABI_MODESTO        11      /* Novell Modesto.  */
#define ELFOSABI_OPENBSD        12      /* OpenBSD.  */
#define ELFOSABI_ARM            97      /* ARM */
#define ELFOSABI_STANDALONE     255     /* Standalone (embedded) application */

#define EI_ABIVERSION   8               /* ABI version */

// e_type:
#define ET_NONE   0x0000                // no file type
#define ET_REL    0x0001                // relocatable file
#define ET_EXEC   0x0002                // executable file
#define ET_DYN    0x0003                // shared object file
#define ET_CORE   0x0004                // core file (core dump)
#define ET_LOPROC 0xff00                // processor specific (from)
#define ET_HIPROC 0xffff                // processor specific (to)

// e_machine:
// some of the many predefined machine types:
#define EM_NONE     0x0000              // no machine
#define EM_SPARC    0x0002              // SPARC
#define EM_386      0x0003              // Intel 80386
#define EM_68k      0x0004              // Motorola 68000 family
#define EM_88k      0x0005              // Motorola 88000 family
#define EM_MIPS     0x0008              // MIPS RS3000 big-endian
#define EM_PPC      0x0014              // PowerPC
#define EM_PPC64    0x0015              // PowerPC 64 bit
#define EM_ARM      0x0028              // ARM
#define EM_SH       0x002A              // Hitachi SH
#define EM_TRICORE  0x002C              // Infineon Tricore
#define EM_COLDFIRE 0x0034              // Motorola Coldfire
#define EM_PCP      0x0037              // Infineon PCP
#define EM_STARCORE 0x003A              // Motorola Star*Core
#define EM_ST100    0x003C              // STMicroelectronics ST100
#define EM_DLX      0x5aa5              // DLX Processor

// Processor specific flags in header's e_flags field:
#define EF_ARM_HASENTRY 0x02    // entry is valid even if it is zero

// Section header
typedef struct
{
  Elf32_Word    sh_name;
  Elf32_Word    sh_type;
  Elf32_Word    sh_flags;
  Elf32_Addr    sh_addr;
  Elf32_Off             sh_offset;
  Elf32_Word    sh_size;
  Elf32_Word    sh_link;
  Elf32_Word    sh_info;
  Elf32_Word    sh_addralign;
  Elf32_Word    sh_entsize;
} Elf32_Shdr;

typedef struct
{
  // order of elements matches Elf32_Shdr
  Elf64_Word    sh_name;
  Elf64_Word    sh_type;
  Elf64_Xword   sh_flags;       // 64
  Elf64_Addr    sh_addr;        // 64
  Elf64_Off             sh_offset;      // 64
  Elf64_Xword   sh_size;        // 64
  Elf64_Word    sh_link;
  Elf64_Word    sh_info;
  Elf64_Xword   sh_addralign; // 64
  Elf64_Xword   sh_entsize;       // 64
} Elf64_Shdr;


#define SHN_LORESERVE   0xff00
#define SHN_ABS                 0xfff1
#define SHN_COMMON              0xfff2
#define SHN_HIRESERVE   0xffff

#define SHT_NULL         0
#define SHT_PROGBITS 1
#define SHT_SYMTAB       2
#define SHT_STRTAB       3
#define SHT_RELA         4
#define SHT_HASH         5
#define SHT_DYNAMIC      6
#define SHT_NOTE         7
#define SHT_NOBITS       8
#define SHT_REL          9
#define SHT_SHLIB        10
#define SHT_DYNSYM       11

// Vendor specific header types:
#define SHT_MIPS_DWARF 0x7000001e
#define SHT_ARM_ATTR   0x70000003


#define SHF_WRITE            (1 << 0)   /* Writable */
#define SHF_ALLOC            (1 << 1)   /* Occupies memory during execution */
#define SHF_EXECINSTR        (1 << 2)   /* Executable */
#define SHF_MERGE            (1 << 4)   /* Might be merged */
#define SHF_STRINGS          (1 << 5)   /* Contains nul-terminated strings */
#define SHF_INFO_LINK        (1 << 6)   /* sh_info' contains SHT index */
#define SHF_LINK_ORDER       (1 << 7)   /* Preserve order after combining */
#define SHF_OS_NONCONFORMING (1 << 8)   /* Non-standard OS specific handling required */
#define SHF_MASKOS           0x0ff00000 /* OS-specific.  */
#define SHF_MASKPROC         0xf0000000 /* Processor-specific */

// Symbols
typedef struct
{
  Elf32_Word    st_name;
  Elf32_Addr    st_value;
  Elf32_Word    st_size;
  unsigned char st_info;
  unsigned char st_other;
  Elf32_Section st_shndx;
} Elf32_Sym;

typedef struct
{
  // order of elements is different than Elf32_Sym!
  Elf64_Word    st_name;
  unsigned char st_info;
  unsigned char st_other;
  Elf64_Half    st_shndx;
  Elf64_Addr    st_value; // 64
  Elf64_Xword   st_size;  // 64
} Elf64_Sym;

#define SHN_UNDEF       0

#define ELF32_ST_BIND(val)              (((unsigned char) (val)) >> 4)
#define ELF32_ST_TYPE(val)              ((val) & 0xf)
#define ELF32_ST_INFO(bind,type) (((bind)<<4)+((type)&0xf))

// symbol binding
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2
#define STB_LOPROC 13
#define STB_HIPROC 15

// symbol type
#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC   2
#define STT_SECTION 3
#define STT_FILE 4
#define STT_LOPROC 13
#define STT_HIPROC 15

// Relocation
typedef struct {
        Elf32_Addr r_offset;
        Elf32_Word r_info;
} Elf32_Rel;

typedef struct {
        Elf64_Addr r_offset;
        Elf64_Xword r_info;
} Elf64_Rel;

typedef struct {
        Elf32_Addr r_offset;
        Elf32_Word r_info;
        Elf32_Sword r_addend;
} Elf32_Rela;

typedef struct {
        Elf64_Addr r_offset;
        Elf64_Xword r_info;
        Elf64_Sxword r_addend;
} Elf64_Rela;

#define ELF32_R_SYM(i)    ((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))


// program header types (p_type)
#define PT_NULL         0               /* Program header table entry unused */
#define PT_LOAD         1               /* Loadable program segment */
#define PT_DYNAMIC      2               /* Dynamic linking information */
#define PT_INTERP       3               /* Program interpreter */
#define PT_NOTE         4               /* Auxiliary information */
#define PT_SHLIB        5               /* Reserved */
#define PT_PHDR         6               /* Entry for header table itself */
#define PT_NUM          7               /* Number of defined types */
#define PT_LOOS         0x60000000      /* Start of OS-specific */
#define PT_HIOS         0x6fffffff      /* End of OS-specific */
#define PT_LOPROC       0x70000000      /* Start of processor-specific */
#define PT_HIPROC       0x7fffffff      /* End of processor-specific */


// program header flags (p_flags)
#define PF_X            (1 << 0)        /* Segment is executable */
#define PF_W            (1 << 1)        /* Segment is writable */
#define PF_R            (1 << 2)        /* Segment is readable */
#define PF_MASKOS       0x0ff00000      /* OS-specific */
#define PF_MASKPROC     0xf0000000      /* Processor-specific */


// program header entry
typedef struct
{
          Elf32_Word    p_type;                 /* Segment type */
          Elf32_Off     p_offset;               /* Segment file offset */
          Elf32_Addr    p_vaddr;                /* Segment virtual address */
          Elf32_Addr    p_paddr;                /* Segment physical address */
          Elf32_Word    p_filesz;               /* Segment size in file */
          Elf32_Word    p_memsz;                /* Segment size in memory */
          Elf32_Word    p_flags;                /* Segment flags */
          Elf32_Word    p_align;                /* Segment alignment */
} Elf32_Phdr;

typedef struct
{
      // order of elements is different than Elf32_Phdr!
          Elf64_Word    p_type;                 /* Segment type */
          Elf64_Word    p_flags;                /* Segment flags */
          Elf64_Off     p_offset;               /* Segment file offset */
          Elf64_Addr    p_vaddr;                /* Segment virtual address */
          Elf64_Addr    p_paddr;                /* Segment physical address */
          Elf64_Xword   p_filesz;               /* Segment size in file */
          Elf64_Xword   p_memsz;                /* Segment size in memory */
          Elf64_Xword   p_align;                /* Segment alignment */
} Elf64_Phdr;


#endif
