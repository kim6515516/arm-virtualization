/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   IncludeMeFirst.h
 *  \brief  Predefines for all translation units 
 *  \date   Copyright ARM Limited 2008-2011 All Rights Reserved.
 *  
 *  Contains defines that must be done before anything else in all translation
 *  units.
 */

#ifndef INCLUDED_FSINCLUDEMEFIRST_H
#define INCLUDED_FSINCLUDEMEFIRST_H

/* Request xxx_C() macros */
#if !defined(__STDC_CONSTANT_MACROS)
    #define __STDC_CONSTANT_MACROS
#endif

/* Request xxx_MAX macros */
#if !defined(__STDC_LIMIT_MACROS)
    #define __STDC_LIMIT_MACROS
#endif

/* Request PRIxxx macro */
#if !defined(__STDC_FORMAT_MACROS)
    #define __STDC_FORMAT_MACROS
#endif

/* Define a single macro indicating that we're targeting a 64-bit host */
#if defined(__x86_64__) || defined(_M_X64)
    #define SG_X86_64 1
#endif

/* Fix problems due to includes of Windows.h defining a macroised min and max
 * which conflict with std::min and std::max. This catches anyone who has used
 * IncludeMeFirst but has not used SystemInclude */
#if defined(_WIN32) && !defined(NOMINMAX)
    #define NOMINMAX
#endif

#endif
/* eof IncludeMeFirst.h */
