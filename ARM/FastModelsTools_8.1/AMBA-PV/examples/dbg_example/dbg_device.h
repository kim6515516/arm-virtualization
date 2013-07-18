/*
 * AMBA-PV: dbg_device.h - Debug device.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#if ! defined(DBG_DEVICE__H)
#define DBG_DEVICE__H

/* Includes */
#include "sockets/amba_pv_slave_socket.h"
#include <map>
#include <fstream>
#include <iomanip>

using namespace amba_pv;

static const unsigned int c_data[4] = {
    0xaaaaaaaa,
    0xbbbbbbbb,
    0xcccccccc,
    0xdddddddd
};

/* Datatypes */

/*
 * The dbg_device class aims at modeling an AMBA-PV compatible slave.
 */
template<unsigned int BUSWIDTH = 64>
class dbg_device:
    public sc_core::sc_module,
    public amba_pv_slave_base<BUSWIDTH> {

    /* Sockets */
    public:

        /*
         * Slave socket.
         */
        amba_pv_slave_socket<BUSWIDTH> amba_pv_s;

    /* Constructor/Destructor */
        dbg_device(sc_core::sc_module_name);
        ~dbg_device();

    /* sc_object overridables */
        virtual const char * kind() const;

    /* User-layer interface */
        virtual amba_pv_resp_t read(int,
                                    const sc_dt::uint64 &,
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
        virtual bool get_direct_mem_ptr(int,
                                        tlm::tlm_command,
                                        const sc_dt::uint64 &,
                                        const amba_pv_control *,
                                        tlm::tlm_dmi &);

     /* Debug interface */
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

    /* Implementation */
    private:

        /* Member variables */
        unsigned int some_data[4];
};

/* Functions */

template<unsigned int BUSWIDTH>
inline
dbg_device<BUSWIDTH>::dbg_device(sc_core::sc_module_name name):
    sc_core::sc_module(name),
    amba_pv_slave_base<BUSWIDTH>((const char *) name),
    amba_pv_s("amba_pv_s") {

    /* Bindings... */
    amba_pv_s(* this);
    memcpy(reinterpret_cast<unsigned char *>(some_data),
           reinterpret_cast<const unsigned char *>(c_data),
           sizeof(some_data));
}

/*
 * Destructor.
 */
template<unsigned int BUSWIDTH>
inline
dbg_device<BUSWIDTH>::~dbg_device() {
}

/*
 * Returns the kind string of this memory.
 */
template<unsigned int BUSWIDTH>
inline const char *
dbg_device<BUSWIDTH>::kind() const  {
    return ("dbg_device");
}

/*
 * Completes a read transaction
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
dbg_device<BUSWIDTH>::read(int socket_id,
                               const sc_dt::uint64 & addr,
                               unsigned char * data,
                               unsigned int size,
                               const amba_pv_control * ctrl,
                               sc_core::sc_time & t) {
    std::cout << this->name() << ": call to read()" << std::endl;
    return (AMBA_PV_OKAY);
}

/*
 * Completes a write transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
dbg_device<BUSWIDTH>::write(int socket_id,
                                const sc_dt::uint64 & addr,
                                unsigned char * data,
                                unsigned int size,
                                const amba_pv_control * ctrl,
                                unsigned char * strb,
                                sc_core::sc_time & t) {
    std::cout << this->name() << ": call to write()" << std::endl;
    return (AMBA_PV_OKAY);
}

/*
 * Non-intrusive debug read transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
dbg_device<BUSWIDTH>::debug_read(int socket_id,
                                     const sc_dt::uint64& addr,
                                     unsigned char * data,
                                     unsigned int length,
                                     const amba_pv_control * ctrl) {
    std::cout << this->name() << ": call to debug_read(), addr=0x"
              << std::hex << addr << std::endl;
    if (length > sizeof(some_data)) {
        length = sizeof(some_data);
    }
    memcpy(data, reinterpret_cast<unsigned char *>(some_data), length);
    std::cout << std::dec << std::endl;
    return length;
}

/*
 * Non-intrusive debug write transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
dbg_device<BUSWIDTH>::debug_write(int socket_id,
                                      const sc_dt::uint64 & addr,
                                      unsigned char * data,
                                      unsigned int length,
                                      const amba_pv_control * ctrl) {
    std::cout << this->name() << ": call to debug_write(), addr=0x"
              << std::hex << addr << std::endl;
    if (length > sizeof(some_data)) {
        length = sizeof(some_data);
    }
    memcpy(reinterpret_cast<unsigned char *>(some_data), data, length);
    std::cout << std::dec << std::endl;
    return length;
}

/*
 * Requests DMI access to the specified address and returns a reference to a
 * DMI descriptor.
 */
template<unsigned int BUSWIDTH>
inline bool
dbg_device<BUSWIDTH>::get_direct_mem_ptr(int socket_id,
                                         tlm::tlm_command command,
                                         const sc_dt::uint64 & addr,
                                         const amba_pv_control * ctrl,
                                         tlm::tlm_dmi & dmi_data) {
    return false;
}

#endif  /* ! defined(DBG_DEVICE__H) */
