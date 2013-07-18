/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*!
 * \file    test.cpp
 * \brief   Test/example of bare metal access to the
 *          VMFS via the MessageBox PrimeCell peripheral.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "vfs.h"
#include "messagebox.h"


/////////////////////////////////////////////////////////////////////////////////////////////
// test code

// VFS has been added to the EB model with
//  registers/buffer at 0x100a0000
//  irq 41

#define MB_BASE 0x100a0000

static VFS* vfs;
static char cwd[1024];

void set_cwd(const char* path)
{
    strcpy(cwd, path);
}

const char* get_cwd()
{
    return cwd;
}

void list_mounts()
{
    int32_t handle;
    uint8_t attrdata[1024];
    uint32_t attrlen = 1024;
    int32_t ret;

    ret = vfs->openmounts();
    if (ret < 0)
    {
        printf("unable to get mount handle\n");
        return;
    }
    
    handle = ret;

    do {
        ret = vfs->readmounts( handle, VFS_ATTR_DISKSIZE|VFS_ATTR_DISKFREE|VFS_ATTR_NAME, attrdata, attrlen);

        if (ret >= 0)
    {
        uint8_t* ptr = &attrdata[0];

        uint64_t dsize = *(uint64_t*)ptr; ptr+=sizeof(uint64_t);
        uint64_t dfree = *(uint64_t*)ptr; ptr+=sizeof(uint64_t);
        char* name = (char*)ptr;

            printf("mount = %s\n", name);
        printf("disk size=%lld, free=%lld\n", dsize, dfree); 
    }
    } while (ret >= 0);

    vfs->closemounts( handle);
}

void list(const char* dir)
{
    int32_t handle;
    uint8_t attrdata[1024];
    uint32_t attrlen = 1024;
    int32_t ret;

    ret = vfs->opendir( dir);
    if (ret < 0)
    {
        printf("opendir failed\n");
        return;
    }

    handle = ret;

    do {
        ret = vfs->readdir( handle, VFS_ATTR_NAME, attrdata, attrlen);

        if (ret >= 0)
        {
            printf("  %s\n", (char*)attrdata);
        }
    } while (ret >= 0);

    vfs->closedir( handle);
}

void list_long(const char* dir)
{
    int32_t handle;
    uint8_t attrdata[1024];
    uint32_t attrlen = 1024;
    int32_t ret;

    ret = vfs->opendir( dir);
    if (ret < 0)
    {
        printf("opendir failed\n");
        return;
    }

    handle = ret;

    do {
        ret = vfs->readdir( handle, VFS_ATTR_MTIME|VFS_ATTR_NAME|VFS_ATTR_TYPE, attrdata, attrlen);

        if (ret >= 0)
        {
            const char* ftypename[] = { "None", "File", "Dir ", "Link", "Unkn" };
            int type;
            const char* name;
            uint64_t mtime;

            mtime = *(uint64_t*)attrdata;
            type = *(uint32_t*)(attrdata+8);
            name = (const char*)(attrdata+0xc);

            // convert back to seconds. the epoch is correct
            time_t mt = mtime / 1000;

            printf("%s %s %s\n", ftypename[type], name, ctime(&mt));
        }
    } while (ret >= 0);

    vfs->closedir( handle);
}

int make_dir(const char* dirname)
{
    char path[1024];
    sprintf(path, "%s%s", get_cwd(), dirname);

    return vfs->mkdir( path);
}

int remove_dir(const char* dirname)
{
    char path[1024];
    sprintf(path, "%s%s", get_cwd(), dirname);

    return vfs->rmdir( path);
}

int open_file(const char* filename, uint32_t flags)
{
    char path[1024];
    sprintf(path, "%s%s", get_cwd(), filename);

    return vfs->openfile( path, flags);
}

int close_file(int handle)
{
    return vfs->closefile( handle);
}

int read_file(int handle, uint64_t offset, void* data, int32_t len)
{
    return vfs->readfile( handle, offset, data, len);
}

int write_file(int handle, uint64_t offset, void* data, int32_t len)
{
    return vfs->writefile( handle, offset, data, len);
}

int remove_file(const char* filename)
{
    char path[1024];
    sprintf(path, "%s%s", get_cwd(), filename);

    return vfs->remove( path);
}

int rename_file(const char* oldname, const char* newname)
{
    char oldpath[1024];
    char newpath[1024];
    sprintf(oldpath, "%s%s", get_cwd(), oldname);
    sprintf(newpath, "%s%s", get_cwd(), newname);

    return vfs->rename( oldpath, newpath);

}

int main()
{
    MessageBox* mb = MessageBox::Instantiate(MB_BASE);

    vfs = new VFS(mb);

    printf("MessageBox id = 0x%x\n", mb->getId());

    printf("checking we can read mounts...\n");
    list_mounts();

    // from here on we assume a mount called("A:/").
    // we really want a simple command interpreter/script

    set_cwd("A:/");

    printf("listing top level directory...\n");
    list(get_cwd());

    printf("listing top level directory with some meta info...\n");
    list_long(get_cwd());

    printf("make a directory\n");
    make_dir("a_dir");
    list_long(get_cwd());
    
    printf("remove a directory\n");
    remove_dir("a_dir");
    list_long(get_cwd());

    printf("create a file\n");
    
    {
        int fd = open_file("a_file", VFS_OPEN_RDWR|VFS_OPEN_CREATE);
        if (fd >= 0)
        {
            write_file(fd, 0, (void*)"abcdef", 6);
            close_file(fd);
        }
        else
        {
            printf("Error: failed to create file\n");
        }
    }
    list_long(get_cwd());

    printf("read a file\n");
    {
        int fd = open_file("a_file", VFS_OPEN_RDWR);
        if (fd >= 0)
        {
            char buffer[7];

            read_file(fd, 0, buffer, 6);
            close_file(fd);


            if (strncmp(buffer, "abcdef", 6))
            {
                printf("file contents differ\n");
            }
            else
            {
                printf("contents match\n");
            }
        }
        else
        {
            printf("Error: failed to open file\n");
        }
    }

    printf("create a large file\n");
    {
        int fd = open_file("a_file", VFS_OPEN_RDWR|VFS_OPEN_CREATE);
        if (fd >= 0)
        {
            uint8_t buffer[128*1024];
            int i;
            for (i=0; i<128*1024; ++i)
                buffer[i] = i&0xff;

            write_file(fd, 0, buffer, 128*1024);
            close_file(fd);
        }
        else
        {
            printf("Error: failed to create file\n");
        }
    }

    printf("read a large file\n");
    {
        int fd = open_file("a_file", VFS_OPEN_RDWR);
        if (fd >= 0)
        {
            uint8_t buffer[128*1024];
            int i;

            read_file(fd, 0, buffer, 128*1024);
            close_file(fd);

            for (i=0; i<128*1024; ++i)
            {
                if (buffer[i] != (i&0xff))
                {
                    printf("files differ at offset %d (=%d)\n", i, buffer[i]);
                    break;
                }
            }
            if (i == 128*1024)
            {
                printf("files match\n");
            }
        }
        else
        {
            printf("Error: failed to create file\n");
        }
    }

    printf("write to part of a large file\n");
    {
        int fd = open_file("a_file", VFS_OPEN_RDWR);
        if (fd >= 0)
        {
            uint8_t buffer[1024];
            int i;
            for (i=0; i<1024; ++i)
                buffer[i] = i&0xff;

            write_file(fd, 2000, buffer, 1024);
            close_file(fd);
        }
        else
        {
            printf("Error: failed to open file\n");
        }
    }

    printf("read part of a large file\n");
    {
        int fd = open_file("a_file", VFS_OPEN_RDWR);
        if (fd >= 0)
        {
            uint8_t buffer[1024];
            int i;

            read_file(fd, 2000, buffer, 1024);
            close_file(fd);

            for (i=0; i<1024; ++i)
            {
                if (buffer[i] != (i&0xff))
                {
                    printf("files differ at offset %d\n (=%d)", i, buffer[i]);
                    break;
                }
            }
            if (i == 1024)
            {
                printf("files match\n");
            }
        }
        else
        {
            printf("Error: failed to open file\n");
        }
    }
    printf("rename a file\n");
    rename_file("a_file", "b_file");
    list_long(get_cwd());

    printf("delete a file\n");
    remove_file("b_file");
    list_long(get_cwd());

    delete vfs;
    delete mb;

    return 0;
}
