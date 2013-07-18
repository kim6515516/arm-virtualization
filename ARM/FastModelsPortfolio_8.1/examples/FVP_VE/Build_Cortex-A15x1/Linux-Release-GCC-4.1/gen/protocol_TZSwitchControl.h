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
 * Abstract interface class protocol_TZSwitchControl for protocol TZSwitchControl.
 */

#ifndef protocol_TZSwitchControl_h_
#define protocol_TZSwitchControl_h_

// Includes from the 'includes' section of this protocol
#line 48 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/TZSwitch.lisa"

        enum TZSwitch_RouteOption
        {
            TZROUTE_IGNORE    = 0,
            TZROUTE_TO_PORT_A = 1,
            TZROUTE_TO_PORT_B = 2,
            TZROUTE_ABORT     = 3
        };

        enum TZSwitch_InputFilter
        {
            TZINPUT_SECURE,
            TZINPUT_NORMAL,
            TZINPUT_ANY
        };
    
#line 38 "./Linux-Release-GCC-4.1/gen/protocol_TZSwitchControl.h"


// Abstract interface for protocol TZSwitchControl
class protocol_TZSwitchControl
{
public:
        virtual ~protocol_TZSwitchControl() {}
        // Abstract protocol members
	virtual void routeAccesses(TZSwitch_InputFilter input, TZSwitch_RouteOption destination) = 0;

};

#endif /* protocol_TZSwitchControl_h_ */

