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
 * Class definition for Component VE_SysRegs.
 */

#ifndef Component_Component__VE_SysRegs_ClassDef_h_
#define Component_Component__VE_SysRegs_ClassDef_h_

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

#line 21 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"

    
        #define VESYSREG_TRACE if (!0) ; else printf
    
#line 42 "./Linux64-Release-GCC-4.4/gen/Component__VE_SysRegs_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockRateControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__LCD_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVDevice_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__StateSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerCallback_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__VECBProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ValueState_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_busslave_of_PVBusSlave_to_VE_SysRegs : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_VE_SysRegs()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__VE_SysRegs: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *busslave;
	sg::ComponentBase *timer_24mhz;
	sg::ComponentBase *timer_100Hz;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer_24mhz__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer_100Hz__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__PVDevice device;
	FVP_VE_Cortex_A15x1__ClockSignal clock_24Mhz;
	FVP_VE_Cortex_A15x1__ClockSignal clock_100Hz;
	FVP_VE_Cortex_A15x1__ValueState user_switches;
	FVP_VE_Cortex_A15x1__ValueState leds;
	FVP_VE_Cortex_A15x1__StateSignal mmc_card_present;
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback_handler_24mhz;
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback_handler_100Hz;
	FVP_VE_Cortex_A15x1__ClockRateControl clock_CLCD;
	FVP_VE_Cortex_A15x1__LCD lcd;
	FVP_VE_Cortex_A15x1__VECBProtocol cb[2];
	FVP_VE_Cortex_A15x1__LCD mmb[3];
	FVP_VE_Cortex_A15x1__TimerControl __VE_SysRegs_internal_1;
	FVP_VE_Cortex_A15x1__TimerControl __VE_SysRegs_internal_2;


    // resources
    std::string application_pathname;


#line 27 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"

        enum
        {
            BOARD_REV_A,
            BOARD_REV_B,
            BOARD_REV_C
        };
        
        // Default the core tile type to 0x0C for Cortex-A9
        const uint32_t  sys_proc_id0     ;
        // Default the logic tile type to 0xFF for not supported.
        const uint32_t  sys_proc_id1     ;

        const uint32_t  user_switches_value     ;
        const bool  exit_on_shutdown     ;
        const bool  tilePresent     ;

        MxU32  SYS_ID        ;
        MxU32  SYS_SW        ;
        MxU32  SYS_LED        ;
        MxU32  SYS_100HZ         ;
        MxU32  SYS_FLAGS         ;
        MxU32  SYS_FLAGSCLR           ;
        MxU32  SYS_NVFLAGS         ;
        MxU32  SYS_NVFLAGSCLR           ;
        MxU32  SYS_MCI          ;
        MxU32  SYS_FLASH         ;
        MxU32  SYS_CFGSW        ;
        MxU32  SYS_24MHZ         ;
        MxU32  SYS_MISC        ;
        MxU32  SYS_DMA        ;
        MxU32  SYS_PROCID0        ;
        MxU32  SYS_PROCID1        ;
        MxU32  SYS_CFGDATA        ;
        MxU32  SYS_CFGCTRL        ;
        MxU32  SYS_CFGSTAT        ;

        uint32_t RESET_TIME_24MHZ;
        uint32_t RESET_TIME_100HZ;
        uint32_t clockCLCD;
        uint8_t mmbSite;

        // site location
        enum
        {
            SYS_CTRL_SITE_MB,
            SYS_CTRL_SITE_DB1,
            SYS_CTRL_SITE_DB2
        };

        // function
        enum
        {
            SYS_CFG_OSC      = 1, // Oscillator frequency in Hz
            SYS_CFG_VOLT     = 2, // Voltage in uV
            SYS_CFG_AMP      = 3, // Current in uA
            SYS_CFG_TEMP     = 4, // Temperature in uC
            SYS_CFG_RESET    = 5, // DB reset register
            SYS_CFG_SYSCON   = 6, // SCC configuration register
            SYS_CFG_MUXFPGA  = 7, // FPGA select: 0: Motherboard; 1/2: Daughterboard 1/2; 3: Unused
            SYS_CFG_SHUTDOWN = 8, // Shutdown system
            SYS_CFG_REBOOT   = 9, // Reboot system
            SYS_CFG_DVIMODE = 11, // 3-bit DVI mode -- 0: VGA, 1: SVGA, 2: XGA, 3: SXGA, 4: UXGA
            SYS_CFG_POWER   = 12, // Power in uW
        };

        struct SysCtrl
        {
            bool busy;        // Is a transfer is in progress
            bool write;       // Is transfer a write?
            uint8_t function; // Destination device
            uint8_t site;
            uint8_t position;
            uint16_t device;
        } sysCfgCtrl;

        enum
        {
            SYS_CFGSTAT_COMPLETE = 0x1, // Configuration complete. Cleared when SYS_CFGCTRL.S set
            SYS_CFGSTAT_ERROR    = 0x2, // Configuration error. Cleared when SYS_CFGCTRL.S seta
        };

        enum
        {
            SYS_CFGCTRL_START_MASK    = 0x80000000, // [31]
            SYS_CFGCTRL_START_BIT     = 31,
            SYS_CFGCTRL_WRITE_MASK    = 0x40000000, // [30]
            SYS_CFGCTRL_WRITE_BIT     = 30,
            SYS_CFGCTRL_DCC_MASK      = 0x3c000000, // [29:26]
            SYS_CFGCTRL_DCC_BIT       = 26,
            SYS_CFGCTRL_FUNCTION_MASK = 0x03f00000, // [25:20]
            SYS_CFGCTRL_FUNCTION_BIT  = 20,
            SYS_CFGCTRL_SITE_MASK     = 0x00030000, // [17:16]
            SYS_CFGCTRL_SITE_BIT      = 16,
            SYS_CFGCTRL_POSITION_MASK = 0x0000f000, // [15:12]
            SYS_CFGCTRL_POSITION_BIT  = 12,
            SYS_CFGCTRL_DEVICE_MASK   = 0x00000fff, // [11:0]
            SYS_CFGCTRL_DEVICE_BIT    = 0,
        };
    
#line 222 "./Linux64-Release-GCC-4.4/gen/Component__VE_SysRegs_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__VE_SysRegs(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__VE_SysRegs();

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

	uint32_t timer_callback_24mhz();
	uint32_t timer_callback_100hz();
	void init();
	uint32_t getSysID(int revision);
	uint32_t getSysSW();
	uint32_t getSysCfgCtrl();
	void setSysCfgCtrl(uint32_t data);
	void reset(int level);
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
	uint32_t abstract_port__user_switches__getValue();
	void abstract_port__user_switches__setValue(uint32_t data);
	uint32_t abstract_port__leds__getValue();
	void abstract_port__mmc_card_present__setValue(sg::Signal::State state);
	uint32_t abstract_port__timer_callback_handler_24mhz__signal();
	uint32_t abstract_port__timer_callback_handler_100Hz__signal();
	const VisRasterLayout* abstract_port__mmb__lock(uint32_t index);
	void abstract_port__mmb__unlock(uint32_t index);
	void abstract_port__mmb__update(uint32_t index, int x, int y, unsigned int w, unsigned int h);
	void abstract_port__mmb__setPreferredLayout(uint32_t index, unsigned int width, unsigned int height, unsigned int depth);

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


	ParameterFilter_busslave_of_PVBusSlave_to_VE_SysRegs parameterFilter_busslave_of_PVBusSlave_to_VE_SysRegs__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_VE_SysRegs__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_sys_proc_id0 = 0x10000013,
		PARAMETER_ID_sys_proc_id1 = 0x10000014,
		PARAMETER_ID_user_switches_value = 0x10000030,
		PARAMETER_ID_exit_on_shutdown = 0x10000031,
		PARAMETER_ID_tilePresent = 0x10000032,
	};


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_SYS_ID = 0x00000000,
		REGISTER_ID_SYS_SW = 0x00000004,
		REGISTER_ID_SYS_LED = 0x00000008,
		REGISTER_ID_SYS_100HZ = 0x00000024,
		REGISTER_ID_SYS_FLAGS = 0x00000030,
		REGISTER_ID_SYS_FLAGSCLR = 0x00000034,
		REGISTER_ID_SYS_NVFLAGS = 0x00000038,
		REGISTER_ID_SYS_NVFLAGSCLR = 0x0000003c,
		REGISTER_ID_SYS_MCI = 0x00000048,
		REGISTER_ID_SYS_FLASH = 0x0000004c,
		REGISTER_ID_SYS_CFGSW = 0x00000058,
		REGISTER_ID_SYS_24MHZ = 0x0000005c,
		REGISTER_ID_SYS_MISC = 0x00000060,
		REGISTER_ID_SYS_DMA = 0x00000064,
		REGISTER_ID_SYS_PROCID0 = 0x00000084,
		REGISTER_ID_SYS_PROCID1 = 0x00000088,
		REGISTER_ID_SYS_CFGDATA = 0x000000a0,
		REGISTER_ID_SYS_CFGCTRL = 0x000000a4,
		REGISTER_ID_SYS_CFGSTAT = 0x000000a8,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

