/*
 * AMBA-PV: dma.h - DMA model definition.
 *
 * Copyright 2007-2010 ARM Limited.
 * All rights reserved.
 *
 */

#ifndef _DMA_H_
#define _DMA_H_

/* Includes */ 
#include <amba_pv.h>
#include "types.h"

/* Datatypes */

class dma: 
    public sc_core::sc_module,
    public amba_pv::amba_pv_slave_base<BUSWIDTH>,
    public amba_pv::amba_pv_master_base {
      
    /* Registers relative addresses */
    public:
        static const sc_dt::uint64 SRC_ADDR;
        static const sc_dt::uint64 DST_ADDR;
        static const sc_dt::uint64 LENGTH;
        static const sc_dt::uint64 CONTROL;

    /* Control register bits */
        static const unsigned char START;
        static const unsigned char IRQ;

    /* Module ports */
        amba_pv::amba_pv_slave_socket<BUSWIDTH> amba_pv_s;
        amba_pv::amba_pv_master_socket<BUSWIDTH> amba_pv_m;
        amba_pv::signal_master_port<signal_t> dma_irq_out;

    /* Constructor */
        SC_HAS_PROCESS(dma);
        explicit dma(sc_core::sc_module_name, bool = false, bool = false);
        virtual ~dma();

    /* User-layer interface */
    protected:
        virtual amba_pv::amba_pv_resp_t
        read(int,
             const sc_dt::uint64 &,
             unsigned char *,
             unsigned int,
             const amba_pv::amba_pv_control *,
             sc_core::sc_time &);
        virtual amba_pv::amba_pv_resp_t
        write(int,
              const sc_dt::uint64 &,
              unsigned char *,
              unsigned int,
              const amba_pv::amba_pv_control *,
              unsigned char *,
              sc_core::sc_time &);
        virtual unsigned int
        debug_read(int,
                   const sc_dt::uint64 &,
                   unsigned char *,
                   unsigned int,
                   const amba_pv::amba_pv_control *);
        virtual unsigned int
        debug_write(int,
                    const sc_dt::uint64 &,
                    unsigned char *,
                    unsigned int,
                    const amba_pv::amba_pv_control *);

    /* Backward interface */
        virtual void
        invalidate_direct_mem_ptr(int, sc_dt::uint64, sc_dt::uint64);

    /* Implementation */
    private:
      
        /* Member variables */
        bool m_verbose;                 /* Verbosity */
        sc_core::sc_event m_start_transfer;
            /* DMA process related event (start) */
        sc_core::sc_event m_irq_to_change;
            /* Rise/clear interrupt signal related event */
        data_t m_dma_src_addr;          /* Source address register */
        data_t m_dma_dst_addr;          /* Destination address register */
        data_t m_dma_length;            /* Length register (in byte) */
        unsigned char m_dma_control;    /* control register (8 bits register) */
        data_t m_buffer[BURSTLENGTH * 2];   /* Transfer buffer */
        unsigned int m_index_read;      /* Producer index into buffer */
        unsigned int m_index_write;     /* Consumer index into buffer */
        sc_core::sc_semaphore m_read;   /* Producer semaphore */
        sc_core::sc_semaphore m_write;  /* Consumer semaphore */
        std::vector<tlm::tlm_dmi> m_dmi;/* DMI accesses list */
        bool m_enable_dmi;              /* Enbale DMI or not */
      
        /* Helpers */
        void read_transfer();           /* DMA transfer producer process */
        void write_transfer();          /* DMA transfer consumer process */
        void irq();
            /* DMA transfer end IRQ signal management process */
        bool read_block(const sc_dt::uint64 &, unsigned int);
        bool write_block(const sc_dt::uint64 &, unsigned int);
        void debug_block(const sc_dt::uint64 &, unsigned int, const char *);
};

#endif /* _DMA_H_ */
