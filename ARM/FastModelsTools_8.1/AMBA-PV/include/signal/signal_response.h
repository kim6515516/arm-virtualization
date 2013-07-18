/*
 * AMBA-PV: signal_response.h - Signal response type.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef SIGNAL_RESPONSE__H
#define SIGNAL_RESPONSE__H

/**
 * @file        signal_response.h
 *
 * @brief       Signal response type.
 */

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       Signal response type.
 *
 * This class is for use with the signal_transport_if core interface.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_response {

    /* Construction */
    public:
        signal_response();
        signal_response(const STATE &);

    /* Accessors */
        void set_state(const STATE &);
        STATE get_state() const;

    /* Implementation */
    protected:
        STATE m_state;
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<typename STATE>
inline signal_response<STATE>::signal_response():
    m_state(STATE()) {
}

/**
 * @brief       Signal response constructor.
 * 
 * @param       state signal state.
 */
template<typename STATE>
inline signal_response<STATE>::signal_response(const STATE & state):
    m_state(state) {
}

/**
 * @brief       Sets the signal state.
 * 
 * @param       state signal state.
 */
template<typename STATE>
inline void signal_response<STATE>::set_state(const STATE & state) {
    m_state = state;
}

/**
 * @brief       Returns the signal state.
 */
template<typename STATE>
inline STATE signal_response<STATE>::get_state() const {
    return (m_state);
}  

}   /* namespace amba_pv */

#endif  /* defined(SIGNAL_RESPONSE__H) */
