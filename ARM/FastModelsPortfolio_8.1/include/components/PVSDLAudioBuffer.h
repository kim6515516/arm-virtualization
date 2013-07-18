/*!
 *  \file   PVSDLAudioBuffer.h
 *  \brief  SDL Based Audio Buffer 
 *  \date   Copyright ARM Limited 2007-2008 All Rights Reserved.
 *  
 *  SDL based implementation of a PVAudioBuffer
 */

#ifndef INCLUDED_PVSDLAUDIOBUFFER_H
#define INCLUDED_PVSDLAUDIOBUFFER_H

#include "components/PVAudioBuffer.h"
#include "TxLib/TxLib.h"
#include <string>
#include <list>
#include <stdlib.h>
#include <string.h>

struct SDLDllFunctions;
struct SDL_AudioSpec;
class AudioSink;

class PVSdlAudioBuffer : public PVAudioBuffer
{
    SDLDllFunctions *sdl;

public:
    PVSdlAudioBuffer(size_t depth);
    ~PVSdlAudioBuffer();

    void start();
    void stop();
    uint32_t getLevel(uint32_t sim_ms);
    void reset();
    void changeDepth(size_t depth);
    
    bool                m_running;

    TxMutex             m_state_lock;

    void fillBuffer(uint8_t* stream, int len);

private:
    /*! Initialise or re-initialise SDL
     *
     * \param   driver  sound driver to use
     */
    void startSDL(std::string const & driver, SDL_AudioSpec *wanted);
    void updateDrained();
   
    bool        m_sdlOK;
    bool        m_soundOK;
    bool        m_started;
    std::string             m_curDriver;
    std::list<std::string>  m_driverList;

    // Used when we have no SDL output and just want to sink the
    // audio data somewhere silently.
    AudioSink *audiosink;

    // my stuff
    uint64_t            m_ticks_per_ms; // system ticks per ms
    uint64_t            m_fill_ticks;   // time of last buffer fill
    uint64_t            m_dr_ms;        // drain rate in samples/ms
    size_t              m_drained;      // samples drained since the last rp movement
    bool                m_filling;      // we're filling up the jitter buffer
    size_t              m_jitter;       // extra samples for jitter
};

#endif

/* eof PVSDLAudioBuffer.h */
