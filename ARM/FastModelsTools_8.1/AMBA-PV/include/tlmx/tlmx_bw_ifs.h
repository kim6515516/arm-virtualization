/*
 * TLMX: tlmx_bw_ifs.h - TLM 2.0 extended transaction interfaces.
 *
 * Copyright 2012 ARM Limited.
 * All rights reserved.
 */

#ifndef TLMX_BW_IFS__H
#define TLMX_BW_IFS__H

/**
 * @file        tlmx_bw_ifs.h
 *
 * @brief       TLM 2.0 extended transaction interfaces.
 */

/* Includes */

/* Namespaces */

/**
 * @brief       TLMX namespace.
 */
namespace tlmx {

/* Forwards */

/* Datatypes */

/**
 * @brief       TLMX blocking snoop transaction interface.
 *
 * This interface is used for the backward path.
 *
 * @param       TRANS transaction type; defaults to @c tlm::tlm_generic_payload.
 */
template<typename TRANS = tlm::tlm_generic_payload>
class tlmx_blocking_snoop_if: public virtual sc_core::sc_interface {
    public:

        /**
         * @brief Blocking snoop.
         *
         * @param trans transaction.
         * @param t timing annotation.
         */
        virtual void
        b_snoop(TRANS & trans, sc_core::sc_time & t) = 0;
};

/**
 * @brief       TLMX snoop debug transport interface.
 *
 * This interface is used for the backward path.
 *
 * @param       TRANS transaction type; defaults to @c tlm::tlm_generic_payload.
 */
template<typename TRANS = tlm::tlm_generic_payload>
class tlmx_snoop_dbg_if: public virtual sc_core::sc_interface {
    public:

        /**
         * @brief Debug access to an initiator.
         * 
         * This use the same path as the b_snoop() interface.
         * This debug access must be performed without any of the delays,
         * waits, event notifications or side effects associated with a
         * regular transaction.
         * This debug access is, therefore, non-intrusive.
         *
         * @param trans transaction.
         *
         * @return number of bytes read or written or, if error, 0.
         */
        virtual unsigned int
        snoop_dbg(TRANS & trans) = 0;
};

/**
 * @brief       TLMX combined backward interface
 *
 * @param       TYPES protocol traits class; defaults to
 *              @c tlm::tlm_base_protocol_types.
 */
template<typename TYPES = tlm::tlm_base_protocol_types>
class tlmx_bw_transport_if:
    public virtual
    tlm::tlm_bw_nonblocking_transport_if<typename TYPES::tlm_payload_type,
                                         typename TYPES::tlm_phase_type>,
    public virtual
    tlmx_blocking_snoop_if<              typename TYPES::tlm_payload_type>,
    public virtual
    tlm::tlm_bw_direct_mem_if,
    public virtual
    tlmx_snoop_dbg_if<                   typename TYPES::tlm_payload_type> {
};

}   /* namespace tlmx */

#endif  /* defined(TLMX_BW_IFS__H) */
