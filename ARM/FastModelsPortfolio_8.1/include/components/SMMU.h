/* -*- C++ -*-
 *
 * Copyright 2012 ARM Limited. All rights reserved.
 */

#ifndef ARM_INCLUDE_SMMU_H
#define ARM_INCLUDE_SMMU_H
#include "eslapi/hostconf/zstdint.h"

#include "pv/PVBusAddr.h"
#include "pv/PVTransaction.h" // for pv::Tx_Result
#include "pv/DVM.h"

namespace pv {
    class RandomContextTransactionGenerator;
    class TransactionAttributes;
    class RemapRequest;
}

namespace sg {
    class ComponentTrace;
}

///
/// Public interfaces to the SMMU model.
///
namespace SMMU
{
    class print_smmu_if {
    public:
        virtual ~print_smmu_if() {}
        
        virtual std::ostream& print_global_state( std::ostream& os_ ) const = 0;
        virtual std::ostream& print_context_bank( std::ostream& os_, unsigned context_bank_id_ ) const = 0;
        virtual std::ostream& print_all_context_banks( std::ostream& os_ ) const = 0;
    };
    
    class smmu_if;
    class imp_def_if;

    ///
    /// This provides a streaming service that allows you to construct messages
    /// to the trace streams.
    ///
    /// You construct a message and then when you explicitly flush it then it
    /// will appear on the trace stream.
    ///
    class streams_if
    {
    public:
        virtual ~streams_if() {}
        
        virtual std::ostream& debug()           = 0;
        virtual bool          debug_enabled()   = 0;
        virtual std::ostream& info()            = 0;
        virtual bool          info_enabled()    = 0;
        virtual std::ostream& warning()         = 0;
        virtual bool          warning_enabled() = 0;
        virtual std::ostream& error()           = 0;
        virtual bool          error_enabled()   = 0;
    };
    

    ///
    /// The wrapper should provide a way for the SMMU to wiggle pins.  The
    /// wrapper should pass an object implementing this interface to the SMMU
    /// and it will be called back when the SMMU wishes to wiggle a pin.  The
    /// SMMU will call all pins when reset() is _first_ called on the SMMU.
    ///
    class smmu_output_pin_wiggle_if
    {
    public:
        virtual ~smmu_output_pin_wiggle_if();

        virtual void set_context_interrupt_pin( unsigned pin_number_, bool asserted_ ) = 0;

        virtual void set_combined_context_interrupt_pin( bool is_non_secure_, bool asserted_ ) = 0;

        /// This pin represents a global Configuration Access Fault.  This
        /// corresponds to two pins -- the SMMU_gCfgIrpt (secure) and
        /// SMMU_NSgCfgIrpt (non-secure) version.  If security extensions are
        /// not supported then is_non_secure_ == true.
        virtual void set_SMMU_gCfgIrpt( bool is_non_secure_, bool asserted_ ) = 0;

        /// This pin represents a global fault that is not a Configuration
        /// Access Fault.  This represents two pins, the SMMU_gIrpt (secure) and
        /// the SMMU_NSgIrpt (non-secure) version.  If security extensions are
        /// not supported then is_non_secure_ == true.
        virtual void set_SMMU_gIrpt( bool is_non_secure_, bool asserted_ ) = 0;
    };

    ///
    /// This is a thunk wrapper round smmu_output_pin_wiggle_if that makes it
    /// easier to connect to LISA ports.
    ///
    /// NOTE that we only support arrays that are produced by a C-style
    /// array.
    ///
    class smmu_output_pin_wiggle_thunk_t
        : public smmu_output_pin_wiggle_if
    {
    protected:
        class setValue_if {
        public:
            virtual ~setValue_if() {}
            virtual void setValue(unsigned port_number_, bool assert_) = 0;
        };

        template<typename PORT, typename VALUE>
        class setValue_array_port_if : public setValue_if {
        public:
            PORT*    p;
            unsigned array_len;
            VALUE    asserted;
            VALUE    deasserted;
            setValue_array_port_if(PORT* p_, unsigned array_len_,
                                   VALUE asserted_, VALUE deasserted_)
                : p(p_), array_len(array_len_),
                  asserted(asserted_), deasserted(deasserted_)  {}
            virtual void setValue(unsigned port_number_, bool assert_)
            {
                assert( port_number_ < array_len );
                if (port_number_ < array_len && p[port_number_].setValue.implemented())
                    p[port_number_].setValue( assert_ ? asserted : deasserted );
            }
        };

        setValue_if* SMMU_gCfgIrpt[2];
        setValue_if* SMMU_gIrpt[2];
        setValue_if* context_interrupt_pins;
        setValue_if* combined_context_interrupt_pins[2];
    public:

        smmu_output_pin_wiggle_thunk_t()
        {
            SMMU_gCfgIrpt[0] = 0;
            SMMU_gCfgIrpt[1] = 0;
            SMMU_gIrpt[0]    = 0;
            SMMU_gIrpt[1]    = 0;
            context_interrupt_pins = 0;
            combined_context_interrupt_pins[false] = 0;
            combined_context_interrupt_pins[true ] = 0;
        }

        ~smmu_output_pin_wiggle_thunk_t()
        {
            delete SMMU_gCfgIrpt[0];
            delete SMMU_gCfgIrpt[1];
            delete SMMU_gIrpt[0];
            delete SMMU_gIrpt[1];
            delete context_interrupt_pins;
        }

        /// Register SMMU_gCfgIrpt and SMMU_NSgCfgIrpt
        template<typename PORT, typename VALUE>
        void register_SMMU_gCfgIrpt(bool is_non_secure_, PORT& p_, VALUE asserted_, VALUE deasserted_)
        {
            unsigned const index(is_non_secure_);
            assert( SMMU_gCfgIrpt[index] == 0 );
            SMMU_gCfgIrpt[index] = new setValue_array_port_if<PORT,VALUE>(&p_, 1, asserted_, deasserted_);
        }
        
        template<typename PORT, typename VALUE>
        void register_SMMU_gIrpt(bool is_non_secure_, PORT& p_, VALUE asserted_, VALUE deasserted_)
        {
            unsigned const index(is_non_secure_);
            assert( SMMU_gIrpt[index] == 0 );
            SMMU_gIrpt[index] = new setValue_array_port_if<PORT,VALUE>(&p_, 1, asserted_, deasserted_);
        }

        template<typename PORT, typename VALUE>
        void register_context_interrupt_pins(PORT* p_, unsigned p_len_, VALUE asserted_, VALUE deasserted_)
        {
            context_interrupt_pins = new setValue_array_port_if<PORT,VALUE>(p_, p_len_, asserted_, deasserted_);
        }

        template<typename PORT, typename VALUE>
        void register_combined_context_interrupt_pin(PORT& port_, bool is_non_secure_, VALUE asserted_, VALUE deasserted_)
        {
            combined_context_interrupt_pins[is_non_secure_] = new setValue_array_port_if<PORT, VALUE>(
                &port_, 1, asserted_, deasserted_
                );
        }

    protected:
        
        virtual void set_context_interrupt_pin( unsigned pin_number_, bool asserted_ )
        {
            assert( context_interrupt_pins != 0 );
            context_interrupt_pins->setValue(pin_number_, asserted_);
        }
        
        virtual void set_combined_context_interrupt_pin( bool is_non_secure_, bool asserted_ )
        {
            // Not all SMMUs will have this so we check first.
            if (combined_context_interrupt_pins[is_non_secure_] != 0)
                combined_context_interrupt_pins[is_non_secure_]->setValue( 0, asserted_ );
        }
        
        /// This pin represents a global Configuration Access Fault.  This
        /// corresponds to two pins -- the SMMU_gCfgIrpt (secure) and
        /// SMMU_NSgCfgIrpt (non-secure) version.  If security extensions are
        /// not supported then is_non_secure_ == true.
        virtual void set_SMMU_gCfgIrpt( bool is_non_secure_, bool asserted_ )
        {
            unsigned const index(is_non_secure_);

            // ConfigurationAccessFault is optional in the architecture and
            // MMU-500 doesn't have it.
            if (SMMU_gCfgIrpt[index] != 0)
                SMMU_gCfgIrpt[index]->setValue( 0, asserted_ );
        }
        
        /// This pin represents a global fault that is not a Configuration
        /// Access Fault.  This represents two pins, the SMMU_gIrpt (secure) and
        /// the SMMU_NSgIrpt (non-secure) version.  If security extensions are
        /// not supported then is_non_secure_ == true.
        virtual void set_SMMU_gIrpt( bool is_non_secure_, bool asserted_ )
        {
            unsigned const index(is_non_secure_);
            assert( SMMU_gIrpt[index] != 0 );
            SMMU_gIrpt[index]->setValue( 0, asserted_ );
        }
    };

    
    inline unsigned ssd_secure()     { return ~0u;     }
    inline unsigned ssd_non_secure() { return ~0u - 1; }
    
}

#endif
