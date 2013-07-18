/*
 * AMBA-PV: dma.cpp - DMA model implementation.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */

#include "dma.h"

/* Constants */

/*
 * Register relative addresses
 */
const sc_dt::uint64 dma::SRC_ADDR = 0x00;  /* First register */
const sc_dt::uint64 dma::DST_ADDR = SRC_ADDR + sizeof(data_t);
const sc_dt::uint64 dma::LENGTH   = DST_ADDR + sizeof(data_t);
const sc_dt::uint64 dma::CONTROL  = LENGTH + sizeof(data_t);

/*
 * Control register bits
 */
const unsigned char dma::START = 0x01;
const unsigned char dma::IRQ   = 0x10;

/* Functions */

/*
 * Constructor
 */
dma::dma(sc_core::sc_module_name module_name,
         bool enable_dmi,
         bool verbose):
    sc_core::sc_module(module_name),
    amba_pv::amba_pv_slave_base<BUSWIDTH>(name()),
    amba_pv::amba_pv_master_base(name()),
    amba_pv_s("amba_pv_s"),
    amba_pv_m("amba_pv_m"),
    dma_irq_out("dma_irq_out"),
    m_verbose(verbose),
    m_dma_src_addr(0),
    m_dma_dst_addr(0),
    m_dma_length(0),
    m_dma_control(0),
    m_index_read(0),
    m_index_write(0),
    m_read(sizeof(m_buffer) / sizeof(m_buffer[0]) / BURSTLENGTH),
    m_write(0),
    m_enable_dmi(enable_dmi) {
    amba_pv_s(* this);
    amba_pv_m(* this);
    SC_THREAD(read_transfer);
    sensitive << m_start_transfer;
    SC_THREAD(write_transfer);
    sensitive << m_start_transfer;
    SC_METHOD(irq);
    sensitive << m_irq_to_change;
    dont_initialize();
    std::cout << name() << " module created\n";
}

/*
 * Destructor.
 */
dma::~dma() {
    std::cout << name() << ": " << m_dmi.size() << " DMI region(s) created\n";
}

/* amba_pv_if virtual method implementation */

/*
 * Read access
 */
amba_pv::amba_pv_resp_t dma::read(int socket_id,
                                  const sc_dt::uint64 & addr,
                                  unsigned char * data,
                                  unsigned int size,
                                  const amba_pv::amba_pv_control * ctrl,
                                  sc_core::sc_time & t) {
    switch (addr) {      
        case SRC_ADDR:

            /* Read DMA source address register */
            if (size != sizeof(data_t)) {
                std::cout << "ERROR\t" << name()
                          << ": invalid read access on source address"
                          << " register\n";
                return (amba_pv::AMBA_PV_SLVERR);
            }
            (* reinterpret_cast<data_t *>(data)) = m_dma_src_addr;
            if (m_verbose) {
                std::cout << "DEBUG\t" << name() << ": read DMA source "
                          << "address register, returns " << std::showbase
                          << std::hex << m_dma_src_addr << std::endl;
            }
            break;
        case DST_ADDR:

            /* Read DMA destination address register */
            if (size != sizeof(data_t)) {
                std::cout << "ERROR\t" << name()
                          << ": invalid read access on destination address"
                          << " register\n";
                return (amba_pv::AMBA_PV_SLVERR);
            }
            (* reinterpret_cast<data_t *>(data)) = m_dma_dst_addr;
            if (m_verbose) {
                std::cout << "DEBUG\t" << name() << ": read DMA destination"
                          << " address register, returns " << std::showbase
                          << std::hex << m_dma_dst_addr << std::endl;
            }
            break;  
        case LENGTH:

            /* Read DMA length register */      
            if (size != sizeof(data_t)) {
                std::cout << "ERROR\t" << name()
                          << ": invalid read access on length register\n";
                return (amba_pv::AMBA_PV_SLVERR);
            }
            (* reinterpret_cast<data_t *>(data)) = m_dma_length;
            if (m_verbose) {
                std::cout << "DEBUG\t" << name() << ": read DMA length register"
                          << ", returns " << std::showbase << std::hex
                          << m_dma_length << std::endl;
            }
            break;  
        case CONTROL: 

            /* Read DMA control register. This register is 8 bits */
            if (size != 1) {
                std::cout << "ERROR\t" << name()
                          << ": invalid read access on control register\n";
                return (amba_pv::AMBA_PV_SLVERR);
            }
            (* data) = m_dma_control;
            if (m_verbose) {
                std::cout << "DEBUG\t" << name() << ": read DMA control"
                          << " register, returns " << std::hex << std::showbase
                          << static_cast<int>(m_dma_control) << std::endl;
            }
            break;
        default:       
            std::cout << "ERROR\t" << name() << ": received read request"
                      << " with input address out of range: "
                      << std::showbase << std::hex << addr << std::endl;
            return (amba_pv::AMBA_PV_SLVERR);
    }
    return (amba_pv::AMBA_PV_OKAY);
}

/*
 * Write access
 */
amba_pv::amba_pv_resp_t dma::write(int socket_id,
                                   const sc_dt::uint64 & addr,
                                   unsigned char * data,
                                   unsigned int size,
                                   const amba_pv::amba_pv_control * ctrl,
                                   unsigned char * strb,
                                   sc_core::sc_time & t) {
    switch (addr) {
        case SRC_ADDR:

            /* Write DMA source address register */        
            if (size != sizeof(data_t)) {
                std::cout << "ERROR\t" << name()
                          << ": invalid write access on source address"
                          << " register\n";
                return (amba_pv::AMBA_PV_SLVERR);
            }
            m_dma_src_addr = (* reinterpret_cast<data_t *>(data));
            if (m_verbose) {
                std::cout << "DEBUG\t" << name() << ": write " << std::hex
                          << std::showbase << m_dma_src_addr
                          << " in DMA source address register\n";
            }
            break;
        case DST_ADDR:

            /* Write DMA destination address register */
            if (size != sizeof(data_t)) {
                std::cout << "ERROR\t" << name()
                          << ": invalid write access on destination address"
                          << " register\n";
                return (amba_pv::AMBA_PV_SLVERR);
            }
            m_dma_dst_addr = (* reinterpret_cast<data_t *>(data));
            if (m_verbose) {
                std::cout << "DEBUG\t" << name() << ": write " << std::hex
                          << std::showbase << m_dma_dst_addr
                          << " in DMA destination address register\n";
            }
            break;
        case LENGTH:

            /* Write DMA length register */      
            if (size != sizeof(data_t)) {
                std::cout << "ERROR\t" << name()
                          << ": invalid write access on length register\n";
                return (amba_pv::AMBA_PV_SLVERR);
            }
            m_dma_length = (* reinterpret_cast<data_t *>(data));
            if (m_verbose) {
                std::cout << "DEBUG\t" << name() << ": write " << std::hex
                          << std::showbase << m_dma_length
                          << " in DMA length register\n";
            }
            break;  
        case CONTROL: 
        
            /* Read DMA control register. This register is 8 bits */
            if (size != 1) {
                std::cout << "ERROR\t" << name()
                          << ": invalid write access on control register\n";
                return (amba_pv::AMBA_PV_SLVERR);
            }
            if (m_verbose) {
                std::cout << "DEBUG\t" << name() << ": write " << std::hex
                          << std::showbase << static_cast<int>(* data)
                          << " in DMA control register\n";
            }
            if (((* data) & START) && (!( m_dma_control & START))) {
                m_start_transfer.notify();
                m_dma_control |= START;
                if (m_verbose) {
                    std::cout << "DEBUG\t" << name() << ": DMA started\n";
                }
            }
            if ((! ((* data) & IRQ)) && (m_dma_control & IRQ)) {
                m_dma_control &= ~IRQ;
                m_irq_to_change.notify();
            }

            /* Control register is a system synchronization point */
            sc_core::wait(sc_core::SC_ZERO_TIME);
            break;
        default: 
            std::cout << "ERROR\t" << name() << ": received write request "
                      << "with input address out of range: " << std::showbase
                      << std::hex << addr << std::endl;
            return (amba_pv::AMBA_PV_SLVERR);
    }
    return (amba_pv::AMBA_PV_OKAY);
}

/*
 * Debug read access
 */
unsigned int dma::debug_read(int socket_id,
                             const sc_dt::uint64 & addr,
                             unsigned char * data,
                             unsigned int length,
                             const amba_pv::amba_pv_control * ctrl) {
    switch (addr) {      
        case SRC_ADDR:

            /* Read DMA source address register */
            if (length != sizeof(data_t)) {
                return 0;
            }
            (* reinterpret_cast<data_t *>(data)) = m_dma_src_addr;
            break;
        case DST_ADDR:

            /* Read DMA destination address register */
            if (length != sizeof(data_t)) {
                return 0;
            }
            (* reinterpret_cast<data_t *>(data)) = m_dma_dst_addr;
            break;  
        case LENGTH:

            /* Read DMA length register */      
            if (length != sizeof(data_t)) {
                return 0;
            }
            (* reinterpret_cast<data_t *>(data)) = m_dma_length;
            break;  
        case CONTROL: 

            /* Read DMA control register. This register is 8 bits */
            if (length != 1) {
                return 0;
            }
            (* data) = m_dma_control;
            break;
        default:       
            return 0;
    }
    return (length);
}

/*
 * Debug write access
 */
unsigned int dma::debug_write(int socket_id,
                              const sc_dt::uint64 & addr,
                              unsigned char * data,
                              unsigned int length,
                              const amba_pv::amba_pv_control * ctrl) {
    switch (addr) {
        case SRC_ADDR:

            /* Write DMA source address register */        
            if (length != sizeof(data_t)) {
                return 0;
            }
            m_dma_src_addr = (* reinterpret_cast<data_t *>(data));
            break;
        case DST_ADDR:

            /* Write DMA destination address register */
            if (length != sizeof(data_t)) {
                return 0;
            }
            m_dma_dst_addr = (* reinterpret_cast<data_t *>(data));
            break;
        case LENGTH:

            /* Write DMA length register */      
            if (length != sizeof(data_t)) {
                return 0;
            }
            m_dma_length = (* reinterpret_cast<data_t *>(data));
            break;  
        case CONTROL: 
        
            /* Write DMA control register. This register is 8 bits */
            if (length != 1) {
                return 0;
            }
            if (((* data) & START) && (!( m_dma_control & START))) {
                m_dma_control |= START;
            }
            if ((! ((* data) & IRQ)) && (m_dma_control & IRQ)) {
                m_dma_control &= ~IRQ;
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
void dma::irq() {
    if (m_dma_control & IRQ) {
        if (m_verbose) {
            std::cout << "DEBUG\t" << name() << ": rise transfer end IRQ \n";
        }
        dma_irq_out.set_state(true);
    } else {
        if (m_verbose) {
            std::cout << "DEBUG\t" << name() << ": clear transfer end IRQ \n";
        }
        dma_irq_out.set_state(false);
    }
}

/*
 * DMA transfer producer process
 */
void dma::read_transfer() {
    while (true) {

        /* Wait for start transfer event */
        wait();
        if (m_verbose) {
            std::cout << "DEBUG\t" << name() << std::showbase << std::hex
                      << ": DMA transfer started. Source address: "
                      << m_dma_src_addr << " - destination address: "
                      << m_dma_dst_addr << " - length: " << std::dec
                      << m_dma_length << " (bytes)\n";
        }
      
        /*
         * Starts the read part of the memory transfer...
         */
        unsigned int nb_word = (m_dma_length + sizeof(data_t) - 1)
                               / sizeof(data_t);

        for (unsigned int n = 0; (n < nb_word); n += BURSTLENGTH) {

            /* Read source block */
            m_read.wait();
            if (! read_block(m_dma_src_addr + (n * sizeof(data_t)),
                             sc_dt::sc_min(BURSTLENGTH, nb_word - n))) {
                m_read.post();
                continue;
            }
            m_index_read = (m_index_read + 1)
                           % (sizeof(m_buffer) / sizeof(m_buffer[0])
                              / BURSTLENGTH);
            if (m_verbose) {

                /* Output source bock using debug transactions... */
                debug_block(m_dma_src_addr + (n * sizeof(data_t)),
                            sc_dt::sc_min(BURSTLENGTH, nb_word - n), "source");
            }
            m_write.post();
        }
    }
}

/*
 * DMA transfer consumer process
 */
void dma::write_transfer() {
    while (true) {

        /* Wait for start transfer event */
        wait();
 
        /*
         * Starts the write part of the memory transfer...
         */
        unsigned int nb_word = (m_dma_length + sizeof(data_t) - 1)
                               / sizeof(data_t);

        for (unsigned int n = 0; (n < nb_word); n += BURSTLENGTH) {

            /* Write destination block */
            m_write.wait();
            if (! write_block(m_dma_dst_addr + (n * sizeof(data_t)),
                              sc_dt::sc_min(BURSTLENGTH, nb_word - n))) {
                m_write.post();
                continue;
            }
            m_index_write = (m_index_write + 1)
                            % (sizeof(m_buffer) / sizeof(m_buffer[0])
                               / BURSTLENGTH);

            /* Verify destination block */
            if (m_verbose) {

                /* Output destination bock using debug transactions... */
                debug_block(m_dma_dst_addr + (n * sizeof(data_t)),
                            sc_dt::sc_min(BURSTLENGTH, nb_word - n), "destination");
            }
            m_read.post();
        }

        /* Clear the START bit of the control register */
        m_dma_control &= ~START;

        /* Interrupt generation */
        if (! (m_dma_control & IRQ)) {
            m_dma_control |= IRQ;
            m_irq_to_change.notify();
        }
    }
}

/*
 * Read a block of given length at given address.
 */
bool dma::read_block(const sc_dt::uint64 & addr, unsigned int length) {
    std::vector<tlm::tlm_dmi>::iterator i;

    for (i = m_dmi.begin(); ((i != m_dmi.end()) && m_enable_dmi); i ++) {
        if ((i->get_start_address() <= addr)
            && (i->get_end_address() >= addr + (length * sizeof(data_t)))
            && i->is_read_allowed()) {

            /* DMI access found */
            std::memcpy(m_buffer + BURSTLENGTH * m_index_read,
                        i->get_dmi_ptr() + (addr - i->get_start_address()),
                        length * sizeof(data_t));
            return true;
        }
    }

    /* Perform regular transaction */
    amba_pv::amba_pv_transaction trans;
    amba_pv::amba_pv_extension ex(length,
                                  sizeof(data_t),
                                  NULL,
                                  amba_pv::AMBA_PV_INCR);
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;

    trans.set_read();
    trans.set_address(addr);
    trans.set_data_ptr(
        reinterpret_cast<unsigned char *>(m_buffer
                                          + BURSTLENGTH * m_index_read));
    trans.set_data_length(sizeof(data_t) * length);
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        amba_pv_m.b_transport(trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    sc_core::wait(t);
    if (ex.get_resp() != amba_pv::AMBA_PV_OKAY) {
        std::cout << "ERROR\t" << name()
                  << ": read_block() memory failure at "
                  << std::showbase << std::hex << addr << std::endl;
        trans.clear_extension(& ex);
        return false;
    }

    /* DMI may be requested */
    if (trans.is_dmi_allowed() && m_enable_dmi) {
        tlm::tlm_dmi dmi;

        /* Request DMI access for further read */
        trans.set_address(addr);
        if (amba_pv_m.get_direct_mem_ptr(trans, dmi)) {

            /* DMI access available */
            if ((dmi.get_start_address() <= addr)
                && (dmi.get_end_address() >= addr + (length * sizeof(data_t)))) {
                m_dmi.push_back(dmi);
            }
        }
    }
    trans.clear_extension(& ex);
    return true;
}

/*
 * Write a block of given length at given address.
 */
bool dma::write_block(const sc_dt::uint64 & addr, unsigned int length) {
    std::vector<tlm::tlm_dmi>::iterator i;

    for (i = m_dmi.begin(); ((i != m_dmi.end()) && m_enable_dmi); i ++) {
        if ((i->get_start_address() <= addr)
            && (i->get_end_address() >= addr + (length * sizeof(data_t)))
            && i->is_write_allowed()) {

            /* DMI access found */
            std::memcpy(i->get_dmi_ptr() + (addr - i->get_start_address()),
                        m_buffer + BURSTLENGTH * m_index_write,
                        length * sizeof(data_t));
            return true;
        }
    }

    /* Perform regular transaction */
    amba_pv::amba_pv_transaction trans;
    amba_pv::amba_pv_extension ex(length,
                                  sizeof(data_t),
                                  NULL,
                                  amba_pv::AMBA_PV_INCR);
    sc_core::sc_time t = sc_core::SC_ZERO_TIME;

    trans.set_write();
    trans.set_address(addr);
    trans.set_data_ptr(
        reinterpret_cast<unsigned char *>(m_buffer
                                          + BURSTLENGTH * m_index_write));
    trans.set_data_length(sizeof(data_t) * length);
    trans.set_streaming_width(trans.get_data_length());
    trans.set_extension(& ex);
    try {
        amba_pv_m.b_transport(trans, t);
    }
    catch (...) {
        trans.clear_extension(& ex);
        throw;
    }
    sc_core::wait(t);
    if (ex.get_resp() != amba_pv::AMBA_PV_OKAY) {
        std::cout << "ERROR\t" << name()
                  << ": write_block() memory failure at "
                  << std::showbase << std::hex << addr << std::endl;
        trans.clear_extension(& ex);
        return false;
    }

    /* DMI may be requested */
    if (trans.is_dmi_allowed() && m_enable_dmi) {
        tlm::tlm_dmi dmi;

        /* Request DMI access for further write */
        trans.set_address(addr);
        if (amba_pv_m.get_direct_mem_ptr(trans, dmi)) {

            /* DMI access available */
            if ((dmi.get_start_address() <= addr)
                && (dmi.get_end_address() >= addr + (length * sizeof(data_t)))) {
                m_dmi.push_back(dmi);
            }
        }
    }
    trans.clear_extension(& ex);
    return true;
}

/*
 * Invalidate a DMI access.
 */
void dma::invalidate_direct_mem_ptr(int,
                                    sc_dt::uint64 start,
                                    sc_dt::uint64 end) {
    std::vector<tlm::tlm_dmi>::iterator i = m_dmi.begin();
   
    while (i != m_dmi.end()) {
        if (((i->get_start_address() <= start)
             && (i->get_end_address() >= start))
            || ((i->get_start_address() <= end)
            && (i->get_end_address() >= end))) { 

            /* DMI access found -> remove it from our list */
            i = m_dmi.erase(i);
        } else {
            i ++;
        }
    }
}

/*
 * Output block using debug transactions.
 */
void dma::debug_block(const sc_dt::uint64 & addr,
                      unsigned int length,
                      const char * type) {
    std::cout << "DEBUG\t" << name() << std::dec << ": " << type << " block ("
              << length * sizeof(data_t) << " bytes) at "
              << std::showbase << std::hex << addr << ":\n";
    for (unsigned int i = 0; (i < length); i += 1) {
        data_t tmp = 0xffffffff;
        
        if (amba_pv_m.debug_read(addr + (i * sizeof(data_t)),
                                 reinterpret_cast<unsigned char *>(&tmp),
                                 sizeof(tmp),
                                 NULL) != sizeof(tmp)) {
            std::cout << "ERROR\t" << name()
                      << ": debug_read() memory failure at "
                      << std::showbase << std::hex
                      << addr + (i * sizeof(data_t)) << std::endl;
        }
        std::cout << std::hex << resetiosflags(std::ios_base::showbase);
        if (! (i % 4)) {
            std::cout << "\t0x" << addr + (i * sizeof(data_t));
        }
        std::cout << ": 0x" << std::setfill('0')
                  << std::setw(sizeof(data_t) * 2) << tmp;
        if (((i % 4) == 3)
            || (i == (length - 1))) {
            std::cout << std::endl;
        }
    }
}

