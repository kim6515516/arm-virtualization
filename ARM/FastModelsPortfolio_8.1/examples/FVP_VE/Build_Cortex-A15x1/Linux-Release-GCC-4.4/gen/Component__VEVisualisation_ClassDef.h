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
 * Class definition for Component VEVisualisation.
 */

#ifndef Component_Component__VEVisualisation_ClassDef_h_
#define Component_Component__VEVisualisation_ClassDef_h_

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

#line 17 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"

    
        #include <assert.h>

        #include "sg/SystemInclude.h"
        #include "sg/MSCFixes.h"
        #include "UIClass/UIClass.h"
        #include "UIClass/UIIcon.h"

        #define EBVIS_TRACE if (!0) ; else printf

        #ifdef WIN32
            #define pvis_sleep(x) Sleep(x)
        #else
            #include <sys/time.h>
            #define pvis_sleep(x) usleep((x)*1000)
        #endif

        #define  MAX_CLUSTERS           2
        #define  MAX_CORES_PER_CLUSTER  4


        enum CoreRunState
        {
            CORE_RUN_STATE_UNKNOWN     = 0x0,  // Run status currently unknown (i.e. simulation has not started)
            CORE_RUN_STATE_RUNNING     = 0x1,  // None of the below, core is not idle and is executing instructions
            CORE_RUN_STATE_HALTED      = 0x2,  // External halt signal asserted
            CORE_RUN_STATE_STANDBY_WFE = 0x3,  // Last instruction executed was WFE and standby mode has been entered
            CORE_RUN_STATE_STANDBY_WFI = 0x4,  // Last instruction executed was WFI and standby mode has been entered
            CORE_RUN_STATE_IN_RESET    = 0x5,  // External reset signal asserted
            CORE_RUN_STATE_DORMANT     = 0x6,  // Partial core power down 
            CORE_RUN_STATE_SHUTDOWN    = 0x7,  // Complete core power down
            CORE_RUN_STATE_LIMIT
        };

        class ClusterStateDisplay : public Cui
        {
        private:
            unsigned          num_cores;
            CoreRunState      core[MAX_CORES_PER_CLUSTER];
            UIIcon**          crs_icon;
            VisRenderRegion*  rr;

            void renderCore(unsigned x, unsigned y, CoreRunState state)
            {
                UIIcon* icon = crs_icon[state];

                if (icon)
                {
                    icon->render(rr, x, y);
                }
            }

        public:
            ClusterStateDisplay(VisRenderRegion* render_reg,
                                int x, int y,
                                unsigned num_cores_,
                                UIIcon** crs_icon_) :
                Cui(render_reg, x, y, num_cores * 8 + 1, 13), 
                num_cores(num_cores_),
                crs_icon(crs_icon_),
                rr(render_reg)
            {
                assert(num_cores <= MAX_CORES_PER_CLUSTER);

                for(unsigned idx = 0; idx < MAX_CORES_PER_CLUSTER; idx++)
                {
                    core[idx] = CORE_RUN_STATE_UNKNOWN;
                }
            }

            void setCoreState(unsigned idx, uint32_t state_)
            {
                CoreRunState state = CoreRunState(state_);
                
                assert(idx < num_cores);

                if (core[idx] != state)
                {
                    assert(state < CORE_RUN_STATE_LIMIT);

                    core[idx] = state;
                    redraw();
                }
            }

            void redraw()
            {
                for(unsigned idx = 0; idx < num_cores; idx++)
                {
                    renderCore(pos.x + idx * 8 + 2, pos.y + 4, core[idx]);
                }

                update();
            }
        };


        class ClusterState
        {
        private:
            unsigned     index;           // Cluster index
            const char*  name;
            unsigned     num_cores;

            Clabel*    label_id;          // Label text for cluster id
            Clabel*    label_instr_count; // Label text for instruction count
            Cicount*   value_instr_count; // Value text for instruction count
            UIPos      min, max;          // Graphical extent (pixels)

            uint64_t   total_inst;
            uint64_t   delta_ticks;
            uint64_t   inst_per_sec;
            bool       running;

            ClusterStateDisplay*  state_display;
            uint32_t              core_run_state[MAX_CORES_PER_CLUSTER];

        public:
            ClusterState() { init(0,0,0); }

            ~ClusterState()
            {
                delete  label_id;
                delete  label_instr_count;
                delete  value_instr_count;
                delete  state_display;
            }

            void init(unsigned index_, unsigned num_cores_, const char* name_)
            {
                index     = index_;
                name      = name_;
                num_cores = num_cores_;

                label_id          = 0;
                label_instr_count = 0;
                value_instr_count = 0;
                state_display     = 0;

                reset();
            }

            void reset()
            {
                total_inst   = 0;
                delta_ticks  = 0;
                inst_per_sec = 0;
                running      = false;

                for(unsigned i=0; i<MAX_CORES_PER_CLUSTER; i++)
                {
                    core_run_state[i] = 0;
                }
            }

            bool update(uint64_t inst_count, uint32_t elapsed_time_ms, bool multiple_clusters)
            {
                delta_ticks = inst_count - total_inst;
                total_inst  = inst_count;

                if (elapsed_time_ms)
                {
                    // calculate ips here to get a decent sample period
                    inst_per_sec = (((uint64_t)1000) * delta_ticks) / elapsed_time_ms;
                }

                bool new_running = (delta_ticks != 0);

                if (new_running != running)
                {
                    running = new_running;

                    if (multiple_clusters)
                    {
                        // Highlight running clusters
                        UIColour fg, bg;

                        // White and grey
                        fg = running ? UIColour(0xFF, 0xFF, 0xFF) : UIColour(0x90, 0x90, 0x90);
                        bg = UIColour(0x00, 0x00, 0x00);

                        if (label_id)
                           label_id->setColours(fg, bg);

                        if (label_instr_count)
                           label_instr_count->setColours(fg, bg);

                        if (value_instr_count)
                           value_instr_count->setColours(fg, bg);
                    }
                }

                return running;
            }

            unsigned getNumCores() const
            {
                return num_cores;
            }

            void setCoreRunState(int i, uint32_t state)
            {
                core_run_state[i] = state;
            }

            bool hit_gui(int x, int y) const
            {
                return (num_cores > 0) && (x >= min.x) && (x <= max.x) && (y >= min.y) && (y <= max.y);
            }

            int build_gui(VisRenderRegion *render_region, int col, int row, bool multiple_clusters,
                          UIIcon** crs_icon)
            {
                if (num_cores == 0)  return 0;

                min.x = col*VIS_FONT_WIDTH;
                min.y = row*VIS_FONT_HEIGHT + 1;

                if (multiple_clusters)
                {
                    delete label_id;

                    if (name)
                    {
                       label_id = new Clabel(render_region, name, col*VIS_FONT_WIDTH, min.y);
                    }
                    else
                    {
                       char  ident[9];
                       sprintf( ident, "Cluster%d", index);
                       label_id = new Clabel(render_region, ident, col*VIS_FONT_WIDTH, min.y);
                    }

                    label_id->setWidth((label_id->getLength() + 1)* VIS_FONT_WIDTH);

                    col += label_id->getLength()+1;
                }

                delete state_display;
                state_display = new ClusterStateDisplay(render_region, col*VIS_FONT_WIDTH, min.y-2, num_cores,
                                                        crs_icon);
                col += num_cores + 2;

                delete label_instr_count;
                label_instr_count = new Clabel(render_region, 12, col*VIS_FONT_WIDTH, min.y);
                label_instr_count->setWidth((12 + 1)*VIS_FONT_WIDTH);
                col += 12+1;

                delete value_instr_count;
                value_instr_count = new Cicount(render_region, col*VIS_FONT_WIDTH, min.y);
                value_instr_count->setLeftJustify();
                col += value_instr_count->getLength() + 2;

                int width = col*VIS_FONT_WIDTH;

                max.x = min.x + width;
                max.y = min.y + VIS_FONT_HEIGHT-1;

                return col;
            }

            void redraw_labels(bool disp_totals)
            {
                if (label_instr_count)
                    label_instr_count->setLabel(disp_totals ? "Total Instr:" : "Instr / sec:");
            }

            void redraw_values(bool disp_totals)
            {
                if (value_instr_count)
                    value_instr_count->setCount(disp_totals ? total_inst : inst_per_sec);

                if (state_display)
                {
                    for(unsigned i=0; i < num_cores; i++)
                    {
                        state_display->setCoreState(i, core_run_state[i]);
                    }
                }
            }
        };
    
#line 321 "./Linux-Release-GCC-4.4/gen/Component__VEVisualisation_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ClockSignal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__GUIPollCallback_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__InstructionCount_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__KeyboardStatus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__LCD_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__LCDLayoutInfo_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__MouseStatus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerCallback_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__TimerControl_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__ValueState_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__VisEventRecorderProtocol_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_idler_of_GUIPoll_to_VEVisualisation : public ParameterFilter
{
public:
	ParameterFilter_idler_of_GUIPoll_to_VEVisualisation()
	{
		ovrd_params["delay_ms"] = eslapi::CADIParameterInfo_t(0x1000003C | PARAMETERFILTER_FIXED, "delay_ms",eslapi::CADI_PARAM_INT, "GUI update period in ms",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x14), "20" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__VEVisualisation: public SystemGenComponent
{
public:
    // pointers to subcomponents
	sg::ComponentBase *idler;
	sg::ComponentBase *timer;
	Component__VisEventRecorder *recorder;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_idler__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_timer__;
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_recorder__;


    // abstract ports
	FVP_VE_Cortex_A15x1__TimerCallback timer_callback_handler;
	FVP_VE_Cortex_A15x1__ClockSignal clock_50Hz;
	FVP_VE_Cortex_A15x1__MouseStatus touch_screen;
	FVP_VE_Cortex_A15x1__LCDLayoutInfo lcd_layout;
	FVP_VE_Cortex_A15x1__GUIPollCallback gui_callback;
	FVP_VE_Cortex_A15x1__LCD lcd;
	FVP_VE_Cortex_A15x1__InstructionCount cluster0_ticks[4];
	FVP_VE_Cortex_A15x1__InstructionCount cluster1_ticks[4];
	FVP_VE_Cortex_A15x1__ValueState leds;
	FVP_VE_Cortex_A15x1__ValueState daughter_leds;
	FVP_VE_Cortex_A15x1__ValueState daughter_user_switches;
	FVP_VE_Cortex_A15x1__ValueState user_switches;
	FVP_VE_Cortex_A15x1__ValueState boot_switch;
	FVP_VE_Cortex_A15x1__KeyboardStatus keyboard;
	FVP_VE_Cortex_A15x1__MouseStatus mouse;
	FVP_VE_Cortex_A15x1__VisEventRecorderProtocol recorderControl;
	FVP_VE_Cortex_A15x1__TimerControl __VEVisualisation_internal_1;


    // resources
    std::string application_pathname;


#line 303 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/examples/FVP_VE/LISA/VEVisualisation.lisa"

        // An instance of the Visualisation library.
        Visualisation *vis;

        // LCD display region.
        VisRenderRegion *render_lcd;

        // One display region for status information.
        VisRenderRegion *render_status;

        // Core run state icons
        UIIcon* crs_icon[CORE_RUN_STATE_LIMIT];

        // Current configured size of the LCD.
        unsigned int lcd_width;
        unsigned int lcd_height;

        // Maps keycode to a button
        // unused - should be done in newer SDLVis
        // MxU32 key2button[KC_MAX+1];

        ClusterState  cluster_state[2];

        Clabel        *user_dips_label;      // User dipswitch label
        Cdipswitch    *user_dips;            // User dipswitch
        Clabel        *boot_dips_label;      // Boot dipswitch label
        Cdipswitch    *boot_dips;            // Boot dipswitch
        Clabel        *led_label;            // LEDs label
        Cled          *user_led;             // LEDs
        Clabel        *daughter_label;       // Daughterboard LEDs/dipswitch label
        Cdipswitch    *daughter_dips;        // Daughterboard dipswitch
        Cled          *daughter_led;         // Daughterboard LEDs
        Clabel        *rl_label;             // Rate Limit label
        Cbutton       *rl_button;            // Rate Limit button
        Clabel        *label_time_perf;      // Label text for total time or performance index
        Clabel        *value_time_perf;      // Value text for total time or performance index
        Clabel        *mouse_label;          // Grab/Release mouse text
        Cseparateline *white_line;           // White divider

        // Current configured height of the status area.
        int status_height;

        // Cursor position, for rendering parts of the status area.
        int sx, sy;

        // True if the window layout needs to be reconfigured on the
        // next screen redraw.
        bool relayout_needed;

        // status of the ctrl key
        bool ctrl_key;

        // toggle mouse
        bool toggle_mouse;

        // current absolute mouse position (to calc relative changes)
        int mouse_abs_x, mouse_abs_y;

        bool    disp_totals;
        bool    disp_delay;
        bool    stopped;

        unsigned num_clusters;

        // Used by the performance calculation routines
        // Outputs
        float    sim_pidx;

        // Intermediate values
        uint32_t start_time;          // Aggr. sim time calculated on the fly
        uint32_t last_time;
        uint32_t perf_index_real_time_ms;     // accumulated real time elapsed between calculateStats() (in ms)
        uint32_t perf_index_sim_time_ms;      // accumulated sim  time elapsed between calculateStats() (in ms)
        uint32_t throttle_last_real_time_ms;  // last absolte real time timer::timer_callback_handler.signal() was called (for throttling, in ms)
        // time in ms that simulator is ahead of real time (this is the budget we can sleep from)
        // (this does the whole averaging magic and compensation for sleep() inaccuracies)
        // (x<0 == sim time is x ms behind real time, x>0 sim time is x ms ahead of real time)
        int throttle_budget;
        int calculate_stats_phase;

        VisRasterLayout* fake_layout;  // fake area for pl11x when visualisation is disabled

        const uint32_t   trap_key     ; // 74 = KC_LALT = Left Alt (press Left Ctrl plus Left Alt to lock/unlock mouse)
        const bool  rate_limit_enable      ;
        const bool  disable_visualisation     ;
        const std::string  window_title     ;

        const std::string  cpu_name     ;
        const std::string  cluster0_name     ;
        const std::string  cluster1_name     ;

        const uint32_t  number_of_daughter_leds   
                        ;
        const uint32_t  number_of_daughter_user_switches   
                        ;

        uint32_t daughter_user_switches_value;
        uint32_t daughter_leds_value;

        bool     redraw_daughter_switches;

    
#line 506 "./Linux-Release-GCC-4.4/gen/Component__VEVisualisation_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__VEVisualisation(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__VEVisualisation();

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

	void calculateStats(bool force);
	void init();
	void init_gui();
	void init_icons();
	void init_status();
	void draw_buttons();
	void draw_leds();
	void draw_divider();
	void draw_labels();
	void draw_switches();
	void draw_status(uint32_t msTime);
	void reset(int level);
	void delete_gui_elements();
	void terminate();
	uint32_t get_msTime();
	void toggleMouse();
	void handleKeyDown(ATKeyCode key);
	void handleKeyUp(ATKeyCode key);
	void processMessages(bool playback);
	void emit_mouse_move(const VisEvent& event);
	void resize_lcd(unsigned int w, unsigned int h);
	void reconfigureWindow();
	char* ms2str(char* buf, uint32_t ms);
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	uint32_t abstract_port__timer_callback_handler__signal();
	void abstract_port__gui_callback__gui_callback();
	const VisRasterLayout* abstract_port__lcd__lock();
	void abstract_port__lcd__unlock();
	void abstract_port__lcd__update(int x, int y, unsigned int w, unsigned int h);
	void abstract_port__lcd__setPreferredLayout(unsigned int w, unsigned int h, unsigned int d);
	void abstract_port__daughter_leds__setValue(uint32_t value_);
	uint32_t abstract_port__daughter_leds__getValue();
	void abstract_port__daughter_user_switches__setValue(uint32_t value_);
	uint32_t abstract_port__daughter_user_switches__getValue();
	void abstract_port__recorderControl__processEvents();

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


	ParameterFilter_idler_of_GUIPoll_to_VEVisualisation parameterFilter_idler_of_GUIPoll_to_VEVisualisation__;


	CADIParameterProxy *cadiParameterProxy_idler_of_GUIPoll_to_VEVisualisation__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_trap_key = 0x10000035,
		PARAMETER_ID_rate_limit_enable = 0x10000036,
		PARAMETER_ID_disable_visualisation = 0x10000037,
		PARAMETER_ID_window_title = 0x10000038,
		PARAMETER_ID_cpu_name = 0x10000039,
		PARAMETER_ID_cluster0_name = 0x1000003A,
		PARAMETER_ID_cluster1_name = 0x1000003B,
		PARAMETER_ID_number_of_daughter_leds = 0x10000011,
		PARAMETER_ID_number_of_daughter_user_switches = 0x10000015,
	};




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

