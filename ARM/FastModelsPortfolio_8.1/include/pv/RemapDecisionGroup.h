/*!
 * \file    RemapDecisionGroup.h
 * \brief   Object that owns a collection of bus mapping decisions
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

/*
 * Copyright 2011 ARM Limited. All rights reserved.
 */

#ifndef PV_REMAPDECISIONGROUP_H
#define PV_REMAPDECISIONGROUP_H

#include "pv/PVBus.h"
#include "pv/AccessDirection.h"

class DVMNode;

namespace pv
{

    template <typename D> class Channel;
    typedef Channel<AccessRead> ReadChannel;
    typedef Channel<AccessWrite> WriteChannel;

    class PVBusMapper;
    
    ///
    /// This class is used by PVBusMapper to label a group of mapping/routing
    /// decisions that the remap function has made.
    ///
    /// If the remap function tags a decision with a RemapDecisionGroup, then it
    /// can revoke all decisions attached to that tag in the same operation.  In
    /// addition, it can be told when all decisions made with that tag have been
    /// forgotten about and so it could perform some cleanup.
    ///
    /// Typically, a remapping object will allocate a RemapDecisionGroup that
    /// represents a particular set of circumstances under which the
    /// remapping/routing decision made is valid.  If those circumstances
    /// change, then it will call revokeAll() on the RemapDecisionGroup (or
    /// delete it).  This causes any new transactions with the same
    /// TransactionAttributes/address combination to ask to be remapped again,
    /// rather than reusing the already-made decision.
    ///
    /// In order to allow the remap object to manage its storage, then the
    /// RemapDecisionGroup is also told when no more cached decisions are being
    /// made using this group.  This is done by PVBusMapper calling
    /// decisionGroupBecameEmpty() on the decision group.
    ///
    class RemapDecisionGroup
    {
        RemapDecisionGroup(RemapDecisionGroup const&); //disallow
        void operator = (RemapDecisionGroup const&); //disallow

        template <typename D> class ChannelList;
        ChannelList<AccessRead> *read_channels;
        ChannelList<AccessWrite> *write_channels;

    public:

        RemapDecisionGroup();

        /// The destructor will automatically revoke all routing decisions made
        /// for this group (equivalent to calling revokeAll()).
        virtual ~RemapDecisionGroup();

        ///
        /// \name Operations for use by the object doing the remap
        ///
        //@{
        
        /// Revoke all the routing decisions that have been tagged with this
        /// group.
        ///
        /// decisionGroupBecameEmpty() will _not_ be called as a result of this
        /// call.
        void revokeAll();

        //@}

        ///
        /// \name Operations that can be overridden by the object doing the
        ///       remap.
        ///
        //@{

        /// The last cached decision made that was tagged with this group has
        /// been forgotten (i.e. running revokeAll() at this stage has no effect).
        ///
        /// You _are_ allowed to delete this object during this call.
        ///
        /// NOTE that if you call revokeAll() (with or without any decisions
        /// attached) then you will _not_ get called through this function -- it
        /// is assumed that whatever called it will be responsible for any clear
        /// up associated with it.
        virtual void decisionGroupBecameEmpty() {}

        /// Are we actually managing any decisions?
        bool empty() const;
        
        //@}

        // Internal interface used by PVBusMapper
        void addChannel( ReadChannel* channel_ );
        void addChannel( WriteChannel* channel_ );
        void failingToAttachAsChannelIsAlreadyBeingDestroyed();

    private:
        void maybe_became_empty();
    };

    
}

#endif
