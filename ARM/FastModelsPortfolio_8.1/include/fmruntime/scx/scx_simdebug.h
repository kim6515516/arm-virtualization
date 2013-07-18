/*
 * SCX: scx_simdebug.h - SystemC eXport support: simulation debug & plug-ins.
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef ARM_SCX_SIMDEBUG__H
#define ARM_SCX_SIMDEBUG__H

/*!
 * \file    scx_simdebug.h
 * \brief   Simulation debug & plug-ins.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 * SystemC eXport support simulation debug & plug-ins.
 */

/* Includes */
#include <string>

/* Forwards */
namespace eslapi {
class CAInterface;
}

/* Namespaces */

/*!
 * \brief   SystemC eXport support namespace.
 */
namespace scx {

/* Functions */

/* Debug */

/*!
 * \brief   Specifies whether to starts a CADI server.
 * \param   start \c true to start a CADI server, \c false otherwise
 * \param   run \c true to run the simulation immediately after CADI server has
 *          been started, \c false otherwise
 * \param   debug \c true to enable debugging via a plugin, \c false otherwise.
 *
 * Use this function to specify whether to start a CADI server.
 * Starting a CADI Server enables attaching a debugger to debug targets in the
 * simulation.
 *
 * When \a debug is set to \c true, the CADI server is not started, but a
 * plug-in can implement an alternative debugging mechanism in place of it.
 *
 * When \a start is set to \c true, \a debug is ignored.
 *
 * \note    CADI server cannot be started after simulation has started.
 */
extern void
scx_start_cadi_server(bool start = true, bool run = true, bool debug = false);

/*!
 * \brief   Specifies whether to log all CADI calls to XML files.
 * \param   log \c true to log CADI calls, \c false otherwise.
 *
 * Use this function to specify whether to log all CADI calls to XML files.
 *
 * \note    Logging cannot be enabled after simulation has started.
 */
extern void
scx_enable_cadi_log(bool log = true);

/*!
 * \brief   Specifies whether to prefix semi-hosting output with the name of the
 *          CADI target instance.
 * \param   prefix \c true to prefix semi-hosting output, \c false otherwise.
 *
 * Use this function to specify whether to prefix semi-hosting output with the
 * name of the CADI target instance.
 */
extern void
scx_prefix_appli_output(bool prefix = true);

/*!
 * \brief   Specifies whether to enable printing the TCP port number the CADI
 *          server is listening to.
 * \param   print \c true to enable printing the TCP port number, \c false
 *          otherwise.
 *
 * Use this function to specify whether to enable printing the TCP port number
 * the CADI server is listening to.
 *
 * \note    Printing the TCP port number cannot be enabled after simulation has
 *          started.
 */
extern void
scx_print_port_number(bool print = true);

/*!
 * \brief   Specifies whether to enable printing simulation statistics at end of
 *          simulation.
 * \param   print \c true to enable printing simulation statistics, \c false
 *          otherwise.
 *
 * Use this function to specify whether to enable printing simulation
 * statistics at end of simulation.
 *
 * \note    Printing statistics cannot be enabled after simulation has started.
 *
 * \note    The printed statistics will account for LISA \c reset() behaviours
 *          run time and applications loading time. Long simulation run will
 *          compensate for this.
 */
extern void
scx_print_statistics(bool print = true);

/* Plug-ins */

/*!
 * \brief   This function is deprecated. Used scx_load_plugin() instead.
 */
extern void
scx_load_trace_plugin(const std::string & file);

/*!
 * \brief   Specifies a plug-in to be loaded.
 * \param   file specifies the file of the plug-in to be loaded.
 *
 * Use this function to specify a plug-in to be loaded.
 * The plug-in will be loaded at \c end_of_elaboration(), at the latest, or as
 * soon as any of the platform parameter functions is called.
 *
 * \note    Plug-ins must be specified before calling any of the platform
 *          parameter functions, otherwise these plug-ins will not be loaded
 *          and their parameters will not be available.
 */
extern void
scx_load_plugin(const std::string & file);

/* Global interface */

/*!
 * \brief   Asks for a pointer to the global interface.
 * \return  pointer to the global interface, or \c NULL if not found.
 *
 * Use this function to access the global interface of the simulation.
 * The global interface allows access to all interfaces which are registered in
 * the simulation.
 */
extern eslapi::CAInterface *
scx_get_global_interface();

}   /* namespace scx */

#endif  /* defined(ARM_SCX_SIMDEBUG__H) */
