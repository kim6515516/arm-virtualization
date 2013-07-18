/*
 * (C) Copyright 2008 ARM Limited. All rights reserved.
 * (C) Copyright 2011 ARM Limited. All rights reserved.
 */

#include <string>
#include <iostream>
#include <sstream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BS_TRACE if (!0) ; else printf

#include "sg/SystemInclude.h"

#ifndef _WIN32
// POSIX-like systems

#ifndef _LARGEFILE64_SOURCE
#error _LARGEFILE64_SOURCE needs to be defined for Linux builds
#endif

#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

using namespace std;

#define BS_BAD_FILE    (-1)
#define BS_MAP_FAILED  (MAP_FAILED)
#define BS_ERRNUM      ((int32_t)errno)
#define BS_MFDESC      int
#define BS_STAT        stat
#define BS_STAT_T      stat

#else
#define BS_BAD_FILE    (INVALID_HANDLE_VALUE)
#define BS_MAP_FAILED  (NULL)
#define BS_ERRNUM      ((int32_t)GetLastError())
#define BS_MFDESC      HANDLE
#define BS_STAT        _stati64
#define BS_STAT_T      _stati64
#endif


class BackingStore {
public:
    BackingStore(const char *fn, const char *id_str="") :
        m_id_str(id_str), m_fname(fn), m_map_desc(0), m_len(0), m_pageSize(getPageSize()), m_readOnly(false)
    {
        m_pageMask = ~(m_pageSize -1);

        if (open_file())
        {   // Couldn't open the file
            m_fname = NULL;
        }
    }

    ~BackingStore()
    {
        if (m_fname)
        {
            close_file();
        }
    }

    int32_t getLastError(void)
    {
        return m_lastError;
    }

    const char *getLastErrorMessage(void)
    {
        return m_strLastError.c_str();
    }

    // Returns size of backing store, or 0 if no store available
    inline uint64_t size(void)
    {
        if (!m_fname)
            return(0);

        return(m_filelen);
    }

    inline bool isMapped(void)
    {
        return(m_len != 0);
    }

    inline bool isReadOnly(void)
    {
        return(m_readOnly);
    }

    // Return a pointer to a particular offset in the file
    // Offset is modulo block_size
    // Block size must be a power of two, and less than our page size,
    // but that's not currently policed.
    inline bool
    accessBlock(uint64_t offset, uint64_t block_size, uint8_t **ptr)
    {
        offset &= ~(block_size -1);
        // check if block is in the mapped page:
        // - is the first byte of the block below (<) the first byte of the page?
        // - or is the first byte after the block beyond (>) the first byte after the page?
        // (bugfix: >= is wrong, bugfix solved broken jpgs and broken text files)
        if ((offset < m_off) ||
            ((offset+block_size) > (m_off+m_len)))
        {
            map(offset);
        }

        if ((offset < m_off) ||
            ((offset+block_size) > (m_off+m_len)))
        {
            // set output pointer to 0 to mark operation as not successful
            // otherwise we silently write into some random block
            *ptr = 0;
            return false;
        }

        offset = (offset & (~m_pageMask));
        *ptr = &((uint8_t *)m_pa)[offset];
        return true;
    }

    // Overloading the array operators might be fun, but for now...
    // access functions:
    inline uint32_t getWord(uint64_t offset)
    {
        offset &= ~3;
        if ((offset < m_off) || (offset >= (m_off+m_len)))
        {
            map(offset);
        }

        if (!m_len) {
            return(0xdeaddead);
        }

        offset = (offset & (~m_pageMask)) >> 2;
        return(((uint32_t *)m_pa)[offset]);
    }

    inline uint8_t getByte(uint64_t offset)
    {
        if ((offset < m_off) || (offset >= (m_off+m_len)))
        {
            map(offset);
        }

        if (!m_len) {
            return(0xde);
        }

        offset = (offset & (~m_pageMask));
        return(((uint8_t *)m_pa)[offset]);
    }

    inline void putByte(uint64_t offset, uint8_t data)
    {
        if ((offset < m_off) || (offset >= (m_off+m_len)))
        {
            map(offset);
        }

        if (!m_len) {
            return;
        }

        offset = (offset & (~m_pageMask));
        ((uint8_t *)m_pa)[offset] = data;
    }

private:
    const std::string   m_id_str;   // Identifier for error / trace messages

    const char    *m_fname;    // NULL if no file is open
    uint64_t       m_filelen;  // Length of the backing store
    BS_MFDESC      m_desc;     // OS-dependent file descriptor
    BS_MFDESC      m_map_desc; // Windows requires an additional descriptor
    void          *m_pa;       // Currently physical address of mapping
    uint64_t       m_off;      // Offset of the current mapping
    uint64_t       m_len;      // Length of the current mapping (0 if none)

    const uint64_t m_pageSize; // This system's page size
    uint64_t       m_pageMask; // The pagesize -1, inverted
    string         m_strLastError;
    int32_t        m_lastError;
    bool           m_readOnly;  // true if read only file

    template < class T >
        string ToString(const T &arg)
        {
            std::ostringstream out;
            out << arg;
            return (out.str());
        }

    template < class T >
        string ToHexString(const T &arg)
        {
            std::ostringstream out;
            out << std::ios::hex << arg;
            return ("0x" + out.str());
        }

    int open_file()
    {
        m_lastError = 0;

        // First stat the file
        struct BS_STAT_T st;
        if (BS_STAT(m_fname, &st) == -1)
        {
            m_strLastError = (string)"no image file connected";
            m_lastError = 1;
            m_filelen = 0;
            m_fname = NULL;
            return m_lastError;
        }
        m_filelen = st.st_size;

        // Then open it
#ifdef WIN32
        m_desc  = CreateFile(m_fname, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
                             NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#else   // POSIX
        m_desc  = open(m_fname, O_RDWR);
#endif
        if (m_desc == BS_BAD_FILE)
        {
            /* Try and re-open as read-only */
#ifdef WIN32
            m_desc  = CreateFile(m_fname, GENERIC_READ, FILE_SHARE_READ,
                                 NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#else   // POSIX
            m_desc  = open(m_fname, O_RDONLY);
#endif
            m_readOnly = (m_desc != BS_BAD_FILE);
        }
        if (m_desc == BS_BAD_FILE)
        {
            m_strLastError = (string)"Couldn't open '" + m_fname + "' (" + ToString(errno) + ")";
            m_fname = NULL;
            m_lastError = -1;
            return m_lastError;
        }

        BS_TRACE("%s: Opened '%s'%s.\n", m_id_str.c_str(), m_fname,
                 (m_readOnly? " readonly": ""));

#ifdef WIN32
        // Windows also needs to create a mapping object
        if (m_readOnly)
        {
            m_map_desc = CreateFileMapping(m_desc, NULL, PAGE_READONLY, 0, 0, NULL);
        }
        else
        {
            m_map_desc = CreateFileMapping(m_desc, NULL, PAGE_READWRITE, 0, 0, NULL);
        }
        if (m_map_desc == NULL)
        {
            close_file();
            m_strLastError = (string)"CreateFileMapping failed (" + ToString(BS_ERRNUM) + ")";
            m_lastError = -1;
            return m_lastError;
        }
#endif

        map(0);        // Perform initial mapping
        return m_lastError;
    } // open_file


    // Closes m_desc, if m_fname != 0
    // Under Windows, closes m_map_desc, if the desc != NULL
    int close_file(void)
    {
        m_lastError = 0;

        if (m_fname)
        {
#ifdef WIN32
            if (CloseHandle(m_desc) == 0)
#else
            if (close(m_desc) != 0)
#endif
            {
                m_strLastError = (string)"Could not close file '" + m_fname + "'";
                m_lastError = -1;
            } else {
                BS_TRACE("%s: Closed '%s'\n", m_id_str.c_str(), m_fname);
                m_fname = NULL;
                m_readOnly = false;
            }
        }

        // Windows should also close m_map_desc, if it's open
#ifdef WIN32
        if (m_map_desc != NULL)
        {
            if (CloseHandle(m_map_desc) == 0)
            {
                m_strLastError = (string)"Could not close m_map_desc (" + ToString(BS_ERRNUM) + ")";
                m_lastError = -2;
            } else {
                m_map_desc = NULL;
            }
        }
#endif

        return m_lastError;
    }


    //
    // Generic map / unmap functions
    //  - Will try and map a page / minimum allocation size,
    //    storing the pointer in m_pa. m_len contains the size
    //    of the allocated portion, or zero if we didn't map anything
    //  - Will not map a page beyond the filesize (even a partial
    //    page, to be consistent with Windows)
    //  - Return true on success, false on any failure

    bool map(uint64_t offset)
    {
        m_lastError = 0;
        unmap();

        offset = offset & m_pageMask;

        if ((offset + m_pageSize) > m_filelen)
        {
            m_strLastError = (string)"Won't map beyond the end of '" + m_fname + "' "
                + ToHexString(offset) + "-" + ToHexString(offset + m_pageSize) + " exceeds " + ToHexString(m_filelen);
            m_lastError = -1;
            m_len = 0;
            return false;
        }

        void *pa;
#ifdef WIN32
        uint32_t offset_L, offset_H;
        offset_L = offset & 0xffffffffULL;
        offset_H = offset>>32;
        pa = MapViewOfFile(m_map_desc, (m_readOnly? FILE_MAP_READ: FILE_MAP_WRITE), offset_H, offset_L, m_pageSize);
#else
        pa = mmap64(NULL, m_pageSize, (m_readOnly? PROT_READ: PROT_READ | PROT_WRITE), MAP_SHARED, m_desc, offset);
#endif
        if (pa == BS_MAP_FAILED)
        {
            m_strLastError = (string)"map (off=" + ToHexString(offset) + ") failed (" + ToString(BS_ERRNUM) + ").";
            m_lastError = -1;
            m_len = 0;
            return false;
        }
        m_len = m_pageSize;
        m_off = offset;
        m_pa  = pa;
        BS_TRACE("%s: Mapped '%s' off=0x%016" PRIu64 " to %p\n",
                 m_id_str.c_str(), m_fname, m_off, m_pa);
        return true;
    }

    bool unmap(void)
    {
        m_lastError = 0;
        if (m_len == 0)
            return true; // nothing was mapped

#ifdef WIN32
        if (UnmapViewOfFile(m_pa) == 0)
#else
        if (munmap(m_pa, m_len) == -1)
#endif
        {
            m_strLastError = (string)"unmap (" + ToHexString(m_pa) + ", " + ToHexString(m_len)
                + ") failed (" + ToString(BS_ERRNUM) + ").";
            m_lastError = -1;
            return false;
        }
        BS_TRACE("%s: Unmapped from %p.\n", m_id_str.c_str(), m_pa);
        return  true;
    }

    uint64_t getPageSize(void)
    {
#ifdef WIN32
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        BS_TRACE("%s: AllocationGranularity: 0x%x\n",
                 m_id_str.c_str(), si.dwAllocationGranularity);
        return((uint64_t)si.dwAllocationGranularity);

#else  // POSIX
        long ps = sysconf(_SC_PAGESIZE);
        BS_TRACE("%s: Pagesize: 0x%lx\n", m_id_str.c_str(), ps);
        return((uint64_t)ps);
#endif
    }

};

