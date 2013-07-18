/*
 * $Id: ObjectLoaderRawInterface.h 29787 2013-03-01 10:40:01Z brifol01 $
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
 * Raw receiver header file (interface specification)
 */

#ifndef _ObjectLoaderRawInterface_h_
#define _ObjectLoaderRawInterface_h_ "$Id: ObjectLoaderRawInterface.h 29787 2013-03-01 10:40:01Z brifol01 $"

#include "MxTypes.h"
#include "Elf.h"
#include "ObjectLoaderAddress.h"
#include "ObjectLoaderError.h"

// pure virtual interface class:
// this receiver class receives the raw data from the ObjectLoaderFormatSpecificLoader
// (only implemented by ObjectLoader)
class ObjectLoaderRawInterface
{
public:
    // virtual destructor
    virtual ~ObjectLoaderRawInterface() {}

    // put a piece of raw data
    virtual void putRawData(const char *sectionName, ObjectLoaderAddress startAddress, ObjectLoaderAddress size, const MxU8 *rawData,
                            MxU32 flags = SHF_EXECINSTR | SHF_ALLOC | SHF_WRITE, MxU32 type = SHT_PROGBITS) = 0;
    // put a symbol (label)
    virtual void putSymbol(const char *symbolName, ObjectLoaderAddress address, ObjectLoaderAddress size, const char *sectionName, MxU32 binding, MxU32 type) = 0;
    // set the start address of the program
    virtual void putProgramExecutionStartAddress(ObjectLoaderAddress address) = 0;
    // add a source line reference
    virtual void putSourceReference(ObjectLoaderAddress address, const char *sectionName, const char *fileName, int lineNumber) = 0;
    // transfer any other object file information
    // ('key' should specify the type of the information (e.g. 'weak_symbol'), 'key' should never be 0
    //  'sectionName' should be the section name associated with the info or 0 if not associated to any section
    //  'strValue' may be any string value or even 0,
    //  'numValue' may be any numeric value or even 0,
    //  'anyValue' may point to anything or may be even 0)
    // unused parameters should be se to 0
    virtual void putSpecificObjectInfo(const char *key, const char *sectionName, const char *strValue, ObjectLoaderAddress numValue, const void *anyValue) = 0;
};


#endif

