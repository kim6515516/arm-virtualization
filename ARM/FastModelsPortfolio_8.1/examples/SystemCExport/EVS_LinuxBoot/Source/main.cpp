/*
 * main.cpp - LinuxBoot example with support for setting the quantum.
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include <scx_evs_LinuxBoot.h>
#include <sg/MSCFixes.h>

#include "types.h"
#include "pv_timer.h"

#include <cstring>
#include <cstdlib>

/* Globals */

static const char help_extra_options[] =
    "-Q, --quantum N            "
    "Number of ticks to simulate per quantum (default to 100)\n"
    "-f, --fast                 "
    "Fast mode (currently defines FASTSIM_SLEEP_ON_RESET and "
    "FASTSIM_SLEEP_ON_WFIWFE)\n"
    "    --log FILE             "
    "Log all SystemC reports into given FILE\n";

/* Functions */

/*
 * Specific command-line options parsing
 */
double parse_extra_options(int & argc , char * argv[]) {
    double q = 100.0;
    int j = 1;

    for (int i = 1; (i < argc); i += 1) {
        if ((std::strcmp(argv[i], "-Q") == 0)
            || (std::strncmp(argv[i], "-Q=", 3) == 0)
            || (std::strcmp(argv[i], "--quantum") == 0)
            || (std::strncmp(argv[i], "--quantum=", 10) == 0)) {

            /* number of instructions to run per quantum */
            const char * p = strchr(argv[i], '=');

            if (p == NULL) {
                if ((i + 1) >= argc) {
                    std::cerr << argv[0] << ": option '" << argv[i]
                              << "' requires an argument\n";
                    std::exit(EXIT_FAILURE);
                }
                i += 1;
                q = std::atol(argv[i]);
            } else {
                q = std::atol(p + 1);
            }
            continue;
        }
        if ((std::strcmp(argv[i], "-f") == 0)
            || (std::strcmp(argv[i], "--fast") == 0)) {

            /* fast mode */
            setenv("FASTSIM_SLEEP_ON_RESET", "1", 1);
            setenv("FASTSIM_SLEEP_ON_WFIWFE", "1", 1);
            continue;
        }
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
    return (q);
}

/*
 * User's entry point.
 */
int sc_main(int argc , char * argv[]) {

    /*
     * Number of instructions to run per quantum and SystemC report log file
     */
    double quantum = parse_extra_options(argc, argv);

    /*
     * Initialize simulation 
     */
    scx::scx_initialize("LinuxBoot");

    /*
     * Exported platform
     */
    scx_evs_LinuxBoot platform("LinuxBoot");

    /*
     * Instantiate components
     */
    pv_timer timer("timer", (1.0 / 100000000.0), sc_core::SC_SEC);
    amba_pv::amba_pv_decoder<BUSWIDTH, 1, 4> decoder("decoder");
    amba_pv::amba_pv_decoder<BUSWIDTH, 3, 1> funnel("funnel");
    amba_pv::amba_pv_exclusive_monitor<BUSWIDTH> monitor("monitor");
    amba_pv::amba_pv_memory<BUSWIDTH> dram("dram", 0x100000000ull);

    /*
     * Simulation configuration
     */

    /* From command-line options... */
    scx::scx_parse_and_configure(argc, argv, help_extra_options);

    /* Disable rate-limiter
     *
     * NOTE:    get_/set_parameter() functions are also available on the EVS
     *          instance, as well as load_application(). */
    platform.set_parameter("motherboard.vis.rate_limit-enable", false);

    /* Simulation quantum, i.e. seconds to run per quantum */
    tlm::tlm_global_quantum::instance().set(sc_core::sc_time(quantum
                                                             / 100000000.0,
                                                             sc_core::SC_SEC));

    /* DMI enabled for exclusive monitor */
    monitor.set_dmi_enabled();

    /*
     * Bindings
     */
    platform.timer_bus_m(timer.amba_pv_s);
    timer.pv_timer_intr_out0(platform.intr_0);
    timer.pv_timer_intr_out1(platform.intr_1);
    timer.pv_timer_intr_out2(platform.intr_2);
    timer.pv_timer_intr_out3(platform.intr_3);
    platform.rate_hz_0(timer.pv_timer_rate_hz_0);
    platform.rate_hz_1(timer.pv_timer_rate_hz_1);
    platform.rate_hz_2(timer.pv_timer_rate_hz_2);
    platform.rate_hz_3(timer.pv_timer_rate_hz_3);
    platform.cluster_m(decoder.amba_pv_s[0]);
    decoder.bind(0, funnel.amba_pv_s[0], 0x0080000000ull, 0x00FFFFFFFFull);
    decoder.bind(1, funnel.amba_pv_s[1], 0x0800000000ull, 0x08FFFFFFFFull);
    decoder.bind(2, funnel.amba_pv_s[2], 0x8000000000ull, 0x80FFFFFFFFull);
    decoder.bind(3, platform.cpu_s, 0x0000000000ull, 0xFFFFFFFFFFFull, true);
    funnel.bind(0, monitor.amba_pv_s, 0x00000000ull, 0xFFFFFFFFull);
    monitor.amba_pv_m(dram.amba_pv_s);

    /*
     * Start of simulation
     */
    sc_core::sc_start();
    return EXIT_SUCCESS;
}
