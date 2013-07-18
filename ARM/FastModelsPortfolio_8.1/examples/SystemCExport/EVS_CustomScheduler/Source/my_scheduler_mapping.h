/*
 * my_scheduler_mapping.h - custom dummy scheduler mapping (using the default
 * scheduler mapping)
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef MY_SCHEDULER_MAPPING_H
#define MY_SCHEDULER_MAPPING_H

/* Includes */
#include <sg/SGSchedulerInterfaceForComponents.h>
#include <eslapi/CAInterfaceRegistry.h>

/* Custom implementation of the scheduler adapter */
class my_scheduler_mapping: public sg::SchedulerInterfaceForComponents {
public:
    /* Constructor and destructor */
    explicit my_scheduler_mapping(sg::SchedulerInterfaceForComponents *);
    ~my_scheduler_mapping();

    /* sg::SchedulerInterfaceForComponents implementation (mostly forwarding to
     * the default implementation) */
    virtual eslapi::CAInterface *ObtainInterface(eslapi::if_name_t ifName, eslapi::if_rev_t minRev, eslapi::if_rev_t *actualRev);        
    virtual sg::Timer* createTimer(const char* name, sg::TimerCallback *callback);
    virtual sg::SchedulerThread *createThread(const char* name, sg::SchedulerRunnable *runnable);
    virtual sg::ThreadSignal* createThreadSignal(const char* name);
    virtual void wait(sg::ticks_t ticks, sg::FrequencySource *timebase);
    virtual void wait(sg::ThreadSignal *threadSignal);
    virtual void setGlobalQuantum(sg::ticks_t ticks, sg::FrequencySource *timebase);
    virtual double getGlobalQuantum();
    virtual void addSynchronisationPoint(sg::ticks_t ticks, sg::FrequencySource *timebase);
    virtual double getNextSyncPoint();
    virtual void addCallback(sg::SchedulerCallback *callback);
    virtual void removeCallback(sg::SchedulerCallback *callback);
    virtual double getCurrentSimulatedTime();
    virtual double getCurrentLocalTime();
    virtual void setCurrentLocalTime(sg::ticks_t ticks, sg::FrequencySource *timebase);
    virtual void stopRequest();
    virtual void stopAcknowledge(sg::SchedulerRunnable *runnable);

    /* Private data */
private:    
    sg::SchedulerInterfaceForComponents * default_scheduler_mapping;
        /* we use the default implementation of the scheduler mapping just to
         * keep the example simple */
    eslapi::CAInterfaceRegistry schedulerInterfaceRegistry;
        /* scheduler interface registry for a convenient implementation of
         * ObtainInterface() */
};

#endif

