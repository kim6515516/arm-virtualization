/*
 * TxLib: TxEvent.h - Portable multithreading
 *
 * Copyright 1997-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef _TXEVENT_H
#define _TXEVENT_H

class TxEvent
{
public:
  TxEvent(int manualReset=1, int initialState=0);
  ~TxEvent();
  int SetEvent();
  int ResetEvent();
  int PulseEvent();
  int Wait();
  int TimedWait(unsigned mSec);
private:
#ifdef WIN32
  void* m_eventID;
#else
  void* m_mutexID;
  void* m_conditionID;
  int m_manualReset;
  int m_state;
#endif
};

#endif
