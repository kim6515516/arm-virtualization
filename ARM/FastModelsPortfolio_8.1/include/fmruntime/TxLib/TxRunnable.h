/*
 * TxLib: TxRunnable.h - Portable multithreading
 *
 * Copyright 1997-2012 ARM Limited.
 * All rights reserved.
 */


#ifndef TxRunnable_h
#define TxRunnable_h

class TxRunnable
{
 public:
	virtual ~TxRunnable() {}
	virtual void runThread()=0;
};

#endif
