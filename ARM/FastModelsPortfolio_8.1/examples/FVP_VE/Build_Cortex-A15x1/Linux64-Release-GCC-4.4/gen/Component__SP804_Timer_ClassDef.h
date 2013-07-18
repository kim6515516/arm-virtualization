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
 * Class definition for Component SP804_Timer.
 */

#ifndef Component_Component__SP804_Timer_ClassDef_h_
#define Component_Component__SP804_Timer_ClassDef_h_

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

#line 21 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP804_Timer.lisa"

    
        #include "pv/PVBus.h"
        #include <stdio.h>
        #define SP804_TRACE if (!0) ; else printf
    
#line 44 "./Linux64-Release-GCC-4.4/gen/Component__SP804_Timer_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockRateControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVDevice_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_busslave_of_PVBusSlave_to_SP804_Timer : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_SP804_Timer()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__SP804_Timer: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *clk_div1;
	sg::ComponentBase *clk_div0;
	sg::ComponentBase *busslave;
	Component__CounterModule *counter0;
	Component__CounterModule *counter1;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clk_div1__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clk_div0__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_counter0__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_counter1__;


    // abstract ports
	FVP_VE_Cortex_A15x1__Signal irq_out0;
	FVP_VE_Cortex_A15x1__Signal irq_out1;
	FVP_VE_Cortex_A15x1__ClockSignal clock;
	FVP_VE_Cortex_A15x1__ClockRateControl timer_en[2];
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__PVDevice device;


    // resources
    std::string application_pathname;


#line 40 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP804_Timer.lisa"


        MxU32  Timer1Load     ;
        MxU32  Timer1Value     ;
        MxU32  Timer1Control     ;
        MxU32  Timer1IntClr     ;
        MxU32  Timer1RIS     ;
        MxU32  Timer1MIS     ;
        MxU32  Timer1BGLoad     ;

        MxU32  Timer2Load     ;
        MxU32  Timer2Value     ;
        MxU32  Timer2Control     ;
        MxU32  Timer2IntClr     ;
        MxU32  Timer2RIS     ;
        MxU32  Timer2MIS     ;
        MxU32  Timer2BGLoad     ;
    
#line 132 "./Linux64-Release-GCC-4.4/gen/Component__SP804_Timer_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__SP804_Timer(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__SP804_Timer();

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

	uint32_t registerRead(pv::bus_addr_t device_addr);
	void registerWrite(pv::bus_addr_t device_addr, uint32_t data);
	AccessFuncResult debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects);
	AccessFuncResult debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects);
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
	pv::Tx_Result abstract_port__device__read(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__device__write(pv::WriteTransaction tx);
	pv::Tx_Result abstract_port__device__debugRead(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__device__debugWrite(pv::WriteTransaction tx);

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


	ParameterFilter_busslave_of_PVBusSlave_to_SP804_Timer parameterFilter_busslave_of_PVBusSlave_to_SP804_Timer__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_SP804_Timer__;


    // definition of parameter IDs as constants for use in parameter access functions


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_Timer1Load = 0x00000000,
		REGISTER_ID_Timer1Value = 0x00000004,
		REGISTER_ID_Timer1Control = 0x00000008,
		REGISTER_ID_Timer1IntClr = 0x0000000c,
		REGISTER_ID_Timer1RIS = 0x00000010,
		REGISTER_ID_Timer1MIS = 0x00000014,
		REGISTER_ID_Timer1BGLoad = 0x00000018,
		REGISTER_ID_Timer2Load = 0x00000020,
		REGISTER_ID_Timer2Value = 0x00000024,
		REGISTER_ID_Timer2Control = 0x00000028,
		REGISTER_ID_Timer2IntClr = 0x0000002c,
		REGISTER_ID_Timer2RIS = 0x00000030,
		REGISTER_ID_Timer2MIS = 0x00000034,
		REGISTER_ID_Timer2BGLoad = 0x00000038,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

