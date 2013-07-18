/**
 * \file    PVBus/include/pv/ExclusiveLockMaster.h
 * \brief   Interface for masters that want to own their exclusive locks.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 */

#ifndef PVBUS_INCLUDE_PV_EXCLUSIVELOCKMASTER_H
#define PVBUS_INCLUDE_PV_EXCLUSIVELOCKMASTER_H

#include <pv/PVBusAddr.h>

namespace pv
{
    class ExclusiveLockSlave;

    /**
     * Callback interface on the owner of an exclusive lock in some ExclusiveLockSlave.  This
     * interface allows the slave to communicate that a lock has been obtained or lost.
     */
    class ExclusiveLockMaster
    {
    public:
        /**
         * Called by the slave to indicate that the master has obtained an exclusive lock in that slave.
         *
         * \param[in] slave         The slave that contains the lock.
         * \param[in] base_address  The base address of the locked region, as seen by the slave.
         * \param[in] length_bytes  The length of the locked region in bytes.
         */
        virtual void lockObtained(ExclusiveLockSlave *slave, bus_addr_t base_address, bus_addr_t length_bytes) = 0;

        /**
         * Called by the slave to notify the master that the exclusive lock has been lost.
         *
         * \param[in] slave         The slave that contained the lock.
         * \param[in] base_address  The base address of the locked region, as seen by the slave.
         * \param[in] length_bytes  The length of the locked region in bytes.
         */
        virtual void lockLost(ExclusiveLockSlave *slave, bus_addr_t base_address, bus_addr_t length_bytes) = 0;

        /**
         * Optional method which allows a master to indicate the physical address against which the _next_
         * acquired lock will be tagged (modulo some alignment based on the granule)
         *
         * This is _only_ used for tracing
         *
         * NOTE: this API precludes the use of two outstanding exclusive monitor as there is
         *       no way to disambiguate the incoming lockObtained calls
         */
        virtual void prepareLock(bus_addr_t paddr) {}

        // This interface is somewhat restricted in that it only supports a single monitor per master
        // but is sufficient for now

        // extract information about the current exclusive state
        virtual bool isExclusive() const = 0;
        virtual uint64_t getExclusiveAddress() const = 0;
        virtual uint64_t getExclusiveExtent() const = 0;


        virtual ~ExclusiveLockMaster() { }
    };

} // namespace pv

#endif // PVBUS_INCLUDE_PV_EXCLUSIVELOCKMASTER_H
