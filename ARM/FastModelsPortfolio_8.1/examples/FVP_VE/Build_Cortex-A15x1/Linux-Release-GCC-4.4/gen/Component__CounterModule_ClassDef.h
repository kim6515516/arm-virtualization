/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2006 ARM Limited.
 * Copyright 2011 ARM LImited.
 *
 * All rights reserved.
 */

/** \file
 * Class definition for Component CounterModule.
 */

#ifndef Component_Component__CounterModule_ClassDef_h_
#define Component_Component__CounterModule_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <limits.h>
#include <map>
#include <fstream>
#include "SystemGenComponent.h"
#include "CADIBase.h"
#include "ComponentRegister.h"
#include "ResourceAccessFuncTypes.h"
#include "CADIParameterProxy.h"
#include "ParameterFilter.h"
#include "sg/SGTargetInfo.h"
#include "FVP_VE_Cortex_A15x1_DSO.h"

using namespace std;

#line 33 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/CounterModule.lisa"
 
        #include "pv/PVBus.h"
    
#line 41 "./Linux-Release-GCC-4.4/gen/Component__CounterModule_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerCallback_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerControl_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__CounterModule: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *timer;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer__;


    // abstract ports
	FVP_VE_Cortex_A15x1__Signal intr_out;
	FVP_VE_Cortex_A15x1__ClockSignal clk_in;
	FVP_VE_Cortex_A15x1__TimerControl timer_control;
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback_handler;


    // resources
    std::string application_pathname;


#line 48 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/CounterModule.lisa"

        enum { MODE_FREE_RUNNING, MODE_PERIODIC_RELOAD } mode;

        uint32_t load;
        uint64_t reload_time;
        bool enabled;
        bool ie;  // interrupt enable flag
        int prescale;
        int timersize;
        bool oneshot;
        bool rawinterrupt;
        int shift;

        // The number of clock ticks that will be remaining when the next callback from the ClockTimer is generated.
        uint64_t clocktick_counter;
    
#line 107 "./Linux-Release-GCC-4.4/gen/Component__CounterModule_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__CounterModule(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__CounterModule();

    // interface functions
    sg::SimulationContext* getSimulationContext() const { return simulationContext__; }

    // control port implementation
    void control_port__configure(const sg::Params& params);
    void control_port__loadApplicationFile(const std::string& filename);
    std::string control_port__getProperty(const std::string& propname);
    std::string control_port__bypass(const std::string&);
    void control_port__run();
    void control_port__stop();
    void control_port__idle();
    void control_port__quit();
    void control_port__getMxDI(std::map<std::string,eslapi::CADI*>*);
    void control_port__setSimulationEngine(SimulationEngine*);
    void control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* > &, std::string const &);
    void control_port__message(const std::string &msg, sg::message::MessageType msgType);
    std::string control_port__callSimEngine(const std::string&);
    void control_port__reset(int level);
    void control_port__terminate();

    // CADI Port implementations
    eslapi::CADIReturn_t cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params);
    eslapi::CADIReturn_t cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param);
    eslapi::CADIReturn_t cadiPort__GetParameterValues (uint32_t parameterCount, uint32_t *actualNumOfParamsRead, eslapi::CADIParameterValue_t *paramValuesOut);
    eslapi::CADIReturn_t cadiPort__SetParameters(uint32_t count, eslapi::CADIParameterValue_t *params, eslapi::CADIFactoryErrorMessage_t *error);
    eslapi::CADIReturn_t cadiPort__GetProperty(const std::string& propertyName, std::string &value);
    void cadiPort__LoadApplicationFile(const std::string& filename);
    void cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_);

    // helper functions
    void insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface*>&componentName2CADI);

    sg::accessfunc::AccessFuncResult parameter_read_func(uint32_t id, int64_t *data);
    sg::accessfunc::AccessFuncResult parameter_read_string_func(uint32_t id, std::string &data);
    sg::accessfunc::AccessFuncResult parameter_write_func(uint32_t id, const int64_t *data);
    sg::accessfunc::AccessFuncResult parameter_write_string_func(uint32_t id, const std::string &data);

    // dummy functions, mostly required by IsimMain (formerly InterpreterMain), will go away soon

    // May be required by TraceGen however that itself is obsolete
    MxU64 getInstructionCount() const { return 0; }
    // May be required by SystemGen however that itself is obsolete
    MxU64 getCycleCount() const { return 0; }

	void reset(int level);
	void setLoadRegister(uint32_t newLoadValue);
	uint32_t getLoadRegister();
	uint32_t getControlRegister();
	void setControlRegister(uint32_t controlValue);
	uint32_t getValueRegister();
	uint32_t getBGLoadRegister();
	void setBGLoadRegister(uint32_t loadValue);
	uint32_t calculateRescheduleTicks();
	void initTimer();
	uint32_t getRawIntStatus();
	bool getMaskedIntStatus();
	void clearInt();
	void setInt();
	uint32_t handleTimerSignal();
	void getClockTickCounterValue();
	uint32_t registerRead(pv::bus_addr_t addr);
	void registerWrite(pv::bus_addr_t addr, uint32_t data);
	void init();
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	void terminate();
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	uint32_t abstract_port__timer_callback_handler__signal();

    void simHalt();
    void simRun();
    bool simIsRunning();
    void simShutdown();
    void simReset(uint32_t level);


private:
    // methods
    eslapi::CADI* obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const;
    static bool ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy,
                                                    const char *param_name,
                                                    int64_t intVal,
                                                    const char *strVal);
    uint32_t paramNameToParamAccessFuncID(const std::string &name);

    void reset_resources__();
    void freeCADIResources__();






    // definition of parameter IDs as constants for use in parameter access functions




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

