/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   PostInc.h
 *  \brief  Perform operations required after including external header files.
 *  \date   Copyright ARM Limited 2008-2011 All Rights Reserved.
 *  
 *  For MSVC++ Pop warnings level back up after inclusion of external headers
 *
 *  For GCC and compatible compilers pop symbol visibility back.
 *
 *  This file is not part of a stable public API and it may
 *  change without notice.
 *
 *  \remark Intentionally don't guard against multiple inclusion
 */

#if defined(_MSC_VER) && defined(SG_WARNINGS_PUSHED_TO_LEVEL_1)
    #pragma warning( pop )
    #undef SG_WARNINGS_PUSHED_TO_LEVEL_1
#endif

#if (__GNUC__ >= 4) && defined(SG_VISIBILITY_PUSHED_TO_DEFAULT)
    #pragma GCC visibility pop
    #undef SG_VISIBILITY_PUSHED_TO_DEFAULT
#endif

/* eof PostInc.h */
