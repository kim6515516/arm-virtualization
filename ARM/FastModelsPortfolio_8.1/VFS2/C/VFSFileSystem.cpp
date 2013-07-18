/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*!
 * \file    VFSFileSystem.cpp
 * \brief   classes providing generic access to the underlying host filing system
 */

#include "sg/IncludeMeFirst.h"
#include "hostconf/zinttypes.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "VFSFileSystem.h"
#include "sg/MSCFixes.h"
#include "sg/SystemInclude.h"

#define trace if (0) printf

#ifdef WIN32

#define PATH_MAX MAX_PATH

#else // linux

#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <errno.h>

#endif

namespace FileSystem
{

#ifndef WIN32

// To support FAT based targets on Linux host, we opt to synthesize the HIDDEN, SYSTEM and ARCHIVE
// attributes by using the 'other' access permissions. This isn't pretty but it saves creating and
// maintaining a separate metadata file

enum FatAttributeEncoding
{
    FAT_MODE_HIDDEN = S_IROTH,
    FAT_MODE_SYSTEM = S_IWOTH,
    FAT_MODE_ARCHIVE = S_IXOTH
};

#endif

// host specific value for the VFS epoch time (chosen to be 00:00 1st Jan 1970 to simplify conversions)
static uint64_t epoch;

#ifdef WIN32

static uint64_t vfs_time_from_filetime(FILETIME ft)
{
    ULARGE_INTEGER ut;

    ut.LowPart = ft.dwLowDateTime;
    ut.HighPart = ft.dwHighDateTime;

    return (ut.QuadPart / 10000) - epoch;
}

#else

static uint64_t vfs_time_from_filetime(time_t ft)
{
    return ((uint64_t)ft * 1000) - epoch;
}

#endif

FS::FS()
{
    epoch = 0;

#ifdef WIN32
    SYSTEMTIME st;
    FILETIME ft;

    st.wYear = 1970;
    st.wMonth = 1;
    st.wDay = 1;
    st.wHour = 0;
    st.wMinute = 0;
    st.wSecond = 0;
    st.wMilliseconds = 0;

    if (!SystemTimeToFileTime(&st, &ft))
    {
        // report this as an error
    }

    epoch = vfs_time_from_filetime(ft);

#else // linux

    // in linux, this is conveniently 0.
    epoch = vfs_time_from_filetime(0);

#endif
}

FS::~FS()
{
}


Mount* FS::createMount(const char* host_path)
{
    trace("FS::createMount(%s)\n", host_path);

    Mount* mount = new Mount(this, host_path);

    return mount;
}

Mount::Mount(FS* fs, const char* path) :
    fs(fs)
{
    host_path = strdup(path);
}

Mount::~Mount()
{
    free(host_path);
    // todo - close open files/directories on the mount
}

MetaData::MetaData() : type(VFS_TYPE_NONE)
{
    hostpath = NULL;
    filename = NULL;
}

MetaData::~MetaData()
{
    if (hostpath)
        free(hostpath);

#ifdef WIN32
    if (filename)
        free(filename);
#endif
}


int32_t Mount::openFile(const char* filename, uint32_t flags, File*& file)
{
    trace("Mount::openFile(%s, 0x%x)\n", filename, flags);

    char cname[PATH_MAX];
    int32_t ret;
    
    ret = canonicalise(cname, PATH_MAX, filename);
    if (ret < 0)
        return ret;

    File* f = new File(this, cname);

    ret = f->open(flags);
    if (ret < 0)
    {
        delete f;
        return ret;
    }

    file = f;
    return VFS_ERR_OK;
}


int32_t Mount::getInfo(const char* name, MetaData* data)
{
    trace("Mount::getInfo(%s)\n", name);

    char cname[PATH_MAX];

    int32_t ret = canonicalise(cname, PATH_MAX, name);
    if (ret < 0)
        return ret;

    return data->populate(cname);
}

int32_t Mount::openDir(const char* dirname, DirIter*& iter)
{
    trace("Mount:openDir(%s)\n", dirname);

    char cname[PATH_MAX];
    int32_t ret;
    
    ret = canonicalise(cname, PATH_MAX, dirname);
    if (ret < 0)
        return ret;

    DirIter *di = new DirIter(this, cname);
    
    ret = di->open();
    if (ret < 0)
    {
        delete di;
        return ret;
    }

    iter = di;
    return VFS_ERR_OK;
}

#ifdef WIN32



static int32_t translateError(BOOL ok=FALSE)
{
    if (!ok)
    {
        DWORD err = GetLastError();

        switch (err)
        {
        case ERROR_FILE_NOT_FOUND:       return VFS_ERR_NOTFOUND;   break;
        case ERROR_PATH_NOT_FOUND:       return VFS_ERR_NOTFOUND;   break;
        case ERROR_TOO_MANY_OPEN_FILES:  return VFS_ERR_MAXHANDLE;  break;
        case ERROR_ACCESS_DENIED:        return VFS_ERR_PERM;       break;
        case ERROR_ALREADY_EXISTS:       return VFS_ERR_EXIST;      break;
        case ERROR_DIR_NOT_EMPTY:        return VFS_ERR_NOTEMPTY;   break;
        case ERROR_FILENAME_EXCED_RANGE: return VFS_ERR_TOOLONG;    break;
        case ERROR_FILE_EXISTS:          return VFS_ERR_EXIST;      break;
        default:
            {

                LPVOID lpMsgBuf;
                FormatMessage( 
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                    FORMAT_MESSAGE_FROM_SYSTEM | 
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    err,
                    0, // Default language
                    (LPTSTR) &lpMsgBuf,
                    0,
                    NULL 
                );
                trace("vfs: Unmapped windows error 0x%x: %s\n", err, lpMsgBuf);
                LocalFree( lpMsgBuf);
            }
            return VFS_ERR_UNKNOWN;
        }
    }
    else
        return VFS_ERR_OK;
}

int32_t Mount::canonicalise(char* buf, size_t len, const char* name)
{
    // under windows we have to do (a bit) more work
    // TODO - more sanity checking

    strncpy(buf, host_path, len);
    buf[len-1] = 0;

    len -= strlen(buf);
    buf += strlen(buf);

    const char* p = name;

    while ((*p!=0) && (len>0))
    {
        if (*p == '/')
            *buf++ = '\\';
        else
            *buf++ = *p;

        ++p;
        --len;
    }

    *buf = 0;

    if (len == 0)
        return VFS_ERR_TOOLONG;

    // strip off trailing backslashes
    while (*--buf == '\\')
        *buf = 0;

    // todo - wchar conversion here?
    
    return VFS_ERR_OK;
}

int MetaData::populate(const char* cname)
{
    trace("MetaData::populate(name=%s)\n", cname);

    if (hostpath)
        free(hostpath);
    if (filename)
        free(filename);

    hostpath = strdup(cname);

    WIN32_FILE_ATTRIBUTE_DATA  file_data;

    if ( !GetFileAttributesEx(hostpath,
                              GetFileExInfoStandard,
                              &file_data) )
    {
        type = VFS_TYPE_NONE;
        filename = strdup("");
        return translateError();
    }

    mtime = vfs_time_from_filetime(file_data.ftLastWriteTime);
    atime = vfs_time_from_filetime(file_data.ftLastAccessTime);
    ctime = vfs_time_from_filetime(file_data.ftCreationTime);
    
    // cache the attributes so we can generate fat attributes if required
    mode = file_data.dwFileAttributes;

    access = 0777;
    filesize = ((uint64_t)(file_data.nFileSizeHigh)<<32) + file_data.nFileSizeLow;

    char  *slash;

    slash = strrchr(hostpath, '\\');
    if ( slash )
    {
       filename = strdup(slash + 1);
    }
    else
    {
       filename = strdup("");
    }

    if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        type = VFS_TYPE_DIR;
    else
        type = VFS_TYPE_FILE;

    // TODO - links

    trace("  mtime=%"PRIu64", access=%d, filesize=%"PRIu64", type=%d, name=%s\n", mtime, access, filesize, type, filename);

    return VFS_ERR_OK;
}

// for now, this can't generate an error
uint64_t MetaData::getDiskSize() const
{
    if (hostpath)
    {
        ULARGE_INTEGER dtotal;

        if (!GetDiskFreeSpaceEx(hostpath, NULL, &dtotal, NULL))
#if 0
            return translateError(FALSE);
#else
            return 0;
#endif

        return ((uint64_t)dtotal.HighPart << 32) | dtotal.LowPart;
    }
    else
        return 0;
}

// return 'real' time
uint64_t MetaData::getRTime() const
{
    SYSTEMTIME st;
    FILETIME ft;

    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

    return vfs_time_from_filetime(ft);
}

// for now, this can't generate an error
uint64_t MetaData::getDiskFree() const
{
    if (hostpath)
    {
        ULARGE_INTEGER dfree;

        if (!GetDiskFreeSpaceEx(hostpath, &dfree, NULL, NULL))
#if 0
            return translateError(FALSE);
#else
            return 0;
#endif

        return ((uint64_t)dfree.HighPart << 32) | dfree.LowPart;
    }
    else
        return 0;
}

// these are a concession to users of fat filesystems where there are useful
// attributes that need to be stored by the underlying filesystem
uint32_t MetaData::getFatAttributes() const
{
    uint32_t attr = 0;

    if (mode & FILE_ATTRIBUTE_READONLY)
        attr |= VFS_FAT_ATTR_READONLY;
    if (mode & FILE_ATTRIBUTE_HIDDEN)
        attr |= VFS_FAT_ATTR_HIDDEN;
    if (mode & FILE_ATTRIBUTE_SYSTEM)
        attr |= VFS_FAT_ATTR_SYSTEM;
    if (mode & FILE_ATTRIBUTE_DIRECTORY)
        attr |= VFS_FAT_ATTR_DIRECTORY;
    if (mode & FILE_ATTRIBUTE_ARCHIVE)
        attr |= VFS_FAT_ATTR_ARCHIVE;
    if (mode & FILE_ATTRIBUTE_NORMAL)
        attr |= VFS_FAT_ATTR_NORMAL;

    return attr;
}

int32_t MetaData::setFatAttributes(uint32_t attr)
{
    DWORD dwAttr = 0;

    if (attr & VFS_FAT_ATTR_READONLY)
        dwAttr |= FILE_ATTRIBUTE_READONLY;
    if (attr & VFS_FAT_ATTR_HIDDEN)
        dwAttr |= FILE_ATTRIBUTE_HIDDEN;
    if (attr & VFS_FAT_ATTR_SYSTEM)
        dwAttr |= FILE_ATTRIBUTE_SYSTEM;
    if (attr & VFS_FAT_ATTR_ARCHIVE)
        dwAttr |= FILE_ATTRIBUTE_ARCHIVE;

    // not essential
    if (attr & VFS_FAT_ATTR_DIRECTORY)
    {
        if (type != VFS_TYPE_DIR)
            return VFS_ERR_NOTDIR;

        dwAttr |= FILE_ATTRIBUTE_DIRECTORY;
    }

    if (!(attr & VFS_FAT_ATTR_DIRECTORY))
    {
        if (type == VFS_TYPE_DIR)
            return VFS_ERR_ISDIR;
    }

    if (dwAttr == 0)
        dwAttr = FILE_ATTRIBUTE_NORMAL;

    return translateError(SetFileAttributes(hostpath, dwAttr));
}

int32_t Mount::createDir(const char* dirname)
{
    trace("Mount::createDir(%s)\n", dirname);

    char cname[PATH_MAX];

    int ret = canonicalise(cname, PATH_MAX, dirname);
    if (ret < 0)
        return ret;

    return translateError(CreateDirectory(cname, NULL));
}

int32_t Mount::removeDir(const char* dirname)
{
    trace("Mount::removeDir(%s)\n", dirname);

    char cname[PATH_MAX];

    int ret = canonicalise(cname, PATH_MAX, dirname);
    if (ret < 0)
        return ret;

    return translateError(RemoveDirectory(cname));
}

int32_t Mount::createFile(const char* filename)
{
    trace("Mount::createFile(%s)\n", filename);

    char cname[PATH_MAX];

    int ret = canonicalise(cname, PATH_MAX, filename);
    if (ret < 0)
        return ret;

    HANDLE fh = CreateFile(cname,
        GENERIC_READ|GENERIC_WRITE,                         // access
        FILE_SHARE_READ|FILE_SHARE_WRITE,                   // share mode
        0,                                                  // securty
        CREATE_ALWAYS,                                      // creation
        FILE_ATTRIBUTE_NORMAL,                              // flags
        NULL);                                              // template

    if (fh == INVALID_HANDLE_VALUE)
        return translateError();

    return translateError(CloseHandle(fh));
}

int32_t Mount::removeFile(const char* filename)
{
    trace("Mount::removeFile(%s)\n", filename);

    char cname[PATH_MAX];

    int ret = canonicalise(cname, PATH_MAX, filename);
    if (ret < 0)
        return ret;

    // we also let this remove directories - might need a generic 'get attr' function
    WIN32_FIND_DATA finddata;

    HANDLE fh = FindFirstFile(cname, &finddata);
    if (fh == INVALID_HANDLE_VALUE)
        return translateError(FALSE);

    FindClose(fh);

    if (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        return translateError(RemoveDirectory(cname));
    else
        return translateError(DeleteFile(cname));
}

int32_t Mount::renameObject(const char* oldname, const char* newname)
{
    trace("Mount::renameObject(%s, %s)\n", oldname, newname);

    char coldname[PATH_MAX], cnewname[PATH_MAX];
    int32_t ret;
    
    ret = canonicalise(coldname, PATH_MAX, oldname);
    if (ret < 0)
        return ret;

    ret = canonicalise(cnewname, PATH_MAX, newname);
    if (ret < 0)
        return ret;

    return translateError(MoveFile(coldname, cnewname));
}

class DirIterImpl
{
public:
    char name[PATH_MAX];
    size_t namelen;

    HANDLE fh;
    WIN32_FIND_DATA data;
    bool isValid;
};

DirIter::DirIter(Mount* mount, const char* dirname) : mount(mount)
{
    trace("DirIter::DirIter(%s)\n", dirname);

    impl = new DirIterImpl;

    impl->fh = INVALID_HANDLE_VALUE;
    impl->isValid = false;
    strncpy(impl->name, dirname, PATH_MAX);
    impl->namelen = strlen(impl->name);

    // make sure there is no / at the end if dir - canonicalise should have
    // done this
    if (impl->name[impl->namelen-1] == '\\')
        impl->name[--impl->namelen] = 0;
}

DirIter::~DirIter()
{
    close();

    delete impl;
}

int32_t DirIter::open()
{    
    trace("DirIter::open(name=%s)\n", impl->name);

    // use FindFirstFile on the directory itself to check it exists
    // this doesn't work on a root (e.g. C:\) directory so we have to fudge that
    HANDLE fh = FindFirstFile(impl->name, &impl->data);
    if (fh == INVALID_HANDLE_VALUE)
    {
        // might be a disk or server root, see if we can get attributes
        impl->data.dwFileAttributes = GetFileAttributes(impl->name);
        if (impl->data.dwFileAttributes == INVALID_FILE_ATTRIBUTES)
            return VFS_ERR_NOTFOUND;
    }
    else
        FindClose(fh);

    if (!(impl->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        return VFS_ERR_NOTDIR;

    // ok - the object exists and is a directory, put \* on the end of the name
    strcat(impl->name, "\\*");
    impl->isValid = true;

    return VFS_ERR_OK;
}

int32_t DirIter::close()
{
    trace("DirIter::close(name=%s)\n", impl->name);

    if (!isValid())
        return VFS_ERR_BADHANDLE;

    int ret;
    if (impl->fh != INVALID_HANDLE_VALUE)
    {
        ret = translateError(FindClose(impl->fh));
        impl->fh = INVALID_HANDLE_VALUE;
    }
    else
        ret = VFS_ERR_OK;

    impl->name[impl->namelen] = 0;
    impl->isValid = false;

    return ret;
}


bool DirIter::isValid() const
{
    return impl->isValid;
}

// todo - work out error codes
int DirIter::getNextInfo(MetaData* data)
{
    trace("DirIter::getNextInfo()\n");

    if (!isValid())
        return VFS_ERR_BADHANDLE;

    while (1)
    {
        if (impl->fh == INVALID_HANDLE_VALUE)
        {
            impl->fh = FindFirstFile(impl->name, &impl->data);
            if (impl->fh == INVALID_HANDLE_VALUE)
            {
                data->type = VFS_TYPE_NONE;
                return VFS_ERR_OK;
            }
        }
        else
        {
            if (!FindNextFile(impl->fh, &impl->data))
            {
                data->type = VFS_TYPE_NONE;
                return VFS_ERR_OK;
            }
        }

        // don't return '.' or '..' they just complicate matters.
        if ((impl->data.cFileName[0] == '.') && ((impl->data.cFileName[1] == 0) ||
                                                ((impl->data.cFileName[1] == '.') && impl->data.cFileName[2] == 0)))
        {
            continue;
        }

        // get the correct path for the stat
        // todo - length check
        sprintf(impl->name+impl->namelen, "\\%s", impl->data.cFileName);
        
        // todo - this seems a bit silly since we've already got the data...
        return data->populate(impl->name);
    }
}

class FileImpl
{
public:
    char name[PATH_MAX];
    HANDLE fh;
    OVERLAPPED overlapped;
};

File::File(Mount* mount, const char* host_name) : mount(mount)
{ 
    trace("File::File(%s)\n", host_name);

    impl = new FileImpl;

    strncpy(impl->name, host_name, PATH_MAX);
    impl->fh = INVALID_HANDLE_VALUE;
}

int32_t File::open(uint32_t flags)
{
    trace("File::open(0x%d:%s%s%s%s%s)\n", flags, 
        flags & VFS_OPEN_RDONLY   ? "read "     : "",
        flags & VFS_OPEN_WRONLY   ? "write "    : "",
        flags & VFS_OPEN_CREATE   ? "create "   : "",
        flags & VFS_OPEN_NEW      ? "new "      : "",
        flags & VFS_OPEN_TRUNCATE ? "truncate " : "");

    int oflags = 0;

    if ((flags & VFS_OPEN_RDWR) == VFS_OPEN_RDWR)
        oflags |= GENERIC_READ|GENERIC_WRITE;
    else if (flags & VFS_OPEN_RDONLY) 
        oflags |= GENERIC_READ;
    else if (flags & VFS_OPEN_WRONLY)
        oflags |= GENERIC_WRITE;

    DWORD create = OPEN_EXISTING;
    if (flags & VFS_OPEN_CREATE)
    {
        if (flags & VFS_OPEN_TRUNCATE)
            create = CREATE_ALWAYS;
        else if (flags & VFS_OPEN_NEW)
            create = CREATE_NEW;
        else
            create = OPEN_ALWAYS;
    }
    else if (flags & VFS_OPEN_TRUNCATE)
        create = TRUNCATE_EXISTING;

    // files are currently alwasys open shared to match the linux host implementation
    HANDLE fh = CreateFile(impl->name,
                    oflags,
                    FILE_SHARE_READ|FILE_SHARE_WRITE,
                    0,
                    create,
                    FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
                    NULL);

    if (fh == INVALID_HANDLE_VALUE)
        return translateError();

    impl->fh = fh;

    trace(" <- fd=%d\n", impl->fh);
    return VFS_ERR_OK;
}

File::~File()
{
    close();

    delete impl;
}

int32_t File::close()
{
    trace("File::close(fd=%d)\n", impl->fh);

    if (!isValid())
        return VFS_ERR_BADHANDLE;

    if (!CloseHandle(impl->fh))
        return translateError();

    impl->fh = INVALID_HANDLE_VALUE;

    return VFS_ERR_OK;
}

bool File::isValid() const
{
    return (impl->fh != INVALID_HANDLE_VALUE);
}

int32_t File::writeData(uint64_t offset, const void* data, int32_t len)
{
    trace("File::writeData(fd=%d, offset=%"PRIu64", len=%d)\n", impl->fh, offset, len);

    if (!isValid())
        return VFS_ERR_BADHANDLE;

    impl->overlapped.Offset = (uint32_t)offset;
    impl->overlapped.OffsetHigh = (uint32_t)(offset>>32);
    impl->overlapped.hEvent = 0;

    if (!WriteFile(impl->fh, data, len, NULL, &impl->overlapped))
    {
        if (GetLastError() != ERROR_IO_PENDING)
            return translateError();
    }

    DWORD rlen;
    if (!GetOverlappedResult(impl->fh, &impl->overlapped, &rlen, TRUE))
        return translateError();

    return rlen;
}

int32_t File::readData(uint64_t offset, void* data, int32_t len)
{
    trace("File::readData(fd=%d, offset=%"PRIu64", len=%d)\n", impl->fh, offset, len);

    if (!isValid())
        return VFS_ERR_BADHANDLE;

    impl->overlapped.Offset = (uint32_t)offset;
    impl->overlapped.OffsetHigh = (uint32_t)(offset>>32);
    impl->overlapped.hEvent = 0;

    if (!ReadFile(impl->fh, data, len, NULL, &impl->overlapped))
    {
        DWORD err = GetLastError();
        if (err == ERROR_HANDLE_EOF)
            return 0;

        if (err != ERROR_IO_PENDING)
            return translateError();
    }

    DWORD rlen;
    if (!GetOverlappedResult(impl->fh, &impl->overlapped, &rlen, TRUE))
    {
        DWORD err = GetLastError();
        if (err == ERROR_HANDLE_EOF)
            return 0;

        return translateError();
    }

    return rlen;
}

int32_t File::syncData()
{
    trace("File::syncData(fd=%d)\n", impl->fh);

    if (!isValid())
        return VFS_ERR_BADHANDLE;

    return translateError(FlushFileBuffers(impl->fh));
}

int32_t File::getSize(uint64_t* size)
{
    trace("File::getSize(fd=%d)", impl->fh);

    if (!isValid())
        return VFS_ERR_BADHANDLE;

    LARGE_INTEGER ret;
    if (!GetFileSizeEx(impl->fh, &ret))
        return translateError();

    *size = ret.QuadPart;

    trace("  <- size=%"PRId64"\n", *size);
    return VFS_ERR_OK;
}

int32_t File::setSize(uint64_t size)
{
    trace("File::setSize(fd=%d)\n", impl->fh);

    if (!isValid())
        return VFS_ERR_BADHANDLE;

    LARGE_INTEGER pos;

    pos.QuadPart = size;

    if (!SetFilePointerEx(impl->fh, pos, NULL, FILE_BEGIN))
        return translateError();

    return translateError(SetEndOfFile(impl->fh));
}

#else // linux

static int32_t translateError(int err)
{
    if (err == -1)
    {
        switch (errno)
        {
        case EBADF:         return VFS_ERR_BADHANDLE;
        case EACCES:        return VFS_ERR_PERM;
        case ENAMETOOLONG:  return VFS_ERR_TOOLONG;
        case ENOTDIR:       return VFS_ERR_NOTDIR;
        case ENOENT:        return VFS_ERR_NOTFOUND;
        case EPERM:         return VFS_ERR_PERM;
        case EEXIST:        return VFS_ERR_EXIST;
        case ENOSPC:        return VFS_ERR_NOROOM;
        case ENOMEM:        return VFS_ERR_NOROOM;
        case ENOTEMPTY:     return VFS_ERR_NOTEMPTY;
        case EINVAL:        return VFS_ERR_INVALID;
        case EBUSY:         return VFS_ERR_PERM;
        case EROFS:         return VFS_ERR_PERM;
        case EISDIR:        return VFS_ERR_ISDIR;
        case EMFILE:        return VFS_ERR_MAXHANDLE;
        case ENFILE:        return VFS_ERR_MAXHANDLE;
        case EXDEV:         return VFS_ERR_INVALID;
        case EFBIG:         return VFS_ERR_TOOBIG;
        case EOVERFLOW:     return VFS_ERR_TOOBIG;

        default:
            trace("untranslated host error %d\n", errno);
            return VFS_ERR_UNKNOWN;
        }
    }
    else
        return VFS_ERR_OK;
}



int MetaData::populate(const char* cname)
{
    trace("MetaData::populate(name=%s)\n", cname);

    if (hostpath)
        free(hostpath);

    hostpath = strdup(cname);

    // this should be done by using Mount to call getInfo, or by deriving from
    // MetaData
    struct stat s;
    int ret = lstat(cname, &s);
    if (ret < 0)
        return translateError(ret);

    // todo mtime, access, etc    
    mtime = vfs_time_from_filetime(s.st_mtime);
    atime = vfs_time_from_filetime(s.st_atime);
    ctime = vfs_time_from_filetime(s.st_ctime);

    access   = 0777;
    filesize = s.st_size;

    // todo - not pretty
    filename = strrchr(hostpath, '/') + 1;

    if (ret == 0)
    {
        if (S_ISREG(s.st_mode))
            type = VFS_TYPE_FILE;
        else if (S_ISDIR(s.st_mode))
            type = VFS_TYPE_DIR;
        else if (S_ISLNK(s.st_mode))
            type = VFS_TYPE_LINK;
        else
            type = VFS_TYPE_UNKNOWN;
    }
    else
    {
        type = VFS_TYPE_UNKNOWN;
    }

    // needed to synthesize fat attributes
    mode = s.st_mode;

    trace("  mtime=%"PRIu64", access=%d, filesize=%"PRIu64", type=%d, name=%s\n", 
          mtime, access, filesize, type, filename);

    return 0;
}

uint64_t MetaData::getRTime() const
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint64_t ms = ((uint64_t)tv.tv_sec * 1000) + (tv.tv_usec / 1000);

    return ms;
}

// for now, this can't generate an error
uint64_t MetaData::getDiskSize() const
{
    if (hostpath)
    {
        struct statvfs stat;

        int ret = statvfs(hostpath, &stat);

        if (ret < 0)
#if 0
            return translateError(ret);
#else
        return 0;
#endif

        return stat.f_frsize * (uint64_t)stat.f_blocks;
    }
    else
        return 0;
}

// for now, this can't generate an error
uint64_t MetaData::getDiskFree() const
{
    if (hostpath)
    {
        struct statvfs stat;

        int ret = statvfs(hostpath, &stat);
        if (ret < 0)
#if 0
            return translateError(ret);
#else
            return 0;
#endif

        return stat.f_bsize * (uint64_t)stat.f_bavail;
    }
    else
        return 0;
}

// these are a concession to users of fat filesystems where there are useful
// attributes that need to be stored by the underlying filesystem
uint32_t MetaData::getFatAttributes() const
{
    uint32_t attr = 0;

    if (!(mode & S_IWUSR))
        attr |= VFS_FAT_ATTR_READONLY;

    if (mode & FAT_MODE_HIDDEN)
        attr |= VFS_FAT_ATTR_HIDDEN;
    if (mode & FAT_MODE_SYSTEM)
        attr |= VFS_FAT_ATTR_SYSTEM;
    if (mode & FAT_MODE_ARCHIVE)
        attr |= VFS_FAT_ATTR_ARCHIVE;

    if (type == VFS_TYPE_DIR)
        attr |= VFS_FAT_ATTR_DIRECTORY;

    if (attr == 0)
        attr = VFS_FAT_ATTR_NORMAL;

    return attr;
}

int32_t MetaData::setFatAttributes(uint32_t attr)
{
    // not essential
    if ((attr & VFS_FAT_ATTR_DIRECTORY) && (type != VFS_TYPE_DIR))
        return VFS_ERR_NOTDIR;
    if (!(attr & VFS_FAT_ATTR_DIRECTORY) && (type == VFS_TYPE_DIR))
        return VFS_ERR_ISDIR;

    mode |= S_IWUSR;
    mode &= ~(FAT_MODE_HIDDEN|FAT_MODE_SYSTEM|FAT_MODE_ARCHIVE);
   
    if (attr & VFS_FAT_ATTR_READONLY)
        mode &= ~S_IWUSR;

    if (attr & VFS_FAT_ATTR_HIDDEN)
        mode |= FAT_MODE_HIDDEN;
    if (attr & VFS_FAT_ATTR_SYSTEM)
        mode |= FAT_MODE_SYSTEM;
    if (attr & VFS_FAT_ATTR_ARCHIVE)
        mode |= FAT_MODE_ARCHIVE;

    return translateError(chmod(hostpath, mode));
}

int32_t Mount::canonicalise(char* buf, size_t len, const char* name)
{
    // TODO - this should ensure the file is on the mount (i.e. strip out .. past start of mount 
    // todo - limit size
    snprintf(buf, len, "%s/%s", host_path, name);

    return VFS_ERR_OK;
}

int32_t Mount::createDir(const char* dirname)
{
    trace("Mount::createDir(%s)\n", dirname);

    char cname[PATH_MAX];

    int ret = canonicalise(cname, PATH_MAX, dirname);
    if (ret < 0)
        return ret;

    return translateError(mkdir(cname, 0777));
}

int32_t Mount::removeDir(const char* dirname)
{
    trace("Mount::removeDir(%s)\n", dirname);

    char cname[PATH_MAX];

    int ret = canonicalise(cname, PATH_MAX, dirname);
    if (ret < 0)
        return ret;

    return translateError(rmdir(cname));
}

int32_t Mount::createFile(const char* filename)
{
    trace("Mount::createFile(%s)\n", filename);

    char cname[PATH_MAX];

    int ret = canonicalise(cname, PATH_MAX, filename);
    if (ret < 0)
        return ret;

    ret = open(cname, O_RDWR|O_CREAT|O_TRUNC, 0666);
    if (ret < 0)
        return translateError(ret);

    return translateError(close(ret));
}

int32_t Mount::removeFile(const char* filename)
{
    trace("Mount::removeFile(%s)\n", filename);

    char cname[PATH_MAX];

    int ret = canonicalise(cname, PATH_MAX, filename);
    if (ret < 0)
        return ret;

    return translateError(remove(cname));
}

int32_t Mount::renameObject(const char* oldname, const char* newname)
{
    trace("Mount::renameObject(%s, %s)\n", oldname, newname);

    char coldname[PATH_MAX], cnewname[PATH_MAX];
    int32_t ret;
    
    ret = canonicalise(coldname, PATH_MAX, oldname);
    if (ret < 0)
        return ret;

    ret = canonicalise(cnewname, PATH_MAX, newname);
    if (ret < 0)
        return ret;

    return translateError(rename(coldname, cnewname));
}



class DirIterImpl
{
public:
    char name[PATH_MAX];
    int namelen;

    DIR* dir;
    struct dirent* dirent;
};

DirIter::DirIter(Mount* mount, const char* dirname) : mount(mount)
{
    trace("DirIter::DirIter(%s)\n", dirname);

    impl = new DirIterImpl;

    impl->dir = NULL;
    strncpy(impl->name, dirname, PATH_MAX);
    impl->namelen = strlen(impl->name);

    // make sure there is a / at the end of dir
    if (impl->name[impl->namelen-1] != '/')
        impl->name[impl->namelen++] = '/';
}

DirIter::~DirIter()
{
    close();

    delete impl;
}

int32_t DirIter::open()
{    
    trace("DirIter::open(name=%s)\n", impl->name);

    impl->dir = opendir(impl->name);
    if (impl->dir == NULL)
        return translateError(-1);

    return VFS_ERR_OK;
}

int32_t DirIter::close()
{
    trace("DirIter::close(name=%s)\n", impl->name);

    if (impl->dir == NULL)
        return VFS_ERR_BADHANDLE;

    int ret = translateError(closedir(impl->dir));

    impl->dir = NULL;
    impl->name[impl->namelen] = 0;

    return ret;
}


bool DirIter::isValid() const
{
    return (impl->dir != NULL);
}

// todo - work out error codes
int DirIter::getNextInfo(MetaData* data)
{
    trace("DirIter::getNextInfo()\n");

    if (!impl->dir)
        return VFS_ERR_BADHANDLE;

    while (1) 
    {
        struct dirent* d = readdir(impl->dir);

        if (!d)
        {
            trace("  end\n");

            // todo - shouldn't need to do this
            data->type = VFS_TYPE_NONE;

            // really?
            return VFS_ERR_OK;
        }

        // don't return '.' or '..' they just complicate matters.
        if ((d->d_name[0] == '.') && ((d->d_name[1] == 0) || ((d->d_name[1] == '.') && d->d_name[2] == 0)))
            continue;

        // get the correct path for the stat
        strncpy(impl->name+impl->namelen, d->d_name, PATH_MAX-impl->namelen);
        return data->populate(impl->name);
    }
}

class FileImpl
{
public:
    char name[PATH_MAX];
    int fd;
    uint64_t offset;
};

File::File(Mount* mount, const char* host_name) : mount(mount)
{ 
    trace("File::File(%s)\n", host_name);

    impl = new FileImpl;

    strncpy(impl->name, host_name, PATH_MAX);
    impl->fd = -1;
    impl->offset = 0;
}

int32_t File::open(uint32_t flags)
{
    trace("File::open(0x%d:%s%s%s%s%s)\n", flags, 
        flags & VFS_OPEN_RDONLY   ? "read "     : "",
        flags & VFS_OPEN_WRONLY   ? "write "    : "",
        flags & VFS_OPEN_CREATE   ? "create "   : "",
        flags & VFS_OPEN_NEW      ? "new "      : "",
        flags & VFS_OPEN_TRUNCATE ? "truncate " : "");

    int oflags = 0;

    if ((flags & VFS_OPEN_RDWR) == VFS_OPEN_RDWR)
        oflags |= O_RDWR;
    else if (flags & VFS_OPEN_RDONLY) 
        oflags |= O_RDONLY;
    else if (flags & VFS_OPEN_WRONLY)
        oflags |= O_WRONLY;

    if (flags & VFS_OPEN_CREATE)
        oflags |= O_CREAT;

    if (flags & VFS_OPEN_NEW)
        oflags |= O_CREAT|O_EXCL;

    if (flags & VFS_OPEN_TRUNCATE)
        oflags |= O_TRUNC;

    int ret = ::open(impl->name, oflags, 0666);
    if (ret < 0)
        return translateError(ret);

    impl->offset = 0;
    impl->fd = ret;

    trace(" <- fd=%d\n", impl->fd);
    return VFS_ERR_OK;
}

File::~File()
{
    close();

    delete impl;
}

int32_t File::close()
{
    trace("File::close(fd=%d)\n", impl->fd);

    if (impl->fd < 0)
        return VFS_ERR_BADHANDLE;

    int ret = ::close(impl->fd);

    impl->fd = -1;

    return ret;
}

bool File::isValid() const
{
    return (impl->fd >= 0);
}

int32_t File::writeData(uint64_t offset, const void* data, int32_t len)
{
    trace("File::writeData(fd=%d, offset=%"PRIu64", len=%d)\n", impl->fd, 
          offset, len);

    if (impl->fd < 0)
        return VFS_ERR_BADHANDLE;

    if (impl->offset != offset)
    {
        int64_t result = lseek64(impl->fd, (int64_t)offset, SEEK_SET);
        if (result == -1)
            return translateError(result);        

        impl->offset = result;
    }

    ssize_t ret = write(impl->fd, data, len);
    if (ret == -1)
        return translateError(ret);

    impl->offset += ret;

    return ret;
}

int32_t File::readData(uint64_t offset, void* data, int32_t len)
{
    trace("File::readData(fd=%d, offset=%"PRIu64", len=%d)\n", impl->fd, offset, len);

    if (impl->fd < 0)
        return VFS_ERR_BADHANDLE;

    if (impl->offset != offset)
    {
        int64_t result = lseek64(impl->fd, (int64_t)offset, SEEK_SET);
        if (result == -1)
            return translateError(result);

        impl->offset = (uint64_t)result;
    }

    int ret = read(impl->fd, data, len);
    if (ret == -1)
        return translateError(ret);

    impl->offset += ret;

    return ret;
}

int32_t File::syncData()
{
    trace("File::syncData(fd=%d)\n", impl->fd);

    if (impl->fd < 0)
        return VFS_ERR_BADHANDLE;

    return translateError(fsync(impl->fd));
}

int32_t File::getSize(uint64_t* size)
{
    trace("File::getSize(fd=%d)", impl->fd);

    if (impl->fd < 0)
        return VFS_ERR_BADHANDLE;

    int64_t result = lseek64(impl->fd, 0, SEEK_END);
    if (result == -1)
        return translateError(result);

    *size = result;

    impl->offset = (uint64_t)result;

    *size = impl->offset;

    trace("  <- size=%"PRId64"\n", *size);
    return VFS_ERR_OK;
}

int32_t File::setSize(uint64_t size)
{
    trace("File::setSize(fd=%d)\n", impl->fd);

    if (impl->fd < 0)
        return VFS_ERR_BADHANDLE;

    impl->offset = size;
    
    return translateError(ftruncate(impl->fd, size));
}


#endif // linux not windows

}; // namespace FileSystem

