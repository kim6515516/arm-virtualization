/*
 * pv_counter.cpp - PV counter module implementation.
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include "pv_counter.h"

#include <scx/scx.h>

/* Constants */

/*
 * Register relative addresses
 */
const addr_t pv_counter::COUNTER_LOAD               = 0x000;
const addr_t pv_counter::COUNTER_VALUE              = 0x004;
const addr_t pv_counter::COUNTER_CONTROL            = 0x008;
const addr_t pv_counter::COUNTER_INTR_CLEAR         = 0x00C;
const addr_t pv_counter::COUNTER_RAW_INTR_STATUS    = 0x010;
const addr_t pv_counter::COUNTER_MASKED_INTR_STATUS = 0x014;
const addr_t pv_counter::COUNTER_BACKGROUND_LOAD    = 0x018;

/* Functions */

/*
 * Constructor
 */
pv_counter::pv_counter(sc_core::sc_module_name module_name,
                       const sc_core::sc_time & res):
    sc_core::sc_module(module_name),
    intr_out("intr_out"),
    m_res(res.to_seconds()),
    m_counter(0xFFFFFFFFULL),
    m_ie_p(true) {
    SC_METHOD(intr_event_handler);
    sensitive << m_intr_event;
}

/*
 * Constructor
 */
pv_counter::pv_counter(sc_core::sc_module_name module_name,
                       double res,
                       sc_core::sc_time_unit res_unit):
    sc_core::sc_module(module_name),
    intr_out("intr_out"),
    m_res(sc_core::sc_time(res, res_unit).to_seconds()),
    m_counter(0xFFFFFFFFULL),
    m_ie_p(true) {
    SC_METHOD(intr_event_handler);
    sensitive << m_intr_event;
}

/*
 * Sets the resolution of this counter
 */
void pv_counter::set_resolution(const sc_core::sc_time & res) {
    m_res = res.to_seconds();

    /* Re-init counter */
    init_counter(sc_core::SC_ZERO_TIME);
}

/*
 * Sets the resolution of this counter
 */
void pv_counter::set_resolution(double res, sc_core::sc_time_unit res_unit) {
    set_resolution(sc_core::sc_time(res, res_unit));
}

/*
 * Returns the resolution of this counter
 */
sc_core::sc_time pv_counter::get_resolution() const {
    return (sc_core::sc_time(m_res, sc_core::SC_SEC));
}

/*
 * Reads a register
 */
unsigned int pv_counter::register_read(addr_t addr, sc_core::sc_time & t) {
    switch (addr & 0xFF) {
        case COUNTER_LOAD:
            return (m_load);
        case COUNTER_VALUE:
            if (m_enabled_p) {

                /* Update counter value */
                double now = (sc_core::sc_time_stamp() + t).to_seconds();

                m_counter -= static_cast<sc_dt::uint64>((now - m_reload_time)
                                                        / m_res);
                m_reload_time = now;
            }
            return (static_cast<unsigned int>(m_counter >> m_shift));
        case COUNTER_CONTROL:
            return (get_control_register());
        case COUNTER_INTR_CLEAR:
            SC_REPORT_WARNING(name(),
                              "invalid read access on interrupt clear register");
            return 0x00;
        case COUNTER_RAW_INTR_STATUS:
            return (m_raw_intr_p? 1: 0);
        case COUNTER_MASKED_INTR_STATUS:
            return ((m_raw_intr_p && m_ie_p)? true: false);
        case COUNTER_BACKGROUND_LOAD:
            return (m_load);
        default:
            SCX_REPORT_WARNING(name(),
                               "read register: input address out of range: %p",
                               (void *) addr);
            return 0x00;
    }
}

/*
 * Writes a register
 */
void pv_counter::register_write(addr_t addr, unsigned int data, sc_core::sc_time & t) {
    switch (addr & 0xFF) {
        case COUNTER_LOAD:

            /* Re-init counter */
            m_load = data;
            init_counter(t);
            break;
        case COUNTER_VALUE:
            SC_REPORT_WARNING(name(), "invalid write access on value register");
            break;
        case COUNTER_CONTROL:

            /* Set control register and re-init counter */
            set_control_register(data);
            init_counter(t);
            break;
        case COUNTER_INTR_CLEAR:
            if (m_raw_intr_p) {

                /* Signal interupt... */
                m_raw_intr_p = false;
                intr_out.set_state(0, false);
            }
            break;
        case COUNTER_RAW_INTR_STATUS:
            SC_REPORT_WARNING(name(),
                              "invalid write access on raw interrupt status "
                              "register");
            break;
        case COUNTER_MASKED_INTR_STATUS:
            SC_REPORT_WARNING(name(),
                              "invalid write access on masked interrupt status "
                              "register");
            break;
        case COUNTER_BACKGROUND_LOAD:
            m_load = data;
            break;
        default:
            SCX_REPORT_WARNING(name(),
                               "write register: input address out of range: %p",
                               (void *) addr);
            break;
    }
}

/*
 * Reads a register from a debugger
 */
unsigned int pv_counter::register_debug_read(addr_t addr) {
    switch (addr & 0xFF) {
        case COUNTER_LOAD:
            return (m_load);
        case COUNTER_VALUE:
            return (static_cast<unsigned int>(m_counter >> m_shift));
        case COUNTER_CONTROL:
            return (get_control_register());
        case COUNTER_INTR_CLEAR:
            return 0x00;
        case COUNTER_RAW_INTR_STATUS:
            return (m_raw_intr_p? 1: 0);
        case COUNTER_MASKED_INTR_STATUS:
            return ((m_raw_intr_p && m_ie_p)? true: false);
        case COUNTER_BACKGROUND_LOAD:
            return (m_load);
        default:
            return 0x00;
    }
}

/*
 * Writes a register from a debugger
 */
void pv_counter::register_debug_write(addr_t addr, unsigned int data) {
    switch (addr & 0xFF) {
        case COUNTER_LOAD:
            m_load = data;
            break;
        case COUNTER_VALUE:
            break;
        case COUNTER_CONTROL:
            set_control_register(data);
            break;
        case COUNTER_INTR_CLEAR:
            m_raw_intr_p = false;
            break;
        case COUNTER_RAW_INTR_STATUS:
            break;
        case COUNTER_MASKED_INTR_STATUS:
            break;
        case COUNTER_BACKGROUND_LOAD:
            m_load = data;
            break;
        default:
            break;
    }
}

/*
 * Sets the control register
 */
void pv_counter::set_control_register(unsigned int new_ctrl) {
    m_enabled_p = (new_ctrl  >> 7) & 1;
    m_mode = ((new_ctrl >> 6) & 1)? MODE_PERIODIC_RELOAD: MODE_FREE_RUNNING;
    m_ie_p = (new_ctrl  >> 5) & 1;
    m_prescale = (new_ctrl  >> 2) & 3;
    m_counter_size = (new_ctrl  >> 1) & 1;
    m_oneshot_p = (new_ctrl  >> 0) & 1;
    switch (m_prescale) {
        case 0:
            m_shift = 0;  /* Divide by 1 */
            break;
        case 1:
            m_shift = 4;  /* Divide by 16 */
            break;
        case 2:
        default:
            m_shift = 8;  /* Divide by 256 */
            break;
    }
}

/*
 * Returns the control register
 */
unsigned int pv_counter::get_control_register() const {
    return ((m_enabled_p                        << 7)
            | ((m_mode == MODE_PERIODIC_RELOAD) << 6)
            | (m_ie_p                           << 5)
            | (0                                << 4)
            | (m_prescale                       << 2)
            | (m_counter_size                   << 1)
            | (m_oneshot_p                      << 0));
}

/*
 * Sets the interrupt
 */
void pv_counter::set_intr() {
    m_raw_intr_p = true;
    if (m_ie_p) {
        intr_out.set_state(0, true);
    }
}

/*
 * sc_module overridable
 */
void pv_counter::end_of_elaboration() {
    m_load = 0;
    m_counter = 0xFFFFFFFFULL;
    m_reload_time = 0.0;
    m_enabled_p = false;
    m_mode = MODE_FREE_RUNNING;
    m_ie_p = true;
    m_prescale = 0;
    m_counter_size = 0;
    m_oneshot_p = false;
    m_raw_intr_p = false;
    m_shift = 0;
    intr_out.set_state(0, false);
}

/*
 * Initialize this counter
 */
void pv_counter::init_counter(const sc_core::sc_time & t) {

    /* load the counter & notify... */
    if (m_load == 0) {
        m_load -= 1;
    }
    m_counter = static_cast<sc_dt::uint64>(m_load) << m_shift;
    m_reload_time = (sc_core::sc_time_stamp() + t).to_seconds();
    m_intr_event.cancel();
    if (m_enabled_p) {
        sc_core::sc_time intr_time(static_cast<double>(m_counter) * m_res, sc_core::SC_SEC);

        intr_time += t;
        m_intr_event.notify(intr_time);

        /* This is a synchronization point */
        sync(intr_time);
    }
}

/*
 * Counter fired event handler
 */
void pv_counter::intr_event_handler() {
    if (m_enabled_p) {

        /* Sets the interrupt */
        set_intr();
        if (m_oneshot_p) {

            /* One shot */
            m_intr_event.cancel();
            return;
        }

        /* Reload the counter */
        switch (m_mode) {
            case MODE_PERIODIC_RELOAD:
                m_counter = static_cast<sc_dt::uint64>(m_load) << m_shift;
                break;
            case MODE_FREE_RUNNING:
                m_counter = ((m_counter_size == 0)? 0xFFFFULL: 0xFFFFFFFFULL)
                            << m_shift;
                break;
            default:
                sc_assert(false);
                break;
        }

        sc_core::sc_time intr_time(static_cast<double>(m_counter) * m_res, sc_core::SC_SEC);

        m_intr_event.cancel();
        m_reload_time = sc_core::sc_time_stamp().to_seconds();
        m_intr_event.notify(intr_time);

        /* This is a synchronization point */
        sync(intr_time);
    }
}

/*
 * Triggers a synchronization.
 */
void pv_counter::sync(const sc_core::sc_time & t) {
    sc_assert(t > sc_core::SC_ZERO_TIME);
    scx::scx_sync(t.to_seconds());
}

