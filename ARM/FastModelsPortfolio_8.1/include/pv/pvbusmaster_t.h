/*!
 * \file    pvbusmaster_t.h
 * \brief   Instantiate the abstract PVBusMaster and connect to it.
 * \date    Copyright 2010 ARM Limited. All rights reserved.
 *
 */

#ifndef PVBUSMASTER_T_H
#define PVBUSMASTER_T_H

#include "pv/PVBus.h"
#include "pv/PVBusMaster.h"

namespace sg
{
    class SGComponent;
}

namespace pv
{
    ///
    /// Do the heavy-lifting of getting a PVBusMaster and getting a
    /// RandomContextTransactionGenerator out of it.  The class itself is-a
    /// RandomContextTransactionGenerator and forwards the calls.
    ///
    class pvbusmaster_t
        : public pv::Bus
    {
    public:
        pv::TransactionMasterControl            control;

        pv::RandomContextTransactionGenerator*  generator;
        unsigned                                port_index;

        typedef pv::RandomContextTransactionGenerator::buffer_t buffer_t;

        pvbusmaster_t();
        virtual ~pvbusmaster_t();

        class device_if
        {
        protected:
            virtual ~device_if() {}
        public:

            virtual void          aceSnoopRequest(unsigned port_index_, ACE::SnoopRequest* tx) = 0;
            virtual void          debugACESnoopRequest(unsigned port_index_, ACE::SnoopRequest* tx) = 0;

        };

        device_if*  device;

        ///
        /// Initialise.
        ///
        /// You \e may set receiver_of_snoop_requests_ to 0 if you don't accept
        /// them.  For example, this is useful for an I-side cache which won't
        /// receive snoop requests upwards.  Or if this port is an ACE-Lite
        /// master and so has no snoop channel.
        ///
        void init(
            unsigned                            port_index_,
            std::string const&                  base_name_,
            sg::Component*                      parent_,
            device_if*                          receiver_of_snoop_requests_
            );

        virtual void setNumberOfChannels( unsigned number_ = ~0u )
        {
            generator->setNumberOfChannels( number_ );
        }

        virtual pv::Tx_Result read(TransactionAttributes const*             attributes_,
                                   ACE::Payload*                            ace_request_,
                                   bus_addr_t                               address_,
                                   buffer_t*                                buffer_)
        {
            return generator->read( attributes_, ace_request_, address_, buffer_ );
        }

        pv::Tx_Result read(TransactionAttributes const*             attributes_,
                           bus_addr_t                               address_,
                           buffer_t*                                buffer_)
        {
            ACE::Payload payload;
            return read( attributes_, &payload, address_, buffer_ );
        }

        virtual pv::Tx_Result write(TransactionAttributes const*       attributes_,
                                    ACE::Payload*                      ace_request_,
                                    bus_addr_t                         address_,
                                    buffer_t const *                   buffer_)
        {
            return generator->write( attributes_, ace_request_, address_, buffer_ );
        }

        pv::Tx_Result write(TransactionAttributes const*             attributes_,
                            bus_addr_t                               address_,
                            buffer_t*                                buffer_)
        {
            ACE::Payload payload;
            return write( attributes_, &payload, address_, buffer_ );
        }
    };
}

#endif
