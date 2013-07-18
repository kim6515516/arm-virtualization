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
 * Class definition for Component PL111_CLCD.
 */

#ifndef Component_Component__PL111_CLCD_ClassDef_h_
#define Component_Component__PL111_CLCD_ClassDef_h_

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

#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__LCD_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Value_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_pl11x_clcd_of_PL11x_CLCD_to_PL111_CLCD : public ParameterFilter
{
public:
	ParameterFilter_pl11x_clcd_of_PL11x_CLCD_to_PL111_CLCD()
	{
		ovrd_params["pixel_double_limit"] = eslapi::CADIParameterInfo_t(0x1000002B | PARAMETERFILTER_FORWARDED, "pixel_double_limit",eslapi::CADI_PARAM_INT, "Minimum LCD pixel width before display will be zoomed",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x12c), "300" ); // forwarded from "pixel_double_limit"
		ovrd_params["pl11x_behavior"] = eslapi::CADIParameterInfo_t(0x1000002C | PARAMETERFILTER_FIXED, "pl11x_behavior",eslapi::CADI_PARAM_INT, "Define PL11x behaviour. 0 for PL110, 1 for PL111",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__PL111_CLCD: public SystemGenComponent
{
public:
    // pointers to subcomponents
	Component__PL11x_CLCD *pl11x_clcd;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_pl11x_clcd__;


    // abstract ports
	FVP_VE_Cortex_A15x1__ClockSignal clk_in;
	FVP_VE_Cortex_A15x1__Value control;
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__LCD display;
	FVP_VE_Cortex_A15x1__Signal intr;
	FVP_VE_Cortex_A15x1__PVBus pvbus_m;


    // resources
    std::string application_pathname;


#line 22 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL111_CLCD.lisa"

        const uint32_t   pixel_double_limit     ;
        // APB registers
        MxU32   LCDTiming0                      ;
        MxU32    LCDTiming1                        ;
        MxU32  LCDTiming2              ;
        MxU32  LCDTiming3                        ;  // 17 bits
        MxU32  LCDUPBASE          ;
        MxU32  LCDLPBASE          ;
        MxU8  LCDControl                           ;  // 5 bits
        MxU16  LCDIMSC                                 ;
        MxU8  LCDRIS                     ;    // 5 bits
        MxU8  LCDMIS                  ;   // 5 bits
        MxU8  LCDICR                          ;    // 5 bits
        MxU32  LCDUPCURR             ;
        MxU32  LCDLPCURR             ;
        
        // Palette registers
        MxU32  LCDPalette[128]       ; // 0x200-0x3FC
        
        // Hardware cursor registers
        MxU32  CursorImage[256]      ; // 0x800-0xBFC
        MxU32  ClcdCrsrCtrl                         ;
        MxU32  ClcdCrsrConfig                   ;
        MxU32  ClcdCrsrPalette0                         ;
        MxU32  ClcdCrsrPalette1                         ;
        MxU32  ClcdCrsrXY                     ;
        MxU32  ClcdCrsrClip                   ;
        MxU32  ClcdCrsrIMSC        ;
        MxU32  ClcdCrsrICR                 ;
        MxU32  ClcdCrsrRIS            ;
        MxU32  ClcdCrsrMIS         ;
        
        // PrimeCell registers
        MxU8  CLCDPERIPHID0           ;
        MxU8  CLCDPERIPHID1          ;
        MxU8  CLCDPERIPHID2         ;  // 4 bits
        MxU8  CLCDPERIPHID3         ;
        MxU8  CLCDPCELLID0            ;
        MxU8  CLCDPCELLID1           ;
        MxU8  CLCDPCELLID2          ;
        MxU8  CLCDPCELLID3          ;
    
#line 142 "./Linux-Release-GCC-4.1/gen/Component__PL111_CLCD_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__PL111_CLCD(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__PL111_CLCD();

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

	AccessFuncResult debug_read(uint32_t reg_id, uint64_t* datap, bool side_effects);
	AccessFuncResult debug_write(uint32_t reg_id, const uint64_t* datap, bool side_effects);
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	void init();
	void terminate();
	void reset(int level);
	void reset(int level, int /*argc*/, char** /*argv*/);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();

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


	ParameterFilter_pl11x_clcd_of_PL11x_CLCD_to_PL111_CLCD parameterFilter_pl11x_clcd_of_PL11x_CLCD_to_PL111_CLCD__;


	CADIParameterProxy *cadiParameterProxy_pl11x_clcd_of_PL11x_CLCD_to_PL111_CLCD__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_pixel_double_limit = 0x1000002B,
	};


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_LCDTiming0 = 0x00000000,
		REGISTER_ID_LCDTiming1 = 0x00000004,
		REGISTER_ID_LCDTiming2 = 0x00000008,
		REGISTER_ID_LCDTiming3 = 0x0000000c,
		REGISTER_ID_LCDUPBASE = 0x00000010,
		REGISTER_ID_LCDLPBASE = 0x00000014,
		REGISTER_ID_LCDControl = 0x00000018,
		REGISTER_ID_LCDIMSC = 0x0000001c,
		REGISTER_ID_LCDRIS = 0x00000020,
		REGISTER_ID_LCDMIS = 0x00000024,
		REGISTER_ID_LCDICR = 0x00000028,
		REGISTER_ID_LCDUPCURR = 0x0000002c,
		REGISTER_ID_LCDLPCURR = 0x00000030,
		REGISTER_ID_LCDPalette = 0x00000001,
		REGISTER_ID_LCDPalette_0 = 0x00000001,
		REGISTER_ID_LCDPalette_1 = 0x00000002,
		REGISTER_ID_LCDPalette_2 = 0x00000003,
		REGISTER_ID_LCDPalette_3 = 0x00000005,
		REGISTER_ID_LCDPalette_4 = 0x00000006,
		REGISTER_ID_LCDPalette_5 = 0x00000007,
		REGISTER_ID_LCDPalette_6 = 0x00000009,
		REGISTER_ID_LCDPalette_7 = 0x0000000a,
		REGISTER_ID_LCDPalette_8 = 0x0000000b,
		REGISTER_ID_LCDPalette_9 = 0x0000000d,
		REGISTER_ID_LCDPalette_10 = 0x0000000e,
		REGISTER_ID_LCDPalette_11 = 0x0000000f,
		REGISTER_ID_LCDPalette_12 = 0x00000011,
		REGISTER_ID_LCDPalette_13 = 0x00000012,
		REGISTER_ID_LCDPalette_14 = 0x00000013,
		REGISTER_ID_LCDPalette_15 = 0x00000015,
		REGISTER_ID_LCDPalette_16 = 0x00000016,
		REGISTER_ID_LCDPalette_17 = 0x00000017,
		REGISTER_ID_LCDPalette_18 = 0x00000019,
		REGISTER_ID_LCDPalette_19 = 0x0000001a,
		REGISTER_ID_LCDPalette_20 = 0x0000001b,
		REGISTER_ID_LCDPalette_21 = 0x0000001d,
		REGISTER_ID_LCDPalette_22 = 0x0000001e,
		REGISTER_ID_LCDPalette_23 = 0x0000001f,
		REGISTER_ID_LCDPalette_24 = 0x00000021,
		REGISTER_ID_LCDPalette_25 = 0x00000022,
		REGISTER_ID_LCDPalette_26 = 0x00000023,
		REGISTER_ID_LCDPalette_27 = 0x00000025,
		REGISTER_ID_LCDPalette_28 = 0x00000026,
		REGISTER_ID_LCDPalette_29 = 0x00000027,
		REGISTER_ID_LCDPalette_30 = 0x00000029,
		REGISTER_ID_LCDPalette_31 = 0x0000002a,
		REGISTER_ID_LCDPalette_32 = 0x0000002b,
		REGISTER_ID_LCDPalette_33 = 0x0000002d,
		REGISTER_ID_LCDPalette_34 = 0x0000002e,
		REGISTER_ID_LCDPalette_35 = 0x0000002f,
		REGISTER_ID_LCDPalette_36 = 0x00000031,
		REGISTER_ID_LCDPalette_37 = 0x00000032,
		REGISTER_ID_LCDPalette_38 = 0x00000033,
		REGISTER_ID_LCDPalette_39 = 0x00000034,
		REGISTER_ID_LCDPalette_40 = 0x00000035,
		REGISTER_ID_LCDPalette_41 = 0x00000036,
		REGISTER_ID_LCDPalette_42 = 0x00000037,
		REGISTER_ID_LCDPalette_43 = 0x00000038,
		REGISTER_ID_LCDPalette_44 = 0x00000039,
		REGISTER_ID_LCDPalette_45 = 0x0000003a,
		REGISTER_ID_LCDPalette_46 = 0x0000003b,
		REGISTER_ID_LCDPalette_47 = 0x0000003c,
		REGISTER_ID_LCDPalette_48 = 0x0000003d,
		REGISTER_ID_LCDPalette_49 = 0x0000003e,
		REGISTER_ID_LCDPalette_50 = 0x0000003f,
		REGISTER_ID_LCDPalette_51 = 0x00000040,
		REGISTER_ID_LCDPalette_52 = 0x00000041,
		REGISTER_ID_LCDPalette_53 = 0x00000042,
		REGISTER_ID_LCDPalette_54 = 0x00000043,
		REGISTER_ID_LCDPalette_55 = 0x00000044,
		REGISTER_ID_LCDPalette_56 = 0x00000045,
		REGISTER_ID_LCDPalette_57 = 0x00000046,
		REGISTER_ID_LCDPalette_58 = 0x00000047,
		REGISTER_ID_LCDPalette_59 = 0x00000048,
		REGISTER_ID_LCDPalette_60 = 0x00000049,
		REGISTER_ID_LCDPalette_61 = 0x0000004a,
		REGISTER_ID_LCDPalette_62 = 0x0000004b,
		REGISTER_ID_LCDPalette_63 = 0x0000004c,
		REGISTER_ID_LCDPalette_64 = 0x0000004d,
		REGISTER_ID_LCDPalette_65 = 0x0000004e,
		REGISTER_ID_LCDPalette_66 = 0x0000004f,
		REGISTER_ID_LCDPalette_67 = 0x00000050,
		REGISTER_ID_LCDPalette_68 = 0x00000051,
		REGISTER_ID_LCDPalette_69 = 0x00000052,
		REGISTER_ID_LCDPalette_70 = 0x00000053,
		REGISTER_ID_LCDPalette_71 = 0x00000054,
		REGISTER_ID_LCDPalette_72 = 0x00000055,
		REGISTER_ID_LCDPalette_73 = 0x00000056,
		REGISTER_ID_LCDPalette_74 = 0x00000057,
		REGISTER_ID_LCDPalette_75 = 0x00000058,
		REGISTER_ID_LCDPalette_76 = 0x00000059,
		REGISTER_ID_LCDPalette_77 = 0x0000005a,
		REGISTER_ID_LCDPalette_78 = 0x0000005b,
		REGISTER_ID_LCDPalette_79 = 0x0000005c,
		REGISTER_ID_LCDPalette_80 = 0x0000005d,
		REGISTER_ID_LCDPalette_81 = 0x0000005e,
		REGISTER_ID_LCDPalette_82 = 0x0000005f,
		REGISTER_ID_LCDPalette_83 = 0x00000060,
		REGISTER_ID_LCDPalette_84 = 0x00000061,
		REGISTER_ID_LCDPalette_85 = 0x00000062,
		REGISTER_ID_LCDPalette_86 = 0x00000063,
		REGISTER_ID_LCDPalette_87 = 0x00000064,
		REGISTER_ID_LCDPalette_88 = 0x00000065,
		REGISTER_ID_LCDPalette_89 = 0x00000066,
		REGISTER_ID_LCDPalette_90 = 0x00000067,
		REGISTER_ID_LCDPalette_91 = 0x00000068,
		REGISTER_ID_LCDPalette_92 = 0x00000069,
		REGISTER_ID_LCDPalette_93 = 0x0000006a,
		REGISTER_ID_LCDPalette_94 = 0x0000006b,
		REGISTER_ID_LCDPalette_95 = 0x0000006c,
		REGISTER_ID_LCDPalette_96 = 0x0000006d,
		REGISTER_ID_LCDPalette_97 = 0x0000006e,
		REGISTER_ID_LCDPalette_98 = 0x0000006f,
		REGISTER_ID_LCDPalette_99 = 0x00000070,
		REGISTER_ID_LCDPalette_100 = 0x00000071,
		REGISTER_ID_LCDPalette_101 = 0x00000072,
		REGISTER_ID_LCDPalette_102 = 0x00000073,
		REGISTER_ID_LCDPalette_103 = 0x00000074,
		REGISTER_ID_LCDPalette_104 = 0x00000075,
		REGISTER_ID_LCDPalette_105 = 0x00000076,
		REGISTER_ID_LCDPalette_106 = 0x00000077,
		REGISTER_ID_LCDPalette_107 = 0x00000078,
		REGISTER_ID_LCDPalette_108 = 0x00000079,
		REGISTER_ID_LCDPalette_109 = 0x0000007a,
		REGISTER_ID_LCDPalette_110 = 0x0000007b,
		REGISTER_ID_LCDPalette_111 = 0x0000007c,
		REGISTER_ID_LCDPalette_112 = 0x0000007d,
		REGISTER_ID_LCDPalette_113 = 0x0000007e,
		REGISTER_ID_LCDPalette_114 = 0x0000007f,
		REGISTER_ID_LCDPalette_115 = 0x00000080,
		REGISTER_ID_LCDPalette_116 = 0x00000081,
		REGISTER_ID_LCDPalette_117 = 0x00000082,
		REGISTER_ID_LCDPalette_118 = 0x00000083,
		REGISTER_ID_LCDPalette_119 = 0x00000084,
		REGISTER_ID_LCDPalette_120 = 0x00000085,
		REGISTER_ID_LCDPalette_121 = 0x00000086,
		REGISTER_ID_LCDPalette_122 = 0x00000087,
		REGISTER_ID_LCDPalette_123 = 0x00000088,
		REGISTER_ID_LCDPalette_124 = 0x00000089,
		REGISTER_ID_LCDPalette_125 = 0x0000008a,
		REGISTER_ID_LCDPalette_126 = 0x0000008b,
		REGISTER_ID_LCDPalette_127 = 0x0000008c,
		REGISTER_ID_CursorImage = 0x0000008d,
		REGISTER_ID_CursorImage_0 = 0x0000008d,
		REGISTER_ID_CursorImage_1 = 0x0000008e,
		REGISTER_ID_CursorImage_2 = 0x0000008f,
		REGISTER_ID_CursorImage_3 = 0x00000090,
		REGISTER_ID_CursorImage_4 = 0x00000091,
		REGISTER_ID_CursorImage_5 = 0x00000092,
		REGISTER_ID_CursorImage_6 = 0x00000093,
		REGISTER_ID_CursorImage_7 = 0x00000094,
		REGISTER_ID_CursorImage_8 = 0x00000095,
		REGISTER_ID_CursorImage_9 = 0x00000096,
		REGISTER_ID_CursorImage_10 = 0x00000097,
		REGISTER_ID_CursorImage_11 = 0x00000098,
		REGISTER_ID_CursorImage_12 = 0x00000099,
		REGISTER_ID_CursorImage_13 = 0x0000009a,
		REGISTER_ID_CursorImage_14 = 0x0000009b,
		REGISTER_ID_CursorImage_15 = 0x0000009c,
		REGISTER_ID_CursorImage_16 = 0x0000009d,
		REGISTER_ID_CursorImage_17 = 0x0000009e,
		REGISTER_ID_CursorImage_18 = 0x0000009f,
		REGISTER_ID_CursorImage_19 = 0x000000a0,
		REGISTER_ID_CursorImage_20 = 0x000000a1,
		REGISTER_ID_CursorImage_21 = 0x000000a2,
		REGISTER_ID_CursorImage_22 = 0x000000a3,
		REGISTER_ID_CursorImage_23 = 0x000000a4,
		REGISTER_ID_CursorImage_24 = 0x000000a5,
		REGISTER_ID_CursorImage_25 = 0x000000a6,
		REGISTER_ID_CursorImage_26 = 0x000000a7,
		REGISTER_ID_CursorImage_27 = 0x000000a8,
		REGISTER_ID_CursorImage_28 = 0x000000a9,
		REGISTER_ID_CursorImage_29 = 0x000000aa,
		REGISTER_ID_CursorImage_30 = 0x000000ab,
		REGISTER_ID_CursorImage_31 = 0x000000ac,
		REGISTER_ID_CursorImage_32 = 0x000000ad,
		REGISTER_ID_CursorImage_33 = 0x000000ae,
		REGISTER_ID_CursorImage_34 = 0x000000af,
		REGISTER_ID_CursorImage_35 = 0x000000b0,
		REGISTER_ID_CursorImage_36 = 0x000000b1,
		REGISTER_ID_CursorImage_37 = 0x000000b2,
		REGISTER_ID_CursorImage_38 = 0x000000b3,
		REGISTER_ID_CursorImage_39 = 0x000000b4,
		REGISTER_ID_CursorImage_40 = 0x000000b5,
		REGISTER_ID_CursorImage_41 = 0x000000b6,
		REGISTER_ID_CursorImage_42 = 0x000000b7,
		REGISTER_ID_CursorImage_43 = 0x000000b8,
		REGISTER_ID_CursorImage_44 = 0x000000b9,
		REGISTER_ID_CursorImage_45 = 0x000000ba,
		REGISTER_ID_CursorImage_46 = 0x000000bb,
		REGISTER_ID_CursorImage_47 = 0x000000bc,
		REGISTER_ID_CursorImage_48 = 0x000000bd,
		REGISTER_ID_CursorImage_49 = 0x000000be,
		REGISTER_ID_CursorImage_50 = 0x000000bf,
		REGISTER_ID_CursorImage_51 = 0x000000c0,
		REGISTER_ID_CursorImage_52 = 0x000000c1,
		REGISTER_ID_CursorImage_53 = 0x000000c2,
		REGISTER_ID_CursorImage_54 = 0x000000c3,
		REGISTER_ID_CursorImage_55 = 0x000000c4,
		REGISTER_ID_CursorImage_56 = 0x000000c5,
		REGISTER_ID_CursorImage_57 = 0x000000c6,
		REGISTER_ID_CursorImage_58 = 0x000000c7,
		REGISTER_ID_CursorImage_59 = 0x000000c8,
		REGISTER_ID_CursorImage_60 = 0x000000c9,
		REGISTER_ID_CursorImage_61 = 0x000000ca,
		REGISTER_ID_CursorImage_62 = 0x000000cb,
		REGISTER_ID_CursorImage_63 = 0x000000cc,
		REGISTER_ID_CursorImage_64 = 0x000000cd,
		REGISTER_ID_CursorImage_65 = 0x000000ce,
		REGISTER_ID_CursorImage_66 = 0x000000cf,
		REGISTER_ID_CursorImage_67 = 0x000000d0,
		REGISTER_ID_CursorImage_68 = 0x000000d1,
		REGISTER_ID_CursorImage_69 = 0x000000d2,
		REGISTER_ID_CursorImage_70 = 0x000000d3,
		REGISTER_ID_CursorImage_71 = 0x000000d4,
		REGISTER_ID_CursorImage_72 = 0x000000d5,
		REGISTER_ID_CursorImage_73 = 0x000000d6,
		REGISTER_ID_CursorImage_74 = 0x000000d7,
		REGISTER_ID_CursorImage_75 = 0x000000d8,
		REGISTER_ID_CursorImage_76 = 0x000000d9,
		REGISTER_ID_CursorImage_77 = 0x000000da,
		REGISTER_ID_CursorImage_78 = 0x000000db,
		REGISTER_ID_CursorImage_79 = 0x000000dc,
		REGISTER_ID_CursorImage_80 = 0x000000dd,
		REGISTER_ID_CursorImage_81 = 0x000000de,
		REGISTER_ID_CursorImage_82 = 0x000000df,
		REGISTER_ID_CursorImage_83 = 0x000000e0,
		REGISTER_ID_CursorImage_84 = 0x000000e1,
		REGISTER_ID_CursorImage_85 = 0x000000e2,
		REGISTER_ID_CursorImage_86 = 0x000000e3,
		REGISTER_ID_CursorImage_87 = 0x000000e4,
		REGISTER_ID_CursorImage_88 = 0x000000e5,
		REGISTER_ID_CursorImage_89 = 0x000000e6,
		REGISTER_ID_CursorImage_90 = 0x000000e7,
		REGISTER_ID_CursorImage_91 = 0x000000e8,
		REGISTER_ID_CursorImage_92 = 0x000000e9,
		REGISTER_ID_CursorImage_93 = 0x000000ea,
		REGISTER_ID_CursorImage_94 = 0x000000eb,
		REGISTER_ID_CursorImage_95 = 0x000000ec,
		REGISTER_ID_CursorImage_96 = 0x000000ed,
		REGISTER_ID_CursorImage_97 = 0x000000ee,
		REGISTER_ID_CursorImage_98 = 0x000000ef,
		REGISTER_ID_CursorImage_99 = 0x000000f0,
		REGISTER_ID_CursorImage_100 = 0x000000f1,
		REGISTER_ID_CursorImage_101 = 0x000000f2,
		REGISTER_ID_CursorImage_102 = 0x000000f3,
		REGISTER_ID_CursorImage_103 = 0x000000f4,
		REGISTER_ID_CursorImage_104 = 0x000000f5,
		REGISTER_ID_CursorImage_105 = 0x000000f6,
		REGISTER_ID_CursorImage_106 = 0x000000f7,
		REGISTER_ID_CursorImage_107 = 0x000000f8,
		REGISTER_ID_CursorImage_108 = 0x000000f9,
		REGISTER_ID_CursorImage_109 = 0x000000fa,
		REGISTER_ID_CursorImage_110 = 0x000000fb,
		REGISTER_ID_CursorImage_111 = 0x000000fc,
		REGISTER_ID_CursorImage_112 = 0x000000fd,
		REGISTER_ID_CursorImage_113 = 0x000000fe,
		REGISTER_ID_CursorImage_114 = 0x000000ff,
		REGISTER_ID_CursorImage_115 = 0x00000100,
		REGISTER_ID_CursorImage_116 = 0x00000101,
		REGISTER_ID_CursorImage_117 = 0x00000102,
		REGISTER_ID_CursorImage_118 = 0x00000103,
		REGISTER_ID_CursorImage_119 = 0x00000104,
		REGISTER_ID_CursorImage_120 = 0x00000105,
		REGISTER_ID_CursorImage_121 = 0x00000106,
		REGISTER_ID_CursorImage_122 = 0x00000107,
		REGISTER_ID_CursorImage_123 = 0x00000108,
		REGISTER_ID_CursorImage_124 = 0x00000109,
		REGISTER_ID_CursorImage_125 = 0x0000010a,
		REGISTER_ID_CursorImage_126 = 0x0000010b,
		REGISTER_ID_CursorImage_127 = 0x0000010c,
		REGISTER_ID_CursorImage_128 = 0x0000010d,
		REGISTER_ID_CursorImage_129 = 0x0000010e,
		REGISTER_ID_CursorImage_130 = 0x0000010f,
		REGISTER_ID_CursorImage_131 = 0x00000110,
		REGISTER_ID_CursorImage_132 = 0x00000111,
		REGISTER_ID_CursorImage_133 = 0x00000112,
		REGISTER_ID_CursorImage_134 = 0x00000113,
		REGISTER_ID_CursorImage_135 = 0x00000114,
		REGISTER_ID_CursorImage_136 = 0x00000115,
		REGISTER_ID_CursorImage_137 = 0x00000116,
		REGISTER_ID_CursorImage_138 = 0x00000117,
		REGISTER_ID_CursorImage_139 = 0x00000118,
		REGISTER_ID_CursorImage_140 = 0x00000119,
		REGISTER_ID_CursorImage_141 = 0x0000011a,
		REGISTER_ID_CursorImage_142 = 0x0000011b,
		REGISTER_ID_CursorImage_143 = 0x0000011c,
		REGISTER_ID_CursorImage_144 = 0x0000011d,
		REGISTER_ID_CursorImage_145 = 0x0000011e,
		REGISTER_ID_CursorImage_146 = 0x0000011f,
		REGISTER_ID_CursorImage_147 = 0x00000120,
		REGISTER_ID_CursorImage_148 = 0x00000121,
		REGISTER_ID_CursorImage_149 = 0x00000122,
		REGISTER_ID_CursorImage_150 = 0x00000123,
		REGISTER_ID_CursorImage_151 = 0x00000124,
		REGISTER_ID_CursorImage_152 = 0x00000125,
		REGISTER_ID_CursorImage_153 = 0x00000126,
		REGISTER_ID_CursorImage_154 = 0x00000127,
		REGISTER_ID_CursorImage_155 = 0x00000128,
		REGISTER_ID_CursorImage_156 = 0x00000129,
		REGISTER_ID_CursorImage_157 = 0x0000012a,
		REGISTER_ID_CursorImage_158 = 0x0000012b,
		REGISTER_ID_CursorImage_159 = 0x0000012c,
		REGISTER_ID_CursorImage_160 = 0x0000012d,
		REGISTER_ID_CursorImage_161 = 0x0000012e,
		REGISTER_ID_CursorImage_162 = 0x0000012f,
		REGISTER_ID_CursorImage_163 = 0x00000130,
		REGISTER_ID_CursorImage_164 = 0x00000131,
		REGISTER_ID_CursorImage_165 = 0x00000132,
		REGISTER_ID_CursorImage_166 = 0x00000133,
		REGISTER_ID_CursorImage_167 = 0x00000134,
		REGISTER_ID_CursorImage_168 = 0x00000135,
		REGISTER_ID_CursorImage_169 = 0x00000136,
		REGISTER_ID_CursorImage_170 = 0x00000137,
		REGISTER_ID_CursorImage_171 = 0x00000138,
		REGISTER_ID_CursorImage_172 = 0x00000139,
		REGISTER_ID_CursorImage_173 = 0x0000013a,
		REGISTER_ID_CursorImage_174 = 0x0000013b,
		REGISTER_ID_CursorImage_175 = 0x0000013c,
		REGISTER_ID_CursorImage_176 = 0x0000013d,
		REGISTER_ID_CursorImage_177 = 0x0000013e,
		REGISTER_ID_CursorImage_178 = 0x0000013f,
		REGISTER_ID_CursorImage_179 = 0x00000140,
		REGISTER_ID_CursorImage_180 = 0x00000141,
		REGISTER_ID_CursorImage_181 = 0x00000142,
		REGISTER_ID_CursorImage_182 = 0x00000143,
		REGISTER_ID_CursorImage_183 = 0x00000144,
		REGISTER_ID_CursorImage_184 = 0x00000145,
		REGISTER_ID_CursorImage_185 = 0x00000146,
		REGISTER_ID_CursorImage_186 = 0x00000147,
		REGISTER_ID_CursorImage_187 = 0x00000148,
		REGISTER_ID_CursorImage_188 = 0x00000149,
		REGISTER_ID_CursorImage_189 = 0x0000014a,
		REGISTER_ID_CursorImage_190 = 0x0000014b,
		REGISTER_ID_CursorImage_191 = 0x0000014c,
		REGISTER_ID_CursorImage_192 = 0x0000014d,
		REGISTER_ID_CursorImage_193 = 0x0000014e,
		REGISTER_ID_CursorImage_194 = 0x0000014f,
		REGISTER_ID_CursorImage_195 = 0x00000150,
		REGISTER_ID_CursorImage_196 = 0x00000151,
		REGISTER_ID_CursorImage_197 = 0x00000152,
		REGISTER_ID_CursorImage_198 = 0x00000153,
		REGISTER_ID_CursorImage_199 = 0x00000154,
		REGISTER_ID_CursorImage_200 = 0x00000155,
		REGISTER_ID_CursorImage_201 = 0x00000156,
		REGISTER_ID_CursorImage_202 = 0x00000157,
		REGISTER_ID_CursorImage_203 = 0x00000158,
		REGISTER_ID_CursorImage_204 = 0x00000159,
		REGISTER_ID_CursorImage_205 = 0x0000015a,
		REGISTER_ID_CursorImage_206 = 0x0000015b,
		REGISTER_ID_CursorImage_207 = 0x0000015c,
		REGISTER_ID_CursorImage_208 = 0x0000015d,
		REGISTER_ID_CursorImage_209 = 0x0000015e,
		REGISTER_ID_CursorImage_210 = 0x0000015f,
		REGISTER_ID_CursorImage_211 = 0x00000160,
		REGISTER_ID_CursorImage_212 = 0x00000161,
		REGISTER_ID_CursorImage_213 = 0x00000162,
		REGISTER_ID_CursorImage_214 = 0x00000163,
		REGISTER_ID_CursorImage_215 = 0x00000164,
		REGISTER_ID_CursorImage_216 = 0x00000165,
		REGISTER_ID_CursorImage_217 = 0x00000166,
		REGISTER_ID_CursorImage_218 = 0x00000167,
		REGISTER_ID_CursorImage_219 = 0x00000168,
		REGISTER_ID_CursorImage_220 = 0x00000169,
		REGISTER_ID_CursorImage_221 = 0x0000016a,
		REGISTER_ID_CursorImage_222 = 0x0000016b,
		REGISTER_ID_CursorImage_223 = 0x0000016c,
		REGISTER_ID_CursorImage_224 = 0x0000016d,
		REGISTER_ID_CursorImage_225 = 0x0000016e,
		REGISTER_ID_CursorImage_226 = 0x0000016f,
		REGISTER_ID_CursorImage_227 = 0x00000170,
		REGISTER_ID_CursorImage_228 = 0x00000171,
		REGISTER_ID_CursorImage_229 = 0x00000172,
		REGISTER_ID_CursorImage_230 = 0x00000173,
		REGISTER_ID_CursorImage_231 = 0x00000174,
		REGISTER_ID_CursorImage_232 = 0x00000175,
		REGISTER_ID_CursorImage_233 = 0x00000176,
		REGISTER_ID_CursorImage_234 = 0x00000177,
		REGISTER_ID_CursorImage_235 = 0x00000178,
		REGISTER_ID_CursorImage_236 = 0x00000179,
		REGISTER_ID_CursorImage_237 = 0x0000017a,
		REGISTER_ID_CursorImage_238 = 0x0000017b,
		REGISTER_ID_CursorImage_239 = 0x0000017c,
		REGISTER_ID_CursorImage_240 = 0x0000017d,
		REGISTER_ID_CursorImage_241 = 0x0000017e,
		REGISTER_ID_CursorImage_242 = 0x0000017f,
		REGISTER_ID_CursorImage_243 = 0x00000180,
		REGISTER_ID_CursorImage_244 = 0x00000181,
		REGISTER_ID_CursorImage_245 = 0x00000182,
		REGISTER_ID_CursorImage_246 = 0x00000183,
		REGISTER_ID_CursorImage_247 = 0x00000184,
		REGISTER_ID_CursorImage_248 = 0x00000185,
		REGISTER_ID_CursorImage_249 = 0x00000186,
		REGISTER_ID_CursorImage_250 = 0x00000187,
		REGISTER_ID_CursorImage_251 = 0x00000188,
		REGISTER_ID_CursorImage_252 = 0x00000189,
		REGISTER_ID_CursorImage_253 = 0x0000018a,
		REGISTER_ID_CursorImage_254 = 0x0000018b,
		REGISTER_ID_CursorImage_255 = 0x0000018c,
		REGISTER_ID_ClcdCrsrCtrl = 0x00000c00,
		REGISTER_ID_ClcdCrsrConfig = 0x00000c04,
		REGISTER_ID_ClcdCrsrPalette0 = 0x00000c08,
		REGISTER_ID_ClcdCrsrPalette1 = 0x00000c0c,
		REGISTER_ID_ClcdCrsrXY = 0x00000c10,
		REGISTER_ID_ClcdCrsrClip = 0x00000c14,
		REGISTER_ID_ClcdCrsrIMSC = 0x00000c20,
		REGISTER_ID_ClcdCrsrICR = 0x00000c24,
		REGISTER_ID_ClcdCrsrRIS = 0x00000c28,
		REGISTER_ID_ClcdCrsrMIS = 0x00000c2c,
		REGISTER_ID_CLCDPERIPHID0 = 0x00000fe0,
		REGISTER_ID_CLCDPERIPHID1 = 0x00000fe4,
		REGISTER_ID_CLCDPERIPHID2 = 0x00000fe8,
		REGISTER_ID_CLCDPERIPHID3 = 0x00000fec,
		REGISTER_ID_CLCDPCELLID0 = 0x00000ff0,
		REGISTER_ID_CLCDPCELLID1 = 0x00000ff4,
		REGISTER_ID_CLCDPCELLID2 = 0x00000ff8,
		REGISTER_ID_CLCDPCELLID3 = 0x00000ffc,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

