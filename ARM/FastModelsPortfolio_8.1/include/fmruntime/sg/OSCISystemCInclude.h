/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   OSCISystemCInclude.h
 *  \brief  Workaround for problematic defines in OSCI SystemC
 *  \date   Copyright ARM Limited 2011 All Rights Reserved.
 *  
 *  In all version of OSCI SystemC 2.2 sc_cmnhdr.h does a variety of things
 *  which we don't want to happen. This file prevents that header from being
 *  included and redoes the things we do want to happen.
 *
 *  This workaround can be defeated by defining SG_NO_SC_CMNHDR_WORKAROUND
 */

#ifndef INCLUDED_OSCISYSTEMCINCLUDE_H
#define INCLUDED_OSCISYSTEMCINCLUDE_H

#ifndef SG_NO_SC_CMNHDR_WORKAROUND

// Prevent sc_cmnhdr.h from being included
#define SC_CMNHDR_H

// Safely include Windows.h
#include <sg/SystemInclude.h>

// Include standard library headers that sc_cmnhdr.h would have included
#include <sg/PreInc.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <sg/PostInc.h>

#endif

#ifdef _MSC_VER

// this : used in base member initializer list
#pragma warning(disable: 4355)

// new and delete warning when exception handling is turned on
#pragma warning(disable: 4291)

// in many places implicit conversion to bool
// from other integral types is performed
#pragma warning(disable: 4800)

// unary minus operator applied to unsigned
#pragma warning(disable: 4146)

// multiple copy constructors
#pragma warning(disable: 4521)

// identifier was truncated to '255' characters in the browser information
#pragma warning(disable: 4786)

#endif

// SG SystemC Export requires Dynamic Process Support
#ifndef SC_INCLUDE_DYNAMIC_PROCESSES
    #define SC_INCLUDE_DYNAMIC_PROCESSES
#endif

// SystemC (>=2.3) helper macros to aid branch prediction on GCC (compatible) compilers
#ifndef SC_LIKELY_
    #ifndef __GNUC__
        #define SC_LIKELY_( x )    !!(x)
    #else
        #define SC_LIKELY_( x )    __builtin_expect( !!(x), 1 )
    #endif
#endif
#ifndef SC_UNLIKELY_
    #ifndef __GNUC__
        #define SC_UNLIKELY_( x )  !!(x)
    #else
        #define SC_UNLIKELY_( x )  __builtin_expect( !!(x), 0 )
    #endif
#endif


// Include SystemC which now won't include the problematic file
#include <systemc>

#endif

/* eof OSCISystemCInclude.h */
