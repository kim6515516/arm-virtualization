/*
 * AMBA-PV: main.cpp - Bridge example user's entry point.
 *
 * Copyright 2007-2010 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include <amba_pv.h>

#include "master1.h"
#include "master2.h"

/* Functions */

/*
 * User's entry point.
 */
int sc_main(int argc , char *argv[]) {
    int number_of_runs = 1;

    /* Parse arguments */
    if (argc > 1) {
        number_of_runs = atoi(argv[1]);
    }

    /* Instantiate masters and slave */
    master1 m1("master1", number_of_runs);
    master2 m2("master2", number_of_runs);
    amba_pv::amba_pv_decoder<32, 2, 1> b("bus");
    amba_pv::amba_pv_exclusive_monitor<32> x("monitor");
    amba_pv::amba_pv_simple_memory<32> s("memory", 0x10000, 0x0);

    /* Instantiate bridges */
    amba_pv::amba_pv_to_tlm_bridge<32> amba2tlm("amba2tlm");
    amba_pv::amba_pv_from_tlm_bridge<32> tlm2amba("tlm2amba");

    /* Bindings */
    m1.m.bind(amba2tlm.amba_pv_s);
    amba2tlm.tlm_m.bind(tlm2amba.tlm_s);
    tlm2amba.amba_pv_m.bind(b.amba_pv_s[0]);
    m2.m.bind(b.amba_pv_s[1]);
    b.bind(0, x.amba_pv_s, 0x0, 0x10000);
    x.amba_pv_m.bind(s.amba_pv_s);

    /* Start simulation */
    std::cout << std::endl << "Simulation started, "
              << number_of_runs << " runs\n";
    sc_core::sc_start();
    std::cout << "Simulation ended\n";
    return 0;
}
