/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   MCPagedMemory.h
 *  \brief  Paged Memory Class
 *  \date   Copyright ARM Limited 2004 All Rights Reserved.
 *  
 */

#ifndef _MCNonPagedMemory_h_
#define _MCNonPagedMemory_h_

#ifdef SIMGEN_DEBUG
#define CHECK_MEMORY_SIZE(size, address, numElements)    { \
    if ((address + numElements) > size) { printf("Error: Memory size exceeded: Max size is %d , address is 0x%08x , number of elements is %d\n", size, address, numElements); assert(!"Memory access out of bounce!"); } }
#else
#define CHECK_MEMORY_SIZE(size, address, numElements)
#endif

#define SAVERESTORE_VERSION 0xa57e0000

#include <eslapi/CADITypes.h>

// paged memory with MaxCore interface and 32 bit address type
template <class DataT, bool littleEndian>
class MCNonPagedMemory32
{
private:
    MxU32 size;
    DataT *memData;

    typedef MxU32 AddrT;

public:
    MCNonPagedMemory32(MxU32 size) : size(size)
    {
        memData = new DataT[size];
        clear();
    }

    ~MCNonPagedMemory32() 
    {
        delete[] memData;
    }

    // provide array access
     DataT& operator [] (AddrT addr) 
    {
        return memData[addr];
    }

    // provide array access
     const DataT& operator [] (AddrT addr) const
    {
        return memData[addr];
    }

    // clear
    void clear() { fill(0); }

    // fill with any size integer pattern
    template<class PatternType>
    void fill(PatternType fillPattern)
    {
        if (sizeof(MxU8) == sizeof(fillPattern))
        {
            memset(memData, fillPattern, sizeof(DataT) * size);
        }
        else if (sizeof(fillPattern) >= sizeof(DataT))
        {
            unsigned int ratio = sizeof(fillPattern) / sizeof(DataT);
            for(size_t i=0; i < size; ++i)
            {
                // shift in units of DataT width
                size_t shift = i % ratio;
                
                if (!littleEndian) // big endian
                    shift = (ratio - 1) - shift; // reverse shift

                // extract one DataT from pattern
                memData[i] = DataT(fillPattern >> (shift * sizeof(DataT) * 8));
            }
        }
        else
        {
            switch (sizeof(fillPattern))
            {
            case sizeof(MxU16):
                for (size_t i = 0; i < sizeof(DataT) * size / sizeof(fillPattern); ++i)
                    reinterpret_cast<MxU16*>(memData)[i] = fillPattern;
                break;
            case 4:
                for (size_t i = 0; i < sizeof(DataT) * size / sizeof(fillPattern); ++i)
                    reinterpret_cast<MxU32*>(memData)[i] = fillPattern;
                break;
            case 8:
                for (size_t i = 0; i < sizeof(DataT) * size / sizeof(fillPattern); ++i)
                    reinterpret_cast<MxU64*>(memData)[i] = fillPattern;
                break;
            default:
                for (size_t i = 0; i < sizeof(DataT) * size / sizeof(fillPattern); ++i)
                {
                    for (size_t j = 0; j < sizeof(fillPattern); ++j)
                        reinterpret_cast<MxU8*>(memData)[i * sizeof(fillPattern) + j] = reinterpret_cast<MxU8*>(&fillPattern)[j];
                }
                break;
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

    bool save(MxODataStream &os)
    {
        os << MxU32(SAVERESTORE_VERSION);
        os << MxU32(sizeof(AddrT));
        os << MxU32(sizeof(DataT));
        os << size;
        os.writeRawBytes((const char *)memData, size * sizeof(DataT));

        // done
        return true;
    }

    bool restore(MxIDataStream &is)
    {
        clear();

        MxU32 version = 0;
        MxU32 sizeof_AddrT = 0;
        MxU32 sizeof_DataT = 0;

        is >> version;
        is >> sizeof_AddrT;
        is >> sizeof_DataT;

        if((version != SAVERESTORE_VERSION) ||
           (sizeof_AddrT != sizeof(AddrT)) ||
           (sizeof_DataT != sizeof(DataT)))
            return false;
        
        is >> size;

        is.readRawBytes((char *)memData, size * sizeof(DataT));

        // done
        return true;
    }

    DataT* getAddress()
    {
        return memData;
    }
};

// MxU8 memory ======================================================================================================================================================

template<> inline MxStatus MCNonPagedMemory32<MxU8, true>::read8(AddrT addr, MxU8 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    data = memData[addr];
    return MX_STATUS_OK;
}


template<> inline MxStatus MCNonPagedMemory32<MxU8, false>::read8(AddrT addr, MxU8 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    data = memData[addr];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU8, true>::write8(AddrT addr, MxU8 data)
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    memData[addr] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU8, false>::write8(AddrT addr, MxU8 data)
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    memData[addr] = data;
    return MX_STATUS_OK;   
}

// read16/write16

template<> inline MxStatus MCNonPagedMemory32<MxU8, true>::read16(AddrT addr, MxU16 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    data = memData[addr] | (memData[addr + 1] << 8);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU8, false>::read16(AddrT addr, MxU16 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    data = (memData[addr] << 8) | memData[addr + 1];
    return MX_STATUS_OK;
}


template<> inline MxStatus MCNonPagedMemory32<MxU8, true>::write16(AddrT addr, MxU16 data)
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    memData[addr] = (MxU8)data;
    memData[addr+1] = data >> 8;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU8, false>::write16(AddrT addr, MxU16 data)
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    memData[addr] = data >> 8;
    memData[addr+1] = (MxU8)data;

    return MX_STATUS_OK;   
}

// read32/write32

template<> inline MxStatus MCNonPagedMemory32<MxU8, true>::read32(AddrT addr, MxU32 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 4);

    data = 
        memData[addr] | 
        (memData[addr + 1] << 8) | 
        (memData[addr + 2] << 16) | 
        (memData[addr + 3] << 24);

    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU8, false>::read32(AddrT addr, MxU32 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 4);

    data = 
        (memData[addr] << 24) | 
        (memData[addr + 1] << 16) | 
        (memData[addr + 2] << 8) | 
        memData[addr + 3];
    
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU8, true>::write32(AddrT addr, MxU32 data)
{
    CHECK_MEMORY_SIZE(size, addr, 4);

    memData[addr] = data;
    memData[addr + 1] = data >> 8;
    memData[addr + 2] = data >> 16;
    memData[addr + 3] = data >> 24;

    return MX_STATUS_OK;   
}


template<> inline MxStatus MCNonPagedMemory32<MxU8, false>::write32(AddrT addr, MxU32 data)
{
    CHECK_MEMORY_SIZE(size, addr, 4);

    memData[addr] = data >> 24;
    memData[addr + 1] = data >> 16;
    memData[addr + 2] = data >> 8;
    memData[addr + 3] = data;

    return MX_STATUS_OK;   
}


// read64/write64
template<> inline MxStatus MCNonPagedMemory32<MxU8, true>::read64(AddrT addr, MxU64 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 8);

    data = 
        memData[addr] | 
        (MxU32(memData[addr + 1]) << 8) | 
        (MxU32(memData[addr + 2]) << 16) | 
        (MxU32(memData[addr + 3]) << 24) |
        (MxU64(memData[addr + 4]) << 32) | 
        (MxU64(memData[addr + 5]) << 40) | 
        (MxU64(memData[addr + 6]) << 48) |
        (MxU64(memData[addr + 7]) << 56);

    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU8, false>::read64(AddrT addr, MxU64 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 8);

    data = 
        (MxU64(memData[addr]) << 56) | 
        (MxU64(memData[addr + 1]) << 48) | 
        (MxU64(memData[addr + 2]) << 40) | 
        (MxU64(memData[addr + 3]) << 32) | 
        (MxU32(memData[addr + 4]) << 24) | 
        (MxU32(memData[addr + 5]) << 16) | 
        (MxU32(memData[addr + 6]) << 8) | 
        memData[addr + 7];
    
    return MX_STATUS_OK;

}

template<> inline MxStatus MCNonPagedMemory32<MxU8, true>::write64(AddrT addr, MxU64 data)
{
    CHECK_MEMORY_SIZE(size, addr, 8);

    memData[addr] = (MxU8)data;
    memData[addr + 1] = data >> 8;
    memData[addr + 2] = data >> 16;
    memData[addr + 3] = data >> 24;
    memData[addr + 4] = data >> 32;
    memData[addr + 5] = data >> 40;
    memData[addr + 6] = data >> 48;
    memData[addr + 7] = data >> 56;

    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU8, false>::write64(AddrT addr, MxU64 data)
{
    CHECK_MEMORY_SIZE(size, addr, 8);

    memData[addr] = data >> 56;
    memData[addr + 1] = data >> 48;
    memData[addr + 2] = data >> 40;
    memData[addr + 3] = data >> 32;
    memData[addr + 4] = data >> 24;
    memData[addr + 5] = data >> 16;
    memData[addr + 6] = data >> 8;
    memData[addr + 7] = (MxU8)data;

    return MX_STATUS_OK;   
}


// MxU16 memory ======================================================================================================================================================

template<> inline MxStatus MCNonPagedMemory32<MxU16, true>::read16(AddrT addr, MxU16 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    data = memData[addr];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU16, false>::read16(AddrT addr, MxU16 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    data = memData[addr];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU16, true>::write16(AddrT addr, MxU16 data)
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    memData[addr] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU16, false>::write16(AddrT addr, MxU16 data)
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    memData[addr] = data;
    return MX_STATUS_OK;   
}

// read32/write32
template<> inline MxStatus MCNonPagedMemory32<MxU16, true>::read32(AddrT addr, MxU32 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    data = memData[addr] | (memData[addr + 1] << 16);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU16, false>::read32(AddrT addr, MxU32 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    data = (memData[addr] << 16) | memData[addr + 1];
    return MX_STATUS_OK;
}


template<> inline MxStatus MCNonPagedMemory32<MxU16, true>::write32(AddrT addr, MxU32 data)
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    memData[addr] = data;
    memData[addr+1] = data >> 16;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU16, false>::write32(AddrT addr, MxU32 data)
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    memData[addr] = data >> 16;
    memData[addr+1] = data;
    return MX_STATUS_OK;   
}

// read64/write64
template<> inline MxStatus MCNonPagedMemory32<MxU16, true>::read64(AddrT addr, MxU64 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 4);

    data = 
        memData[addr] | 
        (MxU32(memData[addr + 1]) << 16) | 
        (MxU64(memData[addr + 2]) << 32) | 
        (MxU64(memData[addr + 3]) << 48);

    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU16, false>::read64(AddrT addr, MxU64 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 4);

    data = 
        (MxU64(memData[addr]) << 48) | 
        (MxU64(memData[addr + 1]) << 32) | 
        (MxU32(memData[addr + 2]) << 16) | 
        memData[addr + 3];
    
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU16, true>::write64(AddrT addr, MxU64 data)
{
    CHECK_MEMORY_SIZE(size, addr, 4);

    memData[addr] = data;
    memData[addr + 1] = data >> 16;
    memData[addr + 2] = data >> 32;
    memData[addr + 3] = data >> 48;

    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU16, false>::write64(AddrT addr, MxU64 data)
{
    CHECK_MEMORY_SIZE(size, addr, 4);

    memData[addr] = data >> 48;
    memData[addr + 1] = data >> 32;
    memData[addr + 2] = data >> 16;
    memData[addr + 3] = data;

    return MX_STATUS_OK;   
}


// MxU32 memory ======================================================================================================================================================

template<> inline MxStatus MCNonPagedMemory32<MxU32, true>::read32(AddrT addr, MxU32 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    data = memData[addr];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU32, false>::read32(AddrT addr, MxU32 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    data = memData[addr];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU32, true>::write32(AddrT addr, MxU32 data)
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    memData[addr] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU32, false>::write32(AddrT addr, MxU32 data)
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    memData[addr] = data;
    return MX_STATUS_OK;   
}


// read64/write64
template<> inline MxStatus MCNonPagedMemory32<MxU32, true>::read64(AddrT addr, MxU64 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    data = memData[addr] | (MxU64(memData[addr + 1]) << 32);
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU32, false>::read64(AddrT addr, MxU64 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    data = (MxU64(memData[addr]) << 32) | memData[addr + 1];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU32, true>::write64(AddrT addr, MxU64 data)
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    memData[addr] = data;
    memData[addr+1] = data >> 32;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU32, false>::write64(AddrT addr, MxU64 data)
{
    CHECK_MEMORY_SIZE(size, addr, 2);

    memData[addr] = data >> 32;
    memData[addr+1] = data;
    return MX_STATUS_OK;   
}

// MxU64 memory ======================================================================================================================================================
template<> inline MxStatus MCNonPagedMemory32<MxU64, true>::read64(AddrT addr, MxU64 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    data = memData[addr];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU64, false>::read64(AddrT addr, MxU64 &data) const
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    data = memData[addr];
    return MX_STATUS_OK;
}

template<> inline MxStatus MCNonPagedMemory32<MxU64, true>::write64(AddrT addr, MxU64 data)
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    memData[addr] = data;
    return MX_STATUS_OK;   
}

template<> inline MxStatus MCNonPagedMemory32<MxU64, false>::write64(AddrT addr, MxU64 data)
{
    CHECK_MEMORY_SIZE(size, addr, 1);

    memData[addr] = data;
    return MX_STATUS_OK;   
}

#endif // _MCNonPagedMemory_h_
