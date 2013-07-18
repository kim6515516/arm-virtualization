/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*
 *
 * client side vfs layer implementation in C++
 *
 * This class can be used, along with support classes and a suitable
 * messagebox implementation, to provide a client interface to the
 * device VFS implementation.
 *
 * This could share a common interface definition with the server side
 * to reenforce the link
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "messagebox.h"
#include "MessageCodec.h"
#include "VFSOps.h"
#include "vfs.h"

VFS::VFS(MessageBox* mb_)
{
    mb = mb_;
    mc = new MessageComposer(NULL, 0);
    md = new MessageDecomposer(NULL, 0);
}

VFS::~VFS()
{
    delete mc;
    delete md;
}

/*
 * begin the process of a vfs transaction
 * - request a messagebox buffer
 * - prepare the message composer
 * - add the standard vfs arguments
 */
void VFS::startcall(uint32_t op)
{
    void* buffer = mb->start(8192);

    mc->reinit(buffer, 8192);

    mc->put_uint32(0);        // message id
    mc->put_uint32(op);       // vfs operation
}

/*
 * send the vfs operation to the vfs device and get a reply
 * - send the outgoing message
 * - receive the reply
 * - prepare the decoder
 * - retrieve the common results
 */
void VFS::docall()
{
    void* buffer;
    uint32_t blen;
    uint32_t id;

    int ret = mb->end(mc->get_size());

    // drivers should go and do something else and wait for the interrupt
    while (!mb->ready())
        ;

    buffer = mb->receive(&blen);

    md->reinit(buffer, blen);

    md->get_uint32(&id);       // message id inserted above
   
    // todo - check the id's match
}

/*
 * end a vfs transaction to the VFS device
 */
void VFS::endcall()
{
}

/*
 * routines to generate transactions to perform vfs operations
 */

int32_t VFS::openmounts()
{
    int32_t handle;

    startcall(VFS_OPENMOUNTS);

        docall();
        md->get_int32(&handle);

    endcall();

    return handle;
}

int32_t VFS::readmounts(int32_t handle, uint32_t attr, uint8_t* attrdata, uint32_t attrdatalen)
{
    int32_t ret;

    startcall(VFS_READMOUNTS);

        mc->put_int32(handle);
        mc->put_uint32(attr);
        mc->put_uint32(attrdatalen);

        docall();

        md->get_int32(&ret);
        md->get_data(attrdata, &attrdatalen);

    endcall();

    return ret;
}

int32_t VFS::closemounts(int32_t handle)
{
    int32_t ret;

    startcall(VFS_READMOUNTS);

        mc->put_int32(handle);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::opendir(const char* dirname)
{
    int32_t ret;

    startcall(VFS_OPENDIR);

        mc->put_cstr(dirname);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::readdir(int32_t handle, uint32_t attr, uint8_t* attrdata, uint32_t attrdatalen)
{
    int32_t ret;

    startcall(VFS_READDIR);

        mc->put_int32(handle);
        mc->put_uint32(attr);
        mc->put_uint32(attrdatalen);

        docall();

        md->get_int32(&ret);
        md->get_data(attrdata, &attrdatalen);

    endcall();

    return ret;
}

int32_t VFS::closedir(int32_t handle)
{
    int32_t ret;

    startcall(VFS_CLOSEDIR);

        mc->put_int32(handle);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::mkdir(const char* name)
{
    int32_t ret;

    startcall(VFS_MKDIR);

        mc->put_cstr(name);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::rmdir(const char* name)
{
    int32_t ret;

    startcall(VFS_RMDIR);

        mc->put_cstr(name);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::remove(const char* name)
{
    int32_t ret;

    startcall(VFS_REMOVE);

        mc->put_cstr(name);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::rename(const char* oldname, const char* newname)
{
    int32_t ret;

    startcall(VFS_RENAME);

        mc->put_cstr(oldname);
        mc->put_cstr(newname);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::getattr(const char* name, uint32_t attr, uint8_t* attrdata, uint32_t attrdatalen)
{
    int32_t ret;

    startcall(VFS_GETATTR);

        mc->put_cstr(name);
        mc->put_uint32(attr);
        mc->put_uint32(attrdatalen);

        docall();

        md->get_int32(&ret);
        md->get_data(attrdata, &attrdatalen);

    endcall();

    return ret;
}

int32_t VFS::setattr(const char* name, uint32_t attr, const uint8_t* attrdata, uint32_t attrdatalen)
{
    int32_t ret;

    startcall(VFS_SETATTR);

        mc->put_cstr(name);
        mc->put_uint32(attr);
        mc->put_data(attrdata, attrdatalen);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::openfile(const char* name, uint32_t flags)
{
    int32_t ret;

    startcall(VFS_OPENFILE);

        mc->put_cstr(name);
        mc->put_uint32(flags);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::closefile(int32_t handle)
{
    int32_t ret;

    startcall(VFS_CLOSEFILE);

        mc->put_int32(handle);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::writefile(int32_t handle, uint64_t offset, const void* data, int32_t len)
{
    int32_t ret;
    int32_t residual = len;

    // Transfer has to be broken into manageable chunks

    while (residual > 0)
    {
        int32_t t_len = (residual > VFS_MAX_TRANSFER) ? VFS_MAX_TRANSFER : residual;

        startcall(VFS_WRITEFILE);

            mc->put_int32(handle);
            mc->put_uint64(offset);
            mc->put_data(data, t_len);
            mc->put_uint32(t_len);       // why?

            docall();

            md->get_int32(&ret);

        endcall();

        if (ret < 0)
            return ret;

        if (ret == 0)
            break;

        offset += ret;
        residual -= ret;
        data = (uint8_t*)data + ret;
    }

    return len-residual;
}

int32_t VFS::readfile(int32_t handle, uint64_t offset, void* data, int32_t len)
{
    int32_t ret;
    int32_t residual = len;
    uint32_t rlen = len;

    // data must be sent in manageable chunks

    while (residual > 0)
    {
        int32_t t_len = (residual > VFS_MAX_TRANSFER) ? VFS_MAX_TRANSFER : residual;

        startcall(VFS_READFILE);

            mc->put_int32(handle);
            mc->put_uint64(offset);
            mc->put_uint32(t_len); 

            docall();

            md->get_int32(&ret);
            md->get_data(data, &rlen);

        endcall();

           if (ret < 0)
                return ret;

            if (ret == 0)
                break;

        offset += ret;
        residual -= ret;
        data = (uint8_t*)data + ret;
    }

    return len-residual;
}

int32_t VFS::getfilesize(int32_t handle, uint64_t* size)
{
    int32_t ret;

    startcall(VFS_GETFILESIZE);

        mc->put_int32(handle);

        docall();

        md->get_int32(&ret);
        md->get_uint64(size);

    endcall();

    return ret;
}

int32_t VFS::setfilesize(int32_t handle, uint64_t size)
{
    int32_t ret;

    startcall(VFS_SETFILESIZE);

        mc->put_int32(handle);
        mc->put_uint64(size);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::filesync(int32_t handle)
{
    int32_t ret;

    startcall(VFS_FILESYNC);

        mc->put_int32(handle);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::symlink(const char* filename, const char* symlink)
{
    int32_t ret;

    startcall(VFS_SYMLINK);

        mc->put_cstr(filename);
        mc->put_cstr(symlink);

        docall();

        md->get_int32(&ret);

    endcall();

    return ret;
}

int32_t VFS::readlink(const char* filename, char* buf, int32_t bufsiz)
{
    int32_t ret;
    uint32_t rlen;

    startcall(VFS_READLINK);

        mc->put_cstr(filename);
        mc->put_int32(bufsiz);

        docall();

        md->get_int32(&ret);
        md->get_data(buf, &rlen);

    endcall();

    return ret;
}

