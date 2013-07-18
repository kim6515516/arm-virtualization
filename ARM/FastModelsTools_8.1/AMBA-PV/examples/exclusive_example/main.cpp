/*
 * AMBA-PV: main.cpp - Exclusive example user's entry point.
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

    /* Instantiate components */
    master1 m1("master1", number_of_runs);
    master1 m2("master2", number_of_runs);
    master2 m3("master3", number_of_runs);
    amba_pv::amba_pv_decoder<32, 3, 1> b("bus");
#if defined(PROBE)
    amba_pv::amba_pv_simple_probe<32> p("probe");
#endif  /* defined(PROBE) */
    amba_pv::amba_pv_exclusive_monitor<32> x("monitor");
    amba_pv::amba_pv_simple_memory<32> s("memory", 0x10000, 0x0);

    /* Bindings */
    m1.m.bind(b.amba_pv_s[0]);
    m2.m.bind(b.amba_pv_s[1]);
    m3.m.bind(b.amba_pv_s[2]);
#if defined(PROBE)
    b.bind(0, p.amba_pv_s, 0, 0xFFFF);
    p.amba_pv_m.bind(x.amba_pv_s);
#else
    b.bind(0, x.amba_pv_s, 0, 0xFFFF);
#endif  /* defined(PROBE) */
    x.amba_pv_m.bind(s.amba_pv_s);

    std::cout << "\nSimulation started, " << number_of_runs << " runs\n";
    sc_core::sc_start();
    std::cout << "Simulation ended\n";
    return 0;
}
