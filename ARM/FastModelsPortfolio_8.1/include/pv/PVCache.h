 /*!
  * \file    PVCache.h
  * \brief   A model of a cache component
  * \date    Copyright 2010 ARM Limited. All rights reserved.
  *
  */

#ifndef PVCACHE_H
#define PVCACHE_H

#include "sg/SGComponent.h"
#include "sg/SGPort.h"
#include "sg/SGParams.h"

#include "sg/SGFactory.h"

namespace sg { class EventSourceBase; }
namespace fs { class CADIInterface; }

COMPONENT_FACTORY_DECL(PVCache);

namespace PVCache {

/*! Instantiate a new PVCache component with specific parameters.

  If the parameter \a ignore_local_dvm_messages is true then I-cache-maintenance
  DVM messages will not apply to the local cache.

  The parameter \a bitmap_of_downstream_ports_with_a_connected_aceSnoopRequest
  is a bitmap of the downstream ports for which you want to be able to receive
  ACE snoop requests.  So, for example, an I-side cache will not usually
  register to receive snoop requests.  Or if a particular downstream port is an
  ACE-Lite port then it will not have a snoop channel.
 */
    sg::Component *
    Create(
        std::string const&      device_name,
        sg::SimulationContext*  context,
        unsigned                number_of_sets,
        unsigned                number_of_ways,
        unsigned                cache_line_length_in_bytes,
        bool                    ignore_local_dvm_messages,
        unsigned                bitmap_of_downstream_ports_with_a_connected_aceSnoopRequest,
        sg::Params const&       params_,
        fs::CADIInterface**     cadi_reply = NULL
        );
}

namespace CCIInterconnect {

    /// CCIInterconnect control interface.
    class control_if
    {
    protected:
        virtual ~control_if() {}
    public:

        /// \name Control Override Register
        //@{
        virtual void set_terminate_all_barrier_transactions( bool on_ ) = 0;
        virtual bool get_terminate_all_barrier_transactions() const = 0;
        virtual bool get_disable_speculative_fetches() const = 0;
        virtual void set_disable_speculative_fetches( bool on_ ) = 0;
        virtual bool get_dvm_message_disable() const = 0;
        virtual void set_dvm_message_disable( bool on_ ) = 0;
        virtual bool get_snoop_disable() const = 0;
        virtual void set_snoop_disable( bool on_ ) = 0;
        //@}

        /// \name Speculation Control Register
        //@{
        virtual bool get_disable_speculative_fetches_from_master_interface(
            unsigned downstream_port_index_
            ) const = 0;
        virtual void set_disable_speculative_fetches_from_master_interface(
            unsigned downstream_port_index_, bool disable_
            ) = 0;
        //@}

        /// \name Secure Access Register
        //@{
        ; // None all done in CCI register block
        //@}

        /// \name Status Register
        //@{
        virtual bool get_pending_snoop_or_dvm_enables(bool is_debug_) const = 0;
        //@}


        /// \name Imprecise Error Register
        //@{

        /// Get if there was an imprecise error for the specified upstream port index.
        virtual bool get_imprecise_error_for_slave_interface( unsigned upstream_port_index_ ) const = 0;
        virtual void clear_imprecise_error_for_slave_interface( unsigned upstream_port_index_ ) = 0;

        /// Get if there was an imprecise error for the specified upstream port index.
        virtual bool get_imprecise_error_for_master_interface( unsigned downstream_port_index_ ) const = 0;
        virtual void clear_imprecise_error_for_master_interface( unsigned downstream_port_index_ ) = 0;
        //@}


        /// \name Snoop Control Register (per upstream port)
        //@{
        virtual bool get_slave_interface_supports_dvm_messages( unsigned upstream_port_index_ ) const = 0;
        virtual bool get_slave_interface_supports_snoops( unsigned upstream_port_index_ ) const = 0;
        virtual bool get_enable_issuing_of_dvm_message( unsigned upstream_port_index_ ) const = 0;
        virtual void set_enable_issuing_of_dvm_message( unsigned upstream_port_index_, bool enable_ ) = 0;
        virtual bool get_enable_issuing_of_snoops( unsigned upstream_port_index_ ) const = 0;
        virtual void set_enable_issuing_of_snoops( unsigned upstream_port_index_, bool enable_ ) = 0;
        //@}

        /// \name Shareable Override Register (per I/O coherent upstream port only)
        //@{
        enum shareable_override_t {
            do_not_override_adomain = 0,
            override_adomain_to_nsh = 1,
            override_adomain_to_sh  = 2
        };
        virtual shareable_override_t get_shareability_override_for_upstream_port( unsigned upstream_port_index_ ) const = 0;
        virtual void set_shareability_override_for_upstream_port( unsigned upstream_port_index_, shareable_override_t ) = 0;
        //@}
    };

    ///
    /// The control_port implements the CCIInterconnectControl protocol whose
    /// sole purpose is to obtain a pointer to the control_if of the CCIInterconnect.
    ///
    /// The 'slave' of this protocol is the CCIInterconnect.
    ///
    class control_port_t
        : public sg::Port
    {
    public:

        /// Ask for the control_if of the interconnect.
        declare_slave_behaviour( getControlIf, CCIInterconnect::control_if*() );

        control_port_t()
        {
            define_behaviour(getControlIf);
        }
    };

    ///
    /// This implements the connection from the CCIInterconnect to the
    /// CCIRegisters block to expose events.
    ///
    class event_bus_t
        : public sg::Port
    {
    public:

        /// Ask for the control_if of the interconnect.
        declare_peer_behaviour( publishEventSource, void(uint32_t, sg::EventSourceBase*) );

        event_bus_t()
        {
            define_behaviour(publishEventSource);
        }
    };
}

#endif // PVCACHE_H
