/*!
 * \file    EthernetFrame.h
 * \brief   Ethernet frame class
 * \date    Copyright 2009-2010 ARM Limited. All rights reserved.
 */

// EthernetFrame encapsulates an ethernet frame in a broken up format which is
// more accessible by components.

// Frame format in bytes:
// [6 dest mac] [6 src mac] [2 ethertype] [46-1500 data] [4 crc]
// Frame format (from wikipedia:)

#ifndef _ETHERNET_FRAME_H
#define _ETHERNET_FRAME_H

// For memcmp
#include <string.h>

// Everything is in network byte order
class EthernetFrame {
    protected:

        static const int dest_offset = 0;
        static const int src_offset = 6;
        static const int ethertype_offset = 12;
        static const int data_offset = 14;

        // The n indicates it's 'negative'- how many bytes from the end.
        static const int n_crc_offset = 4;


    public:
        unsigned char* buf;
        int buflen;

        // Pointers to interesting bits
        unsigned char* dest_addr;
        unsigned char* src_addr;
        unsigned char* ethertype;
        unsigned char* crc;

        EthernetFrame(unsigned char* newbuf, int len);

        // Returns true if this frame should be routed to 'addr'. i.e. if
        // dest_addr is:
        //  - equal to addr
        //  - equal to broadcast address
        bool routeTo(const unsigned char* addr);
        
        // Returns length of frame.
        unsigned int length() { return buflen; }
};

#endif
