/*
 * types.h - Basic types definition.
 *
 * Copyright 2011 Limited.
 * All rights reserved.
 */

#ifndef TYPES__H
#define TYPES__H

/* Includes */
#include <sg/SGstdint.h>
#include <amba_pv.h>

/* Datatypes */

/*
 * Basic address and data types.
 */
typedef sc_dt::uint64 addr_t;
typedef sc_dt::uint64 data_t;
typedef bool signal_t;
typedef uint32_t value_t;
typedef uint64_t value64_t;

/*
 * Bus width in bits.
 */
static const unsigned int BUSWIDTH = sizeof(data_t) * 8;

#endif  /* defined(TYPES__H) */
