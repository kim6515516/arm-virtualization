/*
 * Copyright 2003 ARM Limited.
 * Copyright 2012 ARM Limited.
 *
 * All rights reserved.
 * 
 */

/** \file
 * TerminateScheduler exception class.
 */

#ifndef _TerminateScheduler_h_
#define _TerminateScheduler_h_

#include <string>
#include <stdexcept>


// these macros are used from the LISA code
#define TERMINATE_SCHEDULER()                throw TerminateScheduler()
#define TERMINATE_SCHEDULER_MESSAGE(message) throw TerminateScheduler(message)


// TerminateScheduler exception class (thrown when some scheduler terminates)
class TerminateScheduler: public std::exception
{
public:
    TerminateScheduler(const std::string& message="(no message available)") :
    message(message) {}
    ~TerminateScheduler() throw() {}
    virtual const char *what() const throw() { return message.c_str(); }
    std::string message;
};


// Breakpoint reached exception
// (used by InteractivePrintState.cpp (no obsolete))
class BreakpointReached: public TerminateScheduler
{
public: BreakpointReached(): TerminateScheduler("breakpoint reached") {}
};


#define _TerminateScheduler_h_DONE
#elif ! defined(_TerminateScheduler_h_DONE)
#error Included recursively.
#endif
