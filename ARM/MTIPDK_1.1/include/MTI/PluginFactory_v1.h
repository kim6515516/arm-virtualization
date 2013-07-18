/*!
 *  \file   PluginFactory_v1.h
 *  \brief  Declares the version 1 of the MTI::PluginFactory interface.
 *  \date   Copyright ARM Limited 2011 All Rights Reserved.
 *  
 *  Normally this header file should not be included directly. The
 *  PluginFactory.h header should be included instead.
 */

#ifndef PLUGINFACTORY_V1_H
#define PLUGINFACTORY_V1_H

#include "eslapi/CAInterface.h"
#include "eslapi/CADITypes.h"
#include "MTI/PluginFactory_v0.h"

namespace MTI
{

namespace v1
{
    class PluginFactory :
        public v0::PluginFactory
    {
    public:
        /// Static helper method to return the interface name for the 
        /// CAInterface.
        static eslapi::if_name_t IFNAME() { return "PluginFactory0"; }
        
        /// Static helper method to return the current interface revision 
        /// for CAInterface.
        static eslapi::if_rev_t IFREVISION() { return 1; }

        /** Return the name if this plugin prefix. */
        virtual const char *GetPrefix() { return "TRACE";}
    };

} // namespace v1

} // namespace MTI

#endif // PLUGINFACTORY_V1_H

// End of file PluginFactory_v1.h
