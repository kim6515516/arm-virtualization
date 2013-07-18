/*
 * hostconf: hostconf/zstdint.h - Ensures existence of C99 integer types.
 *
 * Copyright 2005 ARM Limited. All rights reserved.
 * Copyright 2011 ARM Limited. All rights reserved.
 */

/*
 * RCS $Revision: 173856 $
 * Checkin $Date: 2012-03-01 13:41:08 +0000 (Thu, 01 Mar 2012) $
 * Revising $Author: brasmi01 $
 */

/*
 * This file cannot be called simply "hostconf/stdint.h"
 * because an attempt to include the C99 <stdint.h> from some other
 * HOSTCONF header will cause inclusion of hostconf/stdint.h instead.
 * This happens because paths specified by -I<path> command-line option
 * are searched BEFORE system include paths by both MSVC++ and G++.
 */
#ifndef hostconf_zstdint_h
#define hostconf_zstdint_h

#if defined(__GNUC__) && defined(__SVR4) && defined(__sun)

    /*  GCC has a combined <inttypes.h>, but no <stdint.h> on Solaris.
        Futhermore, this combined <inttypes.h> is somewhat screwed up,
        se we need to adjust the definitions (otherwise things end up 
        with sizeof(intmax_t)<sizeof(int64_t) under __STDC__  */

    #include <inttypes.h>

    /* Pull in Standard C limits.h as it may define SIZE_MAX */
    #include <limits.h>

    #if !(defined(_LP64) || (__STDC__ - 0 == 0 && !defined(_NO_LONGLONG)))
        /*  Sometimes, both intmax_t and uintmax_t are defined as 32-bit
            quantities. This is ungood, because 64-bit integer types are
            guaranteed to exist. We use a little preprocessor trick to
            fool the compiler into using 64-bit intmax_t and uintmax_t */
        /* 7.18.1.5 */
        typedef signed long long    hostconf_intmax_t;
        typedef unsigned long long  hostconf_uintmax_t;
        #define intmax_t            hostconf_intmax_t
        #define uintmax_t           hostconf_uintmax_t

        /*  Sometimes, 64-bit things are not defined in <inttypes.h>
            at all, so we need to define these manually */

        /* 7.18.1.1 */
        typedef signed long long    int64_t;
        typedef unsigned long long  uint64_t;

        /* 7.18.1.2 */
        typedef signed long long    int_least64_t;
        typedef unsigned long long  uint_least64_t;

        /* 7.18.2 */
        #if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)
            /* 7.18.2.1 */
            #define INT64_MIN       (-9223372036854775807LL-1)
            #define INT64_MAX       (9223372036854775807LL)
            #define UINT64_MAX      (18446744073709551615ULL)

            /* 7.18.2.2 */
            #define INT_LEAST64_MIN INT64_MIN
            #define INT_LEAST64_MAX INT64_MAX
            #define UINT_LEAST64_MAX UINT64_MAX

            /* 7.18.2.3 */
            #define INT_FAST64_MIN  INT64_MIN
            #define INT_FAST64_MAX  INT64_MAX
            #define UINT_FAST64_MAX UINT64_MAX

            /* 7.18.2.4 */
            #define INTPTR_MIN      INT32_MIN
            /* Solaris kindly defines INTPTR_MAX and UINTPTR_MAX to nothing
             * and so we have to undo that work here!
             */
            #if defined(INTPTR_MAX)
                #undef INTPTR_MAX
            #endif
            #define INTPTR_MAX      INT32_MAX
            #if defined(UINTPTR_MAX)
                #undef UINTPTR_MAX
            #endif
            #define UINTPTR_MAX     UINT32_MAX

            /* 7.18.3 */
            #define PTRDIFF_MIN     INT32_MIN
            #define PTRDIFF_MAX     INT32_MAX

            /* SIG_ATOMIC_MIN */
            /* SIG_ATOMIC_MAX */
            #ifndef SIZE_MAX
                #define SIZE_MAX UINT32_MAX
            #endif

            /* WCHAR_MIN */
            /* WCHAR_MAX */

            /* WINT_MIN */
            /* WINT_MAX */
        #endif /* !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) */

        #if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS)
            /* Make sure boost doesn't try to redefine these */
            # define BOOST__STDC_CONSTANT_MACROS_DEFINED
            /* 7.18.4.1 */
            #undef INT64_C
            #define INT64_C(x)      (x##ll)
            #undef UINT64_C
            #define UINT64_C(x)     (x##ull)

            /* 7.18.4.2 */
            /*  On Solaris under _ILP32 model both INTMAX_C and UINTMAX_C
                are defined to result in 32-but quantities. Ungood. */
            #undef INTMAX_C
            #define INTMAX_C(x)     INT64_C(x)
            #undef UINTMAX_C
            #define UINTMAX_C(x)    UINT64_C(x)

        #endif /* !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) */
    #endif /* !(defined(_LP64) || (__STDC__ - 0 == 0 && !defined(_NO_LONGLONG))) */

  #if 0
    /*  Solaris 10 <inttypes.h> (or rather <sys/int_types.h>) does define the fast types. */
  #else
    /*  On Solaris, the <inttypes.h> fails to define fast types altogether */

    /* 7.18.1.3 */
    typedef int32_t             int_fast8_t;
    typedef int32_t             int_fast16_t;
    typedef int32_t             int_fast32_t;
    typedef uint32_t            uint_fast8_t;
    typedef uint32_t            uint_fast16_t;
    typedef uint32_t            uint_fast32_t;
    typedef int64_t             int_fast64_t;
    typedef uint64_t            uint_fast64_t;
  #endif

#elif defined(__GNUC__) && defined(__hppa)
    /*  GCC on HP-UX has a standard <inttypes.h> but no <stdint.h>. */

    #include <inttypes.h>

#elif defined(__GNUC__)
    /*  GCC generally has a standard <stdint.h>. */

    #include <stdint.h>

#elif defined(__HP_aCC) || defined(__HP_cc)
    /*  aCC has a combined <inttypes.h>, but no <stdint.h> */

    #include <inttypes.h>

#elif _MSC_VER

    #if _MSC_VER >= 1600
        /* Visual Studio 2010 and later have a <stdint.h>. */
        
        #include <stdint.h>
    
    #else
        /*  Older versions of MSVC++ does not have the standard header
         *  <stdint.h>, so we need to write here all the declarations that
         *  <stdint.h> shall contain */

        /* 7.18.1.1 */
        typedef signed char         int8_t;
        typedef signed short        int16_t;
        typedef signed int          int32_t;
        typedef signed __int64      int64_t;

        typedef unsigned char       uint8_t;
        typedef unsigned short      uint16_t;
        typedef unsigned int        uint32_t;
        typedef unsigned __int64    uint64_t;

        /* 7.18.1.2 */
        typedef signed char         int_least8_t;
        typedef signed short        int_least16_t;
        typedef signed int          int_least32_t;
        typedef signed __int64      int_least64_t;

        typedef unsigned char       uint_least8_t;
        typedef unsigned short      uint_least16_t;
        typedef unsigned int        uint_least32_t;
        typedef unsigned __int64    uint_least64_t;

        /* 7.18.1.3 */
        typedef int32_t             int_fast8_t;
        typedef int32_t             int_fast16_t;
        typedef int32_t             int_fast32_t;
        typedef uint32_t            uint_fast8_t;
        typedef uint32_t            uint_fast16_t;
        typedef uint32_t            uint_fast32_t;
        typedef int64_t             int_fast64_t;
        typedef uint64_t            uint_fast64_t;

        /* 7.18.1.4 */
        #if !defined(UINTPTRT_DEFINED_BY_CLX) && !defined(_UINTPTR_T_DEFINED)
            /* MSVC provides intptr_t and uintptr_t in <stddef.h> */
            #if _MSC_VER >= 1200 && _MSC_VER < 1300
                typedef int32_t         intptr_t;
                typedef uint32_t        uintptr_t;
            #else
                #include <stddef.h>
            #endif
            #define UINTPTRT_DEFINED_BY_HOSTCONF
        #endif

        /* 7.18.1.5 */
        typedef int64_t             intmax_t;
        typedef uint64_t            uintmax_t;

        /* 7.18.2 */
        #if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)
            /*  Include Microsoft's limits header, which defines some
                useful but non-standard limits macros. */
            #include <limits.h>

            /* 7.18.2.1 */
            #define INT8_MIN        _I8_MIN
            #define INT16_MIN       _I16_MIN
            #define INT32_MIN       _I32_MIN
            #define INT64_MIN       _I64_MIN

            #define INT8_MAX        (+_I8_MAX)
            #define INT16_MAX       (+_I16_MAX)
            #define INT32_MAX       (+_I32_MAX)
            #define INT64_MAX       (+_I64_MAX)

            #define UINT8_MAX       (+_UI8_MAX)
            #define UINT16_MAX      (+_UI16_MAX)
            #define UINT32_MAX      (+_UI32_MAX)
            #define UINT64_MAX      (+_UI64_MAX)

            /* 7.18.2.2 */
            #define INT_LEAST8_MIN  INT8_MIN
            #define INT_LEAST16_MIN INT16_MIN
            #define INT_LEAST32_MIN INT32_MIN
            #define INT_LEAST64_MIN INT64_MIN

            #define INT_LEAST8_MAX  INT8_MAX
            #define INT_LEAST16_MAX INT16_MAX
            #define INT_LEAST32_MAX INT32_MAX
            #define INT_LEAST64_MAX INT64_MAX

            #define UINT_LEAST8_MAX  UINT8_MAX
            #define UINT_LEAST16_MAX UINT16_MAX
            #define UINT_LEAST32_MAX UINT32_MAX
            #define UINT_LEAST64_MAX UINT64_MAX

            /* 7.18.2.3 */
            #define INT_FAST8_MIN   INT32_MIN
            #define INT_FAST16_MIN  INT32_MIN
            #define INT_FAST32_MIN  INT32_MIN
            #define INT_FAST64_MIN  INT64_MIN

            #define INT_FAST8_MAX   INT32_MAX
            #define INT_FAST16_MAX  INT32_MAX
            #define INT_FAST32_MAX  INT32_MAX
            #define INT_FAST64_MAX  INT64_MAX

            #define UINT_FAST8_MAX  UINT32_MAX
            #define UINT_FAST16_MAX UINT32_MAX
            #define UINT_FAST32_MAX UINT32_MAX
            #define UINT_FAST64_MAX UINT64_MAX

            /* 7.18.2.4 */
            #if defined(_WIN64)
                #define INTPTR_MIN      INT64_MIN
                #define INTPTR_MAX      INT64_MAX
                #define UINTPTR_MAX     UINT64_MAX
            #else
                #define INTPTR_MIN      INT32_MIN
                #define INTPTR_MAX      INT32_MAX
                #define UINTPTR_MAX     UINT32_MAX
            #endif

            /* 7.18.2.5 */
            #define INTMAX_MIN      INT64_MIN
            #define INTMAX_MAX      INT64_MAX
            #define UINTMAX_MAX     UINT64_MAX

            /* 7.18.3 */
            #if defined(_WIN64)
                #define PTRDIFF_MIN     INT64_MIN
                #define PTRDIFF_MAX     INT64_MAX
            #else
                #define PTRDIFF_MIN     INT32_MIN
                #define PTRDIFF_MAX     INT32_MAX
            #endif

            /* SIG_ATOMIC_MIN */
            /* SIG_ATOMIC_MAX */

            #ifndef SIZE_MAX
                #if defined(_WIN64)
                    #define SIZE_MAX UINT64_MAX
                #else
                    #define SIZE_MAX UINT32_MAX
                #endif
            #endif

            /* WCHAR_MIN */
            /* WCHAR_MAX */

            /* WINT_MIN */
            /* WINT_MAX */
        #endif /* !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) */

        #if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS)
            /* 7.18.4.1 */
            #define INT8_C(x)       x
            #define UINT8_C(x)      (x##u)
            #define INT16_C(x)      x
            #define UINT16_C(x)     (x##u)
            #define INT32_C(x)      x
            #define UINT32_C(x)     (x##u)
            #define INT64_C(x)      (x##i64)
            #define UINT64_C(x)     (x##ui64)

            /* 7.18.4.2 */
            #define INTMAX_C(x)     INT64_C(x)
            #define UINTMAX_C(x)    UINT64_C(x)

        #endif /* !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) */

    #endif /* _MSC_VER >= 1600 */

#elif defined(__ARMCC_VERSION)
    /*  RVCT has the standard header <stdint.h> */

    #include <stdint.h>

#else

    #error Unknown or unsupported toolchain

#endif  /*  TOOLCHAIN selection */

#endif  /*  hostconf_zstdint_h */
/* end of hostconf/zstdint.h */
