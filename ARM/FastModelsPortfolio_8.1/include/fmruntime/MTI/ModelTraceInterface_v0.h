/*!
 *  \file   ModelTraceInterface_v0.h
 *  \brief  The Model Trace Interface and helper classes, version 0.
 *  \date   Copyright ARM Limited 2008-2009 All Rights Reserved.
 *  
 *  Normally this header file should not be included directly. The
 *  ModelTraceInterface.h header should be included instead.
 */

#ifndef MTI_TRACEINTERFACE_V0_H
#define MTI_TRACEINTERFACE_V0_H

#include "eslapi/CAInterface.h"

#include <stddef.h> // size_t

namespace MTI
{
    namespace v0
    {

        class TraceSource;
        class EventFieldType;
        class EventClass;
        struct EventRecord;

        enum Status
        {
            MTI_OK,
            MTI_FUNCTION_NOT_SUPPORTED,  // this functions is completely unsupported in this model
            MTI_PARAMETER_NOT_SUPPORTED, // this parameter combination is not supported by the model
            MTI_PARAMETER_INVALID,       // for example an index is too large
            MTI_BUSY,                    // cannot complete call since model is busy (running?)
            MTI_ERROR                    // general errors that cannot be categorized explicitly
        };

        typedef uint16_t EventClassId;
        typedef int SourceIndex;
        typedef int FieldIndex; // 0 to 31
        typedef int ValueIndex; // 0 to 31

        // This type describes a set of fields of a trace record
        typedef uint32_t FieldMask;

        typedef void (* CallbackT)(void *user_data, const EventClass *, const EventRecord *);

        // A modifying callback returns a mask of the fields which it modified.
        typedef FieldMask (* ModifyingCallbackT)(void *user_data, const EventClass *, EventRecord *);

        class ModelTraceInterface :
            public eslapi::CAInterface
        {
        public:
            /// Static helper method to return the interface name for the 
            /// CAInterface.
            static eslapi::if_name_t IFNAME() { return "ModelModelTraceInterface"; }
        
            /// Static helper method to return the current interface revision 
            /// for CAInterface.
            static eslapi::if_rev_t IFREVISION() { return 0; }

        public: // methods
            virtual SourceIndex GetNumOfTraceSources() const = 0;

            virtual TraceSource *GetTraceSource(SourceIndex index) const = 0;
            virtual TraceSource *GetTraceSource(const char *name) const = 0;

            virtual const EventClass *GetEventClass(EventClassId event_class_id) const = 0;

        }; // ModelTraceInterface


        class EventFieldType
        {
        public: // types        
            enum Type
            {
                MTI_UNSIGNED_INT,
                MTI_SIGNED_INT,
                MTI_BOOL,
                MTI_ENUM,
                MTI_FLOAT,
                MTI_STRING
            };

            typedef uint16_t Size;

        protected:
            virtual ~EventFieldType() {} // not to be called by interface user
        public: // methods
            virtual const TraceSource *GetSource() const = 0;
            virtual FieldIndex GetIndex() const =0;
            virtual const char *GetName() const = 0;
            virtual const char *GetDescription() const = 0;
            virtual Type GetType() const = 0;
            virtual Size GetSize() const = 0;                
        }; // EventFieldType


        class TraceSource
        {
        protected: // methods
            virtual ~TraceSource() {} // must not be called by interface user
        public: // methods
            virtual SourceIndex GetIndex() const =0;
            virtual const char *GetName() const = 0;
            virtual const char *GetDescription() const = 0;
            virtual FieldIndex GetNumFields() const = 0;
        
            virtual const EventFieldType *GetField(FieldIndex index) const = 0;
            virtual const EventFieldType *GetField(const char *name) const = 0;
        
            virtual EventClass *
            CreateEventClass(FieldMask field_mask) const = 0;

            // Counters
            //////////////////////////////////////////////////
            virtual Status
            RegisterCounter(uint64_t *counter) = 0;

            virtual Status
            UnregisterCounter(uint64_t *counter) = 0;

        }; // TraceSource

        class EventClass
        {
        protected:
            virtual ~EventClass() {}
        public:
            virtual EventClassId GetId() const = 0;
            virtual const TraceSource *GetSource() const = 0;
            virtual FieldMask GetMask() const = 0;

            virtual size_t GetEventRecordSize() const = 0;

            virtual ValueIndex GetNumValues() const = 0;
            virtual const EventFieldType * GetEventField(ValueIndex vidx) const = 0;
            virtual size_t GetValueOffset(ValueIndex vidx) const = 0;

            // Trace callbacks
            //////////////////////////////////////////////////
            virtual Status
            RegisterCallback(CallbackT callback, 
                             void *user_ptr = 0) = 0;

            virtual Status
            UnregisterCallback(CallbackT callback,
                               void *user_ptr = 0) = 0;

            // Modifying Callbacks
            //////////////////////////////////////////////////

            virtual Status
            RegisterModifyingCallback(ModifyingCallbackT callback,
                                      void *user_ptr = 0) = 0;

            virtual Status
            UnregisterModifyingCallback(ModifyingCallbackT callback,
                                        void *user_ptr = 0) = 0;

            virtual ValueIndex GetValueIndex(const char *name) const = 0;

        }; // EventClass

        struct EventRecord
        {
            EventClassId event_class_id;

            template<typename T>
            inline T Get(const EventClass *event_class, ValueIndex evi) const
            {
                size_t offset = event_class->GetValueOffset(evi);
                return *(reinterpret_cast<const T *>(reinterpret_cast<const uint8_t *>(this) + offset));
            }

            inline const uint8_t * GetPtr(const EventClass *event_class, ValueIndex evi) const
            {
                size_t offset = event_class->GetValueOffset(evi);
            
                return (reinterpret_cast<const uint8_t *>(this) + offset);
            }

            // Get the size of a value of variable size (in bytes):
            inline const uint16_t GetSize(const EventClass *event_class, ValueIndex evi) const
            {
                size_t offset = event_class->GetValueOffset(evi);
            
                return *reinterpret_cast<const uint16_t *>((reinterpret_cast<const uint8_t *>(this) + offset - 2));
            }

            template<typename T>
            inline T GetAs(const EventClass *event_class, ValueIndex evi) const
            {
                size_t size = event_class->GetEventField(evi)->GetSize();
                T mask = T(-1);
                if (size < sizeof(T)) mask = (T(1) << (size * 8)) - 1;
                T value = Get<T>(event_class, evi);
                value &= mask; // TODO: Sign extend signed values
                return value;
            }

            template<typename T>
            inline void Set(const EventClass *event_class, ValueIndex evi, T val)
            {
                size_t offset = event_class->GetValueOffset(evi);
                *(reinterpret_cast<T *>(reinterpret_cast<uint8_t *>(this) + offset)) = val;
            }

        };

    } // namespace v0

} // namespace MTI

#endif

// end of file ModelTraceInterface_v0.h
