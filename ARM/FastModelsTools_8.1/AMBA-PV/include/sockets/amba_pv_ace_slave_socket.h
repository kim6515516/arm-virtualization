/*
 * AMBA-PV: amba_pv_ace_slave_socket.h - AMBA-PV ACE socket to be instantiated
 *                                       on the slave side.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_ACE_SLAVE_SOCKET__H
#define AMBA_PV_ACE_SLAVE_SOCKET__H

/**
 * @file        amba_pv_ace_slave_socket.h
 *
 * @brief       AMBA-PV ACE socket to be instantiated on the slave side.
 */

/* Includes */
#include "sockets/amba_pv_slave_socket.h"
#include "sockets/amba_pv_master_socket.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV ACE socket to be instantiated on the slave side.
 *
 * This socket is for use as an AMBA ACE slave socket that is bound by an AMBA
 * ACE master socket amba_pv_ace_master_socket. The amba_pv_ace_slave_socket
 * directly inherits from the amba_pv_slave_socket class, but in addition
 * includes an extra upstream TLM interface as well as the downstream TLM
 * interface. The upstream TLM interface is used to model the snoop channels
 * that the AMBA ACE bus architecture requires.
 *
 * The upstream path is implemented using an additional master/slave socket
 * pair that are private data members of amba_pv_ace_slave_socket and
 * amba_pv_ace_master_socket respectively. This extra upstream socket pair
 * are automatically bound when the downstream master to slave sockets are
 * bound.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_ace_slave_socket: public amba_pv_slave_socket<BUSWIDTH> {

    /* Constructor */
    public:
        amba_pv_ace_slave_socket();
        explicit amba_pv_ace_slave_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        void bind(amba_pv_snoop_socket<BUSWIDTH> &);

    /* Upstream blocking snoop */
        void b_snoop(int, amba_pv_transaction &, sc_core::sc_time &);
        void b_snoop(amba_pv_transaction &, sc_core::sc_time &);

    /* Upstream debug */
        unsigned int snoop_dbg(int, amba_pv_transaction &);
        unsigned int snoop_dbg(amba_pv_transaction &);

    /* Implementation */
    private:

        /* Data members */
        amba_pv_master_socket<BUSWIDTH> m_snoop;
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_ace_slave_socket<BUSWIDTH>::amba_pv_ace_slave_socket():
    amba_pv_slave_socket<BUSWIDTH>(sc_core::sc_gen_unique_name("amba_pv_ace_slave_socket")),
    m_snoop(sc_core::sc_gen_unique_name("amba_pv_ace_slave_socket_snoop")) {
}

/**
 * @brief       Constructor.
 *
 * @param       name socket name.
 * @param       socket_id socket identifier (defaults to 0).
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_ace_slave_socket<BUSWIDTH>::amba_pv_ace_slave_socket(const char * name,
                                                             int socket_id /* = 0 */):
    amba_pv_slave_socket<BUSWIDTH>(name, socket_id),
    m_snoop((std::string(name) + "_snoop").c_str(), socket_id) {
}

/**
 * @brief       Returns the kind string of this socket.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_ace_slave_socket<BUSWIDTH>::kind() const  {
    return ("amba_pv_ace_slave_socket");
}

/**
 * @brief       Binds the specified snoop slave socket to the snoop master
 *              socket.
 *
 * @param       upstream amba_pv_ace_slave_socket to bind to the snoop master
 *              socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_ace_slave_socket<BUSWIDTH>::bind(amba_pv_snoop_socket<BUSWIDTH> & upstream) {
    m_snoop.bind(upstream);
}


/**
 * @brief       Blocking upstream transport.
 *
 * This version of the method forwards the b_transport() call to the ACE master
 * socket bound to this ACE slave socket using the upstream snoop pathway.
 *
 * @param       socket_id socket identifier (ignored on the slave side).
 * @param       trans transaction.
 * @param       t timing annotation.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_ace_slave_socket<BUSWIDTH>::b_snoop(int socket_id,
                                            amba_pv_transaction & trans,
                                            sc_core::sc_time & t) {
    m_snoop.b_transport(trans, t);
}

/**
 * @brief       Blocking upstream transport.
 *
 * @param       trans transaction.
 * @param       t timing annotation.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_ace_slave_socket<BUSWIDTH>::b_snoop(amba_pv_transaction & trans,
                                            sc_core::sc_time & t) {
    b_snoop(0, trans, t);
}

/**
 * @brief       Upstream debug transport.
 *
 * This version of the method forwards the transport_dbg() call to the ACE
 * master socket bound to this ACE slave socket using the upstream snoop
 * pathway.
 *
 * @param       socket_id socket identifier (ignored on the slave side).
 * @param       trans transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_ace_slave_socket<BUSWIDTH>::snoop_dbg(int socket_id,
                                              amba_pv_transaction & trans ) {
    return m_snoop.transport_dbg(trans);
}

/**
 * @brief       Upstream debug transport.
 *
 * @param       trans transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_ace_slave_socket<BUSWIDTH>::snoop_dbg(amba_pv_transaction & trans ) {
    return snoop_dbg(0, trans);
}


}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_ACE_SLAVE_SOCKET__H) */
