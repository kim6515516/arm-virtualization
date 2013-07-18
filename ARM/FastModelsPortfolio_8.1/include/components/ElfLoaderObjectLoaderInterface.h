/*
 * Copyright 2010 ARM Limited. All rights reserved.
 */

// ELF loader component for validation systems
// Load an elf file and apply transformations,
// e.g. duplicate accesses in SECURE and NON_SECURE memory spaces

#ifndef VALIDATIONOBJECTLOADERINTERFACE_H
#define VALIDATIONOBJECTLOADERINTERFACE_H

#include "ObjectLoader.h"
#include "FileInterface.h"

#include <pv/PVBus.h>
#include <pv/PVBusMaster.h>
#include <pv/PVAccessWidth.h>
#include <pv/PVMemoryAttributes.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>

#include <list>
#include <algorithm>

#include "zlib/zlib.h"


class GzFileInterface: public FileInterface
{
public:
    GzFileInterface(const char* filename)
        : FileInterface(filename)
    {
        FILE *stream = ::fopen (filename, "rb");
        if (stream == NULL)
            throw "no such file";
        unsigned char magic[2];
        size_t n = ::fread(magic, 1, 2, stream);
        if (n != 2)
            throw "could not read file header";
        ::fclose (stream);
        
        if (magic[0] != 0x1f || magic[1] != 0x8b)
            throw "incorrect magic number for gzip file";
        
        gzFile file = gzopen (filename, "rb");
        if (file == NULL)
            throw "cannot open gzip file";
        malloc_size = 16384;
        data_size = 0;
        uncompressed_data = (char*) malloc(malloc_size);
        while  (!gzeof(file))
        {
            if (data_size >= malloc_size)
            {
                malloc_size *= 2;
                uncompressed_data = (char*)realloc((void*)uncompressed_data, malloc_size);
            }
            data_size += gzread(file, &(uncompressed_data)[data_size], (unsigned)(malloc_size - data_size));
        }

        gzclose (file);
        return;
    }

    virtual ~GzFileInterface()
    {
        free(uncompressed_data);
    }

    virtual int fseek(long offset, int whence)
    {
        if (whence == SEEK_SET)
            pointer = offset;
        else if (whence == SEEK_CUR)
            pointer += offset;
        else if (whence == SEEK_END)
            pointer = data_size + offset;
        return 0;
    }

    virtual long ftell()
    {
        return (long) pointer;
    }

    virtual int feof()
    {
        return (pointer >= data_size);
    }

    virtual size_t read(void *ptr, size_t count)
    {
        if (pointer >= data_size)
            return 0;
        if ((size_t)(data_size - pointer) < count)
            count = data_size - pointer;
        memcpy (ptr, &uncompressed_data[pointer], count);
        pointer += count;
        return count;
    }

private:
    char* uncompressed_data;
    size_t data_size;
    size_t malloc_size;
    size_t pointer;
};



struct section_desc
{
    std::string id;
    uint64_t    ipa;
    uint64_t    pa;
    uint64_t    offset;
    uint64_t    size;
    bool        ns;


};

static bool operator<(const section_desc& x, const section_desc& y)
{
    return x.ipa < y.ipa;
}



class ElfLoaderObjectLoaderInterface: public ObjectLoaderInterface
{
    pv::TransactionGenerator* tx_gen;
    bool ns_copy;

    std::list<section_desc> section_list;

    uint64_t start_address;

public:
    bool use_lfile(const std::string lfile) {

        section_list.clear();

        if (lfile.empty())
        {
            return false;
        }

        bool found_start = false;
        bool found_end = false;
        
        std::ifstream inf(lfile.c_str());
        if (!inf.good())
        {
            std::cerr << "File not found: " << lfile << std::endl;
            return true;
        }

        std::string line;
        while (inf.good() && !inf.eof())
        {
            getline(inf, line);
            

            if (!found_start)
            {
                if ( 0 == line.compare("** ELF_SECTION_RELOC_START **"))
                {
                    found_start = true;
                }
            }
            else
            {
                if ( 0 == line.compare("** ELF_SECTION_RELOC_END **"))
                {
                    found_end = true;
                    break;
                }
                
                // remove comments following #
                size_t endpos = line.find('#');
                if (endpos != std::string::npos)
                {
                    line.resize(endpos);
                }
                            
                section_desc section;

                std::stringstream is(line, stringstream::in);
                is.clear();

                getline( is, section.id, ',');
                if (is.eof())
                {
                    // empty lines are allowed
                    continue;
                }
            

                char limiter;
                is >> std::skipws >> std::showbase >> std::hex >> section.ipa >> std::skipws >> limiter;
                if (is.fail() || is.eof() || (limiter!=','))
                {
                    std::cerr << lfile << ": ipa field parse error in line " << line << std::endl;    
                    std::cerr << section.id << is.fail() << is.eof() << limiter << std::endl;
                    break;
                }

                is >> std::skipws >> std::showbase >> std::hex >> section.pa >> std::skipws >> limiter;
                if (is.fail() || is.eof() || (limiter!=','))
                {
                    std::cerr << lfile << ": pa field parse error in line " << line << std::endl;        
                    break;
                }

                is >> std::skipws >> std::showbase >> std::hex >> section.offset >> std::skipws >> limiter;
                if (is.fail() || is.eof() || (limiter!=','))
                {
                    std::cerr << lfile << ": offset field parse error in line " << line << std::endl;        
                    break;
                }

                is >> std::skipws >> std::showbase >> std::hex >> section.size >> std::skipws >> limiter;
                if (is.fail() || is.eof() || (limiter!=','))
                {
                    std::cerr << lfile << ": size field parse error in line " << line << std::endl;        
                    break;
                }

                section.ns = false;
                is >> std::skipws >> limiter;
                if (limiter == 'N')
                {
                    section.ns = true;
                    is >> limiter;
                }

                if (limiter != 'S')
                {
                    std::cerr << lfile << ": security field parse error in line " << line << std::endl;        
                    break;
                }

                section_list.push_back(section);
            
            }
        
        }
        
        if (! found_end)
        {
            std::cerr << lfile << ": Relocation load file parse error" << std::endl;    
            if (!inf.good()) std::cerr << "File not good" << std::endl;
            else if (inf.eof()) std::cerr << "End of file" << std::endl;
            else if (inf.fail()) std::cerr << "getline failed" << std::endl;
            return true;
        }
        
        section_list.sort();

        return false;        
    }




    // we put data packets into memory
    virtual void putPacket(MxU32 memorySpaceId, ObjectLoaderAddress address , const MxU8* packet, MxU32  mauBytes , MxU32  flags , MxU32  type )
    {
//        printf("MyObjectLoaderInterface::putPacket(memorySpaceId=%d, address=0x%08x_%08x, packet[]={%s}, mauBytes=%d, flags=%08X, type=%08X);\n",
//               memorySpaceId, (uint32_t)(address >> 32), (uint32_t)(address), ObjectLoader::hexDumpLine(packet, mauBytes).c_str(), mauBytes, flags, type);



        if (section_list.empty())
        {
            // default behaviour, no relocation. Load into S and NS memory if requested 
            writeToMemory( (pv::bus_addr_t )address, false, (const uint8_t *) packet, mauBytes );
            if (ns_copy)
            {
                writeToMemory( (pv::bus_addr_t )address, true, (const uint8_t *) packet, mauBytes );
            }
        }
        else
        {
            // mapping behaviour
        
            // don't expect a very large number of regions, so linear walk is unlikely to be problematic
            // don't stop after the first match, as there may be more than one (especially for NS and S regions)
            // list is sorted by IPA start, so we can stop walking if we find a region which starts after the end of this packet

            uint64_t unmatched_ipa_start = address;
            
            for (std::list<section_desc>::iterator iter = section_list.begin(); iter != section_list.end(); ++iter)
            {
                if (iter->ipa > (address + mauBytes))
                {
                    break;
                }
                else if ( (iter->ipa + iter->size) < address )
                {
                    continue;
                }
                
                // find the overlapping region and write to memory
                
                pv::bus_addr_t ipa_start = std::max(address, iter->ipa);
                pv::bus_addr_t ipa_end = std::min(address + mauBytes, iter->ipa + iter->size);
                                
                writeToMemory( iter->pa + (ipa_start - iter->ipa), iter->ns, (const uint8_t *) packet + (ipa_start - address), ipa_end - ipa_start );
                
                
                if (ipa_start > unmatched_ipa_start)
                {
                    std::cerr <<  "no loadfile match for elf region at IPA " << std::hex << std::showbase << unmatched_ipa_start << " size " << (ipa_start - unmatched_ipa_start) << std::endl;
                }
                unmatched_ipa_start = std::max(unmatched_ipa_start, ipa_end);
                
            }
            
            if (unmatched_ipa_start < (address + mauBytes))
            {
                std::cerr <<  "no loadfile match for elf region at IPA " << std::hex << std::showbase << unmatched_ipa_start << " size " << (address + mauBytes - unmatched_ipa_start) << std::endl;
            }
        }
    }

    virtual void writeToMemory(pv::bus_addr_t addr, bool ns, const MxU8* data, uint32_t  count)
    {
        tx_gen->setNonSecure(ns);
    
        bool ok = true;

        while ((addr & 0x7) && count)
        {
            ok &= tx_gen->write8(addr, (uint8_t *)data,true);
            addr++;
            data++;
            count--;
        }
        while (count > 7)
        {
            ok &= tx_gen->write64(addr, (uint64_t *)data,true);
            addr+=8;
            data+=8;
            count-=8;
        }
        while (count)
        {
            ok &= tx_gen->write8(addr, (uint8_t *)data,true);
            addr++;
            data++;
            count--;
        }

        if (!ok)
        {
            std::cerr <<  "elf loading error at PA 0x" << std::hex << addr << (ns?"_NS":"_S") << std::endl;
        }
    }

    // we currently ignore all symbols, entry points and source line information
    virtual void putSymbol(MxU32 /* memorySpaceId */, const char * /* symbolName */, ObjectLoaderAddress /* address */, ObjectLoaderAddress /* size */, MxU32 /* binding */, MxU32 /* type */) {}
    virtual void putProgramExecutionStartAddress(ObjectLoaderAddress address ) { start_address = address; }
    virtual void putSourceReference(MxU32 /* memorySpaceId */, ObjectLoaderAddress /* address */, const char * /* fileName */, int /* lineNumber */) {}


    ElfLoaderObjectLoaderInterface(pv::TransactionGenerator* tx_gen)
    :   tx_gen(tx_gen),
        ns_copy(false),
        start_address(0)
    {
        tx_gen->setNonSecure(false);
    }
    void set_ns_copy(bool s) {ns_copy = s;}

    uint64_t get_start_address() const { return start_address; }
};

#endif // VALIDATIONOBJECTLOADERINTERFACE_H
