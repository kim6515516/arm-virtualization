/*
 * AMBA-PV: dma_testbench.h - Testbench module definition.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef _DMA_TESTBENCH_H_
#define _DMA_TESTBENCH_H_

/* Includes */
#include <amba_pv.h>
#include "types.h"
#include "dma.h"

/* Datatypes */

class dma_testbench:
    public sc_core::sc_module,
    public amba_pv::amba_pv_master_base,
    public amba_pv::signal_slave_base<signal_t> {

    /* Module ports */
    public:
        amba_pv::amba_pv_master_socket<BUSWIDTH> amba_pv_m;
        amba_pv::signal_slave_export<signal_t> dma_irq_in;

    /* Constructor */
        SC_HAS_PROCESS(dma_testbench);
        dma_testbench(sc_core::sc_module_name,
                      int,
                      sc_dt::uint64,
                      sc_dt::uint64,
                      sc_dt::uint64);

    /* Signal interface */
    protected:
        void set_state(int, const signal_t &);
            /* Testbench signal */
    
    /* Implementation  */
    private:

        /* Member variables */
        int m_number_of_runs;               /* Number of runs */
        sc_dt::uint64 m_mem_base_address;
            /* Memory base address */
        sc_dt::uint64 m_mem_size;
            /* Memory size */
        sc_dt::uint64 m_dma_base_address;
            /* DMA base address */
        sc_core::sc_event m_end_transfer;   /* DMA transfer end event */

        /* Helpers */
        void run();                         /* Testbench process */
};

#endif /* _DMA_TESTBENCH_H_ */
