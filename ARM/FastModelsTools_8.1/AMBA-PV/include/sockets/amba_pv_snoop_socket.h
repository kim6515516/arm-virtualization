/*
 * AMBA-PV: amba_pv_snoop_socket.h - AMBA-PV slave socket used to implement the 
 *                                   upstream ACE snoop interface
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_SNOOP_SOCKET__H
#define AMBA_PV_SNOOP_SOCKET__H

/**
 * @file        amba_pv_snoop_socket.h
 *
 * @brief       AMBA-PV slave socket used to implement the upstream ACE snoop
 *              interface
 */

/* Includes */
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "bus/amba_pv_extension.h"
#include "core/amba_pv_types.h"
#include "core/amba_pv_core_ifs.h"
#include "user/amba_pv_if.h"
#include "sockets/amba_pv_socket_base.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV slave socket used to implement the upstream ACE snoop
 *              interface
 *
 * amba_pv_snoop_socket is the upstream ACE slave socket that is a private data
 * member of each amba_pv_ace_master_socket.
 *
 * amba_pv_snoop_socket provides implementations for the amba_pv_bw_snoop_if
 * user-layer interface.
 *
 * This socket inherits from the OSCI TLM 2.0
 * @c tlm_utils::simple_target_socket_tagged class. A tagged socket enables a
 * component to determine through which socket an incoming method call arrived.
 * This is required if there are multiple master sockets such as in, for
 * example, a bus decoder.
 *
 * @note        The current implementation of amba_pv_snoop_socket inherits
 *              from OSCI TLM 2.0 @c tlm_utils::simple_target_socket_tagged.
 *              Hence, if compiling applications that use
 *              amba_pv_snoop_socket with OSCI SystemC, it is required to
 *              define the macro @c SC_INCLUDE_DYNAMIC_PROCESSES before
 *              including the OSCI SystemC header file.
 *
 * @note        This socket, as its base class
 *              @c tlm_utils::simple_target_socket_tagged, does not support
 *              hierarchical binding, master-socket-to-master-socket or
 *              slave-socket-to-slave-socket
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_snoop_socket:
    public amba_pv_socket_base,
    public tlm_utils::simple_target_socket_tagged<amba_pv_bw_snoop_if,
                                                  BUSWIDTH,
                                                  amba_pv_protocol_types> {

    /* Typdefs */
    public:
        typedef
            tlm_utils::simple_target_socket_tagged<amba_pv_bw_snoop_if,
                                                   BUSWIDTH,
                                                   amba_pv_protocol_types>
            base_type;

    /* Constructor */
        amba_pv_snoop_socket();
        explicit amba_pv_snoop_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        using base_type::bind;
        using base_type::operator();
        void bind(amba_pv_bw_snoop_if & iface);
        void operator() (amba_pv_bw_snoop_if & iface);
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_snoop_socket<BUSWIDTH>::amba_pv_snoop_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_snoop_socket")) {
}

/**
 * @brief       Constructor.
 *
 * @param       name socket name.
 * @param       socket_id socket identifier (defaults to 0).
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_snoop_socket<BUSWIDTH>::amba_pv_snoop_socket(const char * name,
                                                     int socket_id /* = 0 */):
    amba_pv_socket_base(socket_id),
    base_type(name) {
}

/**
 * @brief       Returns the kind string of this socket.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_snoop_socket<BUSWIDTH>::kind() const  {
    return ("amba_pv_snoop_socket");
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_bw_snoop_if interface to bind to this
 *              socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_snoop_socket<BUSWIDTH>::bind(amba_pv_bw_snoop_if & iface) {
    register_b_transport(& iface,
                         & amba_pv_bw_snoop_if::b_snoop,
                         this->get_socket_id());
    register_transport_dbg(& iface,
                           & amba_pv_bw_snoop_if::snoop_dbg,
                           this->get_socket_id());
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_bw_snoop_if interface to bind to this
 *              socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_snoop_socket<BUSWIDTH>::operator() (amba_pv_bw_snoop_if & iface) {
    bind(iface);
}

}   /* namespave amba_pv */

#endif  /* defined(AMBA_PV_SNOOP_SOCKET__H) */
