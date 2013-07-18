/*!
 * \file    SGScheduler.h
 * \brief   Basic framework for driving an event based simulator
 * \date    Copyright 2005 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_SCHEDULER_H
#define ARM_SG_SCHEDULER_H

#include "sg/SGstdint.h"

#include "sg/SGComponentWithSchedulerAccess.h"
#include "sg/SGTicks.h" // ticks_t is factored out to keep visibility of header files low

// should we split off the port definitions?

namespace sg {

class ComponentFactory;

class FrequencySource;
class FrequencyMultiplier;    
class FrequencyConstant1Hz;
class Timer;
class TimerCallback;
class SchedulerCallback;

/*! A ClockSignal represents a relative rate of a clock signal.
 * 
 *
 */
class ClockSignal : public Port
{
    // default behaviour
    void default_setClock(FrequencySource*) {}
    FrequencySource* default_getClock() { return NULL; }

public:
    declare_behaviour(rateInHz, double (void) );
    declare_behaviour(currentTicks, uint64_t (void) );

    // TODO - remove once fully converted
    declare_behaviour(getClock, FrequencySource* (void) );
    declare_behaviour(setClock, void (FrequencySource*) );


    ClockSignal() {
        define_behaviour(rateInHz);
        define_behaviour(currentTicks);

        // todo - remove once fully converted
        define_behaviour(getClock);
        define_behaviour(setClock);

        getClock.bind_default_behaviour(this, &ClockSignal::default_getClock);
        setClock.bind_default_behaviour(this, &ClockSignal::default_setClock);
    }
};

/*! A port used to call the owner of a timer when a timed event occurs
 *  
 *  Note: if the timer is used as a repeating timer, there should be only
 *        one behaviour bound to the callback
 */
class TimerCallbackPort : public Port
{
public:
    declare_behaviour(signal, uint32_t (void) );

    TimerCallbackPort() {
        define_behaviour(signal);
    }
};

class TimerCallback64Port : public Port
{
public:
    declare_behaviour(signal, uint64_t (void) );

    TimerCallback64Port() {
        define_behaviour(signal);
    }
};


class TimerControl : public Port
{
public:
    declare_slave_behaviour(cancel, void () );
    declare_slave_behaviour(set, void (uint32_t ticks) );
    declare_slave_behaviour(isSet, bool () );
    declare_slave_behaviour(remaining, uint32_t () );

    TimerControl() {
        define_behaviour(cancel);
        define_behaviour(set);
        define_behaviour(isSet);
        define_behaviour(remaining);
    }
};

class TimerControl64 : public Port
{
public:
    declare_slave_behaviour(cancel, void () );
    declare_slave_behaviour(set, void (uint64_t ticks) );
    declare_slave_behaviour(isSet, bool () );
    declare_slave_behaviour(remaining, uint64_t () );

    TimerControl64() {
        define_behaviour(cancel);
        define_behaviour(set);
        define_behaviour(isSet);
        define_behaviour(remaining);
    }
};

class ClockTimer : public ComponentWithSchedulerAccess
{
    friend class ClockTimerCallback;
    // underlying timer. should be hidden
    Timer* timer;
    TimerCallback* clockTimerCallback;

    void setClock(FrequencySource*);

    uint32_t default_callback() { return 0; }
    ticks_t timerCallback();

public: // ports

    /*! ClockTimer only allows one callback when the timer expires
     *  as the callback returns a value. Don't seem to be able to
     *  use pretty syntax here.
     */
    typedef fastdelegate::FastDelegate0<uint32_t> Callback;

    //! A timer MUST be bound to a clock to determine its countdown rate
    ClockSignal clock;

    //! The signal behaviour on the callback port will be invoked when the timer expires
    TimerCallbackPort timer_callback;

    //! Port to allow the timer to be controlled without using its C++ interface.
    TimerControl timer_control;

public:
    ClockTimer(std::string const& name, SimulationContext *context);
    ~ClockTimer();

    // may also want a TimerControl port
    virtual void cancel();
    virtual void set(uint32_t ticks);
    virtual bool isSet();
    virtual uint32_t remaining();
};

class ClockTimer64 : public ComponentWithSchedulerAccess
{
private:
    friend class ClockTimer64Callback;
    // underlying timer. should be hidden
    Timer* timer;
    TimerCallback* clockTimerCallback;

    void setClock(FrequencySource*);

    uint64_t default_callback() { return 0; }
    ticks_t timerCallback();

public: // ports

    /*! ClockTimer only allows one callback when the timer expires
     *  as the callback returns a value. Don't seem to be able to
     *  use pretty synax here.
     */
    typedef fastdelegate::FastDelegate0<uint64_t> Callback;

    //! A timer MUST be bound to a clock to determine its countdown rate
    ClockSignal clock;

    //! The signal behaviour on the callback port will be invoked whe the timer expires
    TimerCallback64Port timer_callback;

    //! Port to allow the timer to be controlled without using its C++ interface.
    TimerControl64 timer_control;

public:
    ClockTimer64(std::string const& name, SimulationContext *context);
    ~ClockTimer64();

    // The the excess we need to count if we've been set for longer than the 32
    // bit counter can deal with. This must be public so the callback can
    // manipulate it.
    uint64_t excess;

    // may also want a TimerControl port
    virtual void cancel();
    virtual void set(uint64_t ticks);
    virtual bool isSet();
    virtual uint64_t remaining();
};


/*! Callback (output) port for asynchronous (worker thread) signalling
 */
class AsyncCallback : public Port
{
public:
    declare_slave_behaviour(signal, void (void) );

    AsyncCallback() {
        define_behaviour(signal);
    }
};

/*! Signal (input) port for asynchronous (worker thread) signalling
 */
class AsyncControl : public Port
{
public:
    declare_slave_behaviour(signal, void (void) );

    AsyncControl() {
        define_behaviour(signal);
    }
};

/* Allows a component to be called back in the simulation thread when
 * signalled in a worker thread
 *
 * Either bind a behaviour at creation time or use standard port/behaviour
 * binding to bind to the signal port
 */
class AsyncSignal : public ComponentWithSchedulerAccess
{
    friend class AsyncSignalSchedulerCallback;
    SchedulerCallback *asyncSignalSchedulerCallback;
    void default_callback() { }

public: // ports
    typedef fastdelegate::FastDelegate0<void> Callback;

    // The signal behaviour of the callback port will be invoked in the simulation thread
    // when a worker thread calls the signal() method
    AsyncCallback   async_callback;
    
    // non-simulation threads call signal() on this port in order to schedule 
    // an event: a call to async_callback.signal() on the simulation thread
    AsyncControl   async_control;

public:

    AsyncSignal(std::string const& name, SimulationContext *context);
    ~AsyncSignal();

    // When invoked by a worker thread, this will schedule a callback on the callback port
    // in the simulation thread.
    void signal();
private:
    void constructor();
    void schedulerCallback();
};

/* Represents a control interface for a Clocking object which supports
 * rate settings. Allows e.g. a clockdivider to be a completely opaque
 * component exposing only Ports.
 */
class ClockRateControl : public Port
{
public:
    declare_behaviour(set, void (uint32_t mul, uint32_t div) );

    ClockRateControl() {
        define_behaviour(set);
    }
};

/* A Clock divider exports one ClockSignal representing a rate relative
 * to another ClockSignal
 */
class ClockDivider : public ComponentWithSchedulerAccess
{
    // could be hidden?
//    ClockInterface* clock;
    FrequencyMultiplier* frequencyMultiplier;

    void outputChanged();
    void outputChanging();

    void setMasterClock(FrequencySource*);
    FrequencySource* getOutputClock();

public: // ports

    // master signal input
    // drives the clock divider
    ClockSignal master;

    // clock output
    // provides the divided rate of the divider for others to use
    ClockSignal output;

    // rate control
    // allows the divider rate to be set
    ClockRateControl rate;
    
public:
    ClockDivider(std::string const& name, SimulationContext *context, uint32_t mul=1, uint32_t div=1);
    ~ClockDivider();

    // ClockDivider implementation
    double rateInHz();

    // set the rate of the output relative to the master 
    void setRate(uint32_t mul, uint32_t div);

    // Get the CurrentTicks of the Divider Output
    uint64_t currentTicks();
};

// a clock that can act as a root clock
class MasterClock : public ComponentWithSchedulerAccess
{
public: // ports
    ClockSignal output;

private:
    // could be hidden?
//    ClockInterface* clock;
    FrequencyConstant1Hz* outputFrequency;

    void outputChanged();
    void outputChanging();

    FrequencySource* getOutputClock();

public:
    MasterClock(std::string const& name, SimulationContext *context);
    ~MasterClock();

    // ClockDivider implementation
    double rateInHz();

    // Get the CurrentTicks of the output
    uint64_t currentTicks();
};


} // namespace sg

sg::ComponentFactory *MasterClock_GetFactory();
sg::ComponentFactory *ClockDivider_GetFactory();
sg::ComponentFactory *ClockTimer_GetFactory();
sg::ComponentFactory *ClockTimer64_GetFactory();
sg::ComponentFactory *AsyncSignal_GetFactory();

#endif // ARM_SG_SCHEDULER_H
