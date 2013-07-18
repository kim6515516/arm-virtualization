/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   MSCFixes.h
 *  \brief  Portability fixes required for Microsoft C/C++ 
 *  \date   Copyright ARM Limited 2008 All Rights Reserved.
 *          Copyright ARM Limited 2012 All Rights Reserved.
 *
 *  The Microsoft C/C++ compiler fails to define many standard
 *  functions found in modern libc implementations, or
 *  defines them with the nonstandard names.
 *
 *  This file fixes names where possible.
 *
 *  This file is not part of a stable public API and it may
 *  change without notice.
 */

#ifndef INCLUDED_MSCFIXES_H
#define INCLUDED_MSCFIXES_H

#ifdef _MSC_VER
    #if !defined(snprintf)
        #define snprintf _snprintf
    #endif

    #if !defined(putenv)
        #define putenv _putenv
    #endif

    #if !defined(setenv)
        #define setenv(x,y,z) _putenv_s(x,y)
    #endif

    #if !defined(strtoll)
        #define strtoll _strtoi64
    #endif

    #if !defined(strtoull)
        #define strtoull _strtoui64
    #endif

    #if !defined(strdup)
        #define strdup _strdup
    #endif

    #if !defined(isatty)
        #define isatty _isatty
    #endif

#endif

#endif

/* eof MSCFixes.h */
