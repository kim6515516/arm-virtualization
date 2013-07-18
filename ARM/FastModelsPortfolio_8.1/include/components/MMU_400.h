//
// MMU_400
//
// The MMU-400 is a System MMU (SMMU).  This header implements part of the component
// for the MMU-400.
//
// Copyright 2011 ARM Limited. All rights reserved.
//
#ifndef ARM_INCLUDE_MMU_400_H
#define ARM_INCLUDE_MMU_400_H

#include <string>

#include "pv/PVBusMaster.h"
#include "pv/PVTransaction.h"
#include "pv/DVM.h"

#include "components/SMMU.h"

namespace sg
{
    class ComponentTrace;
}

namespace pv
{
    class RemapRequest;
}

namespace SMMU
{
    class smmu_output_pin_wiggle_if;
}

namespace MMU_400
{
    //
    // We could make MMU-400 a full C++ component but the formation of SSD_Index
    // and StreamID is very specific to the configuration and it is expected
    // that people should do that in a LISA wrapper.
    //
    class mmu_400_if : public SMMU::print_smmu_if
    {
    public:
        virtual ~mmu_400_if();

        // Configuration options that are not interesting to the model:
        //
        //     * AXI Data bus width
        //     * AXI ID signal width (0-23) // We don't really support an AXI ID
        //     * Depth of write buffer
        //     * Width of AWUSER/WUSER/BUSER/ARUSER/RUSER
        //     * Registering of the AXI interfaces.
        //
        // The downstream 'AXI ID' of the transaction is _not_ generated.
        //
        // None of the IMPLEMENTATION DEFINED registers in the MMU-400 are defined.q
        //     * Integration model register -- ITCTRL
        //     * Integration input register -- ITIP
        //     * Integration output register -- ITOP
        //

        //     * StreamID sideband signal width
        //     * StreamID include WnR (enable or disable)
        //     * StreamID AXI ID bit selections
        //
        //     * selection of APB3 or APB4 for the register file.
        //        * if apb3 then two ports to register file
        //        * if apb4 then single port to register file
        //
        //     * SSD determination
        //        * wsb_ns/rsb_ns if SSD table not present
        //        * SSD sideband signal width
        //        * SSD AXI ID bit selection
        //

        enum downstream_port_protocol_t {
            axi3_or_axi4_downstream,
            ace_lite_downstream
        };

        virtual void configure(
            downstream_port_protocol_t   pvbus_m_protocol_,
            
            unsigned                     tlb_depth_,             // 2-64
            unsigned                     number_of_contexts_,    // 1-8
            unsigned                     number_of_smrs_,        // 2, 4, 8, 16, 24 or 32
            bool                         ptw_has_separate_port_,
            downstream_port_protocol_t   pvbus_ptw_m_protocol_,  // only has meaning if ptw_has_separate_port_
            bool                         use_ssd_determination_table_,
                                         
            unsigned                     stream_id_width_,
            unsigned                     ssd_index_width_,       // used if use_ssd_determination_table_
                                         
            std::string const&           programmable_secure_by_default_ssd_indices_,
            std::string const&           programmable_non_secure_by_default_ssd_indices_,
            std::string const&           always_secure_ssd_indices_,

            bool                         cfg_cttw_,

            pv::RandomContextTransactionGenerator*      ptw_pvbus_m_,
            pv::RandomContextTransactionGenerator*      pvbus_m_,
            SMMU::smmu_output_pin_wiggle_if*            pin_wiggler_,

            unsigned                     seed_,

            unsigned                     percent_tlbstatus_commits_
            ) = 0;

        /// \name Used if the APB3 register file port is configured
        ///
        /// APB3 can't transport the security world of the transaction so we
        /// have two ports.
        //@{
        virtual pv::Tx_Result apb3_control_s_read( pv::ReadTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb3_control_s_write( pv::WriteTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb3_control_ns_read( pv::ReadTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb3_control_ns_write( pv::WriteTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb3_control_s_debug_read( pv::ReadTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb3_control_s_debug_write( pv::WriteTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb3_control_ns_debug_read( pv::ReadTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb3_control_ns_debug_write( pv::WriteTransaction tx_ ) = 0;
        //@}

        /// \name Used if the APB4 register file port is configured
        ///
        /// APB4 can transport the security world of the transaction and we only
        /// need a single port.
        //@{
        virtual pv::Tx_Result apb4_control_read( pv::ReadTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb4_control_write( pv::WriteTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb4_control_debug_read( pv::ReadTransaction tx_ ) = 0;
        virtual pv::Tx_Result apb4_control_debug_write( pv::WriteTransaction tx_ ) = 0;
        //@}

        virtual void init_trace_sources( sg::ComponentTrace* ) = 0;

        /// This is simulation reset
        virtual void reset() = 0;

        /// This is signal reset
        virtual void set_reset( bool signal_level_ ) = 0;

        /// This configures the cfg_cttw flag and determines if coherent page
        /// walks are allowed.  This is sampled out of reset, kinda.
        virtual void set_cfg_cttw( bool signal_level_ ) = 0;

        /// Actually perform the remap!
        virtual unsigned remap(
            pv::RemapRequest&                 req_,
            unsigned                          tbu_number_,

            unsigned                          stream_id_,
            unsigned                          ssd_index_or_ssd_state_,

            unsigned*                         unpredictable_summary_
            ) = 0;

        /// Inject a barrier into the SMMU, return true if the barrier shouldn be
        /// propagated downstream and if so what its shareability is.
        virtual std::pair<bool, ACE::adomain_t> inject_barrier(
            unsigned                          tbu_number_,

            ACE::adomain_t                    domain_,

            unsigned                          stream_id_,
            unsigned                          ssd_index_or_ssd_state_,
            
            unsigned*                         unpredictable_summary_
            ) = 0;

        /// FastSim can't understand fixed bursts, but we need to be able to
        /// deal with them in some way.  We do this by reserving a special user
        /// flag mask to indicate them.  The remap is considered to be for a
        /// fixed burst if (user_flag & user_flag_mask_) == user_flag_value_.
        ///
        /// This is used for validation purposes only.
        virtual void set_fixed_burst_user_flag_mask(
            unsigned user_flag_mask_,
            unsigned user_flag_value_
            ) = 0;
        
        virtual DVM::error_response_t handleUpstreamDVMMessageFromDownstream(
            DVM::Message*        message_,
            bool                 on_ptw_port_
            ) = 0;
        
        ///
        /// \name Print functions
        ///
        /// These prints out the state of the SMMU.  For large SMMUs then there
        /// is a lot of state, so you can ask for only specific parts to be
        /// printed out.
        ///
        //@{
        virtual std::ostream& print_global_state( std::ostream& os_ ) const = 0;
        virtual std::ostream& print_context_bank( std::ostream& os_, unsigned context_bank_id_ ) const = 0;
        virtual std::ostream& print_all_context_banks( std::ostream& os_ ) const = 0;
        //@}
    };


    mmu_400_if* makeMMU400(sg::ComponentBase * parentComponent_,  std::string const& name_);
}

namespace MMU_400_TestBench
{
    typedef MMU_400::mmu_400_if::downstream_port_protocol_t downstream_port_protocol_t;
    ///
    /// The testbench -- PRIVATE to ARM
    ///
    class testbench_if
    {
    public:
        virtual ~testbench_if();
    
        virtual void init_trace_sources( sg::ComponentTrace* trace_registry_ ) = 0;

        virtual void configure(
            downstream_port_protocol_t   pvbus_m_protocol_,
            
            unsigned                     tlb_depth_,             // 2-64
            unsigned                     number_of_contexts_,    // 1-8
            unsigned                     number_of_smrs_,        // 2, 4, 8, 16, 24 or 32
            bool                         ptw_has_separate_port_,
            downstream_port_protocol_t   pvbus_ptw_m_protocol_,  // only has meaning if ptw_has_separate_port_
            bool                         use_ssd_determination_table_,
                                         
            unsigned                     stream_id_width_,
            unsigned                     ssd_index_width_,       // used if use_ssd_determination_table_
                                         
            std::string const&           programmable_secure_by_default_ssd_indices_,
            std::string const&           programmable_non_secure_by_default_ssd_indices_,
            std::string const&           always_secure_ssd_indices_,

            bool                         cfg_cttw_
            ) = 0;

        virtual void init(
            pv::RandomContextTransactionGenerator* s_register_access_,
            pv::RandomContextTransactionGenerator* ns_register_access_,
            pv::RandomContextTransactionGenerator* register_access_,
            pv::RandomContextTransactionGenerator* remap_access_
            ) = 0;

        virtual void set_mmu_400( MMU_400::mmu_400_if* mmu_400_ ) = 0;

        virtual void reset() = 0;

        virtual void do_work(unsigned mutation_percent_) = 0;

        virtual pv::Tx_Result downstream_access(bool is_debug_, pv::ReadTransaction  tx_) = 0;
        virtual pv::Tx_Result downstream_access(bool is_debug_, pv::WriteTransaction tx_) = 0;

        virtual pv::Tx_Result downstream_ptw_access( bool is_debug_, pv::ReadTransaction tx_ ) = 0;
        
        virtual void cfg_flt_irpt_changed(bool is_non_secure_, bool asserted_) = 0;
        virtual void glbl_flt_irpt_changed(bool is_non_secure_, bool asserted_) = 0;
        virtual void ctx_irpt_ns_changed(bool asserted_) = 0;

        virtual void comb_irpt_changed(bool is_non_secure_, bool asserted_) = 0;
    };

    testbench_if* makeTestBench(unsigned seed_);
}

#endif
