/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */
 
/* 
 * Messagebox definitions shared between messagebox device and driver
 */

#ifndef MBOXTYPES_H
#define MBOXTYPES_H

enum MessageBoxDefs 
{
    // device register offsets

    MBOX_REG_ID      = 0x00,
    MBOX_REG_DATA    = 0x04,
    MBOX_REG_CONTROL = 0x08,
    MBOX_REG_STATUS  = 0x0c,
    MBOX_REG_START   = 0x10,
    MBOX_REG_END     = 0x14,
    MBOX_REG_IRQMASK = 0x18,

    // control register commands

    MBOX_CONTROL_START = 1,          // start sending a message
    MBOX_CONTROL_END   = 2,          // end sending a message
    MBOX_CONTROL_CANCEL= 3,          // cancel sending a message
    
    // status register bits

    MBOX_STATUS_RXEMPTY = (1<<0),    // no more incoming message data
    MBOX_STATUS_TXFULL  = (1<<1),    // no more room for an outgoing message
    MBOX_STATUS_RXREADY = (1<<2),    // a new incoming message is ready to be received
    
    // device memory layout

    MBOX_REGISTER_BASE = 0x0,        // base of device registers
    MBOX_REGISTER_SIZE = 0x1000,     // size of register region
    MBOX_BUFFER_BASE   = 0x1000,     // base of shared buffer
    MBOX_BUFFER_SIZE   = 0xf000,     // size of buffer region
    MBOX_DEVICE_SIZE   = MBOX_REGISTER_SIZE + MBOX_BUFFER_SIZE
};     

#endif // MBOXTYPES_H
