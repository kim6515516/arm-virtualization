/*
 * pv_counter.h - PV counter module definition.
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef _PV_COUNTER_H_
#define _PV_COUNTER_H_

/* Includes */ 
#include <amba_pv.h>

#include "types.h"

/* Datatypes */

/*
 * Counter module definition.
 */
class pv_counter: public sc_core::sc_module {
      
    /* Registers relative addresses */
    public:
        static const addr_t COUNTER_LOAD;
        static const addr_t COUNTER_VALUE;
        static const addr_t COUNTER_CONTROL;
        static const addr_t COUNTER_INTR_CLEAR;
        static const addr_t COUNTER_RAW_INTR_STATUS;
        static const addr_t COUNTER_MASKED_INTR_STATUS;
        static const addr_t COUNTER_BACKGROUND_LOAD;
     
    /* Control register bits */
        enum mode {
            MODE_FREE_RUNNING,
            MODE_PERIODIC_RELOAD
        };

    /* Module ports */
        amba_pv::signal_master_port<signal_t> intr_out;

    /* Constructor */
        SC_HAS_PROCESS(pv_counter);
        pv_counter(sc_core::sc_module_name, const sc_core::sc_time &);
        pv_counter(sc_core::sc_module_name, double, sc_core::sc_time_unit);

    /* Accessors */
        void set_resolution(const sc_core::sc_time &);
        void set_resolution(double, sc_core::sc_time_unit);
        sc_core::sc_time get_resolution() const;

    /* Programming */
        unsigned int register_read(addr_t, sc_core::sc_time &);
        void register_write(addr_t, unsigned int, sc_core::sc_time &);

    /* Debugging */
        unsigned int register_debug_read(addr_t);
        void register_debug_write(addr_t, unsigned int);

    /* Implementation */
    private:
      
        /* Member variables */
        double m_res;
        mode m_mode;
        unsigned int m_load;
        sc_dt::uint64 m_counter;
        double m_reload_time;
        bool m_enabled_p;
        bool m_ie_p;    /* Interrupt enable flag */
        int m_prescale;
        int m_counter_size;
        bool m_oneshot_p;
        bool m_raw_intr_p;
        int m_shift;
        sc_core::sc_event m_intr_event;  /* Interrupt event */
      
        /* sc_module overridable */
        virtual void end_of_elaboration();

        /* Helpers */
        unsigned int get_control_register() const;
        void set_control_register(unsigned int);
        void set_intr();
        void init_counter(const sc_core::sc_time &);
        void intr_event_handler();
        void sync(const sc_core::sc_time &);
};

#endif /* _PV_COUNTER_H_ */
