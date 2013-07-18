/*
 * AMBA-PV: amba_pv_if.h - AMBA-PV user-layer transaction interface.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_IF__H
#define AMBA_PV_IF__H

/**
 * @file        amba_pv_if.h
 *
 * @brief       AMBA-PV user-layer transaction interface.
 */

/* Includes */
#include "bus/amba_pv_extension.h"
#include "core/amba_pv_types.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV user-layer transaction interface.
 *
 * This interface is implemented by amba_pv_master_socket and
 * amba_pv_slave_base.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024; defaults to 64.
 *
 * @see         amba_pv_master_socket, amba_pv_slave_base, amba_pv_slave_socket
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_if {

    /* Destruction */
    public:

        /**
         * @brief Destructor.
         */
        virtual ~amba_pv_if() {
        };

    /* Accessors */

        /**
         * @brief Returns the bus width, in bytes, based on @e BUSWIDTH.
         */
        unsigned int get_bus_width_bytes() const {
            return (BUSWIDTH / 8);
        };

    /* User interface */

        /**
         * @brief Completes a read transaction.
         *
         * @param socket_id socket identifier (index into bound interfaces on
         *        the master side).
         * @param addr transaction address.
         * @param data transaction data pointer. It must point to an array of
         *        @a size bytes.
         * @param size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
         *        64, 128]. The transaction size must be less than or equal to
         *        the value returned by get_bus_width_bytes().
         * @param ctrl AMBA&nbsp;3 control information (set to @c NULL if
         *        unused on the master side).
         * @param t timing annotation.
         *
         * @return @c AMBA_PV_OKAY if the transaction is successful.
         */
        virtual amba_pv_resp_t
        read(int socket_id,
             const sc_dt::uint64 & addr,
             unsigned char * data,
             unsigned int size,
             const amba_pv_control * ctrl,
             sc_core::sc_time & t) = 0;

        /**
         * @brief Completes a write transaction.
         *
         * @param socket_id socket identifier (index into bound interfaces on
         *        the master side).
         * @param addr transaction address.
         * @param data transaction data pointer. It must point to an array of
         *        @a size bytes.
         * @param size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
         *        64, 128]. The transaction size must be less than or equal to
         *        the value returned by get_bus_width_bytes().
         * @param ctrl AMBA&nbsp;3 control information (set to @c NULL if
         *        unused on the master side).
         * @param strb write strobes pointer (set to @c NULL if none). It must
         *        point to an array of @a size elements.
         * @param t timing annotation.
         *
         * @return @c AMBA_PV_OKAY if the transaction is successful.
         */
        virtual amba_pv_resp_t
        write(int socket_id,
              const sc_dt::uint64 & addr,
              unsigned char * data,
              unsigned int size,
              const amba_pv_control * ctrl,
              unsigned char * strb,
              sc_core::sc_time & t) = 0;

        /**
         * @brief Completes a burst read transaction.
         *
         * @param socket_id socket identifier (index into bound interfaces on
         *        the master side).
         * @param addr transaction address.
         * @param data transaction data pointer. It must point to an array of
         *        (@a size * @a length) bytes.
         * @param length transaction burst length as in [1-16].
         * @param size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
         *        64, 128]. The transaction size must be less than or equal to
         *        the value returned by get_bus_width_bytes().
         * @param ctrl AMBA&nbsp;3 control information (set to @c NULL if
         *        unused on the master side).
         * @param burst transaction burst type, one of @c AMBA_PV_INCR,
         *        @c AMBA_PV_FIXED, or @c AMBA_PV_WRAP.
         * @param t timing annotation.
         *
         * @return @c AMBA_PV_OKAY if the transaction is successful.
         */
        virtual amba_pv_resp_t
        burst_read(int socket_id,
                   const sc_dt::uint64 & addr,
                   unsigned char * data,
                   unsigned int length,
                   unsigned int size,
                   const amba_pv_control * ctrl,
                   amba_pv_burst_t burst,
                   sc_core::sc_time & t) = 0;

        /**
         * @brief Completes a burst write transaction.
         *
         * @param socket_id socket identifier (index into bound interfaces on
         *        the master side).
         * @param addr transaction address.
         * @param data transaction data pointer. It must point to an array of
         *        (@a size * @a length) bytes.
         * @param length transaction burst length as in [1-16].
         * @param size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
         *        64, 128]. The transaction size must be less than or equal to
         *        the value returned by get_bus_width_bytes().
         * @param ctrl AMBA&nbsp;3 control information (set to @c NULL if
         *        unused on the master side).
         * @param burst transaction burst type, one of @c AMBA_PV_INCR,
         *        @c AMBA_PV_FIXED, or @c AMBA_PV_WRAP.
         * @param strb write strobes pointer (set to @c NULL if none).
         * @param strb_length Write strobes length. It must be a multiple of
         *        @a size.
         * @param t timing annotation.
         *
         * @return @c AMBA_PV_OKAY if the transaction is successful.
         */
        virtual amba_pv_resp_t
        burst_write(int socket_id,
                    const sc_dt::uint64 & addr,
                    unsigned char * data,
                    unsigned int length,
                    unsigned int size,
                    const amba_pv_control * ctrl,
                    amba_pv_burst_t burst,
                    unsigned char * strb,
                    unsigned int strb_length,
                    sc_core::sc_time & t) = 0;

        /**
         * @brief Requests DMI access to the specified address and returns a
         *        reference to a DMI descriptor.
         *
         * The DMI descriptor contains the bounds of the DMI region. 
         *
         * @param socket_id socket identifier (index into bound interfaces on
         *        the master side).
         * @param command @c tlm::TLM_READ_COMMAND for a DMI read access
         *        request. @c tlm::TLM_WRITE_COMMAND for a DMI write access
         *        request.
         * @param addr address to which the DMI access is requested.
         * @param ctrl AMBA&nbsp;3 control information (set to @c NULL if
         *        unused on the master side).
         * @param dmi_data returned DMI descriptor.
         *
         * @return @c true if a DMI region is granted, @c false otherwise.
         */
        virtual bool
        get_direct_mem_ptr(int socket_id,
                           tlm::tlm_command command,
                           const sc_dt::uint64 & addr,
                           const amba_pv_control * ctrl,
                           tlm::tlm_dmi & dmi_data) = 0;

        /**
         * @brief Non-intrusive debug read transaction.
         *
         * @param socket_id socket identifier (index into bound interfaces on
         *        the master side).
         * @param addr transaction address.
         * @param data transaction data pointer. It must point to an array of
         *        @a length bytes.
         * @param length transaction length.
         * @param ctrl AMBA&nbsp;3 control information (set to @c NULL if
         *        unused on the master side).
         *
         * @return number of bytes read or, if error, 0.
         */
        virtual unsigned int
        debug_read(int socket_id,
                   const sc_dt::uint64 & addr,
                   unsigned char * data,
                   unsigned int length,
                   const amba_pv_control * ctrl) = 0;

        /**
         * @brief Non-intrusive debug write transaction.
         *
         * @param socket_id socket identifier (index into bound interfaces on
         *        the master side).
         * @param addr transaction address.
         * @param data transaction data pointer. It must point to an array of
         *        @a length bytes.
         * @param length transaction length.
         * @param ctrl AMBA&nbsp;3 control information (set to @c NULL if
         *        unused on the master side).
         *
         * @return number of bytes written or, if error, 0.
         */
        virtual unsigned int
        debug_write(int socket_id,
                    const sc_dt::uint64 & addr,
                    unsigned char * data,
                    unsigned int length,
                    const amba_pv_control * ctrl) = 0;
};

}  /* namespace amba_pv */

#endif  /* defined(AMBA_PV_IF__H) */
