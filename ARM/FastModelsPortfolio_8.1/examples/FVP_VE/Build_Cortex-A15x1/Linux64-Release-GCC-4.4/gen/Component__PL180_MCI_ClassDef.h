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
 * Class definition for Component PL180_MCI.
 */

#ifndef Component_Component__PL180_MCI_ClassDef_h_
#define Component_Component__PL180_MCI_ClassDef_h_

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

#line 18 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL180_MCI.lisa"


#define PL180_ERROR           if (!0) ; else printf
#define PL180_INTERRUPTS      if (!0) ; else printf
#define PL180_TRACE           if (!0) ; else printf
#define PL180_DEBUG           if (!0) ; else printf
#define PL180_DEBUG_REGISTERS if (!0) ; else printf
#define PL180_DEBUG_READ      if (!0) ; else printf
#define PL180_DEBUG_WRITE     if (!0) ; else printf

#line 48 "./Linux64-Release-GCC-4.4/gen/Component__PL180_MCI_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__MMC_Protocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
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

class ParameterFilter_busslave_of_PVBusSlave_to_PL180_MCI : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_PL180_MCI()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__PL180_MCI: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *busslave;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;


    // abstract ports
	FVP_VE_Cortex_A15x1__Signal MCIINTR[2];
	FVP_VE_Cortex_A15x1__MMC_Protocol mmc_m;
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__PVDevice device;


    // resources
    std::string application_pathname;


#line 41 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL180_MCI.lisa"

    // debugger visible registers
    MxU8  MCIPower   
         
                       ;
    MxU16  MCIClock   
         
                         ;
    MxU32  MCIArgument        
         
                      ;
    MxU16  MCICommand         
         
                      ;
    MxU8  MCIRespCmd   
         
                       ;
    MxU32  MCIResponse0           
         
                      ;
    MxU32  MCIResponse1           
         
                      ;
    MxU32  MCIResponse2           
         
                      ;
    MxU32  MCIResponse3           
         
                      ;
    MxU32  MCIDataTimer                  
         
                      ;
    MxU16  MCIDataLength        
         
                      ;
    MxU8  MCIDataCtrl       
         
                       ;
    MxU16  MCIDataCnt                
         
                      ;
    MxU32  MCIStatus             
         
                      ;
    MxU16  MCIClear              
         
                      ;
    MxU32  MCIMask0   
         
                      ;
    MxU32  MCIMask1   
         
                      ;
    MxU8  MCISelect     
         
                       ;
    MxU16  MCIFifoCnt                
         
                      ;

    MxU32  MCIFIFO          
         
                      ;

    // ID registers
    MxU8  MCIPeriphID0      
         
                        ;
    MxU8  MCIPeriphID1     
         
                        ;
    MxU8  MCIPeriphID2    
         
                        ;
    MxU8  MCIPeriphID3    
         
                        ;
    MxU8  MCIPCellID0       
         
                        ;
    MxU8  MCIPCellID1      
         
                        ;
    MxU8  MCIPCellID2     
         
                        ;
    MxU8  MCIPCellID3     
         
                        ;


    // Internal state
    uint8_t stat_CmdSent;
    uint8_t stat_CmdTimeOut;
    uint8_t stat_CmdRespEnd;
    uint8_t stat_DataEnd;
    uint8_t stat_DataBlockEnd;

    uint8_t        *tx_addr;
    const uint8_t  *rx_addr;
    uint32_t        transfer_len;  // These members reflect state of the MMC-facing
    uint32_t        transfer_idx;  // current transfer

    bool            receiving;     // flag to indicate that receive is in process
    // (this is the status register RxActive bit, and is true when the data path
    // state machine is in the WAIT_R or RECEIVE states.)
    bool            transmitting;  // flag to indicate that receive is in process
    // (set after first Tx call from MMC card)

    uint32_t  data_ctrl_len;
    uint32_t nrread;
    bool doTrace;

    enum {
        MCIStatus_STATIC_MASK  = ((1<<11)-1),
        MCIStatus_CMDCRCFAIL_BIT     = 0,
        MCIStatus_DATACRCFAIL_BIT    = 1,
        MCIStatus_CMDTIMEOUT_BIT     = 2,
        MCIStatus_DATATIMEOUT_BIT    = 3,
        MCIStatus_TXUNDERRUN_BIT     = 4,
        MCIStatus_RXOVERRUN_BIT      = 5,
        MCIStatus_CMDRESPEND_BIT     = 6,
        MCIStatus_CMDSENT_BIT        = 7,
        MCIStatus_DATAEND_BIT        = 8,
        MCIStatus_STARTBITERROR_BIT  = 9,
        MCIStatus_DATABLOCKEND_BIT   = 10,

        MCIStatus_TXACTIVE_BIT       = 12,
        MCIStatus_RXACTIVE_BIT       = 13,
        MCIStatus_TXFIFOHALFEMPTY_BIT = 14, // (TXFIFOHALFFULL_BIT)
        MCIStatus_RXFIFOHALFFULL_BIT = 15,
        MCIStatus_TXFIFOFULL_BIT     = 16,
        MCIStatus_RXFIFOFULL_BIT     = 17,
        MCIStatus_TXFIFOEMPTY_BIT    = 18,
        MCIStatus_RXFIFOEMPTY_BIT    = 19,
        MCIStatus_TXDATAAVAIL_BIT    = 20,
        MCIStatus_RXDATAAVAIL_BIT    = 21,

    }; // MCIStatus register defines

    enum {
        MCI_FIFOSIZE     = 16,
        MCI_FIFOHALFSIZE = 8,
    };

    enum {
        MCIDataCtrl_MASK            = 0xff,
        MCIDataCtrl_EN_MASK         = (1     ),
        MCIDataCtrl_DIR_MASK        = (1  <<1),
        MCIDataCtrl_MODE_MASK       = (1  <<2),
        MCIDataCtrl_DMA_MASK        = (1  <<3),
        MCIDataCtrl_BLOCKSIZE_MASK  = (0xf<<4),
    };

    sg::Signal::State MCIINTR_int[2];


#line 264 "./Linux64-Release-GCC-4.4/gen/Component__PL180_MCI_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__PL180_MCI(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__PL180_MCI();

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

	void init_id_registers();
	void init();
	void reset(int level);
	void common_reset();
	uint32_t read_word_from_mmc();
	void write_word_to_mmc(uint32_t data);
	void update_status(bool update_static);
	void clear_status(uint32_t bits);
	void merge_dynamic_status();
	char* intstat();
	void update_static_status();
	void update_intr(uint32_t index, uint32_t status);
	void sendCmd(uint32_t data);
	uint32_t registerRead(uint32_t addr);
	void registerWrite(uint32_t addr, uint32_t data);
	AccessFuncResult debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects);
	AccessFuncResult debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects);
	const char* register_name(uint32_t off);
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
	bool abstract_port__mmc_m__Rx(const uint8_t* block, uint32_t len);
	bool abstract_port__mmc_m__Tx(uint8_t* block, uint32_t len);
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


	ParameterFilter_busslave_of_PVBusSlave_to_PL180_MCI parameterFilter_busslave_of_PVBusSlave_to_PL180_MCI__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_PL180_MCI__;


    // definition of parameter IDs as constants for use in parameter access functions


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_MCIPower = 0x00000000,
		REGISTER_ID_MCIClock = 0x00000004,
		REGISTER_ID_MCIArgument = 0x00000008,
		REGISTER_ID_MCICommand = 0x0000000c,
		REGISTER_ID_MCIRespCmd = 0x00000010,
		REGISTER_ID_MCIResponse0 = 0x00000014,
		REGISTER_ID_MCIResponse1 = 0x00000018,
		REGISTER_ID_MCIResponse2 = 0x0000001c,
		REGISTER_ID_MCIResponse3 = 0x00000020,
		REGISTER_ID_MCIDataTimer = 0x00000024,
		REGISTER_ID_MCIDataLength = 0x00000028,
		REGISTER_ID_MCIDataCtrl = 0x0000002c,
		REGISTER_ID_MCIDataCnt = 0x00000030,
		REGISTER_ID_MCIStatus = 0x00000034,
		REGISTER_ID_MCIClear = 0x00000038,
		REGISTER_ID_MCIMask0 = 0x0000003c,
		REGISTER_ID_MCIMask1 = 0x00000040,
		REGISTER_ID_MCISelect = 0x00000044,
		REGISTER_ID_MCIFifoCnt = 0x00000048,
		REGISTER_ID_MCIFIFO = 0x00000080,
		REGISTER_ID_MCIPeriphID0 = 0x00000fe0,
		REGISTER_ID_MCIPeriphID1 = 0x00000fe4,
		REGISTER_ID_MCIPeriphID2 = 0x00000fe8,
		REGISTER_ID_MCIPeriphID3 = 0x00000fec,
		REGISTER_ID_MCIPCellID0 = 0x00000ff0,
		REGISTER_ID_MCIPCellID1 = 0x00000ff4,
		REGISTER_ID_MCIPCellID2 = 0x00000ff8,
		REGISTER_ID_MCIPCellID3 = 0x00000ffc,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

