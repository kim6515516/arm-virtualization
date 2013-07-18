/*
 * $Id: ObjectLoaderFormatSpecificLoader.h 29787 2013-03-01 10:40:01Z brifol01 $
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
 * Raw Loader header file (interface specification)
 */

#ifndef _ObjectLoaderFormatSpecificLoader_h_
#define _ObjectLoaderFormatSpecificLoader_h_ "$Id: ObjectLoaderFormatSpecificLoader.h 29787 2013-03-01 10:40:01Z brifol01 $"

#include <stdio.h>
#include "ObjectLoaderRawInterface.h"
#include "ObjectLoaderError.h"
#include "FileInterface.h"


// forward declarations
class ObjectLoader;

// pure virtual interface class:
// base class for all raw loaders
class ObjectLoaderFormatSpecificLoader
{
public:
        // constructor
        ObjectLoaderFormatSpecificLoader(): objectLoader(0) {}

        /// load a file
        // - throw a ObjectLoaderErrorFormatNotRecognized() exception if the file
        //   format is not recognized
    //   Note: This exception must never be thrown after any data has been loaded.
    //   This exception *must* be thrown when the file is not the correct file format.
    // - throw a ObjectLoaderError() for all other errors (bad IO or bad file
        //   integrity) (only *after* the file is for sure the correct file format)
        // - if no exception is thrown the file was loaded successfully
        virtual void loadFile(FileInterface *file_interface, ObjectLoaderRawInterface *rawReceiver, bool verbose) = 0;

        // return a short name for the supported format
        virtual const char *getFormatName() = 0;

        // set a parameter for this loader (not a must to reimplement this)
        virtual void setLoaderParameter(const string&, const string&) { throw ObjectLoaderError("loader '" + string(getFormatName()) + "': loader does not accept parameters"); }

        // get pointer to the ObjectLoader instance this format specific loader belongs to
        ObjectLoader *getObjectLoader() { return objectLoader; }

        // set pointer to the ObjectLoader instance this format specific loader belongs to
        void setObjectLoader(ObjectLoader *objectLoader_) { objectLoader = objectLoader_; }

        // virtual destructor to allow destruction of list of loaders
        // (does not need to be reimplemented)
        virtual ~ObjectLoaderFormatSpecificLoader() {}

    // loaders which return true here will not be mentioned in the 'supported formats are' message
    virtual bool isHiddenFormat() const { return false; }

    // helper class to make sure files get closed when exceptions are thrown
    class Automatic_fclose
    {
    public:
        Automatic_fclose(FILE *&file_): file(file_) {}
        ~Automatic_fclose() { if (file) fclose(file); file = 0; }
    private:
        FILE *&file;
    };

private:
        // private data
        ObjectLoader *objectLoader;
};


#endif

