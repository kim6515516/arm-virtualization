/*!
 * \file    SGTicks.h
 * \brief   Type for integer clock tick count.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 */

#ifndef SGCLOCKTICKS_H
#define SGCLOCKTICKS_H

#include "sg/SGstdint.h"

namespace sg
{
    /*! Certain functions measure time in clock ticks (i.e. relative to a clock). */
    typedef uint64_t ticks_t;
} // namespace sg

#endif // SGCLOCKTICKS_H
