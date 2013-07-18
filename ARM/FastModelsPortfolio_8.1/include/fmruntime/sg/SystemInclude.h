/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   SystemInclude.h
 *  \brief  Includes system headers in a controlled manner
 *  \date   Copyright ARM Limited 2008-2011 All Rights Reserved.
 *
 *  On Windows includes Windows.h with the right predefines
 *  on *nix includes unistd.h
 *
 *  This file is not part of a stable public API and it may
 *  change without notice.
 */

#ifndef INCLUDED_SYSTEMINCLUDE_H
#define INCLUDED_SYSTEMINCLUDE_H

#include "sg/PreInc.h"

/* Defining WIN32_LEAN_AND_MEAN removes some of the less used parts of the
 * Win32 API which makes anything that pulls us in compiles much faster.
 *
 * For historical reasons there are at least 4 ways of telling Windows what the
 * lowest version of the API you require is
 *      WINVER          From 16 bit windows
 *      _WIN32_WINNT    To distinguish between NT4 and Win95
 *      _WIN32_WINDOWS  To distinguish between Win95 and NT4
 *      _WIN32_IE       Due to IE historically patching system components when
 *                      installed
 *
 *  Windows Vista includes yet another mechanism which automatically sets the
 *  above however this is only available in Vista capable version of the sdk
 *  and we have to compile against older ones so we can't use it. If we could
 *  this would involve setting NTDDI_VERSION then including sdkddkver.h
 *
 *  Defining NOMINMAX works around round Windows.h breaking use of std::min and
 *  std::max by defining min and max as macros and therefore breaking some
 *  usage.
 */

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
        #define SG_WIN32_LEAN_AND_MEAN_DEFINED
    #endif

    /* This targets us to a minimum of original Windows XP RTM respecting a
     * decision to use a later version if it has already been made.
     */
    #if defined(WINVER)
        #if WINVER < 0x0501
            #error "Fast Models requires version 0x0501 of the Win32 API"
        #endif
    #else
        #define WINVER 0x0501
    #endif

    #if defined(_WIN32_WINNT)
        #if _WIN32_WINNT < 0x0501
            #error "Fast Models requires version 0x0501 of the Win32 API"
        #endif
    #else
        #define _WIN32_WINNT 0x0501
    #endif

    #if defined(_WIN32_WINDOWS)
        #if _WIN32_WINNT < 0x0501
            #error "Fast Models requires version 0x0501 of the Win32 API"
        #endif
    #else
        #define _WIN32_WINDOWS 0x0501
    #endif

    /* This looks at what has been defined and uses the maximum of the possible
     * defines that could have been defined by the user */
    #if WINVER > _WIN32_WINNT
        #if WINVER > _WIN32_WINDOWS
            #undef _WIN32_WINNT
            #undef _WIN32_WINDOWS
            #define _WIN32_WINNT WINVER
            #define _WIN32_WINDOWS WINVER
        #else
            #undef WINVER
            #undef _WIN32_WINNT
            #define WINVER _WIN32_WINDOWS
            #define _WIN32_WINNT _WIN32_WINDOWS
        #endif
    #else
        #if _WIN32_WINNT > _WIN32_WINDOWS
            #undef WINVER
            #undef _WIN32_WINDOWS
            #define WINVER _WIN32_WINNT
            #define _WIN32_WINDOWS _WIN32_WINNT
        #else
            #undef WINVER
            #undef _WIN32_WINNT
            #define WINVER _WIN32_WINDOWS
            #define _WIN32_WINNT _WIN32_WINDOWS
        #endif
    #endif

    /* If NOMINMAX has already been defined then leave it otherwise define it
     * specifically for including Windows.h then remove it again. */
    #ifndef NOMINMAX
        #define NOMINMAX
        #define SG_NOMINMAX_DEFINED
    #endif

    #include <Windows.h>
    
    #ifdef SG_NOMINMAX_DEFINED
        #undef NOMINMAX
    #endif
    
    #ifdef SG_WIN32_LEAN_AND_MEAN_DEFINED
        #undef WIN32_LEAN_AND_MEAN
    #endif
#endif

#ifdef __unix__
    #include <unistd.h>
#endif

#include "sg/PostInc.h"

#endif

/* eof SystemInclude.h */
