 /*!
 * \file    PVBusAddr.h
 * \brief   Type-definition for bus addresses.
 * \date    Copyright 2005-2009 ARM Limited. All rights reserved.
 *
 */

#ifndef PVBUSADDR_H
#define PVBUSADDR_H

#include "sg/SGstdint.h"
#include <cassert>

namespace pv {

typedef uint64_t bus_addr_t;

// an address with the top bit set is deemed to be invalid
// an enum would be better but enums may only be 32 bit on some platforms
#define INVALID_BUS_ADDRESS 0x1000000000000000ULL

//! Total address space that can be handled by PVBus infrastructure.
#define PVBUS_ADDRESS_RANGE (1ULL << 43)

//! check whether an address is deemed to be valid
inline bool isValidAddress(pv::bus_addr_t addr) { return (addr & INVALID_BUS_ADDRESS) == 0; }

// return an invalid address
inline pv::bus_addr_t invalidAddress() { return INVALID_BUS_ADDRESS; }

    ///
    /// Is the argument t_ aligned to the unit_size_ (which must be a power of two)?
    ///
    template< typename T, typename U >
    inline bool is_aligned_to( T t_, U unit_size_ )
    {
        // Assert that unit_size_ must be a power of two.
        assert( T(unit_size_ & (T(0) - unit_size_)) == T(unit_size_) );
        return T(t_ & (unit_size_ - 1)) == 0;
    }

    ///
    /// Align a type t_ to the unit size specified, which must be a power of two.
    ///
    /// This this can be used to align an address (down) to the nearest power of
    /// two boundary.
    ///
    template< typename T, typename U >
    inline T align_to( T t_, U unit_size_ )
    {
        assert( T(unit_size_ & (T(0) - unit_size_)) == T(unit_size_) );
        T const ret = t_ & T(~T(unit_size_ - 1));
        assert( is_aligned_to( ret, unit_size_ ) );
        assert( (t_ - ret) < T(unit_size_) );
        return ret;
    }

}

#endif
