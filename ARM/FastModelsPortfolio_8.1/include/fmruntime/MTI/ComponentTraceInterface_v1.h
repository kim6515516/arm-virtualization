/*!
 *  \file   ComponentTraceInterface_v1.h
 *  \brief  Version 1 MTI::ComponentTraceInterface and helper classes.
 *  \date   Copyright ARM Limited 2008-2009 All Rights Reserved.
 *  
 *  Normally this header file should not be included directly. The
 *  ModelTraceInterface.h header should be included instead.
 */

#ifndef MTI_COMPONENTTRACEINTERFACE_V1_H
#define MTI_COMPONENTTRACEINTERFACE_V1_H

#include "eslapi/CAInterface.h"

#include <stddef.h> // size_t
#include <utility>  // std::pair

namespace MTI
{
    namespace v1
    {
        class TraceSource;
        class EventFieldType;
        class EventClass;
        struct EventRecord;

        /**
         * Used as return value in certain methods to indicate success or error.
         */
        enum Status
        {
            MTI_OK,                      /// No error, function successfully executed.
            MTI_FUNCTION_NOT_SUPPORTED,  /// This method is completely unsupported in this model.
            MTI_PARAMETER_NOT_SUPPORTED, /// This parameter combination is not supported by this model.
            MTI_PARAMETER_INVALID,       /// A parameter value is invalid, e.g. too large.
            MTI_BUSY,                    /// A method cannot be completed since the model is busy (running ?).
            MTI_ERROR                    /// A general error that cannot be categorized occurred.
        };

        /// Index to enumerate EventClass.
        typedef uint16_t EventClassId;

        /// Index to enumerate TraceSource in a ComponentTraceInterface.
        typedef int SourceIndex;

        /// Index to enumerate EventFieldType in a TraceSource.
        typedef int FieldIndex; // 0 to 31

        /// Index to enumerate values in a EventRecord.
        typedef int ValueIndex; // 0 to 31


        /// This type describes a set of fields of a trace source.
        typedef uint32_t FieldMask;

        /**
         * This is the type of the callback functions that can be
         * called when trace events occur.
         *
         * \param user_data This returns the value given when
         * registering a callback with a trace source. Use is up to
         * the user. Typical use is to use user_data to be able to
         * call into a C++ method using a C wrapper function (or
         * static class method).
         *
         * \param event_class This points to the EventClass with which
         * the callback was registered. The data from EventClass help
         * to interpret the data in event_record.
         *
         * \param event_record This is a pointer to the data detailing
         * the trace event that occurred.
         */
        typedef void (* CallbackT)(void *user_data, const EventClass *event_class, const EventRecord *event_record);

        /// Class to access all the trace sources of a component.
        /**
         * This class contains methods to query the trace sources a
         * single component provides. It is also possible to directly
         * access a trace source of known name.
         */
        class ComponentTraceInterface :
            public eslapi::CAInterface
        {
        public:
            /// Static helper method to return the interface name for the 
            /// CAInterface.
            static eslapi::if_name_t IFNAME() { return "ComponentTraceInterface1"; }
        
            /// Static helper method to return the current interface revision 
            /// for CAInterface.
            static eslapi::if_rev_t IFREVISION() { return 2; }
            
        protected:
            /// Not to be called by interface users.
            /**
             * An interface user must never delete an instance of type
             * ComponentTraceInterface as returned by
             * SystemTraceInterface::GetComponentTrace(). ComponentTraceInterface
             * instances live as long as their simulation.
             */
            virtual ~ComponentTraceInterface() {}

        public: // methods

            /** Return the number of trace sources of the component. */
            virtual SourceIndex GetNumOfTraceSources() const = 0;

            /**
             * Return a pointer to a trace source by index.
             *
             * \param index Index should be 0 to
             * GetNumOfTraceSources()-1.
             *
             * \return Returns a pointer to a trace source. Will
             * return 0 if an illegal index is given.
             */
            virtual TraceSource *GetTraceSource(SourceIndex index) const = 0;

            /**
             * Return a pointer to a trace source by name.
             *
             * \param name Name of a trace source. Trace source names are case sensitive.
             * 
             * \return Returns a pointer to a trace source. Will
             * return 0 if no trace source with the specified name exists.
             */
            virtual TraceSource *GetTraceSource(const char *name) const = 0;
            
            /**
             * Get the event class with the unique event class ID.
             *
             * \param event_class_id The ID for which the EventClass pointer should be returned.
             *
             * \return Returns a pointer to a EventClass. The instance
             * returned lives as long as the simulation and must not
             * be freed. If no events exist with the specified ID a 0
             * pointer is returned.
             */
            virtual const EventClass *GetEventClass(EventClassId event_class_id) const = 0;

            /** Get the type of a trace component.  This will help a
             * trace plugin to identify what kind of component is
             * providing trace. Examples of strings returned are
             * "ARM1176JZF-S" or "ARM_Cortex-A8".
             *
             * \return Returns a short typename identifying the kind
             * of component. A component which does not implement this
             * functionality should return 0.
             */
            virtual const char *GetComponentType() const =0;

            /**
             * This will return a string identifying the version of the
             * component providing trace. The format of the version
             * string is up to the component implementor. However
             * components provided as part of Fast Models will use the
             * number of the Fast Models release as the version string
             * (for example "5.1.24").
             * 
             * \return A string giving the component's version. A
             * component which does not implement this functionality
             * should return 0.
             */
            virtual const char *GetComponentVersion() const =0;
        };

        /// For compatibility with older versions of the interface:
        typedef ComponentTraceInterface ModelTraceInterface;

        /**
         * This class describes the field of an event emitted by a trace source. 
         */
        class EventFieldType
        {
        public: // types        

            /** This describes the type of a field of a trace event.
             */
            enum Type
            {
                MTI_UNSIGNED_INT,
                MTI_SIGNED_INT,
                MTI_BOOL,
                MTI_ENUM,
                MTI_FLOAT,
                MTI_STRING
            };

            /// This type describes the size of fields of trace events.
            typedef uint16_t Size;

            /** This type is used to enumerate enum constants for
             *  EventFieldType of type MTI_ENUM. */
            typedef uint32_t EnumIndex;

            /** This type is used to return one enum constant by the
             * GetEnumConstant() method.  */
            typedef std::pair<uint32_t, const char *> EnumConstant;

        protected:
            /**
             * An interface user must never delete an instance of type
             * EventFieldType as returned by
             * EventClass::GetField(). The instances live as long as
             * the simulation they belong to.
             */
            virtual ~EventFieldType() {} // not to be called by interface user

        public: // methods

            /// Return the source this EventFieldType is defined for.
            virtual const TraceSource *GetSource() const = 0;

            /// Get the index of this event field type. Event fields
            /// are numbered from 0 to TraceSource::GetNumFields()-1.
            virtual FieldIndex GetIndex() const =0;

            /// Get the name of this event field.
            virtual const char *GetName() const = 0;

            /// Get a human readable description of this event field.
            virtual const char *GetDescription() const = 0;

            /// Get the type of this event field.
            virtual Type GetType() const = 0;

            /** Return the size of the data of this event field in bytes. A
             * size of 0 indicates a field of variable size. The
             * maximum size in this case is given by
             * GetMaxSize(). The actual size can be acquired via EventRecord::GetSize().
             */
            virtual Size GetSize() const = 0;

            /// Return the maximum size of this field. For fields of
            /// fixed size this will return the same as GetSize().
            virtual Size GetMaxSize() const =0;

            // Enumeration support

            /// For fields of type MTI_ENUM this will return how many
            /// enumeration constants exist.
            virtual EnumIndex GetNumOfEnumConstants() const = 0;

            /** For a field of type MTI_ENUM this can return one
             * enumeration constant.
             *
             * \param enum_index The enumeration index must be in the
             * range 0 to GetNumOfEnumConstants()-1. It is NOT the
             * 'value' of the enum - use the LookupEnum() method to
             * look up single enum values.
             *
             * \return This returns a pair<uint32_t, const char *>. If
             * the enum_index is outside the range 0
             * .. GetNumOfEnumConstants()-1 then a pair with a 0 const char
             * pointer is returned.
             */
            virtual const EnumConstant GetEnumConstant(EnumIndex enum_index) const = 0;

            /**
             * Look up a single enumeration constant.
             *
             * \param value The value of the enum constant to look up.
             *
             * \return A pointer to a string constant is returned. If
             * no enum constant exists for the value given then 0 is
             * returned.
             */
            virtual const char *LookupEnum(uint32_t value) const = 0;

        }; // EventFieldType

        /**
         * A trace source is a single fixed source of a stream of
         * events during simulation. It is possible to register
         * a counter to be incremented when a trace event occurs.
         * For more complex actions an EventClass should be created
         * by selecting the set of fields which are of interest.
         * A callback can then be registered with this EventClass
         * to be called when the event occurs.
         */
        class TraceSource
        {
        protected: // methods
            /**
             * An interface user must never delete an instance of type
             * TraceSource as returned by
             * ComponentTraceInterface::GetTraceSource(). TraceSource
             * instances live as long as their simulation.
             */
            virtual ~TraceSource() {} // must not be called by interface user

        public: // methods
            
            /// Return the index of this trace source in the trace component.
            virtual SourceIndex GetIndex() const =0;

            /// Return the name of this trace source
            virtual const char *GetName() const = 0;

            /// Return a human readable description of the semantics of this trace source.
            virtual const char *GetDescription() const = 0;

            /// Return the number of fields that an event of this trace source can optionally generate.
            virtual FieldIndex GetNumFields() const = 0;
        
            /**
             * Return a instance of EventFieldType by index.
             *
             * \param index The index must be between 0 and GetNumFields()-1.
             *
             * \return Returns a pointer to an instance of
             * EventFieldType. If the index is out of range 0 is returned.
             */
            virtual const EventFieldType *GetField(FieldIndex index) const = 0;

            /**
             * Return an instance of EventFieldType by name.
             *
             * \param name The name of an event field as returned by EventFieldType::GetName().
             *
             * \return Returns a pointer to an instance of
             * EventFieldType. If no field with that name exists 0 is
             * returned.
             */            
            virtual const EventFieldType *GetField(const char *name) const = 0;
        
            /**
             * Create an EventClass by selecting a subset of event fields.
             * 
             * \param field_mask 
             *
             * \return 
             */
            virtual EventClass *
            CreateEventClass(FieldMask field_mask) const = 0;

            // Counters
            //////////////////////////////////////////////////

            /**
             * This will register a counter with an event
             * source. Every time an trace event is triggered the
             * counter will be increased by one. The interface user
             * must provide the storage for the counter. It must
             * remain valid until the simulation is destroyed, or the
             * counter is unregistered by calling
             * UnregisterCounter(). The counter variable will not be
             * initialized when registering.  The model must be halted
             * to register a counter.
             *
             * \param counter A pointer to a 64 bit counter variable
             * allocated by the interface user. It's up to the user to
             * keep the counter's memory allocated until it is
             * unregistered.
             *
             * \return Returns MTI_OK if successful.
             */
            virtual Status
            RegisterCounter(uint64_t *counter) = 0;

            /**
             * This method will unregister a counter which has
             * previously been registered using RegisterCounter(). The
             * model must be halted to unregister a counter.
             * 
             * \param counter Pointer to a 64 bit counter variable
             * which has been used with RegisterCounter() earlier.
             *
             * \return Will return MTI_OK if successful.
             */
            virtual Status
            UnregisterCounter(uint64_t *counter) = 0;

            /**
             * This will register a 32 bit counter with an event
             * source. Every time an trace event is triggered the
             * counter will be increased by one. The interface user
             * must provide the storage for the counter. It must
             * remain valid until the simulation is destroyed, or the
             * counter is unregistered by calling
             * UnregisterCounter(). The counter variable will not be
             * initialized when registering.  The model must be halted
             * to register a counter.
             *
             * \param counter A pointer to a 32 bit counter variable
             * allocated by the interface user. It's up to the user to
             * keep the counter's memory allocated until it is
             * unregistered.
             *
             * \return Returns MTI_OK if successful.
             */
            virtual Status
            RegisterCounter(uint32_t *counter) = 0;

            /**
             * This method will unregister a counter which has
             * previously been registered using RegisterCounter(). The
             * model must be halted to unregister a counter.
             * 
             * \param counter Pointer to a 32 bit counter variable
             * which has been used with RegisterCounter() earlier.
             *
             * \return Will return MTI_OK if successful.
             */
            virtual Status
            UnregisterCounter(uint32_t *counter) = 0;

        }; // TraceSource

        /**
         * An event class describes a subset of fields selected from a
         * certain trace source. Once an event class has been created
         * (with TraceSource::CreateEventClass()) callbacks can be
         * registered with it.
         *
         * Callbacks registered with the EventClass are passed an
         * EventRecord which contains the values of the fields requested.
         * EventClass includes methods which allow the caller to
         * determine the size and layout of the EventRecord.
         *
         * Every EventClass has a unique EventClassId.
         * This EventClassId is also included in the EventRecord. This
         * makes it possible to find the EventClass and TraceSource that
         * the EventRecord belongs to.
         */
        class EventClass
        {
        protected:
            /// Not to be called by an interface user.
            /**
             * An interface user must never delete an instance of type
             * EventClass. It is created by a call to
             * TraceSource::CreateEventClass() and will live as long
             * as the simulation. 
             */
            virtual ~EventClass() {}

        public:
            /** Return the unique EventClassId of this EventClass. */
            virtual EventClassId GetId() const = 0;
            
            /** Return the TraceSource this EventClass is defined for. */
            virtual const TraceSource *GetSource() const = 0;

            /** Get the mask that was used for the creation of this EventClass. */
            virtual FieldMask GetMask() const = 0;

            /** Return the size of an EventRecord produced by this
             * EventClass. If the EventClass contains variable sized
             * fields this is the maximum size of EventRecord
             * that might be generated.
             */
            virtual size_t GetEventRecordSize() const = 0;

            /** Return the number of values in the EventRecord
             * produced. This is equal to the number of bits set in the
             * FieldMask used to produce this EventClass.
             */
            virtual ValueIndex GetNumValues() const = 0;

            /** Returns the EventFieldType describing the value of the
             * EventRecord produced by this EventClass.
             */
            virtual const EventFieldType * GetEventField(ValueIndex vidx) const = 0;

            /** Return the index of the value by name.
             *
             * \param name The name of the value. Value names are the same
             * as the field name they are selected from.
             *
             * \return The index of the value in the range 0 to
             * GetNumValues()-1. If no value with the specified name exists
             * then ValueIndex(-1) is returned.
             */
            virtual ValueIndex GetValueIndex(const char *name) const = 0;

            /** Return the offset in bytes of a specified value inside
             * the EventRecord.
             *
             * \param vidx A value index in the range 0 to
             * GetNumValues()-1.
             *
             * \return Returns the offset in bytes. When an illegal
             * value index is given 0 is returned. (0 is the offset of
             * the event class id, so can never be a legal offset of a
             * value.)
             */
            virtual size_t GetValueOffset(ValueIndex vidx) const = 0;

            // Trace callbacks
            //////////////////////////////////////////////////

            /** Register a callback with this EventClass. Every time
             * this trace event happens the callback function is
             * called. Depending on the event the callback may be
             * called with a high frequency. In this case it is
             * important to make the callback function execute quickly to
             * keep the impact on the simulation performance
             * low. If more complex operations are required then one
             * might create a separate worker thread to do
             * the expensive operations. The callback function would then
             * just pass a short signal to the worker thread and
             * return to the simulation. 
             *
             * It is possible to register multiple callbacks for the
             * same EventClass. All of the callbacks will be called
             * when an event occurs. The order in which they are
             * called is undefined. 
             *
             * The same callback can be registered multiple times with
             * different values of user_ptr. However the same
             * callback/user_ptr combination should not be registered
             * more than once, otherwise the behavior is undefined.
             * 
             * The simulation must be in the stopped state to register (or
             * unregister) callbacks.
             *
             * \param callback This is a pointer to a user defined "C"
             * function (can be a static class member function).
             *
             * \param user_ptr The use of this pointer is left to the
             * interface user. It is passed as a parameter when the
             * callback is called. A typical use case is to pass a
             * class pointer which can then be used in a wrapper
             * function to call a class member function.
             *
             * \return Returns MTI_OK if the callback was successfully
             * registered.
             */
            virtual Status
            RegisterCallback(CallbackT callback, 
                             void *user_ptr = 0) = 0;

            /** Unregister a callback registered earlier by
             * RegisterCallback(). The simulation must be in the halted
             * state to unregister (or register) callbacks.
             *
             * \param callback The pointer earlier passed to RegisterCallback().
             * 
             * \param user_ptr The user_ptr used to register the
             * callback. The combination of callback and user_ptr
             * uniquely identifies the registration which should be
             * removed.
             * 
             * \return Returns MTI_OK if the callback was successfully removed.
             */
            virtual Status
            UnregisterCallback(CallbackT callback,
                               void *user_ptr = 0) = 0;

            /**
             * Dump the current state of a trace source through the
             * callback provided. This could be useful if the current
             * internal state of a trace source is unknown,
             * for example after switching on tracing in the middle of a
             * simulation run. A typical example would be a trace
             * source describing register events. Since only register
             * writes trigger a normal callback the status of
             * the register file is unknown when tracing is started.
             * A call to DumpState will cause a callback for every
             * register of the register file, with the current register
             * value.
             *
             * Not all trace sources will implement this
             * functionality.
             *
             * The simulation does not have to be stopped in order for
             * this call to work. It is permitted to call this from
             * within a another callback, provided that that
             * callback is from a different TraceSource.
             * 
             * \param callback The callback function the callbacks should be made to.
             *
             * \param user_ptr A pointer passed through to the
             * callback, with user defined content.
             * 
             * \return Returns MTI_OK if the call was successful. The
             * function will return only after the callbacks have been
             * made.
             */
            virtual Status 
            DumpState(CallbackT callback,
                      void *user_ptr = 0) = 0;
            
        }; // EventClass

        /** An EventRecord is the structure passed when calling
         * callback functions. Except for the event_class_id field the
         * layout of the data is dynamic and depends on the fields
         * selected when creating an EventClass. Accessor methods
         * are used to access the data.
         * This allows the binary layout of the event to change without
         * requiring MTI plugins to be recompiled.
         */
        struct EventRecord
        {
            /** The event_class_id can be used to look up the
             * EventClass this EventRecord belongs to.
             * Since callbacks are always passed a pointer to the
             * EventClass it isn't generally necessary to use this
             * inside callbacks.
             */
            EventClassId event_class_id;

            /** This template method is used to access a value of known
             * type and size. Since the type and size of a event field
             * might change with different models it is recommended to
             * at least once check the size and type of a value before
             * using this method. Alternatively the GetAs() method
             * should be used. Types permitted are uint8_t, uint16_t,
             * uint32_t, uint64_t, int8_t, int16_t, int32_t and
             * int64_t. */
            template<typename T>
            inline T Get(const EventClass *event_class, ValueIndex vidx) const
            {
                size_t offset = event_class->GetValueOffset(vidx);
                return *(reinterpret_cast<const T *>(reinterpret_cast<const uint8_t *>(this) + offset));
            }

            /** This is a special method to access boolean values of an
             * EventRecord. */
            inline bool GetBool(const EventClass *event_class, ValueIndex vidx) const
            {
                size_t offset = event_class->GetValueOffset(vidx);
                return (*(reinterpret_cast<const uint8_t *>(this) + offset)) != 0;
            }

            /** This method helps to access values not accessible via
             * the Get<> or GetAs<> methods. These are for example
             * values of variable size, or those which have a size
             * different from a C type (not 8, 16, 32 or 64 bits). The
             * method returns a pointer to the first byte of the
             * data. */
            inline const uint8_t * GetPtr(const EventClass *event_class, ValueIndex vidx) const
            {
                size_t offset = event_class->GetValueOffset(vidx);
            
                return (reinterpret_cast<const uint8_t *>(this) + offset);
            }

            /** This method returns the size of a value of an
             * EventRecord in bytes. The combination of
             * GetVariableSize()/GetPtr() is used to access variable
             * sized values. It must not be used on values of fixed
             * size (in that case use GetSize() instead). */
            inline EventFieldType::Size GetVariableSize(const EventClass *event_class, ValueIndex vidx) const
            {
                size_t offset = event_class->GetValueOffset(vidx);
                
                return *reinterpret_cast<const uint16_t *>((reinterpret_cast<const uint8_t *>(this) + offset - 2));
            }

            /** This method returns the size of a value. It can be
             * used on both fixed and variable sized fields. */
            inline EventFieldType::Size GetSize(const EventClass *event_class, ValueIndex vidx) const
            {
                EventFieldType::Size size = event_class->GetEventField(vidx)->GetSize();
                if (size == 0)
                    return GetVariableSize(event_class, vidx);
                return size;
            }

            /** This convenience method will access a value of an
             * EventRecord, and convert it into the specified data type
             * Depending on the size of the EventRecord's value
             * and the target type, the data might be extended or
             * truncated. Signed values will be correctly sign-extended
             * if necessary. */
            template<typename T>
            inline T GetAs(const EventClass *event_class, ValueIndex vidx) const
            {
                size_t size = event_class->GetEventField(vidx)->GetSize();
                T mask = T(-1);
                if (size < sizeof(T)) mask = (T(1) << (size * 8)) - 1;
                T value = Get<T>(event_class, vidx);
                value &= mask; // TODO: Sign extend signed values

                if ((event_class->GetEventField(vidx)->GetType() == EventFieldType::MTI_SIGNED_INT) &&
                    (size < sizeof(T)))
                { // sign extend
                    if (value & (T(1) << ((size * 8) - 1)))
                        value |= ~mask;
                }
                return value;
            }
        };

    } // namespace v1

} // namespace MTI

#endif

// end of file ComponentTraceInterface_v1.h
