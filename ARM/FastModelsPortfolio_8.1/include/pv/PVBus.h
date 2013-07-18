 /*!
 * \file    PVBus.h
 * \brief   Port interface bus communication between core and devices.
 * \date    Copyright 2005-2009 ARM Limited. All rights reserved.
 *
 */

#ifndef PVBUS_H
#define PVBUS_H

#include "pv/PVBusAddr.h"
#include "pv/PVTransaction.h"

#include "sg/SGPort.h"

namespace DVM
{
    class UpstreamVisitor;
    class DownstreamVisitor;
}
namespace pv
{
    class PrefetchOnlyReadTransaction;
    class PrefetchOnlyWriteTransaction;
    template <typename Direction> class DownstreamRequest;
    typedef DownstreamRequest<AccessRead> ReadRequest;
    typedef DownstreamRequest<AccessWrite> WriteRequest;
}

namespace ACE
{
    class SnoopRequest;
}

namespace pv {

/*! Basic I/O functions, used for communicating with a memory-mapped device. */
// Warning: Keep the interface and default behaviors in sync with PVDeviceProtocol.lisa
class Device : public sg::Port
{
 public:
    //! Ask the bus to perform a read transaction.
    declare_slave_behaviour(read, Tx_Result (ReadTransaction tx));

    //! Ask the bus to perform a write transaction.
    declare_slave_behaviour(write, Tx_Result (WriteTransaction tx));

    //! Ask the bus to perform a debug read transaction.
    declare_slave_behaviour(debugRead, Tx_Result (ReadTransaction tx));

    //! Ask the bus to perform a debug write transaction.
    declare_slave_behaviour(debugWrite, Tx_Result (WriteTransaction tx));

    /// PVBusSlave guarantees to us that for any particular memory address that
    /// it will always give us the same RevokeTransaction if that range has been
    /// previously prefetched but not revoked.  This guarantee means that for
    /// any address range that has returned a prefetch range, it need only store
    /// a single RevokeTransaction* for that range.  It may give the same
    /// RevokeTransaction to more than one address range.  When the device
    /// wishes to revoke a particular prefetch request then it should deliver
    /// the RevokeTransaction and the bus range that it responded to.  It should
    /// give the _exact_ bus range that it responded with and not expand the
    /// range or contract it.
    ///
    /// On a related note, masters _may_ make "prefetch only" requests that
    /// appear on the read() and write() methods.  However, you must register
    /// yourself as capable of dealing with them to receive them.  You do this
    /// by calling configure() on the PVBusSlave.
    declare_master_behaviour(revokePrefetch,   void (RevokeTransaction* tx, pv::range_t<pv::bus_addr_t> range));

    pv::Tx_Result default_debugRead(pv::ReadTransaction tx)
    {
        return tx.generateAbort();
    }
    
    pv::Tx_Result default_debugWrite(pv::WriteTransaction tx)
    {
        return tx.generateAbort();
    }

    Device() {
        define_behaviour(read);
        define_behaviour(write);
        define_behaviour(debugRead);
        define_behaviour(debugWrite);
        define_behaviour(revokePrefetch);

        // default behaviors of unimplemented debug accesses functions cause aborts
        // (resulting in CADI_STATUS_GeneralError on the debug interface)
//        debugRead.bind_default_behaviour( this, &Device::default_debugRead);
//        debugWrite.bind_default_behaviour( this, &Device::default_debugWrite);
    }
};


/*! The PVBus is only used for internal communication between PVBus
 *  components.
 */
// Warning: Keep the interface and default behaviors in sync with PVBusProtocol.lisa
class Bus : public sg::Port
{
 public:
    //! Ask the bus to perform a read transaction.
    declare_slave_behaviour(read, Tx_Result (ReadTransaction tx));

    //! Ask the bus to perform a write transaction.
    declare_slave_behaviour(write, Tx_Result (WriteTransaction tx));

    //! Ask the bus to perform a debug read transaction.
    declare_slave_behaviour(debugRead, Tx_Result (ReadTransaction tx));

    //! Ask the bus to perform a debug write transaction.
    declare_slave_behaviour(debugWrite, Tx_Result (WriteTransaction tx));

    //! A device on the bus is about to change its physical mapping.
    declare_master_behaviour(busMapChanging, void (bus_addr_t base, bus_addr_t size));

    //! A device on the bus has completed changing its physical mapping.
    declare_master_behaviour(busMapChanged, void (bus_addr_t base, bus_addr_t size));

    //! A DVM recipient discovery protocol.
    declare_slave_behaviour(discoverDownstreamChildDVMNodes, void(DVM::DownstreamVisitor*));

    //! A DVM recipient discovery protocol.
    declare_master_behaviour(discoverUpstreamParentDVMNodes, void(DVM::UpstreamVisitor*));

    //! Support a coherency request from downstream.
    declare_master_behaviour(aceSnoopRequest, void(ACE::SnoopRequest*));
    declare_master_behaviour(debugACESnoopRequest, void(ACE::SnoopRequest*));

    //! PVBus re-entrant channels support
    declare_slave_behaviour(doReadAccess, Tx_Result(ReadRequest *));
    declare_slave_behaviour(doWriteAccess, Tx_Result(WriteRequest *));

    pv::Tx_Result default_debugRead(pv::ReadTransaction tx)
    {
        return tx.generateAbort();
    }
    
    pv::Tx_Result default_debugWrite(pv::WriteTransaction tx)
    {
        return tx.generateAbort();
    }

    Bus() {
        define_behaviour(read);
        define_behaviour(write);
        define_behaviour(debugRead);
        define_behaviour(debugWrite);
        define_behaviour(busMapChanging);
        define_behaviour(busMapChanged);
        define_behaviour(discoverDownstreamChildDVMNodes);
        define_behaviour(discoverUpstreamParentDVMNodes);
        define_behaviour(aceSnoopRequest);
        define_behaviour(debugACESnoopRequest);
        define_behaviour(doReadAccess);
        define_behaviour(doWriteAccess);

        // default behaviors of unimplemented debug accesses functions cause aborts
        // (resulting in CADI_STATUS_GeneralError on the debug interface)
//        debugRead.bind_default_behaviour( this, &Bus::default_debugRead);
//        debugWrite.bind_default_behaviour( this, &Bus::default_debugWrite);
    }

    //! Helper function for bus masters to perform a channel access.
    template <typename D> Tx_Result doAccess(DownstreamRequest<D> *);
};

} // namespace pv

#endif // PVBUS_H
