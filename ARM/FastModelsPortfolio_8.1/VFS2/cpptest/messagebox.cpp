/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*
    Very simple implementation of a messagebox for passing messages (data) between
    the vm and a device.

    Currently this implements just enough to satisfy the needs of VFS
*/

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "MBoxTypes.h"
#include "messagebox.h"

// The message box can use a memory mapped buffer (fast), or a pio data register
// #define USE_PIO

class MessageBoxImpl : public MessageBox
{
public:

    // structure mapped to memory mapped registers 

    struct MBRegs
    {
        uint32_t id;
        uint32_t data;
        uint32_t control;
        uint32_t status;
        uint32_t start;
        uint32_t end;
        uint32_t irqmask;
    };

    volatile MBRegs* dev;

    uint32_t* buffer;

    MessageBoxImpl(uint32_t dev_base)
    {
        dev = (MBRegs*)dev_base;

        // If we're using PIO, allocate a local buffer, otherwise use the one provided
        // by the device
#ifdef USE_PIO
        buffer = new uint32_t[MBOX_BUFFER_SIZE];
#else
        buffer = (uint32_t*)(dev_base+MBOX_BUFFER_BASE);
#endif
    }

    virtual ~MessageBoxImpl()
    {
#ifdef USE_PIO
        delete buffer;
#endif
    }

    // return a pointer to a buffer which can be used for composing a message. Depending
    // on configuration, this could be a locally allocated buffer or the one in the device
    virtual void* start(uint32_t len)
    {
        // new message

        dev->control = MBOX_CONTROL_START;

        // initialise the buffer pointers

        dev->start = 0;
        dev->end = 0;

        return buffer;
    }

    // Send the buffer (hopefully populated by the caller) to the device. If the buffer
    // is memory mapped, this is trivial
    virtual int end(uint32_t len)
    {
#ifdef USE_PIO
        // buffer is in local memory, copy it word by word to the device
        uint32_t* bptr = buffer;
        assert((len & 3) == 0);

        len = len/4;

        while (len > 0)
        {
            dev->data = *bptr++;
            --len;
        }   
#else
        // buffer is already on the device, we just need to set the end pointer so the device
        // knows the length of the message
        dev->end = len;
#endif

        // actually send it
        dev->control = MBOX_CONTROL_END;

        // not strictly necessary, tell the caller whether the reply is immediately available
        return ready();
    }

    // Return whether there is a packet ready to receive
    virtual bool ready()
    {
        return (dev->status & MBOX_STATUS_RXREADY) != 0;
    }

    // receive a packet of data from the device. If we're using PIO, read it out into
    // the local buffer, otherwise just returna pointer to the device buffer
    virtual void* receive(uint32_t* len)
    {
#ifdef USE_PIO
        uint32_t bidx = 0;

        while ((dev->status & MBOX_STATUS_RXEMPTY) == 0)
            buffer[bidx++] = dev->data;

        *len = bidx*4;

        return buffer;
#else
        *len = dev->end - dev->start;

        return buffer + dev->start;
#endif

    }

    virtual uint32_t getId()
    {
        return dev->id;
    }
};


MessageBox* MessageBox::Instantiate(uint32_t dev_base)
{
    return new MessageBoxImpl(dev_base);
}

