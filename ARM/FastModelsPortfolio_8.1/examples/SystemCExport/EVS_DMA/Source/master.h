/*
 * master.h - DMA master definition.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef _MASTER_H_
#define _MASTER_H_

/* Includes */
#include <amba_pv.h>
#include "types.h"

/* Datatypes */

class master:
    public sc_core::sc_module,
    public amba_pv::signal_slave_base<signal_t> {

    /* Port */
    public:
        amba_pv::signal_slave_export<signal_t> pv_dma_irq_in;

    /* Constructor */
        SC_HAS_PROCESS(master);
        explicit master(sc_core::sc_module_name);

    /* Signal API */
        virtual void set_state(int, const bool &);
    
    /* Implementation  */
    private:

        /* Member variables */
        sc_core::sc_event m_end_transfer;    /* DMA end transfer event */

        /* Helpers */
        void run();                         /* Master process */
};

#endif /* _MASTER_H_ */
