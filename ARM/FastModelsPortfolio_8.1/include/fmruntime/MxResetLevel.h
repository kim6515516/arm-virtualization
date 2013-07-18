/*
 * Copyright 2006 ARM Limited.
 * Copyright 2012 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Reset evel definition.
 */

#ifndef _MxResetLevel_h_
#define _MxResetLevel_h_

// put this into a namespace to avoid namespace pollution for code
// if you would like to use this without the explicit namespace
// use 'using namespace mxresetlevel;'
namespace mxresetlevel
{
    enum MxResetLevel { MX_RESETLEVEL_HARD, MX_RESETLEVEL_SOFT };
}

#endif /* ifndef _MxResetLevel_h_ */

