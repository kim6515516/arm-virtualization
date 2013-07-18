/*
 * pv_dma.h - PV DMA module definition.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef _PV_DMA_H_
#define _PV_DMA_H_

/* Includes */ 
#include <amba_pv.h>
#include "types.h"

/* Datatypes */

class pv_dma:
    public sc_core::sc_module,
    public amba_pv::amba_pv_slave_base<BUSWIDTH>,
    public amba_pv::amba_pv_master_base {
      
    /* Registers relative addresses */
    public:
        static const addr_t SRC_ADDR;
        static const addr_t DST_ADDR;
        static const addr_t LENGTH;
        static const addr_t CONTROL;

    /* Control register bits */
        static const unsigned char START;
        static const unsigned char IRQ;

    /* Module ports */
        amba_pv::amba_pv_slave_socket<BUSWIDTH> amba_pv_s;
        amba_pv::amba_pv_master_socket<BUSWIDTH> amba_pv_m;
        amba_pv::signal_master_port<signal_t> pv_dma_irq_out;

    /* Constructor */
        SC_HAS_PROCESS(pv_dma);
        explicit pv_dma(sc_core::sc_module_name);

    /* amba_pv_if methods implementation (overrides amba_pv_slave_base default
     * implementation) */
        virtual amba_pv::amba_pv_resp_t
        read(int,
             const addr_t &,
             unsigned char *,
             unsigned int,
             const amba_pv::amba_pv_control *,
             sc_core::sc_time &);
        virtual amba_pv::amba_pv_resp_t
        write(int,
              const addr_t &,
              unsigned char *,
              unsigned int,
              const amba_pv::amba_pv_control *,
              unsigned char *,
              sc_core::sc_time &);
        virtual unsigned int
        debug_read(int,
                   const addr_t &,
                   unsigned char *,
                   unsigned int,
                   const amba_pv::amba_pv_control *);
        virtual unsigned int
        debug_write(int,
                    const addr_t &,
                    unsigned char *,
                    unsigned int,
                    const amba_pv::amba_pv_control *);

    /* Implementation */
    private:
      
        /* Member variables */
        sc_core::sc_event m_start_transfer;
            /* DMA process related event (start) */
        sc_core::sc_event m_irq_to_change;
            /* Rise/clear interrupt signal related event */
        unsigned int m_pv_dma_src_addr; /* Source address register */
        unsigned int m_pv_dma_dst_addr; /* Destination address register */
        unsigned int m_pv_dma_length;   /* Length register (in byte) */
        unsigned char m_pv_dma_control; /* Control register (8 bits register) */
      
        /* Helpers */
        void transfer();                /* DMA transfer management process */
        void irq();
            /* DMA transfer end IRQ signal management process */
};

#endif /* _PV_DMA_H_ */
