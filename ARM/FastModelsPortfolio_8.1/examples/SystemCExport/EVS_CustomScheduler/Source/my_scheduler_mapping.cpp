/*
 * my_scheduler_mapping.cpp - custom dummy scheduler mapping (using the default scheduler mapping)
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include <cstdio>

#include <scx/scx.h>

#include "my_scheduler_mapping.h"

/* Constructor and destructor */
my_scheduler_mapping::my_scheduler_mapping(sg::SchedulerInterfaceForComponents *default_scheduler_mapping_): 
default_scheduler_mapping(default_scheduler_mapping_),
schedulerInterfaceRegistry("my_scheduler_mapping::schedulerInterfaceRegistry", false)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "my_scheduler_mapping()");
    // register SchedulerInterfaceForComponents
    schedulerInterfaceRegistry.RegisterInterface(sg::SchedulerInterfaceForComponents::IFNAME(),
                                                 sg::SchedulerInterfaceForComponents::IFREVISION(),
                                                 static_cast<sg::SchedulerInterfaceForComponents*>(this));
}

my_scheduler_mapping::~my_scheduler_mapping()
{
    SCX_REPORT_INFO("my_scheduler_mapping", "~my_scheduler_mapping()");
}

/* sg::SchedulerInterfaceForComponents implementation (mostly forwarding to the
 * default implementation) */
eslapi::CAInterface *my_scheduler_mapping::ObtainInterface(eslapi::if_name_t ifName, eslapi::if_rev_t minRev, eslapi::if_rev_t *actualRev)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "ObtainInterface(ifName='%s')", ifName);
    return schedulerInterfaceRegistry.ObtainInterface(ifName, minRev, actualRev);
}

sg::Timer* my_scheduler_mapping::createTimer(const char* name, sg::TimerCallback *callback)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "createTimer(name='%s')", name);
    return default_scheduler_mapping->createTimer(name, callback);
}

sg::SchedulerThread *my_scheduler_mapping::createThread(const char* name, sg::SchedulerRunnable *runnable)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "createThread(name='%s')", name);
    return default_scheduler_mapping->createThread(name, runnable);
}

sg::ThreadSignal* my_scheduler_mapping::createThreadSignal(const char* name)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "createThreadSignal(name='%s')", name);
    return default_scheduler_mapping->createThreadSignal(name);
}

/* Example: Print verbose message for each wait() */
void my_scheduler_mapping::wait(sg::ticks_t ticks, sg::FrequencySource *timebase)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "wait(ticks=%llu)", (unsigned long long) ticks);
    default_scheduler_mapping->wait(ticks, timebase);
}

void my_scheduler_mapping::wait(sg::ThreadSignal *threadSignal)
{
    default_scheduler_mapping->wait(threadSignal);
}

void my_scheduler_mapping::setGlobalQuantum(sg::ticks_t ticks, sg::FrequencySource *timebase)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "setGlobalQuantum(ticks=%llu)", (unsigned long long) ticks);
    default_scheduler_mapping->setGlobalQuantum(ticks, timebase);
}

double my_scheduler_mapping::getGlobalQuantum()
{
    SCX_REPORT_INFO("my_scheduler_mapping", "getGlobalQuantum()");
    return default_scheduler_mapping->getGlobalQuantum();
}

void my_scheduler_mapping::addSynchronisationPoint(sg::ticks_t ticks, sg::FrequencySource *timebase)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "addSynchronisationPoint(ticks=%llu)", (unsigned long long) ticks);
    default_scheduler_mapping->addSynchronisationPoint(ticks, timebase);
}

double my_scheduler_mapping::getNextSyncPoint()
{
    SCX_REPORT_INFO("my_scheduler_mapping", "getGlobalQuantum()");
    return default_scheduler_mapping->getNextSyncPoint();
}

void my_scheduler_mapping::addCallback(sg::SchedulerCallback *callback)
{
    default_scheduler_mapping->addCallback(callback);
}

void my_scheduler_mapping::removeCallback(sg::SchedulerCallback *callback)
{
    default_scheduler_mapping->removeCallback(callback);
}

double my_scheduler_mapping::getCurrentSimulatedTime()
{
    SCX_REPORT_INFO("my_scheduler_mapping", "getCurrentSimulatedTime()");
    return default_scheduler_mapping->getCurrentSimulatedTime();
}

double my_scheduler_mapping::getCurrentLocalTime()
{
    SCX_REPORT_INFO("my_scheduler_mapping", "getCurrentLocalTime()");
    return default_scheduler_mapping->getCurrentLocalTime();
}

void my_scheduler_mapping::setCurrentLocalTime(sg::ticks_t ticks, sg::FrequencySource *timebase)
{
    SCX_REPORT_INFO("my_scheduler_mapping", "setCurrentLocalTime(ticks=%llu)", (unsigned long long) ticks);
    default_scheduler_mapping->setCurrentLocalTime(ticks, timebase);
}

void my_scheduler_mapping::stopRequest()
{
    SCX_REPORT_INFO("my_scheduler_mapping", "stopRequest()");
    default_scheduler_mapping->stopRequest();
}

void my_scheduler_mapping::stopAcknowledge(sg::SchedulerRunnable *runnable)
{
    default_scheduler_mapping->stopAcknowledge(runnable);
}

