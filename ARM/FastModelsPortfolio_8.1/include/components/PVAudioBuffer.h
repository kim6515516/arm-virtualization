/*!
 *  \file   PVAudioBuffer.h
 *  \brief  Audio Buffer Interface
 *  \date   Copyright ARM Limited 2007-2008 All Rights Reserved.
 *  
 *  This defines the interface to an Audio Buffer which is implemented by a
 *  Host Audio Interface
 */

#ifndef INCLUDED_PVAUDIOBUFFER_H
#define INCLUDED_PVAUDIOBUFFER_H

/* External includes */
#include "sg/SGstdint.h"
#include "stddef.h"
#include "stdlib.h"

/*! An AudioBuffer simulates a buffer of a fixed size draining at a constant
 * rate in simulated time.
 *
 * The format of the audio is fixed at Strereo 16 bit Little Endian PCM and the
 * sample rate is fixed at 48KHz.
 * 
 */
class PVAudioBuffer
{
public:

    // a sample is two 16 bit values (left + right)
    typedef uint32_t sample_t;

    virtual ~PVAudioBuffer()
    {
    }

    /*! Start the buffer draining. Particular implementations may have
     * other effects such as starting host playback or opening a file to write
     * data into.
     */
    virtual void    start() = 0;
    
    /*! Stop the buffer draining. Particularl implementations may have other
     * effects such as ending host playback or closing a data file.
     */
    virtual void    stop()   = 0;

    /*! Get the level of the buffer in stereo samples.
     *
     * \param   sim_ms  The number of elapse simulated milliseconds since the
     *                  last time getLevel was called. This parameter is
     *                  ignored if the buffer is not running.
     */
    virtual uint32_t    getLevel(uint32_t sim_ms) = 0;
    
    /*! Resets the buffer without changing its depth
     */
    virtual void reset() = 0;

    /*! Changes the buffer's depth
     *  
     *  \remark This may cause reallocation of the buffer if depth is significantly
     *  larger than the original depth set.
     *
     *  \param  depth Depth to reset
     */
    virtual void changeDepth(size_t depth) = 0;

    /*! Write a stereo sample into the buffer
     */
    inline void write(uint16_t left,uint16_t right)
    {
        bufBase[wp] = ((uint32_t)right << 16) |
                      (uint32_t)left;
        
        if(++wp == actualDepth)
            wp = 0;
    }
        
protected:
    /*! Allocates a buffer.
     * 
     * \param   depth Depth of buffer in stereo samples
     */
    PVAudioBuffer(size_t depth)  :
        bufBase(NULL),
        sdepth(depth)
    {
    }
public:    
    /*! Base of allocated buffer */
    sample_t*   bufBase;
    /*! Actual Read Position */
    size_t      rp;
    /*! Simulated Read Position */
    size_t      srp;
    /*! Write Pointer */
    size_t      wp;
    /*! Actual depth of the buffer */
    size_t      actualDepth;
    /*! The current depth of the simulated buffer */
    size_t      sdepth;
};



#endif

/* eof PVAudioBuffer.h */
