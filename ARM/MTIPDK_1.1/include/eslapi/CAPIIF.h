// ===========================================================================
// Description : CAPIIF interface declaration.
//
// Author      : ARM
// Date        : July 17th 2006
// File Name   : CAPIIF.h
// Release     : 2.0.000
//
// Copyright (c) 2006-2008 ARM. All rights reserved.
//
// ============================================================================

#ifndef _CAPIIF_H_
#define _CAPIIF_H_

#include "CAInterface.h" 
#include "CASIGlobal.h" 
#include "CAPITypes.h" 


namespace eslapi {

    class CASIModuleIF; 

    /// Cycle Accurate Profiling Interface.

    /// Mantains a set of profiling streams and the associated metadata.
    /// <br>Profiling events are collected in the streams by the component.
    /// <br>Profiling stream metadata is exposed through CAPIStreamInfo_t structs.
    /// <br>Profiling stream data is exposet through CAPIStream_t structs.
    class WEXP CAPIIF: public CAInterface{
    public:

        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CAPI2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

    
        /// @name Metadata Related Functions
        //@{
        /// @docinclude CAPIChannelType_t
        /// @docinclude CAPIColor_e
        /// @docinclude CAPISymbolValue_t
        /// @docinclude CAPIChannelSymbolInfo_t
        /// @docinclude CAPIChannelInfo_t
        /// @docinclude CAPIStreamInfo_t
        /// @docinclude CAPIReturn_t
    
        /// @brief Returns the metatdata associated with the profiling streams.
        ///
        /// Each CAPI objects will define the structure of its streams by providing an appropriate implementation.
        /// Example usage:
        /// <code>
        /// <br>uint32_t nrStreams
        /// <br>CAPIStreamInfo_t streamsInfo [100];
        /// <br>capi->CAPIGetProfilingStreams (100, & nrStreams, streamsInfo);
        /// </code>
        /// @param desiredNrStreams IN. Size of the <code>streams</code> array. Call
        ///   with a relatively large number to retrieve all the streams meta-data
        /// @param actualNrStreams  OUT. Number of streams defined in the component
        /// @param streamsInfo OUT. Metadata for the first <code>desiredNrStreams</code>
        ///   defined by the CAPI object
        /// @param streamIndex IN. The index into the stream array starting from which the streams should be returned 
        virtual CAPIReturn_t CAPIGetProfilingStreams (uint32_t desiredNrStreams, uint32_t * actualNrStreams, CAPIStreamInfo_t * streamsInfo, int streamIndex) = 0;
    
        //@}
    
        /// @name Data Related Functions
        //@{
        /// @docinclude CAPITraceSegment_t
        /// @docinclude CAPIStream_t
    
        /// Returns the profiling stream associated with <code>name</code>.
    
        /// <code>name</code> will match the value in <code> stream->info->streamName</code>
        /// @param name IN. Name of the stream
        virtual CAPIStream_t * CAPIFindStream (const char * name) = 0; 

        /// Returns the number of streams in this interface 
        virtual uint32_t CAPIGetNumStreams(void) = 0; 

        /// Returns the stream with a given index 
        /// @param[in] index  The index of the stream to be returned (index between 0 and CAPIGetNumStreams() - 1). 
        virtual const CAPIStream_t * CAPIGetStream(uint32_t index) = 0; 


        //@}

        /// Returns the target (the module that this CAPI interface belongs to) 
        virtual CASIModuleIF* CAPIGetTarget() = 0; 
    };

} //namespace 

#endif 


