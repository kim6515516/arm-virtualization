/*
 * AMBA-PV: amba_pv_simple_probe.h - AMBA-PV simple probe model.
 *
 * Copyright 2007-2009, 2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_SIMPLE_PROBE__H
#define AMBA_PV_SIMPLE_PROBE__H

/**
 * @file        amba_pv_simple_probe.h
 *
 * @brief       AMBA-PV simple probe model.
 */

/* Includes */
#include "bus/amba_pv_extension.h"
#include "sockets/amba_pv_master_socket.h"
#include "sockets/amba_pv_slave_socket.h"
#include <iostream>
#include <sstream>

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV simple probe model.
 *
 * The amba_pv_simple_probe model prints the contents of transaction between a master and a slave to @c std::cout, a
 * file, or a stream.
 *
 * @note        If configured for printing transactions, the amba_pv_simple_probe model might have an effect on
 *              performance.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_simple_probe:
    public virtual amba_pv_fw_transport_if,
    public virtual amba_pv_bw_transport_if,
    public sc_core::sc_module {

    /* Sockets */
    public:

        /**
         * @brief Slave socket.
         */
        amba_pv_slave_socket<BUSWIDTH> amba_pv_s;

        /**
         * @brief Master socket.
         */
        amba_pv_master_socket<BUSWIDTH> amba_pv_m;

    /* Construction */
        explicit amba_pv_simple_probe(const sc_core::sc_module_name &, bool /* trans_verbose */ = true);
        amba_pv_simple_probe(const sc_core::sc_module_name &, const std::string &, bool /* trans_verbose */ = true);
            /* Deprecated. Use other constructor instead. */
        amba_pv_simple_probe(const sc_core::sc_module_name &, std::ostream &, bool /* trans_verbose */ = true);
            /* Deprecated. Use other constructor instead. */
        virtual ~amba_pv_simple_probe();

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Accessors */
        void set_verbose(bool /* verbose */ = true);
            /* Deprecated. Use set_trans_verbose() instead. */
        void set_out_file(const std::string &);
            /* Deprecated. Use set_trans_verbose() instead. */
        void set_out_file(std::ostream &);
            /* Deprecated. Use set_trans_verbose() instead. */
        void set_trans_verbose(bool /* verbose */ = true);
        void set_transport_verbose(bool /* verbose */ = true);
        bool is_transport_verbose() const;
        void set_debug_verbose(bool /* verbose */ = true);
        bool is_debug_verbose() const;
        void set_dmi_verbose(bool /* verbose */ = true);
        bool is_dmi_verbose() const;
        void set_data_verbose(bool /* verbose */ = true);
        bool is_data_verbose() const;

    /* Forward interface */
    protected:
        virtual void b_transport(int, amba_pv_transaction &, sc_core::sc_time &);
        virtual unsigned int transport_dbg(int, amba_pv_transaction &);
        virtual bool get_direct_mem_ptr(int, amba_pv_transaction &, tlm::tlm_dmi &);

    /* Backward interface */
        virtual void invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);

    /* Implementation */
    private:

        /* Member variables */
        bool m_transport_verbose;
        bool m_debug_verbose;
        bool m_dmi_verbose;
        bool m_data_verbose;
        std::ostringstream m_out;

        /* Helpers */
        void print_control(amba_pv_control *);
        void print_data(amba_pv_transaction &);
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name probe name.
 * @param       trans_verbose @c true to print transactions (default), @c false otherwise.
 *
 * @see         set_trans_verbose()
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_simple_probe<BUSWIDTH>::amba_pv_simple_probe(const sc_core::sc_module_name & name,
                                                     bool trans_verbose /* = true */):
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s"),
    amba_pv_m("amba_pv_m"),
    m_transport_verbose(trans_verbose),
    m_debug_verbose(trans_verbose),
    m_dmi_verbose(trans_verbose),
    m_data_verbose(false) {

    /* Bindings... */
    amba_pv_s(* this);
    amba_pv_m(* this);
}

/**
 * @brief       Constructor.
 *
 * @param       name probe name.
 * @param       file file transactions are printed to.
 * @param       trans_verbose @c true to print transactions (default), @c false otherwise.
 *
 * @see         set_out_file(), set_trans_verbose()
 *
 * @note        This constructor is deprecated. Use other constructor instead.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_simple_probe<BUSWIDTH>::amba_pv_simple_probe(const sc_core::sc_module_name & name,
                                                     const std::string & file,
                                                     bool trans_verbose /* = true */):
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s"),
    amba_pv_m("amba_pv_m"),
    m_transport_verbose(trans_verbose),
    m_debug_verbose(trans_verbose),
    m_dmi_verbose(trans_verbose),
    m_data_verbose(false) {
    static bool warn_amba_pv_simple_probe = false;

    if (! warn_amba_pv_simple_probe) {
        warn_amba_pv_simple_probe = true;
        SC_REPORT_WARNING(kind(), "amba_pv_simple_probe(): deprecated, use other constructor instead");
    }
    sc_core::sc_report_handler::set_log_file_name(file.c_str());
    sc_core::sc_report_handler::set_actions(name, sc_core::SC_INFO, sc_core::SC_LOG);

    /* Bindings... */
    amba_pv_s(* this);
    amba_pv_m(* this);
}

/**
 * @brief       Constructor.
 *
 * @param       name probe name.
 * @param       stream stream transactions are printed to.
 * @param       trans_verbose @c true to print transactions (default), @c false otherwise.
 *
 * @see         set_out_file(), set_trans_verbose()
 *
 * @note        This constructor is deprecated. Use other constructor instead.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_simple_probe<BUSWIDTH>::amba_pv_simple_probe(const sc_core::sc_module_name & name,
                                                     std::ostream & stream,
                                                     bool trans_verbose /* = true */):
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s"),
    amba_pv_m("amba_pv_m"),
    m_transport_verbose(trans_verbose),
    m_debug_verbose(trans_verbose),
    m_dmi_verbose(trans_verbose),
    m_data_verbose(false) {
    static bool warn_amba_pv_simple_probe = false;

    if (! warn_amba_pv_simple_probe) {
        warn_amba_pv_simple_probe = true;
        SC_REPORT_WARNING(kind(), "amba_pv_simple_probe(): deprecated, use other constructor instead");
    }
    sc_core::sc_report_handler::set_actions(name, sc_core::SC_INFO, sc_core::SC_LOG);

    /* Bindings... */
    amba_pv_s(* this);
    amba_pv_m(* this);
}

/**
 * @brief       Destructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_simple_probe<BUSWIDTH>::~amba_pv_simple_probe() {
}

/**
 * @brief       Returns the kind string of this probe.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_simple_probe<BUSWIDTH>::kind() const  {
  return ("amba_pv_simple_probe");
}

/**
 * @brief       Sets verbosity of this probe.
 *
 * If verbosity is set to @c false, no transactions are printed.
 *
 * @param       verbose @c true to print transactions (default), @c false otherwise.
 *
 * @note        set_verbose() is deprecated. Use set_trans_verbose() instead.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::set_verbose(bool verbose /* = true */) {
    static bool warn_set_verbose = false;

    if (! warn_set_verbose) {
        warn_set_verbose = true;
        SC_REPORT_WARNING(kind(), "set_verbose(): deprecated, use set_trans_verbose() instead");
    }
    set_trans_verbose(verbose);
}

/**
 * @brief       Sets the @a file transactions are printed to.
 *
 * @param       file file transactions are printed to.
 *
 * @note        set_out_file() is deprecated. Use \c sc_report_handler::set_log_file_name() instead.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::set_out_file(const std::string & file) {
    static bool warn_set_out_file = false;

    if (! warn_set_out_file) {
        warn_set_out_file = true;
        SC_REPORT_WARNING(kind(), "set_out_file(): deprecated, use sc_report_handler::set_log_file_name() instead");
    }
    sc_core::sc_report_handler::set_log_file_name(file.c_str());
    sc_core::sc_report_handler::set_actions(name(), sc_core::SC_INFO, sc_core::SC_LOG);
}

/**
 * @brief       Sets the @a stream transactions are printed to.
 *
 * @param       stream stream transactions will be printed to.
 *
 * @note        set_out_file() is deprecated. Use \c sc_report_handler::set_log_file_name() instead.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::set_out_file(std::ostream & stream) {
    static bool warn_set_out_file = false;

    if (! warn_set_out_file) {
        warn_set_out_file = true;
        SC_REPORT_WARNING(kind(), "set_out_file(): deprecated, use sc_report_handler::set_log_file_name() instead");
    }
}

/**
 * @brief       Sets verbosity of this probe.
 *
 * If verbosity is set to @c false, no transactions are printed.
 *
 * @param       verbose @c true to print transactions (default), @c false otherwise.
 *
 * @see         set_transport_verbose(), set_debug_verbose(), set_dmi_verbose()
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::set_trans_verbose(bool verbose /* = true */) {
    m_transport_verbose = verbose;
    m_debug_verbose = verbose;
    m_dmi_verbose = verbose;
}

/**
 * @brief       Sets verbosity of this probe with regard to @c b_transport() regular transactions.
 *
 * If verbosity is set to @c false, no regular transactions are printed.
 *
 * @param       verbose @c true to print @c b_transport() regular transactions (default), @c false otherwise.
 *
 * @see         is_transport_verbose()
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::set_transport_verbose(bool verbose /* = true */) {
    m_transport_verbose = verbose;
}

/**
 * @brief       Gets verbosity of this probe with regard to @c b_transport() regular transactions.
 *
 * @return      Returns @c true if regular transactions are printed (default), @c false otherwise.
 *
 * @see         set_transport_verbose()
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_simple_probe<BUSWIDTH>::is_transport_verbose() const {
    return (m_transport_verbose);
}

/**
 * @brief       Sets verbosity of this probe with regard to @c transport_dbg() debug transactions.
 *
 * If verbosity is set to @c false, no debug transactions are printed.
 *
 * @param       verbose @c true to print debug transactions (default), @c false otherwise.
 *
 * @see         is_debug_verbose()
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::set_debug_verbose(bool verbose /* = true */) {
    m_debug_verbose = verbose;
}

/**
 * @brief       Gets verbosity of this probe with regard to @c transport_dbg() debug transactions.
 *
 * @return      Returns @c true if debug transactions are printed (default), @c false otherwise.
 *
 * @see         set_debug_verbose()
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_simple_probe<BUSWIDTH>::is_debug_verbose() const {
    return (m_debug_verbose);
}

/**
 * @brief       Sets verbosity of this probe with regard to DMI transactions.
 *
 * If verbosity is set to @c false, no DMI transactions are printed.
 *
 * @param       verbose @c true to print DMI transactions (default), @c false otherwise.
 *
 * @see         is_dmi_verbose()
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::set_dmi_verbose(bool verbose /* = true */) {
    m_dmi_verbose = verbose;
}

/**
 * @brief       Gets verbosity of this probe with regard to DMI transactions.
 *
 * @return      Returns @c true if DMI transactions are printed (default), @c false otherwise.
 *
 * @see         set_dmi_verbose()
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_simple_probe<BUSWIDTH>::is_dmi_verbose() const {
    return (m_dmi_verbose);
}

/**
 * @brief       Sets verbosity of this probe with regard to transactions data.
 *
 * If verbosity is set to @c false, the data pointer is printed instead.
 *
 * @param       verbose @c true to print transactions data (default), @c false otherwise.
 *
 * @see         is_data_verbose()
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::set_data_verbose(bool verbose /* = true */) {
    m_data_verbose = verbose;
}

/**
 * @brief       Gets verbosity of this probe with regard to transactions data.
 *
 * @return      Returns @c true if transactions data are printed, @c false otherwise.
 *
 * @see         set_data_verbose()
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_simple_probe<BUSWIDTH>::is_data_verbose() const {
    return (m_data_verbose);
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method completes the transaction and prints its contents.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::b_transport(int socket_id, amba_pv_transaction & trans, sc_core::sc_time & t) {
    std::string cmd = "";
    amba_pv_extension * ex = NULL;

    /* Retrieve AMBA-PV extension */
    trans.get_extension(ex);

    /* Print transaction */
    if (is_transport_verbose() && (ex != NULL)) {
        m_out.str("");

        /* Print request */
        if (trans.is_read()) {
            if (ex->get_length() > 1) {
                cmd = "burst_read(";
            } else {
                cmd = "read(";
            }
        } else {
            if (ex->get_length() > 1) {
                cmd = "burst_write(";
            } else {
                cmd = "write(";
            }
        }
        m_out << cmd << "addr=" << std::showbase << std::hex << trans.get_address();
        if (trans.is_write()) {
            m_out << ", ";
            print_data(trans);
        }
        if (ex->get_length() > 1) {
            m_out << ", len=" << std::noshowbase << std::dec << ex->get_length();
        }
        m_out << ", size=" << std::noshowbase << std::dec << ex->get_size();
        if (ex->get_length() > 1) {
            m_out << ", burst=" << amba_pv_burst_string(ex->get_burst());
        }
        print_control(ex);
        m_out << ", t=" << t << ")";
        SC_REPORT_INFO(name(), m_out.str().c_str());
    }

    /* Transaction proceeds */
    amba_pv_m->b_transport(trans, t);
    if (is_transport_verbose() && (ex != NULL)) {
        m_out.str("");

        /* Print response */
        m_out << cmd;
        if (trans.is_read()) {
            print_data(trans);
            m_out << ", ";
        }
        m_out << "t=" << t << "): rsp=" << amba_pv_resp_string(ex->get_resp());
        SC_REPORT_INFO(name(), m_out.str().c_str());
    }
}

/**
 * @brief       Debug access to a target.
 *
 * This version of the method forwards this debug access to the slave and prints its contents.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_simple_probe<BUSWIDTH>::transport_dbg(int socket_id, amba_pv_transaction & trans) {
    std::string cmd = "";
    amba_pv_extension * ex = NULL;

    /* Retrieve AMBA-PV extension */
    trans.get_extension(ex);

    /* Print debug access */
    if (is_debug_verbose()) {
        m_out.str("");

        /* Print request */
        if (trans.is_read()) {
                cmd = "debug_read(";
        } else {
                cmd = "debug_write(";
        }
        m_out << cmd << "addr=" << std::showbase << std::hex << trans.get_address();
        if (trans.is_write()) {
            m_out << ", ";
            print_data(trans);
        }
        m_out << ", len=" << std::noshowbase << std::dec << trans.get_data_length();
        print_control(ex);
        m_out << ")";
        SC_REPORT_INFO(name(), m_out.str().c_str());
    }

    /* Debug access proceeds */
    unsigned int ret = amba_pv_m->transport_dbg(trans);

    if (is_debug_verbose()) {
        m_out.str("");

        /* Print response */
        m_out << cmd;
        if (trans.is_read()) {
            print_data(trans);
        }
        m_out << "): " << std::dec << ret;
        SC_REPORT_INFO(name(), m_out.str().c_str());
    }
    return (ret);
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * This version of the method forwards this DMI access request to the slave and prints its contents.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_simple_probe<BUSWIDTH>::get_direct_mem_ptr(int socket_id,
                                                   amba_pv_transaction & trans,
                                                   tlm::tlm_dmi & dmi_data) {
    std::string cmd = "";
    amba_pv_extension * ex = NULL;

    /* Retrieve AMBA-PV extension */
    trans.get_extension(ex);

    /* Print DMI request */
    if (is_dmi_verbose()) {
        m_out.str("");

        /* Print request */
        cmd = "get_direct_mem_ptr(";
        if (trans.is_read()) {
            m_out << cmd << "read";
        } else {
            m_out << cmd << "write";
        }
        m_out << ", addr=" << std::showbase << std::hex << trans.get_address();
        print_control(ex);
        m_out << ")";
        SC_REPORT_INFO(name(), m_out.str().c_str());
    }

    /* DMI request proceeds... */
    bool ret = amba_pv_m->get_direct_mem_ptr(trans, dmi_data);

    if (is_dmi_verbose() && (ex != NULL)) {
        m_out.str("");

        /* Print response */
        m_out << cmd << "start_address=" << std::showbase << std::hex << dmi_data.get_start_address()
              << ", end_address=" << std::showbase << std::hex << dmi_data.get_end_address() << ", access={";
        if (dmi_data.is_read_allowed()) {
            m_out << "read";
        }
        if (dmi_data.is_write_allowed()) {
            if (dmi_data.is_read_allowed()) {
                m_out << ", ";
            }
            m_out << "write";
        }
        m_out << "}): " << (ret? "true": "false");
        SC_REPORT_INFO(name(), m_out.str().c_str());
    }
    return (ret);
}

/**
 * @brief       Invalidates DMI pointers previously established for the specified DMI region.
 *
 * This version of the method forwards this DMI call to the master after printing its arguments.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::invalidate_direct_mem_ptr(int socket_id,
                                                          sc_dt::uint64 start_range,
                                                          sc_dt::uint64 end_range) {
    if (is_dmi_verbose()) {
        m_out.str("");
        m_out << "invalidate_direct_mem_ptr(start_range=" << std::showbase << std::hex << start_range << ", end_range="
              << std::showbase << std::hex << end_range << ")";
        SC_REPORT_INFO(name(), m_out.str().c_str());
    }
    amba_pv_s->invalidate_direct_mem_ptr(start_range, end_range);
}

/*
 * Prints a transaction control information.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::print_control(amba_pv_control * ctrl) {
    if (ctrl == NULL) {
        return;
    }
    m_out << ", id=" << std::showbase << std::hex << ctrl->get_id();
    if (ctrl->is_privileged()) {
        m_out << ", privileged";
    }
    if (ctrl->is_non_secure()) {
        m_out << ", non_secure";
    }
    if (ctrl->is_instruction()) {
        m_out << ", instruction";
    }
    if (ctrl->is_exclusive()) {
        m_out << ", exclusive";
    }
    if (ctrl->is_locked()) {
        m_out << ", locked";
    }
    if (ctrl->is_bufferable()) {
        m_out << ", bufferable";
    }
    if (ctrl->is_cacheable()) {
        m_out << ", cacheable";
    }
    if (ctrl->is_read_allocate()) {
        m_out << ", read_allocate";
    }
    if (ctrl->is_write_allocate()) {
        m_out << ", write_allocate";
    }
#if defined(AMBA_PV_INCLUDE_ATTRIBUTES)
    if (ctrl->attributes_size() > 0) {
        m_out << ", {";
        for (amba_pv_attributes::const_iterator_type i = ctrl->attributes_begin();
             (i != ctrl->attributes_end());
             i ++) {
            if (i != ctrl->attributes_begin()) {
                m_out << ", ";
            }
            m_out << i->first << "=" << i->second;
        }
        m_out << "}";
    }
#endif  /* defined(AMBA_PV_INCLUDE_ATTRIBUTES) */
}

/*
 * Dumps a transaction data.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_simple_probe<BUSWIDTH>::print_data(amba_pv_transaction & trans) {
    m_out << "data=";
    if (is_data_verbose()) {
        m_out << "{";
        for (unsigned int i = 0; (i < trans.get_data_length()); i += 1) {
            if (i > 0) {
                m_out << ", ";
            }
            m_out << std::showbase << std::hex << static_cast<unsigned int>(trans.get_data_ptr()[i]);
        }
        m_out << "}";
    } else {
        m_out << static_cast<void *>(trans.get_data_ptr());
    }
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_SIMPLE_PROBE__H) */
