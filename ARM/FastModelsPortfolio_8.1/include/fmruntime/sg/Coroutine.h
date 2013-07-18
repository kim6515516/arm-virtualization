/*!
 * \file    Coroutine.h
 * \brief   class wrapping coroutine like functionality
 * \date    Copyright 2005 ARM Limited. All rights reserved.
 * \author  Graeme Barnes.
 *
 * 
 */

#ifndef ARM_SG_COROUTINE_H
#define ARM_SG_COROUTINE_H


namespace sg {

/////////////////////////////////////////////////////////////////////////////////////////////

/* A thread is a concurrently schedulable process which can suspend its action by
   switching control to another thread.

   Each thread has its own stack and stack pointer which is current when the thread
   is running. The thread has a start routine which is invoked when the thread is
   started. Thread may be restarted, it is up to higher layers to ensure that threads
   don't leak resources.

   \TODO possibly add a cleanup routine called when the thread exits cleanly?

   There is no concept of parent/child threads, each thread exists in isolation. This
   has the consequence that a thread routine must not return as there is nowhere to go
   once the thread ends (it will call abort()). 

   The threads have no innate concept of scheduling, this must be handled by another
   layer.

   There must be an initial thread, from which other threads can be spawned. This thread
   has no thread routine as it represents the current 'real' thread that is running. Once
   an initial thread has been created, new threads can be spawned and the initial thread
   can yield to the new thread (and vice versa).
*/

class Coroutine_Impl;

class Coroutine
{
    static const unsigned int default_stack_size = 32768;

    // TODO - these should be moved to the implementation

    // WARNING - sp MUST be first, assembler routines in linux versions RELY on it
    unsigned char* sp;          // stack pointer when thread isn't active
    unsigned char* stack;       // fixed size stack frame for thread
    unsigned int   stack_size;  // size of stack frame

    char*          name;        // thread name, always useful

    Coroutine_Impl* impl;       // internal data

    friend class Coroutine_Impl;
    friend class TestCoroutine;


public:
    // This is the routine which must be implemented by the derived class
    // when the thread is started
    virtual void CoroutineStart() = 0;

protected:
    // Allocate space for a coroutine. The coroutine must be started before  
    Coroutine(const char* name_ = "Unnamed thread", unsigned int stack_size=default_stack_size);

public:
    virtual ~Coroutine();

    const char* Name() const { return name; }

    // These should probably be protected because they must only be called from the currently
    // active coroutine.
 
    // (Re)start a coroutine running
    //    current stack stack will be stored in this threads state block
    // returns the thread that switched back to this one
    Coroutine* Start(Coroutine* new_thread);

    // switch control to another thread that has already been started
    // returns the thread that switched back to this one
    Coroutine* SwitchTo(Coroutine* new_thread);
};

} // namespace sg

#endif // ARM_SG_COROUTINE_H
