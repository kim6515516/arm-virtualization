/*
 * AMBA-PV: amba_pv_ext_master_socket.h - AMBA-PV socket to be instantiated on the master side and that supports
 *                                        hierarchical binding.
 *
 * Copyright 2007-2009, 2012-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXT_MASTER_SOCKET__H
#define AMBA_PV_EXT_MASTER_SOCKET__H

/**
 * @file        amba_pv_ext_master_socket.h
 *
 * @brief       AMBA-PV socket to be instantiated on the master side.
 */

/* Includes */
#include "core/amba_pv_types.h"
#include "core/amba_pv_core_ifs.h"
#include "bus/amba_pv_extension.h"
#include "sockets/amba_pv_socket_base.h"
#include "user/amba_pv_if.h"

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
class amba_pv_base_slave_socket;
     
/* Datatypes */

/**
 * @brief       AMBA-PV base master socket.
 *
 * This socket inherits from the OSCI TLM 2.0 @c tlm::tlm_initiator_socket class and implements a tagged socket.
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
class amba_pv_base_master_socket:
    protected virtual tlm::tlm_bw_transport_if<amba_pv_protocol_types>,
    public amba_pv_socket_base,
    public tlm::tlm_initiator_socket<BUSWIDTH,
                                     amba_pv_protocol_types,
                                     N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                     ,POL
#endif
                                    > {

    /* Typdefs */
    public:
        typedef tlm::tlm_initiator_socket<BUSWIDTH,
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
                                      >
            base_master_socket_type;
        typedef
            amba_pv_base_slave_socket<BUSWIDTH,
                                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                      ,POL
#endif
                                     >
            base_slave_socket_type;
        typedef tlm::tlm_bw_transport_if<amba_pv_protocol_types> bw_interface_type;

    /* Constructor */
        amba_pv_base_master_socket();
        explicit amba_pv_base_master_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        virtual void bind(base_master_socket_type &);
        void operator() (base_master_socket_type &);
        virtual void bind(base_slave_socket_type &);
        void operator() (base_slave_socket_type &);
        virtual void bind(amba_pv_bw_transport_if &);
        void operator() (amba_pv_bw_transport_if &);

    /* Implementation */
    private:

        /* Member variables */
        amba_pv_bw_transport_if * m_interface;

        /* TLM 2.0 backward interface */
        virtual void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64);
        virtual tlm::tlm_sync_enum nb_transport_bw(amba_pv_transaction &, tlm::tlm_phase &, sc_core::sc_time &);

        /* Helpers */
        void report_error(const char *);
};

/**
 * @brief       AMBA-PV socket to be instantiated on the master side.
 *
 * This socket is for use as a master socket bound to one or more slave sockets.
 *
 * amba_pv_master_socket provides implementations for the amba_pv_if user-layer interface.
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
class amba_pv_master_socket:
    public virtual amba_pv_if<BUSWIDTH>,
    public amba_pv_base_master_socket<BUSWIDTH,
                                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                      ,POL
#endif
                                     > {

    /* Typdefs */
    public:
        typedef
            amba_pv_base_master_socket<BUSWIDTH,
                                       N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                       ,POL
#endif
                                      >
            base_type;

    /* Constructor */
        amba_pv_master_socket();
        explicit amba_pv_master_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Convenience interface */
        virtual amba_pv_resp_t
        read(int, const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *, sc_core::sc_time &);
        amba_pv_resp_t
        read(const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *, sc_core::sc_time &);
        virtual amba_pv_resp_t
        write(int,
              const sc_dt::uint64 &,
              unsigned char *,
              unsigned int,
              const amba_pv_control *,
              unsigned char *,
              sc_core::sc_time &);
        amba_pv_resp_t
        write(const sc_dt::uint64 &,
              unsigned char *,
              unsigned int,
              const amba_pv_control *,
              unsigned char *,
              sc_core::sc_time &);
        virtual amba_pv_resp_t
        burst_read(int,
                   const sc_dt::uint64 &,
                   unsigned char *,
                   unsigned int,
                   unsigned int,
                   const amba_pv_control *,
                   amba_pv_burst_t,
                   sc_core::sc_time &);
        amba_pv_resp_t
        burst_read(const sc_dt::uint64 &,
                   unsigned char *,
                   unsigned int,
                   unsigned int,
                   const amba_pv_control *,
                   amba_pv_burst_t,
                   sc_core::sc_time &);
        virtual amba_pv_resp_t
        burst_write(int,
                    const sc_dt::uint64 &,
                    unsigned char *,
                    unsigned int,
                    unsigned int,
                    const amba_pv_control *,
                    amba_pv_burst_t,
                    unsigned char *,
                    unsigned int,
                    sc_core::sc_time &);
        amba_pv_resp_t
        burst_write(const sc_dt::uint64 &,
                    unsigned char *,
                    unsigned int,
                    unsigned int,
                    const amba_pv_control *,
                    amba_pv_burst_t,
                    unsigned char *,
                    unsigned int,
                    sc_core::sc_time &);
        virtual bool
        get_direct_mem_ptr(int, tlm::tlm_command, const sc_dt::uint64 &, const amba_pv_control *, tlm::tlm_dmi &);
        bool get_direct_mem_ptr(tlm::tlm_command, const sc_dt::uint64 &, const amba_pv_control *, tlm::tlm_dmi &);
        virtual unsigned int
        debug_read(int, const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *);
        virtual unsigned int
        debug_write(int, const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *);
        unsigned int debug_read(const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *);
        unsigned int debug_write(const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *);

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
amba_pv_base_master_socket<BUSWIDTH,
                           N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                           ,POL
#endif
                          >::amba_pv_base_master_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_base_master_socket")),
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
amba_pv_base_master_socket<BUSWIDTH,
                           N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                           ,POL
#endif
                          >::amba_pv_base_master_socket(const char * name, int socket_id /* = 0 */):
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
amba_pv_base_master_socket<BUSWIDTH,
                           N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                           ,POL
#endif
                          >::kind() const  {
    return ("amba_pv_base_master_socket");
}

/**
 * @brief       Binds this socket to the specified master socket (hierarchical bind).
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
amba_pv_base_master_socket<BUSWIDTH,
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
 * @param       s amba_pv_base_master_socket master socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_master_socket<BUSWIDTH,
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
 * @param       s amba_pv_base_slave_socket slave socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_master_socket<BUSWIDTH,
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
 * @param       s amba_pv_base_slave_socket slave socket to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_master_socket<BUSWIDTH,
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
 * @param       iface amba_pv_bw_transport_if interface to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_master_socket<BUSWIDTH,
                           N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                           ,POL
#endif
                          >::bind(amba_pv_bw_transport_if & iface) {
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
 * @param       iface amba_pv_bw_transport_if interface to bind to this socket.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
amba_pv_base_master_socket<BUSWIDTH,
                           N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                           ,POL
#endif
                          >::operator() (amba_pv_bw_transport_if & iface) {
    bind(iface);
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
amba_pv_base_master_socket<BUSWIDTH,
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
amba_pv_base_master_socket<BUSWIDTH,
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
amba_pv_base_master_socket<BUSWIDTH,
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
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::amba_pv_master_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_master_socket")) {
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
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::amba_pv_master_socket(const char * name, int socket_id /* = 0 */):
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
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::kind() const  {
    return ("amba_pv_master_socket");
}

/**
 * @brief       Completes a read transaction.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::read(int index,
                             const sc_dt::uint64 & addr,
                             unsigned char * data,
                             unsigned int size,
                             const amba_pv_control * ctrl,
                             sc_core::sc_time & t) {
    amba_pv_transaction trans;
    amba_pv_extension ex(size, ctrl);
    
    trans.set_read();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(size);
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        b_transport(index, trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ex.get_resp());
}

/**
 * @brief       Completes a read transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer.
 *              It must point to an array of @a size bytes.
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32, 64, 128].
 *              The transaction size must be less than or equal to the value returned by get_bus_width_bytes().
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused on the master side).
 * @param       t timing annotation.
 *
 * @return      @c AMBA_PV_OKAY if the transaction is successful.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::read(const sc_dt::uint64 & addr,
                             unsigned char * data,
                             unsigned int size,
                             const amba_pv_control * ctrl,
                             sc_core::sc_time & t) {
    return (read(0, addr, data, size, ctrl, t));
}

/**
 * @brief       Completes a write transaction.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::write(int index,
                              const sc_dt::uint64 & addr,
                              unsigned char * data,
                              unsigned int size,
                              const amba_pv_control * ctrl,
                              unsigned char * strb,
                              sc_core::sc_time & t) {
    amba_pv_transaction trans;
    amba_pv_extension ex(size, ctrl);

    trans.set_write();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(size);
    trans.set_byte_enable_ptr(strb);
    if (strb != NULL) {
        trans.set_byte_enable_length(size);
    }
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        b_transport(index, trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ex.get_resp());
}

/**
 * @brief       Completes a write transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer.
 *              It must point to an array of @a size bytes.
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32, 64, 128].
 *              The transaction size must be less than or equal to the value returned by get_bus_width_bytes().
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused on the master side).
 * @param       strb write strobes pointer (set to @c NULL if none).
 *              It must point to an array of @a size elements.
 * @param       t timing annotation.
 *
 * @return      @c AMBA_PV_OKAY if the transaction is successful.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::write(const sc_dt::uint64 & addr,
                              unsigned char * data,
                              unsigned int size,
                              const amba_pv_control * ctrl,
                              unsigned char * strb,
                              sc_core::sc_time & t) {
    return (write(0, addr, data, size, ctrl, strb, t));
}

/**
 * @brief       Completes a burst read transaction.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::burst_read(int index,
                                   const sc_dt::uint64 & addr,
                                   unsigned char * data,
                                   unsigned int length,
                                   unsigned int size,
                                   const amba_pv_control * ctrl,
                                   amba_pv_burst_t burst,
                                   sc_core::sc_time & t) {
    amba_pv_transaction trans;
    amba_pv_extension ex(length, size, ctrl, burst);

    trans.set_read();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(size * length);
    if (burst == AMBA_PV_FIXED) {
        trans.set_streaming_width(size);
    } else {
        trans.set_streaming_width(trans.get_data_length());
    };
    trans.set_extension(& ex);
    try {
        b_transport(index, trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ex.get_resp());
}

/**
 * @brief       Completes a burst read transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer.
 *              It must point to an array of (@a size * @a length) bytes.
 * @param       length transaction burst length as in [1-16].
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32, 64, 128].
 *              The transaction size must be less than or equal to the value returned by get_bus_width_bytes().
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused on the master side).
 * @param       burst transaction burst type, one of @c AMBA_PV_INCR, @c AMBA_PV_FIXED, or @c AMBA_PV_WRAP.
 * @param       t timing annotation.
 *
 * @return      @c AMBA_PV_OKAY if the transaction is successful.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::burst_read(const sc_dt::uint64 & addr,
                                   unsigned char * data,
                                   unsigned int length,
                                   unsigned int size,
                                   const amba_pv_control * ctrl,
                                   amba_pv_burst_t burst,
                                   sc_core::sc_time & t) {
    return (burst_read(0, addr, data, length, size, ctrl, burst, t));
}

/**
 * @brief       Completes a burst write transaction.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::burst_write(int index,
                                    const sc_dt::uint64 & addr,
                                    unsigned char * data,
                                    unsigned int length,
                                    unsigned int size,
                                    const amba_pv_control * ctrl,
                                    amba_pv_burst_t burst,
                                    unsigned char * strb,
                                    unsigned int strb_length,
                                    sc_core::sc_time & t) {
    amba_pv_transaction trans;
    amba_pv_extension ex(length, size, ctrl, burst);
    
    trans.set_write();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(size * length);
    if (burst == AMBA_PV_FIXED) {
        trans.set_streaming_width(size);
    } else {
        trans.set_streaming_width(trans.get_data_length());
    };
    trans.set_byte_enable_ptr(strb);
    if (strb != NULL) {
        trans.set_byte_enable_length(strb_length);
    }
    trans.set_extension(& ex);
    try {
        b_transport(index, trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ex.get_resp());
}

/**
 * @brief       Completes a burst write transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer.
 *              It must point to an array of (@a size * @a length) bytes.
 * @param       length transaction burst length as in [1-16].
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32, 64, 128].
 *              The transaction size must be less than or equal to the value returned by get_bus_width_bytes().
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused on the master side).
 * @param       burst transaction burst type, one of @c AMBA_PV_INCR, @c AMBA_PV_FIXED, or @c AMBA_PV_WRAP.
 * @param       strb write strobes pointer (set to @c NULL if none).
 * @param       strb_length Write strobes length. It must be a multiple of @a size.
 * @param       t timing annotation.
 *
 * @return      @c AMBA_PV_OKAY if the transaction is successful.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::burst_write(const sc_dt::uint64 & addr,
                                    unsigned char * data,
                                    unsigned int length,
                                    unsigned int size,
                                    const amba_pv_control * ctrl,
                                    amba_pv_burst_t burst,
                                    unsigned char * strb,
                                    unsigned int strb_length,
                                    sc_core::sc_time & t) {
    return (burst_write(0,
                        addr,
                        data,
                        length,
                        size,
                        ctrl,
                        burst,
                        strb,
                        strb_length,
                        t));
}

/**
 * @brief       Requests DMI access to the specified address and returns a reference to a DMI descriptor. 
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline bool
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::get_direct_mem_ptr(int index,
                                           tlm::tlm_command command,
                                           const sc_dt::uint64 & addr,
                                           const amba_pv_control * ctrl,
                                           tlm::tlm_dmi & dmi_data) {
    amba_pv_transaction trans;
    amba_pv_extension ex(this->get_bus_width_bytes(), ctrl);
    bool ret = false;
    
    if (command == tlm::TLM_READ_COMMAND) {
        trans.set_read();
    } else {
        trans.set_write();
    }
    trans.set_address(addr);
    trans.set_extension(& ex);
    try {
        ret = get_direct_mem_ptr(index, trans, dmi_data);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ret);
}

/**
 * @brief       Requests DMI access to the specified address and returns a reference to a DMI descriptor. 
 *
 * @param       command @c tlm::TLM_READ_COMMAND for a DMI read access request, @c tlm::TLM_WRITE_COMMAND for a DMI
 *              write access request.
 * @param       addr address to which the DMI access is requested.
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused on the master side).
 * @param       dmi_data returned DMI descriptor.
 *
 * @return      @c true if a DMI region is granted, @c false otherwise.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline bool
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::get_direct_mem_ptr(tlm::tlm_command command,
                                           const sc_dt::uint64 & addr,
                                           const amba_pv_control * ctrl,
                                           tlm::tlm_dmi & dmi_data) {
    return (get_direct_mem_ptr(0, command, addr, ctrl, dmi_data));
}


/**
 * @brief       Non-intrusive debug read transaction.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline unsigned int
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::debug_read(int index,
                                   const sc_dt::uint64 & addr,
                                   unsigned char * data,
                                   unsigned int length,
                                   const amba_pv_control * ctrl) {
    amba_pv_transaction trans;
    amba_pv_extension ex(1, 1, ctrl, AMBA_PV_INCR);
    unsigned int ret = 0;

    trans.set_read();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(length);
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        ret = transport_dbg(index, trans);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ret);
}

/**
 * @brief       Non-intrusive debug read transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer.
 *              It must point to an array of @a length bytes.
 * @param       length transaction length.
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused on the master side).
 *
 * @return      number of bytes read or, if error, 0.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline unsigned int
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::debug_read(const sc_dt::uint64 & addr,
                                   unsigned char * data,
                                   unsigned int length,
                                   const amba_pv_control * ctrl) {
    return (debug_read(0, addr, data, length, ctrl));
}

/**
 * @brief       Non-intrusive debug write transaction.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline unsigned int
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::debug_write(int index,
                                    const sc_dt::uint64 & addr,
                                    unsigned char * data,
                                    unsigned int length,
                                    const amba_pv_control * ctrl) {
    amba_pv_transaction trans;
    amba_pv_extension ex(1, 1, ctrl, AMBA_PV_INCR);
    unsigned int ret = 0;

    trans.set_write();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(length);
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        ret = transport_dbg(index, trans);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ret);
}

/**
 * @brief       Non-intrusive debug write transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer.
 *              It must point to an array of @a length bytes.
 * @param       length transaction length.
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused on the master side).
 *
 * @return      number of bytes written or, if error, 0.
 */
template<unsigned int BUSWIDTH,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline unsigned int
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::debug_write(const sc_dt::uint64 & addr,
                                    unsigned char * data,
                                    unsigned int length,
                                    const amba_pv_control * ctrl) {
    return (debug_write(0, addr, data, length, ctrl));
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
amba_pv_master_socket<BUSWIDTH,
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
amba_pv_master_socket<BUSWIDTH,
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
amba_pv_master_socket<BUSWIDTH,
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
amba_pv_master_socket<BUSWIDTH,
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
amba_pv_master_socket<BUSWIDTH,
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
amba_pv_master_socket<BUSWIDTH,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::get_direct_mem_ptr(amba_pv_transaction & trans, tlm::tlm_dmi & dmi_data) {
    return (get_direct_mem_ptr(0, trans, dmi_data));
}

}   /* namespave ext */

}   /* namespave amba_pv */

#endif  /* defined(AMBA_PV_EXT_MASTER_SOCKET__H) */
