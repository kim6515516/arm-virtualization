/*! \file PrefetchRange.h
 *  \brief Type for handling ranges of prefetchable memory.
 *  \date Copyright 2011 ARM Limited. All rights reserved.
 */

#ifndef PV_PREFETCHRANGE_H
#define PV_PREFETCHRANGE_H

#include <assert.h>
#include <list>

#include "sg/SGstdint.h"
#include "pv/RemapRange.h"
#include "pv/PVBusAddr.h"
#include "pv/AccessDirection.h"

namespace pv
{

/*! A type that encapsulates a prefetch pointer for accessing a range of addresses. */
template <typename AccessDirection_>
class PrefetchRange
{
    typedef AccessDirection_ AccessDirection;
private:
    typedef typename AccessDirection::slave_buffer_ptr slave_buffer_ptr;
    typedef typename AccessDirection::slave_u8_ptr slave_u8_ptr;

    slave_u8_ptr prefetch_pointer;
    bus_range_t    prefetch_range;

public:
    /*! Default constructor creates an invalid prefetch range. */
    PrefetchRange()
    : prefetch_pointer(0)
    , prefetch_range(bus_range_t::make_empty())
    {
    }

    /*! Construct a prefetch pointer for direct memory access to any byte address within the given range.
     *  The range can be empty, in which case this represents an "invalid"
     *  prefetch range, and the prefetch-pointer must be NULL.
     *  If the range is non-empty, the prefetch pointer can be NULL, indicating a range
     *  that is definitely not prefetchable at the moment.
     */
    PrefetchRange(slave_buffer_ptr prefetch_pointer_, bus_range_t prefetch_range_)
    : prefetch_pointer(slave_u8_ptr(prefetch_pointer_))
    , prefetch_range(prefetch_range_)
    {
        // Don't allow a non-zero prefetch pointer if not valid.
        assert(prefetch_pointer == 0 || isValid());
    }
    
    /*! Convert a prefetch range in the destination's address space back into the
     *  address space of the source, narrowing it to the range covered by the mapping.
     */
    PrefetchRange unmap(bus_remap_range_t mapping) {
        // Narrow our prefetch range to the destination size of the mapping
        PrefetchRange windowed_target_range = this->intersection_with(mapping.destination_range);
        
        // Transform the bus address range back into the source space of the mapping.
        bus_range_t source_range = mapping.unmap(windowed_target_range.prefetch_range);
        return PrefetchRange(windowed_target_range.prefetch_pointer,
                             source_range);
    }

    /*! Compute a PrefetchRange that is the intersection of ourselves with
     *  a given range, adjusting the prefetch_pointer as necessary.
     */
    PrefetchRange intersection_with(bus_range_t range) {
        bus_range_t intersection = prefetch_range.intersection_with(range);
        slave_u8_ptr windowed_prefetch_pointer = 0;
        if (prefetch_pointer != 0) {
            assert(intersection.begin >= prefetch_range.begin);
            windowed_prefetch_pointer = prefetch_pointer + (intersection.begin - prefetch_range.begin);
        }
        PrefetchRange output(windowed_prefetch_pointer, intersection);
        return output;
    }

    /*! True if this represents a valid prefetch range. */
    bool isValid() { return !prefetch_range.empty(); }

    /*! True if this range covers the given byte address. */
    bool contains(bus_addr_t addr) { return prefetch_range.contains(addr); }

    /*! Get the pointer to the storage for the start of the range.
     *  This pointer must only be used to access offsets within the
     *  size of the range (and must not be used at all if the range
     *  is empty.
     */
    slave_buffer_ptr getPointer() { return prefetch_pointer; }

    /*! Get a pointer to the storage location for the given address.
     *  Precondition: addr must be within the prefetch_range.
     */
    slave_buffer_ptr pointerFor(bus_addr_t addr) {
        assert(prefetch_range.contains(addr));
        if (prefetch_pointer == 0) {
            return 0;
        }
        return prefetch_pointer + prefetch_range.offset_of(addr);
    }

    /*! Get the range of addresses covered by this prefetch pointer. */
    bus_range_t    getRange()   { return prefetch_range; }
};

}

#endif // PV_PREFETCHRANGE_H
