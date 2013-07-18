/*
 * TLMX: tlmx_initiator_socket.h - TLM 2.0 extended initiator socket.
 *
 * Copyright 2012 ARM Limited.
 * All rights reserved.
 */

#ifndef TLMX_INITIATOR_SOCKET__H
#define TLMX_INITIATOR_SOCKET__H

/**
 * @file        tlmx_initiator_socket.h
 *
 * @brief       TLM 2.0 extended initiator socket.
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
 * @brief       TLMX initiator socket.
 *
 * Principal initiator full-duplex socket, parameterized with protocol traits
 * class.
 * This full-duplex socket is for use as an initiator socket bound to one or
 * more target full-duplex sockets.
 *
 * @note        The current implementation of tlmx_initiator_socket inherits
 *              from OSCI TLM 2.0 @c tlm::tlm_base_initiator_socket.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024; defaults to 64.
 * @param       TYPES protocol traits class; defaults to
 *              @c tlm::tlm_base_protocol_types.
 * @param       N number of bindings. Defaults to 1.
 * @param       POL port binding policy. Defaults to
 *              @c sc_core::SC_ONE_OR_MORE_BOUND.
 */
template<unsigned int BUSWIDTH = 32,
         typename TYPES = tlm::tlm_base_protocol_types,
         int N = 1
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
#endif
        >
class tlmx_initiator_socket:
    public tlm::tlm_base_initiator_socket<BUSWIDTH,
                                          tlm::tlm_fw_transport_if<TYPES>,
                                          tlmx_bw_transport_if<TYPES>,
                                          N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                          ,POL
#endif
                                         > {
    public:

        /* Typedefs */
        typedef tlm::tlm_base_initiator_socket<BUSWIDTH,
                                               tlm::tlm_fw_transport_if<TYPES>,
                                               tlmx_bw_transport_if<TYPES>,
                                               N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                                               ,POL
#endif
                                              > base_type;

        /* Construction */
        tlmx_initiator_socket();
        explicit tlmx_initiator_socket(const char * name);

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
tlmx_initiator_socket<BUSWIDTH,
                      TYPES,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::tlmx_initiator_socket():
    base_type(sc_core::sc_gen_unique_name("tlmx_initiator_socket")) {
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
tlmx_initiator_socket<BUSWIDTH,
                      TYPES,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::tlmx_initiator_socket(const char * name):
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
tlmx_initiator_socket<BUSWIDTH,
                      TYPES,
                      N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                      ,POL
#endif
                     >::kind() const  {
    return ("tlmx_initiator_socket");
}

}   /* namespace tlmx */

#endif  /* defined(TLMX_INITIATOR_SOCKET__H) */
