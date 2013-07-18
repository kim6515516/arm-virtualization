/*
 * AMBA-PV: amba_pv_dvm.h - AMBA-PV additional information for DVM messages.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_DVM__H
#define AMBA_PV_DVM__H

/**
 * @file        amba_pv_dvm.h
 *
 * @brief       AMBA-PV additional information for DVM messages.
 */

/* Includes */

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief     DVM Message type.
 *
 * The bit representation of this type matches the encoding of the DVM message type field
 * in the AxADDR AMBA4 signal.
 *
 * @see       amba_pv_dvm, amba_pv_dvm_os_t, amba_pv_dvm_security_t
 */
enum amba_pv_dvm_message_t {
    AMBA_PV_TLB_INVALIDATE                        = 0x0, /**< TLB invalidate */
    AMBA_PV_BRANCH_PREDICTOR_INVALIDATE           = 0x1, /**< Branch predictor invalidate */
    AMBA_PV_PHYSICAL_INSTRUCTION_CACHE_INVALIDATE = 0x2, /**< Physical instruction cache invalidate */
    AMBA_PV_VIRTUAL_INSTRUCTION_CACHE_INVALIDATE  = 0x3, /**< Virtual instruction cache invalidate */
    AMBA_PV_SYNC                                  = 0x4, /**< Synchronisation message */
    AMBA_PV_HINT                                  = 0x6  /**< Reserved message type for future Hint messages */
};


/**
 * @brief     DVM message Guest OS or hypervisor type.
 *
 * The bit representation of this type matches the encoding of the DVM guest OS or 
 * hypervisor field in the AxADDR AMBA4 signal.
 *
 * @see       amba_pv_dvm, amba_pv_dvm_message_t, amba_pv_dvm_security_t
 */
enum amba_pv_dvm_os_t {
    AMBA_PV_HYPERVISOR_OR_GUEST = 0x0, /**< Transaction applies to hypervisor and all Guest OS*/
    AMBA_PV_GUEST               = 0x2, /**< Transaction applies to Guest OS */
    AMBA_PV_HYPERVISOR          = 0x3  /**< Transaction applies to hypervisor */
};


/**
 * @brief     DVM message security type.
 *
 * The bit representation of this type matches the encoding of the DVM security field
 * in the AxADDR AMBA4 signal.
 *
 * @see       amba_pv_dvm, amba_pv_dvm_message_t, amba_pv_dvm_os_t
 */
enum amba_pv_dvm_security_t {
    AMBA_PV_SECURE_AND_NON_SECURE = 0x0, /**< Transaction applies to Secure and Non-secure */
    AMBA_PV_SECURE_ONLY           = 0x2, /**< Transaction applies to Secure only */
    AMBA_PV_NON_SECURE_ONLY       = 0x3  /**< Transaction applies to Non-secure only */
};


/**
 * @brief    Provides DVM message information used by the AMBA ACE buses.
 *
 * This class is used as a base class for the AMBA-PV extension type
 * (amba_pv_extension).
 *
 * @see         amba_pv_extension
 */
class amba_pv_dvm{

    /* Construction */
    public:
        amba_pv_dvm();

    /* Accessors */

        /* Encoded transaction */
        void set_dvm_transaction(unsigned int);
        unsigned int get_dvm_transaction() const;

        /* Additional address */
        void set_dvm_additional_address(sc_dt::uint64);
        bool is_dvm_additional_address_set() const;
        sc_dt::uint64 get_dvm_additional_address() const;

        /* VMID */
        void set_dvm_vmid(unsigned int);
        bool is_dvm_vmid_set() const;
        unsigned int get_dvm_vmid() const;

        /* ASID */
        void set_dvm_asid(unsigned int);
        bool is_dvm_asid_set() const;
        unsigned int get_dvm_asid() const;

        /* Virtual Index */
        void set_dvm_virtual_index(unsigned int);
        bool is_dvm_virtual_index_set() const;
        unsigned int get_dvm_virtual_index() const;

        /* Completion */
        void set_dvm_completion(bool /* completion */ = true);
        bool is_dvm_completion_set() const;

        /* Message type */
        void set_dvm_message_type(amba_pv_dvm_message_t);
        amba_pv_dvm_message_t get_dvm_message_type() const;

        /* Guest OS or hypervisor */
        void set_dvm_os(amba_pv_dvm_os_t);
        amba_pv_dvm_os_t get_dvm_os() const;

        /* Security */
        void set_dvm_security(amba_pv_dvm_security_t);
        amba_pv_dvm_security_t get_dvm_security() const;

        /* Resetting */
        void reset();

    /* Implementation */
    private:
        enum {
            VMID_MASK              = 0xFF,
            VMID_LSB               = 24,
            VMID_SET               = 1<<6,
            ASID_MASK              = 0xFF,
            ASID_LSB               = 16,
            ASID_SET               = 1<<5,
            VIRTUAL_INDEX_MASK     = 0xFFFF,
            VIRTUAL_INDEX_LSB      = 16,
            VIRTUAL_INDEX_SET      = (1<<6) | (1<<5),
            TYPE_MASK              = 0x7,
            TYPE_LSB               = 12,
            OS_MASK                = 0x3,
            OS_LSB                 = 10,
            SECURITY_MASK          = 0x3,
            SECURITY_LSB           = 8,
            ADDITIONAL_ADDRESS_SET = 1<<0
        };

        /* Variable members */
        unsigned int   m_dvm_transaction;
        sc_dt::uint64  m_dvm_additional_address;
};

/* Functions */

/**
 * @brief       Returns the text string representation of the specified 
 *              DVM message type.
 *
 * @param       message_type DVM message type 
 *
 * @return      the text string representation of @a message_type.
 */
inline std::string
amba_pv_dvm_message_string(amba_pv_dvm_message_t message_type) {
    switch (message_type) {
        case AMBA_PV_TLB_INVALIDATE:
            return "AMBA_PV_TLB_INVALIDATE";
        case AMBA_PV_BRANCH_PREDICTOR_INVALIDATE:
            return "AMBA_PV_BRANCH_PREDICTOR_INVALIDATE";
        case AMBA_PV_PHYSICAL_INSTRUCTION_CACHE_INVALIDATE:
            return "AMBA_PV_PHYSICAL_INSTRUCTION_CACHE_INVALIDATE";
        case AMBA_PV_VIRTUAL_INSTRUCTION_CACHE_INVALIDATE:
            return "AMBA_PV_VIRTUAL_INSTRUCTION_CACHE_INVALIDATE";
        case AMBA_PV_SYNC:
            return "AMBA_PV_SYNC";
        case AMBA_PV_HINT:
            return "AMBA_PV_HINT";
        default:
            return "AMBA_PV_UNKNOWN";
    };
}

/**
 * @brief       Returns the text string representation of the specified 
 *              DVM Guest OS or hypervisor type.
 *
 * @param       os DVM Guest OS or hypervisor type 
 *
 * @return      the text string representation of @a os.
 */
inline std::string
amba_pv_dvm_os_string(amba_pv_dvm_os_t os) {
    switch (os) {
        case AMBA_PV_HYPERVISOR_OR_GUEST:
            return "AMBA_PV_HYPERVISOR_OR_GUEST";
        case AMBA_PV_GUEST:
            return "AMBA_PV_GUEST";
        case AMBA_PV_HYPERVISOR:
            return "AMBA_PV_HYPERVISOR";
        default:
            return "AMBA_PV_UNKNOWN";
    };
}

/**
 * @brief       Returns the text string representation of the specified 
 *              DVM security type.
 *
 * @param       security DVM security type 
 *
 * @return      the text string representation of @a security.
 */
inline std::string
amba_pv_dvm_security_string(amba_pv_dvm_security_t security) {
    switch (security) {
        case AMBA_PV_SECURE_AND_NON_SECURE:
            return "AMBA_PV_SECURE_AND_NON_SECURE";
        case AMBA_PV_SECURE_ONLY:
            return "AMBA_PV_SECURE_ONLY";
        case AMBA_PV_NON_SECURE_ONLY:
            return "AMBA_PV_NON_SECURE_ONLY";
        default:
            return "AMBA_PV_UNKNOWN";
    };
}

/**
 * @brief       Default constructor.
 */
inline
amba_pv_dvm::amba_pv_dvm() {
     reset();
}

/**
 * @brief       Set the encoded DVM transaction.
 *
 * @param       dvm_transaction DVM transaction, as encoded on AxADDR signal
 *
 * @see         get_dvm_transaction(), set_dvm_additional_address()
 */
inline void
amba_pv_dvm::set_dvm_transaction(unsigned int dvm_transaction) {
    m_dvm_transaction = dvm_transaction;
}

/**
 * @brief       Return the encoded DVM transaction.
 *
 * @see         set_dvm_transaction()
 */
inline unsigned int
amba_pv_dvm::get_dvm_transaction() const {
    return m_dvm_transaction;
}

/**
 * @brief       Set the DVM additional address for this transaction.
 *
 * @see         get_dvm_additional_address(), is_dvm_additional_address_set()
 */
inline void
amba_pv_dvm::set_dvm_additional_address(sc_dt::uint64 additional_address) {
    m_dvm_transaction |= ADDITIONAL_ADDRESS_SET;
    m_dvm_additional_address = additional_address;
}

/**
 * @brief       Indicate whether there is an additional address for this DVM transaction.
 *
 * @see         get_dvm_additional_address(), set_dvm_additional_address()
 */
inline bool
amba_pv_dvm::is_dvm_additional_address_set() const {
    return (m_dvm_transaction & ADDITIONAL_ADDRESS_SET) != 0;
}

/**
 * @brief       Return the DVM additional address for this transaction.
 *
 * @see         set_dvm_additional_address(), is_dvm_additional_address_set()
 */
inline sc_dt::uint64 
amba_pv_dvm::get_dvm_additional_address() const {
    return m_dvm_additional_address;
}

/**
 * @brief       Set the VMID for this DVM transaction.
 *
 * @param       vmid Virtual Machine IDentifier (VMID) [0-255]
 *
 * @see         get_dvm_vmid(), is_dvm_vmid_set()
 */
inline void
amba_pv_dvm::set_dvm_vmid(unsigned int vmid) {
    m_dvm_transaction &= ~(VMID_MASK << VMID_LSB);
    m_dvm_transaction |= ((vmid & VMID_MASK) << VMID_LSB) | VMID_SET;
}

/**
 * @brief       Indicate whether there is a VMID set for this DVM transaction.
 *
 * @see         get_dvm_vmid(), set_dvm_vmid()
 */
inline bool
amba_pv_dvm::is_dvm_vmid_set() const {
    return (m_dvm_transaction & VMID_SET) != 0;
}

/**
 * @brief       Return the VMID for this DVM transaction.
 *
 * @see         set_dvm_vmid(), is_dvm_vmid_set()
 */
inline unsigned int
amba_pv_dvm::get_dvm_vmid() const {
    return (m_dvm_transaction >> VMID_LSB) & VMID_MASK;
}

/**
 * @brief       Set the ASID for this DVM transaction.
 *
 * @param       asid Address Space IDentifier (ASID) [0-255]
 *
 * @see         get_dvm_asid(), is_dvm_asid_set()
 */
inline void
amba_pv_dvm::set_dvm_asid(unsigned int asid) {
    m_dvm_transaction &= ~(ASID_MASK << ASID_LSB);
    m_dvm_transaction |= ((asid & ASID_MASK) << ASID_LSB) | ASID_SET;
}

/**
 * @brief       Indicate whether there is an ASID set for this DVM transaction.
 *
 * @see         get_dvm_asid(), set_dvm_asid()
 */
inline bool
amba_pv_dvm::is_dvm_asid_set() const {
    return (m_dvm_transaction & ASID_SET) != 0;
}

/**
 * @brief       Return the ASID for this DVM transaction.
 *
 * @see         set_dvm_asid(), is_dvm_asid_set()
 */
inline unsigned int
amba_pv_dvm::get_dvm_asid() const {
    return (m_dvm_transaction >> ASID_LSB) & ASID_MASK;
}

/**
 * @brief       Set the Virtual Index for this DVM transaction.
 *
 * @param       virtual_index Virtual index [0-0xFFFF]
 *
 * @see         get_dvm_virtual_index(), is_dvm_virtual_index_set()
 */
inline void
amba_pv_dvm::set_dvm_virtual_index(unsigned int virtual_index) {
    m_dvm_transaction &= ~(VIRTUAL_INDEX_MASK << VIRTUAL_INDEX_LSB);
    m_dvm_transaction |= ((virtual_index & VIRTUAL_INDEX_MASK) << VIRTUAL_INDEX_LSB) | VIRTUAL_INDEX_SET;
}

/**
 * @brief       Indicate whether there is a virtual index set for this DVM transaction.
 *
 * @see         get_dvm_virtual_index(), set_dvm_virtual_index()
 */
inline bool
amba_pv_dvm::is_dvm_virtual_index_set() const {
    return (m_dvm_transaction & VIRTUAL_INDEX_SET) == VIRTUAL_INDEX_SET;
}

/**
 * @brief       Return the virtual index for this DVM transaction.
 *
 * @see         set_dvm_virtual_index(), is_dvm_virtual_index_set()
 */
inline unsigned int
amba_pv_dvm::get_dvm_virtual_index() const {
    return (m_dvm_transaction >> VIRTUAL_INDEX_LSB) & VIRTUAL_INDEX_MASK;
}

/**
 * @brief       Set the message type for this DVM transaction.
 *
 * @param       message_type DVM message type
 *
 * @see         get_dvm_message_type()
 */
inline void
amba_pv_dvm::set_dvm_message_type(amba_pv_dvm_message_t message_type) {
    m_dvm_transaction &= ~(TYPE_MASK << TYPE_LSB);
    m_dvm_transaction |= ((unsigned(message_type) & TYPE_MASK) << TYPE_LSB);
}

/**
 * @brief       Return the message type for this DVM transaction.
 *
 * @see         set_dvm_message_type()
 */
inline amba_pv_dvm_message_t
amba_pv_dvm::get_dvm_message_type() const {
    return amba_pv_dvm_message_t((m_dvm_transaction >> TYPE_LSB) & TYPE_MASK);
}

/**
 * @brief       Set the OS type for this DVM transaction.
 *
 * @param       os guest OS or hypervisor type
 *
 * @see         get_dvm_os()
 */
inline void
amba_pv_dvm::set_dvm_os(amba_pv_dvm_os_t os) {
    m_dvm_transaction &= ~(OS_MASK << OS_LSB);
    m_dvm_transaction |= ((unsigned(os) & OS_MASK) << OS_LSB);
}

/**
 * @brief       Return the OS type for this DVM transaction.
 *
 * @see         set_dvm_os()
 */
inline amba_pv_dvm_os_t
amba_pv_dvm::get_dvm_os() const {
    return amba_pv_dvm_os_t((m_dvm_transaction >> OS_LSB) & OS_MASK);
}

/**
 * @brief       Set the security type for this DVM transaction.
 *
 * @param       security DVM security type
 *
 * @see         get_dvm_security()
 */
inline void
amba_pv_dvm::set_dvm_security(amba_pv_dvm_security_t security) {
    m_dvm_transaction &= ~(SECURITY_MASK << SECURITY_LSB);
    m_dvm_transaction |= ((unsigned(security) & SECURITY_MASK) << SECURITY_LSB);
}

/**
 * @brief       Return the security for this DVM transaction.
 *
 * @see         set_dvm_security()
 */
inline amba_pv_dvm_security_t
amba_pv_dvm::get_dvm_security() const {
    return amba_pv_dvm_security_t((m_dvm_transaction >> SECURITY_LSB) & SECURITY_MASK);
}

/**
 * @brief       Reset DVM message to default value.
 */
inline void
amba_pv_dvm::reset() {
    m_dvm_transaction = 0x00000000;
    m_dvm_additional_address = 0x0;
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_DVM__H) */
