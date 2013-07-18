/*
 * AMBA-PV: amba_pv_ext_slave_socket.h - AMBA-PV socket to be instantiated on the slave side and that supports
 *                                       hierarchical binding.
 *
 * Copyright 2007-2009, 2012-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXT_SLAVE_SOCKET__H
#define AMBA_PV_EXT_SLAVE_SOCKET__H

/**
 * @file        amba_pv_ext_slave_socket.h
 *
 * @brief       AMBA-PV socket to be instantiated on the slave side.
 */

/* Includes */
#include "core/amba_pv_core_ifs.h"
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
class amba_pv_base_master_socket;
     
/* Datatypes */

/**
 * @brief       AMBA-PV base slave socket.
 *
 * This socket inherits from the OSCI TLM 2.0 @c tlm::tlm_target_socket class and implements a tagged socket.
 * A tagged socket allows a component to determine through which socket an incoming method call arrived.
 * This is required if there are multiple slave sockets such as in, for example, an interconnect or a multi-port memory.
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
class amba_pv_base_slave_socket:
    protected virtual tlm::tlm_fw_transport_if<amba_pv_protocol_types>,
    public amba_pv_socket_base,
    public tlm::tlm_target_socket<BUSWIDTH,
                                  amba_pv_protocol_types,
                                  N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                  ,POL
#endif
                                 > {

    /* Typdefs */
    public:
        typedef
            tlm::tlm_target_socket<BUSWIDTH,
                                  amba_pv_protocol_types,
                                  N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                  ,POL
#endif
                                 > base_type;
        typedef
            amba_pv_base_master_socket<BUSWIDTH,
                                       N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                       ,POL
#endif
                                      > base_master_socket_type;
        typedef
            amba_pv_base_slave_socket<BUSWIDTH,
                                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                      ,POL
#endif
                                     > base_slave_socket_type;
        typedef tlm::tlm_fw_transport_if<amba_pv_protocol_types> fw_interface_type;

    /* Constructor */
        amba_pv_base_slave_socket();
        explicit amba_pv_base_slave_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        virtual void bind(base_slave_socket_type &);
        void operator() (base_slave_socket_type &);
        virtual void bind(base_master_socket_type &);
        void operator() (base_master_socket_type &);
        virtual void bind(amba_pv_fw_transport_if &);
        void operator() (amba_pv_fw_transport_if &);

    /* Implementation */
    private:

        /* Member variables */
        amba_pv_fw_transport_if * m_interface;

        /* TLM 2.0 forward interface */
        virtual void b_transport(amba_pv_transaction &, sc_core::sc_time &);
        virtual unsigned int transport_dbg(amba_pv_transaction &);
        virtual bool get_direct_mem_ptr(amba_pv_transaction &, tlm::tlm_dmi &);
        virtual tlm::tlm_sync_enum nb_transport_fw(amba_pv_transaction &, tlm::tlm_phase &, sc_core::sc_time &);

        /* Helpers */
        void report_error(const char *);
};

/**
 * @brief       AMBA-PV socket to be instantiated on the slave side.
 *
 * This socket is for use as a slave socket bound to one or more master sockets.
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
class amba_pv_slave_socket:
    public amba_pv_base_slave_socket<BUSWIDTH,
                                     N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                     ,POL
#endif
                                    > {

    /* Typdefs */
    public:
        typedef
            amba_pv_base_slave_socket<BUSWIDTH,
                                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                      ,POL
#endif
                                     > base_type;

    /* Constructor */
        amba_pv_slave_socket();
        explicit amba_pv_slave_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Backward DMI invalidation */
        void invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);
        void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64);
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
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::amba_pv_base_slave_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_base_slave_socket")),
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
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::amba_pv_base_slave_socket(const char * name, int socket_id /* = 0 */):
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
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::kind() const  {
    return ("amba_pv_base_slave_socket");
}

/**
 * @brief       Binds this socket to the specified slave socket (hierarchical bind).
 *
 * @param       s amba_pv_base_slave_socket slave socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::bind(base_slave_socket_type & s) {
    base_type::bind(static_cast<base_type &>(s));
    m_interface = s.m_interface;
}

/**
 * @brief       Binds this socket to the specified slave socket (hierarchical bind).
 *
 * @param       s amba_pv_base_slave_socket slave socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::operator() (base_slave_socket_type & s) {
    bind(s);
}

/**
 * @brief       Binds this socket to the specified master socket.
 *
 * @param       s amba_pv_base_master_socket master socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::bind(base_master_socket_type & s) {
    base_type::bind(static_cast<typename base_master_socket_type::base_type &>(s));
}

/**
 * @brief       Binds this socket to the specified master socket.
 *
 * @param       s amba_pv_base_master_socket master socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_slave_socket<BUSWIDTH,
                           N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                           ,POL
#endif
                          >::operator() (base_master_socket_type & s) {
    bind(s);
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_fw_transport_if interface to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::bind(amba_pv_fw_transport_if & iface) {
    if (m_interface != NULL) {
        report_error("instance already bound");
    }
    m_interface = & iface;

    /* Also bind the export to self */
    base_type::bind(* static_cast<fw_interface_type *>(this));
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_fw_transport_if interface to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::operator() (amba_pv_fw_transport_if & iface) {
    bind(iface);
}

/*
 * Blocking transport.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::b_transport(amba_pv_transaction & trans, sc_core::sc_time & t) {
    if (m_interface == NULL) {
        report_error("b_transport(): instance has no interface");
    }
    m_interface->b_transport(get_socket_id(), trans, t);
}

/*
 * Debug access to a target.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline unsigned int
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::transport_dbg(amba_pv_transaction & trans) {
    if (m_interface == NULL) {

        /* No debug support */
        return 0;
    }
    return (m_interface->transport_dbg(get_socket_id(), trans));
}

/*
 * Requests a DMI access based on the specified transaction.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline bool
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::get_direct_mem_ptr(amba_pv_transaction & trans, tlm::tlm_dmi & dmi_data) {
    if (m_interface == NULL) {

        /* No DMI support */
        dmi_data.allow_read_write();
        dmi_data.set_start_address(0x0);
        dmi_data.set_end_address(sc_dt::uint64(-1));
        return false;
    }
    return (m_interface->get_direct_mem_ptr(get_socket_id(), trans, dmi_data));
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
amba_pv_base_slave_socket<BUSWIDTH,
                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                          ,POL
#endif
                         >::nb_transport_fw(amba_pv_transaction & trans, tlm::tlm_phase &, sc_core::sc_time &) {
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
amba_pv_base_slave_socket<BUSWIDTH,
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
amba_pv_slave_socket<BUSWIDTH,
                     N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                     ,POL
#endif
                    >::amba_pv_slave_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_slave_socket")) {
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
amba_pv_slave_socket<BUSWIDTH,
                     N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                     ,POL
#endif
                    >::amba_pv_slave_socket(const char * name, int socket_id /* = 0 */):
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
amba_pv_slave_socket<BUSWIDTH,
                     N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                     ,POL
#endif
                    >::kind() const  {
    return ("amba_pv_slave_socket");
}

/**
 * @brief       Invalidates DMI pointers previously established for the specified DMI region.
 *
 * @param       index interface index (for sockets bound more than once).
 * @param       start_range DMI region start address.
 * @param       end_range DMI region end address.
 *
 * This version of the method forwards the invalidate_direct_mem_ptr() call to the @a index'ed master socket this slave
 * socket is bound to.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL
#endif
        >
inline void
amba_pv_slave_socket<BUSWIDTH,
                     N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                     ,POL
#endif
                    >::invalidate_direct_mem_ptr(int index, sc_dt::uint64 start_range, sc_dt::uint64 end_range) {
    (* this)[index]->invalidate_direct_mem_ptr(start_range, end_range);
}

/**
 * @brief       Invalidates DMI pointers previously established for the specified DMI region.
 *
 * @param       start_range DMI region start address.
 * @param       end_range DMI region end address.
 *
 * This version of the method forwards the invalidate_direct_mem_ptr() call to the master socket this slave socket is
 * bound to.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL
#endif
        >
inline void
amba_pv_slave_socket<BUSWIDTH,
                     N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                     ,POL
#endif
                    >::invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range) {
    invalidate_direct_mem_ptr(0, start_range, end_range);
}

}   /* namespace ext */

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_EXT_SLAVE_SOCKET__H) */
