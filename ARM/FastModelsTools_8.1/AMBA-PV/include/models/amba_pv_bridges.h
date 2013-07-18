/*
 * AMBA-PV: amba_pv_bridges.h - OSCI TLM 2.0 BP - AMBA-PV bridge modules.
 *
 * Copyright 2007-2009, 2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_BRIDGES__H
#define AMBA_PV_BRIDGES__H

/**
 * @file        amba_pv_bridges.h
 *
 * @brief       OSCI TLM 2.0 BP - AMBA-PV bridge modules.
 */

/* Includes */
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/simple_initiator_socket.h>
#include "bus/amba_pv_extension.h"
#include "core/amba_pv_core_ifs.h"
#include "sockets/amba_pv_master_socket.h"
#include "sockets/amba_pv_slave_socket.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
  * @brief      OSCI TLM 2.0 BP to AMBA-PV bridge module.
 *
 * The amba_pv_from_tlm_bridge class translates OSCI TLM 2.0 BP transactions
 * into AMBA-PV specific transactions.
 * This consists mainly in adding the AMBA-PV extension (class
 * amba_pv_extension) to the OSCI TLM 2.0 GP.
 * In addition, the bridge checks the following:
 * - The address attribute must be aligned to the bus length for burst
 *   transactions and to the data length for single transactions. If not, an
 *   error response of @c tlm::TLM_ADDRESS_ERROR_RESPONSE is returned.
 * - The data length attribute must be a multiple of the bus length for burst
 *   transactions. If not, an error response of @c tlm::TLM_BURST_ERROR_REPONSE
 *   is returned.
 * - The streaming width attribute must be equal to the bus length for fixed
 *   burst transactions. If not, an error response of
 *   @c tlm::TLM_BURST_ERROR_REPONSE is returned.
 * - The byte enable pointer attribute must be @c NULL on read transactions. If
 *   not, an error response of @c tlm::TLM_BYTE_ENABLE_ERROR_REPONSE is
 *   returned.
 * - The byte enable length attribute must be equal to the data length for
 *   single write transactions and a multiple of the bus length for burst write
 *   transactions. If not, an error response of
 *   @c tlm::TLM_BYTE_ENABLE_ERROR_REPONSE is returned.
 *
 * @note        The bus length is defined as (@a BUSWIDTH + 7) / 8.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 *
 * @see         amba_pv_extension
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_from_tlm_bridge:
    public virtual amba_pv_bw_transport_if,
    public sc_core::sc_module {

    /* Ports */
    public:

        /**
         * Slave socket from OSCI TLM 2.0 BP.
         */
        tlm_utils::simple_target_socket<amba_pv_from_tlm_bridge,
                                        BUSWIDTH,
                                        tlm::tlm_base_protocol_types> tlm_s;

        /**
         * Master socket to AMBA-PV.
         */
        amba_pv_master_socket<BUSWIDTH> amba_pv_m;

    /* Constructor */
        explicit amba_pv_from_tlm_bridge(const sc_core::sc_module_name &);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Backward interface */
    protected:
        virtual void
        invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);

    /* Implementation */
    private:

        /* TLM socket interface */
        void b_transport(amba_pv_transaction &, sc_core::sc_time &);
        bool get_direct_mem_ptr(amba_pv_transaction &, tlm::tlm_dmi &);
        unsigned int transport_dbg(amba_pv_transaction &);

        /* Helper */
        bool add_extension(amba_pv_transaction &, amba_pv_extension &) const;
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name bridge name.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_from_tlm_bridge<BUSWIDTH>::amba_pv_from_tlm_bridge(const sc_core::sc_module_name & name):
    sc_core::sc_module(name),
    tlm_s("tlm_s"),
    amba_pv_m("amba_pv_m") {

    /* Bindings */
    tlm_s.register_b_transport(this, & amba_pv_from_tlm_bridge::b_transport);
    tlm_s.register_get_direct_mem_ptr(this,
        & amba_pv_from_tlm_bridge::get_direct_mem_ptr);
    tlm_s.register_transport_dbg(this,
        & amba_pv_from_tlm_bridge::transport_dbg);
    amba_pv_m(* this);
}

/**
 * @brief       Returns the kind string of this bridge.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_from_tlm_bridge<BUSWIDTH>::kind() const  {
    return ("amba_pv_from_tlm_bridge");
}

/*
 * Translates OSCI TLM 2.0 BP transactions into AMBA-PV transactions.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_from_tlm_bridge<BUSWIDTH>::b_transport(amba_pv_transaction & trans,
                                               sc_core::sc_time & t) {
    amba_pv_extension ex;

    bool added = add_extension(trans, ex);

    if (added) {
        unsigned int l = trans.get_data_length();
        unsigned int w = amba_pv_m.get_bus_width_bytes();

        /* Address attribute must be aligned to the bus length for burst
         * transactions and to the data length for single transactions! */
        if (trans.get_address() & (ex.get_size() - 1)) {
            trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
            trans.clear_extension(& ex);
            return;
        }
        if (l > w) {

            /* Data length attribute must be a multiple of bus length for burst
             * transactions! */
            if ((l % w) != 0) {
                trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
                trans.clear_extension(& ex);
                return;
            }
            if (trans.get_streaming_width() < l) {

                /* Streaming width attribute must be equal to the bus length for
                 * fixed burst transactions! */
                if (trans.get_streaming_width() != w) {
                    trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
                    trans.clear_extension(& ex);
                    return;
                }
            }
        }

        /* Byte enable pointer attribute must be NULL on read transactions! */
        if (trans.is_read() && (trans.get_byte_enable_ptr() != NULL)) {
            trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
            trans.clear_extension(& ex);
            return;
        }

        /* Byte enable length attribute must be equal to the data length for
         * single write transactions and a multiple of the bus length for burst
         * write transactions! */
        if (trans.is_write() && (trans.get_byte_enable_ptr() != NULL)
            && (trans.get_byte_enable_length() % ex.get_size()) != 0) {
            trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
            trans.clear_extension(& ex);
            return;
        }
    }
    try {
        amba_pv_m->b_transport(trans, t);
    }
    catch (...) {
        if (added) {
            trans.clear_extension(& ex);
        }
        throw;
    }

    /* Convert AMBA-PV response to TLM 2.0 response status if needed.
     *
     * Note:    tlm::TLM_INCOMPLETE_RESPONSE is not used by AMBA-PV. */
    if (trans.get_response_status() == tlm::TLM_INCOMPLETE_RESPONSE) {
        trans.set_response_status(amba_pv_resp_to_tlm(ex.get_resp()));
    }
    if (added) {
        trans.clear_extension(& ex);
    }
}

/*
 * Translates OSCI TLM 2.0 BP DMI requests into AMBA-PV DMI requests.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_from_tlm_bridge<BUSWIDTH>::get_direct_mem_ptr(amba_pv_transaction & trans,
                                                      tlm::tlm_dmi & dmi_data) {
    amba_pv_extension ex;
    bool ret = false;

    if (trans.get_extension(amba_pv_extension::ID) != NULL) {
        return (amba_pv_m->get_direct_mem_ptr(trans, dmi_data));
    }
    trans.set_extension(& ex);
    try {
        ret = amba_pv_m->get_direct_mem_ptr(trans, dmi_data);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ret);
}

/*
 * Translates TLM 2.0 BP debug transactions into AMBA-PV debug
 * transactions.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_from_tlm_bridge<BUSWIDTH>::transport_dbg(amba_pv_transaction & trans) {
    amba_pv_extension ex;
    unsigned int ret = 0;

    if (trans.get_extension(amba_pv_extension::ID) != NULL) {
        return (amba_pv_m->transport_dbg(trans));
    }
    trans.set_extension(& ex);
    try {
        ret = amba_pv_m->transport_dbg(trans);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ret);
}

/**
 * @brief       Invalidates DMI pointers previously established for the
 *              specified DMI region.
 *
 * This version of the method converts DMI invalidate from AMBA-PV backward to
 * OSCI TLM 2.0 BP.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_from_tlm_bridge<BUSWIDTH>::invalidate_direct_mem_ptr(int socket_id,
                                                             sc_dt::uint64 start_range,
                                                             sc_dt::uint64 end_range) {
    tlm_s->invalidate_direct_mem_ptr(start_range, end_range);
}

/*
 * Adds AMBA-PV extension into an OSCI TLM 2.0 BP transaction.
 *
 * Sets the attributes of the amba_pv_addressing class, especially the burst
 * type and length. The burst size is set to the transaction length in case of
 * single access and to the bus length in case of burst access.
 *
 * Returns true if extension added, false if extension already present.
 *
 * If the extension is added, it and needs to be cleared later on.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_from_tlm_bridge<BUSWIDTH>::add_extension(amba_pv_transaction & trans,
                                                 amba_pv_extension & ex) const {
    if (trans.get_extension(amba_pv_extension::ID) != NULL) {
        return false;
    }

    unsigned int l = trans.get_data_length();
    unsigned int w = amba_pv_m.get_bus_width_bytes();

    if (l > w) {

        /* Burst access */
        ex.set_size(w);
        ex.set_length(l / w);
        if (trans.get_streaming_width() < l) {

            /* Streaming/fixed burst */
            ex.set_burst(AMBA_PV_FIXED);
        }
    } else {

        /* Single access */
        ex.set_size(l);
    }
    trans.set_extension(& ex);
    return true;
}

/**
 * @brief       AMBA-PV to OSCI TLM 2.0 BP bridge module.
 *
 * The amba_pv_to_tlm_bridge class converts AMBA-PV transactions into OSCI
 * TLM 2.0 BP transactions.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_to_tlm_bridge:
    public virtual amba_pv_fw_transport_if,
    public sc_core::sc_module {

    /* Ports */
    public:

        /**
         * Slave socket from AMBA-PV.
         */
        amba_pv_slave_socket<BUSWIDTH> amba_pv_s;

        /**
         * Master socket to OSCI TLM 2.0 BP.
         */
        tlm_utils::simple_initiator_socket<amba_pv_to_tlm_bridge,
                                           BUSWIDTH,
                                           tlm::tlm_base_protocol_types> tlm_m;

    /* Constructor */
        explicit amba_pv_to_tlm_bridge(const sc_core::sc_module_name &);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Forward interface */
    protected:
        virtual void b_transport(int,
                                 amba_pv_transaction &,
                                 sc_core::sc_time &);
        virtual bool
        get_direct_mem_ptr(int, amba_pv_transaction & trans, tlm::tlm_dmi &);
        virtual unsigned int transport_dbg(int, amba_pv_transaction & trans);

    /* Implementation */
    private:

        /* TLM socket interface */
        void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64);
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name bridge name.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_to_tlm_bridge<BUSWIDTH>::amba_pv_to_tlm_bridge(const sc_core::sc_module_name & name):
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s"),
    tlm_m("tlm_m") {

    /* Bindings */
    amba_pv_s(* this);
    tlm_m.register_invalidate_direct_mem_ptr(this,
        & amba_pv_to_tlm_bridge::invalidate_direct_mem_ptr);
}

/**
 * @brief       Returns the kind string of this bridge.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_to_tlm_bridge<BUSWIDTH>::kind() const  {
    return ("amba_pv_to_tlm_bridge");
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method converts an AMBA-PV transaction into an OSCI TLM
 * 2.0 BP transaction.
 * The main change is conversion of wrapping bursts into incremental burts.
 * In addition, the transaction address is aligned to the burst size.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_to_tlm_bridge<BUSWIDTH>::b_transport(int socket_id,
                                             amba_pv_transaction & trans,
                                             sc_core::sc_time & t) {
    amba_pv_extension * ex = NULL;

    trans.get_extension(ex);
    if (ex == NULL) {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return;
    }

    unsigned int s = ex->get_size();
    unsigned int l = ex->get_length();

    /* Is the transaction a wrapping burst? */
    if (ex->get_burst() == AMBA_PV_WRAP) {

        /* Convert wrapping burst into an incremental one... */
        amba_pv_transaction trans2;
        amba_pv_extension * ex2 = NULL;
        unsigned char * data = trans.get_data_ptr();
        unsigned char * be = trans.get_byte_enable_ptr();
        unsigned char * data2 = NULL;
        unsigned char * be2 = NULL;

        /* Wrap boundary */
        sc_dt::uint64 addr = trans.get_address();
        sc_dt::uint64 wrap_boundary = addr & ~sc_dt::uint64((s * l) - 1);
        unsigned int n =
            static_cast<unsigned int>(((addr - wrap_boundary) & ~sc_dt::uint64(s - 1)) / s);

        /* Copy and update transaction */
        trans2.deep_copy_from(trans);

        /* Copy data and update transaction */
        data2 = new unsigned char[trans.get_data_length()];
        std::memcpy(data2 + (l - n) * s, data, n * s);
        std::memcpy(data2, data + n * s, (l - n) * s);
        trans2.set_data_ptr(data2);

        /* Copy byte enable and update transaction */
        if (be != NULL) {
            be2 = new unsigned char[l * s];

            for (unsigned int m = 0; (m < n); m += 1) {
                std::memcpy(be2 + (l - n + m) * s,
                            be + ((m * s) % trans.get_byte_enable_length()),
                            s);
            }
            for (unsigned int m = n; (m < l); m += 1) {
                std::memcpy(be2 + ((m - n) * s),
                            be + ((m * s) % trans.get_byte_enable_length()),
                            s);
            }
            trans2.set_byte_enable_ptr(be2);
            trans2.set_byte_enable_length(l * s);
        }

        /* Update transaction */
        trans2.get_extension(ex2);
        sc_assert(ex2 != NULL);
        ex2->set_burst(AMBA_PV_INCR);
        trans2.set_address(wrap_boundary);

        /* Transport */
        try {
            tlm_m->b_transport(trans2, t);
        }
        catch (...) {
            delete [] data2;
            if (be2 != NULL) {
                delete [] be2;
            }
            throw;
        }

        /* Update original transaction */
        trans.update_extensions_from(trans2);
        ex->set_burst(AMBA_PV_WRAP);
        trans.set_response_status(trans2.get_response_status());
        trans.set_dmi_allowed(trans2.is_dmi_allowed());

        /* Copy back data */
        if (trans.is_read()) {
            std::memcpy(data, data2 + (l - n) * s, n * s);
            std::memcpy(data + n * s, data2, (l - n) * s);
        }
        delete [] data2;
        if (be2 != NULL) {
            delete [] be2;
        }
    } else {

        /* Align address */
        trans.set_address(trans.get_address() & ~sc_dt::uint64(s - 1));

        /* Transport */
        tlm_m->b_transport(trans, t);
    }

    /* Convert TLM 2.0 response status into AMBA-PV response. */
    ex->set_resp(amba_pv_resp_from_tlm(trans.get_response_status(),
                                       ex->is_exclusive()));
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * This version of the method converts AMBA-PV DMI request into OSCI TLM 2.0 BP
 * request.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_to_tlm_bridge<BUSWIDTH>::get_direct_mem_ptr(int socket_id,
                                                    amba_pv_transaction & trans,
                                                    tlm::tlm_dmi & dmi_data) {
    return (tlm_m->get_direct_mem_ptr(trans, dmi_data));
}

/**
 * @brief       Debug access to a target.
 *
 * This version of the method converts AMBA-PV debug transaction into OSCI TLM
 * 2.0 BP debug transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_to_tlm_bridge<BUSWIDTH>::transport_dbg(int socket_id,
                                               amba_pv_transaction & trans) {
    return (tlm_m->transport_dbg(trans));
}

/*
 * Invalidates DMI pointers previously established for the specified DMI
 * region.
 *
 * This version of the method converts DMI invalidate from OSCI TLM 2.0 BP
 * backward to AMBA-PV.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_to_tlm_bridge<BUSWIDTH>::invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                           sc_dt::uint64 end_range) {
    amba_pv_s->invalidate_direct_mem_ptr(start_range, end_range);
}
}   /* namespace amba_pv */ 

#endif  /* defined(AMBA_PV_BRIDGES__H) */
