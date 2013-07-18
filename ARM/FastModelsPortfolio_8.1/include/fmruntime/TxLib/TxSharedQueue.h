/*
 * TxLib: TxSharedQueue.h - Synchronized shared queue.
 *
 * Copyright 2012 ARM Limited.
 * All rights reserved.
 */

#ifndef TX_SHARED_QUEUE__H
#define TX_SHARED_QUEUE__H

/*!
 * \file    TxSharedQueue.h
 * \brief   Synchronized shared queue.
 * \date    Copyright 2012 ARM Limited. All rights reserved.
 */

/* Includes */
#include <cstddef>
#include <queue>
#include <algorithm>

#include "TxMutex.h"
#include "TxConditionVariable.h"

/* Data types */

/**
 * \brief   Multiple producer, multiple consumer synchronized queue.
 *
 * Specialization of the message queue idiom as a synchronized shared queue.
 *
 * \param   T element type, must implement copy constructor and assignement
 *          operator.
 */
template <class T>
class TxSharedQueue {

    /* Construction */
    public:
       explicit TxSharedQueue(std::size_t /* maxSize */ = 4096);
       ~TxSharedQueue();

   /* Accessors */
       void push(const T &);
       void pop(T &);
       bool empty() const;
       std::size_t size() const;
       std::size_t getMaxSize() const;

   /* Implementation  */
   private:

       /* Variable members */
       mutable TxMutex m_mutex;
       TxConditionVariable m_notEmpty;
       TxConditionVariable m_notFull;
       std::queue<T> m_queue;
       std::size_t m_maxSize;

       /* Copying- Disabled */
       TxSharedQueue(const TxSharedQueue &);
       TxSharedQueue & operator=(const TxSharedQueue &);
};

/* Functions */

/**
 * \brief       Constructor.
 *
 * \param       maxSize specifies the maximum number of elements this shared
 *              queue can hold.
 */
template <class T>
inline
TxSharedQueue<T>::TxSharedQueue(std::size_t maxSize /* = 4096 */):
    m_maxSize(std::max(std::size_t(1), maxSize)) {
}

/**
 * \brief       Destructor.
 */
template <class T>
inline
TxSharedQueue<T>::~TxSharedQueue() {
}

/**
 * \brief       Insert element.
 *
 * Adds a new element at the end of this shared queue, after its current last
 * element.
 * The content of this new element is initialized to a copy of @a t.
 * This function will block when this shared queue has reached its maximum size,
 * that is when size() is greater than or equal to getMaxSize().
 *
 * \param       t a reference to the element to insert.
 *
 * \see         size(), getMaxSize()
 */
template <class T>
inline void
TxSharedQueue<T>::push(const T & t) {
    TxCriticalSection lock(m_mutex);

    while (m_queue.size() >= m_maxSize) {
        m_notFull.wait(m_mutex);
    }
    m_queue.push(t);
    m_notEmpty.notify();
}

/**
 * \brief       Access and delete next element.
 *
 * Access the next element in this shared queue and removes it, effectively
 * reducing this shared queue's size by one.
 * This functions calls the removed element's destructor.
 * This function will block when there are no elements in this shared queue,
 * that is when empty() returns @c true.
 *
 * \param       t a reference to the accessed element.
 */
template <class T>
inline void
TxSharedQueue<T>::pop(T & t) {
    TxCriticalSection lock(m_mutex);

    while (m_queue.empty()) {
        m_notEmpty.wait(m_mutex);
    }
    t = m_queue.front();
    m_queue.pop();
    m_notFull.notify();
}

/**
 * \brief       Test whether shared queue is empty.
 *
 * Returns whether this shared queue is empty, that is whether its size is @c 0.
 */
template <class T>
inline bool
TxSharedQueue<T>::empty() const {
    TxCriticalSection lock(m_mutex);

    return (m_queue.empty());
}

/**
 * \brief       Return size.
 *
 * Returns the number of elements in this shared queue.
 */
template <class T>
inline std::size_t
TxSharedQueue<T>::size() const {
    TxCriticalSection lock(m_mutex);

    return (m_queue.size());
}

/**
 * \brief       Return maximum size.
 *
 * Returns the maximum number of elements in this shared queue.
 */
template <class T>
inline std::size_t
TxSharedQueue<T>::getMaxSize() const {
    return (m_maxSize);
}

#endif  /* defined(TX_SHARED_QUEUE__H) */
