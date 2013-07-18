/*!
 * \file    RemapTransactionIntermediary.h
 * \brief   Object to be called from PVBusMapper
 *          which can make downstream transactions with the same attributes
 *          as the incoming transaction
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

/*
 * Copyright 2011 ARM Limited. All rights reserved.
 */

#ifndef REMAPTRANSACTIONINTERMEDIARY_H
#define REMAPTRANSACTIONINTERMEDIARY_H

#include "pv/PVTransaction.h"
#include "pv/TransactionAttributes.h"
#include "pv/RemapRequest.h"

namespace pv
{
class Tx_Result;


    ///
    /// This transaction generator once created is the responsibility of the
    /// client to manage its lifetime.
    ///
    /// NOTE with care, that this should _only_ be used for addresses that are
    /// within the upstream address range that the remap() decision was made
    /// for.
    ///
    /// In the simplest case, then one is created by a remap() decision that
    /// asks for a transaction intermediary to be inserted.  It is then given in
    /// every call to the
    /// RemapTransactionIntermediary::handleReadAccess()/handleWriteAccess()
    /// calls and can be used to make a downstream transaction possibly (but not
    /// confined to) based on the incoming transaction.
    ///
    /// The client of PVBusMapper is allowed to store the
    /// RemapContextTransactionGenerator for longer, so long as it
    /// reference()/dereference() it as appropriate.
    ///
    /// NOTE that reset() does _not_ destroy the generator, and so it is
    /// important that the client correctly dereferences it.
    ///
    /// NOTE in particular that it caches the remap() decision as it was at that
    /// time, so if the remap decision changes then it is the client's
    /// responsibility to notice this and take whatever action it wants.
    /// Typically, it would want to forget about this old transaction generator
    /// and cache the new one.  This forgetting process would involving
    /// dereference() if it had previously called reference() so that it can be
    /// garbage collected.
    ///
    /// NOTE that there is a limitation, you cannot reference() a generator
    /// if the remap request was marked as being valid for the whole of memory.
    /// (This is because if the bus map changes, a large region can potentially
    /// start being represented as a series of smaller ones, and we currently
    /// assume a 1-1 mapping between generator and downstream channels.)
    ///
    /// NOTE that the base class contains information about the original
    /// transaction address and attributes.
    ///
    class RemapContextTransactionGenerator : public RemapRequestAttributes
    {
    public:
        RemapContextTransactionGenerator(RemapRequest const * remap_request_)
        :   RemapRequestAttributes(*(RemapRequestAttributes const *)remap_request_)
        ,   downstream_transaction_attributes(* remap_request_->getTransactionAttributes())
        {}

        /// NOTE that this will only make a read/write as determined by the
        /// remap() decision that this was made for.  Also note that the
        /// RemapContextTransactionGenerator is _not_ specialized on access
        /// type.
        ///
        /// NOTE that the remapped_address_ must be the remapped address and
        /// _not_ the address as presented to the upstream system.
        virtual pv::Tx_Result makeDownstreamAccess(
            bus_addr_t  remapped_address_,
            Payload*    payload_,
            bool        allow_prefetch_ = false
            ) const = 0; // Should assert that upstream_address_ is suitable for remapping
        
        // These are the start attributes used to create the downstream channel
        // (not to be confused with the attributes that the end-point will get).
        //
        // i.e. these are the attributes after the remapping stage.
        TransactionAttributes const *getDownstreamTransactionAttributes() const
        {
            return &downstream_transaction_attributes;
        }

        // NOTE that we make everything const to prevent modifier methods on
        // RemapRequestAttributes being called.  The reference/dereference
        // methods are then (non-intuitively) const methods (and uses a mutable
        // reference count).
        //
        // TODO wonder if we should do reference counting or actually allow the
        // client to delete this instead?  Would seem an easier interface?
        virtual void reference()   const = 0;
        virtual void dereference() const = 0;
    protected:
        // Use reference/dereference instead.
        virtual ~RemapContextTransactionGenerator() {};

        // These are the start attributes used to create the downstream channel.
        pv::TransactionAttributes downstream_transaction_attributes;
    };

    ///
    /// This class is created by the client device and is used to intercept the
    /// transactions flowing through the PVBusMapper for those that we have
    /// given a remap() ruling to act as an intermediary.
    ///
    /// NOTE that you can supply the _same_ RemapTransactionIntermediary to
    /// multiple (different) remap() decisions.  As the
    /// handleReadAccess/handleWriteAccess is given the appropriate generator_
    /// for the specific remap() decision then it can deal successfully with
    /// this case.  For example, a bus logger component could use a single
    /// RemapTransactionIntermediary for all remap() decisions.
    ///
    /// NOTE that the PVBusMapper is allowed to forget a remap() decision for
    /// any reason and so might call remap() again for a transaction that it has
    /// already asked for before.  It is upto the client to detect this and take
    /// a suitable action.  For example, it should either return the same
    /// transaction intermediary (and createdRemapContextTransactionGenerator()
    /// will be called again) or delete/detach() the previous one and return a
    /// new one.
    ///
    class RemapTransactionIntermediary
    {
        RemapTransactionIntermediary (RemapTransactionIntermediary const &); // disallow
        void operator= (RemapTransactionIntermediary const &); // disallow
    public:
        struct private_state_t;
        private_state_t* get_pimpl() {return pimpl;}
    private:
        private_state_t* pimpl;
    public:

        RemapTransactionIntermediary();

        ///
        /// This is called immediately after the client device returns from remap()
        /// with a request for a transaction intermediary.
        ///
        /// If the intermediary wants to cache the generator independently of the
        /// call to handleReadAccess/handleWriteAccess then this is an ideal place
        /// to do so.  Alternatively it could detect the first call to
        /// handleReadAccess/handleWriteAccess and cache the \a generator_ argument.
        ///
        virtual void createdRemapContextTransactionGenerator(
            RemapContextTransactionGenerator const* generator_
            )
        {
            (void)generator_;
        }
        
        ///
        /// \name handleReadAccess/handleWriteAccess
        ///
        /// After the client returns a remap() decision with a request to attach
        /// this intermediary then it will call
        /// createdRemapContextTransactionGenerator() and then
        /// handleReadAccess/handleWriteAccess.
        ///
        /// Subsequent accesses that are classified by PVBusMapper as obeying the
        /// same remap() decision will then directly call
        /// handleReadAccess/handleWriteAccess.
        ///
        /// NOTE that if the client doesn't wish to cache the generator_ in order to
        /// make transactions at other times then it need not call
        /// reference/dereference on the generator.  However, if you are going to
        /// cache it then you _must_ remember to call reference()/dereference().
        ///
        /// The remapped_address_ passed in is the address after the remapping
        /// process.
        ///
        /// If you wish to recover the upstream address or upstream attributes
        /// then you can ask the generator_ to compute them for you.
        ///
        //@{
        virtual pv::Tx_Result handleReadAccess(
            bus_addr_t                               remapped_address_,
            Payload*                                 payload_,
            RemapContextTransactionGenerator const*  generator_
            ) = 0;
        
        virtual pv::Tx_Result handleWriteAccess(
            bus_addr_t                               remapped_address_,
            Payload*                                 payload_,
            RemapContextTransactionGenerator const*  generator_
            ) = 0;
        //@}


        /// If the PVBusMapper has forgotton about a ruling that you have given, then
        /// it will call this at the point at which it forgets.
        ///
        /// The generator_ is still valid, but unless you have retained a reference() to
        /// it (or reference() it in this call) then it will be destroyed when this call
        /// returns.
        ///
        /// If the upstream master makes another request with this upstream_address_ and
        /// attributes then you will be asked for another ruling.
        ///
        /// This call provides you an opportunity to garbage collect RemapTransactionIntermediary
        /// objects when they are no longer used.
        ///
        virtual void decisionForgotten( RemapContextTransactionGenerator const* generator_)
        {
            (void)generator_;
        }

        
        /// This is a request by the client device to detach() the intermediary from
        /// the remap() decision that this was attached to.  This will force the
        /// next transaction to back through the remap() process.
        void detach();
        
        virtual ~RemapTransactionIntermediary();
        // destructor needs to detach() from the control structures in the PVBusMapper if not already.
    };
    
} // namespace pv;

#endif /* REMAPTRANSACTIONINTERMEDIARY_H */
