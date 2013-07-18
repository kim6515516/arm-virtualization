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
 * Class definition for Component FVP_VE_Cortex_A15x1.
 */

#ifndef Component_Component__FVP_VE_Cortex_A15x1_ClassDef_h_
#define Component_Component__FVP_VE_Cortex_A15x1_ClassDef_h_

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

#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_cluster_of_ARMCortexA15x1CT_to_FVP_VE_Cortex_A15x1 : public ParameterFilter
{
public:
	ParameterFilter_cluster_of_ARMCortexA15x1CT_to_FVP_VE_Cortex_A15x1()
	{
		ovrd_params["PERIPHBASE"] = eslapi::CADIParameterInfo_t(0x10000000 | PARAMETERFILTER_FIXED, "PERIPHBASE",eslapi::CADI_PARAM_INT, "Base address of peripheral memory space",0,MxS64CONST(0x0),MxS64CONST(0xffffffff),MxS64CONST(0x13080000), "0x13080000" );
		ovrd_params["cpu0.semihosting-heap_base"] = eslapi::CADIParameterInfo_t(0x10000001, "cpu0.semihosting-heap_base",eslapi::CADI_PARAM_INT, "Virtual address of heap base ",0,MxS64CONST(0x0),MxS64CONST(0xffffffff),MxS64CONST(0x0), "0x00000000" );
		ovrd_params["cpu0.semihosting-heap_limit"] = eslapi::CADIParameterInfo_t(0x10000002, "cpu0.semihosting-heap_limit",eslapi::CADI_PARAM_INT, "Virtual address of top of heap ",0,MxS64CONST(0x0),MxS64CONST(0xffffffff),MxS64CONST(0xff000000), "0xff000000" );
		ovrd_params["cpu0.semihosting-stack_base"] = eslapi::CADIParameterInfo_t(0x10000003, "cpu0.semihosting-stack_base",eslapi::CADI_PARAM_INT, "Virtual address of base of descending stack ",0,MxS64CONST(0x0),MxS64CONST(0xffffffff),MxS64CONST(0xffff0000), "0xffff0000" );
		ovrd_params["cpu0.semihosting-stack_limit"] = eslapi::CADIParameterInfo_t(0x10000004, "cpu0.semihosting-stack_limit",eslapi::CADI_PARAM_INT, "Virtual address of stack limit ",0,MxS64CONST(0x0),MxS64CONST(0xffffffff),MxS64CONST(0xff000000), "0xff000000" );
	}
};

class ParameterFilter_motherboard_of_VEMotherBoard_to_FVP_VE_Cortex_A15x1 : public ParameterFilter
{
public:
	ParameterFilter_motherboard_of_VEMotherBoard_to_FVP_VE_Cortex_A15x1()
	{
		ovrd_params["proc_id0"] = eslapi::CADIParameterInfo_t(0x10000005, "proc_id0",eslapi::CADI_PARAM_INT, "Processor ID at CoreTile Express Site 1",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x14000000), "0x14000000" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__FVP_VE_Cortex_A15x1: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *cluster;
	Component__VEMotherBoard *motherboard;
	Component__VEDaughterBoard *daughterboard;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_cluster__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_motherboard__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_daughterboard__;


    // abstract ports


    // resources
    std::string application_pathname;



    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__FVP_VE_Cortex_A15x1(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__FVP_VE_Cortex_A15x1();

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

	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	void init();
	void terminate();
	void reset(int level);
	void reset(int level, int /*argc*/, char** /*argv*/);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();

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


	ParameterFilter_cluster_of_ARMCortexA15x1CT_to_FVP_VE_Cortex_A15x1 parameterFilter_cluster_of_ARMCortexA15x1CT_to_FVP_VE_Cortex_A15x1__;
	ParameterFilter_motherboard_of_VEMotherBoard_to_FVP_VE_Cortex_A15x1 parameterFilter_motherboard_of_VEMotherBoard_to_FVP_VE_Cortex_A15x1__;


	CADIParameterProxy *cadiParameterProxy_cluster_of_ARMCortexA15x1CT_to_FVP_VE_Cortex_A15x1__;
	CADIParameterProxy *cadiParameterProxy_motherboard_of_VEMotherBoard_to_FVP_VE_Cortex_A15x1__;


    // definition of parameter IDs as constants for use in parameter access functions




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

