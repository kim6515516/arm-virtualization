 /*!
  * \file    PVBusSlave.h
  * \brief   Port interface bus communication between core and devices.
  * \date    Copyright 2005-2008 ARM Limited. All rights reserved.
  *
  *  A full slave implementation of the PVBus protocol, providing the
  *  hooks needed to allow a bus master to have fast access to a device,
  *  bypassing any bus decoders.
  *
  *  The bus slave implements a block of addressable device memory,
  *  which can be partitioned into ranges with different behaviors,
  *  either passing on transactions to a slave port, or implementing
  *  them as accesses to memory storage - which can be provided by the
  *  BusSlave or by its owner.
  */

#ifndef PVBUSSLAVE_H
#define PVBUSSLAVE_H

#include "sg/SGstdint.h"

#include "sg/SGComponent.h"
#include "sg/SGPort.h"

#include "pv/PVBusAddr.h"
#include "pv/PVAccessWidth.h"
#include "pv/ACE.h"

namespace pv {

    class slave_config_t;

/*! Ranges of storage can be configured as either MEMORY or DEVICE.
 *  Accesses to MEMORY will handled directly by the MemoryBusSlave;
 *  Accesses to DEVICE memory will be passed to the read()/write()
 *  on the bus, which should be implemented by the component that
 *  owns the MemoryBusSlave.
 *  All accesses to ABORT regions will generate data aborts.
 *  All accesses to IGNORE regions will do nothing (reads return 0).
 *
 *  ACCESSMODE_TRACKED_MEMORY (currently experimental for v8 FS3)
 *  behaves like MEMORY but keeps an additional bitmap to track
 *  which bytes have not yet been written to, and are UNKNOWN
 *  when read.
 *  It is impossible to prefetch into this region until PVBus masters
 *  are capable of accessing and writing to the UNKNOWN bitmap
 */
enum accessMode { ACCESSMODE_MEMORY,
                  ACCESSMODE_DEVICE,
                  ACCESSMODE_ABORT,
                  ACCESSMODE_IGNORE,
                  ACCESSMODE_TRACKED_MEMORY};

/*! The accessMode can be set independently for read accesses and
 *  write accesses.
 */
enum accessType { ACCESSTYPE_READ,
                  ACCESSTYPE_WRITE,
                  ACCESSTYPE_RW };


class BusSlaveControl : public sg::Port {
 public:
    /*! Set the fill pattern used for uninitialised memory.
     *  This consists of two alternating words.
     *  Note that this won't affect any pages that have already been
     *  accessed, so ideally it should be called at startup time.
     */
    declare_slave_behaviour(setFillPattern,
                            void (uint32_t fill1, uint32_t fill2));

    /*! Control whether accesses are routed to storage or to device I/O. */
    declare_slave_behaviour(setAccess,
                           void (bus_addr_t base, bus_addr_t top,
                                 accessType type, accessMode mode));

    /*! Get pointer to read from a region of underlying storage.
     *
     *  Dereferencing the returned value will yield the byte at the
     *  requested address.  If address is aligned, the returned pointer
     *  can be cast to a uint32_t* to read a word of data (which may need
     *  to be byte-reversed if host and target endianness differ).
     *
     *  Storage is arranged in pages.  The returned pointer is valid for
     *  any address within the page.  If the limit parameter is not NULL,
     *  the upper address limit will be stored in the location pointed to.
     *  This is the first address above the page containing the requested
     *  address.
     *
     *  The returned pointer is not guaranteed to remain valid indefinitely.
     *  The caller should not cache the pointer value while the simulation
     *  is running.
     */
    declare_slave_behaviour(getReadStorage,
                            uint8_t const * (bus_addr_t address,
                                             bus_addr_t *limit));

    /*! Return a pointer to underlying storage, as for getReadStorage().
     *  The MemoryBusSlave will revoke access for any other users of the
     *  device, so that they are forced to re-read the memory contents.
     */
    declare_slave_behaviour(getWriteStorage,
                            uint8_t * (bus_addr_t address,
                                       bus_addr_t *limit));

    /*! Allow the client to provide a region of contiguous read-only memory
     *  that will be used to satisfy read requests within the given address
     *  range.  (Memory writes will still go to the original storage space).
     */
    declare_slave_behaviour(provideReadStorage,
                            void (bus_addr_t device_base, bus_addr_t device_limit,
                                  uint8_t const *storage));

    /*! Allow the client to provide a region of contiguous write-only memory
     *  that will be used to satisfy write requests within the given address
     *  range.  (Memory read will still go to the original storage space).
     */
    declare_slave_behaviour(provideWriteStorage,
                            void (bus_addr_t device_base, bus_addr_t device_limit,
                                  uint8_t *storage));

    /*! Allow the client to provide a region of contiguous memory that will
     *  be used to satisfy all memory accesses within the given address
     *  range.
     */
    declare_slave_behaviour(provideReadWriteStorage,
                            void (bus_addr_t device_base, bus_addr_t device_limit,
                                  uint8_t *storage));

    /*! Tell the PVBusSlave about our ACE configuration
     */
    declare_slave_behaviour( configure, void (slave_config_t*) );


    BusSlaveControl() {
        define_behaviour(setFillPattern);
        define_behaviour(setAccess);
        define_behaviour(getReadStorage);
        define_behaviour(getWriteStorage);
        define_behaviour(provideReadStorage);
        define_behaviour(provideWriteStorage);
        define_behaviour(provideReadWriteStorage);
        define_behaviour(configure);
    }
};

    class slave_config_t
    {
    private:
        unsigned bitmap_of_accepted_ace_operations;

    public:
        /// Default constructor accepts:
        ///    - ReadNoSnoop
        ///    - ReadOnce
        ///    - ReadClean
        ///    - ReadShared
        ///    - ReadNotSharedDirty
        ///    - ReadUnique
        ///    - WriteNoSnoop
        ///    - PseudoWriteOnce
        ///    - WriteUnique
        ///    - WriteLineUnique
        ///    - WriteBack
        ///    - WriteClean
        ///    - Default
        ///    - DebugRead
        ///    - DebugWrite
        slave_config_t();

        bool is_acceptable_operation( ACE::ace_operation_t ace_operation_ ) const
        {
            return (bitmap_of_accepted_ace_operations & (1u << ace_operation_)) != 0;
        }

        /// Explicitly add acceptance of a single ace operation
        void acceptACE(ACE::ace_operation_t ace_operation_)
        {
            bitmap_of_accepted_ace_operations |= (1u << ace_operation_);
        }

        /// If the attached device slave can deal with prefetch only request
        /// then this should be set.
        bool     accepts_prefetch_only;

        /// Set if the attached device slave wants to handle exclusive requests
        bool     accepts_exclusive_requests;

        /// Set if the built-in global monitor should ignore non-exclusive stores
        bool     ignore_non_exclusive_stores_to_global_monitor;

        /// The address granularity of the global monitor built into PVBusSlave
        unsigned  exclusive_monitor_log2_granule_size;


        /// NOTE: This method is no longer supported, use....
        ///   - acceptACE_CleanShared_CleanInvalid_MakeInvalid()
        ///   - acceptACE_CleanUnique_MakeUnique()
        struct deliberate_error_disambiguate_with_ACE_ops_required;
        void acceptCacheMaintenance(deliberate_error_disambiguate_with_ACE_ops_required);

        /// Accept in addition ACE cache maintenance operations
        inline void acceptACE_CleanShared_CleanInvalid_MakeInvalid()
        {
            acceptACE(ACE::CleanShared);
            acceptACE(ACE::CleanInvalid);
            acceptACE(ACE::MakeInvalid);
        }

        /// Accept in addition ACE CleanUnique, MakeUnique
        inline void acceptACE_CleanUnique_MakeUnique()
        {
            acceptACE(ACE::CleanUnique);
            acceptACE(ACE::MakeUnique);
        }

        /// Accept in addition ACE Evict
        inline void acceptEvict()
        {
            acceptACE(ACE::Evict);
        }

        /// Accept in addition MemoryBarriers
        inline void acceptMemoryBarriers()
        {
            acceptACE(ACE::Memory_Barrier);
            acceptACE(ACE::SynchronisationBarrier);
        }

        /// Indicate that the attached device can accept prefetch only requests
        /// (the read/write transaction will be marked as isPrefetchOnly()).
        ///
        /// This is off by default as older slaves will not understand it.
        void acceptPrefetchOnly();

        /// Indicate that the attached device wants to handle exclusives,
        /// so bypass PVBusSlave's built-in handling.
        void acceptExclusiveTransactions();

        /// Indicate that built-in global monitor should not open
        /// a monitor if there is a non-exclusive store to the 
        /// monitored address. This behaviour is ImpDef in the ARM ARM
        void ignoreNonExclusiveStoresToGlobalMonitor();

        /// Sets the address granularity of the built-on global monitor
        /// the default is 0 (1 byte)
        void setLog2ExclusiveMonitorGranuleSize(unsigned log2_size);
    };

    typedef slave_config_t ace_config_t; // DEPRECATED use slave_config_t

} // namespace pv

#include "sg/SGFactory.h"

COMPONENT_FACTORY_DECL(PVBusSlave);

sg::ComponentBase *PVBusSlave_Create(
        std::string const &name,
        sg::SimulationContext *context,
        pv::bus_addr_t size = 1ULL<<32,
        pv::AccessWidth max_access_width = pv::ACCESS_64_BITS
);

#endif // PVBUSSLAVE_H
