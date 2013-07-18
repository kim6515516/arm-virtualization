/*
 * AMBA-PV: amba_pv_decoder.h - AMBA-PV bus decoder model.
 *
 * Copyright 2007-2009, 2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_DECODER__H
#define AMBA_PV_DECODER__H

/**
 * @file        amba_pv_decoder.h
 *
 * @brief       AMBA-PV bus decoder model.
 */

/* Includes */
#include "sockets/amba_pv_master_socket.h"
#include "sockets/amba_pv_slave_socket.h"
#include "sockets/amba_pv_socket_array.h"
#include "models/amba_pv_address_map.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV bus decoder model.
 *
 * Each master is bound to an @e amba_pv_s[...] slave socket of the decoder,
 * and each of the @e amba_pv_m[...] master sockets belonging to the decoder
 * is bound to a socket belonging to a different slave.
 * Each master-to-slave socket connection is point-to-point.
 * The numbers of slave and master sockets of the decoder are specified using
 * template arguments.
 *
 * This decoder routes transactions through to the appropriate slave depending
 * on the transaction address, translating the address to local address for
 * each slave as it does so. The same address translation applies also to DMI
 * and debug transactions.
 *
 * @note        amba_pv_decoder does not currently support locked transactions
 *              (see amba_pv_control::set_locked()). Any locked transaction
 *              will be handled as if it were not locked.
 *
 * @note        The names of the master sockets follows the scheme
 *              @c "amba_pv_m%d", and the name for the slave sockets follows
 *              the scheme @c "amba_pv_s%d", where @c %d is the socket index.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 * @param       NUMMASTERS number of masters connected to this decoder.
 *              Defaults to 1.
 * @param       NUMSLAVES number of slaves connected to this decoder. Defaults
 *              to 1.
 */
template<unsigned int BUSWIDTH = 64,
         int NUMMASTERS = 1,
         int NUMSLAVES = 1>
class amba_pv_decoder:
    public virtual amba_pv_fw_transport_if,
    public virtual amba_pv_bw_transport_if,
    public sc_core::sc_module {

    /* Typdefs */
    typedef amba_pv_slave_socket<BUSWIDTH> slave_socket_type;
    typedef amba_pv_master_socket<BUSWIDTH> master_socket_type;
    typedef typename slave_socket_type::base_type base_slave_socket_type;
    typedef tlm::tlm_fw_transport_if<amba_pv_protocol_types> if_type;
    typedef sc_core::sc_export<if_type> export_type;

    /* Sockets */
    public:

        /**
         * @brief Slaves socket array.
         */
        amba_pv_socket_array<slave_socket_type> amba_pv_s;

        /**
         * @brief Masters socket array.
         */
        amba_pv_socket_array<master_socket_type> amba_pv_m;

    /* Construction */
        explicit amba_pv_decoder(const sc_core::sc_module_name &);
        amba_pv_decoder(const sc_core::sc_module_name &, const std::string &);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        void bind(int,
                  base_slave_socket_type &,
                  const sc_dt::uint64 &,
                  const sc_dt::uint64 &,
                  bool /* default_map */ = false);
        void operator() (int,
                         base_slave_socket_type &,
                         const sc_dt::uint64 &,
                         const sc_dt::uint64 &,
                         bool /* default_map */ = false);

    /* Accessors */
        unsigned int get_id_shift() const;
        void set_id_shift(unsigned int);
        std::string get_map_file() const;
        void set_map_file(const std::string &);
        amba_pv_address_map get_address_map() const;
        void set_address_map(const amba_pv_address_map &);
        amba_pv_address_map get_default_address_map() const;
        void set_default_address_map(const amba_pv_address_map &);
        void load_address_map(const std::string &);
        void load_address_map(std::istream &);
        void print_address_map(const std::string &) const;
        void print_address_map(std::ostream &) const;
        void set_verbose(bool /* verbose */ = true);

    /* Forward interface */
    protected:
        virtual void b_transport(int,
                                 amba_pv_transaction &,
                                 sc_core::sc_time &);
        virtual unsigned int transport_dbg(int, amba_pv_transaction &);
        virtual bool get_direct_mem_ptr(int,
                                        amba_pv_transaction &,
                                        tlm::tlm_dmi &);

    /* Backward interface */
        virtual void
        invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);

    /* Implementation */
    private:

        /* Member variables */
        std::string m_map_file;
        amba_pv_address_map m_map;
        amba_pv_address_map m_default_map;
        unsigned int m_id_shift;
        bool m_verbose;

        /* sc_module override */
        virtual void end_of_elaboration();

        /* Helpers */
        bool decode(amba_pv_transaction &, amba_pv_address_region * &) const;
        bool find_slave(int, amba_pv_address_region * &) const;
        void update_slave_rank(amba_pv_address_map &);
        void detect_address_overlap(amba_pv_address_map &);
        void update_id(amba_pv_transaction &, int) const;
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name module name.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::amba_pv_decoder(const sc_core::sc_module_name & name):
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s", NUMMASTERS),
    amba_pv_m("amba_pv_m", NUMSLAVES),
    m_id_shift(static_cast<unsigned int>(log(static_cast<double>(NUMMASTERS))
                                         / log(2.0))),
    m_verbose(false) {

    /* Bindings */
    for (int i = 0; (i < NUMMASTERS); i += 1) {
        amba_pv_s[i].set_socket_id(i);
        amba_pv_s[i](* this);
    }
    for (int i = 0; (i < NUMSLAVES); i += 1) {
        amba_pv_m[i].set_socket_id(i);
        amba_pv_m[i](* this);
    }
}

/**
 * @brief       Parameterized constructor.
 *
 * @param       name module name.
 * @param       file file from which the address map of this decoder is loaded.
 *
 * @note        The use of an address map file relies on the
 *              @c sc_core::sc_find_object() method to find the slave sockets
 *              bound to the master sockets of this decoder. OSCI TLM 2.0, 9
 *              Jun 2008, contains bugs in the convenience sockets, as their
 *              names are computed by @c sc_core::sc_gen_unique_name(). It is
 *              recommended to use the bind() methods rather than such map file
 *              when binding to OSCI TLM 2.0 convenience sockets. The OSCI TLM
 *              2.0.1 release, 15 Jul 2009, fixes this.
 *
 * @see         bind()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::amba_pv_decoder(const sc_core::sc_module_name & name,
                                            const std::string & file):
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s", NUMMASTERS),
    amba_pv_m("amba_pv_m", NUMSLAVES),
    m_map_file(file),
    m_id_shift(static_cast<unsigned int>(log(static_cast<double>(NUMMASTERS))
                                         / log(2.0))),
    m_verbose(false) {

    /* Bindings */
    for (int i = 0; (i < NUMMASTERS); i += 1) {
        amba_pv_s[i].set_socket_id(i);
        amba_pv_s[i](* this);
    }
    for (int i = 0; (i < NUMSLAVES); i += 1) {
        amba_pv_m[i].set_socket_id(i);
        amba_pv_m[i](* this);
    }
}

/**
 * @brief       Returns the kind string of this decoder.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline const char *
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::kind() const  {
    return ("amba_pv_decoder");
}

/**
 * @brief       Binds the specified slave socket to the master socket of this
 *              decoder at the specified @a index.
 *
 * @param       index master socket index.
 * @param       s slave socket to bind to the master socket.
 * @param       start start address of the memory region associated to the
 *              slave socket @a s.
 * @param       end end address of this region.
 * @param       default_map @c true to add the memory region to the default
 *              address map instead; default to @c false.
 *
 * @see         operator()()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::bind(int index,
                                 base_slave_socket_type & s,
                                 const sc_dt::uint64 & start,
                                 const sc_dt::uint64 & end,
                                 bool default_map /* = false */) {

    /* Bind master socket to given slave socket */                    
    amba_pv_m[index].bind(s);

    /* Add corresponding memory region to selected address map */
    if (default_map) {
        m_default_map.add_region(start,
                                 end,
                                 s.name(),
                                 amba_pv_m[index].get_socket_id());
    } else {
        m_map.add_region(start,
                         end,
                         s.name(),
                         amba_pv_m[index].get_socket_id());
    }
}

/**
 * @brief       Binds the specified slave socket to the master socket of this
 *              decoder at the specified @a index.
 *
 * @param       index master socket index.
 * @param       s slave socket to bind to the master socket.
 * @param       start start address of the memory region associated to the
 *              slave socket @a s.
 * @param       end end address of this region.
 * @param       default_map @c true to add the memory region to the default
 *              address map instead; default to @c false.
 *
 * @see         bind()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::operator() (int index,
                                        base_slave_socket_type & s,
                                        const sc_dt::uint64 & start,
                                        const sc_dt::uint64 & end,
                                        bool default_map /* = false */) {
    bind(index, s, start, end, default_map);
}

/**
 * @brief       Returns the transaction ID shift value.
 *
 * This method returns the shift value used in updating the transaction ID, to
 * ensure its uniqueness, before forwarding the transaction throught to the
 * addressed slave.
 * The transaction ID shift value is initialised by default to the following:
 * @code log(NUMMASTERS) / log(2.0) @endcode
 *
 * @see         set_id_shift(), amba_pv_control
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline unsigned int
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::get_id_shift() const {
    return (m_id_shift);
}

/**
 * @brief       Sets the transaction ID shift value.
 *
 * This method sets the shift value used in updating the transaction ID, to
 * ensure its uniqueness, before forwarding the transaction throught to the
 * addressed slave.
 * When the shift value is set to zero, the transaction ID will not be updated.
 *
 * @see         get_id_shift(), amba_pv_control
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::set_id_shift(unsigned int id_shift) {
    m_id_shift = id_shift;
}

/**
 * @brief       Returns the address map file.
 *
 * @see         set_map_file()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline std::string
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::get_map_file() const {
    return (m_map_file);
}

/**
 * @brief       Sets the address map file.
 *
 * @param       file file from which the address map of this decoder is loaded.
 *
 * @note        The use of an address map file relies on the
 *              @c sc_core::sc_find_object() method to find the slave sockets
 *              bound to the master sockets of this decoder. OSCI TLM 2.0, 9
 *              Jun 2008, contains bugs in the convenience sockets, as their
 *              names are computed by @c sc_core::sc_gen_unique_name(). It is
 *              recommended to use the bind() methods rather than such map file
 *              when binding to OSCI TLM 2.0 convenience sockets. The OSCI TLM
 *              2.0.1 release, 15 Jul 2009, fixes this.
 *
 * @see         get_map_file()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::set_map_file(const std::string & file) {
    m_map_file = file;
}

/**
 * @brief       Returns the address map of this decoder.
 *
 * @see         set_address_map()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline amba_pv_address_map
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::get_address_map() const {
    return (m_map);
}

/**
 * @brief       Sets the address map of this decoder.
 *
 * @note        Setting the address map is not possible if the simulation is
 *              running.
 *
 * @param       map new address map.
 *
 * @see         get_address_map()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::set_address_map(const amba_pv_address_map & map) {

    /* Ensure we are not running... */
#if SYSTEMC_VERSION >= 20060505
    if (sc_core::sc_is_running()) {
#else
    if (sc_get_curr_simcontext()->is_running()) {
#endif
        SC_REPORT_ERROR(kind(),
                        "set_address_map(): simulation is running");
    }
    m_map = map;
}

/**
 * @brief       Returns the default address map of this decoder.
 *
 * @see         set_default_address_map()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline amba_pv_address_map
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::get_default_address_map() const {
    return (m_default_map);
}

/**
 * @brief       Sets the default address map of this decoder.
 *
 * @note        Setting the default address map is not possible if the
 *              simulation is running.
 *
 * @param       map new default address map.
 *
 * @see         get_default_address_map()
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::set_default_address_map(const amba_pv_address_map & map) {

    /* Ensure we are not running... */
#if SYSTEMC_VERSION >= 20060505
    if (sc_core::sc_is_running()) {
#else
    if (sc_get_curr_simcontext()->is_running()) {
#endif
        SC_REPORT_ERROR(kind(),
                        "set_default_address_map(): simulation is running");
    }
    m_default_map = map;
}

/**
 * @brief       Loads the address map of this decoder from the specified file.
 *
 * @note        Loading the address map is not possible if the simulation is
 *              running.
 *
 * @param       file file from which the address map of this decoder is loaded.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::load_address_map(const std::string & file) {
    std::ifstream ifs;

    ifs.open(file.c_str());
    if (! ifs.is_open()) {
        std::string msg("load_address_map(): error opening \"");

        msg += file;
        msg += "\"";
        SC_REPORT_WARNING(kind(), msg.c_str());
    } else {
        load_address_map(ifs);
    }
}

/**
 * @brief       Loads the address map of this decoder from the specified stream.
 *
 * @note        Loading the address map is not possible if the simulation is
 *              running.
 *
 * @param       is stream from which load the address map of this decoder is
 *              loaded.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::load_address_map(std::istream & is) {
    char buf[1024];

    /* Ensure we are not running... */
#if SYSTEMC_VERSION >= 20060505
    if (sc_core::sc_is_running()) {
#else
    if (sc_get_curr_simcontext()->is_running()) {
#endif
        SC_REPORT_ERROR(kind(),
                        "load_address_map(): simulation is running");
    }

    /* Get a line... */
    while (is.getline(buf, sizeof(buf) - 1, '\n') || is.gcount()) {
        if (is.eof()) {
            break;
        } else if (is.fail()) {
            std::string msg("load_address_map(): \"" + m_map_file
                            + "\": line too long");

            SC_REPORT_ERROR(kind(),
                            msg.c_str());
            is.clear(is.rdstate() & ~std::ios::failbit);
        } else {
            int pos = 0;

            /* Skip spaces. */
            while (std::isspace(buf[pos])) {
                pos += 1;
            };

            std::string line(buf + pos);

            if ((line[0] == ';') || (line[0] == '#')) {

                /* Comment line; skip it. */
            } else if (line.length() == 0) {

                /* Empty line; ignore it. */
            } else {
                std::string slave_name, default_map;
                sc_dt::uint64 start = 0, end = sc_dt::uint64(-1);
                std::stringstream ls(line);

                /* Read address region: 1) name */
                ls >> slave_name;

                /* Read address region: 2) start and end addresses
                 * using hexadecimal format */
                ls >> std::hex >> start >> end;

                /* Read address region: 3) check if memory region must be added
                 * to default memory map */
                ls >> default_map;

                /* Add region to corresponding map.
                 * The slave rank will be initialised to the corresponding
                 * socket identifier during end_of_elaboration(). */
                if (default_map == "default") {
                    m_default_map.add_region(start, end, slave_name);
                } else {
                    m_map.add_region(start, end, slave_name);
                }
            }
        }
    }
}

/**
 * @brief       Prints the address map of this decoder.
 *
 * @param       file file to which the address map of this decoder is printed.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::print_address_map(const std::string & file) const {
    std::ofstream ofs;

    ofs.open(file.c_str());
    if (! ofs.is_open()) {
        std::string msg("print_address_map(): error opening \"");

        msg += file;
        msg += "\"";
        SC_REPORT_WARNING(kind(), msg.c_str());
    } else {
        print_address_map(ofs);
    }
}

/**
 * @brief       Prints the address map of this decoder.
 *
 * @param       os stream to which the address map of this decoder is printed.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::print_address_map(std::ostream & os) const {
    amba_pv_address_map::const_iterator i;

    os << "# " << name() << ": address map\n\n";
    for (i = m_map.begin(); (i != m_map.end()); i ++) {

        /* Print address region: 1) slave name */
        os << (* i)->get_slave_name() << " ";
    
        /* Print address region: 2) start and end addresses using hexadecimal
         * format */
        os << std::hex << std::showbase << (* i)->get_start() << " "
           << (* i)->get_end() << std::endl;
    }
    for (i = m_default_map.begin(); (i != m_default_map.end()); i ++) {

        /* Print address region: 1) slave name */
        os << (* i)->get_slave_name() << " ";

        /* Print address region: 2) start and end addresses using hexadecimal
         * format, default address region marker */
        os << std::hex << std::showbase << (* i)->get_start() << " "
           << (* i)->get_end() << " default\n";
    }
}

/**
 * @brief       Sets the verbosity of this decoder.
 *
 * The set_verbose() method turns on or off the display of <tt>"decode error
 * at address..."</tt> warning messages.
 *
 * @param       verbose @c true (default) to turn on the display of warning
 *              messages, @c false otherwise.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::set_verbose(bool verbose /* = true */) {
    m_verbose = verbose;
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method decodes the address of the specified transaction
 * and forwards it through the corresponding master socket to the addressed
 * slave.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::b_transport(int socket_id,
                                        amba_pv_transaction & trans,
                                        sc_core::sc_time & t) {

    /* Decode incoming request address */
    amba_pv_address_region * r = NULL;

    if (decode(trans, r)) {

        /* Adjust transaction ID */
        update_id(trans, socket_id);

        /* Send request out to appropriate slave */
        amba_pv_m[r->get_slave_rank()]->b_transport(trans, t);
        return;
    }

    /* Decode error */
    if (m_verbose) {
        std::stringstream str;

        str << "b_transport(): decode error at address: "
            << std::hex << std::showbase << trans.get_address();
        SC_REPORT_WARNING(kind(), str.str().c_str());
    }

    /* Retrieve AMBA-PV extension and set response accordingly */
    amba_pv_extension * ex = NULL;

    trans.get_extension(ex);
    if (ex != NULL) {
        ex->set_decerr();
    }
    trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
}

/**
 * @brief       Debug access to a target.
 *
 * This version of the method decodes the address of the specified transaction
 * and forwards it through the corresponding master socket to the addressed
 * slave.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline unsigned int
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::transport_dbg(int socket_id,
                                          amba_pv_transaction & trans) {

    /* Decode incoming request address */
    amba_pv_address_region * r = NULL;

    if (decode(trans, r)) {

        /* Adjust transaction ID */
        update_id(trans, socket_id);

        /* Send request out to appropriate slave */
        return (amba_pv_m[r->get_slave_rank()]->transport_dbg(trans));
    }

    /* Decode error */
    if (m_verbose) {
        std::stringstream str;

        str << "transport_dbg(): decode error at address: "
            << std::hex << std::showbase << trans.get_address();
        SC_REPORT_WARNING(kind(), str.str().c_str());
    }
    return 0;
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * This version of the method decodes the address of the specified transaction
 * and forwards it through the corresponding master socket to the addressed
 * slave.
 * On return, the address range of the DMI descriptor is adjusted to the slave
 * mapped range.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline bool
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::get_direct_mem_ptr(int socket_id,
                                               amba_pv_transaction & trans,
                                               tlm::tlm_dmi & dmi_data) {

    /* Decode incoming request address */
    amba_pv_address_region * r = NULL;

    if (decode(trans, r)) {
        bool dmi_allowed;

        /* Adjust transaction ID */
        update_id(trans, socket_id);

        /* Send request out to appropriate slave */
        dmi_allowed =
            amba_pv_m[r->get_slave_rank()]->get_direct_mem_ptr(trans, dmi_data);

        /* Adjust DMI range to slave mapped range */
        dmi_data.set_start_address(dmi_data.get_start_address()
                                   + r->get_start());
        if (dmi_data.get_end_address() <= (r->get_end() - r->get_start())) {
            dmi_data.set_end_address(dmi_data.get_end_address() + r->get_start());
        } else {
            dmi_data.set_end_address(r->get_end());
        }
        return (dmi_allowed);
    }

    /* Decode error */
    if (m_verbose) {
        std::stringstream str;

        str << "get_direct_mem_ptr(): decode error at address: "
            << std::hex << std::showbase << trans.get_address();
        SC_REPORT_WARNING(kind(), str.str().c_str());
    }
    return false;
}

/**
 * @brief       Invalidates DMI pointers previously established for the
 *              specified DMI region.
 *
 * This version of the method adjusts the address range of the DMI descriptor
 * to the slave mapped range and broadcasts the invalidate_direct_mem_ptr()
 * call through the slave sockets to all masters.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::invalidate_direct_mem_ptr(int socket_id,
                                                      sc_dt::uint64 start_range,
                                                      sc_dt::uint64 end_range) {

    /* Encode incoming notification */
    amba_pv_address_region * r = NULL;

    if (find_slave(socket_id, r)) {

        /* Adjust DMI range to slave mapped range */
        start_range += r->get_start();
        if (end_range <= (r->get_end() - r->get_start())) {
            end_range += r->get_start();
        } else {
            end_range = r->get_end();
        }

        /* Forward call to all masters */
        for (int i = 0; (i < NUMMASTERS); i += 1) {
            amba_pv_s[i]->invalidate_direct_mem_ptr(start_range, end_range);
        }
        return;
    }

    /* Slave not found */
    if (m_verbose) {
        std::stringstream str;

        str << "invalidate_direct_mem_ptr(): slave not found: "
            << std::dec << std::noshowbase << socket_id;
        SC_REPORT_WARNING(kind(), str.str().c_str());
    }
}

/*
 * Loads the address map file when elaboration, i.e. socket binding is
 * done and assigns each map entry with the associated slave rank, i.e. socket
 * identifier.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::end_of_elaboration() {

    /* Load address map file */
    if (! m_map_file.empty()) {
        load_address_map(m_map_file.c_str());
    }

    /* Update slave rank of address map entries */
    update_slave_rank(m_map);

    /* Update slave rank of default address map */
    update_slave_rank(m_default_map);

    /* Address overlap detection.
     * For both address maps */
    detect_address_overlap(m_map);
    detect_address_overlap(m_default_map);
}

/*
 * Returns whether or not a given transaction is decoded by the address map of
 * this decoder.
 * If so, updates the transaction address.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline bool
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::decode(amba_pv_transaction & trans,
                                   amba_pv_address_region * & r) const {

    /* Decode incoming request address */
    if (m_map.decode(trans.get_address(), r)
        && (r->get_slave_rank() != -1)) {
        trans.set_address(trans.get_address() - r->get_start());
        return true;
    }
    if (m_default_map.decode(trans.get_address(), r)
        && (r->get_slave_rank() != -1)) {
        trans.set_address(trans.get_address() - r->get_start());
        return true;
    }
    return false;
}

/*
 * Finds the slave mapped range with the specified socket identifier.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline bool
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::find_slave(int socket_id,
                                       amba_pv_address_region * & r) const {
    amba_pv_address_map::const_iterator i;

    for (i = m_map.begin(); (i != m_map.end()); i ++) {
        if ((* i)->get_slave_rank() == socket_id) {
            r = (* i);
            return true;
        }
    }
    for (i = m_default_map.begin(); (i != m_default_map.end()); i ++) {
        if ((* i)->get_slave_rank() == socket_id) {
            r = (* i);
            return true;
        }
    }
    return false;
}

/*
 * Update the slave rank of the given address map.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::update_slave_rank(amba_pv_address_map & m) {
    amba_pv_address_map::iterator i;

    for (i = m.begin(); (i != m.end()); i ++) {
        if ((* i)->get_slave_rank() != -1) {

            /* Slave rank already set */
            continue;
        }

        /* Find slave socket and set slave rank to socket identifier */
#if defined(SYSTEMC_VERSION) && SYSTEMC_VERSION <= 20050714
        sc_object * o =
            sc_core::sc_get_curr_simcontext()->find_object((* i)->get_slave_name().c_str());
#else
        sc_object * o =
            sc_core::sc_find_object((* i)->get_slave_name().c_str());
#endif
        export_type * s = dynamic_cast<export_type *>(o);
        bool found = false;

        if (s != NULL) {
            for (int j = 0; (j < NUMSLAVES); j += 1) {
                if (s->get_interface() == amba_pv_m[j].get_interface()) {
                    (* i)->set_slave_rank(amba_pv_m[j].get_socket_id());
                    found = true;
                    break;
                }
            }
        }
        if (! found) {
            std::string msg("update_slave_rank(): \"");

            msg += (* i)->get_slave_name() + "\": slave socket not found";
            SC_REPORT_WARNING(kind(), msg.c_str());
        }
    }
}

/*
 * Address overlap detection.
 * For each region object, the other region objects are checked to detect
 * address overlap.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::detect_address_overlap(amba_pv_address_map & m) {
    amba_pv_address_map::const_iterator j, k;

    /* For each region object, the other region objects are checked to detect
     * address overlap. */
    for (j = m.begin(); (j != m.end()); j ++) {
        for (k = j + 1; (k != m.end()); k ++) {
            if (((* k)->decode((* j)->get_start())) ||
                ((* k)->decode((* j)->get_end()))   ||
                ((* j)->decode((* k)->get_start())) || 
                ((* j)->decode((* k)->get_end()))) {
                std::string msg("");
                std::stringstream strstr(msg);

                /* Print warning message if address map collision detected */
                strstr << "detect_address_overlap(): "
                       << std::showbase << std::hex  << " \""
                       << (* k)->get_slave_name() << "\" address region ("
                       << (* k)->get_start() << " - " << (* k)->get_end()
                       << ") overlaps address region for \""
                       << (* j)->get_slave_name() << "\" ("
                       << (* j)->get_start() << " - " << (* j)->get_end()
                       << ")";
                SC_REPORT_WARNING(kind(), strstr.str().c_str());
            }
        }
    }
}

/*
 * Updates incoming transaction ID to maintain its uniqueness.
 */
template<unsigned int BUSWIDTH, int NUMMASTERS, int NUMSLAVES>
inline void
amba_pv_decoder<BUSWIDTH,
                NUMMASTERS,
                NUMSLAVES>::update_id(amba_pv_transaction & trans,
                                      int socket_id) const {

    /* Is shifting enabled? */
    if (m_id_shift == 0) {
        return;
    }
    
    /* Retrieve AMBA-PV extension and shift transaction ID */
    amba_pv_extension * ex = NULL;

    trans.get_extension(ex);
    if (ex != NULL) {
        ex->set_id((ex->get_id() << m_id_shift) + socket_id);
    }
}

}   /* namespave amba_pv */

#endif  /* defined(AMBA_PV_DECODER__H) */
