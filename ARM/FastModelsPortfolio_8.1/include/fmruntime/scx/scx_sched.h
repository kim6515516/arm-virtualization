/*
 * SCX: scx_sched.h - SystemC eXport support: scheduling API.
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef ARM_SCX_SCHED__H
#define ARM_SCX_SCHED__H

/*!
 * \file    scx_sched.h
 * \brief   Scheduling API.
 * \date    Copyright 2011-2013 ARM Limited. All rights reserved.
 *
 * SystemC eXport support scheduling API.
 */

/* Includes */

/* Forwards */
namespace sg {
class SchedulerInterfaceForComponents;
}

/* Namespaces */

/*!
 * \brief   SystemC eXport support namespace.
 */
namespace scx {

/* Forwards */
class scx_simcontrol_if;

/* Functions */

/*!
 * \brief   Add a future synchronisation point in time.
 * \param   sync_time specifies the time of the future synchronisation point
 *          relative to the start of the current quantum. Measured in seconds.
 *
 * SystemC components call this function to provide a hint to the scheduler
 * implementation when a potentially useful system synchronisation point will
 * occur in the future.
 * The scheduler uses this information to determine the quantum size of threads
 * as they get scheduled.
 * Threads that already ran their quantum are unaffected, all other threads
 * (including the current thread) will run until the synchronisation point
 * specified by \a sync_time.
 *
 * Calling scx_sync() again will add another synchronisation point.
 *
 * Synchronisation points automatically vanish when the simulation time
 * reaches them.
 */
extern void
scx_sync(double sync_time);

/*!
 * \brief   Returns a pointer to a new instance of the default implementation 
 *          of the scheduler mapping provided with Fast Models.
 * \param   simcontrol Pointer to an already existing simulation controller.
 *          When this is \c NULL, this function returns \c NULL.
 */
extern sg::SchedulerInterfaceForComponents *
scx_create_default_scheduler_mapping(scx_simcontrol_if * simcontrol);

}   /* namespace scx */

#endif  /* defined(ARM_SCX_SCHED__H) */
