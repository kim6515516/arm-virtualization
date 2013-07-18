/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2000-2009 ARM Limited.
 * Copyright 2012 ARM Limited.
 *
 * All rights reserved.
 */


/** \file
 * Implementation of the CADI factory.
 */

#if ! defined(WITHOUT_MAXCORE_MXDIFACTORY)

// global definitions: this must always be the first include
# include "GlobalDefs.h"
# include "Components.h"
# include "GlobalSystemAttributes.h"

# include <eslapi/CADIFactory.h>

extern eslapi::CADIBroker* CreateSgCADIBroker(sg::ComponentFactory* pFactory, const char* name);

/// File id of this file
const char *_FVP_VE_Cortex_A15x1_CADIFactory_fileid = "$Id: tpl_ComponentsCADIFactory.cpp 15703 2006-05-11 13:18:44Z spees $";

class FVP_VE_Cortex_A15x1_GlobalSystemAttributes : public GlobalSystemAttributes
{
public:
    FVP_VE_Cortex_A15x1_GlobalSystemAttributes() : GlobalSystemAttributes(){};

    virtual void setupGlobalSystemAttributes()
    {
        
 
 
 
 
 

 

 
 
 
 
 

 
 
 

 
 
 
 
 
 
 
 
 
 
 

 

 
 
 
 
 
 
 
 

 
 
 

 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 
 
 
 
    }

};
// instantiate global attributes statically
FVP_VE_Cortex_A15x1_GlobalSystemAttributes theFVP_VE_Cortex_A15x1_GlobalSystemAttributes;


extern "C"
{
    /// @brief Global function exported by a dynamically loaded object.
    ///
    /// This function must exist in a dynamically loaded object (DLL/.so).
    /// It allows the client to instantiate the CADIBroker.
    CADI_WEXP eslapi::CADIBroker * CreateCADIBroker()
    {
        if(GlobalSystemAttributes::getGlobalSystemAttributes())
            GlobalSystemAttributes::getGlobalSystemAttributes()->setupGlobalSystemAttributes();

        return CreateSgCADIBroker(FVP_VE_Cortex_A15x1_NMS::FVP_VE_Cortex_A15x1_GetFactory(),"FVP_VE_Cortex_A15x1");
    }
}

#endif // !WITHOUT_MAXCORE_MXDIFACTORY


