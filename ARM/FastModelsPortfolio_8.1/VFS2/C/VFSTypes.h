/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*!
 * \file    VFSTypes.h
 * \brief   public VFS types/functions shared between target/host side
 *
 */

#ifndef VFSTYPES_H
#define VFSTYPES_H


// todo - move these to be common to host/target code, and common to C/C++
enum VFSError
{
    VFS_ERR_OK        =  0,     // all ok (actually 0 or +ve means ok)
    VFS_ERR_BADHANDLE = -1,     // invalid or wrong type of handle
    VFS_ERR_NOENTRY   = -2,     // no more entries in a directory
    VFS_ERR_NOROOM    = -3,     // ran out of memory/buffer/disk space
    VFS_ERR_MAXHANDLE = -4,     // ran out of handles
    VFS_ERR_NOMOUNT   = -5,     // no such mount exists
    VFS_ERR_NOTFOUND  = -6,     // object not found
    VFS_ERR_PERM      = -7,     // permission error
    VFS_ERR_NOTDIR    = -8,     // path element wasn't a directory
    VFS_ERR_TOOLONG   = -9,     // path or path element too long
    VFS_ERR_EXIST     = -10,    // an object with the name already exists
    VFS_ERR_NOTEMPTY  = -11,    // tried to remove a directory that wasn't empty
    VFS_ERR_INVALID   = -12,    // invalid operation or operand, e.g. bad pathname
    VFS_ERR_ISDIR     = -13,    // object is a directory
    VFS_ERR_TOOBIG    = -14,    // parameter or return value was too large to represent
    VFS_ERR_UNIMPL    = -15,    // unimplemented feature
    VFS_ERR_UNKNOWN   = -100    // unexpected host error
};

// Objects types that can exist on a filesystem
// \todo do we need NONE and UNKNOWN?
// \todo mount is only used internally
enum VFSType
{
    VFS_TYPE_NONE,      // file not found
    VFS_TYPE_FILE,      // regular file
    VFS_TYPE_DIR,       // directory
    VFS_TYPE_LINK,      // symbolic link
    VFS_TYPE_UNKNOWN,   // unknown/other object type
    VFS_TYPE_MOUNT      // mount point
};

// flags passed to Mount::openFile
// \todo change these to be 0, 1 and 2
enum VFSOpenFlags
{
    VFS_OPEN_RDONLY = 1,    // open file for reading
    VFS_OPEN_WRONLY = 2,    // open file for writing
    VFS_OPEN_RDWR   = VFS_OPEN_RDONLY|VFS_OPEN_WRONLY,
    VFS_OPEN_CREATE   = 4,  // create file if it doesn't exist
    VFS_OPEN_NEW      = 8,  // file must not exist when opening
    VFS_OPEN_TRUNCATE = 16  // truncate file when opening
};

/*! Bitfield values passed in calls that send/receive attribute blocks.
 *
 *  Attribues must be passed/will be returned in increasing attribute bitfield value
 *
 *  The object name (VFS_ATTR_NAME) attribute must always be last in the attribute block
 */
enum VFSAttr
{
    VFS_ATTR_MTIME    = 0x0001, // uint64_t modification time
    VFS_ATTR_ACCESS   = 0x0002, // uint32_t access permissions (read/write/execute etc)    
    VFS_ATTR_TYPE     = 0x0004, // uint32_t object type (as above)
    VFS_ATTR_SIZE     = 0x0008, // uint64_t object size in bytes
    VFS_ATTR_CTIME    = 0x0010, // uint64_t object creation time (if supported)
    VFS_ATTR_ATIME    = 0x0020, // uint64_t object access time
    VFS_ATTR_RTIME    = 0x0040, // uint64_t current real time
    VFS_ATTR_DISKSIZE = 0x0100, // uint64_t size of disk in bytes
    VFS_ATTR_DISKFREE = 0x0200, // uint64_t free space on disk in bytes
    VFS_ATTR_FAT      = 0x0400, // uint32_t synthesized FAT attributes as defined below
    VFS_ATTR_NAME     = 0x8000, // char*    object name
};

/*! Bitfield values passed in the VFA_ATTR_FAT attribute. 
 *
 *  Not all fat attributes are supported.
 *
 *  On Linux hosts some of these bits are synthesized by the use
 *  of 'other' permission bits. For newly created files these bits are unlikely
 *  to represent the correct attribute values so, for target filesystems using
 *  FAT attributes, setattr with VFS_ATTR_FAT must be called after each file or
 *  directory is created. Files created by the host rather than the target will
 *  have the same issue and there is currently no solution to this problem.
 */
enum VFSFatAttr
{
    VFS_FAT_ATTR_READONLY = 0x0001, // file/directory is read only
    VFS_FAT_ATTR_HIDDEN   = 0x0002, // file/directory should normally be hidden
    VFS_FAT_ATTR_SYSTEM   = 0x0004, // file/directory is a system file
    VFS_FAT_ATTR_DIRECTORY= 0x0010, // object is a directory, not a file
    VFS_FAT_ATTR_ARCHIVE  = 0x0020, // object should be archived
    VFS_FAT_ATTR_NORMAL   = 0x0080, // file/directory has no other attributes set
};

/*! general VFS constants
 */
enum VFSTraits
{
    VFS_MAX_PATH     = 1024,    // maximum length of a path
    VFS_MAX_HANDLES  = 256,     // maximun number of open handles
    VFS_MAX_TRANSFER = 4096     // largest single data transfer (e.g. in readfile)
};

#endif // VFSTYPES_H


