/*!
 * \file   AccessDirection.h
 * \brief  Separate reads from writes.
 * \date   Copyright 2009 ARM Limited. All rights reserved.
 *
 */

#ifndef ACCESSDIRECTION_H
#define ACCESSDIRECTION_H

#include "sg/SGstdint.h"

namespace pv
{
/*! Identify read vs write accesses. */
enum AccessDirectionValue {
    ACCESS_READ = 1,
    ACCESS_WRITE = 2
};
/*! \brief Base class for templating read and write operations.
 *
 *  The only difference in parameter signature for the read and
 *  write handler functions is that write functions take a pointer
 *  to a block of CONST data, whereas read functions pass a pointer
 *  to non-const data.
 *
 *  Rather than duplicating lots of definitions in order to create 
 *  separate operations for read and for write accesses, we template
 *  everything on an AccessDirection class.  This makes the code 
 *  slightly less readable, but halves the amount of code we need
 *  to maintain.
 *
 *  The subclasses AccessRead and AccessWrite define types for
 *  pointers to data values of various sizes, with or without a
 *  CONST type.
 */
class AccessDirection
{
};

/*! \brief Traits class for the pointer types used for read accesses.
 */
class AccessRead : public AccessDirection
{
public:
    enum { ID = ACCESS_READ };
    static AccessDirectionValue const id = ACCESS_READ;

    //! Type for a buffer provided by the master to store the read results.
    typedef void  *      master_buffer_ptr;
    //! Type for a buffer provided by the slave containing readable memory.
    typedef void const * slave_buffer_ptr;

    typedef uint8_t *  master_u8_ptr;
    typedef uint16_t * master_u16_ptr;
    typedef uint32_t * master_u32_ptr;
    typedef uint64_t * master_u64_ptr;

    typedef uint8_t &  master_u8_ref;
    typedef uint16_t & master_u16_ref;
    typedef uint32_t & master_u32_ref;
    typedef uint64_t & master_u64_ref;

    typedef uint8_t const *  slave_u8_ptr;
    typedef uint16_t const * slave_u16_ptr;
    typedef uint32_t const * slave_u32_ptr;
    typedef uint64_t const * slave_u64_ptr;

    typedef uint8_t const &  slave_u8_ref;
    typedef uint16_t const & slave_u16_ref;
    typedef uint32_t const & slave_u32_ref;
    typedef uint64_t const & slave_u64_ref;
};

/*! \brief Traits class for the pointer types used for write accesses.
 */
class AccessWrite : public AccessDirection
{
public:
    enum { ID = ACCESS_WRITE };
    static AccessDirectionValue const id = ACCESS_WRITE;

    //! Type for a buffer provided by the master to store the write data.
    typedef void const * master_buffer_ptr;
    //! Type for a buffer provided by the slave containing writeable memory.
    typedef void *       slave_buffer_ptr;

    typedef uint8_t const *  master_u8_ptr;
    typedef uint16_t const * master_u16_ptr;
    typedef uint32_t const * master_u32_ptr;
    typedef uint64_t const * master_u64_ptr;

    typedef uint8_t const &  master_u8_ref;
    typedef uint16_t const & master_u16_ref;
    typedef uint32_t const & master_u32_ref;
    typedef uint64_t const & master_u64_ref;

    typedef uint8_t *  slave_u8_ptr;
    typedef uint16_t * slave_u16_ptr;
    typedef uint32_t * slave_u32_ptr;
    typedef uint64_t * slave_u64_ptr;

    typedef uint8_t &  slave_u8_ref;
    typedef uint16_t & slave_u16_ref;
    typedef uint32_t & slave_u32_ref;
    typedef uint64_t & slave_u64_ref;
};

}
#endif
