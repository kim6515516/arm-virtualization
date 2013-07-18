/*
 * AMBA-PV: main.cpp - DMA example user's entry point.
 *
 * Copyright 2007-2010 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#if defined(WIN32)
    #include <time.h>
#else
    #include <sys/times.h> 
    #include <unistd.h>
#endif  /* defined(WIN32) */
#include <amba_pv.h>
#include "types.h"
#include "dma_testbench.h"
#include "dma.h"

/* Globals */

/* Number of clock ticks per second */
#if  defined(WIN32)
static const clock_t HZ = CLOCKS_PER_SEC;
#else
static const clock_t HZ = (clock_t) sysconf(_SC_CLK_TCK);
#endif  /* defined(WIN32) */

/* Functions */

/*
 * User's entry point.
 */
int sc_main(int argc , char *argv[]) {
    int number_of_runs = 1;
    bool enable_dmi = false;
    bool verbose = false;

    /* Parse arguments */
    for (int i = 1; (i < argc); i += 1) {
        if ((! strcmp(argv[i], "--dmi")) || (! strcmp(argv[i], "-d"))) {
            enable_dmi = true;
        } else if ((! strcmp(argv[i], "--verbose"))
                   || (! strcmp(argv[i], "-v"))) {
            verbose = true;
        } else if ((! strcmp(argv[i], "--help"))
                   || (! strcmp(argv[i], "-h"))) {
            std::cout << argv[0]
                      << ": Usage: [OPTION]... [NUMBER_OF_RUNS]\n"
                      << "Simulates a DMA transfer NUMBER_OF_RUNS times."
                      << "\nOptions:\n"
                      << "  -d, --dmi     Enable DMI\n"
                      << "  -h, --help    Show this help message and exit\n"
                      << "  -v, --verbose Be verbose about DMA transfers\n\n";
            return EXIT_SUCCESS;
        } else if (isdigit(argv[i][0])) {
            number_of_runs = atoi(argv[i]);
        } else {
            std::cerr << argv[0] << ": unrecognized option '"
                      << argv[i] << "'\nTry '" << argv[0]
                      << " --help' for more information.\n";
            return EXIT_FAILURE;
        }
    }

    /* Instantiate components */
    dma_testbench tb("tb", number_of_runs, 0x0, 0x4000, 0x4000);
    amba_pv::amba_pv_memory<BUSWIDTH> mem1("mem1", 0x2000);
    amba_pv::amba_pv_memory<BUSWIDTH> mem2("mem2", 0x2000);
    dma dma("dma", enable_dmi, (number_of_runs <= 1) || verbose);
    amba_pv::amba_pv_decoder<BUSWIDTH, 2, 3> router("router");

    /* Parameters of the components */
    mem1.set_fill_pattern(0xDF, 0xDF);

    /* Bindings */
    tb.amba_pv_m(router.amba_pv_s[0]);
    dma.amba_pv_m(router.amba_pv_s[1]);
    dma.dma_irq_out(tb.dma_irq_in);
    router.bind(0, mem1.amba_pv_s, 0x0, 0x1FFF);
    router.bind(1, mem2.amba_pv_s, 0x2000, 0x3FFF);
    router.bind(2, dma.amba_pv_s, 0x4000, 0x400F);

#if ! defined(WIN32)
    struct tms tms_buf;
#endif  /* ! defined(WIN32) */
    clock_t begin_time, end_time;

    std::cout << "\nSimulation started\n";
#if defined(WIN32)
    begin_time = clock();
#else
    times(& tms_buf);
    begin_time = tms_buf.tms_utime + tms_buf.tms_cutime;
#endif  /* defined(WIN32) */
    sc_core::sc_start();
#if defined(WIN32)
    end_time = clock();
#else
    times(& tms_buf);
    end_time = tms_buf.tms_utime + tms_buf.tms_cutime;
#endif  /* defined(WIN32) */
    std::cout << "Simulation ended\n";

    float user_time = float(end_time - begin_time) / HZ;
    float num_trans = number_of_runs * static_cast<float>(11.0);
    float num_bytes = static_cast<float>(number_of_runs)
                      * ((7 * 4) + (64 * 4 * 2));
        /* Would need a counter mechanism... */
    char buf[1024];

    if (number_of_runs > 1) {
        std::cout << "\n--- Simulation statistics: " << std::string(45, '-')
                  << std::endl;
        sprintf(buf, "Total transactions executed : %.0f\n", num_trans);
        std::cout << buf;
        sprintf(buf, "Total KBytes transferred    : %.0f\n", num_bytes / 1024.0);
        std::cout << buf;
        sprintf(buf,
                "Total simulation time       : %.6f sec.\n",
                float(sc_core::sc_time_stamp().to_seconds()));
        std::cout << buf;
        sprintf(buf, "Real simulation time        : %.6f sec.\n", user_time);
        std::cout << buf;
        sprintf(buf,
                "Transactions per sec.       : %.3f\n",
                num_trans / user_time);
        std::cout << buf;
        sprintf(buf,
                "KBytes transferred per sec. : %.3f\n",
                num_bytes / user_time / 1024.0);
        std::cout << buf;
        std::cout << std::string(72, '-') << std::endl;
    }
    return EXIT_SUCCESS;
}
