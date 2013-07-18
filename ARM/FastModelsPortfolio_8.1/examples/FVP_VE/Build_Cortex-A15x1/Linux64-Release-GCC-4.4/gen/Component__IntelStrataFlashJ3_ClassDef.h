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
 * Class definition for Component IntelStrataFlashJ3.
 */

#ifndef Component_Component__IntelStrataFlashJ3_ClassDef_h_
#define Component_Component__IntelStrataFlashJ3_ClassDef_h_

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

#line 12 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/Common/LISA/IntelStrataFlashJ3.lisa"

    
        #define NOR_FLASH_PROGRAM_COMMAND    0x00100010
        #define NOR_FLASH_READ_ARRAY         0x00FF00FF
        #define NOR_FLASH_READ_STATUS        0x70707070
        #define NOR_FLASH_PROGRAM_VERIFY     0x00D000D0
        #define NOR_FLASH_BYTE_WORD_PROGRAM  0x00400040
        #define NOR_FLASH_ID_MODE            0x00900090
        #define NOR_FLASH_BLOCK_WRITE_MODE   0x00E800E8
        #define NOR_FLASH_STATUS_READY_MASK  0x00800080
        #define NOR_FLASH_CFI_QUERY_COMMAND  0x00980098
        #define NOR_FLASH_MAX_WRITE_BUFF     0x80
        #define NOR_FLASH_BLOCK_ERASE        0x00200020
        #define NOR_FLASH_BLOCK_LOCK_CONFIRM 0x00010001
        #define NOR_FLASH_BLOCK_LOCK_BITS    0x00600060

        enum IntelStrataFlashJ3_BlockWriteState
        {
            IntelStrataFlashJ3_BLOCK_WRITE_COUNT,                      // first write is word count-1
            IntelStrataFlashJ3_BLOCK_WRITE_START,                      // then buffer address + first data
            IntelStrataFlashJ3_BLOCK_WRITE_CONTINUE                    // then other data until a confirm command
        };
    
#line 61 "./Linux64-Release-GCC-4.4/gen/Component__IntelStrataFlashJ3_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__FlashLoaderPort_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBusSlaveControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVDevice_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_mbs_of_PVBusSlave_to_IntelStrataFlashJ3 : public ParameterFilter
{
public:
	ParameterFilter_mbs_of_PVBusSlave_to_IntelStrataFlashJ3()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FORWARDED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" ); // forwarded from "size"
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__IntelStrataFlashJ3: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *mbs;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_mbs__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__PVBusSlaveControl mbs_control;
	FVP_VE_Cortex_A15x1__PVDevice mem_port;
	FVP_VE_Cortex_A15x1__FlashLoaderPort flashloader;


    // resources
    std::string application_pathname;


#line 53 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/Common/LISA/IntelStrataFlashJ3.lisa"

        const uint32_t   size           ;
             ;
        uint8_t       cfi_data[64];

        uint32_t block_size_bits;                     // number of address bits in one block region.
        uint32_t blocks;                              // number of blocks.
        uint32_t edit_block;                          // which block is currently being programmed.
        uint32_t edit_state;                          // the flash state variable.
        uint32_t erase_region_size;                   // size of the erase region

        uint32_t block_write_state;
        uint32_t block_write_address;
        uint32_t block_write_count;

        bool in_read_special_mode;

        pv::bus_addr_t bytes;                      // size of the flash device in bytes.
        uint32_t fill1, fill2;                       // pattern that needs to be programmed into the flash if needed.

    
#line 141 "./Linux64-Release-GCC-4.4/gen/Component__IntelStrataFlashJ3_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__IntelStrataFlashJ3(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__IntelStrataFlashJ3();

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

	void do_read(pv::bus_addr_t address, int width, uint32_t* data);
	void erase(pv::bus_addr_t base, pv::bus_addr_t end);
	void flash_write(pv::bus_addr_t address, int width, const uint32_t* data);
	void do_write(pv::bus_addr_t address, int width, uint32_t* data);
	void cfi_read(pv::bus_addr_t address, uint32_t* data);
	void set_read_special(pv::bus_addr_t base, pv::bus_addr_t end);
	void set_edit_block(uint32_t block);
	uint32_t address_to_offset(pv::bus_addr_t address);
	uint32_t cfi_length();
	uint32_t address_to_block(pv::bus_addr_t address);
	void flash_read(pv::bus_addr_t address, int width, uint32_t* data);
	void clear_read_special();
	pv::bus_addr_t block_to_address(uint32_t block);
	void set_read_array(pv::bus_addr_t base, pv::bus_addr_t end);
	pv::bus_addr_t get_size();
	uint32_t get_size_shift(uint32_t size);
	void init();
	AccessFuncResult debug_read(uint32_t , uint32_t , uint64_t offset, uint32_t size_in_maus, uint64_t* data, bool , sg::MemoryAccessContext* mac);
	AccessFuncResult debug_write(uint32_t , uint32_t , uint64_t offset, uint32_t size_in_maus, const uint64_t* data, bool , sg::MemoryAccessContext* mac);
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
	pv::Tx_Result abstract_port__mem_port__read(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__mem_port__write(pv::WriteTransaction tx);
	pv::Tx_Result abstract_port__mem_port__debugRead(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__mem_port__debugWrite(pv::WriteTransaction tx);
	uint32_t abstract_port__flashloader__loadFlashFile(FlashLoader* loader);
	uint32_t abstract_port__flashloader__saveFlashFile(FlashLoader* loader);

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


	ParameterFilter_mbs_of_PVBusSlave_to_IntelStrataFlashJ3 parameterFilter_mbs_of_PVBusSlave_to_IntelStrataFlashJ3__;


	CADIParameterProxy *cadiParameterProxy_mbs_of_PVBusSlave_to_IntelStrataFlashJ3__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_size = 0x10000009,
	};




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

