/*
 * SCX: scx.h - SystemC eXport support: main header file.
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef ARM_SCX__H
#define ARM_SCX__H

/*!
 * \file    scx.h
 * \brief   Main header file.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 * SystemC eXport support main header file.
 */

 /* Includes */

/* Exported Virtual Subsystem (EVS) related includes */
#include "scx_evs_base.h"

/* Simulation configuration related includes */
#include "scx_simconfig.h"

/* Simulation control related includes */
#include "scx_simcontrol.h"

/* Simulation debug & plug-in support related includes */
#include "scx_simdebug.h"

/* Scheduling related includes */
#include "scx_sched.h"

/* Run-time reporting facilities related includes */
#include "scx_report.h"
#include "scx_ids.h"

#endif  /* defined(ARM_SCX__H) */
