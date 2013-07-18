/*
 * AMBA-PV: amba_pv.h - AMBA-PV main header file.
 *
 * Copyright 2007-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV__H
#define AMBA_PV__H

/**
 * @file        amba_pv.h
 *
 * @brief       AMBA-PV main header file.
 */

/* Defines */

/* The current implementation of AMBA-PV<->TLM bridges make use of TLM 2.0 convenience sockets.
 * Hence, when compiling applications that use AMBA-PV <->TLM bridges with SystemC, it is necessary to define the macro
 * SC_INCLUDE_DYNAMIC_PROCESSES before including the SystemC header file.
 */
#if ! defined(SC_INCLUDE_DYNAMIC_PROCESSES)
#if defined(SYSTEMC_INCLUDED)
#error "SC_INCLUDE_DYNAMIC_PROCESSES must be defined before #include <systemc>"
#else
#define SC_INCLUDE_DYNAMIC_PROCESSES
#endif
#endif

 /* Includes */
#include <systemc>
using sc_core::SC_ID_ASSERTION_FAILED_; /* sc_assert() misses sc_core:: */
#include <tlm.h>

/* Version definitions */
#include "amba_pv_ver.h"

/* TLM extension-related includes */
#include "tlmx/tlmx_bw_ifs.h"
#include "tlmx/tlmx_initiator_socket.h"
#include "tlmx/tlmx_target_socket.h"

/* Bus-related includes */
#include "bus/amba_pv_control.h"
#include "bus/amba_pv_attributes.h"
#include "bus/amba_pv_extension.h"

/* Core interfaces-related includes */
#include "core/amba_pv_types.h"
#include "core/amba_pv_core_ifs.h"
#include "core/amba_pv_ext_core_ifs.h"

/* Sockets-related includes */
#include "sockets/amba_pv_socket_base.h"
#include "sockets/amba_pv_socket_array.h"
#include "sockets/amba_pv_master_socket.h"
#include "sockets/amba_pv_slave_socket.h"
#include "sockets/amba_pv_ace_master_socket.h"
#include "sockets/amba_pv_ace_slave_socket.h"
#include "sockets/amba_pv_ext_master_socket.h"
#include "sockets/amba_pv_ext_slave_socket.h"
#include "sockets/amba_pv_ext_ace_master_socket.h"
#include "sockets/amba_pv_ext_ace_slave_socket.h"

/* User-related includes */
#include "user/amba_pv_if.h"
#include "user/amba_pv_slave_base.h"
#include "user/amba_pv_master_base.h"
#include "user/amba_pv_ace_master_base.h"
#include "user/amba_pv_ext_slave_base.h"
#include "user/amba_pv_ext_master_base.h"
#include "user/amba_pv_ext_ace_slave_base.h"
#include "user/amba_pv_ext_ace_master_base.h"

/* Models-related includes */
#include "models/amba_pv_bridges.h"
#include "models/amba_pv_exclusive_monitor.h"
#include "models/amba_pv_memory_base.h"
#include "models/amba_pv_simple_memory.h"
#include "models/amba_pv_memory.h"
#include "models/amba_pv_address_map.h"
#include "models/amba_pv_decoder.h"
#include "models/amba_pv_simple_probe.h"
#include "models/amba_pv_protocol_checker_base.h"
#include "models/amba_pv_protocol_checker.h"
#include "models/amba_pv_ace_protocol_checker.h"

/* Signal-related includes */
#include "signal/signal_core_ifs.h"
#include "signal/signal_master_port.h"
#include "signal/signal_slave_export.h"
#include "signal/signal_if.h"
#include "signal/signal_slave_base.h"
#include "signal/signal_bridges.h"

#endif  /* defined(AMBA_PV__H) */
