/*!
 * \file    TransactionAttributes.h
 * \brief   Attributes used to construct a channel.
 * \date    Copyright 2009 ARM Limited. All rights reserved.
 *
 */

#ifndef TRANSACTIONATTRIBUTES_H
#define TRANSACTIONATTRIBUTES_H

#include "pv/PVMemoryAttributes.h"

namespace pv {

/*! Holds the attributes that are associated with a channel.
 *  All requests over a channel implicitly have the same attributes.
 *  It is up to the slave to cache this information when it provides
 *  the ChannelPageSlave.
 */
class TransactionAttributes : public MemoryAttributes
{
    enum { MASTER_ID_PTW_BIT = 15 };

public:

    bool isExclusive()         const { return exclusive::get(attr) != 0; }
    void setExclusive(bool on)       { exclusive::set(attr, on); assert( isExclusive() == on ); }

    bool isDebug()             const { return is_debug::get(attr) != 0; }
    void setDebug(bool on)           { is_debug::set(attr, on); assert( isDebug() == on ); }

    bool isCacheMaintenance()  const { return is_cache_maintenance_operation::get(attr) != 0; }
    void setCacheMaintenance( bool on ) { is_cache_maintenance_operation::set(attr, on); assert( isCacheMaintenance() == on ); }

    bool isPTW()               const { return (master_id & (1<<MASTER_ID_PTW_BIT)) != 0; }

    void setPTW(bool on)
    {
        if (on) master_id |= 1<<MASTER_ID_PTW_BIT;
        else    master_id &= ~(1<<MASTER_ID_PTW_BIT);

        assert(isPTW() == on);
    }

    /*! Provide a comparison operator to allow attributes to be stored in a map. */
    bool operator < (const TransactionAttributes& compare) const
    {
        // NOTE that the base class compares all attributes, independent of
        // whether they are for a derived class or not.
        return (MemoryAttributes const&)*this < (MemoryAttributes const&)compare;
    }

    bool operator == (const TransactionAttributes& compare) const
    {
        // NOTE that the base class compares all attributes, independent of
        // whether they are for a derived class or not.
        return (MemoryAttributes const&)*this == (MemoryAttributes const&)compare;
    }

    bool operator != (const TransactionAttributes& compare) const
    {
        return !(*this == compare);
    }

    void operator = (MemoryAttributes const& o_)
    {
        *(MemoryAttributes*)this = o_;
    }

    TransactionAttributes()
    {
    }

    TransactionAttributes( MemoryAttributes const& o_ )
        : MemoryAttributes(o_)
    {
    }

    ///
    /// MemoryAttributes is missing a few flags, this constructor allows us to
    /// construct a Transaction attributes from a flag (is_debug_) and something
    /// like a pv::Transaction that will tell us if it is exclusive and the ace
    /// operation.
    ///
    template<typename TX>
    TransactionAttributes( MemoryAttributes const& o_, bool is_debug_, TX const& tx_ )
        : MemoryAttributes(o_)
    {
        setExclusive( tx_.isExclusive() );
        setDebug( is_debug_ );
        ACE::ace_operation_t op = tx_.getACEOperation();
        unsigned const mask = 1u << op;
        unsigned const set
            = (1u << ACE::CleanShared)
            | (1u << ACE::CleanInvalid)
            | (1u << ACE::MakeInvalid);
        setCacheMaintenance( (mask & set) != 0 );
    }

    void dbg_print(); // print to std::cerr
};

    std::ostream& operator << (std::ostream& os_, TransactionAttributes const& o_);

    inline MemoryAttributes::MemoryAttributes( TransactionAttributes const& o_ )
    {
        (MemoryAttributesCommon&)*this = (MemoryAttributesCommon const&)o_;
        squash_non_memory_attributes();
    }

    inline void MemoryAttributes::operator = (TransactionAttributes const& o_)
    {
        (MemoryAttributesCommon&)*this = (MemoryAttributesCommon const&)o_;
        squash_non_memory_attributes();
    }

} // namespace pv

#endif // TRANSACTIONATTRIBUTES_H
