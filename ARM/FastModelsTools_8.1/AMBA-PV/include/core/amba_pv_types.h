/*
 * AMBA-PV: amba_pv_types.h - AMBA-PV protocol types.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_TYPES__H
#define AMBA_PV_TYPES__H

/**
 * @file        amba_pv_types.h
 *
 * @brief       AMBA-PV protocol types.
 */

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Typedefs */

/* Datatypes */

/**
 * @brief       AMBA-PV protocol types.
 *
 * This structure defines the payload and phase types for AMBA-PV.
 * It is used for the @c TYPES template parameter with OSCI TLM 2.0 classes and
 * interfaces.
 *
 * If using amba_pv_protocol_types with OSCI TLM 2.0 classes and interfaces,
 * the following rules apply to the OSCI TLM 2.0 GP attributes:
 * - The data length attribute must be greater than or equal to the burst size
 *   times the burst length. If not, an error response of
 *   @c tlm::TLM_BURST_ERROR_REPONSE is returned.
 * - The streaming width attribute must be equal to the burst size for a fixed
 *   burst. If not, an error response of @c tlm::TLM_BURST_ERROR_REPONSE is
 *   returned.
 * - The byte enable pointer attribute must be @c NULL on read transactions. If
 *   not, an error response of @c tlm::TLM_BYTE_ENABLE_ERROR_REPONSE is
 *   returned.
 * - The byte enable length attribute must be a multiple of the burst size on
 *   write transactions. If not, an error response of
 *   @c tlm::TLM_BYTE_ENABLE_ERROR_REPONSE is returned.
 * - If the address attribute is not aligned on the burst size, only the
 *   address of the first burst beat must be unaligned, the addresses of
 *   subsequent data transfers being aligned.
 *
 * @note        This does not enforce any requirements on slaves for read
 *              transactions. This must be represented with appropriate byte
 *              enables for write transactions.
 * 
 * @note        AMBA&nbsp;3 buses specific signals are defined in an extension
 *              class.
 *
 * @see         amba_pv_extension
 */
struct amba_pv_protocol_types {
    typedef tlm::tlm_generic_payload tlm_payload_type;
    typedef tlm::tlm_phase tlm_phase_type;
};

/**
 * @brief       AMBA-PV transaction type.
 *
 * The amba_pv_transaction type is equivalent to the
 * tlm_payload_type of the amba_pv_protocol_types struct.
 */
typedef amba_pv_protocol_types::tlm_payload_type amba_pv_transaction;

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_TYPES__H) */
