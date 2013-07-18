/*!
 * \file    SystemGenComponent.h
 * \date    Copyright 2002-2013 ARM Limited. All rights reserved.
 */

#ifndef SYSTEMGENCOMPONENT_H
#define SYSTEMGENCOMPONENT_H

#include "MxTypes.h"
#include <map>
#include "SGComponentWithPorts.h"
#include "sg/SGControlProtocol.h"
#include "sg/Attributes.h"
#include "sg/SGSimulationContext.h"
#include "sg/SGSchedulerInterfaceForComponents.h"
#include "CADIProtocol.h"
#include "MxIDataStream.h"
#include "MxODataStream.h"
#include "CADIBase.h"

namespace sg
{
    class EventSourceBase;    
}

class SystemGenComponent : public sg::ComponentWithPorts
{
public:
    SystemGenComponent(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~SystemGenComponent();
    
    // 'getInstanceName()' is a LISA keyword and a LISA langage feature, do not alter
    // (the implementation may be changed however)
    std::string getInstanceName() const { return getName(); }
    // get hierarchical instance name in CADI consistent way - without top component
    // (for top component itself - empty string)
    std::string getInstancePath() const;

    // default implementation of some behaviors
    // jo: these are dangerous as they suggest that this is an interface between components
    bool save(MxODataStream& /*os*/) {return true;}
    bool restore(MxIDataStream& /*is*/) {return true;}
    void step() {}
    void simShutdown();
    void cadiRefresh(uint32_t refreshReason);
    // this should be called by LISA components whenever a breakpoint is hit
    // (must always be called before the simHalt())
    void simBreakpointHit(uint32_t cadiBptNum);

    // MaxSim-style message functions for all SG components
    void message(const std::string &msg, sg::message::MessageType msgType);
    void message(sg::message::MessageType msgType, const char *fmt, ...) SG_FORMATSTR(printf, 3, 4);

    void addExtendedTargetFeature(const std::string &etf);

    void addTraceSource(sg::EventSourceBase *es);

    const std::string& getExtendedTargetFeatures() const { return extendedTargetFeatures; }

    // get global interface
    // (intended to be used from LISA to get a list of all components in the system from within any component)
    eslapi::CAInterface *getGlobalInterface();
    // get SCADI interface
    // (intended to be used from LISA to access the SCADI interface of the own component)
    eslapi::CADI *getSCADI();

    // Retrieve local time of currently running temporally decoupled thread.
    // Returns Local time in seconds.
    // This methods is intended to be used from LISA bridges to set the timing annotation on the forward path of
    // outgoing TLM transactions.
    //
    // WARNING! This method is not intended to be supported and will definitely change in future releases.
    double getCurrentLocalTime();

    // Set local time of currently running temporally decoupled thread.
    // This methods is intended to be used from LISA bridges to set the local time on the return path of outgoing
    // TLM transactions.
    //
    // WARNING! This method is not intended to be supported and will definitely change in future release.
    void setCurrentLocalTime(double);

protected:
    static MxS64             GetParameterValue(const sg::Params &params, 
                                               const std::string &param_name,
                                               MxS64 val_default,
                                               MxS64 min_val, MxS64 max_val);
    
    static const std::string GetParameterValue(const sg::Params &params,
                                        const std::string &param_name,
                                        const std::string &val_default);

protected:
    sg::SimulationContext* simulationContext__;
    sg::CADIBase* cadi__;
    // the following map allows to get an cadi interface of sub component my name
    std::map< std::string, eslapi::CAInterface* > componentName2CADI__;
    const sg::Params externParameters__;
    std::map<std::string,std::string> properties__; // contents of the properties section of this component

    // CADIPort (the CADI interface forwards some CADI calls to this port)
    sg::CADIProtocol cadiPort__;
     // applications loaded by the component and its command line params
    std::map<std::string, std::string> applications2params;

    sg::SchedulerInterfaceForComponents * sched__;
    void initScheduler();

private:
    void connectControlPorts(sg::ComponentBase *c);
    void disconnectControlPorts(sg::ComponentBase *c);
    void populateChildControlPort(sg::CADIMap &, const std::string&);

private:
    std::string extendedTargetFeatures;

    // Local clock frequency source for SystemGenComponent::setCurrentLocalTime().
    class FrequencySource: public sg::FrequencySource {

        // Construction
        public:
            explicit FrequencySource(double f): m_frequency(f) {}
            ~FrequencySource() {}

        // Accessors
        public:
            const char *getName() const { return "FrequencySource"; }
            void registerFrequencyObserver(sg::FrequencyObserver *) {}
            void unregisterFrequencyObserver(sg::FrequencyObserver *) {}
            double getFrequency() { return m_frequency; }

        // Implementation
        protected:
            void notifyFrequencyObservers() {}

        private:
            double m_frequency;
    };

public:
    sg::SGControlProtocol control_port;
    sg::SGControlProtocol child_control_port;
};

#endif

