/*
 * TxLib: TxCriticalSection.h - Portable multithreading 
 * Copyright (C) ARM Limited 1998-2007. All rights reserved.
 */


#ifndef TxCriticalSection_h
#define TxCriticalSection_h

#include "TxMutex.h"


class TxCriticalSection
{
 public:
	explicit TxCriticalSection(TxMutex& mutex);
	~TxCriticalSection();

 private:
	TxMutex& m_mutex;
};

#endif //TxCriticalSection_h
