/*!
 * \file    PVBusMapper.h
 * \brief   Component for controlling PVBusMapper accesses.
 * \date    Copyright 2013 ARM Limited. All rights reserved.
 *
 * PVBusMapper provides a single bus slave port ('pvbus_s') and
 * an array of  master ports ('pvbus_m[64]').  A 'control' port
 * is used to route requests as they come in, based on transaction
 * attributes.
 */

#ifndef PVBUSMAPPER_H
#define PVBUSMAPPER_H

//! Special constants to allow the PVBusMapperControl.remap() method
//  to indicate that a transaction should be aborted or ignored, instead
//  of being routed to a downstream port.

enum PVBusMapper_RouteOption
{
    PVBUSMAPPER_ABORT  = ~0U,
    PVBUSMAPPER_IGNORE = ~1U
};

#endif  // PVBUSMAPPER_H
