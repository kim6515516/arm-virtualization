/*!
 *  \file   GetTopLevelCADIFromSystemTraceInterface.h
 *  \brief  Get the top level CADI interface from a SystemTraceInterface pointer.
 *  \date   Copyright ARM Limited 2011 All Rights Reserved.
 *
 */

#ifndef GetTopLevelCADIFromSystemTraceInterface_h_
#define GetTopLevelCADIFromSystemTraceInterface_h_

#include "MTI/ModelTraceInterface.h"
#include "eslapi/CADI.h"

// get CADI interface of the most top level component which is present in the SystemTraceInterface and which offers CADI
inline eslapi::CADI *GetTopLevelCADIFromSystemTraceInterface(MTI::SystemTraceInterface *sti)
{
    if (!sti)
        return 0;
    size_t minLen = 1000000000;
    eslapi::CADI *cadi = 0;
    // find component with the shortest path name which has a CADI inerface
    for(MTI::SystemTraceInterface::TraceComponentIndex i = 0; i < sti->GetNumOfTraceComponents(); i++)
    {
        const char *name = sti->GetComponentTracePath(i);
        if (!name)
            continue;
        size_t len = strlen(name);
        eslapi::CAInterface *cti_caif = sti->GetComponentTrace(i);
        if (!cti_caif)
            continue;
        eslapi::CAInterface *cadi_caif = cti_caif->ObtainInterface(eslapi::CADI::IFNAME(), eslapi::CADI::IFREVISION(), 0);
        if (!cadi_caif)
            continue;
        if (len < minLen)
        {
            minLen = len;
            cadi = static_cast<eslapi::CADI *>(cadi_caif);
        }
    }
    return cadi;
}

#endif

