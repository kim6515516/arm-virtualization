/*!
 * \file    VirtualEthernetProtocol.h
 * \brief   Virtual ethernet protocol header file.
 * \date    Copyright 2009-2010 ARM Limited. All rights reserved.
 */

#ifndef _VirtualEthernetProtocol_H
#define _VirtualEthernetProtocol_H

#include "sg/SGComponent.h"

class EthernetFrame;

class VirtualEthernet : public sg::Port
{
public:
    declare_slave_behaviour(sendToSlave, void (EthernetFrame* frame));
    declare_master_behaviour(sendToMaster, void (EthernetFrame* frame));
    
    VirtualEthernet() {
        define_behaviour(sendToSlave);
        define_behaviour(sendToMaster);
    }
};

#endif
