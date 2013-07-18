/*
 * SCX: scx_simconfig.h - SystemC eXport support: simulation configuration API.
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef ARM_SCX_SIMCONFIG__H
#define ARM_SCX_SIMCONFIG__H

/*!
 * \file    scx_simconfig.h
 * \brief   Simulation configuration API.
 * \date    Copyright 2011-2012 ARM Limited. All rights reserved.
 *
 * SystemC eXport support simulation configuration API.
 */

/* Includes */
#include <string>
#include <sstream>
#include <map>

/* Namespaces */

/*!
 * \brief   SystemC eXport support namespace.
 */
namespace scx {

/* Forwards */
class scx_simcontrol_if;
extern scx_simcontrol_if * scx_get_default_simcontrol();

/* Functions */

/* Simulation initilization */

/*!
 * \brief   Initializes the simulation.
 * \param   id specifies an identifier for this simulation.
 * \param   ctrl specifies a pointer to the simulation control implementation;
 *          defaults to the one provided with Fast Models.
 *
 * Use this function to initialize the simulation.
 * The simulation must be initialized before constructing any exported
 * subsystem.
 *
 * \note    It is recommended to specify a unique identifier across all
 *          simulations running on the same host.
 */
extern void
scx_initialize(const std::string & id,
               scx_simcontrol_if * ctrl = scx_get_default_simcontrol());

/* Application loading */

/*!
 * \brief   Loads given \a application on given \a instance.
 * \param   instance specifies the name of the instance to load into
 * \param   application specifies the application to load.
 *
 * Use this function to load given \a application in the memory of given
 * \a instance.
 * The parameter \a instance must start with an EVS instance name, or with '*'
 * to load given \a application into given \a instance on all EVS in the
 * platform.
 * To load the same application on all cores of an SMP processor, specify "*"
 * for the core instead of its index, in parameter \a instance.
 * The loading of the application will happen at \c start_of_simulation()
 * call-back, at the earliest.
 */
extern void
scx_load_application(const std::string & instance,
                     const std::string & application);

/*!
 * \brief   Loads given \a application on all instances that execute software.
 * \param   application specifies the application to load.
 *
 * Use this function to load given \a application in the memory of all instances
 * that execute software, across all EVS in the platform.
 * The loading of the application will happen at \c start_of_simulation()
 * call-back, at the earliest.
 */
extern void
scx_load_application_all(const std::string & application);

/*!
 * \brief   Loads given raw \a data on given \a instance at given memory
 *          \a address.
 * \param   instance specifies the name of the instance to load into
 * \param   data specifies the filename of the raw data to load
 * \param   address specifies the memory \a address at which to load given
 *          raw \data.
 *
 * Use this function to load given raw \a data in the memory of given
 * \a instance.
 * The parameter \a instance must start with an EVS instance name, or with '*'
 * to load given raw \a data into given \a instance on all EVS in the platform.
 * On an SMP processor, when the parameter \a instance specifies "*" for the
 * core instead of its index, given raw \a data will only be loaded on the
 * first core.
 * The parameter \a address might start with a memory space specifier.
 * The loading of the raw data will happen at \c start_of_simulation()
 * call-back, at the earliest.
 */
extern void
scx_load_data(const std::string & instance,
              const std::string & data,
              const std::string & address);

/*!
 * \brief   Loads given raw \a data on all instances that execute software
 *          at given memory \a address.
 * \param   data specifies the filename of the raw data to load
 * \param   address specifies the memory \a address at which to load given
 *          raw \data.
 *
 * Use this function to load given raw \a data in the memory of all instances
 * that execute software, across all EVS in the platform.
 * On an SMP processor, given raw \a data will only be loaded on the first core.
 * The parameter \a address might start with a memory space specifier.
 * The loading of the raw data will happen at \c start_of_simulation()
 * call-back, at the earliest.
 */
extern void
scx_load_data_all(const std::string & data,
                  const std::string & address);

/* Parameter handling */

/*!
 * \brief   Sets the value of given parameter.
 * \param   name specifies the name of the parameter
 * \param   value specifies the value of the parameter.
 * \return  \c true when the parameter exists, \c false otherwise.
 *
 * Use this function to set parameters from components present in EVS or from
 * plug-ins.
 * The parameter \a name must start with an EVS instance name for given
 * parameter on this specific EVS, or with \c "*" for setting given parameter
 * on all EVS in the platform, or with a plug-in prefix (defaults to \c "TRACE")
 * for setting a plug-in parameter.
 *
 * \note    Changes made to parameters within System Canvas take precedence over
 *          changes made with scx_set_parameter().
 * \note    Parameters might be set during the construction phase, and before
 *          the elaboration phase. Calls to scx_set_parameter() are ignored
 *          after the construction phase.
 * \note    Plug-ins must be specified before calling any of the platform
 *          parameter functions, otherwise plug-ins will not be loaded and
 *          their parameters will not be available.
 */
extern bool
scx_set_parameter(const std::string & name, const std::string & value);

/*!
 * \brief   Sets the value of a given parameter.
 * \param   name specifies the name of the parameter
 * \param   value specifies the value of the parameter.
 * \return  \c true when the parameter exists, \c false otherwise.
 *
 * Use this function to set parameters from components present in EVS or
 * plug-ins.
 * The parameter \a name must start with an EVS instance name for given
 * parameter on this specific EVS, or with \c "*" for setting given parameter
 * on all EVS in the platform, or with a plug-in prefix (defaults to \c "TRACE")
 * for setting a plug-in parameter.
 *
 * \note    Changes made to parameters within System Canvas take precedence over
 *          changes made with scx_set_parameter().
 * \note    Parameters might be set during the construction phase, and before
 *          the elaboration phase. Calls to scx_set_parameter() are ignored
 *          after the construction phase.
 * \note    Plug-ins must be specified before calling any of the platform
 *          parameter functions, otherwise plug-ins will not be loaded and
 *          their parameters will not be available.
 */
template<class T>
inline bool
scx_set_parameter(const std::string & name, T value) {
    std::stringstream strm;

    strm << value;
    return (scx_set_parameter(name, strm.str()));
}

/*!
 * \brief   Retrieves the value of a given parameter.
 * \param   name specifies the name of the parameter
 * \param   value specifies a reference to the value of the parameter.
 * \return  \c true when the parameter exists, \c false otherwise.
 *
 * Use this function to get parameters from components present in EVS or
 * plug-ins.
 * The parameter \a name must start with an EVS instance name for retrieving an
 * EVS parameter or with a plug-in prefix (defaults to \c "TRACE") for
 * retrieving a plug-in parameter.
 *
 * \note    Plug-ins must be specified before calling any of the platform
 *          parameter functions, otherwise plug-ins will not be loaded and
 *          their parameters will not be available.
 */
extern bool
scx_get_parameter(const std::string & name, std::string & value);

/*!
 * \brief   Retrieves the value of a given parameter.
 * \param   name specifies the name of the parameter
 * \param   value specifies a reference to the value of the parameter.
 * \return  \c true when the parameter exists, \c false otherwise.
 *
 * Use this function to get parameters from components present in EVS or
 * plug-ins.
 * The parameter \a name must start with an EVS instance name for retrieving an
 * EVS parameter or with a plug-in prefix (defaults to \c "TRACE") for
 * retrieving a plug-in parameter.
 *
 * \note    Plug-ins must be specified before calling any of the platform
 *          parameter functions, otherwise plug-ins will not be loaded and
 *          their parameters will not be available.
 */
template<class T>
inline bool
scx_get_parameter(const std::string & name, T & value) {
    std::string v;
    std::stringstream strm;

    if (! scx_get_parameter(name, v)) {
        return false;
    }
    strm.str(v);
    strm >> value;
    return true;
}

/*!
 * \brief   Retrieves the value of a given parameter as a @c bool.
 */
extern bool
scx_get_parameter(const std::string &, bool &);

/*!
 * \brief   Retrieves the value of a given parameter as a @c short.
 */
extern bool
scx_get_parameter(const std::string &, short &);

/*!
 * \brief   Retrieves the value of a given parameter as an @c unsigned @c short.
 */
extern bool
scx_get_parameter(const std::string &, unsigned short &);

/*!
 * \brief   Retrieves the value of a given parameter as an @c int.
 */
extern bool
scx_get_parameter(const std::string &, int &);

/*!
 * \brief   Retrieves the value of a given parameter as an @c unsigned @c int.
 */
extern bool
scx_get_parameter(const std::string &, unsigned int &);

/*!
 * \brief   Retrieves the value of a given parameter as a @c long.
 */
extern bool
scx_get_parameter(const std::string &, long &);

/*!
 * \brief   Retrieves the value of a given parameter as an @c unsigned @c long.
 */
extern bool
scx_get_parameter(const std::string &, unsigned long &);

/*!
 * \brief   Retrieves the value of a given parameter as an @c long @c long.
 */
extern bool
scx_get_parameter(const std::string &, long long &);

/*!
 * \brief   Retrieves the value of a given parameter as an @c unsigned @c long
 *          @c long.
 */
extern bool
scx_get_parameter(const std::string &, unsigned long long &);

/*!
 * \brief   Retrieves the value of a given parameter.
 * \param   name specifies the name of the parameter to be retrieved.
 * \return  the value of the parameter when it exists, empty string (\c "")
 *          otherwise.
 *
 * Use this function to get parameters from components present in EVS or
 * plug-ins.
 * The parameter \a name must start with an EVS instance name for retrieving an
 * EVS parameter or with a plug-in prefix (defaults to \c "TRACE") for
 * retrieving a plug-in parameter.
 *
 * \note    Plug-ins must be specified before calling any of the platform
 *          parameter functions, otherwise plug-ins will not be loaded and
 *          their parameters will not be available.
 */
inline std::string
scx_get_parameter(const std::string & name) {
    std::string v;

    return (scx_get_parameter(name, v)? v: "");
}

/*!
 * \brief   Retrieves a list of all parameters within this simulation.
 *
 * Use this function to get a list of all parameters from all components present
 * in all EVS and from all plug-ins.
 * The parameter names start with an EVS instance name for EVS parameters and
 * a plug-in prefix (defaults to \c "TRACE") for plug-in parameters.
 *
 * \note    Plug-ins must be specified before calling any of the platform
 *          parameter functions, otherwise plug-ins will not be loaded and
 *          their parameters will not be available.
 */
extern std::map<std::string, std::string>
scx_get_parameter_list();

/*!
 * \brief   Parses command-line options and configures this simulation.
 * \param   argc specifies command-line options
 * \param   argv specifies command-line options
 * \param   trailer specifies a string which is printed after all options when
 *          printing help message (--help option)
 * \paral   sig_handler specifes whether to enable signal handler function.
 *          \c true to enable (default), \c false to disable.
 *
 * Use this function to parse command-line options and configure this
 * simulation accordingly.
 * The application must pass the values of the options from function
 * \c sc_main() as arguments to function scx_parse_and_configure().
 * The supported options are listed in the table below.
 * <table>
 * <tr>
 * <th>Short<th>Long option<th>Description
 * </tr>
 * <tr>
 * <td>\c -a<td>\c --application<td>Application to load, format: <tt>-a
 * [INST=]FILE</tt>
 * </tr>
 * <tr>
 * <td>\c -d<td>\c --data<td>Raw data to load, format: <tt>-d
 * [INST=]FILE@[MEMSPACE:]ADDRESS</tt>
 * </tr>
 * <tr>
 * <td>\c -L<td>\c --cadi-log<td>Logs all CADI calls to XML log files</tr>
 * <tr>
 * <td>\c -S<td>\c --cadi-server<td>Start CADI server allowing debuggers to
 * connect to targets in the simulation
 * </tr>
 * <tr>
 * <td>\c -D<td>\c --allow-debug-plugin<td>Allow a plug-in to debug the
 * simulation
 * </tr>
 * <tr>
 * <td>\c -h<td>\c --help<td>Print help message and exit</tr>
 * <tr>
 * <td>\c -K<td>\c --keep-console<td>Keep console window open after
 * completion (Windows only)
 * </tr>
 * <tr>
 * <td>\c -l<td>\c --list-params<td>Print list of platform parameters to
 * standard output and exit
 * </tr>
 * <tr>
 * <td>\c -C<td>\c --parameter<td>Set parameter, format:
 * <tt>-C INST.PARAM=VALUE</tt>
 * </tr>
 * <tr>
 * <td><td>\c --plugin<td>Plug-in to load, format: <tt>--plugin
 * [NAME=]FILE</tt>
 * </tr>
 * <tr>
 * <td><td>\c --trace-plugin<td>Deprecated. Use <tt>--plugin FILE</tt> instead
 * </tr>
 * <tr>
 * <td>\c -P<td>\c --prefix<td>Prefix semi-hosting output with the name of the
 * instance
 * </tr>
 * <tr>
 * <td>\c -p<td>\c --print-port-number<td>Print TCP port number the CADI server
 * is listening to
 * </tr>
 * <td>\c -R<td>\c --run<td>Run simulation immediately after CADI server has
 * been started
 * </tr>
 * <tr><td>\c -s<td>\c --stat<td>Print run statistics on simulation exit</tr>
 * </table>
 * Additionally, all remaining command-line arguments are treated as
 * applications to load.
 * This function will call \c std::exit(EXIT_SUCCESS) to exit (\c --list-params,
 * \c --help). It will call \c std::exit(EXIT_FAILURE) in case of error (error
 * in parameter specifier, invalid option, application or plug-in not found).
 *
 * \see     scx_load_application(), scx_load_application_all(),
 *          scx_load_data(), scx_load_data_all(),
 *          scx_set_parameter(), scx_get_parameter(), scx_get_parameter_list(),
 *          scx_start_cadi_server(), scx_enable_cadi_log(),
 *          scx_prefix_appli_output(), scx_print_port_number(),
 *          scx_print_statistics(), scx_load_plugin()
 */
extern void
scx_parse_and_configure(int argc,
                        char * argv[],
                        const char * trailer = NULL,
                        bool sig_handler = true);

}   /* namespace scx */

#endif  /* defined(ARM_SCX_SIMCONFIG__H) */
