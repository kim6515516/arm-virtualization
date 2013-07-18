/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2005 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Class definition for protocol FVP_VE_Cortex_A15x1__Builtin__BUSProtocol.
 */

#ifndef FVP_VE_Cortex_A15x1__Builtin__BUSProtocol_ClassDef_h_
#define FVP_VE_Cortex_A15x1__Builtin__BUSProtocol_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_Builtin__BUSProtocol.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__Builtin__BUSProtocol;

// Abstract interface implementation for port
class protocol_Builtin__BUSProtocol__Implementation: public protocol_Builtin__BUSProtocol
{
public:
    protocol_Builtin__BUSProtocol__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__Builtin__BUSProtocol *port) { thisPort = port; }

    // Protocol members
	inline MxStatus read8(MxU32 , MxU8& );
	inline MxStatus read16(MxU32 , MxU16& );
	inline MxStatus read32(MxU32 , MxU32& );
	inline MxStatus read64(MxU32 , MxU64& );
	inline MxStatus read(MxU32 , MxU32* );
	inline MxStatus write8(MxU32 , MxU8 );
	inline MxStatus write16(MxU32 , MxU16 );
	inline MxStatus write32(MxU32 , MxU32 );
	inline MxStatus write64(MxU32 , MxU64 );
	inline MxStatus write(MxU32 , MxU32* );
	inline MxStatus readDbg8(MxU32 , MxU8& );
	inline MxStatus readDbg16(MxU32 , MxU16& );
	inline MxStatus readDbg32(MxU32 , MxU32& );
	inline MxStatus readDbg64(MxU32 , MxU64& );
	inline MxStatus readDbg(MxU32 , MxU32* );
	inline MxStatus writeDbg8(MxU32 , MxU8 );
	inline MxStatus writeDbg16(MxU32 , MxU16 );
	inline MxStatus writeDbg32(MxU32 , MxU32 );
	inline MxStatus writeDbg64(MxU32 , MxU64 );
	inline MxStatus writeDbg(MxU32 , MxU32* );


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__Builtin__BUSProtocol *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__Builtin__BUSProtocol: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< MxStatus (MxU32,MxU8&) > read8;
	sg::SlaveConnector< MxStatus (MxU32,MxU16&) > read16;
	sg::SlaveConnector< MxStatus (MxU32,MxU32&) > read32;
	sg::SlaveConnector< MxStatus (MxU32,MxU64&) > read64;
	sg::SlaveConnector< MxStatus (MxU32,MxU32*) > read;
	sg::SlaveConnector< MxStatus (MxU32,MxU8) > write8;
	sg::SlaveConnector< MxStatus (MxU32,MxU16) > write16;
	sg::SlaveConnector< MxStatus (MxU32,MxU32) > write32;
	sg::SlaveConnector< MxStatus (MxU32,MxU64) > write64;
	sg::SlaveConnector< MxStatus (MxU32,MxU32*) > write;
	sg::SlaveConnector< MxStatus (MxU32,MxU8&) > readDbg8;
	sg::SlaveConnector< MxStatus (MxU32,MxU16&) > readDbg16;
	sg::SlaveConnector< MxStatus (MxU32,MxU32&) > readDbg32;
	sg::SlaveConnector< MxStatus (MxU32,MxU64&) > readDbg64;
	sg::SlaveConnector< MxStatus (MxU32,MxU32*) > readDbg;
	sg::SlaveConnector< MxStatus (MxU32,MxU8) > writeDbg8;
	sg::SlaveConnector< MxStatus (MxU32,MxU16) > writeDbg16;
	sg::SlaveConnector< MxStatus (MxU32,MxU32) > writeDbg32;
	sg::SlaveConnector< MxStatus (MxU32,MxU64) > writeDbg64;
	sg::SlaveConnector< MxStatus (MxU32,MxU32*) > writeDbg;


    FVP_VE_Cortex_A15x1__Builtin__BUSProtocol()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(read8);
		define_behaviour(read16);
		define_behaviour(read32);
		define_behaviour(read64);
		define_behaviour(read);
		define_behaviour(write8);
		define_behaviour(write16);
		define_behaviour(write32);
		define_behaviour(write64);
		define_behaviour(write);
		define_behaviour(readDbg8);
		define_behaviour(readDbg16);
		define_behaviour(readDbg32);
		define_behaviour(readDbg64);
		define_behaviour(readDbg);
		define_behaviour(writeDbg8);
		define_behaviour(writeDbg16);
		define_behaviour(writeDbg32);
		define_behaviour(writeDbg64);
		define_behaviour(writeDbg);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_Builtin__BUSProtocol__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_Builtin__BUSProtocol *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline MxStatus protocol_Builtin__BUSProtocol__Implementation::read8(MxU32 param0__, MxU8& param1__)
{
	return thisPort->read8(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::read16(MxU32 param0__, MxU16& param1__)
{
	return thisPort->read16(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::read32(MxU32 param0__, MxU32& param1__)
{
	return thisPort->read32(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::read64(MxU32 param0__, MxU64& param1__)
{
	return thisPort->read64(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::read(MxU32 param0__, MxU32* param1__)
{
	return thisPort->read(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::write8(MxU32 param0__, MxU8 param1__)
{
	return thisPort->write8(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::write16(MxU32 param0__, MxU16 param1__)
{
	return thisPort->write16(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::write32(MxU32 param0__, MxU32 param1__)
{
	return thisPort->write32(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::write64(MxU32 param0__, MxU64 param1__)
{
	return thisPort->write64(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::write(MxU32 param0__, MxU32* param1__)
{
	return thisPort->write(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::readDbg8(MxU32 param0__, MxU8& param1__)
{
	return thisPort->readDbg8(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::readDbg16(MxU32 param0__, MxU16& param1__)
{
	return thisPort->readDbg16(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::readDbg32(MxU32 param0__, MxU32& param1__)
{
	return thisPort->readDbg32(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::readDbg64(MxU32 param0__, MxU64& param1__)
{
	return thisPort->readDbg64(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::readDbg(MxU32 param0__, MxU32* param1__)
{
	return thisPort->readDbg(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::writeDbg8(MxU32 param0__, MxU8 param1__)
{
	return thisPort->writeDbg8(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::writeDbg16(MxU32 param0__, MxU16 param1__)
{
	return thisPort->writeDbg16(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::writeDbg32(MxU32 param0__, MxU32 param1__)
{
	return thisPort->writeDbg32(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::writeDbg64(MxU32 param0__, MxU64 param1__)
{
	return thisPort->writeDbg64(param0__, param1__);
}

inline MxStatus protocol_Builtin__BUSProtocol__Implementation::writeDbg(MxU32 param0__, MxU32* param1__)
{
	return thisPort->writeDbg(param0__, param1__);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort)
class FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__Builtin__BUSProtocol
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort(MxU32 inFirst,
                                                 MxU32 inLast,
                                                 MxU32 outFirst,
                                                 MxU32 outLast):
    inFirst__(inFirst),
    inLast__(inLast),
    outFirst__(outFirst),
    outSize__(outLast - outFirst + 1)
    {
    }

    bool isCovered__(MxU32 address) const
    {
        return (address >= inFirst__) && (address <= inLast__);
    }

    void remapAddress__(MxU32 &address) const
    {
        if(outSize__)
            address = ((address - inFirst__) % outSize__) + outFirst__;
    }

private:
    MxU32 inFirst__;
    MxU32 inLast__;
    MxU32 outFirst__;
    MxU32 outSize__;
};


// Addressable protocol class definition
class FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort: public FVP_VE_Cortex_A15x1__Builtin__BUSProtocol
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::isMapped__, this);
		bind_method(*this, read8, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__read8__, this);
		bind_method(*this, read16, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__read16__, this);
		bind_method(*this, read32, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__read32__, this);
		bind_method(*this, read64, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__read64__, this);
		bind_method(*this, read, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__read__, this);
		bind_method(*this, write8, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__write8__, this);
		bind_method(*this, write16, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__write16__, this);
		bind_method(*this, write32, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__write32__, this);
		bind_method(*this, write64, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__write64__, this);
		bind_method(*this, write, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__write__, this);
		bind_method(*this, readDbg8, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__readDbg8__, this);
		bind_method(*this, readDbg16, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__readDbg16__, this);
		bind_method(*this, readDbg32, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__readDbg32__, this);
		bind_method(*this, readDbg64, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__readDbg64__, this);
		bind_method(*this, readDbg, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__readDbg__, this);
		bind_method(*this, writeDbg8, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__writeDbg8__, this);
		bind_method(*this, writeDbg16, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__writeDbg16__, this);
		bind_method(*this, writeDbg32, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__writeDbg32__, this);
		bind_method(*this, writeDbg64, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__writeDbg64__, this);
		bind_method(*this, writeDbg, &FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort::wrapper__writeDbg__, this);

    }

    ~FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
        {
            if ((*it)->isCovered__(addr)) {
                (*it)->remapAddress__(addr);
                return *it;
            }
        }
        return defaultOutPort__;
    }

    sg::Port* mapRange__(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast)
    {
        FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort*)port);
        if(defaultOutPort__ == port)
        {
            delete defaultOutPort__;
            defaultOutPort__ = 0;
        }
    }

    bool isMapped__(MxU64 addr)
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
        {
            if ((*it)->isCovered__(static_cast<MxU32>(addr)))
                return true;
        }
        return false;
    }

    // Wrapper functions for protocol behaviors
	MxStatus wrapper__read8__(MxU32 param0__, MxU8& param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'read8' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->read8(param0__, param1__);
	}
	MxStatus wrapper__read16__(MxU32 param0__, MxU16& param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'read16' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->read16(param0__, param1__);
	}
	MxStatus wrapper__read32__(MxU32 param0__, MxU32& param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'read32' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->read32(param0__, param1__);
	}
	MxStatus wrapper__read64__(MxU32 param0__, MxU64& param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'read64' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->read64(param0__, param1__);
	}
	MxStatus wrapper__read__(MxU32 param0__, MxU32* param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'read' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->read(param0__, param1__);
	}
	MxStatus wrapper__write8__(MxU32 param0__, MxU8 param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'write8' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->write8(param0__, param1__);
	}
	MxStatus wrapper__write16__(MxU32 param0__, MxU16 param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'write16' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->write16(param0__, param1__);
	}
	MxStatus wrapper__write32__(MxU32 param0__, MxU32 param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'write32' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->write32(param0__, param1__);
	}
	MxStatus wrapper__write64__(MxU32 param0__, MxU64 param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'write64' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->write64(param0__, param1__);
	}
	MxStatus wrapper__write__(MxU32 param0__, MxU32* param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'write' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->write(param0__, param1__);
	}
	MxStatus wrapper__readDbg8__(MxU32 param0__, MxU8& param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'readDbg8' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->readDbg8(param0__, param1__);
	}
	MxStatus wrapper__readDbg16__(MxU32 param0__, MxU16& param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'readDbg16' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->readDbg16(param0__, param1__);
	}
	MxStatus wrapper__readDbg32__(MxU32 param0__, MxU32& param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'readDbg32' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->readDbg32(param0__, param1__);
	}
	MxStatus wrapper__readDbg64__(MxU32 param0__, MxU64& param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'readDbg64' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->readDbg64(param0__, param1__);
	}
	MxStatus wrapper__readDbg__(MxU32 param0__, MxU32* param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'readDbg' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->readDbg(param0__, param1__);
	}
	MxStatus wrapper__writeDbg8__(MxU32 param0__, MxU8 param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'writeDbg8' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->writeDbg8(param0__, param1__);
	}
	MxStatus wrapper__writeDbg16__(MxU32 param0__, MxU16 param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'writeDbg16' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->writeDbg16(param0__, param1__);
	}
	MxStatus wrapper__writeDbg32__(MxU32 param0__, MxU32 param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'writeDbg32' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->writeDbg32(param0__, param1__);
	}
	MxStatus wrapper__writeDbg64__(MxU32 param0__, MxU64 param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'writeDbg64' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->writeDbg64(param0__, param1__);
	}
	MxStatus wrapper__writeDbg__(MxU32 param0__, MxU32* param1__)
	{
		// this also modifies the address
		FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *outPort = locateOutPort__(param0__);
		if (outPort == 0)
		{
			printf("behavior 'writeDbg' of protocol Builtin__BUSProtocol and port '%s' called for unmapped address: 0x%08" MxFMT64 "X\n", portName__, MxU64(param0__));
			return MX_STATUS_NOMEMORY;
		}
		return outPort->writeDbg(param0__, param1__);
	}


private:
    typedef std::list<FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__Builtin__BUSProtocol__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

