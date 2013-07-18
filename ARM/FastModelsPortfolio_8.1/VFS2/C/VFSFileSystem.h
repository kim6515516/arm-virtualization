/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*!
 * \file    VFSFileSystem.h
 * \brief   classes providing generic access to the underlying host filing system
 */

#ifndef VFSFILESYSTEM_H
#define VFSFILESYSTEM_H

#include "eslapi/eslapi_stdint.h"

#include "VFSTypes.h"


// todo
//  error handling
//  constants

namespace FileSystem
{
    class FS;

    class Mount;
    class DirIter;

    // file information as returned by Dir::read and Filesystem::getInfo
    class MetaData
    {  
        char* hostpath;         // path to object represented by MetaData

        char* filename;         // leaf name
        uint64_t mtime;         // modification time
        uint64_t ctime;         // creation time
        uint64_t atime;         // access time
        uint64_t filesize;      // size in bytes
        uint32_t access;        // access permissions

        uint32_t mode;          // host specific flags used to generate fat attributes

    public:
        VFSType type;

    public:
        int32_t populate(const char*);

    public:
        MetaData();
        ~MetaData();

        const char* getName() const     { return filename; }
        uint64_t getMTime() const       { return mtime; }
        uint64_t getATime() const       { return atime; }
        uint64_t getCTime() const       { return ctime; }
        uint64_t getFileSize() const    { return filesize; }
        uint32_t getAccess() const      { return access; }
        VFSType getType() const          { return type; }

        uint64_t getDiskSize() const;
        uint64_t getDiskFree() const;

        uint32_t getFatAttributes() const;
        int32_t setFatAttributes(uint32_t attr);

        uint64_t getRTime() const;
    };

    class FileImpl;

    // Object encapsulating a file handle
    class File
    {
        Mount *mount;

        FileImpl* impl;

    public:
        File(Mount* mount, const char* host_name);
        ~File();

        int32_t open(uint32_t flags);
        int32_t close();

        bool isValid() const;

        int32_t writeData(uint64_t offset, const void* data, int32_t len);
        int32_t readData(uint64_t offset, void* data, int32_t len);

        int32_t getSize(uint64_t*);
        int32_t setSize(uint64_t);

        int32_t syncData();

        int32_t lastError() const;
    };

    class DirIterImpl;

    // Object representing an iterator on a directory
    class DirIter
    {
        Mount* mount;

        DirIterImpl* impl;

    public:
        DirIter(Mount* mount, const char* host_name);
        ~DirIter();

        int32_t open();
        int32_t close();

        bool isValid() const;

        int32_t getNextInfo(MetaData*);
    };

    // Object representing a 'mount point', the root of a host directory tree
    // used as persistent storage
    class Mount
    {
        friend class File;
        friend class DirIter;

        FS* fs;

        char* host_path;

        // todo - keep a list of all open files/directories on the mount?
        int canonicalise(char* cname, size_t len, const char* name);

    public:
        Mount(FS* fs, const char* host_path);
        ~Mount();

        // create a new directory in the filesystem
        int32_t createDir(const char* dirname);

        // remove an empty directory from the filesystem
        int32_t removeDir(const char* dirname);

        // create a new file in the filesystem.
        // currently won't replace an old one
        int32_t createFile(const char* filename);

        // remove a file from the filesystem
        int32_t removeFile(const char* filename);

        // rename an object in the filesystem
        int32_t renameObject(const char* oldname, const char* newname);

//      todo - symlink support
//      int symlink(const char* filename, char* symlink);
//      int readlink(const char* filename, char* buffer, int32_t bufsize);

       // create a new file handle for an existing file in the mount
        // returns NULL if not possible
        // OPEN_RDONLY, OPEN_WRONLY, OPEN_RDWR
        int32_t openFile(const char* filename, uint32_t flags, File*&);
        
        // create a new directory handle for an existing directory in the mount
        // Returns NULL if not possible
        int32_t openDir(const char* dirname, DirIter*&);

        // return meta data on an object - might want separate accessors for this?
        int32_t getInfo(const char* name, MetaData*);
        
        // don't yet support setting meta data and want to be able to set things independently
        // int setInfo(const char* name, MetaData*);
    };

    // A filesystem containing mounts
    class FS
    {
    public:

        FS();
        ~FS();

       // create a mount point that is backed by a given directory on the host
        Mount* createMount(const char* host_path);
    };

}; // namespace FileSystem

#endif // VFSFILESYSTEM_H
