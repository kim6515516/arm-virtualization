/*
 * AMBA-PV: signal_if.h - Signal and SignalState interfaces.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef SIGNAL_IF__H
#define SIGNAL_IF__H

/**
 * @file        signal_if.h
 *
 * @brief       Signal and SignalState interfaces.
 */

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       Signal interface.
 *
 * It is used to indicate changes in the state of side-band signals such as,
 * for example, interrupts.
 *
 * This interface is implemented by signal_master_port and must be
 * implemented into slave modules inheriting from signal_slave_base.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_if {

    /* Destructor */
    public:

        /**
         * @brief Virtual destructor.
         */
        virtual ~signal_if() {
        };

    /* Accessors */

        /**
         * @brief Transfers a signal state.
         *
         * set_state() is used to indicate a change in the state of the signal.
         *
         * @param export_id export identifier (for multi-export slave).
         * @param state signal state.
         */
        virtual void set_state(int export_id,
                               const STATE & state) = 0;
};

/**
 * @brief       SignalState interface.
 *
 * It is used to indicate changes in the state of side-band signals such as,
 * for example, interrupts and to retrieve the state.
 *
 * This interface is implemented by signal_state_master_port and must be
 * implemented into slave modules inheriting from signal_state_slave_base.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_state_if: public virtual signal_if<STATE> {

    /* Accessors */
    public:

        /**
         * @brief Retrieves the signal state.
         *
         * @param export_id export identifier (for multi-export slave).
         *
         * @return the signal state.
         */
        virtual STATE get_state(int export_id,
                                tlm::tlm_tag<STATE> * = NULL) = 0;
};

}   /* namespace amba_pv */

#endif  /* defined(SIGNAL_IF__H) */
