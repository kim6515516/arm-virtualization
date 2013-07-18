//
// uTrickbox for Dual Cluster platform
//
#ifndef DUALCLUSTERSYSTEMCONFIGURATIONBLOCK_H
#define DUALCLUSTERSYSTEMCONFIGURATIONBLOCK_H

#include "sg/SGSignal.h"
#include "pv/PVBusAddr.h"

#include "DualClusterSystemConfigurationBlock_ResetStateMachine.h"

inline unsigned to_bit(sg::Signal::State s )
{
    return s == sg::Signal::Set?1:0;
}

inline sg::Signal::State from_bit(bool s)
{
    return s ? sg::Signal::Set : sg::Signal::Clear;
}

inline sg::Signal::State from_bit(unsigned bit_position, unsigned value)
{
    return (value & (1u << bit_position)) != 0 ? sg::Signal::Set : sg::Signal::Clear;
}

template<typename T>
inline void set_bit_of_to( T* variable, unsigned bit_position, bool value )
{
    T const mask = T(1) << bit_position;
    *variable = *variable & ~mask | T(value) << bit_position;
}

namespace DCSCBDetails
{
    template< typename PortType >
    inline void apply_bool_to( bool always_apply_cfg_, PortType& p_, bool value_, bool* old_value_ )
    {
        if ((always_apply_cfg_ || value_ != *old_value_) && p_.setValue.implemented())
            p_.setValue( from_bit( value_ ) );
        *old_value_ = value_;
    }

    template< typename PortType >
    inline void apply_bool_to( PortType& p_, bool value_ )
    {
        if (p_.setValue.implemented())
            p_.setValue( from_bit( value_ ) );
    }

    template< typename PortType, typename ValueType >
    inline void apply_value_to( bool always_apply_cfg_, PortType& p_, ValueType value_, ValueType* old_value_ )
    {
        if ((always_apply_cfg_ || value_ != *old_value_) && p_.setValue.implemented())
            p_.setValue( value_ );
        *old_value_ = value_;
    }

    template< typename SignalPortType >
    inline void apply_cfg_to(
        bool                      always_apply_cfg_,

        SignalPortType&           cpu_reset_port_,
        SignalPortType*           cpu_reset_port2_,
        SignalPortType&           cpu_poreset_port_,
//        SignalPortType&           cpu_debug_port_,

        SignalPortType&           cfgend_port_,
        SignalPortType&           vinithi_port_,
        SignalPortType&           teinit_port_,

        reset_handler_t::reset_pin_delta_t const&  delta_,

        cfg_t&                    old_cfg_value_
        )
    {
        switch (delta_.pin)
        {
            if (1)
            {
            case reset_handler_t::cpu_reset_pin:
                apply_bool_to( cpu_reset_port_,  delta_.valueQ() );
                if (cpu_reset_port2_ != 0)
                    apply_bool_to( *cpu_reset_port2_, delta_.valueQ() );
            }
            else
            {
            case reset_handler_t::cpu_poreset_pin:
                apply_bool_to( cpu_poreset_port_, delta_.valueQ() );
            }
            //
            // Apply configuration in these cases
            //
            apply_bool_to( always_apply_cfg_, cfgend_port_, delta_.cfgendQ(), &old_cfg_value_.cfgend    );
            apply_bool_to( always_apply_cfg_, vinithi_port_, delta_.vinithiQ(), &old_cfg_value_.vinithi );
            apply_bool_to( always_apply_cfg_, teinit_port_, delta_.teinitQ(), &old_cfg_value_.teinit    );
            break;

        case reset_handler_t::debug_reset_pin:
//            apply_bool_to( cpu_debug_port_, delta.valueQ() );
            break;

        case reset_handler_t::cluster_reset_pin:
        case reset_handler_t::system_debug_reset_pin:
        case reset_handler_t::system_reset_pin:
            assert(0); // not handled
        }
    }

}

namespace DCSCBRegisters
{
    enum register_identifier_t {
        //
        // If this enum changes then to_register() must also change.
        //

        RST_HOLD0     = 0x000,
        RST_HOLD1     = 0x004,
        SYS_SWRESET   = 0x008,
        RST_STAT0     = 0x00C,
        RST_STAT1     = 0x010,

        CLUSTER0_CFG_R     = 0x020,
        CLUSTER0_CFG_W     = 0x024,
        CLUSTER1_CFG_R     = 0x028,
        CLUSTER1_CFG_W     = 0x02C,

        DCS_CFG_R     = 0x030,

        /// 8 64 bit registers that are used as rw storage by the boot loader
        /// to detect warm reset and intended to hold the warm start address
        /// or 0 if this is a cold start.
        BX_ADDR_CL0_CPU0      = 0x040,
        BX_ADDR_CL0_CPU0_high = 0x044,
        BX_ADDR_CL0_CPU1      = 0x048,
        BX_ADDR_CL0_CPU1_high = 0x04c,
        BX_ADDR_CL0_CPU2      = 0x050,
        BX_ADDR_CL0_CPU2_high = 0x054,
        BX_ADDR_CL0_CPU3      = 0x058,
        BX_ADDR_CL0_CPU3_high = 0x05c,
        BX_ADDR_CL1_CPU0      = 0x060,
        BX_ADDR_CL1_CPU0_high = 0x064,
        BX_ADDR_CL1_CPU1      = 0x068,
        BX_ADDR_CL1_CPU1_high = 0x06c,
        BX_ADDR_CL1_CPU2      = 0x070,
        BX_ADDR_CL1_CPU2_high = 0x074,
        BX_ADDR_CL1_CPU3      = 0x078,
        BX_ADDR_CL1_CPU3_high = 0x07c,

        DCS_LEDS      = 0x104, // LEDs on board
        DCS_SW        = 0x108, // Switches on board

        INT_CTRL      = 0x120,
        INT_FREQ      = 0x124,
        INT_TYPE0     = 0x130,
        INT_TYPE1     = 0x134,
        INT_TYPE2     = 0x138,
        INT_TYPE3     = 0x13c,
        INT_GENERATE  = 0x140,
        INT_NUMBER    = 0x144,
        INT_ACK       = 0x148,
        INT_SEQ_first = 0x200, // range of 128 registers
        INT_SEQ_last  = 0x3FC, // last one!


        MODEL_SW_TRACE_TUBE        = 0x00 + 0x400, // 8 bit register
        MODEL_SW_TRACE_DATA0       = 0x00 + 0x408, // 64 bit register
        MODEL_SW_TRACE_DATA0_high  = 0x00 + 0x408 + 4, // 64 bit register (high word)
        MODEL_SW_TRACE_DATA1       = 0x00 + 0x410, // 64 bit register
        MODEL_SW_TRACE_DATA1_high  = 0x00 + 0x410 + 4, // 64 bit register (high word)
        MODEL_SW_TRACE_DATA2       = 0x00 + 0x418, // 64 bit register
        MODEL_SW_TRACE_DATA2_high  = 0x00 + 0x418 + 4, // 64 bit register (high word)

        MODEL_SW_TRACE2_TUBE       = 0x20 + 0x400, // 8 bit register
        MODEL_SW_TRACE2_DATA0      = 0x20 + 0x408, // 64 bit register
        MODEL_SW_TRACE2_DATA0_high = 0x20 + 0x408 + 4, // 64 bit register (high word)
        MODEL_SW_TRACE2_DATA1      = 0x20 + 0x410, // 64 bit register
        MODEL_SW_TRACE2_DATA1_high = 0x20 + 0x410 + 4, // 64 bit register (high word)
        MODEL_SW_TRACE2_DATA2      = 0x20 + 0x418, // 64 bit register
        MODEL_SW_TRACE2_DATA2_high = 0x20 + 0x418 + 4, // 64 bit register (high word)

        MODEL_SW_TRACE3_TUBE       = 0x40 + 0x400, // 8 bit register
        MODEL_SW_TRACE3_DATA0      = 0x40 + 0x408, // 64 bit register
        MODEL_SW_TRACE3_DATA0_high = 0x40 + 0x408 + 4, // 64 bit register (high word)
        MODEL_SW_TRACE3_DATA1      = 0x40 + 0x410, // 64 bit register
        MODEL_SW_TRACE3_DATA1_high = 0x40 + 0x410 + 4, // 64 bit register (high word)
        MODEL_SW_TRACE3_DATA2      = 0x40 + 0x418, // 64 bit register
        MODEL_SW_TRACE3_DATA2_high = 0x40 + 0x418 + 4, // 64 bit register (high word)
        
        MODEL_SW_TRACE4_TUBE       = 0x60 + 0x400, // 8 bit register
        MODEL_SW_TRACE4_DATA0      = 0x60 + 0x408, // 64 bit register
        MODEL_SW_TRACE4_DATA0_high = 0x60 + 0x408 + 4, // 64 bit register (high word)
        MODEL_SW_TRACE4_DATA1      = 0x60 + 0x410, // 64 bit register
        MODEL_SW_TRACE4_DATA1_high = 0x60 + 0x410 + 4, // 64 bit register (high word)
        MODEL_SW_TRACE4_DATA2      = 0x60 + 0x418, // 64 bit register
        MODEL_SW_TRACE4_DATA2_high = 0x60 + 0x418 + 4, // 64 bit register (high word)

        MODEL_SW_TRACE_LAST,


        DCS_AID       = 0xFF8, // Auxiliary platform ID register

        DCS_ID        = 0xFFC,

        // Not implemented!  Only for debuggers
        DBG_RST_CTRL  = 0x520,
        DBG_RST_SCHED = 0x018,

        INVALID_REGISTER = 4 * 1024 - 1 // also acts as a mask
    };

    //! Return the register_identifier_t from a transaction, if it
    //  is misaligned or the wrong size then it will return INVALID_REGISTER
    //  otherwise it will return the right value.
    template<typename Transaction>
    inline register_identifier_t to_register( Transaction const& t_ )
    {
        pv::bus_addr_t const offset = t_.getAddress() & INVALID_REGISTER;

        if (offset >= MODEL_SW_TRACE_TUBE
            && offset < MODEL_SW_TRACE_LAST)
        {
            // Allow all sized transfers.
            return register_identifier_t( offset );
        }

        const bool doConversion = ((offset & 0x3) == 0
                                   || offset <= RST_STAT1
                                   || (offset <= CLUSTER0_CFG_R && offset <= DCS_CFG_R)
                                   || (offset <= BX_ADDR_CL0_CPU0 && offset <= BX_ADDR_CL1_CPU3_high)
                                   || (offset <= DCS_LEDS && offset <= DCS_SW)
                                   || (offset <= INT_CTRL && offset <= INT_FREQ)
                                   || (offset <= INT_TYPE0 && offset <= INT_ACK)
                                   || (offset <= INT_SEQ_first && offset <= INT_SEQ_last)
                                   || (offset <= DCS_AID && offset <= DCS_ID)
                                   || (offset == DBG_RST_CTRL)
                                   || (offset == DBG_RST_SCHED)
                                  ) &&
                                  (t_.getAccessByteWidth() == 4);

        
        return doConversion ? register_identifier_t( offset ) : INVALID_REGISTER;
    }
}


#endif
