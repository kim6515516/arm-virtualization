/*
 * AMBA-PV: amba_pv_control.h - AMBA-PV additional control information.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_CONTROL__H
#define AMBA_PV_CONTROL__H

/**
 * @file        amba_pv_control.h
 *
 * @brief       AMBA-PV additional control information.
 */

/* Includes */
#if defined(AMBA_PV_INCLUDE_ATTRIBUTES)
    #include "bus/amba_pv_attributes.h"
#endif  /* defined(AMBA_PV_INCLUDE_ATTRIBUTES) */

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief     Snoop type.
 *
 * The snoop type, together with the barrier and domain information, determines the
 * transaction type for the extended transactions on coherent buses.
 *
 * The bit representation of this type matches the AxSNOOP AMBA4 signals.
 *
 * @see         amba_pv_control, amba_pv_domain_t, amba_pv_bar_t
 */
enum amba_pv_snoop_t {
    AMBA_PV_READ_NO_SNOOP         = 0x0, /**<  Read transaction for non-shareable memory */

    AMBA_PV_READ_ONCE             = 0x0, /**<  Read transaction for shareable memory, when local caching is not
                                               required */
    AMBA_PV_READ_CLEAN            = 0x2, /**<  Read transaction for shareable memory, that requires a clean copy of a
                                               cache line */

    AMBA_PV_READ_NOT_SHARED_DIRTY = 0x3, /**<  Read transaction for shareable memory, can accept the cache line
                                               in any state except SharedDirty */

    AMBA_PV_READ_SHARED           = 0x1, /**<  Read transaction for shareable memory, can accept the cache line
                                               in any state */

    AMBA_PV_READ_UNIQUE           = 0x7, /**<  Read transaction for shareable memory, ensures that cache line is
                                               held in a Unique state */

    AMBA_PV_CLEAN_UNIQUE          = 0xB, /**<  Cache clean operation, ensures the cache line is held in a Unique state */

    AMBA_PV_CLEAN_SHARED          = 0x8, /**<  Broadcast cache clean operation */

    AMBA_PV_CLEAN_INVALID         = 0x9, /**<  Broadcast cache clean and invalidate operation */


    AMBA_PV_MAKE_UNIQUE           = 0xC, /**<  Cache invalidate operation, ensures the cache line is held in a
                                               Unique state */
    AMBA_PV_MAKE_INVALID          = 0xD, /**<  Broadcast cache invalidate operation */


    AMBA_PV_WRITE_NO_SNOOP        = 0x0, /**<  Write transaction for non-shareable memory. */

    AMBA_PV_WRITE_UNIQUE          = 0x0, /**<  Write transaction for shareable memory that will must propogate to main
                                               memory. */

    AMBA_PV_WRITE_LINE_UNIQUE     = 0x1, /**<  Shareable write transaction that must propogate to main memory. 
                                               A full cache line store of all bytes within the cache line must
                                               be updated. */

    AMBA_PV_WRITE_BACK            = 0x3, /**<  Write transaction can be used in shareable and non-shareable regions
                                               of memory and is a write of a dirty cache line to update main
                                               memory. For a shareable region of memory the cache line is no
                                               longer allocated. */

    AMBA_PV_WRITE_CLEAN           = 0x2, /**<  Write transaction can be used in shareable and non-shareable regions
                                               of memory and is a write of a dirty cache line to update main
                                               memory. For a shareable region of memory the cache line remains
                                               allocated. */


    AMBA_PV_EVICT                 = 0x4, /**<  Indicates that a cache line has been evicted from a master's local
                                               cache. Must only be used in a shareable memory region and only
                                               used by a master that supports a snoop filer. */

    AMBA_PV_BARRIER               = 0x0, /**<  ACE barrier transactions */


    AMBA_PV_DVM_COMPLETE          = 0xE, /**<  DVM complete transaction */

    AMBA_PV_DVM_MESSAGE           = 0xF  /**<  DVM operation or DVM sync transactions */
};


/**
 * @brief     Domain type.
 *
 * The domain type indicates the level of shareablility.
 *
 * The bit representation of this type matches the AxDOMAIN AMBA4 signals.
 *
 * @see         amba_pv_control, amba_pv_snoop_t
 */
enum amba_pv_domain_t {
    AMBA_PV_NON_SHAREABLE   = 0x0,  /**< The domain contains a single master */
    AMBA_PV_INNER_SHAREABLE = 0x1,  /**< The inner domain can include additional masters */
    AMBA_PV_OUTER_SHAREABLE = 0x2,  /**< The outer domain contains all masters in the inner domain and can include
                                         additonal masters */
    AMBA_PV_SYSTEM          = 0x3   /**< The system domain include all masters in the system */
};


/**
 * @brief     Barrier type.
 *
 * The barrier type indicates the type for barraier transactions and the response to barriers for normal accesses.
 *
 * The bit representation of this type matches the AxBAR AMBA4 signals.
 *
 * @see         amba_pv_control, amba_pv_snoop_t
 */
enum amba_pv_bar_t {
    AMBA_PV_RESPECT_BARRIER          = 0x0,  /**< Normal access, respecting barriers */
    AMBA_PV_MEMORY_BARRIER           = 0x1,  /**< Memory barrier */
    AMBA_PV_IGNORE_BARRIER           = 0x2,  /**< Normal access, ignoring barriers */
    AMBA_PV_SYNCHRONISATION_BARRIER  = 0x3   /**< Synchronisation barrier */
};


/**
 * @brief       Provides support for additional control information used by the
 *              AMBA buses.
 *
 * The additional control information provided by the AMBA buses
 * includes:
 * - system-level caching and buffering control
 * - secure and privileged access
 * - atomic operations, using exclusive or locked accesses.
 * - quaility of service indication
 * - multiple region support
 * - coherency support
 * - barrier transactions
 * - distributed virtual memory (DVM) support
 *
 * This class is used as a base class for the AMBA-PV extension type
 * (amba_pv_extension).
 *
 * @see         amba_pv_extension
 */
#if defined(AMBA_PV_INCLUDE_ATTRIBUTES)
class amba_pv_control:
    public amba_pv_attributes {
#else
class amba_pv_control {
#endif  /* defined(AMBA_PV_INCLUDE_ATTRIBUTES) */

    /* Construction */
    public:
        amba_pv_control();

    /* Accessors */

        /* ID */
        void set_id(unsigned int);
        unsigned int get_id() const;

        /* Secure and privileged access */
        void set_privileged(bool /* privileged */ = true);
        bool is_privileged() const;
        void set_non_secure(bool /* non_secure */ = true);
        bool is_non_secure() const;
        void set_instruction(bool /* instruction */ = true);
        bool is_instruction() const;

        /* Atomic operations */
        void set_exclusive(bool /* exclusive */ = true);
        bool is_exclusive() const;
        void set_locked(bool /* locked */ = true);
        bool is_locked() const;

        /* System-level caching and buffering control */
        void set_bufferable(bool /* bufferable */ = true);
        bool is_bufferable() const;
        void set_cacheable(bool /* cacheable */ = true);
        bool is_cacheable() const;
        void set_read_allocate(bool /* allocate */ = true);
        bool is_read_allocate() const;
        void set_write_allocate(bool /* allocate */ = true);
        bool is_write_allocate() const;

        /* Extensions and changes to system-level caching and buffering control (AXI4) */
        void set_modifiable(bool /* modifiable */ = true);
        bool is_modifiable() const;
        void set_read_other_allocate(bool /* other_allocate */ = true);
        bool is_read_other_allocate() const;
        void set_write_other_allocate(bool /* other_allocate */ = true);
        bool is_write_other_allocate() const;

        /* Quality of Service (AXI4) */
        void set_qos(unsigned int);
        unsigned int get_qos() const;

        /* Multiple region signalling (AXI4) */
        void set_region(unsigned int);
        unsigned int get_region() const;

        /* User signalling (AXI4) */
        void set_user(unsigned int);
        unsigned int get_user() const;

        /* System-level coherency (ACE) */
        void set_snoop(amba_pv_snoop_t);
        amba_pv_snoop_t get_snoop() const;
        void set_domain(amba_pv_domain_t);
        amba_pv_domain_t get_domain() const;
        void set_bar(amba_pv_bar_t);
        amba_pv_bar_t get_bar() const;

        /* Resetting */
        void reset();

    /* Implementation */
    private:

        /* Variable members */
        unsigned int m_id;
        bool m_privileged;
        bool m_non_secure;
        bool m_instruction;
        bool m_exclusive;
        bool m_locked;
        bool m_bufferable;
        bool m_modifiable;
        bool m_axcache_allocate_bit2;
        bool m_axcache_allocate_bit3;
        unsigned int m_qos;
        unsigned int m_region;
        unsigned int m_user;
        amba_pv_snoop_t m_snoop;
        amba_pv_domain_t m_domain;
        amba_pv_bar_t m_bar;
};

/* Functions */

/**
 * @brief       Returns the text string representation of the specified 
 *              read snoop type.
 *
 * The additional arguments help disambiguate aliased enumerations.
 *
 * @param       snoop read transaction snoop type 
 * @param       domain the domain for the transaction
 * @param       bar the bar type for the transaction
 *
 * @return      the text string representation of @a snoop.
 */
inline std::string
amba_pv_snoop_read_string(amba_pv_snoop_t snoop,
                          amba_pv_domain_t domain,
                          amba_pv_bar_t bar) {
    switch (snoop) {
        case AMBA_PV_READ_NO_SNOOP:
            if ((bar == AMBA_PV_MEMORY_BARRIER)||
                (bar == AMBA_PV_SYNCHRONISATION_BARRIER))
                return "AMBA_PV_BARRIER";
            if ((domain == AMBA_PV_INNER_SHAREABLE)||
                (domain == AMBA_PV_OUTER_SHAREABLE))
                return "AMBA_PV_READ_ONCE";
            else
                return "AMBA_PV_READ_NO_SNOOP";
        case AMBA_PV_READ_SHARED:
            return "AMBA_PV_READ_SHARED";
        case AMBA_PV_READ_CLEAN:
            return "AMBA_PV_READ_CLEAN";
        case AMBA_PV_READ_NOT_SHARED_DIRTY:
            return "AMBA_PV_READ_NOT_SHARED_DIRTY";
        case AMBA_PV_EVICT:
            return "AMBA_PV_EVICT";
        case AMBA_PV_READ_UNIQUE:
            return "AMBA_PV_READ_UNIQUE";
        case AMBA_PV_CLEAN_SHARED:
            return "AMBA_PV_CLEAN_SHARED";
        case AMBA_PV_CLEAN_INVALID:
            return "AMBA_PV_CLEAN_INVALID";
        case AMBA_PV_CLEAN_UNIQUE:
            return "AMBA_PV_CLEAN_UNIQUE";
        case AMBA_PV_MAKE_UNIQUE:
            return "AMBA_PV_MAKE_UNIQUE";
        case AMBA_PV_MAKE_INVALID:
            return "AMBA_PV_MAKE_INVALID";
        case AMBA_PV_DVM_COMPLETE:
            return "AMBA_PV_DVM_COMPLETE";
        case AMBA_PV_DVM_MESSAGE:
            return "AMBA_PV_DVM_MESSAGE";
        default:
            return "AMBA_PV_UNKNOWN";
    };
}

/**
 * @brief       Returns the text string representation of the specified 
 *              snoop type for write transactions.
 *
 * The additional arguments help disambiguate aliased enumerations.
 *
 * @param       snoop write transaction snoop type 
 * @param       domain the domain for the transaction
 * @param       bar the bar type for the transaction
 *
 * @return      the text string representation of @a snoop.
 */
inline std::string
amba_pv_snoop_write_string(amba_pv_snoop_t snoop,
                           amba_pv_domain_t domain,
                           amba_pv_bar_t bar) {
    switch (snoop) {
        case AMBA_PV_WRITE_NO_SNOOP:
            if ((bar == AMBA_PV_MEMORY_BARRIER)||
                (bar == AMBA_PV_SYNCHRONISATION_BARRIER))
                return "AMBA_PV_BARRIER";
            if ((domain == AMBA_PV_INNER_SHAREABLE)||
                (domain == AMBA_PV_OUTER_SHAREABLE))
                return "AMBA_PV_WRITE_UNIQUE";
            else
                return "AMBA_PV_WRITE_NO_SNOOP";
        case AMBA_PV_WRITE_LINE_UNIQUE:
            return "AMBA_PV_WRITE_LINE_UNIQUE";
        case AMBA_PV_WRITE_CLEAN:
            return "AMBA_PV_WRITE_CLEAN";
        case AMBA_PV_WRITE_BACK:
            return "AMBA_PV_WRITE_BACK";
        case AMBA_PV_EVICT:
            return "AMBA_PV_EVICT";
        default:
            return "AMBA_PV_UNKNOWN";
    };
}

/**
 * @brief       Returns the text string representation of the specified domain
 *              type.
 *
 * @param       domain domain type 
 *
 * @return      the text string representation of @a domain.
 */
inline std::string
amba_pv_domain_string(amba_pv_domain_t domain) {
    switch (domain) {
        case AMBA_PV_NON_SHAREABLE:
            return "AMBA_PV_NON_SHAREABLE";
        case AMBA_PV_INNER_SHAREABLE:
            return "AMBA_PV_INNER_SHAREABLE";
        case AMBA_PV_OUTER_SHAREABLE:
            return "AMBA_PV_OUTER_SHAREABLE";
        case AMBA_PV_SYSTEM:
            return "AMBA_PV_SYSTEM";
        default:
            return "AMBA_PV_UNKNOWN";
    };
}

/**
 * @brief       Returns the text string representation of the specified bar 
 *              type.
 *
 * @param       bar bar transaction type 
 *
 * @return      the text string representation of @a bar.
 */
inline std::string
amba_pv_bar_string(amba_pv_bar_t bar) {
    switch (bar) {
        case AMBA_PV_RESPECT_BARRIER:
            return "AMBA_PV_RESPECT_BARRIER";
        case AMBA_PV_MEMORY_BARRIER:
            return "AMBA_PV_MEMORY_BARRIER";
        case AMBA_PV_IGNORE_BARRIER:
            return "AMBA_PV_IGNORE_BARRIER";
        case AMBA_PV_SYNCHRONISATION_BARRIER:
            return "AMBA_PV_SYNCHRONISATION_BARRIER";
        default:
            return "AMBA_PV_UNKNOWN";
    };
}


/**
 * @brief       Default constructor.
 */
inline
amba_pv_control::amba_pv_control():
    m_id(0),
    m_privileged(false),
    m_non_secure(false),
    m_instruction(false),
    m_exclusive(false),
    m_locked(false),
    m_bufferable(false),
    m_modifiable(false),
    m_axcache_allocate_bit2(false),
    m_axcache_allocate_bit3(false),
    m_qos(0),
    m_region(0),
    m_user(0),
    m_snoop(AMBA_PV_READ_NO_SNOOP),
    m_domain(AMBA_PV_NON_SHAREABLE),
    m_bar(AMBA_PV_RESPECT_BARRIER) {
}

/**
 * @brief       Sets the ID for this transaction.
 *
 * This is the identification tag for this transaction. It is mainly used for:
 * - exclusive access
 * - out-of-order transaction processing (not relevant at PV level)
 *
 * This ID is set by the master originating the transaction.
 * The interconnect must modify the transfer ID to ensure its uniqueness
 * accross all its masters before passing the transaction to the addressed
 * slave.
 *
 * @param       id transfer ID.
 *
 * @see         get_id()
 */
inline void
amba_pv_control::set_id(unsigned int id) {
    m_id = id;
}

/**
 * @brief       Returns the ID for this transaction.
 *
 * @see         set_id()
 */
inline unsigned int
amba_pv_control::get_id() const {
    return (m_id);
}

/**
 * @brief       Sets whether this transaction is privileged or not.
 *
 * This enables masters to indicate their processing mode. A privileged
 * transaction typically has a greater level of access within the system.
 *
 * @param       privileged @c true for a privileged transaction, @c false
 *              otherwise.
 *
 * @see         is_privileged()
 */
inline void
amba_pv_control::set_privileged(bool privileged /* = true */) {
    m_privileged = privileged;
}

/**
 * @brief       Indicates whether or not this transaction is privileged.
 *
 * @return      @c true for a privileged transaction, @c false otherwise.
 *
 * @see         set_privileged()
 */
inline bool
amba_pv_control::is_privileged() const {
    return (m_privileged);
}

/**
 * @brief       Sets this transaction as secure or non-secure.
 *
 * This enables differentiating between secure and non-secure transactions.
 *
 * @param       non_secure @c true for a non-secure transaction, @c false
 *              otherwise.
 *
 * @note        This flag is initialized to @c false, so that the transaction
 *              is considered as secure by default.
 *
 * @see         is_non_secure()
 */
inline void
amba_pv_control::set_non_secure(bool non_secure /* = true */) {
    m_non_secure = non_secure;
}

/**
 * @brief       Indicates whether or not this transaction is non-secure.
 *
 * @return      @c true for a non-secure transaction, @c false otherwise.
 *
 * @see         set_non_secure()
 */
inline bool
amba_pv_control::is_non_secure() const {
    return (m_non_secure);
}

/**
 * @brief       Sets whether this transaction is an instruction or a data
 *              transaction.
 *
 * @param       instruction @c true for an instruction transaction, @c false
 *              otherwise.
 *
 * @note        This flag is initialized to @c false, so that the transaction
 *              is marked as a data transaction unless it is specifically known
 *              to be an instruction transaction.
 *
 * @see         is_instruction()
 */
inline void
amba_pv_control::set_instruction(bool instruction /* = true */) {
    m_instruction = instruction;
}

/**
 * @brief       Indicates whether this transaction is an instruction or a data
 *              transaction.
 *
 * @return      @c true for an instruction transaction, @c false otherwise.
 *
 * @see         set_instruction()
 */
inline bool
amba_pv_control::is_instruction() const {
    return (m_instruction);
}

/**
 * @brief       Sets whether or not this transaction is an exclusive
 *              transaction.
 *
 * @param       exclusive @c true for an exclusive transaction, @c false
 *              otherwise.
 *
 * @note        This flag must not be @c true if is_locked() returned
 *              @c true.
 *
 * @see         is_exclusive(), is_locked()
 */
inline void
amba_pv_control::set_exclusive(bool exclusive /* = true */) {
    m_exclusive = exclusive;
}

/**
 * @brief       Indicates whether or not this transaction is an exclusive
 *              transaction.
 *
 * @return      @c true for an exclusive transaction, @c false otherwise.
 *
 * @see         set_exclusive()
 */
inline bool
amba_pv_control::is_exclusive() const {
    return (m_exclusive);
}

/**
 * @brief       Sets whether or not this transaction is locked. 
 *
 * @param       locked @c true for a locked transaction, @c false otherwise.
 *
 * @note        Locked transactions require that the interconnect prevents any
 *              other transactions occurring while the locked sequence is in
 *              progress and can therefore have an impact on the interconnect
 *              performance. It is recommended that locked accesses are only
 *              used to support legacy devices.
 *
 * @note        This flag must not be @c true if is_exclusive() returned
 *              @c true.
 *
 * @see         is_locked(), is_exclusive()
 */
inline void
amba_pv_control::set_locked(bool locked /* = true */) {
    m_locked = locked;
}

/**
 * @brief       Indicates whether or not this transaction is locked.
 *
 * @return      @c true for a locked transaction, @c false otherwise.
 *
 * @see         set_locked()
 */
inline bool
amba_pv_control::is_locked() const {
    return (m_locked);
}

/**
 * @brief       Sets whether or not this transaction is bufferable.
 *
 * A bufferable transaction can be delayed in reaching its final destination.
 * This is usually only relevant to writes.
 *
 * @param       bufferable @c true for a bufferable transaction, @c false
 *              otherwise.
 *
 * @see         is_bufferable()
 */
inline void
amba_pv_control::set_bufferable(bool bufferable /* = true */) {
    m_bufferable = bufferable;
}

/**
 * @brief       Indicates whether or not this transaction is bufferable.
 *
 * @return      @c true for a bufferable transaction, @c false otherwise.
 *
 * @see         set_bufferable()
 */
inline bool
amba_pv_control::is_bufferable() const {
    return (m_bufferable);
}

/**
 * @brief       Sets whether or not this transaction is cacheable.
 *
 * For writes, a number of different writes can be merged together. For reads,
 * a location can be pre-fetched or can be fetched just once for multiple read
 * transactions. To determine if a transaction must be cached, use this flag
 * with the set_read_allocate() and set_write_allocate() flags.
 *
 * @param       cacheable @c true for a cacheable transaction, @c false
 *              otherwise.
 *
 * @see         is_cacheable(), set_read_allocate(), set_write_allocate(),
 *              set_modifiable()
 */
inline void
amba_pv_control::set_cacheable(bool cacheable /* = true */) {
    m_modifiable = cacheable;
}

/**
 * @brief       Indicates whether or not this transaction is cacheable.
 *
 * @return      @c true for a cacheable transaction, @c false otherwise.
 *
 * @see         set_cacheable(), is_modifiable()
 */
inline bool
amba_pv_control::is_cacheable() const {
    return m_modifiable;
}

/**
 * @brief       Sets whether or not this transaction is modifiable. (AXI4)
 *
 * If a transaction is modifiable it can be broken into multiple transactions,
 * and multiple transactions can be merged into a single transaction. A read
 * transaction can fetch more data than required. But the exclusivity and
 * protection attributes cannot be modified.
 *
 * @note The modifiable flag is the same as the cacheable flag but has been
 *       renamed for AXI4 to better describe the required functionality.
 *
 * @param       modifiable @c true for a cacheable transaction, @c false
 *              otherwise.
 *
 * @see         is_modifiable(), set_read_allocate(), set_write_allocate(),
 *              set_cacheable()
 */
inline void
amba_pv_control::set_modifiable(bool modifiable /* = true */) {
    m_modifiable = modifiable;
}

/**
 * @brief       Indicates whether or not this transaction is modifiable. (AXI4)
 *
 * @note The modifiable flag is the same as the cacheable flag but has been
 *       renamed for AXI4 to better describe the required functionality.
 *
 * @return      @c true for a modifiable transaction, @c false otherwise.
 *
 * @see         set_modifiable(), is_cacheable()
 */
inline bool
amba_pv_control::is_modifiable() const {
    return m_modifiable;
}

/**
 * @brief       Sets the Allocate signal for read transactions.
 *
 * When asserted the transaction must be looked up in a cache because
 * it could have been previously allocated. If asserted it is also recommended
 * that the transaction is allocated in the cache for performance reasons.
 *
 * @param       allocate @c true to assert, @c false to deassert
 *
 * @note        This flag must not be @c true if is_modifiable() returned
 *              @c false.
 *
 * @see         is_read_allocate(), set_read_other_allocate()
 */
inline void
amba_pv_control::set_read_allocate(bool allocate /* = true */) {
    m_axcache_allocate_bit2 = allocate;
}

/**
 * @brief       Gets the status of the Allocate signal for read transactions
 *
 * When asserted the transaction must be looked up in a cache because
 * it could have been previously allocated. If asserted it is also recommended
 * that the transaction is allocated in the cache for performance reasons.
 *
 * @return      @c true the signal is asserted, @c false deasserted
 *
 * @see         set_read_allocate(), is_read_other_allocate()
 */
inline bool
amba_pv_control::is_read_allocate() const {
    return m_axcache_allocate_bit2;
}

/**
 * @brief       Sets the Allocate signal for write transactions
 *
 * When asserted the transaction must be looked up in a cache because
 * it could have been previously allocated. If asserted it is also recommended
 * that the transaction is allocated in the cache for performance reasons.
 *
 * @param       allocate @c true to assert, @c false to deassert
 *
 * @note        This flag must not be @c true if is_modifiable() returned
 *              @c false.
 *
 * @see         is_write_allocate(), set_write_other_allocate()
 */
inline void
amba_pv_control::set_write_allocate(bool allocate /* = true */) {
    m_axcache_allocate_bit3 = allocate;
}

/**
 * @brief       Gets the status of the Allocate signal for write transactions
 *
 * When asserted the transaction must be looked up in a cache because
 * it could have been previously allocated. If asserted it is also recommended
 * that the transaction is allocated in the cache for performance reasons.
 *
 * @return      @c true the signal is asserted, @c false deasserted
 *
 * @see         set_write_allocate(), is_write_other_allocate()
 */
inline bool
amba_pv_control::is_write_allocate() const {
    return m_axcache_allocate_bit3;
}

/**
 * @brief       Sets the Other Allocate signal for read transactions
 *
 * When asserted the transaction must be looked up in a cache because
 * it could have been previously allocated by a write transaction or 
 * a transaction from another master.
 *
 * @param       other_allocate @c true to assert, @c false to deassert
 *
 * @note        This flag must not be @c true if is_modifiable() returned
 *              @c false.
 *
 * @see         set_read_allocate(), is_read_other_allocate()
 */
inline void
amba_pv_control::set_read_other_allocate(bool other_allocate /* = true */) {
    m_axcache_allocate_bit3 = other_allocate;
}

/**
 * @brief       Gets the status of the Other Allocate signal for read transactions
 *
 * When asserted the transaction must be looked up in a cache because
 * it could have been previously allocated by a write transaction or 
 * or a transaction from another master.
 *
 * @return      @c true the signal is asserted, @c false deasserted
 *
 * @see         set_read_other_allocate(), is_read_allocate()
 */
inline bool
amba_pv_control::is_read_other_allocate() const {
    return m_axcache_allocate_bit3;
}

/**
 * @brief       Sets the Other Allocate signal for write transactions
 *
 * When asserted the transaction must be looked up in a cache because
 * it could have been previously allocated by a read transaction or 
 * or a transaction from another master.
 *
 * @param       other_allocate @c true to assert, @c false to deassert
 *
 * @note        This flag must not be @c true if is_modifiable() returned
 *              @c false.
 *
 * @see         is_write_other_allocate(), set_write_allocate()
 */
inline void
amba_pv_control::set_write_other_allocate(bool other_allocate /* = true */) {
    m_axcache_allocate_bit2 = other_allocate;
}

/**
 * @brief       Gets the status of the Other Allocate signal for write transactions
 *
 * When asserted the transaction must be looked up in a cache because
 * it could have been previously allocated by a read transaction or 
 * or a transaction from another master.
 *
 * @return      @c true the signal is asserted, @c false deasserted
 *
 * @see         set_write_other_allocate(), is_write_allocate()
 */
inline bool
amba_pv_control::is_write_other_allocate() const {
    return m_axcache_allocate_bit2;
}

/**
 * @brief       Sets the QOS bits for this transaction.
 *
 * @param       qos QOS bits
 *
 * @see         get_qos()
 */
inline void
amba_pv_control::set_qos(unsigned int qos) {
    m_qos = qos;
}

/**
 * @brief       Returns the QOS bits for this transaction.
 *
 * @see         set_qos()
 */
inline unsigned int
amba_pv_control::get_qos() const {
    return m_qos;
}

/**
 * @brief       Sets the REGION bits for this transaction.
 *
 * @param       region REGION bits
 *
 * @see         get_region()
 */
inline void
amba_pv_control::set_region(unsigned int region) {
    m_region = region;
}

/**
 * @brief       Returns the REGION bits for this transaction.
 *
 * @see         set_region()
 */
inline unsigned int
amba_pv_control::get_region() const {
    return m_region;
}

/**
 * @brief       Sets the USER bits for this transaction.
 *
 * @param       user USER bits
 *
 * @see         get_user()
 */
inline void
amba_pv_control::set_user(unsigned int user) {
    m_user = user;
}

/**
 * @brief       Returns the USER bits for this transaction.
 *
 * @see         set_user()
 */
inline unsigned int
amba_pv_control::get_user() const {
    return m_user;
}

/**
 * @brief       Sets the snoop type for shareable transactions.
 *
 * @param       snoop transaction type for shareable transactions.
 *
 * @see         get_snoop()
 */
inline void
amba_pv_control::set_snoop(amba_pv_snoop_t snoop) {
    m_snoop = snoop;
}

/**
 * @brief       Returns the snoop type for shareable transactions.
 *
 * @see         set_snoop()
 */
inline amba_pv_snoop_t
amba_pv_control::get_snoop() const {
    return m_snoop;
}

/**
 * @brief       Sets the shareablility domain for this transactions.
 *
 * @param       domain shareability domain.
 *
 * @see         get_domain()
 */
inline void
amba_pv_control::set_domain(amba_pv_domain_t domain) {
    m_domain = domain;
}

/**
 * @brief       Returns the shareablility domain for this transactions.
 *
 * @see         set_domain()
 */
inline amba_pv_domain_t
amba_pv_control::get_domain() const {
    return m_domain;
}

/**
 * @brief       Sets the barrier type for this transaction.
 *
 * @param       bar barrier type.
 *
 * @see         get_bar()
 */
inline void
amba_pv_control::set_bar(amba_pv_bar_t bar) {
    m_bar = bar;
}

/**
 * @brief       Returns the barrier type for this transaction.
 *
 * @see         set_bar()
 */
inline amba_pv_bar_t
amba_pv_control::get_bar() const {
    return m_bar;
}

/**
 * @brief       Resets all members to their default value.
 */
inline void
amba_pv_control::reset() {
#if defined(AMBA_PV_INCLUDE_ATTRIBUTES)
    amba_pv_attributes::clear();
#endif  /* defined(AMBA_PV_INCLUDE_ATTRIBUTES) */
    m_id = 0;
    m_privileged = false;
    m_non_secure = false;
    m_instruction = false;
    m_exclusive = false;
    m_locked = false;
    m_bufferable = false;
    m_modifiable = false;
    m_axcache_allocate_bit2 = false;
    m_axcache_allocate_bit3 = false;
    m_qos = 0;
    m_region = 0;
    m_user = 0;
    m_snoop = AMBA_PV_READ_NO_SNOOP;
    m_domain = AMBA_PV_NON_SHAREABLE;
    m_bar = AMBA_PV_RESPECT_BARRIER;
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_CONTROL__H) */
