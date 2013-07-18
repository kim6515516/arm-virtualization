/*!
 * \file    SGSchedulerTestInterface.h
 * \brief   Abstract interface used by the scheduler test framework to test the standalone scheduler.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

#ifndef SGSCHEDULERTESTINTERFACE_H
#define SGSCHEDULERTESTINTERFACE_H

#include "eslapi/CAInterface.h"
#include "sg/SGstdint.h"
#include "sg/SGTicks.h"

namespace sg
{
    /*! SchedulerTestInterface:
     * This interface is used by the test framework to test the standalone scheduler.
     */
    class SchedulerTestInterface: public eslapi::CAInterface
    {
    public:
        // CAInterface related stuff
        static eslapi::if_name_t IFNAME() { return "sg.SchedulerTestInterface"; }
        static eslapi::if_rev_t IFREVISION() { return 0; }
        virtual eslapi::CAInterface *ObtainInterface(eslapi::if_name_t ifName, eslapi::if_rev_t minRev, eslapi::if_rev_t *actualRev) = 0;
        
        // --- main interface, used by the scheduler test framework to test the standalone scheduler ---

        /*! Return the total number of ticks of the internal monotonic clock. */
        virtual ticks_t currentTicks() = 0;

        /*! Returns true if scheduler is running */
        virtual bool isRunning() = 0;
        
        /*! Returns true if and only if at least one timer is scheduled to be run. */
        virtual bool getTimersRemaining() = 0;
        
        /*! Reset internal monotonic tick count to zero. */
        virtual void reset() = 0;
        
    protected:        
        /*! Protected virtual destructor: Do not allow to destroy instances through this interface. */
        virtual ~SchedulerTestInterface() {}
    };
} // namespace sg

#endif
