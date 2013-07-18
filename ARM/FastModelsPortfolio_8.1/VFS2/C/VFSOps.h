/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*!
 * \file    VFSOps.h
 * \brief   functions/operations internal to vfs shared on target/host side
 *
 */

#ifndef VFSOPS_H
#define VFSOPS_H

// VFS operation values passed in VFS messages
enum VFSOp
{
    VFS_OPENMOUNTS      = 0,
    VFS_READMOUNTS      = 1,
    VFS_CLOSEMOUNTS     = 2,
    
    VFS_OPENDIR         = 3,
    VFS_READDIR         = 4,
    VFS_CLOSEDIR        = 5,
    VFS_MKDIR           = 6,
    VFS_RMDIR           = 7,
    VFS_REMOVE          = 8,
    VFS_RENAME          = 9,
    VFS_GETATTR         = 10,
    VFS_SETATTR         = 11,
    
    VFS_OPENFILE        = 12,
    VFS_CLOSEFILE       = 13,
    VFS_WRITEFILE       = 14,
    VFS_READFILE        = 15,
    VFS_GETFILESIZE     = 16,
    VFS_SETFILESIZE     = 17,
    VFS_FILESYNC        = 18,
    
    VFS_SYMLINK         = 19,
    VFS_READLINK        = 20
};


#endif // VFSOPS_H


