/*
 * AMBA-PV: signal_master_port.h - Signal and SignalState ports to be
 *                                 instantiated on the master side.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef SIGNAL_MASTER_PORT__H
#define SIGNAL_MASTER_PORT__H

/**
 * @file        signal_master_port.h
 *
 * @brief       Signal and SignalState ports to be instantiated on the master
 *              side.
 */

/* Includes */
#include "signal/signal_request.h"
#include "signal/signal_response.h"
#include "signal/signal_core_ifs.h"
#include "signal/signal_if.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       Signal port to be instantiated on the master side.
 *
 * This port is for use as a master port bound to one or more slave exports.
 *
 * signal_master_port provides an implementation of the signal_if interface.
 *
 * @param       STATE signal state type.
 * @param       N number of bindings; defaults to 1.
 * @param       POL port binding policy; defaults to
 *              @c sc_core::SC_ONE_OR_MORE_BOUND.
 */
template<typename STATE,
         int N = 1
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
#endif
        >
class signal_master_port:
    public virtual signal_if<STATE>,
    public sc_core::sc_port<nonblocking_transport_if<signal_request<STATE>,
                                                     signal_response<STATE> >,
                            N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                            ,POL
#endif
                           > {

    /* Typdefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;
    typedef nonblocking_transport_if<request_type, response_type> iface_type;
    typedef
        sc_core::sc_port<iface_type,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                        >
        base_type;

    /* Constructor */
    public:
        signal_master_port();
        explicit signal_master_port(const char *);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* User-layer interface */
        virtual void set_state(int, const STATE &);
        void set_state(const STATE &);
};

/**
 * @brief       SignalState port to be instantiated on the master side.
 *
 * This port is for use as a master port bound to one or more slave exports.
 *
 * signal_state_master_port provides an implementation of the signal_state_if
 * interface.
 *
 * @param       STATE signal state type.
 * @param       N number of bindings; defaults to 1.
 * @param       POL port binding policy; defaults to
 *              @c sc_core::SC_ONE_OR_MORE_BOUND.
 */
template<typename STATE,
         int N = 1
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
#endif
        >
class signal_state_master_port:
    public virtual signal_state_if<STATE>,
    public sc_core::sc_port<nonblocking_transport_if<signal_request<STATE>,
                                                     signal_response<STATE> >,
                            N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                            ,POL
#endif
                           > {

    /* Typdefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;
    typedef nonblocking_transport_if<request_type, response_type> iface_type;
    typedef
        sc_core::sc_port<iface_type,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                        >
        base_type;

    /* Constructor */
    public:
        signal_state_master_port();
        explicit signal_state_master_port(const char *);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* User-layer interface */
        virtual void set_state(int, const STATE &);
        void set_state(const STATE &);
        virtual STATE get_state(int, tlm::tlm_tag<STATE> * = NULL);
        STATE get_state(tlm::tlm_tag<STATE> * = NULL);
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline
signal_master_port<STATE,
                   N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                   ,POL
#endif
                  >::signal_master_port():
    base_type(sc_core::sc_gen_unique_name("signal_master_port")) {
}

/**
 * @brief       Parameterized constructor.
 *
 * @param       name port name.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline
signal_master_port<STATE,
                   N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                   ,POL
#endif
                  >::signal_master_port(const char * name):
    base_type(name) {
}

/**
 * @brief       Returns the kind string of this port.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline const char *
signal_master_port<STATE,
                   N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                   ,POL
#endif
                  >::kind() const  {
    return ("signal_master_port");
}

/**
 * @brief       Transfers a signal state.
 *
 * This version of the method forward the user-layer set_state() call to the
 * Signal core interface signal_transport_if.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
signal_master_port<STATE,
                   N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                   ,POL
#endif
                  >::set_state(int export_id, const STATE & state) {
    request_type req(state);

    req.set_command(SIGNAL_SET);
    (* this)->nb_transport(req);
}

/**
 * @brief       Transfers a signal state.
 *
 * @param       state signal state.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
signal_master_port<STATE,
                   N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                   ,POL
#endif
                  >::set_state(const STATE & state) {
    set_state(0, state);
}

/**
 * @brief       Default constructor.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline
signal_state_master_port<STATE,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                         >::signal_state_master_port():
    base_type(sc_core::sc_gen_unique_name("signal_state_master_port")) {
}

/**
 * @brief       Parameterized constructor.
 *
 * @param       name port name.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline
signal_state_master_port<STATE,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                         >::signal_state_master_port(const char * name):
    base_type(name) {
}

/**
 * @brief       Returns the kind string of this port.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline const char *
signal_state_master_port<STATE,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                         >::kind() const  {
    return ("signal_state_master_port");
}

/**
 * @brief       Transfers a signal state.
 *
 * This version of the method forwards the user-layer set_state() call to the
 * SignalState core interface signal_state_transport_if.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
signal_state_master_port<STATE,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                         >::set_state(int export_id, const STATE & state) {
    request_type req(state);

    req.set_command(SIGNAL_SET);
    (* this)->nb_transport(req);
}

/**
 * @brief       Transfers a signal state.
 *
 * @param       state signal state.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline void
signal_state_master_port<STATE,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                         >::set_state(const STATE & state) {
    set_state(0, state);
}

/**
 * @brief       Retrieves the signal state.
 *
 * This version of the method forwards the user-layer get_state() call to the
 * Signal core interface signal_transport_if.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline STATE
signal_state_master_port<STATE,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                         >::get_state(int export_id,
                                      tlm::tlm_tag<STATE> * /* = NULL */) {
    request_type req;
    response_type rsp;

    req.set_command(SIGNAL_GET);
    rsp = (* this)->nb_transport(req);
    return (rsp.get_state());
}

/**
 * @brief       Retrieves the signal state.
 */
template<typename STATE,
         int N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
         ,sc_core::sc_port_policy POL 
#endif
        >
inline STATE
signal_state_master_port<STATE,
                         N
#if ! (defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION <= 20050714))
                         ,POL
#endif
                         >::get_state(tlm::tlm_tag<STATE> * /* = NULL */) {
    return (get_state(0, NULL));
}

}   /* namespace amba_pv */

#endif  /* defined(SIGNAL_MASTER_PORT__H) */
