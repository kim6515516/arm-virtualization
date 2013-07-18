/*
 * AMBA-PV: amba_pv_memory.h - AMBA-PV advanced memory model.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_MEMORY__H
#define AMBA_PV_MEMORY__H

/**
 * @file        amba_pv_memory.h
 *
 * @brief       AMBA-PV advanced memory model.
 */

/* Includes */
#include "sockets/amba_pv_slave_socket.h"
#include "models/amba_pv_memory_base.h"
#include <map>
#include <fstream>
#include <iomanip>

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV advanced memory model.
 *
 * The amba_pv_memory class models an AMBA compatible memory at the PV level
 * and features:
 * - page-based organization with allocate on write policy for optimized
 *   heap usage
 * - a read to non-allocated pages returns the default value
 * - constructor parameter for page size
 * - save and restore.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_memory:
    public amba_pv_memory_base<BUSWIDTH>,
    public sc_core::sc_module {

    /* Sockets */
    public:

        /**
         * @brief Slave socket.
         */
        amba_pv_slave_socket<BUSWIDTH> amba_pv_s;

    /* Constructor/Destructor */
        amba_pv_memory(const sc_core::sc_module_name &,
                       const sc_dt::uint64 &,
                       unsigned int = 4096);
        amba_pv_memory(const sc_core::sc_module_name &,
                       const sc_dt::uint64 &,
                       unsigned char,
                       unsigned int = 4096);
            /* Deprecated. Use other constructor instead. */
        ~amba_pv_memory();

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Accessors */
        unsigned int get_page_size() const;
        void set_fill_pattern(unsigned char, unsigned char);


    /* Save/restore */
        void save(const std::string &);
        void save(std::ostream &);
        void restore(const std::string &);
        void restore(std::istream &);

    /* User-layer interface */
    protected:
        virtual amba_pv_resp_t read(int,
                                    const sc_dt::uint64 &,
                                    unsigned char *,
                                    unsigned int,
                                    const amba_pv_control *,
                                    sc_core::sc_time &);
        virtual amba_pv_resp_t write(int,
                                     const sc_dt::uint64 &,
                                     unsigned char *,
                                     unsigned int,
                                     const amba_pv_control *,
                                     unsigned char *,
                                     sc_core::sc_time &);
        virtual bool get_direct_mem_ptr(int,
                                        tlm::tlm_command,
                                        const sc_dt::uint64 &,
                                        const amba_pv_control *,
                                        tlm::tlm_dmi &);
         virtual unsigned int debug_read(int,
                                         const sc_dt::uint64 &,
                                         unsigned char *,
                                         unsigned int,
                                         const amba_pv_control *);
         virtual unsigned int debug_write(int,
                                          const sc_dt::uint64 &,
                                          unsigned char *,
                                          unsigned int,
                                          const amba_pv_control *);

    /* Implementation */
    private:

        /* Member variables */
        unsigned int m_page_size; /* Page size (in bytes) */
        unsigned char * m_empty_page;   /* Uninitialized page */
        std::map<sc_dt::uint64, unsigned char *> m_pages; /* Pages */

        /* Helper methods */
        void clear();
        bool read_int(const sc_dt::uint64 &, unsigned char *, unsigned int);
        bool write_int(const sc_dt::uint64 &, unsigned char *, unsigned int);
        template<typename T>
        static void save_val(std::ostream &, const T &);
        template<typename T>
        static void restore_val(std::istream &, T &);
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name memory name.
 * @param       size memory size in bytes. @a size is rounded up to the next
 *              multiple of 4096.
 * @param       page_size memory page size in bytes. Defaults to 4096.
 *              @a page_size is rounded up to the next multiple of 4096.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_memory<BUSWIDTH>::amba_pv_memory(const sc_core::sc_module_name & name,
                                         const sc_dt::uint64 & size,
                                         unsigned int page_size):
    amba_pv_memory_base<BUSWIDTH>((const char *) name, size),
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s"),
    m_page_size((page_size + 4095) & ~4095),
    m_empty_page(NULL) {
    m_empty_page = new unsigned char[m_page_size];

    /* Bindings... */
    amba_pv_s(* this);
}

/**
 * @brief       Constructor.
 *
 * @param       name memory name.
 * @param       size memory size in bytes. @a size is rounded up to the next
 *              multiple of 4096.
 * @param       fill_char fill character used for uninitialized memory.
 * @param       page_size memory page size in bytes. Defaults to 4096.
 *              @a page_size is rounded up to the next multiple of 4096.
 *
 * @note        This constructor is deprecated. Use the other constructor
 *              instead.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_memory<BUSWIDTH>::amba_pv_memory(const sc_core::sc_module_name & name,
                                         const sc_dt::uint64 & size,
                                         unsigned char fill_char,
                                         unsigned int page_size):
    amba_pv_memory_base<BUSWIDTH>((const char *) name, size),
    sc_core::sc_module(name),
    amba_pv_s("amba_pv_s"),
    m_page_size((page_size + 4095) & ~4095),
    m_empty_page(NULL) {
    static bool warn_constructor = false;

    if (! warn_constructor) {
        warn_constructor = true;
        SC_REPORT_INFO(kind(),
                       "amba_pv_memory(): deprecated, use other constructor "
                       "instead");
    }
    m_empty_page = new unsigned char[m_page_size];
    std::memset(m_empty_page, fill_char, m_page_size);

    /* Bindings... */
    amba_pv_s(* this);
}

/**
 * @brief       Destructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_memory<BUSWIDTH>::~amba_pv_memory() {
    clear();
    delete [] m_empty_page;
}

/**
 * @brief       Returns the kind string of this memory.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_memory<BUSWIDTH>::kind() const {
    return ("amba_pv_memory");
}

/**
 * @brief       Returns the page size of this memory.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_memory<BUSWIDTH>::get_page_size() const {
    return (m_page_size);
}

/**
 * @brief       Sets the fill pattern used for uninitialized memory.
 *
 * This does not affect any pages that have already been allocated, so ideally
 * this must be called before the first write transaction to this memory.
 *
 * @param       fill_char1 first character to use for uninitialized memory.
 * @param       fill_char2 second character to use for uninitialized memory.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_memory<BUSWIDTH>::set_fill_pattern(unsigned char fill_char1,
                                           unsigned char fill_char2) {
    for (unsigned int i =0; (i < m_page_size); i += 2) {
        m_empty_page[i] = fill_char1;
        m_empty_page[i + 1] = fill_char2;
    }
}

/**
 * @brief       Saves the contents of this memory to the specified @a file.
 *
 * @param       file name of file to save memory contents to.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_memory<BUSWIDTH>::save(const std::string & file) {
    std::ofstream ofs;
    
    ofs.open(file.c_str(), std::ios::trunc);
    if (! ofs.is_open()) {
        std::string msg("save(): error opening \"");

        msg += file;
        msg += "\"";
        SC_REPORT_WARNING(kind(), msg.c_str());
    } else {
        save(ofs);
    }
}

/**
 * @brief       Saves the contents of this memory to the specified stream.
 *
 * @param       os stream to save memory contents to.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_memory<BUSWIDTH>::save(std::ostream & os) {
    typename std::map<sc_dt::uint64, unsigned char *>::iterator i;
    bool exist_p;
    unsigned char * page;

    for (sc_dt::uint64 addr = 0;
         (addr < this->get_addr_limit());
         addr += m_page_size) {
        
        /* Check page existence */
        if ((i = m_pages.find(addr)) != m_pages.end()) {
            exist_p = ((* i).second != NULL);
        } else {
            exist_p = false;
        }
        if (! exist_p) {
            continue;
        }
   
        /* Save page address */
        save_val(os, addr);

        /* Save page */
        page = (* i).second;
        for (unsigned int j = 0; (j < m_page_size); j += sizeof(unsigned int)) {
            save_val(os, (* reinterpret_cast<unsigned int *>(page + j)));
        }
    }
}

/**
 * @brief       Restore the contents of this memory from the specified @a file.
 *
 * @param       file name of file to restore this memory contents from.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_memory<BUSWIDTH>::restore(const std::string & file) {
    std::ifstream ifs;
    
    ifs.open(file.c_str());
    if (! ifs.is_open()) {
        std::string msg("restore(): error opening \"");

        msg += file;
        msg += "\"";
        SC_REPORT_WARNING(kind(), msg.c_str());
    } else {
        restore(ifs);
    }
}

/**
 * @brief       Restore the contents of this memory from the specified stream.
 *
 * @param       is stream to restore this memory contents from.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_memory<BUSWIDTH>::restore(std::istream & is) {
    typename std::map<sc_dt::uint64, unsigned char *>::iterator j;
    sc_dt::uint64 addr;
    unsigned char * page;
            
    /* Invalidate possible previous DMI pointers to the memory...*/
    amba_pv_s->invalidate_direct_mem_ptr(0, (sc_dt::uint64) -1);

    /* Clear the memory... */
    clear();
    while (is.peek() != EOF) {
        
        /* Restore page address */
        restore_val(is, addr);
        if ((j = m_pages.find(addr)) != m_pages.end()) {
            
            /* Clear page in case of multiple restore... */
            delete [] (* j).second;
            m_pages.erase(j);
        }

        /* (Re)create page... */
        page = new unsigned char[m_page_size];
        m_pages[addr] = page;

        /* Restore page */
        for (unsigned int k = 0; (k < m_page_size); k += sizeof(unsigned int)) {
            restore_val(is, (* reinterpret_cast<unsigned int *>(page +k)));
        }
    }
}

/**
 * @brief       Completes a read transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_memory<BUSWIDTH>::read(int socket_id,
                               const sc_dt::uint64 & addr,
                               unsigned char * data,
                               unsigned int size,
                               const amba_pv_control * ctrl,
                               sc_core::sc_time & t) {
    if (((addr & ~sc_dt::uint64(size - 1)) + size) > this->get_addr_limit()) {
        return (AMBA_PV_DECERR);
    }
    if (! read_int(addr, data, size)) {
        return (AMBA_PV_SLVERR);
    }
    return (AMBA_PV_OKAY);
}

/**
 * @brief       Completes a write transaction.
 */
template<unsigned int BUSWIDTH>
inline amba_pv_resp_t
amba_pv_memory<BUSWIDTH>::write(int socket_id,
                                const sc_dt::uint64 & addr,
                                unsigned char * data,
                                unsigned int size,
                                const amba_pv_control * ctrl,
                                unsigned char * strb,
                                sc_core::sc_time & t) {
    if (((addr & ~sc_dt::uint64(size - 1)) + size) > this->get_addr_limit()) {
        return (AMBA_PV_DECERR);
    }
    if (strb != NULL) {
        unsigned char * tmp = new unsigned char[size];
        
        if (! read_int(addr, tmp, size)) {
            delete [] tmp;
            return (AMBA_PV_SLVERR);
        }
        for (unsigned int i = 0; (i < size); i += 1) {
            if (strb[i] == TLM_BYTE_ENABLED) {
                tmp[i] = data[i];
            }
        }
        if (! write_int(addr, tmp, size)) {
            delete [] tmp;
            return (AMBA_PV_SLVERR);
        }
        delete [] tmp;
    } else if (! write_int(addr, data, size)) {
        return (AMBA_PV_SLVERR);
    }
    return (AMBA_PV_OKAY);
}

/**
 * @brief       Non-intrusive debug read transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_memory<BUSWIDTH>::debug_read(int socket_id,
                                     const sc_dt::uint64& addr,
                                     unsigned char* data,
                                     unsigned int length,
                                     const amba_pv_control* ctrl) {
    unsigned int num_values = 0;
    sc_dt::uint64 addr2 = addr;
    unsigned char * data2 =data;

    while (num_values < length) {
        if (! read_int(addr2 ++, data2 ++, 1)) {
            break;
        }
        num_values ++;
    }
    return (num_values);
}

/**
 * @brief       Non-intrusive debug write transaction.
 */
template<unsigned int BUSWIDTH>
inline unsigned int
amba_pv_memory<BUSWIDTH>::debug_write(int socket_id,
                                      const sc_dt::uint64 & addr,
                                      unsigned char *data,
                                      unsigned int length,
                                      const amba_pv_control *ctrl) {
    unsigned int num_values = 0;
    sc_dt::uint64 addr2 = addr;
    unsigned char * data2 = data;

    while (num_values < length) {
        if (! write_int(addr2 ++, data2 ++, 1)) {
            break;
        }
        num_values ++;
    }
    return (num_values);
}

/**
 * @brief       Requests DMI access to the specified address and returns a
 *              reference to a DMI descriptor.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_memory<BUSWIDTH>::get_direct_mem_ptr(int socket_id,
                                             tlm::tlm_command command,
                                             const sc_dt::uint64 & addr,
                                             const amba_pv_control * ctrl,
                                             tlm::tlm_dmi & dmi_data) {
    typename std::map<sc_dt::uint64, unsigned char *>::iterator i;
    unsigned char * page;
    sc_dt::uint64 addr_page = addr & ~sc_dt::uint64(m_page_size - 1);

    if (addr >= this->get_addr_limit()) {
        return false;
    }
    dmi_data.set_start_address(addr_page);
    dmi_data.set_end_address(dmi_data.get_start_address() + m_page_size - 1);
    dmi_data.allow_read_write();
    if ((i = m_pages.find(addr_page)) != m_pages.end()) {
        page = (* i).second;
    } else {
        if (command == tlm::TLM_READ_COMMAND) {

            /* Read only: 1) provide with uninitialised page */
            page = m_empty_page;
            dmi_data.allow_read();
        } else if (command == tlm::TLM_WRITE_COMMAND) {

            /* Write: 1) invalidate possible previous DMI pointer to the RO
             *           page...*/
            amba_pv_s->invalidate_direct_mem_ptr(dmi_data.get_start_address(),
                                                 dmi_data.get_end_address());

            /*        2) allocate new page */
            page = new unsigned char[m_page_size];
            std::memcpy(page, m_empty_page, m_page_size);
            m_pages[addr_page] = page;
        } else {

            /* Unknown command! */
            return false;
        }
    }
    dmi_data.set_dmi_ptr(page);
    return true;
}

/*
 * Clear this memory.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_memory<BUSWIDTH>::clear() {
    typename std::map<sc_dt::uint64, unsigned char *>::iterator i;

    for (i = m_pages.begin(); (i != m_pages.end()); i ++) {
        if ((* i).second != NULL) {
            delete [] (* i).second;
        }
    }
    m_pages.clear();
}

/*
 * Internal read.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_memory<BUSWIDTH>::read_int(const sc_dt::uint64 & addr,
                                   unsigned char * data,
                                   unsigned int size) {
    sc_dt::uint64 aa = addr & ~sc_dt::uint64(size - 1); /* Aligned address */

    if ((aa + size) > this->get_addr_limit()) {
        return false;
    }

    sc_dt::uint64 addr_page = aa & ~sc_dt::uint64(m_page_size - 1);
        /* Page address */
    typename std::map<sc_dt::uint64, unsigned char *>::iterator i;
    unsigned char * page = NULL;

    if ((i = m_pages.find(addr_page)) != m_pages.end()) {
        page = (* i).second;
    } else {
        page = m_empty_page;
    }

    unsigned int offset_page =
        static_cast<unsigned int>(aa & (m_page_size - 1)); /* Offset in page */

    std::memcpy(data, page + offset_page, size);
    return true;
} 

/*
 * Internal write.
 */
template<unsigned int BUSWIDTH>
inline bool
amba_pv_memory<BUSWIDTH>::write_int(const sc_dt::uint64 & addr,
                                    unsigned char * data,
                                    unsigned int size) {
    sc_dt::uint64 aa = addr & ~sc_dt::uint64(size - 1); /* Aligned address */
    
    if ((aa + size) > this->get_addr_limit()) {
        return false;
    }

    sc_dt::uint64 addr_page = aa & ~sc_dt::uint64(m_page_size - 1);
        /* Page address */
    typename std::map<sc_dt::uint64, unsigned char *>::iterator i;
    unsigned char * page;

    if ((i = m_pages.find(addr_page)) != m_pages.end()) {

        /* Page exists... */
        page = (* i).second;
    } else {
            
        /* 1) Invalidate possible previous DMI pointer to the page...*/
        amba_pv_s->invalidate_direct_mem_ptr(addr_page,
                                             addr_page + m_page_size - 1);

        /* 2) Create page... */
        page = new unsigned char[m_page_size];
        std::memcpy(page, m_empty_page, m_page_size);
        m_pages[addr_page] = page;
    }

    unsigned int offset_page =
        static_cast<unsigned int>(aa & (m_page_size - 1)); /* Offset in page */

    std::memcpy(page + offset_page, data, size);
    return true;
}

/*
 * Internal save single value.
 */
template<unsigned int BUSWIDTH>
template<typename T>
inline void
amba_pv_memory<BUSWIDTH>::save_val(std::ostream & os, const T & v) {
    os << std::hex << std::setfill('0') << std::setw(2 * sizeof(T))
       << std::noshowbase << v << std::endl;
}

/*
 * Internal restore single value.
 */
template<unsigned int BUSWIDTH>
template<typename T>
inline void
amba_pv_memory<BUSWIDTH>::restore_val(std::istream & is, T & v) {
    is >> std::hex >> v;
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_MEMORY__H) */
