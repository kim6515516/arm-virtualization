/*!
 * \file    PVBusMaster.h
 * \brief   An interface to allow a component to provide a PVBus master port
 * \date    Copyright 2006-2013 ARM Limited. All rights reserved.
 *
 * This defines mechanisms for generating PVBus transactions.
 */

#ifndef PVBUS_MASTER_H
#define PVBUS_MASTER_H

#include "sg/SGPort.h"
#include "pv/PVTransaction.h"      // for tx data/result etc
#include "pv/TransactionAttributes.h"

namespace pv {

typedef ACE::Payload ACERequest;

/*! An interface that provides the ability to drive simple transactions on
 *  a PVBus port.
 */
class TransactionGenerator
{
public:
    virtual ~TransactionGenerator() {}

    //! Internal function used by bus to tell us when mappings change.
    virtual void invalidateAddressRange(bus_addr_t base, bus_addr_t limit) = 0;


    // Control AXI-specific signal generation for future transactions.
    virtual void setPrivileged(bool priv = true) = 0;    //!< Privileged processing mode.
    virtual void setInstruction(bool instr = true) = 0;  //!< Instruction access (vs data).
    virtual void setNonSecure(bool ns = true) = 0;       //!< Normal-world access (vs secure).
    virtual void setLocked(bool locked = true) = 0;      //!< Locked atomic access.
    virtual void setExclusive(bool excl = true) = 0;     //!< Exclusive atomic access.

    // for internal use only, to support internal code in PL310 model
    virtual void setMemoryAttributes(const MemoryAttributes *attributes) = 0;
    // also internal use for PL310 only
    virtual uint32_t getUserFlags() = 0;
    // also internal use for PL310 only
    virtual void setUserFlags(uint32_t) = 0;

    //! Function to provide an integer value that can be used by a slave to identify the originator of the transaction.
    //! There is no implication that it is intended to be used to mimic the AXI ID field.
    virtual void setMasterID(uint32_t master_id) = 0;    //!< Transaction master ID

    //! Return prefetch hint result of the last transaction (true=prefetch is supported, false=prefetch is not supported).
    //  This is just a hint. Masters have to request the DMI access separately.
    virtual bool getPrefetchHint() = 0;

    // Generate transactions
    virtual bool read(bus_addr_t addr,
                      AccessWidth width,
                      uint32_t *data,
                      bool is_debug) = 0;               //!< Generate a read transaction.

    bool read(bus_addr_t addr,
              AccessWidth width,
              uint32_t *data)
    {
        return read(addr, width, data, false);
    }

    virtual bool write(bus_addr_t addr,
                       AccessWidth width,
                       uint32_t const *data,
                       bool is_debug) = 0;        //!< Generate a write transaction.

    bool write(bus_addr_t addr,
               AccessWidth width,
               uint32_t const *data)
    {
        return write(addr, width, data, false);
    }

    bool read8(bus_addr_t addr, uint8_t *data, bool is_debug);     //!< Generate a read transaction.
    bool read16(bus_addr_t addr, uint16_t *data, bool is_debug);   //!< Generate a read transaction.
    bool read32(bus_addr_t addr, uint32_t *data, bool is_debug);   //!< Generate a read transaction.
    bool read64(bus_addr_t addr, uint64_t *data, bool is_debug);   //!< Generate a read transaction.

    bool read8(bus_addr_t addr, uint8_t *data)   { return read8(addr,  data, false); }
    bool read16(bus_addr_t addr, uint16_t *data) { return read16(addr, data, false); }
    bool read32(bus_addr_t addr, uint32_t *data) { return read32(addr, data, false); }
    bool read64(bus_addr_t addr, uint64_t *data) { return read64(addr, data, false); }

    bool write8(bus_addr_t addr, uint8_t const *data, bool is_debug);   //!< Generate a write transaction.
    bool write16(bus_addr_t addr, uint16_t const *data, bool is_debug); //!< Generate a write transaction.
    bool write32(bus_addr_t addr, uint32_t const *data, bool is_debug); //!< Generate a write transaction.
    bool write64(bus_addr_t addr, uint64_t const *data, bool is_debug); //!< Generate a write transaction.

    bool write8(bus_addr_t addr, uint8_t *data)   { return write8(addr,  data, false); }
    bool write16(bus_addr_t addr, uint16_t *data) { return write16(addr, data, false); }
    bool write32(bus_addr_t addr, uint32_t *data) { return write32(addr, data, false); }
    bool write64(bus_addr_t addr, uint64_t *data) { return write64(addr, data, false); }

public: // public DMI interface

    /// Get DMI (direct memory interface) pointer for the region around address_.
    /// This has similar semantics as the SystemC get_direct_mem_ptr():
    /// - requests a prefetch pointer
    /// - no notification on memory change (no snoop lock)
    /// - returns true is DMI is available for the requested access, else false
    /// - dmi_data_out_ is output only and contains the actual DMI pointer, the address
    ///   range it is valid for and the access types it is valid for (read/write/rw)
    virtual bool getDirectMemPtr(bool isRead,  // true=read, false=write
                                 TransactionAttributes const*       attributes_,
                                 ACERequest*                        ace_request_,
                                 bus_addr_t                         address_,
                                 DirectMemPtrData *                 dmi_data_out_) = 0;


    /// Set callback for invalidateDirectMemPtr() calls.
    /// This callback will be called whenever a previously returned DMI pointer becomes invalid.
    /// All DMI pointers covered by the address range must no longer be used after this callback was called.
    /// Setting a new callback overwrites the previous callback. Setting 0 as callback disables the callback.
    /// Each transaction generator only supports one callback.
    class CallbackInvalidateDirectMemPtr
    {
    public:
        virtual ~CallbackInvalidateDirectMemPtr() {}
        // Invalidate all DMI pointers overlapping with range (or restrict them not to cover range.
        // Range addresses are in the same addresses used by the bus master which owns (calls) this callback.
        virtual void invalidateDirectMemPtr(bus_addr_range_t range) = 0;
    };
    virtual void setCallbackInvalidateDirectMemPtr(CallbackInvalidateDirectMemPtr* cb_) = 0;

private: public: // Internal functions for burst transactions

    /*! Generate a burst read transaction.
     *  The fail_buffer must have space for one byte for each beat.
     *  On exit, it will contain a Tx_Data result code for each beat.
     */
    virtual bool read_burst(bus_addr_t addr,
                            void *data,
                            AccessWidth width,
                            unsigned burst_length,
                            bool is_debug,
                            uint8_t *fail_buffer = 0) = 0;

    bool read_burst(bus_addr_t addr,
                    void *data,
                    AccessWidth width,
                    unsigned burst_length,
                    uint8_t *fail_buffer = 0)
    {
        return read_burst(addr, data, width, burst_length, false, fail_buffer);
    }

    //! Generate a burst write transaction.
    virtual bool write_burst(bus_addr_t addr,
                             const void *data,
                             AccessWidth width,
                             unsigned burst_length,
                             bool is_debug) = 0; //!< Generate a burst read transaction.

    bool write_burst(bus_addr_t addr,
                     const void *data,
                     AccessWidth width,
                     unsigned burst_length)
    {
        return write_burst(addr, data, width, burst_length, false);
    }
};



class StreamingTransactionGenerator
{
public:
    virtual ~StreamingTransactionGenerator() {}

    //! Set the range of addresses over which this generator will DMA data
    // \param base address of DMA region
    // \param size of DMA region (bytes)
    virtual void setRange(bus_addr_t base, bus_addr_t size) = 0;

    //! Reset DMA pointer
    // \param new address for DMA pointer
    virtual void startDma(bus_addr_t address) = 0;

    //! Read the next block of DMA data
    // \param datap on exit points to start of DMA data
    // \param lenp  on entry length of data to request, on exit length of data available (bytes)
    // \return true if the data in the buffer may have changed since the last read
    virtual bool getDmaData(const uint8_t **datap, uint32_t* lenp) = 0;
};



/*! An interface that provides the ability to drive transactions from multiple
 *  contexts (UNSUPPORTED).
 */

class RandomContextTransactionGenerator
{
public:
    // The user can destroy a transaction generator if they want to -- otherwise
    // PVBusMaster will do it for you.
    virtual ~RandomContextTransactionGenerator() {}

    struct buffer_t
    {
        AccessWidth  access_width;
        void*        buffer;
        unsigned     buffer_len_in_width;
        uint8_t*     per_beat_fault;

        buffer_t(
            AccessWidth  access_width_,
            void*        buffer_,
            unsigned     buffer_len_in_width_,
            uint8_t*     per_beat_fault_ = 0
            )
            : access_width        ( access_width_        ),
              buffer              ( buffer_              ),
              buffer_len_in_width ( buffer_len_in_width_ ),
              per_beat_fault      ( per_beat_fault_      )
        {
        }

        buffer_t()
            : access_width(ACCESS_INVALID), buffer(0), buffer_len_in_width(0), per_beat_fault(0)
        {
        }

        AccessWidth  getAccessWidth()        const { return access_width;                              }
        unsigned     getAccessWidthInBytes() const { return accessWidthToByteWidth( access_width );    }
        unsigned     getTotalSizeInBytes()   const { return getAccessWidthInBytes() * getBurstCount(); }
        unsigned     getBurstCount()         const { return buffer_len_in_width;                       }
        void*        getDataBuffer()         const { return buffer;                                    }
        uint8_t*     getDataBufferAsUint8()  const { return static_cast<uint8_t*>(buffer);             }


        /// Satisfy the request from a byte representation of memory as pointed
        /// to by \a start_.
        void copyFrom( uint8_t const* start_ );

        /// Satisfy the request from a byte representation of memory as pointed
        /// to by \a start_.
        void copyTo( uint8_t* start_ );

        template<typename T>
        T& at(unsigned index_)
        {
            assert( index_ < buffer_len_in_width );
            return *(asArray<T>() + index_);
        }

        template<typename T>
        T const& at(unsigned index_) const
        {
            assert( index_ < buffer_len_in_width );
            return *(asArray<T>() + index_);
        }

        template<typename T>
        T* asArray()
        {
            assert( sizeof(T) == accessWidthToByteWidth(access_width) && buffer_len_in_width != 0 );
            return static_cast<T*>(buffer);
        }

        template<typename T>
        T const* asArray() const
        {
            assert( sizeof(T) == accessWidthToByteWidth(access_width) && buffer_len_in_width != 0 );
            return static_cast<T*>(buffer);
        }
    };


    /// A 'Channel' is a concept that is used internally to PVBus, it (roughly)
    /// corresponds to a connection between a PVBusMaster and a specific
    /// end-point PVBusSlave.  You can tune the number of channels that this
    /// generator is allowed to keep active at once using this function.
    virtual void setNumberOfChannels( unsigned number_ = ~0u ) = 0;

    /// Perform a read access using the specified attributes, the width and
    /// burst length are read from \a buffer_.  It must obey ACE/AXI constraints
    /// in terms of not crossing 4KiB boundaries, burst restrictions, etc.
    virtual pv::Tx_Result read(TransactionAttributes const*             attributes_,
                               ACERequest*                              ace_request_,
                               bus_addr_t                               address_,
                               buffer_t*                                buffer_) = 0;

    /// Perform a read access using the specified attributes, the width and
    /// burst length are used from \a buffer_.  It must obey ACE/AXI constraints
    /// in terms of not crossing 4KiB boundaries, burst restrictions, etc.
    virtual pv::Tx_Result write(TransactionAttributes const*       attributes_,
                                ACERequest*                        ace_request_,
                                bus_addr_t                         address_,
                                buffer_t const *                   buffer_) = 0;

    //! Return prefetch hint result for the last transaction
    // (true=prefetch is supported, false=prefetch is not supported).
    // This is just a hint. Masters have to request the DMI access separately.
    virtual bool getPrefetchHint() = 0;
};


class TransactionMasterControl : public sg::Port {
public:
    declare_slave_behaviour(createTransactionGenerator,              TransactionGenerator *());
    declare_slave_behaviour(createStreamingTransactionGenerator,     StreamingTransactionGenerator *());
    declare_slave_behaviour(createRandomContextTransactionGenerator, RandomContextTransactionGenerator *());

    TransactionMasterControl()
    {
        define_behaviour(createTransactionGenerator);
        define_behaviour(createStreamingTransactionGenerator);
        define_behaviour(createRandomContextTransactionGenerator);
    }
};

} // namespace pv

#include "sg/SGFactory.h"
COMPONENT_FACTORY_DECL(PVBusMaster);

#endif // PVBUS_MASTER_H
