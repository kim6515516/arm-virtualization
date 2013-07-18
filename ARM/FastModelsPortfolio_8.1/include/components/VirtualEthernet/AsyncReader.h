/*!
 * \file    AsyncReader.h
 * \brief   Asynchronize reader class for reading devices
 * \date    Copyright 2009-2010 ARM Limited. All rights reserved.
 */


#ifndef _ASYNC_READER_H
#define _ASYNC_READER_H

#include <iostream>
#include <algorithm>

#include "TxLib/TxLib.h"
#include "sg/SystemInclude.h"

#ifdef __unix
    // select
    #include <sys/select.h>

    #include <sys/ioctl.h>
#endif

// Typedef the file descriptor type so return values don't have to be changed.
#ifdef WIN32
    typedef HANDLE descriptor_t;
    typedef DWORD rwsize_t;
#else
    typedef int descriptor_t;
    typedef ssize_t rwsize_t;
#endif

// Errors & interrupted syscall handling
#include <errno.h>

// AsyncSignal
#include "sg/SGScheduler.h"

#define VE_TRACE if (!0) ; else fprintf

/*!
 * Buffer structure for hold a packet
 */
struct BUFFER
{
    unsigned char* data;
    rwsize_t len;
    bool dirty;
};

/*!
 * Working thread to move packet listening to the background
 */
class AsyncReader : public TxRunnable {
public:
    /*!
     * AsyncReader constructor
     */
    AsyncReader(sg::SimulationContext* simulationContext);
    /*!
     * AsyncReader destructor
     */
    virtual ~AsyncReader();
    /*!
     * Initialisation function called immediately after the
     * constructor. Returns false if it failed, so that the newly
     * constructed object can be immediately destroyed again. Default
     * implementation is empty and always returns success; subclasses
     * can override.
     */
    virtual bool init() { return true; }
    /*!
     * Shortcut to read the 'main' file descriptor.
     * @param buf A pointer to the buffer in the memory
     * @param count Number of bytes to read
     * @return read succeed or not
     */
    bool doRead(void* buf, size_t count) { return doRead(fd, buf, count); }
    /*!
     * Shortcut to write the 'main' file descriptor.
     * @param buf A pointer to the buffer in the memory
     * @param count Number of bytes to write
     * @return write succeed or not
     */
    bool doWrite(void* buf, size_t count) { return doWrite(fd, buf, count); }

protected:
    /*!
     * Start listening thread
     */
    void startProcess();
    /*!
     * Routine after receiving read complete signal
     */
    virtual void readComplete() {}
    /*!
     * Send out given data frame
     */
    virtual void sendData(void*, rwsize_t sz) {}
    /*!
     * Send out the head packet in the FIFO
     */
    virtual void sendHeadData() {}
    /*!
     * Open device or file
     */
    virtual bool open() = 0;

private:
    /*!
     * Checks if there is any available data from the file descriptor,
     * and tries to read count bytes if there is. Retries EINTR on Linux
     * @param fd File descriptor
     * @param buf A pointer to the buffer in the memory
     * @param count Number of bytes to read
     * @param len The actual bytes been read
     * @return read succeed or not
     */
    virtual bool doRead(descriptor_t fd, void* buf, size_t count, rwsize_t* len=NULL);
    /*!
     * Write data into the file indicated by a file descriptor. Retries EINTR on Linux.
     * @param fd File descriptor
     * @param buf A pointer to the buffer in the memory
     * @param count Number of bytes to write
     * @param len The actual bytes been written
     * @return write succeed or not
     */
    virtual bool doWrite(descriptor_t fd, void* buf, size_t count, rwsize_t* len=NULL);
    /*!
     * Overwrite runThread in TxRunnable
     */
    virtual void runThread();  // overwrite runThread in TxRunnable
    /*!
     * Read ethernet packets and put them into the FIFO
     * Once received a packet, signal read complete.
     */
    virtual void process();
    /*!
     * Signal callback routine
     */
    void async_callback();

protected:
    static const int MTU = 4096;        //!< Maximum Transmission Unit
    static const int MAX_FIFO = 256;    //!< Maximum fifo size
    BUFFER FIFO[MAX_FIFO];              //!< FIFO for holding incoming packets
    int fifo_start;                     //!< The head of the fifo
    int fifo_end;                       //!< The tail of the fifo
    descriptor_t fd;                    //!< File handle for TAP device
#ifdef WIN32
    OVERLAPPED overlapped_r;            //!< OVERLAPPED structure for Windows asynchronized read
    OVERLAPPED overlapped_w;            //!< OVERLAPPED structure for Windows asynchronized write
#endif
    bool exit;                           //!< Thread exit flag
    sg::AsyncSignal async;               //!< object to generate callbacks in the simulation thread
    TxThread * thread;                   //!< actual listen thread

private:
    TxEvent read_ready;                  //!< set when packet is available to process
};

#endif
