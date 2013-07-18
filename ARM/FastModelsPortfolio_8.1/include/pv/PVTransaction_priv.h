/*!
 * \file    PVTransaction_priv.h
 * \brief   Implementation details, subject to change.
 * \date    Copyright 2005-2008,2012 ARM Limited. All rights reserved.
 *
 * This defines definitions of data types and inlined behaviour that
 * is not fixed as part of the PVBus API.  Clients must not depend on
 * any of these definitions.
 */

#ifndef PVTRANSACTION_PRIV_H
#define PVTRANSACTION_PRIV_H

#ifndef PVTRANSACTION_H
#error This header must only be included from PVTransaction.h
#endif

#include <cassert>
#include <cstdlib>
#include <cstring>

#include "pv/PVMemoryAttributes.h"
#include "pv/ACE.h"
#include "pv/PVRange.h"
#include "pv/AccessDirection.h"
#include "pv/PrefetchRange.h"

namespace pv {

class BusSlave;

    /// Opaque class used by PVBus2 slaves (ARM INTERNAL ONLY)
    class RevokeTransaction;

class Tx_Result
{
 public:
    //! Give users a copy-constructor.
    Tx_Result(Tx_Result const &t) : _priv(t._priv) { }

    //! Give users an assignment operator.
    Tx_Result &operator = (Tx_Result const &t) {
        _priv = t._priv;
        return *this;
    }

    //! Provide a default constructor that creates an undefined result value.
    Tx_Result() : _priv(0) {

    }

    bool isOK() const;
    bool isExclusiveOK() const;
    bool isExclusiveAbort() const;
    bool isAbort() const;
    bool isDecodeAbort() const;
    bool isIgnore() const;
    bool isWontPrefetch() const;
    bool isUndefined() const;

    inline Tx_Result combineWith( Tx_Result o_ ) const;

 private:
 public: // for now
    unsigned int _priv;

    explicit Tx_Result(uint32_t res) : _priv(res) { }

    friend class Transaction;
    friend class ReadTransaction;
    friend class WriteTransaction;

private:
    unsigned slow_combineWith(Tx_Result o_) const;
};


class Payload : public ACE::Payload
{
private:
    friend class Transaction;
    friend class ReadTransaction;
    friend class WriteTransaction;
    friend class ReadPrefetchTransaction;
    friend class WritePrefetchTransaction;
    friend class BusSlave;
    friend class MemoryPage;

public:
    typedef struct PayloadState
    {
        void * valuep;
        unsigned burst_count;
        unsigned burst_sequence;
        uint8_t * faultp;
    } PayloadState;

private:
    void*           valuep;
    uint8_t*        writeprefetch;
    uint8_t const*  readprefetch;

    // This is a token to pass back to the PVBusSlave::revokePrefetch() call to
    // undo any prefetch that we did.  It is a pointer to an opaque structure
    // and is persistent.  It is only valid if getWantPrefetch() is true.  It
    // is _not_ dependent on revoke_read_prefetch_on_change.
    RevokeTransaction*          revoke_transaction;

    /// OUT: \e address range for which the prefetch pointer is valid.  In
    /// which case readprefetch/writeprefetch correspond directly to the byte at
    /// address prefetch_range.begin. NOTE with care that this is the \b address
    /// and not the offset.
    pv::range_t<pv::bus_addr_t> prefetch_address_range;

    /// IN: This is a PVBus2 transaction and the client will understand the
    /// prefetching that the slave can perform.
    bool want_prefetch;
    bool revoke_read_prefetch_on_change;     //!< Client requests notification prior to any modification of prefetchable data.
    // OUT: hint: true if prefetch may be denied by slave for (AccessRead if this is an AccessWrite
    // transaction or Access Write if this is an AccessRead transaction). Valid only for non-OK transaction results (denied prefetch requests, WONTPREFETCH).
    // The actual prefetch pointer is _not_ returned in this transaction. This is just a hint that the prefetch pointer for the 
    // other type of access may or may not be retrieved.
    bool prefetch_denied_for_other_access_hint;
    /// OUT: Read prefetch might be available for address
    bool prefetch_read_hint;
    /// OUT: Write prefetch might be available for address
    bool prefetch_write_hint;

public: // public access to these is deprecated.
    unsigned   burst_count;  //! How many beats in the burst transaction, or zero if prefetch only request.
    uint8_t *  faultp;       //! Block of result codes for each beat.
    unsigned   burst_sequence; //! Index of the current transaction beat.

    AccessWidth   width;
    bool       privileged;
    bool       instruction;
    bool       non_secure;
    bool       locked;
    bool       exclusive;

    bool       side_effect; // access with side effect or not


    uint32_t    master_id;    //! Transaction master id


private: public: // for internal use only, to support internal code in CTModels.
   Payload();

   // Returns a pointer to the data value storage.
   void *referenceDataValue();
   // Returns a pointer to the const data value storage.
   const void *referenceDataValue() const;
   // Prepares a read transaction to store data at the given location.
   void prepareReadDataValueStorage(void *);
   // Ensures a read transaction has stored data at the given location.
   void releaseReadDataValueStorage(void *);
   // Prepares a write transaction to take data from the given location.
   void prepareWriteDataValueStorage(void const *);

   template <typename AccessDirection>
   void prepareStorage(typename AccessDirection::master_buffer_ptr ptr);

   // Get the response from a DeviceAccess_ReadPrefetch call
   uint8_t const * getReadPrefetchPointer();
   // Get the response from a DeviceAccess_WritePrefetch call
   uint8_t * getWritePrefetchPointer();
   /// Get either the read or write prefetch pointer
   template <typename AccessDirection>
   typename AccessDirection::slave_u8_ptr getPrefetchPointer();

   /// Setup a prefetch range.
   template <typename AccessDirection>
   void setPrefetchRange(PrefetchRange<AccessDirection> prefetch_range);

   template <typename AccessDirection>
   PrefetchRange<AccessDirection> getPrefetchRange();

   /// Set hint whether prefetch is denied for the 'other' type of access (see prefetch_denied_for_other_access)
   void setPrefetchIsDeniedForOtherAccessHint(bool is_denied = true);
   /// Get hint whether prefetch is denied for the 'other' type of access (see prefetch_denied_for_other_access)
   bool getPrefetchIsDeniedForOtherAccessHint();
   /// Set hint that read prefetching might be supported for address (implements TLM is_dmi_allowed())
   void setPrefetchReadHint();
   /// Get hint that read prefetching might be supported for address (implements TLM is_dmi_allowed())
   bool getPrefetchReadHint();
   /// Set hint that read prefetching might be supported for address (implements TLM is_dmi_allowed())
   void setPrefetchWriteHint();
   /// Get hint that read prefetching might be supported for address (implements TLM is_dmi_allowed())
   bool getPrefetchWriteHint();
   /// Clear prefetch hint
   void clearPrefetchHint();
  

public:  // ARM INTERNAL ONLY for use by PVBus2

    ///
    /// \name For use by the slave of this transaction
    ///
    //@{
    bool getWantPrefetch() const;

    bool isPrefetchOnly() const;

    /// Return true if client has requested snoop-locked access.
    bool           shouldRevokeReadPrefetchOnChange() const;

    pv::range_t<pv::bus_addr_t> getPrefetchAddressRange() const;

    //@}

    ///
    /// \name For use by the master of this transaction
    ///
    //@{
    void setPrefetchAndSnoopLock( bool want_prefetch_, bool revoke_read_prefetch_on_change_ );

    void setRevokeTransaction(RevokeTransaction* revoke_transaction_);

    //@}

    RevokeTransaction* getRevokeTransaction() const;

    // This is not enough by itself to set 'instruction' you must also have matching memory attributes.
    void setInstruction(bool instruction_);

    /// \name TX result codes
    ///
    /// NOTE the numbers of these results are important to
    /// Tx_Result::combineWith().  This is used by ChannelTransactionCutter
    /// which has to accumulate the results of separate transactions.  Any
    /// changes to these may need ChannelTransactionCutter being changed.
    ///
    /// Those components that return heterogenous result codes for different
    /// beats of data can use Tx_Result::combineWith() to deliver a final
    /// response, as well as the individual per-beat faults.
    ///
    /// NOTE that TX_EXCLUSIVEABORT is lowered in priority to between TX_EXOK
    /// and TX_ABORT.
    //@{
    static const uint32_t TX_OK = 1;
    static const uint32_t TX_EXOK = 1; // currently we use the same return code for OK and for EXOK, whereas AXI uses OK to mean exclusive-fail.
    static const uint32_t TX_ABORT = 2; // general/slave
    static const uint32_t TX_WAIT = 3;
    static const uint32_t TX_IGNORE = 4;
    static const uint32_t TX_WONTPREFETCH = 5;  // used purely for prefetch transactions
    static const uint32_t TX_DECODEABORT = 6;
    static const uint32_t TX_EXCLUSIVEABORT = 7; // generated by exclusive monitors
    static const uint32_t TX_ALIGNMENTABORT = 8;
    //@}

    void saveState(PayloadState&);
    void restoreState(const PayloadState&);

    void setAccessWidth(AccessWidth w);
    void setAccessByteWidth(int width);
    AccessWidth getAccessWidth();

    void setExclusive(bool);
    bool isExclusive();

    void setLocked(bool);
    bool isLocked();

    void setSideEffects(bool do_side_effects);
    bool hasSideEffects();

    bool nextBeat(pv::Tx_Result previous_result);
    void rollBack(unsigned desired_beat);
    void rollForward(unsigned desired_beat);

    unsigned getBurstCount();
    unsigned getBurstSequence();
    uint8_t* getFaultArray();

    void setupBurst(unsigned count_, uint8_t* faultp_, unsigned sequence_ = 0);

    /// Equivalent to calling nextBeat() for all beats, also works on prefetch
    /// only requests.
    void allBeatsCompletedInOneOperation( Tx_Result result );

    /// If we have independently filled out all of the data and all of the
    /// per-beat fault data then we can call this instead of
    /// allBeatsCompletedInOneOperation()
    void allBeatsCompletedInOneOperationAndFaultArrayFilledIn();
};


class Tx_Data : public Payload
{
public:
    Tx_Data(MemoryAttributes const * memory_attributes = 0);

    MemoryAttributes const *memory_attributes; //! Memory region attributes

    /// Access the memory attributes for this transaction.
    MemoryAttributes const* getMemoryAttributes();
};

inline AccessWidth byteWidthToAccessWidth(int byte_width)
{
    switch (byte_width) {
    case 1: return ACCESS_8_BITS;
    case 2: return ACCESS_16_BITS;
    case 4: return ACCESS_32_BITS;
    case 8: return ACCESS_64_BITS;
    case 16: return ACCESS_128_BITS;
    default: return ACCESS_INVALID;
    }
}

inline int accessWidthToByteWidth(AccessWidth width)
{
    return 1 << (int)(width);
}

inline int accessWidthToBitWidth(AccessWidth width)
{
    return 8 << (int)(width);
}

inline Payload::Payload() :
    valuep(NULL),
    writeprefetch(NULL),
    readprefetch(NULL),
    revoke_transaction(0),
    want_prefetch(false),
    revoke_read_prefetch_on_change(false),
    prefetch_denied_for_other_access_hint(false),
    prefetch_read_hint(false),
    prefetch_write_hint(false),
    burst_count(1),
    faultp(NULL),
    burst_sequence(0),
    width(ACCESS_INVALID),
    privileged(false),
    instruction(false),
    non_secure(false),
    locked(false),
    exclusive(false),
    side_effect(true),
    master_id(static_cast<uint32_t>(-1))
{
}

inline void *
Payload::referenceDataValue()
{
    return valuep;
}

inline const void *
Payload::referenceDataValue() const
{
    return valuep;
}

inline void Payload::prepareReadDataValueStorage(void *storage)
{
    valuep = storage;
}

inline void Payload::releaseReadDataValueStorage(void *storage)
{
    assert(storage == valuep);
}

inline void Payload::prepareWriteDataValueStorage(void const *storage)
{
    // const_cast here because valuep is also used for read-transactions,
    // where the storage must be modifiable; as a result we can't
    // maintain const-correctness here.
    valuep = const_cast<void *>(storage);
}

template <> inline
void Payload::prepareStorage<AccessRead>(AccessRead::master_buffer_ptr ptr)
{
    prepareReadDataValueStorage(ptr);
}

template <> inline
void Payload::prepareStorage<AccessWrite>(AccessWrite::master_buffer_ptr ptr)
{
    prepareWriteDataValueStorage(ptr);
}


inline uint8_t const *
Payload::getReadPrefetchPointer()
{
    return readprefetch;
}
inline uint8_t *
Payload::getWritePrefetchPointer()
{
    return writeprefetch;
}

template <> inline
AccessRead::slave_u8_ptr
Payload::getPrefetchPointer<AccessRead>()
{
    return readprefetch;
}

template <> inline
AccessWrite::slave_u8_ptr
Payload::getPrefetchPointer<AccessWrite>()
{
    return writeprefetch;
}

template <> inline
void Payload::setPrefetchRange<AccessRead>(
        PrefetchRange<AccessRead> prefetch_range)
{
    readprefetch = (uint8_t const *)prefetch_range.getPointer();
    prefetch_address_range = prefetch_range.getRange();
    setPrefetchReadHint();
}

template <> inline
void Payload::setPrefetchRange<AccessWrite>(
        PrefetchRange<AccessWrite> prefetch_range)
{
    writeprefetch = (uint8_t *)prefetch_range.getPointer();
    prefetch_address_range = prefetch_range.getRange();
    setPrefetchWriteHint();
}

template <> inline
PrefetchRange<AccessRead>
Payload::getPrefetchRange()
{
    if (want_prefetch) {
        return PrefetchRange<AccessRead>(readprefetch, prefetch_address_range);
    } else {
        return PrefetchRange<AccessRead>();
    }
}

template <> inline
PrefetchRange<AccessWrite>
Payload::getPrefetchRange()
{
    if (want_prefetch) {
        return PrefetchRange<AccessWrite>(writeprefetch, prefetch_address_range);
    } else {
        return PrefetchRange<AccessWrite>();
    }
}

/// Set hint whether prefetch is denied for the 'other' type of access (see prefetch_denied_for_other_access)
inline void Payload::setPrefetchIsDeniedForOtherAccessHint(bool is_denied)
{
    prefetch_denied_for_other_access_hint = is_denied;
}
    
/// Get hint whether prefetch is denied for the 'other' type of access (see prefetch_denied_for_other_access)
inline bool Payload::getPrefetchIsDeniedForOtherAccessHint()
{
    return prefetch_denied_for_other_access_hint;
}
    
/// Set hint that read prefetching might be supported for address (implements TLM is_dmi_allowed())
inline void Payload::setPrefetchReadHint()
{
    prefetch_read_hint = true;
}
    
/// Get hint that read prefetching might be supported for address (implements TLM is_dmi_allowed())
inline bool Payload::getPrefetchReadHint()
{
    return prefetch_read_hint;
}
    
/// Set hint that read prefetching might be supported for address (implements TLM is_dmi_allowed())
inline void Payload::setPrefetchWriteHint()
{
    prefetch_write_hint = true;
}
    
/// Get hint that read prefetching might be supported for address (implements TLM is_dmi_allowed())
inline bool Payload::getPrefetchWriteHint()
{
    return prefetch_write_hint;
}
    
/// Clear prefetch hint
inline void Payload::clearPrefetchHint()
{
    prefetch_read_hint = false;
    prefetch_write_hint = false;
}
    
inline bool Payload::getWantPrefetch() const
{
    return want_prefetch;
}

inline bool Payload::isPrefetchOnly() const
{
    return burst_count == 0;
}

inline bool Payload::shouldRevokeReadPrefetchOnChange() const
{
    return revoke_read_prefetch_on_change;
}

inline pv::range_t<pv::bus_addr_t> Payload::getPrefetchAddressRange() const
{
    return prefetch_address_range;
}


inline void Payload::setPrefetchAndSnoopLock( bool want_prefetch_, bool revoke_read_prefetch_on_change_ )
{
    assert(!(revoke_read_prefetch_on_change_ && !want_prefetch_));
    want_prefetch = want_prefetch_;
    prefetch_address_range = bus_range_t::make_empty();
    readprefetch = 0;
    writeprefetch = 0;
    revoke_read_prefetch_on_change = revoke_read_prefetch_on_change_;
}
inline void Payload::setRevokeTransaction(RevokeTransaction* revoke_transaction_)
{
    revoke_transaction = revoke_transaction_;
}

inline RevokeTransaction* Payload::getRevokeTransaction() const
{
    return revoke_transaction;
}

inline void Payload::setInstruction(bool instruction_)
{
    instruction = instruction_;
}

inline void Payload::setAccessWidth(AccessWidth w)
{
    width = w;
}

inline AccessWidth Payload::getAccessWidth()
{
    return width;
}

inline void Payload::setExclusive(bool e_)
{
    exclusive = e_;
}

inline bool Payload::isExclusive()
{
    return exclusive;
}

inline void Payload::setLocked(bool l_)
{
    locked = l_;
}

inline bool Payload::isLocked()
{
    return locked;
}

inline void Payload::setSideEffects(bool do_side_effects)
{
    side_effect = do_side_effects;
}

inline bool Payload::hasSideEffects()
{
    return side_effect;
}

inline void Payload::saveState(PayloadState& state)
{
    state.valuep = valuep;
    state.burst_count = burst_count;
    state.burst_sequence = burst_sequence;
    state.faultp = faultp;
}

inline void Payload::restoreState(const PayloadState& state)
{
    valuep = state.valuep;
    burst_count = state.burst_count;
    burst_sequence = state.burst_sequence;
    faultp = state.faultp;
}

inline unsigned Payload::getBurstCount()
{
    return burst_count;
}

inline unsigned Payload::getBurstSequence()
{
    return burst_sequence;
}

inline uint8_t* Payload::getFaultArray()
{
    return faultp;
}

inline void Payload::setupBurst(unsigned count_, uint8_t* faultp_, unsigned sequence_)
{
    burst_count    = count_;
    faultp         = faultp_;
    burst_sequence = sequence_;
}


inline void Payload::allBeatsCompletedInOneOperation( Tx_Result result )
{
    assert( burst_sequence == 0 );
    burst_sequence = burst_count;
    if (faultp != NULL)
    {
        for (unsigned i = 0; i != burst_count; ++ i)
        {
            faultp[i] = result._priv;
        }
    }
}

inline void Payload::allBeatsCompletedInOneOperationAndFaultArrayFilledIn()
{
    assert( burst_sequence == 0 );
    burst_sequence = burst_count;
}

inline MemoryAttributes const* Tx_Data::getMemoryAttributes()
{
    return memory_attributes;
}

inline Transaction::Transaction(bus_addr_t address_, Tx_Data *tx_data_)
: address(address_), data(tx_data_), memory_attributes(tx_data_->getMemoryAttributes())
{
}

inline Transaction::Transaction(bus_addr_t address_,
                                Payload * payload_,
                                MemoryAttributes const * attributes_)
  : address(address_), data(payload_), memory_attributes(attributes_)
{
}

inline ACE::ace_operation_t Transaction::getACEOperation() const
{
    return getPayload()->get_ace_operation(getMemoryAttributes());
}

inline ReadTransaction::ReadTransaction(bus_addr_t address_,
                                        Tx_Data * tx_data_)
: Transaction(address_, tx_data_)
{
}

inline ReadTransaction::ReadTransaction(bus_addr_t address_,
                                        Payload * payload_,
                                        MemoryAttributes const * attributes_)
: Transaction(address_, payload_, attributes_)
{
}

inline WriteTransaction::WriteTransaction(bus_addr_t address_,
                                          Tx_Data * tx_data_)
: Transaction(address_, tx_data_)
{
}

inline WriteTransaction::WriteTransaction(bus_addr_t address_,
                                          Payload * payload_,
                                          MemoryAttributes const * attributes_)
: Transaction(address_, payload_, attributes_)
{
}

inline ReadPrefetchTransaction::ReadPrefetchTransaction(bus_addr_t address_,
                                                        Tx_Data * tx_data_)
: Transaction(address_, tx_data_)
{
}

inline ReadPrefetchTransaction::ReadPrefetchTransaction(bus_addr_t address_,
                                                        Payload * payload_,
                                                        MemoryAttributes const * attributes_)
: Transaction(address_, payload_, attributes_)
{
}

inline WritePrefetchTransaction::WritePrefetchTransaction(bus_addr_t address_,
                                                          Tx_Data * tx_data_)
: Transaction(address_, tx_data_)
{
}

inline WritePrefetchTransaction::WritePrefetchTransaction(bus_addr_t address_,
                                                          Payload * payload_,
                                                          MemoryAttributes const * attributes_)
: Transaction(address_, payload_, attributes_)
{
}

inline const MemoryAttributes *
Transaction::getMemoryAttributes() const
{
    return memory_attributes;
}

inline bus_addr_t Transaction::getAddress() const
{
    return address;
}

inline void Transaction::setAddress(bus_addr_t address_)
{
    address = address_;
}

inline pv::bus_addr_t Transaction::getAddressEndIncl() const
{
    return getAddress() + getTransactionByteSize() - 1;
}

inline bus_addr_range_t Transaction::getAddressRange() const
{
    return range_begin_size<pv::bus_addr_t>(address, /*total size incl. all beats*/getTransactionByteSize());
}

inline AccessWidth Transaction::getAccessWidth() const
{
    return data->getAccessWidth();
}

inline int Transaction::getAccessByteWidth() const
{
    return accessWidthToByteWidth(getAccessWidth());
}

inline int Transaction::getAccessBitWidth() const
{
    return accessWidthToBitWidth(getAccessWidth());
}

inline bool Transaction::isAligned() const
{
    pv::bus_addr_t mask = (pv::bus_addr_t(1) << data->getAccessWidth()) - 1;
    return (address & mask) == 0;
}

inline bool Transaction::isPrivileged() const
{
    if (getMemoryAttributes()) {
        return getMemoryAttributes()->isPrivileged();
    }
    return data->privileged;
}

inline bool Transaction::isInstruction() const
{
    if (getMemoryAttributes()) {
        return getMemoryAttributes()->isInstruction();
    }
    return data->instruction;
}

inline bool Transaction::isNonSecure() const
{
    if (getMemoryAttributes()) {
        return getMemoryAttributes()->isNormalWorld();
    }
    return data->non_secure;
}

inline bool Transaction::isLocked() const
{
    return data->isLocked();
}

inline bool Transaction::isExclusive() const
{
    return data->isExclusive();
}

inline bool Transaction::isCacheMaintenance() const
{
    return getPayload()->is_for_a_cache_maintenance_operation();
}

inline bool Transaction::isWithoutData() const
{
    return getPayload()->is_without_data();
}

inline uint32_t Transaction::getMasterID() const
{
    if (getMemoryAttributes()) {
        return getMemoryAttributes()->getMasterID();
    }
    return data->master_id;
}

inline ExclusiveLockMaster *Transaction::getExclusiveLockMaster() const
{
    if (getMemoryAttributes()) {
        return getMemoryAttributes()->getExclusiveLockMaster();
    }
    else {
        return NULL;
    }
}

inline bool Transaction::hasSideEffect() const
{
    return data->hasSideEffects();
}

inline Tx_Result Transaction::generateAbort()
{
    return generateSlaveAbort();
}

inline Tx_Result Transaction::generateIgnore()
{
    return Tx_Result(Tx_Data::TX_IGNORE);
}

inline Tx_Result Transaction::generateSlaveAbort()
{
    return Tx_Result(Tx_Data::TX_ABORT);
}

inline Tx_Result Transaction::generateDecodeAbort()
{
    return Tx_Result(Tx_Data::TX_DECODEABORT);
}

inline Tx_Result Transaction::generateExclusiveAbort()
{
    return Tx_Result(Tx_Data::TX_EXCLUSIVEABORT);
}

inline Tx_Result Transaction::generateWaitState(unsigned /* ticks */)
{
    return Tx_Result(Tx_Data::TX_WAIT);
}

inline Payload *Transaction::getPayload() const
{
    return data;
}

inline void *Transaction::referenceDataValue() const
{
    return data->referenceDataValue();
}

inline uint8_t *Transaction::getFaultArray() const
{
    return data->getFaultArray();
}

inline unsigned Transaction::getBurstLength() const
{
    return data->getBurstCount();
}

inline unsigned Transaction::getBurstSequence() const
{
    return data->getBurstSequence();
}

inline unsigned Transaction::getTransactionByteSize() const
{
    return getAccessByteWidth() * getBurstLength();
}

inline bool Transaction::nextBeat(pv::Tx_Result previous_result)
{
    return data->nextBeat(previous_result);
}

inline void Transaction::allBeatsCompletedInOneOperation( Tx_Result result )
{
    return data->allBeatsCompletedInOneOperation(result);
}


inline Tx_Result ReadTransaction::setReturnData64(uint64_t v)
{
    if (getAccessWidth() == pv::ACCESS_64_BITS)
    {
        *static_cast<uint64_t *>(referenceDataValue()) = v;
    } else {
        narrowing_write(v);
    }
    return Tx_Result(Tx_Data::TX_OK);
}

inline Tx_Result ReadTransaction::setReturnData32(uint32_t v)
{
    if (getAccessWidth() == pv::ACCESS_32_BITS)
    {
        *static_cast<uint32_t *>(referenceDataValue()) = v;
    } else {
        narrowing_write(v);
    }
    return Tx_Result(Tx_Data::TX_OK);
}

inline Tx_Result ReadTransaction::setReturnData16(uint16_t v)
{
    if (getAccessWidth() == pv::ACCESS_16_BITS)
    {
        *static_cast<uint16_t *>(referenceDataValue()) = v;
    } else {
        narrowing_write(v);
    }
    return Tx_Result(Tx_Data::TX_OK);
}

inline Tx_Result ReadTransaction::setReturnData8(uint8_t v)
{
    if (getAccessWidth() == pv::ACCESS_8_BITS)
    {
        *static_cast<uint8_t *>(referenceDataValue()) = v;
    } else {
        narrowing_write(v);
    }
    return Tx_Result(Tx_Data::TX_OK);
}

// Take a value returned from a device which is wider than that
// requested in the transaction, and write the lower sizeof(T)
// bytes into the transaction payload.
template< typename T >
inline void ReadTransaction::narrowing_write( T t )
{
    // The offset will always be small so it is safe to cast the result to a
    // potentially smaller type.
    unsigned const offset_in_t = (unsigned)(getAddress() & (sizeof(T) - 1));

    // The user must supply _more_ data than we asked for!
    assert( sizeof(t) >  (unsigned) getAccessByteWidth());

    // The address must also be aligned to the transfer size.
    assert( (getAddress() & (getAccessByteWidth() - 1)) == 0 );

    // This rather redundant looking switch statement allows the
    // compiler to see the special cases of 1/2/4 byte accesses.
    // GCC optimizes these constant size memcpy()s down to a
    // movz/mov pair.
    uint8_t *dst = static_cast<uint8_t *>(referenceDataValue());
    uint8_t const *src = reinterpret_cast<uint8_t const*>(&t) + offset_in_t;
    switch (getAccessWidth()) {
        case pv::ACCESS_8_BITS:   memcpy(dst, src, 1); break;
        case pv::ACCESS_16_BITS:  memcpy(dst, src, 2); break;
        case pv::ACCESS_32_BITS:  memcpy(dst, src, 4); break;
        default:                  memcpy(dst, src, getAccessByteWidth()); break;
    }
}

// this is also used to accept and confirm prefetch only accesses
inline Tx_Result ReadTransaction::readComplete()
{
    return Tx_Result(Tx_Data::TX_OK);
}

// prefetch only transactions are normal ReadTransactions, give PVDevice::read() implementations a chance to deny prefetch accesses
inline Tx_Result ReadTransaction::wontPrefetch()
{
    getPayload()->readprefetch = NULL;
    return Tx_Result(Tx_Data::TX_WONTPREFETCH);
}

inline Tx_Result ReadTransaction::completeFrom(
    uint8_t const* begin_,
    uint8_t const* end_
    )
{
        assert( getBurstSequence() == 0 );
        assert( end_ > begin_ );
        assert( std::size_t(end_ - begin_) >= getTransactionByteSize() );

        // Assuming little-endian
        memcpy( referenceDataValue(), begin_, getTransactionByteSize() );

        Tx_Result const ret = readComplete();

        // Now need to signal that each beat has been completed so that
        // PVBusSlave doesn't keep repeating the access.
        allBeatsCompletedInOneOperation( ret );

        return ret;
}

inline uint64_t WriteTransaction::getData64() const
{
    return *static_cast<uint64_t *>(referenceDataValue());
}

inline uint32_t WriteTransaction::getData32() const
{
    return *static_cast<uint32_t *>(referenceDataValue());
}

inline uint16_t WriteTransaction::getData16() const
{
    return *static_cast<uint16_t *>(referenceDataValue());
}

inline uint8_t WriteTransaction::getData8() const
{
    return *static_cast<uint8_t *>(referenceDataValue());
}

// this is also used to accept and confirm prefetch only accesses
inline Tx_Result WriteTransaction::writeComplete()
{
    return Tx_Result(Tx_Data::TX_OK);
}

// prefetch only transactions are normal WriteTransactions, give PVDevice::write() implementations a chance to deny prefetch accesses
inline Tx_Result WriteTransaction::wontPrefetch()
{
    getPayload()->writeprefetch = NULL;
    return Tx_Result(Tx_Data::TX_WONTPREFETCH);
}

inline Tx_Result WriteTransaction::completeTo(
        uint8_t*   begin_,
        uint8_t*   end_
        )
{

        assert( getBurstSequence() == 0 );
        assert( end_ > begin_ );
        assert( std::size_t(end_ - begin_) >= getTransactionByteSize() );

        // Assume little-endian
        memcpy( begin_, referenceDataValue(), getTransactionByteSize() );

        Tx_Result const ret = writeComplete();

        allBeatsCompletedInOneOperation( ret );

        return ret;
}

inline Tx_Result ReadPrefetchTransaction::setPrefetchAddress(uint8_t const* mem)
{
    getPayload()->readprefetch = mem;
    return Tx_Result(Tx_Data::TX_OK);
}

inline Tx_Result ReadPrefetchTransaction::transactionComplete()
{
    return Tx_Result(Tx_Data::TX_OK);
}

inline Tx_Result ReadPrefetchTransaction::wontPrefetch()
{
    getPayload()->readprefetch = NULL;
    return Tx_Result(Tx_Data::TX_WONTPREFETCH);
}

inline Tx_Result WritePrefetchTransaction::setPrefetchAddress(uint8_t * mem)
{
    getPayload()->writeprefetch = mem;
    return Tx_Result(Tx_Data::TX_OK);
}

inline Tx_Result WritePrefetchTransaction::transactionComplete()
{
    return Tx_Result(Tx_Data::TX_OK);
}

inline Tx_Result WritePrefetchTransaction::wontPrefetch()
{
    getPayload()->writeprefetch = NULL;
    return Tx_Result(Tx_Data::TX_WONTPREFETCH);
}

inline Transaction Transaction::remap(bus_addr_t new_addr) const
{
    Transaction tx(new_addr, getPayload(), getMemoryAttributes());
    return tx;
}

inline ReadTransaction ReadTransaction::remap(bus_addr_t new_addr) const
{
    ReadTransaction tx(new_addr, getPayload(), getMemoryAttributes());
    return tx;
}

inline WriteTransaction WriteTransaction::remap(bus_addr_t new_addr) const
{
    WriteTransaction tx(new_addr, getPayload(), getMemoryAttributes());
    return tx;
}

inline ReadPrefetchTransaction ReadPrefetchTransaction::remap(bus_addr_t new_addr) const
{
    ReadPrefetchTransaction tx(new_addr, getPayload(), getMemoryAttributes());
    return tx;
}

inline WritePrefetchTransaction WritePrefetchTransaction::remap(bus_addr_t new_addr) const
{
    WritePrefetchTransaction tx(new_addr, getPayload(), getMemoryAttributes());
    return tx;
}

inline bool Tx_Result::isOK() const
{
    return _priv == Tx_Data::TX_OK;
}

inline bool Tx_Result::isExclusiveOK() const
{
    return _priv == Tx_Data::TX_EXOK;
}

inline bool Tx_Result::isExclusiveAbort() const
{
    return _priv == Tx_Data::TX_EXCLUSIVEABORT;
}

inline bool Tx_Result::isAbort() const
{
    return _priv == Tx_Data::TX_ABORT;
}

inline bool Tx_Result::isDecodeAbort() const
{
    return _priv == Tx_Data::TX_DECODEABORT;
}

inline bool Tx_Result::isIgnore() const
{
    return _priv == Tx_Data::TX_IGNORE;
}

inline bool Tx_Result::isWontPrefetch() const
{
    return _priv == Tx_Data::TX_WONTPREFETCH;
}

inline bool Tx_Result::isUndefined() const
{
    return _priv == 0;
}

inline Tx_Result Tx_Result::combineWith( Tx_Result o_ ) const
{
    unsigned ret = _priv < o_._priv ? o_._priv : _priv;
    // Lower EXCLUSIVEABORT to something to between TX_EXOK and TX_ABORT
    return Tx_Result(
        ret == Payload::TX_EXCLUSIVEABORT
        ? slow_combineWith(o_)
        : ret
        );
}

///
/// If you are handling a burst transaction then you must handle the whole
/// transaction or just a single beat.
///
/// To calculate the next beat address then you initialise a
/// BeatAddressGenerator and call it for each beat.  This will also call the
/// nextBeat() on each transaction correctly for you.
///
class BeatGenerator
{
    Transaction    tx;
    pv::bus_addr_t address;
public:
    BeatGenerator( Transaction tx_ ) : tx(tx_), address(tx.getAddress()) {}

    pv::bus_addr_t getBeatAddress() const { return address; }

    bool nextBeat( pv::Tx_Result result_of_last_beat_ )
    {
        address += tx.getAccessByteWidth();
        return tx.nextBeat(result_of_last_beat_);
    }
};

} // namespace pv
#endif // PVTRANSACTION_PRIV_H
