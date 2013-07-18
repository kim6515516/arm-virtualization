/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2005 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Class definition for protocol FVP_VE_Cortex_A15x1__Builtin__ControlProtocol.
 */

#ifndef FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef_h_
#define FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <list>
#include "sg/SGPort.h"

#include "protocol_Builtin__ControlProtocol.h"

namespace FVP_VE_Cortex_A15x1_NMS {

class FVP_VE_Cortex_A15x1__Builtin__ControlProtocol;

// Abstract interface implementation for port
class protocol_Builtin__ControlProtocol__Implementation: public protocol_Builtin__ControlProtocol
{
public:
    protocol_Builtin__ControlProtocol__Implementation(): thisPort(0) {}

    void SetPort(FVP_VE_Cortex_A15x1__Builtin__ControlProtocol *port) { thisPort = port; }

    // Protocol members
	inline void configure(const sg::Params& params);
	inline void init();
	inline void interconnect();
	inline void reset(int level);
	inline void loadApplicationFile(const std::string& filename);
	inline void disconnect();
	inline void terminate();
	inline bool save(MxODataStream& os);
	inline bool restore(MxIDataStream& is);
	inline void populateCADIMap(std::map<std::string,eslapi::CAInterface *> & , const std::string& );
	inline void step();
	inline void update();
	inline void communicate();
	inline std::string getProperty(const std::string& );
	inline void traceEndOfCycle();
	inline std::string bypass(const std::string& );
	inline std::string callSimEngine(const std::string& );
	inline void run();
	inline void stop();
	inline void idle();
	inline void quit();
	inline void setSimulationEngine(SimulationEngine* );
	inline void message(const std::string& msg, sg::message::MessageType msgType);


private:
    // Parent port this interface belongs to.
    FVP_VE_Cortex_A15x1__Builtin__ControlProtocol *thisPort;
};


// Protocol (port) class definition
class FVP_VE_Cortex_A15x1__Builtin__ControlProtocol: public sg::Port
{
private:
    
public:
    // Resources


    // Connector instances
	sg::SlaveConnector< void (const sg::Params&) > configure;
	sg::SlaveConnector< void (void) > init;
	sg::SlaveConnector< void (void) > interconnect;
	sg::SlaveConnector< void (int) > reset;
	sg::SlaveConnector< void (const std::string&) > loadApplicationFile;
	sg::SlaveConnector< void (void) > disconnect;
	sg::SlaveConnector< void (void) > terminate;
	sg::SlaveConnector< bool (MxODataStream&) > save;
	sg::SlaveConnector< bool (MxIDataStream&) > restore;
	sg::SlaveConnector< void (std::map<std::string,eslapi::CAInterface *> &,const std::string&) > populateCADIMap;
	sg::SlaveConnector< void (void) > step;
	sg::SlaveConnector< void (void) > update;
	sg::SlaveConnector< void (void) > communicate;
	sg::SlaveConnector< std::string (const std::string&) > getProperty;
	sg::SlaveConnector< void (void) > traceEndOfCycle;
	sg::SlaveConnector< std::string (const std::string&) > bypass;
	sg::MasterConnector< std::string (const std::string&) > callSimEngine;
	sg::SlaveConnector< void (void) > run;
	sg::SlaveConnector< void (void) > stop;
	sg::PeerConnector< void (void) > idle;
	sg::MasterConnector< void (void) > quit;
	sg::SlaveConnector< void (SimulationEngine*) > setSimulationEngine;
	sg::MasterConnector< void (const std::string&,sg::message::MessageType) > message;


    FVP_VE_Cortex_A15x1__Builtin__ControlProtocol()
    {
        abstractInterface__.SetPort(this);
		define_behaviour(configure);
		define_behaviour(init);
		define_behaviour(interconnect);
		define_behaviour(reset);
		define_behaviour(loadApplicationFile);
		define_behaviour(disconnect);
		define_behaviour(terminate);
		define_behaviour(save);
		define_behaviour(restore);
		define_behaviour(populateCADIMap);
		define_behaviour(step);
		define_behaviour(update);
		define_behaviour(communicate);
		define_behaviour(getProperty);
		define_behaviour(traceEndOfCycle);
		define_behaviour(bypass);
		define_behaviour(callSimEngine);
		define_behaviour(run);
		define_behaviour(stop);
		define_behaviour(idle);
		define_behaviour(quit);
		define_behaviour(setSimulationEngine);
		define_behaviour(message);


    }

    // Set name (currently ignored here)
    void SetName__(const char *) {}

    // Abstract port interface for non-LISA C++ components
    protocol_Builtin__ControlProtocol__Implementation abstractInterface__;

    // Get abstract interface for non-LISA C++ components
    protocol_Builtin__ControlProtocol *getAbstractInterface() { return &abstractInterface__; }
};


// Abstract interface implementations
inline void protocol_Builtin__ControlProtocol__Implementation::configure(const sg::Params& params)
{
	return thisPort->configure(params);
}

inline void protocol_Builtin__ControlProtocol__Implementation::init()
{
	return thisPort->init();
}

inline void protocol_Builtin__ControlProtocol__Implementation::interconnect()
{
	return thisPort->interconnect();
}

inline void protocol_Builtin__ControlProtocol__Implementation::reset(int level)
{
	return thisPort->reset(level);
}

inline void protocol_Builtin__ControlProtocol__Implementation::loadApplicationFile(const std::string& filename)
{
	return thisPort->loadApplicationFile(filename);
}

inline void protocol_Builtin__ControlProtocol__Implementation::disconnect()
{
	return thisPort->disconnect();
}

inline void protocol_Builtin__ControlProtocol__Implementation::terminate()
{
	return thisPort->terminate();
}

inline bool protocol_Builtin__ControlProtocol__Implementation::save(MxODataStream& os)
{
	return thisPort->save(os);
}

inline bool protocol_Builtin__ControlProtocol__Implementation::restore(MxIDataStream& is)
{
	return thisPort->restore(is);
}

inline void protocol_Builtin__ControlProtocol__Implementation::populateCADIMap(std::map<std::string,eslapi::CAInterface *> & param0__, const std::string& param1__)
{
	return thisPort->populateCADIMap(param0__, param1__);
}

inline void protocol_Builtin__ControlProtocol__Implementation::step()
{
	return thisPort->step();
}

inline void protocol_Builtin__ControlProtocol__Implementation::update()
{
	return thisPort->update();
}

inline void protocol_Builtin__ControlProtocol__Implementation::communicate()
{
	return thisPort->communicate();
}

inline std::string protocol_Builtin__ControlProtocol__Implementation::getProperty(const std::string& param0__)
{
	return thisPort->getProperty(param0__);
}

inline void protocol_Builtin__ControlProtocol__Implementation::traceEndOfCycle()
{
	return thisPort->traceEndOfCycle();
}

inline std::string protocol_Builtin__ControlProtocol__Implementation::bypass(const std::string& param0__)
{
	return thisPort->bypass(param0__);
}

inline std::string protocol_Builtin__ControlProtocol__Implementation::callSimEngine(const std::string& param0__)
{
	return thisPort->callSimEngine(param0__);
}

inline void protocol_Builtin__ControlProtocol__Implementation::run()
{
	return thisPort->run();
}

inline void protocol_Builtin__ControlProtocol__Implementation::stop()
{
	return thisPort->stop();
}

inline void protocol_Builtin__ControlProtocol__Implementation::idle()
{
	return thisPort->idle();
}

inline void protocol_Builtin__ControlProtocol__Implementation::quit()
{
	return thisPort->quit();
}

inline void protocol_Builtin__ControlProtocol__Implementation::setSimulationEngine(SimulationEngine* param0__)
{
	return thisPort->setSimulationEngine(param0__);
}

inline void protocol_Builtin__ControlProtocol__Implementation::message(const std::string& msg, sg::message::MessageType msgType)
{
	return thisPort->message(msg, msgType);
}




// Mapping object
// (these ports are implemented inside FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort)
class FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort: public FVP_VE_Cortex_A15x1__Builtin__ControlProtocol
{
public:
    // constructor
    FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort(MxU32 inFirst,
                                                 MxU32 inLast,
                                                 MxU32 outFirst,
                                                 MxU32 outLast):
    inFirst__(inFirst),
    inLast__(inLast),
    outFirst__(outFirst),
    outSize__(outLast - outFirst + 1)
    {
    }

    bool isCovered__(MxU32 address) const
    {
        return (address >= inFirst__) && (address <= inLast__);
    }

    void remapAddress__(MxU32 &address) const
    {
        if(outSize__)
            address = ((address - inFirst__) % outSize__) + outFirst__;
    }

private:
    MxU32 inFirst__;
    MxU32 inLast__;
    MxU32 outFirst__;
    MxU32 outSize__;
};


// Addressable protocol class definition
class FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort: public FVP_VE_Cortex_A15x1__Builtin__ControlProtocol
{
public:
    declare_slave_behaviour(mapRange, sg::Port*(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast));
    declare_slave_behaviour(mapDefault, sg::Port*());
    declare_slave_behaviour(unmapRange, void(sg::Port*));
    declare_slave_behaviour(isMapped, bool(MxU64));

    FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort():
    defaultOutPort__(0),
    portName__("(unknown name)")
    {
        define_behaviour(mapRange);
        define_behaviour(mapDefault);
        define_behaviour(unmapRange);
        define_behaviour(isMapped);
        bind_method(*this, mapRange, &FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort::mapRange__, this);
        bind_method(*this, mapDefault, &FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort::mapDefault__, this);
        bind_method(*this, unmapRange, &FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort::unmapRange__, this);
        bind_method(*this, isMapped, &FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort::isMapped__, this);

    }

    ~FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort()
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
            delete *it;
        delete defaultOutPort__;
    }

    void SetName__(const char *name) { portName__ = name; }

    FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort *locateOutPort__(MxU32 &addr)
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
        {
            if ((*it)->isCovered__(addr)) {
                (*it)->remapAddress__(addr);
                return *it;
            }
        }
        return defaultOutPort__;
    }

    sg::Port* mapRange__(MxU64 inFirst, MxU64 inLast, MxU64 outFirst, MxU64 outLast)
    {
        FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort *masterPort =
            new FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort(inFirst, inLast, outFirst, outLast);
		this->configure.connectTo(&masterPort->configure);
		this->init.connectTo(&masterPort->init);
		this->interconnect.connectTo(&masterPort->interconnect);
		this->reset.connectTo(&masterPort->reset);
		this->loadApplicationFile.connectTo(&masterPort->loadApplicationFile);
		this->disconnect.connectTo(&masterPort->disconnect);
		this->terminate.connectTo(&masterPort->terminate);
		this->save.connectTo(&masterPort->save);
		this->restore.connectTo(&masterPort->restore);
		this->populateCADIMap.connectTo(&masterPort->populateCADIMap);
		this->step.connectTo(&masterPort->step);
		this->update.connectTo(&masterPort->update);
		this->communicate.connectTo(&masterPort->communicate);
		this->getProperty.connectTo(&masterPort->getProperty);
		this->traceEndOfCycle.connectTo(&masterPort->traceEndOfCycle);
		this->bypass.connectTo(&masterPort->bypass);
		this->callSimEngine.connectTo(&masterPort->callSimEngine);
		this->run.connectTo(&masterPort->run);
		this->stop.connectTo(&masterPort->stop);
		this->idle.connectTo(&masterPort->idle);
		this->quit.connectTo(&masterPort->quit);
		this->setSimulationEngine.connectTo(&masterPort->setSimulationEngine);
		this->message.connectTo(&masterPort->message);

        // push_front() because the first statement should have the lowest priority and the last statement should have the
        // highest priority, like PVBusDecoder
        outPortList__.push_front(masterPort);
        return masterPort;
    }

    // map default slave
    sg::Port* mapDefault__()
    {
        delete defaultOutPort__;
        defaultOutPort__ = new FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort(0, MxU32(0) - 1, 0, MxU32(0) - 1);
        return defaultOutPort__;
    }

    void unmapRange__(sg::Port* port)
    {
        outPortList__.remove((FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort*)port);
        if(defaultOutPort__ == port)
        {
            delete defaultOutPort__;
            defaultOutPort__ = 0;
        }
    }

    bool isMapped__(MxU64 addr)
    {
        OutPortList__::iterator it;
        for (it = outPortList__.begin(); it != outPortList__.end(); ++it)
        {
            if ((*it)->isCovered__(static_cast<MxU32>(addr)))
                return true;
        }
        return false;
    }

    // Wrapper functions for protocol behaviors


private:
    typedef std::list<FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort*> OutPortList__;
    OutPortList__ outPortList__;
    FVP_VE_Cortex_A15x1__Builtin__ControlProtocol__AddressablePort_OutPort *defaultOutPort__;
    const char *portName__;
};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

