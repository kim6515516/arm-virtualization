/*
 * $Id: ObjectLoaderInterface.h 29787 2013-03-01 10:40:01Z brifol01 $
 *
 * Project:  LISA Simulator Generator
 * $Author: brifol01 $
 * $Date: 2013-03-01 10:40:01 +0000 (Fri, 01 Mar 2013) $
 * $Revision: 29787 $
 *
 * Copyright (c) 2000-2003 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 */

/** \file
 * Loader memory interface header file (interface specification)
 */

#ifndef _LoaderInterface_h_
#define _LoaderInterface_h_ "$Id: ObjectLoaderInterface.h 29787 2013-03-01 10:40:01Z brifol01 $"

#include "MxTypes.h"
#include "ObjectLoaderAddress.h"
#include "ObjectLoaderError.h"


// pure virtual interface class:
// base class which finally receives all the data
// (the architecture describer has to reimplement this, usually the simulator contains an instance of a class which is derived from this class)
class ObjectLoaderInterface
{
public:
        // called for each packet of program code data:
        // The packet is associated to the address space 'addressSpaceId', it base address is 'address', the actual data is in 'packet'. The length
        // of the packet is 'mauBytes'. It is constant for each address space and is equal to the 'mau_bytes' field for that address space in memory.conf.
        // If you did not pass any memory.conf information to the ObjectLoader then 'mayBytes' is always 1 which means that per call a single byte is transferred
        // in packet[0]. 'flags', and 'type' are the ELF section flags and type (simulated for other formats).
        virtual void putPacket(MxU32 addressSpaceId, ObjectLoaderAddress address, const MxU8* packet, MxU32 mauBytes, MxU32 flags, MxU32 type) = 0;

        // called for every symbol in the file
        virtual void putSymbol(MxU32 addressSpaceId, const char *symbolName, ObjectLoaderAddress address, ObjectLoaderAddress size, MxU32 binding, MxU32 type) = 0;

        // called usually once (or not at all) per executable file to set the entry point
        virtual void putProgramExecutionStartAddress(ObjectLoaderAddress address) = 0;

        // called for every source reference
        virtual void putSourceReference(MxU32 addressSpaceId, ObjectLoaderAddress address, const char *fileName, int lineNumber) = 0;

        // transfer any other object file information
        // this is not pure virtual since the user does not need to accept this kind of information
        // the default implementation simply ignores all specific object info
        virtual void putSpecificObjectInfo(MxU32 /* addressSpaceId */, const char * /* key */, const char * /* strValue */, ObjectLoaderAddress /* numValue */, const void * /* anyValue */) {}

    // virtual destructor to make compiler happy
    virtual ~ObjectLoaderInterface() {}
};


#endif

