 /*!
 * \file    PVTransaction.h
 * \brief   Data-type for bus transactions
 * \date    Copyright 2005-2009,2012 ARM Limited. All rights reserved.
 *
 */

#ifndef PVTRANSACTION_H
#define PVTRANSACTION_H

#include "sg/SGstdint.h"
#include "pv/PVBusAddr.h"
#include "pv/PVAccessWidth.h"
#include "pv/PVRange.h"
#include "pv/ACE.h"

#include <iosfwd>

namespace pv {

    /// Define a standard type for representing ranges of bus addresses.
    typedef pv::range_t<bus_addr_t> bus_addr_range_t;

class MemoryAttributes;
class ExclusiveLockMaster;

/*! An opaque type used to hold return values from transactions.
 *  Tx_Result types can be copied and copy-constructed, but they
 *  can't be inspected or created, except through the Transaction
 *  class.
 */
class Tx_Result;

/*! An opaque type describing the context of a transaction. */
class Tx_Data;
class Payload;

/*! Base class for read/write transactions. */
class Transaction
{
    // The details of this structure may change between revisions,
    // requiring a recompile of code using this API.  Code must not
    // depend on the internal implementation of this structure.

public:
    bus_addr_t address;   //!< Address of the transaction.

private:
    Payload   *data;      //!< Further transaction details.
    MemoryAttributes const *memory_attributes;

public:
    /*! Allow an immutable transaction object to be constructed from an
     *  address and a Tx_Data (which holds the memory attributes and the
     *  payload information).
     */
    Transaction(bus_addr_t address_,
                Tx_Data * tx_data_);

    Transaction(bus_addr_t address_,
                Payload * tx_data_,
                MemoryAttributes const * attributes_);

    //! Return a copy of this transaction with a new address.
    Transaction remap(bus_addr_t new_addr) const;

    // Accessors
    bus_addr_t       getAddress() const;         //!< Transaction address.
    bus_addr_t       getAddressEndIncl() const;  //!< Address of last byte in the transaction
    bus_addr_range_t getAddressRange() const;    //!< The range of addresses that the transaction accesses
    void             setAddress(bus_addr_t);     //!< Transaction address.

    AccessWidth getAccessWidth() const;    //!< Request width in lg2 bytes.
    int         getAccessByteWidth() const;//!< Request width in bytes.
    int         getAccessBitWidth() const; //!< Request width in bits.
    bool        isAligned() const;         //!< Request address is aligned to request width boundary.

    bool       isPrivileged() const;       //!< Privileged process mode?
    bool       isInstruction() const;      //!< Instruction request vs data?
    bool       isNonSecure() const;        //!< Normal-world vs secure-world?
    bool       isLocked() const;           //!< Atomic locked access?
    bool       isExclusive() const;        //!< Atomic exclusive access?
    bool       isCacheMaintenance() const; //!< Cache maintenance operation
    bool       isWithoutData() const;      //!< Transaction has no data payload
    uint32_t   getMasterID() const;        //!< Transaction master ID
    ExclusiveLockMaster *getExclusiveLockMaster() const;
    bool       hasSideEffect() const;      //!< The transaction has side effect?

    // Generate transaction returns

    Tx_Result  generateAbort();   //!< Cause the transaction to abort.

    Tx_Result  generateIgnore();  //!< Cause the transaction to be ignored.

    Tx_Result  generateSlaveAbort();    //! Cause the transaction to abort
    Tx_Result  generateDecodeAbort();   //! Cause the transaction to abort
    Tx_Result  generateExclusiveAbort();//! Cause the transaction to abort

private: public: // These are not publicly supported

    uint32_t getUserFlags() const;

    Payload *getPayload() const;

    // for internal use only, to support internal code in PL310 model
    const MemoryAttributes *getMemoryAttributes() const;

    // Returns a pointer to the const data value storage.
    void *referenceDataValue() const;

    // Return a pointer to the per-beat fault array.
    uint8_t *getFaultArray() const;

    /*! How many beats in this transaction? (Returns 1 for non-bursts) */
    unsigned getBurstLength() const;

    /*! Get current beat sequence number of ongoing transaction (e.g. 0, 1, 2, 3 for a getBurstLength() == 4) */
    unsigned getBurstSequence() const;

    /*! Get total size in bytes (sum of all accesses) for burst and non-burst accesses. */
    unsigned getTransactionByteSize() const;

    /*! Move on to handling the next beat of a burst transaction,
     *  setting the result code for the previous beat.
     *  \return true if the transaction is not yet complete.
     */
    bool nextBeat(pv::Tx_Result previous_result);

    /*! Equivalent to calling nextBeat() for all beats, also works on prefetch
     * only requests.
     */
    void allBeatsCompletedInOneOperation( Tx_Result result );

    /*! Generate a return code indicating that the device wants to
     *  produce a wait-state.  The master must repeat the transaction
     *  request.
     *  \param ticks A hint that the slave will continue to generate
     *               wait-states until this number of bus clocks.
     */
    Tx_Result  generateWaitState(unsigned ticks = 1);

    /*! This call returns the ACE operation to perform assuming that the
      transaction is_read_ or not.  This takes into account the shareability of
      the request and will squash shareable only operations to non-shareable. */
    ACE::ace_operation_t getACEOperation() const;
};

//! A transaction where a master reads from a slave.
class ReadTransaction : public Transaction {
    template< typename T > void narrowing_write( T t_ );

public:
    /*! Allow an immutable read-transaction object to be constructed from an
     *  address and a Tx_Data (which holds the memory attributes and the
     *  payload information).
     */
    ReadTransaction(bus_addr_t address_,
                    Tx_Data * tx_data_);

    ReadTransaction(bus_addr_t address_,
                    Payload * tx_data_,
                    MemoryAttributes const * memory_attributes);

    /*! Return a copy of this transaction with a new address. */
    ReadTransaction remap(bus_addr_t new_addr) const;

    /*! Return a 64-bit value on the bus.  The data will be byte-laned as
     *  appropriate if the transaction size is not 64-bits.
     */
    Tx_Result setReturnData64(uint64_t);

    /*! Return a 32-bit value on the bus.  The data will be byte-laned as
     *  appropriate if the transaction size is not 32-bits.
     */
    Tx_Result setReturnData32(uint32_t);

    /*! Return a 16-bit value on the bus.  The data will be byte-laned as
     *  appropriate if the transaction size is not 16-bits.
     */
    Tx_Result setReturnData16(uint16_t);

    /*! Return an 8-bit value on the bus.  The data will be byte-laned as
     *  appropriate if the transaction size is not 8-bits.
     */
    Tx_Result setReturnData8(uint8_t);

    /*! This method provides an alternative way of returning a Tx_Result
     *  success value (instead of just using the value returned from
     *  setReturnData<n>()).
     *
     *  This method can only be called if one of the setReturnData<n>
     *  methods has already been called for the current transaction.
     */
    Tx_Result readComplete();

    /*! Only for prefetch-only transactions (which are normal ReadTransactions):
     * PVDevice::read() implementations use this to deny prefetch-only accesses.
     */
    Tx_Result wontPrefetch();
        
    /*! Complete the whole transaction (and it must be at least the whole
     *  transaction) from an array of data that directly matches the request.
     *  In addition will call readComplete() and return the result.
     */
    Tx_Result completeFrom( uint8_t const* begin_, uint8_t const* end_ );
    
};

//! A transaction where a master reads writes to a slave.
class WriteTransaction : public Transaction {
public:
    /*! Allow an immutable write-transaction object to be constructed from an
     *  address and a Tx_Data (which holds the memory attributes and the
     *  payload information).
     */
    WriteTransaction(bus_addr_t address_,
                     Tx_Data * tx_data_);

    WriteTransaction(bus_addr_t address_,
                     Payload * tx_data_,
                     MemoryAttributes const * memory_attributes);

    /*! Return a copy of this transaction with a new address. */
    WriteTransaction remap(bus_addr_t new_addr) const;


    /*! Get bottom 64-bits of data from the bus.  If the transaction width
     *  is less than 64-bits, the data will be extended as appropriate.
     */
    uint64_t getData64() const;

    /*! Get bottom 32-bits of data from the bus.  If the transaction width
     *  is less than 32-bits, the data will be extended as appropriate.
     */
    uint32_t getData32() const;

    /*! Get bottom 16-bits of data from the bus.  If the transaction width
     *  is less than 16-bits, the data will be extended as appropriate.
     */
    uint16_t getData16() const;

    /*! Get bottom 8-bits of data from the bus.  If the transaction width
     *  is less than 8-bits, the data will be extended as appropriate.
     */
    uint8_t  getData8() const;

    /*! Signal that the slave has handled the write successfully. */
    Tx_Result writeComplete();

    /*! Only for prefetch-only transactions (which are normal WriteTransactions):
     * PVDevice::write() implementations use this to deny prefetch-only accesses.
     */
    Tx_Result wontPrefetch();
        
    /*! Complete the whole transaction (and it must be at least the whole
     *  transaction) from an array of data that directly matches the request.
     *  In addition will call readComplete() and return the result.
     */
    Tx_Result completeTo( uint8_t* begin_, uint8_t* end_ );
};

//! A transaction where a master obtains a pointer to the underlying memory representing
//  a region of bus address space. The slave may refuse to return a pointer to such
//  memory (if e.g. it doesn't exist).
class ReadPrefetchTransaction : public Transaction {
public:
    /*! Allow an immutable read-prefetch-transaction object to be constructed
     *  from an address and a Tx_Data (which holds the memory attributes and
     *  the payload information).
     */
    ReadPrefetchTransaction(bus_addr_t address_,
                            Tx_Data * tx_data_);

    ReadPrefetchTransaction(bus_addr_t address_,
                            Payload * tx_data_,
                            MemoryAttributes const * memory_attributes);

    ReadPrefetchTransaction remap(bus_addr_t new_addr) const;

    /*! Set the pointer that may be used by a master to directly access implementation
     *  memory. This may be NULL, which indicates to the master that a future request
     *  may or may not be NULL. This differs in meaning from wontPrefetch
     */
    Tx_Result setPrefetchAddress(uint8_t const*);

    /*! Signal that the slave has handled the prefetch transaction successfully */
    Tx_Result transactionComplete();

    /*! Signal that the prefetch transaction failed and that future transactions are also
     *  very likely to return NULL.
     */
    Tx_Result wontPrefetch();
};

//! A transaction where a master obtains a pointer to the underlying memory representing
//  a region of bus address space. The slave may refuse to return a pointer to such
//  memory (if e.g. it doesn't exist).
class WritePrefetchTransaction : public Transaction {
public:
    /*! Allow an immutable read-prefetch-transaction object to be constructed
     *  from an address and a Tx_Data (which holds the memory attributes and
     *  the payload information).
     */
    WritePrefetchTransaction(bus_addr_t address_,
                            Tx_Data * tx_data_);

    WritePrefetchTransaction(bus_addr_t address_,
                             Payload * tx_data_,
                             MemoryAttributes const * memory_attributes);

    WritePrefetchTransaction remap(bus_addr_t new_addr) const;

    /*! Set the pointer that may be used by a master to directly access implementation
     *  memory. This may be NULL, which indicates to the master that a future request
     *  may or may not be NULL. This differs in meaning from wontPrefetch
     */
    Tx_Result setPrefetchAddress(uint8_t*);

    /*! Signal that the slave has handled the prefetch transaction successfully */
    Tx_Result transactionComplete();

    /*! Signal that the prefetch transaction failed and that future transactions will also
     *  return NULL for the prefetch address
     */
    Tx_Result wontPrefetch();
};


//! DMI request response data (see RandomContextTransactionGenerator::getDirectMemoryPtr()).
class DirectMemPtrData
{   
public:
    DirectMemPtrData() { init(); }
    
    /// reset to defaults
    void init()
    {
        dmi_ptr = 0;
        granted_access = A_NONE;
        // read_latency = 0;
        // write_latency = 0;
    }
    
    // public data    
    
    /// address range for which DMI access is granted or denied (contains the address DMI was requested for)
    bus_addr_range_t range;
    
    /// actual DMI pointer
    /// (0 for denied DMI access)
    uint8_t *dmi_ptr;
    
    /// granted access (SystemC like semantics)
    /// A_NONE: no DMI access is granted or denied
    /// A_READ: only read access is granted or denied
    /// A_WRITE: only write access is granted or denied
    /// A_READWRITE: read and write access is granted or denied
    enum GrantedAccess { A_NONE = 0, A_READ = 1, A_WRITE = 2, A_READWRITE = A_READ | A_WRITE }; // do not change these numeric values, these concrete integer values are part of the interface
    GrantedAccess granted_access;
    
    /// average access latency time per byte
    // (type is to be defined)
};


    std::ostream& operator << (std::ostream& os_, Transaction const& t_);
    std::ostream& operator << (std::ostream& os_, ReadTransaction const& t_);
    std::ostream& operator << (std::ostream& os_, WriteTransaction const& t_);
} // namespace pv

/*! Pull in inline definitions of data structures. */
#include "pv/PVTransaction_priv.h"

#endif // PVTRANSACTION_H
