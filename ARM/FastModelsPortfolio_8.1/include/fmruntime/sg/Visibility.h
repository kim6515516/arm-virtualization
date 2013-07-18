/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   Visibility.h
 *  \brief  Abstraction for symbol visibility in DSOs
 *  \date   Copyright ARM Limited 2011 All Rights Reserved.
 *
 *  This file is not part of a stable public API and it may
 *  change without notice.
 *
 *  Win32 requires symbol visibility modifiers for DSOs. Historically SYSV DSOs
 *  do not not however modern versions of the GNU toolchain support it and it
 *  can have size benefits and allow the compiler to generate more optimal
 *  code. In order to make symbol visibility work under Linux objects destined
 *  to be linked into shared objects should be compiled with
 *  -fvisibility=hidden. However care must be taken as system headers or
 *  headers for thirdparty libraries may not be expecting to be compiled with
 *  such attributes. Care must also be taken if the program at any point
 *  compares function pointers to inline methods or functions. This must be
 *  globally visibile, however it's better remove such behaviour from the
 *  program. Also if the interface to the DSO includes any C++ entities with
 *  vague linkage such as:
 *      Out-of-line Functions
 *      Static Data
 *      Virtual Tables
 *      Typeinfo
 *      Constructors or Destructors
 *      Instantiated Templates
 *  Then these must have default visibility. The most obvious case here is
 *  typeinfo required for catching C++ exceptions. Again the best idea is to not
 *  throw exceptions across shared object boundaries.
 *
 *  In order to use this file each DSO that is built needs to wrap the defines
 *  provided by this file in its own defines. For example for the FOO:
 *  
 *  #if defined(FOO_STATIC)
 *      #define FOO_DSO
 *  #elif defined(FOO_BUILDING_DSO)
 *      #define FOO_DSO SG_DSO_EXPORT
 *  #else
 *      #define FOO_DSO SG_DSO_IMPORT
 *  #endif
 * 
 *  This assumes structure means that all symbols that are exported or imported
 *  are decorated with FOO_DSO when building the DSO FOO_BUILDING_DSO must be
 *  defined. When using the DSO nothing needs to be defined. If the code is also
 *  compiled into a static library then FOO_STATIC must be define when both
 *  building and using the code.
 *
 */

#ifndef INCLUDED_VISIBILITY_H
#define INCLUDED_VISIBILITY_H

#if defined(_WIN32)
    #if defined(_MSC_VER)
        #define SG_DSO_EXPORT __declspec(dllexport)
        #define SG_DSO_IMPORT __declspec(dllimport)
        #define SG_DSO_LOCAL    
    #else
        #error "Unsupported Compiler"
    #endif
#elif defined(__unix__) || defined(__unix) || defined(unix)
    #if __GNUC__ >= 4
        #define SG_DSO_EXPORT __attribute__((visibility ("default")))
        #define SG_DSO_IMPORT
        #define SG_DSO_LOCAL __attribute__((visibility ("hidden")))
    #else
        #define SG_DSO_EXPORT
        #define SG_DSO_IMPORT   
    #endif
#else
    #error "Unsupported OS"
#endif

#endif
/* eof Visibility.h */
