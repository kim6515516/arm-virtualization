/*
 * pv_timer.cpp - PV timer module implementation.
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include "pv_timer.h"

#include <scx/scx.h>

/* Constants */

/*
 * Timer register relative addresses
 */
const addr_t pv_timer::TIMER0_LOAD               = pv_counter::COUNTER_LOAD;
const addr_t pv_timer::TIMER0_VALUE              = pv_counter::COUNTER_VALUE;
const addr_t pv_timer::TIMER0_CONTROL            = pv_counter::COUNTER_CONTROL;
const addr_t pv_timer::TIMER0_INTR_CLEAR         = pv_counter::COUNTER_INTR_CLEAR;
const addr_t pv_timer::TIMER0_RAW_INTR_STATUS    = pv_counter::COUNTER_RAW_INTR_STATUS;
const addr_t pv_timer::TIMER0_MASKED_INTR_STATUS = pv_counter::COUNTER_MASKED_INTR_STATUS;
const addr_t pv_timer::TIMER0_BACKGROUND_LOAD    = pv_counter::COUNTER_BACKGROUND_LOAD;
const addr_t pv_timer::TIMER1_LOAD               = pv_counter::COUNTER_LOAD + 0x20;
const addr_t pv_timer::TIMER1_VALUE              = pv_counter::COUNTER_VALUE + 0x20;
const addr_t pv_timer::TIMER1_CONTROL            = pv_counter::COUNTER_CONTROL + 0x20;
const addr_t pv_timer::TIMER1_INTR_CLEAR         = pv_counter::COUNTER_INTR_CLEAR + 0x20;
const addr_t pv_timer::TIMER1_RAW_INTR_STATUS    = pv_counter::COUNTER_RAW_INTR_STATUS + 0x20;
const addr_t pv_timer::TIMER1_MASKED_INTR_STATUS = pv_counter::COUNTER_MASKED_INTR_STATUS + 0x20;
const addr_t pv_timer::TIMER1_BACKGROUND_LOAD    = pv_counter::COUNTER_BACKGROUND_LOAD + 0x20;
const addr_t pv_timer::TIMER2_LOAD               = pv_counter::COUNTER_LOAD + 0x1000;
const addr_t pv_timer::TIMER2_VALUE              = pv_counter::COUNTER_VALUE + 0x1000;
const addr_t pv_timer::TIMER2_CONTROL            = pv_counter::COUNTER_CONTROL + 0x1000;
const addr_t pv_timer::TIMER2_INTR_CLEAR         = pv_counter::COUNTER_INTR_CLEAR + 0x1000;
const addr_t pv_timer::TIMER2_RAW_INTR_STATUS    = pv_counter::COUNTER_RAW_INTR_STATUS + 0x1000;
const addr_t pv_timer::TIMER2_MASKED_INTR_STATUS = pv_counter::COUNTER_MASKED_INTR_STATUS + 0x1000;
const addr_t pv_timer::TIMER2_BACKGROUND_LOAD    = pv_counter::COUNTER_BACKGROUND_LOAD + 0x1000;
const addr_t pv_timer::TIMER3_LOAD               = pv_counter::COUNTER_LOAD + 0x1020;
const addr_t pv_timer::TIMER3_VALUE              = pv_counter::COUNTER_VALUE + 0x1020;
const addr_t pv_timer::TIMER3_CONTROL            = pv_counter::COUNTER_CONTROL + 0x1020;
const addr_t pv_timer::TIMER3_INTR_CLEAR         = pv_counter::COUNTER_INTR_CLEAR + 0x1020;
const addr_t pv_timer::TIMER3_RAW_INTR_STATUS    = pv_counter::COUNTER_RAW_INTR_STATUS + 0x1020;
const addr_t pv_timer::TIMER3_MASKED_INTR_STATUS = pv_counter::COUNTER_MASKED_INTR_STATUS + 0x1020;
const addr_t pv_timer::TIMER3_BACKGROUND_LOAD    = pv_counter::COUNTER_BACKGROUND_LOAD + 0x1020;

/* Functions */

/*
 * Constructor
 */
pv_timer::pv_timer(sc_core::sc_module_name module_name,
                   const sc_core::sc_time & res):
    sc_core::sc_module(module_name),
    amba_pv::amba_pv_slave_base<BUSWIDTH>(name()),
    amba_pv::signal_slave_base<value64_t>((const char *)name()),
    amba_pv_s("amba_pv_s"),
    pv_timer_intr_out0("pv_timer_intr_out0"),
    pv_timer_intr_out1("pv_timer_intr_out1"),
    pv_timer_intr_out2("pv_timer_intr_out2"),
    pv_timer_intr_out3("pv_timer_intr_out3"),
    pv_timer_rate_hz_0("pv_timer_rate_hz_0", 0),
    pv_timer_rate_hz_1("pv_timer_rate_hz_1", 1),
    pv_timer_rate_hz_2("pv_timer_rate_hz_2", 2),
    pv_timer_rate_hz_3("pv_timer_rate_hz_3", 3),
    m_counter0("counter0", res),
    m_counter1("counter1", res),
    m_counter2("counter2", res),
    m_counter3("counter3", res) {
    amba_pv_s(* this);
    pv_timer_rate_hz_0(* this),
    pv_timer_rate_hz_1(* this),
    pv_timer_rate_hz_2(* this),
    pv_timer_rate_hz_3(* this),
    m_counter0.intr_out(pv_timer_intr_out0);
    m_counter1.intr_out(pv_timer_intr_out1);
    m_counter2.intr_out(pv_timer_intr_out2);
    m_counter3.intr_out(pv_timer_intr_out3);
}

/*
 * Constructor
 */
pv_timer::pv_timer(sc_core::sc_module_name module_name,
                   double res,
                   sc_core::sc_time_unit res_unit):
    sc_core::sc_module(module_name),
    amba_pv::amba_pv_slave_base<BUSWIDTH>(name()),
    amba_pv::signal_slave_base<value64_t>((const char *)name()),
    amba_pv_s("amba_pv_s"),
    pv_timer_intr_out0("pv_timer_intr_out0"),
    pv_timer_intr_out1("pv_timer_intr_out1"),
    pv_timer_intr_out2("pv_timer_intr_out2"),
    pv_timer_intr_out3("pv_timer_intr_out3"),
    pv_timer_rate_hz_0("pv_timer_rate_hz_0", 0),
    pv_timer_rate_hz_1("pv_timer_rate_hz_1", 1),
    pv_timer_rate_hz_2("pv_timer_rate_hz_2", 2),
    pv_timer_rate_hz_3("pv_timer_rate_hz_3", 3),
    m_counter0("counter0", sc_core::sc_time(res, res_unit)),
    m_counter1("counter1", sc_core::sc_time(res, res_unit)),
    m_counter2("counter2", sc_core::sc_time(res, res_unit)),
    m_counter3("counter3", sc_core::sc_time(res, res_unit)) {
    amba_pv_s(* this);
    pv_timer_rate_hz_0(* this),
    pv_timer_rate_hz_1(* this),
    pv_timer_rate_hz_2(* this),
    pv_timer_rate_hz_3(* this),
    m_counter0.intr_out(pv_timer_intr_out0);
    m_counter1.intr_out(pv_timer_intr_out1);
    m_counter2.intr_out(pv_timer_intr_out2);
    m_counter3.intr_out(pv_timer_intr_out3);
}

/*
 * Sets the resolution of this timer
 */
void pv_timer::set_resolution(int id, const sc_core::sc_time & res) {
    switch (id) {
        case 0:
            m_counter0.set_resolution(res);
            break;
        case 1:
            m_counter1.set_resolution(res);
            break;
        case 2:
            m_counter2.set_resolution(res);
            break;
        case 3:
            m_counter3.set_resolution(res);
            break;
        default:
            break;
    }
}

/*
 * Sets the resolution of this timer
 */
void pv_timer::set_resolution(int id,
                              double res,
                              sc_core::sc_time_unit res_unit) {
    switch (id) {
        case 0:
            m_counter0.set_resolution(res, res_unit);
            break;
        case 1:
            m_counter1.set_resolution(res, res_unit);
            break;
        case 2:
            m_counter2.set_resolution(res, res_unit);
            break;
        case 3:
            m_counter3.set_resolution(res, res_unit);
            break;
        default:
            break;
    }
}

void pv_timer::set_state(int id, const value64_t & value) {
    set_resolution(id, 1.0 / static_cast<double>(value), sc_core::SC_SEC);
}

/*
 * Returns the resolution of this timer
 */
sc_core::sc_time pv_timer::get_resolution() const {
    return (m_counter0.get_resolution());
}

/* amba_pv_if virtual method implementation */

/*
 * Reads a register
 */
amba_pv::amba_pv_resp_t pv_timer::read(int socket_id,
                                       const addr_t & addr,
                                       unsigned char * data,
                                       unsigned int size,
                                       const amba_pv::amba_pv_control * ctrl,
                                       sc_core::sc_time & t) {
    if (size != sizeof(unsigned int)) {
        SCX_REPORT_WARNING(name(), "read: invalid size: %u", size);
        return (amba_pv::AMBA_PV_SLVERR);
    };
    switch (addr) {
        case 0x0000:
        case 0x0004:
        case 0x0008:
        case 0x000C:
        case 0x0010:
        case 0x0014:
        case 0x0018:
            (* reinterpret_cast<unsigned int *>(data)) = m_counter0.register_read(addr & 0x1F, t);
            break;
        case 0x0020:
        case 0x0024:
        case 0x0028:
        case 0x002C:
        case 0x0030:
        case 0x0034:
        case 0x0038:
            (* reinterpret_cast<unsigned int *>(data)) = m_counter1.register_read(addr & 0x1F, t);
            break;
        case 0x1000:
        case 0x1004:
        case 0x1008:
        case 0x100C:
        case 0x1010:
        case 0x1014:
        case 0x1018:
            (* reinterpret_cast<unsigned int *>(data)) = m_counter2.register_read(addr & 0x1F, t);
            break;
        case 0x1020:
        case 0x1024:
        case 0x1028:
        case 0x102C:
        case 0x1030:
        case 0x1034:
        case 0x1038:
            (* reinterpret_cast<unsigned int *>(data)) = m_counter3.register_read(addr & 0x1F, t);
            break;

        /* ID registers */
        case 0x0Fe0:    /* Timer ID register 0 */
        case 0x1Fe0:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000004;
            break;
        case 0x0Fe4:    /* Timer ID register 1 */
        case 0x1Fe4:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000018;
            break;
        case 0x0FE8:    /* Timer ID register 2 */
        case 0x1FE8:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000014;    
            break;
        case 0x0FEC:    /* Timer ID register 3 */
        case 0x1FEC:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000000;    
            break;
        case 0x0FF0:    /* Primecell ID register 0 */
        case 0x1FF0:
            (* reinterpret_cast<unsigned int *>(data)) = 0x0000000D;
            break;
        case 0x0FF4:    /* Primecell ID register 1 */
        case 0x1FF4:
            (* reinterpret_cast<unsigned int *>(data)) = 0x000000F0;
            break;
        case 0x0FF8:    /* Primecell ID register 2 */
        case 0x1FF8:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000005;
            break;
        case 0x0FFC:    /* Primecell ID register 3 */
        case 0x1FFC:
            (* reinterpret_cast<unsigned int *>(data)) = 0x000000B1;
            break;
        default:
            SCX_REPORT_WARNING(name(),
                               "read: input address out of range: %p",
                               (void *) addr);
            return (amba_pv::AMBA_PV_SLVERR);
    }
    return (amba_pv::AMBA_PV_OKAY);
}

/*
 * Writes a register
 */
amba_pv::amba_pv_resp_t pv_timer::write(int socket_id,
                                        const addr_t & addr,
                                        unsigned char * data,
                                        unsigned int size,
                                        const amba_pv::amba_pv_control * ctrl,
                                        unsigned char * strb,
                                        sc_core::sc_time & t) {
    if (size != sizeof(unsigned int)) {
        SCX_REPORT_WARNING(name(), "write: invalid size: %u", size);
        return (amba_pv::AMBA_PV_SLVERR);
    };
    if (strb != NULL) {
        SC_REPORT_WARNING(name(), "write: strobes not supported");
        return (amba_pv::AMBA_PV_SLVERR);
    };
    switch (addr) {
        case 0x0000:
        case 0x0004:
        case 0x0008:
        case 0x000C:
        case 0x0010:
        case 0x0014:
        case 0x0018:
            m_counter0.register_write(addr & 0x1F, (* reinterpret_cast<unsigned int *>(data)), t);
            break;
        case 0x0020:
        case 0x0024:
        case 0x0028:
        case 0x002C:
        case 0x0030:
        case 0x0034:
        case 0x0038:
            m_counter1.register_write(addr & 0x1F, (* reinterpret_cast<unsigned int *>(data)), t);
            break;
        case 0x1000:
        case 0x1004:
        case 0x1008:
        case 0x100C:
        case 0x1010:
        case 0x1014:
        case 0x1018:
            m_counter2.register_write(addr & 0x1F, (* reinterpret_cast<unsigned int *>(data)), t);
            break;
        case 0x1020:
        case 0x1024:
        case 0x1028:
        case 0x102C:
        case 0x1030:
        case 0x1034:
        case 0x1038:
             m_counter3.register_write(addr & 0x1F, (* reinterpret_cast<unsigned int *>(data)), t);
            break;
        default:
            SCX_REPORT_WARNING(name(),
                               "write: input address out of range: %p",
                               (void *) addr);
            return (amba_pv::AMBA_PV_SLVERR);
    }
    return (amba_pv::AMBA_PV_OKAY);
}

/*
 * Debug read register access
 */
unsigned int pv_timer::debug_read(int socket_id,
                                  const addr_t & addr,
                                  unsigned char * data,
                                  unsigned int length,
                                  const amba_pv::amba_pv_control * ctrl) {
    if (length < sizeof(unsigned int)) {
        return 0;
    }
    switch (addr) {
        case 0x0000:
        case 0x0004:
        case 0x0008:
        case 0x000C:
        case 0x0010:
        case 0x0014:
        case 0x0018:
            (* reinterpret_cast<unsigned int *>(data)) =
                m_counter0.register_debug_read(addr & 0x1F);
            break;
        case 0x0020:
        case 0x0024:
        case 0x0028:
        case 0x002C:
        case 0x0030:
        case 0x0034:
        case 0x0038:
            (* reinterpret_cast<unsigned int *>(data)) =
                m_counter1.register_debug_read(addr & 0x1F);
            break;
        case 0x1000:
        case 0x1004:
        case 0x1008:
        case 0x100C:
        case 0x1010:
        case 0x1014:
        case 0x1018:
            (* reinterpret_cast<unsigned int *>(data)) =
                m_counter2.register_debug_read(addr & 0x1F);
            break;
        case 0x1020:
        case 0x1024:
        case 0x1028:
        case 0x102C:
        case 0x1030:
        case 0x1034:
        case 0x1038:
            (* reinterpret_cast<unsigned int *>(data)) =
                m_counter3.register_debug_read(addr & 0x1F);
            break;

        /* ID registers */
        case 0x0Fe0:    /* Timer ID register 0 */
        case 0x1Fe0:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000004;
            break;
        case 0x0Fe4:    /* Timer ID register 1 */
        case 0x1Fe4:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000018;
            break;
        case 0x0FE8:    /* Timer ID register 2 */
        case 0x1FE8:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000014;    
            break;
        case 0x0FEC:    /* Timer ID register 3 */
        case 0x1FEC:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000000;    
            break;
        case 0x0FF0:    /* Primecell ID register 0 */
        case 0x1FF0:
            (* reinterpret_cast<unsigned int *>(data)) = 0x0000000D;
            break;
        case 0x0FF4:    /* Primecell ID register 1 */
        case 0x1FF4:
            (* reinterpret_cast<unsigned int *>(data)) = 0x000000F0;
            break;
        case 0x0FF8:    /* Primecell ID register 2 */
        case 0x1FF8:
            (* reinterpret_cast<unsigned int *>(data)) = 0x00000005;
            break;
        case 0x0FFC:    /* Primecell ID register 3 */
        case 0x1FFC:
            (* reinterpret_cast<unsigned int *>(data)) = 0x000000B1;
            break;
        default:
            return 0;
    }
    return (sizeof(unsigned int));
}

/*
 * Debug write access
 */
unsigned int pv_timer::debug_write(int socket_id,
                                   const addr_t & addr,
                                   unsigned char * data,
                                   unsigned int length,
                                   const amba_pv::amba_pv_control * ctrl) {
    if (length < sizeof(unsigned int)) {
        return 0;
    };
    switch (addr) {
        case 0x0000:
        case 0x0004:
        case 0x0008:
        case 0x000C:
        case 0x0010:
        case 0x0014:
        case 0x0018:
            m_counter0.register_debug_write(addr & 0x1F,
                (* reinterpret_cast<unsigned int *>(data)));
            break;
        case 0x0020:
        case 0x0024:
        case 0x0028:
        case 0x002C:
        case 0x0030:
        case 0x0034:
        case 0x0038:
            m_counter1.register_debug_write(addr & 0x1F,
                (* reinterpret_cast<unsigned int *>(data)));
            break;
        case 0x1000:
        case 0x1004:
        case 0x1008:
        case 0x100C:
        case 0x1010:
        case 0x1014:
        case 0x1018:
            m_counter2.register_debug_write(addr & 0x1F,
                (* reinterpret_cast<unsigned int *>(data)));
            break;
        case 0x1020:
        case 0x1024:
        case 0x1028:
        case 0x102C:
        case 0x1030:
        case 0x1034:
        case 0x1038:
             m_counter3.register_debug_write(addr & 0x1F,
                (* reinterpret_cast<unsigned int *>(data)));
            break;
        default:
            return 0;
    }
    return (sizeof(unsigned int));
}
