/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   VEPBackendFactories.h
 *  \brief  Provides factories to instantiate alternative backends for VirtualEthernet 
 *  \date   Copyright ARM Limited 2011 All Rights Reserved.
 *  
 *  
 */

#ifndef INCLUDED_VEPBACKENDFACTORIES_H
#define INCLUDED_VEPBACKENDFACTORIES_H

#include <string>

class AsyncReader;
class protocol_VirtualEthernet;

namespace sg {

class SimulationContext;

AsyncReader* createVEPTunDevice(sg::SimulationContext* scontext,
                                const std::string& name,
                                protocol_VirtualEthernet* vep);

AsyncReader* createVEPUserNetDevice(sg::SimulationContext* scontext,
                                    const std::string& name,
                                    const std::string& userNetPorts,
                                    protocol_VirtualEthernet* vep);

}


#endif

/* eof VEPBackendFactories.h */
