/*!
 * \file    Range.h
 * \brief   A range type.
 * \date    Copyright 2010-2012 ARM Limited. All rights reserved.
 *
 *  This file is not part of a stable public API and it may
 *  change without notice.
 */

#ifndef SG_RANGE_H
#define SG_RANGE_H

#include <iostream>
#include <algorithm>
#include <cassert>
#include <limits>

namespace sg
{
    template< typename T > struct range_t;
    template< typename T > inline range_t<T> range_begin_end_incl( T begin_, T end_incl_ );
    template< typename T > inline range_t<T> range_empty();

    ///
    /// Subtracting two T may give a non-T, this allows a user to implement this
    /// functionality.
    ///
    template< typename T > struct range_t_traits
    {
        typedef T size_type;

        ///
        /// \name Members for use in creating an empty and full ranges.
        ///
        /// If asked to create an empty range then we need to create a T for
        /// such purposes, these functions construct such a T.
        ///
        //@{
        static T begin_for_empty()      { return 1; }
        static T end_incl_for_empty()   { return 0; }
        static T begin_for_full_range() { return (std::numeric_limits<T>::min)(); }
        static T end_incl_for_full_range() { return (std::numeric_limits<T>::max)(); }
        //@}

        // This is called within the size() method of the range (u_).  If
        // the range represents the full range then we cannot represent the
        // full size in the return result.  Prefer to assert fail!
        template<typename U>
        static void assert_size_not_full(U const& u_)
        {
            assert( ! u_.full() );
        }
    };

    ///
    /// Partial specialisation for pointers, the subtraction of two pointers yields a ptrdiff_t
    ///
    template< typename T > struct range_t_traits<T*>
    {
        typedef std::ptrdiff_t size_type;
        static T* begin_for_empty()    { return (T*)1; }
        static T* end_incl_for_empty() { return (T*)0; }

//        static T begin_for_full_range();        // NO! See comment for assert_size_not_full
//        static T end_incl_for_full_range();     // NO! See comment for assert_size_not_full
        
        // This is called within the size() method of the range (u_).  If
        // the range represents the full range then we cannot represent the
        // full size in the return result.
        //
        // However, we don't expect people to construct full ranges of host
        // memory pointers.  The use for such a thing is limited so we have
        // prevented the ability to detect such a thing.  Generally one would
        // expect a finite range or the empty range.
        template<typename U>
        static void assert_size_not_full(U const& u_)
        {
            (void)u_; // do nothing
        }
    };

    ///
    /// Represent a range, can be constructed with either a semi-open or closed
    /// range using range_begin_end/range_begin_end_incl.
    ///
    template< typename T >
    struct range_t
    {
        typedef T                                      value_type;
        typedef range_t_traits<T>                      traits;
        typedef typename traits::size_type             size_type;

        T  begin;
        T  end_incl;

        // NOTE that this is _not_ a copy constructor -- C++'s rules say that a
        // copy constructor cannot be a template.
        template< typename U >
        range_t( range_t<U> const& o_ )
            : begin(o_.begin), end_incl(o_.end_incl)
        {
            // Assert that o_ is representable in this type.
            assert( begin == o_.begin );
            assert( end_incl == o_.end_incl );
        }

        // NOTE no constructor with two arguments -- so we are forced at call
        // site to name what we mean.

        range_t()
        {
        }

        // Compiler-generated copy-constructor and assignment operator are OK

        /// Align the range start and end with a specified power-of-two granule.
        ///
        /// A post-condition is that an empty range stays empty, a range can
        /// only get bigger and that the begin and end points are
        /// granule-aligned.  In addition, the expansion of the range is minimal
        /// -- that is the difference between the new begin and the old is <
        /// size_ and similarly the new end and the old is < size_.
        ///
        void expand_to_cover_power_of_two_granule( size_type size_ )
        {
            // is size_ a power of two?
            assert( size_ != 0 && (size_ & (T(0) - size_)) == size_ );
            // TODO make this work if T is a pointer!  We need some additional
            // traits to allow us to do it!
            if (empty())
                return;
            begin    &= T(~T(size_ - 1));
            end_incl |= T(size_ - 1);
        }

        // Align start and end such that start and end are aligned to the granule
        // and start and end both always lie inside the original range. This can make
        // the range empty.
        void reduce_to_contained_power_of_two_granule( size_type size_ )
        {
            // is size_ a power of two?
            assert( size_ != 0 && (size_ & (T(0) - size_)) == size_ );
            // empty range stays empty
            if (empty())
                return;
            // handle corner cases at the end and the beginning of the space
            if ((begin > (T(0) - size_)) || (end_incl < (size_ - 1)))
            {
                *this = make_empty();
                return;
            }
            begin = (begin + (size_ - 1)) & T(~T(size_ - 1));
            end_incl = (end_incl - (size_ - 1)) | T(size_ - 1);
            if (end_incl < begin)
                *this = make_empty();
        }

        /// Does this range intersect the argument, are there a non-zero number
        /// of elements in the intersection?
        ///
        /// This answers the question does (*this `intersection` o_) != null_set.
        ///
        /// As such, if either of the ranges are the null_set then the result is
        /// false.
        bool intersects( range_t const& o_ ) const
        {
            bool const ret = end_incl >= o_.begin && begin <= o_.end_incl
                && ! empty() && ! o_.empty()
                ;
            return ret;
        }

        /// Compute the intersection of two ranges.
        range_t intersection_with( range_t const& o_ ) const
        {
            if (empty() || o_.empty())
                return range_empty<T>();
            range_t r;
            r.begin    = (std::max)( begin,    o_.begin    );
            r.end_incl = (std::min)( end_incl, o_.end_incl );

            if (r.begin > r.end_incl) {
                r = range_empty<T>();
            }

            assert( intersects( o_ ) == ! r.empty() );

            return r;
        }

        /// True if the range is empty.
        bool empty() const
        {
            // Although there are many ways of representing an empty range,
            // it is an error to construct anything other than the canonical representation.
            // This simplifies the comparison operator, and reduces the number of corner-cases
            // to write tests for.
            assert(!(end_incl < begin) || (begin == traits::begin_for_empty() && end_incl == traits::end_incl_for_empty()));
            return end_incl < begin;
        }

        /// True if the range is the full range
        bool full() const
        {
            // NOTE that for types it might not make sense for a full range
            // and the traits will not have the begin_for_full_range(), etc.
            // in and this will fail to compile.
            return begin == traits::begin_for_full_range()
                && end_incl == traits::end_incl_for_full_range();
        }

        /// How many elements are in the range?  NOTE that if this covers the
        /// whole range then this may return a bogus value as size_type may not
        /// be able to express the whole range.  You can use full() to determine
        /// if it is the full range.
        size_type size() const
        {
            traits::assert_size_not_full(*this);
            return empty() ? 0 :  end_incl - begin + 1;
        }

        /// Does the range contain the point specified in the argument.
        bool contains( T t_ ) const
        {
            bool const ret = begin <= t_ && t_ <= end_incl;
            assert( intersects(range_begin_end_incl(t_,t_)) == ret );
            return ret;
        }

        /// Get offset of a value from start of range.
        /// Precondition: value is not less than start of range.
        size_type offset_of( T t_ ) const
        {
            assert(t_ >= begin);
            return t_ - begin;
        }

        /// Does the range contain (or is the same as) the argument.
        ///
        /// NOTE that the empty set is a subset of every set (including itself).
        /// Therefore every set is_a_superset_or_same_as() of the empty set.
        ///
        /// NOTE that strictly 'superset' means that 'A' is a superset of 'A'.
        /// However, some people disagree, so we disambiguate by using
        /// 'or_same_as'.
        ///
        bool is_a_superset_or_same_as( range_t t_ ) const
        {
            bool const ret
                = (begin <= t_.begin && t_.end_incl <= end_incl)
                || t_.empty()                // any set is a superset of empty()
                || (empty() && t_.empty())   // the empty() set is a superset of itself
                ;
            return ret;
        }

        /// This range is below the specified point.  If the range is empty then the result is undefined.
        bool range_is_below_point( T t_ ) const
        {
            assert( ! empty() );
            return end_incl < t_;
        }

        /// This range is above the specified point.  If the range is empty then the result is undefined.
        /// If this returns true then it means that t_ is not a member of the range.
        bool range_is_above_point( T t_ ) const
        {
            assert( ! empty() );
            bool const ret = t_ < begin;
            assert( (  ret && ! contains(t_)) ||
                    (! ret && (contains(t_) || range_is_below_point(t_)) ) );
            return ret;
        }

        bool operator == ( range_t const& o_ ) const
        {
            return begin == o_.begin && end_incl == o_.end_incl && empty() == o_.empty();
        }

        bool operator != ( range_t const& o_ ) const
        {
            return !(*this == o_);
        }

        /// Defining an ordering over the range type, so that values can be
        /// stored in an ordered container.
        /// The empty range compares less than everything apart from itself.
        /// Otherwise, ranges are ordered by start address, then by end address.
        bool operator < ( range_t const & r) const
        {
            if (empty()) return !r.empty();
            return begin < r.begin
               || (begin == r.begin && end_incl < r.end_incl);
        }


        /// \name Models sequence concept
        //@{
        T    front()     const { assert( ! empty() ); return begin; }
        void pop_front()       {
            assert( ! empty() );
            if (begin != end_incl) {
                ++begin;
                assert( !empty() );
            } else {
                *this = range_empty<T>();
                assert( empty() );
            }
        }
        // empty() is defined above
        //@}

        /// \name Named constructors
        //@{
        static range_t from_begin_end(T begin_, T end_) {

            // NOTE that case where end = MIN_T, therefore end - 1 is MAX_T
            // So [begin, MIN_T) (which should be the empty set) becomes [begin, MAX_T)
            // which is a rather large set!  So we have to filter that out first.
            
            if (end_ <= begin_)
                return make_empty();

            range_t<T> r;
            r.begin = begin_;
            r.end_incl = T(end_ - 1);
            return r;
        }

        static range_t from_begin_end_incl(T begin_, T end_incl_) {

            if (end_incl_ < begin_)
                return make_empty();
            
            range_t<T> r;
            r.begin = begin_;
            r.end_incl = end_incl_;
            return r;
        }

        static range_t from_begin_size(T begin_, typename traits::size_type size_ )
        {
            if (size_ == 0)
                return range_empty<T>();

            range_t<T> r = range_begin_end_incl( begin_, begin_ + size_ - 1 );
            assert( r.size() == size_ );
            return r;
        }

        static range_t make_empty() {
            range_t<T> r;
            r.begin = traits::begin_for_empty();
            r.end_incl = traits::end_incl_for_empty();
            assert(r.empty());
            return r;
        }

        static range_t make_full_range() {
            range_t<T> r;
            r.begin = traits::begin_for_full_range();
            r.end_incl = traits::end_incl_for_full_range();
            return r;
        }
        //@}

    };

    ///
    /// Construct a range [begin, end) -- begin is part of the range, but
    /// end is not.
    ///
    template< typename T >
    inline range_t<T> range_begin_end( T begin_, T end_ )
    {
        return range_t<T>::from_begin_end(begin_, end_);
    }

    ///
    /// Construct a range [begin, begin + size) -- begin is part of the range, but
    /// begin + size is not.
    ///
    template< typename T >
    inline range_t<T> range_begin_size( T begin_, typename range_t_traits<T>::size_type size_ )
    {
        return range_t<T>::from_begin_size(begin_, size_);
    }

    ///
    /// Construct a range [begin, end] -- both begin and end are part of the
    /// range.
    ///
    template< typename T>
    inline range_t<T> range_begin_end_incl( T begin_, T end_incl_ )
    {
        return range_t<T>::from_begin_end_incl(begin_, end_incl_);
    }

    ///
    /// Construct an empty range.  This is the unique representation of the empy set.
    ///
    template< typename T >
    inline range_t<T> range_empty()
    {
        return range_t<T>::make_empty();
    }

    ///
    /// Construct a full range.
    ///
    template< typename T >
    inline range_t<T> range_full_range()
    {
        return range_t<T>::make_full_range();
    }

    ///
    /// Construct an sg::range_t from another equivalent representation.
    ///
    template< typename T >
    inline range_t<typename T::value_type> range_from_range( T t_ )
    {
        range_t<typename T::value_type> r; r.begin = t_.begin; r.end_incl = t_.end_incl;
        return r;
    }

    template<typename T>
    inline std::ostream& operator <<( std::ostream& os_, range_t<T> t_ )
    {
        return os_ << "[" << t_.begin << ", " << t_.end_incl << "]";
    }

}

#endif
