/*!
 * \file    FlashLoader.h
 * \brief   Support loading a gzipped image into Flash.
 * \date    Copyright 2004-2008 ARM Limited. All rights reserved.
 *
 * Load a flash image file into flash.
 */

#ifndef FLASHLOADER_H
#define FLASHLOADER_H

#include <string>

#define OPEN_FOR_READ 1
#define OPEN_FOR_WRITE 2

template <typename T> class InternalRegister;

class FlashLoaderState;

class FlashLoader
{
 public:
    typedef InternalRegister<size_t> ProgressMonitor;

 protected:
    FlashLoaderState *state;

    void setProgress(size_t new_offset);

 public:
    FlashLoader();
    ~FlashLoader();

    /*! Allow a listener to observe load progress. */
    void setProgressMonitor(ProgressMonitor *);

    /*! Open a flash file for reading/writing. Returns false on failure. */
    bool open(std::string const & filename, uint32_t readwrite);

    /*! Close the flash file handle (if one is open). */
    void close();

    /*! Read data from file into buffer.  Returns number of bytes written.
     *  If return value is less than buffer_size, then end-of-file 
     *  has been reached.
     */
    size_t readData(uint8_t *buffer, size_t buffer_size);

    /*! Write data from buffer into file. Returns number of bytes read.
     */
    size_t writeData(const uint8_t *buffer, size_t buffer_size);
};

#endif
