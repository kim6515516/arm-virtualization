/*
 * TxLib: TxActiveObject.h - Active object class.
 *
 * Copyright 2012 ARM Limited.
 * All rights reserved.
 */

#ifndef TX_ACTIVE_OBJECT__H
#define TX_ACTIVE_OBJECT__H

/*!
 * \file    TxActive.h
 * \brief   Active object class.
 * \date    Copyright 2012 ARM Limited. All rights reserved.
 */

/* Includes */
#include "TxThread.h"
#include "TxSharedQueue.h"

/* Data types */

/**
 * \brief   Active object class.
 *
 * \param   M message type, must implement @c operator() function and support
 *          copying. The default constructor will be used by the active object
 *          to flush the message queue.
 * \param   MQ message queue type, default to TxSharedQueue<M>.
 *
 * Usage:
 * \code
 * TxActiveObject<M> * a = TxActiveObject<M>::create();
 * ...
 * a->push(m1);
 * ...
 * a->push(m2);
 * ...
 * delete a;
 * \encode
 */
template <class M, class MQ = TxSharedQueue<M> >
class TxActiveObject: public TxRunnable {

    /* Creation/destruction */
    public:
       static TxActiveObject * create(std::size_t /* maxSize */ = 4096);
       virtual ~TxActiveObject();

   /* Accessors */
       void push(const M &);
       void done();

   /* Implementation  */
   private:

       /* Member variables */
       MQ m_mq;                 /* Message queue */
       TxThread * m_thread;     /* Worker thread */
       volatile bool m_done;    /* Job done? */

       /* Construction */
       TxActiveObject(std::size_t);

       /* Worker thread */
       void runThread();

       /* Copying- Disabled */
       TxActiveObject(const TxActiveObject &);
       TxActiveObject & operator=(const TxActiveObject &);
};

/* Functions */

/**
 * \brief       Creation.
 *
 * Returns a pointer to a newly created active object.
 *
 * \param       maxSize specifies the maximum number of messages the message
 *              queue can hold, defaults to 4096.
 */
template <class M, class MQ>
inline TxActiveObject<M, MQ> *
TxActiveObject<M, MQ>::create(std::size_t maxSize /* = 4096 */) {
    TxActiveObject * a = new TxActiveObject(maxSize);

    a->m_thread = new TxThread(a);
    return (a);
}

/**
 * \brief       Destructor.
 *
 * Blocks until all pending message are processed.
 */
template <class M, class MQ>
inline
TxActiveObject<M, MQ>::~TxActiveObject() {
    push(M());
    m_thread->join(NULL);
    delete m_thread;
}

/**
 * \brief       Push asynchronously message on queue.
 */
template <class M, class MQ>
inline void
TxActiveObject<M, MQ>::push(const M & m) {
    m_mq.push(m);
}

/**
 * \brief       Tell worker thread to exit.
 */
template <class M, class MQ>
inline void
TxActiveObject<M, MQ>::done() {
    m_done = true;
}

/**
 * \brief       Private constructor.
 *
 * \param       maxSize specifies the maximum number of messages the message
 *              queue can hold.
 */
template <class M, class MQ>
inline
TxActiveObject<M, MQ>::TxActiveObject(std::size_t maxSize):
    m_mq(maxSize),
    m_thread(NULL),
    m_done(false) {
}

/**
 * \brief       Worker thread of this active object.
 *
 * Blocks until messages are available on the queue and process them until told
 * to exit.
 */
template <class M, class MQ>
inline void
TxActiveObject<M, MQ>::runThread() {
    M m;

    while (! m_done) {
        m_mq.pop(m);
        m();
    }
}

#endif  /* defined(TX_ACTIVE_OBJECT__H) */
