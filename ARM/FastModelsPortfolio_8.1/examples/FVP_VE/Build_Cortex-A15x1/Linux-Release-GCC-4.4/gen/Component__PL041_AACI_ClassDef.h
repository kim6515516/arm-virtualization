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
 * Class definition for Component PL041_AACI.
 */

#ifndef Component_Component__PL041_AACI_ClassDef_h_
#define Component_Component__PL041_AACI_ClassDef_h_

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

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL041_AACI.lisa"

    
        #include    "components/ac97_defs.h"
        #include    "stdlib.h"
        #include    "string.h"
        #define AACI_TRACE if(!0) ; else printf
        
        // Bit positions
        #define TXCR_TXEN       (1<<0)
        #define TXCR_TX1        (1<<1)
        #define TXCR_TX2        (1<<2)
        #define TXCR_TX3        (1<<3)
        #define TXCR_TX4        (1<<4)
        #define TXCR_TX5        (1<<5)
        #define TXCR_TX6        (1<<6)
        #define TXCR_TX7        (1<<7)
        #define TXCR_TX8        (1<<8)
        #define TXCR_TX9        (1<<9)
        #define TXCR_TX10       (1<<10)
        #define TXCR_TX11       (1<<11)
        #define TXCR_TX12       (1<<12)
        #define TXCR_TSIZE_MASK (0x3<<13)
        #define TXCR_16B        (0x0<<13)
        #define TXCR_18B        (0x1<<13)
        #define TXCR_20B        (0x2<<13)
        #define TXCR_12B        (0x3<<13)
        #define TXCR_COMPACT    (1<<15)
        #define TXCR_FEN        (1<<16)
        
        #define SR_TXFE         (1<<1)
        #define SR_TXHE         (1<<3)
        #define SR_TXFF         (1<<5)
        #define SR_TXUR         (1<<9)
        
        #define ISR_TXCINTR     (1<<0)
        #define ISR_TXINTR      (1<<2)
        #define ISR_URINTR      (1<<5)
        
        #define INTCLR_TXUEC1   (1<<5)
        
        #define MAINCR_SL2TXEN (1<<6)
        #define MAINCR_SL2RXEN (1<<5)
        #define MAINCR_SL1TXEN (1<<4)
        #define MAINCR_SL1RXEN (1<<3)
        #define MAINCR_IFE     (1<<0)
        
        #define SLFR_SL2TXEMPTY (1<<9)
        #define SLFR_SL2RXVALID (1<<8)
        #define SLFR_SL1TXEMPTY (1<<7)
        #define SLFR_SL1RXVALID (1<<6)
    
#line 89 "./Linux-Release-GCC-4.4/gen/Component__PL041_AACI_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__AudioControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PL080_DMAC_DmaPortProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVDevice_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
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

class ParameterFilter_busslave_of_PVBusSlave_to_PL041_AACI : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_PL041_AACI()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__PL041_AACI: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *busslave;
	sg::ComponentBase *timer;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer__;


    // abstract ports
	FVP_VE_Cortex_A15x1__ClockSignal clk_in_ref;
	FVP_VE_Cortex_A15x1__AudioControl audio;
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__Signal irq;
	FVP_VE_Cortex_A15x1__PL080_DMAC_DmaPortProtocol dma_rx;
	FVP_VE_Cortex_A15x1__PL080_DMAC_DmaPortProtocol dma_tx;
	FVP_VE_Cortex_A15x1__TimerCallback timer_cbHandler;
	FVP_VE_Cortex_A15x1__PVDevice device;
	FVP_VE_Cortex_A15x1__TimerControl __PL041_AACI_internal_1;


    // resources
    std::string application_pathname;


#line 76 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL041_AACI.lisa"
   
        // Real depth of FIFO in Normal (non compact) mode
        size_t              depth;
        // The effective depth of the FIFO in stereo samples
        size_t              effectiveDepth;
        // Half effective depth of the FIFO in stereo samples
        size_t              effectiveHalfDepth;
        
        // Underlying Audio Buffer
        PVAudioBuffer*      audioBuf;
        
        // Time in ticks of input clock between updates
        uint32_t            tDelta;
        // Number of samples which ought to have drained from the FIFO during
        // the tDelta period.
        uint32_t            sampleDelta;
        
        // Is the data being written stereo?
        bool                isStereo;
        
        // Is the AACI set to compact mode?
        bool                isCompact;
        
        // Is the AACI in a legal config (ie only slot 3 or 4 enabled) we can't
        // deal with other configurations.
        bool                isLegal;
        
        // Are we writing into the audio buffer if DR1 is written to? We can
        // only write on every second sample as we must write stereo samples.
        bool                isWrite;
        
        // The previous sample so we can write stereo samples into the audio
        // buffer.
        int16_t             prevSample;
        
        // Is transmit enabled (and therefore is the FIFO being drained)
        bool                isRunning;
        
        // Interrupt Status
        bool                irq_signal;
        
        // AACI Registers
        uint32_t rxcr1;
        uint32_t txcr1;
        uint32_t sr1;
        /*! Contains the actual status of the interrupts must be masked with
        * ie1 to generate the real isr1 for reading */
        uint32_t isr1;
        uint32_t ie1;
        
        uint32_t rxcr2;
        uint32_t txcr2;
        uint32_t sr2;
        /*! Contains the actual status of the interrupts must be masked with
        * ie2 to generate the real isr2 for reading */
        uint32_t isr2;
        uint32_t ie2;
        
        uint32_t rxcr3;
        uint32_t txcr3;
        uint32_t sr3;
        /*! Contains the actual status of the interrupts must be masked with
        * ie3 to generate the real isr3 for reading */
        uint32_t isr3;
        uint32_t ie3;
        
        uint32_t rxcr4;
        uint32_t txcr4;
        uint32_t sr4;
        /*! Contains the actual status of the interrupts must be masked with
        * ie4 to generate the real isr4 for reading */
        uint32_t isr4;
        uint32_t ie4;
        
        uint32_t sl1rx;
        uint32_t sl1tx;
        uint32_t sl2rx;
        uint32_t sl2tx;
        uint32_t sl12rx;
        uint32_t sl12tx;
        
        uint32_t slfr;
        /*! Contains the actual status of the interrupts must be masked with
        * slien to generate the real slistat for reading */
        uint32_t slistat;
        uint32_t slien;
        uint32_t maincr;
        uint32_t rst;
        uint32_t sync;
        uint32_t mainfr;
        
        uint8_t* SmBuffer0;
        uint8_t* SmBuffer1;
        uint8_t* SmBuffer2;
        uint8_t* SmBuffer3;
        
        // LM4529A Registers
        uint32_t masterVol;
        uint32_t auxVol;
        uint32_t monoVol;
        uint32_t beepVol;
        uint32_t phoneVol;
        uint32_t micVol;
        uint32_t lineVol;
        uint32_t cdVol;
        uint32_t videoVol;
        uint32_t auxinVol;
        uint32_t pcmVol;
        uint32_t recVol;
        uint32_t recSel;
        uint32_t recGain;
        uint32_t gen;
        uint32_t pdctrl;
        uint32_t eaid;
        uint32_t eactrl;
        uint32_t pcmDACRate;
        uint32_t pcmADCRate;
        
        // REGISTERS available to the debugger. No registers are currently read sensitive
        MxU32  RXCR1       ;
        MxU32  TXCR1      ;
        MxU32  SR1                ;
        MxU32  ISR1      ;
        MxU32  IE1      ;
        MxU32  RXCR2       ;
        MxU32  TXCR2      ;
        MxU32  SR2                ;
        MxU32  ISR2      ;
        MxU32  IE2      ;
        MxU32  RXCR3       ;
        MxU32  TXCR3      ;
        MxU32  SR3                ;
        MxU32  ISR3      ;
        MxU32  IE3      ;
        MxU32  RXCR4       ;
        MxU32  TXCR4      ;
        MxU32  SR4                ;
        MxU32  ISR4      ;
        MxU32  IE4      ;
        MxU32  SL1RX            ;
        MxU32  SL1TX           ;
        MxU32  SL2RX            ;
        MxU32  SL2TX           ;
        MxU32  SL12RX           ;
        MxU32  SL12TX          ;
        MxU32  LSFR            ;
        MxU32  SLISTAT         ;
        MxU32  SLIEN         ;
        MxU32  ALLINTCLR          ;
        MxU32  MAINCR                  ;
        MxU32  RESET                 ;
        MxU32  SYNC                  ;
        MxU32  ALLINTS         ;
        MxU32  MAINFR                    ;
        
        // the fifo write registers are not currently shown to the debugger
    
#line 316 "./Linux-Release-GCC-4.4/gen/Component__PL041_AACI_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__PL041_AACI(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__PL041_AACI();

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

	void ResetRegisters();
	void resetLM4549Registers();
	void updateInterrupts();
	void setSlot1rx(uint32_t data);
	void setSlot2rx(uint32_t data);
	uint32_t getSlot2rx();
	void getSlot2tx(uint32_t* dest);
	void slot1tx();
	void handleIntClr(uint32_t data);
	void handleMainCR(uint32_t newValue);
	void updateFIFO1(uint32_t sim_ms);
	void writeFIFO1(uint32_t data);
	void init();
	void terminate();
	void reset(int level);
	void updateControl1();
	uint32_t registerRead(pv::bus_addr_t device_addr);
	void registerWrite(pv::bus_addr_t device_addr, uint32_t data);
	AccessFuncResult debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects);
	AccessFuncResult debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects);
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	void abstract_port__dma_rx__response(uint32_t response);
	void abstract_port__dma_tx__response(uint32_t response);
	uint32_t abstract_port__timer_cbHandler__signal();
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


	ParameterFilter_busslave_of_PVBusSlave_to_PL041_AACI parameterFilter_busslave_of_PVBusSlave_to_PL041_AACI__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_PL041_AACI__;


    // definition of parameter IDs as constants for use in parameter access functions


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_RXCR1 = 0x00000000,
		REGISTER_ID_TXCR1 = 0x00000004,
		REGISTER_ID_SR1 = 0x00000008,
		REGISTER_ID_ISR1 = 0x0000000c,
		REGISTER_ID_IE1 = 0x00000010,
		REGISTER_ID_RXCR2 = 0x00000014,
		REGISTER_ID_TXCR2 = 0x00000018,
		REGISTER_ID_SR2 = 0x0000001c,
		REGISTER_ID_ISR2 = 0x00000020,
		REGISTER_ID_IE2 = 0x00000024,
		REGISTER_ID_RXCR3 = 0x00000028,
		REGISTER_ID_TXCR3 = 0x0000002c,
		REGISTER_ID_SR3 = 0x00000030,
		REGISTER_ID_ISR3 = 0x00000034,
		REGISTER_ID_IE3 = 0x00000038,
		REGISTER_ID_RXCR4 = 0x0000003c,
		REGISTER_ID_TXCR4 = 0x00000040,
		REGISTER_ID_SR4 = 0x00000044,
		REGISTER_ID_ISR4 = 0x00000048,
		REGISTER_ID_IE4 = 0x0000004c,
		REGISTER_ID_SL1RX = 0x00000050,
		REGISTER_ID_SL1TX = 0x00000054,
		REGISTER_ID_SL2RX = 0x00000058,
		REGISTER_ID_SL2TX = 0x0000005c,
		REGISTER_ID_SL12RX = 0x00000060,
		REGISTER_ID_SL12TX = 0x00000064,
		REGISTER_ID_LSFR = 0x00000068,
		REGISTER_ID_SLISTAT = 0x0000006c,
		REGISTER_ID_SLIEN = 0x00000070,
		REGISTER_ID_ALLINTCLR = 0x00000074,
		REGISTER_ID_MAINCR = 0x00000078,
		REGISTER_ID_RESET = 0x0000007c,
		REGISTER_ID_SYNC = 0x00000080,
		REGISTER_ID_ALLINTS = 0x00000084,
		REGISTER_ID_MAINFR = 0x00000088,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

