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
 * Class definition for Component SP810_SysCtrl.
 */

#ifndef Component_Component__SP810_SysCtrl_ClassDef_h_
#define Component_Component__SP810_SysCtrl_ClassDef_h_

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

#line 19 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"

    
        #define SP810_TRACE if (!0) ; else printf
        
        // create a mask of bits in a word
        #define sp810_mask(s, e) (0xffffffff>>(31-(s)) & (0xffffffff << (e)))
        #define sp810_bit(b) (1<<(b))
    
#line 46 "./Linux-Release-GCC-4.1/gen/Component__SP810_SysCtrl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockRateControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVDevice_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__StateSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ValueState_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_busslave_of_PVBusSlave_to_SP810_SysCtrl : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_SP810_SysCtrl()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__SP810_SysCtrl: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *busslave;
	sg::ComponentBase *clkdiv_clk0;
	sg::ComponentBase *clkdiv_clk1;
	sg::ComponentBase *clkdiv_clk2;
	sg::ComponentBase *clkdiv_clk3;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clkdiv_clk0__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clkdiv_clk1__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clkdiv_clk2__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clkdiv_clk3__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVDevice device;
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__ClockSignal clk_in;
	FVP_VE_Cortex_A15x1__ClockSignal ref_clk_in;
	FVP_VE_Cortex_A15x1__Signal npor;
	FVP_VE_Cortex_A15x1__ValueState sys_id;
	FVP_VE_Cortex_A15x1__ValueState sys_stat;
	FVP_VE_Cortex_A15x1__Signal wd_en;
	FVP_VE_Cortex_A15x1__ValueState sys_mode;
	FVP_VE_Cortex_A15x1__StateSignal remap_stat;
	FVP_VE_Cortex_A15x1__ClockRateControl timer_clk_en[4];
	FVP_VE_Cortex_A15x1__StateSignal remap_clear;
	FVP_VE_Cortex_A15x1__Signal wd_clk_en;
	FVP_VE_Cortex_A15x1__ValueState hclkdivsel;
	FVP_VE_Cortex_A15x1__Signal sleep_mode;
	FVP_VE_Cortex_A15x1__Signal pll_en;


    // resources
    std::string application_pathname;


#line 29 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"

        // SCCTRL
        enum {
            WDOGENOV_MASK = (1<<(23)),
            WDOGENOV_SHIFT = 23,
            TIMEREN3OV_MASK = (1<<(22)),
            TIMEREN3OV_SHIFT = 22,
            TIMEREN3SEL_MASK = (1<<(21)),
            TIMEREN3SEL_SHIFT = 21,
            TIMEREN2OV_MASK = (1<<(20)),
            TIMEREN2OV_SHIFT = 20,
            TIMEREN2SEL_MASK = (1<<(19)),
            TIMEREN2SEL_SHIFT = 19,
            TIMEREN1OV_MASK = (1<<(18)),
            TIMEREN1OV_SHIFT = 18,
            TIMEREN1SEL_MASK = (1<<(17)),
            TIMEREN1SEL_SHIFT = 17,
            TIMEREN0OV_MASK = (1<<(16)),
            TIMEREN0OV_SHIFT = 16,
            TIMEREN0SEL_MASK = (1<<(15)),
            TIMEREN0SEL_SHIFT = 15,
            HCLKDIVSEL_MASK = (0xffffffff>>(31-(14)) & (0xffffffff << ( 12))),
            HCLKDIVSEL_SHIFT = 12,
            REMAPSTAT_MASK = (1<<(9)),
            REMAPSTAT_SHIFT = 9,
            REMAPCLEAR_MASK = (1<<(8)),
            REMAPCLEAR_SHIFT = 8,
            MODESTATUS_MASK = (0xffffffff>>(31-(6)) & (0xffffffff << ( 3))),
            MODESTATUS_SHIFT = 3,
            MODECTRL_MASK = (0xffffffff>>(31-(2)) & (0xffffffff << ( 0))),
            MODECTRL_SHIFT = 0
        };
        // SCSYSID
        enum {
            SCSYSID3_MASK = (0xffffffff>>(31-(31)) & (0xffffffff << ( 24))),
            SCSYSID3_SHIFT = 24,
            SCSYSID2_MASK = (0xffffffff>>(31-(23)) & (0xffffffff << ( 16))),
            SCSYSID2_SHIFT = 16,
            SCSYSID1_MASK = (0xffffffff>>(31-(15)) & (0xffffffff << ( 8))),
            SCSYSID1_SHIFT = 8,
            SCSYSID0_MASK = (0xffffffff>>(31-(7)) & (0xffffffff << ( 0))),
            SCSYSID0_SHIFT = 0
        };
        // SCPERIPHID
        enum {
            SCPeriphID3_MASK = (0xffffffff>>(31-(31)) & (0xffffffff << ( 24))),
            SCPeriphID3_SHIFT = 24,
            SCPeriphID2_MASK = (0xffffffff>>(31-(23)) & (0xffffffff << ( 16))),
            SCPeriphID2_SHIFT = 16,
            SCPeriphID1_MASK = (0xffffffff>>(31-(15)) & (0xffffffff << ( 8))),
            SCPeriphID1_SHIFT = 8,
            SCPeriphID0_MASK = (0xffffffff>>(31-(7)) & (0xffffffff << ( 0))),
            SCPeriphID0_SHIFT = 0
        };
        
        // SCPCellID
        enum {
            SCPCellID3_MASK = (0xffffffff>>(31-(31)) & (0xffffffff << ( 24))),
            SCPCellID3_SHIFT = 24,
            SCPCellID2_MASK = (0xffffffff>>(31-(23)) & (0xffffffff << ( 16))),
            SCPCellID2_SHIFT = 16,
            SCPCellID1_MASK = (0xffffffff>>(31-(15)) & (0xffffffff << ( 8))),
            SCPCellID1_SHIFT = 8,
            SCPCellID0_MASK = (0xffffffff>>(31-(7)) & (0xffffffff << ( 0))),
            SCPCellID0_SHIFT = 0
        };
        
        // Mode status
        enum ModeStatus {
            SLEEP       = 0 << MODESTATUS_SHIFT,
            DOZE        = 1 << MODESTATUS_SHIFT,
            XTAL_CTL    = 3 << MODESTATUS_SHIFT,
            SW_TO_XTAL  = 11<< MODESTATUS_SHIFT,
            SW_FROM_XTAL= 9 << MODESTATUS_SHIFT,
            SLOW        = 2 << MODESTATUS_SHIFT,
            PLL_CTL     = 6 << MODESTATUS_SHIFT,
            SW_TO_PLL   = 14<< MODESTATUS_SHIFT,
            SW_FROM_PLL = 10<< MODESTATUS_SHIFT,
            NORMAL      = 4 << MODESTATUS_SHIFT
        };


        const uint32_t  sysid     ;
        // If use_s8 is true, the boot device can be selected as a real hardware
        // But you need to load boot monitor into the flash. For convenience, we
        // set the default value to false which is using sdram as the boot device
        const bool  use_s8     ;
        
        MxU32  SCCTRL                         ;
        MxU32  SCSYSSTAT                          ;
        MxU8  SCIMCTRL                  ;
        MxU8  SCIMSTAT                   ;
        MxU32  SCXTALCTRL                        ;
        MxU32  SCPLLCTRL                            ;
        MxU32  SCPLLFCTRL                  ;
        MxU32  SCPERCTRL0                     ;
        MxU32  SCPERCTRL1                     ;
        MxU32  SCPEREN                ;
        MxU32  SCPERDIS               ;
        MxU32  SCPERCLKEN         ;
        MxU32  SCPERSTAT                ;
        MxU8  SCSysID0                 ;
        MxU8  SCSysID1                 ;
        MxU8  SCSysID2                 ;
        MxU8  SCSysID3                 ;
        MxU8  SCITCR                ;
        MxU16  SCITIR0               ;
        MxU32  SCITIR1               ;
        MxU16  SCITOR                ;
        MxU8  SCCNTCTRL                    ;
        MxU32  SCCNTDATA                           ;
        MxU32  SCCNTSTEP                           ;
        MxU8  SCPeriphID0              ;
        MxU8  SCPeriphID1              ;
        MxU8  SCPeriphID2              ;
        MxU8  SCPeriphID3              ;
        MxU8  SCPCellID0               ;
        MxU8  SCPCellID1               ;
        MxU8  SCPCellID2               ;
        MxU8  SCPCellID3               ;
        
        uint32_t sc_ctrl;
        uint32_t sc_sys_stat;
        uint32_t sc_imctrl;
        uint32_t sc_xtal_ctrl;
        uint32_t sc_pll_ctrl;
        uint32_t sc_pll_fctrl;
        uint32_t sc_perctrl0;
        uint32_t sc_perctrl1;
        uint32_t sc_perclk_en;
        uint32_t sc_perclk_stat;
        uint32_t sc_sysid;
        uint32_t sc_periphid;
        uint32_t sc_pcellid;
        
        // Status variables
        bool s_fiq; // nFIQ
        bool s_irq; // nIRQ
        bool s_por; // nPOR
        sg::Signal::State s_remap;
        bool s_wd_clk;
        bool s_im_stat;
        bool s_timer_enov0;
        bool s_timer_enov1;
        bool s_timer_enov2;
        bool s_timer_enov3;
        bool s_sbw; // stand by wait
        ModeStatus mode_status;
        uint32_t BASE_CLOCK;
    
#line 278 "./Linux-Release-GCC-4.1/gen/Component__SP810_SysCtrl_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__SP810_SysCtrl(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__SP810_SysCtrl();

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
	void changeClock(bool b, uint32_t p);
	void updateSystemControl();
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
	void abstract_port__remap_stat__setValue(sg::Signal::State state);
	sg::Signal::State abstract_port__remap_stat__getValue();

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


	ParameterFilter_busslave_of_PVBusSlave_to_SP810_SysCtrl parameterFilter_busslave_of_PVBusSlave_to_SP810_SysCtrl__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_SP810_SysCtrl__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_sysid = 0x1000002E,
		PARAMETER_ID_use_s8 = 0x1000002F,
	};


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_SCCTRL = 0x00000000,
		REGISTER_ID_SCSYSSTAT = 0x00000004,
		REGISTER_ID_SCIMCTRL = 0x00000008,
		REGISTER_ID_SCIMSTAT = 0x0000000c,
		REGISTER_ID_SCXTALCTRL = 0x00000010,
		REGISTER_ID_SCPLLCTRL = 0x00000014,
		REGISTER_ID_SCPLLFCTRL = 0x00000018,
		REGISTER_ID_SCPERCTRL0 = 0x0000001c,
		REGISTER_ID_SCPERCTRL1 = 0x00000020,
		REGISTER_ID_SCPEREN = 0x00000024,
		REGISTER_ID_SCPERDIS = 0x00000028,
		REGISTER_ID_SCPERCLKEN = 0x0000002c,
		REGISTER_ID_SCPERSTAT = 0x00000030,
		REGISTER_ID_SCSysID0 = 0x00000ee0,
		REGISTER_ID_SCSysID1 = 0x00000ee4,
		REGISTER_ID_SCSysID2 = 0x00000ee8,
		REGISTER_ID_SCSysID3 = 0x00000eec,
		REGISTER_ID_SCITCR = 0x00000f00,
		REGISTER_ID_SCITIR0 = 0x00000f04,
		REGISTER_ID_SCITIR1 = 0x00000f08,
		REGISTER_ID_SCITOR = 0x00000f0c,
		REGISTER_ID_SCCNTCTRL = 0x00000f10,
		REGISTER_ID_SCCNTDATA = 0x00000f14,
		REGISTER_ID_SCCNTSTEP = 0x00000f18,
		REGISTER_ID_SCPeriphID0 = 0x00000fe0,
		REGISTER_ID_SCPeriphID1 = 0x00000fe4,
		REGISTER_ID_SCPeriphID2 = 0x00000fe8,
		REGISTER_ID_SCPeriphID3 = 0x00000fec,
		REGISTER_ID_SCPCellID0 = 0x00000ff0,
		REGISTER_ID_SCPCellID1 = 0x00000ff4,
		REGISTER_ID_SCPCellID2 = 0x00000ff8,
		REGISTER_ID_SCPCellID3 = 0x00000ffc,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

