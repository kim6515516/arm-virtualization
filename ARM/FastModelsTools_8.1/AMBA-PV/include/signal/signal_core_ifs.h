/*
 * AMBA-PV: signal_core_ifs.h - Signal core interfaces.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef SIGNAL_CORE_IFS__H
#define SIGNAL_CORE_IFS__H

/**
 * @file        signal_core_ifs.h
 *
 * @brief       Signal core interfaces.
 */

/* Includes */
#include "signal/signal_request.h"
#include "signal/signal_response.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       Non-blocking transport core interface.
 *
 * This is a non-blocking variant of the @c tlm::tlm_transport_if interface.
 *
 * @param       REQ request type.
 * @param       RSP response type.
 */
template<typename REQ, typename RSP>
class nonblocking_transport_if: public virtual sc_core::sc_interface {

    /* Bidirectional non-blocking interface */
    public:

        /**
         * @brief Bidirectional non-blocking transport.
         *
         * @param req signal request.
         *
         * @return the signal response.
         */
        virtual RSP nb_transport(const REQ & req) = 0;
};

/**
 * @brief       Signal core interface.
 *
 * This is a tagged variant of the nonblocking_transport_if interface.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_transport_if: public virtual sc_core::sc_interface {

    /* Typedefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;

    /* Bidirectional non-blocking interface */
    public:

        /**
         * @brief Bidirectional non-blocking transport.
         *
         * @param export_id export identifier (for multi-export slave).
         * @param req signal request.
         *
         * @return the signal response.
         */
        virtual response_type nb_transport(int export_id,
                                           const request_type & req) = 0;
};

/**
 * @brief       SignalState core interface.
 *
 * This is an indirect tagged variant of the nonblocking_transport_if
 * interface through signal_transport_if.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_state_transport_if:
    public virtual signal_transport_if<STATE> {
};

}   /* namespave amba_pv */

#endif  /* defined(SIGNAL_CORE_IFS__H) */
