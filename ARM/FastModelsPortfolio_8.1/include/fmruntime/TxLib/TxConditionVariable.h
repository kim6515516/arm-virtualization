/*
 * TxLib: TxConditionVariable.h - Condition variable class.
 *
 * Copyright 2012 ARM Limited.
 * All rights reserved.
 */

#ifndef TX_CONDITION_VARIABLE__H
#define TX_CONDITION_VARIABLE__H

/*!
 * \file    TxConditionVariable.h
 * \brief   Active object class.
 * \date    Copyright 2012 ARM Limited. All rights reserved.
 */

/* Includes */
#if defined(_WIN32)
#include <set>
#endif  /* defined(_WIN32) */

#include "TxMutex.h"

/* Data types */

/**
 * \brief   Condition variable class.
 *
 * Condition variables are synchronization primitives that enable threads to
 * wait until a particular condition occurs.
 */
class TxConditionVariable {

    /* Creation/destruction */
    public:
       TxConditionVariable();
       ~TxConditionVariable();

   /* Accessors */
       void wait(TxMutex &);
       int wait(TxMutex &, unsigned);
       void notify();
       void notifyAll();

   /* Implementation  */
   private:
       void * m_conditionID;
#if defined(_WIN32)
       std::set<void *> m_waitSet;
#endif  /* defined(_WIN32) */

       /* Copying- Disabled */
       TxConditionVariable(const TxConditionVariable &);
       TxConditionVariable & operator=(const TxConditionVariable &);
};

#endif  /* defined(TX_CONDITION_VARIABLE__H) */
