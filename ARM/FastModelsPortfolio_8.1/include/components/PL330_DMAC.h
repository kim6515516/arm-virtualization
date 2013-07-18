/*!
 * \file    PL330_DMAC.h
 * \brief   PL330 DMA Controller
 * \date    Copyright 2009-2011 ARM Limited. All rights reserved.
 *
*/

#ifndef PL330_DMAC_H
#define PL330_DMAC_H

#include <queue>
#include <pv/PVBusMaster.h>
#include <vector>
#include <string>
#include "protocol_PL330CppToLISA.h"
#include "sg/SGSignal.h"
#include "sg/SGComponentTraceHelper.h"
#include <sstream>

// Debug prints are performed based on the following groups of messages
#define DEBUG_ALL    0xFFFFffff
#define DEBUG_TRACE             1
#define DEBUG_FRAMEWORK   1 << 1
#define DEBUG_REG         1 << 2
#define DEBUG_REGU        1 << 3
#define DEBUG_CH                1 << 4
#define DEBUG_INST              1 << 5
#define DEBUG_TODO              1 << 6
#define DEBUG_MSG_WARNING       1 << 7
#define DEBUG_MSG_ERROR         1 << 8

#define ACTIVE_DEBUG_FLAGS 0

#define IFDEBUG(value, command) if( ACTIVE_DEBUG_FLAGS & value ){ command }


#define compile_time_assert(E) ((void)(compile_time_assert_<(E)>::test))
#define CompileTimeAssert(E)   ((void)(compile_time_assert_<(E)>::test))

namespace fs_pl330
{
    //
    // compile_time_assert( COMPILE_TIME_CONSTANT_EXPRESSION )
    //
    // An expression which evaluates to void if the argument is true, otherwise
    // fails to compile.
    //
    // With g++ 3.4.3 then the error message is something like:
    //    common_macros.h: In instantiation of `compile_time_assert_< false>':
    //    t.cpp:5:   instantiated from here
    //    common_macros.h:42: warning: division by zero in `1 / 0'
    //    common_macros.h:42: error: enumerator value for `test' not integer constant
    // so it is fairly clear that a compile_time_assert fell over and that it
    // was at t.cpp:5.
    //
    // If the expression is not compile-time constant then you get a message such as:
    //    t.cpp: In function `void foo(int)':
    //    t.cpp:5: error: `i' cannot appear in a constant-expression
    //    t.cpp:5: error: template argument 1 is invalid
    //    t.cpp:5: error: `test' is not a member of `<declaration error>'
    // which unfortunately isn't as clear, but it correctly identifies the
    // line of the failure and what is non-constant and the line itself will
    // contain the 'compile_time_assert()' macro.
    //
    //
    // For cl then the result of the compile-time expression being false is:
    //    common_macros.h(69) : error C2057: expected constant expression
    //               t.cpp(5) : see reference to class template instantiation 'compile_time_assert_<0>' being compiled
    // which is, unfortunately, somewhat obscure!
    // 
    // and the expression not being compile time constant is obscure as well:
    //    common_macros.h(64) : error C2973: 'compile_time_assert_' : invalid template argument 'condition'
    //    common_macros.h(66) : see declaration of 'compile_time_assert_'
    //               t.cpp(5) : see reference to class template instantiation 'compile_time_assert_< ?? >' being compiled
    //
    // Interestingly, some of these casts (and I forget which) have to be C-style
    // casts to get them through the VC++6.0.  Constructor casts bool(expr) seemed
    // to confuse it!
    template<bool condition>
    struct compile_time_assert_ {
        enum { test = 1/((unsigned)condition) };
    };
    
    ///
    /// Produce a mask of 1s [start:start+length-1]
    ///
    template<typename T>
    inline
    T
    mask1s( unsigned start, unsigned length )
    {
        assert( length != 0 );
        return
            start >= sizeof(T) * 8
            ? T(0)
            : T( length >= sizeof(T) * 8
                 ? ~T(0) << start
                 : ((T(1) << length) - 1) << start
                );
    }

    /// Takes bits t[start+length-1:start] into lowest bits of return value
    template<typename T>
    inline
    T
    mask_and_shift_by_start_length( T t, unsigned start, unsigned length )
    {
        return static_cast<T>((t >> start) & mask1s<T>( 0, length));
    }

    /// slices bits t[length-1:0] into original[start+length-1:start] and returns the result
    template<typename T>
    inline
    T
    shift_and_slice_into_by_start_length( T original, T t, unsigned start, unsigned length )
    {
        return static_cast<T>(
            (original   & ~mask1s<T>( start, length ))
            |  (t << start & mask1s<T>( start, length ))
            );
    }
    
    /// slices bits t[msb_:0] into original[msb_:lsb_] and returns the result
    template< typename T, unsigned msb_, unsigned lsb_ >
    inline
    T
    shift_and_slice_into_by_msb_lsb( T original, T t )
    {
        CompileTimeAssert( msb_ < sizeof(T) * 8 );
        
        unsigned start  = lsb_;
        unsigned length = msb_ - lsb_ + 1;
        
        return static_cast<T>(
            (original   & ~mask1s<T>( start, length ))
            |  (t << start & mask1s<T>( start, length ))
            );
    }
    
    ///
    /// Return <code>input_[msb_:lsb_]</code> in the lowest bit of the return value.
    ///
    template< typename T, unsigned msb_, unsigned lsb_ >
    T
    get_shifted_bits_by_msb_lsb( T input_ )
    {
        // only allow unsigned shifts and those for which sizeof() is well defined
        CompileTimeAssert( msb_ > lsb_ ); // If you want to just get a single bit use the function with a single template parameter!
        CompileTimeAssert( msb_ < sizeof(T) * 8 );
        
        T value, mask;

        mask = T(~T(0));                               // All 1's
        mask = T(mask >> (sizeof(T) * 8 - 1 - msb_));  // Shift mask down so it is set from the MSB of the slice down
        value = T(input_ & mask);                      // Mask off MSB to bit 0
        value = T(value >> lsb_);                      // Shift off unwanted bits

        return value;
    }

    ///
    /// Return \a bit_ of \a input_ in the lowest bit of the return value.
    ///
    template< typename T, unsigned bit_ >
    T
    get_shifted_bit( T input_ )
    {
        CompileTimeAssert( bit_ < sizeof(T) * 8 );

        return T(input_ >> bit_ & T(1));
    }
    
    template< typename T >
    T
    get_shifted_bit( unsigned bit_, T input_ )
    {
        assert( bit_ < sizeof(T) * 8 );

        return T(input_ >> bit_ & T(1));
    }
    
    enum register_access_t { READ, WRITE };
    
    /*  !!! Warning! READ and WRITE appear backwards !!!
    
        Note that a register read is when we assemble fields into a register
        and a write is when we have been given a register and we want to extract
        fields.
    */
    
    template< typename T, register_access_t access_type_, unsigned msb_, unsigned lsb_ >
    void
    register_access( T &reg_, T &field_ )
    {
        if( access_type_ == WRITE )
        {
            field_ = get_shifted_bits_by_msb_lsb< T, msb_, lsb_ >( reg_ );
        }
        else if( access_type_ == READ )
        {
            reg_ = shift_and_slice_into_by_msb_lsb< T, msb_, lsb_ >( reg_, field_ );
        }
    }
    
    template< typename reg_t, typename field_t, register_access_t access_type_, unsigned msb_, unsigned lsb_ >
    void
    register_access2( reg_t &reg_, field_t &field_ )
    {
        if( access_type_ == WRITE )
        {
            field_ = field_t(get_shifted_bits_by_msb_lsb< reg_t, msb_, lsb_ >( reg_ ));
        }
        else if( access_type_ == READ )
        {
            reg_t field_temp = field_;
            reg_ = shift_and_slice_into_by_msb_lsb< reg_t, msb_, lsb_ >( reg_, field_temp );
        }
    }

    template< typename T, register_access_t access_type_, unsigned bit_ >
    void
    register_access_bit( T &reg_, T &field_ )
    {
        if( access_type_ == WRITE )
        {
            field_ = get_shifted_bit< T, bit_ >( reg_ );
        }
        else if( access_type_ == READ )
        {
            reg_ = shift_and_slice_into_by_msb_lsb< T, bit_, bit_ >( reg_, field_ );
        }
    }
    
    template< typename T, register_access_t access_type_, unsigned bit_ >
    void
    register_access_bit( T &reg_, bool &field_ )
    {
        uint32_t temp = field_;
        register_access_bit< T, access_type_, bit_ >( reg_, temp );
        field_ = temp != 0;
    }
    
    template< typename T, register_access_t access_type_ >
    void
    register_access_bit( unsigned bit_, T &reg_, T &field_ )
    {
        if( access_type_ == WRITE )
        {
            field_ = get_shifted_bit< T >( bit_, reg_ );
        }
        else if( access_type_ == READ )
        {
            reg_ = shift_and_slice_into_by_start_length<T>( reg_, field_, bit_, 1 );
        }
    }
    
    template< typename T, register_access_t access_type_ >
    void
    register_access_bit( unsigned bit_, T &reg_, bool &field_ )
    {
        uint32_t temp = field_;
        register_access_bit< T, access_type_ >( bit_, reg_, temp );
        field_ = temp != 0;
    }
    
    /*
    A template for converting (basically an int, but also something else) to a string.
    Useful for the "message" function to print output messages.
    */
    template <class T>
    inline std::string any2string(const T x)
    {
        std::stringstream ret_value;
        ret_value << x;
        return ret_value.str();
    }
    
    // the values in this enum are the ones that are returned in
    // peripheral ID register 2 (0xfe8) for the various revisions
    enum pl330_revision {PL330_R0P0 = 0x4, PL330_R1P0 = 0x14, PL330_R1P1 = 0x24, PL330_R1P2 = 0x34, PL330_RUNK = 0xff};

    
struct dma_params_t
{
    pl330_revision revision;
    uint32_t fifo_size;
    uint32_t max_transfer;
    bool generate_clear;
    uint32_t activate_delay;

    uint32_t p_max_irqs;
    uint32_t p_buffer_depth;
    uint32_t p_lsq_read_size;
    uint32_t p_lsq_write_size;
    uint32_t p_read_issuing_capability;
    uint32_t p_write_issuing_capability;
    uint32_t p_axi_bus_width_param;
    uint32_t p_cache_line_words;
    uint32_t p_cache_lines;
    uint32_t p_max_channels;
    bool p_controller_nsecure;
    bool p_irq_nsecure;
    bool p_periph_nsecure;
    bool p_controller_boots;
    uint32_t p_reset_pc;
//    uint32_t p_apbs_base;
//    uint32_t p_apbns_base;
    uint32_t p_max_periph;
    uint32_t p_perip_request_acceptance_0;
    uint32_t p_perip_request_acceptance_1;
    uint32_t p_perip_request_acceptance_2;
    uint32_t p_perip_request_acceptance_3;
    uint32_t p_perip_request_acceptance_4;
    uint32_t p_perip_request_acceptance_5;
    uint32_t p_perip_request_acceptance_6;
    uint32_t p_perip_request_acceptance_7;
    uint32_t p_perip_request_acceptance_8;
    uint32_t p_perip_request_acceptance_9;
    uint32_t p_perip_request_acceptance_10;
    uint32_t p_perip_request_acceptance_11;
    uint32_t p_perip_request_acceptance_12;
    uint32_t p_perip_request_acceptance_13;
    uint32_t p_perip_request_acceptance_14;
    uint32_t p_perip_request_acceptance_15;
    uint32_t p_perip_request_acceptance_16;
    uint32_t p_perip_request_acceptance_17;
    uint32_t p_perip_request_acceptance_18;
    uint32_t p_perip_request_acceptance_19;
    uint32_t p_perip_request_acceptance_20;
    uint32_t p_perip_request_acceptance_21;
    uint32_t p_perip_request_acceptance_22;
    uint32_t p_perip_request_acceptance_23;
    uint32_t p_perip_request_acceptance_24;
    uint32_t p_perip_request_acceptance_25;
    uint32_t p_perip_request_acceptance_26;
    uint32_t p_perip_request_acceptance_27;
    uint32_t p_perip_request_acceptance_28;
    uint32_t p_perip_request_acceptance_29;
    uint32_t p_perip_request_acceptance_30;
    uint32_t p_perip_request_acceptance_31;
};

enum message_level_t
{
    MSG_WARNING,
    MSG_ERROR,
    MSG_DEBUG,
    MSG_INFO,
    MSG_FATAL_ERROR
};

class DMAC
{
private:
    protocol_PL330CppToLISA *to_lisa_comms;
    unsigned debug_indent;
public:
    DMAC()
        : dbg()
        , exStage()
    {
       status_to_unsigned[STOPPED]                  = 0;
       status_to_unsigned[EXECUTING]                = 1;
       status_to_unsigned[CACHE_MISS]               = 2;
       status_to_unsigned[UPDATING_PC]              = 3;
       status_to_unsigned[WAITING_FOR_EVENT]        = 4;
       status_to_unsigned[AT_BARRIER]               = 5;
       // 6 Is reserved
       status_to_unsigned[WAITING_FOR_PERIPH]       = 7;
       status_to_unsigned[KILLING]                  = 8;
       status_to_unsigned[COMPLETING]               = 9;
       // 0xa to 0xd reserved
       status_to_unsigned[FAULTING_COMPLETING]      = 0xE;
       status_to_unsigned[FAULTING]                 = 0xF;
       
       instruction_readers[0] = 0;
       instruction_readers[1] = 0;
       debug_indent = 0;
       
       //no active event initially
       for(unsigned i=0; i<number_of_events; i++)
       {
            pending_events[i] = false;
       }

       irq_abort.asserted = false;
    }
    
    unsigned static const number_of_channels    = 8;
    unsigned static const number_of_DMA_ports   = 16;
    unsigned static const channel_mask          = ((number_of_channels)-1);
    unsigned static const DMA_port_mask         = ((number_of_DMA_ports)-1);

    unsigned static const no_DMA_port           = 0xffffffff;
    unsigned static const no_DMA_channel        = 0xffffffff;

    // maximum number of bytes that can be transferred in a burst
    unsigned static const max_DMA_burst         = 1024;
    
    unsigned static const symbols_thread_status_t_max = 17;
    unsigned static const number_of_events      = 32;

    enum AXIMasterFlagBurstTypeEnum
    {
        AXI_BURST_FIXED = 0,            // no address increment by Slave
        AXI_BURST_INCR,                 // address increment by Slave
        AXI_BURST_WRAP,                 // wrapped address increment by Slave
        AXI_BURST_RESERVED              // reserved
    };

    enum wait_src_t
    {
        WAIT_P
        ,WAIT_E
    };

    enum fault_status_t
    {
        FAULT_RESTORE = 0
        ,FAULT_SAVE   = 1
        ,FAULT_FETCH  = 2
        ,FAULT_LOAD   = 4
        ,FAULT_STORE  = 5
    };

    // reflects AMBA DMA Controller DMA-330 Technical Reference Manual > Functional Overview > Operating states
    enum thread_status_t //used for several status registers. Update status_to_unsigned to make
                         //this readable by external registers.
    {
        STOPPED
        ,EXECUTING
        ,CACHE_MISS
        ,UPDATING_PC
        ,WAITING_FOR_EVENT
        ,AT_BARRIER
        //,LSQ_BUSY
        ,WAITING_FOR_PERIPH
        ,KILLING
        ,COMPLETING
        //,YIELDING_WFE
        //,YIELDING_WFP
        //,SAVING_STATE
        //,RESTORING_STATE
        ,FAULTING_COMPLETING
        ,FAULTING
        //,WAITING_FOR_PCHANNEL
    };

    std::map< thread_status_t, uint32_t > status_to_unsigned;

    enum bus_error_t
    {
        SLAVE_ERROR
        ,DECODE_ERROR
    };

    enum req_type_t
    {
        REQ_SINGLE = 0,
        REQ_BURST
    };

    ///@brief Struct describing the Current Status Register of a v-channel.
    /// Also includes flags to indicate which barriers are being waited for: these are used in
    /// conjunction with the at_barrier state
    struct csr_t
    {
        bool            nsecure;
        bool            fault_enable;
        fault_status_t  fault_status;
        bus_error_t     etype;
        bool            yield;
        bool            restore;
        bool            bns;
        bool            wfp_periph;
        uint32_t        pchannel;
        uint32_t        wakeup;
        thread_status_t status;
        bool            await_r_barrier;
        bool            await_w_barrier;
        req_type_t      request_type;
        bool            request_last;
    };


    ///@brief Struct describing the Fault Status Register of a v-channel.
    struct ftr_t
    {
        bool lock_up; ///<Non-secure channel has been aborted due to a lock-up condition
        bool error_decode; ///<erroneous instruction was read from the system memory or from the debug interface
        bool error_read; ///<Data read receives non-OKAY response
        bool error_write; ///<Data write receives non-OKAY response
        bool error_instr; ///<Instruction fetch receives non-OKAY response
        bool mfifo_size; ///<DMAST or DMALD requires more entries than the entire MFIFO can hold
        bool secure_channel; ///<Non-secure channel attempted to configure CCR for secure AXI access
        bool secure_periph; ///<Non-secure channel issues DMAWFP, DMALDP, DMASTP or DMAFLUSHP against secure peripheral interface
        bool secure_event; ///<Non-secure thread issues DMAWFE or DMASEV against secure interrupt/event
        bool instr_range; ///<Instruction operand out-of-range
        bool instr_undef; ///<Undefined instruction
        
        void reset()
        {
            lock_up = false;
            error_decode = false;
            error_read = false;
            error_write = false;
            error_instr = false;
            mfifo_size = false;
            secure_channel = false;
            secure_periph = false;
            secure_event = false;
            instr_range = false;
            instr_undef = false;
        }
    };


    enum regname_t
    {
        DSR_enum
        ,DPC_enum
        ,DCP_enum
        ,CSR_enum
        ,CPC_enum
        ,SAR_enum
        ,CCR_enum
        ,DAR_enum
        ,LC0_enum
        ,LC1_enum
    };

    enum imm_kind_t
    {
        CN
        ,IMM32
        ,ITER
        ,EX_IMM_KIND
        ,EV
        ,PERIPH
        ,BNS_IMM_KIND
        ,IMM_YIELD
        ,INVAL
        ,RESTORE_IMM_KIND
        ,NSECURE
        ,JUMP
        ,IMM_CONT
        ,IMM_EXEC
        ,IMM_WFP
        ,IMM_FOREVER
    };

    union imm_t
    {
        uint32_t cn;
        uint32_t imm32;
        uint32_t iter;
        uint32_t ex;
        uint32_t ev;
        uint32_t periph;
        uint32_t jump;
        bool     bns;
        bool     imm_yield;
        bool     inval;
        bool     restore_imm;
        bool     nsecure;
        bool     imm_cont;
        bool     imm_exec;
        bool     imm_wfp;
        bool     imm_forever;
    };

    enum opcode_t
    {
        DMAADDH
        ,DMAADNH
        ,DMAEND
        ,DMAKILL
        ,DMAFLUSHP
        ,DMAGO
        ,DMALD
        ,DMALDP
        ,DMALP
        ,DMALPEND
        ,DMAMOV
        ,DMANOP
        ,DMAPAGE
        ,DMARMB
        ,DMASEV
        ,DMAST
        ,DMASTP
        ,DMASTZ
        ,DMAWFE
        ,DMAWFP
        ,DMAWMB
        ,DMALPFE
    };

    struct dma_instruction_t
    {
        opcode_t   opcode;
        regname_t  rd;
        imm_kind_t kind[4];
        imm_t      imm[4];
        uint32_t   sizeInBytes;
        uint32_t   addr;
        bool       ns;

        bool is_non_secure() const { return ns; }
    };

    // virtual channel resident registers
    struct vcrr_t
    {
        uint32_t status_register;
        uint32_t program_counter;
        uint32_t vcr_reserved0;
        uint32_t vcr_reserved1;
    };

    /// @brief Loop Counter register
    struct lc_t
    {
        uint32_t iter;
        bool forever;
        bool jump_back;
    };

    struct cr_t
    {
        uint32_t acache;    /** @brief Cache type. This signal indicates the bufferable, cacheable,
                                 write-through, write-back, and allocate attributes of the transaction. */
        uint32_t aprot;     /** @brief Protection type. This signal indicates the normal, privileged,
                                 or secure protection level of the transaction and whether the transaction
                                 is a data access or an instruction access. */
        bool     is_privileged;
        bool     is_instruction_access;
        bool     is_secure;
        uint32_t alen;      /** @brief Burst length (number of transfers). The burst length gives the exact number of transfers in a burst. This
                                 information determines the number of data transfers associated with the address. */
        uint32_t asize;     /** @brief Burst size. This signal indicates the size of each transfer in the burst. Byte lane strobes
                                 indicate exactly which byte lanes to update. */
        bool     increment_addr;
    };


    /// @brief Channel Control Register
    struct ccr_t
    {
        uint32_t endian_swap_size;
        cr_t src;
        cr_t dst;
    };

    enum rs_state_t
    {
        RS_IDLE
        ,RS_0
        ,RS_1
        ,RS_2
        ,RS_3
        ,RS_COMPLETING
        ,RS_COMPLETE
    };

    struct rs_t
    {
        rs_state_t       state;
        uint32_t         vnumber;
    };


    /// @brief Physical Channel Allocation register
    struct pca_t
    {
//        bool       nsecure;
        rs_t       restore;
        rs_t       save;
        wait_src_t wait_src;
        bool       allocated;
    };

    struct irq_t
    {
        bool  nsecure;
        bool  asserted;
        bool  enabled;
    };



    struct dsr_t ///DMA Status Register
    {
        // AKA DSR.DNS
        bool             nsecure;   /** 1 = DMA manager operates in the Non-secure state. (You must use the 
                                        boot_manager_ns signal to set the secure state of the DMA manager thread.) */
        uint32_t         wakeup;    /** Wakeup_event
                                        When the DMAC executes a DMAWFE instruction it waits for the event
                                        number stored here to occur */
        
        thread_status_t  status;    /** DMA status                             
                                        The operating state of the DMA manager:
                                        Stopped                        
                                        Executing                      
                                        Cache miss                     
                                        Updating PC                    
                                        Waiting for event              
                                        Faulting. */
    };

    bool is_manager_thread_non_secure() const { return dma_regfile.dsr.nsecure; }

    ///@brief Struct describing the Fault Status Register of the manager thread.
    struct frcr0_t
    {
        uint32_t event;
        bool report_controller_fetch;
        bool report_channel_store;
        bool report_channel_load;
        bool report_channel_fetch;
        bool report_channel_save;
        bool report_channel_restore;
    };

    struct ftrd_t
    {
        bool error_instr; ///<Instruction fetch receives non-OKAY response
        bool secure_event; ///<Non-secure thread issues DMAWFE or DMASEV against secure interrupt/event
        bool secure_manager; ///<Non-secure manager issues DMAGO with secure status set
        bool instr_range; ///<Instruction operand out-of-range
        bool instr_undef; ///<Undefined instruction
        
        void reset()
        {
            error_instr = false;
            secure_event = false;
            secure_manager = false;
            instr_range = false;
            instr_undef = false;
        }
    };

    struct dma_regfile_t
    {
        dsr_t      dsr;
        uint32_t   dpc;
        uint32_t   dcp;
        frcr0_t    frcr0;
        ftrd_t     ftrd;
    };
    
    /**
        Get the correct access_width, which for PVBus is a max of 32 bits.
        The PL330 supports writes of up to 16 bytes (128 bits), so we need
        to loop over large writes to emulate them.
    */
    void get_access_width_increment_and_loops( const cr_t &control_reg_, pv::AccessWidth &access_width_, unsigned &loop_writes_, unsigned &increment_ )
    {
        access_width_   = pv::ACCESS_32_BITS;
        loop_writes_    = 1;
        increment_      = 0;
        
        if( control_reg_.asize < 3 )
        {
            access_width_   = pv::byteWidthToAccessWidth(1 << control_reg_.asize);
            increment_      = 1 << control_reg_.asize;
        }
        else
        {
            loop_writes_    = 1 << (control_reg_.asize - 2);
            access_width_   = pv::ACCESS_32_BITS;
            increment_      = 4;
        }
    }


    // structure storing information related to one DMAC channel
    struct PL330_Channel
    {
        uint32_t            program_counter;
        csr_t               status_register; // holds the CNS bit that determines security.
        ftr_t               fault_type_register;
        lc_t                loop_counter_0;
        lc_t                loop_counter_1;
        uint32_t            source_address_register;
        uint32_t            destination_address_register;
        ccr_t               control_register;
        pca_t               physical_channel_allocation;
        uint8_t             bytecode[6];    ///< Instruction-byte aligned vector
        dma_instruction_t   inst; ///< Decoded instruction

        bool is_non_secure() const { return status_register.nsecure; }

        // bit numbers and masks
        enum RegBits
        {
            // config register

            CONFIG_H        = 18,       // halt
            CONFIG_A        = 17,       // active
            CONFIG_L        = 16,       // lock
            CONFIG_ITC      = 15,       // tc interrupt mask
            CONFIG_IE       = 14,       // error interrupt mask
            CONFIG_FLOW     = 11,       // flow control
            CONFIG_FLOW_MASK= 0x7,
            CONFIG_DEST     = 6,        // dest port
            CONFIG_DEST_MASK= number_of_DMA_ports-1,
            CONFIG_SRC      = 1,        // source port
            CONFIG_SRC_MASK = number_of_DMA_ports-1,
            CONFIG_E        = 0,        // enable bit

            // control register

            CONTROL_I       = 31,       // current lli interrupt mask
            CONTROL_PROT    = 28,       // access protection
            CONTROL_PROT_MASK = 0x7,
            CONTROL_DI      = 27,       // dest address increment
            CONTROL_SI      = 26,       // source address increment
            CONTROL_D       = 25,       // dest master select
            CONTROL_S       = 24,       // source master select
            CONTROL_DWIDTH  = 21,       // dest transfer width
            CONTROL_DWIDTH_MASK = 0x7,
            CONTROL_SWIDTH  = 18,       // source transfer width
            CONTROL_SWIDTH_MASK = 0x7,
            CONTROL_DBSIZE  = 15,       // dest burst size
            CONTROL_DBSIZE_MASK = 0x7,
            CONTROL_SBSIZE  = 12,       // source burst size
            CONTROL_SBSIZE_MASK = 0x7,
            CONTROL_TRANSFER_MASK = 0xfff // transfer count
        };
        
        uint32_t channel_num; // channel number as seen by the DMAC

        uint32_t src_addr;    // source address of next transaction
        uint32_t dst_addr;    // dest address of next transaction
        uint32_t config;      // config status
        uint32_t control;     // control reg

        uint32_t src_port;    // active source port
        uint32_t dst_port;    // active dest port

        uint32_t src_transfer;    // if dmac is controller, remaining transfers
        uint32_t dst_transfer;    // if dmac is controller, remaining transfers

        uint32_t src_residual;    // number of transfers remaining in this burst
        uint32_t dst_residual;    // number of transfers remaining in this burst

        uint32_t src_burst;   // source burst transfer size when dma is master
        uint32_t dst_burst;   // destination burst transfer size when dma is master

        uint32_t src_inc;     // byte increment for each source transfer
        uint32_t dst_inc;     // byte increment for each destination transfer

        uint32_t src_width;   // (log2) transfer width for source transfer
        uint32_t dst_width;   // (log2) transfer width for destination transfer

        uint32_t src_master;  // master bus port for source
        uint32_t dst_master;  // master bus port for destination

        bool src_bigend;      // source master is big endian
        bool dst_bigend;      // destination master is big endian

    private:
        pv::TransactionGenerator* reader;  // (shared) transaction generator for source
        pv::TransactionGenerator* writer;  // (shared) transaction generator for destination
    public:

        pv::TransactionGenerator* get_reader() { return reader; }
        pv::TransactionGenerator* get_writer() { return writer; }

        void set_reader(pv::TransactionGenerator* reader_) { reader = reader_; }
        void set_writer(pv::TransactionGenerator* writer_) { writer = writer_; }

        uint32_t src_request;   // current request from source port
        uint32_t dst_request;   // current request from dest port

        uint32_t flow_control;  // flow control type

        std::deque<uint8_t> fifo; // channel fifo
        uint8_t* fifo_in;       // pointer to next entry for src reads
        uint8_t* fifo_out;      // pointer to next entry for dest writes
        uint32_t  fifo_size;      // actual fifo depth as visible to the user

        bool pl080_stopped;           // channel is stopped pending more activity
        uint32_t src_response;  // source response to a perpipheral after a transfer
        uint32_t dst_response;  // destination response to a peripheral after a transfer
        bool src_tc_done;       // latched version of src_tc used in source flow mode

        bool halt;              // state of the config halt bit - masks src requests

        // configuration

        bool generate_clear;    // (don't) send clear responses to peripherals on burst
        
        // debug aids

        /*const char* requestName(uint32_t request)
        {
            static char name[32];

            if (request)
            {
                sprintf(name, "%s%s%s%s",
                        request & PL330_REQ_SINGLE  ? "SINGLE "  : "",
                        request & PL330_REQ_BURST   ? "BURST "   : "",
                        request & PL330_REQ_LSINGLE ? "LSINGLE " : "",
                        request & PL330_REQ_LBURST  ? "LBURST "  : "");
            }
            else
            {
                sprintf(name, "NONE ");
            }

            return name;
        }*/

        /*const char* responseName(uint32_t response)
        {
            static char name[32];

            if (response)
            {
                sprintf(name, "%s%s",
                        response & PL330_RES_CLR ? "CLR " : "",
                        response & PL330_RES_TC  ? "TC "  : "");
            }
            else
            {
                sprintf(name, "NONE ");
            }

            return name;
        }*/

        // implementation

        PL330_Channel()
            : status_register()
            , fault_type_register()
            , loop_counter_0()
            , loop_counter_1()
            , control_register()
            , physical_channel_allocation()
            , inst()
        {
            channel_num    = 0;
            fifo_size      = 16;
            generate_clear = false;
            for (size_t i = 0 ; i < sizeof(bytecode) / sizeof(*bytecode) ; ++i)
                bytecode[i] = 0;
            reset();
        }

        void reset()
        {
            src_addr = 0;
            dst_addr = 0;
            config   = 0;
            control  = 0;

            src_port = no_DMA_port;
            dst_port = no_DMA_port;

            src_transfer = 0;
            dst_transfer = 0;

            src_residual = 0;
            dst_residual = 0;

            src_burst = 0;
            dst_burst = 0;
            src_inc = 0;
            dst_inc = 0;

            src_width = 0;
            dst_width = 0;

            src_master = 0;
            dst_master = 0;

            src_bigend = false;
            dst_bigend = false;

            src_request = 0;
            dst_request = 0;

            halt = false;

            src_response = 0;
            dst_response = 0;

            // I believe this to be CSRn.CNS bit.
            status_register.nsecure        = 0; // NOTE that this starts in 'secure' even if the manager starts
                                                // in non-secure mode.  It would appear that a DMAGO instruction
                                                // is necessary before the channel, and hence the registers associated
                                                // with this channel are accessible to non-secure accesses.
            status_register.status         = STOPPED;
            status_register.bns            = false;
            status_register.wfp_periph     = false;
            status_register.restore        = false;
            status_register.yield          = false;
            status_register.wakeup         = 0x0;
            status_register.pchannel       = 0x0;
            status_register.fault_status   = FAULT_RESTORE;
            status_register.fault_enable   = true;
            program_counter                = 0x0;
            status_register.await_r_barrier = false;
            status_register.await_w_barrier = false;
            status_register.request_type    = REQ_SINGLE;
            status_register.request_last    = false;
            
            fault_type_register.reset();

            source_address_register       = 0x0;
            destination_address_register  = 0x0;
            control_register.endian_swap_size = 0x0;
            control_register.src.acache   = 0x0;
            control_register.src.aprot    = 0x0;
            control_register.src.asize    = 0x0;
            control_register.src.alen     = 0x0;
            control_register.src.increment_addr = false;
            control_register.dst.acache   = 0x0;
            control_register.dst.aprot    = 0x0;
            control_register.dst.asize    = 0x0;
            control_register.dst.alen     = 0x0;
            control_register.dst.increment_addr   = false;
            loop_counter_0.iter         = 0;
            loop_counter_0.forever      = false;
            loop_counter_0.jump_back    = false;
            loop_counter_1.iter         = 0;
            loop_counter_1.forever      = false;
            loop_counter_1.jump_back    = false;
            physical_channel_allocation.allocated        = false;
            physical_channel_allocation.wait_src         = WAIT_P;
            physical_channel_allocation.save.state       = RS_IDLE;
            physical_channel_allocation.restore.state    = RS_IDLE;
            // Indicate that DMAPAGE (no cont) will be required
            
            //reset fifo: if not reset, a corrupt fifo will affect the next simulation, even if the reset button has been pressed!
            fifo.clear();

        }
        
        /** Max number of data bytes to transfer in each beat, or data transfer, within a burst */
        uint32_t asize_to_bytes( uint32_t asize_ )
        {
            return 1 << asize_;
        }
        
        /** Returns the number of bytes that a burstable read transaction should take
            as calculated from the AXI length and AXI burst parameters set up in the
            channel control register */
        uint32_t read_size_in_bytes( void )
        {
            assert( 0 );
            return 0;
        }
        
        void fifo_push( uint32_t const * const data_, unsigned const bytes_to_push_ )
        {
            for( unsigned byte = 0 ; byte < bytes_to_push_ ; byte++ )
            {
                unsigned const index = byte / 4;
                unsigned const shift = (byte % 4) * 8;
                fifo.push_back( uint8_t( data_[index] >> shift ) );
            }
        }
        
        bool fifo_pop( uint32_t * const data_, unsigned const bytes_to_pop_ )
        {
            for( unsigned byte = 0 ; byte < bytes_to_pop_ ; byte++ )
            {
                unsigned const index = byte / 4;
                unsigned const shift = (byte % 4) * 8;
                if( shift == 0 )
                {
                    data_[index] = 0;
                }
                
                if(fifo.empty()) //DMAST not balanced with DMALD: raise abort - precise interrupt (see TRM)
                {
                    return false;
                }
                
                data_[index] |= uint32_t(fifo[0]) << shift;
                fifo.pop_front();
            }
            return true;
        }
    };

    enum dbg_status_t
    {
        DBG_IDLE = 0,
        DBG_EXECUTING
    };

    enum dbg_command_t
    {
        DBG_EXECUTE = 0,
        DBG_NOP
    };

    struct pl330_dma_debug_t
    {
        dbg_command_t       command;
        dbg_status_t        status;
        uint32_t            channel;
        bool                debug_thread;
        uint8_t             inst[6];
    };



    enum thread_t
    {
        CONTROLLER
        ,DMA_CHANNEL
    };

    thread_t current_thread;
    /// @brief Current secure state
//    bool secure;

    uint32_t p_reset_cp;

    /// Array of timeout values for the channels
    uint32_t* timeout;

    pl330_dma_debug_t dbg; // written from the APB interface

    // structure storing information related to one DMAC DmaPort

    struct PL330_DmaPort
    {
        uint32_t port_num;    // only used for debugging

        uint32_t channel;     // the last channel to use this port, used for routing requests
        uint32_t hwRequest;   // latched hardware request status bits
        uint32_t swRequest;   // latched software request status bits

        PL330_DmaPort()
        {
            reset();

            hwRequest = 0;
        }

        void reset()
        {
            channel = no_DMA_channel;
            swRequest = 0;
        }
    };

    uint32_t irqtc_status;                    // raw TC interrupt status
    uint32_t irqerr_status;                   // raw ERR interrupt status

    uint32_t irqtc_mask;                      // TC interrupt mask
    uint32_t irqerr_mask;                     // ERR interrupt mask

    uint32_t config;                          // global config state
    uint32_t sync;                            // global sync state

    bool     irq_tc;                          // currently asserted tc interrupt status
    bool     irq_err;                         // currently asserted err interrupt status
    bool     irq_member;                      // currently asssert irq interrupt status

    PL330_Channel channels[number_of_channels];// dma channels
    PL330_DmaPort dmaports[number_of_DMA_ports];// dma handshake ports

    std::vector<pv::TransactionGenerator*> readers;
    std::vector<pv::TransactionGenerator*> writers;
    
    pv::TransactionGenerator* instruction_readers[2];

    pv::TransactionGenerator* get_instruction_reader(bool is_non_secure_) {
        // We can only produce secure transactions if the manager thread is
        // secure
        assert( is_non_secure_ || ! is_manager_thread_non_secure() );
        return instruction_readers[unsigned(is_non_secure_)];
    }

    bool master_bigend;                      // endianness of master0

    // execution state management

    bool inHeartBeat;                         // stores whether the DMAC is executing to heartBeat function
    bool dma_busy;                            // stores whether the DMAC is running or scheduled to run

    uint32_t enabled_channels[number_of_channels];  // stack of enabled channels in priority order
    int32_t  num_enabled_channels;            // number of enabled channels

    uint32_t p_axi_bus_width;
    uint32_t p_axi_bus_size;
    uint32_t active_channel;                  // index of currently active channel

    bool noContextCheck;                  // index of currently active channel
    bool firstReset;

    dma_params_t dma_params;
    
    bool pending_events[number_of_events]; //the array containing all events issued by a DMASEV and not yet "removed" by a DMAWFE

    /// @brief Main struct used to pass information down the pipeline
    struct pipe_entry_t
    {
        // fe1
        thread_t                  thread;         ///< The thread identifier of this fetch
        uint32_t                  vchannel;       ///< If this fetch is from a DMA channel, this is the vchannel number
        uint32_t                  pchannel;       ///< If this fetch is from a DMA channel, this is the pchannel number
        thread_status_t*          status;         ///< Used to speed up status update
        uint32_t*                 pc_inc;         ///< Used to speed up pc incrementing
        uint32_t                  pc;             ///< Byte address of the instruction
        uint32_t                  cache_index;    ///< Index of the cache hit used to read data in the following cycle
        bool                      debug;          ///< When true indicates that this is a debug instruction
        // fe2
        uint32_t                  idata;          ///< Aligned 32-bit word containing the PC, the result of the instruction fetch
        uint8_t                   bytecode[6];    ///< Instruction-byte aligned vector
        // ex
        dma_instruction_t         inst;           ///< Decoded instruction
        bool                      rnw;            ///< Read-not-Write flag used for hazard detection in the LSQ
        uint32_t                  force_pc;       ///< Address used to move to the PC when a force is issued from the ex stage
        uint32_t                  ar;             ///< Address to send to the LSQ
        cr_t                      cr;             ///< Control to send to the LSQ
        uint32_t                  beat;
        bool                      r_barrier_sent; ///< Read barrier has completed for this channel (required for DMAPAGE)
        bool                      w_barrier_sent; ///< Write barrier has completed for this channel (required for DMAPAGE)
        bool                      split_transfer; ///< This transfer has been split (e.g. at 4KB boundary), generating
        ///< multiple bus accesses.  Therefore, do not clear hazards until the
        ///< last of the generated transactions completes
    };
    
    void init(  std::vector<pv::TransactionGenerator*> &read_tranaction_generators_,
                std::vector<pv::TransactionGenerator*> &write_tranaction_generators_,
                pv::TransactionGenerator*               s_instruction_reader_,
                pv::TransactionGenerator*               ns_instruction_reader_,
                dma_params_t                            dma_params_,
                protocol_PL330CppToLISA                *to_lisa_comms_,
                sg::ComponentTrace*                     component_trace_ );
    
    uint32_t reset( int level );
    void common_reset(  );
    void terminate(  );
    void test_disassembler(  );
    const char* get_symbols_thread_status( uint32_t idx );
    const char* get_symbols_opcode( uint32_t idx );
    const char* get_symbols_regname( uint32_t idx );
    void display_instruction( dma_instruction_t& inst );
    void dma_undef_instr(  );
    void chan_undef_instr(  );
    void undef_instr(  );
    void dma_instr_range(  );
    void chan_instr_range(  );
    void fetchInstructionByte( bool ns_, pv::bus_addr_t addr, uint8_t* pData8 );
    void disassemble( bool is_non_secure, uint8_t* bytecode, pv::bus_addr_t addr, dma_instruction_t& inst, bool debug_instruction = false );
    void dmaRequest( uint32_t port_num, uint32_t request );
    void setResponse( uint32_t port_num, uint32_t response );
    void setSwRequest( uint32_t port_num, uint32_t request );
    void clearSwRequest( uint32_t port_num, uint32_t request );
    void setupChannel( uint32_t ch_num );
    void enableChannel( uint32_t ch_num );
    void disableChannel( uint32_t ch_num );
    void channel_DMAADDH( dma_instruction_t& inst );
    void channel_DMAADNH( dma_instruction_t& inst );
    void channel_DMAEND(  );
    void channel_DMAKILL(  );
    void channel_DMAFLUSHP(  );
    void channel_DMALD(  );
    void channel_DMALDP(  );
    void channel_DMALP( dma_instruction_t& inst );
    void channel_DMALPEND( dma_instruction_t& inst );
    void channel_DMAMOV( dma_instruction_t& inst );
    void channel_DMANOP(  );
    void channel_DMARMB(  );
    void generic_DMASEV( dma_instruction_t& inst_ );
    void channel_DMASEV( dma_instruction_t& inst_ );
    void channel_DMAST(  );
    void channel_DMASTP(  );
    void channel_DMASTZ(  );
    void channel_DMAWFE( dma_instruction_t& inst_ );
    void channel_DMAWFP(  );
    void channel_DMAWMB(  );
    void channel_DMALPFE( dma_instruction_t& inst );
    void executeChannelInstruction( dma_instruction_t& inst );
    void manager_DMAEND(  );
    void manager_DMAKILL(  );
    void manager_DMANOP(  );
    void manager_DMAGO( dma_instruction_t& inst );
    void manager_DMASEV( dma_instruction_t& inst_ );
    void manager_DMAWFE(  );
    void generic_DMAST( bool use_fifo );
    void executeManagerInstruction( dma_instruction_t& inst );
    void runManagerThread(  );
    void runChannelThread(  );
    uint32_t heartBeat(  );
    uint32_t runCallback(  );
    void update_interrupts(  );
    uint32_t registerRead(pv::bus_addr_t device_addr, bool is_non_secure_);
    void registerWrite(pv::bus_addr_t device_addr, uint32_t data, bool is_non_secure_);
    void raise_abort(std::string mes);
    
    template< register_access_t access_type_ >
    uint32_t register_read_write( bool is_non_secure_, pv::bus_addr_t device_addr, uint32_t data );

    pipe_entry_t exStage;
    std::queue <PL330_Channel*> activeChannelQueue;
    PL330_Channel *pActiveChannel;

    dma_regfile_t      dma_regfile;
    std::vector<irq_t> event_irqs;
    irq_t              irq_abort;

    /// Returns if should abort because of APROT/ACACHE
    bool common_set_transaction_attributes(
        bool                       is_read_,
        pv::TransactionGenerator*  generator_,
        unsigned                   channel_number_,
        unsigned                   aprot_,
        unsigned                   acache_
        );
    /// Returns if should abort because of APROTT/ACACHE
    bool set_src_transaction_attributes(unsigned channel_number_, unsigned aprot_, unsigned encoded_acache_);
    /// Returns if should abort because of APROTT/ACACHE
    bool set_dst_transaction_attributes(unsigned channel_number_, unsigned aprot_, unsigned encoded_acache_);
    
    void message( message_level_t type_, std::string text_ )
    {
        to_lisa_comms->message_printer( uint32_t(type_), text_ );
    }
    
    void set_event_irq( uint32_t irq_number_ )
    {
        assert( irq_number_ < number_of_events );
        
        if(    event_irqs[irq_number_].enabled
            && event_irqs[irq_number_].asserted == false )
        {
            to_lisa_comms->update_irq( irq_number_, true );
            event_irqs[irq_number_].asserted = true;
        }
    }
    
    void clear_event_irq( uint32_t irq_number_ )
    {
        assert( irq_number_ < number_of_events );

        if(    event_irqs[irq_number_].enabled
            && event_irqs[irq_number_].asserted )
        {
            assert( irq_number_ < number_of_events );
            to_lisa_comms->update_irq( irq_number_, false );
            event_irqs[irq_number_].asserted = false;
        }
    }
    
    void disable_event_irq( uint32_t irq_number_ )
    {
        assert( irq_number_ < number_of_events );

        if( event_irqs[irq_number_].enabled )
        {
            event_irqs[irq_number_].enabled = false;
            if( event_irqs[irq_number_].asserted )
            {
                to_lisa_comms->update_irq( irq_number_, false );
            }
        }
    }
    
    void enable_event_irq( uint32_t irq_number_ )
    {
        assert( irq_number_ < number_of_events );
        
        if( event_irqs[irq_number_].enabled == false )
        {
            event_irqs[irq_number_].enabled = true;
            if( event_irqs[irq_number_].asserted )
            {
                to_lisa_comms->update_irq( irq_number_, true );
            }
        }
    }
    
    void set_abort_irq( void )
    {
        if( irq_abort.asserted == false ) //this interrupt does not have an enable in the TRM
        {
            to_lisa_comms->update_abort( true );
            irq_abort.asserted = true;
        }
    }
    
    void clear_abort_irq( void ) //this interrupt does not have an enable in the TRM
    {
        if( irq_abort.asserted )
        {
            to_lisa_comms->update_abort( false );
            irq_abort.asserted = false;
        }
    }

    DEFINE_SIMPLE_TRACE_SOURCE(
        start_channel_read_trace,
        "start_channel_read",
        "Start of a channel read",
        ( uint8_t, uint32_t, uint8_t, uint8_t, uint8_t ),
        (
            "channel_number",    "Channel making transaction.",
            "address",           "Address of transaction.",
            "width_in_bytes",    "Width in bytes",
            "acache",            "The ACACHE value expanded to four bits",
            "aprot",             "The APROT value"
            )
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        channel_read_trace,
        "channel_read",
        "A completed channel read",
        ( uint8_t, uint32_t, uint8_t, uint8_t, uint8_t, uint64_t, bool ),
        (
            "channel_number",    "Channel making transaction.",
            "address",           "Address of transaction.",
            "width_in_bytes",    "Width in bytes",
            "acache",            "The ACACHE value expanded to four bits",
            "aprot",             "The APROT value",
            "data",              "The data",
            "error",             "The transaction produced an error."
            )
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        start_channel_write_trace,
        "start_channel_write",
        "Start of a channel write",
        ( uint8_t, uint32_t, uint8_t, uint8_t, uint8_t ),
        (
            "channel_number",    "Channel making transaction.",
            "address",           "Address of transaction.",
            "width_in_bytes",    "Width in bytes",
            "acache",            "The ACACHE value expanded to four bits",
            "aprot",             "The APROT value"
            )
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        channel_write_trace,
        "channel_write",
        "A completed channel write",
        ( uint8_t, uint32_t, uint8_t, uint8_t, uint8_t, uint64_t, bool ),
        (
            "channel_number",    "Channel making transaction.",
            "address",           "Address of transaction.",
            "width_in_bytes",    "Width in bytes",
            "acache",            "The ACACHE value expanded to four bits",
            "aprot",             "The APROT value",
            "data",              "The data",
            "error",             "The transaction produced an error."
            )
        );

    
    bool active_channel_read(pv::bus_addr_t source_address, pv::AccessWidth access_width_, uint32_t* data_);
    bool active_channel_write(pv::bus_addr_t source_address, pv::AccessWidth access_width_, uint32_t const* data_);

    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmamov_trace,
        "inst_dmamov",
        "DMAMOV instruction",
        (
            uint8_t,
            uint8_t,
            uint32_t ),
        (
            "channel_number",
            "Channel issuing instruction",
            
            "register",
            description("Register being moved to")
            ( DSR_enum, "DSR" )
            ( DPC_enum, "DPC" )
            ( DCP_enum, "DCP" )
            ( CSR_enum, "CSR" )
            ( CPC_enum, "CPC" )
            ( SAR_enum, "SAR" )
            ( CCR_enum, "CCR" )
            ( DAR_enum, "DAR" )
            ( LC0_enum, "LC0" )
            ( LC1_enum, "LC1" ),

            "data",
            "Data moved" )
        );
    
    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmanop_trace,
        "inst_dmanop",
        "DMANOP instruction executed by channel",
        ( uint8_t ),
        (
            "channel_number",
            "Channel issuing instruction" )
        );
    
    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmanop_manager_trace,
        "inst_dmanop_manager",
        "DMANOP instruction executed by manager",
        (),
        ()
        );
    
    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmasev_trace,
        "inst_dmasev",
        "DMASEV instruction",
        ( uint8_t, uint8_t ),
        (
            "channel_number",
            "Channel issuing instruction",
            "irq_number",
            "IRQ number" )
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmasev_manager_trace,
        "inst_dmasev_manager",
        "DMASEV instruction executed by manager",
        ( uint8_t ),
        (
            "irq_number",
            "IRQ number" )
        );
    
    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmawfe_trace,
        "inst_dmawfe",
        "DMAWFE instruction",
        ( uint8_t, uint8_t ),
        (
            "channel_number",
            "Channel issuing instruction",
            "pending_event_found",
            "The DMAWFE doesn't wait as event is already signaled." )
        );
    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmawfe_manager_trace,
        "inst_dmawfe_manager",
        "DMAWFE instruction executed by manager",
        (),
        ()
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmald_trace,
        "inst_dmald",
        "DMALD instruction",
        ( uint8_t, uint32_t, uint8_t, uint8_t, bool ),
        (
            "channel_number",
            "Channel issuing instruction",

            "source_address",
            "Source address",

            "transfer_size_in_bytes",
            "Transfer size in bytes",

            "number_of_beats",
            "Number of beats to transfer",

            "increment_addr",
            "Whether to increment the address or not" )
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmast_trace,
        "inst_dmast",
        "DMAST instruction",
        ( uint8_t, uint32_t, uint8_t, uint8_t, bool ),
        (
            "channel_number",
            "Channel issuing instruction",

            "destination_address",
            "Destination address",

            "transfer_size_in_bytes",
            "Transfer size in bytes",

            "number_of_beats",
            "Number of beats to transfer",

            "increment_addr",
            "Whether to increment the address or not" )
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmago_trace,
        "inst_dmago",
        "DMAGO instruction",
        ( uint8_t, uint32_t, bool ),
        (
            "channel_number",
            "Channel issuing instruction",

            "pc",
            "Program counter",

            "cns",
            "The thread in non-secure." )
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmago_no_go_trace,
        "inst_dmago_no_go",
        "DMAGO instruction failed",
        ( uint8_t, uint8_t ),
        (
            "channel_number",
            "Channel issuing instruction",

            "why",
            description("Why failed")
            ( 0, "Non-secure manager thread tried to launch thread as secure" )
            ( 1, "Channel number out of range" )
            ( 2, "Thread not stopped" )
            )
        );
    
    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmaend_trace,
        "inst_dmaend",
        "DMAEND instruction executed by manager thread",
        (),
        ()
        );
    
    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmakill_trace,
        "inst_dmakill",
        "DMAKILL instruction executed by manager thread",
        (),
        ()
        );
    
    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_dmalp_trace,
        "inst_dmalp",
        "DMALP instruction executed by channel, loads 'iterations' into the loop counter",
        ( uint8_t, uint8_t, uint8_t ),
        ( "channel_number",  "Channel issuing instruction",
          "loop_counter",    "Which loop counter",
          "iterations",      "The value to load into the loop counter" )
        );

    DEFINE_SIMPLE_TRACE_SOURCE(
        inst_instruction_not_implemented_trace,
        "inst_instruction_not_implemented",
        "Instruction is not implemented by the model.",
        ( uint8_t ),
        ( "which",
          description("Which instruction is not modelled")
          (0, "DMAWFP")
          (1, "DMALDP")
            )
        );
};


};

#endif //PL330_DMAC_H
