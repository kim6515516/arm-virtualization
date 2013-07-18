/*
 * AMBA-PV: amba_pv_ace_master_socket.h - AMBA-PV ACE socket to be instantiated
 *                                        on the master side.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_ACE_MASTER_SOCKET__H
#define AMBA_PV_ACE_MASTER_SOCKET__H

/**
 * @file        amba_pv_ace_master_socket.h
 *
 * @brief       AMBA-PV ACE socket to be instantiated on the master side.
 */

/* Includes */
#include "sockets/amba_pv_master_socket.h"
#include "sockets/amba_pv_snoop_socket.h"
#include "sockets/amba_pv_ace_slave_socket.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV ACE socket to be instantiated on the master side.
 *
 * This socket is for use as an AMBA ACE master socket bound to one or more AMBA
 * ACE slave sockets. The amba_pv_ace_master_socket directly inherits from the
 * amba_pv_master_socket class, but in addition includes an extra upstream TLM
 * interface as well as the downstream TLM interface. The upstream TLM interface
 * is used to model the snoop channels that the AMBA ACE bus architecture
 * requires.
 *
 * amba_pv_ace_master_socket provides implementations for the
 * amba_pv_bw_transport_if and amba_pv_bw_snoop_if user-layer interfaces the
 * composite interface name is amba_pv_bw_transport_and_snoop_if.
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
class amba_pv_ace_master_socket: public amba_pv_master_socket<BUSWIDTH> {

    public:
    /* Constructor */
        amba_pv_ace_master_socket();
        explicit amba_pv_ace_master_socket(const char *, int = 0);
   
    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        void bind(amba_pv_ace_slave_socket<BUSWIDTH> &);
        void operator() (amba_pv_ace_slave_socket<BUSWIDTH> &);
        void bind(amba_pv_bw_transport_and_snoop_if &);
        void operator() (amba_pv_bw_transport_and_snoop_if &);

    /* Implementation */
    private:

        /* Data member */
        amba_pv_snoop_socket<BUSWIDTH> m_snoop;
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_ace_master_socket<BUSWIDTH>::amba_pv_ace_master_socket():
    amba_pv_master_socket<BUSWIDTH>(sc_core::sc_gen_unique_name("amba_pv_ace_master_socket")),
    m_snoop(sc_core::sc_gen_unique_name("amba_pv_ace_master_socket_snoop")) {
}

/**
 * @brief       Constructor.
 *
 * @param       name socket name.
 * @param       socket_id socket identifier (defaults to 0).
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_ace_master_socket<BUSWIDTH>::amba_pv_ace_master_socket(const char * name,
                                                               int socket_id /* = 0 */):
    amba_pv_master_socket<BUSWIDTH>(name, socket_id),
    m_snoop(sc_core::sc_gen_unique_name((std::string(name) + "_snoop").c_str()),
            socket_id) {
}

/**
 * @brief       Returns the kind string for this socket.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_ace_master_socket<BUSWIDTH>::kind() const  {
    return ("amba_pv_ace_master_socket");
}


/**
 * @brief       Binds the specified ACE slave socket to this ACE master socket.
 *
 * This method will also bind the ACE snoop master socket in the ACE slave
 * socket to the ACE snoop slave socket in this socket.
 *
 * @param       slave amba_pv_ace_slave_socket to bind to this socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_ace_master_socket<BUSWIDTH>::bind(amba_pv_ace_slave_socket<BUSWIDTH> & slave) {
    amba_pv_master_socket<BUSWIDTH>::bind(slave);
    slave.bind(m_snoop);
}

/**
 * @brief       Binds the specified ACE slave socket to this ACE master socket.
 *
 * @param       slave amba_pv_ace_slave_socket to bind to this socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_ace_master_socket<BUSWIDTH>::operator() (amba_pv_ace_slave_socket<BUSWIDTH>& slave) {
    bind(slave);
}


/**
 * @brief       Binds the specified interface to this socket.
 *
 * This method will also bind the ACE snoop slave socket in this socket to the
 * interface.
 *
 * @param       iface amba_pv_bw_transport_and_snoop_if interface to bind to
 *              this socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_ace_master_socket<BUSWIDTH>::bind(amba_pv_bw_transport_and_snoop_if & iface) {
    amba_pv_master_socket<BUSWIDTH>::bind(iface);
    m_snoop.bind(static_cast<amba_pv_bw_snoop_if &>(iface));
}


/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_bw_transport_and_snoop_if interface to bind to
 *              this socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_ace_master_socket<BUSWIDTH>::operator() (amba_pv_bw_transport_and_snoop_if & iface) {
    bind(iface);
}

}   /* namespave amba_pv */

#endif  /* defined(AMBA_PV_ACE_MASTER_SOCKET__H) */
