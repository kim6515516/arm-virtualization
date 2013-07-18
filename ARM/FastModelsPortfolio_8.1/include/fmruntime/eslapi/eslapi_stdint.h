// ===========================================================================
// Description : Wrapper to provide some stdint types for non C99 compliant compilers
//
// Author      : ARM
// Release     : 2.0.0
//
// Copyright (c) 2006-2008 ARM. All rights reserved.
//
// ============================================================================
//

/*

Including this header must give support for the following types and macros:
   
Exact-width integer types:

int8_t  int16_t  int32_t  int64_t
uint8_t uint16_t uint32_t uint64_t


Macros for defining constants of specified widths:

INT8_C  INT16_C  INT32_C  INT64_C
UINT8_C UINT16_C UINT32_C UINT64_C

*/

#ifndef ESLAPI_STDINT_H
# define ESLAPI_STDINT_H

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include "eslapi/hostconf/zstdint.h"

#endif // ESLAPI_STDINT_H
