/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   Framework/include/sg/Thread.h
 *  \brief  Utility functions for threading 
 *  \date   Copyright ARM Limited 2012 All Rights Reserved.
 *  
 *  This file is not part of a stable public API and it may
 *  change without notice.
 */

#ifndef INCLUDED_THREAD_H
#define INCLUDED_THREAD_H

#include <sg/SystemInclude.h>

#if defined(__unix__)
    #include <pthread.h>
#endif

namespace sg {

#if defined(_WIN32)

#define SG_THREADLOCAL __declspec(thread)

typedef DWORD threadId_t;

inline threadId_t thread_self()
{
    return GetCurrentThreadId();
}

inline int thread_equal(threadId_t t1, threadId_t t2)
{
    return ((t1 == t2) ? 1 : 0);
}

#elif defined(__unix__)

#define SG_THREADLOCAL __thread

typedef pthread_t threadId_t;

inline threadId_t thread_self()
{
    return pthread_self();
}

inline int thread_equal(threadId_t t1, threadId_t t2)
{
    return pthread_equal(t1,t2);
}
#else
    #error #error "Threads are not supported on this platform"
#endif

}

#endif

/* eof Thread.h */
