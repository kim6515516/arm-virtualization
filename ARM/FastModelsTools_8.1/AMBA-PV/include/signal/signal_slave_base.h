/*
 * AMBA-PV: signal_slave_base.h - Base class for all Signal and SignalState
 *                                slave modules.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef SIGNAL_SLAVE_BASE__H
#define SIGNAL_SLAVE_BASE__H

/**
 * @file        signal_slave_base.h
 *
 * @brief       Base class for all Signal and SignalState slave modules.
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
 * @brief       Base class for all Signal slave modules.
 *
 * @note        signal_slave_base is not an @c sc_module.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_slave_base:
    public virtual signal_transport_if<STATE>,
    public virtual signal_if<STATE> {

    /* Typedefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;

    /* Constructor */
    public:
        explicit signal_slave_base(const std::string &);

    /* Accessors */
        std::string get_name() const;

    /* Signal interface - Default implementation */
    protected:
        virtual void set_state(int, const STATE &);

    /* Bidirectional non-blocking transfer */
        virtual response_type nb_transport(int, const request_type &);

    /* Implementation */
    private:
        std::string m_name;   /* Slave name. */
};

/**
 * @brief       Base class for all SignalState slave modules.
 *
 * signal_state_slave_base can be used instead of signal_slave_base.
 * This enables combining signal_slave_export and signal_state_slave_export in
 * the same @c sc_module.
 *
 * @note        signal_state_slave_base is not an @c sc_module.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_state_slave_base:
    public virtual signal_state_transport_if<STATE>,
    public virtual signal_state_if<STATE> {

    /* Typedefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;

    /* Constructor */
    public:
        explicit signal_state_slave_base(const std::string &);

    /* Accessors */
        std::string get_name() const;

    /* SignalState interface - Default implementation */
    protected:
        virtual void set_state(int, const STATE &);
        virtual STATE get_state(int, tlm::tlm_tag<STATE> * = NULL);

    /* Bidirectional non-blocking transfer */
        virtual response_type nb_transport(int, const request_type &);

    /* Implementation */
    private:
        std::string m_name;   /* Slave name. */
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name slave name.
 */
template<typename STATE>
inline signal_slave_base<STATE>::signal_slave_base(const std::string & name):
    m_name(name) {
}

/**
 * @brief       Returns the name of this slave.
 */
template<typename STATE>
inline std::string signal_slave_base<STATE>::get_name() const  {
    return (m_name);
}

/**
 * @brief       Transfers a signal state.
 *
 * This version of the method causes an error.
 */
template<typename STATE>
inline void
signal_slave_base<STATE>::set_state(int export_id, const STATE & state) {
    SC_REPORT_ERROR("signal_slave_base", "set_state(): not implemented");
}

/**
 * @brief       Completes a transaction.
 *
 * This version of the method translates this nb_transport() call into
 * signal_if user-layer calls.
 */
template<typename STATE>
inline signal_response<STATE>
signal_slave_base<STATE>::nb_transport(int export_id,
                                       const request_type & req) {
    static response_type rsp;
                                    
    switch (req.get_command()) {
        case SIGNAL_SET:  /* Set command */
            this->set_state(export_id, req.get_state());
            break;
        default:
            sc_assert(false);
    }
    return (rsp);
}

/**
 * @brief       Constructor.
 *
 * @param       name slave name.
 */
template<typename STATE>
inline
signal_state_slave_base<STATE>::signal_state_slave_base(const std::string & name):
    m_name(name) {
}

/**
 * @brief       Returns the name of this slave.
 */
template<typename STATE>
inline std::string signal_state_slave_base<STATE>::get_name() const  {
    return (m_name);
}

/**
 * @brief       Transfers a signal state.
 *
 * This version of the method causes an error.
 */
template<typename STATE>
inline void
signal_state_slave_base<STATE>::set_state(int export_id, const STATE & state) {
    SC_REPORT_ERROR("signal_slave_base", "set_state(): not implemented");
}

/**
 * @brief       Retrieves the signal state.
 *
 * This version of the method causes an error.
 */
template<typename STATE>
inline STATE
signal_state_slave_base<STATE>::get_state(int export_id,
                                          tlm::tlm_tag<STATE> * /* = NULL */) {
    static STATE s;

    SC_REPORT_ERROR("signal_slave_base", "get_state(): not implemented");
    return s;
}

/**
 * @brief       Completes a transaction.
 *
 * This version of the method translates this nb_transport() call into
 * signal_state_if user-layer calls.
 */
template<typename STATE>
inline signal_response<STATE>
signal_state_slave_base<STATE>::nb_transport(int export_id,
                                             const request_type & req) {
    response_type rsp;
                                    
    switch (req.get_command()) {
        case SIGNAL_GET:  /* Get command */
            rsp.set_state(this->get_state(export_id));
            break;
        case SIGNAL_SET:  /* Set command */
            this->set_state(export_id, req.get_state());
            break;
        default:
            sc_assert(false);
    }
    return (rsp);
}

}   /* namespace amba_pv */

#endif  /* defined(SIGNAL_SLAVE_BASE__H) */
