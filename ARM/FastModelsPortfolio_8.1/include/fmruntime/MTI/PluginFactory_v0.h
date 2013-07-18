/*!
 *  \file   PluginFactory_v0.h
 *  \brief  Declares the version 0 of the MTI::PluginFactory interface.
 *  \date   Copyright ARM Limited 2009 All Rights Reserved.
 *  
 *  Normally this header file should not be included directly. The
 *  PluginFactory.h header should be included instead.
 */

#ifndef PLUGINFACTORY_V0_H
#define PLUGINFACTORY_V0_H

#include "eslapi/CAInterface.h"
#include "eslapi/CADITypes.h"

namespace MTI
{

namespace v0
{
    /// Class providing a method to instantiate a PluginInstance.
    /** This interface must be implemented by anybody implementing a
     * (trace) plugin. The interface provides methods to define
     * instantiation time parameters and create an instance of a trace
     * plugin. An implementation of the class must implement an
     * CAInterface::ObtainInterface() method which in will usually
     * return a pointer to itself if an IFNAME() interface is requested.
     */
    class PluginFactory :
        public eslapi::CAInterface
    {
    public:
        /// Static helper method to return the interface name for the 
        /// CAInterface.
        static eslapi::if_name_t IFNAME() { return "PluginFactory0"; }
        
        /// Static helper method to return the current interface revision 
        /// for CAInterface.
        static eslapi::if_rev_t IFREVISION() { return 0; }

        /** This should return the number of instantiation time
         * parameters. Return 0 if a plugin does not have
         * parameters. */
        virtual uint32_t GetNumberOfParameters() = 0;

        /** Return the instantiation time parameters. The caller must
         * provide an array of length GetNumberOfParameters() of
         * CADIParameterInfo_t structures. The implementor can choose to
         * not implement this and return CADI_STATUS_CmdNotSupported
         * if no instantiation time parameters exist.
         *
         * \param parameter_info_list This must point to an array of
         * CADIParameterInfo_t structures with GetNumberOfParameters()
         * elements. The implementor of the GetParameterInfos() method
         * must fill in these structures. The id field must be set to
         * a unique id to match up the parameter with the value passed
         * back via the CADIParameterValue_t structures of the
         * Instantiate() call. The isRunTime field should be set to
         * false (=0). Depending on the type of the parameter either
         * the minValue, maxValue and defaultValue fields (for integer
         * parameters) or the defaultString field should be set.
         *
         * \return Should return MTI_OK after filling in
         * parameters. Can return CADI_STATUS_CmdNotSupported if the
         * plugin does not have parameters.
         */
        virtual eslapi::CADIReturn_t GetParameterInfos(eslapi::CADIParameterInfo_t *parameter_info_list) = 0;
        
        /**
         * This will instantiate a new instance of a trace
         * plugin. Since it is possible to have multiple instances of
         * the same trace plugin this method might be called multiple
         * times, typically with different parameter values.
         * 
         * \param instance_name The name of the instance of the trace
         * plugin. If a plugin is instantiated multiple times the
         * names will be unique. This can for example be used to print
         * better (error) messages, or to make file names unique based
         * on the plugin instance name.
         * 
         * \param number_of_parameters This contains the number of
         * parameter values passed. The number of parameter values
         * passed can be between 0 and the total number of parameters
         * as returned by GetNumberOfParameters().
         * 
         * \param parameter_values This contains the values configured
         * for the instantiation time parameters. The mapping between
         * parameter infos and parameter values is done via the
         * parameter ids of these structures.
         *
         * \return The ObtainInterface method of the CAInterface
         * pointer returned should resolve into a PluginInstance
         * class. 
         */
        virtual CAInterface *Instantiate(const char *instance_name, 
                                         uint32_t number_of_parameters,
                                         eslapi::CADIParameterValue_t *parameter_values) = 0;

        /** This method will be called to indicate the end of the
         * lifetime of the PluginFactory. No further calls to any of
         * its methods will be done. */
        virtual void Release() =0;
    };

} // namespace v0

} // namespace MTI

#endif // PLUGINFACTORY_V0_H

// End of file PluginFactory_v0.h
