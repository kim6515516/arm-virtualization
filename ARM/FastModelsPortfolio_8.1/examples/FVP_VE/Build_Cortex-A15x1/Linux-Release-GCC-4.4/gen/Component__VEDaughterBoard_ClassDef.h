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
 * Class definition for Component VEDaughterBoard.
 */

#ifndef Component_Component__VEDaughterBoard_ClassDef_h_
#define Component_Component__VEDaughterBoard_ClassDef_h_

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
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__LCD_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBusMapperControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__VECBProtocol_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_sram_of_RAMDevice_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_sram_of_RAMDevice_to_VEDaughterBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_clockdivider_of_ClockDivider_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_clockdivider_of_ClockDivider_to_VEDaughterBoard()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FIXED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" );
	}
};

class ParameterFilter_clockCLCD_of_ClockDivider_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_clockCLCD_of_ClockDivider_to_VEDaughterBoard()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FIXED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" );
	}
};

class ParameterFilter_dram_of_RAMDevice_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_dram_of_RAMDevice_to_VEDaughterBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_secureRO_of_IntelStrataFlashJ3_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_secureRO_of_IntelStrataFlashJ3_to_VEDaughterBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x4),MxS64CONST(0xffffffff),MxS64CONST(0x1000), "0x1000" );
	}
};

class ParameterFilter_secureSRAM_of_RAMDevice_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_secureSRAM_of_RAMDevice_to_VEDaughterBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_secureDRAM_of_RAMDevice_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_secureDRAM_of_RAMDevice_to_VEDaughterBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_dmc_of_RAMDevice_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_dmc_of_RAMDevice_to_VEDaughterBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_dmc_phy_of_RAMDevice_to_VEDaughterBoard : public ParameterFilter
{
public:
	ParameterFilter_dmc_phy_of_RAMDevice_to_VEDaughterBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__VEDaughterBoard: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *pvbusdecoder;
	sg::ComponentBase *coresight_mapper;
	Component__RAMDevice *sram;
	Component__VEDCC *vedcc;
	sg::ComponentBase *clockdivider;
	sg::ComponentBase *clockCLCD;
	Component__RAMDevice *dram;
	Component__TZSwitch *dram_aliased;
	Component__TZSwitch *dram_limit_4;
	Component__TZSwitch *dram_limit_8;
	Component__VEInterruptMapper *introuter;
	Component__TZSwitch *secure_region;
	Component__TZSwitch *nonsecure_region;
	sg::ComponentBase *securitydecoder;
	sg::ComponentBase *securepvbusdecoder;
	Component__IntelStrataFlashJ3 *secureRO;
	Component__FlashLoader *secureROloader;
	Component__RAMDevice *secureSRAM;
	Component__RAMDevice *secureDRAM;
	Component__PL370_HDLCD *hdlcd;
	Component__RAMDevice *dmc;
	Component__RAMDevice *dmc_phy;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pvbusdecoder__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_coresight_mapper__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_sram__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_vedcc__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clockdivider__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clockCLCD__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dram__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dram_aliased__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dram_limit_4__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dram_limit_8__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_introuter__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_secure_region__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_nonsecure_region__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_securitydecoder__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_securepvbusdecoder__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_secureRO__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_secureROloader__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_secureSRAM__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_secureDRAM__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_hdlcd__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dmc__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dmc_phy__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVBusMapperControl coresight_mapper_control;
	FVP_VE_Cortex_A15x1__ClockSignal clk_in;
	FVP_VE_Cortex_A15x1__Signal interrupts[48];
	FVP_VE_Cortex_A15x1__PVBus smb_cs[8];
	FVP_VE_Cortex_A15x1__LCD mmb;
	FVP_VE_Cortex_A15x1__VECBProtocol CB;
	FVP_VE_Cortex_A15x1__ClockSignal cpu_clk;
	FVP_VE_Cortex_A15x1__PVBus cpu_pvbus;
	FVP_VE_Cortex_A15x1__PVBus cpu_memorymapped_debug;
	FVP_VE_Cortex_A15x1__PVBus clcd_pvbus;
	FVP_VE_Cortex_A15x1__Signal cpu_irqs[224];


    // resources
    std::string application_pathname;


#line 136 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEDaughterBoard.lisa"

        const int32_t  dram_size       ;
        const bool  dram_alias     ;

        const bool  secure_memory      ;
    
#line 224 "./Linux-Release-GCC-4.4/gen/Component__VEDaughterBoard_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__VEDaughterBoard(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__VEDaughterBoard();

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
	unsigned abstract_port__coresight_mapper_control__remap(pv::RemapRequest& req_);

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


	ParameterFilter_sram_of_RAMDevice_to_VEDaughterBoard parameterFilter_sram_of_RAMDevice_to_VEDaughterBoard__;
	ParameterFilter_clockdivider_of_ClockDivider_to_VEDaughterBoard parameterFilter_clockdivider_of_ClockDivider_to_VEDaughterBoard__;
	ParameterFilter_clockCLCD_of_ClockDivider_to_VEDaughterBoard parameterFilter_clockCLCD_of_ClockDivider_to_VEDaughterBoard__;
	ParameterFilter_dram_of_RAMDevice_to_VEDaughterBoard parameterFilter_dram_of_RAMDevice_to_VEDaughterBoard__;
	ParameterFilter_secureRO_of_IntelStrataFlashJ3_to_VEDaughterBoard parameterFilter_secureRO_of_IntelStrataFlashJ3_to_VEDaughterBoard__;
	ParameterFilter_secureSRAM_of_RAMDevice_to_VEDaughterBoard parameterFilter_secureSRAM_of_RAMDevice_to_VEDaughterBoard__;
	ParameterFilter_secureDRAM_of_RAMDevice_to_VEDaughterBoard parameterFilter_secureDRAM_of_RAMDevice_to_VEDaughterBoard__;
	ParameterFilter_dmc_of_RAMDevice_to_VEDaughterBoard parameterFilter_dmc_of_RAMDevice_to_VEDaughterBoard__;
	ParameterFilter_dmc_phy_of_RAMDevice_to_VEDaughterBoard parameterFilter_dmc_phy_of_RAMDevice_to_VEDaughterBoard__;


	CADIParameterProxy *cadiParameterProxy_sram_of_RAMDevice_to_VEDaughterBoard__;
	CADIParameterProxy *cadiParameterProxy_clockdivider_of_ClockDivider_to_VEDaughterBoard__;
	CADIParameterProxy *cadiParameterProxy_clockCLCD_of_ClockDivider_to_VEDaughterBoard__;
	CADIParameterProxy *cadiParameterProxy_dram_of_RAMDevice_to_VEDaughterBoard__;
	CADIParameterProxy *cadiParameterProxy_secureRO_of_IntelStrataFlashJ3_to_VEDaughterBoard__;
	CADIParameterProxy *cadiParameterProxy_secureSRAM_of_RAMDevice_to_VEDaughterBoard__;
	CADIParameterProxy *cadiParameterProxy_secureDRAM_of_RAMDevice_to_VEDaughterBoard__;
	CADIParameterProxy *cadiParameterProxy_dmc_of_RAMDevice_to_VEDaughterBoard__;
	CADIParameterProxy *cadiParameterProxy_dmc_phy_of_RAMDevice_to_VEDaughterBoard__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_dram_size = 0x10000006,
		PARAMETER_ID_dram_alias = 0x10000007,
		PARAMETER_ID_secure_memory = 0x10000008,
	};




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

