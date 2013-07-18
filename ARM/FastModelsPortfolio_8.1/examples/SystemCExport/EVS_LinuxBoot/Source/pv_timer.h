/*
 * pv_timer.h - PV timer module definition.
 *
 * Copyright 2011 ARM Limited.
 * All rights reserved.
 */

#ifndef _PV_TIMER_H_
#define _PV_TIMER_H_

/* Includes */ 
#include <amba_pv.h>

#include "types.h"
#include "pv_counter.h"

/* Datatypes */

/*
 * Timer module definition, CPTimer-compatible.
 */
class pv_timer: 
    public sc_core::sc_module,
    public amba_pv::amba_pv_slave_base<BUSWIDTH>,
    public amba_pv::signal_slave_base<value64_t> {
      
    /* Registers relative addresses */
    public:
        static const addr_t TIMER0_LOAD;
        static const addr_t TIMER0_VALUE;
        static const addr_t TIMER0_CONTROL;
        static const addr_t TIMER0_INTR_CLEAR;
        static const addr_t TIMER0_RAW_INTR_STATUS;
        static const addr_t TIMER0_MASKED_INTR_STATUS;
        static const addr_t TIMER0_BACKGROUND_LOAD;
        static const addr_t TIMER1_LOAD;
        static const addr_t TIMER1_VALUE;
        static const addr_t TIMER1_CONTROL;
        static const addr_t TIMER1_INTR_CLEAR;
        static const addr_t TIMER1_RAW_INTR_STATUS;
        static const addr_t TIMER1_MASKED_INTR_STATUS;
        static const addr_t TIMER1_BACKGROUND_LOAD;
        static const addr_t TIMER2_LOAD;
        static const addr_t TIMER2_VALUE;
        static const addr_t TIMER2_CONTROL;
        static const addr_t TIMER2_INTR_CLEAR;
        static const addr_t TIMER2_RAW_INTR_STATUS;
        static const addr_t TIMER2_MASKED_INTR_STATUS;
        static const addr_t TIMER2_BACKGROUND_LOAD;
        static const addr_t TIMER3_LOAD;
        static const addr_t TIMER3_VALUE;
        static const addr_t TIMER3_CONTROL;
        static const addr_t TIMER3_INTR_CLEAR;
        static const addr_t TIMER3_RAW_INTR_STATUS;
        static const addr_t TIMER3_MASKED_INTR_STATUS;
        static const addr_t TIMER3_BACKGROUND_LOAD;

    /* Module ports */
        amba_pv::amba_pv_slave_socket<BUSWIDTH> amba_pv_s;
        amba_pv::signal_master_port<signal_t> pv_timer_intr_out0;
        amba_pv::signal_master_port<signal_t> pv_timer_intr_out1;
        amba_pv::signal_master_port<signal_t> pv_timer_intr_out2;
        amba_pv::signal_master_port<signal_t> pv_timer_intr_out3;

        amba_pv::signal_slave_export<value64_t> pv_timer_rate_hz_0;
        amba_pv::signal_slave_export<value64_t> pv_timer_rate_hz_1;
        amba_pv::signal_slave_export<value64_t> pv_timer_rate_hz_2;
        amba_pv::signal_slave_export<value64_t> pv_timer_rate_hz_3;

    /* Constructor */
        pv_timer(sc_core::sc_module_name, const sc_core::sc_time &);
        pv_timer(sc_core::sc_module_name, double, sc_core::sc_time_unit);

    /* Accessors */
        void set_resolution(int, const sc_core::sc_time &);
        void set_resolution(int, double, sc_core::sc_time_unit);
        sc_core::sc_time get_resolution() const;

        void set_state(int, const value64_t &);

    /* amba_pv_if methods implementation (overrides amba_pv_slave_base default
     * implementation) */
        amba_pv::amba_pv_resp_t read(int,
                                     const addr_t &,
                                     unsigned char *,
                                     unsigned int,
                                     const amba_pv::amba_pv_control *,
                                     sc_core::sc_time & );
        amba_pv::amba_pv_resp_t write(int,
                                      const addr_t &,
                                      unsigned char *,
                                      unsigned int,
                                      const amba_pv::amba_pv_control *,
                                      unsigned char *,
                                      sc_core::sc_time &);
        unsigned int debug_read(int,
                                const addr_t &,
                                unsigned char *,
                                unsigned int,
                                const amba_pv::amba_pv_control *);
        unsigned int debug_write(int,
                                 const addr_t &,
                                 unsigned char *,
                                 unsigned int,
                                 const amba_pv::amba_pv_control *);

    /* Implementation */
    private:
      
        /* Member variables */
        pv_counter m_counter0;
        pv_counter m_counter1;
        pv_counter m_counter2;
        pv_counter m_counter3;
};

#endif /* _PV_TIMER_H_ */
