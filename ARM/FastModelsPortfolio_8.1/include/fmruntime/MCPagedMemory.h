/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   MCPagedMemory.h
 *  \brief  Implementation of paged LISA+ MEMORY directives.
 *  \date   Copyright ARM Limited 2004,2012 All Rights Reserved.
 */

#ifndef _MCPagedMemory_h_
#define _MCPagedMemory_h_

#include <eslapi/CADITypes.h>

#include <assert.h>
#include <string.h>
#if !defined(NO_CLASS_IMP)
# define NO_CLASS_IMP
#endif
#include <MxTypes.h>
#include <MxODataStream.h>
#include <MxIDataStream.h>
#ifdef NO_CLASS_IMP
# undef NO_CLASS_IMP
#endif


// paged memory with MaxCore interface and 32 bit address type
template <class DataT, bool allowUnaligned, bool littleEndian>
class MCPagedMemory32
{
private:
    // private data
     
    // empty page always contains the fill pattern of an empty memory
    DataT *emptyPage;
    DataT **pageTable;
    typedef MxU32 AddrT;

    enum HelperEnum
    {
        NUM_BITS_PER_PAGE_IDX = 16,
        PAGE_SIZE = (1 << NUM_BITS_PER_PAGE_IDX),
        NUM_PAGES = (1 << (32 - NUM_BITS_PER_PAGE_IDX)),
        ELEMENT_IDX_MASK = PAGE_SIZE - 1,
        SAVERESTORE_VERSION = 0xa57e0000
    };
    
    // private methods

    // create page (called upon write())
    void createPage(size_t page)
    {
        // create page:
        // make pages a little bit larger so that unaligned 64 bit accesses going beyond the page end will not segfault:
        pageTable[page] = new DataT[size_t(PAGE_SIZE + (8 / sizeof(DataT)))];
        // initialize all values in this page to the fill pattern of the empty page
        memcpy(pageTable[page], emptyPage, PAGE_SIZE * sizeof(DataT));
    }



public:
    // constructor
    MCPagedMemory32() 
    {
        pageTable = new DataT*[int(NUM_PAGES)];
        // make page a little bit larger so that accesses going beyond page end will not segfault
        emptyPage = new DataT[int(PAGE_SIZE + (8 / sizeof(DataT)))];
        for(size_t i = 0; i < NUM_PAGES; i++)
            pageTable[i] = emptyPage;
        // clear initialized the emptyPage
        clear();
    }
    
    // destructor
    ~MCPagedMemory32() 
    {
        // clear frees everything except the emptyPage and the pageTable
        clear();        
        delete[] pageTable;
        delete[] emptyPage;
    }

    // provide array access
     DataT& operator [] (AddrT addr) 
    {
        size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage) // non const version allocates a new page if necessary!
            createPage(page);
        return pageTable[page][addr & ELEMENT_IDX_MASK];
    }

    // provide array access
     const DataT& operator [] (AddrT addr) const
    {
        // no allocation if an empty page is referenced! Just return the address!
        return pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    }

    // clear
    void clear() { fill(MxU8(0)); }
    
    // fill
    void fill(MxU8 fillPattern)
    {
        // free all allocated pages and fill them with the empty page
        for(size_t i = 0; i < NUM_PAGES; i++)
        {
            if(pageTable[i] != emptyPage)
            {
                delete[] pageTable[i];
                pageTable[i] = emptyPage;
            }
        }
        
        // fill the empty page with the fill pattern
        memset(emptyPage, fillPattern, sizeof(DataT) * PAGE_SIZE);
    }
    
    // fill with any size integer pattern
    template<class PatternType>
    void fill(PatternType fillPattern)
    {
        // free all allocated pages and fill them with the empty page
        for(size_t i = 0; i < NUM_PAGES; i++)
        {
            if(pageTable[i] != emptyPage)
            {
                delete[] pageTable[i];
                pageTable[i] = emptyPage;
            }
        }
        
        // three cases:
        if (sizeof(fillPattern) == sizeof(DataT)) // simple case
        {
            for(size_t i=0; i < PAGE_SIZE; ++i)
                emptyPage[i] = fillPattern;
        }
        else if (sizeof(DataT) > sizeof(fillPattern))
        {
            // double up pattern to fill one DataT:
            DataT pattern = 0;
            for(unsigned int j = 0; j < (sizeof(DataT) / sizeof(fillPattern)); ++j)
                pattern |= DataT(fillPattern) << (j * sizeof(fillPattern) * 8);

            // Fill complete page with that value
            for(size_t i=0; i < PAGE_SIZE; ++i)
                emptyPage[i] = pattern;
        }
        else    // sizeof(fillPattern) > sizeof(DataT)
        {
            unsigned int ratio = sizeof(fillPattern) / sizeof(DataT);    
            for(size_t i=0; i < PAGE_SIZE; ++i)
            {
                // shift in units of DataT width
                size_t shift = i % ratio;
                
                if (!littleEndian) // big endian
                    shift = (ratio - 1) - shift; // reverse shift

                // extract one DataT from pattern
                emptyPage[i] = DataT(fillPattern >> (shift * sizeof(DataT) * 8)); 
            }
        }
    }

    void fill8(MxU8 fillPattern)   { fill(fillPattern); }
    void fill16(MxU16 fillPattern) { fill(fillPattern); }
    void fill32(MxU32 fillPattern) { fill(fillPattern); }
    void fill64(MxU64 fillPattern) { fill(fillPattern); }

    // read and write access functions
    MxStatus read8 (AddrT addr, MxU8  &data) const;
    MxStatus read16(AddrT addr, MxU16 &data) const;
    MxStatus read32(AddrT addr, MxU32 &data) const;
    MxStatus read64(AddrT addr, MxU64 &data) const;
    MxStatus readDbg8 (AddrT addr, MxU8  &data) const { return read8 (addr, data); }
    MxStatus readDbg16(AddrT addr, MxU16 &data) const { return read16(addr, data); }
    MxStatus readDbg32(AddrT addr, MxU32 &data) const { return read32(addr, data); }
    MxStatus readDbg64(AddrT addr, MxU64 &data) const { return read64(addr, data); }
    MxStatus write8 (AddrT addr, MxU8  data);
    MxStatus write16(AddrT addr, MxU16 data);
    MxStatus write32(AddrT addr, MxU32 data);
    MxStatus write64(AddrT addr, MxU64 data);
    MxStatus writeDbg8 (AddrT addr, MxU8  data) { return write8 (addr, data); }
    MxStatus writeDbg16(AddrT addr, MxU16 data) { return write16(addr, data); }
    MxStatus writeDbg32(AddrT addr, MxU32 data) { return write32(addr, data); }
    MxStatus writeDbg64(AddrT addr, MxU64 data) { return write64(addr, data); }

    // access methods for CADI calls
    // write
    eslapi::CADIReturn_t CADI_write8(void * /*access_data */, uint32_t offset, eslapi::CADIAddrSimple_t /* baseaddress */, const uint8_t *data, uint32_t /* mauSizeInBytes */, bool)
    { write8(offset, *(reinterpret_cast<const MxU8*>(data))); return eslapi::CADI_STATUS_OK; }
    eslapi::CADIReturn_t CADI_write16(void * /*access_data*/, uint32_t offset, eslapi::CADIAddrSimple_t /* baseaddress */, const uint8_t *data, uint32_t /* mauSizeInBytes */, bool)
    { write16(offset, *(reinterpret_cast<const MxU16*>(data))); return eslapi::CADI_STATUS_OK; }
    eslapi::CADIReturn_t CADI_write32(void * /*access_data*/, uint32_t offset, eslapi::CADIAddrSimple_t /* baseaddress */, const uint8_t *data, uint32_t /* mauSizeInBytes */, bool)
    { write32(offset, *(reinterpret_cast<const MxU32*>(data))); return eslapi::CADI_STATUS_OK; }
    eslapi::CADIReturn_t CADI_write64(void * /*access_data*/, uint32_t offset, eslapi::CADIAddrSimple_t /* baseaddress */, const uint8_t *data, uint32_t /* mauSizeInBytes */, bool)
    { write64(offset, *(reinterpret_cast<const MxU64*>(data))); return eslapi::CADI_STATUS_OK; }

    // read
    eslapi::CADIReturn_t CADI_read8(void * /*access_data*/, uint32_t offset, eslapi::CADIAddrSimple_t /* baseaddress */, uint8_t *data, uint32_t /* mauSizeInBytes */, bool)
    { read8(offset, *data); return eslapi::CADI_STATUS_OK; }
    eslapi::CADIReturn_t CADI_read16(void *access_data, uint32_t offset, eslapi::CADIAddrSimple_t /* baseaddress */, uint8_t *data, uint32_t /* mauSizeInBytes */, bool)
    { read16(offset, *(reinterpret_cast<MxU16*>(data))); return eslapi::CADI_STATUS_OK; }
    eslapi::CADIReturn_t CADI_read32(void *access_data, uint32_t offset, eslapi::CADIAddrSimple_t /* baseaddress */, uint8_t *data, uint32_t /* mauSizeInBytes */, bool)
    { read32(offset,*(reinterpret_cast<uint32_t*>(data))); return eslapi::CADI_STATUS_OK; }
    eslapi::CADIReturn_t CADI_read64(void *access_data, uint32_t offset, eslapi::CADIAddrSimple_t /* baseaddress */, uint8_t *data, uint32_t /* mauSizeInBytes */, bool)
    { read64(offset, *(reinterpret_cast<uint64_t*>(data))); return eslapi::CADI_STATUS_OK; }

    // take care when editing save or restore: they have to be 100% symmetric!
    bool save(MxODataStream &os)
    {
        // write header
        os << MxU32(SAVERESTORE_VERSION);
        os << MxU32(NUM_PAGES);
        os << MxU32(PAGE_SIZE);
        os << MxU32(sizeof(AddrT));
        os << MxU32(sizeof(DataT));
        // count and write number of allocated pages
        MxU32 numPages = 0;
        MxU32 i = 0;
        for(i = 0; i < NUM_PAGES; i++)
            if(pageTable[i] != emptyPage)
                numPages++;
        os << MxU32(numPages);
        // write empty page
        os.writeRawBytes((const char *)emptyPage, PAGE_SIZE * sizeof(DataT));
        // write all other pages
        for(i = 0; i < NUM_PAGES; i++)
        {
            if(pageTable[i] != emptyPage)
            {
                // write page index
                os << MxU32(i);
                // write page
                os.writeRawBytes((const char *)(pageTable[i]), PAGE_SIZE * sizeof(DataT));
            }
        }
        // storing always succeeds
        return true;
    }

    bool restore(MxIDataStream &is)
    {
        // clear memory
        clear();
        // read header
        MxU32 version = 0;
        MxU32 rNUM_PAGES = 0;
        MxU32 rPAGE_SIZE = 0;
        MxU32 sizeof_AddrT = 0;
        MxU32 sizeof_DataT = 0;
        MxU32 numPages = 0;
        is >> version;
        is >> rNUM_PAGES;
        is >> rPAGE_SIZE;
        is >> sizeof_AddrT;
        is >> sizeof_DataT;
        is >> numPages;
        // check consistency
        if((version != SAVERESTORE_VERSION) ||
           (rNUM_PAGES != NUM_PAGES) ||
           (rPAGE_SIZE != PAGE_SIZE) ||
           (sizeof_AddrT != sizeof(AddrT)) ||
           (sizeof_DataT != sizeof(DataT)))
            return false;
        if(numPages > NUM_PAGES) 
            return false;
        // read emptyPage
        is.readRawBytes((char *)emptyPage, PAGE_SIZE * sizeof(DataT));
        // read all other pages
        for(MxU32 i = 0; i < numPages; i++)
        {
            // read page index
            MxU32 page = 0;
            is >> page;
            if(page >= NUM_PAGES)
                return false;
            // read page
            pageTable[page] = new DataT[PAGE_SIZE + (8 / sizeof(DataT))];    
            is.readRawBytes((char *)(pageTable[page]), PAGE_SIZE * sizeof(DataT));
        }
        // done
        return true;
    }
    
    // find next non-zero address for addresses >= addr
    // (do not use for annotated memories, used for validProgramMemoryAddresses only)
    // (this routine treats all empty pages as zero, no matter whether they are really zero or not)
    // (addr may stay the same if addr is non-zero)
    // (returns false if and only if all addresses >= addr are zero)
    bool findNextNonZeroAddress(AddrT &addr) const
    {
        AddrT a = addr & ELEMENT_IDX_MASK;
        AddrT page = addr >> NUM_BITS_PER_PAGE_IDX;
        AddrT restOfPage = PAGE_SIZE - a;
        
        // loop over all following pages (including the current page)
        for(; page < NUM_PAGES; page++)
        {
            // if the current page is empty skip it
            if(pageTable[page] != emptyPage)
            {
                // loop over all addresses in the current page (starting at a)
                for(; a < restOfPage; a++)
                {
                    if(pageTable[page][a])
                    {
                        // found non-zero address
                        addr = a | (page << NUM_BITS_PER_PAGE_IDX);
                        return true;
                    }
                }
            }
                        
            // try next page
            a = 0;
            restOfPage = PAGE_SIZE;
        }
        
        // no non-zero address >= addr found
        return false;
    }
    
    // get direct read/write access to element
    // (do not use for annotated memories, used for validProgramMemoryAddresses only)
    // (if the accesse page is still empty a new page is always allocated)
    DataT& directReadWrite(AddrT addr)
    {
        size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        return pageTable[page][addr & ELEMENT_IDX_MASK];
    }
    
    // get direct read access to element
    // (do not use for annotated memories, used for validProgramMemoryAddresses only)
    // (no page is allocated if accesses element is empty)
    DataT directRead(AddrT addr) const
    {
        return pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    }
};

// MxU8 memory ======================================================================================================================================================

// read8 and write8 are the same for allowUnaligned=true or false and littleEndian=true/false, but we can not use partial template member specialisation since gcc 2.95.x does not support it
template<> inline MxStatus MCPagedMemory32<MxU8, true, true>::read8(AddrT addr, MxU8 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, true>::read8(AddrT addr, MxU8 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, false>::read8(AddrT addr, MxU8 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, false>::read8(AddrT addr, MxU8 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, true>::write8(AddrT addr, MxU8 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, true>::write8(AddrT addr, MxU8 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, false>::write8(AddrT addr, MxU8 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, false>::write8(AddrT addr, MxU8 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}


// read16/write16

template<> inline MxStatus MCPagedMemory32<MxU8, true, true>::read16(AddrT addr, MxU16 &data) const
{
    if ((addr & 1) == 0) // aligned access, which cannot cross page boundary
    {
        // do single 16 bit access, potentially unaligned
        data = *reinterpret_cast<const MxU16 *>(&(pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK]));
    }
    else
    {   // crossing page boundary
        data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] 
            | (pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK] << 8);
    }
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, true>::read16(AddrT addr, MxU16 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (16 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU8 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = p[addr & ELEMENT_IDX_MASK] | (p[(addr + 1) & ELEMENT_IDX_MASK] << 8);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, false>::read16(AddrT addr, MxU16 &data) const
{
    data = (pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] << 8) 
        | pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, false>::read16(AddrT addr, MxU16 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (16 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU8 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = (p[addr & ELEMENT_IDX_MASK] << 8) | p[(addr + 1) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, true>::write16(AddrT addr, MxU16 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    if ((addr & 1) == 0)        // an aligned access never crosses a page boundary
    {
        // single 16 bit write:
        *reinterpret_cast<MxU16 *>(&(pageTable[page][addr & ELEMENT_IDX_MASK])) = data;
    }
    else
    {
        pageTable[page][addr & ELEMENT_IDX_MASK] = (MxU8)data;
        page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 8;
    }
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, true>::write16(AddrT addr, MxU16 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (16 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = (MxU8)data;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 8;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, false>::write16(AddrT addr, MxU16 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 8;
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = (MxU8)data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, false>::write16(AddrT addr, MxU16 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (16 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 8;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = (MxU8)data;
    return MX_STATUS_OK;
}


// read32/write32

template<> inline MxStatus MCPagedMemory32<MxU8, true, true>::read32(AddrT addr, MxU32 &data) const
{
    if ((addr & 3) == 0) // aligned access, which cannot cross page boundary
    {
        // do single 32 bit access, potentially unaligned
        data = *reinterpret_cast<const MxU32 *>(&(pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK]));
    }
    else
    {// crossing page boundary
        data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] 
            | (pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK] << 8)
            | (pageTable[(addr + 2) >> NUM_BITS_PER_PAGE_IDX][(addr + 2) & ELEMENT_IDX_MASK] << 16)
            | (pageTable[(addr + 3) >> NUM_BITS_PER_PAGE_IDX][(addr + 3) & ELEMENT_IDX_MASK] << 24);
    }

    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, true>::read32(AddrT addr, MxU32 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 3)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (32 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU8 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = p[addr & ELEMENT_IDX_MASK] 
        | (p[(addr + 1) & ELEMENT_IDX_MASK] << 8)
        | (p[(addr + 2) & ELEMENT_IDX_MASK] << 16)
        | (p[(addr + 3) & ELEMENT_IDX_MASK] << 24);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, false>::read32(AddrT addr, MxU32 &data) const
{
    data = (pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] << 24) 
        | (pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK] << 16) 
        | (pageTable[(addr + 2) >> NUM_BITS_PER_PAGE_IDX][(addr + 2) & ELEMENT_IDX_MASK] << 8) 
            | pageTable[(addr + 3) >> NUM_BITS_PER_PAGE_IDX][(addr + 3) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, false>::read32(AddrT addr, MxU32 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 3)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (32 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU8 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = (p[addr & ELEMENT_IDX_MASK] << 24) 
        | (p[(addr + 1) & ELEMENT_IDX_MASK] << 16) 
        | (p[(addr + 2) & ELEMENT_IDX_MASK] << 8)
        | p[(addr + 3) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, true>::write32(AddrT addr, MxU32 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    if ((addr & 3) == 0)        // an aligned access never crosses a page boundary
    {
        // single 32 bit write:
        *reinterpret_cast<MxU32 *>(&(pageTable[page][addr & ELEMENT_IDX_MASK])) = data;
    }
    else
    {
        pageTable[page][addr & ELEMENT_IDX_MASK] = data;
        page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 8;
        page = (addr + 2) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = data >> 16;
        page = (addr + 3) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = data >> 24;
    }
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, true>::write32(AddrT addr, MxU32 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 3)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (32 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 8;
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = data >> 16;
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = data >> 24;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, false>::write32(AddrT addr, MxU32 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 24;
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 16;
    page = (addr + 2) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = data >> 8;
    page = (addr + 3) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, false>::write32(AddrT addr, MxU32 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 3)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (32 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 24;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 16;
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = data >> 8;
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}


// read64/write64
template<> inline MxStatus MCPagedMemory32<MxU8, true, true>::read64(AddrT addr, MxU64 &data) const
{
    if ((addr & 7) == 0) // aligned access, which cannot cross page boundary
    {
        // do single 64 bit access, potentially unaligned
        data = *reinterpret_cast<const MxU64 *>(&(pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK]));
    }
    else                        // crossing page boundary
    {
        data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] 
            | (MxU32(pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK]) << 8)
            | (MxU32(pageTable[(addr + 2) >> NUM_BITS_PER_PAGE_IDX][(addr + 2) & ELEMENT_IDX_MASK]) << 16)
            | (MxU32(pageTable[(addr + 3) >> NUM_BITS_PER_PAGE_IDX][(addr + 3) & ELEMENT_IDX_MASK]) << 24)
            | (MxU64(pageTable[(addr + 4) >> NUM_BITS_PER_PAGE_IDX][(addr + 4) & ELEMENT_IDX_MASK]) << 32)
            | (MxU64(pageTable[(addr + 5) >> NUM_BITS_PER_PAGE_IDX][(addr + 5) & ELEMENT_IDX_MASK]) << 40)
            | (MxU64(pageTable[(addr + 6) >> NUM_BITS_PER_PAGE_IDX][(addr + 6) & ELEMENT_IDX_MASK]) << 48)
            | (MxU64(pageTable[(addr + 7) >> NUM_BITS_PER_PAGE_IDX][(addr + 7) & ELEMENT_IDX_MASK]) << 56);
    }
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, true>::read64(AddrT addr, MxU64 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 7)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU8 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = p[addr & ELEMENT_IDX_MASK] 
        | (MxU32(p[(addr + 1) & ELEMENT_IDX_MASK]) << 8)
        | (MxU32(p[(addr + 2) & ELEMENT_IDX_MASK]) << 16)
        | (MxU32(p[(addr + 3) & ELEMENT_IDX_MASK]) << 24)
        | (MxU64(p[(addr + 4) & ELEMENT_IDX_MASK]) << 32)
        | (MxU64(p[(addr + 5) & ELEMENT_IDX_MASK]) << 40)
        | (MxU64(p[(addr + 6) & ELEMENT_IDX_MASK]) << 48)
        | (MxU64(p[(addr + 7) & ELEMENT_IDX_MASK]) << 56);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, false>::read64(AddrT addr, MxU64 &data) const
{
    data = (MxU64(pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK]) << 56)
        | (MxU64(pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK]) << 48)
        | (MxU64(pageTable[(addr + 2) >> NUM_BITS_PER_PAGE_IDX][(addr + 2) & ELEMENT_IDX_MASK]) << 40)
        | (MxU64(pageTable[(addr + 3) >> NUM_BITS_PER_PAGE_IDX][(addr + 3) & ELEMENT_IDX_MASK]) << 32)
        | (MxU32(pageTable[(addr + 4) >> NUM_BITS_PER_PAGE_IDX][(addr + 4) & ELEMENT_IDX_MASK]) << 24)
        | (MxU32(pageTable[(addr + 5) >> NUM_BITS_PER_PAGE_IDX][(addr + 5) & ELEMENT_IDX_MASK]) << 16)
        | (MxU32(pageTable[(addr + 6) >> NUM_BITS_PER_PAGE_IDX][(addr + 6) & ELEMENT_IDX_MASK]) << 8)
        | pageTable[(addr + 7) >> NUM_BITS_PER_PAGE_IDX][(addr + 7) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, false>::read64(AddrT addr, MxU64 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 7)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU8 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = (MxU64(p[addr & ELEMENT_IDX_MASK]) << 56)
        | (MxU64(p[(addr + 1) & ELEMENT_IDX_MASK]) << 48) 
        | (MxU64(p[(addr + 2) & ELEMENT_IDX_MASK]) << 40)
        | (MxU64(p[(addr + 3) & ELEMENT_IDX_MASK]) << 32)
        | (MxU32(p[(addr + 4) & ELEMENT_IDX_MASK]) << 24)
        | (MxU32(p[(addr + 5) & ELEMENT_IDX_MASK]) << 16)
        | (MxU32(p[(addr + 6) & ELEMENT_IDX_MASK]) << 8)
        | p[(addr + 7) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, true>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    if ((addr & 7) == 0)        // an aligned access never crosses a page boundary
    {
        // single 64 bit write:
        *reinterpret_cast<MxU64 *>(&(pageTable[page][addr & ELEMENT_IDX_MASK])) = data;
    }
    else
    {
        pageTable[page][addr & ELEMENT_IDX_MASK] = (MxU8)data;
        page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = (MxU8)(data >> 8);
        page = (addr + 2) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = (MxU8)(data >> 16);
        page = (addr + 3) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = (MxU8)(data >> 24);
        page = (addr + 4) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 4) & ELEMENT_IDX_MASK] = (MxU8)(data >> 32);
        page = (addr + 5) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 5) & ELEMENT_IDX_MASK] = (MxU8)(data >> 40);
        page = (addr + 6) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 6) & ELEMENT_IDX_MASK] = (MxU8)(data >> 48);
        page = (addr + 7) >> NUM_BITS_PER_PAGE_IDX;
        if (pageTable[page] == emptyPage)
            createPage(page);
        pageTable[page][(addr + 7) & ELEMENT_IDX_MASK] = (MxU8)(data >> 56);
    }
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, true>::write64(AddrT addr, MxU64 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 7)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = (MxU8)data;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = (MxU8)(data >> 8);
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = (MxU8)(data >> 16);
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = (MxU8)(data >> 24);
    pageTable[page][(addr + 4) & ELEMENT_IDX_MASK] = (MxU8)(data >> 32);
    pageTable[page][(addr + 5) & ELEMENT_IDX_MASK] = (MxU8)(data >> 40);
    pageTable[page][(addr + 6) & ELEMENT_IDX_MASK] = (MxU8)(data >> 48);
    pageTable[page][(addr + 7) & ELEMENT_IDX_MASK] = (MxU8)(data >> 56);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU8, true, false>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = (MxU8)(data >> 56);
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = (MxU8)(data >> 48);
    page = (addr + 2) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = (MxU8)(data >> 40);
    page = (addr + 3) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = (MxU8)(data >> 32);
    page = (addr + 4) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 4) & ELEMENT_IDX_MASK] = (MxU8)(data >> 24);
    page = (addr + 5) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 5) & ELEMENT_IDX_MASK] = (MxU8)(data >> 16);
    page = (addr + 6) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 6) & ELEMENT_IDX_MASK] = (MxU8)(data >> 8);
    page = (addr + 7) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 7) & ELEMENT_IDX_MASK] = (MxU8)data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU8, false, false>::write64(AddrT addr, MxU64 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 7)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = (MxU8)(data >> 56);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = (MxU8)(data >> 48);
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = (MxU8)(data >> 40);
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = (MxU8)(data >> 32);
    pageTable[page][(addr + 4) & ELEMENT_IDX_MASK] = (MxU8)(data >> 24);
    pageTable[page][(addr + 5) & ELEMENT_IDX_MASK] = (MxU8)(data >> 16);
    pageTable[page][(addr + 6) & ELEMENT_IDX_MASK] = (MxU8)(data >> 8);
    pageTable[page][(addr + 7) & ELEMENT_IDX_MASK] = (MxU8)(data);
    return MX_STATUS_OK;
}


// MxU16 memory ======================================================================================================================================================

// read16 and write16 are the same for allowUnaligned=true or false and littleEndian=true/false, but we can not use partial template member specialisation since gcc 2.95.x does not support it
template<> inline MxStatus MCPagedMemory32<MxU16, true, true>::read16(AddrT addr, MxU16 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, true>::read16(AddrT addr, MxU16 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, false>::read16(AddrT addr, MxU16 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, false>::read16(AddrT addr, MxU16 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, true>::write16(AddrT addr, MxU16 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, true>::write16(AddrT addr, MxU16 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, false>::write16(AddrT addr, MxU16 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, false>::write16(AddrT addr, MxU16 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}


// read32/write32
template<> inline MxStatus MCPagedMemory32<MxU16, true, true>::read32(AddrT addr, MxU32 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] 
        | (pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK] << 16);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, true>::read32(AddrT addr, MxU32 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (32 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU16 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = p[addr & ELEMENT_IDX_MASK] | (p[(addr + 1) & ELEMENT_IDX_MASK] << 16);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, false>::read32(AddrT addr, MxU32 &data) const
{
    data = (pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] << 16) 
        | pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, false>::read32(AddrT addr, MxU32 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (32 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU16 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = (p[addr & ELEMENT_IDX_MASK] << 16) | p[(addr + 1) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, true>::write32(AddrT addr, MxU32 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 16;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, true>::write32(AddrT addr, MxU32 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (32 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 16;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, false>::write32(AddrT addr, MxU32 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 16;
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, false>::write32(AddrT addr, MxU32 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (32 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 16;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}


// read64/write64
template<> inline MxStatus MCPagedMemory32<MxU16, true, true>::read64(AddrT addr, MxU64 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] 
        | (MxU32(pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK]) << 16)
        | (MxU64(pageTable[(addr + 2) >> NUM_BITS_PER_PAGE_IDX][(addr + 2) & ELEMENT_IDX_MASK]) << 32)
        | (MxU64(pageTable[(addr + 3) >> NUM_BITS_PER_PAGE_IDX][(addr + 3) & ELEMENT_IDX_MASK]) << 48);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, true>::read64(AddrT addr, MxU64 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 3)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU16 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = p[addr & ELEMENT_IDX_MASK] 
        | (MxU32(p[(addr + 1) & ELEMENT_IDX_MASK]) << 16)
        | (MxU64(p[(addr + 2) & ELEMENT_IDX_MASK]) << 32)
        | (MxU64(p[(addr + 3) & ELEMENT_IDX_MASK]) << 48);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, false>::read64(AddrT addr, MxU64 &data) const
{
    data = (MxU64(pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK]) << 48)
        | (MxU64(pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK]) << 32)
        | (MxU32(pageTable[(addr + 2) >> NUM_BITS_PER_PAGE_IDX][(addr + 2) & ELEMENT_IDX_MASK]) << 16)
            | pageTable[(addr + 3) >> NUM_BITS_PER_PAGE_IDX][(addr + 3) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, false>::read64(AddrT addr, MxU64 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 3)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU16 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = (MxU64(p[addr & ELEMENT_IDX_MASK]) << 48) 
        | (MxU64(p[(addr + 1) & ELEMENT_IDX_MASK]) << 32)
        | (MxU32(p[(addr + 2) & ELEMENT_IDX_MASK]) << 16)
        | p[(addr + 3) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, true>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 16;
    page = (addr + 2) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = data >> 32;
    page = (addr + 3) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = data >> 48;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, true>::write64(AddrT addr, MxU64 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 3)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 16;
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = data >> 32;
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = data >> 48;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU16, true, false>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 48;
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 32;
    page = (addr + 2) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = data >> 16;
    page = (addr + 3) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU16, false, false>::write64(AddrT addr, MxU64 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 3)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 48;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 32;
    pageTable[page][(addr + 2) & ELEMENT_IDX_MASK] = data >> 16;
    pageTable[page][(addr + 3) & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}


// MxU32 memory ======================================================================================================================================================

// read32 and write32 are the same for allowUnaligned=true or false and littleEndian=true/false, but we can not use partial template member specialisation since gcc 2.95.x does not support it
template<> inline MxStatus MCPagedMemory32<MxU32, true, true>::read32(AddrT addr, MxU32 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, false, true>::read32(AddrT addr, MxU32 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, true, false>::read32(AddrT addr, MxU32 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, false, false>::read32(AddrT addr, MxU32 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, true, true>::write32(AddrT addr, MxU32 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU32, false, true>::write32(AddrT addr, MxU32 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, true, false>::write32(AddrT addr, MxU32 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU32, false, false>::write32(AddrT addr, MxU32 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}


// read64/write64
template<> inline MxStatus MCPagedMemory32<MxU32, true, true>::read64(AddrT addr, MxU64 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK] 
        | (MxU64(pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK]) << 32);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, false, true>::read64(AddrT addr, MxU64 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU32 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = p[addr & ELEMENT_IDX_MASK] | (MxU64(p[(addr + 1) & ELEMENT_IDX_MASK]) << 32);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, true, false>::read64(AddrT addr, MxU64 &data) const
{
    data = (MxU64(pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK]) << 32)
        | pageTable[(addr + 1) >> NUM_BITS_PER_PAGE_IDX][(addr + 1) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, false, false>::read64(AddrT addr, MxU64 &data) const
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit read at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    MxU32 *p = pageTable[addr >> NUM_BITS_PER_PAGE_IDX];
    data = (MxU64(p[addr & ELEMENT_IDX_MASK]) << 32) | p[(addr + 1) & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, true, true>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 32;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU32, false, true>::write64(AddrT addr, MxU64 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data >> 32;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU32, true, false>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 32;
    page = (addr + 1) >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU32, false, false>::write64(AddrT addr, MxU64 data)
{
#ifdef SIMGEN_DEBUG
    if (addr & 1)
    {
        printf("Error: MEMORY resource not configured for unaligned accesses (64 bit write at 0x%08x)\n"
               "Please add attribute 'allow_unaligned_access(true)' to this MEMORY resource.\n", 
               addr);
    }
#endif
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data >> 32;
    pageTable[page][(addr + 1) & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}


// MxU64 memory ======================================================================================================================================================

// read64 and write64 are the same for allowUnaligned=true or false and littleEndian=true/false, but we can not use partial template member specialisation since gcc 2.95.x does not support it
template<> inline MxStatus MCPagedMemory32<MxU64, true, true>::read64(AddrT addr, MxU64 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU64, false, true>::read64(AddrT addr, MxU64 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU64, true, false>::read64(AddrT addr, MxU64 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU64, false, false>::read64(AddrT addr, MxU64 &data) const
{
    data = pageTable[addr >> NUM_BITS_PER_PAGE_IDX][addr & ELEMENT_IDX_MASK];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU64, true, true>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU64, false, true>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}

template<> inline MxStatus MCPagedMemory32<MxU64, true, false>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCPagedMemory32<MxU64, false, false>::write64(AddrT addr, MxU64 data)
{
    size_t page = addr >> NUM_BITS_PER_PAGE_IDX;
    if (pageTable[page] == emptyPage)
        createPage(page);
    pageTable[page][addr & ELEMENT_IDX_MASK] = data;
    return MX_STATUS_OK;
}


#endif // _MCPagedMemory_h_

