/*
 * AMBA-PV: signal_bridges.h - Generic sc_signal - Signal(State) bridge modules.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef SIGNAL_BRIDGES__H
#define SIGNAL_BRIDGES__H

/**
 * @file        signal_bridges.h
 *
 * @brief       Generic sc_signal - Signal(State) bridge modules.
 */

/* Includes */
#include "signal_request.h"
#include "signal_core_ifs.h"
#include "signal_master_port.h"
#include "signal_slave_export.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       Generic sc_signal to Signal bridge module.
 *
 * The signal_from_sc_bridge class translates @c sc_signal events into
 * Signal transactions.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_from_sc_bridge: public sc_core::sc_module {
    SC_HAS_PROCESS(signal_from_sc_bridge);

    /* Ports */
    public:

        /**
         * @brief SystemC signal in.
         */
        sc_core::sc_in<STATE> signal_in;

        /**
         * @brief Master port to Signal.
         */
        signal_master_port<STATE> signal_m;

    /* Constructor */
        explicit signal_from_sc_bridge(const sc_core::sc_module_name &);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Implementation */
    private:
        void signal();
};

/**
 * @brief       Generic Signal to sc_signal bridge module.
 *
 * The signal_to_sc_bridge class translates Signal transactions into
 * @c sc_signal events.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_to_sc_bridge:
    public virtual signal_transport_if<STATE>,
    public sc_core::sc_module {

    /* Typdefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;

    /* Ports */
    public:

        /**
         * @brief Signal slave export.
         */
        signal_slave_export<STATE> signal_s;

        /**
         * @brief Out sc_signal.
         */
        sc_core::sc_out<STATE> signal_out;

    /* Constructor */
        explicit signal_to_sc_bridge(const sc_core::sc_module_name &);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bidirectional non-blocking interface */
    protected:
        virtual response_type nb_transport(int, const request_type &);
};

/**
 * @brief       Generic sc_signal to SignalState bridge module.
 *
 * The signal_state_from_sc_bridge class translates @c sc_signal events into
 * SignalState transactions.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_state_from_sc_bridge: public sc_core::sc_module {
    SC_HAS_PROCESS(signal_state_from_sc_bridge);

    /* Ports */
    public:

        /**
         * @brief SystemC signal in.
         */
        sc_core::sc_in<STATE> signal_in;

        /**
         * @brief Master port to SignalState.
         */
        signal_state_master_port<STATE> signal_m;

    /* Constructor */
        explicit signal_state_from_sc_bridge(const sc_core::sc_module_name &);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Implementation */
    private:
        void signal();
};

/**
 * @brief       Generic SignalState to sc_signal bridge module.
 *
 * The signal_state_to_sc_bridge class translates SignalState transactions into
 * @c sc_signal events.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_state_to_sc_bridge:
    public virtual signal_state_transport_if<STATE>,
    public sc_core::sc_module {

    /* Typdefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;

    /* Ports */
    public:

        /**
         * @brief SignalState slave export.
         */
        signal_state_slave_export<STATE> signal_s;

        /**
         * @brief Out sc_signal.
         */
        sc_core::sc_out<STATE> signal_out;

    /* Constructor */
        explicit signal_state_to_sc_bridge(const sc_core::sc_module_name &);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bidirectional non-blocking interface */
    protected:
        virtual response_type nb_transport(int, const request_type &);
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name bridge name.
 */
template<typename STATE>
inline signal_from_sc_bridge<STATE>::signal_from_sc_bridge(const sc_core::sc_module_name & name):
    sc_core::sc_module(name),
    signal_in("signal_in"),
    signal_m("signal_m") {

    /* Process(es) */
    SC_METHOD(signal);
    sensitive << signal_in;
}

/**
 * @brief       Returns the kind string of this bridge.
 */
template<typename STATE>
inline const char * signal_from_sc_bridge<STATE>::kind() const  {
    return ("signal_from_sc_bridge");
}

/*
 * Translates sc_signal events into Signal transactions.
 */
template<typename STATE>
inline void signal_from_sc_bridge<STATE>::signal() {
    signal_m.set_state(0, signal_in.read());
}

/**
 * @brief       Constructor.
 *
 * @param       name bridge name.
 */
template<typename STATE>
inline signal_to_sc_bridge<STATE>::signal_to_sc_bridge(const sc_core::sc_module_name & name):
    sc_core::sc_module(name),
    signal_s("signal_s"),
    signal_out("signal_out") {

    /* Bindings */
    signal_s(* this);
}

/**
 * @brief       Returns the kind string of this bridge.
 */
template<typename STATE>
inline const char * signal_to_sc_bridge<STATE>::kind() const  {
    return ("signal_to_sc_bridge");
}

/**
 * @brief       Bidirectional non-blocking transport.
 *
 * This version of the method translates Signal transactions into @c sc_signal
 * events.
 */
template<typename STATE>
inline signal_response<STATE>
signal_to_sc_bridge<STATE>::nb_transport(int export_id,
                                         const request_type & req) {
    static response_type rsp;
                                    
    switch (req.get_command()) {
        case SIGNAL_SET:  /* Set command */
            signal_out.write(req.get_state());
            break;
        default:
            sc_assert(false);
    }
    return (rsp);
}

/**
 * @brief       Constructor.
 *
 * @param       name bridge name.
 */
template<typename STATE>
inline
signal_state_from_sc_bridge<STATE>::signal_state_from_sc_bridge(const sc_core::sc_module_name & name):
    sc_core::sc_module(name),
    signal_in("signal_in"),
    signal_m("signal_m") {

    /* Process(es) */
    SC_METHOD(signal);
    sensitive << signal_in;
}

/**
 * @brief       Returns the kind string of this bridge.
 */
template<typename STATE>
inline const char * signal_state_from_sc_bridge<STATE>::kind() const  {
    return ("signal_state_from_sc_bridge");
}

/*
 * Translates sc_signal events into SignalState transactions.
 */
template<typename STATE>
inline void signal_state_from_sc_bridge<STATE>::signal() {
    signal_m.set_state(0, signal_in.read());
}

/**
 * @brief       Constructor.
 *
 * @param       name bridge name.
 */
template<typename STATE>
inline
signal_state_to_sc_bridge<STATE>::signal_state_to_sc_bridge(const sc_core::sc_module_name & name):
    sc_core::sc_module(name),
    signal_s("signal_s"),
    signal_out("signal_out") {

    /* Bindings */
    signal_s(* this);
}

/**
 * @brief       Returns the kind string of this bridge.
 */
template<typename STATE>
inline const char * signal_state_to_sc_bridge<STATE>::kind() const  {
    return ("signal_state_to_sc_bridge");
}

/**
 * @brief       Bidirectional non-blocking transport.
 *
 * This version of the method translates SignalState transactions into
 * @c sc_signal events.
 */
template<typename STATE>
inline signal_response<STATE>
signal_state_to_sc_bridge<STATE>::nb_transport(int export_id,
                                               const request_type & req) {
    static response_type rsp;
                                    
    switch (req.get_command()) {
        case SIGNAL_GET:  /* Get command */
            rsp.set_state(signal_out.read());
            break;
        case SIGNAL_SET:  /* Set command */
            signal_out.write(req.get_state());
            break;
        default:
            sc_assert(false);
    }
    return (rsp);
}

}   /* namespace amba_pv */

#endif  /* defined(SIGNAL_BRIDGES__H) */
