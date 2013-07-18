/*
 * $Id: DWARF_Util.h 29787 2013-03-01 10:40:01Z brifol01 $
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

#ifndef DWARF_UTIL_H
#define DWARF_UTIL_H

#include "MxTypes.h"
#include <string>
#include <vector>

namespace DebugInfoDB
{
// read functions

    inline MxU8 DW_read1byte(const MxU8 *&cursor)
    {
        return *cursor++;
    }

    MxU16 DW_read2byte(const MxU8 *&cursor, bool isBigEndian);

    MxU32 DW_read4byte(const MxU8 *&cursor, bool isBigEndian);

    MxU64 DW_read8byte(const MxU8 *&cursor, bool isBigEndian);

    // read a 1,2,4 or 8 byte quantity
    MxU64 DW_readAddress(const MxU8 *&cursor, bool isBigEndian, MxU32 addressTypeSizeInBytes);

    // you really should provide an end pointer to avoid segfaults on corrupt input files
    MxU64 DW_readULEB128(const MxU8 *&cursor); // jo: dangerous function may segfault on end of buffer, do not use
    MxU64 DW_readULEB128(const MxU8 *&cursor, const MxU8 *end);

    // you really should provide an end pointer to avoid segfaults on corrupt input files
    MxS64 DW_readSLEB128(const MxU8 *&cursor); // jo: dangerous function may segfault on end of buffer, do not use
    MxS64 DW_readSLEB128(const MxU8 *&cursor, const MxU8 *end);

    // read a null terminated string
    const std::string DW_readString(const MxU8 *&cursor, const MxU8 *end);
}

#endif
