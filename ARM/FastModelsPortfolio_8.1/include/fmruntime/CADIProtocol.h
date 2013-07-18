/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   CADIProtocol.h
 *  \brief  CADI protocol
 *  \date   Copyright ARM Limited 2002 All Rights Reserved.
 *          Copyright ARM Limited 2013 All Rights Reserved.
 *  
 */

#ifndef _CADIProtocol_h_
#define _CADIProtocol_h_

#include "sg/SGPort.h"
#include "eslapi/CADITypes.h"

namespace sg
{

// The CADI protocol is used forward CADI calls from the CADI interface 
// directly to a component or something else which implements a CADIProtocol.
// The CADIBase class implements this forwarding of calls so derived classes 
// do not need to do any forwarding themselves (if they want to forward the
// call at all).
    
class CADIProtocol: public Port
{
public:
    // connector instances

    // these slave behaviors are always called from the GUI/debugger thread
    // feel free to add more CADI functions here
    SlaveConnector< eslapi::CADIReturn_t (uint32_t, uint32_t, uint32_t*, eslapi::CADIParameterInfo_t*) > GetParameters;
    SlaveConnector< eslapi::CADIReturn_t (const std::string&, eslapi::CADIParameterInfo_t*) > GetParameterInfo;
    SlaveConnector< eslapi::CADIReturn_t (uint32_t, uint32_t *, eslapi::CADIParameterValue_t *) > GetParameterValues;
    SlaveConnector< eslapi::CADIReturn_t (uint32_t, eslapi::CADIParameterValue_t*, eslapi::CADIFactoryErrorMessage_t*) > SetParameters;    
    SlaveConnector< eslapi::CADIReturn_t (uint64_t&) > GetInstructionCount;
    SlaveConnector< eslapi::CADIReturn_t (uint64_t&, bool) > GetCycleCount;
    SlaveConnector< void (const std::string& ) > LoadApplicationFile;
    SlaveConnector< eslapi::CADIReturn_t (const std::string&, std::string&) > GetProperty; // propertyNameIn, valueOut
    SlaveConnector< void (std::map<std::string, std::string>&) > GetApplicationsAndCommandLineParams;
    MasterConnector< void (void) > simShutdown; 
    MasterConnector< void (uint32_t) > cadiRefresh; 
    
    // constructor
    CADIProtocol()
    {
        define_behaviour(GetParameters);
        define_behaviour(GetParameterInfo);
        define_behaviour(GetParameterValues);
        define_behaviour(SetParameters);
        define_behaviour(GetInstructionCount);
        define_behaviour(GetCycleCount);
        define_behaviour(LoadApplicationFile);
        define_behaviour(GetProperty);
        define_behaviour(GetApplicationsAndCommandLineParams);
        define_behaviour(simShutdown);
        define_behaviour(cadiRefresh);
    }
};
    
} // namespace sg

#endif /* ifndef _CADIProtocol_h_ */

