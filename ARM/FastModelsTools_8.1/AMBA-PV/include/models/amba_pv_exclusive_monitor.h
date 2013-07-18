/*
 * AMBA-PV: amba_pv_exclusive_monitor.h - AMBA-PV exclusive monitor model.
 *
 * Copyright 2007-2009, 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXCLUSIVE_MONITOR__H
#define AMBA_PV_EXCLUSIVE_MONITOR__H

/**
 * @file        amba_pv_exclusive_monitor.h
 *
 * @brief       AMBA-PV exclusive monitor model.
 */

/* Includes */
#include "sockets/amba_pv_master_socket.h"
#include "sockets/amba_pv_slave_socket.h"
#include <map>

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV exclusive monitor model.
 *
 * The amba_pv_exclusive_monitor model provides exclusive access support, and
 * can be added before any AMBA-PV slave.
 *
 * Exclusive accesses are <em>single aligned transfers</em>, for which
 * amba_pv_control::is_exclusive() returns @c true.
 *
 * The amba_pv_exclusive_monitor model can be configured to:
 * - either disable DMI (default behavior) and thus reject all DMI requests
 * - or enable DMI for non exclusive regions and thus reject DMI requests
 *   that intersects with exclusive regions and invalidate DMI pointers for the
 *   same.
 *
 * @note        When DMI is enabled, the onus is on the master to not use DMI
 *              for exclusive accesses. If the master uses DMI for exclusive
 *              accesses, wrong behavior might be observed.
 *
 * @note        When configured to disable DMI, the amba_pv_exclusive_monitor
 *              model might have an effect on performance.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_exclusive_monitor:
    public virtual amba_pv_fw_transport_if,
    public virtual amba_pv_bw_transport_if,
    public sc_core::sc_module {

    /* Sockets */
    public:

        /**
         * @brief Slave socket.
         */
        amba_pv_slave_socket<BUSWIDTH> amba_pv_s;

        /**
         * @brief Master socket.
         */
        amba_pv_master_socket<BUSWIDTH> amba_pv_m;

    /* Constructor */
        explicit amba_pv_exclusive_monitor(const sc_core::sc_module_name &);
        amba_pv_exclusive_monitor(const sc_core::sc_module_name &,
                                  unsigned int,
                                  bool = false);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Accessors */
        unsigned int get_erg() const;
        void set_erg(unsigned int);
        bool is_dmi_enabled() const;
        void set_dmi_enabled(bool = true);

    /* Forward interface */
    protected:
        virtual void b_transport(int,
                                 amba_pv_transaction &,
                                 sc_core::sc_time &);
        virtual unsigned int transport_dbg(int, amba_pv_transaction &);
        virtual bool get_direct_mem_ptr(int,
                                        amba_pv_transaction &,
                                        tlm::tlm_dmi &);

    /* Backward Interface */
        virtual void
        invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);

    /* Implementation */
    private:

        /* Typedefs*/
        typedef std::map<unsigned int, sc_dt::uint64> monitor_t;
        typedef std::map<sc_dt::uint64, std::deque<unsigned int> > monitored_t;

        /* Member variables */
        monitor_t m_monitor;    /* Exclusive monitor */
            /* m_monitor[n]: tagged address for master(n):
             * - (m_monitor.find(n) == m_monitor.end()): monitor in open state
             * - (m_monitor.find(n) != m_monitor.end()): monitor in exclusive
             *   state
             * where n is given by amba_pv_extension::get_id() */
        monitored_t m_monitored;/* Monitored address->masters map */
            /* m_monitored[t]: masters for tagged address t:
             * - (m_monitored.find(t) == m_monitored.end()): t not monitored
             * - (m_monitored.find(t) != m_monitored.end()): t monitored
             * where t is given by tagged_address(a), where a is given by
             * amba_pv_transaction::get_adddress() */
        unsigned int m_erg;     /* Exclusives Reservation Granule (ERG) */
        bool m_dmi_enabled;     /* DMI enabled */

        /* Helper functions */
        sc_dt::uint64 tagged_address(const sc_dt::uint64 &) const;
        sc_dt::uint64 address_from_tag(const sc_dt::uint64 &) const;
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name monitor name.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_exclusive_monitor<BUSWIDTH>::amba_pv_exclusive_monitor(const sc_core::sc_module_name & name):
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s"),
    amba_pv_m("amba_pv_m"),
    m_erg(sc_dt::sc_max(3u,
                        static_cast<unsigned int>(log((BUSWIDTH + 7) / 8.0)
                                                  / log(2.0)))),
    m_dmi_enabled(false) {

    /* Bindings... */
    amba_pv_s(* this);
    amba_pv_m(* this);
}

/**
 * @brief       Parameterized constructor.
 *
 * The <em>Exclusives Reservation Granule</em> (ERG) is set to:
 * max(@a erg , log2((@e BUSWIDTH + 7) / 8)).
 *
 * @param       name monitor name.
 * @param       erg the ERG of this monitor in [3..11].
 * @param       dmi_enabled @c true to enable DMI for non exclusive regions
 *              Defaults to @c false.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_exclusive_monitor<BUSWIDTH>::amba_pv_exclusive_monitor(const sc_core::sc_module_name & name,
                                                               unsigned int erg,
                                                               bool dmi_enabled /* = false */):
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s"),
    amba_pv_m("amba_pv_m"),
    m_erg(sc_dt::sc_max(erg,
                        static_cast<unsigned int>(log((BUSWIDTH + 7) / 8.0)
                                                  / log(2.0)))),
    m_dmi_enabled(dmi_enabled) {
    sc_assert((erg >= 3) && (erg <= 11));

    /* Bindings... */
    amba_pv_s(* this);
    amba_pv_m(* this);
}

/**
 * @brief       Returns the kind string of this monitor.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_exclusive_monitor<BUSWIDTH>::kind() const {
    return ("amba_pv_exclusive_monitor");
}

/**
 * @brief       Returns the ERG of this monitor.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_exclusive_monitor<BUSWIDTH>::get_erg() const {
    return (m_erg);
}

/**
 * @brief       Sets the ERG of this monitor.
 *
 * The new ERG is set to: max(@a erg, log2((@e BUSWIDTH + 7) / 8)).
 *
 * @param       erg the new ERG as in [3..11].
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_exclusive_monitor<BUSWIDTH>::set_erg(unsigned int erg) {
    sc_assert((erg >=3) && (erg <= 11));
    m_erg = sc_dt::sc_max(erg,
                          static_cast<unsigned int>(log((BUSWIDTH + 7) / 8.0)
                                                    / log(2.0)));
}

/**
 * @brief       Returns whether or not DMI is enabled for non exclusive regions
 *              for this monitor.
 *
 * @return      @c true when DMI is enabled, @c false otherwise.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_exclusive_monitor<BUSWIDTH>::is_dmi_enabled() const {
    return (m_dmi_enabled);
}

/**
 * @brief       Sets whether or not DMI is enabled for non exclusive regions
 *              for this monitor.
 *
 * When DMI is enabled, the monitor rejects DMI requests that intersect with
 * exclusive regions and invalidates DMI pointers for the same.
 *
 * When DMI is disabled, DMI is not allowed.
 *
 * @note        When DMI is disabled during simulation, DMI pointers previously
 *              acquired are not invalidated.
 *
 * @note        When DMI is enabled, the onus is on the master to not use DMI
 *              for exclusive accesses. If the master uses DMI for exclusive
 *              accesses, wrong behavior might be observed.
 *
 * @param       dmi_enabled @c true to enable DMI, @c false otherwise.
 *
 * @see         @c tlm::tlm_generic_payload::set_dmi_allowed() in the <em>TLM
 *              2.0 Language Reference Manual</em> for more information on DMI
 *              allowed.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_exclusive_monitor<BUSWIDTH>::set_dmi_enabled(bool dmi_enabled) {
    m_dmi_enabled = dmi_enabled;
}

/**
 * @brief       Blocking transport.
 *
 * This version of the method completes the specified transaction while
 * processing exclusive access.
 * amba_pv_extension::get_rsp() indicates the successful completion of the
 * exclusive access, or an error occured. The response @c AMBA_PV_EXOKAY is
 * returned to indicate a successful completion of the exclusive access, while
 * @c AMBA_PV_OKAY is returned in case of failure.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_exclusive_monitor<BUSWIDTH>::b_transport(int socket_id,
                                                 amba_pv_transaction & trans,
                                                 sc_core::sc_time & t) {
    monitor_t::iterator i;
    typename std::deque<unsigned int>::iterator j;
    amba_pv_extension * ex = NULL;
    sc_dt::uint64 tag;
    bool dmi_allowed = true;

    /* Retrieve AMBA-PV extension */
    trans.get_extension(ex);
    if (ex == NULL) {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return;
    }

    /* Compute tagged address */
    tag = tagged_address(trans.get_address());
    if (trans.is_read()) {

        /* Read transaction */
        if (ex->is_exclusive()) {

            /* Monitor the exclusive read access, whether in open or exclusive
             * state */
            m_monitor[ex->get_id()] = tag;

            /* Record tag->ID association */
            m_monitored[tag].push_back(ex->get_id());

            /* Invalidate corresponding DMI region */
            if (is_dmi_enabled()) {
                amba_pv_s.invalidate_direct_mem_ptr(address_from_tag(tag),
                                                    address_from_tag(tag + 1)
                                                    - 1);
            }

            /* DMI not allowed for exclusive reads */
            dmi_allowed = false;
        } else {
            
            /* DMI not allowed if address monitored */
            if (m_monitored.find(tag) != m_monitored.end()) {
                dmi_allowed = false;
            }
        }

        /* (Exclusive) Read proceeds */
        amba_pv_m->b_transport(trans, t);
    } else if (trans.is_write()) {

        /* Write transaction */
        if (ex->is_exclusive()) {

            /* Check if exclusive access already monitored */
            if ((i = m_monitor.find(ex->get_id())) != m_monitor.end()) {

                /* Monitor in exclusive state */
                if ((* i).second != tag) {

                    /* Reset to another location => exclusive write fails,
                     * monitor remains in exclusive state */
                    ex->set_okay();
                    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
                    return;
                } else {
                    
                    /* Access no longer monitored as location is updated,
                     * monitor back to open state */
                    m_monitor.erase(i);
                }
            } else {

                /* Access not monitored => exclusive write fails, monitor
                 * remains in open state */
                ex->set_okay();
                trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
                return;
            }
        }

        /* Update monitors */
        for (j = m_monitored[tag].begin();
             (j != m_monitored[tag].end());
             j ++) {

            /* Access no longer monitored as location is updated, monitor
             * back to open state */
            m_monitor.erase(* j);
        }
        m_monitored.erase(tag);

        /* DMI not allowed if address monitored */
        if (m_monitored.find(tag) != m_monitored.end()) {
            dmi_allowed = false;
        }

        /* (Exclusive) Write proceeds */
        amba_pv_m->b_transport(trans, t);
    } else {

        /* Unknown transaction command */
        trans.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
        ex->set_slverr();
        return;
    }

    /* DMI not allowed if DMI disabled */
    if (! is_dmi_enabled()) {
        dmi_allowed = false;
    }

    /* Update response and DMI allowed */
    if (ex->is_exclusive()) {
        if (ex->is_okay()) {
            ex->set_exokay();
        }
    }
    trans.set_dmi_allowed(dmi_allowed);
}

/**
 * @brief       Debug access to a target.
 *
 * This version of the method forwards this debug access to the slave.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_exclusive_monitor<BUSWIDTH>::transport_dbg(int socket_id,
                                                   amba_pv_transaction & trans) {
    return (amba_pv_m->transport_dbg(trans));
}

/**
 * @brief       Requests a DMI access based on the specified transaction.
 *
 * This version of the method returns @c false when DMI is disabled, @c false
 * for exclusive accesses, or when the DMI region intersects with an exclusive
 * region and the DMI region cannot be resized outside of the exclusive region.
 * It returns @c true when DMI access is granted.
 *
 * @note        Read-only DMI is allowed though as a potential performance
 *              optimization.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_exclusive_monitor<BUSWIDTH>::get_direct_mem_ptr(int socket_id,
                                                        amba_pv_transaction & trans,
                                                        tlm::tlm_dmi & dmi) {
    monitored_t::iterator i;
    amba_pv_extension * ex = NULL;

    /* DMI not allowed if DMI disabled */
    if (! is_dmi_enabled()) {
        return false;
    }

    /* Retrieve AMBA-PV extension */
    trans.get_extension(ex);
    if (ex == NULL) {
        return false;
    }

    /* DMI not allowed for exclusive accesses */
    if (ex->is_exclusive()) {
        return false;
    }

    /* Forward DMI access request */
    if (! amba_pv_m->get_direct_mem_ptr(trans, dmi)) {
        return false;
    }

    /* DMI not allowed when DMI region intersects with an exclusive region and
     * DMI region cannot be resized outside of exclusive region.
     *
     * NOTE:    Read-only DMI allowed though as a potential performance
     *          optimization. */
    if (dmi.is_write_allowed()) {
        sc_dt::uint64 dmi_start = dmi.get_start_address();
        sc_dt::uint64 dmi_end = dmi.get_end_address();

        for (i = m_monitored.begin(); (i != m_monitored.end()); i ++) {
            sc_dt::uint64 excl_start = address_from_tag((* i).first);
            sc_dt::uint64 excl_end = address_from_tag((* i).first + 1) - 1;

            if (((excl_start >= dmi_start) && (excl_start <= dmi_end))
                || ((excl_end >= dmi_start) && (excl_end <= dmi_end))) {

                /* Resize DMI region... */
                if ((trans.get_address() < excl_start)
                    && (dmi_end >= excl_start) && (dmi_start < excl_start)) {

                    /* ...from end... */
                    dmi.set_end_address(excl_start - 1);
                } else if ((trans.get_address() > excl_end)
                    && (dmi_start <= excl_end) && (dmi_end > excl_end)) {

                    /* ... from start */
                    dmi.set_start_address(excl_end + 1);
                } else {

                    /* Cannot be resized */
                    return false;
                }
            }
        }
        sc_assert(dmi.get_start_address() <= dmi.get_end_address());
    }
    return true;
}

/**
 * @brief       Invalidates DMI pointers previously established for the given
 *              DMI region.
 *
 * This version of the method simply forwards the call backward to the master.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_exclusive_monitor<BUSWIDTH>::invalidate_direct_mem_ptr(int socket_id,
                                                               sc_dt::uint64 start_range,
                                                               sc_dt::uint64 end_range) {
    amba_pv_s->invalidate_direct_mem_ptr(start_range, end_range);
}

/*
 * Returns the tagged address of the given memory address.
 */
template<unsigned int BUSWIDTH>
inline sc_dt::uint64
amba_pv_exclusive_monitor<BUSWIDTH>::tagged_address(const sc_dt::uint64 & a) const {
    return (a >> m_erg);
}

/*
 * Returns the memory address from the given tag.
 */
template<unsigned int BUSWIDTH>
inline sc_dt::uint64
amba_pv_exclusive_monitor<BUSWIDTH>::address_from_tag(const sc_dt::uint64 & tag) const {
    return (tag << m_erg);
}

}   /* namepsace amba_pv */

#endif  /* defined(AMBA_PV_EXCLUSIVE_MONITOR__H) */
