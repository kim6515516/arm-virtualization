/*
 * AMBA-PV: master1.h - Exclusive example first master definition.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef MASTER1__H
#define MASTER1__H

/* Includes */
#include "amba_pv.h"

/* Datatypes */

/*
 * First master.
 */
class master1: public sc_core::sc_module, public amba_pv::amba_pv_master_base {
    SC_HAS_PROCESS(master1);

    /* Construction */
    public:
        explicit master1(sc_core::sc_module_name, int /* number_of_runs */ = 1);

    /* Ports */
        amba_pv::amba_pv_master_socket<32> m;

    /* Implementation */
    private:

        /* Member variables */
        int m_number_of_runs;

        /* Helpers */
        void run();
};

#endif  /* defined(MASTER1__H) */
