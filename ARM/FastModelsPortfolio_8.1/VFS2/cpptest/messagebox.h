/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H


/* message box 'device driver'
    on the device side, we actually want to compose on the fly
    this requires:
      'locking' the device and getting the regs interface
      sending a start message
      putting data on every argument write
      sending an end message
      returning status declaring whether there is data waiting
      
      In future we'll lock a buffer making it easy to send blocks of data
      rather than using a device interface
*/

class MessageBox
{
protected:
    MessageBox() {}

public:
    static MessageBox* Instantiate(uint32_t dev_base);

    virtual ~MessageBox() {}

    virtual uint32_t getId()                = 0;
    virtual void*    start(uint32_t len)    = 0;
    virtual int      end(uint32_t len)      = 0;
    virtual void*    receive(uint32_t* len) = 0;
    virtual bool     ready()                = 0;
};

#endif // MESSAGEBOX_H
