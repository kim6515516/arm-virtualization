/*
 * $Id: Dwarf2StringConstants.h 29787 2013-03-01 10:40:01Z brifol01 $
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

#ifndef DWARF2STRINGCONSTANTS_H
#define DWARF2STRINGCONSTANTS_H

#include "MxTypes.h"

namespace DebugInfoDB
{
    // these functions return a string for a numeric value
    // the returned pointer is valid at least until the next call to one of these functions
    const char *DW_TAG_GetString(MxU32 tag);
    const char *DW_AT_GetString(MxU32 at);
    const char *DW_FORM_GetString(MxU32 at);
    const char *DW_OP_GetString(MxU32 at);
    const char *DW_ATE_GetString(MxU32 at);
    const char *DW_ATE_GetStringReadElf(MxU32 at);
    const char *DW_ACCESS_GetString(MxU32 at);
    const char *DW_ACCESS_GetStringReadElf(MxU32 at);
    const char *DW_VIS_GetString(MxU32 at);
    const char *DW_VIRTUALITY_GetString(MxU32 at);
    const char *DW_VIRTUALITY_GetStringReadElf(MxU32 at);
    const char *DW_LANG_GetString(MxU32 at);
    const char *DW_LANG_GetStringReadElf(MxU32 at);
    const char *DW_ID_GetString(MxU32 at);
    const char *DW_CC_GetString(MxU32 at);
    const char *DW_INL_GetString(MxU32 at);
    const char *DW_INL_GetStringReadElf(MxU32 at);
    const char *DW_ORD_GetString(MxU32 at);
    const char *DW_DSC_GetString(MxU32 at);
    const char *DW_LNS_GetString(MxU32 at);
    const char *DW_LNE_GetString(MxU32 at);
    const char *DW_MACINFO_GetString(MxU32 at);
    const char *DW_CFA_GetString(MxU32 at);
    const char *DW_CFA_RR_GetString(MxU32 at);
}

#endif
