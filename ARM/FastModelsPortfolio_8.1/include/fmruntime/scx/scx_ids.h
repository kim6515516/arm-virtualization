/*
 * SCX: scx_ids.h - SystemC eXport support: definition of report identifiers.
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef ARM_SCX_IDS__H
#define ARM_SCX_IDS__H

/*!
 * \file    scx_ids.h
 * \brief   Definition of SystemC eXport support report identifiers.
 * \date    Copyright 2011-2012 ARM Limited. All rights reserved.
 */

/* Namespaces */

/*!
 * \brief   SystemC eXport support namespace.
 */
namespace scx {

/* Globals  - Message identifiers */

/*!
 * \brief   Message identifier for deprecation messages.
 *
 * \note    Deprecation messages can be suppressed at runtime by setting the
 *          environment variable \c FM_SCX_DEPRECATION_WARNINGS to 0.
 */
extern const char
SCX_ID_FM_DEPRECATION[];

/*!
 * \brief   Message identifier for incompatible pthreads library messages.
 */
extern const char
SCX_ID_INCOMPATIBLE_PTHREADS[];

/*!
 * \brief   Message identifier for initialize not called messages.
 */
extern const char
SCX_ID_INITIALIZE_NOT_CALLED[];

/*!
 * \brief   Message identifier for internal error messages.
 */
extern const char
SCX_ID_INTERNAL_ERROR[];

/*!
 * \brief   Message identifier for EVS exists messages.
 */
extern const char
SCX_ID_EVS_EXISTS[];

/*!
 * \brief   Message identifier for invalid factory messages.
 */
extern const char
SCX_ID_INVALID_FACTORY[];

/*!
 * \brief   Message identifier for instantiate failed messages.
 */
extern const char
SCX_ID_INSTANTIATE_FAILED[];

/*!
 * \brief   Message identifier for component not found messages.
 */
extern const char
SCX_ID_INSTANCE_NOT_FOUND[];

/*!
 * \brief   Message identifier for license missing messages.
 */
extern const char *
SCX_ID_LICENSE_MISSING;

/*!
 * \brief   Message identifier for invalid simulation control messages.
 */
extern const char
SCX_ID_INVALID_SIMCONTROL[];

/*!
 * \brief   Message identifier for get report handler failed messages.
 */
extern const char
SCX_ID_GET_REPORT_HANDLER[];

/*!
 * \brief   Message identifier for get scheduler failed messages.
 */
extern const char
SCX_ID_GET_SCHEDULER[];

/*!
 * \brief   This identifier is deprecated. Use SCX_ID_LOAD_PLUGINS instead.
 */
#define SCX_ID_LOAD_TRACE_PLUGINS SCX_ID_LOAD_PLUGINS

/*!
 * \brief   Message identifier for load plug-ins failed messages.
 */
extern const char
SCX_ID_LOAD_PLUGINS[];

/*!
 * \brief   This identifier is deprecated. Use SCX_ID_REGISTER_PLUGINS instead.
 */
#define SCX_ID_REGISTER_TRACE_PLUGINS SCX_ID_REGISTER_PLUGINS

/*!
 * \brief   Message identifier for register plug-ins failed messages.
 */
extern const char
SCX_ID_REGISTER_PLUGINS[];

/*!
 * \brief   This identifier is deprecated. Do not use.
 */
#define SCX_ID_GET_CDI_REGISTRY SCX_ID_FM_DEPRECATION

/*!
 * \brief   This identifier is deprecated. Do not use.
 */
#define SCX_ID_REGISTER_CADI_HOST_IF SCX_ID_FM_DEPRECATION

/*!
 * \brief   Message identifier for add callback failed messages.
 */
extern const char
SCX_ID_ADD_CALLBACK[];
    
/*!
 * \brief   Message identifier for load application failed messages.
 */
extern const char
SCX_ID_LOAD_APPLICATION[];

/*!
 * \brief   Message identifier for load data failed messages.
 */
extern const char
SCX_ID_LOAD_DATA[];

}   /* namespace scx */

#endif  /* defined(ARM_SCX_IDS__H) */
