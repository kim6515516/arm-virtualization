/*
 * TLMX: tlmx_target_socket.h - TLM 2.0 extended target socket.
 *
 * Copyright 2012 ARM Limited.
 * All rights reserved.
 */

#ifndef TLMX_TARGET_SOCKET__H
#define TLMX_TARGET_SOCKET__H

/**
 * @file        tlmx_target_socket.h
 *
 * @brief       TLM 2.0 extended target socket.
 */

/* Includes */
#include "tlmx/tlmx_bw_ifs.h"

/* Namespaces */

/**
 * @brief       TLMX namespace.
 */
namespace tlmx {

/* Forwards */

/* Datatypes */

/**
 * @brief       TLMX target socket.
 *
 * Principal target full-duplex socket, parameterized with protocol traits
 * class.
 * This full-duplex socket is for use as a target socket bound to one or
 * more initiator full-duplex sockets.
 *
 * @note        The current implementation of tlmx_target_socket inherits
 *              from OSCI TLM 2.0 @c tlm::tlm_base_target_socket.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024; defaults to 64.
 * @param       TYPES protocol traits class; defaults to
 *              @c tlm::tlm_base_protocol_types.
 * @param       N number of bindings; defaults to 1.
 * @param       POL port binding policy; defaults to
 *              @c sc_core::SC_ONE_OR_MORE_BOUND.
 */
template<unsigned int BUSWIDTH = 32,
         typename TYPES = tlm::tlm_base_protocol_types,
         int N = 1
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
#endif
        >
class tlmx_target_socket:
    public tlm::tlm_base_target_socket<BUSWIDTH,
                                       tlm::tlm_fw_transport_if<TYPES>,
                                       tlmx_bw_transport_if<TYPES>,
                                       N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                       ,POL
#endif
                                      > {
    public:

        /* Typedefs */
        typedef tlm::tlm_base_target_socket<BUSWIDTH,
                                            tlm::tlm_fw_transport_if<TYPES>,
                                            tlmx_bw_transport_if<TYPES>,
                                            N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                            ,POL
#endif
                                           > base_type;

        /* Construction */
        tlmx_target_socket();
        explicit tlmx_target_socket(const char * name);

        /* sc_object overridables */
        virtual const char * kind() const;
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<unsigned int BUSWIDTH,
         typename TYPES,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL
#endif
        >
inline
tlmx_target_socket<BUSWIDTH,
                   TYPES,
                   N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                   ,POL
#endif
                  >::tlmx_target_socket():
    base_type(sc_core::sc_gen_unique_name("tlmx_target_socket")) {
}

/**
 * @brief       Constructor.
 *
 * @param       name socket name.
 */
template<unsigned int BUSWIDTH,
         typename TYPES,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL
#endif
        >
inline
tlmx_target_socket<BUSWIDTH,
                   TYPES,
                   N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                   ,POL
#endif
                  >::tlmx_target_socket(const char * name):
    base_type(name) {
}

/**
 * @brief       Returns the kind string of this socket.
 */
template<unsigned int BUSWIDTH,
         typename TYPES,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL
#endif
        >
inline const char *
tlmx_target_socket<BUSWIDTH,
                   TYPES,
                   N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                   ,POL
#endif
                  >::kind() const  {
    return ("tlmx_target_socket");
}

}   /* namespace tlmx */

#endif  /* defined(TLMX_TARGET_SOCKET__H) */
