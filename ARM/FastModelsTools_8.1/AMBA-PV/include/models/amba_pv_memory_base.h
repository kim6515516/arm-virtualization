/*
 * AMBA-PV: amba_pv_memory_base.h - AMBA-PV memory model base class.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_MEMORY_BASE__H
#define AMBA_PV_MEMORY_BASE__H

/**
 * @file        amba_pv_memory_base.h
 *
 * @brief       AMBA-PV memory model base class.
 */

/* Includes */
#include "user/amba_pv_slave_base.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV memory model base class.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_memory_base: public amba_pv_slave_base<BUSWIDTH> {

    /* Constructor/Destructor */
    public:
        amba_pv_memory_base(const std::string &,
                            const sc_dt::uint64 &);

    /* Accessors */
        sc_dt::uint64 get_addr_limit() const;

    /* Transport interface */
    protected:
        virtual void b_transport(int,
                                 amba_pv_transaction &,
                                 sc_core::sc_time &);

    /* Implementation */
    private:

        /* Member variables */
        sc_dt::uint64 m_addr_limit;      /* Memory address limit (first not-
                                          * -allowed address) */
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
amba_pv_memory_base<BUSWIDTH>::amba_pv_memory_base(const std::string & name,
                                                   const sc_dt::uint64 & size):
    amba_pv_slave_base<BUSWIDTH>(name),
    m_addr_limit((size + 4095) & ~sc_dt::uint64(4095)) {
}

/**
 * @brief       Returns the address limit (this is, the first not allowed
 *              address) of this memory.
 */
template<unsigned int BUSWIDTH>
inline sc_dt::uint64
amba_pv_memory_base<BUSWIDTH>::get_addr_limit() const {
    return (m_addr_limit);
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method sets the DMI allowed attribute to @c true for
 * non-exclusive accesses and forward the b_transport() call to the base class.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_memory_base<BUSWIDTH>::b_transport(int socket_id,
                                           amba_pv_transaction & trans,
                                           sc_core::sc_time & t) {
    amba_pv_extension * ex = NULL;

    trans.get_extension(ex);
    if ((ex != NULL) && (! ex->is_exclusive())) {
        trans.set_dmi_allowed(true);
    }
    amba_pv_slave_base<BUSWIDTH>::b_transport(socket_id, trans, t);
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_MEMORY_BASE__H) */
