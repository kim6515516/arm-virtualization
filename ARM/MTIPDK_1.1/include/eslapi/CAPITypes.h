// ===========================================================================
// Description : CAPI types declaration.
//
// Author      : ARM
// Date        : July 17th 2006
// File Name   : CAPITypes.h
// Release     : 2.0.000
//
// Copyright (c) 2006-2008 ARM. All rights reserved.
//
// ============================================================================

#ifndef CAPI_TYPES_H
#define CAPI_TYPES_H

#include "CASIGlobal.h"
#include "CAPIColors.h"
#include "CAPIRegistry.h" 
#include "CAPIGlobalContainer.h" 

#include <stdarg.h> 

#ifdef DEBUG
# include <assert.h>
#endif

namespace eslapi {

/// Default segment size for streams data 
#define CAPI_DEFAULT_SEGMENT_SIZE 1000

    // Forward declaration 
    class CAPI;

    /// Return values for CAPI functions
    enum CAPIReturn_t{
        CAPI_STATUS_OK,
        CAPI_STATUS_GeneralError,
        CAPI_STATUS_UnknownCommand,
        CAPI_STATUS_IllegalArgument,
        CAPI_STATUS_CmdNotSupported,
        CAPI_STATUS_ArgNotSupported,
        CAPI_STATUS_InsufficientResources
    };

    /// Possible types for the profiling channels

    /// The channel types BOOL/U8/U16/... represent boolean, unsigned byte, half-word, etc.
    /// types, as represented by the host machine.
    /// <br>The channel type CAPI_CHANNEL_TYPE_SYMBOL is stored in memory as a byte,
    /// and represents possible enumeration values, starting with 0.
    /// Each such enumeration value will have a symbol name and a color associated.
    /// The symbol channels are intended for symbol-based information gathering,
    /// such as the transaction types (read/write/burst/...), cache event (hit/miss), etc.
    enum CAPIChannelType_t{
        CAPI_CHANNEL_TYPE_BOOL, ///< bool
        CAPI_CHANNEL_TYPE_SYMBOL, ///< A symbol with values 0, 1, 2, ..., and strings associated with it in CAPIChannelSymbolInfo_t
        CAPI_CHANNEL_TYPE_U8, ///< unsigned char
        CAPI_CHANNEL_TYPE_U16, ///< unsigned short
        CAPI_CHANNEL_TYPE_U32, ///< unsigned int
        CAPI_CHANNEL_TYPE_U64, ///< unsigned long long
        CAPI_CHANNEL_TYPE_S8, ///< signed char
        CAPI_CHANNEL_TYPE_S16, ///< signed short
        CAPI_CHANNEL_TYPE_S32, ///< signed int
        CAPI_CHANNEL_TYPE_S64,  ///< signed long long
        CAPI_CHANNEL_TYPE_F32,  ///< floating point (32 bit) 
        CAPI_CHANNEL_TYPE_F64  ///< floating point double (64 bit)
    };


    /// UI hints for a value of a channel of type CAPI_CHANNEL_TYPE_SYMBOL

    /// Specifies the value names and colors associated with the values of a symbol, for channels of type CAPI_CHANNEL_TYPE_SYMBOL
    struct CAPISymbolValue_t{
        char *valueName;        ///< Human readable name of the value
        uint32_t valueColor;     /**< Color hint.
                                   The possible vales are described by the CAPIColor_e enumeration.
                                   The CAPIColor_e enumeration is not used directly for binary compatibility reasons. */
    };

    /// Values associated with a channel of type CAPI_CHANNEL_TYPE_SYMBOL

    struct CAPIChannelSymbolInfo_t{
        int nrSymbolValues; ///< The number of symbol values in the symbolStrings array of strings
        CAPISymbolValue_t *symbolValues; ///< The symbol values array, associtated with values (0, 1, 2, ...) for type CAPI_CHANNEL_TYPE_SYMBOL
    };

    enum CAPIChannelDisplayType_t{
        CAPI_CHANNEL_DISPLAY_TYPE_DECIMAL, 
        CAPI_CHANNEL_DISPLAY_TYPE_HEXADECIMAL
	};

    /// Metadata for a profiling channel.

    /// Each profiling stream may contain one or more such channels.
    /// Note: The count field is currently not used. For consistency set this value to 1.
    struct CAPIChannelInfo_t{
        char *channelName; ///< The channel name
        char * description; ///< The channel description
        CAPIChannelType_t type; ///< The type of the data elements for this channel
        int count; ///< Number of the data elements of type "type" for every event (by default it should be 1)

        /// For type CAPI_CHANNEL_TYPE_SYMBOL:
        CAPIChannelSymbolInfo_t * symbolInfo;

        CAPIChannelDisplayType_t infoType; ///< This information is used by the tools in order to display the channel in decimal or hexadecimal format. 
    };

    /// Metadata for a profiling stream.

    struct CAPIStreamInfo_t{
        char *streamName; ///< ID Name of the stream
        char *streamLabel; ///< Human readable name of the stream
        char * description; ///< Human readable description of the stream
        uint32_t nrOfChannels; ///< Number of channels
        CAPIChannelInfo_t **channels; ///< Metadata array for stream's channels
    };


    /// Node in the profile data list

    /// Each node stores eventsTraceSegmentSize events.
    /// For the last element in list, only nrOfEventsInLastSegment events will be stored.
    struct CAPITraceSegment_t{
        uint8_t *eventsTrace; ///< Profile data block
        CAPITraceSegment_t *next; ///< Next node in list
    };

    /// Collected profiling stream content

    /// The CAPIStream_t class manages/contains the actual stream data content
    /// and a poitner to the meta-data (CAPIStreamInfo_t).
    class WEXP CAPIStream_t: public CAInterface{
    public: 
        CAPIStream_t(CAPI * _owner,CAPIStreamInfo_t * _info, uint64_t _segmentSize = CAPI_DEFAULT_SEGMENT_SIZE); 

        inline static CAPIReturn_t recordEvent (CAPIStream_t *stream, ... ); 

        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CAPIStream_t2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        /// @name Versioning base implementation 
        //@{

        /// Return interface if requested 
        virtual CAInterface * ObtainInterface(
            if_name_t    ifName,
            if_rev_t     minRev,
            if_rev_t *   actualRev);
        //@} 


    public: 
        CAPIStreamInfo_t * info; ///< IMMUTABLE. The stream meta-data description
        CAPI *owner;             ///< IMMUTABLE. The CAPI object owning this stream
        bool enabled;            ///< USER_MODIFIABLE. If true, profile data will be collected

        /// IMMUTABLE. The sum of the widths of the channels in this stream
        uint64_t eventWidthInBytes;
        /// USER_MODIFIABLE. The number of events in the trace
        uint64_t nrOfEvents;
        /// USER_MODIFIABLE. The number of events in the last CAPITraceSegment_t segment
        uint64_t nrOfEventsInLastSegment;
        CAPITraceSegment_t *eventHead; ///< USER_MODIFIABLE. The profile data list head
        CAPITraceSegment_t *eventTail; ///< USER_MODIFIABLE. The profile data list tail
        /// USER_MODIFIABLE. The capacity of a CAPITraceSegment_t profile data list node
        uint64_t eventsTraceSegmentSize;

        /// USER_MODIFIABLE. Hook for custom model user data
        void * userData;

    public:
        inline void
            StartRecordEvent(void)
            {
                if(enabled)
                {
                    if(((uint32_t) nrOfEventsInLastSegment) >= ((uint32_t) eventsTraceSegmentSize)) {
                        eventTail->next = eslapi::CAPIRegistry::getCAPIRegistry()->getCAPICallback()->allocateTraceSegment (this);
                        eventTail = eventTail->next;
                        eventTail->next = NULL;
                        nrOfEventsInLastSegment = 0;
                    }
                    uint64_t currentCycle = eslapi::CAPIRegistry::getCAPIRegistry()->getCAPICallback()->getCurrentCycle();
                    CAPIGlobalContainer::byteOffsetRecordEvent = nrOfEventsInLastSegment * ((uint32_t) eventWidthInBytes);
                    *((uint64_t*)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) =  (uint64_t) currentCycle;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 8;
                    CAPIGlobalContainer::channelNumRecordEvent = 0;
                }
            }
        
        
        inline void
            RecordChannelBool(bool value)
            {
                if(enabled)
                {
                    *((bool*)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 1;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(CAPIGlobalContainer::channelNumRecordEvent <= info->nrOfChannels);
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_BOOL);
#endif
		}
            }

        
        
        inline void
            RecordChannelSymbol(int symbol)
            {
                if(enabled)
                {
                    *((uint8_t*)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = symbol;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 1;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(CAPIGlobalContainer::channelNumRecordEvent <= info->nrOfChannels);
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_SYMBOL);
#endif      
                }
            }
        
        
        inline void
            RecordChannelU8(uint8_t value)
            {
                if(enabled)
		{
                    *((uint8_t *)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 1;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_U8); 
#endif
		}
            }


        inline void
            RecordChannelS8(int8_t value)
            {
                if(enabled)
		{
                    *((int8_t *)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 1;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_S8); 
#endif
		}
            }


        inline void
            RecordChannelU16(uint16_t value)
            {
                if(enabled)
		{
                    *((uint16_t *)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 2;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_U16);
#endif
		}
            }


        inline void
            RecordChannelS16(int16_t value)
            {
                if(enabled)
		{
                    *((int16_t *)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 2;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_S16);
#endif
		}
            }


        inline void
            RecordChannelU32(uint32_t value)
            {
                if(enabled)
		{
                    *((uint32_t *)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 4;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_U32);
#endif
		}
            }


        inline void
            RecordChannelS32(int32_t value)
            {
                if(enabled)
		{
                    *((int32_t *)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 4;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_S32);
#endif
		}
            }


        inline void
            RecordChannelU64(uint64_t value)
            {
                if(enabled)
		{
                    *((uint64_t *)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 8;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_U64);
#endif
		}
            }


        inline void
            RecordChannelS64(int64_t value)
            {
                if(enabled)
		{
                    *((int64_t *)&(eventTail->eventsTrace[CAPIGlobalContainer::byteOffsetRecordEvent])) = value;
                    CAPIGlobalContainer::byteOffsetRecordEvent += 8;
#ifdef DEBUG
                    ++CAPIGlobalContainer::channelNumRecordEvent; // channel 0 is cycle, first recorded channel is 1
                    assert(info->channels[CAPIGlobalContainer::channelNumRecordEvent]->type == CAPI_CHANNEL_TYPE_S64);
#endif
		}
            }


	inline void
            EndRecordEvent(void)
            {
                if(enabled)
                {
                    nrOfEventsInLastSegment ++;
                    nrOfEvents ++;
#ifdef DEBUG
                    assert(CAPIGlobalContainer::channelNumRecordEvent == info->nrOfChannels); // all channels must be recorded
#endif
                }
            }

    }; //class CAPIStream_t


#ifndef _MXSI_EXPORT_LIBRARY_

//Macros for fast event recording:
#define CAPIRecordEvent1(stream,arg1) \
{\
  uint64_t currentCycle; \
  uint64_t offset=0,base=0;  \
  uint8_t temp8; \
  uint16_t temp16; \
  uint32_t temp32;  \
  uint64_t temp64; \
\
 if(stream->enabled){\
  if(((uint32_t) stream->nrOfEventsInLastSegment) >= ((uint32_t) stream->eventsTraceSegmentSize)) { \
	stream->eventTail->next = eslapi::CAPIRegistry::getCAPIRegistry()->getCAPICallback()->allocateTraceSegment (stream); \
    stream->eventTail = stream->eventTail->next; \
    stream->eventTail->next = NULL; \
    stream->nrOfEventsInLastSegment = 0; \
  } \
\
	currentCycle = eslapi::CAPIRegistry::getCAPIRegistry()->getCAPICallback()->getCurrentCycle(); \
\
  base = stream->nrOfEventsInLastSegment * ((uint32_t) stream->eventWidthInBytes); \
  offset = 0; \
\
  *((uint64_t*)&(stream->eventTail->eventsTrace[base + offset])) =  (uint64_t) currentCycle; \
  offset += 8; \
      \
  switch(stream->info->channels[1]->type){ \
  case eslapi::CAPI_CHANNEL_TYPE_U8: \
  case eslapi::CAPI_CHANNEL_TYPE_BOOL: \
  case eslapi::CAPI_CHANNEL_TYPE_SYMBOL: \
    temp8 = (uint8_t) arg1; \
    *((uint8_t*)&(stream->eventTail->eventsTrace[base + offset])) =  temp8; \
    offset += 1; \
    break;  \
  case eslapi::CAPI_CHANNEL_TYPE_U16: \
    temp16 = (uint16_t) arg1; \
    *((uint16_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp16; \
    offset += 2; \
    break; \
  case eslapi::CAPI_CHANNEL_TYPE_U32: \
    temp32 = (uint32_t) arg1; \
    *((uint32_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp32; \
    offset += 4; \
    break; \
  case eslapi::CAPI_CHANNEL_TYPE_U64: \
    temp64 = (uint64_t) arg1; \
    *((uint64_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp64; \
    offset += 8; \
    break; \
  default: \
    assert(0); \
  }\
  stream->nrOfEventsInLastSegment ++; \
  stream->nrOfEvents ++; \
 }\
}


//Macros for fast event recording:
#define CAPIRecordEvent2(stream,arg1,arg2) \
{\
  uint64_t currentCycle; \
  uint64_t offset=0,base=0;  \
  uint8_t temp8; \
  uint16_t temp16; \
  uint32_t temp32;  \
  uint64_t temp64; \
\
 if(stream->enabled){\
  if(((uint32_t) stream->nrOfEventsInLastSegment) >= ((uint32_t) stream->eventsTraceSegmentSize)) { \
    stream->eventTail->next = eslapi::CAPIRegistry::getCAPIRegistry()->getCAPICallback()->allocateTraceSegment (stream); \
    stream->eventTail = stream->eventTail->next; \
    stream->eventTail->next = NULL; \
    stream->nrOfEventsInLastSegment = 0; \
  } \
\
  currentCycle = eslapi::CAPIRegistry::getCAPIRegistry()->getCAPICallback()->getCurrentCycle(); \
\
  base = stream->nrOfEventsInLastSegment * ((uint32_t) stream->eventWidthInBytes); \
  offset = 0; \
\
  *((uint64_t*)&(stream->eventTail->eventsTrace[base + offset])) =  (uint64_t) currentCycle; \
  offset += 8; \
      \
  switch(stream->info->channels[1]->type){ \
  case eslapi::CAPI_CHANNEL_TYPE_U8: \
  case eslapi::CAPI_CHANNEL_TYPE_BOOL: \
  case eslapi::CAPI_CHANNEL_TYPE_SYMBOL: \
    temp8 = (uint8_t) arg1; \
    *((uint8_t*)&(stream->eventTail->eventsTrace[base + offset])) =  temp8; \
    offset += 1; \
    break;  \
  case eslapi::CAPI_CHANNEL_TYPE_U16: \
    temp16 = (uint16_t) arg1; \
    *((uint16_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp16; \
    offset += 2; \
    break; \
  case eslapi::CAPI_CHANNEL_TYPE_U32: \
    temp32 = (uint32_t) arg1; \
    *((uint32_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp32; \
    offset += 4; \
    break; \
  case eslapi::CAPI_CHANNEL_TYPE_U64: \
    temp64 = (uint64_t) arg1; \
    *((uint64_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp64; \
    offset += 8; \
    break; \
  default: \
    assert(0); \
  }\
      \
  switch(stream->info->channels[2]->type){ \
  case eslapi::CAPI_CHANNEL_TYPE_U8: \
  case eslapi::CAPI_CHANNEL_TYPE_BOOL: \
  case eslapi::CAPI_CHANNEL_TYPE_SYMBOL: \
    temp8 = (uint8_t) arg2; \
    *((uint8_t*)&(stream->eventTail->eventsTrace[base + offset])) =  temp8; \
    offset += 1; \
    break;  \
  case eslapi::CAPI_CHANNEL_TYPE_U16: \
    temp16 = (uint16_t) arg2; \
    *((uint16_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp16; \
    offset += 2; \
    break; \
  case eslapi::CAPI_CHANNEL_TYPE_U32: \
    temp32 = (uint32_t) arg2; \
    *((uint32_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp32; \
    offset += 4; \
    break; \
  case eslapi::CAPI_CHANNEL_TYPE_U64: \
    temp64 = (uint64_t) arg2; \
    *((uint64_t*)&(stream->eventTail->eventsTrace[base + offset])) = temp64; \
    offset += 8; \
    break; \
  default: \
    assert(0); \
  }\
  stream->nrOfEventsInLastSegment ++; \
  stream->nrOfEvents ++; \
 }\
}

#else
#define CAPIRecordEvent1(stream,arg1)
#define CAPIRecordEvent2(stream,arg1,arg2)
#endif


#define CAPIIsProfilingStreamEnabled(stream) stream->enabled

} //namespace 

#endif
