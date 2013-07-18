/*!
 * \file    RemapRequest.h
 * \brief   A request object from PVBusMapper t
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

/*
 * Copyright 2011 ARM Limited. All rights reserved.
 */

#ifndef PV_REMAPREQUEST_H
#define PV_REMAPREQUEST_H

#include <vector>
#include <cassert>

#include "pv/PVBusAddr.h"

#include "pv/PVTransaction.h"
#include "pv/TransactionAttributes.h"

namespace pv
{
    class RemapDecisionGroup;
    class RemapTransactionIntermediary;
    class Transaction;
    class ReadTransaction;
    class WriteTransaction;
    
    ///
    /// This class represents the information required to (almost) reproduce a
    /// RemapRequest (i.e. RemapRequestAttributes is the question, RemapRequest
    /// is the answer)
    ///
    class RemapRequestAttributes
    {
    protected:

        ///
        /// \name 'Question' fields
        ///
        //@{
        unsigned                             upstream_port_index;

        pv::bus_addr_t                       transaction_address;
        bool                                 is_read;

        pv::TransactionAttributes            original_upstream_transaction_attributes;
        //@}

        ///
        /// \name 'Answer' fields
        ///
        /// NOTE that this doesn't store the attribute transformation.
        ///
        /// If the remapper is _not_ acting as an intermediary then these
        /// attributes will come from the channel.  When we act as an
        /// intermediary then we have to store them separately.
        ///
        //@{
        bool                                 transform_shared_to_io_coherent;
        bool                                 transform_MakeInvalid_to_CleanInvalid;

        pv::bus_addr_t                       remapped_page_base;
        bool                                 remap_valid_for_all_of_memory;
        //@}

    public:
        RemapRequestAttributes(
            unsigned                          upstream_port_index_,
            pv::bus_addr_t                    transaction_address_,
            bool                              is_read_,
            pv::TransactionAttributes const*  original_upstream_transaction_attributes_
            )
            : upstream_port_index(upstream_port_index_),
              transaction_address(transaction_address_), // Must be before remapped_page_base
              is_read(is_read_),
              original_upstream_transaction_attributes(*original_upstream_transaction_attributes_),
              transform_shared_to_io_coherent(false),
              transform_MakeInvalid_to_CleanInvalid(false),
              remapped_page_base(getPageBase()), // Must be after transaction_address_
              remap_valid_for_all_of_memory(false)
        {
            assert( remapped_page_base == getPageBase() );
        }


        unsigned getUpstreamPortIndex() const
        {
            return upstream_port_index;
        }

        /// Return the 4 KiB aligned address that this request is asking for.
        pv::bus_addr_t getPageBase() const
        {
            return transaction_address & ~4095ull;
        }

        /// Return the original transaction address
        pv::bus_addr_t getOriginalTransactionAddress() const
        {
            return transaction_address;
        }

        /// Return the original (unmodified) transaction attributes.
        pv::TransactionAttributes const* getOriginalTransactionAttributes() const
        {
            return &original_upstream_transaction_attributes;
        }

        bool isRead() const
        {
            return is_read;
        }


        ///
        /// \name 'Answer'
        ///
        //@{
        bool           isRemapValidForAllOfMemory() const { return remap_valid_for_all_of_memory; }
        pv::bus_addr_t getRemapPageBase()           const { return remapped_page_base;            }
        //@}
    };


    ///
    /// This class represent a remap request from the PVBusMapper.  It is
    /// created by the PVBusMapper and passed to the object performing the remap
    /// request.
    ///
    class RemapRequest : public RemapRequestAttributes
    {
        RemapRequest(RemapRequest const&); //Disallow, this is important as the actual RemapRequest
                                           //passed is a derived type and we have to avoid slicing it.
        void operator =(RemapRequest const&); //Disallow
    public:

        virtual ~RemapRequest();

        pv::TransactionAttributes* getModifiableTransactionAttributes()
        {
            return attributes;
        }
        const pv::TransactionAttributes* getTransactionAttributes() const
        {
            return attributes;
        }


        /// Is this transaction for a PrefetchOnly request
        bool isPrefetchOnly() const
        {
            return is_prefetch_only;
        }


        /// Remap the page base to the new value, this must be page aligned.
        void setRemapPageBase(pv::bus_addr_t page_base_)
        {
            assert( state == transaction_not_valid
                    || 0 == "Attempt to change remap transformation after calling getSoleTransactionNoForward()" );
            assert( (page_base_ & (4*1024 - 1)) == 0 ); // must be 4 KiB aligned
            remapped_page_base = page_base_;

            // and we are not allowed to have specified ValidForAllOfMemory
            assert( !remap_valid_for_all_of_memory );
        }

        // By default, decisions are assumed to be valid for only a region of 4k.
        // If the client can guarantee that its decision does not take address into account
        // then we can mark this remap decision as being potentially valid for all of memory.
        // In this case remapping address is not allowed!
        // Other users may limit the size they takes notice of, and make further requests for a ruling already given
        //
        // There is a current limitation that retaining a reference to RemapContextTransactionGenerator
        // assumes a 4k page extent, and is therefore incompatible with this option
        void setRemapValidForAllOfMemory()
        {
            assert( state == transaction_not_valid
                    || 0 == "Attempt to change remap transformation after calling getSoleTransactionNoForward()" );

            assert( remapped_page_base == getPageBase()
                    || 0 == "setRemapValidForAllOfMemory called after requesting address remapping");

            remap_valid_for_all_of_memory = true;
        }


        void addRemapDecisionGroup( RemapDecisionGroup* group_ )
        {
            assert( group_ != 0 );
            groups.push_back( group_ );
        }

        /// If you have assembled a vector of RemapDecisionGroup independently and
        /// just want to swap it (which is very efficient), then use this function.
        void swapRemapDecisionGroup( std::vector<RemapDecisionGroup*>& groups_ )
        {
            groups.swap(groups_);
        }

        void setRemapTransactionIntermediary(RemapTransactionIntermediary* intermediary_)
        {
            assert( intermediary_ != 0 );
            intermediary = intermediary_;
        }

        ///
        /// If you transform the shareability of the transaction then there are
        /// other transformations that must apply.  Some of these
        /// transformations will be detected automatically by the PVBusMapper
        /// but there are others that are optional and need you to tell us if
        /// you want them applied.
        ///
        /// nsh -> sys, sys -> nsh: no transformation makes sense
        ///
        /// nsh -> ish/osh, sys -> ish/osh: the transformation applied is to
        /// make all requests as ReadOnce/PseudoWriteOnce.  This is done
        /// automatically and you need not do anything.
        ///
        /// ish/osh -> nsh, ish/osh -> nsh: everything maps to
        /// ReadNoSnoop/WriteNoSnoop.  This is done automatically and you need
        /// not do anything.
        ///
        /// ish -> osh, osh -> ish: you can either leave the request the same
        /// (do nothing) or you can transform the requests into I/O coherent
        /// requests.  The resultant system may not be 'coherent' but may be
        /// feasible for particular SW patterns.  To use this transformation
        /// then you must call transformSharedToIOCoherent().
        ///
        /// ish -> ish, osh -> osh changing to I/O coherent.  In order to invoke
        /// this behaviour then call transformSharedToIOCoherent().
        ///
        /// NOTE that cache-maintenance operations are transported through
        /// different channels and so if you wish to terminate them then you
        /// route them to the PVBUSMAPPER_IGNORE slave.
        ///
        /// NOTE it is safe to call this function if the original attributes
        /// were nsh/sys, even if it is not transformed to ish/osh; the call
        /// will be ignored.
        ///
        void transformSharedToIOCoherent()
        {
            assert( state == transaction_not_valid
                    || 0 == "Attempt to change remap transformation after calling getSoleTransactionNoForward()" );
            transform_shared_to_io_coherent = true;
        }

        ///
        /// If this is a request for the transformation of cache maintenance
        /// requests, then you can request that all cache invalidates
        /// (ACE::MakeInvalid) are converted to cache clean and invalidate
        /// (ACE::CleanInvalid).
        ///
        void transformCMOMakeInvalidToCleanInvalid()
        {
            assert( state == transaction_not_valid
                    || 0 == "Attempt to change remap transformation after calling getSoleTransactionNoForward()" );
            assert( getTransactionAttributes()->isCacheMaintenance()
                    || 0 == "Attempt to call transformCMOMakeInvalidToCleanInvalid() when the RemapRequest is not "
                            "related to a cache maintenance request" );
            transform_MakeInvalid_to_CleanInvalid = true;
        }

        ///
        /// If you don't want to form a channel, but deal directly with the
        /// transaction now (and subsequent transactions with the same
        /// attributes will come in as another remap request) then you can call
        /// this to give you the transaction.
        ///
        /// If you have already modified the attributes or changed the address
        /// mapping then these will be reflected in the transaction that you are
        /// returned.  NOTE that it is UNDEFINED what happens if you apply more
        /// transformations after calling getSoleTransactionNoForward().  Some
        /// or all of the transformations may be compounded, ignored or
        /// corrupted.
        ///
        /// If you have attached transaction intermediaries then these will be
        /// ignored.
        ///
        /// Once you have called getSoleTransactionNoForward() then you can
        /// record the transaction response by calling
        /// returnSoleTransactionResult().  If you don't call
        /// returnSoleTransactionResult then the transaction will not be
        /// terminated and the remap request will work as normal (although you
        /// must still not call any more transformation functions).  This allows
        /// you to examine the transaction further before deciding if you want
        /// to terminate it or not.
        ///
        /// Only call these functions _once_.
        ///
        /// NOTE that the return from getSoleTransactionNoForward() can be
        /// static_cast to pv::ReadTransaction or
        /// pv::WriteTransaction(). Alternatively you can use the
        /// getSoleTransactionNoForwardAsRead()/getSoleTransactionNoForwardAsWrite()
        /// which does the cast for you.
        ///
        //@{
        virtual pv::Transaction*  getSoleTransactionNoForward() = 0;
        pv::ReadTransaction*      getSoleTransactionNoForwardAsRead();
        pv::WriteTransaction*     getSoleTransactionNoForwardAsWrite();
        virtual void              returnSoleTransactionResult(pv::Tx_Result const& result_) = 0;
        //@}        

    protected:

        friend class PVBusMapper;

        RemapRequest(
            unsigned                          upstream_port_index_,
            pv::TransactionAttributes*        attributes_,
            pv::bus_addr_t                    transaction_address_,
            bool                              is_prefetch_only_,
            bool                              is_read_
            )
            : RemapRequestAttributes(
                upstream_port_index_,
                transaction_address_,
                is_read_,
                attributes_
                ),
              attributes(attributes_),
              is_prefetch_only(is_prefetch_only_),
              intermediary(0),
              state(transaction_not_valid)
        {
        }

        pv::TransactionAttributes*           attributes;
        bool                                 is_prefetch_only;

        std::vector< RemapDecisionGroup* >   groups;
        RemapTransactionIntermediary*        intermediary;
        
        enum {
            transaction_not_valid,
            transaction_valid,
            transaction_and_result_valid
        } state;
    };
}

#endif
