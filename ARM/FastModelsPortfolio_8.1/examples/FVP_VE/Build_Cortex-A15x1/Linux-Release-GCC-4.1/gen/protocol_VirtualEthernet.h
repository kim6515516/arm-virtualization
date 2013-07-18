/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2007 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Abstract interface class protocol_VirtualEthernet for protocol VirtualEthernet.
 */

#ifndef protocol_VirtualEthernet_h_
#define protocol_VirtualEthernet_h_

// Includes from the 'includes' section of this protocol
#line 15 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetProtocol.lisa"

        #include "components/VirtualEthernet/Protocol/EthernetFrame.h"
    
#line 25 "./Linux-Release-GCC-4.1/gen/protocol_VirtualEthernet.h"


// Abstract interface for protocol VirtualEthernet
class protocol_VirtualEthernet
{
public:
        virtual ~protocol_VirtualEthernet() {}
        // Abstract protocol members
	virtual void sendToSlave(EthernetFrame* frame) = 0;
	virtual void sendToMaster(EthernetFrame* frame) = 0;

};

#endif /* protocol_VirtualEthernet_h_ */

