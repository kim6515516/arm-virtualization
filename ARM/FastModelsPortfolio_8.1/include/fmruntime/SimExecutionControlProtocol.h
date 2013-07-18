/*!
 * \file    SimExecutionControlProtocol.h
 * \date    Copyright ARM Limited 2006 All Rights Reserved.
 *
 */

#ifndef _SimExecutionControlProtocol_h_
#define _SimExecutionControlProtocol_h_

#include "sg/SGPort.h"

namespace eslapi { class CAInterface; };

namespace sg
{

class SimExecutionControlProtocolSystemGen: public Port
{
public:
    // connector instances
    
    // the slave behaviors are always called from the simulator thread
    SlaveConnector< void (void) > stop;
    SlaveConnector< void (const std::string&) > stopAndFatalError;
    SlaveConnector< void (void) > simShutdown;
    SlaveConnector< void (const char *message) > simMessage;
    SlaveConnector< void (void) > simKilled;
    SlaveConnector< eslapi::CAInterface* (void) > getGlobalInterface;

    // constructor
    SimExecutionControlProtocolSystemGen()
    {
        define_behaviour(stop);
        define_behaviour(stopAndFatalError);
        define_behaviour(simShutdown);
        define_behaviour(simMessage);
        define_behaviour(simKilled);
        define_behaviour(getGlobalInterface);
    }
};

} // namespace sg

#endif /* ifndef _SimExecutionControlProtocol_h_ */

