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
 * Class definition for Component PS2Keyboard.
 */

#ifndef Component_Component__PS2Keyboard_ClassDef_h_
#define Component_Component__PS2Keyboard_ClassDef_h_

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

#line 20 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PS2Keyboard.lisa"

    
        #define debug_queue    if (!0) ; else printf
        #define TRACE_KEYBOARD if (!0) ; else printf
        
        #include "components/KeyCode.h"
    
#line 45 "./Linux-Release-GCC-4.1/gen/Component__PS2Keyboard_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__KeyboardStatus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PS2Data_ClassDef.h"
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
Component__PS2Keyboard: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *ps2_clocktimer;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_ps2_clocktimer__;


    // abstract ports
	FVP_VE_Cortex_A15x1__ClockSignal clk_in;
	FVP_VE_Cortex_A15x1__PS2Data ps2;
	FVP_VE_Cortex_A15x1__TimerCallback ps2_timer_callback;
	FVP_VE_Cortex_A15x1__KeyboardStatus keyboard;
	FVP_VE_Cortex_A15x1__TimerControl __PS2Keyboard_internal_1;


    // resources
    std::string application_pathname;


#line 40 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PS2Keyboard.lisa"

        // ps2 resources
        
        enum ps2_consts
        {
            tx_fifo_max = 128,

            PS2_ACK = 0xfa
        };
        
        uint8_t tx_fifo[tx_fifo_max];
        uint8_t tx_fifo_level;
        uint8_t tx_fifo_in;
        uint8_t tx_fifo_out;
        
        bool command_pending; //!< kmi has indicated that there is a command pending
        bool ok_to_send;      //!< kmi has indicated that it is ok to send data

        uint32_t poll_period;   //!< polling period in usecs (0 = nothing to do)
        bool   poll_active;   //!< protects timer from being set during a callback

        struct KeyMap
        {
            ATKeyCode kc;
            uint8_t ps2;
        };
        
        uint8_t scancode_set;          // current scan codes
        uint8_t command_pos;           // command queue index (depth 2)
        uint8_t command;               // command byte
        uint8_t lastbyte;              // last byte sent

        uint8_t scancode[3][KC_MAX];
        uint8_t scancode_ext[3][KC_MAX];
    
#line 132 "./Linux-Release-GCC-4.1/gen/Component__PS2Keyboard_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__PS2Keyboard(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__PS2Keyboard();

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
	void ps2_init();
	void ps2_reset();
	void clearQueue();
	void queueData(uint8_t* buf, uint8_t count);
	void device_init();
	void device_reset();
	void reply1(uint8_t data);
	void reply2(uint8_t data1, uint8_t data2);
	void Command(uint8_t data);
	void init_keymaps();
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
	void abstract_port__ps2__setClockData(enum ps2clockdata_state state);
	uint32_t abstract_port__ps2_timer_callback__signal();
	void abstract_port__keyboard__keyDown(ATKeyCode code);
	void abstract_port__keyboard__keyUp(ATKeyCode code);

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

