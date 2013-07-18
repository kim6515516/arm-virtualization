/*
 * $Id: FileInterface.h 28624 2011-07-07 14:19:29Z pgotch $
 *
 * Project:  File Interface
 * $Author: pgotch $
 * $Date: 2011-07-07 15:19:29 +0100 (Thu, 07 Jul 2011) $
 * $Revision: 28624 $
 *
 * Copyright (c) 2000-2011 by ARM
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM
 * All rights reserved.
 */

/** \file
 * File Interface implementation.
 */

#ifndef _FileInterface_h_
#define _FileInterface_h_

#include <stdio.h>
#include <string>
#include <stdlib.h>

class FileInterface
{
public:
    FileInterface(const char* filename);
    virtual ~FileInterface();

    virtual int fseek(long offset, int whence) = 0;
    virtual long ftell() = 0;
    virtual int feof() = 0;

    virtual size_t read(void *ptr, size_t count) = 0;

    void rewind();
    char *fgets(char *s, int size);
    void getline(std::string& str);
    int fgetc();
    size_t fread(void *ptr, size_t size, size_t nmemb);

    char* filename;
};


class RawFileInterface: public FileInterface
{
public:
    RawFileInterface(const char* filename);
    virtual ~RawFileInterface();

    virtual int fseek(long offset, int whence);
    virtual long ftell();
    virtual int feof();
    virtual size_t read(void *ptr, size_t count);

private:
    FILE* filehandle;
};


int fseek(FileInterface *stream, long offset, int whence);
long ftell(FileInterface *stream);
void rewind(FileInterface *stream);
int feof(FileInterface *stream);

size_t fread(void *ptr, size_t size, size_t nmemb, FileInterface *stream);
char *fgets(char *s, int size, FileInterface *stream);
FileInterface* getline(FileInterface *stream, std::string& str);
#endif
