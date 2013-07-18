/*
 * AMBA-PV: main.cpp - Debug example's user's entry point.
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
#include "dbg_master.h"
#include "dbg_device.h"

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

    /* Instantiate components */
    dbg_master<BUSWIDTH> generic_master("dbg_master");
    dbg_device<BUSWIDTH> generic_slave("dbg_device");

#if defined(PROBE)
     amba_pv::amba_pv_simple_probe<BUSWIDTH> probe("dbg_probe", true);
#endif  /* defined(PROBE) */

    /* Bindings */
#if defined(PROBE)
    generic_master.amba_pv_m(probe.amba_pv_s);
    probe.amba_pv_m(generic_slave.amba_pv_s);
#else
    generic_master.amba_pv_m(generic_slave.amba_pv_s);
#endif  /* defined(PROBE) */

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
                      * ((7 * 4) + (16 * 4 * 2));
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
