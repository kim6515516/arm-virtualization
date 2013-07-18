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
 * Class definition for Component MessageBox.
 */

#ifndef Component_Component__MessageBox_ClassDef_h_
#define Component_Component__MessageBox_ClassDef_h_

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

#line 28 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"

    
        // shared definitions between driver/device
        #include "MBoxTypes.h"
        
        #define MESSAGEBOX_TRACE        if (!0) ; else printf
        #define MESSAGEBOX_TRACE_DATA   if (!0) ; else printf
        #define MESSAGEBOX_TRACE_MSG    if (!0) ; else printf
    
#line 47 "./Linux-Release-GCC-4.1/gen/Component__MessageBox_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__MessageBoxProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBusSlaveControl_ClassDef.h"
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

class ParameterFilter_busslave_of_PVBusSlave_to_MessageBox : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_MessageBox()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__MessageBox: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *busslave;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVBus pvbus_s;
	FVP_VE_Cortex_A15x1__Signal intr;
	FVP_VE_Cortex_A15x1__MessageBoxProtocol message;
	FVP_VE_Cortex_A15x1__PVDevice device;
	FVP_VE_Cortex_A15x1__PVBusSlaveControl __MessageBox_internal_1;


    // resources
    std::string application_pathname;


#line 39 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/MessageBox.lisa"
        
        const uint32_t  id     ;

        MxU32  MESSAGEBOX_ID        ;
        MxU32  MESSAGEBOX_DATA                 ;
        MxU32  MESSAGEBOX_CONTROL              ;
        MxU32  MESSAGEBOX_STATUS               ;
        MxU32  MESSAGEBOX_START                ;
        MxU32  MESSAGEBOX_END                  ;
        MxU32  MESSAGEBOX_IRQMASK             ;
        
        // memory mapped buffer
        uint8_t buffer[MBOX_BUFFER_SIZE];
        
        uint32_t start;     // start pointer for data in buffer
        uint32_t end;       // end pointer for data in buffer
        uint32_t status;    // status register
        uint32_t control;   // control register
        uint32_t irqmask;   // irq status masking register
       
        bool irq;           // current IRQ signal status
    
#line 130 "./Linux-Release-GCC-4.1/gen/Component__MessageBox_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__MessageBox(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__MessageBox();

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
	void set_control(uint32_t control);
	uint32_t read_data();
	void write_data(uint32_t data);
	uint32_t get_start();
	void set_start(uint32_t data);
	uint32_t get_end();
	void set_end(uint32_t data);
	void update_interrupts();
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
	void reset(int level);
	void reset(int level, int /*argc*/, char** /*argv*/);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	void abstract_port__message__begin_msg(void** bufferp, uint32_t reserve_len);
	void abstract_port__message__cancel_msg();
	void abstract_port__message__end_msg(uint32_t len);
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


	ParameterFilter_busslave_of_PVBusSlave_to_MessageBox parameterFilter_busslave_of_PVBusSlave_to_MessageBox__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_MessageBox__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_id = 0x10000034,
	};


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_MESSAGEBOX_ID = 0x00000000,
		REGISTER_ID_MESSAGEBOX_DATA = 0x00000004,
		REGISTER_ID_MESSAGEBOX_CONTROL = 0x00000008,
		REGISTER_ID_MESSAGEBOX_STATUS = 0x0000000c,
		REGISTER_ID_MESSAGEBOX_START = 0x00000010,
		REGISTER_ID_MESSAGEBOX_END = 0x00000014,
		REGISTER_ID_MESSAGEBOX_IRQMASK = 0x00000018,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

