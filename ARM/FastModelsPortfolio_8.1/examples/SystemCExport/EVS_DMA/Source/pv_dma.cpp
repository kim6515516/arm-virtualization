/*
 * pv_dma.cpp - DMA module implementation.
 *
 * Copyright 2007-2009, 2011 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include "pv_dma.h"
#include <scx/scx.h>

/* Constants */

/*
 * Register relative addresses
 */
const addr_t pv_dma::SRC_ADDR = 0x00;  /* First register */
const addr_t pv_dma::DST_ADDR = SRC_ADDR + sizeof(data_t);
const addr_t pv_dma::LENGTH   = DST_ADDR + sizeof(data_t);
const addr_t pv_dma::CONTROL  = LENGTH + sizeof(data_t);

/*
 * Control register bit
 */
const unsigned char pv_dma::START = 0x01;
const unsigned char pv_dma::IRQ   = 0x10;

/* Functions */

/*
 * Constructor
 */
pv_dma::pv_dma(sc_core::sc_module_name module_name):
    sc_core::sc_module(module_name),
    amba_pv::amba_pv_slave_base<BUSWIDTH>(name()),
    amba_pv::amba_pv_master_base(name()),
    amba_pv_s("amba_pv_s"),
    amba_pv_m("amba_pv_m"),
    pv_dma_irq_out("pv_dma_irq_out"),
    m_pv_dma_src_addr(0),
    m_pv_dma_dst_addr(0),
    m_pv_dma_length(0),
    m_pv_dma_control(0) {
    amba_pv_s(* this);
    amba_pv_m(* this);
    SC_METHOD(transfer);
    sensitive << m_start_transfer;
    dont_initialize();
    SC_METHOD(irq);
    sensitive << m_irq_to_change;
    dont_initialize();
}

/* amba_pv_if virtual method implementation */

/*
 * DMA read access
 */
amba_pv::amba_pv_resp_t
pv_dma::read(int id,
             const addr_t & address,
             unsigned char * data,
             unsigned int size,
             const amba_pv::amba_pv_control * ctrl,
             sc_core::sc_time & t) {
    switch (address) {      
        case SRC_ADDR:

            /* Read pv_dma source address register. This register is 32 bits */
            if (size != 4) {
                SC_REPORT_WARNING(name(),
                                  "invalid read access on source address "
                                  "register");
                return (amba_pv::AMBA_PV_SLVERR);
            }
            (* reinterpret_cast<unsigned int *>(data)) = m_pv_dma_src_addr;
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
            std::cout << ": read pv_dma source address register, returns ";
            std::cout << m_pv_dma_src_addr << std::endl;
            break;
        case DST_ADDR:

            /* Read pv_dma destination address register.
             * This register is 32 bits */
            if (size != 4) {
                SC_REPORT_WARNING(name(),
                                  "invalid read access on destination address "
                                  "register");
                return (amba_pv::AMBA_PV_SLVERR);
            }
            (* reinterpret_cast<unsigned int *>(data)) = m_pv_dma_dst_addr;
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
            std::cout << ": read pv_dma destination address register, returns ";
            std::cout << m_pv_dma_dst_addr << std::endl;
            break;  
        case LENGTH:

            /* Read pv_dma length register. This register is 32 bits */
            if (size != 4) {
                SC_REPORT_WARNING(name(),
                                  "invalid read access on length register");
                return (amba_pv::AMBA_PV_SLVERR);
            }
            (* reinterpret_cast<unsigned int *>(data)) = m_pv_dma_length;
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
            std::cout << ": read pv_dma length register, returns ";
            std::cout << m_pv_dma_length << std::endl;
            break;  
        case CONTROL: 

            /* Read pv_dma control register. This register is 8 bits */
            if (size != 1) {
                SC_REPORT_WARNING(name(),
                                  "invalid read access on control register");
                return (amba_pv::AMBA_PV_SLVERR);
            }
            (* data) = m_pv_dma_control;
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
            std::cout << ": read pv_dma control register, returns ";
            std::cout << (int) m_pv_dma_control << std::endl;

            /* Control register is a system synchronization point */
            scx::scx_sync(t.to_seconds());
            break;
        default:       
            SCX_REPORT_WARNING(name(),
                               "DMA has received a read request with input "
                               "address out of range: %p", (void *) address);
            return (amba_pv::AMBA_PV_SLVERR);
    }
    return (amba_pv::AMBA_PV_OKAY);
}

/*
 * Write access
 */
amba_pv::amba_pv_resp_t
pv_dma::write(int id,
              const addr_t & address,
              unsigned char * data,
              unsigned int size,
              const amba_pv::amba_pv_control * ctrl,
              unsigned char * strb, 
              sc_core::sc_time & t) {
    switch (address) {
        case SRC_ADDR:

            /* Write pv_dma source address register. This register is 32 bits */
            if (size != 4) {
                SC_REPORT_WARNING(name(),
                                  "invalid write access on source address "
                                  "register");
                return (amba_pv::AMBA_PV_SLVERR);
            }
            m_pv_dma_src_addr = (* reinterpret_cast<unsigned int *>(data));
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
            std::cout << ": write " << m_pv_dma_src_addr;
            std::cout << " in pv_dma source address register\n";
            break;
        case DST_ADDR:

            /* Write pv_dma destination address register.
             * This register is 32 bits */
            if (size != 4) {
                SC_REPORT_WARNING(name(),
                                  "invalid write access on destination address "
                                  "register");
                return (amba_pv::AMBA_PV_SLVERR);
            }
            m_pv_dma_dst_addr = (* reinterpret_cast<unsigned int *>(data));
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
            std::cout << ": write " << m_pv_dma_dst_addr;
            std::cout << " in pv_dma destination address register\n";
            break;
        case LENGTH:

            /* Write pv_dma length register. This register is 32 bits */
            if (size != 4) {
                SC_REPORT_WARNING(name(),
                                  "invalid write access on length register");
                return (amba_pv::AMBA_PV_SLVERR);
            }
            m_pv_dma_length = (* reinterpret_cast<unsigned int *>(data));
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
            std::cout << ": write " << m_pv_dma_length;
            std::cout << " in pv_dma length register\n";
            break;  
        case CONTROL: 

            /* Write pv_dma control register. This register is 8 bits */
            if (size != 1) {
                SC_REPORT_WARNING(name(),
                                  "invalid write access on control register");
                return (amba_pv::AMBA_PV_SLVERR);
            }
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
            std::cout << ": write " << (unsigned int) (* data);
            std::cout << " in pv_dma control register\n";
            if (((* data) & START) && (!( m_pv_dma_control & START))) {
                m_start_transfer.notify();
                m_pv_dma_control |= START;
                std::cout << "DEBUG\t" << name() << ": pv_dma started\n";
            }
            if ((!((* data) & IRQ)) && (m_pv_dma_control & IRQ)) {
                m_pv_dma_control &= ~IRQ;
                m_irq_to_change.notify();
            }

            /* Control register is a system synchronization point */
            scx::scx_sync(t.to_seconds());
            break;
        default: 
            SCX_REPORT_WARNING(name(),
                               "DMA has received a write request with input "
                               "address out of range: %p", (void *) address);
            return (amba_pv::AMBA_PV_SLVERR);
    }
    return (amba_pv::AMBA_PV_OKAY);
}

/*
 * Debug read access
 */
unsigned int
pv_dma::debug_read(int socket_id,
                   const addr_t & addr,
                   unsigned char * data,
                   unsigned int length,
                   const amba_pv::amba_pv_control * ctrl) {
    switch (addr) {      
        case SRC_ADDR:

            /* Read pv_dma source address register. This register is 32 bits */
            if (length != 4) {
                return 0;
            }
            (* reinterpret_cast<unsigned int *>(data)) = m_pv_dma_src_addr;
            break;
        case DST_ADDR:

            /* Read pv_dma destination address register.
             * This register is 32 bits */
            if (length != 4) {
                return 0;
            }
            (* reinterpret_cast<unsigned int *>(data)) = m_pv_dma_dst_addr;
            break;  
        case LENGTH:

            /* Read pv_dma length register. This register is 32 bits */
            if (length != 4) {
                return 0;
            }
            (* reinterpret_cast<unsigned int *>(data)) = m_pv_dma_length;
            break;  
        case CONTROL: 

            /* Read pv_dma control register. This register is 8 bits */
            if (length != 1) {
                return 0;
            }
            (* data) = m_pv_dma_control;
            break;
        default:       
            return 0;
    }
    return (length);
}

/*
 * Debug write access
 */
unsigned int
pv_dma::debug_write(int socket_id,
                    const addr_t & addr,
                    unsigned char * data,
                    unsigned int length,
                    const amba_pv::amba_pv_control * ctrl) {
    switch (addr) {
        case SRC_ADDR:

            /* Write pv_dma source address register. This register is 32 bits */
            if (length != 4) {
                return 0;
            }
            m_pv_dma_src_addr = (* reinterpret_cast<unsigned int *>(data));
            break;
        case DST_ADDR:

            /* Write pv_dma destination address register.
             * This register is 32 bits */
            if (length != 4) {
                return 0;
            }
            m_pv_dma_dst_addr = (* reinterpret_cast<unsigned int *>(data));
            break;
        case LENGTH:

            /* Write DMA length register */      
            if (length != 4) {
                return 0;
            }
            m_pv_dma_length = (* reinterpret_cast<unsigned int *>(data));
            break;  
        case CONTROL: 

            /* Write pv_dma control register. This register is 8 bits */
            if (length != 1) {
                return 0;
            }
            if (((* data) & START) && (!( m_pv_dma_control & START))) {
                m_pv_dma_control |= START;
            }
            if ((!((* data) & IRQ)) && (m_pv_dma_control & IRQ)) {
                m_pv_dma_control &= ~IRQ;
            }
            break;
        default: 
            return 0;
    }
    return (length);
}

/*
 * Transfer end IRQ signal management
 */
void pv_dma::irq() {
    if (m_pv_dma_control & IRQ) {
        std::cout << "DEBUG\t" << name() << ": rise end transfer IRQ \n";
        pv_dma_irq_out.set_state(true);
    } else {
        std::cout << "DEBUG\t" << name() << ": clear end transfer IRQ \n";
        pv_dma_irq_out.set_state(false);  
    }
}

/*
 * DMA transfer management
 */
void pv_dma::transfer() {
    static const size_t BURST_LENGTH = 16;
    amba_pv::amba_pv_resp_t status;
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;

    if (m_pv_dma_control & START) {
        std::cout << "DEBUG\t" << name() << std::showbase << std::hex;
        std::cout << ": pv_dma transfer started. Source address: ";
        std::cout << m_pv_dma_src_addr << " - destination address: ";
        std::cout << m_pv_dma_dst_addr << " - length: " << std::dec;
        std::cout << m_pv_dma_length << " (bytes)\n";
     
        /*
         * Starts the memory transfer...
         */
        size_t nb_word = (m_pv_dma_length + sizeof(data_t) - 1)
                         / sizeof(data_t);
        data_t * tmp = new data_t[nb_word];

        for (size_t n = 0; (n < nb_word); n += BURST_LENGTH) {
            status = amba_pv_m.burst_read(0,
                                          m_pv_dma_src_addr + (n * sizeof(data_t)),
                                          reinterpret_cast<unsigned char *>(tmp + n),
                                          sc_dt::sc_min(BURST_LENGTH, nb_word - n),
                                          sizeof(data_t),
                                          NULL,
                                          amba_pv::AMBA_PV_INCR,
                                          t);
            if (status != amba_pv::AMBA_PV_OKAY) {
                SCX_REPORT_WARNING(name(),
                                  "read memory failure at %p",
                                  (void *) (m_pv_dma_src_addr + (n * sizeof(data_t))));
                std::cout << std::endl;
                continue;
            }

            /* Output source bock using debug transactions.... */
            std::cout << "DEBUG\t" << name() << std::dec
                      << ": source block ("
                      << sc_dt::sc_min(BURST_LENGTH, nb_word - n) * 8
                      << " bytes) at " << std::showbase << std::hex
                      << m_pv_dma_src_addr + (n * sizeof(data_t))
                      << "\n";
            for (size_t i = 0;
                 (i < sc_dt::sc_min(BURST_LENGTH, nb_word - n));
                 i += 1) {
                data_t tmp = 0xffffffff;

                if (amba_pv_m.debug_read(m_pv_dma_src_addr + (n + i) * sizeof(data_t),
                                         reinterpret_cast<unsigned char *>(&tmp),
                                         sizeof(tmp),
                                         NULL) != sizeof(tmp)) {
                    SCX_REPORT_WARNING(name(),
                                       "debug_read() memory failure at %p",
                                       (void *) ((n + i) * sizeof(data_t)));
                }

                std::cout << std::hex
                          << resetiosflags(std::ios_base::showbase);
                if (! (i % 4)) {
                    std::cout << "\t0x"
                              << (m_pv_dma_src_addr
                                  + ((n + i) * sizeof(data_t)));
                }
                std::cout << ": 0x" << std::setfill('0')
                          << std::setw(sizeof(data_t) * 2)
                          << tmp;
                if (((i % 4) == 3)
                    || (i == (sc_dt::sc_min(BURST_LENGTH, nb_word - n) - 1))) {
                    std::cout << std::endl;
                }
            }

            /* Write destination block */
            status = amba_pv_m.burst_write(0,
                                           m_pv_dma_dst_addr + (n * sizeof(data_t)),
                                           reinterpret_cast<unsigned char *>(tmp + n),
                                           sc_dt::sc_min(BURST_LENGTH, nb_word - n),
                                           sizeof(data_t),
                                           NULL,
                                           amba_pv::AMBA_PV_INCR,
                                           NULL,
                                           0,
                                           t);
            if (status != amba_pv::AMBA_PV_OKAY) {
                SCX_REPORT_WARNING(name(),
                                   "write memory failure at %p",
                                   (void *) (m_pv_dma_dst_addr + (n * sizeof(data_t))));
                continue;
            }

            /* Verify destination block */
            status = amba_pv_m.burst_read(0,
                                          m_pv_dma_dst_addr + (n * sizeof(data_t)),
                                          reinterpret_cast<unsigned char *>(tmp + n),
                                          sc_dt::sc_min(BURST_LENGTH, nb_word - n),
                                          sizeof(data_t),
                                          NULL,
                                          amba_pv::AMBA_PV_INCR,
                                          t);

            if (status != amba_pv::AMBA_PV_OKAY) {
                continue;
            }

            /* Output destination bock using debug transactions... */
            std::cout << "DEBUG\t" << name() << std::dec
                      << ": destination block ("
                      << sc_dt::sc_min(BURST_LENGTH, nb_word - n) * 8
                      << " bytes) at " << std::showbase << std::hex
                      << m_pv_dma_dst_addr + (n * sizeof(data_t))
                      << "\n";
            for (size_t i = 0;
                 (i < sc_dt::sc_min(BURST_LENGTH, nb_word - n));
                 i += 1) {
                data_t tmp = 0xffffffff;

                if (amba_pv_m.debug_read(m_pv_dma_dst_addr+ (n + i) * sizeof(data_t),
                                         reinterpret_cast<unsigned char *>(&tmp),
                                         sizeof(tmp),
                                         NULL) != sizeof(tmp)) {
                    SCX_REPORT_WARNING(name(),
                                       "debug_read() memory failure at %p",
                                       (void *) ((n + i) * sizeof(data_t)));
                }

                std::cout << std::hex
                          << resetiosflags (std::ios_base::showbase);
                if (! (i % 4)) {
                    std::cout << "\t0x"
                              << (m_pv_dma_dst_addr
                                  + ((n + i) * sizeof(data_t)));
                }
                std::cout << ": 0x" << std::setfill('0')
                          << std::setw(sizeof(data_t) * 2)
                          << tmp;
                if (((i % 4) == 3)
                    || (i == (sc_dt::sc_min(BURST_LENGTH, nb_word - n) - 1))) {
                    std::cout << std::endl;
                }
            }
        }

        delete [] tmp;
 
        /* Clear the START bit of the control register */
        m_pv_dma_control &= ~START;

        /* Interrupt generation */
        if (! (m_pv_dma_control & IRQ)) {
            m_pv_dma_control |= IRQ;
            m_irq_to_change.notify();

            /* This is a synchronization point */
            scx::scx_sync(t.to_seconds());
        }
    }
}

