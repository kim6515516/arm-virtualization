/*
 * AMBA-PV: amba_pv_slave_socket.h - AMBA-PV socket to be instantiated on the
 *                                   slave side.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_SLAVE_SOCKET__H
#define AMBA_PV_SLAVE_SOCKET__H

/**
 * @file        amba_pv_slave_socket.h
 *
 * @brief       AMBA-PV socket to be instantiated on the slave side.
 */

/* Includes */
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/simple_initiator_socket.h>
#include "bus/amba_pv_extension.h"
#include "core/amba_pv_core_ifs.h"
#include "sockets/amba_pv_socket_base.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV socket to be instantiated on the slave side.
 *
 * This socket inherits from the OSCI TLM 2.0
 * @c tlm_utils::simple_target_socket_tagged class. A tagged socket allows a
 * component to determine through which socket an incoming method call
 * arrived. This is required if there are multiple slave sockets such as in,
 * for example, an interconnect or a multi-port memory.
 *
 * @note        This version of the amba_pv_slave_socket class inherits
 *              from the OSCI TLM 2.0 @c tlm_utils::simple_target_socket_tagged
 *              class. Hence, if compiling applications that use
 *              amba_pv_slave_socket with OSCI SystemC, it is required to
 *              define the macro @c SC_INCLUDE_DYNAMIC_PROCESSES before
 *              including the OSCI SystemC header file.
 *
 * @note        This socket, as its base class
 *              @c tlm_utils::simple_target_socket_tagged, does not support
 *              hierarchical binding, master-socket-to-master-socket or
 *              slave-socket-to-slave-socket.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_slave_socket:
    public amba_pv_socket_base,
    public tlm_utils::simple_target_socket_tagged<amba_pv_fw_transport_if,
                                                  BUSWIDTH,
                                                  amba_pv_protocol_types> {

    /* Typdefs */
    public:
        typedef
            tlm_utils::simple_target_socket_tagged<amba_pv_fw_transport_if,
                                                   BUSWIDTH,
                                                   amba_pv_protocol_types>
            base_type;

    /* Constructor */
        amba_pv_slave_socket();
        explicit amba_pv_slave_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Backward DMI invalidation */
        void invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);
        void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64);

    /* Bindings */
        using base_type::bind;
        using base_type::operator();
        void bind(amba_pv_fw_transport_if &);
        void operator() (amba_pv_fw_transport_if &);
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_slave_socket<BUSWIDTH>::amba_pv_slave_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_slave_socket")) {
}

/**
 * @brief       Constructor.
 *
 * @param       name socket name.
 * @param       socket_id socket identifier (defaults to 0).
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_slave_socket<BUSWIDTH>::amba_pv_slave_socket(const char * name,
                                                     int socket_id /* = 0 */):
    amba_pv_socket_base(socket_id),
    base_type(name) {
}

/**
 * @brief       Returns the kind string of this socket.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_slave_socket<BUSWIDTH>::kind() const  {
    return ("amba_pv_slave_socket");
}

/**
 * @brief       Invalidates DMI pointers previously established for the
 *              specified DMI region.
 *
 * @param       socket_id socket identifier (ignored on the slave side).
 * @param       start_range DMI region start address.
 * @param       end_range DMI region end address.
 *
 * This version of the method forwards the invalidate_direct_mem_ptr() call to
 * the master socket this slave socket is bound to.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_slave_socket<BUSWIDTH>::invalidate_direct_mem_ptr(int socket_id,
                                                          sc_dt::uint64 start_range,
                                                          sc_dt::uint64 end_range) {
    (* this)->invalidate_direct_mem_ptr(start_range, end_range);
}

/**
 * @brief       Invalidates DMI pointers previously established for the
 *              specified DMI region.
 *
 * @param       start_range DMI region start address.
 * @param       end_range DMI region end address.
 *
 * This version of the method forwards the invalidate_direct_mem_ptr() call to
 * the master socket this slave socket is bound to.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_slave_socket<BUSWIDTH>::invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                          sc_dt::uint64 end_range) {
    invalidate_direct_mem_ptr(0, start_range, end_range);
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_fw_transport_if interface to bind to this
 *              socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_slave_socket<BUSWIDTH>::bind(amba_pv_fw_transport_if & iface) {
    register_b_transport(& iface,
                         & amba_pv_fw_transport_if::b_transport,
                         this->get_socket_id());
    register_transport_dbg(& iface,
                           & amba_pv_fw_transport_if::transport_dbg,
                           this->get_socket_id());
    register_get_direct_mem_ptr(& iface,
                                & amba_pv_fw_transport_if::get_direct_mem_ptr,
                                this->get_socket_id());
    register_nb_transport_fw(& iface,
                             & amba_pv_fw_transport_if::nb_transport_fw,
                             this->get_socket_id());
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_fw_transport_if interface to bind to this
 *              socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_slave_socket<BUSWIDTH>::operator() (amba_pv_fw_transport_if & iface) {
    bind(iface);
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_SLAVE_SOCKET__H) */
