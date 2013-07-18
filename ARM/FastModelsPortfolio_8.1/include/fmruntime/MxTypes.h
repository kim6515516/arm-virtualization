/*!
 * \file    MxTypes.h
 * \brief   Types for components inherited from SoC Designer.
 * \date    Copyright 2000-2005 ARM Limited. All rights reserved.
 *          Copyright 2012 ARM Limited. All rights reserved.
 *
 */


#ifndef MxTypes_h
#define MxTypes_h

// 8 bit types
typedef signed char MxS8;
typedef unsigned char MxU8;

// 16 bit types
typedef signed short MxS16;
typedef unsigned short MxU16;

// 32 bit types
typedef signed int MxS32;
typedef unsigned int MxU32;

// 64 bit types
#ifdef _MSC_VER
typedef signed __int64 MxS64;
typedef unsigned __int64 MxU64;
#else
// use long long only on 32 bit Linux
#ifndef __x86_64__
typedef signed long long MxS64;
typedef unsigned long long MxU64;
#else
#include <stdint.h>
typedef int64_t MxS64;
typedef uint64_t MxU64;
#endif
#endif

#ifdef _MSC_VER
# define MxFMT64d    "%I64d"
# define MxFMT64i    "%I64i"
# define MxFMT64u    "%I64u"
# define MxFMT64x    "%I64x"
# define MxFMT64X    "%I64X"
# define MxFMT0864x  "%08I64x"
# define MxFMT0864X  "%08I64X"
# define MxFMT01664x "%016I64x"
# define MxFMT01664X "%016I64X"
# define MxFMT64     "I64"
#else
# ifndef __x86_64__
# define MxFMT64d    "%lld"
# define MxFMT64i    "%lli"
# define MxFMT64u    "%llu"
# define MxFMT64x    "%llx"
# define MxFMT64X    "%llX"
# define MxFMT0864x  "%08llx"
# define MxFMT0864X  "%08llX"
# define MxFMT01664x "%016llx"
# define MxFMT01664X "%016llX"
# define MxFMT64     "ll"
# else
// On 64 bit Linux a long is 64 bit wide (= int64_t)
# define MxFMT64d    "%ld"
# define MxFMT64i    "%li"
# define MxFMT64u    "%lu"
# define MxFMT64x    "%lx"
# define MxFMT64X    "%lX"
# define MxFMT0864x  "%08lx"
# define MxFMT0864X  "%08lX"
# define MxFMT01664x "%016lx"
# define MxFMT01664X "%016lX"
# define MxFMT64     "l"
# endif
#endif

#ifdef _MSC_VER
# define MxU64CONST(value) ((MxU64)(value##i64))
# define MxS64CONST(value) ((MxS64)(value##i64))
#else
# define MxU64CONST(value) ((MxU64)(value##ull))
# define MxS64CONST(value) ((MxS64)(value##ll))
#endif

enum MxStatus
{
	MX_STATUS_OK = 0,
	MX_STATUS_WAIT = 1,
	MX_STATUS_NOACCESS = 2,
	MX_STATUS_NOMEMORY = 3,
	MX_STATUS_ERROR = -1,
	MX_STATUS_NOTSUPPORTED = -2
};

enum MxGrant
{
	MX_GRANT_OK = 0,
	MX_GRANT_DENIED = 1,
	MX_GRANT_ERROR = -1,
	MX_GRANT_NOTSUPPORTED = -2
};

#endif
