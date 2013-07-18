/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2007 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Abstract interface class protocol_Builtin__ControlProtocol for protocol Builtin__ControlProtocol.
 */

#ifndef protocol_Builtin__ControlProtocol_h_
#define protocol_Builtin__ControlProtocol_h_

// Includes from the 'includes' section of this protocol


#include <map>
#include <sg/SGControlProtocol.h>
		namespace maxsim
		{
			class MxDI;
		}
		class SimulationEngine;
	
#line 31 "./Linux-Release-GCC-4.1/gen/protocol_Builtin__ControlProtocol.h"


// Abstract interface for protocol Builtin__ControlProtocol
class protocol_Builtin__ControlProtocol
{
public:
        virtual ~protocol_Builtin__ControlProtocol() {}
        // Abstract protocol members
	virtual void configure(const sg::Params& params) = 0;
	virtual void init() = 0;
	virtual void interconnect() = 0;
	virtual void reset(int level) = 0;
	virtual void loadApplicationFile(const std::string& filename) = 0;
	virtual void disconnect() = 0;
	virtual void terminate() = 0;
	virtual bool save(MxODataStream& os) = 0;
	virtual bool restore(MxIDataStream& is) = 0;
	virtual void populateCADIMap(std::map<std::string,eslapi::CAInterface *> & , const std::string& ) = 0;
	virtual void step() = 0;
	virtual void update() = 0;
	virtual void communicate() = 0;
	virtual std::string getProperty(const std::string& ) = 0;
	virtual void traceEndOfCycle() = 0;
	virtual std::string bypass(const std::string& ) = 0;
	virtual std::string callSimEngine(const std::string& ) = 0;
	virtual void run() = 0;
	virtual void stop() = 0;
	virtual void idle() = 0;
	virtual void quit() = 0;
	virtual void setSimulationEngine(SimulationEngine* ) = 0;
	virtual void message(const std::string& msg, sg::message::MessageType msgType) = 0;

};

#endif /* protocol_Builtin__ControlProtocol_h_ */

