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
 * Class definition for Component VEMotherBoard.
 */

#ifndef Component_Component__VEMotherBoard_ClassDef_h_
#define Component_Component__VEMotherBoard_ClassDef_h_

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
#include "FVP_VE_Cortex_A15x1__InstructionCount_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__LCD_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
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

class ParameterFilter_ve_sysregs_of_VE_SysRegs_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_ve_sysregs_of_VE_SysRegs_to_VEMotherBoard()
	{
		ovrd_params["sys_proc_id0"] = eslapi::CADIParameterInfo_t(0x10000013 | PARAMETERFILTER_FORWARDED, "sys_proc_id0",eslapi::CADI_PARAM_INT, "Procesor ID register at CoreTile Express Site 1",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0xc000000), "0x0c000000" ); // forwarded from "proc_id0"
		ovrd_params["sys_proc_id1"] = eslapi::CADIParameterInfo_t(0x10000014 | PARAMETERFILTER_FORWARDED, "sys_proc_id1",eslapi::CADI_PARAM_INT, "Processor ID at CoreTile Express Site 2",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0xff000000), "0xff000000" ); // forwarded from "proc_id1"
	}
};

class ParameterFilter_dummy_usb_of_RAMDevice_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_dummy_usb_of_RAMDevice_to_VEMotherBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_dummy_ram_of_RAMDevice_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_dummy_ram_of_RAMDevice_to_VEMotherBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_dummy_local_dap_rom_of_RAMDevice_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_dummy_local_dap_rom_of_RAMDevice_to_VEMotherBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_psram_of_RAMDevice_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_psram_of_RAMDevice_to_VEMotherBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_vram_of_RAMDevice_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_vram_of_RAMDevice_to_VEMotherBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x100000000), "0x100000000" );
	}
};

class ParameterFilter_flash1_of_IntelStrataFlashJ3_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_flash1_of_IntelStrataFlashJ3_to_VEMotherBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x4),MxS64CONST(0xffffffff),MxS64CONST(0x1000), "0x1000" );
	}
};

class ParameterFilter_flash0_of_IntelStrataFlashJ3_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_flash0_of_IntelStrataFlashJ3_to_VEMotherBoard()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Memory Size",0,MxS64CONST(0x4),MxS64CONST(0xffffffff),MxS64CONST(0x1000), "0x1000" );
	}
};

class ParameterFilter_clock24MHz_of_ClockDivider_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_clock24MHz_of_ClockDivider_to_VEMotherBoard()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FIXED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" );
	}
};

class ParameterFilter_clock100Hz_of_ClockDivider_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_clock100Hz_of_ClockDivider_to_VEMotherBoard()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FIXED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" );
	}
};

class ParameterFilter_clockCLCD_of_ClockDivider_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_clockCLCD_of_ClockDivider_to_VEMotherBoard()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FIXED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" );
	}
};

class ParameterFilter_clock35MHz_of_ClockDivider_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_clock35MHz_of_ClockDivider_to_VEMotherBoard()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FIXED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" );
	}
};

class ParameterFilter_clock50Hz_of_ClockDivider_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_clock50Hz_of_ClockDivider_to_VEMotherBoard()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FIXED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" );
	}
};

class ParameterFilter_vis_of_VEVisualisation_to_VEMotherBoard : public ParameterFilter
{
public:
	ParameterFilter_vis_of_VEVisualisation_to_VEMotherBoard()
	{
		ovrd_params["daughter_led_count"] = eslapi::CADIParameterInfo_t(0x10000011 | PARAMETERFILTER_FORWARDED, "daughter_led_count",eslapi::CADI_PARAM_INT, "Number of LEDs that the daughter board has",0,MxS64CONST(0x0),MxS64CONST(0x20),MxS64CONST(0x0), "0" ); // forwarded from "number_of_daughter_leds"
		ovrd_params["daughter_user_switch_count"] = eslapi::CADIParameterInfo_t(0x10000015 | PARAMETERFILTER_FORWARDED, "daughter_user_switch_count",eslapi::CADI_PARAM_INT, "Number of switches that the daughter board has",0,MxS64CONST(0x0),MxS64CONST(0x20),MxS64CONST(0x0), "0" ); // forwarded from "number_of_daughter_switches"
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__VEMotherBoard: public SystemGenComponent
{
public:
    // pointers to subcomponents
	Component__SP805_Watchdog *sp805_wdog;
	Component__PL050_KMI *pl050_kmi1;
	Component__PL050_KMI *pl050_kmi0;
	Component__SP804_Timer *Timer_2_3;
	Component__SP804_Timer *Timer_0_1;
	Component__SP810_SysCtrl *sp810_sysctrl;
	Component__PL111_CLCD *pl111_clcd;
	Component__PL031_RTC *pl031_rtc;
	Component__PL011_Uart *pl011_uart3;
	Component__PL011_Uart *pl011_uart2;
	Component__PL011_Uart *pl011_uart1;
	Component__PL011_Uart *pl011_uart0;
	Component__PL180_MCI *pl180_mci;
	Component__PL041_AACI *pl041_aaci;
	Component__VE_SysRegs *ve_sysregs;
	sg::ComponentBase *smsc_91c111;
	Component__PS2Mouse *ps2mouse;
	Component__PS2Keyboard *ps2keyboard;
	Component__MMC *mmc;
	Component__VE_CompactFlash *dummy_CF;
	Component__RAMDevice *dummy_usb;
	Component__RAMDevice *dummy_ram;
	Component__RAMDevice *dummy_local_dap_rom;
	Component__RAMDevice *psram;
	Component__RAMDevice *vram;
	Component__IntelStrataFlashJ3 *flash1;
	Component__IntelStrataFlashJ3 *flash0;
	Component__FlashLoader *flashloader1;
	Component__FlashLoader *flashloader0;
	sg::ComponentBase *clk;
	sg::ComponentBase *clock24MHz;
	sg::ComponentBase *clock100Hz;
	sg::ComponentBase *clockCLCD;
	sg::ComponentBase *clock35MHz;
	sg::ComponentBase *clock50Hz;
	sg::ComponentBase *cs3_decoder;
	sg::ComponentBase *cs2_decoder;
	sg::ComponentBase *terminal_0;
	sg::ComponentBase *terminal_1;
	sg::ComponentBase *terminal_2;
	sg::ComponentBase *terminal_3;
	Component__AudioOut_SDL *audioout;
	Component__VEVisualisation *vis;
	Component__VirtualEthernetCrossover *virtualethernetcrossover;
	Component__HostBridge *hostbridge;
	Component__VFS2 *vfs2;
	sg::ComponentBase *virtioblockdevice;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_sp805_wdog__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl050_kmi1__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl050_kmi0__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_Timer_2_3__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_Timer_0_1__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_sp810_sysctrl__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl111_clcd__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl031_rtc__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl011_uart3__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl011_uart2__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl011_uart1__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl011_uart0__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl180_mci__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl041_aaci__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_ve_sysregs__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_smsc_91c111__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_ps2mouse__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_ps2keyboard__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_mmc__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dummy_CF__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dummy_usb__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dummy_ram__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_dummy_local_dap_rom__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_psram__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_vram__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_flash1__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_flash0__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_flashloader1__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_flashloader0__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clk__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clock24MHz__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clock100Hz__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clockCLCD__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clock35MHz__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clock50Hz__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_cs3_decoder__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_cs2_decoder__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_terminal_0__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_terminal_1__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_terminal_2__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_terminal_3__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_audioout__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_vis__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_virtualethernetcrossover__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_hostbridge__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_vfs2__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_virtioblockdevice__;


    // abstract ports
	FVP_VE_Cortex_A15x1__ClockSignal masterclk;
	FVP_VE_Cortex_A15x1__Signal interrupts[48];
	FVP_VE_Cortex_A15x1__VECBProtocol CB[2];
	FVP_VE_Cortex_A15x1__PVBus clcd_pvbus;
	FVP_VE_Cortex_A15x1__PVBus virtio_m;
	FVP_VE_Cortex_A15x1__LCD mmb_db1;
	FVP_VE_Cortex_A15x1__PVBus smb_cs[8];
	FVP_VE_Cortex_A15x1__InstructionCount cluster0_ticks[4];
	FVP_VE_Cortex_A15x1__InstructionCount cluster1_ticks[4];
	FVP_VE_Cortex_A15x1__ValueState daughter_leds;
	FVP_VE_Cortex_A15x1__ValueState daughter_switches;


    // resources
    std::string application_pathname;


#line 15 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEMotherBoard.lisa"

       // Default proc_id0 0x0c000000 is for Cortex-A9
       const uint32_t  proc_id0     ;
       const uint32_t  proc_id1     ;
       const uint32_t  number_of_daughter_leds   
                       ;
       const uint32_t  number_of_daughter_switches   
                       ;

    
#line 326 "./Linux-Release-GCC-4.1/gen/Component__VEMotherBoard_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__VEMotherBoard(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__VEMotherBoard();

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


	ParameterFilter_ve_sysregs_of_VE_SysRegs_to_VEMotherBoard parameterFilter_ve_sysregs_of_VE_SysRegs_to_VEMotherBoard__;
	ParameterFilter_dummy_usb_of_RAMDevice_to_VEMotherBoard parameterFilter_dummy_usb_of_RAMDevice_to_VEMotherBoard__;
	ParameterFilter_dummy_ram_of_RAMDevice_to_VEMotherBoard parameterFilter_dummy_ram_of_RAMDevice_to_VEMotherBoard__;
	ParameterFilter_dummy_local_dap_rom_of_RAMDevice_to_VEMotherBoard parameterFilter_dummy_local_dap_rom_of_RAMDevice_to_VEMotherBoard__;
	ParameterFilter_psram_of_RAMDevice_to_VEMotherBoard parameterFilter_psram_of_RAMDevice_to_VEMotherBoard__;
	ParameterFilter_vram_of_RAMDevice_to_VEMotherBoard parameterFilter_vram_of_RAMDevice_to_VEMotherBoard__;
	ParameterFilter_flash1_of_IntelStrataFlashJ3_to_VEMotherBoard parameterFilter_flash1_of_IntelStrataFlashJ3_to_VEMotherBoard__;
	ParameterFilter_flash0_of_IntelStrataFlashJ3_to_VEMotherBoard parameterFilter_flash0_of_IntelStrataFlashJ3_to_VEMotherBoard__;
	ParameterFilter_clock24MHz_of_ClockDivider_to_VEMotherBoard parameterFilter_clock24MHz_of_ClockDivider_to_VEMotherBoard__;
	ParameterFilter_clock100Hz_of_ClockDivider_to_VEMotherBoard parameterFilter_clock100Hz_of_ClockDivider_to_VEMotherBoard__;
	ParameterFilter_clockCLCD_of_ClockDivider_to_VEMotherBoard parameterFilter_clockCLCD_of_ClockDivider_to_VEMotherBoard__;
	ParameterFilter_clock35MHz_of_ClockDivider_to_VEMotherBoard parameterFilter_clock35MHz_of_ClockDivider_to_VEMotherBoard__;
	ParameterFilter_clock50Hz_of_ClockDivider_to_VEMotherBoard parameterFilter_clock50Hz_of_ClockDivider_to_VEMotherBoard__;
	ParameterFilter_vis_of_VEVisualisation_to_VEMotherBoard parameterFilter_vis_of_VEVisualisation_to_VEMotherBoard__;


	CADIParameterProxy *cadiParameterProxy_ve_sysregs_of_VE_SysRegs_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_dummy_usb_of_RAMDevice_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_dummy_ram_of_RAMDevice_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_dummy_local_dap_rom_of_RAMDevice_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_psram_of_RAMDevice_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_vram_of_RAMDevice_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_flash1_of_IntelStrataFlashJ3_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_flash0_of_IntelStrataFlashJ3_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_clock24MHz_of_ClockDivider_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_clock100Hz_of_ClockDivider_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_clockCLCD_of_ClockDivider_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_clock35MHz_of_ClockDivider_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_clock50Hz_of_ClockDivider_to_VEMotherBoard__;
	CADIParameterProxy *cadiParameterProxy_vis_of_VEVisualisation_to_VEMotherBoard__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_proc_id0 = 0x10000005,
		PARAMETER_ID_proc_id1 = 0x10000010,
		PARAMETER_ID_number_of_daughter_leds = 0x10000011,
		PARAMETER_ID_number_of_daughter_switches = 0x10000012,
	};




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

