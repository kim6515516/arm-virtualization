/*
 * AMBA-PV: amba_pv_ace_master_base.h - Base class for all AMBA-PV ACE master modules.
 *
 * Copyright 2011 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_ACE_MASTER_BASE__H
#define AMBA_PV_ACE_MASTER_BASE__H

/**
 * @file        amba_pv_ace_master_base.h
 *
 * @brief       Base class for all AMBA-PV ACE master modules.
 */

/* Includes */
#include "core/amba_pv_core_ifs.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       Base class for all AMBA-PV ACE master modules.
 *
 * amba_pv_ace_master_base is intended to be bound to one or more
 * amba_pv_ace_master_socket.
 *
 * @note        amba_pv_ace_master_base is not an @c sc_module.
 */
class amba_pv_ace_master_base:
    public virtual amba_pv_bw_transport_and_snoop_if {

    /* Constructor */
    public:
        explicit amba_pv_ace_master_base(const std::string &);

    /* Accessors */
        std::string get_name() const;

    /* Backward interface */
    protected:
        virtual void
        invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);
        virtual void
        b_snoop(int, amba_pv_transaction &, sc_core::sc_time &);
        virtual unsigned int
        snoop_dbg(int, amba_pv_transaction &);

    /* Implementation */
    private:
        std::string m_name;   /**< Master name. */
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name master name.
 */
inline
amba_pv_ace_master_base::amba_pv_ace_master_base(const std::string & name):
    m_name(name) {
}

/**
 * @brief       Returns the name of this master.
 */
inline std::string
amba_pv_ace_master_base::get_name() const  {
    return (m_name);
}

/**
 * @brief       Invalidates DMI pointers previously established for the
 *              specified DMI region.
 *
 * This default implementation does nothing.
 */
inline void
amba_pv_ace_master_base::invalidate_direct_mem_ptr(int,
                                               sc_dt::uint64,
                                               sc_dt::uint64) {
}

/**
 * @brief       Blocking snoop transport.
 *
 * This default implementation does nothing.
 */
inline void
amba_pv_ace_master_base::b_snoop(int,
                                 amba_pv_transaction &,
                                 sc_core::sc_time &) {
}

/**
 * @brief       Snoop debug transport.
 *
 * This default implementation does nothing.
 */
inline unsigned int
amba_pv_ace_master_base::snoop_dbg(int,
                                   amba_pv_transaction &) {
   return 0;
}


}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_ACE_MASTER_BASE__H) */
