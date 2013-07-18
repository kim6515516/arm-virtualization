#ifndef REMAP_RANGE_H
#define REMAP_RANGE_H

#include "pv/PVRange.h"
#include "pv/PVBusAddr.h"

#include <limits>
#include <iostream>

namespace pv
{

/** Represents a 1:1 mapping of a contiguous range of addresses
 *  from a source address range to a destination address range.
 *
 *  The two ranges must be of identical sizes.
 */
template <typename T>
class remap_range_t
{
    typedef remap_range_t<T> Self;
    typedef sg::range_t<T> range_t;
    typedef sg::range_t_traits<T> traits_t;
    typedef typename traits_t::size_type size_type;

    void validate()
    {
        assert((source_range.empty() && destination_range.empty())
               || (source_range.full() && destination_range.full()) // we can't call size() if the full size is
                                                                    // not representable in the range type.
               || (source_range.size() == destination_range.size()) );
    }

public:
    range_t source_range;  //!< Range of addresses mapped by this remapping
    range_t destination_range; //!< Remapped range for addresses.

    /*! Construct an empty mapping. */
    remap_range_t() :
        source_range(range_empty<T>()),
        destination_range(range_empty<T>())
    {
    }

    /*! Copy constructor. */
    remap_range_t(Self const& src) :
        source_range(src.source_range),
        destination_range(src.destination_range)
    {
        validate();
    }

    /*! Construct a mapping between two address ranges of identical size.
     */
    remap_range_t(range_t source, range_t destination) :
        source_range(source),
        destination_range(destination)
    {
        validate();
    }
    
    /*! Construct a mapping between two address ranges of identical size.
     */
    remap_range_t(std::pair<range_t,range_t> source_destination_) :
        source_range(source_destination_.first),
        destination_range(source_destination_.second)
    {
        validate();
    }

    /*! Construct a flat 1:1 mapping for a range of addresses. */
    remap_range_t(range_t source) :
        source_range(source),
        destination_range(source)
    {
        validate();
    }

    /*! Construct a flat 1:1 mapping for the full address range. */
    static remap_range_t create_full_range_flat_mapping()
    {
        return remap_range_t(
            pv::range_begin_end_incl(traits_t::begin_for_full_range(),
                                     traits_t::end_incl_for_full_range()));
    }

    /*! Does this mapping cover an empty range of addresses? */
    bool empty()
    {
        return source_range.empty();
    }

    /*! Is the given address in the source address range. */
    bool covers(T const &a) const {
        return source_range.contains(a);
    }


    /*! Map the given address into the destination address range. */
    T remap(T const &in) const {
        assert(covers(in));
        return priv_remap(in);
    }

    /*! Remap a range of address into the destination address range.
     *  The entire range must be covered by this mapping.
     */
    range_t remap(range_t const &in) const {
        range_t output;
        output.begin = remap(in.begin);
        output.end_incl = remap(in.end_incl);
        return output;
    }
    
    /*! Remap a range of address into the destination address range.
     *  The range can be a different size to the mapping that we
     *  support, in which case the range is truncated.
     *  The return result is a subset of the input range (first)
     *  that is mapped onto a subset of the output range (second)
     */
    std::pair<range_t,range_t>
    remap_different_sized_range(range_t const &in) const {
        range_t input_intersection = in.intersection_with(source_range);
        range_t output;
        output.begin    = priv_remap(input_intersection.begin);
        output.end_incl = priv_remap(input_intersection.end_incl);
        assert(input_intersection.size() == output.size());
        return std::make_pair(input_intersection, output);
    }

    /*! Reverse map an address from the destination address range to the source range. */
    T unmap(T const &destination_address) const {
        assert(destination_range.contains(destination_address));
        return (destination_address - destination_range.begin) + source_range.begin;
    }

    /*! Unmap a range of address into the source address range.
     *  The entire range must be covered by the destination of this mapping.
     */
    range_t unmap(range_t const &destination_address_range) const {
        range_t output;
        output.begin = unmap(destination_address_range.begin);
        output.end_incl = unmap(destination_address_range.end_incl);
        return output;
    }

    /*! Unmap a range of address from the destination address range
     *  to the source range.
     *  The range can be a different size to the mapping that we
     *  support, in which case the range is truncated.
     *  The return result is a subset of the input range (first)
     *  that is mapped onto a subset of the output range (second)
     */
    std::pair<range_t,range_t>
    unmap_different_sized_range(range_t const &out) const {
        range_t output_intersection = out.intersection_with(destination_range);
        if (output_intersection.empty())
            return std::make_pair( range_t::make_empty(), range_t::make_empty() );
        range_t input;
        input.begin    = unmap(output_intersection.begin);
        input.end_incl = unmap(output_intersection.end_incl);
        assert(output_intersection.size() == input.size());
        return std::make_pair(input, output_intersection);
    }

    /*! Compose a new mapping that has the effect of applying
     *  the given mapping to the output of this mapping.
     *  ie. this->andThen(second_mapping)->remap(x) == second_mapping->remap(this->remap(x))
     *  The resulting mapping will cover range of addresses whose size
     *  is the intersection of the address range that "this" maps to and
     *  the address range that "second_mapping" maps from.
     */
    Self andThen(Self const &second_mapping) const {
        // Find the intersection of ranges of intermediate addresses -
        // the output of this mapping and the input of the second mapping.
        range_t intermediate_window = destination_range.intersection_with(second_mapping.source_range);

        Self output;

        // The source range of the new mapping will be the results of
        // reverse-applying this to intermediate_window.
        output.source_range = unmap(intermediate_window);

        // Similarly, the destination range is the result of applying
        // second_mapping to intermediate_window.
        output.destination_range = second_mapping.remap(intermediate_window);

        // Confirm that source and destination ranges match.
        output.validate();

        return output;
    }

private:
    
    /*! Map the given address into the destination address range. */
    T priv_remap(T const &in) const {
        return (in - source_range.begin) + destination_range.begin;
    }

};

template <typename T>
inline std::ostream& operator << (std::ostream & os, remap_range_t<T> t)
{
    return os << t.source_range << " -> " << t.destination_range;
}

/*! Convenient typename for remap ranges over bus-addresses. */
typedef remap_range_t<bus_addr_t> bus_remap_range_t;

} // namespace pv
#endif
