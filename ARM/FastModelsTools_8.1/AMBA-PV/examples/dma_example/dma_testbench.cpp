/*
 * AMBA-PV: dma_testbench.cpp - Testbench module implementation.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

/* Includes */

#include "dma_testbench.h"

/* Functions */

/*
 * Constructor
 */
dma_testbench::dma_testbench(sc_core::sc_module_name module_name,
                             int number_of_runs,
                             sc_dt::uint64 mem_base_address,
                             sc_dt::uint64 mem_size,
                             sc_dt::uint64 dma_base_address):
    sc_core::sc_module(module_name), 
    amba_pv::amba_pv_master_base((const char *) module_name),
    amba_pv::signal_slave_base<signal_t>((const char *) module_name),
    amba_pv_m("amba_pv_m"),
    dma_irq_in("dma_irq_in"),
    m_number_of_runs(number_of_runs),
    m_mem_base_address(mem_base_address),
    m_mem_size(mem_size),
    m_dma_base_address(dma_base_address) {
    amba_pv_m(* this);
    dma_irq_in(* this);
    SC_THREAD(run);
    std::cout << name() << " module created - " << m_number_of_runs
              << " run" << ((number_of_runs > 1)? "s\n": "\n");
}

/*
 * Testbench IRQ transfer
 */
void dma_testbench::set_state(int, const signal_t & end_transfer) {
    if (end_transfer) {
        m_end_transfer.notify();
    }
}

/*
 * Testbench process
 */
void dma_testbench::run() {
    sc_dt::uint64 address;
    unsigned char value[sizeof(data_t)] = {0};
    amba_pv::amba_pv_control ctrl;
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;
    sc_dt::uint64 src_addr = 0, dst_addr = m_mem_size;

    for (int n = 0; (n < m_number_of_runs); n +=1) {

        /*
         * DMA programming: write register values...
         */

        /* Write DMA source address register */
        (* reinterpret_cast<data_t *>(value)) =
            static_cast<data_t>(m_mem_base_address + src_addr);
        src_addr = (src_addr + 256) % m_mem_size;
        if (amba_pv_m.write(m_dma_base_address + dma::SRC_ADDR,
                            value,
                            sizeof(value),
                            & ctrl,
                            NULL,
                            t) != amba_pv::AMBA_PV_OKAY) {
            std::cout << "ERROR\t" << name()
                      << ": write in DMA source address register failure\n";
        }
        sc_core::wait(t);
        t = sc_core::SC_ZERO_TIME;

        /* Write DMA destination address register */
        dst_addr = (dst_addr - 256) %  m_mem_size;
        (* reinterpret_cast<data_t *>(value)) =
            static_cast<data_t>(m_mem_base_address + dst_addr);
        if (amba_pv_m.write(m_dma_base_address + dma::DST_ADDR,
                            value,
                            sizeof(value),
                            & ctrl,
                            NULL,
                            t) != amba_pv::AMBA_PV_OKAY) {
            std::cout << "ERROR\t" << name()
                      << ": write in DMA destination address register"
                         " failure\n";
        }
        sc_core::wait(t);
        t = sc_core::SC_ZERO_TIME;

        /* Write DMA length register */
        (* reinterpret_cast<data_t *>(value)) = 256;
        if (amba_pv_m.write(m_dma_base_address + dma::LENGTH,
                            value,
                            sizeof(value),
                            & ctrl,
                            NULL,
                            t) != amba_pv::AMBA_PV_OKAY) {
            std::cout << "ERROR\t" << name()
                      << ": write in DMA length register failure\n";
        }
        sc_core::wait(t);
        t = sc_core::SC_ZERO_TIME;

        /*
         * DMA programming: starts the DMA transfer...
         */

        /* Start the DMA transfer */
        address = m_dma_base_address + dma::CONTROL;
        (* value) = dma::START;
        if (amba_pv_m.write(address,
                            value,
                            1,
                            & ctrl,
                            NULL,
                            t) != amba_pv::AMBA_PV_OKAY) {
            std::cout << "ERROR\t" << name()
                      << ": write in DMA control register failure\n";
        }
        if (m_number_of_runs <= 1) {

            /* Dump registers using debug transactions */
            amba_pv_m.debug_read(m_dma_base_address + dma::SRC_ADDR,
                                 value,
                                 sizeof(value),
                                 & ctrl);
            std::cout << "DEBUG\t" << name() << ": DMA source address: "
                      << std::hex << std::showbase
                      << (* reinterpret_cast<data_t *>(value)) << std::endl;
            amba_pv_m.debug_read(m_dma_base_address + dma::DST_ADDR,
                                 value,
                                 sizeof(value),
                                 & ctrl);
            std::cout << "DEBUG\t" << name() << ": DMA destination address: "
                      << std::hex << std::showbase
                      << (* reinterpret_cast<data_t *>(value)) << std::endl;
            amba_pv_m.debug_read(m_dma_base_address + dma::LENGTH,
                                 value,
                                 sizeof(value),
                                 & ctrl);
            std::cout << "DEBUG\t" << name() << ": DMA length: "
                      << std::hex << std::showbase
                      << (* reinterpret_cast<data_t *>(value)) << std::endl;
            amba_pv_m.debug_read(m_dma_base_address + dma::CONTROL,
                                 value,
                                 1,
                                 & ctrl);
            std::cout << "DEBUG\t" << name() << ": DMA control: "
                      << std::hex << std::showbase
                      << static_cast<unsigned int>(value[0]) << std::endl;
        }
        sc_core::wait(t);
        t = sc_core::SC_ZERO_TIME;

        /* Verification: read DMA control register (8 bits value) */
        amba_pv_m.debug_read(address, value, 1, & ctrl);

        /* Waiting for DMA end of transfer */
        if (!((* value) & dma::IRQ))
            wait(m_end_transfer);

        /*
         * Clears DMA interrupt
         */

        /* Read DMA control register */
        if (amba_pv_m.read(address,
                           value,
                           1,
                           & ctrl,
                           t) != amba_pv::AMBA_PV_OKAY) {
            std::cout << "ERROR\t" << name()
                      << ": read in DMA control register failure\n";
        }
        sc_core::wait(t);
        t = sc_core::SC_ZERO_TIME;

        /* Clears the IRQ bit of the DMA control register (8 bits value to
         * align before writing) */
        (* value) &= ~dma::IRQ;      
        if (amba_pv_m.write(address,
                            value,
                            1,
                            & ctrl,
                            NULL,
                            t) != amba_pv::AMBA_PV_OKAY) {
            std::cout << "ERROR\t" << name()
                      << ": write in DMA control register failure\n";
        }
        sc_core::wait(t);
        t = sc_core::SC_ZERO_TIME;
    }
}
