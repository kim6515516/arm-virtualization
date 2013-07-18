/*!
 * \file    PVBusCache.h
 * \brief   Constants used by PVBusCache API
 * \date    Copyright 2009 ARM Limited. All rights reserved.
 *
 * This defines constants that are private, subject to change and that should
 * not be used outside of PL310 model.
 */

#ifndef PVBUSCACHE_H
#define PVBUSCACHE_H

namespace pv {

// Static constants
enum {
    MAX_CACHE_INPUTS = 4,  //! Maximum number of PVBus input ports
    MAX_CACHE_OUTPUTS = 4  //! Maximum number of PVBus output ports.
};

//! Control which types of access to revoke hitLine status from.
enum CacheRevocation {
    REVOKE_READ_HIT,       //!< Stop reads from hitting a line.
    REVOKE_WRITE_HIT,      //!< Stop writes from hitting a line.
    REVOKE_READ_WRITE_HIT, //!< Stop any accesses from hitting a line.
};

//! Allow the cache to control how a transaction is routed.
enum CacheRoutingDecision {
    ROUTE_TO_BUS_OUT_0 = 0,
    ROUTE_TO_BUS_OUT_1 = 1,
    ROUTE_TO_BUS_OUT_2 = 2,
    ROUTE_TO_BUS_OUT_3 = 3,
    HANDLE_IN_CACHE = -1
};

}
#endif // PVBUSCACHE_H
