/*
 * AMBA-PV: master1.cpp - Bridge example first master implementation.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include "master1.h"

/* Functions */

/*
 * First master constructor.
 */
master1::master1(sc_core::sc_module_name name, int number_of_runs):
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
 * First master thread.
 * Attempts to perform an exclusive access at 0x0, followed by a second attempt
 * at 0x04.
 */
void master1::run() {
    sc_dt::uint64 addr = 0x0;
    unsigned int data[2];
    amba_pv::amba_pv_control ctrl;
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;

    ctrl.set_id(1);
    ctrl.set_exclusive(true);
    for (int i = 0; (i < m_number_of_runs); i += 1, addr += 4) {
        if ((i % 2) == 0) {

            /* Attempts to perform an exclusive access */
            m.read(addr,
                   reinterpret_cast<unsigned char *>(data),
                   sizeof(data[0]),
                   & ctrl,
                   t);
            std::cout << name() << ".read(0x" << std::hex << addr
                      << ", exclusive): 0x" << data[0] << std::endl;
            sc_core::wait(t);
            t = sc_core::SC_ZERO_TIME;
            std::cout << name() << ".write(0x" << std::hex << addr << ", 0x"
                      << data[0] << ", exclusive)\n";
            if (m.write(addr,
                        reinterpret_cast<unsigned char *>(data),
                        sizeof(data[0]),
                        & ctrl,
                        NULL,
                        t) != amba_pv::AMBA_PV_EXOKAY) {
                std::cerr << name() << ": exclusive access failed!\n";
            }
        } else {

            /* Attempts to perform an exclusive access */
            m.read(addr,
                   reinterpret_cast<unsigned char *>(data + 1),
                   sizeof(data[1]),
                   & ctrl,
                   t);
            std::cout << name() << ".read(0x" << std::hex << addr
                      << ", exclusive): 0x" << data[1] << std::endl;
            sc_core::wait(t);
            t = sc_core::SC_ZERO_TIME;
            std::cout << name() << ".write(0x" << std::hex << addr << ", 0x"
                      << data[1] << ", exclusive)\n";
            if (m.write(addr,
                        reinterpret_cast<unsigned char *>(data + 1),
                        sizeof(data[1]),
                        & ctrl,
                        NULL,
                        t) != amba_pv::AMBA_PV_EXOKAY) {
                std::cerr << name() << ": exclusive access failed!\n";
            }
        }
    }
}

