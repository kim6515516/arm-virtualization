/*!
 * \file    ACE.h
 * \brief   Coherency extensions to memory systems.
 * \date    Copyright 2009-2011 ARM Limited. All rights reserved.
 *
 */

#ifndef ARM_ACE_H
#define ARM_ACE_H

#include "sg/IncludeMeFirst.h"
#include <iostream>
#include <cassert>
#include "sg/SGstdint.h"

#include "pv/PVBitField.h"
#include "pv/PVRange.h"
#include "pv/PVBusAddr.h"

namespace pv
{
    class MemoryAttributes;
}

namespace ACE
{
    ///
    /// Encode the ACE operation that we should perform.  This corresponds to
    /// some conflation of AxSNOOP and AxBAR.
    ///
    enum ace_operation_t
    {
        //
        // NOTE enumerators are important
        //


        /// \name Snoop requests
        ///
        /// This set of operations can be sent downstream, or upstream
        //@{
        ReadNoSnoop,   // ACE encodes this is as ReadOnce and ADOMAIN == non-shared or full-system
        ReadOnce,
        ReadClean,
        ReadShared,
        ReadNotSharedDirty,
        ReadUnique,
        CleanShared,
        CleanInvalid,
        MakeInvalid,
        //@}

        CleanUnique,
        MakeUnique,

        WriteNoSnoop,   // ACE encodes this is as ReadOnce and ADOMAIN == non-shared or full-system
        PseudoWriteOnce, // Non-ACE operation used for cores to communicate directly with L1
                         // this does _not_ require a Write Through to main memory, whereas
                         // WriteUnique* does.
        WriteUnique,
        WriteLineUnique,
        WriteBack,
        WriteClean,
        Evict,

        ///
        /// Default is used to indicate 'do the right thing based on
        /// shareability'.
        ///
        /// So an AXI3 master, it will have no concept of shareability and so
        /// would have set the adomain to non-shared or system.  These will be
        /// translated to ReadNoSnoop/WriteNoSnoop.  If the AXI3 master has a
        /// version of shareability on AUSER then it should set the shareability
        /// correctly in the MemoryAttributes as well and then we will translate
        /// it into ReadOnce/PseudoWriteOnce.
        ///
        /// For non-AXI things, like I-side and D-side BIUs then it can just set
        /// the shareability and mark it as 'Default' and it will JustWork (tm).
        ///
        Default,

        /// Never used on a channel
        Memory_Barrier,  // NOTE: "MemoryBarrier" is #defined by Windows.h so can cannot be used
        /// Never used on a channel
        SynchronisationBarrier,

        /// Pseudo-operation used to indicate that the upstream port should not
        /// respond to this request.
        NoOperation,

        /// Pseudo-operation representing a debug read.  In this case, all
        /// memory is treated as shared and it will be snooped from everywhere.
        DebugRead,

        /// Pseudo-operation representing a debug write.  In this case, all
        /// copies of the line will be altered, even if they are non-shared or
        /// upstream of a master.  NOTE that this will 'undo' cache incoherency
        /// for modelled, enabled caches for the affected bytes.
        DebugWrite


#if 0
        switch()
        {
        case ACE::ReadNoSnoop:
            break;
        case ACE::ReadOnce:
            break;
        case ACE::ReadClean:
            break;
        case ACE::ReadShared:
            break;
        case ACE::ReadNotSharedDirty:
            break;
        case ACE::ReadUnique:
            break;
        case ACE::CleanShared:
            break;
        case ACE::CleanInvalid:
            break;
        case ACE::MakeInvalid:
            break;
        case ACE::CleanUnique:
            break;
        case ACE::MakeUnique:
            break;
        case ACE::WriteNoSnoop:
            break;
        case ACE::PseudoWriteOnce:
            break;
        case ACE::WriteUnique:
            break;
        case ACE::WriteLineUnique:
            break;
        case ACE::WriteBack:
            break;
        case ACE::WriteClean:
            break;
        case ACE::Evict:
            break;
        case ACE::Default:
            break;
        case ACE::Memory_Barrier:
            break;
        case ACE::SynchronisationBarrier:
            break;
        case ACE::NoOperation:
            break;
        case ACE::DebugRead:
            break;
        case ACE::DebugWrite:
            break;
        }
#endif

    };

    // ACE operation encoding on AxSNOOP AMBA channel
    enum axsnoop_t
    {
        ARSNOOP_READ_NO_SNOOP         = 0x0,
        ARSNOOP_READ_ONCE             = 0x0,
        ARSNOOP_READ_SHARED           = 0x1,
        ARSNOOP_READ_CLEAN            = 0x2,
        ARSNOOP_READ_NOT_SHARED_DIRTY = 0x3,
        ARSNOOP_READ_UNIQUE           = 0x7,
        ARSNOOP_CLEAN_SHARED          = 0x8,
        ARSNOOP_CLEAN_INVALID         = 0x9,
        ARSNOOP_CLEAN_UNIQUE          = 0xB,
        ARSNOOP_MAKE_UNIQUE           = 0xC,
        ARSNOOP_MAKE_INVALID          = 0xD,

        AWSNOOP_WRITE_NO_SNOOP        = 0x0,
        AWSNOOP_WRITE_UNIQUE          = 0x0,
        AWSNOOP_WRITE_LINE_UNIQUE     = 0x1,
        AWSNOOP_WRITE_CLEAN           = 0x2,
        AWSNOOP_WRITE_BACK            = 0x3,

        AxSNOOP_BARRIER               = 0x0,
        AxSNOOP_EVICT                 = 0x4,

        ARSNOOP_DVM_COMPLETE          = 0xE,
        ARSNOOP_DVM_MESSAGE           = 0xF
    };


    ///
    /// Does the ACE operation appear on the read channel.
    ///
    /// NOTE that this excludes Default.
    ///
    inline bool is_read_channel_ace_operation( ace_operation_t t_ )
    {
        return
            ((0
              | 1u << ReadNoSnoop
              | 1u << ReadOnce
              | 1u << ReadClean
              | 1u << ReadShared
              | 1u << ReadNotSharedDirty
              | 1u << ReadUnique
              | 1u << CleanShared
              | 1u << CleanInvalid
              | 1u << MakeInvalid
              | 1u << CleanUnique
              | 1u << MakeUnique
              | 1u << Memory_Barrier
              | 1u << SynchronisationBarrier
              | 1u << DebugRead
                ) & (1u << t_))
            != 0;
    }

    ///
    /// Does the ACE operation on the write channel
    ///
    /// NOTE that this excludes Default.
    ///
    inline bool is_write_channel_ace_operation( ace_operation_t t_ )
    {
        return
            ((0
              | 1u << WriteNoSnoop
              | 1u << PseudoWriteOnce
              | 1u << WriteUnique
              | 1u << WriteLineUnique
              | 1u << WriteBack
              | 1u << WriteClean
              | 1u << Evict
              | 1u << DebugWrite
                ) & (1u << t_))
            != 0;
    }


    inline std::ostream& operator << ( std::ostream& os_, ace_operation_t t_ )
    {
        switch(t_)
        {
        case ACE::ReadNoSnoop:             return os_ << "ReadNoSnoop";
        case ACE::ReadOnce:                return os_ << "ReadOnce";
        case ACE::ReadClean:               return os_ << "ReadClean";
        case ACE::ReadShared:              return os_ << "ReadShared";
        case ACE::ReadNotSharedDirty:      return os_ << "ReadNotSharedDirty";
        case ACE::ReadUnique:              return os_ << "ReadUnique";
        case ACE::CleanShared:             return os_ << "CleanShared";
        case ACE::CleanInvalid:            return os_ << "CleanInvalid";
        case ACE::MakeInvalid:             return os_ << "MakeInvalid";
        case ACE::CleanUnique:             return os_ << "CleanUnique";
        case ACE::MakeUnique:              return os_ << "MakeUnique";
        case ACE::WriteNoSnoop:            return os_ << "WriteNoSnoop";
        case ACE::PseudoWriteOnce:         return os_ << "PseudoWriteOnce";
        case ACE::WriteUnique:             return os_ << "WriteUnique";
        case ACE::WriteLineUnique:         return os_ << "WriteLineUnique";
        case ACE::WriteBack:               return os_ << "WriteBack";
        case ACE::WriteClean:              return os_ << "WriteClean";
        case ACE::Evict:                   return os_ << "Evict";
        case ACE::Default:                 return os_ << "Default";
        case ACE::Memory_Barrier:          return os_ << "MemoryBarrier";
        case ACE::SynchronisationBarrier:  return os_ << "SynchronisationBarrier";
        case ACE::NoOperation:             return os_ << "NoOperation";
        case ACE::DebugRead:               return os_ << "DebugRead";
        case ACE::DebugWrite:              return os_ << "DebugWrite";
        }
        return os_ << "<Error>";
    }

    // Translate ARSNOOP 4-bit field to an ace_operation_t
    // Requires ARDOMAIN and ARBAR to disambiguate
    inline ace_operation_t ace_operation_from_ARSNOOP(unsigned arsnoop,
                                                      unsigned ardomain,
                                                      unsigned arbar)
    {
        switch(arsnoop)
        {
        case ARSNOOP_READ_NO_SNOOP:
            if ((arbar & (1<<0)) != 0)             // is ARBAR[0] set indicating a barrier
            {
               if ((arbar & (1<<1)) != 0)          // is ARBAR[1] set
                  return SynchronisationBarrier;
               else
                  return Memory_Barrier;
            }
            if ((ardomain == 1)||(ardomain == 2))  // ARDOMAIN[1:0} is Inner or Outer Shared
               return ReadOnce;
            else
               return ReadNoSnoop;

        case ARSNOOP_READ_SHARED:           return ReadShared;
        case ARSNOOP_READ_CLEAN:            return ReadClean;
        case ARSNOOP_READ_NOT_SHARED_DIRTY: return ReadNotSharedDirty;
        case AxSNOOP_EVICT:                 return Evict;
        case ARSNOOP_READ_UNIQUE:           return ReadUnique;
        case ARSNOOP_CLEAN_SHARED:          return CleanShared;
        case ARSNOOP_CLEAN_INVALID:         return CleanInvalid;
        case ARSNOOP_CLEAN_UNIQUE:          return CleanUnique;
        case ARSNOOP_MAKE_UNIQUE:           return MakeUnique;
        case ARSNOOP_MAKE_INVALID:          return MakeInvalid;
        default:                            return NoOperation;
        }
    }

    // Translate AWSNOOP 4-bit field to an ace_operation_t
    // Requires AWDOMAIN and AWBAR to disambiguate
    inline ace_operation_t ace_operation_from_AWSNOOP(unsigned awsnoop,
                                                      unsigned awdomain,
                                                      unsigned awbar)
    {
        switch(awsnoop)
        {
        case AWSNOOP_WRITE_NO_SNOOP:
            if ((awbar & (1<<0)) != 0)             // is ARBAR[0] set indicating a barrier
            {
               if ((awbar & (1<<1)) != 0)          // is ARBAR[1] set
                  return SynchronisationBarrier;
               else
                  return Memory_Barrier;
            }
            if ((awdomain == 1)||(awdomain == 2))  // ARDOMAIN[1:0] is Inner or Outer Shared
               return WriteUnique;
            else
               return WriteNoSnoop;
 
        case AWSNOOP_WRITE_LINE_UNIQUE:     return WriteLineUnique;
        case AWSNOOP_WRITE_CLEAN:           return WriteClean;
        case AWSNOOP_WRITE_BACK:            return WriteBack;
        case AxSNOOP_EVICT:                 return Evict;
        default:                            return NoOperation;
        }
    }

    /// Translate ace_operation_t to an AxSNOOP 4-bit encoding
    inline unsigned AxSNOOP_from_ace_operation(ace_operation_t operation)
    {
        switch(operation)
        {
        case ReadNoSnoop:            return ARSNOOP_READ_NO_SNOOP;
        case ReadOnce:               return ARSNOOP_READ_ONCE;
        case ReadShared:             return ARSNOOP_READ_SHARED;
        case ReadClean:              return ARSNOOP_READ_CLEAN;
        case ReadNotSharedDirty:     return ARSNOOP_READ_NOT_SHARED_DIRTY;
        case ReadUnique:             return ARSNOOP_READ_UNIQUE;
        case CleanUnique:            return ARSNOOP_CLEAN_UNIQUE;
        case MakeUnique:             return ARSNOOP_MAKE_UNIQUE;
        case CleanShared:            return ARSNOOP_CLEAN_SHARED;
        case CleanInvalid:           return ARSNOOP_CLEAN_INVALID;
        case MakeInvalid:            return ARSNOOP_MAKE_INVALID;

        case WriteNoSnoop:           return AWSNOOP_WRITE_NO_SNOOP;
        case WriteUnique:            return AWSNOOP_WRITE_UNIQUE;
        case WriteLineUnique:        return AWSNOOP_WRITE_LINE_UNIQUE;
        case WriteClean:             return AWSNOOP_WRITE_CLEAN;
        case WriteBack:              return AWSNOOP_WRITE_BACK;

        case Evict:                  return AxSNOOP_EVICT;
        case Memory_Barrier:         return AxSNOOP_BARRIER;
        case SynchronisationBarrier: return AxSNOOP_BARRIER;

        case PseudoWriteOnce:
        case Default:
        case NoOperation:
        case DebugRead:
        case DebugWrite:
           break;
        }

        return 0x0; // !!
    }

    ///
    /// The 'shareability' domain of the transaction.
    ///
    /// NOTE that the ACE domain is not specifically represented in the
    /// ACE::Payload as we use the MemoryAttributes to determine it.  These are
    /// stored in pv::MemoryAttributes.
    ///
    enum adomain_t
    {
        // VALUES IMPORTANT: Map onto ACE wire protocol.

        /// Non-shared (nsh) -- no coherency required.
        adomain_non_shared = 0,

        /// Inner-shared (ish) -- only coherency required for masters in the same
        /// inner shareability domain as the issuing master.
        adomain_inner_shared = 1,

        /// Outer-shared (osh) -- coherency required for all masters in the same outer
        /// shareability domain as the issuing master.
        ///
        /// \note If something is osh, then in ACE it must also be ish.
        adomain_outer_shared = 2,

        /// All masters in the system are considered part of the same domain,
        /// including those with no coherency support and no caches.  This means
        /// that a transaction is not cacheable at \e any level of the
        /// hierarchy.
        adomain_system = 3

#if 0
        switch()
        {
        case ACE::adomain_non_shared:
        case ACE::adomain_inner_shared:
        case ACE::adomain_outer_shared:
        case ACE::adomain_system:
        }
#endif
    };

    inline adomain_t strongestADOMAIN( adomain_t a_, adomain_t b_ )
    {
        return a_ > b_ ? a_ : b_;
    }

    ///
    /// The information about how this transaction interacts with barriers.
    ///
    /// \note This is not exactly the same use as cachein ACE where it is used to
    /// indicate barrier transactions -- instead we fold that ace_operation_t.
    ///
    enum abar_t
    {
        /// A normal transaction that respects barriers.
        abar_respect_barriers = 0,

        /// A transaction that ignores barriers.
        abar_ignore_barriers = 2
    };

    inline std::ostream& operator << (std::ostream& os_, adomain_t t_)
    {
        switch(t_)
        {
        case adomain_non_shared:   return os_ << "nsh";
        case adomain_inner_shared: return os_ << "ish";
        case adomain_outer_shared: return os_ << "osh";
        case adomain_system:       return os_ << "sys";
        }
        return os_ << "<ERROR>";
    }

    inline bool isInnerShareable( adomain_t t_ )
    {
        return t_ == adomain_inner_shared || t_ == adomain_outer_shared;
    }

    inline bool isOnlyInnerShareable( adomain_t t_ )
    {
        return t_ == adomain_inner_shared;
    }

    inline bool isShareable( adomain_t t_ )
    {
        return isInnerShareable(t_);
    }

    inline bool isOuterShareable( adomain_t t_ )
    {
        return t_ == adomain_outer_shared;
    }

    /// If we have 'Default' as ace_operation_t then given the read/writeness
    /// and the shareability convert it to
    /// ReadNoSnoop/WriteNoSnoop/PseudoWriteOnce/ReadOnce as appropriate.
    inline ace_operation_t default_ace_operation_for(
        bool              is_read_,
        ACE::adomain_t    adomain_,
        bool              is_hittable_
        )
    {
        if (is_hittable_ && isShareable(adomain_))
            return is_read_ ? ReadOnce : PseudoWriteOnce;
        else
            return is_read_ ? ReadNoSnoop : WriteNoSnoop;
    }

    class ace_rresp_t;

    ///
    /// ace_crresp_t
    ///
    /// NOTE that CRRESP and RRESP are very similar.  CRRESP has extra fields
    /// WasUnique and also IsShared -- this is because we say if the line \e
    /// WasUnique in the upstream system and also if we are keeping a copy of it
    /// (\e IsShared).
    ///
    /// NOTE that crresp is a superset of rresp.
    ///
    /// It is convenient for many functions to actually always compute CRRESP
    /// and then assign it as RRESP.
    ///
    class ace_crresp_t
    {
    protected:
        ARM_DEFINE_BITFIELD( rep_t, uint8_t );
        ARM_DEFINE_BITFIELD_ENTRY( rep_t, DataTransfer, 0,0 ); // CRRESP only
        ARM_DEFINE_BITFIELD_ENTRY( rep_t, Error,        1,1 ); // CRRESP only
        ARM_DEFINE_BITFIELD_ENTRY( rep_t, PassDirty,    2,2 );
        ARM_DEFINE_BITFIELD_ENTRY( rep_t, IsShared,     3,3 );
        ARM_DEFINE_BITFIELD_ENTRY( rep_t, IsSharedPassDirty, 3,2 );
        ARM_DEFINE_BITFIELD_ENTRY( rep_t, WasUnique,    4,4 ); // CRRESP only
        rep_t   rep;
        // CRRESP[0] DataTransfer
        // CRRESP[1] Error
        // CRRESP[2] PassDirty
        // CRRESP[3] IsShared
        // CRRESP[4] WasUnique

        friend class ace_rresp_t;
    public:

        ace_crresp_t()
        {
        }

        ace_crresp_t( bool dirty_, bool unique_, bool was_unique_, bool data_transfer_ )
        {
            init(dirty_, unique_, was_unique_, data_transfer_);
        }

        ///
        /// \name Common RRESP and CRRESP operations
        ///
        //@{
        void removeUnique()
        {
            IsShared::set(rep, true);
        }

        void setPassDirty()
        {
            PassDirty::set(rep, true);
        }

        bool isPassDirty() const { return PassDirty::get(rep) != 0; }
        bool isShared()    const { return IsShared::get(rep) != 0;  }
        bool isUnique()    const { return ! isShared();             }
        //@}

        void init( bool dirty_, bool unique_, bool was_unique_, bool data_transfer_ )
        {
            PassDirty::set(rep, dirty_);
            IsShared::set(rep, ! unique_);
            WasUnique::set(rep, was_unique_ );
            DataTransfer::set(rep, data_transfer_ );
            Error::set(rep, false);
            assert( isPassDirty() == dirty_ );
            assert( isUnique() == unique_ );
            assert( isWasUnique() == was_unique_ );
            assert( isDataTransfer() == data_transfer_ );
            assert( !isError());
        }

        void setDataTransfer()
        {
            DataTransfer::set(rep, true);
        }

        void setError()
        {
            Error::set(rep, true);
            assert( isError() );
        }

        void setWasUnique()
        {
            WasUnique::set(rep, true);
            assert( isWasUnique() );
        }

        bool isDataTransfer() const { return DataTransfer::get(rep) != 0; }
        bool isError() const { return Error::get(rep) != 0; }
        bool isWasUnique() const { return WasUnique::get(rep) != 0; }


        ///
        /// Mask the IsShared and PassDirty bits according to this bitmask:
        ///    - bit[0] is PassDirty
        ///    - bit[1] is IsShared
        void maskIsSharedAndPassDirty( unsigned mask_ )
        {
            IsSharedPassDirty::set( rep, mask_ & IsSharedPassDirty::get(rep) );
        }

        ///
        /// Accumulate DataTransfer, Error, PassDirty, Uniqueness and WasUnique.
        ///
        /// If you start with a blank ace_crresp_t and get (potentially)
        /// multiple upstream responses then the end response of the whole thing
        /// is that of the accumulated result.
        ///
        /// Thus the accumulated result is DataTransfer if any of them responded
        /// with DataTransfer.
        ///
        /// The accumulated result is Error if any of them responded with Error.
        ///
        /// The accumulated result is PassDirty if any of them responded with
        /// PassDirty.
        ///
        /// The accumulated result is IsShared (!Unique) if any returned
        /// IsShared.
        ///
        /// The accumulated result is WasUnique if the respondee WasUnique.
        ///
        void accumulate( ace_crresp_t const& o_ )
        {
            // We have told people to construct a blank ace_crresp_t and then
            // accumulate results into it -- this is a precondition for this to
            // work.
            assert( ! ace_crresp_t().isDataTransfer() );
            assert( ! ace_crresp_t().isError()        );
            assert( ! ace_crresp_t().isPassDirty()    );
            assert(   ace_crresp_t().isUnique()       );
            assert( ! ace_crresp_t().isShared()       );
            assert( ! ace_crresp_t().isWasUnique()    );

            bool const dbg_prior_data_transfer = isDataTransfer();
            bool const dbg_prior_pass_dirty    = isPassDirty();
            bool const dbg_prior_shared        = isShared();
            (void)dbg_prior_data_transfer;
            (void)dbg_prior_pass_dirty;
            (void)dbg_prior_shared;

            //
            // All the rules boil down to:
            //
            rep.rep |= o_.rep.rep;

            // We can never remove sharedness once it has been asserted.
            assert( (dbg_prior_shared && isShared())
                    || ( ! dbg_prior_shared
                         && isShared() == o_.isShared() ) );

            // We can never remove PassDirty
            assert( (dbg_prior_pass_dirty && isPassDirty())
                    || ( ! dbg_prior_pass_dirty
                         && isPassDirty() == o_.isPassDirty() ) );

            // We can never remove DataTransfer
            assert( (dbg_prior_data_transfer && isDataTransfer())
                    || ( ! dbg_prior_data_transfer
                         && isDataTransfer() == o_.isDataTransfer() ) );
        }
    };

    ///
    /// This is a representation of the extra fields for RRESP[3:2].
    ///
    /// Bits [1:0] are encoded by the pv::Tx_Result.
    ///
    /// NOTE that an RRESP is-a CRRESP but with some fields inaccessible.
    ///
    class ace_rresp_t : public ace_crresp_t
    {
    public:

        ace_rresp_t()
        {
            // Default construction gives:
            assert( ! isPassDirty() && ! isShared() );
        }

        ace_rresp_t( bool dirty_, bool unique_ )
        {
            init(dirty_,  unique_);
        }

        explicit ace_rresp_t( ace_crresp_t crresp_ )
        {
            rep = crresp_.rep;
        }

        void init( bool dirty_, bool unique_ )
        {
            PassDirty::set(rep, dirty_);
            IsShared::set(rep, ! unique_);
            assert( isPassDirty() == dirty_  );
            assert( isUnique()    == unique_ );
        }

    private: // Operations inherited from CRRESP that are illegal on an RRESP

        void init( bool dirty_, bool unique_, bool was_unique_, bool data_transfer_ )
        {
            (void)dirty_; (void)unique_; (void)was_unique_; (void)data_transfer_;
            assert(0); // disallow
        }

        void setDataTransfer()
        {
            assert(0); // disallow
        }

        void setError()
        {
            assert(0); // disallow
        }

        void setWasUnique()
        {
            assert(0);
        }

        bool isDataTransfer() const { assert(0); return false; }
        bool isError()        const { assert(0); return false; }
        bool isWasUnique()    const { assert(0); return false; }
    };

    inline std::ostream& operator << (std::ostream& os_, ace_rresp_t t_)
    {
        return os_ << (t_.isPassDirty() ? "PassDirty" : "PassClean")
                   << (t_.isUnique()    ? "-Unique"   : "-Shared"  )
            ;
    }


    inline std::ostream& operator << (std::ostream& os_, ace_crresp_t t_)
    {
        return os_ << (t_.isPassDirty()    ? "PassDirty"     : "PassClean")
                   << (t_.isUnique()       ? "-Unique"       : "-Shared"  )
                   << (t_.isDataTransfer() ? "-DataTransfer" : "")
                   << (t_.isWasUnique()    ? "-WasUnique"    : "")
                   << (t_.isError()        ? "-Error"        : "")
            ;
    }

    ///
    /// Transaction payload for a down-stream ACE transaction that is in
    /// addition to the standard AXI formulation.
    ///
    class Payload
    {
        ace_operation_t operation;
        abar_t          abar;
        ace_rresp_t     rresp;
    public:
        Payload()
            : operation       ( Default               ),
              abar            ( abar_respect_barriers )
        {
        }

        void init(
            ace_operation_t operation_,
            abar_t          abar_
            )
        {
            operation = operation_;
            abar      = abar_;
            rresp     = ace_rresp_t();
        }

        void assign_ace_payload(Payload const& p_)
        {
            *this = p_;
        }

        ///
        /// Return the ACE operation this corresponds to.
        ///
        ace_operation_t get_ace_operation() const
        {
            return operation;
        }

        ///
        /// Return the filtered ACE operation.
        ///
        /// Sometimes the bus system will change the memory attributes of a
        /// transaction as it flows through the system, however, it might not
        /// change the ACE operation that it would be allowed -- for example,
        /// adding or removing shareability.  As a result the operation returned
        /// by get_ace_operation() may not be appropriate for the current
        /// transaction attributes.  This function will filter and squash the
        /// ACE operation to that appropriate to the memory attributes.
        ///
        ace_operation_t  get_ace_operation( pv::MemoryAttributes const* attributes_ );

        ///
        /// Setup the ACE operation to perform
        ///
        void set_ace_operation( ACE::ace_operation_t operation_ )
        {
            operation = operation_;
        }

        ///
        /// Return the ACE operation this corresponds to.
        ///
        abar_t get_abar() const
        {
            return abar;
        }

        ///
        /// Return the ACE operation this corresponds to.
        ///
        void set_abar( abar_t abar_ )
        {
            abar = abar_;
        }

        /// Excludes 'Default'
        bool is_read_channel_ace_operation() const
        {
            return ACE::is_read_channel_ace_operation(get_ace_operation());
        }

        /// Excludes 'Default'
        bool is_write_channel_ace_operation() const
        {
            return ACE::is_write_channel_ace_operation(get_ace_operation());
        }

        bool is_default_ace_operation() const
        {
            return get_ace_operation() == Default;
        }

        ///
        /// \name Accessors for RRESP (valid only if a read)
        ///
        //@{
        void        set_rresp(ace_rresp_t rresp_) { rresp = rresp_;             }
        ace_rresp_t get_rresp() const             { return rresp;               }
        bool        is_rresp_pass_dirty() const   { return rresp.isPassDirty(); }
        bool        is_rresp_unique() const       { return rresp.isUnique();    }
        
        ///
        /// Mask the IsShared and PassDirty bits according to this bitmask:
        ///    - bit[0] is PassDirty
        ///    - bit[1] is IsShared
        void maskIsSharedAndPassDirty( unsigned mask_ )
        {
            rresp.maskIsSharedAndPassDirty(mask_);
        }

        //@}

        /// Is this request for a cache maintenance operation?
        bool is_for_a_cache_maintenance_operation() const
        {
            return 0 != ( (1u << operation)
                          & (1u << CleanShared
                             | 1u << CleanInvalid
                             | 1u << MakeInvalid) );
        }

        /// Is this request without a data payload?
        bool is_without_data() const
        {
            return 0 != ( (1u << operation)
                          & (  1u << CleanShared
                             | 1u << CleanInvalid
                             | 1u << MakeInvalid
                             | 1u << CleanUnique
                             | 1u << MakeUnique
                             | 1u << Memory_Barrier
                             | 1u << SynchronisationBarrier
                             | 1u << Evict) );
        }

        /// Return the ACE AxBAR signal encoding this payload corresponds to
        unsigned get_ace_AxBAR() const
        {
            switch(operation)
            {
            case ACE::Memory_Barrier:          
            case ACE::SynchronisationBarrier:
               return abar | (1<<0);

            default:
               return abar;
            }
        }

        /// Return the ACE AxSNOOP signal encoding this payload corresponds to
        unsigned get_ace_AxSNOOP() const
        {
            return AxSNOOP_from_ace_operation(operation);
        }
    };

    ///
    /// A snoop request upstream.
    ///
    /// If multiple masters are connected to a single port (which is illegal in
    /// HW!) then the SnoopRequest is sent to all connected masters.  This acts
    /// a bit like a mini-interconnect and the masters have to cooperate to
    /// ensure that the request behaves correctly.
    ///
    /// What this actually means is that it can receive a snoop request
    /// NoOperation that it should ignore!.
    ///
    class SnoopRequest
    {
        /// The address range that the request should touch.  The top bit is the
        /// NS bit (1 means non-secure).  The bottom 56 bits are the address.
        /// The rest are reserved.
        pv::range_t<uint64_t>   ns_addr_range;
        ace_operation_t         operation;
        uint8_t*                storage;
        ace_crresp_t            crresp;

        ///
        /// This is used for linting cache maintenance operations and does not
        /// represent anything that is transported in the real ACE.
        ///
        /// Record the domain and the downstream operation that this snoop
        /// request was is in response to.
        ///
        //@{
        adomain_t               domain;
        ace_operation_t         for_downstream_operation;
        //@}

        static uint64_t const ns_mask      = uint64_t(1) << 63;
        static uint64_t const ns_addr_mask = ~ns_mask;
    public:

        SnoopRequest() : operation(NoOperation) {}

        // For debug purposes set the ns_addr_range to empty
        void dbg_set_to_empty()
        {
            ns_addr_range = pv::range_empty<uint64_t>();
            operation     = ACE::NoOperation;
            storage       = 0;
        }

        void         set_crresp(ace_crresp_t crresp_) { crresp = crresp_; }
        ace_crresp_t get_crresp() const               { return crresp;    }

        bool is_crresp_data_transfer() const { return crresp.isDataTransfer(); }
        bool is_crresp_was_unique()    const { return crresp.isWasUnique();    }
        bool is_crresp_pass_dirty()    const { return crresp.isPassDirty();    }
        bool is_crresp_unique()        const { return crresp.isUnique();       }

        /// Initialise.
        void init(
            pv::range_t<uint64_t>        ns_addr_range_,
            ace_operation_t              operation_,
            uint8_t*                     storage_,
            adomain_t                    domain_,
            ace_operation_t              downstream_operation_causing_this_snoop_
            )
        {
            ns_addr_range                        = ns_addr_range_;
            operation                            = operation_;
            storage                              = storage_;
            domain                               = domain_;
            for_downstream_operation             = downstream_operation_causing_this_snoop_;
        }

        unsigned size() const { return unsigned(ns_addr_range.size()); }

        uint8_t*       get_storage()       { return storage; }
        uint8_t const* get_storage() const { return storage; }

        void set_storage( uint8_t* storage_ ) { storage = storage_; }

        /// Does the operation correspond to a valid request, rather than a
        /// previously satisfied request that should be ignored?
        bool is_valid_operation() const
        {
            return operation != NoOperation;
        }

        ace_operation_t get_ace_operation() const
        {
            return operation;
        }

        /// Is this snoop request in response to a cache maintenance operation?
        bool is_for_a_cache_maintenance_operation() const
        {
            return 0 != ( (1u << for_downstream_operation)
                          & (1u << CleanShared
                             | 1u << CleanInvalid
                             | 1u << MakeInvalid) );
        }

        /// Return the ace operation that caused this snoop operation.
        ace_operation_t get_downstream_operation_causing_this_snoop() const
        {
            return for_downstream_operation;
        }
        
        /// Return adomain_inner_shared/adomain_outer_shared of the operation
        /// that cause this snoop request.
        adomain_t get_adomain() const
        {
            return domain;
        }

        pv::range_t<uint64_t> get_encoded_ns_addr_range() const
        {
            return ns_addr_range;
        }

        pv::range_t<pv::bus_addr_t> get_address_range() const
        {
            return pv::range_begin_end_incl(
                ns_addr_range.begin    & ns_addr_mask,
                ns_addr_range.end_incl & ns_addr_mask
                );
        }

        bool is_non_secure() const
        {
            return (ns_addr_range.begin & ns_mask) != 0;
        }

        uint64_t get_address_begin() const
        {
            return ns_addr_range.begin & ns_addr_mask;
        }

        /// Return the ACE AxSNOOP signal encoding this request contains
        unsigned get_ace_AxSNOOP() const
        {
            return AxSNOOP_from_ace_operation(operation);
        }

        std::ostream& print( std::ostream& os_ ) const;
    };

    inline std::ostream& operator << (std::ostream& os_, SnoopRequest const& t_ )
    {
        return t_.print(os_);
    }

    ///
    /// \name Prefetching pointers and ACE requests
    ///
    /// Our model implementation allows for sending back prefetch pointers to
    /// areas of memory that a master may use without first asking the
    /// downstream system.
    ///
    /// However, the interaction of this and ACE requests have to be carefully
    /// thought about.
    ///
    /// The basic logic that a use of a prefetch pointer should do _in the master_
    /// is:
    ///
    /// \code
    ///     if (we_have_a_prefetch_region())
    ///     {
    ///         if (is_ace_request_satisfiable_from_prefetch( ace_request_ ))
    ///         {
    ///            ...; // use prefetch region and set rresp from
    ///                 //    construct_rresp_for_prefetch_response( ace_request_ );
    ///            return;
    ///         }
    ///         // If the ace operation that will be transported downstream is
    ///         // incompatible with having an extant prefetch region then the
    ///         // downstream system should revoke it.
    ///     }
    ///
    ///     // no prefetch or prefetch is unsuitable.
    ///     transport_downstream()
    /// \endcode
    ///
    ///
    /// NOTE that at the moment, we do not require the master to store extra
    /// information about the prefetched region -- for example, the ACE state
    /// and so therefore we have to be a bit more pessimistic about the requests
    /// that we satisfy than if we could do that.
    ///
    /// In the slave, that is providing the prefetch region then it should
    /// use the functions:
    ///
    /// \code
    ///     // Use this function when the line state changes, if the
    ///     // new line state is invalid then clearly you must revoke!
    ///     bool is_line_state_read_prefetchable(
    ///        bool state_is_dirty,
    ///        bool state_is_unique
    ///        );
    ///
    ///     // Use this function when the line state changes, if the
    ///     // new line state is invalid then clearly you must revoke!
    ///     bool is_line_state_write_prefetchable(
    ///        bool state_is_dirty,
    ///        bool state_is_unique
    ///        );
    ///
    ///     bool can_construct_read_prefetch_for(
    ///         Payload    payload_,
    ///         bool       state_is_dirty_,
    ///         bool       state_is_unique_
    ///         );
    ///
    ///     bool can_construct_write_prefetch_for(
    ///         Payload    payload_,
    ///         bool       state_is_dirty_,
    ///         bool       state_is_unique_
    ///         );
    /// \endcode
    ///
    /// NOTE that these functions \b must return true in order for a slave to
    /// give a prefetch response, however, it can also pose additional
    /// constraints before returning true.  For example, it is assumed that if
    /// the line is in a UniqueDirty state then subsequent writes can be
    /// performed without any state transformation in the cache.  However, if
    /// the cache has multiple lines or wants to count writes, etc. then it
    /// can't return prefetch.
    ///
    /// The reason that the slave is responsible for revoking prefetch when it
    /// receives an incompatible ACE request is that we may have several masters
    /// talking to the same prefetch region and so the slave would have to
    /// revoke it anyway.
    ///
    //@{

    inline bool is_ace_request_satisfiable_from_prefetch( Payload const& payload_ )
    {
        ace_operation_t const op = payload_.get_ace_operation();

        return (
            (1u << op)
            & (1u   << ReadNoSnoop
               | 1u << WriteNoSnoop
               | 1u << ReadOnce
// NOTE that Write*Unique has a guarantee that it will reach main memory
//               | 1u << WriteUniqye
//               | 1u << WriteLineUnique
               | 1u << PseudoWriteOnce
               | 1u << Default
               | 1u << DebugRead
               | 1u << DebugWrite // The master will only have doled out write if it was already unique-dirty
                                  // or had reached main memory.
               | 1u << NoOperation
                )
            ) != 0;
    }

    inline ace_rresp_t construct_rresp_for_prefetch_response(
        Payload const& payload_
        )
    {
        //
        // We are only allow prefetch ace requests to be satisfiable if they are
        // ReadNoSnoop and ReadOnce.
        //
        // The ACE Spec only admits the following responses for the transactions
        // that we are allowed to prefetch:
        //
        //    ReadNoSnoop     ! PassDirty && ! IsShared
        //    ReadOnce        ! PassDirty()  (i.e. can be Shared or ! Shared)
        //
        // It is not possible for a core to use the ReadOnce Sharedness
        // information to do anything with it.  So we always return a fixed
        // value of ! PassDirty && ! IsShared.
        //
        (void)payload_;
        return ace_rresp_t(); // default
    }

    inline bool is_line_state_read_prefetchable(
       bool state_is_dirty,
       bool state_is_unique
       )
    {
        (void)state_is_dirty;
        (void)state_is_unique;
        return true;
    }

    inline bool is_line_state_write_prefetchable(
        bool state_is_dirty,
        bool state_is_unique
        )
    {
        // If the state is UniqueDirty then further writes do not have to inform
        // the downstream memory.  If it were UniqueClean then we couldn't give
        // out prefetch as we couldn't tell if someone had written to it and so
        // make it dirty.
        return state_is_dirty && state_is_unique;
    }

    inline bool can_construct_read_prefetch_for(
        Payload       payload_,
        bool          state_is_dirty_,
        bool          state_is_unique_
        )
    {
        // If the state is Unique or Shared  then writes do not have to inform the
        // downstream memory.
        ace_operation_t const op = payload_.get_ace_operation();
        assert( op != WriteBack && op != WriteUnique && op != WriteLineUnique && op != WriteClean && op != Evict && op != DebugWrite );

        return (
            (1u << op)
            & (1u   << ReadNoSnoop
               | 1u << ReadOnce
               | 1u << DebugRead
               | 1u << Default)
            ) != 0
            && is_line_state_read_prefetchable( state_is_dirty_, state_is_unique_ );
            ;
    }

    inline bool can_construct_write_prefetch_for(
        Payload       payload_,
        bool          state_is_dirty_,
        bool          state_is_unique_
        )
    {
        ace_operation_t const op = payload_.get_ace_operation();
        assert( op == NoOperation
                || op == Default
                || op == WriteNoSnoop
                || op == PseudoWriteOnce
                || op == WriteBack
                || op == WriteUnique
                || op == WriteLineUnique
                || op == WriteClean
                || op == Evict
                || op == DebugWrite
            );

        return
            ((1u << op)
             & (1u   << WriteNoSnoop
                | 1u << PseudoWriteOnce
// Write*Unique has to write to main memory, so we can't provide a prefetch
//               | 1u << WriteUnique
//               | 1u << WriteLineUnique
                | 1u << DebugWrite
                | 1u << Default)
                ) != 0
            && is_line_state_write_prefetchable( state_is_dirty_, state_is_unique_ );
    }
    //@}
}

#endif
