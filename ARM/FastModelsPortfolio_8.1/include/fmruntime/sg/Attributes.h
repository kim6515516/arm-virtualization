/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   Attributes.h
 *  \brief  Abstraction for useful compiler hints
 *  \date   Copyright ARM Limited 2013 All Rights Reserved.
 *
 *  This file is not part of a stable public API and it may
 *  change without notice.
 *
 */

#ifndef INCLUDED_ATTRIBUTES_H
#define INCLUDED_ATTRIBUTES_H


#if defined(__GNUC__)
    /* SG_FORCE_INLINE: A compiler hint prefix to inline this function */
    #define SG_FORCE_INLINE __inline

    /* SG_PURE: Function has no side effects except return values */
    #define SG_PURE         __attribute__((pure))

    /* SG_CONST: Function is pure *and* doesn't depend on anything but the function arguments
     * and doesn't depend on dereferenced argument pointers.
     */
    #define SG_CONST        __attribute__((const))

    /* SG_DEPRECATED: Warn if a variable or type is used anywhere in the program */
    #define SG_DEPRECATED   __attribute__((deprecated))

    /* SG_UNUSED: Tell the compiler a variable is intentionally unused */
    #define SG_UNUSED       __attribute__((unused))

    /* SG_NORETURN: Hint to compiler that the function never returns.
     * Useful to hide spurious uninitialised value warnings in callers.
     */
    #define SG_NORETURN     __attribute__((noreturn))

    /* SG_FORMATSTR: Used to indicate we're implementing a printf/scanf-like function */
    /* NB if using with class functions, the function has an implicit 'this' as the first arg */
    #define SG_FORMATSTR(type, fmt_idx, var_idx) __attribute__((format(type, fmt_idx, var_idx)))

#elif defined(_MSC_VER)
    #define SG_FORCE_INLINE __forceinline
    #define SG_PURE
    #define SG_CONST
    #define SG_DEPRECATED
    #define SG_UNUSED
    #define SG_NORETURN
    #define SG_FORMATSTR(type, fmt_idx, var_idx)

#else
    #define SG_FORCE_INLINE
    #define SG_PURE
    #define SG_CONST
    #define SG_DEPRECATED
    #define SG_UNUSED
    #define SG_NORETURN
    #define SG_FORMATSTR(type, fmt_idx, var_idx)
#endif

#endif
/* eof Attributes.h */
