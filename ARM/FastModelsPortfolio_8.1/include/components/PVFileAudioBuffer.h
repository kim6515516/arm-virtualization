/*!
 *  \file   PVFileAudioBuffer.h
 *  \brief  File Based Audio Buffer
 *  \date   Copyright ARM Limited 2007-2008 All Rights Reserved.
 *  
 *  File based implementation of a PVAudioBuffer
 */

#ifndef INCLUDED_PVFILEAUDIOBUFFER_H
#define INCLUDED_PVFILEAUDIOBUFFER_H

#include "components/PVAudioBuffer.h"
#include <stdio.h>
#include <string>

class PVFileAudioBuffer : public PVAudioBuffer
{
public:
    PVFileAudioBuffer(size_t depth,std::string const & fname) :
        PVAudioBuffer(depth),
        fhandle(NULL),
        fOK(false),
        running(false)
    {
        // The actual depth must be bigger than the simulated depth so that
        // sizing of the FIFO works.
        actualDepth = 2*sdepth;

        bufBase = new uint32_t[actualDepth];
        rp      = 0;
        srp     = 0;
        wp      = 0;
        
        if (fname != "") {
            fhandle = fopen(fname.c_str(),"wb");
            if(fhandle != NULL)
            {
                fOK = true;
            }
        }        
    }

    ~PVFileAudioBuffer()
    {
        if(fhandle != NULL)
        {
            fclose(fhandle);
        }
        if(bufBase != NULL)
        {
            delete[] bufBase;
        }
    }

    inline void start() { running = true; }
    inline void stop() { running = false; }
    
    inline uint32_t getLevel(uint32_t sim_ms)
    { 
        size_t fifoLevel = 0;
       
        // Calculate the FIFO level
        if( srp <= wp )
        {
            fifoLevel = wp - srp;
        }
        else
        {
            fifoLevel = actualDepth - (srp - wp);
        }

        // We only drain the FIFO if we are running and the FIFO is not empty
        if(running && (srp != wp))
        {
            size_t samplesToDrain = 48*sim_ms;

            // We can't drain more samples than are actually currently in the
            // buffer.
            if(samplesToDrain > fifoLevel)
            {
                samplesToDrain = fifoLevel;
            }
            
            // Calculate the new simulated read position
            size_t  newSrp = (srp + samplesToDrain) % actualDepth;
            
            if(fOK)
            {
                // We only write to the file if it exists.
                // Write the data between the current srp and the newSrp
                // accounting for wrap round.
                
                if(srp < newSrp)
                {
                    fwrite(&(bufBase[srp]),4,newSrp - srp,fhandle);
                }
                else
                {
                    fwrite(&(bufBase[srp]),4,actualDepth - srp,fhandle);
                    fwrite(&(bufBase[0]),4,newSrp,fhandle);
                }
                
            }
            // However we need to drain the fifo anyway
            srp = newSrp;
        }
        
        return fifoLevel;
    }
    
    inline void reset()
    {
        rp      = 0;
        srp     = 0;
        wp      = 0;
    }

    inline void changeDepth(size_t depth)
    {
        if(bufBase != NULL)
        {
            delete[] bufBase;
            bufBase = NULL;
        }
       
        sdepth = depth;
        actualDepth = 2*sdepth;

        bufBase = new uint32_t[actualDepth];
        rp      = 0;
        srp     = 0;
        wp      = 0;
    }

private:
    FILE*               fhandle;
    bool                fOK;
    bool                running;
};

#endif

/* eof PVFileAudioBuffer.h */
