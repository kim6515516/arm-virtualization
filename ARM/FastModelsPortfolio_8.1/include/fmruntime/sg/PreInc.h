/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   PreInc.h
 *  \brief  Perform operations required before including external header files.
 *  \date   Copyright ARM Limited 2008-2011 All Rights Reserved.
 *
 *  For MSVC++ Push warning levels down for inclusion of external headers and
 *  make sure relevant predefines are passed before standard type headers are
 *  included.
 *
 *  For GCC and compatible compilers make symbols have default visibility
 *  
 *  This file is not part of a stable public API and it may
 *  change without notice.
 *
 *  \remark Intentionally don't guard against multiple inclusion. 
 */

#if defined(_MSC_VER) && !defined(SG_WARNINGS_PUSHED_TO_LEVEL_1)
    #define SG_WARNINGS_PUSHED_TO_LEVEL_1
    #pragma warning( push, 1 )
#endif

#if (__GNUC__ >= 4) && !defined(SG_VISIBILITY_PUSHED_TO_DEFAULT)
    #define SG_VISIBILITY_PUSHED_TO_DEFAULT
    #pragma GCC visibility push(default)
#endif

/* eof PreInc.h */
