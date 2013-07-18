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
 * Class definition for Component PL050_KMI.
 */

#ifndef Component_Component__PL050_KMI_ClassDef_h_
#define Component_Component__PL050_KMI_ClassDef_h_

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

#line 16 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL050_KMI.lisa"

    
        #include <stdio.h>

        #define TRACE_KMI if (!0) ; else printf
    
#line 44 "./Linux-Release-GCC-4.1/gen/Component__PL050_KMI_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockRateControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PS2Data_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVDevice_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerCallback_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_busslave_of_PVBusSlave_to_PL050_KMI : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_PL050_KMI()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__PL050_KMI: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *clk_divider;
	sg::ComponentBase *clk_timer;
	sg::ComponentBase *busslave;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clk_divider__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clk_timer__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__Signal intr;
	FVP_VE_Cortex_A15x1__ClockSignal clock;
	FVP_VE_Cortex_A15x1__PVDevice device;
	FVP_VE_Cortex_A15x1__PS2Data ps2device;
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback;
	FVP_VE_Cortex_A15x1__ClockRateControl __PL050_KMI_internal_1;


    // resources
    std::string application_pathname;


#line 41 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL050_KMI.lisa"

        MxU32  KMICR                ;
        MxU32  KMISTAT                 ;
        MxU32  KMIDATA                   ;
        MxU32  KMICLKDIV          ;
        MxU32  KMIIR      ;

        MxU32  KMIPeriphID0      ;
        MxU32  KMIPeriphID1      ;
        MxU32  KMIPeriphID2      ;
        MxU32  KMIPeriphID3      ;
        MxU32  KMIPCellID0      ;
        MxU32  KMIPCellID1      ;
        MxU32  KMIPCellID2      ;
        MxU32  KMIPCellID3      ;

        enum consts {
            KMICR_FKMIC    = (1<<0),
            KMICR_FKMID    = (1<<1),
            KMICR_ENABLE   = (1<<2),
            KMICR_TXEN     = (1<<3),
            KMICR_RXEN     = (1<<4),
            KMICR_TYPE     = (1<<5),

            KMITXINT = 2,
            KMIRXINT = 1,

            KMIST_D      = (1 << 0),
            KMIST_C      = (1 << 1),
            KMIST_PARITY = (1 << 2),
            KMIST_RXBUSY = (1 << 3),
            KMIST_RXFULL = (1 << 4),
            KMIST_TXBUSY = (1 << 5),
            KMIST_TXEMPTY= (1 << 6)
        };
        
        uint8_t cr;       //!< Control register.
        uint8_t stat;     //!< Status register.
        uint8_t rxdata;   //!< RX data register.
        uint8_t txdata;   //!< TX data register.
        uint8_t ir;       //!< Interrupt register.
        uint8_t clkdiv;   //!< Clock divide register.
        
        uint8_t irmask;   //!< Pseudo interrupt mask register.    
        
        bool irq;         //!< current status of IRQ line
    
#line 160 "./Linux-Release-GCC-4.1/gen/Component__PL050_KMI_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__PL050_KMI(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__PL050_KMI();

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
	void reset(int level);
	void update_kmi_interrupt();
	void control_write(uint32_t new_cr);
	uint32_t status_read();
	void data_write(uint8_t data);
	uint8_t data_read();
	void update_clock();
	void device_reset();
	uint32_t registerRead(uint32_t device_addr);
	void registerWrite(uint32_t device_addr, uint32_t data);
	AccessFuncResult debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects);
	AccessFuncResult debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects);
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
	pv::Tx_Result abstract_port__device__read(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__device__write(pv::WriteTransaction tx);
	pv::Tx_Result abstract_port__device__debugRead(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__device__debugWrite(pv::WriteTransaction tx);
	uint8_t abstract_port__ps2device__getData();
	void abstract_port__ps2device__putData(uint8_t data);
	uint32_t abstract_port__timer_callback__signal();

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


	ParameterFilter_busslave_of_PVBusSlave_to_PL050_KMI parameterFilter_busslave_of_PVBusSlave_to_PL050_KMI__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_PL050_KMI__;


    // definition of parameter IDs as constants for use in parameter access functions


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_KMICR = 0x00000000,
		REGISTER_ID_KMISTAT = 0x00000004,
		REGISTER_ID_KMIDATA = 0x00000008,
		REGISTER_ID_KMICLKDIV = 0x0000000c,
		REGISTER_ID_KMIIR = 0x00000010,
		REGISTER_ID_KMIPeriphID0 = 0x00000fe0,
		REGISTER_ID_KMIPeriphID1 = 0x00000fe4,
		REGISTER_ID_KMIPeriphID2 = 0x00000fe8,
		REGISTER_ID_KMIPeriphID3 = 0x00000fec,
		REGISTER_ID_KMIPCellID0 = 0x00000ff0,
		REGISTER_ID_KMIPCellID1 = 0x00000ff4,
		REGISTER_ID_KMIPCellID2 = 0x00000ff8,
		REGISTER_ID_KMIPCellID3 = 0x00000ffc,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

