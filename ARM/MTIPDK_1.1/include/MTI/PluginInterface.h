/*!
 *  \file   PluginInterface.h
 *  \brief  Defines a generic shared library entry point.
 *  \date   Copyright ARM Limited 2008-2009 All Rights Reserved.
 *  
 */

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

// This describes an arbitrary CAInterface based plugin:

#include "eslapi/CAInterface.h"

// Since a plugin is not linked, but loaded via
// LoadLibrary/GetProcAddress we do not need __declspec(dllimport)

#ifndef _WIN32
    #if __GNUC__ >= 4
        #define PLUGIN_INTERFACE_WEXP __attribute__((visibility ("default")))
    #else
        #define PLUGIN_INTERFACE_WEXP
    #endif
#else
    #define PLUGIN_INTERFACE_WEXP __declspec(dllexport)
#endif

extern "C"
{    
    /** Type describing the function prototype of the GetCAInterface
     * function. Typical use is to cast to symbol pointer to a
     * function pointer after dynamically loading a (trace)
     * plugin. */
    typedef eslapi::CAInterface *(* GetCAInterfaceFunc)();
    
    /** This is the entry point and only function of a trace plugin
     * .so/.dll. It will return a CAInterface pointer, on which the
     * ObtainInterface method must be called, to obtain an interface
     * of type PluginFactory. */
    PLUGIN_INTERFACE_WEXP eslapi::CAInterface *GetCAInterface();
}

#endif

// End of file PluginInterface.h
