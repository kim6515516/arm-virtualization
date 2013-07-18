/*
 * AMBA-PV: amba_pv_extension.h - AMBA-PV extension class.
 *
 * Copyright 2007-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_EXTENSION__H
#define AMBA_PV_EXTENSION__H

/**
 * @file        amba_pv_extension.h
 *
 * @brief       AMBA-PV extension class.
 */

/* Includes */
#include "core/amba_pv_types.h"
#include "bus/amba_pv_control.h"
#include "bus/amba_pv_dvm.h"
#include "bus/amba_pv_response.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief     Burst type.
 *
 * The burst type, together with the size information, determines how the
 * address for each transfer within the burst is calculated.
 *
 * @note        AMBA-PV does not support undefined-length bursts.
 *
 * @see         amba_pv_extension
 */
enum amba_pv_burst_t {
    AMBA_PV_FIXED = 0,  /**< is a fixed-address burst. */
    AMBA_PV_INCR,       /**< is an incrementing-address burst. */
    AMBA_PV_WRAP        /**< is an incrementing-address burst that wraps to a
                         * lower address at the wrap boundary. */
};


/**
 * @brief       AMBA-PV extension class.
 *
 * The amba_pv_extension class extends @c tlm::tlm_extension by providing
 * support for AMBA&nbsp;4 buses specific addressing options and additional
 * control information.
 *
 * The addressing options provided by the AMBA&nbsp;4 buses include:
 * - burst length, from 1 to 256 data transfers per burst
 * - burst transfer size of 8-1024 bits
 * - wrapping, incrementing, and non-incrementing burst types.
 *
 * The additional control information provided by the AMBA&nbsp;4 buses
 * includes:
 * - system-level caching and buffering control
 * - secure and privileged access
 * - atomic operations, using exclusive or locked accesses.
 *
 * The AMBA-PV extension must be used with AMBA-PV sockets, that is, sockets
 * parameterized with the amba_pv_protocol_types traits class.
 * This follows the rules set out in the section "Define a new protocol traits
 * class containg a typedef for tlm_generic_payload" of the <em>TLM 2.0 Language
 * Reference Manual</em>.
 * The AMBA-PV extension is a mandatory extension for the modelling of
 * AMBA&nbsp;4 buses.
 * For more information, see the section "Non-ignorable amd mandatory
 * extensions", <em>TLM 2.0 Language Reference Manual</em>.
 *
 * @see         amba_pv_master_socket, amba_pv_slave_socket
 */
class amba_pv_extension:
    public tlm::tlm_extension<amba_pv_extension>,
    public amba_pv_control,
    public amba_pv_dvm {

    /* Construction */
    public:
        amba_pv_extension();
        amba_pv_extension(unsigned int,
                          const amba_pv_control *);
        amba_pv_extension(unsigned int,
                          unsigned int,
                          const amba_pv_control *,
                          amba_pv_burst_t);

    /* Copying */
        virtual tlm::tlm_extension_base * clone() const;
        virtual void copy_from(tlm::tlm_extension_base const &);

    /* Accessors */

        /* Burst length support */
        void set_length(unsigned int);
        unsigned int get_length() const;

        /* Burst size support */
        void set_size(unsigned int);
        unsigned int get_size() const;

        /* Burst type support */
        void set_burst(amba_pv_burst_t);
        amba_pv_burst_t get_burst() const;

        /* Response */
        void set_resp(amba_pv_resp_t);
        amba_pv_resp_t get_resp() const;

        /* Normal access response */
        bool is_okay() const;
        void set_okay();

        /* Exclusive access response */
        bool is_exokay() const;
        void set_exokay();

        /* Slave error response */
        bool is_slverr() const;
        void set_slverr();

        /* Decoder error response */
        bool is_decerr() const;
        void set_decerr();

        /* PassDirty read and snoop response bit */
        bool is_pass_dirty() const;
        void set_pass_dirty(bool /* dirty */ =true);

        /* IsShared read and snoop response bit */
        bool is_shared() const;
        void set_shared(bool /* shared */=true);

        /* DataTransfer snoop response bit */
        bool is_snoop_data_transfer() const;
        void set_snoop_data_transfer(bool /* data_transfer */=true);

        /* Error snoop response bit */
        bool is_snoop_error() const;
        void set_snoop_error(bool /* error */=true);

        /* WasUnique snoop response bit */
        bool is_snoop_was_unique() const;
        void set_snoop_was_unique(bool /* was_unique */=true);

        /* Combined response status */
        amba_pv_response* get_response();

        /* Response arrays */
        void set_response_array_ptr(amba_pv_response*);
        amba_pv_response* get_response_array_ptr();
        void set_response_array_complete(bool /*complete*/=true);
        bool is_response_array_complete() const;

        /* Resetting */
        void reset();
        void reset(unsigned int,
                   const amba_pv_control *);
        void reset(unsigned int,
                   unsigned int,
                   const amba_pv_control *,
                   amba_pv_burst_t);

    /* Implementation */
    private:

        /* Variable members */
        unsigned int m_length;
        unsigned int m_size;
        amba_pv_burst_t m_burst;
        amba_pv_response   m_response;
        amba_pv_response*  m_response_array;
        bool               m_response_array_complete;
};

/* Functions */

/**
 * @brief       Returns the text string representation of the specified burst
 *              type.
 *
 * @param       burst burst type as one of @c AMBA_PV_FIXED, @c AMBA_PV_INCR,
 *              or @c AMBA_PV_WRAP.
 *
 * @return      the text string representation of @a burst.
 */
inline std::string
amba_pv_burst_string(amba_pv_burst_t burst) {
    switch (burst) {
        case AMBA_PV_FIXED:
            return "AMBA_PV_FIXED";
        case AMBA_PV_INCR:
            return "AMBA_PV_INCR";
        case AMBA_PV_WRAP:
            return "AMBA_PV_WRAP";
        default:
            return "AMBA_PV_UNKNOWN";
    };
}

/**
 * @brief       Computes the address of a transfer in a burst.
 *
 * @param       addr burst address.
 * @param       length burst length.
 * @param       size burst size in bytes.
 * @param       burst burst type as one of @c AMBA_PV_FIXED, @c AMBA_PV_INCR,
 *              or @c AMBA_PV_WRAP.
 * @param       n burst beat number as in [0 .. (@a length - 1)].
 */
inline sc_dt::uint64
amba_pv_address(const sc_dt::uint64 & addr,
                unsigned int length,
                unsigned int size,
                amba_pv_burst_t burst,
                unsigned int n) {
    sc_dt::uint64 a = addr;

    if ((burst != AMBA_PV_FIXED) && (n > 0)) {
        a = (addr & ~sc_dt::uint64(size - 1)) + n * size;
        if (burst == AMBA_PV_WRAP) {
            sc_dt::uint64 wrap_boundary = addr & ~sc_dt::uint64((size * length) - 1);

            if (a >= (wrap_boundary | sc_dt::uint64((size * length) - 1))) {
                a = wrap_boundary + (a & sc_dt::uint64((size * length) - 1));
            }
        }
    }
    return (a);
}

/**
 * @brief       Default constructor.
 *
 * By default:
 * - the burst length is initialized to 1
 * - the burst size is initialized to 8
 * - the burst type is initialized to @c AMBA_PV_INCR
 * - the response is initialized to @c AMBA_PV_OKAY.
 */
inline
amba_pv_extension::amba_pv_extension():
    m_length(1),
    m_size(8),
    m_burst(AMBA_PV_INCR),
    m_response(AMBA_PV_OKAY),
    m_response_array(0),
    m_response_array_complete(false) {
}

/**
 * @brief       Constructor for read and write transactions.
 *
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
 *              64, 128].
 * @param       ctrl optional AMBA&nbsp;4 control information (set to @c NULL if
 *              unused).
 */
inline
amba_pv_extension::amba_pv_extension(unsigned int size,
                                     const amba_pv_control * ctrl):
    m_length(1),
    m_size(size),
    m_burst(AMBA_PV_INCR),
    m_response(AMBA_PV_OKAY),
    m_response_array(0),
    m_response_array_complete(false) {
    if (ctrl != NULL) {
        amba_pv_control::operator=(* ctrl);
    }
}

/**
 * @brief       Constructor for burst read and write transactions.
 *
 * @param       length transaction burst length as in [1-256].
 * @param       size transaction burst size in bytes as one of [1, 2, 4, 8, 16,
 *              32, 64, 128].
 * @param       ctrl optional AMBA&nbsp;4 control information (set to @c NULL if
 *              unused).
 * @param       burst transaction burst type as one of @c AMBA_PV_INCR,
 *              @c AMBA_PV_FIXED, @c AMBA_PV_WRAP.
 */
inline
amba_pv_extension::amba_pv_extension(unsigned int length,
                                     unsigned int size,
                                     const amba_pv_control * ctrl,
                                     amba_pv_burst_t burst):
    m_length(length),
    m_size(size),
    m_burst(burst),
    m_response(AMBA_PV_OKAY),
    m_response_array(0),
    m_response_array_complete(false) {
    if (ctrl != NULL) {
        amba_pv_control::operator=(* ctrl);
    }
}

/**
 * @brief       Returns a copy of this extension.
 */
inline tlm::tlm_extension_base *
amba_pv_extension::clone() const {
    return (new amba_pv_extension(* this));
}

/**
 * @brief       Copy this extension from a specified one.
 *
 * copy_from() assumes that the specified extension @a ext is of the same type
 * as this one.
 *
 * @param       ext extention to copy from.
 */
inline void
amba_pv_extension::copy_from(tlm::tlm_extension_base const &ext) {
    sc_assert(ID == static_cast<amba_pv_extension const &>(ext).ID);
    operator =(static_cast<amba_pv_extension const &>(ext));
}

/**
 * @brief       Sets the number of data transfers that occur within this
 *              burst.
 *
 * Each burst can be between 1 and 256 transfers long.
 *
 * @param       length number of data transfers as in [1-256].
 *
 * @see         get_length()
 */
inline void
amba_pv_extension::set_length(unsigned int length) {
    m_length = length;
}

/**
 * @brief       Returns the number of data transfers that occur within this
 *              burst.
 *
 * @see         set_length()
 */
inline unsigned int
amba_pv_extension::get_length() const {
    return (m_length);
}

/**
 * @brief       Sets the maximum number of data bytes to transfer in each
 *              beat, or data transfer, within a burst.
 *
 * @param       size bytes in each transfer as one of [1, 2, 4, 8, 16, 32, 64,
 *              128].
 *
 * @see         get_size()
 */
inline void
amba_pv_extension::set_size(unsigned int size) {
    m_size = size;
}

/**
 * @brief       Returns the maximum number of data bytes to transfer in each
 *              beat, or data transfer, within a burst.
 *
 * @see         set_size()
 */
inline unsigned int
amba_pv_extension::get_size() const {
    return (m_size);
}

/**
 * @brief       Specifies the burst type.
 *
 * @param       burst burst type as one of @c AMBA_PV_FIXED, @c AMBA_PV_INCR,
 *              or @c AMBA_PV_WRAP.
 *
 * @see         get_burst()
 */
inline void
amba_pv_extension::set_burst(amba_pv_burst_t burst) {
    m_burst = burst;
}

/**
 * @brief       Returns the burst type.
 *
 * @see         set_burst()
 */
inline amba_pv_burst_t
amba_pv_extension::get_burst() const {
    return (m_burst);
}

/**
 * @brief       Sets this transaction response.
 *
 * @param       resp transaction response.
 *
 * @see         get_resp(), set_okay(), set_exokay(), set_slverr(), set_decerr(), set_pass_dirty(), set_shared()
 */
inline void
amba_pv_extension::set_resp(amba_pv_resp_t resp) {
    m_response.set_resp(resp);
}

/**
 * @brief       Returns this transaction response.
 *
 * @see         set_resp(), is_okay(), is_exokay(), is_slverr(), is_decerr(), is_pass_dirty(), is_shared()
 */
inline amba_pv_resp_t
amba_pv_extension::get_resp() const {
    return m_response.get_resp();
}

/**
 * @brief       Returns wether or not the @c OKAY response is set.
 *
 * The @c OKAY reponse indicates if a normal access has been successful. It
 * indicates also an exclusive access failure. 
 *
 * @return      @c true if the @c OKAY response is set, @c false otherwise.
 *
 * @see         set_okay()
 */
inline bool
amba_pv_extension::is_okay() const {
    return m_response.is_okay();
}

/**
 * @brief       Sets the @c OKAY response.
 * 
 * @see         is_okay(), set_pass_dirty(), set_shared()
 */
inline void
amba_pv_extension::set_okay() {
    m_response.set_okay();
}

/**
 * @brief       Returns wether or not the response is @c EXOKAY.
 *
 * If @c true, the @c EXOKAY response indicates that either the read or write
 * portion of an exclusive access has been successful. 
 *
 * @return      @c true if the response is @c EXOKAY, @c false otherwise.
 *
 * @see         set_exokay(), is_pass_dirty(), is_shared()
 */
inline bool
amba_pv_extension::is_exokay() const {
    return m_response.is_exokay();
}

/**
 * @brief       Sets the @c EXOKAY response.
 *
 * The PassDirty and IsShared response flags will be cleared.
 *
 * @see         is_exokay(), set_pass_dirty(), set_shared()
 */
inline void
amba_pv_extension::set_exokay() {
    m_response.set_exokay();
}

/**
 * @brief       Returns wether or not the response is @c SLVERR.
 *
 * The @c SLVERR response is used if the access has reached the slave successfully,
 * but the slave returned an error condition to the originating master.
 *
 * @return      @c true if the response is @c SLVERR, @c false otherwise.
 *
 * @see         set_slverr()
 */
inline bool
amba_pv_extension::is_slverr() const {
    return m_response.is_slverr();
}

/**
 * @brief       Sets the @c SLVERR response.
 *
 * @see         is_slverr()
 */
inline void
amba_pv_extension::set_slverr() {
    m_response.set_slverr();
}

/**
 * @brief       Returns wether or not the response is @c DECERR.
 *
 * The @c DECERR response is generated typically by an interconnect component to
 * indicate that there is no slave at the transaction address.
 *
 * @return      @c true if the response is @c DECERR, @c false otherwise.
 *
 * @see         set_decerr()
 */
inline bool
amba_pv_extension::is_decerr() const {
    return m_response.is_decerr();
}

/**
 * @brief       Sets the @c DECERR response.
 *
 * @see         is_decerr()
 */
inline void
amba_pv_extension::set_decerr() {
    m_response.set_decerr();
}

/**
 * @brief       Returns wether or not the @c PassDirty response bit is set.
 *
 * The @c PassDirty response bit indicates the cache line is dirty with respect
 * to main memory. For AMBA-PV ACE this bit is a part of both read and snoop
 * responses.
 *
 * @return      @c true if the @c PassDirty bit is set, @c false otherwise.
 *
 * @see         set_pass_dirty(), set_okay(), set_exokay()
 */
inline bool
amba_pv_extension::is_pass_dirty() const {
    return m_response.is_pass_dirty();
}

/**
 * @brief       Sets the @c PassDirty response bit.
 *
 * The @c PassDirty response bit indicates the cache line is dirty with respect
 * to main memory. For AMBA-PV ACE this bit is a part of both read and snoop
 * responses.
 *
 * @param       pass_dirty status of @c PassDirty bit
 *
 * @see         is_pass_dirty(), is_okay(), is_exokay()
 */
inline void
amba_pv_extension::set_pass_dirty(bool pass_dirty /* = true */ ) {
    m_response.set_pass_dirty(pass_dirty);
}

/**
 * @brief       Returns wether or not the @c IsShared response bit is set.
 *
 * The @c IsShared response bit hints that another copy of the data might be held
 * in another cache. For AMBA-PV ACE this bit is a part of both read and snoop
 * responses.
 *
 * @return      @c true if the @c IsShared bit is set, @c false otherwise.
 *
 * @see         set_shared(), set_okay(), set_exokay()
 */
inline bool
amba_pv_extension::is_shared() const {
    return m_response.is_shared();
}

/**
 * @brief       Sets the @c IsShared response bit.
 *
 * The @c IsShared response bit hints that another copy of the data might be held
 * in another cache. For AMBA-PV ACE this bit is a part of both read and snoop
 * responses.
 *
 * @param       is_shared status of @c IsShared bit
 *
 * @see         is_shared(), is_okay(), is_exokay()
 */
inline void
amba_pv_extension::set_shared(bool is_shared /* = true */) {
    m_response.set_shared(is_shared);
}

/**
 * @brief       Returns wether or not the @c DataTransfer snoop response bit is set.
 *
 * The @c DataTransfer response bit indicates that a full cache line of data will be
 * provided on the snoop data channel for this transaction.
 *
 * @return      @c true if the @c DataTransfer bit is set, @c false otherwise.
 *
 * @see         set_snoop_data_transfer()
 */
inline bool
amba_pv_extension::is_snoop_data_transfer() const {
    return m_response.is_snoop_data_transfer();
}

/**
 * @brief       Sets the @c DataTransfer snoop response bit.
 *
 * The @c DataTransfer response bit indicates that a full cache line of data will be
 * provided on the snoop data channel for this transaction.
 *
 * @param       data_transfer status of @c DataTransfer bit
 *
 * @see         is_snoop_data_transfer()
 */
inline void
amba_pv_extension::set_snoop_data_transfer(bool data_transfer/* = true */ ) {
    m_response.set_snoop_data_transfer(data_transfer);
}

/**
 * @brief       Returns wether or not the @c Error snoop response bit is set.
 *
 * The @c Error response bit indicates that the snooped cache line is in error.
 *
 * @return      @c true if the @c Error bit is set, @c false otherwise.
 *
 * @see         set_snoop_error()
 */
inline bool
amba_pv_extension::is_snoop_error() const {
    return m_response.is_snoop_error();
}

/**
 * @brief       Sets the @c Error snoop response bit.
 *
 * The @c Error response bit indicates that the snooped cache line is in error.
 *
 * @param       error status of @c Error bit
 *
 * @see         is_snoop_error()
 */
inline void
amba_pv_extension::set_snoop_error(bool error/* = true */ ) {
    m_response.set_snoop_error(error);
}

/**
 * @brief       Returns wether or not the @c WasUnique snoop response bit is set.
 *
 * The @c WasUnique bit indicates that the cache line was held in a Unique state
 * before the snoop.
 *
 * @return      @c true if the @c WasUnique bit is set, @c false otherwise.
 *
 * @see         set_snoop_was_unique()
 */
inline bool
amba_pv_extension::is_snoop_was_unique() const {
    return m_response.is_snoop_was_unique();
}

/**
 * @brief       Sets the @c WasUnique snoop response bit.
 *
 * The @c WasUnique bit indicates that the cache line was held in a Unique state
 * before the snoop.
 *
 * @param       was_unique status of @c WasUnique bit
 *
 * @see         is_snoop_was_unique()
 */
inline void
amba_pv_extension::set_snoop_was_unique(bool was_unique/* = true */) {
    m_response.set_snoop_was_unique(was_unique);
}

/**
 * @brief       Get combined response.
 *
 * Get a pointer to the transaction response object. 
 *
 * @see         get_response_array_ptr()
 */
inline amba_pv_response*
amba_pv_extension::get_response() {
    return &m_response;
}

/**
 * @brief       Set response array pointer.
 *
 * Used by masters to supply a response array for burst transaction
 * responses. The size of the array must match the burst length set by
 * set_length(). Use of the response array by a slave is optional.
 *
 * @param       response_array_ptr response array pointer
 *
 * @see         get_response_array_ptr(), set_length()
 */
inline void
amba_pv_extension::set_response_array_ptr(amba_pv_response* response_array_ptr) {
    m_response_array = response_array_ptr;
    if (m_response_array == (amba_pv_response*)0)
    {
        m_response_array_complete = false;
    }
}

/**
 * @brief       Get response array pointer.
 *
 * Get the response array pointer for burst transactions. If the response
 * array pointer is not null, then the size of the array will match the burst
 * length returned by get_length(). Use of the response array by a slave is
 * optional, but if a slave does use the response array then the slave
 * should set_response_array_complete() when all the array elements have been
 * assigned.
 *
 * @see         set_response_array_ptr(), get_length(), set_response_array_complete()
 */
inline amba_pv_response*
amba_pv_extension::get_response_array_ptr() {
    return m_response_array;
}

/**
 * @brief       Indicate whether the response array has been completed.
 *
 * A slave should use this method when all the response array elements have been
 * assigned.
 *
 * @param       complete @c true response array has been completed
 *
 * @see         get_response_array_complete(), get_response_array_ptr()
 */
inline void
amba_pv_extension::set_response_array_complete(bool complete) {
    if (m_response_array == 0)
    {
        m_response_array_complete = false;
    }
    else
    {
        m_response_array_complete = complete;
    }
}

/**
 * @brief       Indicates whether a slave has used the response array to return a response.
 *
 * A master should use this method to determine the correct source for a transaction
 * response. If this method returns @c true then the get_resp() method should not be used to
 * determine the transaction response and the responses stored in the response array
 * should be used instead.
 *
 * @see         set_response_array_complete(), get_response_array_ptr()
 */
inline bool 
amba_pv_extension::is_response_array_complete() const {
    return m_response_array_complete;
}


/**
 * @brief       Resets all members of this AMBA-PV extension to their default
 *              value.
 */
inline void
amba_pv_extension::reset() {
    m_length = 1;
    m_size = 8;
    m_burst = AMBA_PV_INCR;
    m_response.reset();
    amba_pv_control::reset();
    amba_pv_dvm::reset();
}

/**
 * @brief       Resets all members of this AMBA-PV extension for read and write
 *              transactions.
 *
 * @param       size transaction size in bytes as one of [1, 2, 4, 8, 16, 32,
 *              64, 128].
 * @param       ctrl optional AMBA&nbsp;4 control information (set to @c NULL if
 *              unused).
 */
inline void
amba_pv_extension::reset(unsigned int size,
                         const amba_pv_control * ctrl) {
    m_length = 1;
    m_size = size;
    m_burst = AMBA_PV_INCR;
    m_response.reset();
    if (ctrl != NULL) {
        amba_pv_control::operator=(* ctrl);
    }
    else
       amba_pv_control::reset();
    amba_pv_dvm::reset();
}

/**
 * @brief       Resets all members of this AMBA-PV extension for burst read and
 *              write transactions.
 *
 * @param       length transaction burst length as in [1-256].
 * @param       size transaction burst size in bytes as one of [1, 2, 4, 8, 16,
 *              32, 64, 128].
 * @param       ctrl optional AMBA&nbsp;4 control information (set to @c NULL if
 *              unused).
 * @param       burst transaction burst type as one of @c AMBA_PV_INCR,
 *              @c AMBA_PV_FIXED, @c AMBA_PV_WRAP.
 */
inline void
amba_pv_extension::reset(unsigned int length,
                         unsigned int size,
                         const amba_pv_control * ctrl,
                         amba_pv_burst_t burst) {
    m_length = length;
    m_size = size;
    m_burst = burst;
    m_response.reset();
    if (ctrl != NULL) {
        amba_pv_control::operator=(* ctrl);
    }
    else
       amba_pv_control::reset();
    amba_pv_dvm::reset();
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_EXTENSION__H) */
