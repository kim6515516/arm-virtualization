/*
 * AMBA-PV: amba_pv_address_map.h - AMBA-PV address mapping information related
 *                                  structures.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_ADDRESS_MAP__H
#define AMBA_PV_ADDRESS_MAP__H

/**
 * @file        amba_pv_address_map.h
 *
 * @brief       AMBA-PV address mapping information related structures.
 */

/* Includes */
#include "core/amba_pv_types.h"
#include <map>
#include <sstream>

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV address region structure.
 */
class amba_pv_address_region {

    /* Construction */
    public:
        amba_pv_address_region(const sc_dt::uint64 &,
                               const sc_dt::uint64 &,
                               const std::string &,
                               int /* rank */ = -1);

    /* Accessors */
        sc_dt::uint64 get_start() const;
        void set_start(const sc_dt::uint64 &);
        sc_dt::uint64 get_end() const;
        void set_end(const sc_dt::uint64 &);
        std::string get_slave_name() const;
        void set_slave_name(const std::string &);
        int get_slave_rank() const;
        void set_slave_rank(int);

    /* Decoding */
        bool decode(const sc_dt::uint64 &) const;

    /* Implementation */
    private:

        /* Member variables */
        sc_dt::uint64 m_start;
        sc_dt::uint64 m_end;
        std::string m_slave_name;
        int m_slave_rank;
};

/**
 * @brief       AMBA-PV address mapping information structure.
 *
 * amba_pv_address_map is typically used to implement address decoding, as in
 * amba_pv_decoder.
 * 
 * @note        The implementation of this class does not make any attempt at
 *              ensuring that AXI or AHB recommendations on minimal address
 *              space allocated to a single slave are met.
 *
 * @see         amba_pv_decoder
 */
class amba_pv_address_map {
        
    /* Typedefs */
    public:
        typedef std::vector<amba_pv_address_region *>::iterator iterator;
        typedef
            std::vector<amba_pv_address_region *>::const_iterator
            const_iterator;
        typedef std::vector<amba_pv_address_region *>::reference reference;
        typedef
            std::vector<amba_pv_address_region *>::const_reference
            const_reference;
        typedef std::vector<amba_pv_address_region *>::size_type size_type;
            
    /* Construction */
        amba_pv_address_map();
        virtual ~amba_pv_address_map();

    /* Accessors */
        void add_region(const sc_dt::uint64 &,
                        const sc_dt::uint64 &,
                        const std::string &,
                        int /* rank */ = -1);
        bool decode(const sc_dt::uint64 &,
                    amba_pv_address_region * &) const;

    /* Vector-like accessors */
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        size_type size() const;
        reference operator[](size_type);
        const_reference operator[](size_type) const;
        reference at(size_type);
        const_reference at(size_type) const;

    /* Copy */
        amba_pv_address_map(const amba_pv_address_map &);
        amba_pv_address_map & operator=(const amba_pv_address_map &);

    /* Implementation */
    private:

        /* Member variables */
        std::vector<amba_pv_address_region *> m_regions;
};

/* Functions - amba_pv_address_region */

/**
 * @brief       Constuctor.
 *
 * @param       start start address of this region.
 * @param       end end address of this region.
 * @param       name name of the associated slave port.
 * @param       rank rank of the associated slave port.
 */
inline
amba_pv_address_region::amba_pv_address_region(const sc_dt::uint64 & start,
                                               const sc_dt::uint64 & end,
                                               const std::string & name,
                                               int rank /* = -1 */):
    m_start(start),
    m_end(end),
    m_slave_name(name),
    m_slave_rank(rank) {
}

/**
 * @brief       Returns the start address of this region.
 */
inline sc_dt::uint64
amba_pv_address_region::get_start() const {
    return (m_start);
}

/**
 * @brief       Sets the start address of this region.
 *
 * @param       start start address of this region.
 */
inline void
amba_pv_address_region::set_start(const sc_dt::uint64 & start) {
    m_start = start;
}

/**
 * @brief       Returns the end address of this region.
 */
inline sc_dt::uint64
amba_pv_address_region::get_end() const {
    return (m_end);
}

/**
 * @brief       Sets the end address of this region.
 *
 * @param       end end address of this region.
 */
inline void
amba_pv_address_region::set_end(const sc_dt::uint64 & end) {
    m_end = end;
}

/**
 * @brief       Returns the name of the slave port associated to this address
 *              region.
 */
inline std::string
amba_pv_address_region::get_slave_name() const {
    return (m_slave_name);
}

/**
 * @brief       Sets the name of the slave port associated to this address
 *              region.
 *
 * @param       name name of the associated slave port.
 */
inline void
amba_pv_address_region::set_slave_name(const std::string & name) {
    m_slave_name = name;
}

/**
 * @brief       Returns the rank of the slave port associated to this address
 *              region.
 */
inline int
amba_pv_address_region::get_slave_rank() const {
    return (m_slave_rank);
}

/**
 * @brief       Sets the rank of the slave port associated to this address
 *              region.
 *
 * @param       rank rank of the associated slave port.
 */
inline void
amba_pv_address_region::set_slave_rank(int rank) {
    m_slave_rank = rank;
}

/**
 * @brief       Returns whether the specified address @a a is decoded by this
 *              address region.
 *
 * @param       a address to decode.
 *
 * @return      @c true if this region decodes the given address @a a,
 *              @c false otherwise.
 */
inline bool
amba_pv_address_region::decode(const sc_dt::uint64 & a) const {
    return ((a >= m_start) && (a <= m_end));
}

/* Functions - amba_pv_address_map */

/**
 * @brief       Default constuctor.
 */
inline
amba_pv_address_map::amba_pv_address_map() {
}

/**
 * @brief       Destuctor.
 */
inline
amba_pv_address_map::~amba_pv_address_map() {
    for (iterator i = m_regions.begin(); (i != m_regions.end()); i ++) {
        delete (* i);
    }
}

/**
 * @brief       Returns whether the specified address @a a is decoded by this
 *              address map.
 *
 * @param       a address to decode.
 * @param       r pointer to the memory address region that decodes the given
 *              address @a a.
 *
 * @return      @c true if this address map contains a region that decodes the
 *              given address @a a, @c false otherwise.
 */
inline bool
amba_pv_address_map::decode(const sc_dt::uint64 & a,
                            amba_pv_address_region * & r) const {
    for (const_iterator i = m_regions.begin();
         (i != m_regions.end());
         i ++) {
        if ((* i)->decode(a)) {
            r = (* i);
            return true;
        }
    }
    return false;
}

/**
 * @brief       Add a memory region to this address map.
 *
 * @param       start start address of this memory region.
 * @param       end end address of this memory region.
 * @param       name name of the associated slave port.
 * @param       rank rank of the associated slave port.
 */
inline void
amba_pv_address_map::add_region(const sc_dt::uint64 & start,
                                const sc_dt::uint64 & end,
                                const std::string & name,
                                int rank /* = -1 */) {
    amba_pv_address_region * r = NULL;

    /* Check for overlapping regions */
    if ((decode(start, r)) || (decode(end, r))) {
        std::stringstream msg;

        msg << std::showbase << std::hex
            << "add_region(): overlapping address spaces of 2 regions: "
            << "region \"" << name << "\": " << start << ".." << end
            << ", region \"" << r->get_slave_name() << "\": "
            << r->get_start() << ".." << r->get_end();
        SC_REPORT_ERROR("amba_pv_address_map", msg.str().c_str());
    }

    /* Create new region and add it to the map */
    r = new amba_pv_address_region(start, end, name, rank);
    m_regions.push_back(r);
}

/**
 * @brief       Returns an iterator that can be used to begin traversing this
 *              map.
 */
inline std::vector<amba_pv_address_region *>::iterator
amba_pv_address_map::begin() {
    return (m_regions.begin());
}

/**
 * @brief       Returns an iterator that can be used to begin traversing this
 *              map.
 */
inline std::vector<amba_pv_address_region *>::const_iterator
amba_pv_address_map::begin() const {
    return (m_regions.begin());
}

/**
 * @brief       Returns an iterator that can be used in a comparison for
 *              ending traversal through this map.
 */
inline std::vector<amba_pv_address_region *>::iterator
amba_pv_address_map::end() {
    return (m_regions.end());
}

/**
 * @brief       Returns an iterator that can be used in a comparison for
 *              ending traversal through this map.
 */
inline std::vector<amba_pv_address_region *>::const_iterator
amba_pv_address_map::end() const {
    return (m_regions.end());
}

/**
 * @brief       Returns the number of address regions currently stored in this
 *              map.
 */
inline std::vector<amba_pv_address_region *>::size_type
amba_pv_address_map::size() const {
    return (m_regions.size());
}

/**
 * @brief       Returns the address region of specified index @a n from the
 *              beginning of this map in constant time.
 *
 * @param       n index of the address region to return (zero-based).
 */
inline std::vector<amba_pv_address_region *>::reference
amba_pv_address_map::operator[](size_type n) {
    return (m_regions[n]);
}

/**
 * @brief       Returns the address region of specified index @a n from the
 *              beginning of this map in constant time.
 *
 * @param       n index of the address region to return (zero-based).
 */
inline std::vector<amba_pv_address_region *>::const_reference
amba_pv_address_map::operator[](size_type n) const {
    return (m_regions[n]);
}

/**
 * @brief       Returns the address region of specified index @a n from the
 *              beginning of this map in constant time.
 *
 * Bounds checking is performed.
 *
 * @param       n index of the address region to return (zero-based).
 */
inline std::vector<amba_pv_address_region *>::reference
amba_pv_address_map::at(size_type n) {
    return (m_regions.at(n));
}

/**
 * @brief       Returns the address region of specified index @a n from the
 *              beginning of this map in constant time.
 *
 * Bounds checking is performed.
 *
 * @param       n index of the address region to return (zero-based).
 */
inline std::vector<amba_pv_address_region *>::const_reference
amba_pv_address_map::at(size_type n) const {
    return (m_regions.at(n));
}

/**
 * @brief       Copy constuctor.
 *
 * @param       map reference to another address map.
 */
inline
amba_pv_address_map::amba_pv_address_map(const amba_pv_address_map & map) {
    for (const_iterator i = map.begin(); (i != map.end()); i ++) {
        m_regions.push_back(new amba_pv_address_region(* (* i)));
    }
}

/**
 * @brief       Copy assignement.
 *
 * @param       map reference to another address map.
 */
inline amba_pv_address_map &
amba_pv_address_map::operator=(const amba_pv_address_map & map) {
    if (this != & map) {
        for (iterator i = m_regions.begin(); (i != m_regions.end()); i ++) {
            delete (* i);
        }
        m_regions.clear();
        for (const_iterator j = map.begin(); (j != map.end()); j ++) {
            m_regions.push_back(new amba_pv_address_region(* (* j)));
        }
    }
    return (* this);
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_ADDRESS_MAP__H) */
