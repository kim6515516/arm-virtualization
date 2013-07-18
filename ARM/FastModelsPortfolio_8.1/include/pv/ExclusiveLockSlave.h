/**
 * \file    PVBus/include/pv/ExclusiveLockSlave.h
 * \brief   Interface for slaves that hold exclusive locks for their masters.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 */

#ifndef PVBUS_INCLUDE_PV_EXCLUSIVELOCKSLAVE_H
#define PVBUS_INCLUDE_PV_EXCLUSIVELOCKSLAVE_H

#include "pv/PVBusAddr.h"

namespace pv
{
    class ExclusiveLockMaster;

    /**
     * Callback interface on the holder of an exclusive lock for some ExclusiveLockMaster.  This
     * allows the master to identify the slave and to relinquish the lock if it chooses.
     */
    class ExclusiveLockSlave
    {
    public:
        /**
         * Called by the master to inform the slave that that master is no longer interested in the lock.
         *
         * \param[in] master        The master that owns the lock.
         * \param[in] base_address  The base address of the locked region, as seen by the slave.
         * \param[in] length_bytes  The length of the locked region in bytes.
         */
        virtual void releaseLock(ExclusiveLockMaster *master, bus_addr_t base_address, bus_addr_t length_bytes) = 0;

        virtual ~ExclusiveLockSlave() { }
    };

} // namespace pv

#endif // PVBUS_INCLUDE_PV_EXCLUSIVELOCKSLAVE_H
