/*!
 *  \file   PluginInstance_v0.h
 *  \brief  Declaring the version 0 of the MTI::PluginInstance interface.
 *  \date   Copyright ARM Limited 2009 All Rights Reserved.
 *  
 *  Normally this header file should not be included directly. The
 *  PluginInstance.h header should be included instead.
 */

#ifndef PLUGININSTANCE_V0_H
#define PLUGININSTANCE_V0_H

#include "eslapi/CAInterface.h"
#include "eslapi/CADITypes.h"

namespace MTI
{

namespace v0
{
    /// Interface implementing the plugin interface.
    /** This interface must be implemented by anybody implementing a
     * (trace) plugin. The interface provides the RegisterSimulation()
     * method which is called at instantiation time to
     * pass a pointer to the main model trace interface of class
     * SystemTraceInterface. An implementation of the class must
     * implement the CAInterface::ObtainInterface() method, which
     * will usually return a pointer to itself if an IFNAME() interface
     * is requested.
     */
    class PluginInstance :
        public eslapi::CAInterface
    {
    public:
        /// Static helper method to return the interface name for the 
        /// CAInterface.
        static eslapi::if_name_t IFNAME() { return "PluginInstance0"; }
        
        /// Static helper method to return the current interface revision 
        /// for CAInterface.
        static eslapi::if_rev_t IFREVISION() { return 0; }

        // Plugin Interface:

        /** This method is called by the simulation at instantiation time.
         *
         * \param simulation is a pointer of type CAInterface and can
         * be turned into a SystemTraceInterface pointer by calling its
         * ObtainInterface() method. It is also possible to get access
         * to the CADI interface of the top level component by calling
         * ObtainInterface() for a CADI interface on this simulation
         * pointer.
         *
         * \return This should usually return CADI_STATUS_OK to
         * indicate that the plugin was successfully initialized.
         */
        virtual eslapi::CADIReturn_t RegisterSimulation(eslapi::CAInterface *simulation) = 0;

        /** After this method is called no further calls to a
         * PluginInstance will be done. It should be used for any
         * cleanup required, and can be used to delete the instance of
         * PluginInstance, depending on the allocation model of the
         * plugin. */
        virtual void Release() =0;

        /** Return the name if this plugin instance. */
        virtual const char *GetName() const =0;
    };

} // namespace v0

} // namespace MTI

#endif

// End of file PluginInstance_v0.h
