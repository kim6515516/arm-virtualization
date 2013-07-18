/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

#ifndef VFS_H
#define VFS_H

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

#include "VFSTypes.h"

class MessageBox;
class MessageComposer;
class MessageDecomposer;

class VFS
{
    MessageBox*         mb;
    MessageComposer*    mc;
    MessageDecomposer*  md;

    void startcall(uint32_t op);
    void docall();
    void endcall();

public:

    VFS(MessageBox*);
    ~VFS();

    /*! Open an iterator on the list of mounts added with add Mount
     * 
     * \return a handle to be used with readmounts/closemounts or a VFSError code
     */
    int32_t openmounts();

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
    int32_t readmounts(int32_t handle, uint32_t attr, uint8_t* attrdata, uint32_t attrdatalen);

    /* Close a mount iterator handle
     *
     * \param id        mount iterator handle
     *
     * \return VFSError code
     */
    int32_t closemounts(int32_t handle);

    /* Open a directory iterator handle
     *
     * \param name      full (vfs) path name to directory
     *
     * \return directory iterator handle for use with readdir/closedir or a VFSError code
     */
    int32_t opendir(const char* dirname);

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
    int32_t readdir(int32_t handle, uint32_t attr, uint8_t* attrdata, uint32_t attrdatalen);

    /* Close a directory iterator
     *
     * \param id        directory iterator handle
     *
     * \return VFSError code
     */
    int32_t closedir(int32_t handle);

    /* Create a directory
     *
     * \param name      (vfs) directory name to create
     *
     * \return VFSError code
     */
    int32_t mkdir(const char* name);

    /* Remove a directory
     *
     * \param name      (vfs) directory name to create
     *
     * \return VFSError code
     */
    int32_t rmdir(const char* name);

    /* Remove a file
     *
     * \param name      (vfs) file to remove (may also work on other object types)
     *
     * \return VFSError code
     */
    int32_t remove(const char* name);

    /* Rename an object
     *
     * \param oldname   (vfs) object to rename
     * \param newname   (vfs) new name of object
     *
     * \return VFSError code
     */
    int32_t rename(const char* oldname, const char* newname);

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
    int32_t getattr(const char* name, uint32_t attr, uint8_t* attrdata, uint32_t attrdatalen);

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
    int32_t setattr(const char* name, uint32_t attr, const uint8_t* attrdata, uint32_t attrdatalen);

    /* Open a file object on the filesystem for reading/writing
     *
     * \param filename  (vfs) file name
     * \param flags     VFSOpenFlags value indicating how to open the file
     *
     * \return file handle to use with readfile/writefile/closefile etc or a VFSError code
     */
    int32_t openfile(const char* name, uint32_t flags);

    /* Close a file object by a handle returned from openfile
     *
     * \param id        file handle
     *
     * \return VFSError code
     */
    int32_t closefile(int32_t handle);

    /* Write data to a file 
     *
     * \param id        file handle returned from openfile
     * \param offset    offset into file from where to start writing
     * \param data      pointer to data block containing data to be written
     * \param len       length of data to be written
     * 
     * \return length of data actually written to the file or a VFSError code
     */
    int32_t writefile(int32_t handle, uint64_t offset, const void* data, int32_t len);

    /* Read data from a file 
     *
     * \param id        file handle returned from openfile
     * \param offset    offset into file from where to start reading
     * \param data      pointer to data block to receive data read from file
     * \param len       size of data block to receive data
     * 
     * \return length of data actually read from the file or a VFSError code
     */
    int32_t readfile(int32_t handle, uint64_t offset, void* data, int32_t len);

    /* Get the size of an open file
     *
     * \param id        file handle returned from openfile
     * \param size      pointer to instance data to receive file size
     *
     * \return VFSError code
     */
    int32_t getfilesize(int32_t handle, uint64_t* size);

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
    int32_t setfilesize(int32_t handle, uint64_t size);

    /* Force modified parts of a file back to persistent storage
     *
     * \param id        file handle returned from openfile
     *
     * \return VFSError code
     */
    int32_t filesync(int32_t handle);

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
    int32_t symlink(const char* filename, const char* symlink);

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
    int32_t readlink(const char* filename, char* buf, int32_t bufsiz);
};


#endif // VFS_H
