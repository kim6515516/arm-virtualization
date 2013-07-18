/*
 * TxLib: TxMutex.h - Portable multithreading
 *
 * Copyright 1997-2012 ARM Limited.
 * All rights reserved.
 */


#ifndef TxMutex_h
#define TxMutex_h


class TxMutex
{
public:
  TxMutex();
  ~TxMutex();
  int lock();
  int unlock();
  int trylock();
public:
  void* mutexID;
};

#endif



