/*
 * AMBA-PV: amba_pv_ext_core_ifs.h - AMBA-PV core transaction interfaces that support hierarchical binding.
 *
 * Copyright 2007-2009, 2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXT_CORE_IFS__H
#define AMBA_PV_EXT_CORE_IFS__H

/**
 * @file        amba_pv_ext_core_ifs.h
 *
 * @brief       AMBA-PV core transaction interfaces.
 */

/* Includes */
#include "core/amba_pv_types.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/**
 * @brief       Extensions namespace.
 */
namespace ext {

/* Datatypes */

/**
 * @brief       AMBA-PV core transaction interface.
 *
 * This is a tagged variant of the @c tlm::tlm_fw_transport_if interface.
 * This interface is used for the forward path.
 *
 * @note        AMBA-PV slaves and AMBA-PV ACE slaves must implement the amba_pv_fw_transport_if interface.
 */
class amba_pv_fw_transport_if: public virtual sc_core::sc_interface {

    /* Transport interface */
    public:

        /**
         * @brief Blocking transport.
         *
         * @param socket_id socket identifier (index into bound interfaces on the master side).
         * @param trans transaction.
         * @param t timing annotation.
         */
        virtual void b_transport(int socket_id, amba_pv_transaction & trans, sc_core::sc_time & t) = 0;

    /* Debug interface */

        /**
         * @brief Debug access to a slave.
         * 
         * This use the same path as the b_transport() interface.
         * This debug access must be performed without any of the delays, waits, event notifications or side effects
         * associated with a regular transaction.
         * This debug access is, therefore, non-intrusive.
         *
         * @param socket_id socket identifier (index into bound interfaces on the master side).
         * @param trans transaction.
         *
         * @return number of bytes read or written or, if error, 0.
         */
        virtual unsigned int transport_dbg(int socket_id, amba_pv_transaction & trans) = 0;

    /* DMI interface */

        /**
         * @brief Requests a DMI access based on the specified transaction.
         *
         * Returns a reference to a DMI descriptor of type @c tlm_dmi that contains the bounds of the DMI region.
         *
         * @param socket_id socket identifier (index into bound interfaces on the master side).
         * @param trans transaction.
         * @param dmi_data DMI Descriptor.
         *
         * @return @c true if DMI access is granted, @c false otherwise.
         */
        virtual bool get_direct_mem_ptr(int socket_id, amba_pv_transaction & trans, tlm::tlm_dmi & dmi_data) = 0;
};

/**
 * @brief       AMBA-PV core transaction interface.
 *
 * This is a tagged variant of the @c tlm::tlm_bw_transport_if interface.
 * This interface is used for the backward path.
 *
 * @note        AMBA-PV masters must implement the amba_pv_bw_transport_if interface.
 */
class amba_pv_bw_transport_if: public virtual sc_core::sc_interface {

    /* DMI interface */
    public:

        /**
         * @brief Invalidates DMI pointers previously established for the specified DMI region.
         *
         * @param socket_id socket identifier (index into bound interfaces on the slave side).
         * @param start_range DMI region start address.
         * @param end_range DMI region end address.
         */
        virtual void invalidate_direct_mem_ptr(int socket_id, sc_dt::uint64 start_range, sc_dt::uint64 end_range) = 0;
};

/**
 * @brief       AMBA-PV ACE core transaction interface.
 *
 * This is a tagged variant of the @c tlm::tlm_bw_transport_if interface.
 * This interface is used for the backward snoop path.
  *
 * @note        AMBA-PV ACE masters must implement the amba_pv_ace_bw_transport_if interface.
*/
class amba_pv_ace_bw_transport_if: public virtual sc_core::sc_interface {

    /* Snoop interface */
    public:

        /**
         * @brief Blocking snoop.
         *
         * @param socket_id socket identifier (index into bound interfaces on the slave side).
         * @param trans transaction.
         * @param t timing annotation.
         */
        virtual void b_snoop(int socket_id, amba_pv_transaction & trans, sc_core::sc_time & t) = 0;

    /* Debug snoop interface */

        /**
         * @brief Debug snoop access to a master.
         * 
         * This use the same path as the b_snoop() interface.
         * This debug access must be performed without any of the delays, waits, event notifications or side effects
         * associated with a regular snoop transaction.
         * This debug access is, therefore, non-intrusive.
         *
         * @param socket_id socket identifier (index into bound interfaces on the slave side).
         * @param trans transaction.
         *
         * @return number of bytes read or written or, if error, 0.
         */
        virtual unsigned int snoop_dbg(int socket_id, amba_pv_transaction & trans) = 0;

    /* DMI interface */

        /**
         * @brief Invalidates DMI pointers previously established for the specified DMI region.
         *
         * @param socket_id socket identifier (index into bound interfaces on the slave side).
         * @param start_range DMI region start address.
         * @param end_range DMI region end address.
         */
        virtual void invalidate_direct_mem_ptr(int socket_id, sc_dt::uint64 start_range, sc_dt::uint64 end_range) = 0;
};

}   /* namespace ext */

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_EXT_CORE_IFS__H) */
