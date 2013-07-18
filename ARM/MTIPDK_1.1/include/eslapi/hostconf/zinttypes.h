/*
 * hostconf: hostconf/zinttypes.h - Ensures existence of C99 integer formats.
 *
 * Copyright 2005 ARM Limited. All rights reserved.
 * Copyright 2011 ARM Limited. All rights reserved.
 */

/*
 * RCS $Revision: 171707 $
 * Checkin $Date: 2011-10-18 16:49:46 +0100 (Tue, 18 Oct 2011) $
 * Revising $Author: benfos01 $
 */

/*
 * This file cannot be called simply "hostconf/inttypes.h"
 * because an attempt to include the C99 <inttypes.h> from some other
 * HOSTCONF header will cause inclusion of hostconf/inttypes.h instead.
 * This happens because paths specified by -I<path> command-line option
 * are searched BEFORE system include paths by both MSVC++ and G++.
 */

#ifndef hostconf_zinttypes_h
#define hostconf_zinttypes_h

#include "hostconf/zstdint.h"

#if defined(__GNUC__) && defined(__SVR4) && defined(__sun)

    /*  GCC has a combined <inttypes.h>, but no <stdint.h>. However,
        on Solaris, this combined <inttypes.h> is somewhat screwed up,
        se we need to adjust the definitions (otherwise things end up 
        with sizeof(intmax_t)<sizeof(int64_t) under __STDC__  */

    #include <inttypes.h>

    #if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS)

        /* 7.8.1 Macros for format specifiers */

        #if defined(__arch64__) && defined(__sparcv9)

        /* 64-bit SPARC has defines corect, but not fast ones.
           Redefining results in warnings because int64 is 'long'. */

        #define PRIdFAST64  "ld"
        #define PRIiFAST64  "li"
        #define PRIoFAST64  "lo"
        #define PRIuFAST64  "lu"
        #define PRIxFAST64  "lx"
        #define PRIXFAST64  "lX"
        #define SCNdFAST64  "ld"
        #define SCNiFAST64  "li"
        #define SCNoFAST64  "lo"
        #define SCNuFAST64  "lu"
        #define SCNxFAST64  "lx"

        #else /* if !defined(__arch64__) && !defined(__sparcv9) */

        /*  Under certain circumstances the 64-bit formats are not 
            defined at all ... */
        #define PRId64      "lld"
        #define PRIi64      "lli"
        #define PRIo64      "llo"
        #define PRIu64      "llu"
        #define PRIx64      "llx"
        #define PRIX64      "llX"
        #define SCNd64      "lld"
        #define SCNi64      "lli"
        #define SCNo64      "llo"
        #define SCNu64      "llu"
        #define SCNx64      "llx"

        #define PRIdLEAST64 "lld"
        #define PRIiLEAST64 "lli"
        #define PRIoLEAST64 "llo"
        #define PRIuLEAST64 "llu"
        #define PRIxLEAST64 "llx"
        #define PRIXLEAST64 "llX"
        #define SCNdLEAST64 "lld"
        #define SCNiLEAST64 "lli"
        #define SCNoLEAST64 "llo"
        #define SCNuLEAST64 "llu"
        #define SCNxLEAST64 "llx"

        #define PRIdFAST64  "lld"
        #define PRIiFAST64  "lli"
        #define PRIoFAST64  "llo"
        #define PRIuFAST64  "llu"
        #define PRIxFAST64  "llx"
        #define PRIXFAST64  "llX"
        #define SCNdFAST64  "lld"
        #define SCNiFAST64  "lli"
        #define SCNoFAST64  "llo"
        #define SCNuFAST64  "llu"
        #define SCNxFAST64  "llx"

        /*  ...while MAX formats are defined to be 32-bits instead of 64 */
        #undef PRIdMAX
        #define PRIdMAX     "lld"
        #undef PRIiMAX
        #define PRIiMAX     "lli"
        #undef PRIoMAX
        #define PRIoMAX     "llo"
        #undef PRIuMAX
        #define PRIuMAX     "llu"
        #undef PRIxMAX
        #define PRIxMAX     "llx"
        #undef PRIXMAX
        #define PRIXMAX     "llX"
        #undef SCNdMAX
        #define SCNdMAX     "lld"
        #undef SCNiMAX
        #define SCNiMAX     "lli"
        #undef SCNoMAX
        #define SCNoMAX     "llo"
        #undef SCNuMAX
        #define SCNuMAX     "llu"
        #undef SCNxMAX
        #define SCNxMAX     "llx"

        #endif /* !defined(__arch64__) && !defined(__sparcv9) */

    #endif /* !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS) */

    /*  On Solaris, the <inttypes.h> fails to define fast types altogether */

    #define PRIdFAST8       "d"
    #define PRIiFAST8       "i"
    #define PRIoFAST8       "o"
    #define PRIuFAST8       "u"
    #define PRIxFAST8       "x"
    #define PRIXFAST8       "X"
    /* No suitable scanf length modifier for SCN?FAST8 */

    #define PRIdFAST16      "d"
    #define PRIiFAST16      "i"
    #define PRIoFAST16      "o"
    #define PRIuFAST16      "u"
    #define PRIxFAST16      "x"
    #define PRIXFAST16      "X"
    #define SCNdFAST16      "hd"
    #define SCNiFAST16      "hi"
    #define SCNoFAST16      "ho"
    #define SCNuFAST16      "hu"
    #define SCNxFAST16      "hx"

    #define PRIdFAST32      "d"
    #define PRIiFAST32      "i"
    #define PRIoFAST32      "o"
    #define PRIuFAST32      "u"
    #define PRIxFAST32      "x"
    #define PRIXFAST32      "X"
    #define SCNdFAST32      "d"
    #define SCNiFAST32      "i"
    #define SCNoFAST32      "o"
    #define SCNuFAST32      "u"
    #define SCNxFAST32      "x"

    /* 7.8.2 Functions for greatest-width integer types */

    /* We know intmax_t is 'long long' here */
    #ifdef __cplusplus
    extern "C"
    #endif
    long long llabs(long long);

    #ifdef __cplusplus
    extern "C"
    #endif
    long long strtoll(const char *nptr, char **endptr, int base);
    
    #ifdef __cplusplus
    extern "C"
    #endif
    unsigned long long strtoull(const char *nptr, char **endptr, int base);
    #define imaxabs llabs
    #define strtoimax strtoll
    #define strtoumax strtoull
    /* Not implemented: imaxdiv, wcstoimax, wcstoumax */

#elif defined(__GNUC__) || \
      defined(__HP_aCC) || defined(__HP_cc) || \
      defined(__ARMCC_VERSION)

    /*  In all these toolchains have the standard header <inttypes.h> */
    #include <inttypes.h>

#elif defined(_MSC_VER)
    /*  MSVC++ does not have the standard header <inttypes.h>, so we need to
        write here all the declarations that <inttypes.h> shall contain */

    #include <stdlib.h>

    #if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS)

        /* 7.8.1 Macros for format specifiers */
        #define PRId8       "d"
        #define PRIi8       "i"
        #define PRIo8       "o"
        #define PRIu8       "u"
        #define PRIx8       "x"
        #define PRIX8       "X"
        /* No suitable scanf length modifier for SCN?8 */

        #define PRIdLEAST8  "d"
        #define PRIiLEAST8  "i"
        #define PRIoLEAST8  "o"
        #define PRIuLEAST8  "u"
        #define PRIxLEAST8  "x"
        #define PRIXLEAST8  "X"
        /* No suitable scanf length modifier for SCN?LEAST8 */

        #define PRIdFAST8   "d"
        #define PRIiFAST8   "i"
        #define PRIoFAST8   "o"
        #define PRIuFAST8   "u"
        #define PRIxFAST8   "x"
        #define PRIXFAST8   "X"
        /* No suitable scanf length modifier for SCN?FAST8 */

        #define PRId16      "d"
        #define PRIi16      "i"
        #define PRIo16      "o"
        #define PRIu16      "u"
        #define PRIx16      "x"
        #define PRIX16      "X"
        #define SCNd16      "hd"
        #define SCNi16      "hi"
        #define SCNo16      "ho"
        #define SCNu16      "hu"
        #define SCNx16      "hx"

        #define PRIdLEAST16 "d"
        #define PRIiLEAST16 "i"
        #define PRIoLEAST16 "o"
        #define PRIuLEAST16 "u"
        #define PRIxLEAST16 "x"
        #define PRIXLEAST16 "X"
        #define SCNdLEAST16 "hd"
        #define SCNiLEAST16 "hi"
        #define SCNoLEAST16 "ho"
        #define SCNuLEAST16 "hu"
        #define SCNxLEAST16 "hx"

        #define PRIdFAST16  "d"
        #define PRIiFAST16  "i"
        #define PRIoFAST16  "o"
        #define PRIuFAST16  "u"
        #define PRIxFAST16  "x"
        #define PRIXFAST16  "X"
        #define SCNdFAST16  "hd"
        #define SCNiFAST16  "hi"
        #define SCNoFAST16  "ho"
        #define SCNuFAST16  "hu"
        #define SCNxFAST16  "hx"

        #define PRId32      "d"
        #define PRIi32      "i"
        #define PRIo32      "o"
        #define PRIu32      "u"
        #define PRIx32      "x"
        #define PRIX32      "X"
        #define SCNd32      "d"
        #define SCNi32      "i"
        #define SCNo32      "o"
        #define SCNu32      "u"
        #define SCNx32      "x"

        #define PRIdLEAST32 "d"
        #define PRIiLEAST32 "i"
        #define PRIoLEAST32 "o"
        #define PRIuLEAST32 "u"
        #define PRIxLEAST32 "x"
        #define PRIXLEAST32 "X"
        #define SCNdLEAST32 "d"
        #define SCNiLEAST32 "i"
        #define SCNoLEAST32 "o"
        #define SCNuLEAST32 "u"
        #define SCNxLEAST32 "x"

        #define PRIdFAST32 "d"
        #define PRIiFAST32 "i"
        #define PRIoFAST32 "o"
        #define PRIuFAST32 "u"
        #define PRIxFAST32 "x"
        #define PRIXFAST32 "X"
        #define SCNdFAST32 "d"
        #define SCNiFAST32 "i"
        #define SCNoFAST32 "o"
        #define SCNuFAST32 "u"
        #define SCNxFAST32 "x"

        #define PRId64      "I64d"
        #define PRIi64      "I64i"
        #define PRIo64      "I64o"
        #define PRIu64      "I64u"
        #define PRIx64      "I64x"
        #define PRIX64      "I64X"
        #define SCNd64      "I64d"
        #define SCNi64      "I64i"
        #define SCNo64      "I64o"
        #define SCNu64      "I64u"
        #define SCNx64      "I64x"

        #define PRIdLEAST64 "I64d"
        #define PRIiLEAST64 "I64i"
        #define PRIoLEAST64 "I64o"
        #define PRIuLEAST64 "I64u"
        #define PRIxLEAST64 "I64x"
        #define PRIXLEAST64 "I64X"
        #define SCNdLEAST64 "I64d"
        #define SCNiLEAST64 "I64i"
        #define SCNoLEAST64 "I64o"
        #define SCNuLEAST64 "I64u"
        #define SCNxLEAST64 "I64x"

        #define PRIdFAST64  "I64d"
        #define PRIiFAST64  "I64i"
        #define PRIoFAST64  "I64o"
        #define PRIuFAST64  "I64u"
        #define PRIxFAST64  "I64x"
        #define PRIXFAST64  "I64X"
        #define SCNdFAST64  "I64d"
        #define SCNiFAST64  "I64i"
        #define SCNoFAST64  "I64o"
        #define SCNuFAST64  "I64u"
        #define SCNxFAST64  "I64x"

        #define PRIdMAX     "I64d"
        #define PRIiMAX     "I64i"
        #define PRIoMAX     "I64o"
        #define PRIuMAX     "I64u"
        #define PRIxMAX     "I64x"
        #define PRIXMAX     "I64X"
        #define SCNdMAX     "I64d"
        #define SCNiMAX     "I64i"
        #define SCNoMAX     "I64o"
        #define SCNuMAX     "I64u"
        #define SCNxMAX     "I64x"

        #define PRIdPTR     "d"
        #define PRIiPTR     "i"
        #define PRIoPTR     "o"
        #define PRIuPTR     "u"
        #define PRIxPTR     "x"
        #define PRIXPTR     "X"
        #define SCNdPTR     "d"
        #define SCNiPTR     "i"
        #define SCNoPTR     "o"
        #define SCNuPTR     "u"
        #define SCNxPTR     "x"

    #endif /* !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS) */

    /* 7.8.2 Functions for greatest-width integer types */

    /* We know intmax_t is __int64 etc. here */
    #define imaxabs _abs64
    #define strtoimax _strtoi64
    #define strtoumax _strtoui64
    #define wcstoimax _wcstoi64
    #define wcstoumax _wcstoui64

    /* Not implemented: imaxdiv */

#else

    #error Unknown or unsupported toolchain

#endif  /*  TOOLCHAIN selection */

#if defined(__cplusplus) && !defined(__STDC_FORMAT_MACROS)
#undef hostconf_zinttypes_h
#endif /* allow reinclusion */

#endif  /*  hostconf_zinttypes_h */

/* end of hostconf/zinttypes.h */
