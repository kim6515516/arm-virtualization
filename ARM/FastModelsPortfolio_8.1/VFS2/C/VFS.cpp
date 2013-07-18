/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*!
 * \file    VFS.cpp
 * \brief   class providing access to host filing system objects. This version uses
 *          VFSFileSystem and should probably merge with it
 */

#include "eslapi/eslapi_stdint.h"

#include "VFS.h"

#include "string.h"
#include "stdio.h"

#define vfs_trace       if (0) printf
#define vfs_trace_op    if (0) printf
#define vfs_trace_debug if (0) printf

VFS::VFS()
{
    initHandles();
}

VFS::~VFS()
{
}

void VFS::addMount(const char* name, const char* host_path)
{
    FileSystem::Mount* mount = fs.createMount(host_path);
    mounts.insert(std::make_pair(name, mount));
}

// Open an iterator on the global list of available mounts
int VFS::openmounts()
{
    // get a handle for future reference
    Handle* handle = createHandle();
    if (!handle)
        return VFS_ERR_MAXHANDLE;
    
    // create a mount iterator
    MountTable::iterator iter = mounts.begin();
    
    handle->type      = VFS_TYPE_MOUNT;
    handle->mountiter = iter;  
    
    return handle->getId();
}

// Read various attributes about an entry from the mount list
int VFS::readmounts(int32_t id, uint32_t attr, uint8_t* attrdata, size_t attrlen)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_MOUNT)
        return VFS_ERR_BADHANDLE;
        
    MountTable::iterator& iter = handle->mountiter;
    
    if (iter == mounts.end())
        return VFS_ERR_NOENTRY;
        
/*            
    FileSystem::Mount* mount = iter->second;
    
    // mounts support a restricted set of attributes - name and flags
    if (attr & VFS_ATTR_FLAGS)
    {
        attr &=~ VFS_ATTR_FLAGS;
        
        if (attrlen < 4)
            return VFS_ERR_NOROOM;
            
        *(uint32_t*)attrdata = mount->getFlags();
        attrdata += 4;
        attrlen -= 4;
    }
*/ 
        

    // get info on the root directory, this will ensure the 
    // mount actually exists and gets us an object we can use to
    // query the disk information
    FileSystem::Mount* mount = iter->second;
    FileSystem::MetaData data;
    int  result = mount->getInfo("/", &data);
    if (result < 0)
        return result;

    if (attr & VFS_ATTR_DISKSIZE)
    {
        attr &= ~VFS_ATTR_DISKSIZE;

        if (attrlen < 8)
            return VFS_ERR_NOROOM;

        *(uint64_t*)attrdata = data.getDiskSize();
        attrdata += 8;
        attrlen -= 8;
    }

    if (attr & VFS_ATTR_DISKFREE)
    {
        attr &= ~VFS_ATTR_DISKFREE;

        if (attrlen < 8)
            return VFS_ERR_NOROOM;

        *(uint64_t*)attrdata = data.getDiskFree();
        attrdata += 8;
        attrlen -= 8;
    }

    // this must be last
    if (attr & VFS_ATTR_NAME)
    {
        attr &=~ VFS_ATTR_NAME;
        
        const char* name = iter->first.c_str();
        size_t len = strlen(name)+1;
        
        if (attrlen < len)
            return VFS_ERR_NOROOM;
        
        strncpy((char*)attrdata, name, attrlen);
        attrdata += len;
        attrlen -= len;        
    }
    
    if (attr)
    {
        // something was requested that isn't handled
        return VFS_ERR_INVALID;
    }
    
    ++iter;     
    
    return VFS_ERR_OK; 
} 

// close an open mount iterator
int VFS::closemounts(int id)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_MOUNT)
        return VFS_ERR_BADHANDLE;
        
    freeHandle(handle);
    
    return VFS_ERR_OK;
}

// open a handle to a directory iterator
int VFS::opendir(const char* name)
{
    Handle* handle = createHandle();
    if (!handle)
        return VFS_ERR_MAXHANDLE;
        
    FileSystem::Mount* mount = getMount(name);
    if (!mount)
        return VFS_ERR_NOMOUNT;
        
    FileSystem::DirIter* dir;
    
    int ret = mount->openDir(stripMount(name), dir);
    if (ret < 0)
        return ret;

    handle->type = VFS_TYPE_DIR;
    handle->dir = dir;
    
    return handle->getId();
}

// read directory information on the next entry in a directory
int VFS::readdir(int id, uint32_t attr, uint8_t* attrdata, uint32_t attrlen)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_DIR)
        return VFS_ERR_BADHANDLE;
    
    FileSystem::DirIter* iter = handle->dir;
    
    FileSystem::MetaData data;
    int result;

    result = iter->getNextInfo(&data);
    if (result < 0)
        return result;
        
    // todo - just return NOENTRY
    if (data.getType() == VFS_TYPE_NONE)
        return VFS_ERR_NOENTRY;
    
    return fillAttrBlock(attr, attrdata, attrlen, &data);
}

int VFS::closedir(int id)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_DIR)
        return VFS_ERR_BADHANDLE;
        
    FileSystem::DirIter* iter = handle->dir;
    
    delete iter;
    
    freeHandle(handle);
        
    return VFS_ERR_OK;
}

int VFS::mkdir(const char* name)
{
    FileSystem::Mount* mount = getMount(name);
    if (!mount)
        return VFS_ERR_NOMOUNT;
        
    return mount->createDir(stripMount(name));
}

int VFS::rmdir(const char* name)
{
    FileSystem::Mount* mount = getMount(name);
    if (!mount)
        return VFS_ERR_NOMOUNT;
        
    return mount->removeDir(stripMount(name));
}

int VFS::remove(const char* name)
{
    FileSystem::Mount* mount = getMount(name);
    if (!mount)
        return VFS_ERR_NOMOUNT;
        
    return mount->removeFile(stripMount(name));
}

int VFS::rename(const char*oldname, const char* newname)
{
    FileSystem::Mount* oldmount = getMount(oldname);
    if (!oldmount)
        return VFS_ERR_NOMOUNT;
        
    FileSystem::Mount* newmount = getMount(newname);
    if (!newmount)
        return VFS_ERR_NOMOUNT;
        
    if (oldmount != newmount)
        return VFS_ERR_INVALID;
        
   return oldmount->renameObject(stripMount(oldname), stripMount(newname));
}

int VFS::getattr(const char* name, uint32_t attr, uint8_t* attrdata, uint32_t attrlen)
{
    FileSystem::Mount* mount = getMount(name);
    if (!mount)
        return VFS_ERR_NOMOUNT;
        
    FileSystem::MetaData info;
    int result;
    
    result = mount->getInfo(stripMount(name), &info);
    if (result < 0)
        return result;
        
    result = fillAttrBlock(attr, attrdata, attrlen, &info);

    return result;
}

int VFS::setattr(const char* name, uint32_t attr, const uint8_t* attrdata, uint32_t attrlen)
{
    FileSystem::Mount* mount = getMount(name);
    if (!mount)
        return VFS_ERR_NOMOUNT;

    FileSystem::MetaData info;
    int result;
    
    result = mount->getInfo(stripMount(name), &info);
    if (result < 0)
        return result;

    return decodeAttrBlock(attr, attrdata, attrlen, &info);
}

int VFS::openfile(const char* filename, uint32_t flags)
{
    Handle* handle = createHandle();
    if (!handle)
        return VFS_ERR_MAXHANDLE;
    
    FileSystem::Mount* mount = getMount(filename);
    if (!mount)
        return VFS_ERR_NOMOUNT;
   
     
/*
    int result;
    if (flags & VFS_OPEN_CREATE)
    {
        result = mount->createFile(stripMount(filename));
        if (result < 0)
            return result;
    }
*/

    FileSystem::File* file;
    
    int result = mount->openFile(stripMount(filename), flags, file);
    if (result < 0)
        return result;

    handle->type = VFS_TYPE_FILE;
    handle->file = file;
        
    return handle->getId();
}

int VFS::closefile(int32_t id)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_FILE)
        return VFS_ERR_BADHANDLE;
        
    FileSystem::File* file = handle->file;
        
    delete file;
    
    freeHandle(handle);
    
    return VFS_ERR_OK;
}

int VFS::writefile(int32_t id, uint64_t offset, const void* data, int32_t len)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_FILE)
        return VFS_ERR_BADHANDLE;
        
    FileSystem::File* file = handle->file;
        
    // todo - return length written
    int32_t ret = file->writeData(offset, data, len);
    if (ret < 0)
        return ret;
        
    return ret;
}

int VFS::readfile(int32_t id, uint64_t offset, void* data, int32_t len)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_FILE)
        return VFS_ERR_BADHANDLE;
        
    FileSystem::File* file = handle->file;
        
    // todo - return length read
    int32_t ret = file->readData(offset, data, len);
    if (ret < 0)
        return ret;
        
    return ret;
}

int VFS::getfilesize(int32_t id, uint64_t* size)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_FILE)
        return VFS_ERR_BADHANDLE;
        
    FileSystem::File* file = handle->file;
    
    return file->getSize(size);
}

int VFS::setfilesize(int32_t id, uint64_t size)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_FILE)
        return VFS_ERR_BADHANDLE;
        
    FileSystem::File* file = handle->file;
    
    return file->setSize(size);
}

int VFS::filesync(int32_t id)
{
    Handle* handle = getHandle(id);
    if (!handle)
        return VFS_ERR_BADHANDLE;
        
    if (handle->type != VFS_TYPE_FILE)
        return VFS_ERR_BADHANDLE;
        
    FileSystem::File* file = handle->file;
    
    return file->syncData();
}

// TODO

int VFS::symlink(const char* filename, const char* data)
{
    return VFS_ERR_UNIMPL;
}

int VFS::readlink(const char* filename, char* data, int bufsiz)
{
    return VFS_ERR_UNIMPL;
}    

// Utility methods to manage the handle table etc
void VFS::initHandles()
{
    handles.resize(VFS_MAX_HANDLES);
    for (int i=0; i<VFS_MAX_HANDLES; ++i)
    {
        handles[i].id = i;
        handles[i].type = VFS_TYPE_NONE;
    }
}


// get an unused handle. This does not mark the handle as in use (as we are single threaded here)
// - setting the type to anything other than VFS_TYPE_NONE will mark it in use
VFS::Handle* VFS::createHandle()
{
    for (uint32_t i=0; i<handles.size(); ++i)
    {
        if (handles[i].type == VFS_TYPE_NONE)
            return &handles[i];
    }
    
    vfs_trace_debug("vfs: No more handles\n");
    return NULL;
}

// get an existing handle by id
VFS::Handle* VFS::getHandle(int32_t id)
{
    if ((uint32_t)id < handles.size())
        return &handles[id];
        
    return NULL;
}

// release a handle - the contents will be forgotten so must have been removed
void VFS::freeHandle(Handle* handle)
{
    handle->type = VFS_TYPE_NONE;
}

// get the mount given a pathname of the form mount:/path/to/file
FileSystem::Mount* VFS::getMount(const char* pathname)
{
    const char* sep = strchr(pathname, ':');
    if (!sep)
    {
        vfs_trace_debug("vfs: invalid pathname '%s'\n", pathname);
        return NULL;
    }
    
    std::string mountname = std::string(pathname, sep-pathname);
    
    MountTable::iterator pos = mounts.find(mountname);
    if (pos == mounts.end())
        return NULL;
        
    return pos->second;
}

// returns the path without the mount prefix
const char* VFS::stripMount(const char* pathname)
{
    const char* sep = strchr(pathname, ':');
    if (!sep)
    {
        vfs_trace_debug("vfs: invalid pathname '%s'\n", pathname);
        return NULL;
    }
    
    return ++sep;
}

// use the filesystem metadata object to set file attributes encoded in an attribute block
// not yet fully implemented
int32_t VFS::decodeAttrBlock(int attr, const uint8_t* attrdata, uint32_t attrlen, FileSystem::MetaData* data)
{
    if (attr & VFS_ATTR_FAT)
    {
        attr &= ~VFS_ATTR_FAT;

        if (attrlen < 4)
            return VFS_ERR_INVALID;

        uint32_t fat_attr = *(uint32_t*)attrdata;
        attrdata += 4;
        attrlen -= 4;

        // set synthesized fat attributes
        int32_t err = data->setFatAttributes(fat_attr);
        if (err != VFS_ERR_OK)
            return err;
    }

    if (attr)
    {
        vfs_trace_debug("Unsuporrted attributes 0x%x for operation\n", attr);
        return VFS_ERR_INVALID;
    }

    return VFS_ERR_OK;
}

// turn filesystem metadata into a block of data that can be returned to the caller
int32_t VFS::fillAttrBlock(int attr, uint8_t* attrdata, size_t attrlen, FileSystem::MetaData* data)
{
    if (attr & VFS_ATTR_MTIME)
    {
        attr &= ~VFS_ATTR_MTIME;
        
        if (attrlen < 8)
            return VFS_ERR_NOROOM;
            
        *(uint64_t*)attrdata = data->getMTime();
        attrdata += 8;
        attrlen -= 8;
    }
    
    if (attr & VFS_ATTR_ACCESS)
    {
        attr &= ~VFS_ATTR_ACCESS;
        
        if (attrlen < 4)
            return VFS_ERR_NOROOM;
            
        *(uint32_t*)attrdata = data->getAccess();
        attrdata += 4;
        attrlen -=4;
    }
    
    if (attr & VFS_ATTR_TYPE)
    {
        attr &= ~VFS_ATTR_TYPE;
        
        if (attrlen < 4)
            return VFS_ERR_NOROOM;
            
        *(uint32_t*)attrdata = (uint32_t)data->getType();
        attrdata += 4;
        attrlen -=4;
    }
        
    if (attr & VFS_ATTR_SIZE)
    {
        attr &= ~VFS_ATTR_SIZE;
        
        if (attrlen < 8)
            return VFS_ERR_NOROOM;
            
        *(uint64_t*)attrdata = data->getFileSize();
        attrdata += 8;
        attrlen -= 8;
    }

    if (attr & VFS_ATTR_CTIME)
    {
        attr &= ~VFS_ATTR_CTIME;
        
        if (attrlen < 8)
            return VFS_ERR_NOROOM;
            
        *(uint64_t*)attrdata = data->getCTime();
        attrdata += 8;
        attrlen -= 8;
    }

    if (attr & VFS_ATTR_ATIME)
    {
        attr &= ~VFS_ATTR_ATIME;
        
        if (attrlen < 8)
            return VFS_ERR_NOROOM;
            
        *(uint64_t*)attrdata = data->getATime();
        attrdata += 8;
        attrlen -= 8;
    }

    if (attr & VFS_ATTR_RTIME)
    {
        attr &= ~VFS_ATTR_RTIME;
        
        if (attrlen < 8)
            return VFS_ERR_NOROOM;
            
        *(uint64_t*)attrdata = data->getRTime();
        attrdata += 8;
        attrlen -= 8;
    }

    if (attr & VFS_ATTR_DISKSIZE)
    {
        attr &= ~VFS_ATTR_DISKSIZE;

        if (attrlen < 8)
            return VFS_ERR_NOROOM;

        *(uint64_t*)attrdata = data->getDiskSize();
        attrdata += 8;
        attrlen -= 8;
    }

    if (attr & VFS_ATTR_DISKFREE)
    {
        attr &= ~VFS_ATTR_DISKFREE;

        if (attrlen < 8)
            return VFS_ERR_NOROOM;

        *(uint64_t*)attrdata = data->getDiskFree();
        attrdata += 8;
        attrlen -= 8;
    }

    if (attr & VFS_ATTR_FAT)
    {
        attr &= ~VFS_ATTR_FAT;

        if (attrlen < 4)
            return VFS_ERR_NOROOM;

        *(uint32_t*)attrdata = data->getFatAttributes();
        attrdata += 4;
        attrlen -= 4;
    }

    // this must be last
    if (attr & VFS_ATTR_NAME)
    {
        attr &= ~VFS_ATTR_NAME;
        
        const char* name = data->getName();
        size_t len = strlen(name)+1;
        
        if (attrlen < len)
            return VFS_ERR_NOROOM;
        
        strncpy((char*)attrdata, name, attrlen);
        attrdata += len;
        attrlen -= len;        
    }
    
    if (attr)
    {
        vfs_trace_debug("Unsuporrted attributes 0x%x for operation\n", attr);
        return VFS_ERR_INVALID;
    }
    
    return VFS_ERR_OK;
}
