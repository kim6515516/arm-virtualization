/*
 * AMBA-PV: amba_pv_protocol_checker_base.h - AMBA-PV protocol checker base model.
 *
 * Copyright 2009-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_PROTOCOL_CHECKER_BASE__H
#define AMBA_PV_PROTOCOL_CHECKER_BASE__H

/**
 * @file        amba_pv_protocol_checker_base.h
 *
 * @brief       AMBA-PV protocol checker base model.
 */

/* Includes */
#include "bus/amba_pv_extension.h"
#include <map>

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Typedefs */

/**
 * @brief     AMBA procotol checks type.
 *
 * @see         amba_pv_protocol_checker_base
 */
enum amba_pv_protocol_t {
    AMBA_PV_APB       = 0,    /**< selects checking against the APB protocol. */
    AMBA_PV_AHB       = 1,    /**< selects checking against the AHB protocol. */
    AMBA_PV_AXI       = 2,    /**< selects checking against the AXI3 protocol. (deprecated) */
    AMBA_PV_AXI3      = 2,    /**< selects checking against the AXI3 protocol. */
    AMBA_PV_AXI4_LITE = 3,    /**< selects checking against the AXI4-Lite protocol. */
    AMBA_PV_AXI4      = 4,    /**< selects checking against the AXI4 protocol. */
    AMBA_PV_ACE_LITE  = 5,    /**< selects checking against the ACE-Lite protocol. */
    AMBA_PV_ACE       = 6     /**< selects checking against the ACE protocol. */
};

/* Datatypes */

/**
 * @brief       AMBA-PV protocol checker base model.
 *
 * The amba_pv_protocol_checker_base model is used for confirming that your model
 * complies with the AMBA-PV protocol.
 *
 * You can instantiate the protocol checker between any pair of AMBA-PV master
 * and slave sockets. The transactions that pass through are checked against
 * the AMBA-PV protocol and errors reported using the SystemC reporting
 * mechanism. All errors are reported with a message type of
 * @c "amba_pv_protocol_checker_base" and with a severity of @c SC_ERROR.
 * Recommendations are reported with a severity of @c SC_WARNING.
 *
 * You can configure the the protocol checker to specifically test your model
 * against one of the ACE, AXI, AHB or APB protocols.
 *
 * @note        The AMBA-PV protocol checker model does not perform any OSCI
 *              TLM 2.0 BP checks.
 *
 * @note        The AMBA-PV protocol checker model might have an effect on
 *              performance.
 *
 * @param       BUSWIDTH bus width in bits as one of 8, 16, 32, 64, 128, 256,
 *              512, or 1024. Defaults to 64.
 */
template<unsigned int BUSWIDTH = 64>
class amba_pv_protocol_checker_base: public sc_core::sc_module
{
public:
    /* Construction */
    explicit amba_pv_protocol_checker_base(const sc_core::sc_module_name &,
                                           bool recommend_on,
                                           amba_pv_protocol_t protocol);
    virtual ~amba_pv_protocol_checker_base();

    /* sc_object overridables */
    virtual const char * kind() const;

    /* Accessors */
    void recommend_on(bool /* recommend_on */ = true);
    virtual void check_protocol(amba_pv_protocol_t protocol);

protected:
    /* Helpers */
    virtual void before_end_of_elaboration();
    void architecture_checks();
    void extension_checks(const amba_pv_extension *);
    void control_checks(const amba_pv_extension *);
    void addressing_checks(const amba_pv_transaction &,
                       const amba_pv_extension *);
    void data_checks(const amba_pv_transaction &,
                     const amba_pv_extension *);
    void response_checks(const amba_pv_transaction &,
                         amba_pv_extension *);
    void check_a_response(const amba_pv_transaction &,
                          const amba_pv_extension *,
                          const amba_pv_response*);
    void exclusive_checks(const amba_pv_transaction &,
                          const amba_pv_extension *);
    void cacheability_checks(const amba_pv_transaction &,
                             const amba_pv_extension *);

    /* Implementation */
private:
        /* Member variables */
    bool m_recommend_on;
    amba_pv_protocol_t m_check_protocol;
    std::map<unsigned int, amba_pv_transaction *> m_exclusive_reads;
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * Constructs a new amba_pv_protocol_checker_base with parameter for configuring
 * recommended rules.
 *
 * @param       name protocol checker name.
 * @param       recommend_on @c true to enable reporting of protocol
 *              recommendations, @c false otherwise.
 * @param       protocol selected AMBA protocol checks as one of
 *              @c AMBA_PV_APB, @c AMBA_PV_AHB, @c AMBA_PV_AXI3, @c AMBA_PV_AXI4_LITE,
 *              @c AMBA_PV_AXI4, @c AMBA_PV_ACE_LITE, @c AMBA_PV_ACE
 *
 * @see         recommend_on()
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_protocol_checker_base<BUSWIDTH>::amba_pv_protocol_checker_base(const sc_core::sc_module_name & name,
                                                                       bool recommend_on,
                                                                       amba_pv_protocol_t protocol):
    sc_module(name),
    m_recommend_on(recommend_on),
    m_check_protocol(protocol)
{} 

/**
 * @brief       Destructor.
 */
template<unsigned int BUSWIDTH>
inline
amba_pv_protocol_checker_base<BUSWIDTH>::~amba_pv_protocol_checker_base() {
    std::map<unsigned int, amba_pv_transaction *>::iterator i;

    for (i = m_exclusive_reads.begin(); (i != m_exclusive_reads.end()); i ++) {
        delete (* i).second;
    }
}

/**
 * @brief       Returns the kind string of this protocol checker.
 */
template<unsigned int BUSWIDTH>
inline const char *
amba_pv_protocol_checker_base<BUSWIDTH>::kind() const  {
  return ("amba_pv_protocol_checker");
}

/**
 * @brief       Enables or disables reporting of protocol recommendations.
 *
 * If @a recommend_on is set to @c false, no recommendations are reported and
 * the following warning is issued:
 * @code
 * Warning: amba_pv_protocol_checker_base: All AMBA-PV recommended rules have been disabled by recommend_on()
 * @endcode
 *
 * @param       recommend_on @c true to enable reporting of recommendations
 *              (default), @c false otherwise.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::recommend_on(bool recommend_on /* = true */) {
    m_recommend_on = recommend_on;
    if (! m_recommend_on) {
        SC_REPORT_WARNING(kind(),
                          "All AMBA-PV recommended rules have been disabled "
                          "by recommend_on()");
    }
}

/**
 * @brief       Selects the AMBA protocol checks to perform.
 *
 * The protocol checker tests your model against the selected AMBA
 * protocol.
 *
 * If @a protocol is set to anything other than @c AMBA_PV_AXI3, transactions are checked against
 * that protocol and the following warning is issued:
 * @code
 * Warning: amba_pv_protocol_checker_base: AMBA_PV_protocol protocol rules have been selected by check_protocol()
 * @endcode
 *
 * Where @c AMBA_PV_protocol is the selected protocol.
 *
 * @param       protocol selected AMBA protocol checks as one of
 *              @c AMBA_PV_APB, @c AMBA_PV_AHB, @c AMBA_PV_AXI3, @c AMBA_PV_AXI4_LITE,
 *              @c AMBA_PV_AXI4, @c AMBA_PV_ACE_LITE, @c AMBA_PV_ACE
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::check_protocol(amba_pv_protocol_t protocol) {
    m_check_protocol = protocol;
    switch (m_check_protocol) {
        case AMBA_PV_APB:
            SC_REPORT_WARNING(kind(),
                              "APB protocol rules have been selected by check_protocol()");
            break;

        case AMBA_PV_AHB:
            SC_REPORT_WARNING(kind(),
                              "AHB protocol rules have been selected by check_protocol()");
            break;

        case AMBA_PV_AXI3:
            break;

        case AMBA_PV_AXI4_LITE:
            SC_REPORT_WARNING(kind(),
                              "AXI4-Lite protocol rules have been selected by check_protocol()");
            break;

        case AMBA_PV_AXI4:
            SC_REPORT_WARNING(kind(),
                              "AXI4 protocol rules have been selected by check_protocol()");
            break;

        case AMBA_PV_ACE_LITE:
            SC_REPORT_WARNING(kind(),
                              "ACE-Lite protocol rules have been selected by check_protocol()");
            break;

        case AMBA_PV_ACE:
            SC_REPORT_WARNING(kind(),
                              "ACE protocol rules have been selected by check_protocol()");
            break;

        default:
            SC_REPORT_ERROR(kind(),
                            "Unrecognised protocol selected in check_protocol()");
            break;
    }
}

/*
 * sc_object overridable.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::before_end_of_elaboration() {
    sc_module::before_end_of_elaboration();
    architecture_checks();
}

/*
 * Performs architecture checks.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::architecture_checks()
{
    switch(m_check_protocol)
    {
    case AMBA_PV_APB:
        if (BUSWIDTH > 32)
        {
            SC_REPORT_ERROR(kind(), "The data bus can be up to 32 bits wide");
        }
        break;

    case AMBA_PV_AHB:
        switch(BUSWIDTH)
        {
        case 32: case 64: case 128: case 256: case 512: case 1024: break;

        case 8:
        case 16:
            SC_REPORT_WARNING(kind(),
                              "Recommended that the minimum data bus width is 32 bits");
            break;

        default:
            SC_REPORT_ERROR(kind(),
                            "The data bus can be 8, 16, 32, 64, 128, 256, 512, or 1024 bits wide");
        }
        break;

    case AMBA_PV_AXI4_LITE:
        switch(BUSWIDTH)
        {
        case 32: case 64: break;

        default:
            SC_REPORT_ERROR(kind(), "The data bus can be 32 or 64 bits wide");
        }
        break;

    case AMBA_PV_AXI3:
    case AMBA_PV_AXI4:
    case AMBA_PV_ACE_LITE:
    case AMBA_PV_ACE:
        switch(BUSWIDTH)
        {
        case 32: case 64: case 128: case 256: case 512: case 1024: break;

        default:
            SC_REPORT_ERROR(kind(),
                            "The data bus can be 32, 64, 128, 256, 512, or 1024 bits wide");
        }
        break;
    }
}

/*
 * Performs extension checks.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::extension_checks(const amba_pv_extension * ex)
{
    // Common checks

    // Check for an extension
    if (ex == NULL)
    {
        SC_REPORT_ERROR(kind(), "The amba_pv_extension pointer cannot be NULL");
        return;
    }

    // Check size
    if (ex->get_size() > (BUSWIDTH / 8))
    {
        SC_REPORT_ERROR(kind(),
                        "The size of any transfer must not exceed the bus "
                        "width of the sockets in the transaction");
    }


    // Bus specific checks
    switch(m_check_protocol)
    {
    case AMBA_PV_APB:
    case AMBA_PV_AXI4_LITE:
        // Check size
        if (ex->get_size() != (BUSWIDTH / 8))
        {
            SC_REPORT_ERROR(kind(),
                            "The size of any transfer must equal the bus width "
                            "of the sockets in the transaction");
        }
        // Check burst length
        if (ex->get_length() > 1)
        {
            SC_REPORT_ERROR(kind(),
                            "All transactions are single transfers");
        }
        break;

    case AMBA_PV_AHB:
        // Check size
        switch (ex->get_size())
        {
        case 1: case 2: case 4: case 8: case 16: case 32: case 64: case 128:
            break;

        default:
            SC_REPORT_ERROR(kind(),
                            "The size of any transfer must be 1, 2, 4, "
                            "8, 16, 32, 64 or 128 bytes");
        }
        // Check burst type and length
        switch(ex->get_burst())
        {
        case AMBA_PV_WRAP:
            switch (ex->get_length())
            {
            case 4: case 8: case 16: break;

            default:
                SC_REPORT_ERROR(kind(),
                                "A transaction with burst type of WRAP must "
                                "have a length of 4, 8 or 16");
            }
            break;

        case AMBA_PV_INCR:
            break; 

        case AMBA_PV_FIXED:
            SC_REPORT_ERROR(kind(), "A burst must have a type INCR or WRAP");
            break;
        }
        break;

    case AMBA_PV_AXI3:
    case AMBA_PV_AXI4:
    case AMBA_PV_ACE_LITE:
    case AMBA_PV_ACE:
        // Check size
        switch (ex->get_size())
        {
        case 1: case 2: case 4: case 8: case 16: case 32: case 64: case 128: break;

        default:
            SC_REPORT_ERROR(kind(),
                            "The size of any transfer must be 1, 2, 4, "
                            "8, 16, 32, 64 or 128 bytes");
        }

        // Check burst type and length
        switch(ex->get_burst())
        {
        case AMBA_PV_WRAP:
            switch(ex->get_length())
            {
            case 2: case 4: case 8: case 16: break;

            default:
                SC_REPORT_ERROR(kind(),
                                "A transaction with burst type of WRAP must "
                                "have a length of 2, 4, 8 or 16");
            }
            break;

        case AMBA_PV_INCR:
        case AMBA_PV_FIXED:
            if ((m_check_protocol == AMBA_PV_AXI3) &&
                ((ex->get_length() < 1) || (ex->get_length() > 16)))
            {
                SC_REPORT_ERROR(kind(), "A transaction can have a burst length 1-16");
            }
            else if ((ex->get_length() < 1) || (ex->get_length() > 256))
            {
                SC_REPORT_ERROR(kind(), "A transaction can have a burst length 1-256");
            }
            break;
        }
        break;
    }
}


/*
 * Performs control checks.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::control_checks(const amba_pv_extension * ex)
{
    // Check for an extension
    if (ex == NULL)
    {
        SC_REPORT_ERROR(kind(), "The amba_pv_extension pointer cannot be NULL");
        return;
    }

    // Bus specific checks
    switch(m_check_protocol)
    {
    case AMBA_PV_APB:
    case AMBA_PV_AHB:
        // Check QoS
        if (ex->get_qos() != 0)
        {
            SC_REPORT_ERROR(kind(),
                            "Quality of Service values are not supported");
        }

        // Check Region
        if (ex->get_region() != 0)
        {
            SC_REPORT_ERROR(kind(), "Region values are not supported");
        }
        break;
    
    case AMBA_PV_AXI3:
    case AMBA_PV_AXI4_LITE:
    case AMBA_PV_AXI4:
    case AMBA_PV_ACE_LITE:
    case AMBA_PV_ACE:
        // Check QoS
        if (ex->get_qos() > 15)
        {
            SC_REPORT_ERROR(kind(),
                            "Quality of Service values can be 0-15");
        }

        // Check Region
        if (ex->get_region() > 15)
        {
            SC_REPORT_ERROR(kind(),
                            "Region values can be 0-15");
        }
        break;
    }
}

/*
 * Performs addressing checks.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::addressing_checks(const amba_pv_transaction & trans,
                                                           const amba_pv_extension * ex)
{
    // Check for an extension
    if (ex == NULL)
    {
        SC_REPORT_ERROR(kind(), "The amba_pv_extension pointer cannot be NULL");
        return;
    }

    sc_dt::uint64 boundary;
    unsigned int total_num_bytes = ex->get_size() * ex->get_length();

    // Bus specific checks
    switch(m_check_protocol)
    {
    case AMBA_PV_APB:
    case AMBA_PV_AXI4_LITE:
        // Check alignment
        if (trans.get_address() & (ex->get_size() - 1))
        {
            SC_REPORT_ERROR(kind(),
                            "All transactions must have an aligned address");
        }
        break;

    case AMBA_PV_AHB:
        // Check alignment
        if (trans.get_address() & (ex->get_size() - 1))
        {
            SC_REPORT_ERROR(kind(),
                            "All transactions must have an aligned address");
        }
        // Check address range of burst
        boundary = (trans.get_address() & ~1023) + 1024;
        if ((trans.get_address() + total_num_bytes) > boundary)
        {
            SC_REPORT_ERROR(kind(), "A burst cannot cross a 1KB boundary");
        }
        break;

    case AMBA_PV_AXI3:
    case AMBA_PV_AXI4:
    case AMBA_PV_ACE_LITE:
    case AMBA_PV_ACE:
        // Check alignment
        if ((ex->get_burst() == AMBA_PV_WRAP) &&
            (trans.get_address() & (ex->get_size() - 1)))
        {
            SC_REPORT_ERROR(kind(),
                        "A transaction with a burst type of WRAP must have an "
                        "aligned address");
        }
        // Check address range of burst
        boundary = (trans.get_address() & ~4095) + 4096;
        if ((trans.get_address() + total_num_bytes) > boundary)
        {
            SC_REPORT_ERROR(kind(), "A burst cannot cross a 4KB boundary");
        }
        break;
    }
}

/*
 * Performs data checks.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::data_checks(const amba_pv_transaction & trans,
                                                     const amba_pv_extension * ex)
{
    // Common checks

    // Check for an extension
    if (ex == NULL)
    {
        SC_REPORT_ERROR(kind(), "The amba_pv_extension pointer cannot be NULL");
        return;
    }

    // Ignore data for AMBA4 DVM messages
    if (ex->get_snoop() == AMBA_PV_DVM_MESSAGE)
    {
        return;
    }

    // Check data length
    if (trans.get_data_length() < (ex->get_size() * ex->get_length()))
    {
        SC_REPORT_ERROR(kind(),
                        "Transaction data length is greater than or equal to the beat "
                        "size times the burst length");
    }

    // Bus specific checks
    switch(m_check_protocol)
    {
    case AMBA_PV_APB:
    case AMBA_PV_AXI4_LITE:
        // Check byte enable
        if (trans.get_byte_enable_ptr() != NULL)
        {
            SC_REPORT_ERROR(kind(),
                            "All transactions must have a NULL byte enable "
                            "pointer");
        }
        break;

    case AMBA_PV_AHB:
        // Check byte enable
        if (trans.get_byte_enable_ptr() != NULL)
        {
            SC_REPORT_ERROR(kind(),
                            "All transactions must have a NULL byte enable "
                            "pointer");
        }
        // Check streaming width
        if ((ex->get_burst() != AMBA_PV_FIXED) &&
            (trans.get_streaming_width() < trans.get_data_length()))
        {
            SC_REPORT_ERROR(kind(),
                            "The streaming width must be greater than or equal "
                            "to the transaction data length");
        }
        break;

    case AMBA_PV_AXI3:
    case AMBA_PV_AXI4:
    case AMBA_PV_ACE_LITE:
    case AMBA_PV_ACE:
        // Check byte enable
        if (trans.is_read() && (trans.get_byte_enable_ptr() != NULL))
        {
            SC_REPORT_ERROR(kind(),
                            "A read transaction must have a NULL byte enable "
                            "pointer");
        }
        if (trans.is_write() && (trans.get_byte_enable_ptr() != NULL) &&
            ((trans.get_byte_enable_length() % ex->get_size()) != 0))
        {
            SC_REPORT_ERROR(kind(),
                            "The byte enable length is a multiple of the transfer "
                            "size for a write transaction");
        }
        // Check streaming width
        if ((ex->get_burst() == AMBA_PV_FIXED) &&
            (trans.get_streaming_width() != ex->get_size()))
        {
            SC_REPORT_ERROR(kind(),
                            "The streaming width is equal to the beat size for "
                            "transactions with burst type of FIXED");
        }
        if ((ex->get_burst() != AMBA_PV_FIXED) &&
            (trans.get_streaming_width() < trans.get_data_length()))
        {
            SC_REPORT_ERROR(kind(),
                            "The streaming width must be greater than or equal "
                            "to the transaction data length");
        }
        break;
    }
}

/*
 * Performs response checks.
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::response_checks(const amba_pv_transaction & trans,
                                                         amba_pv_extension * ex)
{
    // Common checks

    // Check for an extension
    if (ex == NULL)
    {
        SC_REPORT_ERROR(kind(), "The amba_pv_extension pointer cannot be NULL");
        return;
    }

    amba_pv_response* response = ex->get_response_array_ptr();

    if (response != (amba_pv_response*)0)
    {
        switch(m_check_protocol)
        {
        case AMBA_PV_APB:
        case AMBA_PV_AXI4_LITE:
            SC_REPORT_WARNING(kind(), "A response array is not appropriate as all "
                                      "transactions are single transfers");
            break;

        default:
            break;
        }

        if (ex->is_response_array_complete())
        {
           for(unsigned i=0; i < ex->get_length(); i++)
           {
              check_a_response( trans, ex, &response[i] );
           }
           return;
        }
    }

    check_a_response( trans, ex, ex->get_response() );
}


template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::check_a_response(const amba_pv_transaction & trans,
                                                          const amba_pv_extension * ex,
                                                          const amba_pv_response* resp)
{
    // Bus specific checks
    switch(m_check_protocol)
    {
    case AMBA_PV_APB:
    case AMBA_PV_AHB:
        // Check response
        if (resp->is_decerr() || resp->is_exokay())
        {
            SC_REPORT_ERROR(kind(), "A response can be OKAY or SLVERR");
        }
        break;

    case AMBA_PV_AXI4_LITE:
        // Check response
        if (resp->is_exokay())
        {
            SC_REPORT_ERROR(kind(), "An EXOKAY response is not supported");
        }
        break;

    case AMBA_PV_AXI3:
    case AMBA_PV_AXI4:
    case AMBA_PV_ACE_LITE:
    case AMBA_PV_ACE:
        // Check response
        if (resp->is_exokay() && !ex->is_exclusive())
        {
            SC_REPORT_ERROR(kind(),
                            "An EXOKAY response can only be given to an exclusive "
                            "transaction");
        }
        break;
    }
}

/*
 * Performs exclusive access checks
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::exclusive_checks(const amba_pv_transaction & trans,
                                                          const amba_pv_extension * ex)
{
    // Common checks

    // Check for an extension
    if (ex == NULL)
    {
        SC_REPORT_ERROR(kind(), "The amba_pv_extension pointer cannot be NULL");
        return;
    }

    // Bus specific checks
    switch(m_check_protocol)
    {
    case AMBA_PV_APB:
    case AMBA_PV_AXI4_LITE:
        // Check exclusive and locked
        if (ex->is_exclusive() || ex->is_locked())
        {
            SC_REPORT_ERROR(kind(),
                            "A transaction cannot be exclusive or locked");
        }
        break;

    case AMBA_PV_AHB:
        // Check exclusive
        if (ex->is_exclusive())
        {
            SC_REPORT_ERROR(kind(),
                            "A transaction cannot be exclusive");
        }
        break;

    case AMBA_PV_AXI3:
    case AMBA_PV_AXI4:
    case AMBA_PV_ACE_LITE:
    case AMBA_PV_ACE:
        if (m_check_protocol == AMBA_PV_AXI3)
        {
            // Check exclusive and lock
            if (ex->is_exclusive() && ex->is_locked())
            {
                SC_REPORT_ERROR(kind(),
                                "A transaction cannot be exclusive and locked");
            }
            if (m_recommend_on && ex->is_locked())
            {
                SC_REPORT_WARNING(kind(),
                                  "Recommended that locked accesses are only used to "
                                  "support legacy devices");
            }
        }
        else
        {
            // Check lock
            if (ex->is_locked())
            {
                SC_REPORT_ERROR(kind(), "Locked accesses are not supported");
            }
       }

       if (ex->is_exclusive())
       {
           unsigned int total_num_bytes = ex->get_size() * ex->get_length();

           // Check transfer size
           if (total_num_bytes > 128)
           {
               SC_REPORT_ERROR(kind(),
                               "The maximum number of bytes that can be transfered"
                               "in an exclusive burst is 128");
           }
           if ((total_num_bytes != 1) && (total_num_bytes & (total_num_bytes - 1)))
           {
               SC_REPORT_ERROR(kind(),
                               "The number of bytes to be transferred in an exclusive "
                               "access burst must be a power of 2");
           }

           if (m_check_protocol != AMBA_PV_AXI3)
           {
               if (ex->get_length() > 16)
               {
                   SC_REPORT_ERROR(kind(),
                                   "The burst length for an exclusive access must not "
                                   "exceed 16 transfers");
               }
           }

           // Check address
           if (trans.get_address() & (total_num_bytes - 1))
           {
               SC_REPORT_ERROR(kind(),
                               "The address of an exclusive access is aligned to the "
                               "total number of bytes in the transaction");
           }

           if (!m_recommend_on) return;

           std::map<unsigned int, amba_pv_transaction *>::iterator i;
           amba_pv_extension * ex2 = NULL;

           /* Recommended that every exclusive write has an earlier outstanding
            * exclusive read with the same ID */
           if (trans.is_write())
           {
               if ((i = m_exclusive_reads.find(ex->get_id()))
                   == m_exclusive_reads.end())
               {
                   SC_REPORT_WARNING(kind(),
                                     "Recommended that every exclusive write has an "
                                     "earlier outstanding exclusive read with the "
                                     "same ID");
               }
               else
               {
                   (* i).second->get_extension(ex2);
       
                   /* Recommended that the address, size, and length of an exclusive
                    * write with a given ID is the same as the address, size, and
                    * length of the preceding exclusive read with the same ID */
                   if (((* i).second->get_address() != trans.get_address())
                       || (ex2->get_size() != ex->get_size())
                       || (ex2->get_length() != ex->get_length()))
                   {
                       SC_REPORT_WARNING(kind(),
                                         "Recommended that the address, size, and "
                                         "length of an exclusive write with a given "
                                         "ID is the same as the address, size, and "
                                         "length of the preceding exclusive read with "
                                         "the same ID");
                   }
                   delete (* i).second;
                   m_exclusive_reads.erase(i);
               }
           }
           else if (trans.is_read())
           {
               amba_pv_transaction * trans2 = new amba_pv_transaction();
               trans2->deep_copy_from(trans);
               m_exclusive_reads[ex->get_id()] = trans2;
           }
       }
       break;
    }
}

/*
 * Performs cacheability checks
 */
template<unsigned int BUSWIDTH>
inline void
amba_pv_protocol_checker_base<BUSWIDTH>::cacheability_checks(const amba_pv_transaction& trans,
                                                             const amba_pv_extension* ex)
{
    // Common checks

    // Check for an extension
    if (ex == NULL)
    {
        SC_REPORT_ERROR(kind(), "The amba_pv_extension pointer cannot be NULL");
        return;
    }

    // Bus specific checks
    switch(m_check_protocol)
    {
    case AMBA_PV_APB:
    case AMBA_PV_AXI4_LITE:
        // Check cacheable and allocate
        if (ex->is_modifiable() || ex->is_bufferable() ||
            ex->is_write_allocate() || ex->is_read_allocate())
        {
            SC_REPORT_ERROR(kind(),
                            "All transactions are non-cacheable, non-bufferable");
        }
        // Check snoop, domain and bar
        if ((ex->get_snoop()!=AMBA_PV_READ_NO_SNOOP ) ||
            (ex->get_domain()!=AMBA_PV_NON_SHAREABLE) ||
            (ex->get_bar()!=AMBA_PV_RESPECT_BARRIER ))
        {
            SC_REPORT_ERROR(kind(), "Cache coherent transactions are not supported");
        }
        break;

    case AMBA_PV_AHB:
        // Check cacheable and allocate
        if (ex->is_write_allocate() || ex->is_read_allocate())
        {
            SC_REPORT_ERROR(kind(),
                            "Allocate attributes are not supported");
        }
        // Check snoop, domain and bar
        if ((ex->get_snoop()!=AMBA_PV_READ_NO_SNOOP ) ||
            (ex->get_domain()!=AMBA_PV_NON_SHAREABLE) ||
            (ex->get_bar()!=AMBA_PV_RESPECT_BARRIER ))
        {
            SC_REPORT_ERROR(kind(), "Cache coherent transactions are not supported");
        }
        break;

    case AMBA_PV_AXI3:
    case AMBA_PV_AXI4:
        // Check cacheable and allocate
        if (!ex->is_cacheable() &&
            (ex->is_write_allocate() || ex->is_read_allocate()))
        {
            SC_REPORT_ERROR(kind(),
                            "When a transaction is not modifiable then allocate "
                            "attributes are not set");
        }
        // Check snoop, domain and bar
        if ((ex->get_snoop()!=AMBA_PV_READ_NO_SNOOP ) ||
            (ex->get_domain()!=AMBA_PV_NON_SHAREABLE) ||
            (ex->get_bar()!=AMBA_PV_RESPECT_BARRIER ))
        {
            SC_REPORT_ERROR(kind(), "Cache coherent transactions are not supported");
        }
        break;

    case AMBA_PV_ACE:
    case AMBA_PV_ACE_LITE:
        // Check cacheable and allocate
        if (!ex->is_cacheable() &&
            (ex->is_write_allocate() || ex->is_read_allocate()))
        {
            SC_REPORT_ERROR(kind(),
                            "When a transaction is not modifiable then allocate "
                            "attributes are not set");
        }

        // Check snoop, domain and bar
        amba_pv_bar_t    bar    = ex->get_bar();
        amba_pv_snoop_t  snoop  = ex->get_snoop();
        amba_pv_domain_t domain = ex->get_domain();

        if ((bar == AMBA_PV_MEMORY_BARRIER         )||
            (bar == AMBA_PV_SYNCHRONISATION_BARRIER))
        {
            if (snoop != AMBA_PV_BARRIER)
            {
                SC_REPORT_ERROR(kind(),
                                "A barrier transaction must have a "
                                "Barrier transaction type");
            }
        }
        else
        {
            if (trans.is_read())
            {
                switch(snoop)
                {
                case AMBA_PV_READ_NO_SNOOP:
                //case AMBA_PV_READ_ONCE:   (same enumeration as ReadNoSnoop)
                //With both cases there is no restriction on domain
                    break;
 
                case AMBA_PV_READ_SHARED:
                case AMBA_PV_READ_CLEAN:
                case AMBA_PV_READ_NOT_SHARED_DIRTY:
                case AMBA_PV_READ_UNIQUE:
                case AMBA_PV_CLEAN_UNIQUE:
                case AMBA_PV_MAKE_UNIQUE:
                    if (m_check_protocol == AMBA_PV_ACE)
                    {
                        if ((domain != AMBA_PV_INNER_SHAREABLE) &&
                            (domain != AMBA_PV_OUTER_SHAREABLE))
                        {
                             SC_REPORT_ERROR(kind(),
                                             "A coherent transaction must be "
                                             "inner or outer shareable");
                        }
                    }
                    else
                    {
                        SC_REPORT_ERROR(kind(),
                                        "The only permitted coherent transaction type "
                                        "is ReadOnce");
                    }
                    break;

                case AMBA_PV_CLEAN_SHARED:
                case AMBA_PV_CLEAN_INVALID:
                case AMBA_PV_MAKE_INVALID:
                    if (domain == AMBA_PV_SYSTEM)
                    {
                         SC_REPORT_ERROR(kind(),
                                         "A cache maintenance transaction "
                                         "cannot target the system domain");
                    }
                    break;
 
                case AMBA_PV_DVM_COMPLETE:
                case AMBA_PV_DVM_MESSAGE:
                    if ((domain != AMBA_PV_INNER_SHAREABLE) &&
                        (domain != AMBA_PV_OUTER_SHAREABLE))
                    {
                         SC_REPORT_ERROR(kind(),
                                         "A DVM transaction must be "
                                         "inner or outer shareable");
                    }
                    break;

                default:
                    SC_REPORT_ERROR(kind(), "The permitted read transaction groups are "
                                            "Non-snooping, Coherent, Cache maintenance, "
                                            "Barrier and DVM");
                    break;
                }
            }
            else if (trans.is_write())
            {
                switch(snoop)
                {
                case AMBA_PV_WRITE_NO_SNOOP:
                //case AMBA_PV_WRITE_UNIQUE:   (same enumeration as WriteUnqiue)
                //With both cases there is no restriction on domain
                    break;

                case AMBA_PV_WRITE_LINE_UNIQUE:
                    if ((domain != AMBA_PV_INNER_SHAREABLE)&&
                        (domain != AMBA_PV_OUTER_SHAREABLE))
                    {
                        SC_REPORT_ERROR(kind(),
                                        "A coherent transaction must be "
                                        "inner or outer shareable");
                    }
                    break;

                case AMBA_PV_WRITE_CLEAN:
                case AMBA_PV_WRITE_BACK:
                    if (m_check_protocol == AMBA_PV_ACE)
                    {
                        if (domain == AMBA_PV_SYSTEM)
                        {
                            SC_REPORT_ERROR(kind(),
                                            "A WriteClean or WriteBack transaction "
                                            "cannot target the system domain");
                        }
                    }
                    else
                    {
                        SC_REPORT_ERROR(kind(),
                                        "Memory update transactions are not permitted");
                    }
                    break;

                case AMBA_PV_EVICT:
                    if (m_check_protocol == AMBA_PV_ACE)
                    {
                        if ((domain != AMBA_PV_INNER_SHAREABLE) &&
                            (domain != AMBA_PV_OUTER_SHAREABLE))
                        {
                            SC_REPORT_ERROR(kind(),
                                            "An Evict transaction must be "
                                            "inner or outer shareable");
                        }
                    }
                    else
                    {
                        SC_REPORT_ERROR(kind(),
                                        "Memory update transactions are not permitted");
                    }
                    break;

                default:
                    SC_REPORT_ERROR(kind(),
                                    "The permitted transaction groups are "
                                    "Non-snooping, Coherent, Memory update(ACE) "
                                    "and Barrier");
                    break;
                }
            }
        }
        break;
    }
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_PROTOCOL_CHECKER_BASE__H) */
