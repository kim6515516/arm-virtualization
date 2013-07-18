/*
 * AMBA-PV: signal_request.h - Signal request type.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef SIGNAL_REQUEST__H
#define SIGNAL_REQUEST__H

/**
 * @file        signal_request.h
 *
 * @brief       Signal request type.
 */

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

 
/**
 * @brief       Signal request command type.
 */
enum signal_command {
    SIGNAL_SET = 0, /**< is the command to issue a set operation. */
    SIGNAL_GET      /**< is the command to issue a get operation. */
};

/**
 * @brief       Signal request type.
 *
 * This class is for use with the signal_transport_if and
 * signal_state_transport_if core interfaces.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_request {

    /* Construction */
    public:
        signal_request();
        signal_request(const STATE &);

    /* Accessors */
        signal_command get_command() const;
        void set_command(const enum signal_command);
        STATE get_state() const;
        void set_state(const STATE &);

    /* Implementation */
    private:
        signal_command m_command;
        STATE m_state;
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<typename STATE>
inline signal_request<STATE>::signal_request():
    m_command(SIGNAL_SET),
    m_state(STATE()) {
}

/**
 * @brief       Signal request constructor.
 * 
 * @param       state signal state.
 */
template<typename STATE>
inline signal_request<STATE>::signal_request(const STATE & state):
    m_command(SIGNAL_SET),
    m_state(state) {
}

/**
 * @brief       Sets the command of this request.
 * 
 * @param       command the command of this Signal request.
 */
template<typename STATE>
inline void
signal_request<STATE>::set_command(const enum signal_command command) {
    m_command = command;
}

/**
 * @brief       Returns the command of this request.
 */
template<typename STATE>
inline signal_command signal_request<STATE>::get_command() const {
    return (m_command);
}  

/**
 * @brief       Returns the signal state.
 */
template<typename STATE>
inline STATE signal_request<STATE>::get_state() const {
    return (m_state);
}  

/**
 * @brief       Sets the signal state.
 * 
 * @param       state signal state.
 */
template<typename STATE>
inline void signal_request<STATE>::set_state(const STATE & state) {
    m_state = state;
}

}   /* namespace amba_pv */

#endif  /* defined(SIGNAL_REQUEST__H) */
