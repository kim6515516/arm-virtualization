/*!
 * \file    PVRange.h
 * \brief   A range type.
 * \date    Copyright 2010 ARM Limited. All rights reserved.
 *
 */

#ifndef PVRANGE_H
#define PVRANGE_H

#include <iostream>
#include <algorithm>
#include <cassert>
#include <limits>

#include "sg/Range.h"
#include "pv/PVBusAddr.h"

namespace pv
{
    using sg::range_t;
    using sg::range_t_traits;
    using sg::range_begin_end_incl;
    using sg::range_begin_end;
    using sg::range_begin_size;
    using sg::range_empty;
    using sg::range_from_range;

    typedef sg::range_t<bus_addr_t> bus_range_t;
}

#endif
