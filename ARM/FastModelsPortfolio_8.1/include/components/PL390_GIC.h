// -*- c++ -*-
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
 *    based on GIC specification PR231-GENC-006924 5.3
 *
 */

#ifndef PL390_GIC__H
#define PL390_GIC__H

#include "MxTypes.h"

//----------------------------------------------------------------------//
//                  GENERIC IMPLEMENTATION SETTINGS                     //
//----------------------------------------------------------------------//
#define MAX_N_CORES       8         /* max number of cores (in [1..8]) */
/** number of interrupt lines in the implementation (max is MAX_N_INT_LINES)*/
#define MAX_N_INT_LINES 1020

// These legacy nIRQ and nFIQ interrupt lines are accessed with signal_port_legacy_irq_core0() for nIRQ of core 0 etc.
#define LEGACY_IRQ_ID   31
#define LEGACY_FIQ_ID   28

// max Number of Lockable Share Peripheral Interrupts:
#define NBR_LSPI   31

// Software interrupts are from 0 to 15
#define N_SOFTWARE_INT        16

// start of shared (peripheral) interrupts
#define IRQ_BASE_EXT          32

/** the number of priority levels (see PR231-GENC-006924 5.2 section 3.7.1) */
#define MAX_N_PRIORITY_LEVELS 256

#define MAX_N_SECURE_DOMAIN 2  /* max number of secure domains (TrustZone)*/
#define NONSECURE 1
#define SECURE    0

//----------------------------------------------------------------------//

/* THE DISTRIBUTOR REGISTERS (see PR231-GENC-006924 5.2 at table 3.3) */
/* 0x080 Read/Write     Restricted      0x00000000      Irq 0 to 31 Interrupt Security Register */
/* 0x0FC Read/Write     Restricted      0x00000000      Irq 992 to 1019 Interrupt Security Register */
#define INT_SEC_REG_OFF           0x080
#define INT_SEC_REG_SIZE         (0x100 - INT_SEC_REG_OFF)      /* in 8bit byte */

/* 0x100 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Enable Set Register */
/* 0x17C Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Enable Set Register  */
#define ENABLE_SET_REG_OFF        0x100
#define ENABLE_SET_REG_SIZE      (0x180 - ENABLE_SET_REG_OFF)   /* in 8bit byte */
/* 0x180 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Enable Clear Register */
/* 0x1FC Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Enable Clear Register */
#define ENABLE_CLEAR_REG_OFF      0x180
#define ENABLE_CLEAR_REG_SIZE     ENABLE_SET_REG_SIZE
/* 0x200 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Pending Set Register */
/* 0x27C Read/Write     NS-intsr dependent      0x00000000      rq 992 to 1019 Pending Set Register */
#define PENDING_SET_REG_OFF       0x200
#define PENDING_SET_REG_SIZE     (0x280 - PENDING_SET_REG_OFF)  /* in 8bit byte */
/* 0x280 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Pending Clear Register */
/* 0x2FC Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Pending Clear Register */
#define PENDING_CLEAR_REG_OFF     0x280
#define PENDING_CLEAR_REG_SIZE    PENDING_SET_REG_SIZE           /* in 8bit byte */
/* 0x300 Read Only NS-intsr dependent   0x00000000              Irq 0 to 31 Active Bit Register */
/* 0x37C Read Only NS-intsr dependent   0x00000000              Irq 992 to 1019 Active Bit Register */
#define ACTIVE_BIT_REG_OFF        0x300
#define ACTIVE_BIT_REG_SIZE      (0x400 - ACTIVE_BIT_REG_OFF)   /* in 8bit byte */
/* 0x400 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 3 Priority Register */
/* 0x7F8 Read/Write     NS-intsr dependent      0x00000000      Irq 1016 to 1019 Priority Register */
#define PRIORITY_REG_OFF          0x400
#define PRIORITY_REG_SIZE        (0x7FC - PRIORITY_REG_OFF)     /* in 8bit byte */
/* 0x800 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 3 CPU Targets Register */
/* 0xBF8 Read/Write     NS-intsr dependent      0x00000000      Irq 1016 to 1019 CPU Targets Register */
#define TARGETS_REG_OFF           0x800
#define TARGETS_REG_SIZE         (0xBFC - TARGETS_REG_OFF)      /* in 8bit byte */
/* 0xC00 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 15 Configuration Register */
/* 0xCFC Read/Write     NS-intsr dependent      0x00000000      Irq 1008 to 1019 Configuration Register */
#define CONFIGURATION_REG_OFF     0xC00
#define CONFIGURATION_REG_SIZE   (0xD00-CONFIGURATION_REG_OFF)  /* in 8bit byte */
/* 0xD00        IMP     IMP     IMP     IMPLEMENTATION DEFINED */
/* ... */
/* 0xDFC        IMP     IMP     IMP     IMPLEMENTATION DEFINED */
#define IMPLEMENTATION_DEFINED_REG_OFF     0xD00
#define IMPLEMENTATION_DEFINED_REG_SIZE   (0xE00 - IMPLEMENTATION_DEFINED_REG_OFF)     /* in 8bit byte */

#define PPI_IF_REG_OFF            0xD00

#define SPI_IF_REG_OFF            0xD04
#define SPI_IF_REG_SIZE          (0xD80-SPI_IF_REG_OFF)         /* in 8bit byte */

#define LEGACY_INT_REG            0xDD4

#define MATCH_D_REG               0xDE0
#define ENABLE_D_REG              0xDE4

/* 0xF00        Write Only      Banked   -      Software Interrupt Register */
#define SOFTWARE_INTERRUPT_REG_SIZE    4     /* in 8bit byte */
/* 0xFC0        Read Only       Common  IMP dependent   Identification Register */
/* 0xFC3        Read Only       Common  IMP dependent   Identification Register */
#define IDENTIFICATION8_REG_OFF   0xFC0
/* 0xFD0        Read Only       Common  IMP dependent   Identification Register */
/* 0xFFC        Read Only       Common  IMP dependent   Identification Register */
#define IDENTIFICATION_REG_OFF    0xFD0
#define IDENTIFICATION_REG_SIZE  (0x1000 - IDENTIFICATION_REG_OFF) /* in 8bit byte */

//----------------------------------------------------------------------//

/** type of access */
typedef enum {t_read, t_write} rw_t;
typedef enum {t_debug, t_nondebug} dbg_t;
/** Possible states of an interrupt */
enum fsmState {INACTIVE,
               PENDING,
               PENDING_LVL, /* for a level-sensitive interrupt, became pending because of edge on interrupt line */
               ACTIVE,
               ACTIVEPENDING,
               ACTIVEPENDING_LVL};

/** an Event indicates a corresponding predicate used in the conditions for
    state transitions in the FSM (see PR231-GENC-006924 5.3 section 4.1.2) is true.*/
enum fsmEvent {
  WRITE_SWI,    /**< int id was written in SWI register */
  VALID_TRG,    /**< CPU became target of current int */
  INVALID_TRG,  /**< CPU si no more target of current int */
  EDGE,         /**< transition on interrupt input signal */
  WRITE_P,      /**< flag in Pending register became 1 */
  WRITE_CP,     /**< flag in Pending register became 0 */
  READ_IA,      /**< interrupt ID is in the ACKNOWLEDGE register and is being read */
  WRITE_EOI,    /**< int id has been written in EOI register */
  NOW_ACTIV,    /**< Interrupt when active on another CPU */
  NOT_ACTIV     /**< End of Interrupt on another CPU */
};

/** the type of an interrupt */
enum intType {
  SOFT,    /**< SOFTWARE interrupts */
  LEVEL_S, /**< LEVEL HIGH SENSITIVE interrupts */
  EDGE_T   /**< EDGE TRIGGERED interrupts */
};


class PL390_GIC
{
 public:
  unsigned int n_cpus;
  unsigned int n_ints;
  unsigned int n_sgi;
  unsigned int n_ppi;
  unsigned int n_spi;
  unsigned int n_lspi;
  unsigned int n_priority_levels;
  bool trustzone_enabled;
  bool legacy_irq;
  bool legacy_fiq;
  bool ppi_edge;

  unsigned int if_type;
  unsigned int arch_version;

  unsigned int d_id_width;
  unsigned int c_id_width;

  unsigned int match_d[MAX_N_CORES];
  unsigned int enable_d[MAX_N_CORES];
  unsigned int match_c[MAX_N_CORES];
  unsigned int enable_c[MAX_N_CORES];

  bool irq_o[MAX_N_CORES];       // output IRQ line's value
  bool fiq_o[MAX_N_CORES];
  bool edge_irq_o[MAX_N_CORES];  // which one changed
  bool edge_fiq_o[MAX_N_CORES];

  // constructors / destructor
  PL390_GIC(void);
  PL390_GIC(unsigned int n_cpu, unsigned int n_ints);
  ~PL390_GIC();
  void init(void);

  void reset(void);

  /* Access functions */

  void cfgsdisable_i(MxU32 Value);

  // interrupt input lines
  void signal_port_irq_drive(unsigned int int_no, unsigned int core, MxU32 value);

  // pass-thru to each core nIRQ/nFIQ
  void signal_port_legacy_irq_drive(unsigned int core, MxU32 value);
  void signal_port_legacy_fiq_drive(unsigned int core, MxU32 value);

  // bus_port_access
  MxStatus distributor_read8( MxU32 offset, MxU8  &data, unsigned int cpu_id, int domain);
  MxStatus distributor_read16(MxU32 offset, MxU16 &data, unsigned int cpu_id, int domain);
  MxStatus distributor_read32(MxU32 offset, MxU32 &data, unsigned int cpu_id, int domain);
  MxStatus distributor_read64(MxU32 offset, MxU64 &data, unsigned int cpu_id, int domain);

  MxStatus distributor_write8( MxU32 offset, MxU8  data, unsigned int cpu_id, int domain);
  MxStatus distributor_write16(MxU32 offset, MxU16 data, unsigned int cpu_id, int domain);
  MxStatus distributor_write32(MxU32 offset, MxU32 data, unsigned int cpu_id, int domain);
  MxStatus distributor_write64(MxU32 offset, MxU64 data, unsigned int cpu_id, int domain);

  MxStatus distributor_write(MxU32 offset, MxU64 data, unsigned char strobes, unsigned int cpu_id, int domain);

  // Debug accesses
  MxStatus distributor_readDbg8( MxU32 offset, MxU8  &data, unsigned int cpu_id, int domain);
  MxStatus distributor_readDbg16(MxU32 offset, MxU16 &data, unsigned int cpu_id, int domain);
  MxStatus distributor_readDbg32(MxU32 offset, MxU32 &data, unsigned int cpu_id, int domain);
  MxStatus distributor_readDbg64(MxU32 offset, MxU64 &data, unsigned int cpu_id, int domain);

  MxStatus distributor_writeDbg8( MxU32 offset, MxU8  data, unsigned int cpu_id, int domain);
  MxStatus distributor_writeDbg16(MxU32 offset, MxU16 data, unsigned int cpu_id, int domain);
  MxStatus distributor_writeDbg32(MxU32 offset, MxU32 data, unsigned int cpu_id, int domain);
  MxStatus distributor_writeDbg64(MxU32 offset, MxU64 data, unsigned int cpu_id, int domain);

  // bus_port_access
  MxStatus cpuif_read8( MxU32 offset, MxU8  &data, unsigned int cpu_id, int domain);
  MxStatus cpuif_read16(MxU32 offset, MxU16 &data, unsigned int cpu_id, int domain);
  MxStatus cpuif_read32(MxU32 offset, MxU32 &data, unsigned int cpu_id, int domain);
  MxStatus cpuif_read64(MxU32 offset, MxU64 &data, unsigned int cpu_id, int domain);

  MxStatus cpuif_write8( MxU32 offset, MxU8  data, unsigned int cpu_id, int domain);
  MxStatus cpuif_write16(MxU32 offset, MxU16 data, unsigned int cpu_id, int domain);
  MxStatus cpuif_write32(MxU32 offset, MxU32 data, unsigned int cpu_id, int domain);
  MxStatus cpuif_write64(MxU32 offset, MxU64 data, unsigned int cpu_id, int domain);

  MxStatus cpuif_write(MxU32 offset, MxU64 data, unsigned char strobes, unsigned int cpu_id, int domain);

  // Debug accesses
  MxStatus cpuif_readDbg8( MxU32 offset, MxU8  &data, unsigned int cpu_id, int domain);
  MxStatus cpuif_readDbg16(MxU32 offset, MxU16 &data, unsigned int cpu_id, int domain);
  MxStatus cpuif_readDbg32(MxU32 offset, MxU32 &data, unsigned int cpu_id, int domain);
  MxStatus cpuif_readDbg64(MxU32 offset, MxU64 &data, unsigned int cpu_id, int domain);

  MxStatus cpuif_writeDbg8( MxU32 offset, MxU8  data, unsigned int cpu_id, int domain);
  MxStatus cpuif_writeDbg16(MxU32 offset, MxU16 data, unsigned int cpu_id, int domain);
  MxStatus cpuif_writeDbg32(MxU32 offset, MxU32 data, unsigned int cpu_id, int domain);
  MxStatus cpuif_writeDbg64(MxU32 offset, MxU64 data, unsigned int cpu_id, int domain);

  // output
  void update_signal_nIRQ(unsigned int core); // output multiplex (legacy, enable)
  void update_signal_nFIQ(unsigned int core); // idem for FIQ

  void update_irq_o(unsigned int core, bool val);  // CPU's IRQ input drive
  void update_fiq_o(unsigned int core, bool val);  // CPU's FIQ input drive

  // BAB: Added for FVP GIC
  const char *DistRegName(MxU32 off);
  const char *CpuIfRegName(MxU32 off);

 private:
  unsigned int bp_min_val[MAX_N_SECURE_DOMAIN];

  /** Mask for the PRIORITY MASK registers of CPU interfaces */
  unsigned int prio_mask_r_mask;

  // value of DIC type register (see PR231-GENC-006924 5.6, section 3.8.1.3)
  unsigned int gic_type_r_val;

  bool cfgsdisable;

  // CPU INTERFACES
  // value of nIRQ/nFIQ (must be initialized to 0)
  MxU32 signal_nFIQ[MAX_N_CORES];
  MxU32 signal_nIRQ[MAX_N_CORES];
  unsigned int signal_NSecure[MAX_N_CORES]; // security domain (SECURE or NONSECURE) of int

  unsigned int priority_mask; /**< the mask used when priority regs of CPU ifs are accessed */

  // CPU INTERFACE registers
  MxU32 c_ctrl_reg[MAX_N_CORES][MAX_N_SECURE_DOMAIN]; /**< CONTROL REGISTERs (one for each CPU interface)*/
  MxU32 c_priority_mask_reg[MAX_N_CORES];             /**<  PRIORITY MASK register */
  MxU32 c_binary_point_reg[MAX_N_CORES][MAX_N_SECURE_DOMAIN]; /**< BINARY POINT register */

  MxU32 c_integ_en_reg[MAX_N_CORES]; /** INTEGRATION TEST ENABLE register */
  MxU32 c_interrupt_out_reg[MAX_N_CORES]; /** INTERRUPT OUT register */

  MxU32 c_running_int_priority[MAX_N_CORES];   /**< internal "running priority" register */
  MxU32 c_running_int_domain[MAX_N_CORES];     /**< the security attribute of "running priority" reg */

  // in the software model, keep a stack of active interrupts
  unsigned int c_active_int_stack_id[MAX_N_CORES][1024];   // stack of active interrupts
  int c_active_int_stack_idx[MAX_N_CORES]; // stack indices pointing to running interrupts

#ifndef REFLECT_PRIORITIES
  // together with the id, remember also the priority by the time interrupt was submitted
  MxU32 c_active_int_stack_priority[MAX_N_CORES][1024];        // priorities of active interrupts
#endif
#ifndef REFLECT_DOMAINS
  // remember the security domain by the time the interrupt was submitted
  unsigned int c_active_int_stack_domain[MAX_N_CORES][1024];   // domain of active interrupts
#endif


  // The method used to access thoses registers
  MxStatus c_reg_map_access(MxU32 offset, MxU32 & value, unsigned char strobes, rw_t type,
                            unsigned int cpu_id, int domain, dbg_t side_effect);


  // used to generate the INTERRUPT ACKNOWLEDGE register and the
  // HIGHEST PENDING INTERRUPT register.
  MxU32 getHighestPendingInterruptRegister(unsigned int core, unsigned int domain);

  // data port from the DISTRIBUTOR
  //- latest values of port
  unsigned int c_highest_priority[MAX_N_CORES];
  unsigned int c_highest_priority_id[MAX_N_CORES];
  unsigned int c_hpi_domain[MAX_N_CORES];
  bool c_cpu_interface_edge[MAX_N_CORES];
  // - update of data from DISTRIBUTOR
  bool check_preemption(unsigned int core);
  void update_cpu_interface(unsigned int core);

  unsigned int domain_of_max_active_priority(unsigned int core);
  MxU32 max_active_priority(unsigned int core);

  MxU32        running_int_priority(unsigned int core);
  unsigned int running_int_domain(unsigned int core);

  void writeClearPending(unsigned int int_no, unsigned int core);
  /* Called when an interrupt has been asserted or when the PENDING
     SET register in DISTRIBUTOR is written (see d_reg_map_access()). Sets Pending bits,
     and dispatch to targets CPU*/
  void writeSetPending(unsigned int int_no, unsigned int core);

  void dispatch_event_on_targets(unsigned int int_no, unsigned int core_id, fsmEvent event);

  // input signals from CPU
  // ACKNOWLEDGE REGISTER read
  void readIntAck(unsigned int core);
  // EOI register written
  void writeEndOfInt(unsigned int core, unsigned int int_id, unsigned int src_cpu);
  // To ensure 1-N model restrictions
  void model_1_N_in(unsigned hpi, unsigned core);
  void model_1_N_out(unsigned hpi, unsigned core);

  // FSM for the core interface
  /** Current state of each interrupt on each core */
  fsmState coreFSM[MAX_N_CORES][MAX_N_INT_LINES];
  bool pseudo_pendingFSM[MAX_N_INT_LINES]; // used to keep the pending status while the target list is empty.

  // A pool of requests for a given software interrupt on a target CPU
  // is required to serialize soft IRQs from different CPUs (4th
  // paragraph of section 4.1.14 "Software Triggered Interrupt
  // register", page 27 of PRD03-GENC-004392 7.0).
  unsigned char soft_int_pending_requests[MAX_N_CORES/*dest*/][N_SOFTWARE_INT];
  // selected source for a given (multiply pending) software interrupt
  unsigned int current_soft_int_pending_src[MAX_N_CORES][N_SOFTWARE_INT];
  // source of the currently active software interrupts
  unsigned int current_soft_int_active_src[MAX_N_CORES][N_SOFTWARE_INT];

  // Serialize software interrupt sources of argument soft int ID
  void set_pending_soft_int(unsigned int target_cpu, unsigned int int_id, unsigned int src_cpu);
  void set_active_soft_int(unsigned int target_cpu, unsigned int int_id);
  void finished_soft_int(unsigned int target_cpu, unsigned int int_id);


  // computes the new state (see fsmState) of argument interrupt on argument core
  void transitionFSM(unsigned int dest_cpu, unsigned int interrupt, fsmEvent s);

  // update the pending register and recalculate the highest priority pending interrupt
  void update_pending(unsigned int int_no, unsigned int core);
  // recalculate highest priority and update CPU interface of arg. core
  void update_highestpriority(unsigned int core);
  // updates the active bit register
  void update_active(unsigned int int_no, unsigned int core);
  // update the running priority interrupt register
  void update_running(unsigned int core);


  // DISTRIBUTOR
  // value of interrupt inputs (must be initialized to 0)
  MxU32 signal_port_irq[MAX_N_CORES][MAX_N_INT_LINES];
  MxU32 signal_port_legacy_irq[MAX_N_CORES];
  MxU32 signal_port_legacy_fiq[MAX_N_CORES];

  // dispatch legacy IRQ between Cortex-A9's DIC irq 31 and mux at output of CPU interface.
  void dispatch_legacy_irq(unsigned int core);
  // dispatch legacy FIQ between Cortex-A9's DIC irq 28 and mux at output of CPU interface.
  void dispatch_legacy_fiq(unsigned int core);

  // Distributor registers (see PR231-GENC-006924 5.2 at section 3.8.1, page 12)
  MxU32 gic_ctrl[MAX_N_SECURE_DOMAIN];    /**< CONTROL REG (domain-banked) */
  //MxU32 gic_type;                         /**< GIC TYPE REG (common)*/
  //MxU32 d_impli_id;                       /**< DISTRIBUTOR IMPLEMENTER ID*/

  MxU32 d_int_sec[MAX_N_CORES][INT_SEC_REG_SIZE >> 2];      /**< Interrupt Security */

  MxU32 d_enable[MAX_N_CORES][ENABLE_SET_REG_SIZE >> 2];    /**< Enable flags */


  MxU32 d_pending[MAX_N_CORES][PENDING_SET_REG_SIZE >> 2];  /**< Pending flags */
  MxU32 d_active_bit[MAX_N_CORES][ACTIVE_BIT_REG_SIZE >> 2];/**< Active flags */

  MxU32 d_priority[MAX_N_CORES][PRIORITY_REG_SIZE >> 2];    /**< Priorities */
  MxU32 d_cpu_targets[TARGETS_REG_SIZE >> 2];               /**< CPU Targets (not for banked int) */
  MxU32 d_config[MAX_N_CORES][CONFIGURATION_REG_SIZE >> 2]; /**< Int. Configuration  */
  /** Software Interrupt register is write only and does not need to
      hold a value. Writes are processed on the spot. */
  /** Primecell ARM GIC Identification register file is read only and constant. */

  // The method used to access those
  MxStatus d_reg_map_access(MxU32 offset, MxU32 & value, unsigned char strobes, rw_t type,
                            unsigned int cpu_id, int domain, dbg_t side_effect);

  bool isEdgeTriggered(unsigned int n, unsigned int core_id);
  bool is1N(unsigned int n);
  unsigned int getConfig(unsigned int n, unsigned int core_id);
  unsigned int getDomain(unsigned int int_id, unsigned int core);
  bool isSecure(unsigned int n, unsigned int core_id);
  void setSecure(unsigned int n, unsigned int core_id);
  void clearSecure(unsigned int n, unsigned int core_id);
  bool isPending(unsigned int core_id);
  bool isPending(unsigned int n, unsigned int core_id);
  bool isStickyPending(unsigned int int_id, unsigned int core_id);
  void setPending(unsigned int n, unsigned int core_id);
  void clearPending(unsigned int n, unsigned int core_id);
  bool isEnabled(unsigned int n, unsigned int core_id);
  void setEnabled(unsigned int int_id, unsigned int core_id);
  void clearEnabled(unsigned int int_id, unsigned int core_id);
  bool isTarget(unsigned int int_id, unsigned int core_id);
  bool isActive(unsigned int n, unsigned int core_id);
  void setActive(unsigned int n, unsigned int core_id);
  void clearActive(unsigned int n, unsigned int core_id);

  unsigned int getPriority(unsigned int n, unsigned int core_id);
  unsigned int getCPUTargets(unsigned int n, unsigned int core_id);

  /** returns a positive mask of bytes selected by argument strobes */
  MxU32 byte_strobe2mask(unsigned char strobes)
  {
    MxU32 mask = 0;
    MxU32 fieldsize = 8; // for byte-strobes
    for (int i = 0; i < 4; i++)
      if ((strobes >> i) & 1)
        mask |= (((1 << fieldsize) - 1) << (i * fieldsize));
    return mask;
  }

  /* functions to create positive mask for register reg_offset in register field */
  /* helper functions */
  bool allways_true(unsigned int, unsigned int) {return true;}
  bool isLockedInterrupt(unsigned int, unsigned int);
  bool isSoftwareInterrupt(unsigned int, unsigned int);
  bool isAsserted(unsigned int, unsigned int);
  bool isLevelSensitiveAsserted(unsigned int, unsigned int);
  /** returns a positive mask */
  unsigned int getMask(unsigned int cpu_id, MxU32 reg_offset, unsigned int fieldsize,
                       bool (PL390_GIC::*setfield)(unsigned int, unsigned int)=&PL390_GIC::allways_true);
};

#endif // PL390_GIC__H
