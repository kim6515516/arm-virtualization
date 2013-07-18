/*
 * AMBA-PV: amba_pv_ext_slave_base.h - Base class for all AMBA-PV slave modules that support hierachical binding.
 *
 * Copyright 2007-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXT_SLAVE_BASE__H
#define AMBA_PV_EXT_SLAVE_BASE__H

/**
 * @file        amba_pv_ext_slave_base.h
 *
 * @brief       Base class for all AMBA-PV slave modules.
 */

/* Includes */
#include "bus/amba_pv_extension.h"
#include "core/amba_pv_ext_core_ifs.h"
#include "user/amba_pv_if.h"

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
 * @brief       Base class for all AMBA-PV slave modules.
 *
 * amba_pv_slave_base is intended to be bound to amba_pv_slave_socket.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256, 512, or 1024. Defaults to 64.
 *
 * @note        amba_pv_slave_base is not an @c sc_module.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_slave_base: public virtual amba_pv_fw_transport_if, public virtual amba_pv_if<BUSWIDTH> {

    /* Constructor */
    public:
        explicit amba_pv_slave_base(const std::string &);

    /* Accessors */
        std::string get_name() const;

    /* Forward interface */
    protected:
        virtual void b_transport(int, amba_pv_transaction &, sc_core::sc_time &);
        virtual unsigned int transport_dbg(int, amba_pv_transaction &);
        virtual bool get_direct_mem_ptr(int, amba_pv_transaction &, tlm::tlm_dmi &);

    /* User-layer interface */
        virtual amba_pv_resp_t
        read(int, const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *, sc_core::sc_time &);
        virtual amba_pv_resp_t
        write(int,
              const sc_dt::uint64 &,
              unsigned char *,
              unsigned int,
              const amba_pv_control *,
              unsigned char *,
              sc_core::sc_time &);
        virtual amba_pv_resp_t
        burst_read(int,
                   const sc_dt::uint64 &,
                   unsigned char *,
                   unsigned int,
                   unsigned int,
                   const amba_pv_control *,
                   amba_pv_burst_t,
                   sc_core::sc_time &);
        virtual amba_pv_resp_t
        burst_write(int,
                    const sc_dt::uint64 &,
                    unsigned char *,
                    unsigned int,
                    unsigned int,
                    const amba_pv_control *,
                    amba_pv_burst_t,
                    unsigned char *,
                    unsigned int,
                    sc_core::sc_time &);
        virtual bool
        get_direct_mem_ptr(int, tlm::tlm_command, const sc_dt::uint64 &, const amba_pv_control *, tlm::tlm_dmi &);
        virtual unsigned int
        debug_read(int, const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *);
        virtual unsigned int
        debug_write(int, const sc_dt::uint64 &, unsigned char *, unsigned int, const amba_pv_control *);

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
template<unsigned int BUSWIDTH>
inline
amba_pv_slave_base<BUSWIDTH>::amba_pv_slave_base(const std::string & name):
    m_name(name) {
}

/**
 * @brief       Returns the name of this slave.
 */
template<unsigned int BUSWIDTH>
inline std::string
amba_pv_slave_base<BUSWIDTH>::get_name() const  {
    return (m_name);
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method translates the blocking transport call into amba_pv_if user-layer calls.
 * In addition, the following rules are cheked:
 * - The data length attribute must be greater than or equal to the burst size times the burst length.
 *   If not, an error response of @c tlm::TLM_BURST_ERROR_REPONSE is returned.
 * - The streaming width attribute must be equal to the burst size for a fixed burst.
 *   If not, an error response of @c tlm::TLM_BURST_ERROR_REPONSE is returned.
 * - The byte enable pointer attribute must be @c NULL on read transactions.
 *   If not, an error response of @c tlm::TLM_BYTE_ENABLE_ERROR_REPONSE is returned.
 * - The byte enable length attribute must be a multiple of the burst size on write transactions.
 *   If not, an error response of @c tlm::TLM_BYTE_ENABLE_ERROR_REPONSE is returned.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_slave_base<BUSWIDTH>::b_transport(int socket_id, amba_pv_transaction & trans, sc_core::sc_time & t) {
    amba_pv_extension * ex = NULL;

    /* Retrieve AMBA-PV extension */
    trans.get_extension(ex);
    if (ex == NULL) {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return;
    }

    /* Ensure as many bytes in the transaction as required! */
    if (trans.get_data_length() < (ex->get_size() * ex->get_length())) {
        trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
        ex->set_slverr();
        return;
    }

    /* Streaming width attribute must be equal to the burst size for
     * fixed burst transactions! */
    if ((ex->get_burst() == AMBA_PV_FIXED) && (trans.get_streaming_width() != ex->get_size())) {
        trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
        ex->set_slverr();
        return;
    }

    /* Convert b_transport() into user-layer calls... */
    if (trans.is_read()) {

        /* Read transaction => ensure no byte enable! */
        if (trans.get_byte_enable_ptr() != NULL) {
            trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
            ex->set_slverr();
            return;
        }
        if (ex->get_length() == 1) {

            /* Simple read transaction... */
            ex->set_resp(this->read(socket_id, trans.get_address(), trans.get_data_ptr(), ex->get_size(), ex, t));
        } else {

            /* Burst read transaction... */
            ex->set_resp(this->burst_read(socket_id,
                                          trans.get_address(),
                                          trans.get_data_ptr(),
                                          ex->get_length(),
                                          ex->get_size(),
                                          ex,
                                          ex->get_burst(),
                                          t));
        }
    } else if (trans.is_write()) {

        /* Write transaction => ensure byte enable length multiple of burst
         * size! */
        if ((trans.get_byte_enable_ptr() != NULL) && (trans.get_byte_enable_length() % ex->get_size())) {
            trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
            ex->set_slverr();
            return;
        }
        if (ex->get_length() == 1) {
        
            /* Simple write transaction... */
            ex->set_resp(this->write(socket_id,
                                     trans.get_address(),
                                     trans.get_data_ptr(),
                                     ex->get_size(),
                                     ex,
                                     trans.get_byte_enable_ptr(),
                                     t));
        } else {

            /* Burst write transaction... */
            ex->set_resp(this->burst_write(socket_id,
                                           trans.get_address(),
                                           trans.get_data_ptr(),
                                           ex->get_length(),
                                           ex->get_size(),
                                           ex,
                                           ex->get_burst(),
                                           trans.get_byte_enable_ptr(),
                                           trans.get_byte_enable_length(),
                                           t));
        }
    } else {
        trans.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
        ex->set_slverr();
        return;
    }

    /* Translate AMBA-PV response into TLM response status */
    trans.set_response_status(amba_pv_resp_to_tlm(ex->get_resp()));
}

/**
 * @brief       Debug access to a target.
 *
 * This version of the method translates the transport_dbg() call into amba_pv_if user-layer calls.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_slave_base<BUSWIDTH>::transport_dbg(int socket_id, amba_pv_transaction & trans) {
    amba_pv_extension * ex = NULL;

    /* Retrieve AMBA-PV extension */
    trans.get_extension(ex);
    if (ex == NULL) {
        return 0;
    }

    /* Translate transport_dbg() into user-layer calls... */
    if (trans.is_read()) {

        /* Debug read transaction */
        return (this->debug_read(socket_id, trans.get_address(), trans.get_data_ptr(), trans.get_data_length(), ex));
    } else if (trans.is_write()) {

        /* Debug write transaction */
        return (this->debug_write(socket_id, trans.get_address(), trans.get_data_ptr(), trans.get_data_length(), ex));
    } else {
        SC_REPORT_WARNING("amba_pv_slave_base", "transport_dbg(): unsupported command");
        return 0;
    }
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * This version of the method translates the DMI access request call into amba_pv_if user-layer calls.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_slave_base<BUSWIDTH>::get_direct_mem_ptr(int socket_id, amba_pv_transaction & trans, tlm::tlm_dmi & dmi_data) {
    amba_pv_extension * ex = NULL;

    /* Deny DMI access to the entire memory region by default */
    dmi_data.allow_read_write();
    dmi_data.set_start_address(0x0);
    dmi_data.set_end_address(sc_dt::uint64(-1));

    /* Retrieve AMBA-PV extension */
    trans.get_extension(ex);
    if (ex == NULL) {
        SC_REPORT_WARNING("amba_pv_slave_base", "get_direct_mem_ptr(): NULL amba_pv_extension pointer");
        return false;
    }

    /* Translate DMI access request */
    switch (trans.get_command()) {
        case tlm::TLM_READ_COMMAND:
        case tlm::TLM_WRITE_COMMAND:
            break;
        default:
            SC_REPORT_WARNING("amba_pv_slave_base", "get_direct_mem_ptr(): unsupported command");
            return false;
    }
    return (this->get_direct_mem_ptr(socket_id, trans.get_command(), trans.get_address(), ex, dmi_data));
}

/**
 * @brief       Completes a read transaction.
 *
 * This version of the method causes an error.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_slave_base<BUSWIDTH>::read(int,
                                   const sc_dt::uint64 &,
                                   unsigned char *,
                                   unsigned int,
                                   const amba_pv_control *,
                                   sc_core::sc_time &) {
    SC_REPORT_ERROR("amba_pv_slave_base", "read(): not implemented");
    return AMBA_PV_SLVERR;
}

/**
 * @brief       Completes a write transaction.
 *
 * This version of the method causes an error.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_slave_base<BUSWIDTH>::write(int,
                                    const sc_dt::uint64 &,
                                    unsigned char *,
                                    unsigned int,
                                    const amba_pv_control *,
                                    unsigned char *,
                                    sc_core::sc_time &) {
    SC_REPORT_ERROR("amba_pv_slave_base", "write(): not implemented");
    return AMBA_PV_SLVERR;
}

/**
 * @brief       Completes a burst read transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_slave_base<BUSWIDTH>::burst_read(int socket_id,
                                         const sc_dt::uint64 & addr,
                                         unsigned char * data,
                                         unsigned int length,
                                         unsigned int size,
                                         const amba_pv_control * ctrl,
                                         amba_pv_burst_t burst,
                                         sc_core::sc_time & t) {
    amba_pv_resp_t resp = AMBA_PV_OKAY;

    for (unsigned int n = 0; (n < length); n += 1) {

        /* Compute address */
        sc_dt::uint64 a = amba_pv_address(addr, length, size, burst, n);

        /* Perform transfer */
        amba_pv_resp_t r = read(socket_id, a, data + (size * n), size, ctrl, t);
        if (r != AMBA_PV_OKAY) {
            resp = r;
        }
    }
    return (resp);
}

/**
 * @brief       Completes a burst write transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_slave_base<BUSWIDTH>::burst_write(int socket_id,
                                          const sc_dt::uint64 & addr,
                                          unsigned char * data,
                                          unsigned int length,
                                          unsigned int size,
                                          const amba_pv_control * ctrl,
                                          amba_pv_burst_t burst,
                                          unsigned char * strb,
                                          unsigned int strb_length,
                                          sc_core::sc_time & t) {
    amba_pv_resp_t resp = AMBA_PV_OKAY;

    for (unsigned int n = 0; (n < length); n += 1) {

        /* Compute address */
        sc_dt::uint64 a = amba_pv_address(addr, length, size, burst, n);

        /* Perform transfer */
        amba_pv_resp_t r = write(socket_id,
                                 a,
                                 data + (size * n),
                                 size,
                                 ctrl,
                                 ((strb != NULL)?
                                  strb + ((size * n) % strb_length):
                                  NULL),
                                 t);
        if (r != AMBA_PV_OKAY) {
            resp = r;
        }
    }
    return (resp);
}

/**
 * @brief       Non-intrusive debug read transaction.
 *
 * This version of the method returns @c 0.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_slave_base<BUSWIDTH>::debug_read(int,
                                         const sc_dt::uint64 &,
                                         unsigned char *,
                                         unsigned int,
                                         const amba_pv_control *) {
    return 0;
}

/**
 * @brief       Non-intrusive debug write transaction.
 *
 * This version of the method returns @c 0.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_slave_base<BUSWIDTH>::debug_write(int,
                                          const sc_dt::uint64 &,
                                          unsigned char *,
                                          unsigned int,
                                          const amba_pv_control *) {
    return 0;
}

/**
 * @brief       Requests DMI access to the specified address and returns a reference to a DMI descriptor.
 *
 * This version of the method returns @c false and denies DMI access to the entire memory region.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_slave_base<BUSWIDTH>::get_direct_mem_ptr(int,
                                                 tlm::tlm_command,
                                                 const sc_dt::uint64 &,
                                                 const amba_pv_control *,
                                                 tlm::tlm_dmi & dmi_data) {
    dmi_data.allow_read_write();
    dmi_data.set_start_address(0x0);
    dmi_data.set_end_address(sc_dt::uint64(-1));
    return false;
}

}   /* namespace ext */

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_EXT_SLAVE_BASE__H) */
