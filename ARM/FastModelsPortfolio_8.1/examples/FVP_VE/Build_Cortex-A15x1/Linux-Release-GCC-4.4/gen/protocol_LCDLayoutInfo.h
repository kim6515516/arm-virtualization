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
 * Abstract interface class protocol_LCDLayoutInfo for protocol LCDLayoutInfo.
 */

#ifndef protocol_LCDLayoutInfo_h_
#define protocol_LCDLayoutInfo_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol LCDLayoutInfo
class protocol_LCDLayoutInfo
{
public:
        virtual ~protocol_LCDLayoutInfo() {}
        // Abstract protocol members
	virtual void setLayoutInfo(int x, int y, uint32_t w, uint32_t h) = 0;

};

#endif /* protocol_LCDLayoutInfo_h_ */

