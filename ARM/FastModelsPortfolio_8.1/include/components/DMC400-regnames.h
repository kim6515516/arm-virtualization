/*
   Define various enums and constants used by the DMC400 model  

   Copyright 2012 ARM Limited; all rights reserved
*/

#ifndef _DMC400_regnames_h
#define _DMC400_regnames_h

enum DMC400_REVISION {
  DMC400_REVISION_R0P1,
  DMC400_REVISION_R1P0,
  DMC400_REVISION_R1P1,
  DMC400_REVISION_INVALID };

enum DMC400_SIZES {
  DMC400_APB_SPACE_SIZE = 0x1000  // The APB interface has 4kb of space
};

enum DMC400_MEMORY_TYPES {
  DMC400_CONNECTED  = 0x0,
  DMC400_NOT_CONNECTED = 0xFFFFFFFF
};

enum DMC400_MEMC_STATES {             //the states of the memory controller
  DMC400_CONFIG      = 0,
  DMC400_LOWPOWER    = 1,
  DMC400_PAUSED      = 2,
  DMC400_READY       = 3
};

enum DMC400_REG_OFFSET {
  DMC400_MEMC_STATUS         = 0x000,      //RO - Memory Controller Status Register
  DMC400_MEMC_CONFIG         = 0x004,      //WO - Memory Controller Config Register
  DMC400_MEMC_CMD            = 0x008,      //WO - Memory Command Register
  DMC400_ADDRESS_CONTROL     = 0x010,      //RW - Address Control Register
  DMC400_DECODE_CONTROL      = 0x014,      //RW - Decode Control Register
  DMC400_FORMAT_CONTROL      = 0x018,      //RW - Format Control Register
  DMC400_LOWPOWER_CONTROL    = 0x020,      //RW - LowPwer Control Register

  DMC400_TURNAROUND_PRIORITY = 0x030,      //RW - turnaround priority register
  DMC400_HIT_PRIORITY        = 0x034,      //RW - Hit Priority Register

  DMC400_QOS0_CONTROL        = 0x038,      //RW - qos0 control register
  DMC400_QOS1_CONTROL        = 0x03C,      //RW - qos1 control register
  DMC400_QOS2_CONTROL        = 0x040,      //RW - qos2 control register
  DMC400_QOS3_CONTROL        = 0x044,      //RW - qos3 control register
  DMC400_QOS4_CONTROL        = 0x048,      //RW - qos4 control register
  DMC400_QOS5_CONTROL        = 0x04C,      //RW - qos5 control register
  DMC400_QOS6_CONTROL        = 0x050,      //RW - qos6 control register
  DMC400_QOS7_CONTROL        = 0x054,      //RW - qos7 control register
  DMC400_QOS8_CONTROL        = 0x058,      //RW - qos8 control register
  DMC400_QOS9_CONTROL        = 0x05C,      //RW - qos9 control register
  DMC400_QOS10_CONTROL       = 0x060,      //RW - qos10 control register
  DMC400_QOS11_CONTROL       = 0x064,      //RW - qos11 control register
  DMC400_QOS12_CONTROL       = 0x068,      //RW - qos12 control register
  // note that there is a gap here
  DMC400_QOS13_CONTROL       = 0x070,      //RW - qos13 control register
  DMC400_QOS14_CONTROL       = 0x074,      //RW - qos14 control register
  DMC400_QOS15_CONTROL       = 0x078,      //RW - qos15 control register
  DMC400_TIMEOUT_CONTROL     = 0x07C,      //RW - Timeout control register
  DMC400_QUEUE_CONTROL       = 0x080,      //RW - Queue control register
  DMC400_WRITE_PRIORITY_CONTROL = 0x088,  //RW - write priority control register
  DMC400_WRITE_PRIORITY_CONTROL2 = 0x08C, //RW - write priority control2 register
  DMC400_READ_PRIORITY_CONTROL = 0x090,   //RW - read priority control register
  DMC400_READ_PRIORITY_CONTROL2 = 0x094,  //RW - read priority control register
  DMC400_ACCESS_ADDRESS_MATCH = 0x098,      //RW - Access address match register
  DMC400_ACCESS_ADDRESS_MATCH_63_32 = 0x09C,//RW - Access address match 63_32 register
  DMC400_ACCESS_ADDRESS_MASK = 0x0A0,       //RW - Access address mask register
  DMC400_ACCESS_ADDRESS_MASK_63_32 = 0x0A4, //RW - Access address mask 63_32 register

  DMC400_CHANNEL_STATUS      = 0x100,      //R0 - Channel Status register
  DMC400_DIRECT_CMD          = 0x108,      //WO - Direct command register
  DMC400_MR_DATA             = 0x110,      //RO - mr_data register
  DMC400_REFRESH_CONTROL     = 0x120,      //RW - refresh control register
  DMC400_INTERRUPT_CONTROL   = 0x128,      //RW - interrupt control register
  DMC400_INTERRUPT_CLR       = 0x130,      //WO - interrupt clr register
  DMC400_INTERRUPT_STATUS    = 0x138,      //RO - interrupt status register
  DMC400_INTERRUPT_INFO      = 0x140,      //RO - interrupt info register
  DMC400_MODE_CONTROL        = 0x148,      //RW - ECC control register

  DMC400_T_REFI              = 0x200,      //RW - t_refi
  DMC400_T_RFC               = 0x204,      //RW - t_rfc
  DMC400_T_MRR               = 0x208,      //RW - t_mrr
  DMC400_T_MRW               = 0x20C,      //RW - t_mrw
  DMC400_T_RCD               = 0x218,      //RW - t_rcd
  DMC400_T_RAS               = 0x21C,      //RW - t_ras
  DMC400_T_RP                = 0x220,      //RW - t_rp
  DMC400_T_RPALL             = 0x224,      //RW - t_rpall
  DMC400_T_RRD               = 0x228,      //RW - t_rrd
  DMC400_T_FAW               = 0x22C,      //RW - t_faw
  DMC400_READ_LATENCY        = 0x230,      //RW - read_latency
  DMC400_T_RTR               = 0x234,      //RW - t_rtr
  DMC400_T_RTW               = 0x238,      //RW - t_rtw
  DMC400_T_RTP               = 0x23C,      //RW - t_rtp
  DMC400_WRITE_LATENCY       = 0x240,      //RW - write_latency
  DMC400_T_WR                = 0x244,      //RW - t_wr
  DMC400_T_WTR               = 0x248,      //RW - t_wtr
  DMC400_T_WTW               = 0x24C,      //RW - t_wtw
  DMC400_T_ECKD              = 0x250,      //RW - t_eckd
  DMC400_T_XCKD              = 0x254,      //RW - t_xckd
  DMC400_T_EP                = 0x258,      //RW - t_ep
  DMC400_T_XP                = 0x25C,      //RW - t_xp
  DMC400_T_ESR               = 0x260,      //RW - t_esr
  DMC400_T_XSR               = 0x264,      //RW - t_xsr
  DMC400_T_SRCKD             = 0x268,      //RW - t_srckd
  DMC400_T_CKSRD             = 0x26C,      //RW - t_cksrd

  DMC400_T_RDDATA_EN         = 0x300,      //RW - t_rddata_en
  DMC400_T_PHYWRLAT          = 0x304,      //RW - t_phywrlt
  DMC400_RDLVL_CONTROL       = 0x308,      //RW - rdlvl_control
  DMC400_RDLVL_MRS           = 0x30C,      //RW - rdlvl_mrs
  DMC400_RDLVL_DIRECT        = 0x310,      //WO - rdlvl_direct
  DMC400_T_RDLVL_EN          = 0x318,      //RW - t_rdlvl_en
  DMC400_T_RDLVL_RR          = 0x31C,      //RW - t_rdlvl_rr
  DMC400_WRLVL_CONTROL       = 0x328,      //RW - wrlvl_control
  DMC400_WRLVL_MRS           = 0x326,      //RW - wrlvl_mrs
  DMC400_WRLVL_DIRECT        = 0x330,      //WO - wrlvl_control
  DMC400_T_WRLVL_EN          = 0x338,      //RW - t_wrlvl_en
  DMC400_T_WRLVL_WW          = 0x33C,      //RW - t_wrlvl_ww
  DMC400_PHY_POWER_CONTROL   = 0x348,      //RW - phy_power_control
  DMC400_PHY_UPDATE_CONTROL  = 0x350,      //RW - phy_update_control
  DMC400_T_LPRESP            = 0x358,      //RW - t_lpresp (PHY low-power request time) (r1 only)

  DMC400_USER_STATUS         = 0x400,      //RO - user_status register
  DMC400_USER_CONFIG0        = 0x404,      //RW - user_config0 register
  DMC400_USER_CONFIG1        = 0x408,      //RW - user_config1 register

  DMC400_INTEG_CFG           = 0xE00,      //RW - integ_cfg register
  DMC400_INTEG_OUTPUTS       = 0xE08,      //WO - integ_outputs register

  DMC400_PERIPH_ID_4     = 0xFD0,

  DMC400_PERIPH_ID_0     = 0xFE0,
  DMC400_PERIPH_ID_1     = 0xFE4,
  DMC400_PERIPH_ID_2     = 0xFE8,
  DMC400_PERIPH_ID_3     = 0xFEC,

  DMC400_PCELL_ID_0      = 0xFF0,
  DMC400_PCELL_ID_1      = 0xFF4,
  DMC400_PCELL_ID_2      = 0xFF8,
  DMC400_PCELL_ID_3      = 0xFFC
};
#endif

