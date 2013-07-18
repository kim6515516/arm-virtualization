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
 * Abstract interface class protocol_Builtin__AddressablePortProtocol for protocol Builtin__AddressablePortProtocol.
 */

#ifndef protocol_Builtin__AddressablePortProtocol_h_
#define protocol_Builtin__AddressablePortProtocol_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol Builtin__AddressablePortProtocol
class protocol_Builtin__AddressablePortProtocol
{
public:
        virtual ~protocol_Builtin__AddressablePortProtocol() {}
        // Abstract protocol members
	virtual sg::Port* mapRange(MxU64 , MxU64 , MxU64 , MxU64 ) = 0;
	virtual sg::Port* mapDefault() = 0;
	virtual void unmapRange(sg::Port* ) = 0;

};

#endif /* protocol_Builtin__AddressablePortProtocol_h_ */

