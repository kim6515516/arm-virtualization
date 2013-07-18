/*!
 *  \file   ac97_defs.h
 *  \brief  AC97 Register Definitions
 *  \date   Copyright ARM Limited 2007-2008 All Rights Reserved.
 *  
 *  This encodes the definitions from Intel ac97_r23.pdf
 */

#ifndef INCLUDED_AC97_DEFS_H
#define INCLUDED_AC97_DEFS_H

// Secondary codec register address is in bits [18:12] of slot 1
// ac97_r23.pdf p31 output p34 input
#define SL1MASK 0x0007F000
#define REGTOSL1(x) (x<<12)
#define SL1TOREG(x) (x>>12)
#define SL1READ     (1<<19)
// Secondary codec register values are in bits [19:4] of slot 2
// ac97_r23.pdf p35
#define SL2MASK 0x000FFFF0
#define VALTOSL2(x) (x<<4)
#define SL2TOVAL(x) (x>>4)

// AC97 Secondary Codec Registers
// ac97_r23.pdf p47

/*! Reset */
#define PV_AC97_RESET           0x00
/*! Master volume */
#define PV_AC97_MASTERVOL       0x02
/*! AUX out volume */
#define PV_AC97_AUXVOL          0x04
/*! Mono volume */
#define PV_AC97_MONOVOL         0x06
/*! Master tone */
#define PV_AC97_MASTERTONE      0x08
/*! PC beep volume */
#define PV_AC97_BEEPVOL         0x0A
/*! Phone volume */
#define PV_AC97_PHONEVOL        0x0C
/*! MIC volume */
#define PV_AC97_MICVOL          0x0E
/*! Line in volume */
#define PV_AC97_LINEVOL         0x10
/*! CD volume */
#define PV_AC97_CDVOL           0x12
/*! Video volume */
#define PV_AC97_VIDEOVOL        0x14
/*! AUX in volume */
#define PV_AC97_AUXINVOL        0x16
/*! PCM out volume */
#define PV_AC97_PCMVOL          0x18
/*! Record Select */
#define PV_AC97_RECSEL          0x1A
/*! Record Gain */
#define PV_AC97_RECGAIN         0x1C
/*! Record Gain Mic */
#define PV_AC97_RECMICGAIN      0x1E
/*! General Purpose */
#define PV_AC97_GEN             0x20
/*! 3D Control */
#define PV_AC97_3DCTRL          0x22
/*! Audio Int & Paging */
#define PV_AC97_AIP             0x24
/*! Powerdown control & status */
#define PV_AC97_PDCTRL          0x26
/*! Extended Audio ID */
#define PV_AC97_EXTAUDID        0x28
/*! Extended Audio Control */
#define PV_AC97_EXTAUDCTRL      0x2A
/*! PCM Front DAC Rate */
#define PV_AC97_PCMFDACRATE     0x2C
/*! PCM Surround DAC Rate */
#define PV_AC97_PCMSDACRATE     0x2E
/*! PCM LFE DAC Rate */
#define PV_AC97_PCMLFEDACRATE   0x30
/*! PCM L/R DAC Rate */
#define PV_AC97_PCMLRADCRATE    0x32
/*! PCM Mic ADC Rate */
#define PV_AC97_PCMMICADCRATE   0x34
/*! Centre/LFE Volume */
#define PV_AC97_PCMCENLFEVOL    0x36
/*! Surround Volume */
#define PV_AC97_SURRVOL         0x38
/*! S/PDIF Control */
#define PV_AC97_SPDIFCTRL       0x3A
/*! Vendor ID 1 */
#define PV_AC97_VID1            0x7C
/*! Vendor ID 2 */
#define PV_AC97_VID2            0x7E


// LM4549A Secondary codec values
// LM4549A.pdf p15

#define PV_LM4519A_RESET    0x0D40
#define PV_LM4519A_EXTID    0x0001
#define PV_LM4519A_PDCTRL   0x000F
#define PV_LM4519A_3DCTL    0x0101
#define PV_LM4519A_VID1     0x4E53
#define PV_LM4519A_VID2     0x4349

#endif

/* eof ac97_defs.h */
