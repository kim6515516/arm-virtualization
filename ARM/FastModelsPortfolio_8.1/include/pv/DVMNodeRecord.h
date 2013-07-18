/*!
 * \file    DVMNodeRecord.h
 * \brief   Interface for calling a DVM node from PVBusMapper
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

#ifndef PV_DVMNODERECORD_H
#define PV_DVMNODERECORD_H

#include <set>
#include "pv/DVM.h"
#include "pv/PVBus.h"

class DVMNode;

namespace pv
{
    ///
    /// PVBusMapper also allows you to talk to DVM nodes upstream and downstream
    /// of the PVBusMapper.  This class encapsulates the information in order to
    /// call a DVM Node.
    ///
    /// NOTE that a single DVM node might be connected to us multiply and this
    /// can lead to an asymmetry between receiving and sending DVM messages.
    ///
    /// NOTE also that you can choose not to let the upstream and/or downstream
    /// system see the PVBusMapper, but this does _not_ impair your ability to
    /// send to nodes in the upstream/downstream.  This particular type of
    /// asymmetry might lead to a logical inconsistency in the ACE system and so
    /// be sure that this is your intent before allowing this.
    ///
    /// As a receiver, then we can only tell which of our ports the message came
    /// in, we can also distinguish the sender, but if there multiple paths to
    /// the same sender, then we cannot distinguish the route that it took.
    ///
    /// In hardware, then we cannot distinguish the sender at all.  The hardware
    /// may have multiple upstream ports, in the model we have one port but
    /// (unlike hardware) allow multiple masters to connect to it.  We then
    /// allow the multiple masters to distinguish themselves by sending their
    /// identity (DVMNode*).  However, if there are multiple paths to the same
    /// master then we cannot distinguish the different paths and you must use
    /// some other resolution method to determine that.
    ///
    /// So as a receiver (handleUpstreamDVMMessage/handleDownstreamDVMMessage),
    /// you get the arc_within_port_ (DVMNode*) and the upstream/downstream port
    /// index that it was received on.
    ///
    /// As a sender then you know for each of your ports which DVMNode* are
    /// attached to the port, but potentially there may be multiple paths from
    /// the same port to the same destination (DVMNode*) and you will have to
    /// distinguish between them if you care.
    ///
    /// We purposefully, express the DVMNode* as a void* in order to avoid you
    /// accidentally calling it.  Instead, prefer to call it through the
    /// DVMNodeRecord which will take care of marshaling all the correct
    /// arguments to the function.
    ///
    class DVMNodeRecord
    {
        /// This is _our_ end of the DVM node -- this is the result of calling
        /// getMyArcIdentifier().  It will be the same for all DVMNodeRecord
        /// from the same PVBusMapper.
        DVMNode*       source;

        /// This is the destination node.
        DVMNode*       destination;
        /// This is the id that the destination wished for us to give to it
        /// when we send a message to it.
        DVM::id_t      id_to_deliver_to_destination;

        /// This is the port index on _us_ that this will go out of.
        unsigned       port_index;

        bool           is_upstream; // set by PVBusMapper after the collection has been initialised

        friend class PVBusMapper;
        void init(
            unsigned       port_index_,
            DVM::id_t      id_to_deliver_to_destination_,
            DVMNode*       source_,
            DVMNode*       destination_
            )
        {
            source                       = source_;
            destination                  = destination_;
            port_index                   = port_index_;
            id_to_deliver_to_destination = id_to_deliver_to_destination_;
            is_upstream                  = false;
        }
    public:

        unsigned   getPortIndex()        const { return port_index;  }
        void*      getArcWithinPort()    const { return destination; }
        DVM::id_t  getDestinationDVMID() const { return id_to_deliver_to_destination; }
        bool       isUpstreamDVMNode()   const { return is_upstream; }

        bool matches( unsigned port_index_, void* arc_within_port_ )
        {
            return getPortIndex() == port_index_
                && arc_within_port_ == getArcWithinPort();
        }

        DVM::error_response_t sendDVMMessage(
            DVM::Message* message_
            )
        {
            if (isUpstreamDVMNode())
                return destination->handleUpstreamDVMMessage( source, id_to_deliver_to_destination, message_ );
            else
                return destination->handleDownstreamDVMMessage( source, id_to_deliver_to_destination, message_ );
        }
    };
} // namespace pv

#endif
