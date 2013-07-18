/*
 * TxLib: TxThread.h - Portable multithreading.
 *
 * Copyright 2001-2012 ARM Limited.
 * All rights reserved.
 */


#ifndef TxThread_h
#define TxThread_h


class TxRunnable;

class TxThread
{
public:
  TxThread(TxRunnable*);
  ~TxThread();
    
  // join thread (wait until thread exits)
  // status should be always 0
  // call from outside thread only
  int join(void **status);
    
  // Linux: pthread_detach
  // Windows: not supported (runtime assertion)
  // call from outside thread only
  int detach();
    
  // exit thread
  // value_ptr should be always 0
  // call from inside thread only
  void exit(void *value_ptr);
    
  // Linux: pthread_kill
  // Windows: not supported (runtime assertion)
  // call from outside thread only
  int kill(int sig);
    
  // Linux: pthread_cancel
  // Windows: semantics unclear
  // call from outside thread only
  int cancel();
   
  // Linux: sched_yield
  // Windows: SwitchToThread
  // call from inside thread only
  static void yieldCurrentThread();

  // private method which is internal to this class, do not call directly
  // it is only public to avoid friend declarations for the global 'thread start' 
  // functions which need to call this method
  void start();
private:
  TxRunnable *target;
  void* threadID;

#ifdef WIN32
public:
  // Windows only: see cancel()
  // call from inside thread only
  void testcancel();
private:
  int m_bCancel;
#endif
};

#endif


// Local Variables: ***
// mode:c++ ***
// End: ***

