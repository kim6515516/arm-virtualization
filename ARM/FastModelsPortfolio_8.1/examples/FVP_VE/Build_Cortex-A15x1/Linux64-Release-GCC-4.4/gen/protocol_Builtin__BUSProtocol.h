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
 * Abstract interface class protocol_Builtin__BUSProtocol for protocol Builtin__BUSProtocol.
 */

#ifndef protocol_Builtin__BUSProtocol_h_
#define protocol_Builtin__BUSProtocol_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol Builtin__BUSProtocol
class protocol_Builtin__BUSProtocol
{
public:
        virtual ~protocol_Builtin__BUSProtocol() {}
        // Abstract protocol members
	virtual MxStatus read8(MxU32 , MxU8& ) = 0;
	virtual MxStatus read16(MxU32 , MxU16& ) = 0;
	virtual MxStatus read32(MxU32 , MxU32& ) = 0;
	virtual MxStatus read64(MxU32 , MxU64& ) = 0;
	virtual MxStatus read(MxU32 , MxU32* ) = 0;
	virtual MxStatus write8(MxU32 , MxU8 ) = 0;
	virtual MxStatus write16(MxU32 , MxU16 ) = 0;
	virtual MxStatus write32(MxU32 , MxU32 ) = 0;
	virtual MxStatus write64(MxU32 , MxU64 ) = 0;
	virtual MxStatus write(MxU32 , MxU32* ) = 0;
	virtual MxStatus readDbg8(MxU32 , MxU8& ) = 0;
	virtual MxStatus readDbg16(MxU32 , MxU16& ) = 0;
	virtual MxStatus readDbg32(MxU32 , MxU32& ) = 0;
	virtual MxStatus readDbg64(MxU32 , MxU64& ) = 0;
	virtual MxStatus readDbg(MxU32 , MxU32* ) = 0;
	virtual MxStatus writeDbg8(MxU32 , MxU8 ) = 0;
	virtual MxStatus writeDbg16(MxU32 , MxU16 ) = 0;
	virtual MxStatus writeDbg32(MxU32 , MxU32 ) = 0;
	virtual MxStatus writeDbg64(MxU32 , MxU64 ) = 0;
	virtual MxStatus writeDbg(MxU32 , MxU32* ) = 0;

};

#endif /* protocol_Builtin__BUSProtocol_h_ */

