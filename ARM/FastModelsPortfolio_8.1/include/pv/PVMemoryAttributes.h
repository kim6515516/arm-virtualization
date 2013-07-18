/*!
 * \file    PVMemoryAttributes.h
 * \brief   Represents the bus attributes for a region of memory.
 * \date    Copyright 2005-2009 ARM Limited. All rights reserved.
 *
 * This defines attributes and methods that are private, subject to change and
 * that should not be used outside of PL310 model.
 */

#ifndef PVMEMORYATTRIBUTES_H
#define PVMEMORYATTRIBUTES_H

#include "sg/SGstdint.h"
#include <cassert>
#include <iosfwd>
#include "pv/PVBitField.h"
#include "pv/ACE.h"


namespace pv {

    /*! Encapsulate the attributes of a memory region. */
    class MemoryAttributesCommon
    {
    protected:
        MemoryAttributesCommon()
            : attr(), // default is all low, though technically this is an invalid combination (nshSO)
              user_flags(0),
              master_id(static_cast<uint32_t>(-1))
        {
        }

        /// We need to be able to perform fast comparisons of memory attributes
        /// To this end we bit pack the information.

    public:
        ARM_DEFINE_BITFIELD( Attr_t, uint32_t );

        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, inner_b,     0,0);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, inner_c,     1,1);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, inner_ra,    2,2);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, inner_wa,    3,3);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, inner_hit,   3,2);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, inner_cache, 3,0);

        // Must be contiguous with inner_cache so that both_cache works.
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, outer_b,     4 + 0, 4 + 0);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, outer_c,     4 + 1, 4 + 1);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, outer_ra,    4 + 2, 4 + 2);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, outer_wa,    4 + 3, 4 + 3);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, outer_hit,   4 + 3, 4 + 2);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, outer_cache, 4 + 3, 4 + 0);

        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, both_cache,  7, 0 ); // Both inner and outer cache.

        // Encoding is that of ACE::adomain_t
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, sh_domain,   9,8);

        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, privileged,  10,10);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, normal,      11,11);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, instruction, 12,12);
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, prot,        12,10);

        // Additional attributes added in v8
        // Device memory type can be relaxed to allow Gathering or Reordering
        // currently encoded as device (AXI4_AxCACHE_BUFFERABLE) with two relaxation flags:
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, device_reordering,  13,13 );    // meaningful only for device memory
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, device_gathering,   14,14 );    // meaningful only for device memory and with device_reordering set

        // normal inner/outer cacheable types include a transient hint
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, inner_transient,    15,15 );    // meaningful only for normal memory
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, outer_transient,    16,16 );    // meaningful only for normal memory


        // Define a mask of all those that are related to this class as opposed to
        // any derived class that also has added fields to this.
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, all_memoryattributes, 16,0);

        /// \name Fields used by TransactionAttributes
        ///
        //@{
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, exclusive,   17,17);

        /// The channel is being created for debug transactions.
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, is_debug,    18,18);

        /// The channel is being created for cache-maintenance transactions.  This
        /// must be set for NC/SO/DV cache-maintenance operations, but for C memory
        /// then it is optional.
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, is_cache_maintenance_operation,   19,19);

        // Define a mask of all those that are related to the TransactionAttributes
        // class as opposed to the base class or any other derived class that also
        // has added fields to this.
        ARM_DEFINE_BITFIELD_ENTRY( Attr_t, all_transactionattributes, 19,0);
        //@}

        ///
        /// \define ARM_ARCHMSG_MEMORYATTRIBUTES_FORMAT(FIELD) is a string literal
        ///         that defines how to print out a MemoryAttributes to an
        ///         ArchMsg stream.
        ///
        /// \a FIELD is the name of the field in the trace record that holds the
        /// attributes to print.  For example:
        ///       ARM_ARCHMSG_MEMORYATTRIBUTES_FORMAT( "ATTR" )
        ///
        /// NOTE the definition of this macro *must* be kept in sync with the
        /// field definitions in this class.
        ///
#define ARM_ARCHMSG_MEMORYATTRIBUTES_FORMAT(FIELD)                           \
         "i%{" FIELD "[3]:(w|W)}%{" FIELD "[2]:(r|R)}%{" FIELD "[1]:(m|M)}%{" FIELD "[0]:(b|B)}"  \
          "%{" FIELD "[14:13]:(|_nGRE|_?|_GRE)}%{" FIELD "[15]:(|_T)}" \
        "-o%{" FIELD "[7]:(w|W)}%{" FIELD "[6]:(r|R)}%{" FIELD "[5]:(m|M)}%{" FIELD "[4]:(b|B)}" \
          "%{" FIELD "[14:13]:(|_nGRE|_?|_GRE)}%{" FIELD "[16]:(|_T)}" \
        "-%{" FIELD "[9:8]:(nsh|ish|osh|sys)}"                               \
        "-%{" FIELD "[10]:(p|P)}%{" FIELD "[11]:(S|N)}%{" FIELD "[12]:(D|I)}" \
        "%{" FIELD "[17]:(|-excl)}"                                           \
        "%{" FIELD "[18]:(|-debug)}"                                          \
        "%{" FIELD "[19]:(|-cmo)}"

#define ARM_ARCHMSG_MEMORYATTRIBUTES_VERBOSE_FORMAT(FIELD)                \
        "inner-%{" FIELD "[3:0]:(device-|device-|cacheable-no-allocate|noncacheable|" \
                         "wRmb|wRmB|WT-cacheable|WB-cacheable|" \
                         "Rwmb|RwmB|WT-WAnRA-cacheable|WB-WAnRA-cacheable|" \
                         "RWmb|RWmB|WT-WA-cacheable|WB-WA-cacheable)}" \
        "%{" FIELD "[3:0.14:13]:(nGnRnE|nGRnE?|GnRnE?|GRnE?|nGnRE|nGRE|GnRE?|GRE|)}" \
        "%{" FIELD "[15]:(|-transient)}" \
        " outer-%{" FIELD "[7:4]:(device-|device-|cacheable-no-allocate|noncacheable|" \
                         "wRmb|wRmB|WT-cacheable|WB-cacheable|" \
                         "Rwmb|RwmB|WT-WAnRA-cacheable|WB-WAnRA-cacheable|" \
                         "RWmb|RWmB|WT-WA-cacheable|WB-WA-cacheable)}" \
        "%{" FIELD "[7:4.14:13]:(nGnRnE|nGRnE?|GnRnE?|GRnE?|nGnRE|nGRE|GnRE?|GRE|)}" \
        "%{" FIELD "[16]:(|-transient)}" \
        " shareability: %{" FIELD "[9:8]:(nsh|ish|osh|sys)}"

        
    protected:

        Attr_t   attr;

        /*! Space for private communication channel. */
        uint32_t user_flags;

        /*! Identify the initiator of transactions with these attributes. */
        uint32_t master_id;

    public:
        Attr_t getAttr() const { return attr; }
        void   setAttr(Attr_t attr_) { attr = attr_; }

        ///
        /// Take the mask_ and use it to transfer those bits from other_ to this
        /// class.
        ///
        /// Thus a 1 bit in mask_ will move that corresponding attribute bit across
        ///
        /// The mask should be constructed using:
        ///      MemoryAttributesCommon::inner_cache::mask
        ///      | MemoryAttributesCommon::outer_cache::mask
        /// etc.
        ///
        void modifyAttrFrom( MemoryAttributesCommon const& other_, uint32_t mask_ )
        {
            assert( (mask_ & ~all_transactionattributes::mask) == 0 );
            attr.rep = (attr.rep & ~mask_) | (other_.getAttr().rep & mask_);
        }

        // A memory attribute can store transaction attributes as well.  This
        // can be used to squash them.
        void squash_non_memory_attributes()
        {
            attr.rep = Fields<all_memoryattributes>::get(attr);
            assert( exclusive::get(attr) == false );
        }

    };


    class TransactionAttributes;
    class ExclusiveLockMaster;

    ///
    /// MemoryAttributes represents a set of attributes used to request a
    /// channel to be created between a ChannelMaster and a ChannelSlave.
    ///
    class MemoryAttributes : protected MemoryAttributesCommon
    {
    private:
        ExclusiveLockMaster *exclusive_lock_master;

    public: // for internal use only, to support internal code in PL310 model
        MemoryAttributes();

        Attr_t getAttr() const { return MemoryAttributesCommon::getAttr(); }
        void   setAttr(Attr_t attr_) { MemoryAttributesCommon::setAttr(attr_); }

        void modifyAttrFrom( MemoryAttributes const& other_, uint32_t mask_ )
        {
            return MemoryAttributesCommon::modifyAttrFrom( other_, mask_ );
        }
        
        inline MemoryAttributes(TransactionAttributes const&);
        inline void operator = (TransactionAttributes const&);

        /// \name AMBAAttributes AMBA Attributes
        ///
        ///    - bit[3] of AMBA is 'write-allocate'
        ///    - bit[2] of AMBA is 'read-allocate'
        ///    - bit[1] of AMBA used to be called Cacheable and now is called Modifiable
        ///    - bit[0] of AMBA is called Bufferable.
        ///
        /// For a _read_ the 'write-allocate' means that may have been allocated in the cache.
        ///
        /// For a _write_ the 'read-allocate' means that may have been allocated in the cache
        ///
        /// Thus the conditions for being hittable in a cache is that bit[3:2] != 2'b00
        ///
        /// We retain the \e old naming scheme.
        ///
        /// The new naming scheme has the token AMBA4 in the name, many of the new
        /// AMBA4 accessors are the same but are there for completeness.
        ///
        //@{
        bool isInnerBufferable() const;
        bool isInnerCacheable() const;
        bool isInnerReadAllocatable() const;
        bool isInnerWriteAllocatable() const;
        bool isInnerShareable() const;
        bool isOnlyInnerShareable() const;
        bool isShareable() const;

        /// Four bit encoding of cache bits (no shareability attribute).
        unsigned getInnerAsAMBA() const;

        bool isAMBA4InnerBufferable()       const { return isInnerBufferable(); }
        bool isAMBA4InnerModifyable()       const { return isInnerCacheable();  }
        bool isAMBA4InnerHittable()         const { return (getInnerAsAMBA() & (0x8 | 0x4)) != 0;  }
        bool isAMBA4InnerReadAllocatable()  const { return isInnerReadAllocatable(); }
        bool isAMBA4InnerWriteAllocatable() const { return isInnerWriteAllocatable(); }

        bool isAMBA4InnerWriteBackCacheable() const { return isInnerCacheable() &&  ((getInnerAsAMBA() & (0x1)) != 0); }

        bool isV8InnerTransient()   const;

        /// Four bit encoding of cache bits (no shareability attribute).
        unsigned getInnerAsAMBA4()          const { return getInnerAsAMBA(); }

        bool isOuterBufferable() const;
        bool isOuterCacheable() const;
        bool isOuterReadAllocatable() const;
        bool isOuterWriteAllocatable() const;
        bool isOuterShareable() const;

        bool isV8OuterTransient()   const;

        /// Four bit encoding of cache bits (no shareability attribute).
        unsigned getOuterAsAMBA() const;

        bool isAMBA4OuterBufferable()       const { return isOuterBufferable(); }
        bool isAMBA4OuterModifyable()       const { return isOuterCacheable();  }
        bool isAMBA4OuterHittable()         const { return (getOuterAsAMBA4() & (0x8 | 0x4)) != 0;  }
        bool isAMBA4OuterReadAllocatable()  const { return isOuterReadAllocatable(); }
        bool isAMBA4OuterWriteAllocatable() const { return isOuterWriteAllocatable(); }

        /// Four bit encoding of cache bits (no shareability attribute).
        unsigned getOuterAsAMBA4()          const { return getOuterAsAMBA(); }

        // relaxed device types introduced with v8
        bool isV8Device() const { return isOuterDVSO(); }
        bool isV8DeviceEarlyterminate() const { unsigned const acache = getOuterAsAMBA(); return acache == 1; }
        bool isV8DeviceReordering() const;
        bool isV8DeviceGathering() const;

        //@}

        bool isPrivileged() const;
        bool isNormalWorld() const;
        bool isInstruction() const;

        /// Three bit encoding of prot bits
        unsigned getProtAsAMBA() const;

        /// \name ARM memory type predicates
        //@{
        bool     isInnerDVSO()   const { unsigned const acache = getInnerAsAMBA(); return acache <= 1; }
        bool     isOuterDVSO()   const { unsigned const acache = getOuterAsAMBA(); return acache <= 1; }
        bool     isInnerNormal() const { return ! isInnerDVSO(); }
        bool     isOuterNormal() const { return ! isOuterDVSO(); }
        //@}

        /// In later versions of the ARMARM architecture then inner NC (normal
        /// non-cacheable) and outer NC (normal non-cacheable) are treated as
        /// special.
        ///
        /// We distinguish between NC and NC-NB (non-bufferable).  The architecture
        /// isn't clear about the latter as it can't be generated!
        bool     isInnerNCOuterNC()       const { return both_cache::get(attr) == 0x33; }
        bool     isInnerNCanyOuterNCany() const { return (both_cache::get(attr) & 0xEE) == 0x22; }

        uint32_t getUserFlags() const;
        uint32_t getMasterID() const;
        ExclusiveLockMaster *getExclusiveLockMaster() const;

        void setInnerBufferable(bool on);
        void setInnerCacheable(bool on);
        void setInnerReadAllocatable(bool on);
        void setInnerWriteAllocatable(bool on);
        void setV8InnerTransient(bool on);    // v8

        /// Four bit encoding of cache bits (no shareability attribute).
        void setInnerFromAMBA(unsigned int amba_flags);

        void setOuterBufferable(bool on);
        void setOuterCacheable(bool on);
        void setOuterReadAllocatable(bool on);
        void setOuterWriteAllocatable(bool on);
        void setV8OuterTransient(bool on);    // v8

        /// Four bit encoding of cache bits (no shareability attribute).
        void setOuterFromAMBA(unsigned int amba_flags);

        /// Determine the shareability of the transaction
        void setShareability( ACE::adomain_t domain_ )
        {
            sh_domain::set( attr, domain_ );
            assert( getShareability() == domain_ );
        }

        /// Get the shareability of the transaction
        ACE::adomain_t getShareability() const
        {
            return static_cast<ACE::adomain_t>( sh_domain::get(attr) );
        }

        bool isSystemShareable() const { return getShareability() == ACE::adomain_system; }

        void setV8DeviceReordering(bool on);
        void setV8DeviceGathering(bool on);

        void setPrivileged(bool on);
        void setNormalWorld(bool on);
        void setInstruction(bool on);
        void setProtFromAMBA(unsigned int amba_flags);

        void setUserFlags(uint32_t);
        void setMasterID(uint32_t);
        void setExclusiveLockMaster(ExclusiveLockMaster *exclusive_lock_master);

        /*! Provide a comparison operator to allow attributes to be stored in a map. */
        bool operator < (const MemoryAttributes& compare) const;

        /*! Provide a comparison operator to allow attributes to be compared. */
        bool operator == (const MemoryAttributes& compare) const;

        /*! Provide a comparison operator to allow attributes to be compared. */
        bool operator != (const MemoryAttributes& compare) const
        {
            return !(*this == compare);
        }

    private:
        bool operator <  (const TransactionAttributes& compare) const; // disallow!
        bool operator == (const TransactionAttributes& compare) const; // disallow!
        bool operator != (const TransactionAttributes& compare) const; // disallow!
    public:

        std::ostream& print(std::ostream& os_) const;

        void dbg_print() const; // print to std::cerr
    };

    /*! Stream to an std::ostream. */
    std::ostream& operator << ( std::ostream& os_, MemoryAttributes const& o_ );

} // namespace pv

#endif // PVMEMORYATTRIBUTES_H
