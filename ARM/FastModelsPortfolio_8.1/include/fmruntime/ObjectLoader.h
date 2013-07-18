/*!
 * \file    ObjectLoader.cpp
 * \brief   Top Level Object Loader
 * \date    Copyright 2007 ARM Limited. All rights reserved.
 *          Copyright 2009 ARM Limited. All rights reserved.
 *          Copyright 2011-2013 ARM Limited. All rights reserved.
 */

#ifndef _ObjectLoader_h_
#define _ObjectLoader_h_

#include "MxTypes.h"
#include <string>
#include <map>
#include <set>
#include <vector>
#include "ObjectLoaderRawInterface.h"
#include "ObjectLoaderFormatSpecificLoader.h"
#include "ObjectLoaderMemoryConfInfo.h"
#include "ObjectLoaderInterface.h"
#include "ObjectLoaderError.h"
#include "FileInterface.h"


// object loader version
#define OBJECT_LOADER_VERSION 4
// changes for version 3 on 2006-08-08: setLoaderParameter(param,value) added to ObjectLoader: parameter putPacketChunks added
//                                      ELF loader: loadNOBITSRegions parameter added
// changes for version 4 on 2009-04-21: 64 bit support


using namespace std;


// forward declarations
namespace DebugInfoDB
{
    class DebugInfoRoot;
}

// main program loader class
class ObjectLoader: public ObjectLoaderRawInterface
{
public:
    // constructor, needs config file (memory.conf) and output memory interface
    ObjectLoader(const ObjectLoaderMemoryConfInfo *memoryConfInfo, ObjectLoaderInterface *loaderOutput);

    // destructor, deletes some loaders
    ~ObjectLoader();

    // get object loader version
    virtual MxU32 getVersion() const { return OBJECT_LOADER_VERSION; }

    // register a raw loader (i.e. register a file format)
    void registerObjectLoaderFormatSpecificLoader(ObjectLoaderFormatSpecificLoader *rawLoader, bool autoDelete = false, bool append = true);

    // register a raw loader (i.e. register a file format) (old compatibility function)
    void registerFormatLoader(ObjectLoaderFormatSpecificLoader *rawLoader_, bool autoDelete = false, bool append = true) { registerObjectLoaderFormatSpecificLoader(rawLoader_, autoDelete, append); }

    // get format loader from name
    ObjectLoaderFormatSpecificLoader *getObjectLoaderFormatSpecificLoaderFromName(const string& name) const;

    // get format loader from name (old compatibility function)
    ObjectLoaderFormatSpecificLoader *getFormatLoaderFromName(const string& name) const { return getObjectLoaderFormatSpecificLoaderFromName(name); }

    // set a parameter for a specific file format loader
    // (formatLoaderName may be ELF,In,Hex,COFF,SRec,ObjectLoader for available parameters see header files of format specific loaders)
    // (for formatLoaderName == ObjectLoader see below)
    void setLoaderParameter(const string& formatLoaderName, const string& parameterName, const string& value);

    // set a format independent loader parameter
    // (this is the same as setLoaderParameter("ObjectLoader", ...);
    // available parameters:
    // - putPacketChunks: "0" (default): putPacket() is called once for each MAU (e.g. once for each byte for a byte addressable memory)
    //                         (this is the old and convenient and slow behavior)
    //                    "1": putPacket() is called once for each chunk of consecutive memory as it comes from the file format
    //                         the mauBytes parameter of putPacket will be the length of the chunk in bytes
    //                         (this exists since 2006-08-08 and allows to load large amounts of data faster,
    //                         e.g. the putPacet() routine can decide to pass data in 64 bit chunks to the
    //                         memory subsystem if this is desirable)
    void setLoaderParameter(const string& parameterName, const string& value);

    void setLoaderParameterFromEnv(const char *envvar, const char *loaderName);

    // load a file
    void loadFile(const char *filename);
    void loadFile(FileInterface *file_interface);

    // ObjectLoaderRawInterface implementation: (input interface towards the file)

    // put a piece of raw data
    virtual void putRawData(const char *sectionName, ObjectLoaderAddress startAddress, ObjectLoaderAddress size, const MxU8 *rawData, MxU32 flags, MxU32 type);
    // put a symbol (label)
    virtual void putSymbol(const char *symbolName, ObjectLoaderAddress address, ObjectLoaderAddress size, const char *sectionName, MxU32 binding, MxU32 type);
    // set the start address of the program
    virtual void putProgramExecutionStartAddress(ObjectLoaderAddress address);
    // add a source line reference
    virtual void putSourceReference(ObjectLoaderAddress address, const char *sectionName, const char *fileName, int lineNumber);
    // transfer any other object file information
    virtual void putSpecificObjectInfo(const char *key, const char *sectionName, const char *strValue, ObjectLoaderAddress numValue, const void *anyValue);

    // verbosity control
    void setVerbose(MxU32 verbose);

    // values for verbose flags
    enum {
        V_OFF          =          0,
        V_GENERAL      =          1,
        V_SYMBOL       =          2,
        V_SOURCEREF    =          4,
        V_STARTADDRESS =          8,
        V_RAWDATA      =         16,
        V_DATAPACKETS  =         32,
        V_RAWDATADUMP  =         64,
        V_RAWLOADER    =        128, // set verbose flag of raw loader
        V_SPECIFICOBJECTINFO =  256,
        V_WARN         = 0x00010000,
        V_ALL          = 0xffffffff
    };

    // get address space name of address space id
    const ObjectLoaderAddressSpaceInfo *getAddressSpaceForId(MxU32 id) const;

    // get current section name
    // (this function returns a string when called from one of the interface functions in ObjectLoaderInterface and 0 otherwise)
    const char *getCurrentSectionName() const { return currentSectionName; }

    // get DebugInfoRoot (which receives the debug info loaded)
    // (this function may return 0 which means that debug info is not loaded)
    DebugInfoDB::DebugInfoRoot *getDebugInfoDB() { return debugInfoDB; }

    // set DebugInfoRoot (which receives the debug info loaded)
    void setDebugInfoDB(DebugInfoDB::DebugInfoRoot *debugInfoDB_) { debugInfoDB = debugInfoDB_; }

    // static debugging helpers:

    /// simple single line hex dump without address
    static string hexDumpLine(const MxU8 *data, MxU64 size);
    /// dump memory block
    static void hexDumpBlock(MxU64 baseAddress, const MxU8 *data, MxU64 size);


private:
    /// Convert section name to address space index
    const ObjectLoaderAddressSpaceInfo *getAddressSpace(const char *sectionName, MxU32 sectionFlags = 0, MxU32 sectionType = 0);

    // private data

    /// list of registered format specific loader
    vector<ObjectLoaderFormatSpecificLoader*> rawLoader;
    /// list of registered format specific loader which are to be deleted automatically in destructor (built in standard loaders)
    vector<ObjectLoaderFormatSpecificLoader*> loadersToDelete;
    /// remember pointer to static memory const info
    const ObjectLoaderMemoryConfInfo *memoryConfInfo;
    /// verbose execution
    MxU32 verbose;
    /// output interface towards the simulator
    ObjectLoaderInterface *loaderOutput;
    /// list of unknown sections which occurred during load
    string unknownSectionsList;
    /// map which caches conversion of a section name into a pointer to the address space info struct
    map<string,const ObjectLoaderAddressSpaceInfo *> sectionName2adrSpaceCache;
    /// set which keeps the 'known' unknown sections
    set<string> unknownSections;
    /// mask for all program memory addresses
    ObjectLoaderAddress programAddressMask;
    /// default address space
    const ObjectLoaderAddressSpaceInfo *defaultAddressSpace;
    /// current section name (only valid when called from one of the ObjectLoaderInterface methods which are called by this object)
    const char *currentSectionName;
    /// debug info db
    DebugInfoDB::DebugInfoRoot *debugInfoDB;
    /// true == call putPacket() for large chunks of memory once, else call for each mau
    bool putPacketChunks;
};


#endif

