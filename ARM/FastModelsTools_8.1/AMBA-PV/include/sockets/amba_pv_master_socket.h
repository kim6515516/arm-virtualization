/*
 * AMBA-PV: amba_pv_master_socket.h - AMBA-PV socket to be instantiated on the
 *                                    master side.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_MASTER_SOCKET__H
#define AMBA_PV_MASTER_SOCKET__H

/**
 * @file        amba_pv_master_socket.h
 *
 * @brief       AMBA-PV socket to be instantiated on the master side.
 */

/* Includes */
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "bus/amba_pv_extension.h"
#include "core/amba_pv_types.h"
#include "core/amba_pv_core_ifs.h"
#include "user/amba_pv_if.h"
#include "sockets/amba_pv_socket_base.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV socket to be instantiated on the master side.
 *
 * This socket is for use as a master socket bound to one or more slave
 * sockets.
 *
 * amba_pv_master_socket provides implementations for the amba_pv_if user-layer
 * interface.
 *
 * This socket inherits from the OSCI TLM 2.0
 * @c tlm_utils::simple_initiator_socket_tagged class. A tagged socket enables a
 * component to determine through which socket an incoming method call arrived.
 * This is required if there are multiple master sockets such as in, for
 * example, a bus decoder.
 *
 * @note        The current implementation of amba_pv_master_socket inherits
 *              from OSCI TLM 2.0 @c tlm_utils::simple_initiator_socket_tagged.
 *              Hence, if compiling applications that use
 *              amba_pv_master_socket with OSCI SystemC, it is required to
 *              define the macro @c SC_INCLUDE_DYNAMIC_PROCESSES before
 *              including the OSCI SystemC header file.
 *
 * @note        This socket, as its base class
 *              @c tlm_utils::simple_initiator_socket_tagged, does not support
 *              hierarchical binding, master-socket-to-master-socket or
 *              slave-socket-to-slave-socket
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_master_socket:
    public virtual amba_pv_if<BUSWIDTH>,
    public amba_pv_socket_base,
    public tlm_utils::simple_initiator_socket_tagged<amba_pv_bw_transport_if,
                                                     BUSWIDTH,
                                                     amba_pv_protocol_types> {

    /* Typdefs */
    public:
        typedef
            tlm_utils::simple_initiator_socket_tagged<amba_pv_bw_transport_if,
                                                      BUSWIDTH,
                                                      amba_pv_protocol_types>
            base_type;

    /* Constructor */
        amba_pv_master_socket();
        explicit amba_pv_master_socket(const char *, int = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Convenience interface */
        virtual amba_pv_resp_t read(int,
                                    const sc_dt::uint64 &,
                                    unsigned char *,
                                    unsigned int,
                                    const amba_pv_control *,
                                    sc_core::sc_time &);
        amba_pv_resp_t read(const sc_dt::uint64 &,
                            unsigned char *,
                            unsigned int,
                            const amba_pv_control *,
                            sc_core::sc_time &);
        virtual amba_pv_resp_t write(int,
                                     const sc_dt::uint64 &,
                                     unsigned char *,
                                     unsigned int,
                                     const amba_pv_control *,
                                     unsigned char *,
                                     sc_core::sc_time &);
        amba_pv_resp_t write(const sc_dt::uint64 &,
                             unsigned char *,
                             unsigned int,
                             const amba_pv_control *,
                             unsigned char *,
                             sc_core::sc_time &);
        virtual amba_pv_resp_t burst_read(int,
                                          const sc_dt::uint64 &,
                                          unsigned char *,
                                          unsigned int,
                                          unsigned int,
                                          const amba_pv_control *,
                                          amba_pv_burst_t,
                                          sc_core::sc_time &);
        amba_pv_resp_t burst_read(const sc_dt::uint64 &,
                                  unsigned char *,
                                  unsigned int,
                                  unsigned int,
                                  const amba_pv_control *,
                                  amba_pv_burst_t,
                                  sc_core::sc_time &);
        virtual amba_pv_resp_t burst_write(int,
                                           const sc_dt::uint64 &,
                                           unsigned char *,
                                           unsigned int,
                                           unsigned int,
                                           const amba_pv_control *,
                                           amba_pv_burst_t,
                                           unsigned char *,
                                           unsigned int,
                                           sc_core::sc_time &);
        amba_pv_resp_t burst_write(const sc_dt::uint64 &,
                                   unsigned char *,
                                   unsigned int,
                                   unsigned int,
                                   const amba_pv_control *,
                                   amba_pv_burst_t,
                                   unsigned char *,
                                   unsigned int,
                                   sc_core::sc_time &);
        virtual bool get_direct_mem_ptr(int,
                                        tlm::tlm_command,
                                        const sc_dt::uint64 &,
                                        const amba_pv_control *,
                                        tlm::tlm_dmi &);
        bool get_direct_mem_ptr(tlm::tlm_command,
                                const sc_dt::uint64 &,
                                const amba_pv_control *,
                                tlm::tlm_dmi &);
        virtual unsigned int debug_read(int,
                                        const sc_dt::uint64 &,
                                        unsigned char *,
                                        unsigned int,
                                        const amba_pv_control *);
        virtual unsigned int debug_write(int,
                                         const sc_dt::uint64 &,
                                         unsigned char *,
                                         unsigned int,
                                         const amba_pv_control *);
        unsigned int debug_read(const sc_dt::uint64 &,
                                unsigned char *,
                                unsigned int,
                                const amba_pv_control *);
        unsigned int debug_write(const sc_dt::uint64 &,
                                 unsigned char *,
                                 unsigned int,
                                 const amba_pv_control *);

    /* Blocking transport */
        void b_transport(int, amba_pv_transaction &, sc_core::sc_time &);
        void b_transport(amba_pv_transaction &, sc_core::sc_time &);

    /* Debug transport */
        unsigned int transport_dbg(int, amba_pv_transaction &);
        unsigned int transport_dbg(amba_pv_transaction &);

    /* DMI accesses */
        bool get_direct_mem_ptr(int, amba_pv_transaction &, tlm::tlm_dmi &);
        bool get_direct_mem_ptr(amba_pv_transaction &, tlm::tlm_dmi &);

    /* Bindings */
        using base_type::bind;
        using base_type::operator();
        void bind(amba_pv_bw_transport_if &);
        void operator() (amba_pv_bw_transport_if &);
};

/* Functions */

/**
 * @brief       Default constructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_master_socket<BUSWIDTH>::amba_pv_master_socket():
    base_type(sc_core::sc_gen_unique_name("amba_pv_master_socket")) {
}

/**
 * @brief       Constructor.
 *
 * @param       name socket name.
 * @param       socket_id socket identifier (defaults to 0).
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_master_socket<BUSWIDTH>::amba_pv_master_socket(const char * name,
                                                       int socket_id /* = 0 */):
    amba_pv_socket_base(socket_id),
    base_type(name) {
}

/**
 * @brief       Returns the kind string of this socket.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_master_socket<BUSWIDTH>::kind() const  {
    return ("amba_pv_master_socket");
}

/**
 * @brief       Completes a read transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH>::read(int socket_id,
                                      const sc_dt::uint64 & addr,
                                      unsigned char * data,
                                      unsigned int size,
                                      const amba_pv_control * ctrl,
                                      sc_core::sc_time & t) {
    amba_pv_transaction trans;
    amba_pv_extension ex(size, ctrl);
    
    trans.set_read();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(size);
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        b_transport(socket_id, trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ex.get_resp());
}

/**
 * @brief       Completes a read transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer. It must point to an array of
 *              @a size bytes.
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
 *              64, 128]. The transaction size must be less than or equal to
 *              the value returned by get_bus_width_bytes().
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused
 *              on the master side).
 * @param       t timing annotation.
 *
 * @return      @c AMBA_PV_OKAY if the transaction is successful.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH>::read(const sc_dt::uint64 & addr,
                                      unsigned char * data,
                                      unsigned int size,
                                      const amba_pv_control * ctrl,
                                      sc_core::sc_time & t) {
    return (read(0, addr, data, size, ctrl, t));
}

/**
 * @brief       Completes a write transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH>::write(int socket_id,
                                       const sc_dt::uint64 & addr,
                                       unsigned char * data,
                                       unsigned int size,
                                       const amba_pv_control * ctrl,
                                       unsigned char * strb,
                                       sc_core::sc_time & t) {
    amba_pv_transaction trans;
    amba_pv_extension ex(size, ctrl);

    trans.set_write();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(size);
    trans.set_byte_enable_ptr(strb);
    if (strb != NULL) {
        trans.set_byte_enable_length(size);
    }
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        b_transport(socket_id, trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ex.get_resp());
}

/**
 * @brief       Completes a write transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer. It must point to an array of
 *              @a size bytes.
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
 *              64, 128]. The transaction size must be less than or equal to
 *              the value returned by get_bus_width_bytes().
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused
 *              on the master side).
 * @param       strb write strobes pointer (set to @c NULL if none). It must
 *              point to an array of @a size elements.
 * @param       t timing annotation.
 *
 * @return      @c AMBA_PV_OKAY if the transaction is successful.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH>::write(const sc_dt::uint64 & addr,
                                       unsigned char * data,
                                       unsigned int size,
                                       const amba_pv_control * ctrl,
                                       unsigned char * strb,
                                       sc_core::sc_time & t) {
    return (write(0, addr, data, size, ctrl, strb, t));
}

/**
 * @brief       Completes a burst read transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH>::burst_read(int socket_id,
                                            const sc_dt::uint64 & addr,
                                            unsigned char * data,
                                            unsigned int length,
                                            unsigned int size,
                                            const amba_pv_control * ctrl,
                                            amba_pv_burst_t burst,
                                            sc_core::sc_time & t) {
    amba_pv_transaction trans;
    amba_pv_extension ex(length, size, ctrl, burst);

    trans.set_read();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(size * length);
    if (burst == AMBA_PV_FIXED) {
        trans.set_streaming_width(size);
    } else {
        trans.set_streaming_width(trans.get_data_length());
    };
    trans.set_extension(& ex);
    try {
        b_transport(socket_id, trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ex.get_resp());
}

/**
 * @brief       Completes a burst read transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer. It must point to an array of
 *              (@a size * @a length) bytes.
 * @param       length transaction burst length as in [1-16].
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
 *              64, 128]. The transaction size must be less than or equal to
 *              the value returned by get_bus_width_bytes().
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused
 *              on the master side).
 * @param       burst transaction burst type, one of @c AMBA_PV_INCR,
 *              @c AMBA_PV_FIXED, or @c AMBA_PV_WRAP.
 * @param       t timing annotation.
 *
 * @return      @c AMBA_PV_OKAY if the transaction is successful.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH>::burst_read(const sc_dt::uint64 & addr,
                                            unsigned char * data,
                                            unsigned int length,
                                            unsigned int size,
                                            const amba_pv_control * ctrl,
                                            amba_pv_burst_t burst,
                                            sc_core::sc_time & t) {
    return (burst_read(0, addr, data, length, size, ctrl, burst, t));
}

/**
 * @brief       Completes a burst write transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH>::burst_write(int socket_id,
                                             const sc_dt::uint64 & addr,
                                             unsigned char * data,
                                             unsigned int length,
                                             unsigned int size,
                                             const amba_pv_control * ctrl,
                                             amba_pv_burst_t burst,
                                             unsigned char * strb,
                                             unsigned int strb_length,
                                             sc_core::sc_time & t) {
    amba_pv_transaction trans;
    amba_pv_extension ex(length, size, ctrl, burst);
    
    trans.set_write();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(size * length);
    if (burst == AMBA_PV_FIXED) {
        trans.set_streaming_width(size);
    } else {
        trans.set_streaming_width(trans.get_data_length());
    };
    trans.set_byte_enable_ptr(strb);
    if (strb != NULL) {
        trans.set_byte_enable_length(strb_length);
    }
    trans.set_extension(& ex);
    try {
        b_transport(socket_id, trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ex.get_resp());
}

/**
 * @brief       Completes a burst write transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer. It must point to an array of
 *              (@a size * @a length) bytes.
 * @param       length transaction burst length as in [1-16].
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
 *              64, 128]. The transaction size must be less than or equal to
 *              the value returned by get_bus_width_bytes().
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused
 *              on the master side).
 * @param       burst transaction burst type, one of @c AMBA_PV_INCR,
 *              @c AMBA_PV_FIXED, or @c AMBA_PV_WRAP.
 * @param       strb write strobes pointer (set to @c NULL if none).
 * @param       strb_length Write strobes length. It must be a multiple of
 *              @a size.
 * @param       t timing annotation.
 *
 * @return      @c AMBA_PV_OKAY if the transaction is successful.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_master_socket<BUSWIDTH>::burst_write(const sc_dt::uint64 & addr,
                                             unsigned char * data,
                                             unsigned int length,
                                             unsigned int size,
                                             const amba_pv_control * ctrl,
                                             amba_pv_burst_t burst,
                                             unsigned char * strb,
                                             unsigned int strb_length,
                                             sc_core::sc_time & t) {
    return (burst_write(0,
                        addr,
                        data,
                        length,
                        size,
                        ctrl,
                        burst,
                        strb,
                        strb_length,
                        t));
}

/**
 * @brief       Requests DMI access to the specified address and returns a
 *              reference to a DMI descriptor. 
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_master_socket<BUSWIDTH>::get_direct_mem_ptr(int socket_id,
                                                    tlm::tlm_command command,
                                                    const sc_dt::uint64 & addr,
                                                    const amba_pv_control * ctrl,
                                                    tlm::tlm_dmi & dmi_data) {
    amba_pv_transaction trans;
    amba_pv_extension ex(this->get_bus_width_bytes(), ctrl);
    bool ret = false;
    
    if (command == tlm::TLM_READ_COMMAND) {
        trans.set_read();
    } else {
        trans.set_write();
    }
    trans.set_address(addr);
    trans.set_extension(& ex);
    try {
        ret = get_direct_mem_ptr(socket_id, trans, dmi_data);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ret);
}

/**
 * @brief       Requests DMI access to the specified address and returns a
 *              reference to a DMI descriptor. 
 *
 * @param       command @c tlm::TLM_READ_COMMAND for a DMI read access
 *              request. @c tlm::TLM_WRITE_COMMAND for a DMI write access
 *              request.
 * @param       addr address to which the DMI access is requested.
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused
 *              on the master side).
 * @param       dmi_data returned DMI descriptor.
 *
 * @return      @c true if a DMI region is granted, @c false otherwise.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_master_socket<BUSWIDTH>::get_direct_mem_ptr(tlm::tlm_command command,
                                                    const sc_dt::uint64 & addr,
                                                    const amba_pv_control * ctrl,
                                                    tlm::tlm_dmi & dmi_data) {
    return (get_direct_mem_ptr(0, command, addr, ctrl, dmi_data));
}


/**
 * @brief       Non-intrusive debug read transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_master_socket<BUSWIDTH>::debug_read(int socket_id,
                                            const sc_dt::uint64 & addr,
                                            unsigned char * data,
                                            unsigned int length,
                                            const amba_pv_control * ctrl) {
    amba_pv_transaction trans;
    amba_pv_extension ex(1, 1, ctrl, AMBA_PV_INCR);
    unsigned int ret = 0;

    trans.set_read();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(length);
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        ret = transport_dbg(socket_id, trans);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ret);
}

/**
 * @brief       Non-intrusive debug read transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer. It must point to an array of
 *              @a length bytes.
 * @param       length transaction length.
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused
 *              on the master side).
 *
 * @return      number of bytes read or, if error, 0.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_master_socket<BUSWIDTH>::debug_read(const sc_dt::uint64 & addr,
                                            unsigned char * data,
                                            unsigned int length,
                                            const amba_pv_control * ctrl) {
    return (debug_read(0, addr, data, length, ctrl));
}

/**
 * @brief       Non-intrusive debug write transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_master_socket<BUSWIDTH>::debug_write(int socket_id,
                                             const sc_dt::uint64 & addr,
                                             unsigned char * data,
                                             unsigned int length,
                                             const amba_pv_control * ctrl) {
    amba_pv_transaction trans;
    amba_pv_extension ex(1, 1, ctrl, AMBA_PV_INCR);
    unsigned int ret = 0;

    trans.set_write();
    trans.set_address(addr);
    trans.set_data_ptr(data);
    trans.set_data_length(length);
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        ret = transport_dbg(socket_id, trans);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    trans.clear_extension(& ex);
    return (ret);
}

/**
 * @brief       Non-intrusive debug write transaction.
 *
 * @param       addr transaction address.
 * @param       data transaction data pointer. It must point to an array of
 *              @a length bytes.
 * @param       length transaction length.
 * @param       ctrl AMBA&nbsp;3 control information (set to @c NULL if unused
 *              on the master side).
 *
 * @return      number of bytes written or, if error, 0.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_master_socket<BUSWIDTH>::debug_write(const sc_dt::uint64 & addr,
                                             unsigned char * data,
                                             unsigned int length,
                                             const amba_pv_control * ctrl) {
    return (debug_write(0, addr, data, length, ctrl));
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method forwards the b_transport() call to the slave
 * socket bound to this master socket.
 *
 * @param       socket_id socket identifier (ignored on the master side).
 * @param       trans transaction.
 * @param       t timing annotation.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_master_socket<BUSWIDTH>::b_transport(int socket_id,
                                             amba_pv_transaction & trans,
                                             sc_core::sc_time & t) {
    (* this)->b_transport(trans, t);
}

/**
 * @brief       Blocking transport.
 *
 * @param       trans transaction.
 * @param       t timing annotation.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_master_socket<BUSWIDTH>::b_transport(amba_pv_transaction & trans,
                                             sc_core::sc_time & t) {
    b_transport(0, trans, t);
}

/**
 * @brief       Debug access to a target.
 *
 * This version of the method forwards the transport_dbg() call to the slave
 * socket bound to this master socket.
 *
 * @param       socket_id socket identifier (ignored on the master side).
 * @param       trans transaction.
 *
 * @return      number of bytes read or written or, if error, 0.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_master_socket<BUSWIDTH>::transport_dbg(int socket_id,
                                               amba_pv_transaction & trans) {
    return ((* this)->transport_dbg(trans));
}

/**
 * @brief       Debug access to a target.
 *
 * @param       trans transaction.
 *
 * @return      number of bytes read or written or, if error, 0.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_master_socket<BUSWIDTH>::transport_dbg(amba_pv_transaction & trans) {
    return (transport_dbg(0, trans));
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * This version of the method forwards the get_direct_mem_ptr() call to the
 * slave socket bound to this master socket.
 *
 * @param       socket_id socket identifier (ignored on the master side).
 * @param       trans transaction.
 * @param       dmi_data DMI Descriptor.
 *
 * @return      @c true if DMI access is granted, @c false otherwise.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_master_socket<BUSWIDTH>::get_direct_mem_ptr(int socket_id,
                                                    amba_pv_transaction & trans,
                                                    tlm::tlm_dmi & dmi_data) {
    return ((* this)->get_direct_mem_ptr(trans, dmi_data));
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * @param       trans transaction.
 * @param       dmi_data DMI Descriptor.
 *
 * @return      @c true if DMI access is granted, @c false otherwise.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_master_socket<BUSWIDTH>::get_direct_mem_ptr(amba_pv_transaction & trans,
                                                    tlm::tlm_dmi & dmi_data) {
    return (get_direct_mem_ptr(0, trans, dmi_data));
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_bw_transport_if interface to bind to this
 *              socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_master_socket<BUSWIDTH>::bind(amba_pv_bw_transport_if & iface) {
    register_invalidate_direct_mem_ptr(& iface,
        & amba_pv_bw_transport_if::invalidate_direct_mem_ptr,
        this->get_socket_id());
    register_nb_transport_bw(& iface,
                             & amba_pv_bw_transport_if::nb_transport_bw,
                             this->get_socket_id());
}

/**
 * @brief       Binds the specified interface to this socket.
 *
 * @param       iface amba_pv_bw_transport_if interface to bind to this
 *              socket.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_master_socket<BUSWIDTH>::operator() (amba_pv_bw_transport_if & iface) {
    bind(iface);
}

}   /* namespave amba_pv */

#endif  /* defined(AMBA_PV_MASTER_SOCKET__H) */
