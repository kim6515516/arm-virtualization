/*
 * 
 *
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

#ifndef INCLUDED_FVP_VE_Cortex_A15x1_DSO_NAMESPACE_H
#define INCLUDED_FVP_VE_Cortex_A15x1_DSO_NAMESPACE_H

#include <sg/Visibility.h>

#if defined(SG_BUILDING_DSO_FVP_VE_Cortex_A15x1)
    #define SG_FVP_VE_Cortex_A15x1_DSO SG_DSO_EXPORT
#else
    #define SG_FVP_VE_Cortex_A15x1_DSO SG_DSO_IMPORT
#endif

#endif
