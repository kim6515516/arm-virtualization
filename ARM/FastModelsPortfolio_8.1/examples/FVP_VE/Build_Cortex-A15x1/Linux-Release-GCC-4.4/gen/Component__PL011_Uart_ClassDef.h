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
 * Class definition for Component PL011_Uart.
 */

#ifndef Component_Component__PL011_Uart_ClassDef_h_
#define Component_Component__PL011_Uart_ClassDef_h_

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

#line 16 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL011_Uart.lisa"

    
#include "hostconf/zinttypes.h"
#include "components/PL011-Uart-FIFO.h"
#include <stdio.h>
#include "sg/SGComponentTrace.h"

        #define TRACE_UART_INT   if (!0) ; else printf
        #define TRACE_UART_CLOCK if (!0) ; else printf
    
#line 48 "./Linux-Release-GCC-4.4/gen/Component__PL011_Uart_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockRateControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVDevice_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__SerialData_ClassDef.h"
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

class ParameterFilter_busslave_of_PVBusSlave_to_PL011_Uart : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_PL011_Uart()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__PL011_Uart: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *busslave;
	sg::ComponentBase *clk_divider;
	sg::ComponentBase *timer;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_clk_divider__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__SerialData serial_out;
	FVP_VE_Cortex_A15x1__ClockSignal clk_in_ref;
	FVP_VE_Cortex_A15x1__Signal intr;
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback_handler;
	FVP_VE_Cortex_A15x1__PVDevice device;
	FVP_VE_Cortex_A15x1__ClockRateControl __PL011_Uart_internal_1;
	FVP_VE_Cortex_A15x1__ClockSignal __PL011_Uart_internal_2;
	FVP_VE_Cortex_A15x1__TimerControl __PL011_Uart_internal_3;


    // resources
    std::string application_pathname;


#line 99 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL011_Uart.lisa"

        const uint32_t  clock_rate     ;
        const uint32_t  baud_rate     ;
        const bool  uart_enable     ;
        const bool  untimed_fifos     ;
        const std::string  out_file     ;
        const std::string  in_file      ;
        const bool  unbuffered_output       ;
        const std::string  in_file_escape_sequence      ;
        const bool  shutdown_on_eot      ;
        std::string  shutdown_tag       ;

        enum DataFlags
        {
            UartData_NODATA = (1<<12),
            UartData_OE = (1<<11),
            UartData_BE = (1<<10),
            UartData_PE = (1<<9),
            UartData_FE = (1<<8)
        };

        enum Signals
        {
            // UART Input signals
            SIG_RI = 1<<0,
            SIG_CTS = 1<<1,
            SIG_DSR = 1<<2,
            SIG_DCD = 1<<3,
            // UART Output signals
            SIG_DTR = 1<<4,
            SIG_RTS = 1<<5,
            SIG_Out1 = 1<<6,
            SIG_Out2 = 1<<7,

            SIG_OutMask = (SIG_DTR | SIG_RTS | SIG_Out1 | SIG_Out2),
            SIG_InMask = (SIG_RI | SIG_CTS | SIG_DSR | SIG_DCD)
        };

        enum Interrupts
        {
            ORINT  = (1<<10),
            CTSINT = (1<<1),
            RTINT  = (1<<6),
            TXINT  = (1<<5),
            RXINT  = (1<<4)
        };

        enum FRBits
        {
            // flags register bits
            UARTFR_RI   = (1<<8),
            UARTFR_TXFE = (1<<7),
            UARTFR_RXFE = (1<<4),
            UARTFR_RXFF = (1<<6),
            UARTFR_TXFF = (1<<5),
            UARTFR_BUSY = (1<<3),
            UARTFR_DCD  = (1<<2),
            UARTFR_DSR  = (1<<1),
            UARTFR_CTS  = (1<<0)
        };

        enum DRBits
        {
            // bits in the fifo/data register, these are shifted when read from rsr
            OVERRUN_ERR = (1<<11),
            BREAK_ERR   = (1<<10),
            PARITY_ERR  = (1<<9),
            FRAMING_ERR = (1<<8)
        };

        enum CRBits
        {
            // bits in the Control register
            UARTCR_CTSEn  = (1<<15),
            UARTCR_RTSEn  = (1<<14),
            UARTCR_RTS    = (1<<11),
            UARTCR_RXE    = (1<<9),
            UARTCR_TXE    = (1<<8),
            UARTCR_UARTEN = (1<<0)
        };

        // fifo TX/RX trigger points. Last three are reserved
        uint32_t fifoTide[8];
        char fifo_string[80];

        bool irq_signal;

        uint8_t  lcr_h;
        uint32_t irq;
        uint32_t irq_mask;
        uint16_t fr;
        uint16_t ibrd;
        uint8_t  fbrd;
        uint16_t ifls;
        uint16_t cr;
        uint16_t rsr;

        MxU32  UARTDR                    ;
        MxU32  UARTRSR      ;
        MxU32  UARTFR                                ;
        MxU32  UARTIBRD               ;
        MxU32  UARTFBRD            ;
        MxU32  UARTLCR_H                 ;
        MxU32  UARTCR                                 ;
        MxU32  UARTIFLS             ;
        MxU32  UARTIMSC                ;
        MxU32  UARTRIS                ;
        MxU32  UARTMIS             ;
        MxU32  UARTICR                     ;

        MxU8  UARTPeriphID[4]   ;
        MxU8  UARTCellID[4]   ;

        uint8_t  word_len;
        uint8_t  stop_bits;

        uint32_t rx_intlevel;
        uint32_t tx_intlevel;

        uint8_t  fifo_enabled;
        uint8_t  enabled;
        uint8_t  tx_enabled;
        uint8_t  rx_enabled;
        uint16_t overrun;
        uint16_t fifo_overrun;

        bool  rts;

        FIFO<uint32_t> in;
        FIFO<uint32_t> out;

        uint32_t last_dr;
        FILE *iFile;
        FILE *oFile;

        enum { INFILE_IDLE, INFILE_NEWLINE, INFILE_WAIT_PROMPT } infile_status;
        char     prompt[500];
        uint8_t  compare_index;
        uint8_t  delay_cnt;

        uint64_t ticks;
        sg::EventSource3<uint64_t /*ticks*/, uint8_t /*character*/, bool /*fifo_overflow*/> character_out;
        sg::EventSource3<uint64_t /*ticks*/, uint8_t /*character*/, bool /*fifo_overflow*/> character_in;
        sg::EventSource2<uint64_t /*ticks*/, char const*                                  > line_buffered_out;

        std::string line_buffer;
    
#line 267 "./Linux-Release-GCC-4.4/gen/Component__PL011_Uart_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__PL011_Uart(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__PL011_Uart();

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

	uint32_t byte_ticks();
	void log_hex2(char* dest, uint32_t val);
	void log_fifos();
	void update_clock();
	uint16_t update_fr();
	void set_rts(bool rts_enabled);
	void update_interrupts();
	void disconnect();
	void init();
	void terminate();
	void reset(int level);
	uint32_t registerRead(pv::bus_addr_t device_addr);
	void registerWrite(pv::bus_addr_t device_addr, uint32_t data);
	uint32_t debugRead(pv::bus_addr_t addr);
	uint32_t getUARTDR();
	uint32_t getUARTRSR();
	uint32_t getUARTFR();
	uint32_t getUARTIBRD();
	uint32_t getUARTFBRD();
	uint32_t getUARTLCR_H();
	uint32_t getUARTCR();
	uint32_t getUARTIFLS();
	uint32_t getUARTIMSC();
	uint32_t getUARTRIS();
	uint32_t getUARTMIS();
	void putUARTDR(uint32_t data);
	void putUARTECR(uint32_t );
	void putUARTIBRD(uint32_t data);
	void putUARTFBRD(uint32_t data);
	void putUARTLCR_H(uint32_t data);
	void putUARTCR(uint32_t data);
	void putUARTIFLS(uint32_t data);
	void putUARTIMSC(uint32_t data);
	void putUARTICR(uint32_t data);
	void flush();
	void character_out_event(uint8_t character_, bool fifo_overflow);
	uint32_t handleByteClockSignal();
	uint16_t computeInFile();
	void shutdownTest(uint8_t ch);
	void checkPrompt(uint8_t u8);
	AccessFuncResult debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects);
	AccessFuncResult debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects);
	void interconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	uint32_t abstract_port__timer_callback_handler__signal();
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


	ParameterFilter_busslave_of_PVBusSlave_to_PL011_Uart parameterFilter_busslave_of_PVBusSlave_to_PL011_Uart__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_PL011_Uart__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_clock_rate = 0x10000021,
		PARAMETER_ID_baud_rate = 0x10000022,
		PARAMETER_ID_uart_enable = 0x10000023,
		PARAMETER_ID_untimed_fifos = 0x10000024,
		PARAMETER_ID_out_file = 0x10000025,
		PARAMETER_ID_in_file = 0x10000026,
		PARAMETER_ID_unbuffered_output = 0x10000027,
		PARAMETER_ID_in_file_escape_sequence = 0x10000028,
		PARAMETER_ID_shutdown_on_eot = 0x10000029,
		PARAMETER_ID_shutdown_tag = 0x1000002A,
	};


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_UARTDR = 0x00000000,
		REGISTER_ID_UARTRSR = 0x00000004,
		REGISTER_ID_UARTFR = 0x00000018,
		REGISTER_ID_UARTIBRD = 0x00000024,
		REGISTER_ID_UARTFBRD = 0x00000028,
		REGISTER_ID_UARTLCR_H = 0x0000002c,
		REGISTER_ID_UARTCR = 0x00000030,
		REGISTER_ID_UARTIFLS = 0x00000034,
		REGISTER_ID_UARTIMSC = 0x00000038,
		REGISTER_ID_UARTRIS = 0x0000003c,
		REGISTER_ID_UARTMIS = 0x00000040,
		REGISTER_ID_UARTICR = 0x00000044,
		REGISTER_ID_UARTPeriphID = 0x00000001,
		REGISTER_ID_UARTPeriphID_0 = 0x00000001,
		REGISTER_ID_UARTPeriphID_1 = 0x00000002,
		REGISTER_ID_UARTPeriphID_2 = 0x00000003,
		REGISTER_ID_UARTPeriphID_3 = 0x00000005,
		REGISTER_ID_UARTCellID = 0x00000006,
		REGISTER_ID_UARTCellID_0 = 0x00000006,
		REGISTER_ID_UARTCellID_1 = 0x00000007,
		REGISTER_ID_UARTCellID_2 = 0x00000008,
		REGISTER_ID_UARTCellID_3 = 0x00000009,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

