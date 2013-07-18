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
 * Class definition for Component PL370_HDLCD.
 */

#ifndef Component_Component__PL370_HDLCD_ClassDef_h_
#define Component_Component__PL370_HDLCD_ClassDef_h_

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

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL370_HDLCD.lisa"

    
        #include "pv/PVBusMaster.h"

        // the major/minor revision and product ID values that are 
        // exposed in the VERSION register
        #define HDLCD_MAJOR 0x00
        #define HDLCD_MINOR 0x00
        #define HDLCD_PRODID 0x1cdc

        // create a mask of bits in a word
        #define hdlcd_mask(s, e) (0xffffffff>>(31-(s)) & (0xffffffff << (e)))
        #define hdlcd_bit(b) (1<<(b))

        #include <sstream>
        #include <iomanip>
    
#line 55 "./Linux64-Release-GCC-4.4/gen/Component__PL370_HDLCD_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__LCD_ClassDef.h"
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

class ParameterFilter_busslave_of_PVBusSlave_to_PL370_HDLCD : public ParameterFilter
{
public:
	ParameterFilter_busslave_of_PVBusSlave_to_PL370_HDLCD()
	{
		ovrd_params["size"] = eslapi::CADIParameterInfo_t(0x10000009 | PARAMETERFILTER_FIXED, "size",eslapi::CADI_PARAM_INT, "Addressable range of device (0 means 2^64)",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x0), "0" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__PL370_HDLCD: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *busslave;
	sg::ComponentBase *busmaster;
	sg::ComponentBase *timer;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busslave__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_busmaster__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVDevice device;
	FVP_VE_Cortex_A15x1__ClockSignal clk_in;
	FVP_VE_Cortex_A15x1__PVBus pvbus;
	FVP_VE_Cortex_A15x1__LCD display;
	FVP_VE_Cortex_A15x1__Signal intr;
	FVP_VE_Cortex_A15x1__PVBus pvbus_m;
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback_handler;
	FVP_VE_Cortex_A15x1__TimerControl __PL370_HDLCD_internal_1;


    // resources
    std::string application_pathname;


#line 37 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/PL370_HDLCD.lisa"

        const uint32_t  diagnostic       ;

        // I'm following CLCD reg name notation - which appends the RW/RO/WO attribute of a
        // register to the Long Name
        MxU32  HDLCD_VERSION                 ;

        MxU32  HDLCD_INT_RAWSTAT          ;
        MxU32  HDLCD_INT_CLEAR               ;
        MxU32  HDLCD_INT_MASK                ;
        MxU32  HDLCD_INT_STATUS              ;

        MxU32  HDLCD_FB_BASE           ;
        MxU32  HDLCD_FB_LINE_LENGTH            ;
        MxU32  HDLCD_FB_LINE_COUNT             ;
        MxU32  HDLCD_FB_LINE_PITCH             ;

        MxU32  HDLCD_BUS_OPTIONS         ;

        MxU32  HDLCD_V_SYNC            ;
        MxU32  HDLCD_V_BACK_PORCH             ;
        MxU32  HDLCD_V_DATA             ;
        MxU32  HDLCD_V_FRONT_PORCH            ;

        MxU32  HDLCD_H_SYNC          ;
        MxU32  HDLCD_H_BACK_PORCH           ;
        MxU32  HDLCD_H_DATA           ;
        MxU32  HDLCD_H_FRONT_PORCH          ;

        MxU32  HDLCD_POLARITIES              ;
        MxU32  HDLCD_COMMAND                 ;
        MxU32  HDLCD_PIXELFORMAT            ;
        MxU32  HDLCD_REDSELECT              ;
        MxU32  HDLCD_GREENSELECT            ;
        MxU32  HDLCD_BLUESELECT             ;

        // PrimeCell registers (HDLCD is a nominal PrimeCell of ID PL370)
        MxU8  HDLCDPERIPHID0           ;
        MxU8  HDLCDPERIPHID1          ;
        MxU8  HDLCDPERIPHID2         ;
        MxU8  HDLCDPERIPHID3         ;

        MxU8  HDLCDPCELLID0            ;
        MxU8  HDLCDPCELLID1           ;
        MxU8  HDLCDPCELLID2          ;
        MxU8  HDLCDPCELLID3          ;

        class HDLCD_Blit_Line {
        public:
            HDLCD_Blit_Line()
            {
            }

            uint32_t *pixels_per_line;
            bool bgr;           // swap b+r channels
            
            // passed in from LISA
            uint32_t *default_red;
            uint32_t *default_green;
            uint32_t *default_blue;
            uint32_t *offset_red;
            uint32_t *offset_green;
            uint32_t *offset_blue;
            uint32_t *size_red;
            uint32_t *size_green;
            uint32_t *size_blue;
            uint32_t *bytes_per_pixel;

            // templated fast version for known sizes

            template<class T> uint32_t* blit_line(uint32_t* dst, const T* src, uint32_t render_len)
            {
                T t_src = 0;

                uint32_t v_default_red = *default_red;
                uint32_t v_default_green = *default_green;
                uint32_t v_default_blue = *default_blue;
                uint32_t v_offset_red = *offset_red;
                uint32_t v_offset_green = *offset_green;
                uint32_t v_offset_blue = *offset_blue;
                uint32_t v_size_red = *size_red;
                uint32_t v_size_green = *size_green;
                uint32_t v_size_blue = *size_blue;

                uint32_t mask_red = ~(0xFFFFFFFF << (v_offset_red + v_size_red));
                uint32_t mask_green = ~(0xFFFFFFFF << (v_offset_green + v_size_green));
                uint32_t mask_blue = ~(0xFFFFFFFF << (v_offset_blue + v_size_blue));
                
                uint8_t channel_red = 0;
                uint8_t channel_green = 0;
                uint8_t channel_blue = 0;
                
                while((int32_t)render_len > 0)
                {
                    t_src = *src++;
                    // TODO - if it's big_endian, then switch the bytes

                    if(v_size_red == 0)
                    {
                        channel_red = (uint8_t) v_default_red;
                    }
                    else
                    {
                        channel_red = (t_src & mask_red) >> v_offset_red;
                        channel_red = channel_red << (8 - v_size_red);
                        channel_red |= (channel_red & (0xFF<<v_size_red)) >> v_size_red;
                    }

                    if(v_size_green == 0)
                    {
                        channel_green = (uint8_t) v_default_green;
                    }
                    else
                    {
                        channel_green = (t_src & mask_green) >> v_offset_green;
                        channel_green = channel_green << (8 - v_size_green);
                        channel_green |= (channel_green & (0xFF<<v_size_green)) >> v_size_green;
                    }

                    if(v_size_blue == 0)
                    {
                        channel_blue = (uint8_t) v_default_blue;
                    }
                    else
                    {
                        channel_blue = (t_src & mask_blue) >> v_offset_blue;
                        channel_blue = channel_blue << (8 - v_size_blue);
                        channel_blue |= (channel_blue & (0xFF<<v_size_blue)) >> v_size_blue;
                    }
                    
                    *dst++ = (uint32_t) (channel_red << 0) | (channel_green << 8) | (channel_blue << 16);

                    render_len -= 4;
                }

                return dst;
            }
        };

        // mask for int_raw and int_mask
        enum {
            INT_UNDERRUN = (1<<(3)),
            INT_VSYNC    = (1<<(2)),
            INT_BUS      = (1<<(1)),
            INT_DMA      = (1<<(0)),
            HDLCD_ALL_INT_MASK    = (INT_UNDERRUN|INT_VSYNC|INT_BUS|INT_DMA)
        };
        
        // byte aligned mask for fb_base, fb_line_len, fb_line_pitch
        enum {
            BYTE_ALIENGED_MASK  = (0xffffffff>>(31-(31)) & (0xffffffff << (3))),
            BYTE_ALIENGED_SHIFT = 3
        };

        // length mask for fb_line_count, v_sync, v_back_porch, v_data, v_front_porch, h_sync, 
        // h_back_porch, h_data, h_front_porch
        enum {
            LENGTH_MASK = (0xffffffff>>(31-(11)) & (0xffffffff << (0))),
            LENGTH_SHIFT = 0
        };
        
        enum {
            POLARITY_PXLCK      = (1<<(4)),
            POLARITY_DATA       = (1<<(3)),
            POLARITY_DATAEN     = (1<<(2)),
            POLARITY_HSYNC      = (1<<(1)),
            POLARITY_VSYNC      = (1<<(0)),
            HDLCD_POLARITY_MASK = (POLARITY_PXLCK|POLARITY_DATA|POLARITY_DATAEN|POLARITY_HSYNC|POLARITY_VSYNC)
        };

        // pixel format mask for PIXEL_FORMAT
        enum {
            BIG_ENDIAN_MASK         = (1<<(31)),
            BYTES_PER_PIXEL_MASK    = (0xffffffff>>(31-(4)) & (0xffffffff << (3))),
            BYTES_PER_PIXEL_SHIFT   = 3,
            HDLCD_PIXEL_FMT_MASK    = (BIG_ENDIAN_MASK|BYTES_PER_PIXEL_MASK)
        };
        
        // color select
        enum {
            COLOR_DEFAULT_MASK      = (0xffffffff>>(31-(23)) & (0xffffffff << (16))),
            COLOR_DEFAULT_SHIFT     = 16,
            COLOR_SIZE_MASK         = (0xffffffff>>(31-(11)) & (0xffffffff << (8))),
            COLOR_SIZE_SHIFT        = 8,
            COLOR_OFFSET_MASK       = (0xffffffff>>(31-(4)) & (0xffffffff << (0))),
            COLOR_OFFSET_SHIFT      = 0,
            HDLCD_COLOR_MASK        = (COLOR_OFFSET_MASK|COLOR_SIZE_MASK|COLOR_DEFAULT_MASK)
        };

        enum {
            HDLCD_ENABLE = (1<<(0))
        };

        pv::StreamingTransactionGenerator* dma;
        bool fbuffer_changed;   // true if any changes were detected in the fbuffer
        bool force_redraw;      // force redraw even if source data hasn't changed

        /* Registers variables */

        /* INT_RAWSTAT
         *   Unmasked status of the interrupt sources. Write 1 set the bit and 
         *   trigger an interrupt 
         * [3] UNDERRUN - No data was available to display while DATAEN was active
         * [2] VSYNC - Vertical sync is active
         * [1] BUS_ERROR - The DMA module received a bus error while reading data
         * [0] DMA_END - The DMA module has finished reading a frame
         */
        uint32_t int_raw;
        /* INT_MASK
         *   Hold the bit mask that enables an interrupt source if the 
         *   corresponding mask bit is set to 1.
         * [3] UNDERRUN
         * [2] VSYNC
         * [1] BUS_ERROR
         * [0] DMA_END
         */
        uint32_t int_mask;
        /* USER_OUT
         *   Allow the system integrator to control external modules from LCD controller 
         *   user interface. This register is system-dependant.
         * [31:0] USER_OUT
         */
        uint32_t user_out;
        /* FB_BASE
         *   Hold the address of the first pixel of the first line in the frame buffer
         * [31:3] FB_BASE_ADDR
         * [2:0] RESERVED
         */
        uint32_t fb_base;
        /* FB_LINE_LENGTH
         *   Hold the length of each frame buffer line in bytes
         * [31:3] FB_LINE_LENGTH 4294967288 bits/8 = 536870911 bytes
         * [2:0] RESERVED
         */
        uint32_t fb_line_len;
        /* FB_LINE_COUNT
         *   Hold the number of lines to read from the frame buffer
         * [31:12] RESERVED
         * [11:0] FB_LINE_COUNT 4095 + 1
         */
        uint32_t fb_line_count;
        /* FB_LINE_PITCH
         *   Hold the number of bytes between the start of one line in the frame buffer 
         *   and the start of the next line. This value is treated as a signed 2's 
         *   complement number, enabling negative pitch if required.
         * [31:3] FB_LINE_PITCH
         * [2:0] RESERVED
         */
        uint32_t fb_line_pitch;
        /* BUS_OPTIONS
         *   Control aspects of how the LCD controller accesses the bus.
         * [31:12] RESERVED
         * [11:8] MAX_OUTSTANDING - CAUTION: A value of zero disables all bus transfers
         * [7:5] RESERVED
         * [4] BURST_16
         * [3] BURST_8
         * [2] BURST_4
         * [1] BURST_2
         * [0] BURST_1
         *
         * Bus behaviors, won't implement
         */ 
        uint32_t bus_opts;
        /* V_SYNC
         *   Hold the width of the vertical sync signal, counted in number of horizontal scan lines
         * [31:12] RESERVED
         * [11:0] V_SYNC - Vertical sync width-1 (4096-1)
         */
        uint32_t v_sync;
        /* V_BACK_PORCH
         *   Hold the width of the interval between the vertical sync and the first visible line,
         *   counted in number of horizontal scan lines.
         * [31:12] RESERVED
         * [11:0] Vertical back porch width-1
         */
        uint32_t v_back_porch;
        /* V_DATA
         *   Hold the width of the vertical data area, that is, the number of visible lines,
         *   counted in the number of horizontal scan lines.
         * [31:12] RESERVED
         * [11:0] V_DATA - Vertical data width-1
         */
        uint32_t v_data;
        /* V_FRONT_PORCH
         *   Hold the width of the interval between the last visible line and the next vertical 
         *   synchronization, counted in number of horizontal scan lines
         * [31:12] RESERVED
         * [11:0] V_FRONT_PORCH - Vertical front porch width-1
         */
        uint32_t v_front_porch;
        /* H_SYNC
         *   Hold the width of the horizontal sync signal, counted in pixel clocks
         * [31:12] RESERVED
         * [11:0] H_SYNC - Horizontal sync width-1
         */
        uint32_t h_sync;
        /* H_BACK_PORCH
         *   Hold the width of the interval between the horizontal sync and the first visible 
         *   column, counted in pixel clocks.
         * [31:12] RESERVED
         * [11:0] H_BACK_PORCH - Horizontal back porch width-1
         */
        uint32_t h_back_porch;
        /* H_DATA
         *   Hold the width of the horizontal data area, that is, the number of visible columns 
         *   counted in pixel clocks.
         * [31:12] RESERVED
         * [11:0] H_DATA
         */
        uint32_t h_data;
        /* H_FRONT_PORCH
         *   Hold the width of the interval between the last visible column and the next
         *   horizontal synchronization, counted in pixel clocks.
         * [31:12] RESERVED
         * [11:0] H_FRONT_PORCH - Horizontal front porch width-1
         */
        uint32_t h_front_porch;
        /* POLARITIES
         *   Control the polarities of the synchronization signals and PXLCLK
         * [31:5] RESERVED
         * [4] PXLCLK_POLARITY
         * [3] DATA_POLARITY
         * [2] DATAEN_POLARITY
         * [1] HSYNC_POLARITY
         * [0] VSYNC_POLARITY
         *
         * Too low level, won't implement
         */
        uint32_t polarities;
        /* COMMAND
         *   Start and stop the LCD controller
         * [31:1] RESERVED
         * [0] ENABLE - Enable the LCD controller
         */
        uint32_t command;
        /* PIXEL_FORMAT
         *   BYTES_PER_PIXEL plus on bytes are extracted from the internal buffer.
         * [31] BIG_ENDIAN
         * [30:5] RESERVED
         * [4:3] BYTES_PER_PIXEL
         * [2:0] RESERVED
         */
        uint32_t pixel_fmt;
        /* RED/GREEN/BLUE_SELECT
         *   The bytes extracted from the internal buffer are presented as a 32-bit value.
         *   These registers select how many bits at which position are used to extract
         *   and use as the red, green, and blue color components. If no bits are extracted or
         *   no data is available, the default color is used.
         * [31:24] RESERVED
         * [23:16] DEFAULT
         * [15:12] RESERVED
         * [11:8] SIZE
         * [7:5] RESERVED
         * [4:0] OFFSET
         */
        uint32_t red_select;
        uint32_t green_select;
        uint32_t blue_select;

        uint32_t reg_changed;  // which of the above registers changed

        enum HDLCDRegisters
        {
            HDLCDIntRaw = 0,
            HDLCDIntMask,
            HDLCDUserOut,
            HDLCDFBBase,
            HDLCDFBLineLen,
            HDLCDFBLineCount,
            HDLCDFBLinePitch,
            HDLCDBusOpts,
            HDLCDVSync,
            HDLCDVBackPorch,
            HDLCDVData,
            HDLCDVFrontPorch,
            HDLCDHSync,
            HDLCDHBackPorch,
            HDLCDHData,
            HDLCDHFrontPorch,
            HDLCDPolarities,
            HDLCDCommand,
            HDLCDPixelFmt,
            HDLCDRedSelect,
            HDLCDGreenSelect,
            HDLCDBlueSelect
        };

        // derived flags/variables
        /* Is big endian? bit[31] in PIXEL_FORMAT */
        bool big_endian;
        /* Bytes per pixel, [4:3] in PIXEL_FORMAT */
        uint32_t bytes_per_pixel;
        uint32_t pixels_per_line;
        /* Is LCD enabled? bit[0] in COMMAND */
        bool enabled;
        /* [23:16] in red/green/blue_select */
        uint32_t default_red;
        uint32_t default_green;
        uint32_t default_blue;

        uint32_t size_red;
        uint32_t size_green;
        uint32_t size_blue;

        uint32_t offset_red;
        uint32_t offset_green;
        uint32_t offset_blue;
        
        // pixel colour layout
        bool be_pixel_order;                    // little/big endian pixel order
        bool be_byte_order;                     // little/big endian byte order (<16bpp only)
        uint32_t bits_per_pixel;                // Bits per pixel
        bool bgr;                               // swap b+r channels
        
        const VisRasterLayout * fdata;          // frame buffer data when locked
        
        bool palette_changed;                   // true if the palette changed
        bool colour_format_changed;             // true if any of the colour related registers changed
        HDLCD_Blit_Line blit;

        uint32_t palette[128]; // messy representation, decode when it changes
    
#line 547 "./Linux64-Release-GCC-4.4/gen/Component__PL370_HDLCD_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__PL370_HDLCD(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__PL370_HDLCD();

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

	uint32_t timer_callback();
	void init();
	void reset(int level);
	void terminate();
	void update_registers();
	void update_interrupts();
	void update_palette();
	uint8_t* blit_line(uint8_t* dst, const uint8_t* src, uint32_t len);
	void blit_frame();
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
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	pv::Tx_Result abstract_port__device__read(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__device__write(pv::WriteTransaction tx);
	pv::Tx_Result abstract_port__device__debugRead(pv::ReadTransaction tx);
	pv::Tx_Result abstract_port__device__debugWrite(pv::WriteTransaction tx);
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


	ParameterFilter_busslave_of_PVBusSlave_to_PL370_HDLCD parameterFilter_busslave_of_PVBusSlave_to_PL370_HDLCD__;


	CADIParameterProxy *cadiParameterProxy_busslave_of_PVBusSlave_to_PL370_HDLCD__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_diagnostic = 0x1000000D,
	};


	// definition of register IDs as constants for use in register access functions
	enum
	{
		REGISTER_ID_HDLCD_VERSION = 0x00000000,
		REGISTER_ID_HDLCD_INT_RAWSTAT = 0x00000010,
		REGISTER_ID_HDLCD_INT_CLEAR = 0x00000014,
		REGISTER_ID_HDLCD_INT_MASK = 0x00000018,
		REGISTER_ID_HDLCD_INT_STATUS = 0x0000001c,
		REGISTER_ID_HDLCD_FB_BASE = 0x00000100,
		REGISTER_ID_HDLCD_FB_LINE_LENGTH = 0x00000104,
		REGISTER_ID_HDLCD_FB_LINE_COUNT = 0x00000108,
		REGISTER_ID_HDLCD_FB_LINE_PITCH = 0x0000010c,
		REGISTER_ID_HDLCD_BUS_OPTIONS = 0x00000110,
		REGISTER_ID_HDLCD_V_SYNC = 0x00000200,
		REGISTER_ID_HDLCD_V_BACK_PORCH = 0x00000204,
		REGISTER_ID_HDLCD_V_DATA = 0x00000208,
		REGISTER_ID_HDLCD_V_FRONT_PORCH = 0x0000020c,
		REGISTER_ID_HDLCD_H_SYNC = 0x00000210,
		REGISTER_ID_HDLCD_H_BACK_PORCH = 0x00000214,
		REGISTER_ID_HDLCD_H_DATA = 0x00000218,
		REGISTER_ID_HDLCD_H_FRONT_PORCH = 0x0000021c,
		REGISTER_ID_HDLCD_POLARITIES = 0x00000220,
		REGISTER_ID_HDLCD_COMMAND = 0x00000230,
		REGISTER_ID_HDLCD_PIXELFORMAT = 0x00000240,
		REGISTER_ID_HDLCD_REDSELECT = 0x00000244,
		REGISTER_ID_HDLCD_GREENSELECT = 0x00000248,
		REGISTER_ID_HDLCD_BLUESELECT = 0x0000024c,
		REGISTER_ID_HDLCDPERIPHID0 = 0x00000fe0,
		REGISTER_ID_HDLCDPERIPHID1 = 0x00000fe4,
		REGISTER_ID_HDLCDPERIPHID2 = 0x00000fe8,
		REGISTER_ID_HDLCDPERIPHID3 = 0x00000fec,
		REGISTER_ID_HDLCDPCELLID0 = 0x00000ff0,
		REGISTER_ID_HDLCDPCELLID1 = 0x00000ff4,
		REGISTER_ID_HDLCDPCELLID2 = 0x00000ff8,
		REGISTER_ID_HDLCDPCELLID3 = 0x00000ffc,

	};


};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

