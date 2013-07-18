 /*!
 * \file    SGControlProtocol.h
 * \brief   Internal port protocol used to connect hierarchy
 *          of SystemGenerator components.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 *          Copyright 2013 ARM Limited. All rights reserved.
 *
 * This file defines the port protocol used on the system '$control'
 * ports implemented by all components.
 */

#ifndef ARM_SG_CONTROL_PROTOCOL_H
#define ARM_SG_CONTROL_PROTOCOL_H

#include <map>
#include <string>

#include "sg/SGPort.h"
#include "sg/SGParams.h"

class MxIDataStream;
class MxODataStream;

class SimulationEngine;

namespace eslapi {
    class CAInterface;
} // namespace eslapi

namespace sg {

namespace message
{
    enum MessageTypeEnum
    {
        MSG_FATAL_ERROR = -2,
        MSG_ERROR = -1,
        MSG_WARNING = 0,
        MSG_INFO = 1,
        MSG_DEBUG = 2
    };

    typedef int MessageType;
} // namespace message

typedef std::map< std::string, eslapi::CAInterface* > CADIMap;

// protocol class definition
class SGControlProtocol : public Port
{
public:
    // connector instances
    SlaveConnector< void (const Params&) > configure;
    SlaveConnector< void (void) > init;
    SlaveConnector< void (void) > interconnect;
    SlaveConnector< void (void) > postConnect;
    SlaveConnector< void (int) > reset;
    SlaveConnector< void (const std::string&) > loadApplicationFile;
    SlaveConnector< void (void) > disconnect;
    SlaveConnector< void (void) > terminate;
    SlaveConnector< bool (MxODataStream&) > save;
    SlaveConnector< bool (MxIDataStream&) > restore;
    SlaveConnector< void  (CADIMap &, std::string const &prefix) > populateCADIMap;
    SlaveConnector< void (void) > refresh;
    SlaveConnector< void (void) > step;
    SlaveConnector< void (void) > update;
    SlaveConnector< void (void) > communicate;
    SlaveConnector< std::string (const std::string&) > getProperty;
    SlaveConnector< void (void) > traceEndOfCycle;               // for MaxSim or single steppied model only
    SlaveConnector< std::string (const std::string&) > bypass;

    MasterConnector< std::string (const std::string&) > callSimEngine;

    // event-driven simulation engine
    SlaveConnector< void (void) > run;
    SlaveConnector< void (void) > stop; // asynchronous?
    PeerConnector< void (void) > idle;
    MasterConnector< void (void) > quit;
    SlaveConnector< void (SimulationEngine*) > setSimulationEngine;
    MasterConnector< void (const std::string&, message::MessageType) > message;
    SlaveConnector< void (const std::string&, const std::string&, const std::string&) > setParameterAttribute;

    // constructor
    SGControlProtocol()
    {
        define_behaviour(configure);
        define_behaviour(init);
        define_behaviour(interconnect);
        define_behaviour(postConnect);
        define_behaviour(reset);
        define_behaviour(loadApplicationFile);
        define_behaviour(disconnect);
        define_behaviour(terminate);
        define_behaviour(save);
        define_behaviour(restore);
        define_behaviour(populateCADIMap);
        define_behaviour(refresh);
        define_behaviour(step);
        define_behaviour(update);   
        define_behaviour(communicate);
        define_behaviour(getProperty);
        define_behaviour(traceEndOfCycle);
        define_behaviour(bypass);

        define_behaviour(callSimEngine);
        
        // event-driven simulation engine
        define_behaviour(run);
        define_behaviour(stop);
        define_behaviour(idle);
        define_behaviour(quit);
        define_behaviour(setSimulationEngine);
        define_behaviour(message);
        define_behaviour(setParameterAttribute);
    }
};

} // namespace sg

#endif /* ifndef ARM_SG_CONTROL_PROTOCOL_H */
