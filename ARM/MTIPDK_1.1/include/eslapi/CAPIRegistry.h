// ===========================================================================
// Description : CAPIRegistry interface declaration.
//
// Author      : ARM
// Date        : July 17th 2006
// File Name   : CAPIRegistry.h
// Release     : 2.0.000
//
// Copyright (c) 2006-2008 ARM. All rights reserved.
//
// ============================================================================

#ifndef _CAPIREGISTRY_H_
#define _CAPIREGISTRY_H_

#include "CAInterface.h" 
#include <vector>

namespace eslapi{

    class CAPI; 
    struct CAPITraceSegment_t; 
    class CAPIStream_t; 

    /// @brief Interaction with the simulation kernel.
    ///
    /// The CAPICallbackIF estabilishes a basic relation between CAPI and the simulation kernel.
    /// There exists a single unique CAPICallback which applies to all CAPI objects.
    class WEXP CAPICallbackIF: public CAInterface{
    public:

        /// @brief Allocates a trace segment.
        ///
        /// Profiling data may grow very large for long simulation.
        /// By setting an appropriate memory manager the CAPI client has full control
        /// on how much of the profile data should reside in memory at a given time
        /// <p> Note: a profiling stream must have an active CAPITraceSegment_t at all times.
        /// <p>The size of the trace should be:
        /// <p>><code>(stream->eventWidthInBytes * stream->eventsTraceSegmentSize</code>
        ///
        /// @param stream IN. The stream that will use this segment.
        virtual CAPITraceSegment_t * allocateTraceSegment (const CAPIStream_t * stream) = 0;

        /// @brief De-allocates a trace segment, accounting for the memory usage 
        virtual void deallocateTraceSegment (const CAPIStream_t * stream, CAPITraceSegment_t * segment) = 0;
    
        /// @brief Retrieves the current simulation cycle.
        ///
        /// A "cycle" represents the moment in time a profiled event is recorded.
        /// The user may define its custom cycle/timing definition by providing
        /// an appropiate implementation for this callback.
        virtual uint64_t getCurrentCycle () = 0;

        /// @brief Return the total memory allocated by this memory manager (total current memory usage in number of bytes) 
        virtual uint64_t getTotalAllocatedMemory(void) = 0; 
    };


    /// @brief Interaction with the simulation kernel.
    ///
    /// The CAPICallback estabilishes a basic relation between CAPI and the simulation kernel.
    /// There exists a single unique CAPICallback which applies to all CAPI objects.
    class WEXP CAPICallback: public CAPICallbackIF{
    public:

        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CAPICallback2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

    
        virtual CAPITraceSegment_t * allocateTraceSegment (const CAPIStream_t * /*stream*/){return NULL;}

        virtual void deallocateTraceSegment (const CAPIStream_t * /*stream*/, CAPITraceSegment_t * /*segment*/){}
    
        virtual uint64_t getCurrentCycle (){return (uint64_t)-1;}

        virtual uint64_t getTotalAllocatedMemory(void) {return 0;}

        /// @name Versioning base implementation 
        //@{

        /// Return interface if requested 
        virtual CAInterface * ObtainInterface(
            if_name_t    ifName,
            if_rev_t     minRev,
            if_rev_t *   actualRev)
            {
                if((strcmp(ifName,"eslapi.CAPICallback2") == 0) && (minRev <= 0)){
                    *actualRev = 0; 
                    return this; 
                }
                return NULL; 
            }
        //@} 
    };



    class WEXP CAPIRegistry: public CAInterface{
    public: 
        CAPIRegistry();

        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CAPIRegistry2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        /// Registers a CAPI interface with the default CAPI implementation.
        /// During registration, the approrpiate streams are created according to the CAPIGetProfilingStreams definition.
        /// A model should register its CAPI object during construction.
        void CAPIRegisterInterface (CAPI * capi);

        /// Unregisters a CAPI interface. 
        void CAPIUnregisterInterface (CAPI *capi); 

        //Call this to get the MxPI interface for a component
        CAPI * CAPIFindInterface(char * comp_name);

        uint32_t CAPIGetNumInterfaces(void);

        CAPI * CAPIGetInterface(uint32_t index);

        /// Reset the CAPI information 
        void reset(void); 

        /// Remove all CAPI information 
        void clear(void); 

        /// @name Memory Management Functions
        //@{

        /// Sets a new global profiling stream data memory manager

        ///
        /// @param memoryManager IN. Memory manager object
        void setCAPICallback (CAPICallback * _callback) { callback = _callback; }

        /// Returns the current global profiling stream data memory manager

        inline CAPICallback * getCAPICallback () { return callback; }

        /// @brief Returns the static capiRegistry object 
        inline static CAPIRegistry * getCAPIRegistry(void){
            if(capiRegistry == NULL) capiRegistry = new CAPIRegistry(); 
            return capiRegistry;
        }

        /// @name Versioning base implementation 
        //@{

        /// Return interface if requested 
        virtual CAInterface * ObtainInterface(
            if_name_t    ifName,
            if_rev_t     minRev,
            if_rev_t *   actualRev);

        //@} 

    protected: 
        static CAPIRegistry * capiRegistry; 
        CAPICallback * callback;
        std::vector<CAPI*> interfaces;
    }; 
}


#endif 
