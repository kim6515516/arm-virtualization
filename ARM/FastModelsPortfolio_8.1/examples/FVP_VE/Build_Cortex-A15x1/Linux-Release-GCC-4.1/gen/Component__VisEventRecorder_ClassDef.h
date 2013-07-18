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
 * Class definition for Component VisEventRecorder.
 */

#ifndef Component_Component__VisEventRecorder_ClassDef_h_
#define Component_Component__VisEventRecorder_ClassDef_h_

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

#line 69 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"

    
        #include <map>
        #include <vector>
        #include <time.h>
        #include <cstdlib>
        #include "components/Visualisation.h"
        #include "sg/MSCFixes.h"
        #include "hostconf/zinttypes.h"
    
#line 48 "./Linux-Release-GCC-4.1/gen/Component__VisEventRecorder_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockRateControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__InstructionCount_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerCallback_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__VisEventRecorderProtocol_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_playbackDivider_of_ClockDivider_to_VisEventRecorder : public ParameterFilter
{
public:
	ParameterFilter_playbackDivider_of_ClockDivider_to_VisEventRecorder()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FIXED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" );
	}
};

class ParameterFilter_recordingDivider_of_ClockDivider_to_VisEventRecorder : public ParameterFilter
{
public:
	ParameterFilter_recordingDivider_of_ClockDivider_to_VisEventRecorder()
	{
		ovrd_params["mul"] = eslapi::CADIParameterInfo_t(0x1000000A | PARAMETERFILTER_FORWARDED, "mul",eslapi::CADI_PARAM_INT, "Clock Rate Multiplier",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1), "1" ); // forwarded from "recordingTimeBase"
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__VisEventRecorder: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *playbackTimer;
	sg::ComponentBase *playbackDivider;
	sg::ComponentBase *recordingTimer;
	sg::ComponentBase *recordingDivider;
	sg::ComponentBase *masterClock;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_playbackTimer__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_playbackDivider__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_recordingTimer__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_recordingDivider__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_masterClock__;


    // abstract ports
	FVP_VE_Cortex_A15x1__InstructionCount ticks;
	FVP_VE_Cortex_A15x1__VisEventRecorderProtocol control;
	FVP_VE_Cortex_A15x1__TimerCallback playbackTimerCallback;
	FVP_VE_Cortex_A15x1__TimerCallback recordingTimerCallback;
	FVP_VE_Cortex_A15x1__TimerControl __VisEventRecorder_internal_1;
	FVP_VE_Cortex_A15x1__TimerControl __VisEventRecorder_internal_2;
	FVP_VE_Cortex_A15x1__ClockRateControl __VisEventRecorder_internal_3;


    // resources
    std::string application_pathname;


#line 81 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/VisEventRecorder.lisa"

        const std::string 
        recordingFileName      ;
        const std::string 
        playbackFileName      ;
        const uint64_t 
        recordingTimeBase      ;
        uint32_t 
        verbose      ;
        bool 
        checkInstructionCount      ;
        
        // associate VisRegions with names to be able to store pointers to them in an ASCII file
        std::map<std::string, VisRegion *> name2region;
        std::map<VisRegion *, std::string> region2name;
        
        // timers
        uint64_t currentRecordingTimeHigh;
        uint64_t currentRecordingTime;
        
        // ClockTimers are only 32 bit, wrap arond at this value
        uint32_t timerTop;
        
        // enable/disable recording/playback
        bool recordingEnabled;
        bool playbackEnabled;
        
        // playback data
        struct Event
        {
            uint64_t time;
            uint64_t instructionCount;
            VisEvent visEvent;
        };
        std::vector<Event> playbackData;
        uint32_t playbackPC;
        uint64_t playbackCurrentTimeStamp; // set only during 'processesEvents()' callback: timestamp of events which are to be processed now
        uint64_t playbackNextTimeStamp; // timestamp which are to be processed in the next timer callback (the one following after the current one)
        uint64_t playbackLongWait; // != 0 when we need to wait more than 0x40000000 ticks
        enum { INITIAL_DIFF_MESSAGE_THRESHOLD = 300 }; // print a message when a playback event is emitted more than 1000 instructions before or after the instruction count in the recording
        int64_t diffMessageThresholdLower; // print 'differing instruction count' messages only for even lower/higher values
        int64_t diffMessageThresholdUpper;
    
#line 171 "./Linux-Release-GCC-4.1/gen/Component__VisEventRecorder_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__VisEventRecorder(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__VisEventRecorder();

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
	void terminate();
	std::string formatEventRecord(uint64_t time, uint64_t instructionCount, const VisEvent* event, const char* lineEnd);
	const char* getTypeStr(unsigned type);
	VisEvent::VisEventType getEventType(const char* fileName, int linenr, const char* str);
	void appendToFile(const char* fileName, const char* str);
	void writeToFile(const char* fileName, const char* str, const char* mode);
	uint64_t getCurrentRecordingTime();
	void initRecording();
	void initPlayback();
	void parseAndAppendEventRecord(const char* fileName, int linenr, const char* str);
	void parseTimeBaseRecord(const char* fileName, int linenr, const char* str);
	uint32_t getNextPlaybackTimerInterval();
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	bool abstract_port__control__getEvent(VisEvent* event);
	void abstract_port__control__putEvent(const VisEvent* event);
	void abstract_port__control__registerVisRegion(VisRegion* region, const char* regionName);
	uint32_t abstract_port__playbackTimerCallback__signal();
	uint32_t abstract_port__recordingTimerCallback__signal();

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


	ParameterFilter_playbackDivider_of_ClockDivider_to_VisEventRecorder parameterFilter_playbackDivider_of_ClockDivider_to_VisEventRecorder__;
	ParameterFilter_recordingDivider_of_ClockDivider_to_VisEventRecorder parameterFilter_recordingDivider_of_ClockDivider_to_VisEventRecorder__;


	CADIParameterProxy *cadiParameterProxy_playbackDivider_of_ClockDivider_to_VisEventRecorder__;
	CADIParameterProxy *cadiParameterProxy_recordingDivider_of_ClockDivider_to_VisEventRecorder__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_recordingFileName = 0x1000003D,
		PARAMETER_ID_playbackFileName = 0x1000003E,
		PARAMETER_ID_recordingTimeBase = 0x1000003F,
		PARAMETER_ID_verbose = 0x10000040,
		PARAMETER_ID_checkInstructionCount = 0x10000041,
	};




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

