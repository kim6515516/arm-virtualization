/*
 * AMBA-PV: dbg_master.h - Debug master.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef DBG_MASTER__H
#define DBG_MASTER__H

/* Includes */ 
#include <amba_pv.h>
#include "types.h"

/* Datatypes */

template<unsigned int BUSWIDTH = 64>
class dbg_master:
    public sc_core::sc_module,
    public amba_pv::amba_pv_master_base {
      
    /* Registers relative addresses */
    public:

    /* Module ports */
        amba_pv::amba_pv_master_socket<BUSWIDTH> amba_pv_m;

    /* Constructor */
        SC_HAS_PROCESS(dbg_master);
        dbg_master(sc_core::sc_module_name, bool = false);

    /* Implementation */
    private:
      
        /* Member variables */
        bool m_verbose;                 /* Verbosity */
      
        /* Helpers */
        void transfer();                /* transfer management process */
};

/*
 * Constructor
 */
template<unsigned int BUSWIDTH>
inline
dbg_master<BUSWIDTH>::dbg_master(sc_core::sc_module_name module_name,
                                 bool verbose):
    sc_core::sc_module(module_name),
    amba_pv::amba_pv_master_base((const char *) module_name),
    amba_pv_m("amba_pv_m"),
    m_verbose(verbose) {
    amba_pv_m(* this);
    SC_METHOD(transfer);
    std::cout << name() << " module created\n";
}


/*
 * transfer management
 */
template<unsigned int BUSWIDTH>
inline
void dbg_master<BUSWIDTH>::transfer() {
    sc_dt::uint64 start_addr = 0xf0000000;

    std::cout << name() << ": start of transfer()..." << std::endl;

    /* Debug write some values */
    data_t dbg_data[4] = {0x33221100, 0x77665544, 0xbbaa9988, 0xffeeddcc};

    if (amba_pv_m.debug_write(start_addr,
                              reinterpret_cast<unsigned char *>(dbg_data),
                              sizeof(dbg_data),
                              NULL) != sizeof(dbg_data)) {
        std::cout << "ERROR\t" << name()
                  << ": debug_write() memory failure at "
                  << std::showbase << std::hex
                  << start_addr << std::endl;
    }

    /* Debug read back the written values */
    data_t dbg_tmp[sizeof(dbg_data)/sizeof(data_t)];

    if (amba_pv_m.debug_read(start_addr,
                             reinterpret_cast<unsigned char *>(dbg_tmp),
                             sizeof(dbg_data),
                             NULL) != sizeof(dbg_data)) {
        std::cout << "ERROR\t" << name()
                  << ": debug_read() memory failure at "
                  << std::showbase << std::hex
                  << start_addr*sizeof(data_t) << std::endl;
    }

    /* Output destination bock... */
    std::cout << "DEBUG\t" << name() << std::showbase
              << std::hex << ": debug transaction block ("
              << 16 <<  ")" << std::endl;
    for (unsigned int i = 0;
         (i < 4);
         i += 1) {
        std::cout << std::hex
                  << resetiosflags (std::ios_base::showbase);
        if (! (i % sizeof(data_t))) {
            std::cout << "\t0x"
                      << (start_addr
                          + ((i) * sizeof(data_t)));
        }
        std::cout << ": 0x" << std::setfill('0')
                  << std::setw(sizeof(data_t) * 2)
                  << dbg_tmp[i];
        if (((i % sizeof(data_t)) == sizeof(data_t) - 1)
            || (i == 15)) {
            std::cout << std::endl;
        }
    }
    std::cout << name() << ": end of transfer()..." << std::endl;
}

#endif /* DBG_MASTER__H */
