/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2009 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */
/** \file
 * System components.
 */

#include "GlobalDefs.h"
#include "Components.h"

#include "Component__SP805_Watchdog_ClassDef.h"
#include "Component__SP810_SysCtrl_ClassDef.h"
#include "Component__VE_SysRegs_ClassDef.h"
#include "Component__MessageBox_ClassDef.h"
#include "Component__VFS2_ClassDef.h"
#include "Component__MessageBox_ClassDef.h"
#include "Component__VirtualEthernetCrossover_ClassDef.h"
#include "Component__VisEventRecorder_ClassDef.h"
#include "Component__VEVisualisation_ClassDef.h"
#include "Component__VisEventRecorder_ClassDef.h"


#include "eslapi/CADITypes.h"


#include "sg/SGBasicComponentFactory.h"

#include "TerminateScheduler.h"
#include "ParameterFilter.h"

#include <sg/MSCFixes.h>

// make the MSG_<...> symbols available in the global namespace
using namespace sg::message;

// component CADI interfaces
// ------------------------------------------------------------------------------
// CADI Interface for component Component__SP805_Watchdog
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__SP805_Watchdog_CADI : public sg::CADIBase
{
public:
        Component__SP805_Watchdog_CADI(Component__SP805_Watchdog* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__SP805_Watchdog *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__SP810_SysCtrl
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__SP810_SysCtrl_CADI : public sg::CADIBase
{
public:
        Component__SP810_SysCtrl_CADI(Component__SP810_SysCtrl* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__SP810_SysCtrl *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VE_SysRegs
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VE_SysRegs_CADI : public sg::CADIBase
{
public:
        Component__VE_SysRegs_CADI(Component__VE_SysRegs* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VE_SysRegs *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VFS2
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VFS2_CADI : public sg::CADIBase
{
public:
        Component__VFS2_CADI(Component__VFS2* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VFS2 *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__MessageBox
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__MessageBox_CADI : public sg::CADIBase
{
public:
        Component__MessageBox_CADI(Component__MessageBox* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__MessageBox *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VirtualEthernetCrossover
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VirtualEthernetCrossover_CADI : public sg::CADIBase
{
public:
        Component__VirtualEthernetCrossover_CADI(Component__VirtualEthernetCrossover* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VirtualEthernetCrossover *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEVisualisation
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VEVisualisation_CADI : public sg::CADIBase
{
public:
        Component__VEVisualisation_CADI(Component__VEVisualisation* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VEVisualisation *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VisEventRecorder
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VisEventRecorder_CADI : public sg::CADIBase
{
public:
        Component__VisEventRecorder_CADI(Component__VisEventRecorder* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VisEventRecorder *component;
};

} // FVP_VE_Cortex_A15x1_NMS


// non inline behaviors
#line 119 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::init()
{
 {if(!controlPort_busslave__.init.empty()) controlPort_busslave__.init();if(!controlPort_clocktimer__.init.empty()) controlPort_clocktimer__.init();};
 commonReset();
 
}
}

#line 125 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::reset(int level)
{
 {if(!controlPort_busslave__.reset.empty()) controlPort_busslave__.reset(level);if(!controlPort_clocktimer__.reset.empty()) controlPort_clocktimer__.reset(level);};
 commonReset();

 __SP805_Watchdog_internal_1.cancel();

 updateInterrupt();
 updateReset();
 
}
}

#line 136 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::commonReset()
{
 load_value = 0xffffffff;
 int_status = 0;
 int_mask = 0;
 reset_status= 0;
 reset_mask = 0;
 lock_status = 0;
 
}
}

#line 146 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::updateInterrupt()
{
 if (irq_out.setValue.implemented())
 {
 if (int_status & int_mask)
 irq_out.setValue(sg::Signal::Set);
 else
 irq_out.setValue(sg::Signal::Clear);
 }
 
}
}

#line 157 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::updateReset()
{
 if (simhalt)
 {
 if (reset_status & reset_mask)
 simHalt();
 }
 else if (reset_out.setValue.implemented())
 {
 if (reset_status & reset_mask)
 reset_out.setValue(sg::Signal::Set);
 else
 reset_out.setValue(sg::Signal::Clear);
 }
 
}
}

#line 173 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::reloadTimer()
{
 if (load_value > 0)
 {
 __SP805_Watchdog_internal_1.set(load_value);
 }
 else
 {
 __SP805_Watchdog_internal_1.cancel();

 int_status = 1;
 updateInterrupt();
 }
 
}
}

#line 188 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__SP805_Watchdog::handleTimeout()
{
 if (int_status)
 {
 reset_status = 1;
 updateReset();
 }
 else
 {
 int_status = 1;
 updateInterrupt();
 }
 
 return load_value;
 
}
}

#line 204 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__SP805_Watchdog::registerRead(pv::bus_addr_t device_addr)
{
 uint32_t data = 0;

 switch (device_addr) 
 { 
 case 0x000:
 data = load_value;
 
 if (!0) ; else printf("SP805_WdogLoad -> 0x%x\n", data);

 break;
 
 case 0x004: 
 data = __SP805_Watchdog_internal_1.remaining();
 
 if (!0) ; else printf("SP805_WdogValue -> 0x%x\n", data);

 break;

 case 0x008: 
 data = (reset_mask << 1) | (int_mask << 0);

 if (!0) ; else printf("SP805_WdogControl -> 0x%x\n", data);
 
 break;
 
 case 0x00c: 
 if (!0) ; else printf("SP805_WdogIntClr (WO)\n");

 break;

 case 0x010: 
 data = int_status;

 if (!0) ; else printf("SP805_WdogRIS -> 0x%x\n", data);

 break;

 case 0x014: 
 data = int_status & int_mask;

 if (!0) ; else printf("SP805_WdogMIS -> 0x%x\n", data);

 break;

 case 0xc00: 
 data = lock_status;
 
 if (!0) ; else printf("SP805_Lock -> 0x%x\n", data);

 break;
 
 
 case 0xfe0: 
 return 0x00000005;
 case 0xfe4: 
 return 0x00000018;
 case 0xfe8: 
 return 0x00000014; 
 case 0xfec: 
 return 0x00000000; 
 case 0xff0: 
 return 0x0000000d;
 case 0xff4: 
 return 0x000000f0;
 case 0xff8: 
 return 0x00000005;
 case 0xffc: 
 return 0x000000b1;
 
 default:
 if (!0) ; else printf("SP805_Wdog (UNMAPPED) 0x%x\n", (uint32_t)device_addr);
 break;
 }

 return data;
 
}
}

#line 283 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::registerWrite(pv::bus_addr_t device_addr, uint32_t data)
{
 if ((lock_status != 0) && (device_addr != 0xc00))
 {
 if (!0) ; else printf("SP805_Wdog (LOCKED) 0x%x <- 0x%x\n",(uint32_t)device_addr, data);
 return;
 }

 switch (device_addr) 
 {
 case 0x000: 
 if (!0) ; else printf("SP805_WdogLoad <- 0x%x\n", data);

 load_value = data;
 reloadTimer();

 return;

 case 0x004: 
 if (!0) ; else printf("SP805_WdogValue <- 0x%x (RO)\n", data);

 return; 
 
 case 0x008: 
 { 
 if (!0) ; else printf("SP805_WdogControl <- 0x%x\n", data);

 uint32_t new_int_mask = (data >> 0) & 1;
 uint32_t new_reset_mask = (data >> 1) & 1;

 if (new_int_mask && !int_mask)
 {
 
 reloadTimer();
 }
 else if (!new_int_mask)
 {
 __SP805_Watchdog_internal_1.cancel();
 }
 
 int_mask = new_int_mask;
 reset_mask = new_reset_mask;

 updateInterrupt();
 updateReset();

 return;
 }

 case 0x00c: 
 if (!0) ; else printf("SP805_WdogIntClr <- 0x%x\n", data);

 int_status = 0;

 
 reset_status = 0;

 if (int_mask)
 reloadTimer();

 updateInterrupt();
 updateReset();

 return;

 case 0x010: 
 if (!0) ; else printf("SP805_WdogRIS <- 0x%x (RO)\n", data);
 
 return;

 case 0x014: 
 if (!0) ; else printf("SP805_WdogMIS <- 0x%x (RO)\n", data);

 return;
 
 case 0xc00: 
 if (!0) ; else printf("SP805_WdogLock <- 0x%x\n", data);

 if (data == 0x1acce551)
 lock_status = 0;
 else
 lock_status = 1;
 return;
 
 default: 
 if (!0) ; else printf("SP805_Wdog (UNMAPPED) 0x%x <- 0x%x\n", (uint32_t)device_addr, data); 
 return;
 }
 
}
}

#line 375 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { AccessFuncResult 
Component__SP805_Watchdog::debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects)
{
 *datap = registerRead(reg_id);

 return ACCESS_FUNC_OK;
 
}
}

#line 382 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { AccessFuncResult 
Component__SP805_Watchdog::debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects)
{
 registerWrite(reg_id, (uint32_t)*datap);

 return ACCESS_FUNC_OK;
 
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::interconnect()
{{if(!controlPort_busslave__.interconnect.empty()) controlPort_busslave__.interconnect();if(!controlPort_clocktimer__.interconnect.empty()) controlPort_clocktimer__.interconnect();};
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::disconnect()
{{if(!controlPort_busslave__.disconnect.empty()) controlPort_busslave__.disconnect();if(!controlPort_clocktimer__.disconnect.empty()) controlPort_clocktimer__.disconnect();};
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::update()
{{if(!controlPort_busslave__.update.empty()) controlPort_busslave__.update();if(!controlPort_clocktimer__.update.empty()) controlPort_clocktimer__.update();};
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::communicate()
{{if(!controlPort_busslave__.communicate.empty()) controlPort_busslave__.communicate();if(!controlPort_clocktimer__.communicate.empty()) controlPort_clocktimer__.communicate();};
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::traceEndOfCycle()
{{if(!controlPort_busslave__.traceEndOfCycle.empty()) controlPort_busslave__.traceEndOfCycle();if(!controlPort_clocktimer__.traceEndOfCycle.empty()) controlPort_clocktimer__.traceEndOfCycle();};
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::loadApplicationFile(const std::string& filename)
{{if(!controlPort_busslave__.loadApplicationFile.empty()) controlPort_busslave__.loadApplicationFile(filename);if(!controlPort_clocktimer__.loadApplicationFile.empty()) controlPort_clocktimer__.loadApplicationFile(filename);};
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::terminate()
{{if(!controlPort_busslave__.terminate.empty()) controlPort_busslave__.terminate();if(!controlPort_clocktimer__.terminate.empty()) controlPort_clocktimer__.terminate();};
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__SP805_Watchdog::save(MxODataStream& os)
{{if(!controlPort_busslave__.save.empty()) controlPort_busslave__.save(os);if(!controlPort_clocktimer__.save.empty()) controlPort_clocktimer__.save(os);};return true;
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__SP805_Watchdog::restore(MxIDataStream& is)
{{if(!controlPort_busslave__.restore.empty()) controlPort_busslave__.restore(is);if(!controlPort_clocktimer__.restore.empty()) controlPort_clocktimer__.restore(is);};return true;
}
}

#line 5 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::step()
{{if(!controlPort_busslave__.step.empty()) controlPort_busslave__.step();if(!controlPort_clocktimer__.step.empty()) controlPort_clocktimer__.step();};
}
}

#line 71 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP805_Watchdog::abstract_port__reset_in__setValue(sg::Signal::State state)
{
 if (state == sg::Signal::Set)
 reset(1);
 
}
}

#line 83 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__SP805_Watchdog::abstract_port__timer_callback__signal()
{
 return handleTimeout();
 
}
}

#line 93 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__SP805_Watchdog::abstract_port__device__read(pv::ReadTransaction tx)
{
 if (tx.getAccessWidth() > pv::ACCESS_32_BITS || !tx.isAligned()) return tx.generateAbort();

 
 return tx.setReturnData32(registerRead(tx.getAddress() & ~3));
 
}
}

#line 101 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__SP805_Watchdog::abstract_port__device__write(pv::WriteTransaction tx)
{
 if (tx.getAccessWidth() != pv::ACCESS_32_BITS || !tx.isAligned()) return tx.generateAbort();
 registerWrite(tx.getAddress(), tx.getData32());
 return tx.writeComplete();
 
}
}

#line 108 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__SP805_Watchdog::abstract_port__device__debugRead(pv::ReadTransaction tx)
{
 return device.read(tx);
 
}
}

#line 113 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP805_Watchdog.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__SP805_Watchdog::abstract_port__device__debugWrite(pv::WriteTransaction tx)
{
 return device.write(tx);
 
}
}

#line 642 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// ------------------------------------------------------------------------------
// implementation of class Component__SP805_Watchdog
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

Component__SP805_Watchdog::Component__SP805_Watchdog(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params):
    SystemGenComponent(instName, simulationContext, params)

	,simhalt(!!GetParameterValue(params, "simhalt", MxS64CONST(0x0), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))


	,cadiParameterProxy_busslave_of_PVBusSlave_to_SP805_Watchdog__(0)

{
    // initialize properties__
	properties__["component_name"] = "";
	properties__["component_type"] = "Peripheral";
	properties__["debugger_name"] = "";
	properties__["debugger_start_command"] = "";
	properties__["default_view"] = "auto";
	properties__["description"] = "ARM Watchdog Module(SP805)";
	properties__["documentation_file"] = "../Docs/DUI0423O_fast_model_rm.pdf";
	properties__["dso_safe"] = "1";
	properties__["executes_software"] = "0";
	properties__["expose_extern_sub_component_cadi"] = "1";
	properties__["factory_namespace"] = "";
	properties__["has_cadi"] = "1";
	properties__["has_implicit_clk_in"] = "1";
	properties__["hidden"] = "0";
	properties__["icon_file"] = "";
	properties__["ip_provider"] = "";
	properties__["is_single_stepped"] = "0";
	properties__["license_feature"] = "";
	properties__["loadfile_extension"] = "";
	properties__["save_restore"] = "0";
	properties__["small_icon_file"] = "";
	properties__["variant"] = "";
	properties__["version"] = "8.1.37";

    // initialize parameter info
    {
        sg::ComponentFactory *factory = SP805_Watchdog_GetFactory();

        sg::TargetInfo *targetInfo = factory->getTargetInfo(""); // empty string means 'this' component

        if(targetInfo) // if we have no target info we also have no parameters towards CADI interfaces
        {
            // get parameter infos
            for(unsigned int i = 0; i < targetInfo->parameter_count; i++)
            {
                parameterId2parameterName__[targetInfo->parameter_info[i].id] = targetInfo->parameter_info[i].name;
                parameterInfos__.push_back((targetInfo->parameter_info)[i]);
            }
        }

        factory->dereference();
    }

    // create subcomponents
	{
		sg::ComponentFactory *ClockTimer_factory = ClockTimer_GetFactory();
		sg::ComponentFactory *PVBusSlave_factory = PVBusSlave_GetFactory();
		{
			sg::Params params_busslave__ = params.getParamsFor("busslave");
			params_busslave__["size"] = MxU64CONST(0x0000000000001000);
			add(busslave = PVBusSlave_factory->instantiate("busslave", simulationContext, params_busslave__));
		}
		{
			sg::Params params_clocktimer__ = params.getParamsFor("clocktimer");
			add(clocktimer = ClockTimer_factory->instantiate("clocktimer", simulationContext, params_clocktimer__));
		}
		ClockTimer_factory->dereference();
		PVBusSlave_factory->dereference();
	}


    // bind local behaviors to this->control_port
    bind_method(control_port, configure, &Component__SP805_Watchdog::control_port__configure, this);
    bind_method(control_port, init, &Component__SP805_Watchdog::init, this);
    bind_method(control_port, interconnect, &Component__SP805_Watchdog::interconnect, this);
//  bind_method(control_port, postConnect, &Component__SP805_Watchdog::postConnect, this);
    bind_method(control_port, reset, &Component__SP805_Watchdog::control_port__reset, this);
    bind_method(control_port, loadApplicationFile, &Component__SP805_Watchdog::loadApplicationFile, this);
    bind_method(control_port, disconnect, &Component__SP805_Watchdog::disconnect, this);
    bind_method(control_port, terminate, &Component__SP805_Watchdog::control_port__terminate, this);
    bind_method(control_port, populateCADIMap, &Component__SP805_Watchdog::control_port__populateCADIMap, this);
//  bind_method(control_port, refresh, &Component__SP805_Watchdog::refresh, this);
    bind_method(control_port, step, &Component__SP805_Watchdog::step, this);
    bind_method(control_port, update, &Component__SP805_Watchdog::update, this);
    bind_method(control_port, communicate, &Component__SP805_Watchdog::communicate, this);
    bind_method(control_port, getProperty, &Component__SP805_Watchdog::control_port__getProperty, this);
    bind_method(control_port, traceEndOfCycle, &Component__SP805_Watchdog::traceEndOfCycle, this);
    bind_method(control_port, bypass, &Component__SP805_Watchdog::control_port__bypass, this);
    bind_method(control_port, run, &Component__SP805_Watchdog::control_port__run, this);
    bind_method(control_port, stop, &Component__SP805_Watchdog::control_port__stop, this);
    bind_method(control_port, idle, &Component__SP805_Watchdog::control_port__idle, this);
    bind_method(control_port, quit, &Component__SP805_Watchdog::control_port__quit, this);
    bind_method(control_port, setSimulationEngine, &Component__SP805_Watchdog::control_port__setSimulationEngine, this);
    bind_method(control_port, message, &Component__SP805_Watchdog::control_port__message, this);
    bind_method(control_port, callSimEngine, &Component__SP805_Watchdog::control_port__callSimEngine, this);

    // avoid the automatic calling of the methods through the framework
    control_port.configure.setLocalOnly(true);
    control_port.init.setLocalOnly(true);
    control_port.interconnect.setLocalOnly(true);
//  control_port.postConnect.setLocalOnly(true);
    control_port.reset.setLocalOnly(true);
    control_port.loadApplicationFile.setLocalOnly(true);
    control_port.disconnect.setLocalOnly(true);
    control_port.terminate.setLocalOnly(true);
    control_port.save.setLocalOnly(true);
    control_port.restore.setLocalOnly(true);
    control_port.populateCADIMap.setLocalOnly(true);
//  control_port.refresh.setLocalOnly(true);
    control_port.step.setLocalOnly(true);
    control_port.update.setLocalOnly(true);
    control_port.communicate.setLocalOnly(true);
    control_port.getProperty.setLocalOnly(true);
    control_port.traceEndOfCycle.setLocalOnly(true);
//  control_port.bypass.setLocalOnly(true);
//  control_port.run.setLocalOnly(true);
//  control_port.stop.setLocalOnly(true);
//  control_port.idle.setLocalOnly(true); // broadcast ports don't have setLocalOnly
//  control_port.quit.setLocalOnly(true);
//  control_port.setSimulationEngine.setLocalOnly(true);

    // bind cadiPort behaviors
    bind_method(cadiPort__, GetParameters, &Component__SP805_Watchdog::cadiPort__GetParameters, this);
    bind_method(cadiPort__, GetParameterInfo, &Component__SP805_Watchdog::cadiPort__GetParameterInfo, this);
    bind_method(cadiPort__, GetProperty, &Component__SP805_Watchdog::cadiPort__GetProperty, this);
    bind_method(cadiPort__, LoadApplicationFile, &Component__SP805_Watchdog::cadiPort__LoadApplicationFile, this);
    bind_method(cadiPort__, GetApplicationsAndCommandLineParams, &Component__SP805_Watchdog::cadiPort__GetApplicationsAndCommandLineParams, this);

    // connect control ports for subcomponents to subcomponents
	controlPort_busslave__.connectTo(busslave->findPort("$control"));
	controlPort_clocktimer__.connectTo(clocktimer->findPort("$control"));



    // resource initialization code
    reset_resources__();

    // bind behaviors to abstract ports
	bind_method(reset_in, setValue, &Component__SP805_Watchdog::abstract_port__reset_in__setValue, this);
	bind_method(timer_callback, signal, &Component__SP805_Watchdog::abstract_port__timer_callback__signal, this);
	bind_method(device, read, &Component__SP805_Watchdog::abstract_port__device__read, this);
	bind_method(device, write, &Component__SP805_Watchdog::abstract_port__device__write, this);
	bind_method(device, debugRead, &Component__SP805_Watchdog::abstract_port__device__debugRead, this);
	bind_method(device, debugWrite, &Component__SP805_Watchdog::abstract_port__device__debugWrite, this);


    // add abstract ports
	publishMasterPort("irq_out", irq_out);
	irq_out.SetName__("irq_out");
	publishMasterPort("reset_out", reset_out);
	reset_out.SetName__("reset_out");
	publishSlavePort("clk_in", clk_in);
	clk_in.SetName__("clk_in");
	publishSlavePort("pvbus_s", pvbus_s);
	pvbus_s.SetName__("pvbus_s");
	publishSlavePort("reset_in", reset_in);
	reset_in.SetName__("reset_in");
	timer_callback.SetName__("timer_callback");
	device.SetName__("device");
	__SP805_Watchdog_internal_1.SetName__("__SP805_Watchdog_internal_1");


    // wire up static connection map
	pvbus_s.connectTo(busslave->findPort("pvbus_s"));
	busslave->findPort("device").connectTo(device);
	clk_in.connectTo(clocktimer->findPort("clk_in"));
	clocktimer->findPort("timer_callback").connectTo(timer_callback);
	__SP805_Watchdog_internal_1.connectTo(clocktimer->findPort("timer_control"));


    // init profiling

    // init resources


    // run the parameter write access functions for all of the component's parameters
    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        std::string paramName = parameterInfos__[i].name;

        switch (parameterInfos__[i].dataType)
        {
        case eslapi::CADI_PARAM_STRING:
            {
                std::string data = GetParameterValue(params, paramName, parameterInfos__[i].defaultString);
                parameter_write_string_func(paramNameToParamAccessFuncID(paramName), data);
            }
            break;
        case eslapi::CADI_PARAM_BOOL:
        case eslapi::CADI_PARAM_INT:
            {
                int64_t data = GetParameterValue(params, paramName, parameterInfos__[i].defaultValue, parameterInfos__[i].minValue, parameterInfos__[i].maxValue);
                parameter_write_func(paramNameToParamAccessFuncID(paramName), &data);
            }
            break;
        default:
            break;
        }
    }
}


Component__SP805_Watchdog::~Component__SP805_Watchdog()
{
}

void Component__SP805_Watchdog::control_port__configure(const sg::Params& params)
{
	if(controlPort_busslave__.configure.implemented()) controlPort_busslave__.configure(params.getParamsFor("busslave"));
	if(controlPort_clocktimer__.configure.implemented()) controlPort_clocktimer__.configure(params.getParamsFor("clocktimer"));


    assert(simulationContext__->getSimulationEngine());
    cadi__ = new Component__SP805_Watchdog_CADI(this, simulationContext__->getSimulationEngine());

    // forward certain calls from CADI interface to this component
    cadi__->GetCADIPort().connectTo(cadiPort__);

    

    std::map< std::string, eslapi::CAInterface* > tempMap;
    control_port__populateCADIMap(tempMap, ""); // precompute mxdi map

	cadi__->EnableSubComponentCADIImport();


}

void Component__SP805_Watchdog::control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* >&output_map, std::string const & base_prefix)
{
    if (componentName2CADI__.empty())
    {
        componentName2CADI__[getName()] = static_cast<eslapi::CADI*>(cadi__);
        std::string prefix = getName() + ".";

		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_busslave__.populateCADIMap.implemented())
			{
				controlPort_busslave__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
			eslapi::CADI *cadi = obtainCADI__("busslave", compMap);
			if (cadi != NULL)
			{
				cadiParameterProxy_busslave_of_PVBusSlave_to_SP805_Watchdog__ = new CADIParameterProxy(cadi, &parameterFilter_busslave_of_PVBusSlave_to_SP805_Watchdog__);
			}
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_clocktimer__.populateCADIMap.implemented())
			{
				controlPort_clocktimer__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}

    }
    // Copy the local map into the given map with the requested prefix.
    for (std::map<std::string,eslapi::CAInterface*>::iterator it = componentName2CADI__.begin(); it != componentName2CADI__.end(); ++it)
    {
        output_map.insert(std::make_pair(base_prefix + it->first, it->second));
    }
}

eslapi::CADI* Component__SP805_Watchdog::obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const
{
    std::map< std::string, eslapi::CAInterface* >::const_iterator it = componentName2CADI.find(subcomp);
    if (it != componentName2CADI.end())
    {
        eslapi::CAInterface *cai = it->second;
        if (cai != NULL)
        {
            cai = cai->ObtainInterface(eslapi::CADI::IFNAME(), 0, 0);
            if (cai != NULL)
            {
                return static_cast<eslapi::CADI*>(cai);
            }
        }
    }
    return NULL;
}

void Component__SP805_Watchdog::insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface* > &componentName2CADI)
{
    for (std::map<std::string, eslapi::CAInterface*>::iterator it = componentName2CADI.begin(); it != componentName2CADI.end(); it++)
    {
        // put prefix in front of all entries
        componentName2CADI__[prefix + it->first] = it->second;
    }
}


std::string Component__SP805_Watchdog::control_port__getProperty(const std::string& propname)
{
    if(properties__.find(propname) != properties__.end())
    {
        return properties__[propname];
    }
    else
        return ""; // unknown property
}


std::string Component__SP805_Watchdog::control_port__bypass(const std::string&)
{
    return "";
}


void Component__SP805_Watchdog::control_port__run()
{
}


void Component__SP805_Watchdog::control_port__stop()
{
}


void Component__SP805_Watchdog::control_port__idle()
{
}


void Component__SP805_Watchdog::control_port__quit()
{
}


void Component__SP805_Watchdog::control_port__setSimulationEngine(SimulationEngine*)
{
}


void Component__SP805_Watchdog::control_port__message(const std::string &msg, sg::message::MessageType msgType)
{
}


std::string Component__SP805_Watchdog::control_port__callSimEngine(const std::string &)
{
    return "";
}


void Component__SP805_Watchdog::control_port__reset(int level)
{
    // restore the resources' reset values before executing 'reset'
    reset_resources__();
    reset(level);
}


void Component__SP805_Watchdog::control_port__terminate()
{
    // the CADI was created before 'init', therefore we free it after 'terminate'
    terminate();
    freeCADIResources__();
}


void Component__SP805_Watchdog::freeCADIResources__()
{
    // free CADI parameter proxies
	delete cadiParameterProxy_busslave_of_PVBusSlave_to_SP805_Watchdog__;
	cadiParameterProxy_busslave_of_PVBusSlave_to_SP805_Watchdog__ = 0;


    // free CADI interface
    delete cadi__;
    cadi__ = 0;
}


// CADI Port implementations
eslapi::CADIReturn_t Component__SP805_Watchdog::cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params)
{
    // check arguments
    if(actualNumOfParams == 0)
        return eslapi::CADI_STATUS_IllegalArgument;
    *actualNumOfParams = 0;
    if(params == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    // collect parameters
    size_t i = 0;
    for (; (i < desiredNumOfParams) && ((startIndex + i) < parameterInfos__.size()); ++i)
    {
        params[i] = parameterInfos__[startIndex + i];
    }
    *actualNumOfParams = (MxU32)i;

    return eslapi::CADI_STATUS_OK;
}

eslapi::CADIReturn_t Component__SP805_Watchdog::cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param)
{
    if(param == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        if (!strcmp(parameterInfos__[i].name, parameterName.c_str()))
        {
            *param = parameterInfos__[i];

            return eslapi::CADI_STATUS_OK;
        }
    }

    return eslapi::CADI_STATUS_GeneralError;
}


bool Component__SP805_Watchdog::ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy, const char *param_name, int64_t intVal, const char *strVal)
{
    if (!proxy)
        return false;

    // we need the parameter's CADI id in order to create an eslapi::CADIParameterValue_t structure
    // therefore, we first retrieve its eslapi::CADIParameterInfo_t meta-data
    eslapi::CADIParameterInfo_t paramInfo;
    if (proxy->CADIGetParameterInfo(param_name, &paramInfo) != eslapi::CADI_STATUS_OK)
        return false;

    eslapi::CADIParameterValue_t paramVal(paramInfo.id, paramInfo.dataType, intVal, strVal);
    eslapi::CADIFactoryErrorMessage_t error;
    if (proxy->CADISetParameters(1, &paramVal, &error) != eslapi::CADI_STATUS_OK)
        return false;

    return true;
}


sg::accessfunc::AccessFuncResult Component__SP805_Watchdog::parameter_read_func(uint32_t id, int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_simhalt: *data = simhalt; break;

        default:
            printf("error: Component__SP805_Watchdog::parameter_read_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__SP805_Watchdog::parameter_read_string_func(uint32_t id, std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__SP805_Watchdog::parameter_read_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__SP805_Watchdog::parameter_write_func(uint32_t id, const int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_simhalt:
		{
			simhalt = !!*data;
		}
		break;

        default:
            printf("error: Component__SP805_Watchdog::parameter_write_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__SP805_Watchdog::parameter_write_string_func(uint32_t id, const std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__SP805_Watchdog::parameter_write_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

void Component__SP805_Watchdog::cadiPort__LoadApplicationFile(const std::string& filename)
{
    loadApplicationFile(filename);
    applications2params[filename] = "";
}

void Component__SP805_Watchdog::cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_)
{
    applications2params_ = applications2params;
}

eslapi::CADIReturn_t Component__SP805_Watchdog::cadiPort__GetProperty(const std::string& propertyName, std::string &value)
{
    if(properties__.find(propertyName) != properties__.end())
    {
        value = properties__[propertyName];
        return eslapi::CADI_STATUS_OK;
    }
    else
    {
        value = "";
        return eslapi::CADI_STATUS_GeneralError;
    }
}

// functions to stop and lock the simulator
// we only expose the simHalt() function in the documentation for the moment

void Component__SP805_Watchdog::simHalt()
{
    cadi__->StopSimulation();
}


// start simulation from the inside
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
void Component__SP805_Watchdog::simRun()
{
    cadi__->CADIExecContinue();
}


// return true if simulation is running
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
bool Component__SP805_Watchdog::simIsRunning()
{
    uint32_t mode = eslapi::CADI_EXECMODE_Stop;
    cadi__->CADIExecGetMode(&mode);
    return mode != eslapi::CADI_EXECMODE_Stop;
}


void Component__SP805_Watchdog::simShutdown()
{
    cadiPort__.simShutdown();
}

void Component__SP805_Watchdog::simReset(uint32_t level)
{
    cadi__->CADIExecReset(level);
}

uint32_t Component__SP805_Watchdog::paramNameToParamAccessFuncID(const std::string &name)
{
    uint32_t id = 0;
    if (name == "") id = 0xffffffff;
    if (name == "simhalt") id = PARAMETER_ID_simhalt;

    return id;
}

void Component__SP805_Watchdog::reset_resources__()
{
    // resource initialization code
	SP805_WDOG_Load = 0; // reset register
	SP805_WDOG_VALUE = 0; // reset register
	SP805_WDOG_CONTROL = 0; // reset register
	SP805_WDOG_INT_CLR = 0; // reset register
	SP805_WDOG_RAW_INT_STATUS = 0; // reset register
	SP805_WDOG_MASKED_INT_STATUS = 0; // reset register
	SP805_WDOG_LOCK = 0; // reset register

}


} // FVP_VE_Cortex_A15x1_NMS
#line 264 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::init()
{ 
 s_fiq = false;
 s_irq = false;
 s_por = false;
 s_remap = sg::Signal::Clear;
 s_wd_clk = false;
 s_im_stat = false;
 s_timer_enov0 = false;
 s_timer_enov1 = false;
 s_timer_enov2 = false;
 s_timer_enov3 = false;
 s_sbw = false;

 mode_status = NORMAL;
 
 sc_xtal_ctrl = 0x00000;
 sc_pll_ctrl = 0x0000000;
 sc_pll_fctrl = 0x00000000;
 sc_perctrl0 = 0x00000000;
 sc_perctrl1 = 0x00000000;
 BASE_CLOCK = 35000000;
 {if(!controlPort_busslave__.init.empty()) controlPort_busslave__.init();if(!controlPort_clkdiv_clk0__.init.empty()) controlPort_clkdiv_clk0__.init();if(!controlPort_clkdiv_clk1__.init.empty()) controlPort_clkdiv_clk1__.init();if(!controlPort_clkdiv_clk2__.init.empty()) controlPort_clkdiv_clk2__.init();if(!controlPort_clkdiv_clk3__.init.empty()) controlPort_clkdiv_clk3__.init();};
 
}
}

#line 289 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::reset(int level)
{
 {if(!controlPort_busslave__.reset.empty()) controlPort_busslave__.reset(level);if(!controlPort_clkdiv_clk0__.reset.empty()) controlPort_clkdiv_clk0__.reset(level);if(!controlPort_clkdiv_clk1__.reset.empty()) controlPort_clkdiv_clk1__.reset(level);if(!controlPort_clkdiv_clk2__.reset.empty()) controlPort_clkdiv_clk2__.reset(level);if(!controlPort_clkdiv_clk3__.reset.empty()) controlPort_clkdiv_clk3__.reset(level);};
 sc_ctrl = 0x000009;
 sc_imctrl = 0x00;
 if(s_por)
 {
 sc_xtal_ctrl = 0x00000;
 sc_pll_ctrl = 0x0000000;
 sc_pll_fctrl = 0x00000000;
 sc_perctrl0 = 0x00000000;
 sc_perctrl1 = 0x00000000;
 }
 sc_perclk_en = 0xFFFFFFFF;
 sc_sysid = sysid;
 sc_periphid = 0x10180400;
 sc_pcellid = 0x0DF005B1;
 if(use_s8)
 {
 remap_clear.setValue(sg::Signal::Clear);
 sc_ctrl |= 0x1 << REMAPSTAT_SHIFT;
 }
 BASE_CLOCK = 35000000;
 updateSystemControl();
 
}
}

#line 315 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::changeClock(bool b, uint32_t p)
{
 uint32_t mul;
 uint32_t div;

 if(b) 
 {
 mul = 1;
 div = 1;
 }
 else
 {
 div = (uint32_t)ref_clk_in.rateInHz();
 mul = (uint32_t)clk_in.rateInHz();
 }
 if(timer_clk_en[p].set.implemented())
 {
 timer_clk_en[p].set(mul,div);
 }
 
}
}

#line 336 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::updateSystemControl()
{
 if((sc_ctrl & WDOGENOV_MASK) >> WDOGENOV_SHIFT)
 {
 }

 if(timer_clk_en[3].set.implemented())
 {
 if((sc_ctrl & TIMEREN3OV_MASK) >> TIMEREN3OV_SHIFT)
 s_timer_enov3 = true;
 else
 s_timer_enov3 = false;

 if(s_timer_enov3) {
 timer_clk_en[3].set(1,1); 
 }
 else
 {
 if((sc_ctrl & TIMEREN3SEL_MASK) >> TIMEREN3SEL_SHIFT)
 {
 timer_clk_en[3].set(1,35); 
 }
 else
 {
 timer_clk_en[3].set(32768, BASE_CLOCK); 
 }
 }
 }

 if(timer_clk_en[2].set.implemented())
 {
 if((sc_ctrl & TIMEREN2OV_MASK) >> TIMEREN2OV_SHIFT)
 s_timer_enov2 = true;
 else
 s_timer_enov2 = false;
 
 if(s_timer_enov2) {
 timer_clk_en[2].set(1,1); 
 }
 else
 {
 if((sc_ctrl & TIMEREN2SEL_MASK) >> TIMEREN2SEL_SHIFT)
 {
 timer_clk_en[2].set(1,35); 
 }
 else
 {
 timer_clk_en[2].set(32768, BASE_CLOCK); 
 }
 }
 }

 if(timer_clk_en[1].set.implemented())
 {
 if((sc_ctrl & TIMEREN1OV_MASK) >> TIMEREN1OV_SHIFT)
 s_timer_enov1 = true;
 else
 s_timer_enov1 = false;
 
 if(s_timer_enov1) {
 timer_clk_en[1].set(1,1); 
 }
 else
 {
 if((sc_ctrl & TIMEREN1SEL_MASK) >> TIMEREN1SEL_SHIFT)
 {
 timer_clk_en[1].set(1,35); 
 }
 else
 {
 timer_clk_en[1].set(32768, BASE_CLOCK); 
 }
 }
 }

 if(timer_clk_en[0].set.implemented())
 {
 if((sc_ctrl & TIMEREN0OV_MASK) >> TIMEREN0OV_SHIFT)
 s_timer_enov0 = true;
 else
 s_timer_enov0 = false;
 
 if(s_timer_enov0) {
 timer_clk_en[0].set(1,1); 
 }
 else
 {
 if((sc_ctrl & TIMEREN0SEL_MASK) >> TIMEREN0SEL_SHIFT)
 {
 timer_clk_en[0].set(1,35); 
 }
 else
 {
 timer_clk_en[0].set(32768, BASE_CLOCK); 
 }
 }
 }

 if((sc_ctrl & HCLKDIVSEL_MASK) >> HCLKDIVSEL_SHIFT)
 {
 
 }
 
 sc_ctrl |= s_remap?sg::Signal::Set:sg::Signal::Clear << REMAPSTAT_SHIFT;

 if((sc_ctrl & REMAPCLEAR_MASK) >> REMAPCLEAR_SHIFT)
 {
 if(remap_clear.setValue.implemented())
 remap_clear.setValue(sg::Signal::Set);
 sc_ctrl = ~(~sc_ctrl | 0x1 << REMAPSTAT_SHIFT);
 }
 else
 {
 sc_ctrl |= 0x1 << REMAPSTAT_SHIFT;
 }
 if((sc_ctrl & MODESTATUS_MASK) >> MODESTATUS_SHIFT)
 sc_ctrl |= mode_status;
 if((sc_ctrl & MODECTRL_MASK) >> MODECTRL_SHIFT)
 {
 
 }
 
}
}

#line 459 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__SP810_SysCtrl::registerRead(uint32_t device_addr)
{
 uint32_t data = 0;
 switch(device_addr) {
 case 0x00: 
 data = sc_ctrl;
 if (!0) ; else printf("SCCTRL -> %x\n", data);
 return data;
 case 0x004: 
 data = sc_sys_stat;
 if (!0) ; else printf("SCSYSSTAT -> %x\n", data);
 return data;
 case 0x008: 
 data = sc_imctrl;
 if (!0) ; else printf("SCIMCTRL -> %x\n", data);
 return data;
 case 0x00C: 
 data = s_im_stat?1:0;
 if (!0) ; else printf("SCIMSTAT -> %x\n", data);
 return data;
 case 0x010: 
 data = sc_xtal_ctrl;
 if (!0) ; else printf("SCXTALCTRL -> %x\n", data);
 return data;
 case 0x014: 
 data = sc_pll_ctrl;
 if (!0) ; else printf("SCPLLCTRL -> %x\n", data);
 return data;
 case 0x018: 
 data = sc_pll_fctrl;
 if (!0) ; else printf("SCPLLFCTRL -> %x\n", data);
 return data;
 case 0x01C: 
 data = sc_perctrl0;
 if (!0) ; else printf("SCPERCTRL0 -> %x\n", data);
 return data;
 case 0x020: 
 data = sc_perctrl1;
 if (!0) ; else printf("SCPERCTRL1 -> %x\n", data);
 return data;
 case 0x024: 
 if (!0) ; else printf("SCPEREN -> %x -- Write only\n", data);
 return data;
 case 0x028: 
 if (!0) ; else printf("SCPERDIS -> %x -- Write only\n", data);
 return data;
 case 0x02C: 
 data = sc_perclk_en;
 if (!0) ; else printf("SCPERCLKEN -> %x\n", data);
 return data;
 case 0x030: 
 data = sc_perclk_stat;
 if (!0) ; else printf("SCPERSTAT -> %x\n", data);
 return data;
 case 0xEE0: 
 data = (sc_sysid & SCSYSID0_MASK) >> SCSYSID0_SHIFT;
 if (!0) ; else printf("SCSysID0 -> %x\n", data);
 return data;
 case 0xEE4: 
 data = (sc_sysid & SCSYSID1_MASK) >> SCSYSID1_SHIFT;
 if (!0) ; else printf("SCSysID1 -> %x\n", data);
 return data;
 case 0xEE8: 
 data = (sc_sysid & SCSYSID2_MASK) >> SCSYSID2_SHIFT;
 if (!0) ; else printf("SCSysID2 -> %x\n", data);
 return data;
 case 0xEEC: 
 data = (sc_sysid & SCSYSID3_MASK) >> SCSYSID3_SHIFT;
 if (!0) ; else printf("SCSysID3 -> %x\n", data);
 return data;
 case 0xF00: 
 if (!0) ; else printf("SCITCR -> %x -- UNIMPLEMENTED\n", data);
 return data;
 case 0xF04: 
 if (!0) ; else printf("SCITIR0 -> %x -- UNIMPLEMENTED\n", data);
 return data;
 case 0xF08: 
 if (!0) ; else printf("SCITIR1 -> %x -- UNIMPLEMENTED\n", data);
 return data;
 case 0xF0C: 
 if (!0) ; else printf("SCITOR -> %x -- UNIMPLEMENTED\n", data);
 return data;
 case 0xF10: 
 if (!0) ; else printf("SCCNTCTRL -> %x -- UNIMPLEMENTED\n", data);
 return data;
 case 0xF14: 
 if (!0) ; else printf("SCCNTDATA -> %x -- UNIMPLEMENTED\n", data);
 return data;
 case 0xF18: 
 if (!0) ; else printf("SCCNTSTEP -> %x -- UNIMPLEMENTED\n", data);
 return data;
 case 0xFE0: 
 data = (sc_periphid & SCPeriphID0_MASK) >> SCPeriphID0_SHIFT;
 if (!0) ; else printf("SCPeriphID0 -> %x\n", data);
 return data;
 case 0xFE4: 
 data = (sc_periphid & SCPeriphID1_MASK) >> SCPeriphID1_SHIFT;
 if (!0) ; else printf("SCPeriphID1 -> %x\n", data);
 return data;
 case 0xFE8: 
 data = (sc_periphid & SCPeriphID2_MASK) >> SCPeriphID2_SHIFT;
 if (!0) ; else printf("SCPeriphID2 -> %x\n", data);
 return data;
 case 0xFEC: 
 data = (sc_periphid & SCPeriphID3_MASK) >> SCPeriphID3_SHIFT;
 if (!0) ; else printf("SCPeriphID3 -> %x\n", data);
 return data;
 case 0xFF0: 
 data = (sc_pcellid & SCPCellID0_MASK) >> SCPCellID0_SHIFT;
 if (!0) ; else printf("SCPCellID0 -> %x\n", data);
 return data;
 case 0xFF4: 
 data = (sc_pcellid & SCPCellID1_MASK) >> SCPCellID1_SHIFT;
 if (!0) ; else printf("SCPCellID1 -> %x\n", data);
 return data;
 case 0xFF8: 
 data = (sc_pcellid & SCPCellID2_MASK) >> SCPCellID2_SHIFT;
 if (!0) ; else printf("SCPCellID2 -> %x\n", data);
 return data;
 case 0xFFC: 
 data = (sc_pcellid & SCPCellID3_MASK) >> SCPCellID3_SHIFT;
 if (!0) ; else printf("SCPCellID3 -> %x\n", data);
 return data;
 default:
 if (!0) ; else printf("SP810 undefined register %x -> %x\n", (uint32_t)device_addr, data);
 return 0;
 }
 return data;
 
}
}

#line 589 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::registerWrite(uint32_t device_addr, uint32_t data)
{
 switch (device_addr)
 {
 case 0x000: 
 if (!0) ; else printf("SCCTRL <- %x\n", data);
 
 sc_ctrl = data;
 updateSystemControl();
 break;
 case 0x004: 
 if (!0) ; else printf("SCSYSSTAT <- %x\n", data);
 
 sc_sys_stat = data;
 break;
 case 0x008: 
 if (!0) ; else printf("SCIMCTRL <- %x\n", data);
 
 sc_imctrl = data;
 break;
 case 0x00C: 
 if (!0) ; else printf("SCIMSTAT <- %x\n", data);
 
 s_im_stat = data?true:false;
 break;
 case 0x010: 
 if (!0) ; else printf("SCXTALCTRL <- %x\n", data);
 
 sc_xtal_ctrl = data;
 break;
 case 0x014: 
 if (!0) ; else printf("SCPLLCTRL <- %x\n", data);
 sc_pll_ctrl = data;
 break;
 case 0x018: 
 if (!0) ; else printf("SCPLLFCTRL <- %x\n", data);
 sc_pll_fctrl = data;
 break;
 case 0x01C: 
 if (!0) ; else printf("SCPERCTRL0 <- %x\n", data);
 sc_perctrl0 = data;
 break;
 case 0x020: 
 if (!0) ; else printf("SCPERCTRL1 <- %x\n", data);
 sc_perctrl1 = data;
 break;
 case 0x024: 
 if (!0) ; else printf("SCPEREN <- %x\n", data);
 break;
 case 0x028: 
 if (!0) ; else printf("SCPERDIS <- %x\n", data);
 break;
 case 0x02C: 
 if (!0) ; else printf("SCPERCLKEN <- %x -- Read only\n", data);
 break;
 case 0x030: 
 if (!0) ; else printf("SCPERSTAT <- %x -- Read only\n", data);
 break;
 case 0xEE0: 
 if (!0) ; else printf("SCSysID0 <- %x\n", data);
 sc_sysid |= (data << SCSYSID0_SHIFT) & SCSYSID0_MASK ;
 break;
 case 0xEE4: 
 if (!0) ; else printf("SCSysID1 <- %x\n", data);
 sc_sysid |= (data << SCSYSID1_SHIFT) & SCSYSID1_MASK ;
 break;
 case 0xEE8: 
 if (!0) ; else printf("SCSysID2 <- %x\n", data);
 sc_sysid |= (data << SCSYSID2_SHIFT) & SCSYSID2_MASK ;
 break;
 case 0xEEC: 
 if (!0) ; else printf("SCSysID3 <- %x\n", data);
 sc_sysid |= (data << SCSYSID3_SHIFT) & SCSYSID3_MASK ;
 break;
 case 0xF00: 
 if (!0) ; else printf("SCITCR <- %x -- UNIMPLEMENTED\n", data);
 break;
 case 0xF04: 
 if (!0) ; else printf("SCITIR0 <- %x -- UNIMPLEMENTED\n", data);
 break;
 case 0xF08: 
 if (!0) ; else printf("SCITIR1 <- %x -- UNIMPLEMENTED\n", data);
 break;
 case 0xF0C: 
 if (!0) ; else printf("SCITOR <- %x -- UNIMPLEMENTED\n", data);
 break;
 case 0xF10: 
 if (!0) ; else printf("SCCNTCTRL <- %x -- UNIMPLEMENTED\n", data);
 break;
 case 0xF14: 
 if (!0) ; else printf("SCCNTDATA <- %x -- UNIMPLEMENTED\n", data);
 break;
 case 0xFE0: 
 if (!0) ; else printf("SCPeriphID0 <- %x -- Read only\n", data);
 break;
 case 0xFE4: 
 if (!0) ; else printf("SCPeriphID1 <- %x -- Read only\n", data);
 break;
 case 0xFE8: 
 if (!0) ; else printf("SCPeriphID2 <- %x -- Read only\n", data);
 break;
 case 0xFEC: 
 if (!0) ; else printf("SCPeriphID3 <- %x -- Read only\n", data);
 break;
 case 0xFF0: 
 if (!0) ; else printf("SCPCellID0 <- %x -- Read only\n", data);
 break;
 case 0xFF4: 
 if (!0) ; else printf("SCPCellID1 <- %x -- Read only\n", data);
 break;
 case 0xFF8: 
 if (!0) ; else printf("SCPCellID2 <- %x -- Read only\n", data);
 break;
 case 0xFFC: 
 if (!0) ; else printf("SCPCellID3 <- %x -- Read only\n", data);
 break;
 }
 
 
}
}

#line 711 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { AccessFuncResult 
Component__SP810_SysCtrl::debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects)
{
 *datap = registerRead(reg_id);
 
 return ACCESS_FUNC_OK;
 
}
}

#line 718 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { AccessFuncResult 
Component__SP810_SysCtrl::debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects)
{
 registerWrite(reg_id, (uint32_t)*datap);
 
 return ACCESS_FUNC_OK;
 
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::interconnect()
{{if(!controlPort_busslave__.interconnect.empty()) controlPort_busslave__.interconnect();if(!controlPort_clkdiv_clk0__.interconnect.empty()) controlPort_clkdiv_clk0__.interconnect();if(!controlPort_clkdiv_clk1__.interconnect.empty()) controlPort_clkdiv_clk1__.interconnect();if(!controlPort_clkdiv_clk2__.interconnect.empty()) controlPort_clkdiv_clk2__.interconnect();if(!controlPort_clkdiv_clk3__.interconnect.empty()) controlPort_clkdiv_clk3__.interconnect();};
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::disconnect()
{{if(!controlPort_busslave__.disconnect.empty()) controlPort_busslave__.disconnect();if(!controlPort_clkdiv_clk0__.disconnect.empty()) controlPort_clkdiv_clk0__.disconnect();if(!controlPort_clkdiv_clk1__.disconnect.empty()) controlPort_clkdiv_clk1__.disconnect();if(!controlPort_clkdiv_clk2__.disconnect.empty()) controlPort_clkdiv_clk2__.disconnect();if(!controlPort_clkdiv_clk3__.disconnect.empty()) controlPort_clkdiv_clk3__.disconnect();};
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::update()
{{if(!controlPort_busslave__.update.empty()) controlPort_busslave__.update();if(!controlPort_clkdiv_clk0__.update.empty()) controlPort_clkdiv_clk0__.update();if(!controlPort_clkdiv_clk1__.update.empty()) controlPort_clkdiv_clk1__.update();if(!controlPort_clkdiv_clk2__.update.empty()) controlPort_clkdiv_clk2__.update();if(!controlPort_clkdiv_clk3__.update.empty()) controlPort_clkdiv_clk3__.update();};
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::communicate()
{{if(!controlPort_busslave__.communicate.empty()) controlPort_busslave__.communicate();if(!controlPort_clkdiv_clk0__.communicate.empty()) controlPort_clkdiv_clk0__.communicate();if(!controlPort_clkdiv_clk1__.communicate.empty()) controlPort_clkdiv_clk1__.communicate();if(!controlPort_clkdiv_clk2__.communicate.empty()) controlPort_clkdiv_clk2__.communicate();if(!controlPort_clkdiv_clk3__.communicate.empty()) controlPort_clkdiv_clk3__.communicate();};
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::traceEndOfCycle()
{{if(!controlPort_busslave__.traceEndOfCycle.empty()) controlPort_busslave__.traceEndOfCycle();if(!controlPort_clkdiv_clk0__.traceEndOfCycle.empty()) controlPort_clkdiv_clk0__.traceEndOfCycle();if(!controlPort_clkdiv_clk1__.traceEndOfCycle.empty()) controlPort_clkdiv_clk1__.traceEndOfCycle();if(!controlPort_clkdiv_clk2__.traceEndOfCycle.empty()) controlPort_clkdiv_clk2__.traceEndOfCycle();if(!controlPort_clkdiv_clk3__.traceEndOfCycle.empty()) controlPort_clkdiv_clk3__.traceEndOfCycle();};
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::loadApplicationFile(const std::string& filename)
{{if(!controlPort_busslave__.loadApplicationFile.empty()) controlPort_busslave__.loadApplicationFile(filename);if(!controlPort_clkdiv_clk0__.loadApplicationFile.empty()) controlPort_clkdiv_clk0__.loadApplicationFile(filename);if(!controlPort_clkdiv_clk1__.loadApplicationFile.empty()) controlPort_clkdiv_clk1__.loadApplicationFile(filename);if(!controlPort_clkdiv_clk2__.loadApplicationFile.empty()) controlPort_clkdiv_clk2__.loadApplicationFile(filename);if(!controlPort_clkdiv_clk3__.loadApplicationFile.empty()) controlPort_clkdiv_clk3__.loadApplicationFile(filename);};
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::terminate()
{{if(!controlPort_busslave__.terminate.empty()) controlPort_busslave__.terminate();if(!controlPort_clkdiv_clk0__.terminate.empty()) controlPort_clkdiv_clk0__.terminate();if(!controlPort_clkdiv_clk1__.terminate.empty()) controlPort_clkdiv_clk1__.terminate();if(!controlPort_clkdiv_clk2__.terminate.empty()) controlPort_clkdiv_clk2__.terminate();if(!controlPort_clkdiv_clk3__.terminate.empty()) controlPort_clkdiv_clk3__.terminate();};
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__SP810_SysCtrl::save(MxODataStream& os)
{{if(!controlPort_busslave__.save.empty()) controlPort_busslave__.save(os);if(!controlPort_clkdiv_clk0__.save.empty()) controlPort_clkdiv_clk0__.save(os);if(!controlPort_clkdiv_clk1__.save.empty()) controlPort_clkdiv_clk1__.save(os);if(!controlPort_clkdiv_clk2__.save.empty()) controlPort_clkdiv_clk2__.save(os);if(!controlPort_clkdiv_clk3__.save.empty()) controlPort_clkdiv_clk3__.save(os);};return true;
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__SP810_SysCtrl::restore(MxIDataStream& is)
{{if(!controlPort_busslave__.restore.empty()) controlPort_busslave__.restore(is);if(!controlPort_clkdiv_clk0__.restore.empty()) controlPort_clkdiv_clk0__.restore(is);if(!controlPort_clkdiv_clk1__.restore.empty()) controlPort_clkdiv_clk1__.restore(is);if(!controlPort_clkdiv_clk2__.restore.empty()) controlPort_clkdiv_clk2__.restore(is);if(!controlPort_clkdiv_clk3__.restore.empty()) controlPort_clkdiv_clk3__.restore(is);};return true;
}
}

#line 7 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::step()
{{if(!controlPort_busslave__.step.empty()) controlPort_busslave__.step();if(!controlPort_clkdiv_clk0__.step.empty()) controlPort_clkdiv_clk0__.step();if(!controlPort_clkdiv_clk1__.step.empty()) controlPort_clkdiv_clk1__.step();if(!controlPort_clkdiv_clk2__.step.empty()) controlPort_clkdiv_clk2__.step();if(!controlPort_clkdiv_clk3__.step.empty()) controlPort_clkdiv_clk3__.step();};
}
}

#line 202 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__SP810_SysCtrl::abstract_port__device__read(pv::ReadTransaction tx)
{
 if (tx.getAccessWidth() > pv::ACCESS_32_BITS || !tx.isAligned()) return tx.generateAbort();

 
 return tx.setReturnData32((uint32_t)registerRead(tx.getAddress() & ~3));
 
}
}

#line 210 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__SP810_SysCtrl::abstract_port__device__write(pv::WriteTransaction tx)
{
 if (tx.getAccessWidth() != pv::ACCESS_32_BITS || !tx.isAligned()) return tx.generateAbort();
 registerWrite(tx.getAddress(),tx.getData32());
 return tx.writeComplete();
 
}
}

#line 217 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__SP810_SysCtrl::abstract_port__device__debugRead(pv::ReadTransaction tx)
{
 return device.read(tx);
 
}
}

#line 222 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__SP810_SysCtrl::abstract_port__device__debugWrite(pv::WriteTransaction tx)
{
 return device.write(tx);
 
}
}

#line 240 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__SP810_SysCtrl::abstract_port__remap_stat__setValue(sg::Signal::State state)
{
 if(state == sg::Signal::Set)
 if(s_remap != state)
 s_remap = state;
 
}
}

#line 247 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/SP810_SysCtrl.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { sg::Signal::State 
Component__SP810_SysCtrl::abstract_port__remap_stat__getValue()
{
 if(s_remap)
 return sg::Signal::Set;
 else
 return sg::Signal::Clear;
 
}
}

#line 1862 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// ------------------------------------------------------------------------------
// implementation of class Component__SP810_SysCtrl
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

Component__SP810_SysCtrl::Component__SP810_SysCtrl(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params):
    SystemGenComponent(instName, simulationContext, params)

	,sysid(GetParameterValue(params, "sysid", MxS64CONST(0x0), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,use_s8(!!GetParameterValue(params, "use_s8", MxS64CONST(0x0), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))


	,cadiParameterProxy_busslave_of_PVBusSlave_to_SP810_SysCtrl__(0)

{
    // initialize properties__
	properties__["component_name"] = "";
	properties__["component_type"] = "Peripheral";
	properties__["debugger_name"] = "";
	properties__["debugger_start_command"] = "";
	properties__["default_view"] = "auto";
	properties__["description"] = "PrimeXsys System Controller(SP810) NB: Only EB relevant functionalities are fully implemented.";
	properties__["documentation_file"] = "../Docs/DUI0423O_fast_model_rm.pdf";
	properties__["dso_safe"] = "1";
	properties__["executes_software"] = "0";
	properties__["expose_extern_sub_component_cadi"] = "1";
	properties__["factory_namespace"] = "";
	properties__["has_cadi"] = "1";
	properties__["has_implicit_clk_in"] = "1";
	properties__["hidden"] = "0";
	properties__["icon_file"] = "";
	properties__["ip_provider"] = "";
	properties__["is_single_stepped"] = "0";
	properties__["license_feature"] = "";
	properties__["loadfile_extension"] = "";
	properties__["save_restore"] = "0";
	properties__["small_icon_file"] = "";
	properties__["variant"] = "";
	properties__["version"] = "8.1.37";

    // initialize parameter info
    {
        sg::ComponentFactory *factory = SP810_SysCtrl_GetFactory();

        sg::TargetInfo *targetInfo = factory->getTargetInfo(""); // empty string means 'this' component

        if(targetInfo) // if we have no target info we also have no parameters towards CADI interfaces
        {
            // get parameter infos
            for(unsigned int i = 0; i < targetInfo->parameter_count; i++)
            {
                parameterId2parameterName__[targetInfo->parameter_info[i].id] = targetInfo->parameter_info[i].name;
                parameterInfos__.push_back((targetInfo->parameter_info)[i]);
            }
        }

        factory->dereference();
    }

    // create subcomponents
	{
		sg::ComponentFactory *ClockDivider_factory = ClockDivider_GetFactory();
		sg::ComponentFactory *PVBusSlave_factory = PVBusSlave_GetFactory();
		{
			sg::Params params_busslave__ = params.getParamsFor("busslave");
			params_busslave__["size"] = MxU64CONST(0x0000000000001000);
			add(busslave = PVBusSlave_factory->instantiate("busslave", simulationContext, params_busslave__));
		}
		{
			sg::Params params_clkdiv_clk0__ = params.getParamsFor("clkdiv_clk0");
			add(clkdiv_clk0 = ClockDivider_factory->instantiate("clkdiv_clk0", simulationContext, params_clkdiv_clk0__));
		}
		{
			sg::Params params_clkdiv_clk1__ = params.getParamsFor("clkdiv_clk1");
			add(clkdiv_clk1 = ClockDivider_factory->instantiate("clkdiv_clk1", simulationContext, params_clkdiv_clk1__));
		}
		{
			sg::Params params_clkdiv_clk2__ = params.getParamsFor("clkdiv_clk2");
			add(clkdiv_clk2 = ClockDivider_factory->instantiate("clkdiv_clk2", simulationContext, params_clkdiv_clk2__));
		}
		{
			sg::Params params_clkdiv_clk3__ = params.getParamsFor("clkdiv_clk3");
			add(clkdiv_clk3 = ClockDivider_factory->instantiate("clkdiv_clk3", simulationContext, params_clkdiv_clk3__));
		}
		ClockDivider_factory->dereference();
		PVBusSlave_factory->dereference();
	}


    // bind local behaviors to this->control_port
    bind_method(control_port, configure, &Component__SP810_SysCtrl::control_port__configure, this);
    bind_method(control_port, init, &Component__SP810_SysCtrl::init, this);
    bind_method(control_port, interconnect, &Component__SP810_SysCtrl::interconnect, this);
//  bind_method(control_port, postConnect, &Component__SP810_SysCtrl::postConnect, this);
    bind_method(control_port, reset, &Component__SP810_SysCtrl::control_port__reset, this);
    bind_method(control_port, loadApplicationFile, &Component__SP810_SysCtrl::loadApplicationFile, this);
    bind_method(control_port, disconnect, &Component__SP810_SysCtrl::disconnect, this);
    bind_method(control_port, terminate, &Component__SP810_SysCtrl::control_port__terminate, this);
    bind_method(control_port, populateCADIMap, &Component__SP810_SysCtrl::control_port__populateCADIMap, this);
//  bind_method(control_port, refresh, &Component__SP810_SysCtrl::refresh, this);
    bind_method(control_port, step, &Component__SP810_SysCtrl::step, this);
    bind_method(control_port, update, &Component__SP810_SysCtrl::update, this);
    bind_method(control_port, communicate, &Component__SP810_SysCtrl::communicate, this);
    bind_method(control_port, getProperty, &Component__SP810_SysCtrl::control_port__getProperty, this);
    bind_method(control_port, traceEndOfCycle, &Component__SP810_SysCtrl::traceEndOfCycle, this);
    bind_method(control_port, bypass, &Component__SP810_SysCtrl::control_port__bypass, this);
    bind_method(control_port, run, &Component__SP810_SysCtrl::control_port__run, this);
    bind_method(control_port, stop, &Component__SP810_SysCtrl::control_port__stop, this);
    bind_method(control_port, idle, &Component__SP810_SysCtrl::control_port__idle, this);
    bind_method(control_port, quit, &Component__SP810_SysCtrl::control_port__quit, this);
    bind_method(control_port, setSimulationEngine, &Component__SP810_SysCtrl::control_port__setSimulationEngine, this);
    bind_method(control_port, message, &Component__SP810_SysCtrl::control_port__message, this);
    bind_method(control_port, callSimEngine, &Component__SP810_SysCtrl::control_port__callSimEngine, this);

    // avoid the automatic calling of the methods through the framework
    control_port.configure.setLocalOnly(true);
    control_port.init.setLocalOnly(true);
    control_port.interconnect.setLocalOnly(true);
//  control_port.postConnect.setLocalOnly(true);
    control_port.reset.setLocalOnly(true);
    control_port.loadApplicationFile.setLocalOnly(true);
    control_port.disconnect.setLocalOnly(true);
    control_port.terminate.setLocalOnly(true);
    control_port.save.setLocalOnly(true);
    control_port.restore.setLocalOnly(true);
    control_port.populateCADIMap.setLocalOnly(true);
//  control_port.refresh.setLocalOnly(true);
    control_port.step.setLocalOnly(true);
    control_port.update.setLocalOnly(true);
    control_port.communicate.setLocalOnly(true);
    control_port.getProperty.setLocalOnly(true);
    control_port.traceEndOfCycle.setLocalOnly(true);
//  control_port.bypass.setLocalOnly(true);
//  control_port.run.setLocalOnly(true);
//  control_port.stop.setLocalOnly(true);
//  control_port.idle.setLocalOnly(true); // broadcast ports don't have setLocalOnly
//  control_port.quit.setLocalOnly(true);
//  control_port.setSimulationEngine.setLocalOnly(true);

    // bind cadiPort behaviors
    bind_method(cadiPort__, GetParameters, &Component__SP810_SysCtrl::cadiPort__GetParameters, this);
    bind_method(cadiPort__, GetParameterInfo, &Component__SP810_SysCtrl::cadiPort__GetParameterInfo, this);
    bind_method(cadiPort__, GetProperty, &Component__SP810_SysCtrl::cadiPort__GetProperty, this);
    bind_method(cadiPort__, LoadApplicationFile, &Component__SP810_SysCtrl::cadiPort__LoadApplicationFile, this);
    bind_method(cadiPort__, GetApplicationsAndCommandLineParams, &Component__SP810_SysCtrl::cadiPort__GetApplicationsAndCommandLineParams, this);

    // connect control ports for subcomponents to subcomponents
	controlPort_busslave__.connectTo(busslave->findPort("$control"));
	controlPort_clkdiv_clk0__.connectTo(clkdiv_clk0->findPort("$control"));
	controlPort_clkdiv_clk1__.connectTo(clkdiv_clk1->findPort("$control"));
	controlPort_clkdiv_clk2__.connectTo(clkdiv_clk2->findPort("$control"));
	controlPort_clkdiv_clk3__.connectTo(clkdiv_clk3->findPort("$control"));



    // resource initialization code
    reset_resources__();

    // bind behaviors to abstract ports
	bind_method(device, read, &Component__SP810_SysCtrl::abstract_port__device__read, this);
	bind_method(device, write, &Component__SP810_SysCtrl::abstract_port__device__write, this);
	bind_method(device, debugRead, &Component__SP810_SysCtrl::abstract_port__device__debugRead, this);
	bind_method(device, debugWrite, &Component__SP810_SysCtrl::abstract_port__device__debugWrite, this);
	bind_method(remap_stat, setValue, &Component__SP810_SysCtrl::abstract_port__remap_stat__setValue, this);
	bind_method(remap_stat, getValue, &Component__SP810_SysCtrl::abstract_port__remap_stat__getValue, this);


    // add abstract ports
	device.SetName__("device");
	publishSlavePort("pvbus", pvbus);
	pvbus.SetName__("pvbus");
	publishSlavePort("clk_in", clk_in);
	clk_in.SetName__("clk_in");
	publishSlavePort("ref_clk_in", ref_clk_in);
	ref_clk_in.SetName__("ref_clk_in");
	publishSlavePort("npor", npor);
	npor.SetName__("npor");
	publishSlavePort("sys_id", sys_id);
	sys_id.SetName__("sys_id");
	publishSlavePort("sys_stat", sys_stat);
	sys_stat.SetName__("sys_stat");
	publishSlavePort("wd_en", wd_en);
	wd_en.SetName__("wd_en");
	publishSlavePort("sys_mode", sys_mode);
	sys_mode.SetName__("sys_mode");
	publishSlavePort("remap_stat", remap_stat);
	remap_stat.SetName__("remap_stat");
	publishMasterPortArray("timer_clk_en", timer_clk_en, 4);
	{for(int i = 0; i < 4; ++i) timer_clk_en[i].SetName__("timer_clk_en");}
	publishMasterPort("remap_clear", remap_clear);
	remap_clear.SetName__("remap_clear");
	publishMasterPort("wd_clk_en", wd_clk_en);
	wd_clk_en.SetName__("wd_clk_en");
	publishMasterPort("hclkdivsel", hclkdivsel);
	hclkdivsel.SetName__("hclkdivsel");
	publishMasterPort("sleep_mode", sleep_mode);
	sleep_mode.SetName__("sleep_mode");
	publishMasterPort("pll_en", pll_en);
	pll_en.SetName__("pll_en");


    // wire up static connection map
	pvbus.connectTo(busslave->findPort("pvbus_s"));
	busslave->findPort("device").connectTo(device);
	ref_clk_in.connectTo(clkdiv_clk0->findPort("clk_in"));
	ref_clk_in.connectTo(clkdiv_clk1->findPort("clk_in"));
	ref_clk_in.connectTo(clkdiv_clk2->findPort("clk_in"));
	ref_clk_in.connectTo(clkdiv_clk3->findPort("clk_in"));


    // init profiling

    // init resources


    // run the parameter write access functions for all of the component's parameters
    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        std::string paramName = parameterInfos__[i].name;

        switch (parameterInfos__[i].dataType)
        {
        case eslapi::CADI_PARAM_STRING:
            {
                std::string data = GetParameterValue(params, paramName, parameterInfos__[i].defaultString);
                parameter_write_string_func(paramNameToParamAccessFuncID(paramName), data);
            }
            break;
        case eslapi::CADI_PARAM_BOOL:
        case eslapi::CADI_PARAM_INT:
            {
                int64_t data = GetParameterValue(params, paramName, parameterInfos__[i].defaultValue, parameterInfos__[i].minValue, parameterInfos__[i].maxValue);
                parameter_write_func(paramNameToParamAccessFuncID(paramName), &data);
            }
            break;
        default:
            break;
        }
    }
}


Component__SP810_SysCtrl::~Component__SP810_SysCtrl()
{
}

void Component__SP810_SysCtrl::control_port__configure(const sg::Params& params)
{
	if(controlPort_busslave__.configure.implemented()) controlPort_busslave__.configure(params.getParamsFor("busslave"));
	if(controlPort_clkdiv_clk0__.configure.implemented()) controlPort_clkdiv_clk0__.configure(params.getParamsFor("clkdiv_clk0"));
	if(controlPort_clkdiv_clk1__.configure.implemented()) controlPort_clkdiv_clk1__.configure(params.getParamsFor("clkdiv_clk1"));
	if(controlPort_clkdiv_clk2__.configure.implemented()) controlPort_clkdiv_clk2__.configure(params.getParamsFor("clkdiv_clk2"));
	if(controlPort_clkdiv_clk3__.configure.implemented()) controlPort_clkdiv_clk3__.configure(params.getParamsFor("clkdiv_clk3"));


    assert(simulationContext__->getSimulationEngine());
    cadi__ = new Component__SP810_SysCtrl_CADI(this, simulationContext__->getSimulationEngine());

    // forward certain calls from CADI interface to this component
    cadi__->GetCADIPort().connectTo(cadiPort__);

    

    std::map< std::string, eslapi::CAInterface* > tempMap;
    control_port__populateCADIMap(tempMap, ""); // precompute mxdi map

	cadi__->EnableSubComponentCADIImport();


}

void Component__SP810_SysCtrl::control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* >&output_map, std::string const & base_prefix)
{
    if (componentName2CADI__.empty())
    {
        componentName2CADI__[getName()] = static_cast<eslapi::CADI*>(cadi__);
        std::string prefix = getName() + ".";

		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_busslave__.populateCADIMap.implemented())
			{
				controlPort_busslave__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
			eslapi::CADI *cadi = obtainCADI__("busslave", compMap);
			if (cadi != NULL)
			{
				cadiParameterProxy_busslave_of_PVBusSlave_to_SP810_SysCtrl__ = new CADIParameterProxy(cadi, &parameterFilter_busslave_of_PVBusSlave_to_SP810_SysCtrl__);
			}
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_clkdiv_clk0__.populateCADIMap.implemented())
			{
				controlPort_clkdiv_clk0__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_clkdiv_clk1__.populateCADIMap.implemented())
			{
				controlPort_clkdiv_clk1__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_clkdiv_clk2__.populateCADIMap.implemented())
			{
				controlPort_clkdiv_clk2__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_clkdiv_clk3__.populateCADIMap.implemented())
			{
				controlPort_clkdiv_clk3__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}

    }
    // Copy the local map into the given map with the requested prefix.
    for (std::map<std::string,eslapi::CAInterface*>::iterator it = componentName2CADI__.begin(); it != componentName2CADI__.end(); ++it)
    {
        output_map.insert(std::make_pair(base_prefix + it->first, it->second));
    }
}

eslapi::CADI* Component__SP810_SysCtrl::obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const
{
    std::map< std::string, eslapi::CAInterface* >::const_iterator it = componentName2CADI.find(subcomp);
    if (it != componentName2CADI.end())
    {
        eslapi::CAInterface *cai = it->second;
        if (cai != NULL)
        {
            cai = cai->ObtainInterface(eslapi::CADI::IFNAME(), 0, 0);
            if (cai != NULL)
            {
                return static_cast<eslapi::CADI*>(cai);
            }
        }
    }
    return NULL;
}

void Component__SP810_SysCtrl::insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface* > &componentName2CADI)
{
    for (std::map<std::string, eslapi::CAInterface*>::iterator it = componentName2CADI.begin(); it != componentName2CADI.end(); it++)
    {
        // put prefix in front of all entries
        componentName2CADI__[prefix + it->first] = it->second;
    }
}


std::string Component__SP810_SysCtrl::control_port__getProperty(const std::string& propname)
{
    if(properties__.find(propname) != properties__.end())
    {
        return properties__[propname];
    }
    else
        return ""; // unknown property
}


std::string Component__SP810_SysCtrl::control_port__bypass(const std::string&)
{
    return "";
}


void Component__SP810_SysCtrl::control_port__run()
{
}


void Component__SP810_SysCtrl::control_port__stop()
{
}


void Component__SP810_SysCtrl::control_port__idle()
{
}


void Component__SP810_SysCtrl::control_port__quit()
{
}


void Component__SP810_SysCtrl::control_port__setSimulationEngine(SimulationEngine*)
{
}


void Component__SP810_SysCtrl::control_port__message(const std::string &msg, sg::message::MessageType msgType)
{
}


std::string Component__SP810_SysCtrl::control_port__callSimEngine(const std::string &)
{
    return "";
}


void Component__SP810_SysCtrl::control_port__reset(int level)
{
    // restore the resources' reset values before executing 'reset'
    reset_resources__();
    reset(level);
}


void Component__SP810_SysCtrl::control_port__terminate()
{
    // the CADI was created before 'init', therefore we free it after 'terminate'
    terminate();
    freeCADIResources__();
}


void Component__SP810_SysCtrl::freeCADIResources__()
{
    // free CADI parameter proxies
	delete cadiParameterProxy_busslave_of_PVBusSlave_to_SP810_SysCtrl__;
	cadiParameterProxy_busslave_of_PVBusSlave_to_SP810_SysCtrl__ = 0;


    // free CADI interface
    delete cadi__;
    cadi__ = 0;
}


// CADI Port implementations
eslapi::CADIReturn_t Component__SP810_SysCtrl::cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params)
{
    // check arguments
    if(actualNumOfParams == 0)
        return eslapi::CADI_STATUS_IllegalArgument;
    *actualNumOfParams = 0;
    if(params == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    // collect parameters
    size_t i = 0;
    for (; (i < desiredNumOfParams) && ((startIndex + i) < parameterInfos__.size()); ++i)
    {
        params[i] = parameterInfos__[startIndex + i];
    }
    *actualNumOfParams = (MxU32)i;

    return eslapi::CADI_STATUS_OK;
}

eslapi::CADIReturn_t Component__SP810_SysCtrl::cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param)
{
    if(param == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        if (!strcmp(parameterInfos__[i].name, parameterName.c_str()))
        {
            *param = parameterInfos__[i];

            return eslapi::CADI_STATUS_OK;
        }
    }

    return eslapi::CADI_STATUS_GeneralError;
}


bool Component__SP810_SysCtrl::ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy, const char *param_name, int64_t intVal, const char *strVal)
{
    if (!proxy)
        return false;

    // we need the parameter's CADI id in order to create an eslapi::CADIParameterValue_t structure
    // therefore, we first retrieve its eslapi::CADIParameterInfo_t meta-data
    eslapi::CADIParameterInfo_t paramInfo;
    if (proxy->CADIGetParameterInfo(param_name, &paramInfo) != eslapi::CADI_STATUS_OK)
        return false;

    eslapi::CADIParameterValue_t paramVal(paramInfo.id, paramInfo.dataType, intVal, strVal);
    eslapi::CADIFactoryErrorMessage_t error;
    if (proxy->CADISetParameters(1, &paramVal, &error) != eslapi::CADI_STATUS_OK)
        return false;

    return true;
}


sg::accessfunc::AccessFuncResult Component__SP810_SysCtrl::parameter_read_func(uint32_t id, int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_sysid: *data = sysid; break;
	case PARAMETER_ID_use_s8: *data = use_s8; break;

        default:
            printf("error: Component__SP810_SysCtrl::parameter_read_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__SP810_SysCtrl::parameter_read_string_func(uint32_t id, std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__SP810_SysCtrl::parameter_read_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__SP810_SysCtrl::parameter_write_func(uint32_t id, const int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_sysid:
		{
			*(const_cast<uint32_t*>(&sysid)) = *data;
		}
		break;
	case PARAMETER_ID_use_s8:
		{
			*(const_cast<bool*>(&use_s8)) = !!*data;
		}
		break;

        default:
            printf("error: Component__SP810_SysCtrl::parameter_write_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__SP810_SysCtrl::parameter_write_string_func(uint32_t id, const std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__SP810_SysCtrl::parameter_write_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

void Component__SP810_SysCtrl::cadiPort__LoadApplicationFile(const std::string& filename)
{
    loadApplicationFile(filename);
    applications2params[filename] = "";
}

void Component__SP810_SysCtrl::cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_)
{
    applications2params_ = applications2params;
}

eslapi::CADIReturn_t Component__SP810_SysCtrl::cadiPort__GetProperty(const std::string& propertyName, std::string &value)
{
    if(properties__.find(propertyName) != properties__.end())
    {
        value = properties__[propertyName];
        return eslapi::CADI_STATUS_OK;
    }
    else
    {
        value = "";
        return eslapi::CADI_STATUS_GeneralError;
    }
}

// functions to stop and lock the simulator
// we only expose the simHalt() function in the documentation for the moment

void Component__SP810_SysCtrl::simHalt()
{
    cadi__->StopSimulation();
}


// start simulation from the inside
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
void Component__SP810_SysCtrl::simRun()
{
    cadi__->CADIExecContinue();
}


// return true if simulation is running
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
bool Component__SP810_SysCtrl::simIsRunning()
{
    uint32_t mode = eslapi::CADI_EXECMODE_Stop;
    cadi__->CADIExecGetMode(&mode);
    return mode != eslapi::CADI_EXECMODE_Stop;
}


void Component__SP810_SysCtrl::simShutdown()
{
    cadiPort__.simShutdown();
}

void Component__SP810_SysCtrl::simReset(uint32_t level)
{
    cadi__->CADIExecReset(level);
}

uint32_t Component__SP810_SysCtrl::paramNameToParamAccessFuncID(const std::string &name)
{
    uint32_t id = 0;
    if (name == "") id = 0xffffffff;
    if (name == "sysid") id = PARAMETER_ID_sysid;
    if (name == "use_s8") id = PARAMETER_ID_use_s8;

    return id;
}

void Component__SP810_SysCtrl::reset_resources__()
{
    // resource initialization code
	SCCTRL = 0; // reset register
	SCSYSSTAT = 0; // reset register
	SCIMCTRL = 0; // reset register
	SCIMSTAT = 0; // reset register
	SCXTALCTRL = 0; // reset register
	SCPLLCTRL = 0; // reset register
	SCPLLFCTRL = 0; // reset register
	SCPERCTRL0 = 0; // reset register
	SCPERCTRL1 = 0; // reset register
	SCPEREN = 0; // reset register
	SCPERDIS = 0; // reset register
	SCPERCLKEN = 0; // reset register
	SCPERSTAT = 0; // reset register
	SCSysID0 = 0; // reset register
	SCSysID1 = 0; // reset register
	SCSysID2 = 0; // reset register
	SCSysID3 = 0; // reset register
	SCITCR = 0; // reset register
	SCITIR0 = 0; // reset register
	SCITIR1 = 0; // reset register
	SCITOR = 0; // reset register
	SCCNTCTRL = 0; // reset register
	SCCNTDATA = 0; // reset register
	SCCNTSTEP = 0; // reset register
	SCPeriphID0 = 0; // reset register
	SCPeriphID1 = 0; // reset register
	SCPeriphID2 = 0; // reset register
	SCPeriphID3 = 0; // reset register
	SCPCellID0 = 0; // reset register
	SCPCellID1 = 0; // reset register
	SCPCellID2 = 0; // reset register
	SCPCellID3 = 0; // reset register

}


} // FVP_VE_Cortex_A15x1_NMS
#line 215 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::timer_callback_24mhz()
{
 SYS_24MHZ += RESET_TIME_24MHZ;
 return RESET_TIME_24MHZ;
 
}
}

#line 229 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::timer_callback_100hz()
{
 SYS_100HZ += RESET_TIME_100HZ;
 return RESET_TIME_100HZ;
 
}
}

#line 236 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::init()
{
 {if(!controlPort_busslave__.init.empty()) controlPort_busslave__.init();if(!controlPort_timer_24mhz__.init.empty()) controlPort_timer_24mhz__.init();if(!controlPort_timer_100Hz__.init.empty()) controlPort_timer_100Hz__.init();};
 RESET_TIME_24MHZ = 24000000;
 RESET_TIME_100HZ = 100;
 __VE_SysRegs_internal_1.set(RESET_TIME_24MHZ);
 __VE_SysRegs_internal_2.set(RESET_TIME_100HZ);
 mmbSite = 1;
 
}
}

#line 246 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::getSysID(int revision)
{
 uint32_t sysId = 0;

 
 

 
 
 switch (revision)
 {
 case BOARD_REV_A: sysId = 0x0225f500; break;
 case BOARD_REV_B: sysId = 0x12257500; break;
 case BOARD_REV_C: sysId = 0x22252500; break;
 }
 return sysId;
 
}
}

#line 264 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::getSysSW()
{
 
 return user_switches_value; 
 
}
}

#line 270 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::getSysCfgCtrl()
{
 
 uint32_t command = 0;

 if (sysCfgCtrl.busy)
 command |= SYS_CFGCTRL_START_MASK; 
 if (sysCfgCtrl.write)
 command |= SYS_CFGCTRL_WRITE_MASK;
 command |= (sysCfgCtrl.function << SYS_CFGCTRL_FUNCTION_BIT) & SYS_CFGCTRL_FUNCTION_MASK;
 command |= (sysCfgCtrl.site << SYS_CFGCTRL_SITE_BIT ) & SYS_CFGCTRL_SITE_MASK;
 command |= (sysCfgCtrl.position << SYS_CFGCTRL_POSITION_BIT) & SYS_CFGCTRL_POSITION_MASK;
 command |= (sysCfgCtrl.device << SYS_CFGCTRL_DEVICE_BIT ) & SYS_CFGCTRL_DEVICE_MASK;

 return command;
 
}
}

#line 287 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::setSysCfgCtrl(uint32_t data)
{
 sysCfgCtrl.busy = ((data & SYS_CFGCTRL_START_MASK ) >> SYS_CFGCTRL_START_BIT) != 0;
 sysCfgCtrl.write = ((data & SYS_CFGCTRL_WRITE_MASK ) >> SYS_CFGCTRL_WRITE_BIT) != 0;
 sysCfgCtrl.function = (data & SYS_CFGCTRL_FUNCTION_MASK) >> SYS_CFGCTRL_FUNCTION_BIT;
 sysCfgCtrl.site = (data & SYS_CFGCTRL_SITE_MASK ) >> SYS_CFGCTRL_SITE_BIT;
 sysCfgCtrl.position = (data & SYS_CFGCTRL_POSITION_MASK) >> SYS_CFGCTRL_POSITION_BIT;
 sysCfgCtrl.device = (data & SYS_CFGCTRL_DEVICE_MASK ) >> SYS_CFGCTRL_DEVICE_BIT;

 if (!0) ; else printf("sysCfgCtrl.busy = %d, sysCfgCtrl.write = %d, sysCfgCtrl.function = %d, sysCfgCtrl.site = %d, sysCfgCtrl.position = %d, sysCfgCtrl.device = %d\n", sysCfgCtrl.busy, sysCfgCtrl.write, sysCfgCtrl.function, sysCfgCtrl.site, sysCfgCtrl.position, sysCfgCtrl.device);

 if (sysCfgCtrl.busy)
 SYS_CFGSTAT = SYS_CFGSTAT & ~(SYS_CFGSTAT_COMPLETE|SYS_CFGSTAT_ERROR);
 else
 return;

 switch (sysCfgCtrl.site)
 {
 case SYS_CTRL_SITE_MB: 
 switch (sysCfgCtrl.function)
 {
 case SYS_CFG_OSC: 
 if (sysCfgCtrl.device == 1) { 
 if (sysCfgCtrl.write)
 {
 if (clock_CLCD.set.implemented())
 {
 clockCLCD = SYS_CFGDATA;
 clock_CLCD.set(clockCLCD, 1);
 }
 } else {
 SYS_CFGDATA = clockCLCD;
 }
 } else {
 
 SYS_CFGSTAT |= SYS_CFGSTAT_ERROR;
 }
 break;
 case SYS_CFG_SHUTDOWN:
 if (sysCfgCtrl.device == 0 && sysCfgCtrl.write) {
 if (exit_on_shutdown) simShutdown();
 }
 break;
 case SYS_CFG_MUXFPGA:
 
 mmbSite = SYS_CFGDATA;
 break;
 default:
 
 SYS_CFGSTAT |= SYS_CFGSTAT_ERROR;
 break;
 }
 break;

 case SYS_CTRL_SITE_DB1: 
 case SYS_CTRL_SITE_DB2:
 if (sysCfgCtrl.function == SYS_CFG_MUXFPGA)
 {
 
 mmbSite = SYS_CFGDATA;
 }
 else if (sysCfgCtrl.write && cb[sysCfgCtrl.site - 1].write.implemented())
 {
 
 
 bool ok = cb[sysCfgCtrl.site - 1].write(
 sysCfgCtrl.function, sysCfgCtrl.device, SYS_CFGDATA);
 if (!ok) SYS_CFGSTAT |= SYS_CFGSTAT_ERROR;
 }
 else if (!sysCfgCtrl.write && cb[sysCfgCtrl.site - 1].read.implemented())
 {
 
 
 bool ok = cb[sysCfgCtrl.site - 1].read(
 sysCfgCtrl.function, sysCfgCtrl.device, &SYS_CFGDATA);
 if (!ok) SYS_CFGSTAT |= SYS_CFGSTAT_ERROR;
 }
 else
 {
 
 SYS_CFGSTAT |= SYS_CFGSTAT_ERROR;
 }
 break;
 default: 
 
 SYS_CFGSTAT |= SYS_CFGSTAT_ERROR;
 break;
 }

 
 sysCfgCtrl.busy = false;
 SYS_CFGSTAT |= SYS_CFGSTAT_COMPLETE;
 
}
}

#line 381 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::reset(int level)
{
 {if(!controlPort_busslave__.reset.empty()) controlPort_busslave__.reset(level);if(!controlPort_timer_24mhz__.reset.empty()) controlPort_timer_24mhz__.reset(level);if(!controlPort_timer_100Hz__.reset.empty()) controlPort_timer_100Hz__.reset(level);};
 SYS_ID = getSysID(BOARD_REV_A);
 SYS_SW = getSysSW();
 SYS_LED = 0x00000000;
 SYS_100HZ = 0x00000000;
 SYS_FLAGS = 0x00000000;
 SYS_FLAGSCLR = 0x00000000;
 SYS_NVFLAGS = 0x00000000;
 SYS_NVFLAGSCLR = 0x00000000;
 if (mmc_card_present.getValue() == sg::Signal::Set)
 SYS_MCI = 0x00000001;
 else
 SYS_MCI = 0x00000000;

 SYS_FLASH = 0x00000000;
 SYS_CFGSW = 0x00000000;
 SYS_24MHZ = 0x00000000;

 SYS_MISC = 0x00302000;
 if (!tilePresent)
 {
 
 
 SYS_MISC |= 0x1000;
 }
 SYS_DMA = 0x00000000;


 SYS_PROCID0 = sys_proc_id0;
 SYS_PROCID1 = sys_proc_id1;

 SYS_CFGCTRL = 0x00000000;


 SYS_CFGSTAT = 0x00000000;

 RESET_TIME_24MHZ = 24000000;
 RESET_TIME_100HZ = 100;
 __VE_SysRegs_internal_1.set(RESET_TIME_24MHZ);
 __VE_SysRegs_internal_2.set(RESET_TIME_100HZ);
 setSysCfgCtrl(0);
 clockCLCD = 23750000; 
 clock_CLCD.set(clockCLCD,1);
 mmbSite = 1; 
 
}
}

#line 430 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::registerRead(uint32_t device_addr)
{
 uint32_t data = 0;

 switch(device_addr)
 {
 case 0x0:
 data = SYS_ID;
 if (!0) ; else printf("SYS_ID -> %x\n", data);
 break;
 case 0x04:
 data = SYS_SW;
 if (!0) ; else printf("SYS_SW -> %x\n", data);
 break;
 case 0x08:
 data = SYS_LED;
 if (!0) ; else printf("SYS_LED -> %x\n", data);
 break;
 case 0x24:
 data = SYS_100HZ + (RESET_TIME_100HZ - __VE_SysRegs_internal_2.remaining());
 if (!0) ; else printf("SYS_100HZ -> %x\n", data);
 break;
 case 0x30:
 data = SYS_FLAGS;
 if (!0) ; else printf("SYS_FLAGS -> %x\n", data);
 break;
 case 0x34:
 if (!0) ; else printf("SYS_FLAGSCLR is write only!\n");
 break;
 case 0x38:
 data = SYS_NVFLAGS;
 if (!0) ; else printf("SYS_NVFLAGS -> %x\n", data);
 break;
 case 0x3C:
 if (!0) ; else printf("SYS_NVFLAGSCLR is write only!\n");
 break;
 case 0x48:
 data = SYS_MCI;
 if (!0) ; else printf("SYS_MCI -> %x\n", data);
 break;
 case 0x4C:
 data = SYS_FLASH;
 if (!0) ; else printf("SYS_FLASH -> %x\n", data);
 break;
 case 0x58:
 data = SYS_CFGSW;
 if (!0) ; else printf("SYS_CFGSW -> %x\n", data);
 break;
 case 0x5C:
 data = SYS_24MHZ + (RESET_TIME_24MHZ - __VE_SysRegs_internal_1.remaining());
 if (!0) ; else printf("SYS_24MHZ -> %x\n", data);
 break;
 case 0x60:
 data = SYS_MISC;
 if (!0) ; else printf("SYS_MISC -> %x\n", data);
 break;
 case 0x64:
 data = SYS_DMA;
 if (!0) ; else printf("SYS_DMA -> %x\n", data);
 break;
 case 0x84:
 data = SYS_PROCID0;
 if (!0) ; else printf("SYS_PROCID0 -> %x\n", data);
 break;
 case 0x88:
 data = SYS_PROCID1;
 if (!0) ; else printf("SYS_PROCID1 -> %x\n", data);
 break;
 case 0xA0:
 data = SYS_CFGDATA;
 if (!0) ; else printf("SYS_CFGDATA -> %x\n", data);
 break;
 case 0xA4:
 data = getSysCfgCtrl();
 if (!0) ; else printf("SYS_CFGCTRL -> %x\n", data);
 break;
 case 0xA8:
 data = SYS_CFGSTAT;
 if (!0) ; else printf("SYS_CFGSTAT -> %x\n", data);
 break;
 default:
 data = 0xdeaddead;
 if (!0) ; else printf("UNKNOWN[0x%02x] -> %x\n", device_addr, data);
 break;
 }


 return data;
 
}
}

#line 520 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::registerWrite(uint32_t device_addr, uint32_t data)
{
 switch(device_addr)
 {
 case 0x0:
 if (!0) ; else printf("SYS_ID <- %x\n", data);
 SYS_ID = (SYS_ID & 0x0FFFFFFF) | (data & 0xF0000000); 
 break;
 case 0x04:
 if (!0) ; else printf("SYS_SW <- %x\n", data);
 SYS_SW = (SYS_SW & 0xFFFFFF00) | (data & 0xFF); 
 break;
 case 0x08:
 if (!0) ; else printf("SYS_LED <- %x\n", data);
 SYS_LED = (SYS_LED & 0xFFFFFF00) | (data & 0xFF); 
 break;
 case 0x24:
 if (!0) ; else printf("SYS_100HZ is read only!\n");
 break;
 case 0x30:
 if (!0) ; else printf("SYS_FLAGS <- %x\n", data);
 SYS_FLAGS |= data;
 break;
 case 0x34:
 if (!0) ; else printf("SYS_FLAGSCLR <- %x\n", data);
 SYS_FLAGS = ~((~SYS_FLAGS) | data);
 break;
 case 0x38:
 if (!0) ; else printf("SYS_NVFLAGS <- %x\n", data);
 SYS_NVFLAGS |= data;
 break;
 case 0x3C:
 if (!0) ; else printf("SYS_NVFLAGSCLR <- %x\n", data);
 SYS_NVFLAGSCLR = ~((~SYS_NVFLAGSCLR) | data);
 break;
 case 0x48:
 if (!0) ; else printf("SYS_MCI is read only!");
 break;
 case 0x4C:
 if (!0) ; else printf("SYS_FLASH <- %x\n", data);
 SYS_FLASH = data & 0x1; 
 break;
 case 0x58:
 if (!0) ; else printf("SYS_CFGSW <- %x\n", data);
 SYS_CFGSW = (SYS_CFGSW & 0xFFFFFF00) | (data & 0xFF); 
 break;
 case 0x5C:
 if (!0) ; else printf("SYS_24MHZ is read only!\n");
 break;
 case 0x60:
 if (!0) ; else printf("SYS_MISC <- %x\n", data);
 SYS_MISC = (SYS_MISC & 0xf007ffff) | (data & 0x0ff80000);
 
 break;
 case 0x64:
 if (!0) ; else printf("SYS_DMA <- %x\n", data);
 
 break;
 case 0x84:
 if (!0) ; else printf("SYS_PROCID0 <- %x\n", data);
 SYS_PROCID0 = data;
 break;
 case 0x88:
 if (!0) ; else printf("SYS_PROCID1 <- %x\n", data);
 SYS_PROCID1 = data;
 break;
 case 0xA0:
 if (!0) ; else printf("SYS_CFGDATA <- %x\n", data);
 SYS_CFGDATA = data;
 break;
 case 0xA4:
 if (!0) ; else printf("SYS_CFGCTRL <- %x\n", data);
 setSysCfgCtrl(data);
 break;
 case 0xA8:
 if (!0) ; else printf("SYS_CFGSTAT <- %x\n", data);
 SYS_CFGSTAT = data & (SYS_CFGSTAT_COMPLETE | SYS_CFGSTAT_ERROR);
 break;
 default:
 if (!0) ; else printf("UNKNOWN[0x%02x] <- %x\n", device_addr, data);
 break;
 }
 
}
}

#line 605 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { AccessFuncResult 
Component__VE_SysRegs::debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects)
{
 *datap = registerRead(reg_id);

 return eslapi::CADI_STATUS_OK;
 
}
}

#line 612 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { AccessFuncResult 
Component__VE_SysRegs::debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects)
{
 registerWrite(reg_id, (uint32_t)*datap);

 return eslapi::CADI_STATUS_OK;
 
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::interconnect()
{{if(!controlPort_busslave__.interconnect.empty()) controlPort_busslave__.interconnect();if(!controlPort_timer_24mhz__.interconnect.empty()) controlPort_timer_24mhz__.interconnect();if(!controlPort_timer_100Hz__.interconnect.empty()) controlPort_timer_100Hz__.interconnect();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::disconnect()
{{if(!controlPort_busslave__.disconnect.empty()) controlPort_busslave__.disconnect();if(!controlPort_timer_24mhz__.disconnect.empty()) controlPort_timer_24mhz__.disconnect();if(!controlPort_timer_100Hz__.disconnect.empty()) controlPort_timer_100Hz__.disconnect();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::update()
{{if(!controlPort_busslave__.update.empty()) controlPort_busslave__.update();if(!controlPort_timer_24mhz__.update.empty()) controlPort_timer_24mhz__.update();if(!controlPort_timer_100Hz__.update.empty()) controlPort_timer_100Hz__.update();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::communicate()
{{if(!controlPort_busslave__.communicate.empty()) controlPort_busslave__.communicate();if(!controlPort_timer_24mhz__.communicate.empty()) controlPort_timer_24mhz__.communicate();if(!controlPort_timer_100Hz__.communicate.empty()) controlPort_timer_100Hz__.communicate();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::traceEndOfCycle()
{{if(!controlPort_busslave__.traceEndOfCycle.empty()) controlPort_busslave__.traceEndOfCycle();if(!controlPort_timer_24mhz__.traceEndOfCycle.empty()) controlPort_timer_24mhz__.traceEndOfCycle();if(!controlPort_timer_100Hz__.traceEndOfCycle.empty()) controlPort_timer_100Hz__.traceEndOfCycle();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::loadApplicationFile(const std::string& filename)
{{if(!controlPort_busslave__.loadApplicationFile.empty()) controlPort_busslave__.loadApplicationFile(filename);if(!controlPort_timer_24mhz__.loadApplicationFile.empty()) controlPort_timer_24mhz__.loadApplicationFile(filename);if(!controlPort_timer_100Hz__.loadApplicationFile.empty()) controlPort_timer_100Hz__.loadApplicationFile(filename);};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::terminate()
{{if(!controlPort_busslave__.terminate.empty()) controlPort_busslave__.terminate();if(!controlPort_timer_24mhz__.terminate.empty()) controlPort_timer_24mhz__.terminate();if(!controlPort_timer_100Hz__.terminate.empty()) controlPort_timer_100Hz__.terminate();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VE_SysRegs::save(MxODataStream& os)
{{if(!controlPort_busslave__.save.empty()) controlPort_busslave__.save(os);if(!controlPort_timer_24mhz__.save.empty()) controlPort_timer_24mhz__.save(os);if(!controlPort_timer_100Hz__.save.empty()) controlPort_timer_100Hz__.save(os);};return true;
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VE_SysRegs::restore(MxIDataStream& is)
{{if(!controlPort_busslave__.restore.empty()) controlPort_busslave__.restore(is);if(!controlPort_timer_24mhz__.restore.empty()) controlPort_timer_24mhz__.restore(is);if(!controlPort_timer_100Hz__.restore.empty()) controlPort_timer_100Hz__.restore(is);};return true;
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::step()
{{if(!controlPort_busslave__.step.empty()) controlPort_busslave__.step();if(!controlPort_timer_24mhz__.step.empty()) controlPort_timer_24mhz__.step();if(!controlPort_timer_100Hz__.step.empty()) controlPort_timer_100Hz__.step();};
}
}

#line 133 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__VE_SysRegs::abstract_port__device__read(pv::ReadTransaction tx)
{
 
 
 if (tx.getAccessWidth() > pv::ACCESS_32_BITS && (tx.getAddress() & 3) != 0) return tx.generateAbort();

 
 return tx.setReturnData32(registerRead(tx.getAddress() & ~3));
 
}
}

#line 143 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__VE_SysRegs::abstract_port__device__write(pv::WriteTransaction tx)
{
 
 
 if (tx.getAccessWidth() > pv::ACCESS_32_BITS && (tx.getAddress() & 3) != 0) return tx.generateAbort();
 registerWrite(tx.getAddress() & ~3, tx.getData32());
 return tx.writeComplete();
 
}
}

#line 152 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__VE_SysRegs::abstract_port__device__debugRead(pv::ReadTransaction tx)
{
 return device.read(tx);
 
}
}

#line 157 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__VE_SysRegs::abstract_port__device__debugWrite(pv::WriteTransaction tx)
{
 return device.write(tx);
 
}
}

#line 167 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::abstract_port__user_switches__getValue()
{
 return SYS_SW;
 
}
}

#line 171 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::abstract_port__user_switches__setValue(uint32_t data)
{
 SYS_SW = data;
 
}
}

#line 179 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::abstract_port__leds__getValue()
{
 return SYS_LED;
 
}
}

#line 198 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::abstract_port__mmc_card_present__setValue(sg::Signal::State state)
{
 if (state == sg::Signal::Set)
 SYS_MCI |= 0x1;
 else
 SYS_MCI &= ~0x1;
 
}
}

#line 210 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::abstract_port__timer_callback_handler_24mhz__signal()
{
 return timer_callback_24mhz();
 
}
}

#line 224 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VE_SysRegs::abstract_port__timer_callback_handler_100Hz__signal()
{
 return timer_callback_100hz();
 
}
}

#line 623 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { const VisRasterLayout* 
Component__VE_SysRegs::abstract_port__mmb__lock(uint32_t index)
{
 if ((mmbSite == index) && lcd.lock.implemented())
 return lcd.lock();
 else
 return 0;
 
}
}

#line 631 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::abstract_port__mmb__unlock(uint32_t index)
{
 if ((mmbSite == index) && lcd.unlock.implemented())
 lcd.unlock();
 
}
}

#line 637 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::abstract_port__mmb__update(uint32_t index, int x, int y, unsigned int w, unsigned int h)
{
 if ((mmbSite == index) && lcd.update.implemented())
 lcd.update(x, y, w, h);
 
}
}

#line 644 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VE_SysRegs.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VE_SysRegs::abstract_port__mmb__setPreferredLayout(uint32_t index, unsigned int width, unsigned int height, unsigned int depth)
{
 if ((mmbSite == index) && lcd.setPreferredLayout.implemented())
 lcd.setPreferredLayout(width, height, depth);
 
}
}

#line 3206 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// ------------------------------------------------------------------------------
// implementation of class Component__VE_SysRegs
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

Component__VE_SysRegs::Component__VE_SysRegs(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params):
    SystemGenComponent(instName, simulationContext, params)

	,sys_proc_id0(GetParameterValue(params, "sys_proc_id0", MxS64CONST(0xc000000), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,sys_proc_id1(GetParameterValue(params, "sys_proc_id1", MxS64CONST(0xff000000), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,user_switches_value(GetParameterValue(params, "user_switches_value", MxS64CONST(0x0), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,exit_on_shutdown(!!GetParameterValue(params, "exit_on_shutdown", MxS64CONST(0x0), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,tilePresent(!!GetParameterValue(params, "tilePresent", MxS64CONST(0x1), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))


	,cadiParameterProxy_busslave_of_PVBusSlave_to_VE_SysRegs__(0)

{
    // initialize properties__
	properties__["component_name"] = "";
	properties__["component_type"] = "";
	properties__["debugger_name"] = "";
	properties__["debugger_start_command"] = "";
	properties__["default_view"] = "auto";
	properties__["description"] = "";
	properties__["documentation_file"] = "";
	properties__["dso_safe"] = "1";
	properties__["executes_software"] = "0";
	properties__["expose_extern_sub_component_cadi"] = "1";
	properties__["factory_namespace"] = "";
	properties__["has_cadi"] = "1";
	properties__["has_implicit_clk_in"] = "1";
	properties__["hidden"] = "0";
	properties__["icon_file"] = "";
	properties__["ip_provider"] = "";
	properties__["is_single_stepped"] = "0";
	properties__["license_feature"] = "";
	properties__["loadfile_extension"] = "";
	properties__["save_restore"] = "0";
	properties__["small_icon_file"] = "";
	properties__["variant"] = "";
	properties__["version"] = "8.1.37";

    // initialize parameter info
    {
        sg::ComponentFactory *factory = VE_SysRegs_GetFactory();

        sg::TargetInfo *targetInfo = factory->getTargetInfo(""); // empty string means 'this' component

        if(targetInfo) // if we have no target info we also have no parameters towards CADI interfaces
        {
            // get parameter infos
            for(unsigned int i = 0; i < targetInfo->parameter_count; i++)
            {
                parameterId2parameterName__[targetInfo->parameter_info[i].id] = targetInfo->parameter_info[i].name;
                parameterInfos__.push_back((targetInfo->parameter_info)[i]);
            }
        }

        factory->dereference();
    }

    // create subcomponents
	{
		sg::ComponentFactory *ClockTimer_factory = ClockTimer_GetFactory();
		sg::ComponentFactory *PVBusSlave_factory = PVBusSlave_GetFactory();
		{
			sg::Params params_busslave__ = params.getParamsFor("busslave");
			params_busslave__["size"] = MxU64CONST(0x0000000000001000);
			add(busslave = PVBusSlave_factory->instantiate("busslave", simulationContext, params_busslave__));
		}
		{
			sg::Params params_timer_24mhz__ = params.getParamsFor("timer_24mhz");
			add(timer_24mhz = ClockTimer_factory->instantiate("timer_24mhz", simulationContext, params_timer_24mhz__));
		}
		{
			sg::Params params_timer_100Hz__ = params.getParamsFor("timer_100Hz");
			add(timer_100Hz = ClockTimer_factory->instantiate("timer_100Hz", simulationContext, params_timer_100Hz__));
		}
		ClockTimer_factory->dereference();
		PVBusSlave_factory->dereference();
	}


    // bind local behaviors to this->control_port
    bind_method(control_port, configure, &Component__VE_SysRegs::control_port__configure, this);
    bind_method(control_port, init, &Component__VE_SysRegs::init, this);
    bind_method(control_port, interconnect, &Component__VE_SysRegs::interconnect, this);
//  bind_method(control_port, postConnect, &Component__VE_SysRegs::postConnect, this);
    bind_method(control_port, reset, &Component__VE_SysRegs::control_port__reset, this);
    bind_method(control_port, loadApplicationFile, &Component__VE_SysRegs::loadApplicationFile, this);
    bind_method(control_port, disconnect, &Component__VE_SysRegs::disconnect, this);
    bind_method(control_port, terminate, &Component__VE_SysRegs::control_port__terminate, this);
    bind_method(control_port, populateCADIMap, &Component__VE_SysRegs::control_port__populateCADIMap, this);
//  bind_method(control_port, refresh, &Component__VE_SysRegs::refresh, this);
    bind_method(control_port, step, &Component__VE_SysRegs::step, this);
    bind_method(control_port, update, &Component__VE_SysRegs::update, this);
    bind_method(control_port, communicate, &Component__VE_SysRegs::communicate, this);
    bind_method(control_port, getProperty, &Component__VE_SysRegs::control_port__getProperty, this);
    bind_method(control_port, traceEndOfCycle, &Component__VE_SysRegs::traceEndOfCycle, this);
    bind_method(control_port, bypass, &Component__VE_SysRegs::control_port__bypass, this);
    bind_method(control_port, run, &Component__VE_SysRegs::control_port__run, this);
    bind_method(control_port, stop, &Component__VE_SysRegs::control_port__stop, this);
    bind_method(control_port, idle, &Component__VE_SysRegs::control_port__idle, this);
    bind_method(control_port, quit, &Component__VE_SysRegs::control_port__quit, this);
    bind_method(control_port, setSimulationEngine, &Component__VE_SysRegs::control_port__setSimulationEngine, this);
    bind_method(control_port, message, &Component__VE_SysRegs::control_port__message, this);
    bind_method(control_port, callSimEngine, &Component__VE_SysRegs::control_port__callSimEngine, this);

    // avoid the automatic calling of the methods through the framework
    control_port.configure.setLocalOnly(true);
    control_port.init.setLocalOnly(true);
    control_port.interconnect.setLocalOnly(true);
//  control_port.postConnect.setLocalOnly(true);
    control_port.reset.setLocalOnly(true);
    control_port.loadApplicationFile.setLocalOnly(true);
    control_port.disconnect.setLocalOnly(true);
    control_port.terminate.setLocalOnly(true);
    control_port.save.setLocalOnly(true);
    control_port.restore.setLocalOnly(true);
    control_port.populateCADIMap.setLocalOnly(true);
//  control_port.refresh.setLocalOnly(true);
    control_port.step.setLocalOnly(true);
    control_port.update.setLocalOnly(true);
    control_port.communicate.setLocalOnly(true);
    control_port.getProperty.setLocalOnly(true);
    control_port.traceEndOfCycle.setLocalOnly(true);
//  control_port.bypass.setLocalOnly(true);
//  control_port.run.setLocalOnly(true);
//  control_port.stop.setLocalOnly(true);
//  control_port.idle.setLocalOnly(true); // broadcast ports don't have setLocalOnly
//  control_port.quit.setLocalOnly(true);
//  control_port.setSimulationEngine.setLocalOnly(true);

    // bind cadiPort behaviors
    bind_method(cadiPort__, GetParameters, &Component__VE_SysRegs::cadiPort__GetParameters, this);
    bind_method(cadiPort__, GetParameterInfo, &Component__VE_SysRegs::cadiPort__GetParameterInfo, this);
    bind_method(cadiPort__, GetProperty, &Component__VE_SysRegs::cadiPort__GetProperty, this);
    bind_method(cadiPort__, LoadApplicationFile, &Component__VE_SysRegs::cadiPort__LoadApplicationFile, this);
    bind_method(cadiPort__, GetApplicationsAndCommandLineParams, &Component__VE_SysRegs::cadiPort__GetApplicationsAndCommandLineParams, this);

    // connect control ports for subcomponents to subcomponents
	controlPort_busslave__.connectTo(busslave->findPort("$control"));
	controlPort_timer_24mhz__.connectTo(timer_24mhz->findPort("$control"));
	controlPort_timer_100Hz__.connectTo(timer_100Hz->findPort("$control"));



    // resource initialization code
    reset_resources__();

    // bind behaviors to abstract ports
	bind_method(device, read, &Component__VE_SysRegs::abstract_port__device__read, this);
	bind_method(device, write, &Component__VE_SysRegs::abstract_port__device__write, this);
	bind_method(device, debugRead, &Component__VE_SysRegs::abstract_port__device__debugRead, this);
	bind_method(device, debugWrite, &Component__VE_SysRegs::abstract_port__device__debugWrite, this);
	bind_method(user_switches, getValue, &Component__VE_SysRegs::abstract_port__user_switches__getValue, this);
	bind_method(user_switches, setValue, &Component__VE_SysRegs::abstract_port__user_switches__setValue, this);
	bind_method(leds, getValue, &Component__VE_SysRegs::abstract_port__leds__getValue, this);
	bind_method(mmc_card_present, setValue, &Component__VE_SysRegs::abstract_port__mmc_card_present__setValue, this);
	bind_method(timer_callback_handler_24mhz, signal, &Component__VE_SysRegs::abstract_port__timer_callback_handler_24mhz__signal, this);
	bind_method(timer_callback_handler_100Hz, signal, &Component__VE_SysRegs::abstract_port__timer_callback_handler_100Hz__signal, this);
	bind_vector_method(mmb, lock, 3, &Component__VE_SysRegs::abstract_port__mmb__lock, this);
	bind_vector_method(mmb, unlock, 3, &Component__VE_SysRegs::abstract_port__mmb__unlock, this);
	bind_vector_method(mmb, update, 3, &Component__VE_SysRegs::abstract_port__mmb__update, this);
	bind_vector_method(mmb, setPreferredLayout, 3, &Component__VE_SysRegs::abstract_port__mmb__setPreferredLayout, this);


    // add abstract ports
	publishSlavePort("pvbus", pvbus);
	pvbus.SetName__("pvbus");
	device.SetName__("device");
	publishSlavePort("clock_24Mhz", clock_24Mhz);
	clock_24Mhz.SetName__("clock_24Mhz");
	publishSlavePort("clock_100Hz", clock_100Hz);
	clock_100Hz.SetName__("clock_100Hz");
	publishMasterPort("user_switches", user_switches);
	user_switches.SetName__("user_switches");
	publishMasterPort("leds", leds);
	leds.SetName__("leds");
	publishSlavePort("mmc_card_present", mmc_card_present);
	mmc_card_present.SetName__("mmc_card_present");
	timer_callback_handler_24mhz.SetName__("timer_callback_handler_24mhz");
	timer_callback_handler_100Hz.SetName__("timer_callback_handler_100Hz");
	publishMasterPort("clock_CLCD", clock_CLCD);
	clock_CLCD.SetName__("clock_CLCD");
	publishMasterPort("lcd", lcd);
	lcd.SetName__("lcd");
	publishMasterPortArray("cb", cb, 2);
	{for(int i = 0; i < 2; ++i) cb[i].SetName__("cb");}
	publishSlavePortArray("mmb", mmb, 3);
	{for(int i = 0; i < 3; ++i) mmb[i].SetName__("mmb");}
	__VE_SysRegs_internal_1.SetName__("__VE_SysRegs_internal_1");
	__VE_SysRegs_internal_2.SetName__("__VE_SysRegs_internal_2");


    // wire up static connection map
	pvbus.connectTo(busslave->findPort("pvbus_s"));
	busslave->findPort("device").connectTo(device);
	clock_24Mhz.connectTo(timer_24mhz->findPort("clk_in"));
	clock_100Hz.connectTo(timer_100Hz->findPort("clk_in"));
	timer_24mhz->findPort("timer_callback").connectTo(timer_callback_handler_24mhz);
	timer_100Hz->findPort("timer_callback").connectTo(timer_callback_handler_100Hz);
	__VE_SysRegs_internal_1.connectTo(timer_24mhz->findPort("timer_control"));
	__VE_SysRegs_internal_2.connectTo(timer_100Hz->findPort("timer_control"));


    // init profiling

    // init resources


    // run the parameter write access functions for all of the component's parameters
    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        std::string paramName = parameterInfos__[i].name;

        switch (parameterInfos__[i].dataType)
        {
        case eslapi::CADI_PARAM_STRING:
            {
                std::string data = GetParameterValue(params, paramName, parameterInfos__[i].defaultString);
                parameter_write_string_func(paramNameToParamAccessFuncID(paramName), data);
            }
            break;
        case eslapi::CADI_PARAM_BOOL:
        case eslapi::CADI_PARAM_INT:
            {
                int64_t data = GetParameterValue(params, paramName, parameterInfos__[i].defaultValue, parameterInfos__[i].minValue, parameterInfos__[i].maxValue);
                parameter_write_func(paramNameToParamAccessFuncID(paramName), &data);
            }
            break;
        default:
            break;
        }
    }
}


Component__VE_SysRegs::~Component__VE_SysRegs()
{
}

void Component__VE_SysRegs::control_port__configure(const sg::Params& params)
{
	if(controlPort_busslave__.configure.implemented()) controlPort_busslave__.configure(params.getParamsFor("busslave"));
	if(controlPort_timer_24mhz__.configure.implemented()) controlPort_timer_24mhz__.configure(params.getParamsFor("timer_24mhz"));
	if(controlPort_timer_100Hz__.configure.implemented()) controlPort_timer_100Hz__.configure(params.getParamsFor("timer_100Hz"));


    assert(simulationContext__->getSimulationEngine());
    cadi__ = new Component__VE_SysRegs_CADI(this, simulationContext__->getSimulationEngine());

    // forward certain calls from CADI interface to this component
    cadi__->GetCADIPort().connectTo(cadiPort__);

    

    std::map< std::string, eslapi::CAInterface* > tempMap;
    control_port__populateCADIMap(tempMap, ""); // precompute mxdi map

	cadi__->EnableSubComponentCADIImport();


}

void Component__VE_SysRegs::control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* >&output_map, std::string const & base_prefix)
{
    if (componentName2CADI__.empty())
    {
        componentName2CADI__[getName()] = static_cast<eslapi::CADI*>(cadi__);
        std::string prefix = getName() + ".";

		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_busslave__.populateCADIMap.implemented())
			{
				controlPort_busslave__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
			eslapi::CADI *cadi = obtainCADI__("busslave", compMap);
			if (cadi != NULL)
			{
				cadiParameterProxy_busslave_of_PVBusSlave_to_VE_SysRegs__ = new CADIParameterProxy(cadi, &parameterFilter_busslave_of_PVBusSlave_to_VE_SysRegs__);
			}
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_timer_24mhz__.populateCADIMap.implemented())
			{
				controlPort_timer_24mhz__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_timer_100Hz__.populateCADIMap.implemented())
			{
				controlPort_timer_100Hz__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}

    }
    // Copy the local map into the given map with the requested prefix.
    for (std::map<std::string,eslapi::CAInterface*>::iterator it = componentName2CADI__.begin(); it != componentName2CADI__.end(); ++it)
    {
        output_map.insert(std::make_pair(base_prefix + it->first, it->second));
    }
}

eslapi::CADI* Component__VE_SysRegs::obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const
{
    std::map< std::string, eslapi::CAInterface* >::const_iterator it = componentName2CADI.find(subcomp);
    if (it != componentName2CADI.end())
    {
        eslapi::CAInterface *cai = it->second;
        if (cai != NULL)
        {
            cai = cai->ObtainInterface(eslapi::CADI::IFNAME(), 0, 0);
            if (cai != NULL)
            {
                return static_cast<eslapi::CADI*>(cai);
            }
        }
    }
    return NULL;
}

void Component__VE_SysRegs::insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface* > &componentName2CADI)
{
    for (std::map<std::string, eslapi::CAInterface*>::iterator it = componentName2CADI.begin(); it != componentName2CADI.end(); it++)
    {
        // put prefix in front of all entries
        componentName2CADI__[prefix + it->first] = it->second;
    }
}


std::string Component__VE_SysRegs::control_port__getProperty(const std::string& propname)
{
    if(properties__.find(propname) != properties__.end())
    {
        return properties__[propname];
    }
    else
        return ""; // unknown property
}


std::string Component__VE_SysRegs::control_port__bypass(const std::string&)
{
    return "";
}


void Component__VE_SysRegs::control_port__run()
{
}


void Component__VE_SysRegs::control_port__stop()
{
}


void Component__VE_SysRegs::control_port__idle()
{
}


void Component__VE_SysRegs::control_port__quit()
{
}


void Component__VE_SysRegs::control_port__setSimulationEngine(SimulationEngine*)
{
}


void Component__VE_SysRegs::control_port__message(const std::string &msg, sg::message::MessageType msgType)
{
}


std::string Component__VE_SysRegs::control_port__callSimEngine(const std::string &)
{
    return "";
}


void Component__VE_SysRegs::control_port__reset(int level)
{
    // restore the resources' reset values before executing 'reset'
    reset_resources__();
    reset(level);
}


void Component__VE_SysRegs::control_port__terminate()
{
    // the CADI was created before 'init', therefore we free it after 'terminate'
    terminate();
    freeCADIResources__();
}


void Component__VE_SysRegs::freeCADIResources__()
{
    // free CADI parameter proxies
	delete cadiParameterProxy_busslave_of_PVBusSlave_to_VE_SysRegs__;
	cadiParameterProxy_busslave_of_PVBusSlave_to_VE_SysRegs__ = 0;


    // free CADI interface
    delete cadi__;
    cadi__ = 0;
}


// CADI Port implementations
eslapi::CADIReturn_t Component__VE_SysRegs::cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params)
{
    // check arguments
    if(actualNumOfParams == 0)
        return eslapi::CADI_STATUS_IllegalArgument;
    *actualNumOfParams = 0;
    if(params == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    // collect parameters
    size_t i = 0;
    for (; (i < desiredNumOfParams) && ((startIndex + i) < parameterInfos__.size()); ++i)
    {
        params[i] = parameterInfos__[startIndex + i];
    }
    *actualNumOfParams = (MxU32)i;

    return eslapi::CADI_STATUS_OK;
}

eslapi::CADIReturn_t Component__VE_SysRegs::cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param)
{
    if(param == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        if (!strcmp(parameterInfos__[i].name, parameterName.c_str()))
        {
            *param = parameterInfos__[i];

            return eslapi::CADI_STATUS_OK;
        }
    }

    return eslapi::CADI_STATUS_GeneralError;
}


bool Component__VE_SysRegs::ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy, const char *param_name, int64_t intVal, const char *strVal)
{
    if (!proxy)
        return false;

    // we need the parameter's CADI id in order to create an eslapi::CADIParameterValue_t structure
    // therefore, we first retrieve its eslapi::CADIParameterInfo_t meta-data
    eslapi::CADIParameterInfo_t paramInfo;
    if (proxy->CADIGetParameterInfo(param_name, &paramInfo) != eslapi::CADI_STATUS_OK)
        return false;

    eslapi::CADIParameterValue_t paramVal(paramInfo.id, paramInfo.dataType, intVal, strVal);
    eslapi::CADIFactoryErrorMessage_t error;
    if (proxy->CADISetParameters(1, &paramVal, &error) != eslapi::CADI_STATUS_OK)
        return false;

    return true;
}


sg::accessfunc::AccessFuncResult Component__VE_SysRegs::parameter_read_func(uint32_t id, int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_sys_proc_id0: *data = sys_proc_id0; break;
	case PARAMETER_ID_sys_proc_id1: *data = sys_proc_id1; break;
	case PARAMETER_ID_user_switches_value: *data = user_switches_value; break;
	case PARAMETER_ID_exit_on_shutdown: *data = exit_on_shutdown; break;
	case PARAMETER_ID_tilePresent: *data = tilePresent; break;

        default:
            printf("error: Component__VE_SysRegs::parameter_read_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VE_SysRegs::parameter_read_string_func(uint32_t id, std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__VE_SysRegs::parameter_read_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VE_SysRegs::parameter_write_func(uint32_t id, const int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_sys_proc_id0:
		{
			*(const_cast<uint32_t*>(&sys_proc_id0)) = *data;
		}
		break;
	case PARAMETER_ID_sys_proc_id1:
		{
			*(const_cast<uint32_t*>(&sys_proc_id1)) = *data;
		}
		break;
	case PARAMETER_ID_user_switches_value:
		{
			*(const_cast<uint32_t*>(&user_switches_value)) = *data;
		}
		break;
	case PARAMETER_ID_exit_on_shutdown:
		{
			*(const_cast<bool*>(&exit_on_shutdown)) = !!*data;
		}
		break;
	case PARAMETER_ID_tilePresent:
		{
			*(const_cast<bool*>(&tilePresent)) = !!*data;
		}
		break;

        default:
            printf("error: Component__VE_SysRegs::parameter_write_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VE_SysRegs::parameter_write_string_func(uint32_t id, const std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__VE_SysRegs::parameter_write_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

void Component__VE_SysRegs::cadiPort__LoadApplicationFile(const std::string& filename)
{
    loadApplicationFile(filename);
    applications2params[filename] = "";
}

void Component__VE_SysRegs::cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_)
{
    applications2params_ = applications2params;
}

eslapi::CADIReturn_t Component__VE_SysRegs::cadiPort__GetProperty(const std::string& propertyName, std::string &value)
{
    if(properties__.find(propertyName) != properties__.end())
    {
        value = properties__[propertyName];
        return eslapi::CADI_STATUS_OK;
    }
    else
    {
        value = "";
        return eslapi::CADI_STATUS_GeneralError;
    }
}

// functions to stop and lock the simulator
// we only expose the simHalt() function in the documentation for the moment

void Component__VE_SysRegs::simHalt()
{
    cadi__->StopSimulation();
}


// start simulation from the inside
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
void Component__VE_SysRegs::simRun()
{
    cadi__->CADIExecContinue();
}


// return true if simulation is running
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
bool Component__VE_SysRegs::simIsRunning()
{
    uint32_t mode = eslapi::CADI_EXECMODE_Stop;
    cadi__->CADIExecGetMode(&mode);
    return mode != eslapi::CADI_EXECMODE_Stop;
}


void Component__VE_SysRegs::simShutdown()
{
    cadiPort__.simShutdown();
}

void Component__VE_SysRegs::simReset(uint32_t level)
{
    cadi__->CADIExecReset(level);
}

uint32_t Component__VE_SysRegs::paramNameToParamAccessFuncID(const std::string &name)
{
    uint32_t id = 0;
    if (name == "") id = 0xffffffff;
    if (name == "sys_proc_id0") id = PARAMETER_ID_sys_proc_id0;
    if (name == "sys_proc_id1") id = PARAMETER_ID_sys_proc_id1;
    if (name == "user_switches_value") id = PARAMETER_ID_user_switches_value;
    if (name == "exit_on_shutdown") id = PARAMETER_ID_exit_on_shutdown;
    if (name == "tilePresent") id = PARAMETER_ID_tilePresent;

    return id;
}

void Component__VE_SysRegs::reset_resources__()
{
    // resource initialization code
	SYS_ID = 0; // reset register
	SYS_SW = 0; // reset register
	SYS_LED = 0; // reset register
	SYS_100HZ = 0; // reset register
	SYS_FLAGS = 0; // reset register
	SYS_FLAGSCLR = 0; // reset register
	SYS_NVFLAGS = 0; // reset register
	SYS_NVFLAGSCLR = 0; // reset register
	SYS_MCI = 0; // reset register
	SYS_FLASH = 0; // reset register
	SYS_CFGSW = 0; // reset register
	SYS_24MHZ = 0; // reset register
	SYS_MISC = 0; // reset register
	SYS_DMA = 0; // reset register
	SYS_PROCID0 = 0; // reset register
	SYS_PROCID1 = 0; // reset register
	SYS_CFGDATA = 0; // reset register
	SYS_CFGCTRL = 0; // reset register
	SYS_CFGSTAT = 0; // reset register

}


} // FVP_VE_Cortex_A15x1_NMS
#line 823 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::init()
{
 action = new ProcessMessage(getSimulationContext());
 {if(!controlPort_messagebox__.init.empty()) controlPort_messagebox__.init();};
 
 
 if (mount != "")
 action->vfs.addMount("A", mount.c_str());
 
 background = true;
 
 action->setCompletionPort(complete.getAbstractInterface());
 
}
}

#line 837 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::terminate()
{
 {if(!controlPort_messagebox__.terminate.empty()) controlPort_messagebox__.terminate();};
 delete action;
 
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::interconnect()
{{if(!controlPort_messagebox__.interconnect.empty()) controlPort_messagebox__.interconnect();};
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::disconnect()
{{if(!controlPort_messagebox__.disconnect.empty()) controlPort_messagebox__.disconnect();};
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::update()
{{if(!controlPort_messagebox__.update.empty()) controlPort_messagebox__.update();};
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::communicate()
{{if(!controlPort_messagebox__.communicate.empty()) controlPort_messagebox__.communicate();};
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::traceEndOfCycle()
{{if(!controlPort_messagebox__.traceEndOfCycle.empty()) controlPort_messagebox__.traceEndOfCycle();};
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::loadApplicationFile(const std::string& filename)
{{if(!controlPort_messagebox__.loadApplicationFile.empty()) controlPort_messagebox__.loadApplicationFile(filename);};
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::reset(int level)
{{if(!controlPort_messagebox__.reset.empty()) controlPort_messagebox__.reset(level);};
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::reset(int level, int /*argc*/, char** /*argv*/)
{
	reset(level);

}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VFS2::save(MxODataStream& os)
{{if(!controlPort_messagebox__.save.empty()) controlPort_messagebox__.save(os);};return true;
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VFS2::restore(MxIDataStream& is)
{{if(!controlPort_messagebox__.restore.empty()) controlPort_messagebox__.restore(is);};return true;
}
}

#line 30 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::step()
{{if(!controlPort_messagebox__.step.empty()) controlPort_messagebox__.step();};
}
}

#line 784 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { int32_t 
Component__VFS2::abstract_port__message__handle_message(const void* data, uint32_t len)
{
 void* data_out;
 uint32_t len_out = 8192;
 
 message.begin_msg(&data_out, len_out);

 if (background)
 {
 
 
 action->async_message(data, len, data_out, &len_out);
 }
 else
 {
 
 action->sync_message(data, len, data_out, &len_out);
 
 
 complete.setValue(len_out);
 }
 
 
 return 0;
 
}
}

#line 814 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VFS2::abstract_port__complete__setValue(uint32_t reply_len)
{
 
 message.end_msg(reply_len);
 
}
}

#line 4029 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// ------------------------------------------------------------------------------
// implementation of class Component__VFS2
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

Component__VFS2::Component__VFS2(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params):
    SystemGenComponent(instName, simulationContext, params)

	,mount(GetParameterValue(params, "mount", ""))


	,cadiParameterProxy_messagebox_of_MessageBox_to_VFS2__(0)

{
    // initialize properties__
	properties__["component_name"] = "";
	properties__["component_type"] = "Other";
	properties__["debugger_name"] = "";
	properties__["debugger_start_command"] = "";
	properties__["default_view"] = "auto";
	properties__["description"] = "Virtual Filesystem Device";
	properties__["documentation_file"] = "";
	properties__["dso_safe"] = "1";
	properties__["executes_software"] = "0";
	properties__["expose_extern_sub_component_cadi"] = "1";
	properties__["factory_namespace"] = "";
	properties__["has_cadi"] = "1";
	properties__["has_implicit_clk_in"] = "1";
	properties__["hidden"] = "0";
	properties__["icon_file"] = "";
	properties__["ip_provider"] = "";
	properties__["is_single_stepped"] = "0";
	properties__["license_feature"] = "";
	properties__["loadfile_extension"] = "";
	properties__["save_restore"] = "0";
	properties__["small_icon_file"] = "";
	properties__["variant"] = "";
	properties__["version"] = "8.1.37";

    // initialize parameter info
    {
        sg::ComponentFactory *factory = VFS2_GetFactory();

        sg::TargetInfo *targetInfo = factory->getTargetInfo(""); // empty string means 'this' component

        if(targetInfo) // if we have no target info we also have no parameters towards CADI interfaces
        {
            // get parameter infos
            for(unsigned int i = 0; i < targetInfo->parameter_count; i++)
            {
                parameterId2parameterName__[targetInfo->parameter_info[i].id] = targetInfo->parameter_info[i].name;
                parameterInfos__.push_back((targetInfo->parameter_info)[i]);
            }
        }

        factory->dereference();
    }

    // create subcomponents
	{
		sg::ComponentFactory *MessageBox_factory = MessageBox_GetFactory();
		{
			sg::Params params_messagebox__ = params.getParamsFor("messagebox");
			params_messagebox__["id"] = MxU64CONST(0x0000000056465332);
			messagebox = dynamic_cast<Component__MessageBox*>(MessageBox_factory->instantiate("messagebox", simulationContext, params_messagebox__));
			assert(messagebox);
			add(messagebox);
		}
		MessageBox_factory->dereference();
	}


    // bind local behaviors to this->control_port
    bind_method(control_port, configure, &Component__VFS2::control_port__configure, this);
    bind_method(control_port, init, &Component__VFS2::init, this);
    bind_method(control_port, interconnect, &Component__VFS2::interconnect, this);
//  bind_method(control_port, postConnect, &Component__VFS2::postConnect, this);
    bind_method(control_port, reset, &Component__VFS2::control_port__reset, this);
    bind_method(control_port, loadApplicationFile, &Component__VFS2::loadApplicationFile, this);
    bind_method(control_port, disconnect, &Component__VFS2::disconnect, this);
    bind_method(control_port, terminate, &Component__VFS2::control_port__terminate, this);
    bind_method(control_port, populateCADIMap, &Component__VFS2::control_port__populateCADIMap, this);
//  bind_method(control_port, refresh, &Component__VFS2::refresh, this);
    bind_method(control_port, step, &Component__VFS2::step, this);
    bind_method(control_port, update, &Component__VFS2::update, this);
    bind_method(control_port, communicate, &Component__VFS2::communicate, this);
    bind_method(control_port, getProperty, &Component__VFS2::control_port__getProperty, this);
    bind_method(control_port, traceEndOfCycle, &Component__VFS2::traceEndOfCycle, this);
    bind_method(control_port, bypass, &Component__VFS2::control_port__bypass, this);
    bind_method(control_port, run, &Component__VFS2::control_port__run, this);
    bind_method(control_port, stop, &Component__VFS2::control_port__stop, this);
    bind_method(control_port, idle, &Component__VFS2::control_port__idle, this);
    bind_method(control_port, quit, &Component__VFS2::control_port__quit, this);
    bind_method(control_port, setSimulationEngine, &Component__VFS2::control_port__setSimulationEngine, this);
    bind_method(control_port, message, &Component__VFS2::control_port__message, this);
    bind_method(control_port, callSimEngine, &Component__VFS2::control_port__callSimEngine, this);

    // avoid the automatic calling of the methods through the framework
    control_port.configure.setLocalOnly(true);
    control_port.init.setLocalOnly(true);
    control_port.interconnect.setLocalOnly(true);
//  control_port.postConnect.setLocalOnly(true);
    control_port.reset.setLocalOnly(true);
    control_port.loadApplicationFile.setLocalOnly(true);
    control_port.disconnect.setLocalOnly(true);
    control_port.terminate.setLocalOnly(true);
    control_port.save.setLocalOnly(true);
    control_port.restore.setLocalOnly(true);
    control_port.populateCADIMap.setLocalOnly(true);
//  control_port.refresh.setLocalOnly(true);
    control_port.step.setLocalOnly(true);
    control_port.update.setLocalOnly(true);
    control_port.communicate.setLocalOnly(true);
    control_port.getProperty.setLocalOnly(true);
    control_port.traceEndOfCycle.setLocalOnly(true);
//  control_port.bypass.setLocalOnly(true);
//  control_port.run.setLocalOnly(true);
//  control_port.stop.setLocalOnly(true);
//  control_port.idle.setLocalOnly(true); // broadcast ports don't have setLocalOnly
//  control_port.quit.setLocalOnly(true);
//  control_port.setSimulationEngine.setLocalOnly(true);

    // bind cadiPort behaviors
    bind_method(cadiPort__, GetParameters, &Component__VFS2::cadiPort__GetParameters, this);
    bind_method(cadiPort__, GetParameterInfo, &Component__VFS2::cadiPort__GetParameterInfo, this);
    bind_method(cadiPort__, GetProperty, &Component__VFS2::cadiPort__GetProperty, this);
    bind_method(cadiPort__, LoadApplicationFile, &Component__VFS2::cadiPort__LoadApplicationFile, this);
    bind_method(cadiPort__, GetApplicationsAndCommandLineParams, &Component__VFS2::cadiPort__GetApplicationsAndCommandLineParams, this);

    // connect control ports for subcomponents to subcomponents
	controlPort_messagebox__.connectTo(messagebox->findPort("$control"));



    // resource initialization code
    reset_resources__();

    // bind behaviors to abstract ports
	bind_method(message, handle_message, &Component__VFS2::abstract_port__message__handle_message, this);
	bind_method(complete, setValue, &Component__VFS2::abstract_port__complete__setValue, this);


    // add abstract ports
	publishSlavePort("pvbus_s", pvbus_s);
	pvbus_s.SetName__("pvbus_s");
	publishMasterPort("intr", intr);
	intr.SetName__("intr");
	message.SetName__("message");
	complete.SetName__("complete");


    // wire up static connection map
	pvbus_s.connectTo(messagebox->findPort("pvbus_s"));
	message.connectTo(messagebox->findPort("message"));
	messagebox->findPort("intr").connectTo(intr);


    // init profiling

    // init resources


    // run the parameter write access functions for all of the component's parameters
    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        std::string paramName = parameterInfos__[i].name;

        switch (parameterInfos__[i].dataType)
        {
        case eslapi::CADI_PARAM_STRING:
            {
                std::string data = GetParameterValue(params, paramName, parameterInfos__[i].defaultString);
                parameter_write_string_func(paramNameToParamAccessFuncID(paramName), data);
            }
            break;
        case eslapi::CADI_PARAM_BOOL:
        case eslapi::CADI_PARAM_INT:
            {
                int64_t data = GetParameterValue(params, paramName, parameterInfos__[i].defaultValue, parameterInfos__[i].minValue, parameterInfos__[i].maxValue);
                parameter_write_func(paramNameToParamAccessFuncID(paramName), &data);
            }
            break;
        default:
            break;
        }
    }
}


Component__VFS2::~Component__VFS2()
{
}

void Component__VFS2::control_port__configure(const sg::Params& params)
{
	if(controlPort_messagebox__.configure.implemented()) controlPort_messagebox__.configure(params.getParamsFor("messagebox"));


    assert(simulationContext__->getSimulationEngine());
    cadi__ = new Component__VFS2_CADI(this, simulationContext__->getSimulationEngine());

    // forward certain calls from CADI interface to this component
    cadi__->GetCADIPort().connectTo(cadiPort__);

    

    std::map< std::string, eslapi::CAInterface* > tempMap;
    control_port__populateCADIMap(tempMap, ""); // precompute mxdi map

	cadi__->EnableSubComponentCADIImport();


}

void Component__VFS2::control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* >&output_map, std::string const & base_prefix)
{
    if (componentName2CADI__.empty())
    {
        componentName2CADI__[getName()] = static_cast<eslapi::CADI*>(cadi__);
        std::string prefix = getName() + ".";

		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_messagebox__.populateCADIMap.implemented())
			{
				controlPort_messagebox__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
			eslapi::CADI *cadi = obtainCADI__("messagebox", compMap);
			if (cadi != NULL)
			{
				cadiParameterProxy_messagebox_of_MessageBox_to_VFS2__ = new CADIParameterProxy(cadi, &parameterFilter_messagebox_of_MessageBox_to_VFS2__);
			}
		}

    }
    // Copy the local map into the given map with the requested prefix.
    for (std::map<std::string,eslapi::CAInterface*>::iterator it = componentName2CADI__.begin(); it != componentName2CADI__.end(); ++it)
    {
        output_map.insert(std::make_pair(base_prefix + it->first, it->second));
    }
}

eslapi::CADI* Component__VFS2::obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const
{
    std::map< std::string, eslapi::CAInterface* >::const_iterator it = componentName2CADI.find(subcomp);
    if (it != componentName2CADI.end())
    {
        eslapi::CAInterface *cai = it->second;
        if (cai != NULL)
        {
            cai = cai->ObtainInterface(eslapi::CADI::IFNAME(), 0, 0);
            if (cai != NULL)
            {
                return static_cast<eslapi::CADI*>(cai);
            }
        }
    }
    return NULL;
}

void Component__VFS2::insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface* > &componentName2CADI)
{
    for (std::map<std::string, eslapi::CAInterface*>::iterator it = componentName2CADI.begin(); it != componentName2CADI.end(); it++)
    {
        // put prefix in front of all entries
        componentName2CADI__[prefix + it->first] = it->second;
    }
}


std::string Component__VFS2::control_port__getProperty(const std::string& propname)
{
    if(properties__.find(propname) != properties__.end())
    {
        return properties__[propname];
    }
    else
        return ""; // unknown property
}


std::string Component__VFS2::control_port__bypass(const std::string&)
{
    return "";
}


void Component__VFS2::control_port__run()
{
}


void Component__VFS2::control_port__stop()
{
}


void Component__VFS2::control_port__idle()
{
}


void Component__VFS2::control_port__quit()
{
}


void Component__VFS2::control_port__setSimulationEngine(SimulationEngine*)
{
}


void Component__VFS2::control_port__message(const std::string &msg, sg::message::MessageType msgType)
{
}


std::string Component__VFS2::control_port__callSimEngine(const std::string &)
{
    return "";
}


void Component__VFS2::control_port__reset(int level)
{
    // restore the resources' reset values before executing 'reset'
    reset_resources__();
    reset(level);
}


void Component__VFS2::control_port__terminate()
{
    // the CADI was created before 'init', therefore we free it after 'terminate'
    terminate();
    freeCADIResources__();
}


void Component__VFS2::freeCADIResources__()
{
    // free CADI parameter proxies
	delete cadiParameterProxy_messagebox_of_MessageBox_to_VFS2__;
	cadiParameterProxy_messagebox_of_MessageBox_to_VFS2__ = 0;


    // free CADI interface
    delete cadi__;
    cadi__ = 0;
}


// CADI Port implementations
eslapi::CADIReturn_t Component__VFS2::cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params)
{
    // check arguments
    if(actualNumOfParams == 0)
        return eslapi::CADI_STATUS_IllegalArgument;
    *actualNumOfParams = 0;
    if(params == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    // collect parameters
    size_t i = 0;
    for (; (i < desiredNumOfParams) && ((startIndex + i) < parameterInfos__.size()); ++i)
    {
        params[i] = parameterInfos__[startIndex + i];
    }
    *actualNumOfParams = (MxU32)i;

    return eslapi::CADI_STATUS_OK;
}

eslapi::CADIReturn_t Component__VFS2::cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param)
{
    if(param == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        if (!strcmp(parameterInfos__[i].name, parameterName.c_str()))
        {
            *param = parameterInfos__[i];

            return eslapi::CADI_STATUS_OK;
        }
    }

    return eslapi::CADI_STATUS_GeneralError;
}


bool Component__VFS2::ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy, const char *param_name, int64_t intVal, const char *strVal)
{
    if (!proxy)
        return false;

    // we need the parameter's CADI id in order to create an eslapi::CADIParameterValue_t structure
    // therefore, we first retrieve its eslapi::CADIParameterInfo_t meta-data
    eslapi::CADIParameterInfo_t paramInfo;
    if (proxy->CADIGetParameterInfo(param_name, &paramInfo) != eslapi::CADI_STATUS_OK)
        return false;

    eslapi::CADIParameterValue_t paramVal(paramInfo.id, paramInfo.dataType, intVal, strVal);
    eslapi::CADIFactoryErrorMessage_t error;
    if (proxy->CADISetParameters(1, &paramVal, &error) != eslapi::CADI_STATUS_OK)
        return false;

    return true;
}


sg::accessfunc::AccessFuncResult Component__VFS2::parameter_read_func(uint32_t id, int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {

        default:
            printf("error: Component__VFS2::parameter_read_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VFS2::parameter_read_string_func(uint32_t id, std::string &data)
{
    switch (id)
    {
	case PARAMETER_ID_mount:  data = mount; break;

        default:
            printf("error: Component__VFS2::parameter_read_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VFS2::parameter_write_func(uint32_t id, const int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {

        default:
            printf("error: Component__VFS2::parameter_write_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VFS2::parameter_write_string_func(uint32_t id, const std::string &data)
{
    switch (id)
    {
	case PARAMETER_ID_mount:
		{
			*(const_cast<std::string*>(&mount)) = data;
		}
		break;

        default:
            printf("error: Component__VFS2::parameter_write_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

void Component__VFS2::cadiPort__LoadApplicationFile(const std::string& filename)
{
    loadApplicationFile(filename);
    applications2params[filename] = "";
}

void Component__VFS2::cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_)
{
    applications2params_ = applications2params;
}

eslapi::CADIReturn_t Component__VFS2::cadiPort__GetProperty(const std::string& propertyName, std::string &value)
{
    if(properties__.find(propertyName) != properties__.end())
    {
        value = properties__[propertyName];
        return eslapi::CADI_STATUS_OK;
    }
    else
    {
        value = "";
        return eslapi::CADI_STATUS_GeneralError;
    }
}

// functions to stop and lock the simulator
// we only expose the simHalt() function in the documentation for the moment

void Component__VFS2::simHalt()
{
    cadi__->StopSimulation();
}


// start simulation from the inside
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
void Component__VFS2::simRun()
{
    cadi__->CADIExecContinue();
}


// return true if simulation is running
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
bool Component__VFS2::simIsRunning()
{
    uint32_t mode = eslapi::CADI_EXECMODE_Stop;
    cadi__->CADIExecGetMode(&mode);
    return mode != eslapi::CADI_EXECMODE_Stop;
}


void Component__VFS2::simShutdown()
{
    cadiPort__.simShutdown();
}

void Component__VFS2::simReset(uint32_t level)
{
    cadi__->CADIExecReset(level);
}

uint32_t Component__VFS2::paramNameToParamAccessFuncID(const std::string &name)
{
    uint32_t id = 0;
    if (name == "") id = 0xffffffff;
    if (name == "mount") id = PARAMETER_ID_mount;

    return id;
}

void Component__VFS2::reset_resources__()
{
    // resource initialization code

}


} // FVP_VE_Cortex_A15x1_NMS
#line 160 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::init()
{
 {if(!controlPort_busslave__.init.empty()) controlPort_busslave__.init();};
 control = 0; 
 status = MBOX_STATUS_RXEMPTY;
 start = 0;
 end = 0;
 irqmask = 0;
 irq = false;
 
 
 
 __MessageBox_internal_1.setAccess(MBOX_REGISTER_BASE, MBOX_REGISTER_BASE+MBOX_REGISTER_SIZE, pv::ACCESSTYPE_RW, pv::ACCESSMODE_DEVICE);
 __MessageBox_internal_1.setAccess(MBOX_BUFFER_BASE, MBOX_BUFFER_BASE+MBOX_BUFFER_SIZE, pv::ACCESSTYPE_RW, pv::ACCESSMODE_MEMORY);
 
 
 
 __MessageBox_internal_1.provideReadWriteStorage(MBOX_BUFFER_BASE, MBOX_BUFFER_BASE+MBOX_BUFFER_SIZE, buffer);
 
}
}

#line 184 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::set_control(uint32_t control)
{
 
 switch(control)
 {
 case MBOX_CONTROL_START:
 
 
 
 
 
 start = 0;
 end = 0;
 status &=~ MBOX_STATUS_TXFULL;
 status |= MBOX_STATUS_RXEMPTY;
 
 update_interrupts();
 break;
 
 case MBOX_CONTROL_END:
 
 
 
 
 
 
 if (end < start)
 end = start;
 
 if (!0) ; else printf("incoming message at 0x%x, len %d\n", start, end-start); 
 
 if (message.handle_message.implemented())
 message.handle_message(buffer+start, end-start);
 
 break;
 
 case MBOX_CONTROL_CANCEL:
 
 
 
 break;
 
 default:
 
 
 
 break;
 }
 
}
}

#line 236 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__MessageBox::read_data()
{
 
 
 if (status & MBOX_STATUS_RXREADY)
 {
 status &= ~MBOX_STATUS_RXREADY;
 update_interrupts();
 }
 
 
 
 uint32_t data = 0;
 if (start < end)
 {
 
 union { uint8_t *p; uint32_t *u32; } cast;
 cast.p = buffer + start;
 data = *(cast.u32);

 start += 4;

 if (start == end)
 {
 status |= MBOX_STATUS_RXEMPTY;
 update_interrupts();
 }
 }

 return data; 
 
}
}

#line 270 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::write_data(uint32_t data)
{
 

 if (end < MBOX_BUFFER_SIZE)
 {
 
 union { uint8_t *p; uint32_t *u32; } cast;
 cast.p = buffer + end;
 *(cast.u32) = data;

 end += 4;
 if (end == MBOX_BUFFER_SIZE)
 {
 status |= MBOX_STATUS_TXFULL;
 update_interrupts();
 }
 }
 
}
}

#line 292 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__MessageBox::get_start()
{
 
 
 
 
 
 
 if (status & MBOX_STATUS_RXREADY)
 {
 status &= ~MBOX_STATUS_RXREADY;
 update_interrupts();
 }
 
 return start;
 
}
}

#line 311 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::set_start(uint32_t data)
{
 
 
 
 if (data >= MBOX_BUFFER_SIZE)
 data = 0;
 
 start = data;
 
 if (start >= end)
 {
 status |= MBOX_STATUS_TXFULL;
 update_interrupts();
 }
 
}
}

#line 330 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__MessageBox::get_end()
{
 
 
 
 
 
 
 if (status & MBOX_STATUS_RXREADY)
 {
 status &= ~MBOX_STATUS_RXREADY;
 update_interrupts();
 }
 
 return end;
 
}
}

#line 349 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::set_end(uint32_t data)
{ 
 if (data >= MBOX_BUFFER_SIZE)
 data = 0;
 
 end = data;
 
 if (start >= end)
 {
 status |= MBOX_STATUS_TXFULL;
 update_interrupts();
 }
 
}
}

#line 365 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::update_interrupts()
{
 bool new_irq = (status & irqmask) != 0;
 
 if (irq != new_irq)
 {
 irq = new_irq;
 if (intr.setValue.implemented())
 intr.setValue(irq ? sg::Signal::Set : sg::Signal::Clear);
 }
 
}
}

#line 379 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__MessageBox::registerRead(uint32_t device_addr)
{
 uint32_t data = 0;
 switch (device_addr)
 {
 case MBOX_REG_ID:
 data = id;
 
 if (!0) ; else printf("MESSAGEBOX_ID -> %x\n", data);
 break;
 
 case MBOX_REG_DATA:
 data = read_data();
 
 if (!0) ; else printf("MESSAGEBOX_DATA -> %x\n", data);
 break;
 
 case MBOX_REG_CONTROL:
 data = control;
 
 if (!0) ; else printf("MESSAGEBOX_CONTROL -> %x\n", data);
 break;
 
 case MBOX_REG_STATUS:
 data = status;
 
 if (!0) ; else printf("MESSAGEBOX_STATUS -> %x\n", data);
 break;
 
 case MBOX_REG_START: 
 data = get_start();
 
 if (!0) ; else printf("MESSAGEBOX_START -> %x\n", data);
 break;
 
 case MBOX_REG_END: 
 data = get_end();
 
 if (!0) ; else printf("MESSAGEBOX_END -> %x\n", data);
 break;
 
 case MBOX_REG_IRQMASK:
 data = irqmask;
 
 if (!0) ; else printf("MESSAGEBOX_IRQMASK -> %x\n", data);
 
 default:
 
 if (!0) ; else printf("MESSAGEBOX unimplemented register @ 0x%x\n", device_addr);
 break;
 }
 return data;
 
}
}

#line 433 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::registerWrite(uint32_t device_addr, uint32_t data)
{
 switch (device_addr)
 {
 case MBOX_REG_ID:
 if (!0) ; else printf("MESSAGEBOX_ID (read only)<- %x\n", data);
 return;
 
 case MBOX_REG_DATA:
 if (!0) ; else printf("MESSAGEBOX_DATA <- %x\n", data);
 
 write_data(data);
 
 return;
 
 case MBOX_REG_CONTROL:
 if (!0) ; else printf("MESSAGEBOX_CONTROL <- %x\n", data);
 
 set_control(data);
 
 return;
 
 case MBOX_REG_STATUS:
 if (!0) ; else printf("MESSAGEBOX_STATUS (read only)<- %x\n", data);
 return;
 
 case MBOX_REG_START:
 if (!0) ; else printf("MESSAGEBOX_START <- %x\n", data);
 
 set_start(data);
 
 return;
 
 case MBOX_REG_END:
 if (!0) ; else printf("MESSAGEBOX_END <- %x\n", data);
 
 set_end(data);
 
 return;
 
 case MBOX_REG_IRQMASK:
 if (!0) ; else printf("MESSAGEBOX_IRQMASK <- %x\n", data);
 
 irqmask = data;
 
 update_interrupts();
 
 return;
 
 default:
 if (!0) ; else printf("MESSAGEBOX unimplemented register @ 0x%x <- %x\n", device_addr, data);
 
 return;
 }
 
}
}

#line 492 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { AccessFuncResult 
Component__MessageBox::debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects)
{
 *datap = registerRead(reg_id);

 return eslapi::CADI_STATUS_OK;
 
}
}

#line 499 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { AccessFuncResult 
Component__MessageBox::debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects)
{
 registerWrite(reg_id, (uint32_t)*datap);

 return eslapi::CADI_STATUS_OK;
 
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::interconnect()
{{if(!controlPort_busslave__.interconnect.empty()) controlPort_busslave__.interconnect();};
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::disconnect()
{{if(!controlPort_busslave__.disconnect.empty()) controlPort_busslave__.disconnect();};
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::update()
{{if(!controlPort_busslave__.update.empty()) controlPort_busslave__.update();};
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::communicate()
{{if(!controlPort_busslave__.communicate.empty()) controlPort_busslave__.communicate();};
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::traceEndOfCycle()
{{if(!controlPort_busslave__.traceEndOfCycle.empty()) controlPort_busslave__.traceEndOfCycle();};
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::loadApplicationFile(const std::string& filename)
{{if(!controlPort_busslave__.loadApplicationFile.empty()) controlPort_busslave__.loadApplicationFile(filename);};
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::terminate()
{{if(!controlPort_busslave__.terminate.empty()) controlPort_busslave__.terminate();};
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::reset(int level)
{{if(!controlPort_busslave__.reset.empty()) controlPort_busslave__.reset(level);};
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::reset(int level, int /*argc*/, char** /*argv*/)
{
	reset(level);

}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__MessageBox::save(MxODataStream& os)
{{if(!controlPort_busslave__.save.empty()) controlPort_busslave__.save(os);};return true;
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__MessageBox::restore(MxIDataStream& is)
{{if(!controlPort_busslave__.restore.empty()) controlPort_busslave__.restore(is);};return true;
}
}

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::step()
{{if(!controlPort_busslave__.step.empty()) controlPort_busslave__.step();};
}
}

#line 85 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::abstract_port__message__begin_msg(void** bufferp, uint32_t reserve_len)
{
 assert(reserve_len <= MBOX_BUFFER_SIZE);
 
 *bufferp = buffer;
 
 start = 0;
 end = reserve_len; 
 
 update_interrupts();
 
}
}

#line 99 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::abstract_port__message__cancel_msg()
{
 start = 0;
 end = 0;
 
 status |= MBOX_STATUS_RXEMPTY;
 update_interrupts();
 
}
}

#line 110 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__MessageBox::abstract_port__message__end_msg(uint32_t len)
{
 
 end = start + len;
 
 if (end > MBOX_BUFFER_SIZE)
 end = 0;
 
 if (!0) ; else printf("outgoing message at 0x%x, len %d\n", start, end-start);
 
 if (end > start)
 status &= ~MBOX_STATUS_RXEMPTY; 
 
 
 
 status |= MBOX_STATUS_RXREADY;
 update_interrupts();
 
}
}

#line 136 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__MessageBox::abstract_port__device__read(pv::ReadTransaction tx)
{
 if (tx.getAccessWidth() != pv::ACCESS_32_BITS || !tx.isAligned()) return tx.generateAbort();
 return tx.setReturnData32(registerRead(tx.getAddress()));
 
}
}

#line 142 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__MessageBox::abstract_port__device__write(pv::WriteTransaction tx)
{
 if (tx.getAccessWidth() != pv::ACCESS_32_BITS || !tx.isAligned()) return tx.generateAbort();
 registerWrite(tx.getAddress(),tx.getData32());
 return tx.writeComplete();
 
}
}

#line 149 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__MessageBox::abstract_port__device__debugRead(pv::ReadTransaction tx)
{
 return device.read(tx);
 
}
}

#line 154 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { pv::Tx_Result 
Component__MessageBox::abstract_port__device__debugWrite(pv::WriteTransaction tx)
{
 return device.write(tx);
 
}
}

#line 5142 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// ------------------------------------------------------------------------------
// implementation of class Component__MessageBox
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

Component__MessageBox::Component__MessageBox(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params):
    SystemGenComponent(instName, simulationContext, params)

	,id(GetParameterValue(params, "id", MxS64CONST(0x1400400), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))


	,cadiParameterProxy_busslave_of_PVBusSlave_to_MessageBox__(0)

{
    // initialize properties__
	properties__["component_name"] = "";
	properties__["component_type"] = "Other";
	properties__["debugger_name"] = "";
	properties__["debugger_start_command"] = "";
	properties__["default_view"] = "auto";
	properties__["description"] = "Generic MessageBox";
	properties__["documentation_file"] = "";
	properties__["dso_safe"] = "1";
	properties__["executes_software"] = "0";
	properties__["expose_extern_sub_component_cadi"] = "1";
	properties__["factory_namespace"] = "";
	properties__["has_cadi"] = "1";
	properties__["has_implicit_clk_in"] = "1";
	properties__["hidden"] = "0";
	properties__["icon_file"] = "";
	properties__["ip_provider"] = "";
	properties__["is_single_stepped"] = "0";
	properties__["license_feature"] = "";
	properties__["loadfile_extension"] = "";
	properties__["save_restore"] = "0";
	properties__["small_icon_file"] = "";
	properties__["variant"] = "";
	properties__["version"] = "8.1.37";

    // initialize parameter info
    {
        sg::ComponentFactory *factory = MessageBox_GetFactory();

        sg::TargetInfo *targetInfo = factory->getTargetInfo(""); // empty string means 'this' component

        if(targetInfo) // if we have no target info we also have no parameters towards CADI interfaces
        {
            // get parameter infos
            for(unsigned int i = 0; i < targetInfo->parameter_count; i++)
            {
                parameterId2parameterName__[targetInfo->parameter_info[i].id] = targetInfo->parameter_info[i].name;
                parameterInfos__.push_back((targetInfo->parameter_info)[i]);
            }
        }

        factory->dereference();
    }

    // create subcomponents
	{
		sg::ComponentFactory *PVBusSlave_factory = PVBusSlave_GetFactory();
		{
			sg::Params params_busslave__ = params.getParamsFor("busslave");
			params_busslave__["size"] = MxU64CONST(0x0000000000020000);
			add(busslave = PVBusSlave_factory->instantiate("busslave", simulationContext, params_busslave__));
		}
		PVBusSlave_factory->dereference();
	}


    // bind local behaviors to this->control_port
    bind_method(control_port, configure, &Component__MessageBox::control_port__configure, this);
    bind_method(control_port, init, &Component__MessageBox::init, this);
    bind_method(control_port, interconnect, &Component__MessageBox::interconnect, this);
//  bind_method(control_port, postConnect, &Component__MessageBox::postConnect, this);
    bind_method(control_port, reset, &Component__MessageBox::control_port__reset, this);
    bind_method(control_port, loadApplicationFile, &Component__MessageBox::loadApplicationFile, this);
    bind_method(control_port, disconnect, &Component__MessageBox::disconnect, this);
    bind_method(control_port, terminate, &Component__MessageBox::control_port__terminate, this);
    bind_method(control_port, populateCADIMap, &Component__MessageBox::control_port__populateCADIMap, this);
//  bind_method(control_port, refresh, &Component__MessageBox::refresh, this);
    bind_method(control_port, step, &Component__MessageBox::step, this);
    bind_method(control_port, update, &Component__MessageBox::update, this);
    bind_method(control_port, communicate, &Component__MessageBox::communicate, this);
    bind_method(control_port, getProperty, &Component__MessageBox::control_port__getProperty, this);
    bind_method(control_port, traceEndOfCycle, &Component__MessageBox::traceEndOfCycle, this);
    bind_method(control_port, bypass, &Component__MessageBox::control_port__bypass, this);
    bind_method(control_port, run, &Component__MessageBox::control_port__run, this);
    bind_method(control_port, stop, &Component__MessageBox::control_port__stop, this);
    bind_method(control_port, idle, &Component__MessageBox::control_port__idle, this);
    bind_method(control_port, quit, &Component__MessageBox::control_port__quit, this);
    bind_method(control_port, setSimulationEngine, &Component__MessageBox::control_port__setSimulationEngine, this);
    bind_method(control_port, message, &Component__MessageBox::control_port__message, this);
    bind_method(control_port, callSimEngine, &Component__MessageBox::control_port__callSimEngine, this);

    // avoid the automatic calling of the methods through the framework
    control_port.configure.setLocalOnly(true);
    control_port.init.setLocalOnly(true);
    control_port.interconnect.setLocalOnly(true);
//  control_port.postConnect.setLocalOnly(true);
    control_port.reset.setLocalOnly(true);
    control_port.loadApplicationFile.setLocalOnly(true);
    control_port.disconnect.setLocalOnly(true);
    control_port.terminate.setLocalOnly(true);
    control_port.save.setLocalOnly(true);
    control_port.restore.setLocalOnly(true);
    control_port.populateCADIMap.setLocalOnly(true);
//  control_port.refresh.setLocalOnly(true);
    control_port.step.setLocalOnly(true);
    control_port.update.setLocalOnly(true);
    control_port.communicate.setLocalOnly(true);
    control_port.getProperty.setLocalOnly(true);
    control_port.traceEndOfCycle.setLocalOnly(true);
//  control_port.bypass.setLocalOnly(true);
//  control_port.run.setLocalOnly(true);
//  control_port.stop.setLocalOnly(true);
//  control_port.idle.setLocalOnly(true); // broadcast ports don't have setLocalOnly
//  control_port.quit.setLocalOnly(true);
//  control_port.setSimulationEngine.setLocalOnly(true);

    // bind cadiPort behaviors
    bind_method(cadiPort__, GetParameters, &Component__MessageBox::cadiPort__GetParameters, this);
    bind_method(cadiPort__, GetParameterInfo, &Component__MessageBox::cadiPort__GetParameterInfo, this);
    bind_method(cadiPort__, GetProperty, &Component__MessageBox::cadiPort__GetProperty, this);
    bind_method(cadiPort__, LoadApplicationFile, &Component__MessageBox::cadiPort__LoadApplicationFile, this);
    bind_method(cadiPort__, GetApplicationsAndCommandLineParams, &Component__MessageBox::cadiPort__GetApplicationsAndCommandLineParams, this);

    // connect control ports for subcomponents to subcomponents
	controlPort_busslave__.connectTo(busslave->findPort("$control"));



    // resource initialization code
    reset_resources__();

    // bind behaviors to abstract ports
	bind_method(message, begin_msg, &Component__MessageBox::abstract_port__message__begin_msg, this);
	bind_method(message, cancel_msg, &Component__MessageBox::abstract_port__message__cancel_msg, this);
	bind_method(message, end_msg, &Component__MessageBox::abstract_port__message__end_msg, this);
	bind_method(device, read, &Component__MessageBox::abstract_port__device__read, this);
	bind_method(device, write, &Component__MessageBox::abstract_port__device__write, this);
	bind_method(device, debugRead, &Component__MessageBox::abstract_port__device__debugRead, this);
	bind_method(device, debugWrite, &Component__MessageBox::abstract_port__device__debugWrite, this);


    // add abstract ports
	publishSlavePort("pvbus_s", pvbus_s);
	pvbus_s.SetName__("pvbus_s");
	publishMasterPort("intr", intr);
	intr.SetName__("intr");
	publishSlavePort("message", message);
	message.SetName__("message");
	device.SetName__("device");
	__MessageBox_internal_1.SetName__("__MessageBox_internal_1");


    // wire up static connection map
	pvbus_s.connectTo(busslave->findPort("pvbus_s"));
	busslave->findPort("device").connectTo(device);
	__MessageBox_internal_1.connectTo(busslave->findPort("control"));


    // init profiling

    // init resources


    // run the parameter write access functions for all of the component's parameters
    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        std::string paramName = parameterInfos__[i].name;

        switch (parameterInfos__[i].dataType)
        {
        case eslapi::CADI_PARAM_STRING:
            {
                std::string data = GetParameterValue(params, paramName, parameterInfos__[i].defaultString);
                parameter_write_string_func(paramNameToParamAccessFuncID(paramName), data);
            }
            break;
        case eslapi::CADI_PARAM_BOOL:
        case eslapi::CADI_PARAM_INT:
            {
                int64_t data = GetParameterValue(params, paramName, parameterInfos__[i].defaultValue, parameterInfos__[i].minValue, parameterInfos__[i].maxValue);
                parameter_write_func(paramNameToParamAccessFuncID(paramName), &data);
            }
            break;
        default:
            break;
        }
    }
}


Component__MessageBox::~Component__MessageBox()
{
}

void Component__MessageBox::control_port__configure(const sg::Params& params)
{
	if(controlPort_busslave__.configure.implemented()) controlPort_busslave__.configure(params.getParamsFor("busslave"));


    assert(simulationContext__->getSimulationEngine());
    cadi__ = new Component__MessageBox_CADI(this, simulationContext__->getSimulationEngine());

    // forward certain calls from CADI interface to this component
    cadi__->GetCADIPort().connectTo(cadiPort__);

    

    std::map< std::string, eslapi::CAInterface* > tempMap;
    control_port__populateCADIMap(tempMap, ""); // precompute mxdi map

	cadi__->EnableSubComponentCADIImport();


}

void Component__MessageBox::control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* >&output_map, std::string const & base_prefix)
{
    if (componentName2CADI__.empty())
    {
        componentName2CADI__[getName()] = static_cast<eslapi::CADI*>(cadi__);
        std::string prefix = getName() + ".";

		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_busslave__.populateCADIMap.implemented())
			{
				controlPort_busslave__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
			eslapi::CADI *cadi = obtainCADI__("busslave", compMap);
			if (cadi != NULL)
			{
				cadiParameterProxy_busslave_of_PVBusSlave_to_MessageBox__ = new CADIParameterProxy(cadi, &parameterFilter_busslave_of_PVBusSlave_to_MessageBox__);
			}
		}

    }
    // Copy the local map into the given map with the requested prefix.
    for (std::map<std::string,eslapi::CAInterface*>::iterator it = componentName2CADI__.begin(); it != componentName2CADI__.end(); ++it)
    {
        output_map.insert(std::make_pair(base_prefix + it->first, it->second));
    }
}

eslapi::CADI* Component__MessageBox::obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const
{
    std::map< std::string, eslapi::CAInterface* >::const_iterator it = componentName2CADI.find(subcomp);
    if (it != componentName2CADI.end())
    {
        eslapi::CAInterface *cai = it->second;
        if (cai != NULL)
        {
            cai = cai->ObtainInterface(eslapi::CADI::IFNAME(), 0, 0);
            if (cai != NULL)
            {
                return static_cast<eslapi::CADI*>(cai);
            }
        }
    }
    return NULL;
}

void Component__MessageBox::insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface* > &componentName2CADI)
{
    for (std::map<std::string, eslapi::CAInterface*>::iterator it = componentName2CADI.begin(); it != componentName2CADI.end(); it++)
    {
        // put prefix in front of all entries
        componentName2CADI__[prefix + it->first] = it->second;
    }
}


std::string Component__MessageBox::control_port__getProperty(const std::string& propname)
{
    if(properties__.find(propname) != properties__.end())
    {
        return properties__[propname];
    }
    else
        return ""; // unknown property
}


std::string Component__MessageBox::control_port__bypass(const std::string&)
{
    return "";
}


void Component__MessageBox::control_port__run()
{
}


void Component__MessageBox::control_port__stop()
{
}


void Component__MessageBox::control_port__idle()
{
}


void Component__MessageBox::control_port__quit()
{
}


void Component__MessageBox::control_port__setSimulationEngine(SimulationEngine*)
{
}


void Component__MessageBox::control_port__message(const std::string &msg, sg::message::MessageType msgType)
{
}


std::string Component__MessageBox::control_port__callSimEngine(const std::string &)
{
    return "";
}


void Component__MessageBox::control_port__reset(int level)
{
    // restore the resources' reset values before executing 'reset'
    reset_resources__();
    reset(level);
}


void Component__MessageBox::control_port__terminate()
{
    // the CADI was created before 'init', therefore we free it after 'terminate'
    terminate();
    freeCADIResources__();
}


void Component__MessageBox::freeCADIResources__()
{
    // free CADI parameter proxies
	delete cadiParameterProxy_busslave_of_PVBusSlave_to_MessageBox__;
	cadiParameterProxy_busslave_of_PVBusSlave_to_MessageBox__ = 0;


    // free CADI interface
    delete cadi__;
    cadi__ = 0;
}


// CADI Port implementations
eslapi::CADIReturn_t Component__MessageBox::cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params)
{
    // check arguments
    if(actualNumOfParams == 0)
        return eslapi::CADI_STATUS_IllegalArgument;
    *actualNumOfParams = 0;
    if(params == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    // collect parameters
    size_t i = 0;
    for (; (i < desiredNumOfParams) && ((startIndex + i) < parameterInfos__.size()); ++i)
    {
        params[i] = parameterInfos__[startIndex + i];
    }
    *actualNumOfParams = (MxU32)i;

    return eslapi::CADI_STATUS_OK;
}

eslapi::CADIReturn_t Component__MessageBox::cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param)
{
    if(param == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        if (!strcmp(parameterInfos__[i].name, parameterName.c_str()))
        {
            *param = parameterInfos__[i];

            return eslapi::CADI_STATUS_OK;
        }
    }

    return eslapi::CADI_STATUS_GeneralError;
}


bool Component__MessageBox::ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy, const char *param_name, int64_t intVal, const char *strVal)
{
    if (!proxy)
        return false;

    // we need the parameter's CADI id in order to create an eslapi::CADIParameterValue_t structure
    // therefore, we first retrieve its eslapi::CADIParameterInfo_t meta-data
    eslapi::CADIParameterInfo_t paramInfo;
    if (proxy->CADIGetParameterInfo(param_name, &paramInfo) != eslapi::CADI_STATUS_OK)
        return false;

    eslapi::CADIParameterValue_t paramVal(paramInfo.id, paramInfo.dataType, intVal, strVal);
    eslapi::CADIFactoryErrorMessage_t error;
    if (proxy->CADISetParameters(1, &paramVal, &error) != eslapi::CADI_STATUS_OK)
        return false;

    return true;
}


sg::accessfunc::AccessFuncResult Component__MessageBox::parameter_read_func(uint32_t id, int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_id: *data = id; break;

        default:
            printf("error: Component__MessageBox::parameter_read_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__MessageBox::parameter_read_string_func(uint32_t id, std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__MessageBox::parameter_read_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__MessageBox::parameter_write_func(uint32_t id, const int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_id:
		{
			*(const_cast<uint32_t*>(&id)) = *data;
		}
		break;

        default:
            printf("error: Component__MessageBox::parameter_write_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__MessageBox::parameter_write_string_func(uint32_t id, const std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__MessageBox::parameter_write_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

void Component__MessageBox::cadiPort__LoadApplicationFile(const std::string& filename)
{
    loadApplicationFile(filename);
    applications2params[filename] = "";
}

void Component__MessageBox::cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_)
{
    applications2params_ = applications2params;
}

eslapi::CADIReturn_t Component__MessageBox::cadiPort__GetProperty(const std::string& propertyName, std::string &value)
{
    if(properties__.find(propertyName) != properties__.end())
    {
        value = properties__[propertyName];
        return eslapi::CADI_STATUS_OK;
    }
    else
    {
        value = "";
        return eslapi::CADI_STATUS_GeneralError;
    }
}

// functions to stop and lock the simulator
// we only expose the simHalt() function in the documentation for the moment

void Component__MessageBox::simHalt()
{
    cadi__->StopSimulation();
}


// start simulation from the inside
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
void Component__MessageBox::simRun()
{
    cadi__->CADIExecContinue();
}


// return true if simulation is running
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
bool Component__MessageBox::simIsRunning()
{
    uint32_t mode = eslapi::CADI_EXECMODE_Stop;
    cadi__->CADIExecGetMode(&mode);
    return mode != eslapi::CADI_EXECMODE_Stop;
}


void Component__MessageBox::simShutdown()
{
    cadiPort__.simShutdown();
}

void Component__MessageBox::simReset(uint32_t level)
{
    cadi__->CADIExecReset(level);
}

uint32_t Component__MessageBox::paramNameToParamAccessFuncID(const std::string &name)
{
    uint32_t id = 0;
    if (name == "") id = 0xffffffff;
    if (name == "id") id = PARAMETER_ID_id;

    return id;
}

void Component__MessageBox::reset_resources__()
{
    // resource initialization code
	MESSAGEBOX_ID = 0; // reset register
	MESSAGEBOX_DATA = 0; // reset register
	MESSAGEBOX_CONTROL = 0; // reset register
	MESSAGEBOX_STATUS = 0; // reset register
	MESSAGEBOX_START = 0; // reset register
	MESSAGEBOX_END = 0; // reset register
	MESSAGEBOX_IRQMASK = 0; // reset register

}


} // FVP_VE_Cortex_A15x1_NMS
#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::interconnect()
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::disconnect()
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::update()
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::communicate()
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::traceEndOfCycle()
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::loadApplicationFile(const std::string& filename)
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::init()
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::terminate()
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::reset(int level)
{;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::reset(int level, int /*argc*/, char** /*argv*/)
{
	reset(level);

}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VirtualEthernetCrossover::save(MxODataStream& os)
{;return true;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VirtualEthernetCrossover::restore(MxIDataStream& is)
{;return true;
}
}

#line 4 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::step()
{;
}
}

#line 21 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::abstract_port__deva__sendToSlave(EthernetFrame* frame)
{
 if(devb.sendToMaster.implemented())
 devb.sendToMaster(frame);
 
}
}

#line 28 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VirtualEthernetCrossover.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VirtualEthernetCrossover::abstract_port__devb__sendToSlave(EthernetFrame* frame)
{
 if(deva.sendToMaster.implemented())
 deva.sendToMaster(frame);
 
}
}

#line 5828 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// ------------------------------------------------------------------------------
// implementation of class Component__VirtualEthernetCrossover
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

Component__VirtualEthernetCrossover::Component__VirtualEthernetCrossover(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params):
    SystemGenComponent(instName, simulationContext, params)




{
    // initialize properties__
	properties__["component_name"] = "";
	properties__["component_type"] = "Peripheral";
	properties__["debugger_name"] = "";
	properties__["debugger_start_command"] = "";
	properties__["default_view"] = "auto";
	properties__["description"] = "Ethernet Crossover Cable";
	properties__["documentation_file"] = "../Docs/DUI0423O_fast_model_rm.pdf";
	properties__["dso_safe"] = "1";
	properties__["executes_software"] = "0";
	properties__["expose_extern_sub_component_cadi"] = "1";
	properties__["factory_namespace"] = "";
	properties__["has_cadi"] = "1";
	properties__["has_implicit_clk_in"] = "1";
	properties__["hidden"] = "0";
	properties__["icon_file"] = "";
	properties__["ip_provider"] = "";
	properties__["is_single_stepped"] = "0";
	properties__["license_feature"] = "";
	properties__["loadfile_extension"] = "";
	properties__["save_restore"] = "0";
	properties__["small_icon_file"] = "";
	properties__["variant"] = "";
	properties__["version"] = "8.1.37";

    // initialize parameter info
    {
        sg::ComponentFactory *factory = VirtualEthernetCrossover_GetFactory();

        sg::TargetInfo *targetInfo = factory->getTargetInfo(""); // empty string means 'this' component

        if(targetInfo) // if we have no target info we also have no parameters towards CADI interfaces
        {
            // get parameter infos
            for(unsigned int i = 0; i < targetInfo->parameter_count; i++)
            {
                parameterId2parameterName__[targetInfo->parameter_info[i].id] = targetInfo->parameter_info[i].name;
                parameterInfos__.push_back((targetInfo->parameter_info)[i]);
            }
        }

        factory->dereference();
    }

    // create subcomponents
	{
	}


    // bind local behaviors to this->control_port
    bind_method(control_port, configure, &Component__VirtualEthernetCrossover::control_port__configure, this);
    bind_method(control_port, init, &Component__VirtualEthernetCrossover::init, this);
    bind_method(control_port, interconnect, &Component__VirtualEthernetCrossover::interconnect, this);
//  bind_method(control_port, postConnect, &Component__VirtualEthernetCrossover::postConnect, this);
    bind_method(control_port, reset, &Component__VirtualEthernetCrossover::control_port__reset, this);
    bind_method(control_port, loadApplicationFile, &Component__VirtualEthernetCrossover::loadApplicationFile, this);
    bind_method(control_port, disconnect, &Component__VirtualEthernetCrossover::disconnect, this);
    bind_method(control_port, terminate, &Component__VirtualEthernetCrossover::control_port__terminate, this);
    bind_method(control_port, populateCADIMap, &Component__VirtualEthernetCrossover::control_port__populateCADIMap, this);
//  bind_method(control_port, refresh, &Component__VirtualEthernetCrossover::refresh, this);
    bind_method(control_port, step, &Component__VirtualEthernetCrossover::step, this);
    bind_method(control_port, update, &Component__VirtualEthernetCrossover::update, this);
    bind_method(control_port, communicate, &Component__VirtualEthernetCrossover::communicate, this);
    bind_method(control_port, getProperty, &Component__VirtualEthernetCrossover::control_port__getProperty, this);
    bind_method(control_port, traceEndOfCycle, &Component__VirtualEthernetCrossover::traceEndOfCycle, this);
    bind_method(control_port, bypass, &Component__VirtualEthernetCrossover::control_port__bypass, this);
    bind_method(control_port, run, &Component__VirtualEthernetCrossover::control_port__run, this);
    bind_method(control_port, stop, &Component__VirtualEthernetCrossover::control_port__stop, this);
    bind_method(control_port, idle, &Component__VirtualEthernetCrossover::control_port__idle, this);
    bind_method(control_port, quit, &Component__VirtualEthernetCrossover::control_port__quit, this);
    bind_method(control_port, setSimulationEngine, &Component__VirtualEthernetCrossover::control_port__setSimulationEngine, this);
    bind_method(control_port, message, &Component__VirtualEthernetCrossover::control_port__message, this);
    bind_method(control_port, callSimEngine, &Component__VirtualEthernetCrossover::control_port__callSimEngine, this);

    // avoid the automatic calling of the methods through the framework
    control_port.configure.setLocalOnly(true);
    control_port.init.setLocalOnly(true);
    control_port.interconnect.setLocalOnly(true);
//  control_port.postConnect.setLocalOnly(true);
    control_port.reset.setLocalOnly(true);
    control_port.loadApplicationFile.setLocalOnly(true);
    control_port.disconnect.setLocalOnly(true);
    control_port.terminate.setLocalOnly(true);
    control_port.save.setLocalOnly(true);
    control_port.restore.setLocalOnly(true);
    control_port.populateCADIMap.setLocalOnly(true);
//  control_port.refresh.setLocalOnly(true);
    control_port.step.setLocalOnly(true);
    control_port.update.setLocalOnly(true);
    control_port.communicate.setLocalOnly(true);
    control_port.getProperty.setLocalOnly(true);
    control_port.traceEndOfCycle.setLocalOnly(true);
//  control_port.bypass.setLocalOnly(true);
//  control_port.run.setLocalOnly(true);
//  control_port.stop.setLocalOnly(true);
//  control_port.idle.setLocalOnly(true); // broadcast ports don't have setLocalOnly
//  control_port.quit.setLocalOnly(true);
//  control_port.setSimulationEngine.setLocalOnly(true);

    // bind cadiPort behaviors
    bind_method(cadiPort__, GetParameters, &Component__VirtualEthernetCrossover::cadiPort__GetParameters, this);
    bind_method(cadiPort__, GetParameterInfo, &Component__VirtualEthernetCrossover::cadiPort__GetParameterInfo, this);
    bind_method(cadiPort__, GetProperty, &Component__VirtualEthernetCrossover::cadiPort__GetProperty, this);
    bind_method(cadiPort__, LoadApplicationFile, &Component__VirtualEthernetCrossover::cadiPort__LoadApplicationFile, this);
    bind_method(cadiPort__, GetApplicationsAndCommandLineParams, &Component__VirtualEthernetCrossover::cadiPort__GetApplicationsAndCommandLineParams, this);

    // connect control ports for subcomponents to subcomponents



    // resource initialization code
    reset_resources__();

    // bind behaviors to abstract ports
	bind_method(deva, sendToSlave, &Component__VirtualEthernetCrossover::abstract_port__deva__sendToSlave, this);
	bind_method(devb, sendToSlave, &Component__VirtualEthernetCrossover::abstract_port__devb__sendToSlave, this);


    // add abstract ports
	publishSlavePort("deva", deva);
	deva.SetName__("deva");
	publishSlavePort("devb", devb);
	devb.SetName__("devb");


    // wire up static connection map


    // init profiling

    // init resources


    // run the parameter write access functions for all of the component's parameters
    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        std::string paramName = parameterInfos__[i].name;

        switch (parameterInfos__[i].dataType)
        {
        case eslapi::CADI_PARAM_STRING:
            {
                std::string data = GetParameterValue(params, paramName, parameterInfos__[i].defaultString);
                parameter_write_string_func(paramNameToParamAccessFuncID(paramName), data);
            }
            break;
        case eslapi::CADI_PARAM_BOOL:
        case eslapi::CADI_PARAM_INT:
            {
                int64_t data = GetParameterValue(params, paramName, parameterInfos__[i].defaultValue, parameterInfos__[i].minValue, parameterInfos__[i].maxValue);
                parameter_write_func(paramNameToParamAccessFuncID(paramName), &data);
            }
            break;
        default:
            break;
        }
    }
}


Component__VirtualEthernetCrossover::~Component__VirtualEthernetCrossover()
{
}

void Component__VirtualEthernetCrossover::control_port__configure(const sg::Params& params)
{


    assert(simulationContext__->getSimulationEngine());
    cadi__ = new Component__VirtualEthernetCrossover_CADI(this, simulationContext__->getSimulationEngine());

    // forward certain calls from CADI interface to this component
    cadi__->GetCADIPort().connectTo(cadiPort__);

    

    std::map< std::string, eslapi::CAInterface* > tempMap;
    control_port__populateCADIMap(tempMap, ""); // precompute mxdi map

	cadi__->EnableSubComponentCADIImport();


}

void Component__VirtualEthernetCrossover::control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* >&output_map, std::string const & base_prefix)
{
    if (componentName2CADI__.empty())
    {
        componentName2CADI__[getName()] = static_cast<eslapi::CADI*>(cadi__);
        std::string prefix = getName() + ".";


    }
    // Copy the local map into the given map with the requested prefix.
    for (std::map<std::string,eslapi::CAInterface*>::iterator it = componentName2CADI__.begin(); it != componentName2CADI__.end(); ++it)
    {
        output_map.insert(std::make_pair(base_prefix + it->first, it->second));
    }
}

eslapi::CADI* Component__VirtualEthernetCrossover::obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const
{
    std::map< std::string, eslapi::CAInterface* >::const_iterator it = componentName2CADI.find(subcomp);
    if (it != componentName2CADI.end())
    {
        eslapi::CAInterface *cai = it->second;
        if (cai != NULL)
        {
            cai = cai->ObtainInterface(eslapi::CADI::IFNAME(), 0, 0);
            if (cai != NULL)
            {
                return static_cast<eslapi::CADI*>(cai);
            }
        }
    }
    return NULL;
}

void Component__VirtualEthernetCrossover::insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface* > &componentName2CADI)
{
    for (std::map<std::string, eslapi::CAInterface*>::iterator it = componentName2CADI.begin(); it != componentName2CADI.end(); it++)
    {
        // put prefix in front of all entries
        componentName2CADI__[prefix + it->first] = it->second;
    }
}


std::string Component__VirtualEthernetCrossover::control_port__getProperty(const std::string& propname)
{
    if(properties__.find(propname) != properties__.end())
    {
        return properties__[propname];
    }
    else
        return ""; // unknown property
}


std::string Component__VirtualEthernetCrossover::control_port__bypass(const std::string&)
{
    return "";
}


void Component__VirtualEthernetCrossover::control_port__run()
{
}


void Component__VirtualEthernetCrossover::control_port__stop()
{
}


void Component__VirtualEthernetCrossover::control_port__idle()
{
}


void Component__VirtualEthernetCrossover::control_port__quit()
{
}


void Component__VirtualEthernetCrossover::control_port__setSimulationEngine(SimulationEngine*)
{
}


void Component__VirtualEthernetCrossover::control_port__message(const std::string &msg, sg::message::MessageType msgType)
{
}


std::string Component__VirtualEthernetCrossover::control_port__callSimEngine(const std::string &)
{
    return "";
}


void Component__VirtualEthernetCrossover::control_port__reset(int level)
{
    // restore the resources' reset values before executing 'reset'
    reset_resources__();
    reset(level);
}


void Component__VirtualEthernetCrossover::control_port__terminate()
{
    // the CADI was created before 'init', therefore we free it after 'terminate'
    terminate();
    freeCADIResources__();
}


void Component__VirtualEthernetCrossover::freeCADIResources__()
{
    // free CADI parameter proxies


    // free CADI interface
    delete cadi__;
    cadi__ = 0;
}


// CADI Port implementations
eslapi::CADIReturn_t Component__VirtualEthernetCrossover::cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params)
{
    // check arguments
    if(actualNumOfParams == 0)
        return eslapi::CADI_STATUS_IllegalArgument;
    *actualNumOfParams = 0;
    if(params == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    // collect parameters
    size_t i = 0;
    for (; (i < desiredNumOfParams) && ((startIndex + i) < parameterInfos__.size()); ++i)
    {
        params[i] = parameterInfos__[startIndex + i];
    }
    *actualNumOfParams = (MxU32)i;

    return eslapi::CADI_STATUS_OK;
}

eslapi::CADIReturn_t Component__VirtualEthernetCrossover::cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param)
{
    if(param == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        if (!strcmp(parameterInfos__[i].name, parameterName.c_str()))
        {
            *param = parameterInfos__[i];

            return eslapi::CADI_STATUS_OK;
        }
    }

    return eslapi::CADI_STATUS_GeneralError;
}


bool Component__VirtualEthernetCrossover::ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy, const char *param_name, int64_t intVal, const char *strVal)
{
    if (!proxy)
        return false;

    // we need the parameter's CADI id in order to create an eslapi::CADIParameterValue_t structure
    // therefore, we first retrieve its eslapi::CADIParameterInfo_t meta-data
    eslapi::CADIParameterInfo_t paramInfo;
    if (proxy->CADIGetParameterInfo(param_name, &paramInfo) != eslapi::CADI_STATUS_OK)
        return false;

    eslapi::CADIParameterValue_t paramVal(paramInfo.id, paramInfo.dataType, intVal, strVal);
    eslapi::CADIFactoryErrorMessage_t error;
    if (proxy->CADISetParameters(1, &paramVal, &error) != eslapi::CADI_STATUS_OK)
        return false;

    return true;
}


sg::accessfunc::AccessFuncResult Component__VirtualEthernetCrossover::parameter_read_func(uint32_t id, int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {

        default:
            printf("error: Component__VirtualEthernetCrossover::parameter_read_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VirtualEthernetCrossover::parameter_read_string_func(uint32_t id, std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__VirtualEthernetCrossover::parameter_read_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VirtualEthernetCrossover::parameter_write_func(uint32_t id, const int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {

        default:
            printf("error: Component__VirtualEthernetCrossover::parameter_write_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VirtualEthernetCrossover::parameter_write_string_func(uint32_t id, const std::string &data)
{
    switch (id)
    {

        default:
            printf("error: Component__VirtualEthernetCrossover::parameter_write_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

void Component__VirtualEthernetCrossover::cadiPort__LoadApplicationFile(const std::string& filename)
{
    loadApplicationFile(filename);
    applications2params[filename] = "";
}

void Component__VirtualEthernetCrossover::cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_)
{
    applications2params_ = applications2params;
}

eslapi::CADIReturn_t Component__VirtualEthernetCrossover::cadiPort__GetProperty(const std::string& propertyName, std::string &value)
{
    if(properties__.find(propertyName) != properties__.end())
    {
        value = properties__[propertyName];
        return eslapi::CADI_STATUS_OK;
    }
    else
    {
        value = "";
        return eslapi::CADI_STATUS_GeneralError;
    }
}

// functions to stop and lock the simulator
// we only expose the simHalt() function in the documentation for the moment

void Component__VirtualEthernetCrossover::simHalt()
{
    cadi__->StopSimulation();
}


// start simulation from the inside
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
void Component__VirtualEthernetCrossover::simRun()
{
    cadi__->CADIExecContinue();
}


// return true if simulation is running
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
bool Component__VirtualEthernetCrossover::simIsRunning()
{
    uint32_t mode = eslapi::CADI_EXECMODE_Stop;
    cadi__->CADIExecGetMode(&mode);
    return mode != eslapi::CADI_EXECMODE_Stop;
}


void Component__VirtualEthernetCrossover::simShutdown()
{
    cadiPort__.simShutdown();
}

void Component__VirtualEthernetCrossover::simReset(uint32_t level)
{
    cadi__->CADIExecReset(level);
}

uint32_t Component__VirtualEthernetCrossover::paramNameToParamAccessFuncID(const std::string &name)
{
    uint32_t id = 0;
    if (name == "") id = 0xffffffff;

    return id;
}

void Component__VirtualEthernetCrossover::reset_resources__()
{
    // resource initialization code

}


} // FVP_VE_Cortex_A15x1_NMS
#line 475 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::calculateStats(bool force)
{
 
 calculate_stats_phase++;
 if ((calculate_stats_phase < 5) && (!force))
 return;
 calculate_stats_phase = 0;

 
 draw_leds();
 if (redraw_daughter_switches)
 {
 draw_switches();
 }

 uint32_t ct = get_msTime(); 
 uint32_t elapsed_time_ms = ct - last_time;

 
 if ((elapsed_time_ms < 500) && (!force))
 return;

 bool running = false;

 for(unsigned cluster=0; cluster<num_clusters; cluster++)
 {
 uint64_t ticks=0;
 ClusterState* cl_state = &cluster_state[cluster];

 for(unsigned core=0; core<cl_state->getNumCores(); core++)
 {
 switch(cluster)
 {
 case 0:
 ticks += cluster0_ticks[core].getValue();
 cl_state->setCoreRunState(core, cluster0_ticks[core].getRunState());
 break;

 case 1:
 ticks += cluster1_ticks[core].getValue();
 cl_state->setCoreRunState(core, cluster1_ticks[core].getRunState());
 break;

 default:
 assert(!"Case for additional cluster(s) required");
 break;
 }
 }

 running |= cl_state->update(ticks, elapsed_time_ms, num_clusters > 1);
 }


 
 if (perf_index_real_time_ms)
 sim_pidx = float(perf_index_sim_time_ms) / perf_index_real_time_ms;
 perf_index_sim_time_ms = 0;
 perf_index_real_time_ms = 0;

 if (!running)
 {
 start_time += elapsed_time_ms;
 sim_pidx = 0.0;
 }

 last_time = ct;

 draw_status(ct);
 
}
}

#line 641 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::init()
{
 {if(!controlPort_idler__.init.empty()) controlPort_idler__.init();if(!controlPort_timer__.init.empty()) controlPort_timer__.init();if(!controlPort_recorder__.init.empty()) controlPort_recorder__.init();}; 

 
 

 num_clusters=0;
 for(unsigned cluster=0; cluster<2; cluster++)
 {
 unsigned core;

 for(core=0; core<4; core++)
 {
 if (cluster == 0)
 {
 if( !cluster0_ticks[core].getValue.implemented() ||
 !cluster0_ticks[core].getRunState.implemented()) break;
 }
 else if (cluster == 1)
 {
 if( !cluster1_ticks[core].getValue.implemented() ||
 !cluster1_ticks[core].getRunState.implemented()) break;
 }
 else
 {
 assert(!"Case for additional cluster(s) required");
 }
 }

 if (core > 0)
 {
 const char* name = 0;

 switch(cluster)
 {
 case 0: name = cluster0_name.c_str(); break;
 case 1: name = cluster1_name.c_str(); break;
 
 }

 cluster_state[cluster].init(cluster, core, name);
 num_clusters++;
 }
 }

 
 
 
 

 user_dips_label = 0;
 user_dips = 0;
 boot_dips_label = 0;
 boot_dips = 0;
 led_label = 0;
 user_led = 0;
 daughter_label = 0;
 daughter_dips = 0;
 daughter_led = 0;
 rl_label = 0;
 rl_button = 0;
 label_time_perf = 0;
 value_time_perf = 0;
 mouse_label = 0;
 white_line = 0;

 if (disable_visualisation)
 {
 fake_layout = new VisRasterLayout();
 return;
 }

 ctrl_key = false;
 toggle_mouse = false;
 start_time = get_msTime();
 last_time = start_time;
 perf_index_real_time_ms = 0;
 perf_index_sim_time_ms = 0;
 throttle_last_real_time_ms = start_time;
 throttle_budget = 0;
 calculate_stats_phase = 0;
 sim_pidx = 0.0;

 disp_delay = rate_limit_enable;
 disp_totals = true;
 stopped = false;

 daughter_user_switches_value = 0x0;
 redraw_daughter_switches = false;
 daughter_leds_value = 0x0;

 lcd_width = 320;
 lcd_height = 240;
 init_gui();
 
}
}

#line 738 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::init_gui()
{
 
 vis = createVisualisation(cpu_name.c_str(), window_title.c_str());

 
 render_lcd = vis->createRenderRegion();
 recorderControl.registerVisRegion(render_lcd, "render_lcd");

 render_status = vis->createRenderRegion();
 recorderControl.registerVisRegion(render_status, "render_status");

 resize_lcd(640, 40);

 reconfigureWindow();

 render_lcd->setVisible(true);
 render_status->setVisible(true);

 init_icons();

 init_status();
 
}
}

#line 763 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::init_icons()
{
 for(unsigned i=0; i<CORE_RUN_STATE_LIMIT; i++)
 {
 crs_icon[i] = 0;
 }

 
 static const char* unknown_bitmap[6] =
 { " ###  ",
 "#   # ",
 "   #  ",
 "  #   ",
 "      ",
 "  #   " };

 static const char* run_bitmap[6] =
 { " #    ",
 " ##   ",
 " ###  ",
 " ##   ",
 " #    ",
 "      " };

 static const char* halt_bitmap[6] =
 { "      ",
 "## ## ",
 "## ## ",
 "## ## ",
 "## ## ",
 "      " };

 static const char* wfe_bitmap[6] =
 { " #### ",
 " #    ",
 " ###  ",
 " #    ",
 " #### ",
 "      " };

 static const char* wfi_bitmap[6] =
 { " ###  ",
 "  #   ",
 "  #   ",
 "  #   ",
 " ###  ",
 "      " };

 static const char* reset_bitmap[6] =
 { "      ",
 " #### ",
 " #### ",
 " #### ",
 " #### ",
 "      " };

 static const char* dormant_bitmap[6] =
 { " #### ",
 "##  ##",
 "#    #",
 "######",
 "######",
 "      " };

 static const char* shutdown_bitmap[6] =
 { " #### ",
 "##  ##",
 "#    #",
 "#    #",
 "######",
 "      " };

 uint32_t bg = render_status->mapRGB(0, 0, 0);
 uint32_t fg;

 fg = render_status->mapRGB(0xFF, 0xFF, 0xFF); 
 crs_icon[CORE_RUN_STATE_UNKNOWN] = new UIMonoIcon(vis, 6, 6, fg, bg, unknown_bitmap);

 fg = render_status->mapRGB(0x00, 0xFF, 0x00); 
 crs_icon[CORE_RUN_STATE_RUNNING] = new UIMonoIcon(vis, 6, 6, fg, bg, run_bitmap); 

 fg = render_status->mapRGB(0xA0, 0xA0, 0xA0); 
 crs_icon[CORE_RUN_STATE_HALTED] = new UIMonoIcon(vis, 6, 6, fg, bg, halt_bitmap);

 fg = render_status->mapRGB(0xFF, 0xC0, 0x00); 
 crs_icon[CORE_RUN_STATE_STANDBY_WFE] = new UIMonoIcon(vis, 6, 6, fg, bg, wfe_bitmap);

 fg = render_status->mapRGB(0xFF, 0x80, 0x00); 
 crs_icon[CORE_RUN_STATE_STANDBY_WFI] = new UIMonoIcon(vis, 6, 6, fg, bg, wfi_bitmap);

 fg = render_status->mapRGB(0xA0, 0xA0, 0xA0); 
 crs_icon[CORE_RUN_STATE_IN_RESET] = new UIMonoIcon(vis, 6, 6, fg, bg, reset_bitmap);

 fg = render_status->mapRGB(0xE0, 0x40, 0x20); 
 crs_icon[CORE_RUN_STATE_DORMANT] = new UIMonoIcon(vis, 6, 6, fg, bg, dormant_bitmap);

 fg = render_status->mapRGB(0xFF, 0x00, 0x00); 
 crs_icon[CORE_RUN_STATE_SHUTDOWN] = new UIMonoIcon(vis, 6, 6, fg, bg, shutdown_bitmap);
 
}
}

#line 863 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::init_status()
{
 
 render_status->fillRect(render_status->mapRGB(0, 0, 0),
 0, 0, lcd_width, status_height);

 
 

 delete user_dips_label;
 user_dips_label = new Clabel(render_status, "^ON USERSW 1..8", VIS_FONT_WIDTH, 2);

 
 
 delete user_dips;
 user_dips = new Cdipswitch(render_status,
 user_dips_label->getMaxX() + VIS_FONT_WIDTH*2, 1,
 8, user_switches.getValue());

 delete led_label;
 led_label = new Clabel(render_status, "S6LED0..7",
 user_dips->getMaxX() + VIS_FONT_WIDTH*4, 2);


 delete daughter_label;
 if ( (number_of_daughter_leds != 0) || (number_of_daughter_user_switches !=0) )
 {
 daughter_label = new Clabel(render_status, "Daughter", 
 led_label->getMaxX() + VIS_FONT_WIDTH*4, 2);
 }

 delete daughter_dips;
 if (number_of_daughter_user_switches != 0)
 {
 daughter_dips = new Cdipswitch(render_status,
 daughter_label->getMaxX() + VIS_FONT_WIDTH, 1,
 number_of_daughter_user_switches,
 daughter_user_switches_value);
 }

 
 delete boot_dips_label;
 boot_dips_label = new Clabel(render_status, "^ON BOOTSW 1..8",
 user_dips_label->getX(), VIS_FONT_HEIGHT + 1);

 delete boot_dips;
 boot_dips = new Cdipswitch(render_status, user_dips->getX(), VIS_FONT_HEIGHT + 1,
 8, 0);

 delete user_led;
 user_led = new Cled(render_status, led_label->getX(), VIS_FONT_HEIGHT + 2,
 8, 0);

 delete daughter_led;
 if (number_of_daughter_leds != 0)
 {
 daughter_led = new Cled( render_status,
 daughter_label->getMaxX() + VIS_FONT_WIDTH, VIS_FONT_HEIGHT + 2,
 number_of_daughter_leds, daughter_leds_value);
 }

 

 
 unsigned col = 1;
 unsigned line = 2;
 for(unsigned cluster=0; cluster<num_clusters; cluster++)
 {
 col = cluster_state[cluster].build_gui(render_status, 1, line++, num_clusters > 1, crs_icon) + 3;
 }

 delete label_time_perf;
 label_time_perf = new Clabel(render_status, 12,
 VIS_FONT_WIDTH*col, 1 + VIS_FONT_HEIGHT*2);
 col += 12+1;

 delete value_time_perf;
 value_time_perf = new Clabel(render_status, 10,
 VIS_FONT_WIDTH*col, 1 + VIS_FONT_HEIGHT*2);
 value_time_perf->setLeftJustify();

 
 delete rl_label;
 rl_label = new Clabel(render_status, 14,
 lcd_width - VIS_FONT_WIDTH*(14+1), 2);
 delete rl_button;
 rl_button = new Cbutton(render_status,
 lcd_width - VIS_FONT_WIDTH - 15, VIS_FONT_HEIGHT,
 15, 11, disp_delay, VIS_RED);

 
 delete mouse_label;
 mouse_label = new Clabel(render_status, 31,
 lcd_width - VIS_FONT_WIDTH*(31+1), VIS_FONT_HEIGHT*2);
 mouse_label->setRightJustify();

 
 delete white_line;
 white_line = new Cseparateline(render_status, 0, status_height - 2, lcd_width, 1);

 draw_labels();
 draw_leds();
 draw_switches();
 draw_buttons();
 draw_divider();
 draw_status(get_msTime());
 
}
}

#line 971 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::draw_buttons()
{
 rl_button->setState(disp_delay);
 
}
}

#line 976 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::draw_leds()
{
 bool led_change = false;

 if (leds.getValue.implemented())
 led_change = led_change || user_led->setState(leds.getValue());

 if (daughter_led != 0)
 led_change = led_change || daughter_led->setState(daughter_leds_value);

 if (led_change)
 calculateStats(true);
 
}
}

#line 990 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::draw_divider()
{
 white_line->redraw();
 
}
}

#line 995 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::draw_labels()
{
 for(unsigned i=0; i<2; i++)
 cluster_state[i].redraw_labels(disp_totals);

 label_time_perf->setLabel(disp_totals ? "Total Time: " : "Perf Index:");

 user_dips_label->redraw();
 boot_dips_label->redraw();
 led_label->redraw();
 if (daughter_label != 0)
 {
 daughter_label->redraw();
 }
 rl_label->setLabel(disp_delay ? "Rate Limit  ON" : "Rate Limit OFF" );
 mouse_label->setLabel(toggle_mouse ? "Release mouse: LeftCtrl+LeftAlt" :
 "Grab mouse: LeftCtrl+LeftAlt" );
 
}
}

#line 1014 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::draw_switches()
{
 if (user_switches.getValue.implemented())
 user_dips->setState(user_switches.getValue());

 if (daughter_dips != 0)
 daughter_dips->setState(daughter_user_switches_value);

 if (boot_switch.getValue.implemented())
 boot_dips->setState(boot_switch.getValue());

 redraw_daughter_switches = false;
 
}
}

#line 1028 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::draw_status(uint32_t msTime)
{
 char buf[30];

 for(unsigned i=0; i<2; i++)
 cluster_state[i].redraw_values(disp_totals);

 if (disp_totals) {
 value_time_perf->setLabel(ms2str(buf, msTime - start_time));
 } else {
 sprintf(buf,"%01.2f",sim_pidx);
 value_time_perf->setLabel(buf);
 }
 draw_switches();
 
}
}

#line 1044 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::reset(int level)
{
 {if(!controlPort_idler__.reset.empty()) controlPort_idler__.reset(level);if(!controlPort_timer__.reset.empty()) controlPort_timer__.reset(level);if(!controlPort_recorder__.reset.empty()) controlPort_recorder__.reset(level);};
 if (disable_visualisation)
 return;

 __VEVisualisation_internal_1.cancel();
 __VEVisualisation_internal_1.set(5);

 for(unsigned i=0; i<2; i++)
 cluster_state[i].reset();

 start_time = get_msTime();
 last_time = start_time;
 perf_index_real_time_ms = 0;
 perf_index_sim_time_ms = 0;
 throttle_last_real_time_ms = start_time;
 throttle_budget = 0;
 calculate_stats_phase = 0;

 sim_pidx = 0.0;
 mouse_abs_x = mouse_abs_y = 0;
 
}
}

#line 1068 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::delete_gui_elements()
{
 if (disable_visualisation)
 return;
 delete user_dips_label;
 delete user_dips;
 delete boot_dips_label;
 delete boot_dips;
 delete led_label;
 delete user_led;
 delete daughter_label;
 delete daughter_dips;
 delete daughter_led;
 delete rl_label;
 delete rl_button;
 delete label_time_perf;
 delete value_time_perf;
 delete mouse_label;
 delete white_line;

 delete render_status;
 delete render_lcd;

 delete vis;
 
}
}

#line 1094 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::terminate()
{
 delete_gui_elements();
 if (disable_visualisation)
 delete fake_layout;
 
 {if(!controlPort_idler__.terminate.empty()) controlPort_idler__.terminate();if(!controlPort_timer__.terminate.empty()) controlPort_timer__.terminate();if(!controlPort_recorder__.terminate.empty()) controlPort_recorder__.terminate();};
 
}
}

#line 1103 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VEVisualisation::get_msTime()
{
 
 
 
 struct timeval tv;
 if (gettimeofday(&tv, NULL) != 0) {
 return 0;
 }
 return (tv.tv_sec*1000)+(tv.tv_usec/1000);
 
 
}
}

#line 1116 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::toggleMouse()
{
 toggle_mouse = !toggle_mouse;
 toggle_mouse?vis->lockMouse(render_lcd):vis->unlockMouse();
 draw_labels();
 
}
}

#line 1124 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::handleKeyDown(ATKeyCode key)
{
 if ( key < 256 )
 keyboard.keyDown(key);

 if ( key == KC_LCONTROL )
 ctrl_key = true;

 if ( key == (ATKeyCode)trap_key )
 if (ctrl_key)
 toggleMouse();
 
}
}

#line 1137 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::handleKeyUp(ATKeyCode key)
{
 if (key < 256)
 keyboard.keyUp(key);

 if ( key == KC_LCONTROL )
 ctrl_key = false;
 
}
}

#line 1156 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::processMessages(bool playback)
{
 VisEvent event;

 if (relayout_needed) {
 reconfigureWindow();
 }

 while (((!playback) && vis->poll(&event)) || (playback && recorderControl.getEvent(&event)))
 {
 recorderControl.putEvent(&event);
 switch(event.type)
 {
 case VisEvent::KEYDOWN:
 handleKeyDown((ATKeyCode)event.keysym);
 break;

 case VisEvent::KEYUP:
 handleKeyUp((ATKeyCode)event.keysym);
 break;

 case VisEvent::MOUSEBUTTONDOWN:
 if (event.region == render_status) {
 if (user_dips->isHit(event.abs_x, event.abs_y))
 {
 if (user_switches.setValue.implemented())
 user_switches.setValue(user_dips->getState());
 }
 else if (daughter_dips != 0 &&
 daughter_dips->isHit(event.abs_x, event.abs_y))
 {
 daughter_user_switches_value = daughter_dips->getState();
 }
 else if (boot_dips->isHit(event.abs_x, event.abs_y))
 {
 if (boot_switch.setValue.implemented())
 boot_switch.setValue(boot_dips->getState());
 }
 else if (rl_button->isHit(event.abs_x, event.abs_y))
 {
 disp_delay = !disp_delay;
 if (disp_delay)
 {
 
 throttle_last_real_time_ms = get_msTime();
 throttle_budget = 0;
 }
 draw_buttons();
 draw_labels();
 }
 else
 {
 for(unsigned cluster=0; cluster<2; cluster++)
 {
 if (cluster_state[cluster].hit_gui(event.abs_x, event.abs_y))
 {
 disp_totals = !disp_totals;
 draw_labels();
 calculateStats(true);
 break;
 }
 }
 }
 }
 if (event.region == render_lcd) {
 emit_mouse_move(event);
 if (mouse.mouseButton.implemented()) {
 mouse.mouseButton(event.button, true);
 }
 if (touch_screen.mouseButton.implemented()) {
 touch_screen.mouseButton(event.button, true);
 }
 }
 break;
 case VisEvent::MOUSEBUTTONUP:
 if (event.region == render_lcd) {
 emit_mouse_move(event);
 if (mouse.mouseButton.implemented()) {
 mouse.mouseButton(event.button, false);
 }
 if (touch_screen.mouseButton.implemented())
 touch_screen.mouseButton(event.button, false);
 }
 break;
 case VisEvent::MOUSEMOTION:
 if (event.region == render_lcd) {
 emit_mouse_move(event);
 }
 break;
 case VisEvent::QUIT:
 
 
 
 
 if(!control_port.quit.empty())
 control_port.quit();
 break;
 case VisEvent::None: break;
 }
 }
 
}
}

#line 1259 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::emit_mouse_move(const VisEvent& event)
{
 
 
 
 
 
 
 
 
 

 
 int rel_x = event.abs_x - mouse_abs_x;
 int rel_y = event.abs_y - mouse_abs_y;
 mouse_abs_x = event.abs_x;
 mouse_abs_y = event.abs_y;

 
 int step = 100; 
 if (mouse.mouseMove.implemented()) {
 for (; rel_x | rel_y; )
 {
 int step_x = rel_x;
 if (step_x < -step)
 step_x = -step;
 else if (step_x > step)
 step_x = step;
 int step_y = rel_y;
 if (step_y < -step)
 step_y = -step;
 else if (step_y > step)
 step_y = step;
 mouse.mouseMove(step_x, step_y);
 rel_x -= step_x;
 rel_y -= step_y;
 }
 }
 if (touch_screen.mouseMove.implemented()) {
 touch_screen.mouseMove(event.abs_x,event.abs_y);
 }
 
}
}

#line 1304 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::resize_lcd(unsigned int w, unsigned int h)
{
 if (w == lcd_width && h == lcd_height) {
 return;
 }
 unsigned num_lines = 2 + num_clusters;
 if (num_lines < 3) num_lines = 3;
 status_height = VIS_FONT_HEIGHT*num_lines + 4;
 lcd_width = w;
 lcd_height = h;
 relayout_needed = true;
 
}
}

#line 1317 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::reconfigureWindow()
{
 relayout_needed = false;
 vis->configureWindow(lcd_width,
 lcd_height + status_height,
 24);
 render_lcd->setLocation(0, status_height, lcd_width, lcd_height);
 render_status->setLocation(0, 0, lcd_width, status_height);

 init_status();
 
}
}

#line 1329 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { char* 
Component__VEVisualisation::ms2str(char* buf, uint32_t ms)
{
 int s, m, h, d;
 s= ms/1000;
 d = s/(60*60*24);
 s = s-(d*60*60*24);
 h = s/(60*60);
 s = s-(h*60*60);
 m = s/60;
 s = s-(m*60);
 if (d) {
 sprintf(buf, "%dd, %d:%d:%d",d,h,m,s);
 } else if (h){
 sprintf(buf, "%2d:%02d:%02d",h,m,s);
 } else if (m) {
 sprintf(buf, "%dm %02ds",m,s);
 } else {
 sprintf(buf, "%ds",s);
 }
 return(buf);
 
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::interconnect()
{{if(!controlPort_idler__.interconnect.empty()) controlPort_idler__.interconnect();if(!controlPort_timer__.interconnect.empty()) controlPort_timer__.interconnect();if(!controlPort_recorder__.interconnect.empty()) controlPort_recorder__.interconnect();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::disconnect()
{{if(!controlPort_idler__.disconnect.empty()) controlPort_idler__.disconnect();if(!controlPort_timer__.disconnect.empty()) controlPort_timer__.disconnect();if(!controlPort_recorder__.disconnect.empty()) controlPort_recorder__.disconnect();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::update()
{{if(!controlPort_idler__.update.empty()) controlPort_idler__.update();if(!controlPort_timer__.update.empty()) controlPort_timer__.update();if(!controlPort_recorder__.update.empty()) controlPort_recorder__.update();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::communicate()
{{if(!controlPort_idler__.communicate.empty()) controlPort_idler__.communicate();if(!controlPort_timer__.communicate.empty()) controlPort_timer__.communicate();if(!controlPort_recorder__.communicate.empty()) controlPort_recorder__.communicate();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::traceEndOfCycle()
{{if(!controlPort_idler__.traceEndOfCycle.empty()) controlPort_idler__.traceEndOfCycle();if(!controlPort_timer__.traceEndOfCycle.empty()) controlPort_timer__.traceEndOfCycle();if(!controlPort_recorder__.traceEndOfCycle.empty()) controlPort_recorder__.traceEndOfCycle();};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::loadApplicationFile(const std::string& filename)
{{if(!controlPort_idler__.loadApplicationFile.empty()) controlPort_idler__.loadApplicationFile(filename);if(!controlPort_timer__.loadApplicationFile.empty()) controlPort_timer__.loadApplicationFile(filename);if(!controlPort_recorder__.loadApplicationFile.empty()) controlPort_recorder__.loadApplicationFile(filename);};
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VEVisualisation::save(MxODataStream& os)
{{if(!controlPort_idler__.save.empty()) controlPort_idler__.save(os);if(!controlPort_timer__.save.empty()) controlPort_timer__.save(os);if(!controlPort_recorder__.save.empty()) controlPort_recorder__.save(os);};return true;
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VEVisualisation::restore(MxIDataStream& is)
{{if(!controlPort_idler__.restore.empty()) controlPort_idler__.restore(is);if(!controlPort_timer__.restore.empty()) controlPort_timer__.restore(is);if(!controlPort_recorder__.restore.empty()) controlPort_recorder__.restore(is);};return true;
}
}

#line 6 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::step()
{{if(!controlPort_idler__.step.empty()) controlPort_idler__.step();if(!controlPort_timer__.step.empty()) controlPort_timer__.step();if(!controlPort_recorder__.step.empty()) controlPort_recorder__.step();};
}
}

#line 420 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VEVisualisation::abstract_port__timer_callback_handler__signal()
{
 
 int sim_ms_per_tick = 100; 

 
 uint32_t ct = get_msTime();
 int real_ms_per_tick = ct - throttle_last_real_time_ms;
 throttle_last_real_time_ms = ct;

 
 perf_index_sim_time_ms += sim_ms_per_tick;
 perf_index_real_time_ms += real_ms_per_tick;

 
 uint32_t timer_ticks_per_callback = 5; 
 if (!disp_delay)
 return timer_ticks_per_callback;

 
 if (real_ms_per_tick > 1000)
 real_ms_per_tick = 1000;

 
 throttle_budget += sim_ms_per_tick;
 throttle_budget -= real_ms_per_tick;

 
 
 
 if (throttle_budget < -1000)
 throttle_budget = -1000;

 
 
 
 
 if (throttle_budget > 500)
 throttle_budget = 500;

 
 if (throttle_budget > 0)
 usleep((throttle_budget)*1000);

 
 return timer_ticks_per_callback;
 
}
}

#line 558 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::abstract_port__gui_callback__gui_callback()
{
 if (disable_visualisation)
 return;
 processMessages(false);
 calculateStats(false);
 
}
}

#line 571 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { const VisRasterLayout* 
Component__VEVisualisation::abstract_port__lcd__lock()
{
 if (disable_visualisation)
 return fake_layout;
 return render_lcd->lock();
 
}
}

#line 577 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::abstract_port__lcd__unlock()
{
 if (disable_visualisation)
 return;
 return render_lcd->unlock();
 
}
}

#line 583 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::abstract_port__lcd__update(int x, int y, unsigned int w, unsigned int h)
{
 if (disable_visualisation)
 return;
 if (lcd_layout.setLayoutInfo.implemented())
 lcd_layout.setLayoutInfo(x, y, w, h); 
 return render_lcd->update(x, y, w, h);
 
}
}

#line 591 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::abstract_port__lcd__setPreferredLayout(unsigned int w, unsigned int h, unsigned int d)
{
 if (disable_visualisation)
 return;
 
 (void)d;
 resize_lcd(w, h);
 
}
}

#line 607 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::abstract_port__daughter_leds__setValue(uint32_t value_)
{
 
 daughter_leds_value = value_;
 
}
}

#line 613 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VEVisualisation::abstract_port__daughter_leds__getValue()
{
 return daughter_leds_value;
 
}
}

#line 620 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::abstract_port__daughter_user_switches__setValue(uint32_t value_)
{
 daughter_user_switches_value = value_;
 
 redraw_daughter_switches = true;
 
}
}

#line 627 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VEVisualisation::abstract_port__daughter_user_switches__getValue()
{
 return daughter_user_switches_value;
 
}
}

#line 1149 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VEVisualisation::abstract_port__recorderControl__processEvents()
{
 processMessages(true);
 
}
}

#line 7429 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// ------------------------------------------------------------------------------
// implementation of class Component__VEVisualisation
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

Component__VEVisualisation::Component__VEVisualisation(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params):
    SystemGenComponent(instName, simulationContext, params)

	,trap_key(GetParameterValue(params, "trap_key", MxS64CONST(0x4a), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,rate_limit_enable(!!GetParameterValue(params, "rate_limit-enable", MxS64CONST(0x1), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,disable_visualisation(!!GetParameterValue(params, "disable_visualisation", MxS64CONST(0x0), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,window_title(GetParameterValue(params, "window_title", "Fast Models - CLCD %cpu%"))
	,cpu_name(GetParameterValue(params, "cpu_name", ""))
	,cluster0_name(GetParameterValue(params, "cluster0_name", "Cluster0"))
	,cluster1_name(GetParameterValue(params, "cluster1_name", "Cluster1"))
	,number_of_daughter_leds(GetParameterValue(params, "daughter_led_count", MxS64CONST(0x0), MxS64CONST(0x0), MxS64CONST(0x20)))
	,number_of_daughter_user_switches(GetParameterValue(params, "daughter_user_switch_count", MxS64CONST(0x0), MxS64CONST(0x0), MxS64CONST(0x20)))


	,cadiParameterProxy_idler_of_GUIPoll_to_VEVisualisation__(0)

{
    // initialize properties__
	properties__["component_name"] = "";
	properties__["component_type"] = "Peripheral";
	properties__["debugger_name"] = "";
	properties__["debugger_start_command"] = "";
	properties__["default_view"] = "auto";
	properties__["description"] = "Display window for VE using Visualisation library.";
	properties__["documentation_file"] = "../../../#DUI0423#";
	properties__["dso_safe"] = "1";
	properties__["executes_software"] = "0";
	properties__["expose_extern_sub_component_cadi"] = "1";
	properties__["factory_namespace"] = "";
	properties__["has_cadi"] = "1";
	properties__["has_implicit_clk_in"] = "1";
	properties__["hidden"] = "0";
	properties__["icon_file"] = "";
	properties__["ip_provider"] = "";
	properties__["is_single_stepped"] = "0";
	properties__["license_feature"] = "";
	properties__["loadfile_extension"] = "";
	properties__["save_restore"] = "0";
	properties__["small_icon_file"] = "";
	properties__["variant"] = "";
	properties__["version"] = "8.1.37";

    // initialize parameter info
    {
        sg::ComponentFactory *factory = VEVisualisation_GetFactory();

        sg::TargetInfo *targetInfo = factory->getTargetInfo(""); // empty string means 'this' component

        if(targetInfo) // if we have no target info we also have no parameters towards CADI interfaces
        {
            // get parameter infos
            for(unsigned int i = 0; i < targetInfo->parameter_count; i++)
            {
                parameterId2parameterName__[targetInfo->parameter_info[i].id] = targetInfo->parameter_info[i].name;
                parameterInfos__.push_back((targetInfo->parameter_info)[i]);
            }
        }

        factory->dereference();
    }

    // create subcomponents
	{
		sg::ComponentFactory *ClockTimer_factory = ClockTimer_GetFactory();
		sg::ComponentFactory *GUIPoll_factory = GUIPoll_GetFactory();
		sg::ComponentFactory *VisEventRecorder_factory = VisEventRecorder_GetFactory();
		{
			sg::Params params_idler__ = params.getParamsFor("idler");
			params_idler__["delay_ms"] = MxU64CONST(0x0000000000000014);
			add(idler = GUIPoll_factory->instantiate("idler", simulationContext, params_idler__));
		}
		{
			sg::Params params_timer__ = params.getParamsFor("timer");
			add(timer = ClockTimer_factory->instantiate("timer", simulationContext, params_timer__));
		}
		{
			sg::Params params_recorder__ = params.getParamsFor("recorder");
			recorder = dynamic_cast<Component__VisEventRecorder*>(VisEventRecorder_factory->instantiate("recorder", simulationContext, params_recorder__));
			assert(recorder);
			add(recorder);
		}
		ClockTimer_factory->dereference();
		GUIPoll_factory->dereference();
		VisEventRecorder_factory->dereference();
	}


    // bind local behaviors to this->control_port
    bind_method(control_port, configure, &Component__VEVisualisation::control_port__configure, this);
    bind_method(control_port, init, &Component__VEVisualisation::init, this);
    bind_method(control_port, interconnect, &Component__VEVisualisation::interconnect, this);
//  bind_method(control_port, postConnect, &Component__VEVisualisation::postConnect, this);
    bind_method(control_port, reset, &Component__VEVisualisation::control_port__reset, this);
    bind_method(control_port, loadApplicationFile, &Component__VEVisualisation::loadApplicationFile, this);
    bind_method(control_port, disconnect, &Component__VEVisualisation::disconnect, this);
    bind_method(control_port, terminate, &Component__VEVisualisation::control_port__terminate, this);
    bind_method(control_port, populateCADIMap, &Component__VEVisualisation::control_port__populateCADIMap, this);
//  bind_method(control_port, refresh, &Component__VEVisualisation::refresh, this);
    bind_method(control_port, step, &Component__VEVisualisation::step, this);
    bind_method(control_port, update, &Component__VEVisualisation::update, this);
    bind_method(control_port, communicate, &Component__VEVisualisation::communicate, this);
    bind_method(control_port, getProperty, &Component__VEVisualisation::control_port__getProperty, this);
    bind_method(control_port, traceEndOfCycle, &Component__VEVisualisation::traceEndOfCycle, this);
    bind_method(control_port, bypass, &Component__VEVisualisation::control_port__bypass, this);
    bind_method(control_port, run, &Component__VEVisualisation::control_port__run, this);
    bind_method(control_port, stop, &Component__VEVisualisation::control_port__stop, this);
    bind_method(control_port, idle, &Component__VEVisualisation::control_port__idle, this);
    bind_method(control_port, quit, &Component__VEVisualisation::control_port__quit, this);
    bind_method(control_port, setSimulationEngine, &Component__VEVisualisation::control_port__setSimulationEngine, this);
    bind_method(control_port, message, &Component__VEVisualisation::control_port__message, this);
    bind_method(control_port, callSimEngine, &Component__VEVisualisation::control_port__callSimEngine, this);

    // avoid the automatic calling of the methods through the framework
    control_port.configure.setLocalOnly(true);
    control_port.init.setLocalOnly(true);
    control_port.interconnect.setLocalOnly(true);
//  control_port.postConnect.setLocalOnly(true);
    control_port.reset.setLocalOnly(true);
    control_port.loadApplicationFile.setLocalOnly(true);
    control_port.disconnect.setLocalOnly(true);
    control_port.terminate.setLocalOnly(true);
    control_port.save.setLocalOnly(true);
    control_port.restore.setLocalOnly(true);
    control_port.populateCADIMap.setLocalOnly(true);
//  control_port.refresh.setLocalOnly(true);
    control_port.step.setLocalOnly(true);
    control_port.update.setLocalOnly(true);
    control_port.communicate.setLocalOnly(true);
    control_port.getProperty.setLocalOnly(true);
    control_port.traceEndOfCycle.setLocalOnly(true);
//  control_port.bypass.setLocalOnly(true);
//  control_port.run.setLocalOnly(true);
//  control_port.stop.setLocalOnly(true);
//  control_port.idle.setLocalOnly(true); // broadcast ports don't have setLocalOnly
//  control_port.quit.setLocalOnly(true);
//  control_port.setSimulationEngine.setLocalOnly(true);

    // bind cadiPort behaviors
    bind_method(cadiPort__, GetParameters, &Component__VEVisualisation::cadiPort__GetParameters, this);
    bind_method(cadiPort__, GetParameterInfo, &Component__VEVisualisation::cadiPort__GetParameterInfo, this);
    bind_method(cadiPort__, GetProperty, &Component__VEVisualisation::cadiPort__GetProperty, this);
    bind_method(cadiPort__, LoadApplicationFile, &Component__VEVisualisation::cadiPort__LoadApplicationFile, this);
    bind_method(cadiPort__, GetApplicationsAndCommandLineParams, &Component__VEVisualisation::cadiPort__GetApplicationsAndCommandLineParams, this);

    // connect control ports for subcomponents to subcomponents
	controlPort_idler__.connectTo(idler->findPort("$control"));
	controlPort_timer__.connectTo(timer->findPort("$control"));
	controlPort_recorder__.connectTo(recorder->findPort("$control"));



    // resource initialization code
    reset_resources__();

    // bind behaviors to abstract ports
	bind_method(timer_callback_handler, signal, &Component__VEVisualisation::abstract_port__timer_callback_handler__signal, this);
	bind_method(gui_callback, gui_callback, &Component__VEVisualisation::abstract_port__gui_callback__gui_callback, this);
	bind_method(lcd, lock, &Component__VEVisualisation::abstract_port__lcd__lock, this);
	bind_method(lcd, unlock, &Component__VEVisualisation::abstract_port__lcd__unlock, this);
	bind_method(lcd, update, &Component__VEVisualisation::abstract_port__lcd__update, this);
	bind_method(lcd, setPreferredLayout, &Component__VEVisualisation::abstract_port__lcd__setPreferredLayout, this);
	bind_method(daughter_leds, setValue, &Component__VEVisualisation::abstract_port__daughter_leds__setValue, this);
	bind_method(daughter_leds, getValue, &Component__VEVisualisation::abstract_port__daughter_leds__getValue, this);
	bind_method(daughter_user_switches, setValue, &Component__VEVisualisation::abstract_port__daughter_user_switches__setValue, this);
	bind_method(daughter_user_switches, getValue, &Component__VEVisualisation::abstract_port__daughter_user_switches__getValue, this);
	bind_method(recorderControl, processEvents, &Component__VEVisualisation::abstract_port__recorderControl__processEvents, this);


    // add abstract ports
	timer_callback_handler.SetName__("timer_callback_handler");
	publishSlavePort("clock_50Hz", clock_50Hz);
	clock_50Hz.SetName__("clock_50Hz");
	publishMasterPort("touch_screen", touch_screen);
	touch_screen.SetName__("touch_screen");
	publishMasterPort("lcd_layout", lcd_layout);
	lcd_layout.SetName__("lcd_layout");
	gui_callback.SetName__("gui_callback");
	publishSlavePort("lcd", lcd);
	lcd.SetName__("lcd");
	publishSlavePortArray("cluster0_ticks", cluster0_ticks, 4);
	{for(int i = 0; i < 4; ++i) cluster0_ticks[i].SetName__("cluster0_ticks");}
	publishSlavePortArray("cluster1_ticks", cluster1_ticks, 4);
	{for(int i = 0; i < 4; ++i) cluster1_ticks[i].SetName__("cluster1_ticks");}
	publishSlavePort("leds", leds);
	leds.SetName__("leds");
	publishSlavePort("daughter_leds", daughter_leds);
	daughter_leds.SetName__("daughter_leds");
	publishSlavePort("daughter_user_switches", daughter_user_switches);
	daughter_user_switches.SetName__("daughter_user_switches");
	publishSlavePort("user_switches", user_switches);
	user_switches.SetName__("user_switches");
	publishSlavePort("boot_switch", boot_switch);
	boot_switch.SetName__("boot_switch");
	publishMasterPort("keyboard", keyboard);
	keyboard.SetName__("keyboard");
	publishMasterPort("mouse", mouse);
	mouse.SetName__("mouse");
	recorderControl.SetName__("recorderControl");
	__VEVisualisation_internal_1.SetName__("__VEVisualisation_internal_1");


    // wire up static connection map
	idler->findPort("gui_callback").connectTo(gui_callback);
	clock_50Hz.connectTo(timer->findPort("clk_in"));
	timer->findPort("timer_callback").connectTo(timer_callback_handler);
	recorderControl.connectTo(recorder->findPort("control"));
	cluster0_ticks[0].connectTo(recorder->findPort("ticks"));
	__VEVisualisation_internal_1.connectTo(timer->findPort("timer_control"));


    // init profiling

    // init resources


    // run the parameter write access functions for all of the component's parameters
    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        std::string paramName = parameterInfos__[i].name;

        switch (parameterInfos__[i].dataType)
        {
        case eslapi::CADI_PARAM_STRING:
            {
                std::string data = GetParameterValue(params, paramName, parameterInfos__[i].defaultString);
                parameter_write_string_func(paramNameToParamAccessFuncID(paramName), data);
            }
            break;
        case eslapi::CADI_PARAM_BOOL:
        case eslapi::CADI_PARAM_INT:
            {
                int64_t data = GetParameterValue(params, paramName, parameterInfos__[i].defaultValue, parameterInfos__[i].minValue, parameterInfos__[i].maxValue);
                parameter_write_func(paramNameToParamAccessFuncID(paramName), &data);
            }
            break;
        default:
            break;
        }
    }
}


Component__VEVisualisation::~Component__VEVisualisation()
{
}

void Component__VEVisualisation::control_port__configure(const sg::Params& params)
{
	if(controlPort_idler__.configure.implemented()) controlPort_idler__.configure(params.getParamsFor("idler"));
	if(controlPort_timer__.configure.implemented()) controlPort_timer__.configure(params.getParamsFor("timer"));
	if(controlPort_recorder__.configure.implemented()) controlPort_recorder__.configure(params.getParamsFor("recorder"));


    assert(simulationContext__->getSimulationEngine());
    cadi__ = new Component__VEVisualisation_CADI(this, simulationContext__->getSimulationEngine());

    // forward certain calls from CADI interface to this component
    cadi__->GetCADIPort().connectTo(cadiPort__);

    

    std::map< std::string, eslapi::CAInterface* > tempMap;
    control_port__populateCADIMap(tempMap, ""); // precompute mxdi map

	cadi__->EnableSubComponentCADIImport();


}

void Component__VEVisualisation::control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* >&output_map, std::string const & base_prefix)
{
    if (componentName2CADI__.empty())
    {
        componentName2CADI__[getName()] = static_cast<eslapi::CADI*>(cadi__);
        std::string prefix = getName() + ".";

		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_idler__.populateCADIMap.implemented())
			{
				controlPort_idler__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
			eslapi::CADI *cadi = obtainCADI__("idler", compMap);
			if (cadi != NULL)
			{
				cadiParameterProxy_idler_of_GUIPoll_to_VEVisualisation__ = new CADIParameterProxy(cadi, &parameterFilter_idler_of_GUIPoll_to_VEVisualisation__);
			}
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_timer__.populateCADIMap.implemented())
			{
				controlPort_timer__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_recorder__.populateCADIMap.implemented())
			{
				controlPort_recorder__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}

    }
    // Copy the local map into the given map with the requested prefix.
    for (std::map<std::string,eslapi::CAInterface*>::iterator it = componentName2CADI__.begin(); it != componentName2CADI__.end(); ++it)
    {
        output_map.insert(std::make_pair(base_prefix + it->first, it->second));
    }
}

eslapi::CADI* Component__VEVisualisation::obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const
{
    std::map< std::string, eslapi::CAInterface* >::const_iterator it = componentName2CADI.find(subcomp);
    if (it != componentName2CADI.end())
    {
        eslapi::CAInterface *cai = it->second;
        if (cai != NULL)
        {
            cai = cai->ObtainInterface(eslapi::CADI::IFNAME(), 0, 0);
            if (cai != NULL)
            {
                return static_cast<eslapi::CADI*>(cai);
            }
        }
    }
    return NULL;
}

void Component__VEVisualisation::insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface* > &componentName2CADI)
{
    for (std::map<std::string, eslapi::CAInterface*>::iterator it = componentName2CADI.begin(); it != componentName2CADI.end(); it++)
    {
        // put prefix in front of all entries
        componentName2CADI__[prefix + it->first] = it->second;
    }
}


std::string Component__VEVisualisation::control_port__getProperty(const std::string& propname)
{
    if(properties__.find(propname) != properties__.end())
    {
        return properties__[propname];
    }
    else
        return ""; // unknown property
}


std::string Component__VEVisualisation::control_port__bypass(const std::string&)
{
    return "";
}


void Component__VEVisualisation::control_port__run()
{
}


void Component__VEVisualisation::control_port__stop()
{
}


void Component__VEVisualisation::control_port__idle()
{
}


void Component__VEVisualisation::control_port__quit()
{
}


void Component__VEVisualisation::control_port__setSimulationEngine(SimulationEngine*)
{
}


void Component__VEVisualisation::control_port__message(const std::string &msg, sg::message::MessageType msgType)
{
}


std::string Component__VEVisualisation::control_port__callSimEngine(const std::string &)
{
    return "";
}


void Component__VEVisualisation::control_port__reset(int level)
{
    // restore the resources' reset values before executing 'reset'
    reset_resources__();
    reset(level);
}


void Component__VEVisualisation::control_port__terminate()
{
    // the CADI was created before 'init', therefore we free it after 'terminate'
    terminate();
    freeCADIResources__();
}


void Component__VEVisualisation::freeCADIResources__()
{
    // free CADI parameter proxies
	delete cadiParameterProxy_idler_of_GUIPoll_to_VEVisualisation__;
	cadiParameterProxy_idler_of_GUIPoll_to_VEVisualisation__ = 0;


    // free CADI interface
    delete cadi__;
    cadi__ = 0;
}


// CADI Port implementations
eslapi::CADIReturn_t Component__VEVisualisation::cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params)
{
    // check arguments
    if(actualNumOfParams == 0)
        return eslapi::CADI_STATUS_IllegalArgument;
    *actualNumOfParams = 0;
    if(params == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    // collect parameters
    size_t i = 0;
    for (; (i < desiredNumOfParams) && ((startIndex + i) < parameterInfos__.size()); ++i)
    {
        params[i] = parameterInfos__[startIndex + i];
    }
    *actualNumOfParams = (MxU32)i;

    return eslapi::CADI_STATUS_OK;
}

eslapi::CADIReturn_t Component__VEVisualisation::cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param)
{
    if(param == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        if (!strcmp(parameterInfos__[i].name, parameterName.c_str()))
        {
            *param = parameterInfos__[i];

            return eslapi::CADI_STATUS_OK;
        }
    }

    return eslapi::CADI_STATUS_GeneralError;
}


bool Component__VEVisualisation::ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy, const char *param_name, int64_t intVal, const char *strVal)
{
    if (!proxy)
        return false;

    // we need the parameter's CADI id in order to create an eslapi::CADIParameterValue_t structure
    // therefore, we first retrieve its eslapi::CADIParameterInfo_t meta-data
    eslapi::CADIParameterInfo_t paramInfo;
    if (proxy->CADIGetParameterInfo(param_name, &paramInfo) != eslapi::CADI_STATUS_OK)
        return false;

    eslapi::CADIParameterValue_t paramVal(paramInfo.id, paramInfo.dataType, intVal, strVal);
    eslapi::CADIFactoryErrorMessage_t error;
    if (proxy->CADISetParameters(1, &paramVal, &error) != eslapi::CADI_STATUS_OK)
        return false;

    return true;
}


sg::accessfunc::AccessFuncResult Component__VEVisualisation::parameter_read_func(uint32_t id, int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_trap_key: *data = trap_key; break;
	case PARAMETER_ID_rate_limit_enable: *data = rate_limit_enable; break;
	case PARAMETER_ID_disable_visualisation: *data = disable_visualisation; break;
	case PARAMETER_ID_number_of_daughter_leds: *data = number_of_daughter_leds; break;
	case PARAMETER_ID_number_of_daughter_user_switches: *data = number_of_daughter_user_switches; break;

        default:
            printf("error: Component__VEVisualisation::parameter_read_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VEVisualisation::parameter_read_string_func(uint32_t id, std::string &data)
{
    switch (id)
    {
	case PARAMETER_ID_window_title:  data = window_title; break;
	case PARAMETER_ID_cpu_name:  data = cpu_name; break;
	case PARAMETER_ID_cluster0_name:  data = cluster0_name; break;
	case PARAMETER_ID_cluster1_name:  data = cluster1_name; break;

        default:
            printf("error: Component__VEVisualisation::parameter_read_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VEVisualisation::parameter_write_func(uint32_t id, const int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_trap_key:
		{
			*(const_cast<uint32_t*>(&trap_key)) = *data;
		}
		break;
	case PARAMETER_ID_rate_limit_enable:
		{
			*(const_cast<bool*>(&rate_limit_enable)) = !!*data;
		}
		break;
	case PARAMETER_ID_disable_visualisation:
		{
			*(const_cast<bool*>(&disable_visualisation)) = !!*data;
		}
		break;
	case PARAMETER_ID_number_of_daughter_leds:
		{
			*(const_cast<uint32_t*>(&number_of_daughter_leds)) = *data;
		}
		break;
	case PARAMETER_ID_number_of_daughter_user_switches:
		{
			*(const_cast<uint32_t*>(&number_of_daughter_user_switches)) = *data;
		}
		break;

        default:
            printf("error: Component__VEVisualisation::parameter_write_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VEVisualisation::parameter_write_string_func(uint32_t id, const std::string &data)
{
    switch (id)
    {
	case PARAMETER_ID_window_title:
		{
			*(const_cast<std::string*>(&window_title)) = data;
		}
		break;
	case PARAMETER_ID_cpu_name:
		{
			*(const_cast<std::string*>(&cpu_name)) = data;
		}
		break;
	case PARAMETER_ID_cluster0_name:
		{
			*(const_cast<std::string*>(&cluster0_name)) = data;
		}
		break;
	case PARAMETER_ID_cluster1_name:
		{
			*(const_cast<std::string*>(&cluster1_name)) = data;
		}
		break;

        default:
            printf("error: Component__VEVisualisation::parameter_write_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

void Component__VEVisualisation::cadiPort__LoadApplicationFile(const std::string& filename)
{
    loadApplicationFile(filename);
    applications2params[filename] = "";
}

void Component__VEVisualisation::cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_)
{
    applications2params_ = applications2params;
}

eslapi::CADIReturn_t Component__VEVisualisation::cadiPort__GetProperty(const std::string& propertyName, std::string &value)
{
    if(properties__.find(propertyName) != properties__.end())
    {
        value = properties__[propertyName];
        return eslapi::CADI_STATUS_OK;
    }
    else
    {
        value = "";
        return eslapi::CADI_STATUS_GeneralError;
    }
}

// functions to stop and lock the simulator
// we only expose the simHalt() function in the documentation for the moment

void Component__VEVisualisation::simHalt()
{
    cadi__->StopSimulation();
}


// start simulation from the inside
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
void Component__VEVisualisation::simRun()
{
    cadi__->CADIExecContinue();
}


// return true if simulation is running
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
bool Component__VEVisualisation::simIsRunning()
{
    uint32_t mode = eslapi::CADI_EXECMODE_Stop;
    cadi__->CADIExecGetMode(&mode);
    return mode != eslapi::CADI_EXECMODE_Stop;
}


void Component__VEVisualisation::simShutdown()
{
    cadiPort__.simShutdown();
}

void Component__VEVisualisation::simReset(uint32_t level)
{
    cadi__->CADIExecReset(level);
}

uint32_t Component__VEVisualisation::paramNameToParamAccessFuncID(const std::string &name)
{
    uint32_t id = 0;
    if (name == "") id = 0xffffffff;
    if (name == "trap_key") id = PARAMETER_ID_trap_key;
    if (name == "rate_limit-enable") id = PARAMETER_ID_rate_limit_enable;
    if (name == "disable_visualisation") id = PARAMETER_ID_disable_visualisation;
    if (name == "window_title") id = PARAMETER_ID_window_title;
    if (name == "cpu_name") id = PARAMETER_ID_cpu_name;
    if (name == "cluster0_name") id = PARAMETER_ID_cluster0_name;
    if (name == "cluster1_name") id = PARAMETER_ID_cluster1_name;
    if (name == "daughter_led_count") id = PARAMETER_ID_number_of_daughter_leds;
    if (name == "daughter_user_switch_count") id = PARAMETER_ID_number_of_daughter_user_switches;

    return id;
}

void Component__VEVisualisation::reset_resources__()
{
    // resource initialization code

}


} // FVP_VE_Cortex_A15x1_NMS
#line 146 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::init()
{
 {if(!controlPort_playbackTimer__.init.empty()) controlPort_playbackTimer__.init();if(!controlPort_playbackDivider__.init.empty()) controlPort_playbackDivider__.init();if(!controlPort_recordingTimer__.init.empty()) controlPort_recordingTimer__.init();if(!controlPort_recordingDivider__.init.empty()) controlPort_recordingDivider__.init();if(!controlPort_masterClock__.init.empty()) controlPort_masterClock__.init();};
 
 
 
 timerTop = 0x40000000; 
 initRecording();
 name2region["NULL"] = 0;
 region2name[0] = "NULL";
 diffMessageThresholdLower = -INITIAL_DIFF_MESSAGE_THRESHOLD;
 diffMessageThresholdUpper = +INITIAL_DIFF_MESSAGE_THRESHOLD;
 
}
}

#line 160 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::reset(int level)
{
 {if(!controlPort_playbackTimer__.reset.empty()) controlPort_playbackTimer__.reset(level);if(!controlPort_playbackDivider__.reset.empty()) controlPort_playbackDivider__.reset(level);if(!controlPort_recordingTimer__.reset.empty()) controlPort_recordingTimer__.reset(level);if(!controlPort_recordingDivider__.reset.empty()) controlPort_recordingDivider__.reset(level);if(!controlPort_masterClock__.reset.empty()) controlPort_masterClock__.reset(level);};
 initPlayback(); 

 
 if (recordingEnabled)
 __VisEventRecorder_internal_1.set(timerTop);
 
 
 if (playbackEnabled) { 
 uint32_t delay = getNextPlaybackTimerInterval();
 if ((delay == 0) && playbackEnabled)
 delay = playbackTimerCallback.signal();
 if (delay && playbackEnabled)
 {
 if (verbose >= 2)
 message(sg::message::MSG_INFO, "%s: starting playback timer (interval=%u)\n", getInstanceName().c_str(), delay);
 __VisEventRecorder_internal_2.set(delay);
 }
 }
 
}
}

#line 183 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::terminate()
{
 {if(!controlPort_playbackTimer__.terminate.empty()) controlPort_playbackTimer__.terminate();if(!controlPort_playbackDivider__.terminate.empty()) controlPort_playbackDivider__.terminate();if(!controlPort_recordingTimer__.terminate.empty()) controlPort_recordingTimer__.terminate();if(!controlPort_recordingDivider__.terminate.empty()) controlPort_recordingDivider__.terminate();if(!controlPort_masterClock__.terminate.empty()) controlPort_masterClock__.terminate();};
 
 if (recordingEnabled)
 {
 uint64_t currentTime = getCurrentRecordingTime();
 char buf[4096];
 snprintf(buf, sizeof(buf), "Z %10"PRIu64" # simulation terminated\n", currentTime);
 appendToFile(recordingFileName.c_str(), buf);
 }
 
}
}

#line 297 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { std::string 
Component__VisEventRecorder::formatEventRecord(uint64_t time, uint64_t instructionCount, const VisEvent* event, const char* lineEnd)
{
 
 const char *typeStr = getTypeStr(unsigned(event->type));
 if (!typeStr)
 {
 message(sg::message::MSG_ERROR, "%s: formatEventRecord(): unknown type %d\n", getInstanceName().c_str(), int(event->type));
 typeStr = getTypeStr(0);
 }
 
 
 const char *regionStr = "NULL";
 std::map<VisRegion*, std::string>::const_iterator i = region2name.find(event->region);
 if (i != region2name.end())
 regionStr = i->second.c_str();
 
 
 char buf[4096];
 snprintf(buf, sizeof(buf), "E %10"PRIu64" %10"PRIu64" %-15s 0x%02x %4d %4d %4d %4d %d %s%s",
 time, instructionCount, typeStr, event->keysym, event->rel_x, event->rel_y, event->abs_x, event->abs_y, event->button, regionStr, lineEnd);
 return buf;
 
}
}

#line 321 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { const char* 
Component__VisEventRecorder::getTypeStr(unsigned type)
{
 static const char *type2str[] = {"None", "KEYDOWN", "KEYUP", "MOUSEBUTTONDOWN", "MOUSEBUTTONUP", "MOUSEMOTION", "QUIT"};
 if (type >= (sizeof(type2str) / sizeof(type2str[0])))
 return 0;
 return type2str[type];
 
}
}

#line 330 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { VisEvent::VisEventType 
Component__VisEventRecorder::getEventType(const char* fileName, int linenr, const char* str)
{
 for (int type = 0;; type++)
 {
 const char *typeStr = getTypeStr(type);
 if (typeStr == 0)
 break;
 if (strcmp(str, typeStr) == 0)
 return (VisEvent::VisEventType)type;
 }
 message(sg::message::MSG_ERROR, "%s:%d: unknown event type '%s' in E record\n", fileName, linenr, str);
 return VisEvent::None; 
 
}
}

#line 345 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::appendToFile(const char* fileName, const char* str)
{
 writeToFile(fileName, str, "ab");
 
}
}

#line 351 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::writeToFile(const char* fileName, const char* str, const char* mode)
{
 
 
 
 FILE *f = fopen(fileName, mode);
 if (f == 0)
 {
 message(sg::message::MSG_ERROR, "%s: appendToFile(): error while opening file '%s' for mode '%s', disabling recording\n",
 getInstanceName().c_str(), fileName, mode);
 recordingEnabled = false; 
 return;
 }
 fputs(str, f);
 fclose(f);
 if (verbose)
 message(sg::message::MSG_INFO, "%s: REC: %s", getInstanceName().c_str(), str); 
 
}
}

#line 371 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint64_t 
Component__VisEventRecorder::getCurrentRecordingTime()
{
 uint32_t timeLow = timerTop - __VisEventRecorder_internal_1.remaining();
 
 
 
 if (timeLow)
 timeLow--;
 uint64_t time = currentRecordingTimeHigh + timeLow;
 if (time < currentRecordingTime)
 message(sg::message::MSG_ERROR, "%s: reverse timeflow: %"PRIu64" < %"PRIu64" (but should be >=)\n",
 getInstanceName().c_str(), time, currentRecordingTime);
 currentRecordingTime = time;
 return currentRecordingTime;
 
}
}

#line 388 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::initRecording()
{
 currentRecordingTimeHigh = 0;
 currentRecordingTime = 0;
 recordingEnabled = !recordingFileName.empty();
 if (!recordingEnabled)
 return;
 message(sg::message::MSG_INFO, "%s: recording to file '%s' enabled\n", getInstanceName().c_str(), recordingFileName.c_str());
 writeToFile(recordingFileName.c_str(), "# This is a VisEventRecording recording file. See VisEventRecorder.lisa for details. This line is a comment. Feel free to edit this file.\n", "wb");
 appendToFile(recordingFileName.c_str(), "# E record: E eventType, keysym, rel_x, rel_y, abs_x, abs_y, button, region_name\n");
 char buf[4096];
 time_t dateTmp = 0;
 time(&dateTmp);
 const char *dateStr = ctime(&dateTmp);
 int dateLen = (int)strlen(dateStr) - 1; 
 if (dateLen < 0)
 dateLen = 0;
 uint32_t version = 0;
 snprintf(buf, sizeof(buf), "H 0x%08x, %s, %*.*s, %s # version, instance, date, original_filename\n", version, getInstancePath().c_str(), dateLen, dateLen, dateStr, recordingFileName.c_str());
 appendToFile(recordingFileName.c_str(), buf);
 snprintf(buf, sizeof(buf), "T %"PRIu64" # timebase 1/N seconds for 1Hz master clock\n", recordingTimeBase);
 appendToFile(recordingFileName.c_str(), buf);
 
}
}

#line 413 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::initPlayback()
{
 playbackEnabled = !playbackFileName.empty();
 if (!playbackEnabled)
 return;
 message(sg::message::MSG_INFO, "%s: playback from file '%s' enabled\n", getInstanceName().c_str(), playbackFileName.c_str());
 playbackPC = 0;
 playbackCurrentTimeStamp = 0;
 playbackNextTimeStamp = 0;
 playbackLongWait = 0;
 
 
 FILE *f = fopen(playbackFileName.c_str(), "rb");
 if (f == 0)
 {
 message(sg::message::MSG_ERROR, "%s: initPlayback(): error while opening file '%s' for reading, disabling playback\n",
 getInstanceName().c_str(), playbackFileName.c_str());
 playbackEnabled = false; 
 return;
 }
 char buf[4096];
 int linenr = 0;
 for (;;)
 {
 
 linenr++;
 buf[0] = 0;
 if (fgets(buf, sizeof(buf), f) == 0)
 break;
 buf[sizeof(buf) - 1] = 0; 
 
 
 char *p = buf;
 while((*p != '#') && (*p != '\n') && (*p != 0))
 p++;
 *p = 0;
 
 
 while((p > buf) && isspace((unsigned int)p[-1]))
 p--;
 *p = 0;

 
 p = buf;
 while(isspace((unsigned int)(*p)))
 p++;
 
 
 switch(*p)
 {
 case 'E':
 parseAndAppendEventRecord(playbackFileName.c_str(), linenr, p + 1);
 break;
 case 'T':
 parseTimeBaseRecord(playbackFileName.c_str(), linenr, p + 1);
 break; 
 case 'Z':
 
 break;
 case 'H':
 
 break; 
 case 0:
 
 break;
 default:
 {
 char type = *p;
 if (!isprint(*p))
 type = '?';
 message(sg::message::MSG_ERROR, "%s:%d: unknown '%c'-record (ASCII 0x%02X) in VisEventRecorder recording file (see VisEventRecord.lisa for details)\n",
 playbackFileName.c_str(), linenr, type, type);
 }
 break;
 } 
 }
 fclose(f);
 
 
 if (verbose >= 2)
 {
 for (size_t i = 0; i < playbackData.size(); i++)
 {
 message(sg::message::MSG_INFO, "%s: PLAYINIT[%3d]: %s\n", 
 getInstanceName().c_str(), (int)i, formatEventRecord(playbackData[i].time, playbackData[i].instructionCount, &playbackData[i].visEvent, "").c_str());
 }
 }
 
}
}

#line 503 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::parseAndAppendEventRecord(const char* fileName, int linenr, const char* str)
{
 Event event;
 memset(&event, 0, sizeof(event));
 
 char *p = (char*)str;
 
 
 event.time = strtoull(p, (char**)&p, 0);
 event.instructionCount = strtoull(p, (char**)&p, 0);
 
 
 if (!playbackData.empty())
 {
 if (event.time < playbackData.back().time)
 {
 message(sg::message::MSG_ERROR, "%s:%d: timestamp goes backwards in time in event (E) record '%s'\n",
 fileName, linenr, str);
 }
 }
 
 
 while (isspace((unsigned int)*p))
 p++;
 
 
 const char *eventTypeStr = p;
 while (isalnum((unsigned int)*p))
 p++;
 char saved = *p;
 *p = 0;
 event.visEvent.type = getEventType(fileName, linenr, eventTypeStr);
 *p = saved;

 
 event.visEvent.keysym = strtol(p, (char**)&p, 0);
 event.visEvent.rel_x = strtol(p, (char**)&p, 0);
 event.visEvent.rel_y = strtol(p, (char**)&p, 0);
 event.visEvent.abs_x = strtol(p, (char**)&p, 0);
 event.visEvent.abs_y = strtol(p, (char**)&p, 0);
 event.visEvent.button = strtol(p, (char**)&p, 0);

 
 while (isspace((unsigned int)*p))
 p++;

 
 const char *regionNameStart = p;
 while (isalnum((unsigned int)*p) || (*p == '_'))
 p++;
 
 
 if ((*p != 0) || (p == regionNameStart))
 {
 message(sg::message::MSG_ERROR, "%s:%d: syntax error in event (E) record '%s'\n",
 fileName, linenr, str);
 return;
 }
 saved = *p;
 *p = 0;
 std::string regionName = regionNameStart;
 *p = saved;

 
 std::map<std::string, VisRegion*>::const_iterator i = name2region.find(regionName);
 if (i != name2region.end()) {
 event.visEvent.region = i->second;
 }
 else {
 message(sg::message::MSG_ERROR, "%s:%d: unknown region name '%s' in E record\n",
 fileName, linenr, regionName.c_str());
 } 
 
 
 playbackData.push_back(event);
 
}
}

#line 581 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::parseTimeBaseRecord(const char* fileName, int linenr, const char* str)
{
 const char *p = str;
 uint32_t playbackTimeBase = strtoul(p, (char**)&p, 0); 
 if (*p != 0)
 {
 message(sg::message::MSG_ERROR, "%s:%d: syntax error in time base (T) record '%s'\n",
 fileName, linenr, str);
 return;
 }
 __VisEventRecorder_internal_3.set(playbackTimeBase, 1);
 if (verbose)
 message(sg::message::MSG_INFO, "%s:%d: setting playback time base to %u\n",
 fileName, linenr, playbackTimeBase);
 
}
}

#line 598 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VisEventRecorder::getNextPlaybackTimerInterval()
{
 if (playbackPC >= playbackData.size())
 {
 playbackEnabled = false;
 return 0;
 }
 uint64_t currentTime = playbackNextTimeStamp;
 playbackNextTimeStamp = playbackData[playbackPC].time;
 uint64_t delta = playbackNextTimeStamp - currentTime;
 if (delta > timerTop) {
 playbackLongWait = delta - timerTop;
 delta = timerTop;
 }
 else {
 playbackLongWait = 0;
 }
 return (uint32_t)delta;
 
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::interconnect()
{{if(!controlPort_playbackTimer__.interconnect.empty()) controlPort_playbackTimer__.interconnect();if(!controlPort_playbackDivider__.interconnect.empty()) controlPort_playbackDivider__.interconnect();if(!controlPort_recordingTimer__.interconnect.empty()) controlPort_recordingTimer__.interconnect();if(!controlPort_recordingDivider__.interconnect.empty()) controlPort_recordingDivider__.interconnect();if(!controlPort_masterClock__.interconnect.empty()) controlPort_masterClock__.interconnect();};
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::disconnect()
{{if(!controlPort_playbackTimer__.disconnect.empty()) controlPort_playbackTimer__.disconnect();if(!controlPort_playbackDivider__.disconnect.empty()) controlPort_playbackDivider__.disconnect();if(!controlPort_recordingTimer__.disconnect.empty()) controlPort_recordingTimer__.disconnect();if(!controlPort_recordingDivider__.disconnect.empty()) controlPort_recordingDivider__.disconnect();if(!controlPort_masterClock__.disconnect.empty()) controlPort_masterClock__.disconnect();};
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::update()
{{if(!controlPort_playbackTimer__.update.empty()) controlPort_playbackTimer__.update();if(!controlPort_playbackDivider__.update.empty()) controlPort_playbackDivider__.update();if(!controlPort_recordingTimer__.update.empty()) controlPort_recordingTimer__.update();if(!controlPort_recordingDivider__.update.empty()) controlPort_recordingDivider__.update();if(!controlPort_masterClock__.update.empty()) controlPort_masterClock__.update();};
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::communicate()
{{if(!controlPort_playbackTimer__.communicate.empty()) controlPort_playbackTimer__.communicate();if(!controlPort_playbackDivider__.communicate.empty()) controlPort_playbackDivider__.communicate();if(!controlPort_recordingTimer__.communicate.empty()) controlPort_recordingTimer__.communicate();if(!controlPort_recordingDivider__.communicate.empty()) controlPort_recordingDivider__.communicate();if(!controlPort_masterClock__.communicate.empty()) controlPort_masterClock__.communicate();};
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::traceEndOfCycle()
{{if(!controlPort_playbackTimer__.traceEndOfCycle.empty()) controlPort_playbackTimer__.traceEndOfCycle();if(!controlPort_playbackDivider__.traceEndOfCycle.empty()) controlPort_playbackDivider__.traceEndOfCycle();if(!controlPort_recordingTimer__.traceEndOfCycle.empty()) controlPort_recordingTimer__.traceEndOfCycle();if(!controlPort_recordingDivider__.traceEndOfCycle.empty()) controlPort_recordingDivider__.traceEndOfCycle();if(!controlPort_masterClock__.traceEndOfCycle.empty()) controlPort_masterClock__.traceEndOfCycle();};
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::loadApplicationFile(const std::string& filename)
{{if(!controlPort_playbackTimer__.loadApplicationFile.empty()) controlPort_playbackTimer__.loadApplicationFile(filename);if(!controlPort_playbackDivider__.loadApplicationFile.empty()) controlPort_playbackDivider__.loadApplicationFile(filename);if(!controlPort_recordingTimer__.loadApplicationFile.empty()) controlPort_recordingTimer__.loadApplicationFile(filename);if(!controlPort_recordingDivider__.loadApplicationFile.empty()) controlPort_recordingDivider__.loadApplicationFile(filename);if(!controlPort_masterClock__.loadApplicationFile.empty()) controlPort_masterClock__.loadApplicationFile(filename);};
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VisEventRecorder::save(MxODataStream& os)
{{if(!controlPort_playbackTimer__.save.empty()) controlPort_playbackTimer__.save(os);if(!controlPort_playbackDivider__.save.empty()) controlPort_playbackDivider__.save(os);if(!controlPort_recordingTimer__.save.empty()) controlPort_recordingTimer__.save(os);if(!controlPort_recordingDivider__.save.empty()) controlPort_recordingDivider__.save(os);if(!controlPort_masterClock__.save.empty()) controlPort_masterClock__.save(os);};return true;
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VisEventRecorder::restore(MxIDataStream& is)
{{if(!controlPort_playbackTimer__.restore.empty()) controlPort_playbackTimer__.restore(is);if(!controlPort_playbackDivider__.restore.empty()) controlPort_playbackDivider__.restore(is);if(!controlPort_recordingTimer__.restore.empty()) controlPort_recordingTimer__.restore(is);if(!controlPort_recordingDivider__.restore.empty()) controlPort_recordingDivider__.restore(is);if(!controlPort_masterClock__.restore.empty()) controlPort_masterClock__.restore(is);};return true;
}
}

#line 58 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::step()
{{if(!controlPort_playbackTimer__.step.empty()) controlPort_playbackTimer__.step();if(!controlPort_playbackDivider__.step.empty()) controlPort_playbackDivider__.step();if(!controlPort_recordingTimer__.step.empty()) controlPort_recordingTimer__.step();if(!controlPort_recordingDivider__.step.empty()) controlPort_recordingDivider__.step();if(!controlPort_masterClock__.step.empty()) controlPort_masterClock__.step();};
}
}

#line 203 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { bool 
Component__VisEventRecorder::abstract_port__control__getEvent(VisEvent* event)
{
 
 memset(event, 0, sizeof(VisEvent));
 if (!playbackEnabled)
 return false;
 if (playbackPC >= playbackData.size())
 return false;
 if (playbackCurrentTimeStamp != playbackData[playbackPC].time)
 return false;
 
 *event = playbackData[playbackPC].visEvent;
 if (verbose)
 message(sg::message::MSG_INFO, "%s: PLAY[%3d]: i=%10"PRIu64" %s\n", 
 getInstanceName().c_str(), playbackPC, ticks.getValue(), formatEventRecord(playbackCurrentTimeStamp, playbackData[playbackPC].instructionCount, event, "").c_str());
 
 if (checkInstructionCount)
 {
 int64_t diff = playbackData[playbackPC].instructionCount - ticks.getValue();
 if ((diff < diffMessageThresholdLower) || (diff > diffMessageThresholdUpper))
 {
 message(sg::message::MSG_INFO, "%s: PLAY[%3d]: recorded/playback instruction counts differ by %"PRId64" instructions: increase recordingTimeBase value and re-record: (i=%10"PRIu64" %s)\n",
 getInstanceName().c_str(), playbackPC, diff, ticks.getValue(),
 formatEventRecord(playbackCurrentTimeStamp, playbackData[playbackPC].instructionCount, event, "").c_str());
 if (diff < diffMessageThresholdLower)
 diffMessageThresholdLower = diff;
 if (diff > diffMessageThresholdUpper)
 diffMessageThresholdUpper = diff;
 }
 }
 playbackPC++;
 return true;
 
}
}

#line 238 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::abstract_port__control__putEvent(const VisEvent* event)
{
 if (!recordingEnabled)
 return;
 if (!event)
 return;
 if (event->type == VisEvent::None) 
 return;
 uint64_t currentTime = getCurrentRecordingTime();
 string eventStr = formatEventRecord(currentTime, ticks.getValue(), event, "\n");
 appendToFile(recordingFileName.c_str(), eventStr.c_str());
 
}
}

#line 252 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { void 
Component__VisEventRecorder::abstract_port__control__registerVisRegion(VisRegion* region, const char* regionName)
{
 name2region[regionName] = region;
 region2name[region] = regionName;
 
}
}

#line 260 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VisEventRecorder::abstract_port__playbackTimerCallback__signal()
{
 
 if (playbackLongWait) {
 uint32_t delay = timerTop;
 if (playbackLongWait < timerTop) 
 delay = uint32_t(playbackLongWait);
 playbackLongWait -= delay;
 if (verbose >= 2)
 message(sg::message::MSG_INFO, "%s: playbackTimerCallback: restarting timer (interval=%u, long wait, no event)\n", getInstanceName().c_str(), delay);
 return delay;
 }
 
 playbackCurrentTimeStamp = playbackNextTimeStamp;
 if (verbose >= 2)
 message(sg::message::MSG_INFO, "%s: playbackTimerCallback: emitting messages for timestamp %"PRIu64"\n", getInstanceName().c_str(), playbackCurrentTimeStamp);
 control.processEvents();
 playbackCurrentTimeStamp = uint64_t(-1);
 uint32_t delay = getNextPlaybackTimerInterval();
 if (verbose >= 2)
 message(sg::message::MSG_INFO, "%s: playbackTimerCallback: restarting timer (interval=%u)\n", getInstanceName().c_str(), delay);
 return delay;
 
}
}

#line 287 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"
namespace FVP_VE_Cortex_A15x1_NMS { uint32_t 
Component__VisEventRecorder::abstract_port__recordingTimerCallback__signal()
{
 
 
 currentRecordingTimeHigh += timerTop;
 return timerTop;
 
}
}

#line 8707 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// ------------------------------------------------------------------------------
// implementation of class Component__VisEventRecorder
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

Component__VisEventRecorder::Component__VisEventRecorder(const char * instName, sg::SimulationContext* simulationContext, const sg::Params & params):
    SystemGenComponent(instName, simulationContext, params)

	,recordingFileName(GetParameterValue(params, "recordingFileName", ""))
	,playbackFileName(GetParameterValue(params, "playbackFileName", ""))
	,recordingTimeBase(GetParameterValue(params, "recordingTimeBase", MxS64CONST(0x5f5e100), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,verbose(GetParameterValue(params, "verbose", MxS64CONST(0x0), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))
	,checkInstructionCount(!!GetParameterValue(params, "checkInstructionCount", MxS64CONST(0x1), MxS64CONST(0x8000000000000000), MxS64CONST(0x7fffffffffffffff)))


	,cadiParameterProxy_playbackDivider_of_ClockDivider_to_VisEventRecorder__(0)
	,cadiParameterProxy_recordingDivider_of_ClockDivider_to_VisEventRecorder__(0)

{
    // initialize properties__
	properties__["component_name"] = "";
	properties__["component_type"] = "Other";
	properties__["debugger_name"] = "";
	properties__["debugger_start_command"] = "";
	properties__["default_view"] = "auto";
	properties__["description"] = "Event recorder component for visualisation component (allows to playback and record interactive GUI sessions).";
	properties__["documentation_file"] = "../Docs/DUI0423O_fast_model_rm.pdf";
	properties__["dso_safe"] = "1";
	properties__["executes_software"] = "0";
	properties__["expose_extern_sub_component_cadi"] = "1";
	properties__["factory_namespace"] = "";
	properties__["has_cadi"] = "1";
	properties__["has_implicit_clk_in"] = "1";
	properties__["hidden"] = "0";
	properties__["icon_file"] = "";
	properties__["ip_provider"] = "";
	properties__["is_single_stepped"] = "0";
	properties__["license_feature"] = "";
	properties__["loadfile_extension"] = "";
	properties__["save_restore"] = "0";
	properties__["small_icon_file"] = "";
	properties__["variant"] = "";
	properties__["version"] = "8.1.37";

    // initialize parameter info
    {
        sg::ComponentFactory *factory = VisEventRecorder_GetFactory();

        sg::TargetInfo *targetInfo = factory->getTargetInfo(""); // empty string means 'this' component

        if(targetInfo) // if we have no target info we also have no parameters towards CADI interfaces
        {
            // get parameter infos
            for(unsigned int i = 0; i < targetInfo->parameter_count; i++)
            {
                parameterId2parameterName__[targetInfo->parameter_info[i].id] = targetInfo->parameter_info[i].name;
                parameterInfos__.push_back((targetInfo->parameter_info)[i]);
            }
        }

        factory->dereference();
    }

    // create subcomponents
	{
		sg::ComponentFactory *ClockDivider_factory = ClockDivider_GetFactory();
		sg::ComponentFactory *ClockTimer_factory = ClockTimer_GetFactory();
		sg::ComponentFactory *MasterClock_factory = MasterClock_GetFactory();
		{
			sg::Params params_playbackTimer__ = params.getParamsFor("playbackTimer");
			add(playbackTimer = ClockTimer_factory->instantiate("playbackTimer", simulationContext, params_playbackTimer__));
		}
		{
			sg::Params params_playbackDivider__ = params.getParamsFor("playbackDivider");
			params_playbackDivider__["mul"] = MxU64CONST(0x0000000000000001);
			add(playbackDivider = ClockDivider_factory->instantiate("playbackDivider", simulationContext, params_playbackDivider__));
		}
		{
			sg::Params params_recordingTimer__ = params.getParamsFor("recordingTimer");
			add(recordingTimer = ClockTimer_factory->instantiate("recordingTimer", simulationContext, params_recordingTimer__));
		}
		{
			sg::Params params_recordingDivider__ = params.getParamsFor("recordingDivider");
			params_recordingDivider__["mul"] = recordingTimeBase;
			add(recordingDivider = ClockDivider_factory->instantiate("recordingDivider", simulationContext, params_recordingDivider__));
		}
		{
			sg::Params params_masterClock__ = params.getParamsFor("masterClock");
			add(masterClock = MasterClock_factory->instantiate("masterClock", simulationContext, params_masterClock__));
		}
		ClockDivider_factory->dereference();
		ClockTimer_factory->dereference();
		MasterClock_factory->dereference();
	}


    // bind local behaviors to this->control_port
    bind_method(control_port, configure, &Component__VisEventRecorder::control_port__configure, this);
    bind_method(control_port, init, &Component__VisEventRecorder::init, this);
    bind_method(control_port, interconnect, &Component__VisEventRecorder::interconnect, this);
//  bind_method(control_port, postConnect, &Component__VisEventRecorder::postConnect, this);
    bind_method(control_port, reset, &Component__VisEventRecorder::control_port__reset, this);
    bind_method(control_port, loadApplicationFile, &Component__VisEventRecorder::loadApplicationFile, this);
    bind_method(control_port, disconnect, &Component__VisEventRecorder::disconnect, this);
    bind_method(control_port, terminate, &Component__VisEventRecorder::control_port__terminate, this);
    bind_method(control_port, populateCADIMap, &Component__VisEventRecorder::control_port__populateCADIMap, this);
//  bind_method(control_port, refresh, &Component__VisEventRecorder::refresh, this);
    bind_method(control_port, step, &Component__VisEventRecorder::step, this);
    bind_method(control_port, update, &Component__VisEventRecorder::update, this);
    bind_method(control_port, communicate, &Component__VisEventRecorder::communicate, this);
    bind_method(control_port, getProperty, &Component__VisEventRecorder::control_port__getProperty, this);
    bind_method(control_port, traceEndOfCycle, &Component__VisEventRecorder::traceEndOfCycle, this);
    bind_method(control_port, bypass, &Component__VisEventRecorder::control_port__bypass, this);
    bind_method(control_port, run, &Component__VisEventRecorder::control_port__run, this);
    bind_method(control_port, stop, &Component__VisEventRecorder::control_port__stop, this);
    bind_method(control_port, idle, &Component__VisEventRecorder::control_port__idle, this);
    bind_method(control_port, quit, &Component__VisEventRecorder::control_port__quit, this);
    bind_method(control_port, setSimulationEngine, &Component__VisEventRecorder::control_port__setSimulationEngine, this);
    bind_method(control_port, message, &Component__VisEventRecorder::control_port__message, this);
    bind_method(control_port, callSimEngine, &Component__VisEventRecorder::control_port__callSimEngine, this);

    // avoid the automatic calling of the methods through the framework
    control_port.configure.setLocalOnly(true);
    control_port.init.setLocalOnly(true);
    control_port.interconnect.setLocalOnly(true);
//  control_port.postConnect.setLocalOnly(true);
    control_port.reset.setLocalOnly(true);
    control_port.loadApplicationFile.setLocalOnly(true);
    control_port.disconnect.setLocalOnly(true);
    control_port.terminate.setLocalOnly(true);
    control_port.save.setLocalOnly(true);
    control_port.restore.setLocalOnly(true);
    control_port.populateCADIMap.setLocalOnly(true);
//  control_port.refresh.setLocalOnly(true);
    control_port.step.setLocalOnly(true);
    control_port.update.setLocalOnly(true);
    control_port.communicate.setLocalOnly(true);
    control_port.getProperty.setLocalOnly(true);
    control_port.traceEndOfCycle.setLocalOnly(true);
//  control_port.bypass.setLocalOnly(true);
//  control_port.run.setLocalOnly(true);
//  control_port.stop.setLocalOnly(true);
//  control_port.idle.setLocalOnly(true); // broadcast ports don't have setLocalOnly
//  control_port.quit.setLocalOnly(true);
//  control_port.setSimulationEngine.setLocalOnly(true);

    // bind cadiPort behaviors
    bind_method(cadiPort__, GetParameters, &Component__VisEventRecorder::cadiPort__GetParameters, this);
    bind_method(cadiPort__, GetParameterInfo, &Component__VisEventRecorder::cadiPort__GetParameterInfo, this);
    bind_method(cadiPort__, GetProperty, &Component__VisEventRecorder::cadiPort__GetProperty, this);
    bind_method(cadiPort__, LoadApplicationFile, &Component__VisEventRecorder::cadiPort__LoadApplicationFile, this);
    bind_method(cadiPort__, GetApplicationsAndCommandLineParams, &Component__VisEventRecorder::cadiPort__GetApplicationsAndCommandLineParams, this);

    // connect control ports for subcomponents to subcomponents
	controlPort_playbackTimer__.connectTo(playbackTimer->findPort("$control"));
	controlPort_playbackDivider__.connectTo(playbackDivider->findPort("$control"));
	controlPort_recordingTimer__.connectTo(recordingTimer->findPort("$control"));
	controlPort_recordingDivider__.connectTo(recordingDivider->findPort("$control"));
	controlPort_masterClock__.connectTo(masterClock->findPort("$control"));



    // resource initialization code
    reset_resources__();

    // bind behaviors to abstract ports
	bind_method(control, getEvent, &Component__VisEventRecorder::abstract_port__control__getEvent, this);
	bind_method(control, putEvent, &Component__VisEventRecorder::abstract_port__control__putEvent, this);
	bind_method(control, registerVisRegion, &Component__VisEventRecorder::abstract_port__control__registerVisRegion, this);
	bind_method(playbackTimerCallback, signal, &Component__VisEventRecorder::abstract_port__playbackTimerCallback__signal, this);
	bind_method(recordingTimerCallback, signal, &Component__VisEventRecorder::abstract_port__recordingTimerCallback__signal, this);


    // add abstract ports
	publishSlavePort("ticks", ticks);
	ticks.SetName__("ticks");
	publishSlavePort("control", control);
	control.SetName__("control");
	playbackTimerCallback.SetName__("playbackTimerCallback");
	recordingTimerCallback.SetName__("recordingTimerCallback");
	__VisEventRecorder_internal_1.SetName__("__VisEventRecorder_internal_1");
	__VisEventRecorder_internal_2.SetName__("__VisEventRecorder_internal_2");
	__VisEventRecorder_internal_3.SetName__("__VisEventRecorder_internal_3");


    // wire up static connection map
	masterClock->findPort("clk_out").connectTo(playbackDivider->findPort("clk_in"));
	playbackDivider->findPort("clk_out").connectTo(playbackTimer->findPort("clk_in"));
	playbackTimer->findPort("timer_callback").connectTo(playbackTimerCallback);
	masterClock->findPort("clk_out").connectTo(recordingDivider->findPort("clk_in"));
	recordingDivider->findPort("clk_out").connectTo(recordingTimer->findPort("clk_in"));
	recordingTimer->findPort("timer_callback").connectTo(recordingTimerCallback);
	__VisEventRecorder_internal_1.connectTo(recordingTimer->findPort("timer_control"));
	__VisEventRecorder_internal_2.connectTo(playbackTimer->findPort("timer_control"));
	__VisEventRecorder_internal_3.connectTo(playbackDivider->findPort("rate"));


    // init profiling

    // init resources


    // run the parameter write access functions for all of the component's parameters
    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        std::string paramName = parameterInfos__[i].name;

        switch (parameterInfos__[i].dataType)
        {
        case eslapi::CADI_PARAM_STRING:
            {
                std::string data = GetParameterValue(params, paramName, parameterInfos__[i].defaultString);
                parameter_write_string_func(paramNameToParamAccessFuncID(paramName), data);
            }
            break;
        case eslapi::CADI_PARAM_BOOL:
        case eslapi::CADI_PARAM_INT:
            {
                int64_t data = GetParameterValue(params, paramName, parameterInfos__[i].defaultValue, parameterInfos__[i].minValue, parameterInfos__[i].maxValue);
                parameter_write_func(paramNameToParamAccessFuncID(paramName), &data);
            }
            break;
        default:
            break;
        }
    }
}


Component__VisEventRecorder::~Component__VisEventRecorder()
{
}

void Component__VisEventRecorder::control_port__configure(const sg::Params& params)
{
	if(controlPort_playbackTimer__.configure.implemented()) controlPort_playbackTimer__.configure(params.getParamsFor("playbackTimer"));
	if(controlPort_playbackDivider__.configure.implemented()) controlPort_playbackDivider__.configure(params.getParamsFor("playbackDivider"));
	if(controlPort_recordingTimer__.configure.implemented()) controlPort_recordingTimer__.configure(params.getParamsFor("recordingTimer"));
	if(controlPort_recordingDivider__.configure.implemented()) controlPort_recordingDivider__.configure(params.getParamsFor("recordingDivider"));
	if(controlPort_masterClock__.configure.implemented()) controlPort_masterClock__.configure(params.getParamsFor("masterClock"));


    assert(simulationContext__->getSimulationEngine());
    cadi__ = new Component__VisEventRecorder_CADI(this, simulationContext__->getSimulationEngine());

    // forward certain calls from CADI interface to this component
    cadi__->GetCADIPort().connectTo(cadiPort__);

    

    std::map< std::string, eslapi::CAInterface* > tempMap;
    control_port__populateCADIMap(tempMap, ""); // precompute mxdi map

	cadi__->EnableSubComponentCADIImport();


}

void Component__VisEventRecorder::control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* >&output_map, std::string const & base_prefix)
{
    if (componentName2CADI__.empty())
    {
        componentName2CADI__[getName()] = static_cast<eslapi::CADI*>(cadi__);
        std::string prefix = getName() + ".";

		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_playbackTimer__.populateCADIMap.implemented())
			{
				controlPort_playbackTimer__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_playbackDivider__.populateCADIMap.implemented())
			{
				controlPort_playbackDivider__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
			eslapi::CADI *cadi = obtainCADI__("playbackDivider", compMap);
			if (cadi != NULL)
			{
				cadiParameterProxy_playbackDivider_of_ClockDivider_to_VisEventRecorder__ = new CADIParameterProxy(cadi, &parameterFilter_playbackDivider_of_ClockDivider_to_VisEventRecorder__);
			}
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_recordingTimer__.populateCADIMap.implemented())
			{
				controlPort_recordingTimer__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_recordingDivider__.populateCADIMap.implemented())
			{
				controlPort_recordingDivider__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
			eslapi::CADI *cadi = obtainCADI__("recordingDivider", compMap);
			if (cadi != NULL)
			{
				cadiParameterProxy_recordingDivider_of_ClockDivider_to_VisEventRecorder__ = new CADIParameterProxy(cadi, &parameterFilter_recordingDivider_of_ClockDivider_to_VisEventRecorder__);
			}
		}
		{
			std::map< std::string, eslapi::CAInterface* > compMap;
			if (controlPort_masterClock__.populateCADIMap.implemented())
			{
				controlPort_masterClock__.populateCADIMap(compMap, "");
			}
			insertCADIMap__(prefix, compMap);
		}

    }
    // Copy the local map into the given map with the requested prefix.
    for (std::map<std::string,eslapi::CAInterface*>::iterator it = componentName2CADI__.begin(); it != componentName2CADI__.end(); ++it)
    {
        output_map.insert(std::make_pair(base_prefix + it->first, it->second));
    }
}

eslapi::CADI* Component__VisEventRecorder::obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const
{
    std::map< std::string, eslapi::CAInterface* >::const_iterator it = componentName2CADI.find(subcomp);
    if (it != componentName2CADI.end())
    {
        eslapi::CAInterface *cai = it->second;
        if (cai != NULL)
        {
            cai = cai->ObtainInterface(eslapi::CADI::IFNAME(), 0, 0);
            if (cai != NULL)
            {
                return static_cast<eslapi::CADI*>(cai);
            }
        }
    }
    return NULL;
}

void Component__VisEventRecorder::insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface* > &componentName2CADI)
{
    for (std::map<std::string, eslapi::CAInterface*>::iterator it = componentName2CADI.begin(); it != componentName2CADI.end(); it++)
    {
        // put prefix in front of all entries
        componentName2CADI__[prefix + it->first] = it->second;
    }
}


std::string Component__VisEventRecorder::control_port__getProperty(const std::string& propname)
{
    if(properties__.find(propname) != properties__.end())
    {
        return properties__[propname];
    }
    else
        return ""; // unknown property
}


std::string Component__VisEventRecorder::control_port__bypass(const std::string&)
{
    return "";
}


void Component__VisEventRecorder::control_port__run()
{
}


void Component__VisEventRecorder::control_port__stop()
{
}


void Component__VisEventRecorder::control_port__idle()
{
}


void Component__VisEventRecorder::control_port__quit()
{
}


void Component__VisEventRecorder::control_port__setSimulationEngine(SimulationEngine*)
{
}


void Component__VisEventRecorder::control_port__message(const std::string &msg, sg::message::MessageType msgType)
{
}


std::string Component__VisEventRecorder::control_port__callSimEngine(const std::string &)
{
    return "";
}


void Component__VisEventRecorder::control_port__reset(int level)
{
    // restore the resources' reset values before executing 'reset'
    reset_resources__();
    reset(level);
}


void Component__VisEventRecorder::control_port__terminate()
{
    // the CADI was created before 'init', therefore we free it after 'terminate'
    terminate();
    freeCADIResources__();
}


void Component__VisEventRecorder::freeCADIResources__()
{
    // free CADI parameter proxies
	delete cadiParameterProxy_playbackDivider_of_ClockDivider_to_VisEventRecorder__;
	cadiParameterProxy_playbackDivider_of_ClockDivider_to_VisEventRecorder__ = 0;
	delete cadiParameterProxy_recordingDivider_of_ClockDivider_to_VisEventRecorder__;
	cadiParameterProxy_recordingDivider_of_ClockDivider_to_VisEventRecorder__ = 0;


    // free CADI interface
    delete cadi__;
    cadi__ = 0;
}


// CADI Port implementations
eslapi::CADIReturn_t Component__VisEventRecorder::cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params)
{
    // check arguments
    if(actualNumOfParams == 0)
        return eslapi::CADI_STATUS_IllegalArgument;
    *actualNumOfParams = 0;
    if(params == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    // collect parameters
    size_t i = 0;
    for (; (i < desiredNumOfParams) && ((startIndex + i) < parameterInfos__.size()); ++i)
    {
        params[i] = parameterInfos__[startIndex + i];
    }
    *actualNumOfParams = (MxU32)i;

    return eslapi::CADI_STATUS_OK;
}

eslapi::CADIReturn_t Component__VisEventRecorder::cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param)
{
    if(param == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    for (size_t i = 0; i < parameterInfos__.size(); ++i)
    {
        if (!strcmp(parameterInfos__[i].name, parameterName.c_str()))
        {
            *param = parameterInfos__[i];

            return eslapi::CADI_STATUS_OK;
        }
    }

    return eslapi::CADI_STATUS_GeneralError;
}


bool Component__VisEventRecorder::ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy, const char *param_name, int64_t intVal, const char *strVal)
{
    if (!proxy)
        return false;

    // we need the parameter's CADI id in order to create an eslapi::CADIParameterValue_t structure
    // therefore, we first retrieve its eslapi::CADIParameterInfo_t meta-data
    eslapi::CADIParameterInfo_t paramInfo;
    if (proxy->CADIGetParameterInfo(param_name, &paramInfo) != eslapi::CADI_STATUS_OK)
        return false;

    eslapi::CADIParameterValue_t paramVal(paramInfo.id, paramInfo.dataType, intVal, strVal);
    eslapi::CADIFactoryErrorMessage_t error;
    if (proxy->CADISetParameters(1, &paramVal, &error) != eslapi::CADI_STATUS_OK)
        return false;

    return true;
}


sg::accessfunc::AccessFuncResult Component__VisEventRecorder::parameter_read_func(uint32_t id, int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_recordingTimeBase: *data = recordingTimeBase; break;
	case PARAMETER_ID_verbose: *data = verbose; break;
	case PARAMETER_ID_checkInstructionCount: *data = checkInstructionCount; break;

        default:
            printf("error: Component__VisEventRecorder::parameter_read_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VisEventRecorder::parameter_read_string_func(uint32_t id, std::string &data)
{
    switch (id)
    {
	case PARAMETER_ID_recordingFileName:  data = recordingFileName; break;
	case PARAMETER_ID_playbackFileName:  data = playbackFileName; break;

        default:
            printf("error: Component__VisEventRecorder::parameter_read_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VisEventRecorder::parameter_write_func(uint32_t id, const int64_t *data)
{
    if (data == 0)
        return eslapi::CADI_STATUS_IllegalArgument;

    switch (id)
    {
	case PARAMETER_ID_recordingTimeBase:
		{
			*(const_cast<uint64_t*>(&recordingTimeBase)) = *data;
		}
		break;
	case PARAMETER_ID_verbose:
		{
			verbose = *data;
		}
		break;
	case PARAMETER_ID_checkInstructionCount:
		{
			checkInstructionCount = !!*data;
		}
		break;

        default:
            printf("error: Component__VisEventRecorder::parameter_write_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

sg::accessfunc::AccessFuncResult Component__VisEventRecorder::parameter_write_string_func(uint32_t id, const std::string &data)
{
    switch (id)
    {
	case PARAMETER_ID_recordingFileName:
		{
			*(const_cast<std::string*>(&recordingFileName)) = data;
		}
		break;
	case PARAMETER_ID_playbackFileName:
		{
			*(const_cast<std::string*>(&playbackFileName)) = data;
		}
		break;

        default:
            printf("error: Component__VisEventRecorder::parameter_write_string_func: undefined parameter id '0x%08x'\n", id);
            return sg::accessfunc::ACCESS_FUNC_GeneralError;
    }

    return sg::accessfunc::ACCESS_FUNC_OK;
}

void Component__VisEventRecorder::cadiPort__LoadApplicationFile(const std::string& filename)
{
    loadApplicationFile(filename);
    applications2params[filename] = "";
}

void Component__VisEventRecorder::cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_)
{
    applications2params_ = applications2params;
}

eslapi::CADIReturn_t Component__VisEventRecorder::cadiPort__GetProperty(const std::string& propertyName, std::string &value)
{
    if(properties__.find(propertyName) != properties__.end())
    {
        value = properties__[propertyName];
        return eslapi::CADI_STATUS_OK;
    }
    else
    {
        value = "";
        return eslapi::CADI_STATUS_GeneralError;
    }
}

// functions to stop and lock the simulator
// we only expose the simHalt() function in the documentation for the moment

void Component__VisEventRecorder::simHalt()
{
    cadi__->StopSimulation();
}


// start simulation from the inside
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
void Component__VisEventRecorder::simRun()
{
    cadi__->CADIExecContinue();
}


// return true if simulation is running
// (useful from visualisation components which can execute code while the
// simulation is stopped, like key events)
bool Component__VisEventRecorder::simIsRunning()
{
    uint32_t mode = eslapi::CADI_EXECMODE_Stop;
    cadi__->CADIExecGetMode(&mode);
    return mode != eslapi::CADI_EXECMODE_Stop;
}


void Component__VisEventRecorder::simShutdown()
{
    cadiPort__.simShutdown();
}

void Component__VisEventRecorder::simReset(uint32_t level)
{
    cadi__->CADIExecReset(level);
}

uint32_t Component__VisEventRecorder::paramNameToParamAccessFuncID(const std::string &name)
{
    uint32_t id = 0;
    if (name == "") id = 0xffffffff;
    if (name == "recordingFileName") id = PARAMETER_ID_recordingFileName;
    if (name == "playbackFileName") id = PARAMETER_ID_playbackFileName;
    if (name == "recordingTimeBase") id = PARAMETER_ID_recordingTimeBase;
    if (name == "verbose") id = PARAMETER_ID_verbose;
    if (name == "checkInstructionCount") id = PARAMETER_ID_checkInstructionCount;

    return id;
}

void Component__VisEventRecorder::reset_resources__()
{
    // resource initialization code

}


} // FVP_VE_Cortex_A15x1_NMS

#line 9380 "./Linux64-Release-GCC-4.4/gen/Comp_2.cpp"

// This is an anonymous namespace, it effectively declares everything inside it as 'static', e.g. only visible within the .o file it is compiled into
//     without this we get link errors when linking together LISA generated components
namespace
{

class ComponentFactoryBase :
    public sg::BasicComponentFactory
{
protected:
    void publishSubComponent(sg::ComponentFactory *factory,
                             const std::string &prefix,
                             bool publish_all,
                             const ParameterFilter &param_filter);
};

void
ComponentFactoryBase::publishSubComponent(sg::ComponentFactory *factory,
                                          const std::string &prefix,
                                          bool publish_all,
                                          const ParameterFilter &param_filter)
{
    using namespace sg;

    if (param_filter.isEmpty())
    {
        BasicComponentFactory::publishComponent(factory, prefix, publish_all);
    }
    else
    {
        for (unsigned int t = 0; t < factory->getTargetCount(); ++t)
        {
            TargetInfo *info = factory->getTargetInfo(t);

            std::vector<eslapi::CADIParameterInfo_t> my_param_infos;

            param_filter.filter(info->parameter_info, info->parameter_count, info->instance_path, my_param_infos);

            TargetInfo *my_target_info = new TargetInfo;

                        eslapi::CADITargetInfo_t *my_cadi_target_info = new eslapi::CADITargetInfo_t;
                        *my_cadi_target_info = *(info->cadi_target_info); // copy CADI target info
            my_cadi_target_info->numberOfParameters = (uint32_t)my_param_infos.size();
            my_target_info->cadi_target_info = my_cadi_target_info;

            my_target_info->parameter_count = (unsigned)my_param_infos.size();

            // only copy parameters, if there are ones
                        if (my_target_info->parameter_count)
                        {
                                my_target_info->parameter_info = new eslapi::CADIParameterInfo_t[my_target_info->parameter_count];
                                memcpy(const_cast<eslapi::CADIParameterInfo_t *>(my_target_info->parameter_info),
                                           &my_param_infos.front(),
                                           sizeof(eslapi::CADIParameterInfo_t) * my_target_info->parameter_count);
                        }

            my_target_info->instance_path = info->instance_path;

            // Skip any targets that have an instance_path of "".
            if (my_target_info->instance_path.length() > 0)
            {
                // Add the prefix at the start of the instance path.
                std::string new_path = prefix + "." + my_target_info->instance_path;
                publishTarget(*my_target_info, new_path);
            }
            else if (publish_all)
            {
                std::string new_path = prefix;
                publishTarget(*my_target_info, new_path);
            }
            delete my_target_info;
        }
    }
}

}

using namespace FVP_VE_Cortex_A15x1_NMS;

// component factory implementation
// ------------------------------------------------------------------------------
// component factory of class SP805_Watchdog
// ------------------------------------------------------------------------------
//


namespace
{

// component factory class
// (this concrete class is never exposed to the outside world)
class SP805_Watchdog_ComponentFactoryClass: public ComponentFactoryBase
{
    bool componentsPublished;
    void lazyPublish(void)
    {
        static eslapi::CADITargetInfo_t info
        (
            0, /* MxU32 id; (overridden in CADIFactory) */                                                              // used for identification
            "SP805_Watchdog", /* char  targetName[CADI_NAME_SIZE];     */      // name of the target, i.e. the "type", not the instance name
            "", /* char instanceName[CADI_NAME_SIZE]; (overridden in CADIFactory) */    // name of the CADI target instance
            "8.1.37", /* char        version[CADI_DESCRIPTION]; */           // version string
            "ARM Watchdog Module(SP805)", /* char    description[CADI_DESCRIPTION]; */       // target description
            "Peripheral", /* char componentType[CADI_NAME_SIZE]; */       // classification of the target into a user-defined group
            0, /* MxU32 numberOfParameters; (overridden below) */                               // number of parameters supported
            0, /* bool        executesSoftware; */                            // false = does not execute programs, true = executes software
            false, /* MxU32     isHardwareModel; */                             // 0 = is software model, 1 = is hardware model
            "", /* char systemName[CADI_NAME_SIZE];  (overridden in CADIFactory) */             // name of the system the target belongs to.
            // Is empty for single-core standalone models.
            0, /* MxU32 systemID; (overridden in CADIFactory) */                                                // system id
            "" /* char  systemDescription[CADI_DESCRIPTION]; (overridden in CADIFactory) */ // description of the system
        );

        static eslapi::CADIParameterInfo_t parameters[] =
        {
        eslapi::CADIParameterInfo_t(0x1000002D, "simhalt",eslapi::CADI_PARAM_BOOL, "Halt on reset.",1,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "false" ),

            eslapi::CADIParameterInfo_t( 0, "", eslapi::CADI_PARAM_BOOL, "", 1, INT64_C(0), INT64_C(-1), 0, "0" )
        };
        info.numberOfParameters = (sizeof(parameters) / sizeof(parameters[0])) - 1;

        // build TargetInfo
        sg::TargetInfo targetInfo;
        targetInfo.cadi_target_info = &info;
        targetInfo.parameter_count = targetInfo.cadi_target_info->numberOfParameters;
        targetInfo.parameter_info = parameters;

        // publish this component's TargetInfo
        publishTarget(targetInfo, "");

        // publish subcomponent TargetInfos
        {
            sg::ComponentFactory *componentFactory = PVBusSlave_GetFactory();
            ComponentFactoryBase::publishSubComponent(componentFactory, "busslave", true, ParameterFilter_busslave_of_PVBusSlave_to_SP805_Watchdog());
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockTimer_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "clocktimer", true);
            componentFactory->dereference();
        }

        componentsPublished = true;
    }
    ~SP805_Watchdog_ComponentFactoryClass()
    {
    }

public:
    SP805_Watchdog_ComponentFactoryClass() {
        componentsPublished = false;
    }

    virtual void dereference() { delete this; }

    virtual sg::ComponentBase *instantiate(std::string const & instance_name,
                                                sg::SimulationContext *simulationContext,
                                                sg::Params const & params)
    {
        return new FVP_VE_Cortex_A15x1_NMS::Component__SP805_Watchdog(instance_name.c_str(), simulationContext, params);
    }

    virtual unsigned int getTargetCount()
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetCount();
    }

    virtual sg::TargetInfo * getTargetInfo(unsigned int index)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(index);
    }

    virtual sg::TargetInfo * getTargetInfo(std::string const & instance_path)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(instance_path);
    }

    virtual void publishSubComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all, const ParameterFilter &param_filter)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishSubComponent(factory, prefix, publish_all, param_filter);
    }

    virtual void publishComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishComponent(factory, prefix, publish_all);
    }

};

}

namespace FVP_VE_Cortex_A15x1_NMS {

// factory function
// (this is the function which is exposed to the outside world)
sg::ComponentFactory *SP805_Watchdog_GetFactory()
{
        return new SP805_Watchdog_ComponentFactoryClass();
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// component factory of class SP810_SysCtrl
// ------------------------------------------------------------------------------
//


namespace
{

// component factory class
// (this concrete class is never exposed to the outside world)
class SP810_SysCtrl_ComponentFactoryClass: public ComponentFactoryBase
{
    bool componentsPublished;
    void lazyPublish(void)
    {
        static eslapi::CADITargetInfo_t info
        (
            0, /* MxU32 id; (overridden in CADIFactory) */                                                              // used for identification
            "SP810_SysCtrl", /* char  targetName[CADI_NAME_SIZE];     */      // name of the target, i.e. the "type", not the instance name
            "", /* char instanceName[CADI_NAME_SIZE]; (overridden in CADIFactory) */    // name of the CADI target instance
            "8.1.37", /* char        version[CADI_DESCRIPTION]; */           // version string
            "PrimeXsys System Controller(SP810) NB: Only EB relevant functionalities are fully implemented.", /* char    description[CADI_DESCRIPTION]; */       // target description
            "Peripheral", /* char componentType[CADI_NAME_SIZE]; */       // classification of the target into a user-defined group
            0, /* MxU32 numberOfParameters; (overridden below) */                               // number of parameters supported
            0, /* bool        executesSoftware; */                            // false = does not execute programs, true = executes software
            false, /* MxU32     isHardwareModel; */                             // 0 = is software model, 1 = is hardware model
            "", /* char systemName[CADI_NAME_SIZE];  (overridden in CADIFactory) */             // name of the system the target belongs to.
            // Is empty for single-core standalone models.
            0, /* MxU32 systemID; (overridden in CADIFactory) */                                                // system id
            "" /* char  systemDescription[CADI_DESCRIPTION]; (overridden in CADIFactory) */ // description of the system
        );

        static eslapi::CADIParameterInfo_t parameters[] =
        {
        eslapi::CADIParameterInfo_t(0x1000002E, "sysid",eslapi::CADI_PARAM_INT, "System Identification Register.",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0x00000000" ),
        eslapi::CADIParameterInfo_t(0x1000002F, "use_s8",eslapi::CADI_PARAM_BOOL, "Use Switch 8 (S1-S4)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "false" ),

            eslapi::CADIParameterInfo_t( 0, "", eslapi::CADI_PARAM_BOOL, "", 1, INT64_C(0), INT64_C(-1), 0, "0" )
        };
        info.numberOfParameters = (sizeof(parameters) / sizeof(parameters[0])) - 1;

        // build TargetInfo
        sg::TargetInfo targetInfo;
        targetInfo.cadi_target_info = &info;
        targetInfo.parameter_count = targetInfo.cadi_target_info->numberOfParameters;
        targetInfo.parameter_info = parameters;

        // publish this component's TargetInfo
        publishTarget(targetInfo, "");

        // publish subcomponent TargetInfos
        {
            sg::ComponentFactory *componentFactory = PVBusSlave_GetFactory();
            ComponentFactoryBase::publishSubComponent(componentFactory, "busslave", true, ParameterFilter_busslave_of_PVBusSlave_to_SP810_SysCtrl());
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockDivider_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "clkdiv_clk0", true);
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockDivider_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "clkdiv_clk1", true);
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockDivider_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "clkdiv_clk2", true);
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockDivider_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "clkdiv_clk3", true);
            componentFactory->dereference();
        }

        componentsPublished = true;
    }
    ~SP810_SysCtrl_ComponentFactoryClass()
    {
    }

public:
    SP810_SysCtrl_ComponentFactoryClass() {
        componentsPublished = false;
    }

    virtual void dereference() { delete this; }

    virtual sg::ComponentBase *instantiate(std::string const & instance_name,
                                                sg::SimulationContext *simulationContext,
                                                sg::Params const & params)
    {
        return new FVP_VE_Cortex_A15x1_NMS::Component__SP810_SysCtrl(instance_name.c_str(), simulationContext, params);
    }

    virtual unsigned int getTargetCount()
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetCount();
    }

    virtual sg::TargetInfo * getTargetInfo(unsigned int index)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(index);
    }

    virtual sg::TargetInfo * getTargetInfo(std::string const & instance_path)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(instance_path);
    }

    virtual void publishSubComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all, const ParameterFilter &param_filter)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishSubComponent(factory, prefix, publish_all, param_filter);
    }

    virtual void publishComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishComponent(factory, prefix, publish_all);
    }

};

}

namespace FVP_VE_Cortex_A15x1_NMS {

// factory function
// (this is the function which is exposed to the outside world)
sg::ComponentFactory *SP810_SysCtrl_GetFactory()
{
        return new SP810_SysCtrl_ComponentFactoryClass();
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// component factory of class VE_SysRegs
// ------------------------------------------------------------------------------
//


namespace
{

// component factory class
// (this concrete class is never exposed to the outside world)
class VE_SysRegs_ComponentFactoryClass: public ComponentFactoryBase
{
    bool componentsPublished;
    void lazyPublish(void)
    {
        static eslapi::CADITargetInfo_t info
        (
            0, /* MxU32 id; (overridden in CADIFactory) */                                                              // used for identification
            "VE_SysRegs", /* char  targetName[CADI_NAME_SIZE];     */      // name of the target, i.e. the "type", not the instance name
            "", /* char instanceName[CADI_NAME_SIZE]; (overridden in CADIFactory) */    // name of the CADI target instance
            "8.1.37", /* char        version[CADI_DESCRIPTION]; */           // version string
            "", /* char    description[CADI_DESCRIPTION]; */       // target description
            "", /* char componentType[CADI_NAME_SIZE]; */       // classification of the target into a user-defined group
            0, /* MxU32 numberOfParameters; (overridden below) */                               // number of parameters supported
            0, /* bool        executesSoftware; */                            // false = does not execute programs, true = executes software
            false, /* MxU32     isHardwareModel; */                             // 0 = is software model, 1 = is hardware model
            "", /* char systemName[CADI_NAME_SIZE];  (overridden in CADIFactory) */             // name of the system the target belongs to.
            // Is empty for single-core standalone models.
            0, /* MxU32 systemID; (overridden in CADIFactory) */                                                // system id
            "" /* char  systemDescription[CADI_DESCRIPTION]; (overridden in CADIFactory) */ // description of the system
        );

        static eslapi::CADIParameterInfo_t parameters[] =
        {
        eslapi::CADIParameterInfo_t(0x10000013, "sys_proc_id0",eslapi::CADI_PARAM_INT, "Procesor ID register at CoreTile Express Site 1",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0xc000000), "0x0c000000" ),
        eslapi::CADIParameterInfo_t(0x10000014, "sys_proc_id1",eslapi::CADI_PARAM_INT, "Processor ID at CoreTile Express Site 2",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0xff000000), "0xff000000" ),
        eslapi::CADIParameterInfo_t(0x10000030, "user_switches_value",eslapi::CADI_PARAM_INT, "User switches",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0x0" ),
        eslapi::CADIParameterInfo_t(0x10000031, "exit_on_shutdown",eslapi::CADI_PARAM_BOOL, "SYS_CFG_SHUTDOWN exits simulation",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "false" ),
        eslapi::CADIParameterInfo_t(0x10000032, "tilePresent",eslapi::CADI_PARAM_BOOL, "Tile fitted",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "true" ),

            eslapi::CADIParameterInfo_t( 0, "", eslapi::CADI_PARAM_BOOL, "", 1, INT64_C(0), INT64_C(-1), 0, "0" )
        };
        info.numberOfParameters = (sizeof(parameters) / sizeof(parameters[0])) - 1;

        // build TargetInfo
        sg::TargetInfo targetInfo;
        targetInfo.cadi_target_info = &info;
        targetInfo.parameter_count = targetInfo.cadi_target_info->numberOfParameters;
        targetInfo.parameter_info = parameters;

        // publish this component's TargetInfo
        publishTarget(targetInfo, "");

        // publish subcomponent TargetInfos
        {
            sg::ComponentFactory *componentFactory = PVBusSlave_GetFactory();
            ComponentFactoryBase::publishSubComponent(componentFactory, "busslave", true, ParameterFilter_busslave_of_PVBusSlave_to_VE_SysRegs());
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockTimer_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "timer_24mhz", true);
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockTimer_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "timer_100Hz", true);
            componentFactory->dereference();
        }

        componentsPublished = true;
    }
    ~VE_SysRegs_ComponentFactoryClass()
    {
    }

public:
    VE_SysRegs_ComponentFactoryClass() {
        componentsPublished = false;
    }

    virtual void dereference() { delete this; }

    virtual sg::ComponentBase *instantiate(std::string const & instance_name,
                                                sg::SimulationContext *simulationContext,
                                                sg::Params const & params)
    {
        return new FVP_VE_Cortex_A15x1_NMS::Component__VE_SysRegs(instance_name.c_str(), simulationContext, params);
    }

    virtual unsigned int getTargetCount()
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetCount();
    }

    virtual sg::TargetInfo * getTargetInfo(unsigned int index)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(index);
    }

    virtual sg::TargetInfo * getTargetInfo(std::string const & instance_path)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(instance_path);
    }

    virtual void publishSubComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all, const ParameterFilter &param_filter)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishSubComponent(factory, prefix, publish_all, param_filter);
    }

    virtual void publishComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishComponent(factory, prefix, publish_all);
    }

};

}

namespace FVP_VE_Cortex_A15x1_NMS {

// factory function
// (this is the function which is exposed to the outside world)
sg::ComponentFactory *VE_SysRegs_GetFactory()
{
        return new VE_SysRegs_ComponentFactoryClass();
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// component factory of class VFS2
// ------------------------------------------------------------------------------
//


namespace
{

// component factory class
// (this concrete class is never exposed to the outside world)
class VFS2_ComponentFactoryClass: public ComponentFactoryBase
{
    bool componentsPublished;
    void lazyPublish(void)
    {
        static eslapi::CADITargetInfo_t info
        (
            0, /* MxU32 id; (overridden in CADIFactory) */                                                              // used for identification
            "VFS2", /* char  targetName[CADI_NAME_SIZE];     */      // name of the target, i.e. the "type", not the instance name
            "", /* char instanceName[CADI_NAME_SIZE]; (overridden in CADIFactory) */    // name of the CADI target instance
            "8.1.37", /* char        version[CADI_DESCRIPTION]; */           // version string
            "Virtual Filesystem Device", /* char    description[CADI_DESCRIPTION]; */       // target description
            "Other", /* char componentType[CADI_NAME_SIZE]; */       // classification of the target into a user-defined group
            0, /* MxU32 numberOfParameters; (overridden below) */                               // number of parameters supported
            0, /* bool        executesSoftware; */                            // false = does not execute programs, true = executes software
            false, /* MxU32     isHardwareModel; */                             // 0 = is software model, 1 = is hardware model
            "", /* char systemName[CADI_NAME_SIZE];  (overridden in CADIFactory) */             // name of the system the target belongs to.
            // Is empty for single-core standalone models.
            0, /* MxU32 systemID; (overridden in CADIFactory) */                                                // system id
            "" /* char  systemDescription[CADI_DESCRIPTION]; (overridden in CADIFactory) */ // description of the system
        );

        static eslapi::CADIParameterInfo_t parameters[] =
        {
        eslapi::CADIParameterInfo_t(0x10000033, "mount",eslapi::CADI_PARAM_STRING, "Path to host system folder to make accessible to target OS",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "" ),

            eslapi::CADIParameterInfo_t( 0, "", eslapi::CADI_PARAM_BOOL, "", 1, INT64_C(0), INT64_C(-1), 0, "0" )
        };
        info.numberOfParameters = (sizeof(parameters) / sizeof(parameters[0])) - 1;

        // build TargetInfo
        sg::TargetInfo targetInfo;
        targetInfo.cadi_target_info = &info;
        targetInfo.parameter_count = targetInfo.cadi_target_info->numberOfParameters;
        targetInfo.parameter_info = parameters;

        // publish this component's TargetInfo
        publishTarget(targetInfo, "");

        // publish subcomponent TargetInfos
        {
            sg::ComponentFactory *componentFactory = MessageBox_GetFactory();
            ComponentFactoryBase::publishSubComponent(componentFactory, "messagebox", true, ParameterFilter_messagebox_of_MessageBox_to_VFS2());
            componentFactory->dereference();
        }

        componentsPublished = true;
    }
    ~VFS2_ComponentFactoryClass()
    {
    }

public:
    VFS2_ComponentFactoryClass() {
        componentsPublished = false;
    }

    virtual void dereference() { delete this; }

    virtual sg::ComponentBase *instantiate(std::string const & instance_name,
                                                sg::SimulationContext *simulationContext,
                                                sg::Params const & params)
    {
        return new FVP_VE_Cortex_A15x1_NMS::Component__VFS2(instance_name.c_str(), simulationContext, params);
    }

    virtual unsigned int getTargetCount()
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetCount();
    }

    virtual sg::TargetInfo * getTargetInfo(unsigned int index)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(index);
    }

    virtual sg::TargetInfo * getTargetInfo(std::string const & instance_path)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(instance_path);
    }

    virtual void publishSubComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all, const ParameterFilter &param_filter)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishSubComponent(factory, prefix, publish_all, param_filter);
    }

    virtual void publishComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishComponent(factory, prefix, publish_all);
    }

};

}

namespace FVP_VE_Cortex_A15x1_NMS {

// factory function
// (this is the function which is exposed to the outside world)
sg::ComponentFactory *VFS2_GetFactory()
{
        return new VFS2_ComponentFactoryClass();
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// component factory of class MessageBox
// ------------------------------------------------------------------------------
//


namespace
{

// component factory class
// (this concrete class is never exposed to the outside world)
class MessageBox_ComponentFactoryClass: public ComponentFactoryBase
{
    bool componentsPublished;
    void lazyPublish(void)
    {
        static eslapi::CADITargetInfo_t info
        (
            0, /* MxU32 id; (overridden in CADIFactory) */                                                              // used for identification
            "MessageBox", /* char  targetName[CADI_NAME_SIZE];     */      // name of the target, i.e. the "type", not the instance name
            "", /* char instanceName[CADI_NAME_SIZE]; (overridden in CADIFactory) */    // name of the CADI target instance
            "8.1.37", /* char        version[CADI_DESCRIPTION]; */           // version string
            "Generic MessageBox", /* char    description[CADI_DESCRIPTION]; */       // target description
            "Other", /* char componentType[CADI_NAME_SIZE]; */       // classification of the target into a user-defined group
            0, /* MxU32 numberOfParameters; (overridden below) */                               // number of parameters supported
            0, /* bool        executesSoftware; */                            // false = does not execute programs, true = executes software
            false, /* MxU32     isHardwareModel; */                             // 0 = is software model, 1 = is hardware model
            "", /* char systemName[CADI_NAME_SIZE];  (overridden in CADIFactory) */             // name of the system the target belongs to.
            // Is empty for single-core standalone models.
            0, /* MxU32 systemID; (overridden in CADIFactory) */                                                // system id
            "" /* char  systemDescription[CADI_DESCRIPTION]; (overridden in CADIFactory) */ // description of the system
        );

        static eslapi::CADIParameterInfo_t parameters[] =
        {
        eslapi::CADIParameterInfo_t(0x10000034, "id",eslapi::CADI_PARAM_INT, "MessageBox ID",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1400400), "0x01400400" ),

            eslapi::CADIParameterInfo_t( 0, "", eslapi::CADI_PARAM_BOOL, "", 1, INT64_C(0), INT64_C(-1), 0, "0" )
        };
        info.numberOfParameters = (sizeof(parameters) / sizeof(parameters[0])) - 1;

        // build TargetInfo
        sg::TargetInfo targetInfo;
        targetInfo.cadi_target_info = &info;
        targetInfo.parameter_count = targetInfo.cadi_target_info->numberOfParameters;
        targetInfo.parameter_info = parameters;

        // publish this component's TargetInfo
        publishTarget(targetInfo, "");

        // publish subcomponent TargetInfos
        {
            sg::ComponentFactory *componentFactory = PVBusSlave_GetFactory();
            ComponentFactoryBase::publishSubComponent(componentFactory, "busslave", true, ParameterFilter_busslave_of_PVBusSlave_to_MessageBox());
            componentFactory->dereference();
        }

        componentsPublished = true;
    }
    ~MessageBox_ComponentFactoryClass()
    {
    }

public:
    MessageBox_ComponentFactoryClass() {
        componentsPublished = false;
    }

    virtual void dereference() { delete this; }

    virtual sg::ComponentBase *instantiate(std::string const & instance_name,
                                                sg::SimulationContext *simulationContext,
                                                sg::Params const & params)
    {
        return new FVP_VE_Cortex_A15x1_NMS::Component__MessageBox(instance_name.c_str(), simulationContext, params);
    }

    virtual unsigned int getTargetCount()
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetCount();
    }

    virtual sg::TargetInfo * getTargetInfo(unsigned int index)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(index);
    }

    virtual sg::TargetInfo * getTargetInfo(std::string const & instance_path)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(instance_path);
    }

    virtual void publishSubComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all, const ParameterFilter &param_filter)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishSubComponent(factory, prefix, publish_all, param_filter);
    }

    virtual void publishComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishComponent(factory, prefix, publish_all);
    }

};

}

namespace FVP_VE_Cortex_A15x1_NMS {

// factory function
// (this is the function which is exposed to the outside world)
sg::ComponentFactory *MessageBox_GetFactory()
{
        return new MessageBox_ComponentFactoryClass();
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// component factory of class VirtualEthernetCrossover
// ------------------------------------------------------------------------------
//


namespace
{

// component factory class
// (this concrete class is never exposed to the outside world)
class VirtualEthernetCrossover_ComponentFactoryClass: public ComponentFactoryBase
{
    bool componentsPublished;
    void lazyPublish(void)
    {
        static eslapi::CADITargetInfo_t info
        (
            0, /* MxU32 id; (overridden in CADIFactory) */                                                              // used for identification
            "VirtualEthernetCrossover", /* char  targetName[CADI_NAME_SIZE];     */      // name of the target, i.e. the "type", not the instance name
            "", /* char instanceName[CADI_NAME_SIZE]; (overridden in CADIFactory) */    // name of the CADI target instance
            "8.1.37", /* char        version[CADI_DESCRIPTION]; */           // version string
            "Ethernet Crossover Cable", /* char    description[CADI_DESCRIPTION]; */       // target description
            "Peripheral", /* char componentType[CADI_NAME_SIZE]; */       // classification of the target into a user-defined group
            0, /* MxU32 numberOfParameters; (overridden below) */                               // number of parameters supported
            0, /* bool        executesSoftware; */                            // false = does not execute programs, true = executes software
            false, /* MxU32     isHardwareModel; */                             // 0 = is software model, 1 = is hardware model
            "", /* char systemName[CADI_NAME_SIZE];  (overridden in CADIFactory) */             // name of the system the target belongs to.
            // Is empty for single-core standalone models.
            0, /* MxU32 systemID; (overridden in CADIFactory) */                                                // system id
            "" /* char  systemDescription[CADI_DESCRIPTION]; (overridden in CADIFactory) */ // description of the system
        );

        static eslapi::CADIParameterInfo_t parameters[] =
        {

            eslapi::CADIParameterInfo_t( 0, "", eslapi::CADI_PARAM_BOOL, "", 1, INT64_C(0), INT64_C(-1), 0, "0" )
        };
        info.numberOfParameters = (sizeof(parameters) / sizeof(parameters[0])) - 1;

        // build TargetInfo
        sg::TargetInfo targetInfo;
        targetInfo.cadi_target_info = &info;
        targetInfo.parameter_count = targetInfo.cadi_target_info->numberOfParameters;
        targetInfo.parameter_info = parameters;

        // publish this component's TargetInfo
        publishTarget(targetInfo, "");

        // publish subcomponent TargetInfos

        componentsPublished = true;
    }
    ~VirtualEthernetCrossover_ComponentFactoryClass()
    {
    }

public:
    VirtualEthernetCrossover_ComponentFactoryClass() {
        componentsPublished = false;
    }

    virtual void dereference() { delete this; }

    virtual sg::ComponentBase *instantiate(std::string const & instance_name,
                                                sg::SimulationContext *simulationContext,
                                                sg::Params const & params)
    {
        return new FVP_VE_Cortex_A15x1_NMS::Component__VirtualEthernetCrossover(instance_name.c_str(), simulationContext, params);
    }

    virtual unsigned int getTargetCount()
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetCount();
    }

    virtual sg::TargetInfo * getTargetInfo(unsigned int index)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(index);
    }

    virtual sg::TargetInfo * getTargetInfo(std::string const & instance_path)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(instance_path);
    }

    virtual void publishSubComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all, const ParameterFilter &param_filter)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishSubComponent(factory, prefix, publish_all, param_filter);
    }

    virtual void publishComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishComponent(factory, prefix, publish_all);
    }

};

}

namespace FVP_VE_Cortex_A15x1_NMS {

// factory function
// (this is the function which is exposed to the outside world)
sg::ComponentFactory *VirtualEthernetCrossover_GetFactory()
{
        return new VirtualEthernetCrossover_ComponentFactoryClass();
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// component factory of class VEVisualisation
// ------------------------------------------------------------------------------
//


namespace
{

// component factory class
// (this concrete class is never exposed to the outside world)
class VEVisualisation_ComponentFactoryClass: public ComponentFactoryBase
{
    bool componentsPublished;
    void lazyPublish(void)
    {
        static eslapi::CADITargetInfo_t info
        (
            0, /* MxU32 id; (overridden in CADIFactory) */                                                              // used for identification
            "VEVisualisation", /* char  targetName[CADI_NAME_SIZE];     */      // name of the target, i.e. the "type", not the instance name
            "", /* char instanceName[CADI_NAME_SIZE]; (overridden in CADIFactory) */    // name of the CADI target instance
            "8.1.37", /* char        version[CADI_DESCRIPTION]; */           // version string
            "Display window for VE using Visualisation library.", /* char    description[CADI_DESCRIPTION]; */       // target description
            "Peripheral", /* char componentType[CADI_NAME_SIZE]; */       // classification of the target into a user-defined group
            0, /* MxU32 numberOfParameters; (overridden below) */                               // number of parameters supported
            0, /* bool        executesSoftware; */                            // false = does not execute programs, true = executes software
            false, /* MxU32     isHardwareModel; */                             // 0 = is software model, 1 = is hardware model
            "", /* char systemName[CADI_NAME_SIZE];  (overridden in CADIFactory) */             // name of the system the target belongs to.
            // Is empty for single-core standalone models.
            0, /* MxU32 systemID; (overridden in CADIFactory) */                                                // system id
            "" /* char  systemDescription[CADI_DESCRIPTION]; (overridden in CADIFactory) */ // description of the system
        );

        static eslapi::CADIParameterInfo_t parameters[] =
        {
        eslapi::CADIParameterInfo_t(0x10000035, "trap_key",eslapi::CADI_PARAM_INT, "Trap key that works with left Ctrl to toggle mouse display.",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x4a), "74" ),
        eslapi::CADIParameterInfo_t(0x10000036, "rate_limit-enable",eslapi::CADI_PARAM_BOOL, "Rate limit simulation.",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "true" ),
        eslapi::CADIParameterInfo_t(0x10000037, "disable_visualisation",eslapi::CADI_PARAM_BOOL, "Enable/disable visualisation",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "false" ),
        eslapi::CADIParameterInfo_t(0x10000038, "window_title",eslapi::CADI_PARAM_STRING, "Window title (%cpu% is replaced by cpu_name)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "Fast Models - CLCD %cpu%" ),
        eslapi::CADIParameterInfo_t(0x10000039, "cpu_name",eslapi::CADI_PARAM_STRING, "Cpu name displayed in window title",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "" ),
        eslapi::CADIParameterInfo_t(0x1000003A, "cluster0_name",eslapi::CADI_PARAM_STRING, "Cluster0 name",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "Cluster0" ),
        eslapi::CADIParameterInfo_t(0x1000003B, "cluster1_name",eslapi::CADI_PARAM_STRING, "Cluster1 name",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "Cluster1" ),
        eslapi::CADIParameterInfo_t(0x10000011, "daughter_led_count",eslapi::CADI_PARAM_INT, "Number of LEDs that the daughter board has",0,MxS64CONST(0x0),MxS64CONST(0x20),MxS64CONST(0x0), "0" ),
        eslapi::CADIParameterInfo_t(0x10000015, "daughter_user_switch_count",eslapi::CADI_PARAM_INT, "Number of switches that the daughter board has",0,MxS64CONST(0x0),MxS64CONST(0x20),MxS64CONST(0x0), "0" ),

            eslapi::CADIParameterInfo_t( 0, "", eslapi::CADI_PARAM_BOOL, "", 1, INT64_C(0), INT64_C(-1), 0, "0" )
        };
        info.numberOfParameters = (sizeof(parameters) / sizeof(parameters[0])) - 1;

        // build TargetInfo
        sg::TargetInfo targetInfo;
        targetInfo.cadi_target_info = &info;
        targetInfo.parameter_count = targetInfo.cadi_target_info->numberOfParameters;
        targetInfo.parameter_info = parameters;

        // publish this component's TargetInfo
        publishTarget(targetInfo, "");

        // publish subcomponent TargetInfos
        {
            sg::ComponentFactory *componentFactory = GUIPoll_GetFactory();
            ComponentFactoryBase::publishSubComponent(componentFactory, "idler", true, ParameterFilter_idler_of_GUIPoll_to_VEVisualisation());
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockTimer_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "timer", true);
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = VisEventRecorder_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "recorder", true);
            componentFactory->dereference();
        }

        componentsPublished = true;
    }
    ~VEVisualisation_ComponentFactoryClass()
    {
    }

public:
    VEVisualisation_ComponentFactoryClass() {
        componentsPublished = false;
    }

    virtual void dereference() { delete this; }

    virtual sg::ComponentBase *instantiate(std::string const & instance_name,
                                                sg::SimulationContext *simulationContext,
                                                sg::Params const & params)
    {
        return new FVP_VE_Cortex_A15x1_NMS::Component__VEVisualisation(instance_name.c_str(), simulationContext, params);
    }

    virtual unsigned int getTargetCount()
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetCount();
    }

    virtual sg::TargetInfo * getTargetInfo(unsigned int index)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(index);
    }

    virtual sg::TargetInfo * getTargetInfo(std::string const & instance_path)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(instance_path);
    }

    virtual void publishSubComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all, const ParameterFilter &param_filter)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishSubComponent(factory, prefix, publish_all, param_filter);
    }

    virtual void publishComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishComponent(factory, prefix, publish_all);
    }

};

}

namespace FVP_VE_Cortex_A15x1_NMS {

// factory function
// (this is the function which is exposed to the outside world)
sg::ComponentFactory *VEVisualisation_GetFactory()
{
        return new VEVisualisation_ComponentFactoryClass();
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// component factory of class VisEventRecorder
// ------------------------------------------------------------------------------
//


namespace
{

// component factory class
// (this concrete class is never exposed to the outside world)
class VisEventRecorder_ComponentFactoryClass: public ComponentFactoryBase
{
    bool componentsPublished;
    void lazyPublish(void)
    {
        static eslapi::CADITargetInfo_t info
        (
            0, /* MxU32 id; (overridden in CADIFactory) */                                                              // used for identification
            "VisEventRecorder", /* char  targetName[CADI_NAME_SIZE];     */      // name of the target, i.e. the "type", not the instance name
            "", /* char instanceName[CADI_NAME_SIZE]; (overridden in CADIFactory) */    // name of the CADI target instance
            "8.1.37", /* char        version[CADI_DESCRIPTION]; */           // version string
            "Event recorder component for visualisation component (allows to playback and record interactive GUI sessions).", /* char    description[CADI_DESCRIPTION]; */       // target description
            "Other", /* char componentType[CADI_NAME_SIZE]; */       // classification of the target into a user-defined group
            0, /* MxU32 numberOfParameters; (overridden below) */                               // number of parameters supported
            0, /* bool        executesSoftware; */                            // false = does not execute programs, true = executes software
            false, /* MxU32     isHardwareModel; */                             // 0 = is software model, 1 = is hardware model
            "", /* char systemName[CADI_NAME_SIZE];  (overridden in CADIFactory) */             // name of the system the target belongs to.
            // Is empty for single-core standalone models.
            0, /* MxU32 systemID; (overridden in CADIFactory) */                                                // system id
            "" /* char  systemDescription[CADI_DESCRIPTION]; (overridden in CADIFactory) */ // description of the system
        );

        static eslapi::CADIParameterInfo_t parameters[] =
        {
        eslapi::CADIParameterInfo_t(0x1000003D, "recordingFileName",eslapi::CADI_PARAM_STRING, "recording filename (empty string disables recording)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "" ),
        eslapi::CADIParameterInfo_t(0x1000003E, "playbackFileName",eslapi::CADI_PARAM_STRING, "playback filename (empty string disables playback)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "" ),
        eslapi::CADIParameterInfo_t(0x1000003F, "recordingTimeBase",eslapi::CADI_PARAM_INT, "timebase in 1/s (relative to the master clock (e.g. 100000000 means 10 nanoseconds resultion simulated time for a 1Hz master clock)) to be used for recording (higher values -> higher time resolution, playback time base is always taken from the playback file)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x5f5e100), "100000000" ),
        eslapi::CADIParameterInfo_t(0x10000040, "verbose",eslapi::CADI_PARAM_INT, "enable verbose messages (1=normal, 2=even more)",1,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" ),
        eslapi::CADIParameterInfo_t(0x10000041, "checkInstructionCount",eslapi::CADI_PARAM_BOOL, "check instruction count in recording file against actual instruction count during playback",1,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "true" ),

            eslapi::CADIParameterInfo_t( 0, "", eslapi::CADI_PARAM_BOOL, "", 1, INT64_C(0), INT64_C(-1), 0, "0" )
        };
        info.numberOfParameters = (sizeof(parameters) / sizeof(parameters[0])) - 1;

        // build TargetInfo
        sg::TargetInfo targetInfo;
        targetInfo.cadi_target_info = &info;
        targetInfo.parameter_count = targetInfo.cadi_target_info->numberOfParameters;
        targetInfo.parameter_info = parameters;

        // publish this component's TargetInfo
        publishTarget(targetInfo, "");

        // publish subcomponent TargetInfos
        {
            sg::ComponentFactory *componentFactory = ClockTimer_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "playbackTimer", true);
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockDivider_GetFactory();
            ComponentFactoryBase::publishSubComponent(componentFactory, "playbackDivider", true, ParameterFilter_playbackDivider_of_ClockDivider_to_VisEventRecorder());
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockTimer_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "recordingTimer", true);
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = ClockDivider_GetFactory();
            ComponentFactoryBase::publishSubComponent(componentFactory, "recordingDivider", true, ParameterFilter_recordingDivider_of_ClockDivider_to_VisEventRecorder());
            componentFactory->dereference();
        }
        {
            sg::ComponentFactory *componentFactory = MasterClock_GetFactory();
            ComponentFactoryBase::publishComponent(componentFactory, "masterClock", true);
            componentFactory->dereference();
        }

        componentsPublished = true;
    }
    ~VisEventRecorder_ComponentFactoryClass()
    {
    }

public:
    VisEventRecorder_ComponentFactoryClass() {
        componentsPublished = false;
    }

    virtual void dereference() { delete this; }

    virtual sg::ComponentBase *instantiate(std::string const & instance_name,
                                                sg::SimulationContext *simulationContext,
                                                sg::Params const & params)
    {
        return new FVP_VE_Cortex_A15x1_NMS::Component__VisEventRecorder(instance_name.c_str(), simulationContext, params);
    }

    virtual unsigned int getTargetCount()
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetCount();
    }

    virtual sg::TargetInfo * getTargetInfo(unsigned int index)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(index);
    }

    virtual sg::TargetInfo * getTargetInfo(std::string const & instance_path)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::getTargetInfo(instance_path);
    }

    virtual void publishSubComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all, const ParameterFilter &param_filter)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishSubComponent(factory, prefix, publish_all, param_filter);
    }

    virtual void publishComponent(sg::ComponentFactory *factory, const std::string &prefix,
                          bool publish_all)
    {
        if (!componentsPublished) lazyPublish();
        return ComponentFactoryBase::publishComponent(factory, prefix, publish_all);
    }

};

}

namespace FVP_VE_Cortex_A15x1_NMS {

// factory function
// (this is the function which is exposed to the outside world)
sg::ComponentFactory *VisEventRecorder_GetFactory()
{
        return new VisEventRecorder_ComponentFactoryClass();
}

} // FVP_VE_Cortex_A15x1_NMS

