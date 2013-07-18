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
 * Revision $Revision: 56982 $
 * Checkin  $Date: 2008-03-27 18:30:11 +0000 (Thu, 27 Mar 2008) $
 * Revising $Author: jeacot01 $
 * State    $State$
 */

#ifndef GIC__H
#define GIC__H

#include <stdlib.h>

#include "sg/Attributes.h"
#include "MxTypes.h" // get MxStatus, MxU* types

// IMPLEMENTATION DEFINED PARAMETERS:
// uncomment to choose Cortex-A9 specific implementation:
#define CORTEX_A9_SPECIFIC_GIC

#ifdef CORTEX_A9_SPECIFIC_GIC
//----------------------------------------------------------------------//
//                  Cortex-A9 IMPLEMENTATION SETTINGS                   //
//----------------------------------------------------------------------//
#define MAX_N_CORES       4         /* max number of cores (4 for Cortex-A9's DIC, 8 for the GIC) */
#define trustzone_enabled true      /* false to disable TrustZone */

// These lines are accessed with :
// eg signal_port_irq29_core0_drive() for banked IRQ 29 on core 0, etc.
// adapt according to IMPLEMENTATION

/** number of interrupt lines in the implementation (max is MAX_N_INT_LINES)*/
#define MAX_N_INT_LINES 1020
// IMPLEMENTED INTERRUPT LINES:
// - all software interrupts
// - private peripheral int 28 (FIQ), 29 (TIMER), 30 (WATCHDOG) and 31 (IRQ).
#ifndef NO_LEGACY_IRQ
#define LEGACY_IRQ_ID   31
#define LEGACY_FIQ_ID   28
// additionally interrupts 30 (watchdogs) and 29 (timers) are implemented.
#define IS_IMPLEMENTED_INTERRUPT(id, cpu)  ((unsigned int)(id) < N_SOFTWARE_INT || \
                                            (28 <= (id) && (id) <= 31)           || \
                                            (IRQ_BASE_EXT <= (id) && (id) < n_ints) )
#else
#error "Cortex-A9 has LEGACY IRQ/FIQ implemented"
#endif

/** the number of priority levels (see PR231-GENC-006924 5.2 section 3.7.1) */
#define N_PRIORITY_LEVELS  32

//define REFLECT_PRIORITIES and REFLECT_DOMAINS to have an
//implementation in which changes to the priority registers are
//reflected to the active interrupts on each CPU interface.
#define REFLECT_PRIORITIES
#define REFLECT_DOMAINS

// DISTRIBUTOR implementation revision number is set to 0x143B (see DIST_IMPL_ID_R_RST_VAL).
// You may want to change this value (see DIST_IMPL_ID_R_RST_VAL).

// the region between 0xD00 and 0xE00 is implementation defined
// in this model, reads return 0 and writes are ignored.

// Current spec does leave ambiguity on the 1-N model definition for level-sensitive interrupts:
// - Either 1-N means that whenever such an interrupt becomes active on CPU, it is still
//   pending but not eligible to the HPI on any target CPU (Pending Set/Clear register bit read 1
//   for that interrupt).
// - or it means that it is not pending anymore (Pending Set/Clear register bit read 0 for
//   that interrupt) as soon as it is active (which also implies that the "Active and
//   Pending" state is not reachable by level-sensitive interrupts)
// This beavior can be different for edge triggered and level sensitive interrupts.
// This is the case for Falcon:
#define TMP_1N_MODEL_FORCE_NOT_PENDING_EDGE
//#define TMP_1N_MODEL_FORCE_NOT_PENDING_LVL

// Whenever the CPU target list of an pending interrupt is changed, the interrupt becomes
// pending on new targets and inactive on old ones.
#define PENDING_FLOP_CPU_TARGET_SENSITIV

#define INTERRUPTS_WITH_EMPTY_TARGET_LIST_CANNOT_BECOME_PENDING
//#define PENDING_STATUS_OF_INTERRUPTS_WITH_EMPTY_TARGET_LIST_CANNOT_BE_CLEAR

// byte access always allowed, 16bit and 64bit access always aborting.
#define NO_BYTE_ACCESS(x)    false
#define NO_HLFWORD_ACCESS(x) true
#define NO_DWORD_ACCESS(x)   true

// Number of Lockable Share Peripheral Interrupts:
#define NBR_LSPI   31
#else

//----------------------------------------------------------------------//
//                  GENERIC IMPLEMENTATION SETTINGS                     //
//----------------------------------------------------------------------//
#define MAX_N_CORES       8         /* max number of cores (in [1..8]) */
#define trustzone_enabled true      /* false to disable TrustZone */
/** number of interrupt lines in the implementation (max is MAX_N_INT_LINES)*/
#define MAX_N_INT_LINES 1020
// IMPLEMENTED INTERRUPT LINES:
// the number of shared interrupts lines is set at instantiation (in constructor) and defaults to MAX_N_INT_LINES.
// define NO_LEGACY_IRQ if you don't want of legacy nIRQ and nFIQ interrupt lines
// These lines are accessed with signal_port_legacy_irq_core0() for nIRQ of core 0 etc.
#ifndef NO_LEGACY_IRQ
#define LEGACY_IRQ_ID   31
#define LEGACY_FIQ_ID   28
#endif
#define IS_IMPLEMENTED_INTERRUPT(id, cpu)  (0 <= (id) && (id) < n_ints)
/** the number of priority levels (see PR231-GENC-006924 5.2 section 3.7.1) */
#define N_PRIORITY_LEVELS  32

//define REFLECT_PRIORITIES and REFLECT_DOMAINS to have an
//implementation in which changes to the priority registers are
//reflected to the active interrupts on each CPU interface.

// define NOCHECK to disable check of arguments in methods

// DISTRIBUTOR implementation revision number is set to 0x143B (see DIST_IMPL_ID_R_RST_VAL).
// You may want to change this value (see DIST_IMPL_ID_R_RST_VAL).

// the region between 0xD00 and 0xE00 is implementation defined
// in this model, reads return 0 and writes are ignored.

// Current spec does leave ambiguity on the 1-N model definition for level-sensitive interrupts:
// - Either 1-N means that whenever such an interrupt becomes active on CPU, it is still
//   pending but not eligible to the HPI on any target CPU (Pending Set/Clear register bit read 1
//   for that interrupt).
// - or it means that it is not pending anymore (Pending Set/Clear register bit read 0 for
//   that interrupt) as soon as it is active (which also implies that the "Active and
//   Pending" state is not reachable by level-sensitive interrupts)
#define TMP_1N_MODEL_FORCE_NOT_PENDING_EDGE
#define TMP_1N_MODEL_FORCE_NOT_PENDING_LVL

// Whenever the CPU target list of an pending interrupt is changed, the interrupt becomes
// pending on new targets and inactive on old ones.
#define PENDING_FLOP_CPU_TARGET_SENSITIV


// byte access is only allowed for priority and target register
#define NO_BYTE_ACCESS(x) ((x) >= DISTRIBUTOR_MAP_SIZE || \
                           !((x) >= PRIORITY_REG_OFF && (x) < PRIORITY_REG_OFF + PRIORITY_REG_SIZE) && \
                           !((x) >= TARGETS_REG_OFF  && (x) < TARGETS_REG_OFF  + TARGETS_REG_SIZE)     )
#define NO_HLFWORD_ACCESS(x) NO_BYTE_ACCESS(x)
#define NO_DWORD_ACCESS(x)   false

// Number of Lockable Share Peripheral Interrupts:
#define NBR_LSPI   31
#endif // *_SPECIFIC_GIC

//----------------------------------------------------------------------//


#define DISTRIBUTOR_MAP_SIZE     0x1000 /* do not modify */
#define CPU_INTERFACE_MAP_SIZE   0x100  /* do not modify */


// define REFLECT_PRIORITIES for an implementation which reflects
// priority changes in the distributor to the CPU interfaces.

#define MAX_N_SECURE_DOMAIN 2  /* max number of secure domains (TrustZone)*/
#define NONSECURE 1
#define SECURE    0

// Software interrupts are from 0 to 15
#define N_SOFTWARE_INT        16
// start of shared (peripheral) interrupts
#define IRQ_BASE_EXT          32

/* 0x40-0xCF    IMP     IMP     IMP     IMPLEMENTATION DEFINED */
#define CIF_IMPL_DEF_SIZE        (0xD0 - 0x40) /* in 8bit byte */

/* THE DISTRIBUTOR REGISTERS (see PR231-GENC-006924 5.2 at table 3.3) */
/* 0x080 Read/Write     Restricted      0x00000000      Irq 0 to 31 Interrupt Security Register */
/* 0x0FC Read/Write     Restricted      0x00000000      Irq 992 to 1019 Interrupt Security Register */
#define INT_SEC_REG_SIZE           (1 << 7)     /* in 8bit byte */

/* 0x100 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Enable Set Register */
/* 0x17C Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Enable Set Register  */
#define ENABLE_SET_REG_SIZE      (1 << 7)     /* in 8bit byte */
/* 0x180 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Enable Clear Register */
/* 0x1FC Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Enable Clear Register */
#define ENABLE_CLEAR_REG_SIZE    ENABLE_SET_REG_SIZE
/* 0x200 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Pending Set Register */
/* 0x27C Read/Write     NS-intsr dependent      0x00000000      rq 992 to 1019 Pending Set Register */
#define PENDING_SET_REG_SIZE     (1 << 7)     /* in 8bit byte */
/* 0x280 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 31 Pending Clear Register */
/* 0x2FC Read/Write     NS-intsr dependent      0x00000000      Irq 992 to 1019 Pending Clear Register */
#define PENDING_CLEAR_REG_SIZE   (1 << 7)     /* in 8bit byte */
/* 0x300 Read Only NS-intsr dependent   0x00000000      Irq 0 to 31 Active Bit Register */
/* 0x37C Read Only NS-intsr dependent   0x00000000      Irq 992 to 1019 Active Bit Register */
#define ACTIVE_BIT_REG_SIZE      (1 << 7)     /* in 8bit byte */
/* 0x400 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 3 Priority Register */
/* 0x7F8 Read/Write     NS-intsr dependent      0x00000000      Irq 1016 to 1019 Priority Register */
#define PRIORITY_REG_SIZE        (1 << 10)    /* in 8bit byte */
/* 0x800 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 3 CPU Targets Register */
/* 0xBF8 Read/Write     NS-intsr dependent      0x00000000      Irq 1016 to 1019 CPU Targets Register */
#define TARGETS_REG_SIZE         (1 << 10)    /* in 8bit byte */
/* 0xC00 Read/Write     NS-intsr dependent      0x00000000      Irq 0 to 15 Configuration Register */
/* 0xCFC Read/Write     NS-intsr dependent      0x00000000      Irq 1008 to 1019 Configuration Register */
#define CONFIGURATION_REG_SIZE   (1 << 8)    /* in 8bit byte */
/* 0xD00        IMP     IMP     IMP     IMPLEMENTATION DEFINED */
/* ... */
/* 0xDFC        IMP     IMP     IMP     IMPLEMENTATION DEFINED */
#define IMPLEMENTATION_DEFINED_REG_SIZE   (0xE00 - 0xD00)     /* in 8bit byte */
/* 0xF00        Write Only      Banked   -      Software Interrupt Register */
#define SOFTWARE_INTERRUPT_REG_SIZE    4     /* in 8bit byte */
/* 0xFD0        Read Only       Common  IMP dependent   Identification Register */
/* 0xFFC        Read Only       Common  IMP dependent   Identification Register */
#define IDENTIFICATION_REG_SIZE  (0x1000 - 0xFD0)     /* in 8bit byte */


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


class GIC
{
 public:
  unsigned int n_cores;
  unsigned int n_ints;
  bool irq_o[MAX_N_CORES];       // output IRQ line's value
  bool fiq_o[MAX_N_CORES];
  bool edge_irq_o[MAX_N_CORES];  // which one changed
  bool edge_fiq_o[MAX_N_CORES];

  // constructors / destructor
  GIC(void);
  GIC(unsigned int n_cpu, unsigned int n_ints);
  ~GIC();
  void init(void);

  void reset(void);

  /* Access functions */

  void cfgsdisable_i(MxU32 Value);

  // interrupt input lines
#ifndef NO_LEGACY_IRQ
  // pass-thru to each core nIRQ/nFIQ
  void signal_port_legacy_irq_drive(unsigned int core, MxU32 value);
  void signal_port_legacy_fiq_drive(unsigned int core, MxU32 value);
#endif

  // INTERRUPT LINES.
  // Cortex-A9: TIMER/WATCHDOG get ids 29,30 and LEGACY IRQ gets id 31.
  // generic method
  void signal_port_irq_drive(unsigned int int_no, unsigned int core, MxU32 value);


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
  /** Mask for the PRIORITY MASK registers of CPU interfaces */
  unsigned int prio_mask_r_mask;
  unsigned int bp_min_val;

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


  // The method used to access those registers
  MxStatus c_reg_map_access(MxU32 offset, MxU32 & value, unsigned char strobes, rw_t type,
                            unsigned int cpu_id, int domain, dbg_t side_effect);


  // used to generate the INTERRUPT ACKNOWLEDGE register and the
  // HIGHEST PENDING INTERRUPT register.
  MxU32 gethighestpendinginterruptregister(unsigned int core, unsigned int domain);

  // data port from the DISTRIBUTOR
  //- latest values of port
  unsigned int c_highest_priority[MAX_N_CORES];
  unsigned int c_highest_priority_id[MAX_N_CORES];
  unsigned int c_hpi_domain[MAX_N_CORES];
  bool c_cpu_interface_edge[MAX_N_CORES];
  // - update of data from DISTRIBUTOR
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
#ifndef NO_LEGACY_IRQ
  MxU32 signal_port_legacy_irq[MAX_N_CORES];
  MxU32 signal_port_legacy_fiq[MAX_N_CORES];
  // dispatch legacy IRQ between Cortex-A9's DIC irq 31 and mux at output of CPU interface.
  void dispatch_legacy_irq(unsigned int core);
  // dispatch legacy FIQ between Cortex-A9's DIC irq 28 and mux at output of CPU interface.
  void dispatch_legacy_fiq(unsigned int core);
#endif

  // Distributor registers (see PR231-GENC-006924 5.2 at section 3.8.1, page 12)
  MxU32 gic_ctrl[MAX_N_SECURE_DOMAIN];    /**< CONTROL REG (domain-banked) */
  //MxU32 gic_type;                         /**< GIC TYPE REG (common)*/
  //MxU32 d_impli_id;                       /**< DISTRIBUTOR IMPLEMENTER ID*/

  MxU32 d_int_sec[MAX_N_CORES][INT_SEC_REG_SIZE >> 2];        /**< Interrupt Security */

  MxU32 d_enable[MAX_N_CORES][ENABLE_SET_REG_SIZE >> 2];    /**< Enable flags */

  MxU32 d_pending[MAX_N_CORES][PENDING_SET_REG_SIZE >> 2];  /**< Pending flags */
  MxU32 d_active_bit[MAX_N_CORES][ACTIVE_BIT_REG_SIZE >> 2];/**< Active flags */

  MxU32 d_priority[MAX_N_CORES][PRIORITY_REG_SIZE >> 2];    /**< Priorities */
  MxU32 d_cpu_targets[TARGETS_REG_SIZE >> 2];               /**< CPU Targets (not for banked int) */
  MxU32 d_config[MAX_N_CORES][CONFIGURATION_REG_SIZE >> 2]; /**< Int. Configuration  */
  MxU32 d_implidef[IMPLEMENTATION_DEFINED_REG_SIZE >> 2];   /**< Implementation defined region */
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

    enum log_level_t {
        // internal information and errors
        LOG_DEBUG,
        LOG_REGS,
        LOG_TRACE,
        LOG_INFO,
        LOG_WARNING,
        LOG_ERROR,    /* model simulation keeps running */
        LOG_FATAL,    /* program reached an unrecoverable incoherent state, simulation must stop */
        // User information and errors:
        LOG_USR_INFO,
        LOG_USR_WARNING, /* warning on user input */
        LOG_USR_ERROR,   /* non-lethal error of user */
        LOG_USR_FATAL    /* user error such that simulation cannot continue */
    };

    const char *log_level_t2str(log_level_t err);
    void gic_msg (enum log_level_t level, const char *format, ...) SG_FORMATSTR(printf, 3, 4);
};

#endif // GIC__H
