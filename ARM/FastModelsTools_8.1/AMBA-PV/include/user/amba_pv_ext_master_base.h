/*
 * AMBA-PV: amba_pv_ext_master_base.h - Base class for all AMBA-PV master modules that supports hierarchical binding.
 *
 * Copyright 2007-2009, 2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXT_MASTER_BASE__H
#define AMBA_PV_EXT_MASTER_BASE__H

/**
 * @file        amba_pv_ext_master_base.h
 *
 * @brief       Base class for all AMBA-PV master modules.
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
 * @brief       Base class for all AMBA-PV master modules.
 *
 * amba_pv_master_base is intended to be bound to one or more amba_pv_master_socket.
 *
 * @note        amba_pv_master_base is not an @c sc_module.
 */
class amba_pv_master_base:
    public virtual amba_pv_bw_transport_if {

    /* Constructor */
    public:
        explicit amba_pv_master_base(const std::string &);

    /* Accessors */
        std::string get_name() const;

    /* Backward interface */
    protected:
        virtual void invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);

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
amba_pv_master_base::amba_pv_master_base(const std::string & name):
    m_name(name) {
}

/**
 * @brief       Returns the name of this master.
 */
inline std::string
amba_pv_master_base::get_name() const  {
    return (m_name);
}

/**
 * @brief       Invalidates DMI pointers previously established for the specified DMI region.
 *
 * This default implementation does nothing.
 */
inline void
amba_pv_master_base::invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64) {
}

}   /* namespace ext */

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_EXT_MASTER_BASE__H) */
