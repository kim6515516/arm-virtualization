/*!
 * \file   SGComponentTrace.h
 * \brief  Implementation of the TraceInterface methods for component tracing.
 * \date   Copyright 2010-2011 ARM Limited. All rights reserved.
 */

#ifndef SG_COMPONENT_TRACE_H
#define SG_COMPONENT_TRACE_H

#include <map>
#include <string>
#include <vector>
#include "MTI/ModelTraceInterface.h"
#include "eslapi/CAInterface.h"

#include "eslapi/CADITypes.h"

#include "sg/ActivationFlag.h"

#include <stddef.h>
#include <assert.h>

#include <set>

#ifndef MTI_TRACEINTERFACE_V1_H
#error "This file only supports ModelTraceInterface_v1"
#endif

namespace eslapi
{
    class CAInterface;
    class CADI;
};


namespace sg {

class EventSourceBase;
class SGEventFieldType;
class SGEventClass;

/**
 * sg::SGEventCounter class.
 * This provides the ability to set a counter which is increased each time an EventSource is fired,
 * and which invokes a callback when the counter reaches zero.
 */
class EventCounter {
public:
   /**
    * Default constructor.
    * The initial counter value is set to zero
    */
    EventCounter();
    virtual ~EventCounter();

   /**
    * Constructor.
    * The initial counter value is set to value passed in
    * \param value initial integer value of type uint32_t.
    * \param es pointer to EventSourceBase. pass NULL to stop counting.
    */
    EventCounter(uint32_t value, uint32_t offset,  EventSourceBase* es, bool enabled);

    ///** Set the EventSource of the given sg::EventCounter.
    //* \param es a pointer to sg::EventSourceBase.
    // */
    //void setEventSource( EventSourceBase* es);

    ///** get the EventSource of the given sg::EventCounter.
    // * \return a pointer to sg::EventSourceBase.
    // */
    //EventSourceBase* getEventSource();

    /** Check the status of the event counter, disabled or enabled.
     *  return boolean value of true or false.
     */
    bool isEnabled();

    /** Enable or disable the event counter.
     *  \param enabled boolean value of true or false.
     */
    void setEnabled(bool enabled );

    /** Read current counter value.
     *  \return current counter value.
     */
    uint32_t getValue();

    /** Set current counter value.
     *  \param value integer value of type uint32_t.
     */
     void setValue(uint32_t value);

    /** Set counter offset value.
     *  \param value initial integer value of type uint32_t.
     */
    void setOffset(uint32_t offset);

    /** Read master counter offset value.
     *  \return master counter offset value.
     */
    uint32_t getOffset();

    /** Set master counter start value when event counter is registered with event source .
     *  \param value initial integer value of type uint32_t.
     */
    void setMasterStartValue(uint32_t value);

    /** Read master counter start value.
     *  \return master counter start value.
     */
    uint32_t getMasterStartValue();


    /** Called when the counter overflow and hits zero
     *  The user is expected to derive from sg::EventCounter and implement onHitZero()
     */
    virtual void onHitZero();
    void increase();
public:
    EventSourceBase* event_source;

private:
    uint32_t counter_value;
    // the master counter value of the event source
    // when the event counter is registered with a event source
    uint32_t master_start_value;
    uint32_t master_offset;

    bool is_enabled;
};

class ComponentTrace : public MTI::ComponentTraceInterface
{
public: // methods
    ComponentTrace();
    ComponentTrace(const char *type, const char *version);
    virtual ~ComponentTrace();

    virtual eslapi::CAInterface* ObtainInterface(const char *ifName, eslapi::if_rev_t minRev, eslapi::if_rev_t *actualRev);

    virtual const char *GetComponentType() const;
    virtual const char *GetComponentVersion() const;

    void SetCADI(eslapi::CADI *cadi_) { cadi = cadi_; }
    bool isCADIStopped() const;

    virtual MTI::SourceIndex GetNumOfTraceSources() const;
    virtual MTI::TraceSource *GetTraceSource(MTI::SourceIndex index) const;
    virtual MTI::TraceSource *GetTraceSource(const char *name) const;
    virtual const MTI::EventClass * GetEventClass(MTI::EventClassId event_class_id) const;

    /// Take ownership of trace source (will be deleted)
    void AddTraceSource(EventSourceBase *);

    /// Take ownership of trace source (will be deleted)
    void AddTraceSourceHidden(EventSourceBase *);

    /// Expose a trace source the trace component.  This object will _not_
    /// destroy the object on its destruction.
    void RegisterTraceSource(EventSourceBase *);

    /// Expose a trace source the trace component.  This object will _not_
    /// destroy the object on its destruction.
    void RegisterTraceSourceHidden(EventSourceBase *);

    ComponentTrace* GetCreateTrace(const char *sub_path, const char *type) const;

    // Used by TraceSource::GetIndex()
    MTI::SourceIndex GetSourceIndex(const char *name);


protected: // data
    eslapi::CADI *cadi;
    eslapi::CADITargetFeatures_t ctTargetFeatures;
    bool ctTargetFeaturesOK;

private:
    typedef std::vector<EventSourceBase *> SourcesT;
    SourcesT sources;
    SourcesT hidden_sources;
    SourcesT sources_i_will_destroy;

    mutable bool sources_are_sorted;
    mutable bool hidden_sources_are_sorted;
    bool show_hidden_trace_sources;

    void EnsureSorting() const;
    void GetCADITargetFeatures();
}; // class ComponentTrace


// this allows the size and pointer of a variable length type to be
//   passed through EventSourceN as a single parameter (as it is otherwise counted)
template <size_t max_size_>
struct size_and_pointer {
    static size_t const max_size = max_size_;
    int size;
    const uint8_t*  pointer;
    size_and_pointer(int size_, const uint8_t* pointer_) : size(size_), pointer(pointer_) {}
};

class EventSourceBase :
    public MTI::TraceSource
{
public:
    EventSourceBase(const char *name_="",
                    const char *description_="");

    virtual ~EventSourceBase();

    virtual MTI::SourceIndex GetIndex() const;
    virtual const char *GetName() const { return name.c_str(); }
    virtual const char *GetDescription() const { return description.c_str(); }
    virtual MTI::FieldIndex GetNumFields() const { return MTI::FieldIndex(fields.size()); }

    virtual const MTI::EventFieldType *GetField(MTI::FieldIndex index) const;
    virtual const MTI::EventFieldType *GetField(const char *name) const;

    // Register an trace record type
    virtual MTI::EventClass *
    CreateEventClass(MTI::FieldMask field_mask) const;

    // Counters
    //////////////////////////////////////////////////
    virtual MTI::Status
    RegisterCounter(uint64_t *counter);

    virtual MTI::Status
    UnregisterCounter(uint64_t *counter);

    virtual MTI::Status
    RegisterCounter(uint32_t *counter);

    virtual MTI::Status
    UnregisterCounter(uint32_t *counter);

    virtual void Update();

public: // internal API
    void setDescription(const char *desc);
    void setName(const char *name);

    // returns the id of the field added (starting with 0)
    MTI::FieldIndex AddField(SGEventFieldType *);

    // returns the id of the field added (starting with 0)
    MTI::FieldIndex AddField(const char *name,
                             const char *description,
                             MTI::EventFieldType::Type type,
                             MTI::EventFieldType::Size size,
                             MTI::EventFieldType::Size max_size=0);

    // returns the id of the field added (starting with 0)
    MTI::FieldIndex AddField(const char *name,
                             const char *description,
                             const SGEventFieldType &field_template);

    SGEventFieldType *GetField(const char *name);

    // Add an enum constant. The string_constant variable must point
    // to memory constant for the runtime of the model !
    bool AddEnumConstant(MTI::FieldIndex fidx, uint32_t value, const char *string_constant);
    bool RemoveEnumConstant(MTI::FieldIndex fidx, uint32_t value);
    bool RenameEnumConstant(MTI::FieldIndex fidx, uint32_t value, const char *new_string_constant);

    // Return the superset of all field used in all registered event classes:
    MTI::FieldMask GetUsedFields() const;

    size_t GetMaxEventRecordSize() const;

    virtual MTI::Status DumpState(SGEventClass *, MTI::CallbackT callback, void *user_data);

    void AddActivationFlag(bool *activation_flag);
    void RemoveActivationFlag(bool *activation_flag);

    ActivationValue const* getActiveFlag() const;

    bool isActive() const;

    /// A method that is called when the active state for the class is called.
    /// The class starts up as inactive.
    virtual void activeStateChanged(bool new_active_state_) const;

    uint32_t getMasterEventCounterValue();
    void setMasterEventCounterValue(uint32_t value);
    void setMasterEventCounterStatus(bool status) { master_event_counter.setEnabled(status); }

    MTI::Status RegisterEventCounter(EventCounter *event_counter);
    MTI::Status UnregisterEventCounter(EventCounter *event_counter);
    void nextHitZeroMasterValue();
    void sendEventCounterHitZero();

    inline void IncrementCounters() const
    {
        for(Counters64bitT::const_iterator it = counters64bit.begin();
            it != counters64bit.end(); ++it)
        {
            ++(**it);
        }
        for(Counters32bitT::const_iterator it = counters32bit.begin();
            it != counters32bit.end(); ++it)
        {
            ++(**it);
        }

        if ( master_event_counter.isEnabled() ) {
            master_event_counter.increase();
        }
    }

protected:
    void prepareEventClassTrace(SGEventClass* event_class);
    void sendEventClassTrace(SGEventClass* event_class);


    // non-Pointer version
    // messiness to deal with C++ not being able to specialise templated member functions
    template<typename P>
    void traceParamNonPtr(const P& param);
    void traceParamPtr(const void * param);

    // overload for special case of sg::size_and_pointer (taken in preference to base template)
    template<size_t max_size_>
    void traceParamNonPtr(const size_and_pointer<max_size_>& param) {
        traceParamNonPtr(param.size);
        traceParamPtr(param.pointer);
    }

    template<typename T>
    struct ParamHelper {
        static void traceParam(EventSourceBase* base, const T& t) { base->traceParamNonPtr(t); }
    };

    template<typename T>
    struct ParamHelper<T*> {
        static void traceParam(EventSourceBase* base, T* t) { base->traceParamPtr(t); }
    };

    template<typename P>
    void traceParam(const P& param) { ParamHelper<P>::traceParam(this, param); }

    // to offer more inheritance flexibility implementation is done in the base
    // class with protected visibility and public exposition in the derived classes

    void fireEvent() {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                    ec_it != event_classes.end();
                    ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                sendEventClassTrace(event_class);
            }

            sendEventCounterHitZero();
        }
    }
    
    template<typename T1>
    void fireEvent(T1 p1) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                    ec_it != event_classes.end();
                    ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                sendEventClassTrace(event_class);
            }

            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2>
    void fireEvent(T1 p1, T2 p2) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                    ec_it != event_classes.end();
                    ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3>
    void fireEvent(T1 p1, T2 p2, T3 p3) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                traceParam(p15);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                traceParam(p15);
                traceParam(p16);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                traceParam(p15);
                traceParam(p16);
                traceParam(p17);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                traceParam(p15);
                traceParam(p16);
                traceParam(p17);
                traceParam(p18);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                traceParam(p15);
                traceParam(p16);
                traceParam(p17);
                traceParam(p18);
                traceParam(p19);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                traceParam(p15);
                traceParam(p16);
                traceParam(p17);
                traceParam(p18);
                traceParam(p19);
                traceParam(p20);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                traceParam(p15);
                traceParam(p16);
                traceParam(p17);
                traceParam(p18);
                traceParam(p19);
                traceParam(p20);
                traceParam(p21);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
    void fireEvent(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22) {
        if ( isActive() ) {
            IncrementCounters();
            for(EventClassesT::const_iterator ec_it = event_classes.begin();
                ec_it != event_classes.end();
                ++ec_it)
            {
                SGEventClass *event_class = *ec_it;
                prepareEventClassTrace(event_class);
                traceParam(p1);
                traceParam(p2);
                traceParam(p3);
                traceParam(p4);
                traceParam(p5);
                traceParam(p6);
                traceParam(p7);
                traceParam(p8);
                traceParam(p9);
                traceParam(p10);
                traceParam(p11);
                traceParam(p12);
                traceParam(p13);
                traceParam(p14);
                traceParam(p15);
                traceParam(p16);
                traceParam(p17);
                traceParam(p18);
                traceParam(p19);
                traceParam(p20);
                traceParam(p21);
                traceParam(p22);
                sendEventClassTrace(event_class);
            }
            sendEventCounterHitZero();
        }
    }

public: // data
    ComponentTrace *mti_trace;

    std::string name;
    std::string description;

    typedef std::vector<SGEventFieldType *> FieldsT;
    FieldsT fields;

    typedef std::vector<SGEventClass *> EventClassesT;
    EventClassesT event_classes;

    typedef std::vector<uint64_t *> Counters64bitT;
    Counters64bitT counters64bit;

    typedef std::vector<uint32_t *> Counters32bitT;
    Counters32bitT counters32bit;

    bool is_info_source;

    // must not be private to be available to CT trace...
protected:
    union LOCAL_CURSOR {
        const void**    cv;
        void*           v;
        char*           c;
        uint8_t*        u8;
        uint16_t*       u16;
        uint32_t*       u32;
        uint64_t*       u64;
    } cursor;

    MTI::FieldMask mask;
    int field_index;
    int data_size;
    uint8_t *record;
    ActivationFlag is_active;
    std::set<bool *> activation_flags;
    std::pair<MTI::CallbackT, void *> status_cb;

    std::vector<EventCounter *> event_counters;
    mutable EventCounter master_event_counter;
    uint32_t next_master_value;
}; // EventSourceBase

inline void EventSourceBase::traceParamPtr(const void* param)
{
    if (field_index >= GetNumFields())
        return;

    const MTI::EventFieldType *field = GetField(MTI::FieldIndex(field_index));
    bool field_is_in_record = (mask & (1U << field_index)) != 0;

    switch(field->GetSize())
    {
        case 0: // variable length field
            {
                if (field->GetType() == MTI::EventFieldType::MTI_STRING)
                {
                    if (field_is_in_record) {
                        const char *s = (const char*)param;
                        size_t size = strlen(s) + 1; // size inclusive 0 byte
                        size_t maxsize = field->GetMaxSize();
                        if (maxsize && (size > maxsize))
                            size = maxsize;
                        *cursor.u16++ = uint16_t(size);
                        memcpy(cursor.c, s, size - 1);
                        cursor.c[size-1] = 0;
                        cursor.c += size;
                    }
                    field_index++;
                }
                else
                {
                    // size must have been latched
                    if (data_size > 0)
                    {
                        if (field_is_in_record) {

                            // size will be passed in
                            int size = data_size;
                            uint8_t *data = (uint8_t*)param;
                            *cursor.u16++ = size;
                            memcpy(cursor.c, data, size);
                            cursor.u8 += size;
                        }
                        data_size = 0;
                    }
                    else
                    {
                        assert(!"Trace Field data block size not specified");
                    }
                    field_index++;
                }
            }
            break;
        case sizeof(void*): // pointer
            {
                *cursor.cv++ = param;
                field_index++;
            }
            break;
        default:
            {
                assert(!"Trace: field is not MTI_STRING or field size is not sizeof(P*)");
            }
    }
}

template<typename P>
void EventSourceBase::traceParamNonPtr(const P& param)
{
    if (field_index >= GetNumFields())
        return;

    const MTI::EventFieldType *field = GetField(MTI::FieldIndex(field_index));
    bool field_is_in_record = (mask & (1U << field_index)) != 0;

    switch(field->GetSize())
    {
        case 0: // variable length field
        {
            if (field->GetType() == MTI::EventFieldType::MTI_STRING)
            {
                assert(!"Trace Field MTI_STRING expecting const char* param\n");
            }
            else
            {
                data_size = int(param);
                // don't move the field index on as the data size and data pointer are the same field
            }
        }
        break;

        case 1:
        {
            if (field_is_in_record)
            {
                *cursor.u8++ = uint8_t(param);
            }
            field_index++;
        }
        break;

        case 2:
        {
            if (field_is_in_record)
            {
                *cursor.u16++ = uint16_t(param);
            }
            field_index++;
        }
        break;

        case 4:
        {
            if (field_is_in_record)
            {
                *cursor.u32++ = uint32_t(param);
            }
            field_index++;
        }
        break;

        case 8:
        {
            if (field_is_in_record)
            {
                *cursor.u64++ = uint64_t(param);
            }
            field_index++;
        }
        break;

        case 16:
        {
            if (data_size == 0)
                data_size = 16;

            if (field_is_in_record)
            {
                *cursor.u64++ = uint64_t(param);
            }

            data_size -= 8;
            if (data_size==0)
                field_index++;
        }
        break;

        default:
            assert(!"Trace: unsupported field size"); // unsupported field size
    }
}

class EventSource0 : public EventSourceBase {
public:
    EventSource0(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire() { EventSourceBase::fireEvent(); }
};

template <typename T1>
class EventSource1 : public EventSourceBase {
public:
    EventSource1(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1) { EventSourceBase::fireEvent(p1); }
};

template <typename T1, typename T2>
class EventSource2 : public EventSourceBase {
public:
    EventSource2(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2) { EventSourceBase::fireEvent(p1, p2); }
};

template <typename T1, typename T2, typename T3>
class EventSource3 : public EventSourceBase {
public:
    EventSource3(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3) { EventSourceBase::fireEvent(p1, p2, p3); }
};

template <typename T1, typename T2, typename T3, typename T4>
class EventSource4 : public EventSourceBase {
public:
    EventSource4(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4) { EventSourceBase::fireEvent(p1, p2, p3, p4); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5>
class EventSource5 : public EventSourceBase {
public:
    EventSource5(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
class EventSource6 : public EventSourceBase {
public:
    EventSource6(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
class EventSource7 : public EventSourceBase {
public:
    EventSource7(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
class EventSource8 : public EventSourceBase {
public:
    EventSource8(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
class EventSource9 : public EventSourceBase {
public:
    EventSource9(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
class EventSource10 : public EventSourceBase {
public:
    EventSource10(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
class EventSource11 : public EventSourceBase {
public:
    EventSource11(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
class EventSource12 : public EventSourceBase {
public:
    EventSource12(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
class EventSource13 : public EventSourceBase {
public:
    EventSource13(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
class EventSource14 : public EventSourceBase {
public:
    EventSource14(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
class EventSource15 : public EventSourceBase {
public:
    EventSource15(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
class EventSource16 : public EventSourceBase {
public:
    EventSource16(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
class EventSource17 : public EventSourceBase {
public:
    EventSource17(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
class EventSource18 : public EventSourceBase {
public:
    EventSource18(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
class EventSource19 : public EventSourceBase {
public:
    EventSource19(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
class EventSource20 : public EventSourceBase {
public:
    EventSource20(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
class EventSource21 : public EventSourceBase {
public:
    EventSource21(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
class EventSource22 : public EventSourceBase {
public:
    EventSource22(const char *name_="", const char *description_="")
        : EventSourceBase(name_, description_)
    {}

    inline void fire(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16, T17 p17, T18 p18, T19 p19, T20 p20, T21 p21, T22 p22) { EventSourceBase::fireEvent(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22); }
};



class SGEventFieldType :
    public MTI::EventFieldType
{
public: // methods
    SGEventFieldType(const char *name,
                     const char *description,
                     Type type,
                     Size size,
                     Size max_size=0);

    SGEventFieldType(const char *name,
                     const char *description,
                     const SGEventFieldType &field_template);

    virtual const MTI::TraceSource *GetSource() const { return source; }
    virtual MTI::FieldIndex GetIndex() const { return index; }

    virtual const char *GetName() const { return name.c_str(); }
    virtual const char *GetDescription() const { return description.c_str(); }
    virtual Type GetType() const { return type; }
    virtual Size GetSize() const { return size; }

    virtual Size GetMaxSize() const { return max_size; }

    // Enumeration support
    virtual MTI::EventFieldType::EnumIndex GetNumOfEnumConstants() const
    { return (MTI::EventFieldType::EnumIndex)enum_values.size(); }

    virtual const MTI::EventFieldType::EnumConstant GetEnumConstant(MTI::EventFieldType::EnumIndex eidx) const
    { return enum_values[eidx]; }

    virtual const char *LookupEnum(uint32_t value) const;

public: // data
    EventSourceBase *source;
    MTI::FieldIndex index;

    std::string name;
    std::string description;
    Type type;
    Size size, max_size;

    typedef std::vector<EnumConstant> EnumMapT;
    EnumMapT enum_values;

public: // Internal API
    // Add an enum constant. The string_constant variable must point
    // to memory constant for the runtime of the model !
    bool AddEnumConstant(uint32_t value, const char *string_constant);
    bool RemoveEnumConstant(uint32_t value);
    bool RenameEnumConstant(uint32_t value, const char *new_string_constant);
}; // SGEventFieldType



class SGEventClass :
    public MTI::EventClass
{
public:
    SGEventClass(EventSourceBase *source_,
                 uint32_t field_mask_,
                 MTI::EventClassId id_);

    ~SGEventClass();

    virtual MTI::EventClassId GetId() const { return id; }
    virtual const MTI::TraceSource *GetSource() const { return source; }
    virtual MTI::FieldMask GetMask() const { return field_mask; }

    virtual size_t GetEventRecordSize() const;

    virtual MTI::ValueIndex GetValueIndex(const char *name) const;

    virtual MTI::ValueIndex GetNumValues() const;
    virtual const MTI::EventFieldType * GetEventField(MTI::ValueIndex vidx) const;
    virtual size_t GetValueOffset(MTI::ValueIndex vidx) const; // this should be fast

    // Trace callbacks
    //////////////////////////////////////////////////
    virtual MTI::Status
    RegisterCallback(MTI::CallbackT callback, void *user_ptr = 0);

    virtual MTI::Status
    UnregisterCallback(MTI::CallbackT callback, void *user_ptr = 0);

    virtual MTI::Status
    DumpState(MTI::CallbackT callback, void *user_ptr = 0);

#ifdef MTI_TRACEINTERFACE_V0_H
    // Modifying Callbacks
    //////////////////////////////////////////////////

    virtual MTI::Status
    RegisterModifyingCallback(MTI::ModifyingCallbackT callback, void *user_ptr = 0);

    virtual MTI::Status
    UnregisterModifyingCallback(MTI::ModifyingCallbackT callback, void *user_ptr = 0);
#endif

private:
    EventSourceBase *source;
    uint32_t field_mask;
    MTI::EventClassId id;
    MTI::ValueIndex num_values;
    size_t record_size;
    const SGEventFieldType **fields;
    size_t offsets[32];

public:
    typedef std::vector<std::pair<MTI::CallbackT, void *> > CallbacksT;
    CallbacksT callbacks;
}; // SGEventClass

} // end of namespace sg
#endif
