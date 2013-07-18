/*
 * main.cpp - DualDhrystone platform model wrapper.
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include <scx_evs_Dhrystone.h>

/* Functions */

/*
 * User's entry point.
 */
int sc_main(int argc , char * argv[]) {

    /*
     * Initialize simulation 
     */
    scx::scx_initialize("DualDhrystone");

    /*
     * Components
     */
    amba_pv::amba_pv_memory<64> memory1("Memory1", 0x34000100);
    amba_pv::amba_pv_memory<64> memory2("Memory2", 0x34000100);
    scx_evs_Dhrystone dhrystone1("Dhrystone1");
    scx_evs_Dhrystone dhrystone2("Dhrystone2");

    /*
     * Simulation configuration
     */
   
    /* From command-line options */
    scx::scx_parse_and_configure(argc, argv);

    /* Semi-hosting configuration */
    scx::scx_set_parameter("*.Core.cpu0.semihosting-enable", true);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-ARM_SVC", 0x123456);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-Thumb_SVC", 0xAB);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-heap_base", 0x32000000);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-heap_limit", 0x1000000);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-stack_base", 0x33000000);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-stack_limit", 0x1000000);

    /* Simulation quantum, i.e. seconds to run per quantum */
    tlm::tlm_global_quantum::instance().set(sc_core::sc_time(100.0
                                                             / 100000000,
                                                             sc_core::SC_SEC));

    /*
     * Bindings
     */
    dhrystone1.amba_pv_m(memory1.amba_pv_s);
    dhrystone2.amba_pv_m(memory2.amba_pv_s);

    /*
     * Start of simulation
     */
    sc_core::sc_start();
    return EXIT_SUCCESS;
}
