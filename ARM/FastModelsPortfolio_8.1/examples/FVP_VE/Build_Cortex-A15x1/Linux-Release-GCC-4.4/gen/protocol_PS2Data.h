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
 * Abstract interface class protocol_PS2Data for protocol PS2Data.
 */

#ifndef protocol_PS2Data_h_
#define protocol_PS2Data_h_

// Includes from the 'includes' section of this protocol
#line 9 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PS2DataProtocol.lisa"

        enum ps2clockdata_state {
            PS2_Inhibit,         //!< No comms allowed : !clock
            PS2_Request_To_Send, //!< PS/2 device should read from KMI: clock && !data
            PS2_Ready            //!< Ready for PS/2 device to send data: clock && data
        };
    
#line 29 "./Linux-Release-GCC-4.4/gen/protocol_PS2Data.h"


// Abstract interface for protocol PS2Data
class protocol_PS2Data
{
public:
        virtual ~protocol_PS2Data() {}
        // Abstract protocol members
	virtual void setClockData(enum ps2clockdata_state ) = 0;
	virtual uint8_t getData() = 0;
	virtual void putData(uint8_t data) = 0;

};

#endif /* protocol_PS2Data_h_ */

