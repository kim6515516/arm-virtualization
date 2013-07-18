/*
 * $Id: Int2String.h 29786 2013-03-01 10:39:02Z brifol01 $
 *
 * Project:  LISA Simulator Generator
 * $Author: brifol01 $
 * $Date: 2013-03-01 10:39:02 +0000 (Fri, 01 Mar 2013) $
 * $Revision: 29786 $
 *
 * Copyright (c) 2000-2003 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */

/** \file
 * Macro expander header file.
 */

#ifndef _Int2String_h_
#define _Int2String_h_ "$Id: Int2String.h 29786 2013-03-01 10:39:02Z brifol01 $"

#include "MxTypes.h"

#include <string>
#include <string.h>
#include <stdlib.h>

/// Invalid integer value for number of digits for int2string
#define int_INVALID 0x7fffffff

/// Convert int to string
std::string int2string(int i, const char *format = "%d", int ndigits = int_INVALID);

/// Convert long to string
std::string long2string(long i, const char *format = "%d", int ndigits = int_INVALID);

/// Convert string to int
inline int string2int(const std::string& str, int base = 0) { return strtol(str.c_str(), 0, base); }

/// Convert string to bool
bool string2bool(const std::string& str, bool *error = 0);

/// Valid values for string2bool
extern const char *string2boolValidValues;

/// Convert bool to string
std::string bool2string (bool b);

/// Convert double to string
std::string double2string(double d, const char *format = "%g", int ndigits = int_INVALID);

/// Convert MxU64 into string
std::string MxU642string(MxU64 value, const char *format = MxFMT64u, int ndigits = int_INVALID);

// Convert string to MxU64
// (supports bin, hex, oct, dec, [mM], [kK] and [gG] suffixes (1024**n),
// positive and negative values, works like strtoull)
MxU64  ConstCharPtr2MxU64(const char   *str, const char **endPtr = 0, int base = 0);
inline MxU64 string2MxU64(const std::string &str, const char **endPtr = 0, int base = 0) { return ConstCharPtr2MxU64(str.c_str(), endPtr, base); }

#endif


