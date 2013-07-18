/*
 * AMBA-PV: amba_pv_ver.h - AMBA-PV version definitions.
 *
 * Copyright 2007-2009, 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_VER__H
#define AMBA_PV_VER__H

/**
 * @file        amba_pv_ver.h
 *
 * @brief       AMBA-PV version definitions.
 *
 * This header contains preprocessor symbols to allow for the determination
 * of the AMBA-PV version information.
 */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Defines */

/**
 * @brief       Version date.
 *
 * ISO8601 date (@c YYYYMMDD).
 */
#define AMBA_PV_VERSION 20130416

/**
 * @brief       Version string.
 *
 * @c "major.minor.build".
 */
#define AMBA_PV_VERSION_STRING "1.7.2"

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_VER__H) */
