//-----------------------------------------------------------------------------
// The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from ARM Limited.
//
//            (C) COPYRIGHT 2006 ARM Limited.
//                ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from ARM Limited.
//-----------------------------------------------------------------------------

/*
 *    Class definition of the DIC (Cortex-A9's Interrupt controller)
 *
 *
 * Revision $Revision: 57012 $
 * Checkin  $Date: 2008-03-28 16:30:13 +0000 (Fri, 28 Mar 2008) $
 * Revising $Author: jeacot01 $
 * State    $State$
 */
#include "sg/IncludeMeFirst.h"
#include "hostconf/zinttypes.h"

//#define DEBUG_DBG_ACCESS  // uncomment to trace calls to read[Dbg]*() and write[Dbg]*()
//#define GIC_TRACE         // uncomment to trace accesses to each register.

#include "GIC.h"
#include <stdio.h>  // for fprintf()
#include <stdarg.h> // for vfrpintf() and va_list stuff.


#define IS_16BIT_ALIGNED(addr) (((addr) & 0x1) == 0)
#define IS_32BIT_ALIGNED(addr) (((addr) & 0x3) == 0)
#define IS_64BIT_ALIGNED(addr) (((addr) & 0x7) == 0)

// IMPLEMENTATION DEFINED (from PRD03-GENC-004392 7.0)
// - The way pending interrupts of equal priority are resolved.
// - impl. def. regions (0x40 in CPU interfaces, 0xD00 in distributor)
// - programming the priority register takes immediate effect on active interrupts or not (see 3.6.1  in PRD03-GENC-004392 7.0)
// - some settings can be made read-only (see last paragraph of section 3.5.1 page 10 in PRD03-GENC-004392 7.0)
// - whether legacy nFIQ / nIRQ operation is supported (see section 3.6 of PRD03-GENC-004392 7.0)
// - Implementations may support the ability to lock the control register (last paragraph of section 3.6.1 page 11)
// - Priorities: Interrupts which are used for a particular purpose within an implementation may have read-only priority values.
//

#undef BIT
#undef SETBIT
#undef CLRBIT
#undef GETFIELD
#undef SETFIELD

#define BIT(var,n)       ((MxU32)((var) >> (n)) & 1)
#define SETBIT(var,n)    ( var = ((var) |  (1 << (n))))
#define CLRBIT(var,n)    ( var = ((var) & ~(1 << (n))))
#define GETFIELD(var, n, fieldsize) ((MxU32)((var) >> (n)) & ((1 << (fieldsize)) - 1))
#define SETFIELD(var, n, fieldsize, value)  ((var) = ( (var) & ~(((1 << (fieldsize)) - 1 ) << (n))) | \
                                                     ( (value) &  ((1 << (fieldsize)) - 1) ) << (n) )

// NB: macro uses a positive mask (ie 1 for the bits you want to modify)
#define NEWVAL_WITH_MASK(val, mask, data) (((val) & ~(mask)) | ((data) & (mask)))

#define IS_UNSECURE_DOMAIN(x) ((x) == NONSECURE)
#define IS_SECURE_DOMAIN(x)   ((x) == SECURE)
#define IS_VALID_DOMAIN(x)    ((x) >= 0 && (x) < MAX_N_SECURE_DOMAIN)
#define IS_IN_SECURE_PRIORITY_RANGE(prio) (!((prio) & (1<<7)))

#define IS_VALID_CPUID(id) ((unsigned int)(id) < n_cores)

#define IS_REAL_INTERRUPT(id)      ((unsigned int)(id) < MAX_N_INT_LINES)
#define IS_SPURIOUS_INTERRUPT(id)  ((id) == 1022 || (id) == 1023)
#define IS_SECURE_INTERRUPT(id, core)  isSecure(id, core)
#define IS_BANKED_INTERRUPT(id)        ((unsigned int)(id) <= 31)
#define IS_1N_INTERRUPT(id)            is1N(id)
#define IS_SOFTWARE_INTERRUPT(id)      ((unsigned int)(id) < N_SOFTWARE_INT)
#define IS_LEVEL_SENSITIVE(id, core)   (!IS_SOFTWARE_INTERRUPT(id) && !isEdgeTriggered(id, core))

#define IS_ACTIVE_ON_CPU(int_no, core) (coreFSM[core][int_no] == ACTIVE        ||\
                                        coreFSM[core][int_no] == ACTIVEPENDING ||\
                                        coreFSM[core][int_no] == ACTIVEPENDING_LVL)
#define IS_ACTIVE_ON_ANY_CPU(int_no, core)  isActive(int_no, core)
#define IS_PENDING_ON_CPU(int_no, core_id)  (coreFSM[core_id][int_no] == PENDING      ||\
                                             coreFSM[core_id][int_no] == PENDING_LVL  ||\
                                             coreFSM[core_id][int_no] == ACTIVEPENDING||\
                                             coreFSM[core_id][int_no] == ACTIVEPENDING_LVL)
#define IS_STICKY_PENDING_ON_CPU(int_no, core_id) (coreFSM[core_id][int_no] == PENDING   ||\
                                                   coreFSM[core_id][int_no] == ACTIVEPENDING)

#define IS_STICKY_PENDING(int_no, core) isStickyPending(int_no, core)
#define IS_INACTIVE_ON_CPU(int_no, core) (coreFSM[core][int_no] == INACTIVE)

// check argument interrupt is not disabled by DISTRIBUTOR's CONTROL reg.
#define IS_CTR_ENABLED(int_no, core)    (gic_ctrl[getDomain((int_no), (core))] == 1)
// check the control register in CPU interface
#define IS_IF_ENABLED(core, domain)         (BIT(c_ctrl_reg[core][domain], 0))
#define IS_IF_FIQEn(core)                   (BIT(c_ctrl_reg[core][SECURE], 3))
#define IS_IF_SPBPR(core)                   (BIT(c_ctrl_reg[core][SECURE], 4))

#ifndef NO_LEGACY_IRQ
// check if legacy interrupt is GIC driven or pass-thru (see PRD03-GENC-004392 7.0, tab. 4-12 p30)
#define IRQ_IS_GIC_DRIVEN(core) ( (IS_IF_ENABLED(core, NONSECURE)) || \
                                  (IS_IF_ENABLED(core, SECURE) && !IS_IF_FIQEn(core)) )

#define FIQ_IS_GIC_DRIVEN(core) (IS_IF_FIQEn(core) && IS_IF_ENABLED(core, SECURE))
#endif

#define IS_LOCKED_INTERRUPT(id, cpu) (IRQ_BASE_EXT <= (id) && (id) < IRQ_BASE_EXT + NBR_LSPI && IS_SECURE_INTERRUPT(id, cpu))


/** THE CPU INTERFACE REGISTERS (see PR231-GENC-006924 5.8, table 4-10, page 26) */
/* 0x00 Read/Write      Banked  0x00000000      Control Register */
#define CIF_CTRL_R_OFF       0x00
#define CIF_CTRL_R_RST_VAL   0x00000000
#define CIF_CTRL_R_S_MASK    0x0000001F
#define CIF_CTRL_R_NS_MASK   0x00000001
#define ACKCTL(reg)          ((reg) >> 2 & 0x1) // see PR231-GENC-006924 5.3, fig 3-10-2, p24.

/* 0x04 Read/Write      Security dependent      0x00000000      Priority Mask Register */
#define PRIO_MASK_R_OFF      0x04
#define PRIO_MASK_R_RST_VAL  0x00000000
#define PRIO_MASK_R_MASK     prio_mask_r_mask

/* 0x08 Read/Write      Banked  IMP dependent   Binary Point Register */
#define BINARY_POINT_R_OFF     0x08
#define BINARY_POINT_R_RST_VAL bp_min_val
#define BINARY_POINT_R_MASK    0x00000007
#define BINARY_POINT_R_MIN     bp_min_val

/* 0x0C Read Only       Security dependent      0x000003ff      Interrupt Acknowledge Register */
#define ACK_R_OFF            0x0C
#define ACK_R_RST_VAL        0x000003ff

/* 0x10 Write Only      Security dependent      -       End of Interrupt Register  */
#define EOI_R_OFF            0x10
#define EOI_R_MASK           0x00001FFF

/* 0x14 Read Only       Security dependent      0x000000ff      Running Priority Register  */
#define RUN_PRIO_R_OFF       0x14
#define RUN_PRIO_R_RST_VAL   0x000000ff

/* 0x18 Read Only       Security dependent      0x000003ff      Highest Pending Interrupt Register */
#define HIGHST_PEND_R_OFF     0x18
#define HIGHST_PEND_R_RST_VAL 0x000003ff

/* 0x1C Read/Write      Restricted      0x00000000      Aliased Non-Secure Binary point Register */
#define NS_BINARY_POINT_R_OFF     0x1C
#define NS_BINARY_POINT_R_RST_VAL (bp_min_val + 1)


/* 0x40-0xCF    IMP     IMP     IMP     IMPLEMENTATION DEFINED */
#define CIF_IMPL_DEF_R_OFF     0x40
#define CIF_IMPL_DEF_R_RST_VAL 0x00000000


/* 0xFC Read Only       Common  IMP     CPU Interface Implementer Identification Register */
#define CIF_IMPL_ID_R_OFF     0xFC
#define CIF_IMPL_ID_R_RST_VAL 0x3901043B



/* THE DISTRIBUTOR REGISTERS (see PR231-GENC-006924 5.2 at table 3.3) */
/* 0x000 Read/Write     Banked  0x00000000      Control Registers */
#define CTRL_R_OFF     0x000
#define CTRL_R_SIZE    4     /* in 8bit word */
#define CTRL_R_RST_VAL 0x00000000
#define CTRL_R_MASK    0x00000001

/* 0x004 Read Only      Common  IMP dependent   Interrupt Controller Type Register */
#define GIC_TYPE_R_OFF  0x004
#define GIC_TYPE_R_SIZE 4         /* in 8bit byte */
#define GIC_TYPE_R_RST_VAL (gic_type_r_val)

/* 0x008 Read Only      Common  IMP dependent   Distributor Implementer Identification Register */
#define DIST_IMPL_ID_R_OFF  0x008
#define DIST_IMPL_ID_R_SIZE 4     /* in 8bit byte */
#if defined(CORTEX_A9_SPECIFIC_GIC)
#define DIST_IMPL_ID_R_RST_VAL 0x100043B
#else
#define DIST_IMPL_ID_R_RST_VAL 0x143B  /* (see PR231-GENC-006924 5.2 at section 3.8.1.5) */
#endif

/* 0x080 Read/Write     Restricted      0x00000000      Irq 0 to 31 Interrupt Security Register */
/* 0x0FC Read/Write     Restricted      0x00000000      Irq 992 to 1019 Interrupt Security Register */
#define INT_SEC_REG_OFF       0x080
#define INT_SEC_REG_FIELDSIZE (INT_SEC_REG_SIZE / (1<<7))            /* in bit */
#define INT_SEC_REG_FIELDNBR  (32 / INT_SEC_REG_FIELDSIZE)
#define INT_SEC_REG_FIELDMASK ((1 << INT_SEC_REG_FIELDSIZE) - 1)
#define INT_SEC_REG_BANKED    INT_SEC_REG_FIELDSIZE
#define INT_SEC_REG_RST_VAL   0x00000000


/* 0x100 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Enable Set Register */
/* 0x17C Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Enable Set Register  */
#define ENABLE_SET_REG_OFF       0x100
#define ENABLE_SET_REG_FIELDSIZE (ENABLE_SET_REG_SIZE / (1<<7))            /* in bit */
#define ENABLE_SET_REG_FIELDNBR  (32 / ENABLE_SET_REG_FIELDSIZE)
#define ENABLE_SET_REG_FIELDMASK ((1 << ENABLE_SET_REG_FIELDSIZE) - 1)
#define ENABLE_SET_REG_BANKED    ENABLE_SET_REG_FIELDSIZE
#define ENABLE_SET_REG_RST_VAL   0x00000000

/* 0x180 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Enable Clear Register */
/* 0x1FC Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Enable Clear Register */
#define ENABLE_CLEAR_REG_OFF       0x180
#define ENABLE_CLEAR_REG_FIELDSIZE ENABLE_SET_REG_FIELDSIZE
#define ENABLE_CLEAR_REG_FIELDNBR  ENABLE_SET_REG_FIELDNBR
#define ENABLE_CLEAR_REG_FIELDMASK ENABLE_SET_REG_FIELDMASK
#define ENABLE_CLEAR_REG_BANKED    ENABLE_SET_REG_BANKED
#define ENABLE_CLEAR_REG_RST_VAL   ENABLE_SET_REG_RST_VAL


/* 0x200 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Pending Set Register */
/* 0x27C Read/Write     NS-intsr dependent      0x00000000      rq 992 to 1019 Pending Set Register */
#define PENDING_SET_REG_OFF       0x200
#define PENDING_SET_REG_FIELDSIZE (PENDING_SET_REG_SIZE / (1<<7))            /* in bit */
#define PENDING_SET_REG_FIELDNBR  (32 / PENDING_SET_REG_FIELDSIZE)
#define PENDING_SET_REG_FIELDMASK ((1 << PENDING_SET_REG_FIELDSIZE) - 1)
#define PENDING_SET_REG_BANKED    PENDING_SET_REG_FIELDSIZE
#define PENDING_SET_REG_RST_VAL   0x00000000

/* 0x280 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Pending Clear Register */
/* 0x2FC Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Pending Clear Register */
#define PENDING_CLEAR_REG_OFF       0x280
#define PENDING_CLEAR_REG_FIELDSIZE (PENDING_CLEAR_REG_SIZE / (1<<7))           /* in bit */
#define PENDING_CLEAR_REG_FIELDNBR  (32 / PENDING_CLEAR_REG_FIELDSIZE)
#define PENDING_CLEAR_REG_FIELDMASK ((1 << PENDING_CLEAR_REG_FIELDSIZE) - 1)
#define PENDING_CLEAR_REG_BANKED    PENDING_CLEAR_REG_FIELDSIZE
#define PENDING_CLEAR_REG_RST_VAL   PENDING_SET_REG_RST_VAL


/* 0x300 Read Only NS-intsr dependent   0x00000000      Irq 0 to 31 Active Bit Register */
/* 0x37C Read Only NS-intsr dependent   0x00000000      Irq 992 to 1019 Active Bit Register */
#define ACTIVE_BIT_REG_OFF       0x300
#define ACTIVE_BIT_REG_FIELDSIZE (ACTIVE_BIT_REG_SIZE / (1<<7))           /* in bit */
#define ACTIVE_BIT_REG_FIELDNBR  (32 / ACTIVE_BIT_REG_FIELDSIZE)
#define ACTIVE_BIT_REG_FIELDMASK ((1 << ACTIVE_BIT_REG_FIELDSIZE) - 1)
#define ACTIVE_BIT_REG_BANKED    ACTIVE_BIT_REG_FIELDSIZE
#define ACTIVE_BIT_REG_RST_VAL   0x00000000

/* 0x400 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 3 Priority Register */
/* 0x7F8 Read/Write     NS-intsr dependent      0x00000000      Irq 1016 to 1019 Priority Register */
#define PRIORITY_REG_OFF       0x400
#define PRIORITY_REG_FIELDSIZE (PRIORITY_REG_SIZE / (1<<7))            /* in bit */
#define PRIORITY_REG_FIELDNBR  (32 / PRIORITY_REG_FIELDSIZE)
#define PRIORITY_REG_FIELDMASK ((1 << PRIORITY_REG_FIELDSIZE) - 1)
#define PRIORITY_REG_BANKED    PRIORITY_REG_FIELDSIZE
#define PRIORITY_REG_RST_VAL   0x00000000
// some bitfields are SBZ
#define PRIORITY_REG_MASK    (priority_mask)

/* 0x800 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 3 CPU Targets Register */
/* 0xBF8 Read/Write     NS-intsr dependent      0x00000000      Irq 1016 to 1019 CPU Targets Register */
#define TARGETS_REG_OFF        0x800
#define TARGETS_REG_FIELDSIZE   (TARGETS_REG_SIZE / (1<<7))            /* in bit */
#define TARGETS_REG_FIELDNBR  (32 / TARGETS_REG_FIELDSIZE)
#define TARGETS_REG_FIELDMASK ((1 << TARGETS_REG_FIELDSIZE) - 1)
#define TARGETS_REG_BANKED    TARGETS_REG_FIELDSIZE
#define TARGETS_REG_RST_VAL   0x00000000
#define TARGETS_REG_MASK      (((1 << n_cores) - 1) << 24 | ((1 << n_cores) - 1) << 16 | \
                               ((1 << n_cores) - 1) <<  8 | ((1 << n_cores) - 1))

/* 0xC00 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 15 Configuration Register */
/* 0xCFC Read/Write     NS-intsr dependent      0x00000000      Irq 1008 to 1019 Configuration Register */
#define CONFIGURATION_REG_OFF       0xC00
#define CONFIGURATION_REG_FIELDSIZE (CONFIGURATION_REG_SIZE / (1<<7))            /* in bit */
#define CONFIGURATION_REG_FIELDNBR  (32 / CONFIGURATION_REG_FIELDSIZE)
#define CONFIGURATION_REG_FIELDMASK ((1 << CONFIGURATION_REG_FIELDSIZE) - 1)
#define CONFIGURATION_REG_BANKED    CONFIGURATION_REG_FIELDSIZE
#define CONFIGURATION_REG_RST_VAL   0x55555555

/* 0xD00        IMP     IMP     IMP     IMPLEMENTATION DEFINED */
/* ... */
/* 0xDFC        IMP     IMP     IMP     IMPLEMENTATION DEFINED */
#define IMPLEMENTATION_DEFINED_REG_OFF     0xD00
#define IMPLEMENTATION_DEFINED_REG_RST_VAL 0x00000000


/* 0xF00        Write Only      Banked   -      Software Interrupt Register */
#define SOFTWARE_INTERRUPT_REG_OFF     0xF00
#define SOFTWARE_INTERRUPT_REG_RST_VAL 0  /* dummy */
#define SOFTWARE_INTERRUPT_REG_MASK    ((0x3 << 24) | (0xFF << 16) | (1 << 15) | (0xF))


/* 0xFD0        Read Only       Common  IMP dependent   Identification Register */
/* 0xFFC        Read Only       Common  IMP dependent   Identification Register */
#define IDENTIFICATION_REG_OFF      0xFD0
#define IDENTIFICATION_REG_RST_VAL  0   /* dummy, initialized separately */


/** get the value of interrupt input signal*/
#define INT_SIG_VALUE(int_id, core) (signal_port_irq[IS_BANKED_INTERRUPT(int_id) ? (core) : 0][int_id])


/** macro used to decide which status to return when one of the two 32
    bit accesses that make a 64 bit access fails. */
#define max_error(x, y)  \
  (((x) == MX_STATUS_ERROR    || (y) == MX_STATUS_ERROR)    ? MX_STATUS_ERROR : \
   ((x) == MX_STATUS_NOACCESS || (y) == MX_STATUS_NOACCESS) ? MX_STATUS_NOACCESS : \
   ((x) == MX_STATUS_NOMEMORY || (y) == MX_STATUS_NOMEMORY) ? MX_STATUS_NOMEMORY : \
   ((x) == MX_STATUS_OK) ? (y) : (x) )
  /** @todo discuss the priorities above (most probably not important).*/

/** For message */
#define domain2str(domain) (IS_SECURE_DOMAIN(domain) ? "SECURE" : "UNSECURE")

//////////////////////////////////////////////////////////////////////////
/** Constructors of the Generic Interrupt Controller (GIC) top component */
GIC::GIC() :
  n_cores(MAX_N_CORES),
  n_ints(MAX_N_INT_LINES)
#define gic_msg_fl gic_msg
{
   init();
}

/** Constructor.
    @param n_cpu : number of cores (1 ..MAX_N_CORES)
    @param n_interrupts : total number of interrupts (including private interrupts 0..31).*/
GIC::GIC(unsigned int n_cpu, unsigned int n_interrupts) :
  n_cores(n_cpu),
  n_ints(n_interrupts)
{
  if (n_cpu > MAX_N_CORES)
    gic_msg_fl(LOG_FATAL, " bad argument to GIC constructor (n_cpu = %u)", n_cpu);
  if (n_interrupts > MAX_N_INT_LINES)
    gic_msg_fl(LOG_FATAL, " bad argument to GIC constructor (n_interrupts %u > %u)", n_interrupts, MAX_N_INT_LINES);

#ifndef NO_LEGACY_IRQ
  if (n_interrupts < LEGACY_IRQ_ID + 1)
    gic_msg_fl(LOG_FATAL, " bad argument to GIC constructor (n_interrupts %u < %u)", n_interrupts, LEGACY_IRQ_ID + 1);
  if (n_interrupts < LEGACY_FIQ_ID + 1)
    gic_msg_fl(LOG_FATAL, " bad argument to GIC constructor (n_interrupts %u < %u)", n_interrupts, LEGACY_FIQ_ID + 1);
#endif
  if (n_interrupts < IRQ_BASE_EXT)
    gic_msg_fl(LOG_FATAL, " bad argument to GIC constructor (n_interrupts %u < %u)", n_interrupts, IRQ_BASE_EXT);

  init();
}

void
GIC::init(void)
{
   /** 1. build the mask used when priority mask registers in DISTRIBUTOR and
      priority registers in CPU interfaces are written to. (see
      PR231-GENC-006924 5.2 sections 3.8.2.2 and 3.7.1) */
  {
    unsigned int prio_bit_nbr;
    switch (N_PRIORITY_LEVELS) {
    case 16:  prio_bit_nbr = 4; break;
    case 32:  prio_bit_nbr = 5; break;
    case 64:  prio_bit_nbr = 6; break;
    case 128: prio_bit_nbr = 7; break;
    case 256: prio_bit_nbr = 8; break;
    default:
      gic_msg_fl(LOG_FATAL, "bad number of priority levels %d", N_PRIORITY_LEVELS);
      break;
    }
    bp_min_val = (7 > prio_bit_nbr) ? (7 - prio_bit_nbr) : 0;
    // dont get confused, this is the mask for the PRIORITY MASK registers in the CPU interfaces
    prio_mask_r_mask = (0xFF << (8 - prio_bit_nbr)) & 0xFF;

    // and this is the mask for the PRIORITY registers in the distributor.
    priority_mask = ((prio_mask_r_mask << 24) | (prio_mask_r_mask << 16) |
                     (prio_mask_r_mask <<  8) | (prio_mask_r_mask      )   );
  }

  // value of DIC type register (see PR231-GENC-006924 5.6, section 3.8.1.3, page 15)
  gic_type_r_val = ( NBR_LSPI                       << 11 |  // LSPI
                    (trustzone_enabled ? 0x1 : 0x0) << 10 |  // Domains
                    ((n_cores - 1) & 0x7)           << 5  |  // CPU Number
                     (((n_ints >> 5) - 1) & 0x1F)   << 0  ); // IT lines number

  cfgsdisable = false; // By default, allow write to protected areas.

  // initialize all variables
  reset();
}

GIC::~GIC()
{
  // FREE ANY ALLOCATED MEMORY
  // currently, nothing to free.
}

void
GIC::reset(void)
{
  // Reset values of every register and every signals
#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "GIC::reset()");
#endif

  for (unsigned int cpu = 0; cpu < MAX_N_CORES; cpu ++) {
    // input signals
#ifndef NO_LEGACY_IRQ
    // legacy nIRQ/nFIQ
    signal_port_legacy_irq[cpu] = 0;
    signal_port_legacy_fiq[cpu] = 0;
#endif
    // interrupt request lines
    for (unsigned int j = 0; j < MAX_N_INT_LINES; j ++)
      signal_port_irq[cpu][j] = 0;
  }

  // DISTRIBUTOR's registers
    // 1. CONTROL REG
  for (unsigned int domain = 0; domain < MAX_N_SECURE_DOMAIN; domain++)
    gic_ctrl[domain] = CTRL_R_RST_VAL;

  // 2. Type Register (READ ONLY)
  // 3. Identifier (READ ONLY)

  // 4. Interrupt security register
  for (unsigned int cpu = 0; cpu < n_cores; cpu++) {
    for (unsigned int sub_offset = 0; sub_offset < (INT_SEC_REG_SIZE >> 2); sub_offset++)
      d_int_sec[cpu][sub_offset] = INT_SEC_REG_RST_VAL;

  // 5. Enable register
    for (unsigned int sub_offset = 0; sub_offset < (ENABLE_SET_REG_SIZE >> 2); sub_offset++)
      d_enable[cpu][sub_offset] =  ENABLE_SET_REG_RST_VAL;

    // Software interrupts are always permanently enabled (see PR231-GENC-006924 5.3 section 3.8.1.11)
    for (unsigned int i = 0; i < n_ints; i++)
      if (IS_SOFTWARE_INTERRUPT(i))
        setEnabled(i, cpu);

  // 6. Pending register
    for (unsigned int sub_offset = 0; sub_offset < (PENDING_SET_REG_SIZE >> 2); sub_offset++)
      d_pending[cpu][sub_offset] = PENDING_SET_REG_RST_VAL;

  // 7. ACTIVE BIT register
    for (unsigned int sub_offset = 0; sub_offset < (ACTIVE_BIT_REG_SIZE >> 2); sub_offset++)
      d_active_bit[cpu][sub_offset] = ACTIVE_BIT_REG_RST_VAL;

  // 8. PRIORITY
    for (unsigned int sub_offset = 0; sub_offset < (PRIORITY_REG_SIZE >> 2); sub_offset++)
      d_priority[cpu][sub_offset] = PRIORITY_REG_RST_VAL;
  }

  //9. TARGETS
  for (unsigned int sub_offset = 0; sub_offset < (TARGETS_REG_SIZE >> 2); sub_offset++)
    d_cpu_targets[sub_offset] = TARGETS_REG_RST_VAL;

  // 10. CONFIGURATION
  for (unsigned int cpu = 0; cpu < n_cores; cpu++) {
    for (unsigned int sub_offset = 0; sub_offset < (CONFIGURATION_REG_SIZE >> 2); sub_offset++)
      d_config[cpu][sub_offset] = CONFIGURATION_REG_RST_VAL;
#ifdef CORTEX_A9_SPECIFIC_GIC
    // special settings for private peripheral interrupts:
    // 31(legacy IRQ)->01 (level-s) 30(watchdg), 29(timer)->11 (edge-s), 28(legacy FIQ)->01 (level-s) (see 4.1.8 PRD03-GENC-004392 7.0)
    d_config[cpu][1] = 0x7d000000;
#endif
  }

  // 11. IMPLEMENTATION_DEFINED REGION: nothing
  // d_implidef[IMPLEMENTATION_DEFINED_REG_SIZE >> 2]

  // 12. SOFTWARE_INTERRUPT_REG: WRITE ONLY !

  // 13. IDENTIFICATION (see PR231-GENC-006924 2.1 section 4.1.4 "Identification Register"): WRITE ONLY !

  // CPU INTERFACES:
  for (unsigned int cpu = 0; cpu < n_cores; cpu++) {
    // 1. CONTROL REGION
    for (unsigned int domain = 0; domain < MAX_N_SECURE_DOMAIN; domain++)
      c_ctrl_reg[cpu][domain] = CIF_CTRL_R_RST_VAL;

    // 2. PRIORITY MASK
    c_priority_mask_reg[cpu] = PRIO_MASK_R_RST_VAL;

    // 3. BINARY POINT MASK
    c_binary_point_reg[cpu][SECURE]    =    BINARY_POINT_R_RST_VAL;
    c_binary_point_reg[cpu][NONSECURE] = NS_BINARY_POINT_R_RST_VAL;

    // 4. ACKNOWLEDGE : generated at each read by gethighestpendinginterruptregister()

    // 5. END OF INTERRUPT: WRITE ONLY
    // 6. "RUNNING" PRIORITY: calculated by update_running()
    c_running_int_priority[cpu] = RUN_PRIO_R_RST_VAL;
    c_running_int_domain[cpu]   = SECURE;
    // 7. HIGHST PENDING INTERRUPT : calculated by gethighestpendinginterruptregister()
    c_highest_priority[cpu]         = HIGHST_PEND_R_RST_VAL & PRIO_MASK_R_MASK;
    c_highest_priority_id[cpu]      = 1023;
    c_hpi_domain[cpu]               = SECURE; /* dummy */

    c_cpu_interface_edge[cpu]  = false; // a reset is a modification of signal's value

    // software model's internal stack of active interrupts
    c_active_int_stack_idx[cpu] = -1; /* dummy index */

    //for (unsigned int sub_offset = 0; sub_offset < CIF_IMPL_DEF_SIZE >> 2; sub_offset++)
    //  c_impl_def[cpu][sub_offset] = CIF_IMPL_DEF_RST_VAL;

    // CPU Interface Implementer Identification

    // state machines for peripheral and software interrupts.
    for (unsigned int int_id = 0; int_id < MAX_N_INT_LINES; int_id++)
      coreFSM[cpu][int_id] = INACTIVE;
    for (unsigned int j = 0; j < N_SOFTWARE_INT; j++) {
      soft_int_pending_requests[cpu][j] = 0;
      current_soft_int_pending_src[cpu][j] = 0xFF; /* dummy src cpu id */
      current_soft_int_active_src[cpu][j]  = 0xFF; /* dummy src cpu id */
    }
    // clear outputs
    // -- internal IRQ/FIQ signals
    signal_nFIQ[cpu] = 0;
    signal_nIRQ[cpu] = 0;
    signal_NSecure[cpu] = SECURE; /* dummy */
    // -- output signals
    irq_o[cpu] = false;
    fiq_o[cpu] = false;

    // a reset is a modification of signal's value
#ifdef MAX_CX_MODEL
    edge_irq_o[cpu] = false; // circumvent a bug occurring in Max** (Cottin 2007-01-11), to investigate later.
    edge_fiq_o[cpu] = false;
#else
    edge_irq_o[cpu] = true;
    edge_fiq_o[cpu] = true;
#endif
  }

  for (unsigned int int_id = 0; int_id < MAX_N_INT_LINES; int_id++)
    pseudo_pendingFSM[int_id] = false;
}


/* Access functions */
void GIC::cfgsdisable_i(MxU32 Value)
{
  cfgsdisable = (Value!=0); // see section 4.3.1 of PRD03-GENC-004392 8.1.
}

#ifndef NO_LEGACY_IRQ
// pass-thru to each core nIRQ/nFIQ
void
GIC::signal_port_legacy_irq_drive(unsigned int core, MxU32 value)
{
  if (signal_port_legacy_irq[core] == value) {// spurious call
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, "spurious call signal_port_legacy_irq_drive(core %u, value %u)", core, value);
#endif
    return;
  }
  signal_port_legacy_irq[core] = value;
  dispatch_legacy_irq(core);
}

void
GIC::dispatch_legacy_irq(unsigned int core)
{
  /** @todo confirm this Cortex-A9 specific behavior */
  if (!IRQ_IS_GIC_DRIVEN(core)) {
    signal_port_irq_drive(LEGACY_IRQ_ID, core, false);
    update_signal_nIRQ(core);
  } else {
    signal_port_irq_drive(LEGACY_IRQ_ID, core, signal_port_legacy_irq[core]);
  }
}

void
GIC::signal_port_legacy_fiq_drive(unsigned int core, MxU32 value)
{
  if (signal_port_legacy_fiq[core] == value) { // spurious call
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, "spurious call signal_port_legacy_fiq_drive(core %u, value %u)", core, value);
#endif
    return;
  }
  signal_port_legacy_fiq[core] = value;
  dispatch_legacy_fiq(core);
}

void
GIC::dispatch_legacy_fiq(unsigned int core)
{
  /** @todo confirm this Cortex-A9 specific behavior. */
   if (!FIQ_IS_GIC_DRIVEN(core)) {
    signal_port_irq_drive(LEGACY_FIQ_ID, core, false);
    update_signal_nFIQ(core);
   } else {
     signal_port_irq_drive(LEGACY_FIQ_ID, core, signal_port_legacy_fiq[core]);
   }
}
#endif


// interrupt input lines
void
GIC::signal_port_irq_drive(unsigned int int_id, unsigned int core, MxU32 value)
{
  /** 0. Sanity check */
  if (IS_SOFTWARE_INTERRUPT(int_id)) {
    gic_msg_fl(LOG_ERROR, "bad argument in signal_port_irq_drive()");
    return;
  }
  /** 1. check there is actually a transition */
  if (INT_SIG_VALUE(int_id, core) == (value ? 1 : 0)) {// spurious call
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, "GIC input irq %u line (on core %u if private int) has been"
            " ignored (value %u, but old_val %d)", int_id, core, value, INT_SIG_VALUE(int_id, core));
#endif
    return;
  }

#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "GIC input irq %u line (on core %u if private int) has been"
          " set to %u by peripheral", int_id, core, value);
#endif

  /** 2. remember new value of signal */
  INT_SIG_VALUE(int_id, core) = value ? 1:0;

  /** 3. Dispatch to distributor */
  if (IS_CTR_ENABLED(int_id, core)) // distributor enabled for the security domain of argument interrupt.
    dispatch_event_on_targets(int_id, core, EDGE);
}


/////////////////////
// bus_port_access

MxStatus
GIC::distributor_read8( MxU32 offset, MxU8  &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_read8()");
#endif

  /** 0. Sanity check: byte access is only allowed for priority and target register */
  if (NO_BYTE_ACCESS(offset)) {
#ifdef DEBUG_DBG_ACCESS
    gic_msg_fl(LOG_TRACE, " distributor_read8() returned MX_STATUS_NOACCESS (%d)", MX_STATUS_NOACCESS);
#endif
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit read access + byte extraction */
  MxU32 tmpval;
  MxStatus status = d_reg_map_access(offset & 0xFFFFFFFC, tmpval, 0 /*dummy*/, t_read,
                                     cpu_id, domain, t_nondebug);
  unsigned byte_off = offset % 4;
  data = GETFIELD(tmpval, byte_off * 8, 8);

  return status;
}
MxStatus
GIC::distributor_read16(MxU32 offset, MxU16 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE,
          "distributor_read16(%#x, data, cpu_id %d, domain %s)", offset, cpu_id, domain2str(domain));
#endif

  /** 0. Sanity check */
  if (!IS_16BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_read16(): offset %#x is not halfword-aligned", offset);
    return MX_STATUS_NOACCESS;
  }
  // byte access is only allowed for priority and target register
  if (NO_HLFWORD_ACCESS(offset)) {
#ifdef DEBUG_DBG_ACCESS
    gic_msg_fl(LOG_TRACE, " distributor_read16() returned MX_STATUS_NOACCESS (%d)", MX_STATUS_NOACCESS);
#endif
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access + halfword extraction */
  MxU32 tmpval;
  MxStatus status = d_reg_map_access(offset & 0xFFFFFFFC, tmpval, 0 /*dummy*/,
                                     t_read, cpu_id, domain, t_nondebug);
  unsigned halfword_off = (offset >> 1) % 2;
  data = GETFIELD(tmpval, halfword_off * 16, 16);

  return status;
}
MxStatus
GIC::distributor_read32(MxU32 offset, MxU32 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_read32()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_read32(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }
  if (offset >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_read32(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access */
  return d_reg_map_access(offset, data, 0 /*dummy*/, t_read, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::distributor_read64(MxU32 offset, MxU64 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_read64()");
#endif

  /** 0. Sanity Checks */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_read64(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 3 >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_read64(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  if (NO_DWORD_ACCESS(offset))
    return MX_STATUS_NOACCESS;

  /** 1. Combine two 32bit accesses */
  MxU32 data_low, data_high;
  MxStatus stat0 = d_reg_map_access(offset    , data_low,  0 /*dummy*/, t_read, cpu_id, domain, t_nondebug);
  MxStatus stat1 = d_reg_map_access(offset + 4, data_high, 0 /*dummy*/, t_read, cpu_id, domain, t_nondebug);

  data = ((MxU64)data_high << 32) | data_low;// little endian !

  return max_error(stat0, stat1);
}

MxStatus
GIC::distributor_write8( MxU32 offset, MxU8  data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_write8(%#x, data, cpu_id %d, domain %s)", offset, cpu_id, domain2str(domain));
#endif

  /** 0. Sanity Check: byte access is only allowed for priority and target register */
  if (NO_BYTE_ACCESS(offset))
    return MX_STATUS_NOACCESS;

  /** 1. 32bit access with strobes */
  unsigned byte_offset = offset % 4;
  MxU32 tmpdata = MxU32(data) << byte_offset * 8;
  return d_reg_map_access(offset & 0xFFFFFFFC, tmpdata, (1 << byte_offset),
                          t_write, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::distributor_write16(MxU32 offset, MxU16 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_write16(%#x, data, cpu_id %d, domain %s)", offset, cpu_id, domain2str(domain));
#endif

  /** 0. Sanity Checks */
  if (!IS_16BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_write16(): offset %#x is not halfword-aligned", offset);
    return MX_STATUS_NOACCESS;
  }
  // byte access is only allowed for priority and target register
  if (NO_HLFWORD_ACCESS(offset))
    return MX_STATUS_NOACCESS;

  /** 1. 32bit access with strobes */
  unsigned halfword_off = (offset >> 1) % 2;
  MxU32 tmpdata = MxU32(data) << halfword_off * 16;
  return d_reg_map_access(offset & 0xFFFFFFFC, tmpdata, (3 << halfword_off * 2),
                          t_read, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::distributor_write32(MxU32 offset, MxU32 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_write32()");
#endif

  /** 0. Sanity Check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
               "GIC::distributor_write32(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_write32(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access : Cool ! */
  return d_reg_map_access(offset, data, 0xF, t_write, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::distributor_write64(MxU32 offset, MxU64 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_write64()");
#endif

  /** 0. Sanity Check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_write64(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 3 >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_write64(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  if (NO_DWORD_ACCESS(offset))
    return MX_STATUS_NOACCESS;

  /** 1. Combine two 32bit accesses */
  MxU32 data_low  = data & 0xFFFFFFFF;                    // little endian !
  MxU32 data_high = (data >> 32) & 0xFFFFFFFF;
  MxStatus stat0 = d_reg_map_access(offset    , data_low , 0xF, t_write, cpu_id, domain, t_nondebug);
  MxStatus stat1 = d_reg_map_access(offset + 4, data_high, 0xF, t_write, cpu_id, domain, t_nondebug);

  return max_error(stat0, stat1);
}

/** Up to 64bit accesses with strobes*/
MxStatus
GIC::distributor_write(MxU32 offset, MxU64 data, unsigned char strobes, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_write()");
#endif

  /** 0. Sanity checks */
  if (!IS_64BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_write(): offset %#x is not 64bit aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 7 >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_write(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  MxStatus status0 = MX_STATUS_OK;
  MxStatus status1 = MX_STATUS_OK;
  MxU32 tmpdata;
  unsigned char tmpstrobes;

  /** 1. LSW */
  tmpstrobes = (unsigned char)(strobes & 0xF);
  tmpdata    = (MxU32)(data);
  if (tmpstrobes != 0)
    status0 = d_reg_map_access(offset, tmpdata, tmpstrobes, t_write, cpu_id, domain, t_nondebug);

  /** 2. MSW */
  tmpstrobes = (unsigned char)(strobes >> 4 & 0xF);
  tmpdata    = (MxU32)(data >> 32);
  if (tmpstrobes != 0)
    status1 = d_reg_map_access(offset + 4, tmpdata, tmpstrobes, t_write, cpu_id, domain, t_nondebug);

  /** 3. Merge error status of accesses. */
  return max_error(status0, status1);
}


/////////////////////////
// Debug accesses
MxStatus
GIC::distributor_readDbg8( MxU32 offset, MxU8  &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_readDbg8(offset =%#x, data, cpu_id =%u, domain = %s)",  offset, cpu_id, domain2str(domain));
#endif

  /** 0. Sanity check */
  if (offset >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_readDbg8(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit read access + byte extraction */
  MxU32 tmpval;
  MxStatus status = d_reg_map_access(offset & 0xFFFFFFFC, tmpval, 0 /* dummy */,
                                     t_read, cpu_id, domain, t_debug);

  unsigned byte_off = offset % 4;                    // little endian !
  data = GETFIELD(tmpval, byte_off * 8, 8);

#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_readDbg8() : data = %#x and tmpval = %#x",data, tmpval);
#endif
  return status;
}
MxStatus
GIC::distributor_readDbg16(MxU32 offset, MxU16 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_readDbg16()");
#endif

  /** 0. Sanity check */
  if (!IS_16BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_readDbg16(): offset %#x is not halfword-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_readDbg8(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit read access + halfword extraction */
  MxU32 tmpval;
  MxStatus status = d_reg_map_access(offset & 0xFFFFFFFC, tmpval, 0/* dummy */, t_read,
                                     cpu_id, domain, t_debug);
  unsigned byte_off = offset % 4;                    // little endian !
  data = GETFIELD(tmpval, byte_off * 8, 16);

  return status;
}
MxStatus
GIC::distributor_readDbg32(MxU32 offset, MxU32 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_readDbg32()");
#endif

  /** 0. Sanity check */
  if (offset & 3) {     /* addr must be word aligned */
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_readDbg32(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_readDbg32(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit read access */
  return d_reg_map_access(offset, data, 0/* dummy */, t_read, cpu_id, domain, t_debug);
}
MxStatus
GIC::distributor_readDbg64(MxU32 offset, MxU64 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_readDbg64()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_readDbg64(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 7 >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_readDbg64(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. Combine two 32bit read accesses */
  MxU32 data_low, data_high;
  MxStatus stat0 = d_reg_map_access(offset    , data_low,  0/* dummy */, t_read, cpu_id, domain, t_debug);
  MxStatus stat1 = d_reg_map_access(offset + 4, data_high, 0/* dummy */, t_read, cpu_id, domain, t_debug);

  data = ((MxU64)data_high << 32) | data_low;// little endian !

  return max_error(stat0, stat1);
}

MxStatus
GIC::distributor_writeDbg8( MxU32 offset, MxU8  data, unsigned int cpu_id, int domain)
{
#if defined(DEBUG_DBG_ACCESS)
  gic_msg_fl(LOG_TRACE, " distributor_writeDbg8()");
#endif

  /** 0. Sanity check */
  if (offset >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_writeDbg8(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit write access with strobes */
  unsigned byte_offset = offset % 4;
  MxU32 tmpdata = MxU32(data) << byte_offset * 8;
  return d_reg_map_access(offset & 0xFFFFFFFC, tmpdata, (1 << byte_offset),
                          t_write, cpu_id, domain, t_debug);
}
MxStatus
GIC::distributor_writeDbg16(MxU32 offset, MxU16 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_writeDbg16()");
#endif

  /** 0. Sanity check */
  if (!IS_16BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_writeDbg16(): offset %#x is not halfword-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_writeDbg16(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit read access with strobes */
  unsigned halfword_off = (offset >> 1) % 2;
  MxU32 tmpdata = MxU32(data) << halfword_off * 16;
  return d_reg_map_access(offset & 0xFFFFFFFC, tmpdata, (3 << halfword_off * 2),
                          t_write, cpu_id, domain, t_debug);
}
MxStatus
GIC::distributor_writeDbg32(MxU32 offset, MxU32 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_writeDbg32()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_writeDbg32(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_writeDbg32(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit read access */
  return d_reg_map_access(offset, data, 0xF, t_write, cpu_id, domain, t_debug);
}
MxStatus
GIC::distributor_writeDbg64(MxU32 offset, MxU64 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " distributor_writeDbg64()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::distributor_writeDbg64(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 7 >= DISTRIBUTOR_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::distributor_writeDbg64(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. Combine two 32bit acceses */
  MxU32 data_low  = data & 0xFFFFFFFF;                    // little endian !
  MxU32 data_high = (data >> 32) & 0xFFFFFFFF;
  MxStatus stat0 = d_reg_map_access(offset    , data_low,  0xf, t_write, cpu_id, domain, t_debug);
  MxStatus stat1 = d_reg_map_access(offset + 4, data_high, 0xf, t_write, cpu_id, domain, t_debug);

  return max_error(stat0, stat1);
}

/////////////////////
// bus_port_access for CPU interfaces
MxStatus
GIC::cpuif_read8( MxU32 offset, MxU8  &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_read8()");
#endif

  /** 0. Sanity check */
  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_read8(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access + byte extraction */
  MxU32 tmpval;
  MxStatus status = c_reg_map_access(offset & 0xFFFFFFFC, tmpval, 0 /* dummy */, t_read,
                                     cpu_id, domain, t_nondebug);
  unsigned byte_off = offset % 4;                    // little endian !
  data = GETFIELD(tmpval, byte_off * 8, 8);

  return status;
}
MxStatus
GIC::cpuif_read16(MxU32 offset, MxU16 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_read16()");
#endif

  /** 0. Sanity check */
  if (!IS_16BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_read16(): offset %#x is not halfword-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_read16(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }
  /** 1. 32bit access + halfword extraction */
  MxU32 tmpval;
  MxStatus status = c_reg_map_access(offset & 0xFFFFFFFC, tmpval, 0 /* dummy */, t_read,
                                     cpu_id, domain, t_nondebug);
  unsigned byte_off = offset % 4;                    // little endian !
  data = GETFIELD(tmpval, byte_off * 8, 16);

  return status;
}
MxStatus
GIC::cpuif_read32(MxU32 offset, MxU32 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_read32()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_read32(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_read32(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access */
  return c_reg_map_access(offset, data, 0 /* dummy */, t_read, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::cpuif_read64(MxU32 offset, MxU64 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_read64()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_read64(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 3 >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_read64(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. Combine two 32bit acceses */
  MxU32 data_low, data_high;
  MxStatus stat0 = c_reg_map_access(offset    , data_low,  0 /*dummy*/, t_read, cpu_id, domain, t_nondebug);
  MxStatus stat1 = c_reg_map_access(offset + 4, data_high, 0 /*dummy*/, t_read, cpu_id, domain, t_nondebug);

  data = ((MxU64)data_high << 32) | data_low;// little endian !

  return max_error(stat0, stat1);
}

MxStatus
GIC::cpuif_write8( MxU32 offset, MxU8  data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_write8()");
#endif

  /** 0. Sanity check */
  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_write8(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit read access + byte extraction */
  unsigned byte_offset = offset % 4;
  MxU32 tmpdata = MxU32(data) << byte_offset * 8;
  return c_reg_map_access(offset & 0xFFFFFFFC, tmpdata, (1 << byte_offset),
                          t_write, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::cpuif_write16(MxU32 offset, MxU16 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_write16()");
#endif

  /** 0. Sanity check */
  if (!IS_16BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_write16(): offset %#x is not halfword-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_write16(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access + halfword extraction */
  unsigned halfword_off = (offset >> 1) % 2;
  MxU32 tmpdata = MxU32(data) << halfword_off * 16;
  return c_reg_map_access(offset & 0xFFFFFFFC, tmpdata, (3 << halfword_off * 2),
                          t_read, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::cpuif_write32(MxU32 offset, MxU32 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_write32()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_write32(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_write32(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  return c_reg_map_access(offset, data, 0xf, t_write, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::cpuif_write64(MxU32 offset, MxU64 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_write64()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_write64(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 3 >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_write64(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. Combine two 32bit accesses */
  MxU32 data_low  = data & 0xFFFFFFFF;         // little endian !
  MxU32 data_high = (data >> 32) & 0xFFFFFFFF;
  MxStatus stat0 = c_reg_map_access(offset    , data_low,  0xF, t_write, cpu_id, domain, t_nondebug);
  MxStatus stat1 = c_reg_map_access(offset + 4, data_high, 0xF, t_write, cpu_id, domain, t_nondebug);

  return max_error(stat0, stat1);
}

/** 64bit write with strobes */
MxStatus
GIC::cpuif_write(MxU32 offset, MxU64 data, unsigned char strobes, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_write()");
#endif

  /** 0. Sanity checks */
  if (!IS_64BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_write(): offset %#x is not 64bit aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 7 >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_write(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  MxStatus status0 = MX_STATUS_OK;
  MxStatus status1 = MX_STATUS_OK;
  MxU32 tmpdata;
  unsigned char tmpstrobes;

  /** 1. LSW */
  tmpstrobes = (unsigned char)(strobes & 0xF);
  tmpdata    = (MxU32)(data);
  if (tmpstrobes != 0)
    status0 = c_reg_map_access(offset, tmpdata, tmpstrobes, t_write, cpu_id, domain, t_nondebug);

  /** 2. MSW */
  tmpstrobes = (unsigned char)(strobes >> 4 & 0xF);
  tmpdata    = (MxU32)(data >> 32);
  if (tmpstrobes != 0)
    status1 = c_reg_map_access(offset + 4, tmpdata, tmpstrobes, t_write, cpu_id, domain, t_nondebug);

  /** 3. Merge error status of accesses. */
  return max_error(status0, status1);
}


/////////////////////////
// Debug accesses
MxStatus
GIC::cpuif_readDbg8( MxU32 offset, MxU8  &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_readDbg8()");
#endif

  /** 0. Sanity check */
  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_readDbg8(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access + byte extraction */
  MxU32 tmpval;
  MxStatus status = c_reg_map_access(offset & 0xFFFFFFFC, tmpval, 0 /* dummy */, t_read,
                                     cpu_id, domain, t_debug);
  unsigned byte_off = offset % 4;                    // little endian !
  data = GETFIELD(tmpval, byte_off * 8, 8);

  return status;
}
MxStatus
GIC::cpuif_readDbg16(MxU32 offset, MxU16 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_readDbg16()");
#endif

  /** 0. Sanity check */
  if (!IS_16BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_readDbg16(): offset %#x is not halfword-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_readDbg16(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access + halfword extraction */
  MxU32 tmpval;
  MxStatus status = c_reg_map_access(offset & 0xFFFFFFFC, tmpval, 0 /* dummy */, t_read,
                                     cpu_id, domain, t_debug);
  unsigned byte_off = offset % 4;                    // little endian !
  data = GETFIELD(tmpval, byte_off * 8, 16);

  return status;
}
MxStatus
GIC::cpuif_readDbg32(MxU32 offset, MxU32 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_readDbg32()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_readDbg32(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_readDbg32(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access */
  return c_reg_map_access(offset, data, 0 /* dummy */, t_read, cpu_id, domain, t_debug);
}
MxStatus
GIC::cpuif_readDbg64(MxU32 offset, MxU64 &data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_readDbg64()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_readDbg64(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 7 >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_readDbg64(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. Combine two 32bit acceses */
  MxU32 data_low, data_high;
  MxStatus stat0 = c_reg_map_access(offset    , data_low,  0 /*dummy*/, t_read, cpu_id, domain, t_debug);
  MxStatus stat1 = c_reg_map_access(offset + 4, data_high, 0 /*dummy*/, t_read, cpu_id, domain, t_debug);

  data = ((MxU64)data_high << 32) | data_low;// little endian !

  return max_error(stat0, stat1);
}

MxStatus
GIC::cpuif_writeDbg8( MxU32 offset, MxU8  data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_writeDbg8()");
#endif

  /** 0. Sanity check */
  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_writeDbg8(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit read access + byte extraction */
  unsigned byte_offset = offset % 4;
  MxU32 tmpdata = MxU32(data) << byte_offset * 8;
  return c_reg_map_access(offset & 0xFFFFFFFC, tmpdata, (1 << byte_offset),
                          t_write, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::cpuif_writeDbg16(MxU32 offset, MxU16 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_writeDbg16()");
#endif

  /** 0. Sanity check */
  if (!IS_16BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_writeDbg16(): offset %#x is not halfword-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_writeDbg16(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. 32bit access + halfword extraction */
  unsigned halfword_off = (offset >> 1) % 2;
  MxU32 tmpdata = MxU32(data) << halfword_off * 16;
  return c_reg_map_access(offset & 0xFFFFFFFC, tmpdata, (3 << halfword_off * 2),
                          t_read, cpu_id, domain, t_nondebug);
}
MxStatus
GIC::cpuif_writeDbg32(MxU32 offset, MxU32 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_writeDbg32()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_writeDbg32(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_writeDbg32(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  return c_reg_map_access(offset, data, 0xf, t_write, cpu_id, domain, t_debug);
}
MxStatus
GIC::cpuif_writeDbg64(MxU32 offset, MxU64 data, unsigned int cpu_id, int domain)
{
#ifdef DEBUG_DBG_ACCESS
  gic_msg_fl(LOG_TRACE, " cpuif_writeDbg64()");
#endif

  /** 0. Sanity check */
  if (!IS_32BIT_ALIGNED(offset)) {
    gic_msg_fl(LOG_ERROR,
            "GIC::cpuif_writeDbg64(): offset %#x is not word-aligned", offset);
    return MX_STATUS_NOACCESS;
  }

  if (offset + 7 >= CPU_INTERFACE_MAP_SIZE) {
    gic_msg_fl(LOG_ERROR, "GIC::cpuif_writeDbg64(): offset %#x is outside address range", offset);
    return MX_STATUS_NOACCESS;
  }

  /** 1. Combine two 32bit accesses */
  MxU32 data_low  = data & 0xFFFFFFFF;         // little endian !
  MxU32 data_high = (data >> 32) & 0xFFFFFFFF;
  MxStatus stat0 = c_reg_map_access(offset    , data_low,  0xF, t_write, cpu_id, domain, t_debug);
  MxStatus stat1 = c_reg_map_access(offset + 4, data_high, 0xF, t_write, cpu_id, domain, t_debug);

  return max_error(stat0, stat1);
}



// OUTPUT TO CPU nIRQ/nFIQ lines
/** CPU's IRQ mechanism.
    @param core the ID of the CPU whose line is to update */
void
GIC::update_signal_nIRQ(unsigned int core)
{
#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "update_signal_nIRQ(core = %u)", core);
#endif

  if ((signal_nIRQ[core] && IS_IF_ENABLED(core, signal_NSecure[core]))
#ifndef NO_LEGACY_IRQ
      || (signal_port_legacy_irq[core] && !IRQ_IS_GIC_DRIVEN(core))   // IRQ pass thru
#endif
      ) {
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, " -> update_irq_o(core, true)", core);
#endif
    update_irq_o(core, true);
  } else {
#ifdef GIC_TRACE
    if (!IS_IF_ENABLED(core, signal_NSecure[core]))
      gic_msg_fl(LOG_TRACE, " -> update_irq_o(core = %d, false) because !IS_IF_ENABLED(core, signal_NSecure[core] = %d)", core, signal_NSecure[core]);
    if (!signal_nIRQ[core])
      gic_msg_fl(LOG_TRACE, " -> update_irq_o(core = %d, false) because signal_nIRQ[core] = false (not asserted)", core);
#endif
    update_irq_o(core, false);
  }
}

/** CPU's FIQ mechanism.
    @param core the ID of the CPU whose line is to update */
void
GIC::update_signal_nFIQ(unsigned int core)
{
#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "update_signal_nFIQ(core = %u)", core);
#endif

  if ((signal_nFIQ[core] && IS_IF_ENABLED(core, signal_NSecure[core]))
#ifndef NO_LEGACY_FIQ
      || ((signal_port_legacy_fiq[core] && !FIQ_IS_GIC_DRIVEN(core)))   // FIQ pass thru
#endif
      ) {
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, " -> update_fiq_o(core, true)", core);
    if (signal_nFIQ[core] && IS_IF_ENABLED(core, signal_NSecure[core]))
      gic_msg_fl(LOG_TRACE, "  because signal_nFIQ[%d] is true (and interface is enabled)", core);
    else
      gic_msg_fl(LOG_TRACE, "signal_port_legacy_fiq[] is true and FIQ is pass-thru");
#endif

    update_fiq_o(core, true);
  } else {
#ifdef GIC_TRACE
    if (!IS_IF_ENABLED(core, signal_NSecure[core]))
      gic_msg_fl(LOG_TRACE, " -> update_fiq_o(core = %d, false) because !IS_IF_ENABLED(core, signal_NSecure[core] = %d)", core, signal_NSecure[core]);
    if (!signal_nFIQ[core])
      gic_msg_fl(LOG_TRACE, " -> update_fiq_o(core = %d, false) because signal_nFIQ[core] = false (not asserted)", core);
#endif
    update_fiq_o(core, false);
  }
}

/** detect changes in the (output) IRQ */
void
GIC::update_irq_o(unsigned int core, bool val)
{
  // filter spurious calls
  if (irq_o[core] == val) {
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, " irq_o[core %u] == %d (spurious call to update_irq_o())", core, (int)val);
#endif
    return;
  }

  // set the edge flag
  edge_irq_o[core] = true;
  irq_o[core] = val;

#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, " irq_o[core %u] = %d", core, (int)val);
#endif
}

/** detect changes in the (output) FIQ */
void
GIC::update_fiq_o(unsigned int core, bool val)
{
  // filter spurious calls
  if (fiq_o[core] == val) {
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, " fiq_o[core %u] == %d (spurious call to update_fiq_o())", core, (int)val);
#endif
    return;
  }
  // set the edge flag
  edge_fiq_o[core] = true;
  fiq_o[core] = val;
#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, " fiq_o[core %u] = %d", core, (int)val);
#endif
}

#ifdef GIC_TRACE
static const char* fsmState2str(fsmState state)
{
  switch(state) {
  case INACTIVE         : return "INACTIVE         "; break;
  case PENDING          : return "PENDING          "; break;
  case PENDING_LVL      : return "PENDING_LVL      "; break;
  case ACTIVE           : return "ACTIVE           "; break;
  case ACTIVEPENDING    : return "ACTIVEPENDING    "; break;
  case ACTIVEPENDING_LVL: return "ACTIVEPENDING_LVL"; break;
  default:
    return "(unknown state)";
  }
}
#endif
static const char* fsmEvent2str(fsmEvent event)
{
  switch(event) {
  case WRITE_SWI:
    return "WRITE_SWI (int id is written in SWI reg)";
    break;
  case VALID_TRG:
    return "VALID_TRG (CPU is target of current int)";
    break;
  case INVALID_TRG:
    return "INVALID_TRG (CPU is no more target of current int)";
    break;
  case EDGE:
    return "EDGE (transition on interrupt input signal)";
    break;
  case WRITE_P:
    return "WRITE_P (flag in Pending reg is 1)";
    break;
  case WRITE_CP:
    return "WRITE_CP (flag in Pending reg is 0)";
    break;
  case READ_IA:
    return "READ_IA (interrupt ID has been read in the ACKNOWLEDGE reg)";
    break;
  case WRITE_EOI:
    return "WRITE_EOI (int id has been written in EOI reg)";
    break;
  case NOW_ACTIV:
    return "NOW_ACTIV (int became active on another CPU)";
    break;
  case NOT_ACTIV:
    return "NOT_ACTIV (int finished on another CPU)";
    break;
  default:
    return "(unknown event)";
  }
}

static const char *
rw_t_2str(rw_t e)
{
  switch(e) {
  case t_read:
    return "read";
    break;
  case t_write:
    return "write";
    break;
  default:
    return "(unknown access)";
  }
}

/** access to memory mapped registers of CPU interface. From
    base address, the following registers are mapped:
 - the CONTROL REGISTER (which is implemented by GIC::c_ctrl_reg[])
 - Priority Mask
 - Binary Point
 - Int Ack
 - EOI
 - Running Priority
 - HPI
 - Aliased N-S Binary Point.
 - Implementation defined zone
 - CPU Interface Implementer ID reg
 @param offset the address of the register
 @param value a reference to an integer in which a 32bit value will be
              placed (read) or which contains the source value (write).
 @param type     either Read or Write
 @param cpu_id   the CPU which is performed the access
 @param domain   NS-prot
 @param side_effect t_debug for debug accesses (= no side effect).
*/
MxStatus
GIC::c_reg_map_access(MxU32 offset, MxU32 & value, unsigned char strobes, rw_t type,
                      unsigned int cpu_id, int domain, dbg_t side_effect)
{
  MxU32 writevalue = value;
  MxU32 old_value = 0;

  /** 0. Sanity check */
#ifndef NOCHECK
  if (!IS_VALID_DOMAIN(domain)) {
    gic_msg_fl(LOG_ERROR, "bad domain arg. in reg_map_access()");
    return MX_STATUS_ERROR;
  }
  if (!IS_VALID_CPUID(cpu_id)) {
    gic_msg_fl(LOG_ERROR, "bad cup_id arg. in reg_map_access()");
    return MX_STATUS_ERROR;
  }
#endif

  if (type == t_write && ((strobes & 0xf) == 0)) {
#ifndef NOCHECK
    gic_msg_fl(LOG_WARNING, "empty strobes in "
               "GIC::c_reg_map_access(offset = %#x, value = %#x, strobes = %#x, type = %s, "
               "cpu_id = %u, domain = %s, side_effect = %s)",
               offset, value, strobes, rw_t_2str(type), cpu_id, domain2str(domain),
               side_effect == t_debug ? "t_debug" : "t_nondebug");
#endif
    return MX_STATUS_OK;
  }


  /** 1. Build mask from strobes (write access only) */
  MxU32 strb_mask = (type == t_write) ? byte_strobe2mask(strobes) : 0 /* dummy */;

#ifdef GIC_TRACE
#define TRACE_CIF_ACCESS(regname)                                   \
    gic_msg_fl(LOG_TRACE, "%s %s to " regname " register of cpu interface %u", \
               domain2str(domain), rw_t_2str(type), cpu_id);
#define TRACE_WRITE_VALUE                                      \
    gic_msg_fl(LOG_TRACE, "write value is %#08x", writevalue);

#define TRACE_READ_VALUE                                 \
    gic_msg_fl(LOG_TRACE, "read value is %#08x", value);

#define TRACE_ACCESS_VALUE                                       \
    if (type == t_write)                                         \
      gic_msg_fl(LOG_TRACE, "write value is %#08x", writevalue);\
    else                                                        \
      gic_msg_fl(LOG_TRACE, "read value is %#08x", value);
#else
#define TRACE_CIF_ACCESS(x)
#define TRACE_WRITE_VALUE
#define TRACE_READ_VALUE
#define TRACE_ACCESS_VALUE
#endif

  // regular regs
  switch (offset) {
    case CIF_CTRL_R_OFF:
      // ------------ 1. CONTROL register (secure-banked)------------
      TRACE_CIF_ACCESS("CONTROL");

      // mask SBZ bitfields and managed aliasing of the Enable bit
      // (see PR231-GENC-006924 5.2 section 3.8.2.1)
      if (type == t_read) {
        value = c_ctrl_reg[cpu_id][domain] & (!trustzone_enabled || IS_UNSECURE_DOMAIN(domain) ? CIF_CTRL_R_NS_MASK :
                                              CIF_CTRL_R_S_MASK);
        TRACE_READ_VALUE;
        return MX_STATUS_OK;
      }
      // ----- For write accesses ----- //
      writevalue &= (!trustzone_enabled || IS_UNSECURE_DOMAIN(domain) ? CIF_CTRL_R_NS_MASK:CIF_CTRL_R_S_MASK);
      TRACE_WRITE_VALUE;
      old_value = c_ctrl_reg[cpu_id][domain];

      // If accessing secure ctl reg while CFGSDISABLE is on, only EnableNs is modifiable.
      if (cfgsdisable && IS_SECURE_DOMAIN(domain))
        writevalue = NEWVAL_WITH_MASK(c_ctrl_reg[cpu_id][domain], 1 << 1, writevalue);

      writevalue = NEWVAL_WITH_MASK(c_ctrl_reg[cpu_id][domain], strb_mask, writevalue);
      TRACE_WRITE_VALUE;
      c_ctrl_reg[cpu_id][domain] = writevalue;

      // The NS-Enable bit is aliased
      if (IS_UNSECURE_DOMAIN(domain)) {
        // Reflect the write of NonSecure CRTL reg.
        if (BIT(writevalue, 0)) // If Enable bit of nonsecure CRTL reg is set
          SETBIT(c_ctrl_reg[cpu_id][SECURE], 1);    // set the EnableNS bit
        else                  // If Enable bit of nonsecure CRTL reg is cleared
          CLRBIT(c_ctrl_reg[cpu_id][SECURE], 1);    // clear the EnableNS bit
      } else {
        // Reflect the write of the Secure CRTL reg.
        if (BIT(writevalue, 1)) // EnableNS bit of Secure CRTL reg is set
          SETBIT(c_ctrl_reg[cpu_id][NONSECURE], 0);  //   set the Enable bit
        else
          CLRBIT(c_ctrl_reg[cpu_id][NONSECURE], 0);  // clear the Enable bit
      }

      // SIDE-EFFECT
      // enable or disable the output to CPU nIRQ/nFIQ
      if (IS_UNSECURE_DOMAIN(domain)) {
        if ((old_value ^ writevalue) & 0x1) {
          update_signal_nIRQ(cpu_id); // IRQ is the only possibility for non secure interrupts
        }
      } else { //  ---- for the SECURE BP register -----
        // If SBPR bit (4th bit) changed, it may be the case that a
        // HPI which had been masked becomes eligible (et vis versa)
        // If FIQEn (3rd bit) has changed, we should switch the
        // interrupt lines (nIRQ <-> nFIQ)
        if ((old_value ^ writevalue) & ((1 << 4) | (1 << 3))) {
          c_cpu_interface_edge[cpu_id] = true;
          update_cpu_interface(cpu_id);
        } else if ((old_value ^ writevalue) & 0x3) {
          // Enable has changed, update only final output stage.
          update_signal_nFIQ(cpu_id);
          update_signal_nIRQ(cpu_id);
        }
      }
      break;
    case PRIO_MASK_R_OFF:
      //----------------- 2. PRIORITY MASK -------------------
      TRACE_CIF_ACCESS("PRIORITY MASK");

      // Nonsecure accesses undergo a translation
      // (see PR231-GENC-006924 5.2 section 3.7.3.3, table 3-1 page 10)
      if (IS_UNSECURE_DOMAIN(domain)) {
        // if current priority belongs to the secure reserved range [0-127]
        // then nonsecure accesses silently fail.
        if (IS_IN_SECURE_PRIORITY_RANGE(c_priority_mask_reg[cpu_id])) {
          if (type == t_read)
            value = 0;    // reads return 0
#ifdef GIC_TRACE
          gic_msg_fl(LOG_TRACE,
                  "NONSECURE access to a secure PRIORITY MASK (%#x) silently failed",
                  c_priority_mask_reg[cpu_id]);
#endif
          return MX_STATUS_OK;         // and writes are ignored
        }
        // Priority translation
        if (type == t_write) {
          writevalue = (writevalue >> 1 | 0x80) & PRIO_MASK_R_MASK;
          TRACE_WRITE_VALUE;
          // strobes
          old_value = c_priority_mask_reg[cpu_id];
          writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
          TRACE_WRITE_VALUE;
          c_priority_mask_reg[cpu_id] = writevalue;
        } else {
          value = (c_priority_mask_reg[cpu_id] << 1 & 0xFE) & PRIO_MASK_R_MASK;
          TRACE_READ_VALUE;
        }
      } else { // for secure accesses
        // NO Priority translation
        if (type == t_write) {
          writevalue = writevalue & PRIO_MASK_R_MASK;
          TRACE_WRITE_VALUE;
          old_value = c_priority_mask_reg[cpu_id];
          writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
          TRACE_WRITE_VALUE;
          c_priority_mask_reg[cpu_id] = writevalue;
        } else {
          value = c_priority_mask_reg[cpu_id] & PRIO_MASK_R_MASK;
          TRACE_READ_VALUE;
        }
      }
      if (type == t_write) {
        //-- for write accesses ---
        // SIDE-EFFECT:
        // Release the pending interrupt
        if (old_value != c_priority_mask_reg[cpu_id]) {
          c_cpu_interface_edge[cpu_id] = true;
          update_cpu_interface(cpu_id);
        }
        /** @todo avoid spurious calls */
      }
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, " PRIORITY MASK c_priority_mask_reg[%u] = %#x (%u)",
              cpu_id, c_priority_mask_reg[cpu_id], c_priority_mask_reg[cpu_id]);
#endif

      break;
    case BINARY_POINT_R_OFF:
      // ----------------- 3. BINARY POINT (Banked S/NS) ---------
      TRACE_CIF_ACCESS("BINARY POINT");

      // according PR231-GENC-006924 5.8 section 4.2.3 p29, the BP
      // register view depends on the SECURE control register's SBPR
      // bit (bit 4).
      if (IS_IF_SPBPR(cpu_id) && IS_UNSECURE_DOMAIN(domain)) {
        // For unsecure access when SPBPR bit is set, get secure BP register's
        // value + 1, perform saturation at 7 and ignore writes.
        if (type == t_read) {
          value = c_binary_point_reg[cpu_id][SECURE] + 1;
          TRACE_READ_VALUE;
          if (value >= 7)
            value = 7;
        }
      } else {
        if (type == t_read) {
          value = c_binary_point_reg[cpu_id][domain];
          TRACE_READ_VALUE;
        } else {
          //-- for write accesses ---
          // Mask SBZ bitfields
          writevalue &= BINARY_POINT_R_MASK;
          TRACE_WRITE_VALUE;
          // Minimum value (IMPLI DEF) (see PR231-GENC-006924 5.2 section 3.8.2.3)
          unsigned int min_val = BINARY_POINT_R_MIN + (IS_UNSECURE_DOMAIN(domain) ? 1 : 0);
          writevalue = (writevalue < min_val) ? min_val : writevalue;
          TRACE_WRITE_VALUE;
          old_value = c_binary_point_reg[cpu_id][domain];
          // strobes
          writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
          TRACE_WRITE_VALUE;
          c_binary_point_reg[cpu_id][domain] = writevalue;

          // SIDE-EFFECT:
          // Reassess pre-emption by the current HPI (if any).
          if (old_value != writevalue) {
            c_cpu_interface_edge[cpu_id] = true;
            update_cpu_interface(cpu_id);
          }
        }
      }
      break;
    case NS_BINARY_POINT_R_OFF:
      // ------------- 4.  ALIASED NONSECURE BINARY POINT---------
      TRACE_CIF_ACCESS("ALIASED NONSECURE BINARY POINT");

      // Only for SECURE accesses in Trustzone enabled archi.
      if (!trustzone_enabled || IS_UNSECURE_DOMAIN(domain)) {
        if (type == t_read) {
          value = 0;   // Reads return 0
          TRACE_READ_VALUE;
        }
        return MX_STATUS_OK;        // Writes are silently ignored
      }

      if (type == t_read) {
        value = c_binary_point_reg[cpu_id][NONSECURE];
        TRACE_READ_VALUE;
      } else {
        TRACE_WRITE_VALUE;
        //-- for write accesses ---
        // Mask SBZ bitfields
        writevalue &= BINARY_POINT_R_MASK;
        TRACE_WRITE_VALUE;
        // Minimum value (IMPLI DEF) (see PR231-GENC-006924 5.2 section 3.8.2.3)
        writevalue = (writevalue < (BINARY_POINT_R_MIN + 1)) ? (BINARY_POINT_R_MIN + 1) : writevalue;
        TRACE_WRITE_VALUE;
        old_value = c_binary_point_reg[cpu_id][NONSECURE];
        // strobes
        writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
        TRACE_WRITE_VALUE;
        c_binary_point_reg[cpu_id][NONSECURE] = writevalue;

        // SIDE-EFFECT:
        // Reassess pre-emption by the current HPI (if any).
        if (old_value != writevalue) {
          c_cpu_interface_edge[cpu_id] = true;
          update_cpu_interface(cpu_id);
        }
      }
      break;
    case ACK_R_OFF:
      // ------------ 5. INTERRUPT ACKNOWLEDGE register ----------------
      TRACE_CIF_ACCESS("INTERRUPT ACKNOWLEDGE");

      // Read only
      if (type == t_write) {
        TRACE_WRITE_VALUE;
        return MX_STATUS_OK;
      }
      // 1. If no HPI is currently signalled by CPU interface, return
      // the spurious interrupt number.
      if ((signal_nIRQ[cpu_id] || signal_nFIQ[cpu_id]) &&
          IS_IF_ENABLED(cpu_id, signal_NSecure[cpu_id]) ) {
        // Register has the same format as the HIGHEST PENDING INTERRUPT register
        value = gethighestpendinginterruptregister(cpu_id, domain);
        TRACE_READ_VALUE;
      } else {
        value = 1023; // HPI (if any) is not signalled by CPU interface.
        TRACE_READ_VALUE;
      }

      if (IS_SPURIOUS_INTERRUPT(value & 0x3FF))
        return MX_STATUS_OK;

      // SIDE-EFFECT:
      // acknowledge the interrupt when a non-spurious interrupt has been read
      // from the INTERRUPT ACKNOWLEDGE register.
      if (side_effect != t_debug)
        readIntAck(cpu_id);

      break;
    case EOI_R_OFF:
      // --------------- 6. EOI -------------------
      {
        TRACE_CIF_ACCESS("EOI");
      // Write only
      if (type == t_read) {
        value = 0;
        TRACE_READ_VALUE;
        return MX_STATUS_OK;
      }
      TRACE_WRITE_VALUE;

      // sanity check: an access with sparse strobes is likely to be meaning less.
      if ((strobes & 0x3) != 0x3) {
        gic_msg(LOG_WARNING, "sparce write access to EOI register is ignored");
        return MX_STATUS_OK;
      }

      unsigned int int_id = value & 0x3FF;
      unsigned int cpu_src_id = value >> 10 & 0x7;

      if (IS_SPURIOUS_INTERRUPT(int_id)) // spurious interrupt acknowledge
        return MX_STATUS_OK;
      if (c_active_int_stack_idx[cpu_id] < 0) // no active interrupt at all
        return MX_STATUS_OK;

      if (side_effect != t_debug) // non-debug access
        if (int_id != c_active_int_stack_id[cpu_id][c_active_int_stack_idx[cpu_id]])
          gic_msg(LOG_WARNING,
                  "CPU %u made a %s write to DIC's EOI register but the ID written (%u)"
                  "is not the ID of the currently running interrupt (%u)",
                  cpu_id, domain2str(domain),
                  int_id,
                  c_active_int_stack_id[cpu_id][c_active_int_stack_idx[cpu_id]]);
      // If written interrupt does not match an interrupt active on the cpu
      // (and in the case of software interrupt, matching includes the id of
      // source CPU), do nothing (see PR231-GENC-006924 5.2 section 3.8.2.5,
      // table 3-18)
      /** @todo unify message format and policy (Warning, Error,
          Internal Error) with the rest of the simulator) */

      /** @note could check activity of argument int_id using the list of
          active interrupt in the CPU interface, rather than using
          IS_ACTIVE_ON_CPU() which checks in the DISTRIBUTOR (see the warning
          at the end of GIC::writeEndOfInt().*/
      if (!IS_ACTIVE_ON_CPU(int_id, cpu_id))
        return MX_STATUS_OK;

      if (IS_SOFTWARE_INTERRUPT(int_id) && current_soft_int_active_src[cpu_id][int_id] != cpu_src_id) {
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "EOI Software Interrupt %d: mismatch "
                   "current_soft_int_active_src[cpu_id][int_id] %#x != cpu_src_id %u",
                   int_id, current_soft_int_active_src[cpu_id][int_id], cpu_src_id);
#endif
        return MX_STATUS_OK;
      }

        // Security Match (see PR231-GENC-006924 5.2 section 3.8.2.5, table 3-18)
        if (IS_UNSECURE_DOMAIN(domain)) {
#ifdef REFLECT_DOMAINS
          if (IS_SECURE_INTERRUPT(int_id, cpu_id))
#else
          if (IS_SECURE_DOMAIN(c_active_int_stack_domain[cpu_id][c_active_int_stack_idx[cpu_id]]))
#endif      // Secure NS-intsr, Unsecure NS-prot
          {
            // interrupt cannot be inactivated
          } else {
            // Unsecure NS-intsr, Unsecure NS-prot: Match
            /* the interrupt return to inactive or pending state */
            writeEndOfInt(cpu_id, int_id, cpu_src_id);
          }
        } else {
#ifdef REFLECT_DOMAINS
          if (IS_SECURE_INTERRUPT(int_id, cpu_id))
#else
          if (IS_SECURE_DOMAIN(c_active_int_stack_domain[cpu_id][c_active_int_stack_idx[cpu_id]]))
#endif      //   Secure NS-intsr, Secure NS-prot: match
          {
            /* the interrupt returns to inactive or pending state */
            writeEndOfInt(cpu_id, int_id, cpu_src_id);
          } else {
            // Unsecure NS-intsr, Secure NS-prot: behavior depends on AckCtl
            if (ACKCTL(c_ctrl_reg[cpu_id][domain])) {
              /* the interrupt returns to inactive or pending state */
              writeEndOfInt(cpu_id, int_id, cpu_src_id);
            } else {
              // Interrupt is left in the ACTIVE (or ACTIVEPENDING) state .
            }
          }
        }
      }
      break;
    case RUN_PRIO_R_OFF:
      // ------------------ 7. RUNNING PRIORITY --------------------
      // (see PR231-GENC-006924 5.2 section 3.8.2.6)
      TRACE_CIF_ACCESS("RUNNING PRIORITY");
      // Read only
      if (type == t_write) {
        TRACE_WRITE_VALUE;
        return MX_STATUS_OK;
      }

      // Nonsecure accesses undergo a translation
      // (see PR231-GENC-006924 5.2 section 3.7.3.3, table 3-1 page 10)
      if (c_running_int_priority[cpu_id] != 0xFF && // there are active interrupts
          IS_UNSECURE_DOMAIN(domain)) {
        // if currently running interrupt is
        if (IS_SECURE_DOMAIN(c_running_int_domain[cpu_id])) {
          value = 0;    // reads return 0 (maximum priority)
          TRACE_READ_VALUE;
        } else {
          // translation (using the same mask as for the PRIORITY MASK register)
          // Note that c_running_int_priority[] is calculated by update_running()
          value = (c_running_int_priority[cpu_id] << 1 & 0xFE);
          TRACE_READ_VALUE;
        }
      } else {
        value = c_running_int_priority[cpu_id];
        TRACE_READ_VALUE;
      }
      break;
    case HIGHST_PEND_R_OFF:
      // ------------------- 8. HPI ----------------------------
      TRACE_CIF_ACCESS("HIGHEST PRIORITY INTERRUPT");
      // Read only
      if (type == t_write) {
        TRACE_WRITE_VALUE;
        return MX_STATUS_OK;
      }
      // Register has the same format as the INTERRUPT ACKNOWLEDGE
      // register, the only difference being there are no side-effects
      // in reading this one.
      value = gethighestpendinginterruptregister(cpu_id, domain);
      TRACE_READ_VALUE;

      break;
    case CIF_IMPL_ID_R_OFF:
      // -------------------- 9. CPU INTERFACE IMPLEMENTER ID Reg.----
      TRACE_CIF_ACCESS("CPU INTERFACE IMPLEMENTER ID");

      // Read only
      if (type == t_write) {
        TRACE_WRITE_VALUE;
        return MX_STATUS_OK;
      }

      value = CIF_IMPL_ID_R_RST_VAL;
      TRACE_READ_VALUE;
      break;
    default: // RESERVED
      if (offset <= 0xFF) {
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "%s access to RESERVED AREA by cpu %u",
                   domain2str(domain), cpu_id);
#endif
        if (type == t_read)
          value = 0;
        return MX_STATUS_OK;
      }
      gic_msg_fl(LOG_ERROR, "bad argument offset %u", offset);
      if (type == t_read) {
        value = 0xdeaddead;
        TRACE_READ_VALUE;
      }
      /** @todo unify message format and policy (Warning, Error,
          Internal Error) with the rest of the simulator) */
      return MX_STATUS_ERROR;
      break;
  }
  return MX_STATUS_OK;

#undef TRACE_CIF_ACCESS
#undef TRACE_CIF_ACCESS_ID_RANGE
#undef TRACE_WRITE_VALUE
#undef TRACE_READ_VALUE
#undef TRACE_ACCESS_VALUE
}

/** Generate format and masking for the INTERRUPT ACKNOWLEDGE register and the HIGHEST
    PENDING INTERRUPT register (calculation of the HPI is done in update_highestpriority()).*/
MxU32
GIC::gethighestpendinginterruptregister(unsigned int core, unsigned int domain)
{
  unsigned int int_id;

  /** 1. First check the Security Match (see PR231-GENC-006924 5.2 section 3.8.2.4, table 3-16)*/
  if (IS_UNSECURE_DOMAIN(domain)) {
    if (IS_SECURE_DOMAIN(c_hpi_domain[core])) {
      //   Secure NS-intsr, Unsecure NS-prot
      int_id = 1023; // NO OUTSTANDING INTERRUPT
    } else {
      // Unsecure NS-intsr, Unsecure NS-prot: Match
      int_id = c_highest_priority_id[core];
    }

  } else {
    if (IS_SECURE_DOMAIN(c_hpi_domain[core])) {
      //   Secure NS-intsr, Secure NS-prot: match
      int_id = c_highest_priority_id[core];
    } else {
      // Unsecure NS-intsr, Secure NS-prot: behavior depends on AckCtl
      if (ACKCTL(c_ctrl_reg[core][domain])) {
        int_id = c_highest_priority_id[core];
      } else {
        int_id = 1022; // OUTSTANDING INTERRUPT IS NON SECURE; NO ACKNOWLEDGE!
      }
    }
  }

  /** 2. For Software Interrupt, include the ID of the CPU which triggered the interrupt.*/
  if (IS_SOFTWARE_INTERRUPT(int_id)) {
    return ((current_soft_int_pending_src[core][int_id] & 0x7) << 10) | (int_id & 0x7FF);
  } else {
    return int_id & 0x7FF;
  }
}



/** For core interface, submit a new highest priority interrupt.
    Check priority against mask, and if there is already an active
    interrupt, check if it should be pre-empted.using the running int
    priority register and the Binary point register.
    See PR231-GENC-006924 5.8, section 4.3.2, p34.
 @param core target CPU */
void
GIC::update_cpu_interface(unsigned int core)
{
  bool transmit = true;

  /** 0. skip spurious calls (CPU interface "inputs", including its registers were not modified) */
  if (!c_cpu_interface_edge[core]) {
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, " calling update_cpu_interface(%u): NO EDGE (c_cpu_interface_edge[core] false)", core);
#endif
    return;
  }
#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "update_cpu_interface(core =%u, highest_priority = %u, highest_priority_id = %u"
          "  hpi_domain = %s) ",
          core,
          c_highest_priority[core],
          c_highest_priority_id[core],
          domain2str(c_hpi_domain[core]));
#endif


  /** 1. compare with masks (0 is the highest priority value)*/
  if (IS_SPURIOUS_INTERRUPT(c_highest_priority_id[core])) {
    transmit = false;
  } else if (c_active_int_stack_idx[core] < 0) {  // no active interrupt
    if (c_priority_mask_reg[core] <= c_highest_priority[core]) {
      transmit = false; // rejected
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "HPI masked: "
              " c_priority_mask_reg[core] = %u <= c_highest_priority[core] = %u ",
              c_priority_mask_reg[core], c_highest_priority[core]);
#endif
    }
  } else { // pre-emption scheme
    // Mask: see PRD03-GENC-004392 7.0, section 4.2.3 p31.
    unsigned int mask;
    if (IS_UNSECURE_DOMAIN(c_hpi_domain[core])) {
      if (IS_IF_SPBPR(core)) // use secure BP register
        mask = ~((1 << c_binary_point_reg[core][SECURE]) - 1);
      else
        mask = ~((1 << c_binary_point_reg[core][NONSECURE]) - 1);
    } else {
      // secure interrupt: always use the secure BP
        mask = ~((1 << c_binary_point_reg[core][SECURE]) - 1);
        mask <<= 1;
    }
    // Pre-emption (see PRD03-GENC-004392 7.0, section 4.4.2 p38)
    if (((c_priority_mask_reg[core]    & mask) <= c_highest_priority[core]) ||
        ((c_running_int_priority[core] & mask) <= c_highest_priority[core])   ) {
      transmit = false; // active non preempted, hpi not signaled !
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "HPI not signaled:\n"
              "GIC:  c_priority_mask_reg[core] = %#x\n"
              "GIC:  c_highest_priority[core] = %#x\n"
              "GIC:  c_running_int_priority[core] = %#x\n"
              "GIC:  mask = %#x and SBPR = %u",
              c_priority_mask_reg[core],
              c_highest_priority[core],
              c_running_int_priority[core], mask, IS_IF_SPBPR(core));
#endif
    }
  }

  if (transmit) {
  /*  When all conditions above are met, signal to local cpu. For
      secure interrupts, use either processor's nIRQ or nFIQ input,
      according to a setting in the Control register of CPU
      interface. */
    if (IS_SECURE_DOMAIN(c_hpi_domain[core]) && IS_IF_FIQEn(core)) {
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "HPI signaled on FIQ!");
#endif
      signal_nFIQ[core] = 1;  // CPU's FIQ mechanism
      signal_nIRQ[core] = 0;
    } else {
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "HPI signaled on IRQ!");
#endif
      signal_nFIQ[core] = 0;
      signal_nIRQ[core] = 1;  // CPU's IRQ mechanism
    }
    signal_NSecure[core] = c_hpi_domain[core];
  } else {
    /* Negate the processor's nFIQ/nIRQ signals */
    signal_nFIQ[core] = 0;
    signal_nIRQ[core] = 0;
    signal_NSecure[core] = 0; // dummy
  }

  update_signal_nFIQ(core);
  update_signal_nIRQ(core);

  // from now on, expect a readIntAck() (the processor having acknowledged the
  // present interrupt) or another call to update_cpu_interface() if another
  // interrupt has been raised or a writeEndOfInt() (current active interrupt
  // has finished).

  /** 3. State that new values of "inputs" have been reflected in outputs. */
  c_cpu_interface_edge[core] = false;
}


/** get the security domain of the highest priority active interrupt on argument
    cpu interface.
    @param core the CPU interface ID
    @return the security domain (SECURE is returned when there are no active
            interrupts on core).
*/
unsigned int
GIC::domain_of_max_active_priority(unsigned int core)
{
  unsigned int max_priority = 0xFF; // lowest priority
  unsigned int domain = SECURE;
  for (int i = 0; i <= c_active_int_stack_idx[core]; i++) {
    unsigned int tmp_prio;
#ifdef REFLECT_PRIORITIES
    // get the current priorities from the DISTRIBUTOR
    tmp_prio = getPriority(c_active_int_stack_id[core][i], core);
#else
    // get the priorities which were used when interrupts were submitted by the distributor
    tmp_prio = c_active_int_stack_priority[core][i];
#endif
    if (tmp_prio < max_priority) {
      max_priority = tmp_prio;
#ifdef REFLECT_DOMAINS
      // get the current domain from the DISTRIBUTOR
      domain = getDomain(c_active_int_stack_id[core][i], core);
#else
      // get the domain which was used when interrupt was submitted by the distributor
      domain = c_active_int_stack_domain[core][i];
#endif
    }
  }
  return domain;
}

/** get the highest priority among active interrupt on argument cpu interface.
    @param core the CPU interface ID
    @return the highest active priority (lowest priority is returned when there are no active
            interrupts on core).
*/
MxU32
GIC::max_active_priority(unsigned int core)
{
  MxU32 max_priority = 0xFF; // lowest priority

  for (int i = 0; i <= c_active_int_stack_idx[core]; i++) {
    unsigned int tmp_prio;
#ifdef REFLECT_PRIORITIES
    // get the current tmp_priorities from the DISTRIBUTOR
    tmp_prio = getPriority(c_active_int_stack_id[core][i], core);
#else
    // get the priorities which were used when interrupts were submitted by the distributor
    tmp_prio = c_active_int_stack_priority[core][i];
#endif
    if (tmp_prio < max_priority)
      max_priority = tmp_prio;
  }
  return max_priority;
}

/** @brief Called when a write to the CLEAR PENDING register is attempted (see
    GIC::d_reg_map_access()).  Update the PENDING register.
    @param int_no Which int has been signalled
    @param core_id For banked interrupts, the core on which interrupt is
    requested.
 */
void
GIC::writeClearPending(unsigned int int_no, unsigned int core_id)
{
  //dispatch_event_on_targets(int_no, core_id, WRITE_CP);
  /** 1. For banked interrupts, do only set on local CPU (anyway, the code below
      would behave correctly because getCPUTargets() would provide local CPU as
      the only target). */
  if (IS_BANKED_INTERRUPT(int_no)) {
    transitionFSM(core_id, int_no, WRITE_CP);
    return;
  }

  /** 2. For each cpu, run the finite state machine (calling GIC::transitionFSM()) */
  for (unsigned int targetcpu = 0; targetcpu < n_cores; targetcpu++)
    transitionFSM(targetcpu, int_no, WRITE_CP);
}

/** @brief Called when either an interrupt request has been asserted
    (eg in signal_port_irq29_core0_drive()) or when a write to the
    SET PENDING register is attempted (see GIC::d_reg_map_access()).
    Update the PENDING register and eventually the ACTIVE state in
    DISTRIBUTOR.
    @param int_no Which int has been signalled
    @param core_id For banked interrupts, the core on which interrupt
    is requested.
 */
void
GIC::writeSetPending(unsigned int int_no, unsigned int core_id)
{
  dispatch_event_on_targets(int_no, core_id, WRITE_P);
}

void
GIC::dispatch_event_on_targets(unsigned int int_no, unsigned int core_id, fsmEvent event)
{
  unsigned int target_list;
  /** 1. For banked interrupts, do only set on local CPU (anyway, the code below
      would behave correctly because getCPUTargets() would provide local CPU as
      the only target). */
  if (IS_BANKED_INTERRUPT(int_no)) {
    transitionFSM(core_id, int_no, event);
    return;
  }

  /** 2. Check the list of CPUs the argument interrupt is targeted to,
      calling GIC::getCPUTargets() and for each target cpu, run the finite
      state machine (calling GIC::transitionFSM()) */
  target_list = getCPUTargets(int_no, core_id);
  for (unsigned int targetcpu = 0; targetcpu < n_cores; targetcpu++)
    if (target_list & (1 << targetcpu))
      transitionFSM(targetcpu, int_no, event);
}

/** CPU interface updates its list of active interrupts priorities and updates
    its (ill-called) "running priority" register (which is the NOT the priority of
    the currently running interrupt if we are an implementation which reflects
    changes of priority to active interrupts (see PR231-GENC-006924 5.3, section
    3.8.2.4, 4.1.1.4))
    @param core the processor which reads its acknowledge register.
*/
void
GIC::readIntAck(unsigned int core)
{
#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "GIC::readIntAck(%u)", core);
#endif
  unsigned int hpi = c_highest_priority_id[core];

  /** 1. Reflect in the model stack of interrupt IDs */
  c_active_int_stack_idx[core]++;
  if (c_active_int_stack_idx[core] < 0) {
    gic_msg_fl(LOG_FATAL, "stack index %d out of range", c_active_int_stack_idx[core]);
    c_active_int_stack_idx[core] = 0;
  }
  c_active_int_stack_id[core][c_active_int_stack_idx[core]] = hpi;

#ifndef REFLECT_DOMAINS
  // remember of the interrupt's security attribute
  c_active_int_stack_domain[core][c_active_int_stack_idx[core]] = getDomain(hpi,core);
#endif
#ifndef REFLECT_PRIORITIES
  // remember of the interrupt's priority
  c_active_int_stack_priority[core][c_active_int_stack_idx[core]] = getPriority(hpi,core);
#endif

 /** 3. In the DISTRIBUTOR, set the status of interrupt to ACTIVE (Security
      match has been done in GIC::c_reg_map_access()). This updates the PENDING
      and ACTIVE registers as well as the highest priority pending interrupt
      submitted to the CPU interface.  */
  transitionFSM(core, hpi, READ_IA);

  /** 4. In the case of a software interrupt, remove current request from
      the pool of pending requests and set it the "current active request". */
  if (IS_SOFTWARE_INTERRUPT(hpi))
    set_active_soft_int(core, hpi);
}

/** Processor finished an active interrupt, which becomes INACTIVE or PENDING
    (see PR231-GENC-006924 5.3, section 3.8.2.5).
    @param core the processor which writes its EOI register.
    @param int_id the ID of the active interrupt cpu finished handling.
    @param src_cpu for the software interrupts, the id of initiator.
*/
void
GIC::writeEndOfInt(unsigned int core, unsigned int int_id, unsigned int src_cpu)
{
  /** 0. No active interrupt at all */
  if (c_active_int_stack_idx[core] < 0) {
    gic_msg_fl(LOG_ERROR,
            "called writeEndOfInt(%u, %u, %u) while there is no active interrupt", core, int_id, src_cpu);
    return;
  }

  /** 1. In the CPU interface, update the list of active interrupt priority
      (just drop the top entry from the stack) */
  c_active_int_stack_idx[core]--;
  /** @todo remove the argument from the stack, no matter its position. */

  /** 2.In the DISTRIBUTOR, the interrupt becomes INACTIVE (or PENDING
      in the case of software interrupts and in the case of level
      sensitive interrupts (? depending on the definition we take
      for 1-N model). Security match and check of interrupt id (which
      only needs to match an active int on that cpu) has been done in
      GIC::c_reg_map_access(). This updates the PENDING and ACTIVE
      registers. */
  transitionFSM(core, int_id, WRITE_EOI);

  /** 3. In the case of a software interrupt, clear current active request */
  if (IS_SOFTWARE_INTERRUPT(int_id))
    finished_soft_int(core, int_id);
}

/** Force to the inactive state argument interrupt on any other cores
    than argument. Called when an interrupt becomes active, to ensure
    the 1-N behavior of the interrupt (see section 3.2.2 of
    PRD03-GENC-004392 7.0 page 6) */
void
GIC::model_1_N_in(unsigned hpi, unsigned core)
{
  if (IS_BANKED_INTERRUPT(hpi) || !IS_1N_INTERRUPT(hpi))
    return;
  // NB: Software interrupts are banked, hence never get down here.
#if defined(TMP_1N_MODEL_FORCE_NOT_PENDING_EDGE) && defined(TMP_1N_MODEL_FORCE_NOT_PENDING_LVL)
  if (isEdgeTriggered(hpi, core) || IS_LEVEL_SENSITIVE(hpi, core))
#elif defined(TMP_1N_MODEL_FORCE_NOT_PENDING_EDGE)
  if (isEdgeTriggered(hpi, core))
#elif defined(TMP_1N_MODEL_FORCE_NOT_PENDING_EDGE)
  if (IS_LEVEL_SENSITIVE(hpi, core))
#else
  if (0)
#endif
    {
      // 1-N model forces interrupt to be inactive on other CPUs than the one it is active on.
      for (unsigned int tmpcpu = 0; tmpcpu < core; tmpcpu++)
        if (IS_PENDING_ON_CPU(hpi, tmpcpu)) {
          transitionFSM(tmpcpu, hpi, NOW_ACTIV);
        }
      for (unsigned int tmpcpu = core + 1; tmpcpu < n_cores; tmpcpu++)
        if (IS_PENDING_ON_CPU(hpi, tmpcpu)) {
          transitionFSM(tmpcpu, hpi, NOW_ACTIV);
        }
    } else {
      // Interrupt is still pending, but is not eligible to the HPI on any
      // CPU -> recalculate HPI on CPUs which were target of the CPUs.
      for (unsigned int tmpcpu = 0; tmpcpu < n_cores; tmpcpu++) {
        if (!IS_PENDING_ON_CPU(hpi, tmpcpu)) continue;
        update_highestpriority(tmpcpu);
        update_cpu_interface(tmpcpu);
      }
    }
}

/** Called when an interrupt (argument) was active and the EOI
    register has been written to finish it. Currently, set back to
    pending status level-sensitive interrupts which are asserted but
    inactive because active on argument CPU */
void
GIC::model_1_N_out(unsigned int_id, unsigned core)
{
  if (IS_BANKED_INTERRUPT(int_id) || !IS_1N_INTERRUPT(int_id))
    return;

#ifdef TMP_1N_MODEL_FORCE_NOT_PENDING_LVL
  if (IS_LEVEL_SENSITIVE(int_id, core)) {
  // 1-N model forces interrupt to be inactive on other CPus than the one it is active on.
  unsigned target_list = getCPUTargets(int_id, core);
  for (unsigned int tmpcpu = 0; tmpcpu < core; tmpcpu++)
    if (target_list & (1 << tmpcpu))
      transitionFSM(tmpcpu, int_id, NOT_ACTIV);
  for (unsigned int tmpcpu = core + 1; tmpcpu < n_cores; tmpcpu++)
    if (target_list & (1 << tmpcpu))
      transitionFSM(tmpcpu, int_id, NOT_ACTIV);
  } else
#endif

  // If interrupt is still pending, but was not eligible to the HPI
  // because it was active on some CPU, recalculate HPI on CPUs which
  // are target of the CPUs.
  for (unsigned int tmpcpu = 0; tmpcpu < n_cores; tmpcpu++) {
    if (!IS_PENDING_ON_CPU(int_id, tmpcpu)) continue;
    update_highestpriority(tmpcpu);
    update_cpu_interface(tmpcpu);
  }
}

/** Serialize software interrupt sources of argument soft int ID */
void
GIC::set_pending_soft_int(unsigned int target_cpu, unsigned int int_id, unsigned int src_cpu)
{
  // 1. Serialize software interrupt request
  soft_int_pending_requests[target_cpu][int_id] |= 1 << src_cpu;

  // 2. Arbitrate among pending sources
  // IMPLEMENTATION DEFINED
  /** @todo to be fixed later to match RTL (round robin ?) */
  if (src_cpu < current_soft_int_pending_src[target_cpu][int_id]) {
    current_soft_int_pending_src[target_cpu][int_id] = src_cpu;
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, "current_soft_int_pending_src[cpu %d][int_id %d] = %#x", target_cpu, int_id, current_soft_int_pending_src[target_cpu][int_id]);
#endif

  }
}
/** Serialize software interrupt sources of argument soft int ID */
void
GIC::set_active_soft_int(unsigned int target_cpu, unsigned int int_id)
{
  unsigned current_req = current_soft_int_pending_src[target_cpu][int_id];

#ifndef NOCHECK
  // Sanity check
  if (!(soft_int_pending_requests[target_cpu][int_id] & (1 << current_req)))
    gic_msg_fl(LOG_ERROR, "unexpected call to set_active_soft_int(cpu %u, int_id %u)",
               target_cpu, int_id);
#endif

  /** 0. Set update active request for argument interrupt */
  current_soft_int_active_src[target_cpu][int_id] = current_req;

  /** 1. remove request from pool of pending */
  soft_int_pending_requests[target_cpu][int_id] &= ~(1 << current_req);

  /** 2. Recalculate the next pending request to be taken */
  // IMPLEMENTATION DEFINED
  /** @todo to be fixed later to match RTL (round robin ?) */
  unsigned tmpcpu;
  for (tmpcpu = 0; tmpcpu < n_cores ; tmpcpu++)
    if (soft_int_pending_requests[target_cpu][int_id] & (1 << tmpcpu))
      break;
  if (tmpcpu < n_cores) {
    current_soft_int_pending_src[target_cpu][int_id] = tmpcpu;
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, "current_soft_int_pending_src[cpu %d][int_id %d] = %#x",
               target_cpu, int_id, current_soft_int_pending_src[target_cpu][int_id]);
#endif
  } else {
    current_soft_int_pending_src[target_cpu][int_id] = 0xFF; /* dummy src cpu id */
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, "current_soft_int_pending_src[cpu %d][int_id %d] = %#x",
               target_cpu, int_id, current_soft_int_pending_src[target_cpu][int_id]);
#endif
  }
}

void
GIC::finished_soft_int(unsigned int target_cpu, unsigned int int_id)
{
  unsigned &current_req = current_soft_int_active_src[target_cpu][int_id];

#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "current_soft_int_active_src[cpu %d][int_id %d] = %#x is reset to 0xFF",
             target_cpu, int_id, current_soft_int_active_src[target_cpu][int_id]);
#endif

  /** 0. Sanity Check */
  if (current_req >= n_cores) {
    gic_msg_fl(LOG_FATAL, "unexpected call to finished_soft_int(cpu %u, int_id %u)",
               target_cpu, int_id);
    return;
  }

  /** 1. Set dummy src cpu id */
  current_req = 0xFF;
}


/**
   @brief Advance state machine for a core interrupt computes the new
   state (see fsmState) of argument interrupt on argument core,
   according to event \a s (a change in one of the conditions for state transition, see
   fsmEvent). This code follows closely the FSM described in section
   4.1.2 of PR231-GENC-006924 5.2, page 35).
   @param core   The id of local cpu
   @param int_no The ID of interrupt
   @param event  Tells the FSM which transition condition changed (see fsmEvent),
                 so its does need to evaluate it.
*/
void
GIC::transitionFSM(unsigned int core, unsigned int int_no, fsmEvent event)
{
  intType type;

#ifndef NOCHECK
  if (!IS_VALID_CPUID(core) || !IS_REAL_INTERRUPT(int_no)) {
    gic_msg_fl(LOG_FATAL, "invalid argument in GIC::transitionFSM(%u, %u, %s)",
               core, int_no, fsmEvent2str(event));
    return;
  }
#endif
  const fsmState &current_state = coreFSM[core][int_no];
  fsmState       &next_state    = coreFSM[core][int_no];

#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "calling transitionFSM(core = %u, int ID = %u, %s) while current_state is %s", core, int_no,
             fsmEvent2str(event), fsmState2str(current_state));
#endif

  /** 1. Determine the type of argument interrupt */
  if (IS_SOFTWARE_INTERRUPT(int_no))
    type = SOFT;
  else if (isEdgeTriggered(int_no, core))
    type = EDGE_T;
  else
    type = LEVEL_S;

  /** 2. Run the state machine: For each state, check the conditions of each
      possible transition. Note that during the update phase, further call to
      this function can occur, if one of the fsmEvent occur. Currently, the only
      case is the transition D for level-sensitive interrupts, which is followed
      immediately by transition A whenever the Peripheral request is still asserted.*/

  /*                                                                         */
  /*                                                  +--------+             */
  /*                                          D      /  Active  \            */
  /*                                       +------->+     &      +--+        */
  /*                      A               /          \  Pending /    \       */
  /*                   .------.           |           +---+----+      \      */
  /*       +--------+ /       _\|+--------+          /    ^            \     */
  /*      /          \          /          \        /     |             | F  */
  /*     +  inactive  +        +  Pending   +<-----+ G    + E           |    */
  /*      \          /_         \          /               \           /     */
  /*       +--------+|\        / +--------+                 \         /      */
  /*                   '------`            \              +--------+<+       */
  /*                       B                \            /          \        */
  /*                                         +--------->+   Active   +       */
  /*                                           C         \          /        */
  /*                                                      +--------+         */
  switch (current_state) {
  case INACTIVE:
    {
      // 1 possible transition is A for SOFT(ware) and EDGE_T(riggered) interrupts
      // 2 possible transitions for LEVEL_S(ensitive) ints.
      bool set_pending = false;
      switch (type) {
      case LEVEL_S:
        {
          bool go_pending_lvl = false;
          // 5 events: target, enabled, write to set-pending reg, or assertion of irq
          switch (event) {
          case VALID_TRG:   // int has just become a target
            if (IS_STICKY_PENDING(int_no, core)) {
              // If interrupt had been set pending by writing the PENDING_SET register,
              // changing the target list does dispatch that "sticky" pending state to other targets
              // 1. (A) INACTIVE -> PENDING taken
              next_state = PENDING;
#ifdef GIC_TRACE
              gic_msg_fl(LOG_TRACE, "GIC:(A) INACTIVE -> PENDING taken");
#endif
            } else
              go_pending_lvl = true;
            break;
          case EDGE:        // interrupt line has been asserted (or distributor has been switched on)
          case NOT_ACTIV:   // interrupt finished on another CPU (1-N mode)
            go_pending_lvl = isTarget(int_no, core);
            break;
          case WRITE_P:    // Pending flag has been set (software write)
            if (isTarget(int_no, core)) {
              // 1. (A) INACTIVE -> PENDING taken
              next_state = PENDING;
#ifdef GIC_TRACE
              gic_msg_fl(LOG_TRACE, "GIC:(A) INACTIVE -> PENDING taken");
#endif
            }
            break;
          default:
            break;
          }
          if (go_pending_lvl                           &&
              IS_CTR_ENABLED(int_no, core)             &&
              INT_SIG_VALUE(int_no, core)              &&
              !(IS_ACTIVE_ON_ANY_CPU(int_no, core) &&
                IS_1N_INTERRUPT(int_no)              )   ) {
            next_state = PENDING_LVL; // this state reflects the level of interrupt line (see PENDING_LVL -> INACTIVE below)
#ifdef GIC_TRACE
            gic_msg_fl(LOG_TRACE, "GIC:(A') INACTIVE -> PENDING_LVL taken");
#endif
          }
        }
        break; // LEVEL_S
      case SOFT:
        // 1 event: a proper write to the SWI register
        // (target and security clauses have already been checked)
        set_pending = (event == WRITE_SWI);
        break; // SOFT
      case EDGE_T:
        // 2 events: (rising edge or write to isPending())
        set_pending = (((event == EDGE) && INT_SIG_VALUE(int_no, core)) || // posegde on interrupt line
#ifdef PENDING_FLOP_CPU_TARGET_SENSITIV
                       ((event == VALID_TRG) && IS_STICKY_PENDING(int_no, core)) ||
#endif
                       (event == WRITE_P));        // Pending flag has been set (software write)
        break; // EDGE_T
      }

      // take transition to sticky state PENDING
      if (set_pending) {
        // 1. (A) INACTIVE -> PENDING taken
        next_state = PENDING;
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "GIC:(A) INACTIVE -> PENDING taken");
#endif
      }

      // 2. EFFECT:
      if (next_state != INACTIVE) {
        // 1. Update the pending register view.
        update_pending(int_no, core);
        // 2. Recalculate the pending interrupt of highest priority
        // Calculate the highest priority interrupt.  Submit to CPU interface the
        // new highest priority pending interrupt, together with its current
        // priority and its (current) security domain.  If the highest priority is
        // higher than the mask, assert the CPU nIRQ/nFIQ signal and place
        // candidate interrupt id in the ACKNOWLEDGE register.
        update_highestpriority(core);
        update_cpu_interface(core);
      }
    }
    break; // of state INACTIVE

  case PENDING_LVL:
    // The 3 possible transitions are B, C and D
    switch (event) {
    case WRITE_P:
      next_state = PENDING; // this state is not reversible (even if irq line negedges, this pending state will remain)
      break;
    case EDGE:
    case NOW_ACTIV:
      // ******************** B: PENDING_LVL -> INACTIVE **********
      if (INT_SIG_VALUE(int_no, core) &&
          !(IS_ACTIVE_ON_ANY_CPU(int_no, core) && IS_1N_INTERRUPT(int_no))) {
#ifdef GIC_TRACE
      if (!IS_ACTIVE_ON_ANY_CPU(int_no, core))
        gic_msg_fl(LOG_TRACE, " !IS_ACTIVE_ON_ANY_CPU(int_no, core)");
      if (!IS_1N_INTERRUPT(int_no))
        gic_msg_fl(LOG_TRACE, " !IS_1N_INTERRUPT(int_no)");
#endif
        return;
      }
      // fall thru!
    case INVALID_TRG:
      // 1. (B) PENDING_LVL -> INACTIVE
      next_state = INACTIVE;

#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, " (B) PENDING_LVL -> INACTIVE taken ");
#endif

      // 2. EFFECT:
      // 1. new state is INACTIVE, clear the pending flag in DISTRIBUTOR.
      update_pending(int_no, core);
      // 2. Recalculate the pending interrupt of highest priority
      // Calculate the highest priority interrupt.  Submit to CPU interface the
      // new highest priority pending interrupt, together with its current
      // priority and its (current) security domain.  If the highest priority is
      // higher than the mask, assert the CPU nIRQ/nFIQ signal and place
      // candidate interrupt id in the ACKNOWLEDGE register.
      update_highestpriority(core);
      update_cpu_interface(core);
      break;

    case READ_IA:
      // According to definition of 1-N model that we choose, we have either:
      // ******************** D: PENDING_LVL -> ACTIVEPENDING_LVL ************
      // or
      // ******************** C: PENDING_LVL -> ACTIVE ************
      if (!isEnabled(int_no, core))
        return;
#ifdef TMP_1N_MODEL_FORCE_NOT_PENDING_LVL
      //1. C: PENDING -> ACTIVE
      next_state = ACTIVE;
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "  (D)  PENDING_LVL -> ACTIVE taken");
#endif
#else
      //1. D: PENDING -> ACTIVEPENDING
      next_state = ACTIVEPENDING_LVL;
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "  (D)  PENDING_LVL -> ACTIVEPENDING_LVL taken");
#endif
#endif

      // 2. EFFECT:
      // 2.0. Interrupt is no more eligible to HPI on all cores:
      //      recalculate HPI for all cpus interrupt is pending on.

      // Interpretation of note of section 4.2.7 ("Highest Pending
      // Interrupt Register") page 34 of PRD03-GENC-004392 7.0:
      update_highestpriority(core);
      update_running(core);
      update_cpu_interface(core);

      // 2.1. new state is ACTIVEPENDING(_LVL), set the active flags in DISTRIBUTOR.
      update_active(int_no, core);
#ifdef TMP_1N_MODEL_FORCE_NOT_PENDING_LVL
      update_pending(int_no, core);
#endif

      // 2.2 Ensure 1-N model:
      model_1_N_in(int_no, core);

      break;
    default:
      break; // ignore other events
    }
    break; // of state PENDING_LVL

  case PENDING:
    // For software and edge-triggered ints, the 2 possible transitions are B and C (D is only part of the transitive closure of graph Figure 4.20 of PRD03-GENC-004392 7.0)
    switch (event) {
    case INVALID_TRG:
#ifndef PENDING_FLOP_CPU_TARGET_SENSITIV
      if (!IS_LEVEL_SENSITIVE(int_no, core))
        break;
#endif
      // fall thru!
    case WRITE_CP:
    case NOW_ACTIV:
      if (type == LEVEL_S &&
          !(IS_ACTIVE_ON_ANY_CPU(int_no, core) && IS_1N_INTERRUPT(int_no)) &&
          isTarget(int_no, core) && IS_CTR_ENABLED(int_no, core) && INT_SIG_VALUE(int_no, core)) {
        // 1. PENDING -> PENDING_LVL
        next_state = PENDING_LVL;
        return;
      }
      // ******************** B: PENDING -> INACTIVE **********
      if (type == SOFT) return;

      // 1. (B) PENDING -> INACTIVE
      next_state = INACTIVE;

#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, " (B) PENDING -> INACTIVE taken ");
#endif

      // 2. EFFECT:
      // 1. new state is INACTIVE, clear the pending flag in DISTRIBUTOR.
      update_pending(int_no, core);
      // 2. Recalculate the pending interrupt of highest priority
      // Calculate the highest priority interrupt.  Submit to CPU interface the
      // new highest priority pending interrupt, together with its current
      // priority and its (current) security domain.  If the highest priority is
      // higher than the mask, assert the CPU nIRQ/nFIQ signal and place
      // candidate interrupt id in the ACKNOWLEDGE register.
      update_highestpriority(core);
      update_cpu_interface(core);
      break;

    case READ_IA:
      // ******************** C: PENDING -> ACTIVE ************
      // ******************** D: PENDING -> ACTIVEPENDING_LVL ******* (LEVEL_S only)
      // ******************** D: PENDING -> ACTIVEPENDING ******* (SOFT only)
      if (type != SOFT && !isEnabled(int_no, core))
        return;
      // for a soft interrupt, if several requests are pending: go in state "Active-Pending"
      if (type == SOFT  &&
          soft_int_pending_requests[core][int_no] & ~(1 << current_soft_int_pending_src[core][int_no])  ) {
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "  (D)  PENDING -> ACTIVEPENDING taken");
#endif
        next_state = ACTIVEPENDING;
      } else if (type == LEVEL_S && INT_SIG_VALUE(int_no, core)) {
#ifdef TMP_1N_MODEL_FORCE_NOT_PENDING_LVL
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "  (C)  PENDING -> ACTIVE taken ");
#endif
        next_state = ACTIVE;
#else
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "  (D)  PENDING -> ACTIVEPENDING_LVL taken ");
#endif
        next_state = ACTIVEPENDING_LVL;
#endif
      } else  { // Edge-triggered, soft AND Level-sensitive whose line is negated.
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "  (C)  PENDING -> ACTIVE taken ");
#endif
        next_state = ACTIVE;
      }
      // 2. EFFECT:
      // 0. Interrupt is no more eligible to HPI:
      update_highestpriority(core);
      // 1. In the CPU interface, the set of active interrupts has changed, update
      //    the "running priority" register (see PR231-GENC-006924 5.3 section 3.8.2.6)
      update_running(core);
      // 2. Recalculate the pending interrupt of highest priority
      // Calculate the highest priority interrupt.  Submit to CPU interface the
      // new highest priority pending interrupt, together with its current
      // priority and its (current) security domain.  If the highest priority is
      // higher than the mask, assert the CPU nIRQ/nFIQ signal and place
      // candidate interrupt id in the ACKNOWLEDGE register.
      update_cpu_interface(core);

      // 3. new state is ACTIVE, clear the pending and set the active flags in
      // DISTRIBUTOR's registers.
      update_active(int_no, core);
      update_pending(int_no, core);

      // 4. Ensure the 1-N model:
      model_1_N_in(int_no, core);

      break;
    default:
      break; // ignore other events
    }
    break; // of state PENDING

  case ACTIVE:
    // The 2 possible transitions are D and F.
    switch (event) {
    case WRITE_EOI:
      // ******************* D: ACTIVE -> INACTIVE *************
      // 1. (D)  ACTIVE -> INACTIVE
      if (type == LEVEL_S && INT_SIG_VALUE(int_no, core) && isTarget(int_no, core)) {
        next_state = PENDING_LVL;
        // that transition would be possible depending on the 1-N model definition we take - 2007-05-25
        // see TMP_1N_MODEL_FORCE_NOT_PENDING
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, " (?)  ACTIVE -> PENDING_LVL taken ");
#endif
      } else {
        next_state = INACTIVE;
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, " (D)  ACTIVE -> INACTIVE taken ");
#endif
      }
      // 2.EFFECT:
      // no need to update HPI, interrupt is not pending on argument core.
      /** 1. The set of active interrupts in the CPU interface has
          changed, update the "running priority" register (see
          PR231-GENC-006924 5.3 section 3.8.2.6), which gives the highest
          priority of active interrupts. Since the preemption condition
          changes, there might be a pending interrupt to signal, so do
          call update_cpu_interface().*/
      if (next_state == PENDING_LVL)
        update_highestpriority(core);
      update_running(core);
      update_cpu_interface(core);

      /** 2. new state is INACTIVE, clear the active flags */
      update_active(int_no, core);
      if (next_state == PENDING_LVL)
        update_pending(int_no, core);

      /** 3. Ensure 1-N model */
      model_1_N_out(int_no, core);

      break; // of WRITE_EOI
    case EDGE:
      // ******************* E: ACTIVE -> ACTIVEPENDING(_LVL)******
      if (type == SOFT || !INT_SIG_VALUE(int_no, core))
        return;

      if (type == LEVEL_S) {
#ifdef TMP_1N_MODEL_FORCE_NOT_PENDING_LVL
        return; // ignored
#else
        next_state = ACTIVEPENDING_LVL;
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, " (E)  ACTIVE -> ACTIVEPENDING_LVL taken ");
#endif
#endif
      } else {
        next_state = ACTIVEPENDING;
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, " (E)  ACTIVE -> ACTIVEPENDING taken ");
#endif
      }

      // 2. EFFECT:
      // 1. new state is ACTIVEPENDING, set the pending flag (active flag is already set, normally).
      update_pending(int_no, core);
      // 2. Recalculate the pending interrupt of highest priority
      // Calculate the highest priority interrupt.  Submit to CPU interface the
      // new highest priority pending interrupt, together with its current
      // priority and its (current) security domain.  If the highest priority is
      // higher than the mask, assert the CPU nIRQ/nFIQ signal and place
      // candidate interrupt id in the ACKNOWLEDGE register.
      update_highestpriority(core);
      update_cpu_interface(core);

      break; // of EDGE
    case WRITE_SWI:
    case WRITE_P:
      // ******************* E: ACTIVE -> ACTIVEPENDING ******
      if (((type == SOFT)  && (event != WRITE_SWI)) ||
          ((type != SOFT)  && (event != WRITE_P))     )
        return;
      // 1. (E)  ACTIVE -> ACTIVEPENDING
      next_state = ACTIVEPENDING;
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, " (E)  ACTIVE -> ACTIVEPENDING taken ");
#endif

      // 2. EFFECT:
      // 1. new state is ACTIVEPENDING, set the pending flag (active flag is already set, normally).
      update_pending(int_no, core);
      // 2. Recalculate the pending interrupt of highest priority
      // Calculate the highest priority interrupt.  Submit to CPU interface the
      // new highest priority pending interrupt, together with its current
      // priority and its (current) security domain.  If the highest priority is
      // higher than the mask, assert the CPU nIRQ/nFIQ signal and place
      // candidate interrupt id in the ACKNOWLEDGE register.
      update_highestpriority(core);
      update_cpu_interface(core);
 
      break; // of WRITE_SWI, WRITE_P
    default:
      break; // ignore other events
    }
    break; // of state ACTIVE

  case ACTIVEPENDING:
    // For software and edge-triggered ints, the 2 possible transitions are F and G.
    // For level-sensitive ints, there might be an internal transition ACTIVEPENDING -> ACTIVEPENDING_LVL
    switch (event) {
    case INVALID_TRG:
#ifndef PENDING_FLOP_CPU_TARGET_SENSITIV
      if (!IS_LEVEL_SENSITIVE(int_no, core))
        break;
#endif
      // fall-thru !
    case WRITE_CP:
      // ******************* F: ACTIVEPENDING -> ACTIVE *********
      switch (type) {
      case LEVEL_S:
        if (INT_SIG_VALUE(int_no, core)) {
#ifdef TMP_1N_MODEL_FORCE_NOT_PENDING_LVL
          next_state = ACTIVE;
#else
          next_state = ACTIVEPENDING_LVL; // it is still pending.
          /** @todo confirm this behavior is right (not explicit in PRD03-GENC-004392 7.0) */
#endif
        } else {
          next_state = ACTIVE;
        }
        break;
      case EDGE_T:
        // 1. (F)  ACTIVEPENDING -> ACTIVE
        next_state = ACTIVE;
        break;
      default:
        break;
      }
      // 2. EFFECT:
      if (next_state == ACTIVE) {
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "  (F)  ACTIVEPENDING -> ACTIVE taken ");
#endif
        // 1.new state is ACTIVE, clear the pending flag
        update_pending(int_no, core);
        // 2. Recalculate the pending interrupt of highest priority
        // Calculate the highest priority interrupt.  Submit to CPU interface the
        // new highest priority pending interrupt, together with its current
        // priority and its (current) security domain.  If the highest priority is
        // higher than the mask, assert the CPU nIRQ/nFIQ signal and place
        // candidate interrupt id in the ACKNOWLEDGE register.
        update_highestpriority(core);
        update_cpu_interface(core);
      }

      break; // of WRITE_CP
    case WRITE_EOI:
      // ******************* G: ACTIVEPENDING -> PENDING ************
      // 1. (G)  ACTIVEPENDING -> PENDING
      next_state = PENDING;
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "  (G)  ACTIVEPENDING -> PENDING taken ");
#endif
      // 2.EFFECT:
      // 0. Interrupt becomes eligible to HPI:
      update_highestpriority(core);
      /**  The set of active interrupts In the CPU interface has
          changed, update the "running priority" register (see
          PR231-GENC-006924 5.3 section 3.8.2.6), which gives the highest
          priority of active interrupts. Since the preemption condition
          changes, there might be a pending interrupt to signal, so do
          call update_cpu_interface().*/
      update_running(core);
      update_cpu_interface(core);

      // 1. Update DISTRIBUTOR's active register
      update_active(int_no, core);

      // 2. Ensure 1-N model:
      model_1_N_out(int_no, core);

      break; // of WRITE_EOI

    default:
      break; // ignore other events
    }
    break; // of state ACTIVEPENDING

  case ACTIVEPENDING_LVL:
    // The 2 possible transitions are E and G
    // ******************* F: ACTIVEPENDING_LVL -> ACTIVE *********
    switch (event) {
    case WRITE_P:
      next_state = ACTIVEPENDING; // this state is not reversible (even if irq line negedges, this pending state will remain)
      break;
    case EDGE:
      if (INT_SIG_VALUE(int_no, core)) return;
      // fall-thru !
    case WRITE_CP:
    case INVALID_TRG:
      next_state = ACTIVE;
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "  (F)  ACTIVEPENDING_LVL -> ACTIVE taken ");
#endif
      // 2. EFFECT:
      // 1.new state is ACTIVE, clear the pending flag
      update_pending(int_no, core);
      // 2. Recalculate the pending interrupt of highest priority
      // Calculate the highest priority interrupt.  Submit to CPU interface the
      // new highest priority pending interrupt, together with its current
      // priority and its (current) security domain.  If the highest priority is
      // higher than the mask, assert the CPU nIRQ/nFIQ signal and place
      // candidate interrupt id in the ACKNOWLEDGE register.
      update_highestpriority(core);
      update_cpu_interface(core);
      break; // of cases INVALID_TRG, WRITE_CP and EDGE.
    case WRITE_EOI:
      // ******************* G: ACTIVEPENDING_LVL -> PENDING_LVL ************
      // 1. (G)  ACTIVEPENDING_LVL -> PENDING_LVL
      next_state = PENDING_LVL;
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "  (G)  ACTIVEPENDING_LVL -> PENDING_LVL taken ");
#endif
      // 2.EFFECT:
      /** 2.0. Interrupt becomes eligible to HPI: */
      update_highestpriority(core);
      /** 2.1. The set of active interrupts In the CPU interface has
          changed, update the "running priority" register (see
          PR231-GENC-006924 5.3 section 3.8.2.6), which gives the highest
          priority of active interrupts. Since the preemption condition
          changes, there might be a pending interrupt to signal, so do
          call update_cpu_interface().*/
      update_running(core);
      update_cpu_interface(core);

      /** 2.3 Update DISTRIBUTOR's active and register*/
      update_active(int_no, core);

      /** 2.4. Ensure 1-N model:*/
      model_1_N_out(int_no, core);

      break; // of WRITE_EOI
    default:
      break; // ignore other events
    }
    break; // of state ACTIVEPENDING_LVL

  default:
    gic_msg_fl(LOG_ERROR, "unknown state in GIC::transitionFSM()");
    break;
  }
}


/** update the pending register in DISTRIBUTOR, for the argument interrupt.
    @param int_no   interrupt ID
    @param core     Used for banked interrupts only */
void
GIC::update_pending(unsigned int int_no, unsigned int core)
{
  /** 1. Update bit in PENDING register: it is set iff interrupt is pending on at least one cpu */

  /* look on argument cpu (for non banked interrupts, core might be a hint)*/
  if (IS_PENDING_ON_CPU(int_no, core)) {
    setPending(int_no, core);
    return;
  }

  // for common interrupts, gather the pending state of all cpu:
  if (!IS_BANKED_INTERRUPT(int_no))
    for (unsigned int cpui = 0; cpui < n_cores; cpui++)
      if (IS_PENDING_ON_CPU(int_no, cpui)) {
        setPending(int_no, 0/* dummy, since common interrupt */);
        return;
      }

  clearPending(int_no, core);
}

/** Calculate the highest pending interrupt to argument cpu.  Don't check the
  target list here. If it has changed since interrupts became pending, this
  should only affect inactive ones (see PR231-GENC-006924 5.3, section 4.1.1.8).
  @param core the target CPU interface ID */
void
GIC::update_highestpriority(unsigned int core)
{
  /** @todo speed improvement: when an interrupt becomes pending, just take the
      max of previous highest pending interrupt and the new pending interrupt
      instead of recalculating everything over. */

  unsigned int curr_max_priority;    // priority
  unsigned int curr_max_priority_no; // and interrupt id

  /** 1. Calculate the highest pending interrupt */
  curr_max_priority = 0xFFFFFFFF;  // lowest priority
  curr_max_priority_no = 1023;     // Spurious interrupt ID

  for (unsigned int tmpid = 0; tmpid < n_ints; tmpid++) {
    unsigned int prio;
    // check it is pending on argument cpu (core was a target of that
    // interrupt) and enabled (see PR231-GENC-006924 5.3, 3.8.1.11)
    if (!isEnabled(tmpid, core) || !IS_PENDING_ON_CPU(tmpid, core) || !IS_CTR_ENABLED(tmpid, core))
      continue;

    // Active-Pending transactions are not eligible to the HPI (see Note in
    // section 4.2.7 "Highest Pending Interrupt Register" of PRD03-GENC-004392 7.0 page 34).

    // Note: Note in section 4.2.7 of PRD03-GENC-004392 7.0 is not
    // explicit enough, but "active and pending state" is most
    // probably the state of Figure 4.20 Interrupt State Diagram.
    // See also transitionFSM() where the same interpretation is done.
#if 0
    if (IS_ACTIVE_ON_CPU(tmpid, core))
#else
    if ( ( IS_ACTIVE_ON_CPU(tmpid, core) &&
           (!IS_SOFTWARE_INTERRUPT(tmpid) ||
           current_soft_int_active_src[core][tmpid] == current_soft_int_pending_src[core][tmpid]) ) ||
        (!IS_BANKED_INTERRUPT(tmpid) && IS_1N_INTERRUPT(tmpid) && IS_ACTIVE_ON_ANY_CPU(tmpid, core)) )
#endif
      continue;
    prio = getPriority(tmpid, core);
    if (prio < curr_max_priority) {
      curr_max_priority    = prio;
      curr_max_priority_no = tmpid;
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "int %u has prio %#x", tmpid, prio);
#endif
    }
  }

  /** 2. Submit to CPU interface, the new highest priority pending interrupt,
      together with its current priority and its security domain */

  // check the values were actually updated
  if (c_highest_priority[core]    != curr_max_priority    ||
      c_highest_priority_id[core] != curr_max_priority_no ||
      c_hpi_domain[core]          != getDomain(curr_max_priority_no, core)) {
    c_highest_priority[core]    = curr_max_priority;
    c_highest_priority_id[core] = curr_max_priority_no;
    c_hpi_domain[core]          = getDomain(curr_max_priority_no, core);
    c_cpu_interface_edge[core] = true; // will be reset by reader (ie update_cpu_interface())
  }

  /** @todo could gain a bit of speed by getting the domain only once. Here it
      is fetched from registers in IS_CTR_ENABLED() and in the last call */
}


/** updates the active bit register of DISTRIBUTOR.
    @note update of the active priority list in CPU interface is done in
    GIC::readIntAck() and GIC::writeEndOfInt() called from GIC::c_reg_map_access().
    @param int_no the interrupt ID
    @param core */
void
GIC::update_active(unsigned int int_no, unsigned int core)
{
  /** 1. Check if interrupt is active on argument cpu. This case also handles private interrupts. */
  if (IS_ACTIVE_ON_CPU(int_no, core)) {
    setActive(int_no, core);
    return;
  }

  /** 2. for common interrupts, gather the active state of all cpu: */
  if (!IS_BANKED_INTERRUPT(int_no)) {
    for (unsigned int cpui = 0; cpui < n_cores; cpui++)
      if (IS_ACTIVE_ON_CPU(int_no, cpui)) {
        setActive(int_no, core);
        return;
      }
  }

  // otherwise, clear the active bit
  clearActive(int_no, core);
}

/** update the internal "running priority" register
    (c_running_int_priority[], c_running_int_domain[]), which displays
    the highest priority of all the active interrupts in this cpu. The
    programmer's view of this register includes security matching and
    priority translation, which are performed in GIC::c_reg_map_access(). */
void
GIC::update_running(unsigned int core)
{
  c_running_int_priority[core] = max_active_priority(core);
  c_running_int_domain[core] = domain_of_max_active_priority(core);

  // If there exists pending interrupts, preemption condition should be checked again.
  if (!IS_SPURIOUS_INTERRUPT(c_highest_priority_id[core]))
    c_cpu_interface_edge[core] = true;

  // Note: In the case where priority or security changes are
  // reflected to the active interrupts in CPU interfaces, such
  // changes affect the preemption condition. Hence,
  // update_cpu_interface() must be call be it the case the highest
  // priority did not change.
}


/** this method implements the memory mapping of the Distributor:
    - Control register
    - Interrupt Security
    - Enable Set
    - Enable Clear
    - Pending Set
    - Pending Clear
    - Active Bit
    - Priority
    - CPU Target
    - Config
    - Impl defined
    - SWI
    - ID registers
  @param offset the 32bit word offset from the base address where the
                Distributor is mapped.
  @param cpu_id the ID of the Core (since some registers are banked)
  @param domain the security domain (some regs are banked).
  @param side_effect t_debug for debug accesses (= no side effect).
  @returns MX_STATUS_NOMEMORY when accessing reserved area.
           MX_STATUS_OK otherwise.
           (MX_STATUS_ERROR if argument check enabled and bad argument detected).
*/
MxStatus
GIC::d_reg_map_access(MxU32 offset, MxU32 & value, unsigned char strobes,
                      rw_t type, unsigned int cpu_id, int domain, dbg_t side_effect)
{
  MxU32 writevalue = value;

#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "in d_reg_map_access(offset =%#x)", offset);
#endif

  /** 0. Sanity checks */
#ifndef NOCHECK
  if (!IS_VALID_DOMAIN(domain)) {
    gic_msg_fl(LOG_ERROR, "bad domain arg. in reg_map_access()");
    return MX_STATUS_ERROR;
  }
  if (!IS_VALID_CPUID(cpu_id)) {
    gic_msg_fl(LOG_ERROR, "bad cup_id arg. in reg_map_access()");
    return MX_STATUS_ERROR;
  }
#endif

  if (type == t_write && ((strobes & 0xf) == 0)) {
#ifndef NOCHECK
    gic_msg_fl(LOG_WARNING, "empty strobes in "
               "GIC::d_reg_map_access(offset = %#x, value = %#x, strobes = %#x, type = %s, "
               "cpu_id = %u, domain = %s, side_effect = %s)",
               offset, value, strobes, rw_t_2str(type), cpu_id, domain2str(domain),
               side_effect == t_debug ? "t_debug" : "t_nondebug");
#endif
    return MX_STATUS_OK;
  }


  /** 1. Build mask from strobes (write access only) */
  MxU32 strb_mask = (type == t_write) ? byte_strobe2mask(strobes) : 0 /* dummy */;
#ifdef GIC_TRACE
  gic_msg_fl(LOG_TRACE, "strb_mask = %#x, strobes = %#x", strb_mask, (unsigned int)strobes);
#endif

#ifdef GIC_TRACE
#define TRACE_DIST_ACCESS(regname)                                   \
    gic_msg_fl(LOG_TRACE, "%s %s to " regname " register by cpu %u", \
               domain2str(domain), rw_t_2str(type), cpu_id);
#define TRACE_DIST_ACCESS_ID_RANGE(regname, from_id, to_id)          \
    gic_msg_fl(LOG_TRACE, "%s %s to " regname " register by cpu %u (int_id %d .. %d)", \
               domain2str(domain), rw_t_2str(type), cpu_id, from_id, to_id);
#define TRACE_WRITE_VALUE                                      \
    gic_msg_fl(LOG_TRACE, "write value is %#08x", writevalue);

#define TRACE_READ_VALUE                                 \
    gic_msg_fl(LOG_TRACE, "read value is %#08x", value);

#define TRACE_ACCESS_VALUE                                       \
    if (type == t_write)                                        \
      gic_msg_fl(LOG_TRACE, "write value is %#08x", writevalue);\
    else                                                        \
      gic_msg_fl(LOG_TRACE, "read value is %#08x", value);
#else
#define TRACE_DIST_ACCESS(x)
#define TRACE_DIST_ACCESS_ID_RANGE(x, a, b)
#define TRACE_WRITE_VALUE
#define TRACE_READ_VALUE
#define TRACE_ACCESS_VALUE
#endif

  /** 2. Decode address */
  if (offset == CTRL_R_OFF) {
    // *************************** 1. GIC CONTROL ******************************
    TRACE_DIST_ACCESS("GIC CONTROL");
    // domain-banked
    // mask SBZ bits
    if (type == t_write) {

      if (cfgsdisable && IS_SECURE_DOMAIN(domain)) {
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, " -> silently ignored (CFGSDISABLE true)");
#endif
        return MX_STATUS_OK;
      }

      writevalue &= CTRL_R_MASK;
      /* When DISTRIBUTOR has been switched off, no interrupts are send out of the
         distributor.  Also, disabling eg the secure interrupts, imply the highest
         pending interrupt is calculated among all pending non-secure
         interrupt. Therefore, do call update_highestpriority() for all CPUs.*/
      writevalue = NEWVAL_WITH_MASK(gic_ctrl[domain], strb_mask, writevalue);
      TRACE_WRITE_VALUE;

      /** @todo it is assumed that level-sensitive interrupts's pending status depend on the
         distributor being enabled or not. Waiting for confirmation (Cottin - 2007-04-05)*/
      if (writevalue != gic_ctrl[domain]) {
        gic_ctrl[domain] = writevalue;

        // Update pending status of level sensitive shared interrupts
        for (unsigned int int_id = IRQ_BASE_EXT; int_id < n_ints; int_id++)
          if (IS_IMPLEMENTED_INTERRUPT(int_id, 0/* dummy */) && IS_LEVEL_SENSITIVE(int_id, 0 /* dummy */))
            dispatch_event_on_targets(int_id, 0 /* dummy */, EDGE);

        for (unsigned int tmpcore = 0; tmpcore < n_cores; tmpcore++) {
          // Update pending status of level sensitive private interrupts
          for (unsigned int tmpid = 0; tmpid < IRQ_BASE_EXT; tmpid++)
            if (IS_IMPLEMENTED_INTERRUPT(tmpid, tmpcore) && IS_LEVEL_SENSITIVE(tmpid, tmpcore))
              dispatch_event_on_targets(tmpid, tmpcore, EDGE);
          // candidates might have changed...
          update_highestpriority(tmpcore);
          update_cpu_interface(tmpcore);
        }
      }
    } else {
      value = gic_ctrl[domain];
      TRACE_READ_VALUE;
    }

  } else if (offset == GIC_TYPE_R_OFF) {
    //  ***************************  2. GIC TYPE  ****************************
    TRACE_DIST_ACCESS("TYPE");
    // Read Only
    if (type == t_write)
      return MX_STATUS_OK;

    value = GIC_TYPE_R_RST_VAL;
    TRACE_READ_VALUE;

  } else if (offset == DIST_IMPL_ID_R_OFF) {
    //  ***************************  3. DISTRIBUTOR IMPLEMENTER ID ************
    TRACE_DIST_ACCESS("IMPLEMENTER ID");
    // Read Only
    if (type == t_write)
      return MX_STATUS_OK;
    value = DIST_IMPL_ID_R_RST_VAL;
    TRACE_READ_VALUE;

  } else if (offset >= INT_SEC_REG_OFF &&
             offset <  INT_SEC_REG_OFF + INT_SEC_REG_SIZE) {
    //  *************************** 4. INTERRUPT SECURITY Regs  ***************
    MxU64 sub_offset = (offset - INT_SEC_REG_OFF) >> 2;
    unsigned int int_id = (sub_offset * (1024*4)) / INT_SEC_REG_SIZE;
    unsigned int &ref = d_int_sec[(sub_offset >= INT_SEC_REG_BANKED) ? 0:cpu_id][sub_offset];
    unsigned int old_value;

    TRACE_DIST_ACCESS_ID_RANGE("INTERRUPT SECURITY", int_id, int_id + INT_SEC_REG_FIELDNBR);
    TRACE_ACCESS_VALUE;

    // RESTRICTED: when non-secure, no access !
    // (see PR231-GENC-006924 5.2 at section 3.8.1.7)
    // or considered as RESERVED when secure domains are not implemented
    if (IS_UNSECURE_DOMAIN(domain) || !trustzone_enabled) {
      if (type == t_read)
        value = 0;   // reads return 0
      TRACE_ACCESS_VALUE;
      return MX_STATUS_OK;    // non-secure writes are silently ignored
    }

    // mask unimplemented interrupts
    if (type == t_write) {
      unsigned int mask = 0;
      for (unsigned int i = 0; i < INT_SEC_REG_FIELDNBR; i++)
        if (!IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
          mask |= INT_SEC_REG_FIELDMASK << i * INT_SEC_REG_FIELDSIZE;

      writevalue &= ~mask; // write to unimplemented fields are ignored
      TRACE_WRITE_VALUE;
    }

    // LSPI
    if (type == t_write && cfgsdisable) {
      unsigned int mask = 0;
      for (unsigned int i = 0; i < INT_SEC_REG_FIELDNBR; i++)
        if (!IS_LOCKED_INTERRUPT(int_id + i, cpu_id))
          mask |= INT_SEC_REG_FIELDMASK << i * INT_SEC_REG_FIELDSIZE;

      writevalue = NEWVAL_WITH_MASK(ref, mask, writevalue); // write to locked fields are ignored
      TRACE_WRITE_VALUE;
    }

    if (type == t_read) {
      value = ref; // nothing to mask
      TRACE_ACCESS_VALUE;
      return MX_STATUS_OK;
    }


    // ---- For write only ----
    // SIDE-EFFECT:
    // If for instance Non-Secure interrupts are disabled from CONTROL register, a change
    // Secure -> Non-Secure should affect the highest priority pending interrupt
    // which is calculated among enabled interrupts only.
    // get the corresponding word in the PENDING register
    // also, in implementations which reflect priority changes on running interrupt,
    // the preemption condition might be affected.

    // perform write
    old_value = ref;
    writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
    TRACE_WRITE_VALUE;
    ref = writevalue;

#ifdef GIC_TRACE
    for (unsigned int i = 0; i < INT_SEC_REG_FIELDNBR; i++)
      gic_msg_fl(LOG_TRACE, "int %d is %s", int_id + i,
              IS_SECURE_INTERRUPT(int_id + i, cpu_id) ? "SECURE" : "NONSECURE");
#endif

#if !(PENDING_SET_REG_FIELDSIZE == INT_SEC_REG_FIELDSIZE)
#error "PENDING_SET_REG_FIELDSIZE and INT_SEC_REG_FIELDSIZE should be equal"
#endif
#ifdef REFLECT_DOMAINS
    unsigned int active  = d_active_bit[(sub_offset >= ACTIVE_BIT_REG_BANKED) ? 0 : cpu_id][sub_offset];
#endif
    unsigned int pending = d_pending[(sub_offset >= PENDING_SET_REG_BANKED) ? 0 : cpu_id][sub_offset];
    // the set of pending interrupts whose security status has been modified
#ifdef REFLECT_DOMAINS
    unsigned int modified = (ref ^ old_value) & (pending | active);
#else
    unsigned int modified = (ref ^ old_value) & pending;
#endif

    if (modified)
     for (unsigned tmpcpu = 0; tmpcpu < n_cores; tmpcpu++) { // --- for all cpu ---
#ifdef REFLECT_DOMAINS
        bool has_active_int   = false;
#endif
        bool has_pending_int = false;
        for (unsigned int i = 0; i < INT_SEC_REG_FIELDNBR; i++) {
          if (modified & (1 << i)) { // a  pending interrupt whose security status has been modified
            if (IS_PENDING_ON_CPU(int_id + i, tmpcpu))
              has_pending_int = true;
#ifdef REFLECT_DOMAINS
            if (IS_ACTIVE_ON_CPU(int_id + i, tmpcpu))
              has_active_int = true;
#endif
          }
        }
        if (has_pending_int)
          update_highestpriority(tmpcpu);            // recalculate the highest priority interrupt
#ifdef REFLECT_DOMAINS
        /* If programming the security register takes immediate effect
           on active interrupts or not (which is IMPLEMENTATION
           DEFINED, see PR231-GENC-006924 5.8 section 4.1.9. and 3.6.1),
           the "running priority" must be recalculated. */
        if (has_active_int)
          update_running(tmpcpu);
#endif
        update_cpu_interface(tmpcpu);
      } // -- end of loop on cpu ---

  } else if (offset >=  ENABLE_SET_REG_OFF &&
             offset <   ENABLE_SET_REG_OFF +  ENABLE_SET_REG_SIZE) {
    //  *************************** 5. ENABLE SET  ***************************
    MxU64 sub_offset = (offset - ENABLE_SET_REG_OFF) >> 2;
    unsigned int int_id = (sub_offset * (1024*4)) / ENABLE_SET_REG_SIZE;
    unsigned int &ref = d_enable[(sub_offset >= ENABLE_SET_REG_BANKED) ? 0:cpu_id][sub_offset];
    MxU32 old_value;

    TRACE_DIST_ACCESS_ID_RANGE("ENABLE SET", int_id, int_id + 31);

    // mask unimplemented interrupts
    if (type == t_write) {
      TRACE_WRITE_VALUE;
      unsigned int mask = 0;
      for (unsigned int i = 0; i < ENABLE_SET_REG_FIELDNBR; i++)
        if (!IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
          mask |= ENABLE_SET_REG_FIELDMASK << i * ENABLE_SET_REG_FIELDSIZE;

      writevalue &= ~mask; // write to unimplemented fields are ignored
      TRACE_WRITE_VALUE;
    }

    // LSPI
    if (type == t_write && cfgsdisable) {
      unsigned int mask = 0;
      for (unsigned int i = 0; i < ENABLE_SET_REG_FIELDNBR; i++)
        if (!IS_LOCKED_INTERRUPT(int_id + i, cpu_id))
          mask |= ENABLE_SET_REG_FIELDMASK << i * ENABLE_SET_REG_FIELDSIZE;

      writevalue = NEWVAL_WITH_MASK(ref, mask, writevalue); // write to locked fields are ignored
      TRACE_WRITE_VALUE;
    }


    // set read value
    if (type == t_read) {
      value = ref; // we are going to mask a few things
      TRACE_READ_VALUE;
    }
    // Software interrupts are always permanently enabled (see PRD03-GENC-004392 7.0 section 4.1.11 page 24)
    if (type == t_write && int_id == 0) {// <- id == 0 just for speed optimisation
      unsigned int mask_set_soft_int = 0;
      for (unsigned int i = 0; i < ENABLE_SET_REG_FIELDNBR; i++)
        if (IS_SOFTWARE_INTERRUPT(int_id + i))
          mask_set_soft_int |= ENABLE_SET_REG_FIELDMASK << i * ENABLE_SET_REG_FIELDSIZE;

      writevalue |= mask_set_soft_int; // write to software ints fields
      TRACE_WRITE_VALUE;
    }

    // Unsecure read to the field of a secure interrupt return 0 and
    // writes are ignored for those fields (not for the whole
    // register, see PR231-GENC-006924 5.2, section 3.3).
    if (trustzone_enabled && IS_UNSECURE_DOMAIN(domain)) {
      unsigned int mask_secure_int = 0xFFFFFFFF;
      for (unsigned int i = 0; i < ENABLE_SET_REG_FIELDNBR; i++)
        if (IS_SECURE_INTERRUPT(int_id + i, cpu_id))
          mask_secure_int &= ~(ENABLE_SET_REG_FIELDMASK << i * ENABLE_SET_REG_FIELDSIZE);

      if (type == t_write) {
        writevalue &= mask_secure_int; // cannot write to secure ints fields
        TRACE_WRITE_VALUE;
      } else {
        value      &= mask_secure_int; // read to secure field returns 0
        TRACE_READ_VALUE;
      }
    }

    if (t_read == type)
      return MX_STATUS_OK;

    // ----- for write only -----
    // already set flags are kept set
    writevalue |= ref;
    old_value = ref;
    writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
    TRACE_WRITE_VALUE;
    ref = writevalue;

    // SIDE-EFFECT:
    // 1. (Re)setting the enable flag of pending interrupts affects the
    //   highest priority pending interrupt on CPU on which it is pending.
    // 2. Level sensitive interrupts which are asserted by the
    //   peripheral may be triggered when their enable flag is set.

    // get the corresponding word in the PENDING register
#if !(PENDING_SET_REG_FIELDSIZE == ENABLE_SET_REG_FIELDSIZE)
#error "PENDING_SET_REG_FIELDSIZE and ENABLE_SET_REG_FIELDSIZE should be equal"
#endif
    unsigned int pending = d_pending[(sub_offset >= PENDING_SET_REG_BANKED) ? 0 : cpu_id][sub_offset];
    // the set of pending interrupts whose enable flag has been modified
    unsigned int modified = (old_value ^ writevalue);
    unsigned int pending_and_modified = modified & pending;

    for (unsigned int i = 0; i < ENABLE_SET_REG_FIELDNBR; i++)
      if (pending_and_modified & (1 << i))  // a  pending interrupt whose enable flag has been modified
        for (unsigned tmpcpu = 0; tmpcpu < n_cores; tmpcpu++)
          if (IS_PENDING_ON_CPU(int_id + i, tmpcpu)) { // for all CPU it is pending on,
            update_highestpriority(tmpcpu);          // recalculate the highest priority interrupt
            update_cpu_interface(tmpcpu);
          }
  } else if (offset >=  ENABLE_CLEAR_REG_OFF &&
             offset <   ENABLE_CLEAR_REG_OFF +  ENABLE_CLEAR_REG_SIZE) {
    //  *************************** 6. ENABLE CLEAR  ***************************
    MxU64 sub_offset = (offset - ENABLE_CLEAR_REG_OFF) >> 2;
    unsigned int int_id = (sub_offset * (1024*4)) / ENABLE_CLEAR_REG_SIZE;
    unsigned int &ref = d_enable[(sub_offset >= ENABLE_CLEAR_REG_BANKED) ? 0:cpu_id][sub_offset];
    MxU32 old_value;

    TRACE_DIST_ACCESS_ID_RANGE("ENABLE CLEAR", int_id, int_id + 31);

    // mask unimplemented interrupts
    if (type == t_write) {
      unsigned int mask = 0;
      for (unsigned int i = 0; i < ENABLE_CLEAR_REG_FIELDNBR; i++)
        if (!IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
          mask |= ENABLE_CLEAR_REG_FIELDMASK << i * ENABLE_CLEAR_REG_FIELDSIZE;

      writevalue &= ~mask; // write to unimplemented fields are ignored
      TRACE_WRITE_VALUE;
    }

    // LSPI
    if (type == t_write && cfgsdisable) {
      unsigned int mask = 0;
      for (unsigned int i = 0; i < ENABLE_CLEAR_REG_FIELDNBR; i++)
        if (!IS_LOCKED_INTERRUPT(int_id + i, cpu_id))
          mask |= ENABLE_CLEAR_REG_FIELDMASK << i * ENABLE_CLEAR_REG_FIELDSIZE;

      writevalue = NEWVAL_WITH_MASK(ref, mask, writevalue); // write to locked fields are ignored
      TRACE_WRITE_VALUE;
    }


    if (type == t_read) {
      value = ref; // we are going to mask a few things
      TRACE_READ_VALUE;
    }
    //Software interrupts are always permanently enabled (see PR231-GENC-006924 5.3 section 3.8.1.11)
    if (type == t_write && int_id == 0) {
      unsigned int mask_set_soft_int = 0;
      for (unsigned int i = 0; i < ENABLE_CLEAR_REG_FIELDNBR; i++)
        if (IS_SOFTWARE_INTERRUPT(int_id + i))
          mask_set_soft_int |= ENABLE_CLEAR_REG_FIELDMASK << i * ENABLE_CLEAR_REG_FIELDSIZE;

        writevalue &= ~mask_set_soft_int; // write to software ints fields
    }

    // Unsecure read to the field of a secure interrupt return 0 and
    // writes are ignored for those fields (not for the whole
    // register, which is not explicit in PR231-GENC-006924 5.2, section 3.3).
    if (trustzone_enabled && IS_UNSECURE_DOMAIN(domain)) {
      unsigned int mask_secure_int = 0xFFFFFFFF;
      for (unsigned int i = 0; i < ENABLE_CLEAR_REG_FIELDNBR; i++)
        if (IS_SECURE_INTERRUPT(int_id + i, cpu_id))
          mask_secure_int &= ~(ENABLE_CLEAR_REG_FIELDMASK << i * ENABLE_CLEAR_REG_FIELDSIZE);

      if (type == t_write) {
        writevalue &= mask_secure_int; // cannot write to secure ints fields
        TRACE_WRITE_VALUE;
      } else {
        value      &= mask_secure_int;      // read to secure field return 0
        TRACE_READ_VALUE;
      }
    }

    if (t_read == type)
      return MX_STATUS_OK;

    // ---- For write only ----
    // already cleared flags are kept cleared
    writevalue = ~writevalue & ref;
    old_value = ref;
    writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
    TRACE_WRITE_VALUE;
    ref = writevalue;

    // SIDE-EFFECT:
    // recalculate the highest pending interrupt for all CPU on which was pending a disabled interrupt.

    // Get the corresponding word in the PENDING register
#if !(PENDING_SET_REG_FIELDSIZE == ENABLE_CLEAR_REG_FIELDSIZE)
#error "PENDING_SET_REG_FIELDSIZE and ENABLE_CLEAR_REG_FIELDSIZE should be equal"
#endif
    unsigned int pending = d_pending[(sub_offset >= PENDING_SET_REG_BANKED) ? 0 : cpu_id][sub_offset];
    // the set of pending interrupts whose enable flag has been modified is:
    unsigned int modified = (old_value ^ writevalue) & pending;
    for (unsigned int i = 0; i < ENABLE_CLEAR_REG_FIELDNBR; i++)
      if (modified & (1 << i))  // a  pending interrupt whose enable flag has been modified
        for (unsigned tmpcpu = 0; tmpcpu < n_cores; tmpcpu++)
          if (IS_PENDING_ON_CPU(int_id + i, tmpcpu)) { // for all CPU it is pending on,
            update_highestpriority(tmpcpu);            // recalculate the highest priority interrupt
            update_cpu_interface(tmpcpu);              // And if HPI changed, update CPU interface.
          }

  } else if (offset >= PENDING_SET_REG_OFF &&
             offset <  PENDING_SET_REG_OFF + PENDING_SET_REG_SIZE) {
    //  *************************** 7. PENDING SET  ***************************
    MxU64 sub_offset = (offset - PENDING_SET_REG_OFF) >> 2;
    // interrupt id of the first field (little endian)
    unsigned int int_id = (sub_offset * (1024*4)) / PENDING_SET_REG_SIZE;
    unsigned int &ref = d_pending[(sub_offset >= PENDING_SET_REG_BANKED) ? 0: cpu_id][sub_offset];
    MxU32 old_value = ref;

    TRACE_DIST_ACCESS_ID_RANGE("PENDING SET", int_id, int_id + 31);
    // note the pending state as read in d_pending[][] is derived from
    // the state machines coreFSM[][], the transitions of which are
    // actuated in GIC::transitionFSM(). When writing to this
    // register, d_pending[][] is updated from GIC::transitionFSM().

    if (type == t_write) {
      // mask unimplemented interrupts
      TRACE_WRITE_VALUE;
      unsigned int mask = 0;
      for (unsigned int i = 0; i < PENDING_SET_REG_FIELDNBR; i++)
        if (!IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
          mask |= PENDING_SET_REG_FIELDMASK << i * PENDING_SET_REG_FIELDSIZE;

      writevalue &= ~mask; // write to unimplemented fields are ignored
      TRACE_WRITE_VALUE;

      // LSPI
      if (cfgsdisable) {
        for (unsigned int i = 0; i < PENDING_SET_REG_FIELDNBR; i++)
          if (!IS_LOCKED_INTERRUPT(int_id + i, cpu_id))
            mask |= PENDING_SET_REG_FIELDMASK << i * PENDING_SET_REG_FIELDSIZE;

        writevalue = NEWVAL_WITH_MASK(ref, mask, writevalue); // write to locked fields are ignored
        TRACE_WRITE_VALUE;
      }
      // Pending flag for Software interrupts is read only (see PRD03-GENC-004392 7.0, section 4.1.12)
      if (int_id == 0) {
        unsigned int mask_set_soft_int = 0;
        for (unsigned int i = 0; i < PENDING_SET_REG_FIELDNBR; i++)
          if (IS_SOFTWARE_INTERRUPT(int_id + i))
            mask_set_soft_int |= PENDING_SET_REG_FIELDMASK << i * PENDING_SET_REG_FIELDSIZE;

        writevalue &= ~mask_set_soft_int; // write to software ints fields ignored
        TRACE_WRITE_VALUE;
      }
    } else {
      value = ref;
      TRACE_READ_VALUE;
      for (unsigned int i = 0;  i < PENDING_SET_REG_FIELDNBR; i++)
        if (pseudo_pendingFSM[int_id + i])
          value |= 1 << i;
      TRACE_READ_VALUE;
      // we are going to mask a few things
    }

    // Unsecure read to the field of a secure interrupt returns 0 and
    // writes are ignored for those fields (not for the whole
    // register, which is not explicit in PR231-GENC-006924 5.2, section 3.3).
    if (trustzone_enabled && IS_UNSECURE_DOMAIN(domain)) {
      unsigned int mask_secure_int = 0xFFFFFFFF;
      for (unsigned int i = 0; i < PENDING_SET_REG_FIELDNBR; i++)
        if (IS_SECURE_INTERRUPT(int_id + i, cpu_id))
          mask_secure_int &= ~(PENDING_SET_REG_FIELDMASK << i * PENDING_SET_REG_FIELDSIZE);

      if (type == t_write) {
        writevalue &= mask_secure_int; // cannot write to secure ints fields
        TRACE_WRITE_VALUE;
      } else {
        value      &= mask_secure_int; // read to secure field returns 0
        TRACE_READ_VALUE;
      }
    }

    if (type == t_read)
      return MX_STATUS_OK; // nothing to mask anymore, no side effect.

    // ------ For write accesses --- //

    // Patch: take care of interrupts with an empty list of targets. They can be set pending as well.
#ifndef INTERRUPTS_WITH_EMPTY_TARGET_LIST_CANNOT_BECOME_PENDING
    for (unsigned int i = 0;  i < PENDING_SET_REG_FIELDNBR; i++)
      if ((writevalue & 1 << i) && getCPUTargets(int_id + i, cpu_id) == 0)
        pseudo_pendingFSM[int_id + i] = true;
#endif
    // already set flags will be kept
    writevalue |= old_value;
    TRACE_WRITE_VALUE;
    writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
    TRACE_WRITE_VALUE;

    // SIDE-EFFECT: For a write, update the state machine of each interrupt on each core
    for (unsigned int i = 0;  i < PENDING_SET_REG_FIELDNBR; i++)
      if (BIT(writevalue, i))
        writeSetPending(int_id + i, cpu_id);

  }  else if (offset >= PENDING_CLEAR_REG_OFF &&
              offset <  PENDING_CLEAR_REG_OFF + PENDING_CLEAR_REG_SIZE) {
    //  *************************** 8. PENDING CLEAR  ***************************
    MxU64 sub_offset = (offset - PENDING_CLEAR_REG_OFF) >> 2;
    unsigned int int_id = (sub_offset * (1024*4)) / PENDING_CLEAR_REG_SIZE;
    MxU32 &ref = d_pending[(sub_offset >= PENDING_CLEAR_REG_BANKED) ? 0: cpu_id][sub_offset];
    MxU32 old_value = ref;

    TRACE_DIST_ACCESS_ID_RANGE("PENDING CLEAR", int_id, int_id + 31);

    if (type == t_write) {
      TRACE_WRITE_VALUE;
      // mask unimplemented interrupts
      unsigned int mask = 0;
      for (unsigned int i = 0; i < PENDING_CLEAR_REG_FIELDNBR; i++)
        if (!IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
          mask |= PENDING_CLEAR_REG_FIELDMASK << i * PENDING_CLEAR_REG_FIELDSIZE;
      writevalue &= ~mask; // write to unimplemented fields are ignored
      TRACE_WRITE_VALUE;

      // LSPI
      if (cfgsdisable) {
        for (unsigned int i = 0; i < PENDING_CLEAR_REG_FIELDNBR; i++)
          if (!IS_LOCKED_INTERRUPT(int_id + i, cpu_id))
            mask |= PENDING_CLEAR_REG_FIELDMASK << i * PENDING_CLEAR_REG_FIELDSIZE;

        writevalue = NEWVAL_WITH_MASK(old_value, mask, writevalue); // write to locked fields are ignored
        TRACE_WRITE_VALUE;
      }

      // Pending flag for Software interrupts is read only (see PRD03-GENC-004392 7.0, section 4.1.12)
      if (int_id == 0) {
        unsigned int mask_set_soft_int = 0;
        for (unsigned int i = 0; i < PENDING_CLEAR_REG_FIELDNBR; i++)
          if (IS_SOFTWARE_INTERRUPT(int_id + i))
            mask_set_soft_int |= PENDING_CLEAR_REG_FIELDMASK << i * PENDING_CLEAR_REG_FIELDSIZE;
        writevalue &= ~mask_set_soft_int; // write to software ints fields ignored
      TRACE_WRITE_VALUE;
      }
    } else {
      value = ref;
      TRACE_READ_VALUE;
      for (unsigned int i = 0;  i < PENDING_SET_REG_FIELDNBR; i++)
        if (pseudo_pendingFSM[int_id + i])
          value |= 1 << i;
      TRACE_READ_VALUE;
    }
    // Unsecure read to the field of a secure interrupt return 0 and
    // writes are ignored for those fields (not for the whole
    // register, which is not explicit in PR231-GENC-006924 5.2, section 3.3).
    if (trustzone_enabled && IS_UNSECURE_DOMAIN(domain)) {
      unsigned int mask_secure_int = 0xFFFFFFFF;
      for (unsigned int i = 0; i < PENDING_CLEAR_REG_FIELDNBR; i++)
        if (IS_SECURE_INTERRUPT(int_id + i, cpu_id))
          mask_secure_int &= ~(PENDING_CLEAR_REG_FIELDMASK << i * PENDING_CLEAR_REG_FIELDSIZE);

      if (type == t_write) {
        writevalue &= mask_secure_int; // cannot write to secure ints fields
        TRACE_WRITE_VALUE;
      } else {
        value      &= mask_secure_int; // read to secure field return 0
        TRACE_READ_VALUE;
      }
    }

    // For a read, nothing to do anymore.
    if (type == t_read)
      return MX_STATUS_OK;

    // ------ For write accesses --- //
#ifndef PENDING_STATUS_OF_INTERRUPTS_WITH_EMPTY_TARGET_LIST_CANNOT_BE_CLEAR
    // Patch: take care of pending interrupts with an empty list of targets.
    for (unsigned int i = 0;  i < PENDING_CLEAR_REG_FIELDNBR; i++)
      if ((writevalue & 1 << i) && getCPUTargets(int_id + i, cpu_id) == 0)
        pseudo_pendingFSM[int_id + i] = false;
#endif

    // already cleared flags will be kept cleared.
    writevalue = ~writevalue & old_value;
    TRACE_WRITE_VALUE;
    writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
    TRACE_WRITE_VALUE;

    // SIDE-EFFECT: For a write, update the state machine of each interrupt on each core
    MxU32 modified = old_value ^ writevalue;
    for (unsigned int i = 0;  i < PENDING_CLEAR_REG_FIELDNBR; i++)
      if (BIT(modified, i))
        writeClearPending(int_id + i, cpu_id);
    // NOTE: calling writeClrearPending() updates d_pending[].

  } else if (offset >= ACTIVE_BIT_REG_OFF &&
             offset <  ACTIVE_BIT_REG_OFF + ACTIVE_BIT_REG_SIZE) {
    // ************************* 9. ACTIVE BIT REG *****************************
    MxU64 sub_offset = (offset - ACTIVE_BIT_REG_OFF) >> 2;

#ifdef GIC_TRACE
    unsigned int int_id = (sub_offset * (1024*4)) / ACTIVE_BIT_REG_SIZE;
    TRACE_DIST_ACCESS_ID_RANGE("ACTIVE BIT", int_id, int_id + 31);
#endif
    // Read Only
    if (type == t_write)
      return MX_STATUS_OK;
    /** @todo maybe read write accesses to READONLY registers (like ACTIVE BIT) should raise a warning*/

    value = d_active_bit[(sub_offset >= ACTIVE_BIT_REG_BANKED) ? 0:cpu_id][sub_offset];
    TRACE_READ_VALUE;

    // NO SIDE EFFECTS

  } else if (offset >= PRIORITY_REG_OFF &&
             offset <  PRIORITY_REG_OFF + PRIORITY_REG_SIZE) {
    // *************************** 10. PRIORITY ***************************
    MxU64 sub_offset = (offset - PRIORITY_REG_OFF) >> 2;
    unsigned int int_id = (sub_offset * (1024*4)) / PRIORITY_REG_SIZE;
    unsigned int &ref = d_priority[(sub_offset >= PRIORITY_REG_BANKED) ? 0 : cpu_id][sub_offset];

    TRACE_DIST_ACCESS_ID_RANGE("PRIORITY", int_id, int_id + 3);

    if (type == t_read) {
      value = ref;  // we are going to mask a few things
      TRACE_READ_VALUE;
    }

    // mask unimplemented interrupts
    if (type == t_write) {
      TRACE_WRITE_VALUE;
      unsigned int mask = 0;
      for (unsigned int i = 0; i < PRIORITY_REG_FIELDNBR; i++)
        if (!IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
          mask |= PRIORITY_REG_FIELDMASK << i * PRIORITY_REG_FIELDSIZE;

      writevalue &= ~mask; // write to unimplemented fields are ignored
      TRACE_WRITE_VALUE;
    }

    // LSPI
    if (type == t_write && cfgsdisable) {
      TRACE_WRITE_VALUE;
      unsigned int mask = 0;
      for (unsigned int i = 0; i < PRIORITY_REG_FIELDNBR; i++)
        if (!IS_LOCKED_INTERRUPT(int_id + i, cpu_id))
          mask |= PRIORITY_REG_FIELDMASK << i * PRIORITY_REG_FIELDSIZE;

      writevalue = NEWVAL_WITH_MASK(ref, mask, writevalue); // write to locked fields are ignored
      TRACE_WRITE_VALUE;
    }

    // translation of NonSecure accesses
    //(see PR231-GENC-006924 5.2 at section 3.7.3.3, table 3-1, page 10)
    // A similar translation is performed in GIC::c_reg_map_access() for the
    // priority mask register.
    if (trustzone_enabled && IS_UNSECURE_DOMAIN(domain)) {
      if (type == t_read) { // READ
        for (unsigned int i = 0; i < PRIORITY_REG_FIELDNBR; i++) {
          unsigned int field = GETFIELD(value, i * PRIORITY_REG_FIELDSIZE, PRIORITY_REG_FIELDSIZE);
          field = (IS_SECURE_INTERRUPT(int_id + i, cpu_id) ? 0 : // read 0 for secure interrupts
                   (field << 1) & PRIO_MASK_R_MASK); // translation to NS read
          SETFIELD(value, i * PRIORITY_REG_FIELDSIZE, PRIORITY_REG_FIELDSIZE, field);
        }
      } else {             // WRITE
        for (unsigned int i = 0; i < PRIORITY_REG_FIELDNBR; i++) {
          unsigned int field = GETFIELD(value, i * PRIORITY_REG_FIELDSIZE, PRIORITY_REG_FIELDSIZE);
          field = (IS_SECURE_INTERRUPT(int_id + i, cpu_id) ?
                   GETFIELD(ref, i * PRIORITY_REG_FIELDSIZE, PRIORITY_REG_FIELDSIZE) : // do not modify secure interrupt's priority
                   (field >> 1 | 0x80) & PRIO_MASK_R_MASK); // translation for a NS write
          SETFIELD(writevalue, i * PRIORITY_REG_FIELDSIZE, PRIORITY_REG_FIELDSIZE, field);
        }
      }
    } else { // SECURE access (or no Trustzone impl.)
      // for secure views, nothing particular to do.
    }

    if (type == t_read)
      return MX_STATUS_OK;

    // ---- for write only ---
    // SIDE-EFFECTS:
    // the masking of the value (see PR231-GENC-006924 5.2 section 3.7.1)

    // perform write
    MxU32 old_value = ref;
    writevalue &= PRIORITY_REG_MASK;
    TRACE_WRITE_VALUE;
    writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
    TRACE_WRITE_VALUE;
    ref = writevalue;

    // Modifying priority of pending interrupts implies recalculating
    // the Highest Priority Interrupt of each of its target CPU
    // interfaces.  Also, for implementations which reflect priority
    // changes on active interrupts, the "running priority register"
    // must be updated and also the whole CPU interface
    // (ie update_cpu_interface()), since preemption condition is
    // affected (see PR231-GENC-006924 5.2 section 3.8.1.9 and 3.6.1).

    unsigned int modified = old_value ^ writevalue;

    if (modified)
      for (unsigned int tmpcpu = 0; tmpcpu < n_cores; tmpcpu++) { //--- for all cpu ---
#ifdef REFLECT_PRIORITIES
        bool has_active_int = false;
#endif
        bool has_pending_int = false;
        // check if we modified an interrupt pending or active on cpu.
        for (unsigned int i = 0; i < PRIORITY_REG_FIELDNBR; i++) {
          if (modified & (((1 << PRIORITY_REG_FIELDSIZE) - 1) << i * PRIORITY_REG_FIELDSIZE)) {
            if (IS_PENDING_ON_CPU(int_id + i, tmpcpu))
              has_pending_int = true;
#ifdef REFLECT_PRIORITIES
            if (IS_ACTIVE_ON_CPU(int_id + i, tmpcpu))
              has_active_int = true;
#endif
          }
        }
        if (has_pending_int)
          update_highestpriority(tmpcpu);
#ifdef REFLECT_PRIORITIES
        /* If programming the priority register takes immediate effect
           on active interrupts or not (which is IMPLEMENTATION
           DEFINED, see PR231-GENC-006924 5.8 section 4.1.9. and 3.6.1),
           the "running priority" must be recalculated. */
        if (has_active_int)
          update_running(tmpcpu); // update internal value of "running priority" register
#endif
        update_cpu_interface(tmpcpu);
      } // -- end of loop on cpu ---

  } else if (offset >= TARGETS_REG_OFF &&
             offset <  TARGETS_REG_OFF +  TARGETS_REG_SIZE) {
    // **************************** 11. CPU Target *****************************
    MxU64 sub_offset = (offset -  TARGETS_REG_OFF) >> 2;
    unsigned int int_id = (sub_offset * (1024*4)) / TARGETS_REG_SIZE;
    unsigned int &ref = d_cpu_targets[sub_offset];

    TRACE_DIST_ACCESS_ID_RANGE("CPU TARGET", int_id, int_id + 3);

    // Special Case: mono processor implementation:
    if (n_cores == 1) {
      if (type == t_read) {
        value = 0; // reads return 0
        TRACE_READ_VALUE;
      }
      return MX_STATUS_OK;      // and writes are ignored
    }

    // Banked interrupts are read-only (see PR231-GENC-006924 3.7 section 4.1.10)
    if (sub_offset < TARGETS_REG_BANKED && type == t_write) {
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "write value is %#08x but private ints are read-only", writevalue);
#endif
      return MX_STATUS_OK; // Writes to banked interrupt config registers are ignored.
    }

    if (type == t_read) {
      if (sub_offset < TARGETS_REG_BANKED) {
        unsigned int tmp_val = 0;
        for (unsigned int i = 0; i < TARGETS_REG_FIELDNBR; i++)
          if (IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
            tmp_val |= (1 << cpu_id) << i * TARGETS_REG_FIELDSIZE;
        value = tmp_val;// reads return the cpu itself
        TRACE_READ_VALUE;
      } else {
        value = ref; // we are going to mask a few things if trustzone is implemented
        TRACE_READ_VALUE;
      }
    }

    // mask unimplemented interrupts
    {
      unsigned int mask = 0;
      for (unsigned int i = 0; i < TARGETS_REG_FIELDNBR; i++)
        if (!IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
          mask |= TARGETS_REG_FIELDMASK << i * TARGETS_REG_FIELDSIZE;
      if (type == t_read) {
        value &= ~mask; // unimplemented fields read as zero
        TRACE_READ_VALUE;
      } else {
        writevalue &= ~mask; // write to unimplemented fields are ignored
        TRACE_WRITE_VALUE;
      }
    }

    // LSPI
    if (type == t_write && cfgsdisable) {
      unsigned int mask = 0;
      for (unsigned int i = 0; i < TARGETS_REG_FIELDNBR; i++)
        if (!IS_LOCKED_INTERRUPT(int_id + i, cpu_id))
          mask |= TARGETS_REG_FIELDMASK << i * TARGETS_REG_FIELDSIZE;

      writevalue = NEWVAL_WITH_MASK(ref, mask, writevalue); // write to locked fields are ignored
      TRACE_WRITE_VALUE;
    }


    // Unsecure read to the field of a secure interrupt returns 0 and
    // writes are ignored for those fields (not for the whole
    // register, which is not explicit in PR231-GENC-006924 5.2, section 3.3).
    if (trustzone_enabled && IS_UNSECURE_DOMAIN(domain)) {
      unsigned int mask_secure_int = 0xFFFFFFFF;
      for (unsigned int i = 0; i < TARGETS_REG_FIELDNBR; i++)
        if (IS_SECURE_INTERRUPT(int_id + i, cpu_id))
          mask_secure_int &= ~(TARGETS_REG_FIELDMASK << i * TARGETS_REG_FIELDSIZE);

      if (type == t_write) {
        // cannot modify fields of secure ints.
        writevalue = NEWVAL_WITH_MASK(ref, mask_secure_int, writevalue);
        TRACE_WRITE_VALUE;
      } else {
        value      &= mask_secure_int; // read to secure field return 0
        TRACE_READ_VALUE;
      }
    }

    // For a read, nothing to do anymore.
    if (type == t_read)
      return MX_STATUS_OK;


    // -------- For write only ------------//
    // Mask SBZ bits (to fit the real number of cores)
    writevalue &= TARGETS_REG_MASK;
    // remember previous target list
    unsigned int old_value = ref;
    // strobes
    writevalue = NEWVAL_WITH_MASK(old_value, strb_mask, writevalue);
    TRACE_WRITE_VALUE;
    // perform write
    ref = writevalue;

#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, "updated cpu targets");
#endif

    // SIDE EFFECT:
    // For each (level-sensitive) interrupt whose field has been set, update the
    // state machine on each of its targets (inactive level-s interrupts are
    // sensitive to target changes, see transition A in GIC::transitionFSM()).
    for (unsigned int i = 0; i < TARGETS_REG_FIELDNBR; i++) {
#ifndef PENDING_FLOP_CPU_TARGET_SENSITIV
      if (!IS_LEVEL_SENSITIVE(int_id + i, 0/*dummy since shared interrupt*/))
        continue;
#endif

      unsigned int old_target_list = GETFIELD(old_value , i * TARGETS_REG_FIELDSIZE, TARGETS_REG_FIELDSIZE);
      unsigned int new_target_list = GETFIELD(writevalue, i * TARGETS_REG_FIELDSIZE, TARGETS_REG_FIELDSIZE);
      if (old_target_list != new_target_list) {

        // A pending interrupt is still seen as pending in PENDING CLEAR and PENDING SET
        // registers, whatever its target list is.
        if (new_target_list == 0)
          pseudo_pendingFSM[int_id + i] = IS_STICKY_PENDING(int_id + i, 0/*dummy*/);

        for (unsigned int tmpcpu = 0; tmpcpu < n_cores; tmpcpu ++)
          if (new_target_list & (1 << tmpcpu) && !(old_target_list & (1 << tmpcpu))) {
#ifdef GIC_TRACE
            gic_msg_fl(LOG_TRACE, "CPU %u is new target of interrupt %u", tmpcpu, int_id + i);
#endif
            transitionFSM(tmpcpu, int_id + i, VALID_TRG);
          } else if (old_target_list & (1 << tmpcpu) && !(new_target_list & (1 << tmpcpu))) {
#ifdef GIC_TRACE
            gic_msg_fl(LOG_TRACE, "CPU %u is no more target of interrupt %u", tmpcpu, int_id + i);
#endif
            transitionFSM(tmpcpu, int_id + i, INVALID_TRG);
          }

        // A non empty target list has been set, the pending status (if any) has been
        // transferred to each target core's FSM.  Clear the pseudo one.
        if (old_target_list == 0)
          pseudo_pendingFSM[int_id + i] = false;
      }
    }

  } else if (offset >= CONFIGURATION_REG_OFF &&
             offset <  CONFIGURATION_REG_OFF + CONFIGURATION_REG_SIZE) {
    // *********************** 12. CONFIGURATION REG ***********************
    MxU64 sub_offset = (offset - CONFIGURATION_REG_OFF) >> 2;
    unsigned int int_id = (sub_offset * (1024*4)) / CONFIGURATION_REG_SIZE;
    unsigned int &ref = d_config[(sub_offset >= INT_SEC_REG_BANKED) ? 0:cpu_id][sub_offset];


    TRACE_DIST_ACCESS_ID_RANGE("CONFIGURATION", int_id, int_id + 15);

    // Banked interrupt config registers are read-only (see PR231-GENC-006924 3.7 section 4.1.8)
    if (sub_offset < CONFIGURATION_REG_BANKED && type == t_write) {
#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE, "write value is %#08x but private ints are read-only", writevalue);
#endif
      return MX_STATUS_OK; // Writes to banked interrupt config registers are ignored.
    }

    if (sub_offset == 0) {// the register for Software interrupts [0-15]
      value = 0xAAAAAAAA; //IT[1:0] reads 0b10
      TRACE_READ_VALUE;
    } else {
      // Force IT[0] to 1 for Peripheral (Private & Shared) interrupts.
      if (type == t_write) {
        writevalue |= 0x55555555;
        TRACE_WRITE_VALUE;
      } else {
        value = ref | 0x55555555;
        TRACE_READ_VALUE;
      }
    }

    // Unsecure read to the field of a secure interrupt return 0 and
    // writes are ignored for those fields (not for the whole
    // register,see PR231-GENC-006924 5.2, section 3.3).
    if (trustzone_enabled && IS_UNSECURE_DOMAIN(domain)) {
      unsigned int mask_secure_int = 0xFFFFFFFF;
      unsigned int int_id  = (sub_offset * (1024*4)) / CONFIGURATION_REG_SIZE;

      for (unsigned int i = 0; i < CONFIGURATION_REG_FIELDNBR; i++) {
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "int %d is %s", int_id + i, IS_SECURE_INTERRUPT(int_id + i, cpu_id) ? "SECURE" : "NONSECURE");
#endif
        if (IS_SECURE_INTERRUPT(int_id + i, cpu_id)) {
          mask_secure_int &= ~(CONFIGURATION_REG_FIELDMASK << i * CONFIGURATION_REG_FIELDSIZE);
        }
      }

      if (type == t_write) {
        // cannot modify fields of secure ints.
        writevalue = NEWVAL_WITH_MASK(ref, mask_secure_int, writevalue);
        TRACE_WRITE_VALUE;
      } else {
        value      &= mask_secure_int; // read to secure field return 0
        TRACE_READ_VALUE;
      }
    }

    // mask unimplemented interrupts
    unsigned int mask = 0;
    for (unsigned int i = 0; i < CONFIGURATION_REG_FIELDNBR; i++)
      if (!IS_IMPLEMENTED_INTERRUPT(int_id + i, cpu_id))
        mask |= CONFIGURATION_REG_FIELDMASK << i * CONFIGURATION_REG_FIELDSIZE;
    if (type == t_write) {
      writevalue &= ~mask; // writes to unimplemented fields are ignored.
      TRACE_WRITE_VALUE;
    } else {
      value      &= ~mask; // unimplemented fields read 0.
      TRACE_READ_VALUE;
    }

    if (type == t_read) {
      TRACE_READ_VALUE;
      return MX_STATUS_OK;
    }

    // LSPI
    if (type == t_write && cfgsdisable) {
      unsigned int mask = 0;
      for (unsigned int i = 0; i < CONFIGURATION_REG_FIELDNBR; i++)
        if (!IS_LOCKED_INTERRUPT(int_id + i, cpu_id))
          mask |= CONFIGURATION_REG_FIELDMASK << i * CONFIGURATION_REG_FIELDSIZE;

      writevalue = NEWVAL_WITH_MASK(ref, mask, writevalue); // write to locked fields are ignored
      TRACE_WRITE_VALUE;
    }


    // strobes
    writevalue = NEWVAL_WITH_MASK(ref, strb_mask, writevalue);
    TRACE_WRITE_VALUE;
    ref = writevalue;
    /** @todo discuss adding a warning for UNPREDICTABLE effect if
        programmed when the interrupts are enabled !*/
    // NO SIDE-EFFECT

  } else if (offset >= IMPLEMENTATION_DEFINED_REG_OFF &&
             offset <  IMPLEMENTATION_DEFINED_REG_OFF + IMPLEMENTATION_DEFINED_REG_SIZE) {
    // *********************** 13. IMPL DEFINED REGION ***********************
#ifdef GIC_TRACE
    gic_msg_fl(LOG_TRACE, "%s %s to DISTRIBUTOR's IMPLEMENTATION DEFINED region by cpu %u",
            domain2str(domain), rw_t_2str(type), cpu_id);
#endif
    if (type == t_read)
      value = 0;  // reads return 0
    return MX_STATUS_OK;       // and write accesses are ignored silently

    // NO SIDE-EFFECT (IMPLI DEF)
  } else if (offset == SOFTWARE_INTERRUPT_REG_OFF) {
    // *********************** 14. SWI ***********************
    TRACE_DIST_ACCESS("SWI");

    // Write Only
    if (type == t_read) {
      value = 0;
      TRACE_READ_VALUE;
      return MX_STATUS_OK;
    }
    TRACE_WRITE_VALUE;

    // sanity check: an access with sparse strobes is likely to be meaning less.
    if ((strobes & 0xf) != 0xf) {
      gic_msg(LOG_WARNING, "byte write access to SWI register is ignored");
      return MX_STATUS_OK;
    }
    // --------- For write accesses only --------//
    if (trustzone_enabled) {
      if (IS_UNSECURE_DOMAIN(domain)) {
        writevalue |= (1 << 15); // set the SATT bit
        TRACE_WRITE_VALUE;
      }
    } else { // When Trustzone is not implemented,
      writevalue &= ~(1 << 15);  // the SATT bit is RESERVED
      TRACE_WRITE_VALUE;
    }

    // mask the SBZ bits: useless here, hence commented out
    //writevalue = value & SOFTWARE_INTERRUPT_REG_MASK;

    // Strobes are ignored.

    // SIDE-EFFECT:
    /* raise interrupts: decode register and make target list, than run the
       state machine */
#ifndef ISSCMP
    {
      unsigned int target_filter = GETFIELD(writevalue, 24, 2);
      unsigned int target_list;
      unsigned int satt   = BIT(writevalue, 15);
      unsigned int int_id = GETFIELD(writevalue, 0, 4);

#ifdef GIC_TRACE
      gic_msg_fl(LOG_TRACE,
              "writevalue = %#x, target_filter = %#x, satt = %#x, int_id = %u", writevalue, target_filter, satt, int_id);
#endif
      switch (target_filter) {
      case 0: // use target list
        target_list = GETFIELD(writevalue, 16, 8);
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "use target list = %#x", target_list);
#endif
        break;
      case 1: // all cpu except issuer
        target_list = ((1 << n_cores) - 1) & ~(1 << cpu_id);
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "all cpu except issuer: target_list = %#x", target_list);
#endif
        break;
      case 2: // sent to issuer only
        target_list = (1 << cpu_id);
#ifdef GIC_TRACE
        gic_msg_fl(LOG_TRACE, "sent to issuer only, ie target_list = %#x", target_list);
#endif
        break;
      default: // RESERVED
        if (side_effect != t_debug)
          gic_msg(LOG_WARNING,
                  "CPU %u wrote a reserved filter value in DIC's SWI register", cpu_id);
        return MX_STATUS_OK; // ignore
        break;
      }

      if (!IS_SECURE_DOMAIN(domain)) satt = 1;
      for (unsigned int trg = 0; trg < n_cores; trg ++) {
        if (target_list & (1 << trg)                                    &&
            ((satt ? false : true) == IS_SECURE_INTERRUPT(int_id, trg)) &&
            IS_IMPLEMENTED_INTERRUPT(int_id, trg)                         ) {
          // serialize software interrupts, ie select a requesting source (if several are pending)
          set_pending_soft_int(trg, int_id, cpu_id);
          // set interrupt pending (or "active and pending")
          transitionFSM(trg, int_id, WRITE_SWI);
        }
      }
    }
#endif
  } else if (offset >= IDENTIFICATION_REG_OFF &&
             offset <  IDENTIFICATION_REG_OFF + IDENTIFICATION_REG_SIZE) {
    //*************************  15. ID registers *************************
    TRACE_DIST_ACCESS("DISTRIBUTOR's ID");

    MxU64 sub_offset = (offset - IDENTIFICATION_REG_OFF) >> 2;
    // Read only
    if (type == t_write)
      return MX_STATUS_OK;

    switch(sub_offset) {
    case 0x00: value = 0x04; break; // Peripheral ID field 4..7, mapped in 0xFD0
    case 0x01: value = 0x00; break;
    case 0x02: value = 0x00; break;
    case 0x03: value = 0x00; break;
    case 0x04: value = 0x90; break; // Peripheral ID field 0..3, mapped in 0xFE0
    case 0x05: value = 0xB3; break;
    case 0x06: value = 0x1B; break;
    case 0x07: value = 0; /* IMPLEMENTATION DEFINED */ break;
    case 0x08: value = 0x0D; break; // Component ID, mapped in 0xFF0
    case 0x09: value = 0xF0; break;
    case 0x0a: value = 0x05; break;
    case 0x0b: value = 0xB1; break;
    default:
      gic_msg_fl(LOG_ERROR,
              "IDENTIFICATION_REG_SIZE value does not match current Primecell field number [sub_offset = %"PRId64"]", sub_offset);
      value = 0;
      break;
    }
    TRACE_READ_VALUE;

  } else {
    // DEFAULT CASE: accessed a reserved area
    if (offset < DISTRIBUTOR_MAP_SIZE) {
#ifndef DEBUG_DBG_ACCESS
      if (side_effect != t_debug)
#endif
        gic_msg(LOG_WARNING, "CPU %u accessed reserved area in DIC's distributor"
                " at offset %#x", cpu_id, (MxU32)offset);
      /** @todo unify message format and policy (Warning, Error,
          Internal Error) with the rest of the simulator) */
      if (type == t_read) {
        value = 0;
        TRACE_READ_VALUE;
      }
      return MX_STATUS_NOACCESS;
    }

    gic_msg_fl(LOG_ERROR,
               "   - d_reg_map_access(offset = %#x, value = %u, type = %s, cpu_id %u, domain = %d, "
               "side_effect %s): offset out of range",
               offset, value, (type == t_read ? "t_read" : "t_write"), cpu_id, domain,
               (side_effect == t_debug ? "debug" : "non-debug"));
    if (type == t_read) {
      value = 0xdeaddead;
      TRACE_READ_VALUE;
    }
    /** @todo unify message format and policy (Warning, Error,
        Internal Error) with the rest of the simulator) */
    return MX_STATUS_ERROR;
  }

  return MX_STATUS_OK;


#undef TRACE_DIST_ACCESS
#undef TRACE_DIST_ACCESS_ID_RANGE
#undef TRACE_WRITE_VALUE
#undef TRACE_READ_VALUE
#undef TRACE_ACCESS_VALUE
}



/**
 @brief Examines if the interrupt is edge triggered.
 @param int_id Which int to look for
 @return true or false
 */
bool
GIC::isEdgeTriggered(unsigned int int_id, unsigned int core_id)
{
  unsigned int conf = getConfig(int_id, core_id);

  return BIT(conf,1) ? true : false;
}

/**
 @brief Examines if the interrupt is 1-N.
 @param int_id Which int to look for
 @return true or false
 */
bool
GIC::is1N(unsigned int int_id)
{
  unsigned int conf = getConfig(int_id, 0 /* dummy */);

  return BIT(conf, 0) ? true : false;
}

unsigned int
GIC::getConfig(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / CONFIGURATION_REG_FIELDNBR;
  unsigned int bit_offset = int_id % CONFIGURATION_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  return GETFIELD(d_config[bank][wrd_offset],
                  bit_offset * CONFIGURATION_REG_FIELDSIZE,
                  CONFIGURATION_REG_FIELDSIZE);
}

unsigned int
GIC::getDomain(unsigned int int_id, unsigned int core)
{
  return isSecure(int_id, core) ? SECURE : NONSECURE;
}

bool
GIC::isSecure(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / INT_SEC_REG_FIELDNBR;
  unsigned int bit_offset = int_id % INT_SEC_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  // the interrupt is SECURE If and Only If the security bit is set to 0
  // (see PR231-GENC-006924 5.2 section 3.8.1.7)
  return BIT(d_int_sec[bank][wrd_offset], bit_offset) ? false : true;
}

void
GIC::setSecure(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / INT_SEC_REG_FIELDNBR;
  unsigned int bit_offset = int_id % INT_SEC_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  // the interrupt is SECURE If and Only If the security bit is set to 0
  // (see PR231-GENC-006924 5.2 section 3.8.1.7), hence the CLRBIT() below !
  CLRBIT(d_int_sec[bank][wrd_offset], bit_offset);
}

void
GIC::clearSecure(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / INT_SEC_REG_FIELDNBR;
  unsigned int bit_offset = int_id % INT_SEC_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  // the interrupt is SECURE If and Only If the security bit is set to 0
  // (see PR231-GENC-006924 5.2 section 3.8.1.7), hence the SETBIT() below !
  SETBIT(d_int_sec[bank][wrd_offset], bit_offset);
}

bool
GIC::isPending(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / PENDING_SET_REG_FIELDNBR;
  unsigned int bit_offset = int_id % PENDING_SET_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  return BIT(d_pending[bank][wrd_offset], bit_offset) ? true : false;
}
bool
GIC::isStickyPending(unsigned int int_id, unsigned int core_id)
{
  if (IS_BANKED_INTERRUPT(int_id))
    return IS_STICKY_PENDING_ON_CPU(int_id, core_id);

  for (unsigned tmpcpu = 0; tmpcpu < n_cores; tmpcpu++)
    if (IS_STICKY_PENDING_ON_CPU(int_id, tmpcpu))
      return true;
  return pseudo_pendingFSM[int_id];
}

void
GIC::setPending(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / PENDING_SET_REG_FIELDNBR;
  unsigned int bit_offset = int_id % PENDING_SET_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  SETBIT(d_pending[bank][wrd_offset], bit_offset);
}

void
GIC::clearPending(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / PENDING_SET_REG_FIELDNBR;
  unsigned int bit_offset = int_id % PENDING_SET_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  CLRBIT(d_pending[bank][wrd_offset], bit_offset);
}

/**
 * @brief Gets the interrupt enabled status
 * @param int_id Which int to look for
 * @return true or false
 */
bool
GIC::isEnabled(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / ENABLE_SET_REG_FIELDNBR;
  unsigned int bit_offset = int_id % ENABLE_SET_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  return BIT(d_enable[bank][wrd_offset], bit_offset) ? true : false;
}

void
GIC::setEnabled(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / ENABLE_SET_REG_FIELDNBR;
  unsigned int bit_offset = int_id % ENABLE_SET_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  SETBIT(d_enable[bank][wrd_offset], bit_offset);
}

void
GIC::clearEnabled(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / ENABLE_SET_REG_FIELDNBR;
  unsigned int bit_offset = int_id % ENABLE_SET_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  CLRBIT(d_enable[bank][wrd_offset], bit_offset);
}


/** Check if argument core is in the target list of argument interrupt.
    @note For banked interrupts, it will always be the case. */
bool
GIC::isTarget(unsigned int int_id, unsigned int core_id)
{
  unsigned int target_list = getCPUTargets(int_id, core_id);

  return (target_list & (1 << core_id)) ? true : false;
}

/**
 @brief Gets the interrupt active status as found in the ACTIVE
 register.  It tells if a common interrupt is active on any CPU or for
 a banked interrupt, if it is active on its local cpu (argument \a core_id)
 @param int_id Which int to look for
 @param core_id For banked interrupts, the ACTIVE register is banked.
 @return true or false
 */
bool
GIC::isActive(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / ACTIVE_BIT_REG_FIELDNBR;
  unsigned int bit_offset = int_id % ACTIVE_BIT_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  return BIT(d_active_bit[bank][wrd_offset], bit_offset) ? true : false;
}

void
GIC::setActive(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / ACTIVE_BIT_REG_FIELDNBR;
  unsigned int bit_offset = int_id % ACTIVE_BIT_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  SETBIT(d_active_bit[bank][wrd_offset], bit_offset);
}

void
GIC::clearActive(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / ACTIVE_BIT_REG_FIELDNBR;
  unsigned int bit_offset = int_id % ACTIVE_BIT_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  CLRBIT(d_active_bit[bank][wrd_offset], bit_offset);
}


/**
   @brief Gets the interrupt priority
   @param int_id Which int to look for
   @return priority.
 */
unsigned int
GIC::getPriority(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / PRIORITY_REG_FIELDNBR;
  unsigned int bit_offset = int_id % PRIORITY_REG_FIELDNBR;
  unsigned int bank;

  // Handle banked interrupts and common interrupts
  bank = IS_BANKED_INTERRUPT(int_id) ? core_id : 0;

  return GETFIELD(d_priority[bank][wrd_offset],
                  bit_offset *  PRIORITY_REG_FIELDSIZE,
                  PRIORITY_REG_FIELDSIZE);
}

/**
   @brief Sets the interrupt target CPUs
   @param int_id Which int to look for
   @param core_id the CPU id
   @return Target CPU list as bitfield
*/
unsigned int
GIC::getCPUTargets(unsigned int int_id, unsigned int core_id)
{
  unsigned int wrd_offset = int_id / TARGETS_REG_FIELDNBR;
  unsigned int bit_offset = int_id % TARGETS_REG_FIELDNBR;

  // For banked interrupts or in monocore implementations, always return the
  // local CPU as single target (see PR231-GENC-006924 5.2, section 3.8.1.10).
  if (IS_BANKED_INTERRUPT(int_id) || n_cores == 1)
    return (1 << core_id);

  return GETFIELD(d_cpu_targets[wrd_offset],
                  bit_offset * TARGETS_REG_FIELDSIZE,
                  TARGETS_REG_FIELDSIZE);
}

// BAB: Added for FVP GIC
const char *
GIC::DistRegName(unsigned int off)
{
    static char buf[80];
    if (off == CTRL_R_OFF) 
    {
        return "CTRL_R";
    }   
    else if (off == GIC_TYPE_R_OFF)
    {
        return("GIC_TYPE_R");
    }
    else if (off == DIST_IMPL_ID_R_OFF)
    {
        return("DIST_IMPL_ID_R");
    }    
    else if (off == INT_SEC_REG_OFF)
    {
        return("INT_SEC_R");
    }
    else if ( (off >= ENABLE_SET_REG_OFF) && (off <= ENABLE_SET_REG_OFF + 0x7C) )
    {
        sprintf(buf, "ENABLE_SET_R[%3d]", off - ENABLE_SET_REG_OFF);
        return(buf);
    }
    else if ( (off >= ENABLE_CLEAR_REG_OFF) && (off <= ENABLE_CLEAR_REG_OFF + 0x7C) )
    {
        sprintf(buf, "ENABLE_CLEAR_R[%3d]", off - ENABLE_CLEAR_REG_OFF);
        return(buf);
    }
    else if ( (off >= PENDING_SET_REG_OFF) && (off <= PENDING_SET_REG_OFF + 0x7C) )
    {
        sprintf(buf, "PENDING_SET_R[%3d]", off - PENDING_SET_REG_OFF);
        return(buf);
    }
    else if ( (off >= PENDING_CLEAR_REG_OFF) && (off <= PENDING_CLEAR_REG_OFF + 0x7C) )
    {
        sprintf(buf, "PENDING_CLEAR_R[%3d]", off - PENDING_CLEAR_REG_OFF);
        return(buf);
    }
    else if ( (off >= ACTIVE_BIT_REG_OFF) && (off <= ACTIVE_BIT_REG_OFF + 0x7C) )
    {
        sprintf(buf, "ACTIVE_BIT_R[%3d]", off - ACTIVE_BIT_REG_OFF);
        return(buf);
    }
    else if ( (off >= PRIORITY_REG_OFF) && (off <= PRIORITY_REG_OFF + 0x3FC) )
    {
        sprintf(buf, "PRIORITY_R[0x%03x]", off - PRIORITY_REG_OFF);
        return(buf);
    }
    else if ( (off >= TARGETS_REG_OFF) && (off <= TARGETS_REG_OFF + 0x3FC) )
    {
        sprintf(buf, "TARGETS_R[0x%03x]", off - TARGETS_REG_OFF);
        return(buf);
    }
    else if ( (off >= CONFIGURATION_REG_OFF) && (off <= CONFIGURATION_REG_OFF + 0xFC) )
    {
        sprintf(buf, "CONFIGURATION_R[0x%02x]", off - TARGETS_REG_OFF);
        return(buf);
    }
    else if (off == SOFTWARE_INTERRUPT_REG_OFF)
    {
        return("SW_INT_R");
    }
    else if ( (off >= IDENTIFICATION_REG_OFF) && (off <= IDENTIFICATION_REG_OFF + 0x1C) )
    {
        sprintf(buf, "ID_R[%2d]", off - IDENTIFICATION_REG_OFF);
        return(buf);
    }
    else 
    {
        return("UNKNOWN");
    }
}

// BAB: Added for FVP GIC
const char *
GIC::CpuIfRegName(unsigned int off)
{
    if (off == CIF_CTRL_R_OFF) 
    {
        return "CIF_CTRL_R";
    }   
    else if (off == PRIO_MASK_R_OFF)
    {
        return("PRIO_MASK_R");
    }
    else if (off == BINARY_POINT_R_OFF)
    {
        return("BINARY_POINT_R");
    }    
    else if (off == ACK_R_OFF)
    {
        return("ACK_R");
    }
    else if (off == EOI_R_OFF)
    {
        return("EOI_R");
    }
    else if (off == HIGHST_PEND_R_OFF)
    {
        return("HIGHST_PEND_R");
    }    
    else if (off == NS_BINARY_POINT_R_OFF)
    {
        return("NS_BINARY_POINT_R");
    }
    else if (off == CIF_IMPL_ID_R_OFF)
    {
        return("CIF_IMPL_ID_R");
    }

    return("UNKNOWN");
}


const char *
GIC::log_level_t2str(log_level_t err)
{
    const char *error_str = NULL;
    switch (err) {
        case LOG_DEBUG:      error_str = " (DEBUG)      "; break;
        case LOG_REGS:       error_str = " (REGS)       "; break;
        case LOG_TRACE:      error_str = " (TRACE)      "; break;
        case LOG_INFO:       error_str = "";               break;
        case LOG_WARNING:    error_str = " (WARNING)    "; break;
        case LOG_ERROR:      error_str = " (ERROR)      "; break;
        case LOG_FATAL:      error_str = " (FATAL)      "; break;
        // User information and errors:
        case LOG_USR_INFO:   error_str = " (USR INFO)   "; break;
        case LOG_USR_WARNING:error_str = " (USR WARNING)"; break;
        case LOG_USR_ERROR:  error_str = " (USR ERROR)  "; break;
        case LOG_USR_FATAL:  error_str = " (USR FATAL)  ";  break;
        default:
            error_str = "?";     break;
    }
    return error_str;
}


void
GIC::gic_msg (enum log_level_t level, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    fprintf(stderr, " %s GIC: ", log_level_t2str(level));
    vfprintf(stderr, format, args);
    va_end(args);
    if (level == LOG_FATAL || level == LOG_USR_FATAL)
        exit(1);
    fputc('\n', stderr);
}
