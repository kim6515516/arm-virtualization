/*
 * master.cpp - DMA master implementation.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */

#include "master.h"

/* Functions */

/*
 * Constructor
 */
master::master(sc_core::sc_module_name module_name):
    sc_core::sc_module(module_name), 
    amba_pv::signal_slave_base<signal_t>((const char *) module_name),
    pv_dma_irq_in("pv_dma_irq_in") {
    pv_dma_irq_in(* this);
    SC_THREAD(run);
}

/*
 * Master IRQ transfer
 */
void master::set_state(int, const bool & s) {
    if (s) {
        std::cout << "DEBUG\t" << name() << ": end of DMA transfer received\n";
        m_end_transfer.notify();
    }
}

/*
 * Testbench process
 */
void master::run() {

    while (true) {

        /*
         * Waits for DMA end of transfer.../
         */
        wait(m_end_transfer);
    }
}
