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
 * Class definition for Component MMC.
 */

#ifndef Component_Component__MMC_ClassDef_h_
#define Component_Component__MMC_ClassDef_h_

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

#line 23 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/MMC.lisa"


#define MMC_TRACE          if (!0) ; else printf
#define MMC_DEBUG_TIMER    if (!0) ; else printf
#define MMC_DEBUG          if (!0) ; else printf
#define MMC_DEBUG_VERBOSE  if (!0) ; else printf
#define MMC_DEBUG_READ     if (!0) ; else printf
#define MMC_DEBUG_WRITE    if (!0) ; else printf
#define MMC_ERROR          if (!0) ; else printf
#define MMC_UNSUPPORTED    if (!0) ; else printf

//#define DEFAULT_BLKBITS       (9)
#define DEFAULT_BLKBITS       (11)

#include "hostconf/zinttypes.h"
#include "components/BackingStore.h"


    /*
     * Notation of following status bits is ST_[T]_[CC]_NAME
     * Where [T] is the Type
     *  - E - Error bit
     *  - S - Status bit
     *  - E - Detected & set for response
     *  - X - Detected & set during execution
     * Where [CC] is the Clear Condition
     *  - A - Depends on current card state
     *  - B - Always related to the previous command. Reception
     *        of a valid command will clear it (with a delay of
     *        one command).
     *  - C - Clear on read
     */

    // Command argument was out of the allowed range for the card
#define ST_ER_C_OUT_OF_RANGE        (1 << 31)

    // Misaligned address (not matching the block length) was used in command
#define ST_ERX_C_ADDRESS_ERROR      (1 << 30)

    // Transferred block length is not allowed for the card, or the number
    // of transferred bytes does not match the block length.
#define ST_ER_C_BLOCK_LEN_ERROR     (1 << 29)

    // Error in the sequence of erase commands occurred
#define ST_ER_C_ERASE_SEQ_ERROR     (1 << 28)

    // Invalid selection of write blocks for erase occurred
#define ST_EX_C_ERASE_PARAM         (1 << 27)

    // Attempt to program a write-protected block
#define ST_ERX_C_WP_VIOLATION       (1 << 26)

#define ST_SX_A_CARD_LOCKED         (1 << 25)
#define ST_ERX_C_LOCK_UNLOCK_FAILED (1 << 24)

    // CRC check of previous command failed
#define ST_ER_B_COM_CRC_ERROR       (1 << 23)

    // Command not legal for the card state
#define ST_ER_B_ILLEGAL_COMMAND     (1 << 22)

#define ST_EX_C_CARD_ECC_FAILED     (1 << 21)
#define ST_ERX_C_CC_ERROR           (1 << 20)

    // Unknown error
#define ST_ERX_C_ERROR              (1 << 19)

    // We don't set these
#define ST_EX_C_UNDERRUN            (1 << 18)
#define ST_EX_C_OVERRUN             (1 << 17)

    // - CID Register has been written and cannot be over written.
    // - CSD read-only section does not match the card content.
    // - Attempt made to reverse copy (set as original) or permanent WP
    //   (unprotected) bits.
#define ST_ERX_C_CID_CSD_OVERWRITE  (1 << 16)

    // Only partial address space was erased due to existing write
    // protected blocks.
#define ST_SX_C_WP_ERASE_SKIP       (1 << 15)

    // Command executed without using ECC
#define ST_SX_A_CARD_ECC_DISABLED  (1 << 14)

    // Erase sequence was cleared before command execution because an out
    // of sequence erase command was received.
#define ST_SR_C_ERASE_RESET         (1 << 13)

    // See card_state_t below
#define ST_SX_B_CURRENT_STATE_SHIFT (9)
#define ST_SX_B_CURRENT_STATE       (0xf << ST_SX_B_CURRENT_STATE_SHIFT)

    // State of buffer-empty signaling on bus
#define ST_SX_A_READY_FOR_DATA      (1 << 8)

    // Not supported
#define ST_SR_C_APP_CMD             (1 << 5)

    // Bits that always reflect current state are:
    // ST_SX_A_READY_FOR_DATA, ST_SX_A_CARD_ECC_DISABLED, ST_SX_A_CARD_LOCKED

    // Bits that reflect state from the previous command
    // ST_SX_B_CURRENT_STATE, ST_ER_B_ILLEGAL_COMMAND, ST_ER_B_COM_CRC_ERROR

#define ST__C_BITS (ST_SR_C_APP_CMD | ST_SR_C_ERASE_RESET | ST_SX_C_WP_ERASE_SKIP | \
        ST_ERX_C_CID_CSD_OVERWRITE | ST_EX_C_OVERRUN | ST_EX_C_UNDERRUN | \
        ST_ERX_C_ERROR | ST_ERX_C_CC_ERROR | ST_EX_C_CARD_ECC_FAILED | \
        ST_ERX_C_LOCK_UNLOCK_FAILED | ST_ERX_C_WP_VIOLATION | ST_EX_C_ERASE_PARAM | \
        ST_ER_C_ERASE_SEQ_ERROR | ST_ER_C_BLOCK_LEN_ERROR | \
        ST_ERX_C_ADDRESS_ERROR | ST_ER_C_OUT_OF_RANGE)


    // 4-bit field in status, codes 9-15 reserved
    typedef enum {
        MMCS_IDLE       = 0,
        MMCS_READY      = 1,
        MMCS_ID         = 2,
        MMCS_STANDBY    = 3,
        MMCS_TRANSFER   = 4,    // Ready to transfer
        MMCS_DATA       = 5,    // Transmitting
        MMCS_RECEIVE    = 6,
        MMCS_PROGRAM    = 7,
        MMCS_DISABLED   = 8,
    } card_state_t;

    // Our CID storage type (MMC version 3.1)
    typedef struct {
        // 128 bits of card ID.
        uint8_t    manfid;       // [127:120]
        uint16_t   oemid;        // [119:104]
        char       prod_name[6]; // [103: 56]
        uint8_t    prod_rev;     // [ 55: 48]
        uint32_t   serial;       // [ 47: 16]
        uint8_t    month:4;      // [ 15: 12]             (BCD)
        uint8_t    year:4;       // [ 11:  8] 1997+year   (in BCD)
        uint8_t    res;          // bottom byte is unused (or 7:1 is CRC?)
    } mmc_cid_t;

    // CSD Struct version (used in CSD csd_v)
#define CSD_VER_1_0  0
#define CSD_VER_1_1  1
#define CSD_VER_1_2  2
#define CSD_EXT_CSD  3

    // Spec version defines (used in CSD mmca_v)
#define MMCA_VERSION_1_0  0
#define MMCA_VERSION_1_2  0
#define MMCA_VERSION_1_4  1
#define MMCA_VERSION_2_x  2
#define MMCA_VERSION_3_x  3
#define MMCA_VERSION_4_x  4

    // Card command class definitions (as per CSD's cmdclass)
#define CCC_BASIC        (1<<0)    /* CMD0,1,2,3,4,7,9,10,12,13,15 */
#define CCC_READ         (1<<1)    /* CMD11 */
#define CCC_BLOCK_READ   (1<<2)    /* CMD16,17,18 */
#define CCC_WRITE        (1<<3)    /* CMD20 */
#define CCC_BLOCK_WRITE  (1<<4)    /* CMD16,23,24,25,26,27 */
#define CCC_ERASE        (1<<5)    /* CMD32,33,34,35,36,37,38,39 */
#define CCC_WRITE_PROT   (1<<6)    /* CMD28,29,30 */
#define CCC_LOCK         (1<<7)    /* CMD16,42 */
#define CCC_APP          (1<<8)    /* CMD55,56,57 */
#define CCC_IO_MODE      (1<<9)    /* CMD5,39,40,52,53 */
#define CCC_SWITCH       (1<<10)   /* CMD6,34,35,36,37,50 */


    // Note this structure is different between SD and MMC
    // We've represented MMC CSD 1.2 here
    // Storage (and response) type for the CSD Register
    typedef struct {
        // 128 bits of Card-Specific Data (CSD) [127:96] [95:64] [63:32] [31:0]
#if 0
        uint32_t   csd_v      :2;   // [127:126] - version of the CSD structure (1.1)
        uint32_t   mmca_v     :4;   // [125:122] - MMC Spec version
        uint32_t   w0_res1    :2;   // [121:119] - unused. That's the top byte
        uint32_t   tacc_ns_m  :4;   // [118:115] - data time out in ns (mant)
        uint32_t   tacc_ns_e  :3;   // [114:112] - data time out in ns (exp)
        uint32_t   tacc_clks  :8;   // [111:104] - data time out in clocks
        uint32_t   w0_res2    :2;   // [103:102] - unused.
        uint32_t   max_dtr_m  :4;   // [101:99 ] - Data Transfer Rate (mant)
        uint32_t   max_dtr_e  :3;   // [ 98:96 ] - (exp)

        uint32_t   cmdclass   :12;  // [ 95:84 ] - command class bits
        uint32_t   read_blkbits:4;  // [ 83:80 ] - log2(read block size) (e.g. 9)
        uint32_t   read_partial:1;  // [    79 ] - ???
        uint32_t   write_misal:1;   // [    78 ] - ???
        uint32_t   read_misal :1;   // [    77 ] - ???
        uint32_t   w1_res1    :1;   // [    76 ] - apparently unused
        uint32_t   capacity_m2:12;  // [ 75:64 ] - capacity (mant) [(1+m)<<(e+2)]

        uint32_t   capacity_m1:2;   // [ 63:62 ] - straddles word boundary
        uint32_t   w2_res1    :12;  // [ 61:50 ] - unused
        uint32_t   capacity_e :3;   // [ 49:47 ] - capacity (exp)
        uint32_t   w2_res2    :15;  // [ 46:32 ] - unused

        uint32_t   w3_res1    :3;   // [ 31:29 ] - unused
        uint32_t   r2w        :3;   // [ 28:26 ] - factor used to scale timeout for write
        uint32_t   write_blkbits:4; // [ 25:22 ] - log2(write block size)
        uint32_t   write_partial:1; // [    21 ] - support for partial block write?
        uint32_t   w3_res2    :21;  // [ 20:0  ] - that's all folks
#endif
    } mmc_csd_t;

    // Hitachi spec says this should be arg >> 16 (but we're coding the controller too!)
#define ARG_RCA(a) (a >> 16)

    typedef struct {
        std::string img_file;       // the filename of the MMC image
    } mmc_conf_t;


#line 249 "./Linux-Release-GCC-4.1/gen/Component__MMC_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__MMC_Protocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__StateSignal_ClassDef.h"
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
Component__MMC: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *timer;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer__;


    // abstract ports
	FVP_VE_Cortex_A15x1__MMC_Protocol mmc;
	FVP_VE_Cortex_A15x1__StateSignal card_present;
	FVP_VE_Cortex_A15x1__ClockSignal clk_in;
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback_handler;
	FVP_VE_Cortex_A15x1__TimerControl __MMC_internal_1;
	FVP_VE_Cortex_A15x1__TimerCallback __MMC_internal_2;


    // resources
    std::string application_pathname;


#line 249 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/MMC.lisa"

    // Some MMC Card defaults
    const static uint32_t DEFAULT_BLOCKLEN = 512;
    const static uint32_t DEFAULT_BLOCKCOUNT = 0x80; // max to transfer

    // debugger visible registers. These registers aren't memory mapped,
    // but read by MMC command / responses
    MxU32  OCR_REG  
        
                       ;

    MxU32  CID_REG0  
        
                       ;
    MxU32  CID_REG1  
        
                       ;
    MxU32  CID_REG2  
        
                       ;
    MxU32  CID_REG3  
        
                       ;

    MxU32  CSD_REG0  
        
                       ;
    MxU32  CSD_REG1  
        
                       ;
    MxU32  CSD_REG2  
        
                       ;
    MxU32  CSD_REG3  
        
                       ;

    MxU16  RCA_REG  
        
                       ;

    MxU16  DSR_REG  
        
                       ;

    MxU32  BLOCKLEN_REG  
        
                       ;

    MxU32  STATUS_REG  
        
                       ;

    MxU32  BLOCK_COUNT_REG  
        
                       ;

    // Parameters

    const std::string  p_mmc_file  
                         ;

    const std::string  p_prodName  
                          ;
    const int32_t  p_prodRev  
                                 ;
    const int32_t  p_manid  
          /* Sandisk */          ;
    const int32_t  p_OEMid  
                               ;
    const int32_t  p_sernum  
                           ;
    const bool  p_fast_access  
                                ;

    // Internal state
    card_state_t  cstate;
    card_state_t  old_state;

    BackingStore *mmc_store;
    uint64_t      mmc_capacity;

    // send / receive state
    uint32_t    multiple_blocks;        // are we in a read/write multiple blocks mode?
    uint8_t    *data_pointer;           // data pointer in backing store
    uint32_t    block_address;          // the current block address

#line 389 "./Linux-Release-GCC-4.1/gen/Component__MMC_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__MMC(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__MMC();

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

	void CheckForBackingStoreError();
	void init();
	void terminate();
	void reset(int level);
	void common_reset();
	void reset_transfer();
	void advance_writeToCard_state();
	void flushWriteBlock();
	void dumpBlock(uint32_t adr, uint32_t len, uint8_t* p);
	void advance_readFromCard_state();
	bool check_address(uint32_t blk_addr);
	mmc_resp_t doCommand(mmc_cmd_t cmd, uint32_t arg, void* resp);
	void start_timer(uint32_t delay);
	void stop_timer();
	void assert_timer_is_stopped();
	mmc_resp_t start_rblock(mmc_cmd_t cmd, uint32_t arg, void* resp);
	mmc_resp_t start_wblock(mmc_cmd_t cmd, uint32_t arg, void* resp);
	void stuff_bits(uint32_t& w, uint32_t off, uint32_t s, uint32_t val);
	void init_csd_r(uint32_t* w);
	void init_cid_r(uint32_t* r);
	void update_csd(uint32_t* data);
	void update_cid(uint32_t* data);
	int nlz(uint32_t x);
	bool get_capacity(uint32_t* mp, uint32_t* ep);
	bool is_write_protected();
	bool cstate_change(card_state_t old, card_state_t n, mmc_cmd_t cmd, bool allow_anyway);
	uint32_t is_ready();
	void mmc_update_status(mmc_status_t* st);
	const char* MMCcmdName(mmc_cmd_t cmd);
	const char* MMCstateName(card_state_t st);
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	mmc_resp_t abstract_port__mmc__cmd(mmc_cmd_t cmd, uint32_t arg, void* resp);
	const char* abstract_port__mmc__cmd_name(mmc_cmd_t cmd);
	void abstract_port__mmc__Rx_rdy();
	void abstract_port__mmc__Tx_done();
	sg::Signal::State abstract_port__card_present__getValue();
	uint32_t abstract_port__timer_callback_handler__signal();

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
	enum
	{
		PARAMETER_ID_p_mmc_file = 0x1000001A,
		PARAMETER_ID_p_prodName = 0x1000001B,
		PARAMETER_ID_p_prodRev = 0x1000001C,
		PARAMETER_ID_p_manid = 0x1000001D,
		PARAMETER_ID_p_OEMid = 0x1000001E,
		PARAMETER_ID_p_sernum = 0x1000001F,
		PARAMETER_ID_p_fast_access = 0x10000020,
	};


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_OCR_REG = 0x00000000,
		REGISTER_ID_CID_REG0 = 0x00000004,
		REGISTER_ID_CID_REG1 = 0x00000005,
		REGISTER_ID_CID_REG2 = 0x00000006,
		REGISTER_ID_CID_REG3 = 0x00000007,
		REGISTER_ID_CSD_REG0 = 0x00000008,
		REGISTER_ID_CSD_REG1 = 0x00000009,
		REGISTER_ID_CSD_REG2 = 0x0000000a,
		REGISTER_ID_CSD_REG3 = 0x0000000b,
		REGISTER_ID_RCA_REG = 0x0000000c,
		REGISTER_ID_DSR_REG = 0x0000000d,
		REGISTER_ID_BLOCKLEN_REG = 0x0000000e,
		REGISTER_ID_STATUS_REG = 0x0000000f,
		REGISTER_ID_BLOCK_COUNT_REG = 0x00000010,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

