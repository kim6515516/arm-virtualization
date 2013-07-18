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
 * Class definition for Component TZSwitch.
 */

#ifndef Component_Component__TZSwitch_ClassDef_h_
#define Component_Component__TZSwitch_ClassDef_h_

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

#line 81 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/TZSwitch.lisa"

    
        #include "pv/PVBusMapper.h"

        #include <cassert>
    
#line 44 "./Linux64-Release-GCC-4.4/gen/Component__TZSwitch_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBusMapperControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TZSwitchControl_ClassDef.h"



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
Component__TZSwitch: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *pvbus_mapper;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pvbus_mapper__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVBus pvbus_input;
	FVP_VE_Cortex_A15x1__PVBus pvbus_port_a;
	FVP_VE_Cortex_A15x1__PVBus pvbus_port_b;
	FVP_VE_Cortex_A15x1__TZSwitchControl control;
	FVP_VE_Cortex_A15x1__PVBusMapperControl mapper_control;


    // resources
    std::string application_pathname;


#line 89 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/TZSwitch.lisa"

        uint32_t  secure      ;
        uint32_t  normal      ;

        // Use a struct so that state can be initialised at component construction
        struct Route
        {
            unsigned secure;
            unsigned normal;

            Route() : secure(TZROUTE_TO_PORT_A), normal(TZROUTE_TO_PORT_B) {}
        };

        Route  route;

        enum
        {
            PORT_A = 0,
            PORT_B = 1
        };
    
#line 115 "./Linux64-Release-GCC-4.4/gen/Component__TZSwitch_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__TZSwitch(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__TZSwitch();

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

	void init();
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	void terminate();
	void reset(int level);
	void reset(int level, int /*argc*/, char** /*argv*/);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	void abstract_port__control__routeAccesses(TZSwitch_InputFilter input, TZSwitch_RouteOption destination);
	unsigned abstract_port__mapper_control__remap(pv::RemapRequest& req);

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
	enum
	{
		PARAMETER_ID_secure = 0x1000000B,
		PARAMETER_ID_normal = 0x1000000C,
	};




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

