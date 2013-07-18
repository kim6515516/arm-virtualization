/*!
 *  \file   ModelTraceInterface.h
 *  \brief  The MTI::SystemTraceInterface and MTI::ComponentTraceInterface classes, and helper classes.
 *  \date   Copyright ARM Limited 2008-2009 All Rights Reserved.
 *  
 */

#ifndef MTI_TRACEINTERFACE_H
#define MTI_TRACEINTERFACE_H

#include "MTI/ModelTraceInterface_v1.h"

namespace MTI
{
    // Make one version of the interface the default:
    using namespace v1;
    using v1::SystemTraceInterface;
}

#endif

// end of file ModelTraceInterface.h
