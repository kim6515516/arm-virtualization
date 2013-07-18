/*
 * $Id: ObjectLoaderAddress.h 29638 2013-01-04 13:48:03Z pgotch $
 *
 * Project: ObjectLoader
 * $Author: pgotch $
 * $Date: 2013-01-04 13:48:03 +0000 (Fri, 04 Jan 2013) $
 * $Revision: 29638 $
 *
 * Copyright (c) 2000-2003 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */

/** \file
 * ObjectLoader header file (interface specification)
 */

#ifndef _ObjectLoaderAddress_h_
#define _ObjectLoaderAddress_h_ "$Id: ObjectLoaderAddress.h 29638 2013-01-04 13:48:03Z pgotch $"

#include "MxTypes.h"

// address type used in the loader interfaces


// 2009-04-21: jo: ObjectLoaderAddress is now 64 bit, this is 99% source code compatible, no need to create redundant interfaces for 64 bit
typedef MxU64 ObjectLoaderAddress;
#define ObjectLoaderAddressBits 64
#define ObjectLoaderAddressMax MxU64CONST(0xffffffffffffffff)
#define ObjectLoaderAddressFormat "%08" MxFMT64 "X"


#endif

