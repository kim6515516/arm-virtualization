/*
 * AMBA-PV: amba_pv_ext_ace_master_socket.h - AMBA-PV ACE socket to be instantiated on the master side and that supports
 *                                            hierarchical binding.
 *
 * Copyright 2007-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXT_ACE_MASTER_SOCKET__H
#define AMBA_PV_EXT_ACE_MASTER_SOCKET__H

/**
 * @file        amba_pv_ext_ace_master_socket.h
 *
 * @brief       AMBA-PV ACE socket to be instantiated on the master side.
 */

/* Includes */
#include "tlmx/tlmx_bw_ifs.h"
#include "tlmx/tlmx_initiator_socket.h"
#include "core/amba_pv_ext_core_ifs.h"
#include "core/amba_pv_types.h"
#include "bus/amba_pv_extension.h"
#include "sockets/amba_pv_socket_base.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/**
 * @brief       Extensions namespace.
 */
namespace ext {

/* Forwards */

template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL
#endif
        >
class amba_pv_ace_base_slave_socket;
     
/* Datatypes */

/**
 * @brief       AMBA-PV ACE base master socket.
 *
 * This socket inherits from the tlmx::tlmx_initiator_socket full-duplex socket class and implements a tagged socket.
 * A tagged socket enables a component to determine through which socket an incoming method call arrived.
 * This is required if there are multiple master sockets such as in, for example, a bus decoder.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256, 512, or 1024. Defaults to 64.
 * @param       N number of bindings. Defaults to 1.
 * @param       POL port binding policy. Defaults to @c sc_core::SC_ONE_OR_MORE_BOUND.
 */
template<unsigned int BUSWIDTH = 64,
         int N = 1
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
#endif
        >
class amba_pv_ace_base_master_socket:
    protected virtual tlmx::tlmx_bw_transport_if<amba_pv_protocol_types>,
    public amba_pv_socket_base,
    public tlmx::tlmx_initiator_socket<BUSWIDTH,
                                       amba_pv_protocol_types,
                                       N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                       ,POL
#endif
                                      > {

    /* Typdefs */
    public:
        typedef tlmx::tlmx_initiator_socket<BUSWIDTH,
                                            amba_pv_protocol_types,
                                            N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                            ,POL
#endif
                                            > base_type;
        typedef
            amba_pv_ace_base_master_socket<BUSWIDTH,
                                           N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                           ,POL
#endif
                                          >
            base_master_socket_type;
        typedef
            amba_pv_ace_base_slave_socket<BUSWIDTH,
                                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                          ,POL
#endif
                                         >
            base_slave_socket_type;
        typedef tlmx::tlmx_bw_transport_if<amba_pv_protocol_types> bw_interface_type;

    /* Constructor */
        amba_pv_ace_base_master_socket();
        explicit amba_pv_ace_base_master_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        virtual void bind(base_master_socket_type &);
        void operator() (base_master_socket_type &);
        virtual void bind(base_slave_socket_type &);
        void operator() (base_slave_socket_type &);
        virtual void bind(amba_pv_ace_bw_transport_if &);
        void operator() (amba_pv_ace_bw_transport_if &);

    /* Implementation */
    private:

        /* Member variables */
        amba_pv_ace_bw_transport_if * m_interface;

        /* Full-duplex socket backward interface */
        virtual void b_snoop(amba_pv_transaction &, sc_core::sc_time &);
        virtual unsigned int snoop_dbg(amba_pv_transaction &);
        virtual void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64);
        virtual tlm::tlm_sync_enum nb_transport_bw(amba_pv_transaction &, tlm::tlm_phase &, sc_core::sc_time &);

        /* Helpers */
        void report_error(const char *);
};

/**
 * @brief       AMBA-PV ACE socket to be instantiated on the master side.
 *
 * This socket is for use as an AMBA-PV ACE master socket bound to one or more AMBA-PV ACE slave sockets.
 *
 * amba_pv_ace_master_socket provides convenience methods for the amba_pv_ace_fw_transport_if interface.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256, 512, or 1024. Defaults to 64.
 * @param       N number of bindings. Defaults to 1.
 * @param       POL port binding policy. Defaults to @c sc_core::SC_ONE_OR_MORE_BOUND.
 */
template<unsigned int BUSWIDTH = 64,
         int N = 1
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
#endif
        >
class amba_pv_ace_master_socket:
    public amba_pv_ace_base_master_socket<BUSWIDTH,
                                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                          ,POL
#endif
                                         > {

    /* Typdefs */
    public:
        typedef
            amba_pv_ace_base_master_socket<BUSWIDTH,
                                           N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                           ,POL
#endif
                                          >
            base_type;

    /* Constructor */
        amba_pv_ace_master_socket();
        explicit amba_pv_ace_master_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;


    /* Blocking transport */
        void b_transport(int, amba_pv_transaction &, sc_core::sc_time &);
        void b_transport(amba_pv_transaction &, sc_core::sc_time &);

    /* Debug transport */
        unsigned int transport_dbg(int, amba_pv_transaction &);
        unsigned int transport_dbg(amba_pv_transaction &);

    /* DMI accesses */
        bool get_direct_mem_ptr(int, amba_pv_transaction &, tlm::tlm_dmi &);
        bool get_direct_mem_ptr(amba_pv_transaction &, tlm::tlm_dmi &);
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::amba_pv_ace_base_master_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_ace_base_master_socket")),
    m_interface(NULL) {
}

/**
 * @brief       Constructor.
 *
 * @param       name socket name.
 * @param       socket_id socket identifier (defaults to 0).
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::amba_pv_ace_base_master_socket(const char * name, int socket_id /* = 0 */):
    amba_pv_socket_base(socket_id),
    base_type(name),
    m_interface(NULL) {
}

/**
 * @brief       Returns the kind string of this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline const char *
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::kind() const  {
    return ("amba_pv_ace_base_master_socket");
}

/**
 * @brief       Binds this socket to the specified master socket (hierarchical bind).
 *
 * @param       s amba_pv_ace_base_master_socket master socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::bind(base_master_socket_type & s) {
    base_type::bind(static_cast<base_type &>(s));
    s.m_interface = m_interface;
}

/**
 * @brief       Binds this socket to the specified master socket (hierarchical bind).
 *
 * @param       s amba_pv_ace_base_master_socket master socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::operator() (base_master_socket_type & s) {
    bind(s);
}

/**
 * @brief       Binds this socket to the specified slave socket.
 *
 * @param       s amba_pv_ace_base_slave_socket slave socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::bind(base_slave_socket_type & s) {
    base_type::bind(static_cast<typename base_slave_socket_type::base_type &>(s));
}

/**
 * @brief       Binds this socket to the specified slave socket.
 *
 * @param       s amba_pv_ace_base_slave_socket slave socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::operator() (base_slave_socket_type & s) {
    bind(s);
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_ace_bw_transport_if interface to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::bind(amba_pv_ace_bw_transport_if & iface) {
    if (m_interface != NULL) {
        report_error("instance already bound");
    }
    m_interface = & iface;

    /* Also bind export to self */
    base_type::bind(* static_cast<bw_interface_type *>(this));
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_ace_bw_transport_if interface to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::operator() (amba_pv_ace_bw_transport_if & iface) {
    bind(iface);
}

/*
 * Blocking snoop.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::b_snoop(amba_pv_transaction & trans, sc_core::sc_time & t) {
    if (m_interface == NULL) {
        report_error("b_snoop(): instance has no interface");
    }
    m_interface->b_snoop(get_socket_id(), trans, t);
}

/*
 * Debug access to a master.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline unsigned int
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::snoop_dbg(amba_pv_transaction & trans) {
    if (m_interface == NULL) {

        /* No debug support */
        return 0;
    }
    return (m_interface->snoop_dbg(get_socket_id(), trans));
}

/*
 * Invalidates DMI pointers previously established for the specified DMI region.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range) {
    if (m_interface != NULL) {
        m_interface->invalidate_direct_mem_ptr(get_socket_id(), start_range, end_range);
    }
}

/*
 * Non-blocking transport.
 *
 * Sets the response status to @c tlm::TLM_GENERIC_ERROR_RESPONSE and returns @c tlm::TLM_COMPLETED.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline tlm::tlm_sync_enum
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::nb_transport_bw(amba_pv_transaction & trans, tlm::tlm_phase &, sc_core::sc_time &) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return (tlm::TLM_COMPLETED);
}

/*
 * Report error.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_base_master_socket<BUSWIDTH,
                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                               ,POL
#endif
                              >::report_error(const char * m) {
    std::string msg;

    if (m != NULL) {
        ((msg += m) += ": ") += this->name();
    } else {
        msg = this->name();
    }
    SC_REPORT_ERROR(kind(), msg.c_str());
}

/**
 * @brief       Default constructor.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::amba_pv_ace_master_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_ace_master_socket")) {
}

/**
 * @brief       Constructor.
 *
 * @param       name socket name.
 * @param       socket_id socket identifier (defaults to 0).
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::amba_pv_ace_master_socket(const char * name, int socket_id /* = 0 */):
    base_type(name, socket_id) {
}

/**
 * @brief       Returns the kind string of this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline const char *
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::kind() const  {
    return ("amba_pv_ace_master_socket");
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method forwards the b_transport() call to the @a index'ed slave socket bound to this master
 * socket.
 *
 * @param       index interface index (for sockets bound more than once).
 * @param       trans transaction.
 * @param       t timing annotation.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::b_transport(int index, amba_pv_transaction & trans, sc_core::sc_time & t) {
    (* this)[index]->b_transport(trans, t);
}

/**
 * @brief       Blocking transport.
 *
 * @param       trans transaction.
 * @param       t timing annotation.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::b_transport(amba_pv_transaction & trans, sc_core::sc_time & t) {
    b_transport(0, trans, t);
}

/**
 * @brief       Debug access to a target.
 *
 * This version of the method forwards the transport_dbg() call to the @a index'ed slave socket bound to this master
 * socket.
 *
 * @param       index interface index (for sockets bound more than once).
 * @param       trans transaction.
 *
 * @return      number of bytes read or written or, if error, 0.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline unsigned int
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::transport_dbg(int index, amba_pv_transaction & trans) {
    return ((* this)[index]->transport_dbg(trans));
}

/**
 * @brief       Debug access to a target.
 *
 * @param       trans transaction.
 *
 * @return      number of bytes read or written or, if error, 0.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline unsigned int
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::transport_dbg(amba_pv_transaction & trans) {
    return (transport_dbg(0, trans));
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * This version of the method forwards the get_direct_mem_ptr() call to the @a index'ed slave socket bound to this
 * master socket.
 *
 * @param       index interface index (for sockets bound more than once).
 * @param       trans transaction.
 * @param       dmi_data DMI Descriptor.
 *
 * @return      @c true if DMI access is granted, @c false otherwise.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline bool
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::get_direct_mem_ptr(int index, amba_pv_transaction & trans, tlm::tlm_dmi & dmi_data) {
    return ((* this)[index]->get_direct_mem_ptr(trans, dmi_data));
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * @param       trans transaction.
 * @param       dmi_data DMI Descriptor.
 *
 * @return      @c true if DMI access is granted, @c false otherwise.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline bool
amba_pv_ace_master_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::get_direct_mem_ptr(amba_pv_transaction & trans, tlm::tlm_dmi & dmi_data) {
    return (get_direct_mem_ptr(0, trans, dmi_data));
}

}   /* namespave ext */

}   /* namespave amba_pv */

#endif  /* defined(AMBA_PV_EXT_ACE_MASTER_SOCKET__H) */