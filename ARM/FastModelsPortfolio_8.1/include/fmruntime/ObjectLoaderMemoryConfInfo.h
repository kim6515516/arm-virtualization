/*
 * $Id: ObjectLoaderMemoryConfInfo.h 29787 2013-03-01 10:40:01Z brifol01 $
 *
 * Project:  LISA Simulator Generator
 * $Author: brifol01 $
 * $Date: 2013-03-01 10:40:01 +0000 (Fri, 01 Mar 2013) $
 * $Revision: 29787 $
 *
 * Copyright (c) 2000-2003 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */

/** \file
 * ObjectLoader memory configuration information header file (interface specification)
 */

#ifndef _ObjectLoaderMemoryConfInfo_h_
#define _ObjectLoaderMemoryConfInfo_h_ "$Id: ObjectLoaderMemoryConfInfo.h 29787 2013-03-01 10:40:01Z brifol01 $"

#include "MxTypes.h"

// static memory.conf information
struct ObjectLoaderAddressSpaceInfo
{
    MxU32 id;         // id != index
    MxU32 mauBytes;
    MxU32 addressInc;
    MxU32 addressBits;
    const char *name; // name of address space (e.g. 'program')
    bool isProgramMemory;
    bool isBigEndian;
};

struct ObjectLoaderSectionInfo
{
    const char *name; // name of section (e.g. '.text')
    MxU32 addressSpaceIndex;
    bool ignore;      // true == section is silently ignored during loading
    const char *access;
};

struct ObjectLoaderMemoryConfInfo
{
    MxU32 numAddressSpaces;
    const ObjectLoaderAddressSpaceInfo *addressSpace; // array
    MxU32 numSections;
    const ObjectLoaderSectionInfo *section; // array
    MxU32 programMemoryAddressSpaceIndex;
};

#endif

