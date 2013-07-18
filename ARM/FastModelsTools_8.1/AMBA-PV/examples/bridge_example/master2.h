/*
 * AMBA-PV: master2.h - Bridge example second master definition.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef MASTER2__H
#define MASTER2__H

/* Includes */
#include "amba_pv.h"

/* Datatypes */

/*
 * Second master.
 */
class master2: public sc_core::sc_module, public amba_pv::amba_pv_master_base {
    SC_HAS_PROCESS(master2);

    /* Construction */
    public:
        explicit master2(sc_core::sc_module_name, int /* number_of_runs */ = 1);

    /* Ports */
        amba_pv::amba_pv_master_socket<32> m;

    /* Implementation */
    private:

        /* Member variables */
        int m_number_of_runs;

        /* Helpers */
        void run();
};

#endif  /* defined(MASTER2__H) */
