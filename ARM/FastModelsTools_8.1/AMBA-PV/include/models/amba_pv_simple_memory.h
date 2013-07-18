/*
 * AMBA-PV: amba_pv_simple_memory.h - AMBA-PV simple memory model.
 *
 * Copyright 2007-2010 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_SIMPLE_MEMORY__H
#define AMBA_PV_SIMPLE_MEMORY__H

/**
 * @file        amba_pv_simple_memory.h
 *
 * @brief       AMBA-PV simple memory model.
 */

/* Includes */
#include "sockets/amba_pv_slave_socket.h"
#include "models/amba_pv_memory_base.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV simple memory model.
 *
 * The amba_pv_simple_memory class models an AMBA compatible memory at the PV
 * level.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_simple_memory:
    public amba_pv_memory_base<BUSWIDTH>,
    public sc_core::sc_module {

    /* Sockets */
    public:

        /**
         * @brief Slave socket.
         */
        amba_pv_slave_socket<BUSWIDTH> amba_pv_s;

    /* Constructor/Destructor */
        amba_pv_simple_memory(const sc_core::sc_module_name &,
                              const sc_dt::uint64 &);
        amba_pv_simple_memory(const sc_core::sc_module_name &,
                              const sc_dt::uint64 &,
                              unsigned char);
        amba_pv_simple_memory(const sc_core::sc_module_name &,
                              const sc_dt::uint64 &,
                              unsigned char,
                              unsigned char);
        ~amba_pv_simple_memory();

    /* sc_object overridables */
        virtual const char * kind() const;

    /* User-layer interface */
    protected:
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
        unsigned char * m_array;    /* Memory array */
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name memory name.
 * @param       size memory size in bytes. @a size is rounded up to the next
 *              multiple of 4096.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_simple_memory<BUSWIDTH>::amba_pv_simple_memory(const sc_core::sc_module_name & name,
                                                       const sc_dt::uint64 & size):
    amba_pv_memory_base<BUSWIDTH>(static_cast<const char *>(name), size),
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s") {

    /* Initializations... */
    m_array = new unsigned char[static_cast<unsigned int>(this->get_addr_limit())];

    /* Bindings... */
    amba_pv_s(* this);
}

/**
 * @brief       Constructor.
 *
 * @param       name memory name.
 * @param       size memory size in bytes. @a size is rounded up to the next
 *              multiple of 4096.
 * @param       fill_char fill character used for uninitialized the memory.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_simple_memory<BUSWIDTH>::amba_pv_simple_memory(const sc_core::sc_module_name & name,
                                                       const sc_dt::uint64 & size,
                                                       unsigned char fill_char):
    amba_pv_memory_base<BUSWIDTH>(static_cast<const char *>(name), size),
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s") {

    /* Initializations... */
    m_array = new unsigned char[static_cast<unsigned int>(this->get_addr_limit())];
    std::memset(m_array,
                fill_char,
                static_cast<unsigned int>(this->get_addr_limit()));

    /* Bindings... */
    amba_pv_s(* this);
}

/**
 * @brief       Constructor.
 *
 * @param       name memory name.
 * @param       size memory size in bytes. @a size is rounded up to the next
 *              multiple of 4096.
 * @param       fill_char1 fill character used for uninitialized memory.
 * @param       fill_char2 fill character used for uninitialized memory.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_simple_memory<BUSWIDTH>::amba_pv_simple_memory(const sc_core::sc_module_name & name,
                                                       const sc_dt::uint64 & size,
                                                       unsigned char fill_char1,
                                                       unsigned char fill_char2):
    amba_pv_memory_base<BUSWIDTH>(static_cast<const char *>(name), size),
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s") {

    /* Initializations... */
    m_array = new unsigned char[static_cast<unsigned int>(this->get_addr_limit())];
    for (unsigned int i =0;
         (i < static_cast<unsigned int>(this->get_addr_limit()));
         i += 2) {
        m_array[i] = fill_char1;
        m_array[i + 1] = fill_char2;
    }

    /* Bindings... */
    amba_pv_s(* this);
}

/**
 * @brief       Destructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_simple_memory<BUSWIDTH>::~amba_pv_simple_memory() {

    /* Delete memory array */
    delete [] m_array;
}

/**
 * @brief       Returns the kind string of this memory.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_simple_memory<BUSWIDTH>::kind() const  {
    return ("amba_pv_simple_memory");
}

/**
 * @brief       Completes a read transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_simple_memory<BUSWIDTH>::read(int socket_id,
                                      const sc_dt::uint64 & addr,
                                      unsigned char * data,
                                      unsigned int size,
                                      const amba_pv_control * ctrl,
                                      sc_core::sc_time & t) {
    sc_dt::uint64 aa = addr & ~sc_dt::uint64(size - 1); /* Aligned address */

    if ((aa + size) > this->get_addr_limit()) {
        return (AMBA_PV_DECERR);
    }
    std::memcpy(data, m_array + aa, size);
    return (AMBA_PV_OKAY);
}

/**
 * @brief       Completes a write transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_simple_memory<BUSWIDTH>::write(int socket_id,
                                       const sc_dt::uint64 & addr,
                                       unsigned char * data,
                                       unsigned int size,
                                       const amba_pv_control * ctrl,
                                       unsigned char * strb,
                                       sc_core::sc_time & t) {
    sc_dt::uint64 aa = addr & ~sc_dt::uint64(size - 1); /* Aligned address */

    if ((aa + size) > this->get_addr_limit()) {
        return (AMBA_PV_DECERR);
    }
    if (strb != NULL) {
        for (unsigned int i = 0; (i < size); i += 1) {
            if (strb[i] == TLM_BYTE_ENABLED) {
                m_array[aa + i] = data[i];
            }
        }
    } else {
        std::memcpy(m_array + aa, data, size);
    }
    return (AMBA_PV_OKAY);
}

/**
 * @brief       Requests DMI access to the specified address and returns a
 *              reference to a DMI descriptor.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_simple_memory<BUSWIDTH>::get_direct_mem_ptr(int socket_id,
                                                    tlm::tlm_command command,
                                                    const sc_dt::uint64 & addr,
                                                    const amba_pv_control * ctrl,
                                                    tlm::tlm_dmi & dmi_data) {
    dmi_data.set_start_address(0);
    dmi_data.set_end_address(this->get_addr_limit() - 1);
    dmi_data.allow_read_write();
    if (addr >= this->get_addr_limit()) {
        return false;
    }
    dmi_data.set_dmi_ptr(m_array);
    return true;
}

/**
 * @brief       Non-intrusive debug read transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_simple_memory<BUSWIDTH>::debug_read(int socket_id,
                                            const sc_dt::uint64 & addr,
                                            unsigned char * data,
                                            unsigned int length,
                                            const amba_pv_control * ctrl) {
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;
    unsigned int n;

    for (n = 0; (n < length); n += 1) {
        if (read(0, addr + n, data + n, 1, ctrl, t) != AMBA_PV_OKAY)
            break;
    }
    return (n);
}

/**
 * @brief       Non-intrusive debug write transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_simple_memory<BUSWIDTH>::debug_write(int socket_id,
                                             const sc_dt::uint64 & addr,
                                             unsigned char * data,
                                             unsigned int length,
                                             const amba_pv_control * ctrl) {
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;
    unsigned int n;

    for (n = 0; (n < length); n += 1) {
        if (write(0, addr + n, data + n, 1, ctrl, NULL, t) != AMBA_PV_OKAY)
            break;
    }
    return (n);
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_SIMPLE_MEMORY__H) */
