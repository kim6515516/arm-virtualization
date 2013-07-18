/*
 * main.cpp - Dhrystone platform model wrapper using a custom scheduler
 *            implementation
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include <scx_evs_Dhrystone.h>
#include "my_simulation_controller.h"

/* Globals */

static const char help_log[] =
    "    --log FILE            "
    "log all SystemC reports into given FILE\n";

/* Functions */

/*
 * Specific command-line options parsing
 */
void parse_log(int & argc , char * argv[]) {
    int j = 1;

    for (int i = 1; (i < argc); i += 1) {
        if ((std::strcmp(argv[i], "--log") == 0)
            || (std::strncmp(argv[i], "--log=", 6) == 0)) {

            /* log file */
            const char * p = strchr(argv[i], '=');

            if (p == NULL) {
                if ((i + 1) >= argc) {
                    std::cerr << argv[0] << ": option '" << argv[i]
                              << "' requires an argument\n";
                    std::exit(EXIT_FAILURE);
                }
                i += 1;
                sc_core::sc_report_handler::set_log_file_name(argv[i]);
            } else {
                sc_core::sc_report_handler::set_log_file_name(p + 1);
            }
            sc_core::sc_report_handler::suppress(sc_core::SC_DISPLAY);
            continue;
        }
        argv[j] = argv[i];
        j += 1;
    }
    argc = j;
}

/*
 * User's entry point.
 */
int sc_main(int argc , char * argv[]) {

    /*
     * SystemC report log file
     */
    parse_log(argc, argv);

    /* Create custom implementation of the simulation controller containing a
     * custom scheduler mapping */
    my_simulation_controller my_sim_controller;
    
    /*
     * Initialize simulation 
     */
    scx::scx_initialize("CustomScheduler", & my_sim_controller);
        /* Here we specify our custom simulation controller which in turn
         * specifies our custom scheduler mapping.
         * The following line would use the default scheduler mapping:
         * scx::scx_initialize("CustomScheduler"); */

    /*
     * Components
     */
    amba_pv::amba_pv_memory<64> memory("Memory", 0x34000100);
    scx_evs_Dhrystone dhrystone("Dhrystone");

    /*
     * Simulation configuration
     */
   
    /* From command-line options */
    scx::scx_parse_and_configure(argc, argv, help_log);

    /* Semi-hosting configuration */
    scx::scx_set_parameter("*.Core.cpu0.semihosting-enable", true);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-ARM_SVC", 0x123456);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-Thumb_SVC", 0xAB);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-heap_base", 0x32000000);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-heap_limit", 0x1000000);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-stack_base", 0x33000000);
    scx::scx_set_parameter("*.Core.cpu0.semihosting-stack_limit", 0x1000000);

    /* Simulation quantum, i.e. seconds to run per quantum */
    tlm::tlm_global_quantum::instance().set(sc_core::sc_time(100000.0
                                                             / 100000000,
                                                             sc_core::SC_SEC));

    /*
     * Bindings
     */
    dhrystone.amba_pv_m(memory.amba_pv_s);

    /*
     * Start of simulation
     */
    sc_core::sc_start();
    return EXIT_SUCCESS;
}

