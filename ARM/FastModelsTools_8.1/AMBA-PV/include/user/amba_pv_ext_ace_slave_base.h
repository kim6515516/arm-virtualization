/*
 * AMBA-PV: amba_pv_ext_ace_slave_base.h - Base class for all AMBA-PV ACE slave modules that supports hierarchical
 *                                         binding.
 *
 * Copyright 2012-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXT_ACE_SLAVE_BASE__H
#define AMBA_PV_EXT_ACE_SLAVE_BASE__H

/**
 * @file        amba_pv_ext_ace_slave_base.h
 *
 * @brief       Base class for all AMBA-PV ACE slave modules.
 */

/* Includes */
#include "core/amba_pv_ext_core_ifs.h"

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
 * @brief       Base class for all AMBA-PV ACE slave modules.
 *
 * amba_pv_ace_slave_base is intended to be bound to one or more * amba_pv_ace_slave_socket.
 *
 * @note        amba_pv_ace_slave_base is not an @c sc_module.
 *
 * @note        amba_pv_slave_base can also be used for AMBA-PV ACE slave modules.
 *              It is provided as an alternative, especially for AMBA-PV ACE interconnect components.
 */
class amba_pv_ace_slave_base: public virtual amba_pv_fw_transport_if {

    /* Constructor */
    public:
        explicit amba_pv_ace_slave_base(const std::string &);

    /* Accessors */
        std::string get_name() const;

    /* Forward interface */
    protected:
        virtual void b_transport(int, amba_pv_transaction &, sc_core::sc_time &);
        virtual unsigned int transport_dbg(int, amba_pv_transaction &);
        virtual bool get_direct_mem_ptr(int, amba_pv_transaction &, tlm::tlm_dmi &);

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
inline
amba_pv_ace_slave_base::amba_pv_ace_slave_base(const std::string & name):
    m_name(name) {
}

/**
 * @brief       Returns the name of this slave.
 */
inline std::string
amba_pv_ace_slave_base::get_name() const  {
    return (m_name);
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method does nothing.
 */
inline void
amba_pv_ace_slave_base::b_transport(int, amba_pv_transaction &, sc_core::sc_time &) {
}

/**
 * @brief       Debug access to a target.
 *
 * This version of the method returns @c 0.
 */
inline unsigned int
amba_pv_ace_slave_base::transport_dbg(int, amba_pv_transaction &) {
    return 0;
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * This version of the method returns @c false and denies DMI access to the entire memory region.
 */
inline bool
amba_pv_ace_slave_base::get_direct_mem_ptr(int, amba_pv_transaction &, tlm::tlm_dmi & dmi_data) {
    dmi_data.allow_read_write();
    dmi_data.set_start_address(0x0);
    dmi_data.set_end_address(sc_dt::uint64(-1));
    return false;
}

}   /* namespace ext */

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_EXT_ACE_SLAVE_BASE__H) */
