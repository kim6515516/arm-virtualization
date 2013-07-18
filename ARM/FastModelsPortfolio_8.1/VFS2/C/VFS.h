/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*!
 * \file    VFS.h
 * \brief   class and support constants providing access to host filing system objects
 *
 */

#ifndef VFS_H
#define VFS_H

#include <map>
#include <vector>
#include <string>

#include "VFSTypes.h"

// todo - rework this so it doesn't have to be public (or even merge with it)
#include "VFSFileSystem.h"

/*! Virtual filesystem class providing a generic set of filesystem operations on
 *  subdirectories of the host filing system
 */
class VFS
{
    typedef std::map<std::string, FileSystem::Mount*> MountTable;

    // A structure containing information on an object currently referenced by the target driver
    // There may be multiple handles referencing the same underlying object.
    struct Handle
    {
        int32_t id;           // index in handle table
        VFSType type;       
        
        // only one of these will be valid
        FileSystem::DirIter*  dir;
        FileSystem::File*     file;
        MountTable::iterator  mountiter;
        
        int32_t getId() const { return id; }
    };
    
    // The Filesystem implementation which abstracts away host implementation issues
    FileSystem::FS fs;
    
    // table of mount points backed by host directories
    MountTable mounts;
    
    // table of open handles 
    typedef std::vector<Handle> HandleTable;
    HandleTable handles;

// Private utility methods

    void initHandles();
    Handle* createHandle();
    Handle* getHandle(int32_t id);
    void freeHandle(Handle* handle);
    FileSystem::Mount* getMount(const char* pathname);
    const char* stripMount(const char* pathname);
    int32_t fillAttrBlock(int attr, uint8_t* attrdata, size_t attrlen, FileSystem::MetaData* data);
    int32_t decodeAttrBlock(int attr, const uint8_t* attrdata, uint32_t attrlen, FileSystem::MetaData* data);

public:
    VFS();
    ~VFS();

// Methods for use by the host side, to set up vfs environment

    /* Add a new mount point
     *
     * \param name      target name of mount
     * \param host_path host filesystem absolute path to root of mount point
     *
     * Associates a short name with a path on the host machine. e.g.:
     *
     *    addMount("A", "/path/to/my/directory");
     *
     * then files/directories inside the mount can be accessed as, e.g.:
     *
     *    mkdir("A:/dirtocreate");
     */
    void addMount(const char* name, const char* host_path);


// Methods for use by the target side to access the underlying filesystem

    /*! Open an iterator on the list of mounts added with add Mount
     * 
     * \return a handle to be used with readmounts/closemounts or a VFSError code
     */
    int openmounts();
    
    /* Read the next entry in a list of mounts
     *
     * \param id        mount iterator handle
     * \param attr      a bit mask of attributes to return (one or more VFSAttr)
     * \param attrdata  data block to receive attributes
     * \param attrlen   size of attribute block
     *
     * \return VFSError code
     *
     * The attribute block is packed with data in VFSAttr order (lowest to highest). Be careful
     * to unpack the attribute block using the correct data sizes. Not all attributes are
     * relavent to mount data
     *
     * \todo pass attrlen by reference so it can be updated with the size used
     * \todo pass attr by reference so that the actual returned attributes can be indicated
     */
    int readmounts(int32_t id, uint32_t attr, uint8_t* attrdata, size_t attrlen);
    
    /* Close a mount iterator handle
     *
     * \param id        mount iterator handle
     *
     * \return VFSError code
     */
    int closemounts(int id);
    
    /* Open a directory iterator handle
     *
     * \param name      full (vfs) path name to directory
     *
     * \return directory iterator handle for use with readdir/closedir or a VFSError code
     */
    int opendir(const char* name);    

    /* Read an entry form a directory iterator
     *
     * \param id        directory iterator handle
     * \param attr      a bit mask of attributes to return (one or more VFSAttr)
     * \param attrdata  data block to receive attributes
     * \param attrlen   size of attribute block
     *
     * \return VFSError code
     *
     * The attribute block is packed with data in VFSAttr order (lowest to highest). Be careful
     * to unpack the attribute block using the correct data sizes
     *
     * \todo pass attrlen by reference so it can be updated with the size used
     * \todo pass attr by reference so that the actual returned attributes can be indicated
     */
    int readdir(int id, uint32_t attr, uint8_t* attrdata, uint32_t attrlen);

    /* Close a directory iterator
     *
     * \param id        directory iterator handle
     *
     * \return VFSError code
     */
    int closedir(int id);

    /* Create a directory
     *
     * \param name      (vfs) directory name to create
     *
     * \return VFSError code
     */
    int mkdir(const char* name);

    /* Remove a directory
     *
     * \param name      (vfs) directory name to create
     *
     * \return VFSError code
     */
    int rmdir(const char* name);

    /* Remove a file
     *
     * \param name      (vfs) file to remove (may also work on other object types)
     *
     * \return VFSError code
     */
    int remove(const char* name);

    /* Rename an object
     *
     * \param oldname   (vfs) object to rename
     * \param newname   (vfs) new name of object
     *
     * \return VFSError code
     */
    int rename(const char*oldname, const char* newname);

    /* Retrieve attributes of an object on the filesystem
     *
     * \param name      (vfs) object name
     * \param attr      a bit mask of attributes to return (one or more VFSAttr)
     * \param attrdata  data block to receive attributes
     * \param attrlen   size of attribute block
     *
     * \return VFSError code
     *
     * The attribute block is packed with data in VFSAttr order (lowest to highest). Be careful
     * to unpack the attribute block using the correct data sizes
     *
     * \todo pass attrlen by reference so it can be updated with the size used
     * \todo pass attr by reference so that the actual returned attributes can be indicated
     */
    int getattr(const char* name, uint32_t attr, uint8_t* attrdata, uint32_t attrlen);

    /* Retrieve attributes of an object on the filesystem
     *
     * \param name      (vfs) object name
     * \param attr      a bit mask of attributes to modify (one or more VFSAttr)
     * \param attrdata  data block containing packed attributes
     * \param attrlen   size of attribute block
     *
     * \return VFSError code
     *
     * The attribute block should be packed with data in VFSAttr order (lowest to highest). Be careful
     * to pack the attribute block using the correct data sizes
     *
     * Not all attributes can be modified using this (e.g. file size/disk free/file name)
     *
     * \todo pass attr by reference so that the actual modified attributes can be indicated
     */
    int setattr(const char* filename, uint32_t attr, const uint8_t* attrdata, uint32_t attrlen);

    /* Open a file object on the filesystem for reading/writing
     *
     * \param filename  (vfs) file name
     * \param flags     VFSOpenFlags value indicating how to open the file
     *
     * \return file handle to use with readfile/writefile/closefile etc or a VFSError code
     */
    int openfile(const char* filename, uint32_t flags);

    /* Close a file object by a handle returned from openfile
     *
     * \param id        file handle
     *
     * flags are a combination of the flags in the VFSOpenFlags enumeration
     * 
     * \return VFSError code
     */
    int closefile(int32_t id);

    /* Write data to a file 
     *
     * \param id        file handle returned from openfile
     * \param offset    offset into file from where to start writing
     * \param data      pointer to data block containing data to be written
     * \param len       length of data to be written
     * 
     * \return length of data actually written to the file or a VFSError code
     */
    int writefile(int32_t id, uint64_t offset, const void* data, int32_t len);

    /* Read data from a file 
     *
     * \param id        file handle returned from openfile
     * \param offset    offset into file from where to start reading
     * \param data      pointer to data block to receive data read from file
     * \param len       size of data block to receive data
     * 
     * \return length of data actually read from the file or a VFSError code
     */
    int readfile(int32_t id, uint64_t offset, void* data, int32_t len);

    /* Get the size of an open file
     *
     * \param id        file handle returned from openfile
     * \param size      pointer to instance data to receive file size
     *
     * \return VFSError code
     */
    int getfilesize(int32_t id, uint64_t* size);

    /* Set the size of an open file
     *
     * \param id        file handle returned from openfile
     * \param size      new size of file
     *
     * \return VFSError code
     *
     * this will truncate or extend the file depending on whether the new size is
     * smaller or larger than the current file size
     */
    int setfilesize(int32_t id, uint64_t size);

    /* Force modified parts of a file back to persistent storage
     *
     * \param id        file handle returned from openfile
     *
     * \return VFSError code
     */
    int filesync(int32_t id);
    
    /* Linux target support functions */

    /* Create a symbolic link object
     *
     * \param filename  (vfs) name of link object to be created
     * \param data      content of link object (typically a path to another object)
     *
     * \return VFSError code
     *
     * \todo this is not yet implemented
     */
    int symlink(const char* filename, const char* data);

    /* Read the contents of a symbolic link object
     *
     * \param filename  (vfs) name of link object to be read
     * \param data      data block to receive link object contents
     * \param bufsiz    size of data block to receive link object contents
     *
     * \return VFSError code
     *
     * \todo this is not yet implemented
     */
    int readlink(const char* filename, char* data, int bufsiz) ;  
};

#endif // VFS_H


