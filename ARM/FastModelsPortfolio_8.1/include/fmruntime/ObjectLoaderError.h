/*
 * $Id: ObjectLoaderError.h 29787 2013-03-01 10:40:01Z brifol01 $
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
 * Loader error exception classes.
 */

#ifndef _LoaderError_h_
#define _LoaderError_h_ "$Id: ObjectLoaderError.h 29787 2013-03-01 10:40:01Z brifol01 $"

#include <stdio.h>
#include <string>
#include <exception>

using namespace std;

// exception classes

// thrown by ObjectLoader::loadFile() and ObjectLoaderFormatSpecificLoaderXXX::loadFile()
// this class is used for actual loader error messages (like inconsistent file)
class ObjectLoaderError: public exception
{
public:
        ObjectLoaderError(const string& message_, int lineNumber = -1): message(message_)
        { if(lineNumber >= 0) { char buf[80]; sprintf(buf, " (line %d)", lineNumber); message += buf; }}

        virtual ~ObjectLoaderError() throw () {}

        string message;
        virtual const char* what() const throw() { return message.c_str (); }
};

// thrown by ObjectLoader::loadFile() and ObjectLoaderFormatSpecificLoaderXXX::loadFile()
// this class is used to signal that a specific loader can not load a specific file
// which is often not an error since it often occurs during the format probing
class ObjectLoaderErrorFormatNotRecognized: public ObjectLoaderError
{
public:
        ObjectLoaderErrorFormatNotRecognized(const string& message_): ObjectLoaderError(message_) {}
};

// thrown by ObjectLoader::loadFile() and ObjectLoaderFormatSpecificLoaderXXX::loadFile()
// this class is used to signal that the file could not be opened, probably because it does not exist
class ObjectLoaderErrorCouldNotOpenFile: public ObjectLoaderError
{
public:
        ObjectLoaderErrorCouldNotOpenFile(const string& message_): ObjectLoaderError(message_) {}
};

#endif

