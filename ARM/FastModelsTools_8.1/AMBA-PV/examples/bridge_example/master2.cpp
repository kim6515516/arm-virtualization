/*
 * AMBA-PV: master2.cpp - Bridge example second master implementation.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include "master2.h"

/* Functions */

/*
 * Second master constructor.
 */
master2::master2(sc_core::sc_module_name name, int number_of_runs):
    sc_core::sc_module(name),
    amba_pv::amba_pv_master_base((const char *) name),
    m("axi_m"),
    m_number_of_runs(number_of_runs) {
    m(* this);
    SC_THREAD(run);
    if (m_number_of_runs <= 0) {
        m_number_of_runs = 1;
    }
}

/*
 * Second master thread.
 * Attempts to perform a normal write at 0x0, followed by a second attempt
 * at 0x4.
 */
void master2::run() {
    sc_dt::uint64 addr = 0x0;
    unsigned int data[] = {
        0x12345678,
        0x34125678,
    };
    amba_pv::amba_pv_control ctrl;
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;

    ctrl.set_id(2);
    ctrl.set_exclusive(false);
    for (int i = 0; (i < m_number_of_runs); i += 1, addr += 4) {
        if ((i % 2) == 0) {

            /* Attempts to perform a normal write */
            sc_core::wait(t);
            t = sc_core::SC_ZERO_TIME;
            std::cout << name() << ".write(0x" << std::hex << addr << ", 0x"
                      << data[0] << ")\n";
            m.write(addr,
                    reinterpret_cast<unsigned char *>(data),
                    sizeof(data[0]),
                    & ctrl,
                    NULL,
                    t);
        } else {

            /* Attempts to perform a normal write */
            sc_core::wait(t);
            t = sc_core::SC_ZERO_TIME;
            std::cout << name() << ".write(0x" << std::hex << addr << ", 0x"
                      << data[1] << ")\n";
            m.write(addr,
                    reinterpret_cast<unsigned char *>(data + 1),
                    sizeof(data[1]),
                    & ctrl,
                    NULL,
                    t);
        }
    }
}

