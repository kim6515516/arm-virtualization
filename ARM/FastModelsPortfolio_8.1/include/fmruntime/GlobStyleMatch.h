/*
 * $Id: GlobStyleMatch.h 29787 2013-03-01 10:40:01Z brifol01 $
 *
 * Project:  Pattern matching library
 * $Author: brifol01 $
 * $Date: 2013-03-01 10:40:01 +0000 (Fri, 01 Mar 2013) $
 * $Revision: 29787 $
 *
 * Copyright (c) 2003-2004 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */

#ifndef GLOBSTYLEMATCH_H
#define GLOBSTYLEMATCH_H

#include <string>
#include <stdexcept>
#include "MxTypes.h"

#define GLOBSTYLEMATCH_VERSION 2

bool GlobStyleMatch(const std::string &pattern, const std::string &str);
//      throws std::runtime_error

// get version
MxU32 GlobStyleMatchVersion();

#endif

