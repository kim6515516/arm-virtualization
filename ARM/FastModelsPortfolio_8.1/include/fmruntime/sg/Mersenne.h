/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
*  \file    Mersenne.h
*  \brief   An implementation of a Mersenne Twister random number generator.
*  \date    Copyright ARM Limited 2010-2011. All rights reserved.
*
*  This Mersenne Twister implementation is here simply as a convenience for
*  models that require a reasonable and fast PRNG and cannot rely on a good
*  implementation in the host platform's libc.
*
*  The class is not part of a stable public API and the interface to it may
*  change without notice.
*/

#ifndef INCLUDED_MERSENNE_H
#define INCLUDED_MERSENNE_H

namespace sg
{
    /*!
     * Mersenne Twister Pseudo-Random Number Generator.
     *
     * NOTE that the state of this class is > 2 KiB.  On 2+ GHz x86 hosts
     * it can generate over 100 million values per sercond.
     *
     * It is _not_ suitable for cryptographic purposes, and immediately
     * after initialisation must be run for several thousand iterations
     * before the values produced have a random distribution of bits.
     *
     * On instantiation, it has a default seed, but can be reinitialised
     * by calling init().
     */
    class Mersenne
    {
        uint32_t   MT[624];
        unsigned   index;

        template <unsigned start, unsigned end, int offset>
        void generate_part_of_numbers();

        void generate_numbers();

    public:
        // Default behaviour of copy-constructor, assignment operator and destructor are good.

        Mersenne( uint32_t seed_ = 0x8ab4f124)
            : index(0)
        {
            seed( seed_ );
        }

        void seed( unsigned seed_ );

        uint32_t value()
        {
            uint32_t y = MT[index];
            y ^= y >> 11;
            y ^= (y << 7) & 0x9d2c5680;
            y ^= (y << 15) & 0xefc60000;
            y ^= (y >> 18);

            if (++ index == 624)
            {
                index = 0;
                generate_numbers();
            }
            return y;
        }

        uint32_t operator()()
        {
            return value();
        }

        /// Deliver a random number in range [0, top_), assuming top_ is much less than ~uint32_t(0).
        uint32_t operator()(uint32_t top_)
        {
            return value() % top_;
        }
    };

    template< typename T >
    T get_random_number( Mersenne& r_ )
    {
        return T( sizeof(T) > sizeof(uint32_t)
                  ? uint64_t(r_()) << 32 | r_()
                  : r_() )
            ;
    }
}

#endif
