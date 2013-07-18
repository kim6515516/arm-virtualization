/*
 * 
 *
 * Copyright 2009 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */
/** \file
 * Constructors for CADI wrapper classes. Put in a separate compilation unit
 * so we can compile it without optimisation which is very slow with some
 * versions of some compilers.
 */



#include "GlobalDefs.h"
#include "Components.h"
// includes for components in this file
#include "Component__VEDaughterBoard_ClassDef.h"
#include "Component__VEMotherBoard_ClassDef.h"
#include "Component__FVP_VE_Cortex_A15x1_ClassDef.h"
#include "Component__FlashLoader_ClassDef.h"
#include "Component__IntelStrataFlashJ3_ClassDef.h"
#include "Component__PL370_HDLCD_ClassDef.h"
#include "Component__RAMDevice_ClassDef.h"
#include "Component__TZSwitch_ClassDef.h"
#include "Component__VEDCC_ClassDef.h"
#include "Component__VEInterruptMapper_ClassDef.h"
#include "Component__VEDaughterBoard_ClassDef.h"
#include "Component__RAMDevice_ClassDef.h"
#include "Component__TZSwitch_ClassDef.h"
#include "Component__PL370_HDLCD_ClassDef.h"
#include "Component__VEInterruptMapper_ClassDef.h"
#include "Component__IntelStrataFlashJ3_ClassDef.h"
#include "Component__FlashLoader_ClassDef.h"
#include "Component__VEDCC_ClassDef.h"
#include "Component__AudioOut_SDL_ClassDef.h"
#include "Component__FlashLoader_ClassDef.h"
#include "Component__HostBridge_ClassDef.h"
#include "Component__IntelStrataFlashJ3_ClassDef.h"
#include "Component__MMC_ClassDef.h"
#include "Component__PL011_Uart_ClassDef.h"
#include "Component__PL031_RTC_ClassDef.h"
#include "Component__PL041_AACI_ClassDef.h"
#include "Component__PL050_KMI_ClassDef.h"
#include "Component__PL111_CLCD_ClassDef.h"
#include "Component__PL180_MCI_ClassDef.h"
#include "Component__PS2Keyboard_ClassDef.h"
#include "Component__PS2Mouse_ClassDef.h"
#include "Component__RAMDevice_ClassDef.h"
#include "Component__SP804_Timer_ClassDef.h"
#include "Component__SP805_Watchdog_ClassDef.h"
#include "Component__SP810_SysCtrl_ClassDef.h"
#include "Component__VEVisualisation_ClassDef.h"
#include "Component__VE_CompactFlash_ClassDef.h"
#include "Component__VE_SysRegs_ClassDef.h"
#include "Component__VFS2_ClassDef.h"
#include "Component__VirtualEthernetCrossover_ClassDef.h"
#include "Component__VEMotherBoard_ClassDef.h"
#include "Component__CounterModule_ClassDef.h"
#include "Component__SP804_Timer_ClassDef.h"
#include "Component__CounterModule_ClassDef.h"
#include "Component__AudioOut_SDL_ClassDef.h"
#include "Component__VE_CompactFlash_ClassDef.h"
#include "Component__HostBridge_ClassDef.h"
#include "Component__MMC_ClassDef.h"
#include "Component__PL011_Uart_ClassDef.h"
#include "Component__PL031_RTC_ClassDef.h"
#include "Component__PL041_AACI_ClassDef.h"
#include "Component__PL050_KMI_ClassDef.h"
#include "Component__PL11x_CLCD_ClassDef.h"
#include "Component__PL111_CLCD_ClassDef.h"
#include "Component__PL11x_CLCD_ClassDef.h"
#include "Component__PL180_MCI_ClassDef.h"
#include "Component__PS2Keyboard_ClassDef.h"
#include "Component__PS2Mouse_ClassDef.h"
#include "Component__SP805_Watchdog_ClassDef.h"
#include "Component__SP810_SysCtrl_ClassDef.h"
#include "Component__VE_SysRegs_ClassDef.h"
#include "Component__MessageBox_ClassDef.h"
#include "Component__VFS2_ClassDef.h"
#include "Component__MessageBox_ClassDef.h"
#include "Component__VirtualEthernetCrossover_ClassDef.h"
#include "Component__VisEventRecorder_ClassDef.h"
#include "Component__VEVisualisation_ClassDef.h"
#include "Component__VisEventRecorder_ClassDef.h"


#include "sg/FastDelegate.h"

using namespace fastdelegate;
using namespace FVP_VE_Cortex_A15x1_NMS;

// ------------------------------------------------------------------------------
// CADI Interface for component Component__FVP_VE_Cortex_A15x1
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__FVP_VE_Cortex_A15x1_CADI : public sg::CADIBase
{
public:
        Component__FVP_VE_Cortex_A15x1_CADI(Component__FVP_VE_Cortex_A15x1* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__FVP_VE_Cortex_A15x1 *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEDaughterBoard
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VEDaughterBoard_CADI : public sg::CADIBase
{
public:
        Component__VEDaughterBoard_CADI(Component__VEDaughterBoard* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VEDaughterBoard *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__RAMDevice
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__RAMDevice_CADI : public sg::CADIBase
{
public:
        Component__RAMDevice_CADI(Component__RAMDevice* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__RAMDevice *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__TZSwitch
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__TZSwitch_CADI : public sg::CADIBase
{
public:
        Component__TZSwitch_CADI(Component__TZSwitch* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__TZSwitch *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL370_HDLCD
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PL370_HDLCD_CADI : public sg::CADIBase
{
public:
        Component__PL370_HDLCD_CADI(Component__PL370_HDLCD* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PL370_HDLCD *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEInterruptMapper
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VEInterruptMapper_CADI : public sg::CADIBase
{
public:
        Component__VEInterruptMapper_CADI(Component__VEInterruptMapper* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VEInterruptMapper *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__IntelStrataFlashJ3
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__IntelStrataFlashJ3_CADI : public sg::CADIBase
{
public:
        Component__IntelStrataFlashJ3_CADI(Component__IntelStrataFlashJ3* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__IntelStrataFlashJ3 *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__FlashLoader
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__FlashLoader_CADI : public sg::CADIBase
{
public:
        Component__FlashLoader_CADI(Component__FlashLoader* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__FlashLoader *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEDCC
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VEDCC_CADI : public sg::CADIBase
{
public:
        Component__VEDCC_CADI(Component__VEDCC* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VEDCC *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEMotherBoard
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VEMotherBoard_CADI : public sg::CADIBase
{
public:
        Component__VEMotherBoard_CADI(Component__VEMotherBoard* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VEMotherBoard *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__SP804_Timer
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__SP804_Timer_CADI : public sg::CADIBase
{
public:
        Component__SP804_Timer_CADI(Component__SP804_Timer* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__SP804_Timer *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__CounterModule
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__CounterModule_CADI : public sg::CADIBase
{
public:
        Component__CounterModule_CADI(Component__CounterModule* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__CounterModule *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__AudioOut_SDL
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__AudioOut_SDL_CADI : public sg::CADIBase
{
public:
        Component__AudioOut_SDL_CADI(Component__AudioOut_SDL* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__AudioOut_SDL *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VE_CompactFlash
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VE_CompactFlash_CADI : public sg::CADIBase
{
public:
        Component__VE_CompactFlash_CADI(Component__VE_CompactFlash* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VE_CompactFlash *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__HostBridge
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__HostBridge_CADI : public sg::CADIBase
{
public:
        Component__HostBridge_CADI(Component__HostBridge* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__HostBridge *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__MMC
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__MMC_CADI : public sg::CADIBase
{
public:
        Component__MMC_CADI(Component__MMC* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__MMC *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL011_Uart
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PL011_Uart_CADI : public sg::CADIBase
{
public:
        Component__PL011_Uart_CADI(Component__PL011_Uart* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PL011_Uart *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL031_RTC
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PL031_RTC_CADI : public sg::CADIBase
{
public:
        Component__PL031_RTC_CADI(Component__PL031_RTC* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PL031_RTC *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL041_AACI
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PL041_AACI_CADI : public sg::CADIBase
{
public:
        Component__PL041_AACI_CADI(Component__PL041_AACI* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PL041_AACI *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL050_KMI
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PL050_KMI_CADI : public sg::CADIBase
{
public:
        Component__PL050_KMI_CADI(Component__PL050_KMI* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PL050_KMI *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL111_CLCD
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PL111_CLCD_CADI : public sg::CADIBase
{
public:
        Component__PL111_CLCD_CADI(Component__PL111_CLCD* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PL111_CLCD *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL11x_CLCD
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PL11x_CLCD_CADI : public sg::CADIBase
{
public:
        Component__PL11x_CLCD_CADI(Component__PL11x_CLCD* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PL11x_CLCD *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL180_MCI
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PL180_MCI_CADI : public sg::CADIBase
{
public:
        Component__PL180_MCI_CADI(Component__PL180_MCI* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PL180_MCI *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PS2Keyboard
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PS2Keyboard_CADI : public sg::CADIBase
{
public:
        Component__PS2Keyboard_CADI(Component__PS2Keyboard* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PS2Keyboard *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PS2Mouse
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__PS2Mouse_CADI : public sg::CADIBase
{
public:
        Component__PS2Mouse_CADI(Component__PS2Mouse* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__PS2Mouse *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__SP805_Watchdog
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__SP805_Watchdog_CADI : public sg::CADIBase
{
public:
        Component__SP805_Watchdog_CADI(Component__SP805_Watchdog* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__SP805_Watchdog *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__SP810_SysCtrl
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__SP810_SysCtrl_CADI : public sg::CADIBase
{
public:
        Component__SP810_SysCtrl_CADI(Component__SP810_SysCtrl* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__SP810_SysCtrl *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VE_SysRegs
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VE_SysRegs_CADI : public sg::CADIBase
{
public:
        Component__VE_SysRegs_CADI(Component__VE_SysRegs* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VE_SysRegs *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VFS2
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VFS2_CADI : public sg::CADIBase
{
public:
        Component__VFS2_CADI(Component__VFS2* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VFS2 *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__MessageBox
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__MessageBox_CADI : public sg::CADIBase
{
public:
        Component__MessageBox_CADI(Component__MessageBox* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__MessageBox *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VirtualEthernetCrossover
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VirtualEthernetCrossover_CADI : public sg::CADIBase
{
public:
        Component__VirtualEthernetCrossover_CADI(Component__VirtualEthernetCrossover* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VirtualEthernetCrossover *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEVisualisation
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VEVisualisation_CADI : public sg::CADIBase
{
public:
        Component__VEVisualisation_CADI(Component__VEVisualisation* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VEVisualisation *component;
};

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VisEventRecorder
// ------------------------------------------------------------------------------

namespace FVP_VE_Cortex_A15x1_NMS {

class Component__VisEventRecorder_CADI : public sg::CADIBase
{
public:
        Component__VisEventRecorder_CADI(Component__VisEventRecorder* parentComponent, sg::ComponentBase* simulationEngine);

    eslapi::CADIReturn_t CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response);
    sg::accessfunc::AccessFuncResult GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/);

private:
    Component__VisEventRecorder *component;
};

} // FVP_VE_Cortex_A15x1_NMS


// ------------------------------------------------------------------------------
// CADI Interface for component Component__FVP_VE_Cortex_A15x1
// ------------------------------------------------------------------------------

#include "Component__FVP_VE_Cortex_A15x1_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__FVP_VE_Cortex_A15x1_CADI::Component__FVP_VE_Cortex_A15x1_CADI(Component__FVP_VE_Cortex_A15x1* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__FVP_VE_Cortex_A15x1_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "FVP_VE_Cortex_A15x1" );
    strcpy( features.targetVersion, "" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__FVP_VE_Cortex_A15x1_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__FVP_VE_Cortex_A15x1_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEDaughterBoard
// ------------------------------------------------------------------------------

#include "Component__VEDaughterBoard_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VEDaughterBoard_CADI::Component__VEDaughterBoard_CADI(Component__VEDaughterBoard* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VEDaughterBoard_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000006, MakeDelegate(parentComponent, &Component__VEDaughterBoard::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEDaughterBoard::parameter_write_func), 0 },
		{ 0x10000007, MakeDelegate(parentComponent, &Component__VEDaughterBoard::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEDaughterBoard::parameter_write_func), 0 },
		{ 0x10000008, MakeDelegate(parentComponent, &Component__VEDaughterBoard::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEDaughterBoard::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VEDaughterBoard" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VEDaughterBoard_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VEDaughterBoard_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__RAMDevice
// ------------------------------------------------------------------------------

#include "Component__RAMDevice_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__RAMDevice_CADI::Component__RAMDevice_CADI(Component__RAMDevice* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{

	AddMemorySpace("ram_contents", "ram_contents", 0, 8, UINT64_C(0xffffffffff), 0, 1, 0);
 

        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));

	CADIBase::MemoryBlock *mb;
	mb = AddMemoryBlock(0, "ram_contents", "ram_contents", uint16_t(eslapi::CADI_MEMBLOCK_ROOT), 0, UINT64_C(0x10000000000), 0, eslapi::CADI_MEM_ReadWrite, emptySupportedMultiplesOfMAU, 0, 0, 0);
	mb->access_write_func = MakeDelegate(parentComponent, &Component__RAMDevice::debug_write);
	mb->access_read_func = MakeDelegate(parentComponent, &Component__RAMDevice::debug_read);


        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__RAMDevice_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000009, MakeDelegate(parentComponent, &Component__RAMDevice::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__RAMDevice::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "RAMDevice" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__RAMDevice_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__RAMDevice_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__TZSwitch
// ------------------------------------------------------------------------------

#include "Component__TZSwitch_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__TZSwitch_CADI::Component__TZSwitch_CADI(Component__TZSwitch* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__TZSwitch_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000000B, MakeDelegate(parentComponent, &Component__TZSwitch::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__TZSwitch::parameter_write_func), 0 },
		{ 0x1000000C, MakeDelegate(parentComponent, &Component__TZSwitch::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__TZSwitch::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "TZSwitch" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__TZSwitch_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__TZSwitch_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL370_HDLCD
// ------------------------------------------------------------------------------

#include "Component__PL370_HDLCD_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PL370_HDLCD_CADI::Component__PL370_HDLCD_CADI(Component__PL370_HDLCD* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"HDLCD_VERSION","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "Version(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_INT_RAWSTAT","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "Int Raw Status(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_INT_CLEAR","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "Int Clear(WO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_INT_MASK","Default",24UL, 32, eslapi::CADI_REGTYPE_HEX, "Int Mask(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_INT_STATUS","Default",28UL, 32, eslapi::CADI_REGTYPE_HEX, "Int Status(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_FB_BASE","Default",256UL, 32, eslapi::CADI_REGTYPE_HEX, "Frame Buffer Base Address(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_FB_LINE_LENGTH","Default",260UL, 32, eslapi::CADI_REGTYPE_HEX, "Frame Buffer Line Length(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_FB_LINE_COUNT","Default",264UL, 32, eslapi::CADI_REGTYPE_HEX, "Frame Buffer Line Count(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_FB_LINE_PITCH","Default",268UL, 32, eslapi::CADI_REGTYPE_HEX, "Frame Buffer Line Pitch(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_BUS_OPTIONS","Default",272UL, 32, eslapi::CADI_REGTYPE_HEX, "Bus Options(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_V_SYNC","Default",512UL, 32, eslapi::CADI_REGTYPE_HEX, "Vertical Synch Width(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_V_BACK_PORCH","Default",516UL, 32, eslapi::CADI_REGTYPE_HEX, "Vertical Back Porch(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_V_DATA","Default",520UL, 32, eslapi::CADI_REGTYPE_HEX, "Vertical Data Width(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_V_FRONT_PORCH","Default",524UL, 32, eslapi::CADI_REGTYPE_HEX, "Vertical Front Porch(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_H_SYNC","Default",528UL, 32, eslapi::CADI_REGTYPE_HEX, "Horizontal Synch Width(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_H_BACK_PORCH","Default",532UL, 32, eslapi::CADI_REGTYPE_HEX, "Horizontal Back Porch(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_H_DATA","Default",536UL, 32, eslapi::CADI_REGTYPE_HEX, "Horizontal Data Width(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_H_FRONT_PORCH","Default",540UL, 32, eslapi::CADI_REGTYPE_HEX, "Horizontal Front Porch(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_POLARITIES","Default",544UL, 32, eslapi::CADI_REGTYPE_HEX, "Polarities(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_COMMAND","Default",560UL, 32, eslapi::CADI_REGTYPE_HEX, "Command(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_PIXELFORMAT","Default",576UL, 32, eslapi::CADI_REGTYPE_HEX, "Pixel Format(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_REDSELECT","Default",580UL, 32, eslapi::CADI_REGTYPE_HEX, "Red Select(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_GREENSELECT","Default",584UL, 32, eslapi::CADI_REGTYPE_HEX, "Green Select(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCD_BLUESELECT","Default",588UL, 32, eslapi::CADI_REGTYPE_HEX, "Blue Select(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCDPERIPHID0","Default",4064UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral identification register bits [7:0](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCDPERIPHID1","Default",4068UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral identification register bits [15:8](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCDPERIPHID2","Default",4072UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral identification register bits [23:16](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCDPERIPHID3","Default",4076UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral identification register bits [31:23](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCDPCELLID0","Default",4080UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell identification register bits [7:0](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCDPCELLID1","Default",4084UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell identification register bits [15:8](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCDPCELLID2","Default",4088UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell identification register bits [23:16](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"HDLCDPCELLID3","Default",4092UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell identification register bits [31:23](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->HDLCD_VERSION, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_INT_RAWSTAT, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_INT_CLEAR, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_INT_MASK, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_INT_STATUS, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_FB_BASE, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_FB_LINE_LENGTH, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_FB_LINE_COUNT, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_FB_LINE_PITCH, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_BUS_OPTIONS, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_V_SYNC, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_V_BACK_PORCH, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_V_DATA, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_V_FRONT_PORCH, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_H_SYNC, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_H_BACK_PORCH, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_H_DATA, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_H_FRONT_PORCH, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_POLARITIES, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_COMMAND, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_PIXELFORMAT, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_REDSELECT, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_GREENSELECT, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCD_BLUESELECT, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCDPERIPHID0, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCDPERIPHID1, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCDPERIPHID2, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCDPERIPHID3, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCDPCELLID0, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCDPCELLID1, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCDPCELLID2, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},
		{&parentComponent->HDLCDPCELLID3, 0, 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL370_HDLCD::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__PL370_HDLCD_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000000D, MakeDelegate(parentComponent, &Component__PL370_HDLCD::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL370_HDLCD::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PL370_HDLCD" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PL370_HDLCD_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PL370_HDLCD_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEInterruptMapper
// ------------------------------------------------------------------------------

#include "Component__VEInterruptMapper_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VEInterruptMapper_CADI::Component__VEInterruptMapper_CADI(Component__VEInterruptMapper* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VEInterruptMapper_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VEInterruptMapper" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VEInterruptMapper_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VEInterruptMapper_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__IntelStrataFlashJ3
// ------------------------------------------------------------------------------

#include "Component__IntelStrataFlashJ3_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__IntelStrataFlashJ3_CADI::Component__IntelStrataFlashJ3_CADI(Component__IntelStrataFlashJ3* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{

	AddMemorySpace("ram_contents", "ram_contents", 1, 8, UINT64_C(0xffffffff), 0, 1, 0);
 

        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));

	CADIBase::MemoryBlock *mb;
	mb = AddMemoryBlock(1, "ram_contents", "ram_contents", uint16_t(eslapi::CADI_MEMBLOCK_ROOT), 0, UINT64_C(0x100000000), 0, eslapi::CADI_MEM_ReadWrite, emptySupportedMultiplesOfMAU, 0, 0, 0);
	mb->access_write_func = MakeDelegate(parentComponent, &Component__IntelStrataFlashJ3::debug_write);
	mb->access_read_func = MakeDelegate(parentComponent, &Component__IntelStrataFlashJ3::debug_read);


        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__IntelStrataFlashJ3_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000009, MakeDelegate(parentComponent, &Component__IntelStrataFlashJ3::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__IntelStrataFlashJ3::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "IntelStrataFlashJ3" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__IntelStrataFlashJ3_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__IntelStrataFlashJ3_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__FlashLoader
// ------------------------------------------------------------------------------

#include "Component__FlashLoader_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__FlashLoader_CADI::Component__FlashLoader_CADI(Component__FlashLoader* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__FlashLoader_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000000E, 0, MakeDelegate(parentComponent, &Component__FlashLoader::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__FlashLoader::parameter_write_string_func) },
		{ 0x1000000F, 0, MakeDelegate(parentComponent, &Component__FlashLoader::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__FlashLoader::parameter_write_string_func) },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "FlashLoader" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__FlashLoader_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__FlashLoader_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEDCC
// ------------------------------------------------------------------------------

#include "Component__VEDCC_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VEDCC_CADI::Component__VEDCC_CADI(Component__VEDCC* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VEDCC_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VEDCC" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VEDCC_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VEDCC_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEMotherBoard
// ------------------------------------------------------------------------------

#include "Component__VEMotherBoard_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VEMotherBoard_CADI::Component__VEMotherBoard_CADI(Component__VEMotherBoard* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VEMotherBoard_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000005, MakeDelegate(parentComponent, &Component__VEMotherBoard::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEMotherBoard::parameter_write_func), 0 },
		{ 0x10000010, MakeDelegate(parentComponent, &Component__VEMotherBoard::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEMotherBoard::parameter_write_func), 0 },
		{ 0x10000011, MakeDelegate(parentComponent, &Component__VEMotherBoard::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEMotherBoard::parameter_write_func), 0 },
		{ 0x10000012, MakeDelegate(parentComponent, &Component__VEMotherBoard::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEMotherBoard::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VEMotherBoard" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VEMotherBoard_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VEMotherBoard_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__SP804_Timer
// ------------------------------------------------------------------------------

#include "Component__SP804_Timer_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__SP804_Timer_CADI::Component__SP804_Timer_CADI(Component__SP804_Timer* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"Timer1Load","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer1Value","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer1Control","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer1IntClr","Default",12UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer1RIS","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer1MIS","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer1BGLoad","Default",24UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer2Load","Default",32UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer2Value","Default",36UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer2Control","Default",40UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer2IntClr","Default",44UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer2RIS","Default",48UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer2MIS","Default",52UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"Timer2BGLoad","Default",56UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->Timer1Load, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer1Value, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer1Control, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer1IntClr, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer1RIS, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer1MIS, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer1BGLoad, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer2Load, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer2Value, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer2Control, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer2IntClr, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer2RIS, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer2MIS, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},
		{&parentComponent->Timer2BGLoad, 0, 0, MakeDelegate(parentComponent, &Component__SP804_Timer::debug_read),0,MakeDelegate(parentComponent, &Component__SP804_Timer::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__SP804_Timer_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "SP804_Timer" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__SP804_Timer_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__SP804_Timer_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__CounterModule
// ------------------------------------------------------------------------------

#include "Component__CounterModule_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__CounterModule_CADI::Component__CounterModule_CADI(Component__CounterModule* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__CounterModule_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "CounterModule" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__CounterModule_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__CounterModule_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__AudioOut_SDL
// ------------------------------------------------------------------------------

#include "Component__AudioOut_SDL_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__AudioOut_SDL_CADI::Component__AudioOut_SDL_CADI(Component__AudioOut_SDL* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__AudioOut_SDL_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "AudioOut_SDL" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__AudioOut_SDL_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__AudioOut_SDL_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VE_CompactFlash
// ------------------------------------------------------------------------------

#include "Component__VE_CompactFlash_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VE_CompactFlash_CADI::Component__VE_CompactFlash_CADI(Component__VE_CompactFlash* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VE_CompactFlash_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VE_CompactFlash" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VE_CompactFlash_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VE_CompactFlash_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__HostBridge
// ------------------------------------------------------------------------------

#include "Component__HostBridge_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__HostBridge_CADI::Component__HostBridge_CADI(Component__HostBridge* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__HostBridge_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000016, 0, MakeDelegate(parentComponent, &Component__HostBridge::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__HostBridge::parameter_write_string_func) },
		{ 0x10000017, MakeDelegate(parentComponent, &Component__HostBridge::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__HostBridge::parameter_write_func), 0 },
		{ 0x10000018, 0, MakeDelegate(parentComponent, &Component__HostBridge::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__HostBridge::parameter_write_string_func) },
		{ 0x10000019, 0, MakeDelegate(parentComponent, &Component__HostBridge::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__HostBridge::parameter_write_string_func) },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "HostBridge" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__HostBridge_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__HostBridge_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__MMC
// ------------------------------------------------------------------------------

#include "Component__MMC_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__MMC_CADI::Component__MMC_CADI(Component__MMC* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"OCR_REG","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "Operating Conditions Register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CID_REG0","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "Card ID bits 127:96", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CID_REG1","Default",5UL, 32, eslapi::CADI_REGTYPE_HEX, "Card ID bits 95:64", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CID_REG2","Default",6UL, 32, eslapi::CADI_REGTYPE_HEX, "Card ID bits 63:32", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CID_REG3","Default",7UL, 32, eslapi::CADI_REGTYPE_HEX, "Card ID bits 31:0", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CSD_REG0","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "Card Specific Data bits 127:96", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CSD_REG1","Default",9UL, 32, eslapi::CADI_REGTYPE_HEX, "Card Specific Data bits 95:64", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CSD_REG2","Default",10UL, 32, eslapi::CADI_REGTYPE_HEX, "Card Specific Data bits 63:32", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CSD_REG3","Default",11UL, 32, eslapi::CADI_REGTYPE_HEX, "Card Specific Data bits 31:0", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RCA_REG","Default",12UL, 16, eslapi::CADI_REGTYPE_HEX, "Relative Card Address Register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"DSR_REG","Default",13UL, 16, eslapi::CADI_REGTYPE_HEX, "Driver Stage Register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"BLOCKLEN_REG","Default",14UL, 32, eslapi::CADI_REGTYPE_HEX, "Block length", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"STATUS_REG","Default",15UL, 32, eslapi::CADI_REGTYPE_HEX, "Card Status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"BLOCK_COUNT_REG","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "Block Count", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->OCR_REG, 0, 0, 0,0,0,0},
		{&parentComponent->CID_REG0, 0, 0, 0,0,0,0},
		{&parentComponent->CID_REG1, 0, 0, 0,0,0,0},
		{&parentComponent->CID_REG2, 0, 0, 0,0,0,0},
		{&parentComponent->CID_REG3, 0, 0, 0,0,0,0},
		{&parentComponent->CSD_REG0, 0, 0, 0,0,0,0},
		{&parentComponent->CSD_REG1, 0, 0, 0,0,0,0},
		{&parentComponent->CSD_REG2, 0, 0, 0,0,0,0},
		{&parentComponent->CSD_REG3, 0, 0, 0,0,0,0},
		{&parentComponent->RCA_REG, 0, 0, 0,0,0,0},
		{&parentComponent->DSR_REG, 0, 0, 0,0,0,0},
		{&parentComponent->BLOCKLEN_REG, 0, 0, 0,0,0,0},
		{&parentComponent->STATUS_REG, 0, 0, 0,0,0,0},
		{&parentComponent->BLOCK_COUNT_REG, 0, 0, 0,0,0,0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__MMC_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000001A, 0, MakeDelegate(parentComponent, &Component__MMC::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__MMC::parameter_write_string_func) },
		{ 0x1000001B, 0, MakeDelegate(parentComponent, &Component__MMC::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__MMC::parameter_write_string_func) },
		{ 0x1000001C, MakeDelegate(parentComponent, &Component__MMC::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__MMC::parameter_write_func), 0 },
		{ 0x1000001D, MakeDelegate(parentComponent, &Component__MMC::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__MMC::parameter_write_func), 0 },
		{ 0x1000001E, MakeDelegate(parentComponent, &Component__MMC::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__MMC::parameter_write_func), 0 },
		{ 0x1000001F, MakeDelegate(parentComponent, &Component__MMC::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__MMC::parameter_write_func), 0 },
		{ 0x10000020, MakeDelegate(parentComponent, &Component__MMC::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__MMC::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "MMC" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__MMC_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__MMC_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL011_Uart
// ------------------------------------------------------------------------------

#include "Component__PL011_Uart_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PL011_Uart_CADI::Component__PL011_Uart_CADI(Component__PL011_Uart* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"UARTDR","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "Data read or written", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTRSR","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "Receive status(RO)/Error clear(WO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTFR","Default",24UL, 32, eslapi::CADI_REGTYPE_HEX, "Flag(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTIBRD","Default",36UL, 32, eslapi::CADI_REGTYPE_HEX, "Integer baud rate divisor", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTFBRD","Default",40UL, 32, eslapi::CADI_REGTYPE_HEX, "Fractional baud rate divisor", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTLCR_H","Default",44UL, 32, eslapi::CADI_REGTYPE_HEX, "Line control, high byte", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTCR","Default",48UL, 32, eslapi::CADI_REGTYPE_HEX, "Control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTIFLS","Default",52UL, 32, eslapi::CADI_REGTYPE_HEX, "Interrupt FIFO level select", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTIMSC","Default",56UL, 32, eslapi::CADI_REGTYPE_HEX, "Interrupt mask set/clear", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTRIS","Default",60UL, 32, eslapi::CADI_REGTYPE_HEX, "Raw interrupt status(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTMIS","Default",64UL, 32, eslapi::CADI_REGTYPE_HEX, "Masked interrupt status(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTICR","Default",68UL, 32, eslapi::CADI_REGTYPE_HEX, "Interrupt clear(WO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTPeriphID[0]","Default",1UL, 8, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTPeriphID[1]","Default",2UL, 8, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000000, 0, 0, false, false, false},
		{"UARTPeriphID[2]","Default",3UL, 8, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000001, 0, 0, false, false, false},
		{"UARTPeriphID[3]","Default",5UL, 8, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000002, 0, 0, false, false, false},
		{"UARTCellID[0]","Default",6UL, 8, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"UARTCellID[1]","Default",7UL, 8, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000000, 0, 0, false, false, false},
		{"UARTCellID[2]","Default",8UL, 8, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000001, 0, 0, false, false, false},
		{"UARTCellID[3]","Default",9UL, 8, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000002, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->UARTDR, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTRSR, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTFR, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTIBRD, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTFBRD, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTLCR_H, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTCR, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTIFLS, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTIMSC, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTRIS, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTMIS, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTICR, 0, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::debug_read),0,MakeDelegate(parentComponent, &Component__PL011_Uart::debug_write),0},
		{&parentComponent->UARTPeriphID[0], 0, 0, 0,0,0,0},
		{&parentComponent->UARTPeriphID[1], 0, 0, 0,0,0,0},
		{&parentComponent->UARTPeriphID[2], 0, 0, 0,0,0,0},
		{&parentComponent->UARTPeriphID[3], 0, 0, 0,0,0,0},
		{&parentComponent->UARTCellID[0], 0, 0, 0,0,0,0},
		{&parentComponent->UARTCellID[1], 0, 0, 0,0,0,0},
		{&parentComponent->UARTCellID[2], 0, 0, 0,0,0,0},
		{&parentComponent->UARTCellID[3], 0, 0, 0,0,0,0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__PL011_Uart_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000021, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_func), 0 },
		{ 0x10000022, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_func), 0 },
		{ 0x10000023, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_func), 0 },
		{ 0x10000024, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_func), 0 },
		{ 0x10000025, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_string_func) },
		{ 0x10000026, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_string_func) },
		{ 0x10000027, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_func), 0 },
		{ 0x10000028, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_string_func) },
		{ 0x10000029, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_func), 0 },
		{ 0x1000002A, 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__PL011_Uart::parameter_write_string_func) },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PL011_Uart" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PL011_Uart_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PL011_Uart_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL031_RTC
// ------------------------------------------------------------------------------

#include "Component__PL031_RTC_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PL031_RTC_CADI::Component__PL031_RTC_CADI(Component__PL031_RTC* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"RTCDR","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "Data Register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RTCMR","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "Match Register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RTCLR","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "Load Register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RTCCR","Default",12UL, 32, eslapi::CADI_REGTYPE_HEX, "Control Register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RTCIMSC","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "Interrupt Mask", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RTCRIS","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "Raw interrupt status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RTCMIS","Default",24UL, 32, eslapi::CADI_REGTYPE_HEX, "Masked interrupt status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->RTCDR, 0, 0, MakeDelegate(parentComponent, &Component__PL031_RTC::debug_read),0,MakeDelegate(parentComponent, &Component__PL031_RTC::debug_write),0},
		{&parentComponent->RTCMR, 0, 0, MakeDelegate(parentComponent, &Component__PL031_RTC::debug_read),0,MakeDelegate(parentComponent, &Component__PL031_RTC::debug_write),0},
		{&parentComponent->RTCLR, 0, 0, MakeDelegate(parentComponent, &Component__PL031_RTC::debug_read),0,MakeDelegate(parentComponent, &Component__PL031_RTC::debug_write),0},
		{&parentComponent->RTCCR, 0, 0, MakeDelegate(parentComponent, &Component__PL031_RTC::debug_read),0,MakeDelegate(parentComponent, &Component__PL031_RTC::debug_write),0},
		{&parentComponent->RTCIMSC, 0, 0, MakeDelegate(parentComponent, &Component__PL031_RTC::debug_read),0,MakeDelegate(parentComponent, &Component__PL031_RTC::debug_write),0},
		{&parentComponent->RTCRIS, 0, 0, MakeDelegate(parentComponent, &Component__PL031_RTC::debug_read),0,MakeDelegate(parentComponent, &Component__PL031_RTC::debug_write),0},
		{&parentComponent->RTCMIS, 0, 0, MakeDelegate(parentComponent, &Component__PL031_RTC::debug_read),0,MakeDelegate(parentComponent, &Component__PL031_RTC::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__PL031_RTC_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PL031_RTC" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PL031_RTC_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PL031_RTC_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL041_AACI
// ------------------------------------------------------------------------------

#include "Component__PL041_AACI_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PL041_AACI_CADI::Component__PL041_AACI_CADI(Component__PL041_AACI* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"RXCR1","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Receive control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"TXCR1","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Transmit control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SR1","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ISR1","Default",12UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Interrupt status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"IE1","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Interrupt enable", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RXCR2","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Receive control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"TXCR2","Default",24UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Transmit control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SR2","Default",28UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ISR2","Default",32UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Interrupt status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"IE2","Default",36UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Interrupt enable", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RXCR3","Default",40UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Receive control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"TXCR3","Default",44UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Transmit control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SR3","Default",48UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ISR3","Default",52UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Interrupt status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"IE3","Default",56UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Interrupt enable", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RXCR4","Default",60UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Receive control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"TXCR4","Default",64UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Transmit control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SR4","Default",68UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ISR4","Default",72UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Interrupt status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"IE4","Default",76UL, 32, eslapi::CADI_REGTYPE_HEX, "Channel Interrupt enable", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SL1RX","Default",80UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot1 receive data", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SL1TX","Default",84UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot1 transmit data", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SL2RX","Default",88UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot2 receive data", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SL2TX","Default",92UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot2 transmit data", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SL12RX","Default",96UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot12 receive data", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SL12TX","Default",100UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot12 transmit data", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LSFR","Default",104UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot flag register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SLISTAT","Default",108UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot interrupt status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SLIEN","Default",112UL, 32, eslapi::CADI_REGTYPE_HEX, "Slot interrupt enable", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ALLINTCLR","Default",116UL, 32, eslapi::CADI_REGTYPE_HEX, "All interrupts clear", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MAINCR","Default",120UL, 32, eslapi::CADI_REGTYPE_HEX, "Main control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"RESET","Default",124UL, 32, eslapi::CADI_REGTYPE_HEX, "Reset control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYNC","Default",128UL, 32, eslapi::CADI_REGTYPE_HEX, "Sync control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ALLINTS","Default",132UL, 32, eslapi::CADI_REGTYPE_HEX, "All interrupts status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MAINFR","Default",136UL, 32, eslapi::CADI_REGTYPE_HEX, "Main flags", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->RXCR1, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->TXCR1, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SR1, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->ISR1, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->IE1, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->RXCR2, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->TXCR2, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SR2, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->ISR2, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->IE2, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->RXCR3, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->TXCR3, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SR3, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->ISR3, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->IE3, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->RXCR4, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->TXCR4, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SR4, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->ISR4, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->IE4, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SL1RX, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SL1TX, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SL2RX, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SL2TX, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SL12RX, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SL12TX, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->LSFR, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SLISTAT, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SLIEN, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->ALLINTCLR, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->MAINCR, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->RESET, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->SYNC, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->ALLINTS, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},
		{&parentComponent->MAINFR, 0, 0, MakeDelegate(parentComponent, &Component__PL041_AACI::debug_read),0,MakeDelegate(parentComponent, &Component__PL041_AACI::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__PL041_AACI_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PL041_AACI" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PL041_AACI_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PL041_AACI_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL050_KMI
// ------------------------------------------------------------------------------

#include "Component__PL050_KMI_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PL050_KMI_CADI::Component__PL050_KMI_CADI(Component__PL050_KMI* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"KMICR","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "Control", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMISTAT","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "Status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIDATA","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "Data", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMICLKDIV","Default",12UL, 32, eslapi::CADI_REGTYPE_HEX, "Clock divisor", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIIR","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "Interrupt status", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIPeriphID0","Default",4064UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral id 0", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIPeriphID1","Default",4068UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral id 1", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIPeriphID2","Default",4072UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral id 2", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIPeriphID3","Default",4076UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral id 3", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIPCellID0","Default",4080UL, 32, eslapi::CADI_REGTYPE_HEX, "PrimeCell id 0", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIPCellID1","Default",4084UL, 32, eslapi::CADI_REGTYPE_HEX, "PrimeCell id 1", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIPCellID2","Default",4088UL, 32, eslapi::CADI_REGTYPE_HEX, "PrimeCell id 2", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"KMIPCellID3","Default",4092UL, 32, eslapi::CADI_REGTYPE_HEX, "PrimeCell id 3", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->KMICR, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMISTAT, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIDATA, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMICLKDIV, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIIR, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIPeriphID0, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIPeriphID1, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIPeriphID2, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIPeriphID3, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIPCellID0, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIPCellID1, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIPCellID2, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},
		{&parentComponent->KMIPCellID3, 0, 0, MakeDelegate(parentComponent, &Component__PL050_KMI::debug_read),0,MakeDelegate(parentComponent, &Component__PL050_KMI::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__PL050_KMI_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PL050_KMI" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PL050_KMI_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PL050_KMI_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL111_CLCD
// ------------------------------------------------------------------------------

#include "Component__PL111_CLCD_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PL111_CLCD_CADI::Component__PL111_CLCD_CADI(Component__PL111_CLCD* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"LCDTiming0","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "Horizontal control(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDTiming1","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "Vertical control(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDTiming2","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "Clock and polarity control(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDTiming3","Default",12UL, 32, eslapi::CADI_REGTYPE_HEX, "Line end control(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDUPBASE","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "Upper panel frame base address(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDLPBASE","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "Lower panel frame base address(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDControl","Default",24UL, 8, eslapi::CADI_REGTYPE_HEX, "Interrupt mask(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDIMSC","Default",28UL, 16, eslapi::CADI_REGTYPE_HEX, "Control(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDRIS","Default",32UL, 8, eslapi::CADI_REGTYPE_HEX, "Raw interrupt status(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDMIS","Default",36UL, 8, eslapi::CADI_REGTYPE_HEX, "Masked interrupt status(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDICR","Default",40UL, 8, eslapi::CADI_REGTYPE_HEX, "Interrupt clear(WO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDUPCURR","Default",44UL, 32, eslapi::CADI_REGTYPE_HEX, "Upper panel current address(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDLPCURR","Default",48UL, 32, eslapi::CADI_REGTYPE_HEX, "Lower panel current address(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDPalette[0]","Default",1UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"LCDPalette[1]","Default",2UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000000, 0, 0, false, false, false},
		{"LCDPalette[2]","Default",3UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000001, 0, 0, false, false, false},
		{"LCDPalette[3]","Default",5UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000002, 0, 0, false, false, false},
		{"LCDPalette[4]","Default",6UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000003, 0, 0, false, false, false},
		{"LCDPalette[5]","Default",7UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000004, 0, 0, false, false, false},
		{"LCDPalette[6]","Default",9UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000005, 0, 0, false, false, false},
		{"LCDPalette[7]","Default",10UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000006, 0, 0, false, false, false},
		{"LCDPalette[8]","Default",11UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000007, 0, 0, false, false, false},
		{"LCDPalette[9]","Default",13UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000008, 0, 0, false, false, false},
		{"LCDPalette[10]","Default",14UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000009, 0, 0, false, false, false},
		{"LCDPalette[11]","Default",15UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000a, 0, 0, false, false, false},
		{"LCDPalette[12]","Default",17UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000b, 0, 0, false, false, false},
		{"LCDPalette[13]","Default",18UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000c, 0, 0, false, false, false},
		{"LCDPalette[14]","Default",19UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000d, 0, 0, false, false, false},
		{"LCDPalette[15]","Default",21UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000e, 0, 0, false, false, false},
		{"LCDPalette[16]","Default",22UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000f, 0, 0, false, false, false},
		{"LCDPalette[17]","Default",23UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000010, 0, 0, false, false, false},
		{"LCDPalette[18]","Default",25UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000011, 0, 0, false, false, false},
		{"LCDPalette[19]","Default",26UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000012, 0, 0, false, false, false},
		{"LCDPalette[20]","Default",27UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000013, 0, 0, false, false, false},
		{"LCDPalette[21]","Default",29UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000014, 0, 0, false, false, false},
		{"LCDPalette[22]","Default",30UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000015, 0, 0, false, false, false},
		{"LCDPalette[23]","Default",31UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000016, 0, 0, false, false, false},
		{"LCDPalette[24]","Default",33UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000017, 0, 0, false, false, false},
		{"LCDPalette[25]","Default",34UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000018, 0, 0, false, false, false},
		{"LCDPalette[26]","Default",35UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000019, 0, 0, false, false, false},
		{"LCDPalette[27]","Default",37UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001a, 0, 0, false, false, false},
		{"LCDPalette[28]","Default",38UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001b, 0, 0, false, false, false},
		{"LCDPalette[29]","Default",39UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001c, 0, 0, false, false, false},
		{"LCDPalette[30]","Default",41UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001d, 0, 0, false, false, false},
		{"LCDPalette[31]","Default",42UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001e, 0, 0, false, false, false},
		{"LCDPalette[32]","Default",43UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001f, 0, 0, false, false, false},
		{"LCDPalette[33]","Default",45UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000020, 0, 0, false, false, false},
		{"LCDPalette[34]","Default",46UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000021, 0, 0, false, false, false},
		{"LCDPalette[35]","Default",47UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000022, 0, 0, false, false, false},
		{"LCDPalette[36]","Default",49UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000023, 0, 0, false, false, false},
		{"LCDPalette[37]","Default",50UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000024, 0, 0, false, false, false},
		{"LCDPalette[38]","Default",51UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000025, 0, 0, false, false, false},
		{"LCDPalette[39]","Default",52UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000026, 0, 0, false, false, false},
		{"LCDPalette[40]","Default",53UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000027, 0, 0, false, false, false},
		{"LCDPalette[41]","Default",54UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000028, 0, 0, false, false, false},
		{"LCDPalette[42]","Default",55UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000029, 0, 0, false, false, false},
		{"LCDPalette[43]","Default",56UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002a, 0, 0, false, false, false},
		{"LCDPalette[44]","Default",57UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002b, 0, 0, false, false, false},
		{"LCDPalette[45]","Default",58UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002c, 0, 0, false, false, false},
		{"LCDPalette[46]","Default",59UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002d, 0, 0, false, false, false},
		{"LCDPalette[47]","Default",60UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002e, 0, 0, false, false, false},
		{"LCDPalette[48]","Default",61UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002f, 0, 0, false, false, false},
		{"LCDPalette[49]","Default",62UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000030, 0, 0, false, false, false},
		{"LCDPalette[50]","Default",63UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000031, 0, 0, false, false, false},
		{"LCDPalette[51]","Default",64UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000032, 0, 0, false, false, false},
		{"LCDPalette[52]","Default",65UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000033, 0, 0, false, false, false},
		{"LCDPalette[53]","Default",66UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000034, 0, 0, false, false, false},
		{"LCDPalette[54]","Default",67UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000035, 0, 0, false, false, false},
		{"LCDPalette[55]","Default",68UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000036, 0, 0, false, false, false},
		{"LCDPalette[56]","Default",69UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000037, 0, 0, false, false, false},
		{"LCDPalette[57]","Default",70UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000038, 0, 0, false, false, false},
		{"LCDPalette[58]","Default",71UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000039, 0, 0, false, false, false},
		{"LCDPalette[59]","Default",72UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003a, 0, 0, false, false, false},
		{"LCDPalette[60]","Default",73UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003b, 0, 0, false, false, false},
		{"LCDPalette[61]","Default",74UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003c, 0, 0, false, false, false},
		{"LCDPalette[62]","Default",75UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003d, 0, 0, false, false, false},
		{"LCDPalette[63]","Default",76UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003e, 0, 0, false, false, false},
		{"LCDPalette[64]","Default",77UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003f, 0, 0, false, false, false},
		{"LCDPalette[65]","Default",78UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000040, 0, 0, false, false, false},
		{"LCDPalette[66]","Default",79UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000041, 0, 0, false, false, false},
		{"LCDPalette[67]","Default",80UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000042, 0, 0, false, false, false},
		{"LCDPalette[68]","Default",81UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000043, 0, 0, false, false, false},
		{"LCDPalette[69]","Default",82UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000044, 0, 0, false, false, false},
		{"LCDPalette[70]","Default",83UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000045, 0, 0, false, false, false},
		{"LCDPalette[71]","Default",84UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000046, 0, 0, false, false, false},
		{"LCDPalette[72]","Default",85UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000047, 0, 0, false, false, false},
		{"LCDPalette[73]","Default",86UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000048, 0, 0, false, false, false},
		{"LCDPalette[74]","Default",87UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000049, 0, 0, false, false, false},
		{"LCDPalette[75]","Default",88UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004a, 0, 0, false, false, false},
		{"LCDPalette[76]","Default",89UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004b, 0, 0, false, false, false},
		{"LCDPalette[77]","Default",90UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004c, 0, 0, false, false, false},
		{"LCDPalette[78]","Default",91UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004d, 0, 0, false, false, false},
		{"LCDPalette[79]","Default",92UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004e, 0, 0, false, false, false},
		{"LCDPalette[80]","Default",93UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004f, 0, 0, false, false, false},
		{"LCDPalette[81]","Default",94UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000050, 0, 0, false, false, false},
		{"LCDPalette[82]","Default",95UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000051, 0, 0, false, false, false},
		{"LCDPalette[83]","Default",96UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000052, 0, 0, false, false, false},
		{"LCDPalette[84]","Default",97UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000053, 0, 0, false, false, false},
		{"LCDPalette[85]","Default",98UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000054, 0, 0, false, false, false},
		{"LCDPalette[86]","Default",99UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000055, 0, 0, false, false, false},
		{"LCDPalette[87]","Default",100UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000056, 0, 0, false, false, false},
		{"LCDPalette[88]","Default",101UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000057, 0, 0, false, false, false},
		{"LCDPalette[89]","Default",102UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000058, 0, 0, false, false, false},
		{"LCDPalette[90]","Default",103UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000059, 0, 0, false, false, false},
		{"LCDPalette[91]","Default",104UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005a, 0, 0, false, false, false},
		{"LCDPalette[92]","Default",105UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005b, 0, 0, false, false, false},
		{"LCDPalette[93]","Default",106UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005c, 0, 0, false, false, false},
		{"LCDPalette[94]","Default",107UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005d, 0, 0, false, false, false},
		{"LCDPalette[95]","Default",108UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005e, 0, 0, false, false, false},
		{"LCDPalette[96]","Default",109UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005f, 0, 0, false, false, false},
		{"LCDPalette[97]","Default",110UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000060, 0, 0, false, false, false},
		{"LCDPalette[98]","Default",111UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000061, 0, 0, false, false, false},
		{"LCDPalette[99]","Default",112UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000062, 0, 0, false, false, false},
		{"LCDPalette[100]","Default",113UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000063, 0, 0, false, false, false},
		{"LCDPalette[101]","Default",114UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000064, 0, 0, false, false, false},
		{"LCDPalette[102]","Default",115UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000065, 0, 0, false, false, false},
		{"LCDPalette[103]","Default",116UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000066, 0, 0, false, false, false},
		{"LCDPalette[104]","Default",117UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000067, 0, 0, false, false, false},
		{"LCDPalette[105]","Default",118UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000068, 0, 0, false, false, false},
		{"LCDPalette[106]","Default",119UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000069, 0, 0, false, false, false},
		{"LCDPalette[107]","Default",120UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006a, 0, 0, false, false, false},
		{"LCDPalette[108]","Default",121UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006b, 0, 0, false, false, false},
		{"LCDPalette[109]","Default",122UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006c, 0, 0, false, false, false},
		{"LCDPalette[110]","Default",123UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006d, 0, 0, false, false, false},
		{"LCDPalette[111]","Default",124UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006e, 0, 0, false, false, false},
		{"LCDPalette[112]","Default",125UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006f, 0, 0, false, false, false},
		{"LCDPalette[113]","Default",126UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000070, 0, 0, false, false, false},
		{"LCDPalette[114]","Default",127UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000071, 0, 0, false, false, false},
		{"LCDPalette[115]","Default",128UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000072, 0, 0, false, false, false},
		{"LCDPalette[116]","Default",129UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000073, 0, 0, false, false, false},
		{"LCDPalette[117]","Default",130UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000074, 0, 0, false, false, false},
		{"LCDPalette[118]","Default",131UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000075, 0, 0, false, false, false},
		{"LCDPalette[119]","Default",132UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000076, 0, 0, false, false, false},
		{"LCDPalette[120]","Default",133UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000077, 0, 0, false, false, false},
		{"LCDPalette[121]","Default",134UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000078, 0, 0, false, false, false},
		{"LCDPalette[122]","Default",135UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000079, 0, 0, false, false, false},
		{"LCDPalette[123]","Default",136UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007a, 0, 0, false, false, false},
		{"LCDPalette[124]","Default",137UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007b, 0, 0, false, false, false},
		{"LCDPalette[125]","Default",138UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007c, 0, 0, false, false, false},
		{"LCDPalette[126]","Default",139UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007d, 0, 0, false, false, false},
		{"LCDPalette[127]","Default",140UL, 32, eslapi::CADI_REGTYPE_HEX, "LCD Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007e, 0, 0, false, false, false},
		{"CursorImage[0]","Default",141UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CursorImage[1]","Default",142UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000000, 0, 0, false, false, false},
		{"CursorImage[2]","Default",143UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000001, 0, 0, false, false, false},
		{"CursorImage[3]","Default",144UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000002, 0, 0, false, false, false},
		{"CursorImage[4]","Default",145UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000003, 0, 0, false, false, false},
		{"CursorImage[5]","Default",146UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000004, 0, 0, false, false, false},
		{"CursorImage[6]","Default",147UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000005, 0, 0, false, false, false},
		{"CursorImage[7]","Default",148UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000006, 0, 0, false, false, false},
		{"CursorImage[8]","Default",149UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000007, 0, 0, false, false, false},
		{"CursorImage[9]","Default",150UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000008, 0, 0, false, false, false},
		{"CursorImage[10]","Default",151UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000009, 0, 0, false, false, false},
		{"CursorImage[11]","Default",152UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000a, 0, 0, false, false, false},
		{"CursorImage[12]","Default",153UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000b, 0, 0, false, false, false},
		{"CursorImage[13]","Default",154UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000c, 0, 0, false, false, false},
		{"CursorImage[14]","Default",155UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000d, 0, 0, false, false, false},
		{"CursorImage[15]","Default",156UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000e, 0, 0, false, false, false},
		{"CursorImage[16]","Default",157UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000000f, 0, 0, false, false, false},
		{"CursorImage[17]","Default",158UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000010, 0, 0, false, false, false},
		{"CursorImage[18]","Default",159UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000011, 0, 0, false, false, false},
		{"CursorImage[19]","Default",160UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000012, 0, 0, false, false, false},
		{"CursorImage[20]","Default",161UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000013, 0, 0, false, false, false},
		{"CursorImage[21]","Default",162UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000014, 0, 0, false, false, false},
		{"CursorImage[22]","Default",163UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000015, 0, 0, false, false, false},
		{"CursorImage[23]","Default",164UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000016, 0, 0, false, false, false},
		{"CursorImage[24]","Default",165UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000017, 0, 0, false, false, false},
		{"CursorImage[25]","Default",166UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000018, 0, 0, false, false, false},
		{"CursorImage[26]","Default",167UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000019, 0, 0, false, false, false},
		{"CursorImage[27]","Default",168UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001a, 0, 0, false, false, false},
		{"CursorImage[28]","Default",169UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001b, 0, 0, false, false, false},
		{"CursorImage[29]","Default",170UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001c, 0, 0, false, false, false},
		{"CursorImage[30]","Default",171UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001d, 0, 0, false, false, false},
		{"CursorImage[31]","Default",172UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001e, 0, 0, false, false, false},
		{"CursorImage[32]","Default",173UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000001f, 0, 0, false, false, false},
		{"CursorImage[33]","Default",174UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000020, 0, 0, false, false, false},
		{"CursorImage[34]","Default",175UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000021, 0, 0, false, false, false},
		{"CursorImage[35]","Default",176UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000022, 0, 0, false, false, false},
		{"CursorImage[36]","Default",177UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000023, 0, 0, false, false, false},
		{"CursorImage[37]","Default",178UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000024, 0, 0, false, false, false},
		{"CursorImage[38]","Default",179UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000025, 0, 0, false, false, false},
		{"CursorImage[39]","Default",180UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000026, 0, 0, false, false, false},
		{"CursorImage[40]","Default",181UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000027, 0, 0, false, false, false},
		{"CursorImage[41]","Default",182UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000028, 0, 0, false, false, false},
		{"CursorImage[42]","Default",183UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000029, 0, 0, false, false, false},
		{"CursorImage[43]","Default",184UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002a, 0, 0, false, false, false},
		{"CursorImage[44]","Default",185UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002b, 0, 0, false, false, false},
		{"CursorImage[45]","Default",186UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002c, 0, 0, false, false, false},
		{"CursorImage[46]","Default",187UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002d, 0, 0, false, false, false},
		{"CursorImage[47]","Default",188UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002e, 0, 0, false, false, false},
		{"CursorImage[48]","Default",189UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000002f, 0, 0, false, false, false},
		{"CursorImage[49]","Default",190UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000030, 0, 0, false, false, false},
		{"CursorImage[50]","Default",191UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000031, 0, 0, false, false, false},
		{"CursorImage[51]","Default",192UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000032, 0, 0, false, false, false},
		{"CursorImage[52]","Default",193UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000033, 0, 0, false, false, false},
		{"CursorImage[53]","Default",194UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000034, 0, 0, false, false, false},
		{"CursorImage[54]","Default",195UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000035, 0, 0, false, false, false},
		{"CursorImage[55]","Default",196UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000036, 0, 0, false, false, false},
		{"CursorImage[56]","Default",197UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000037, 0, 0, false, false, false},
		{"CursorImage[57]","Default",198UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000038, 0, 0, false, false, false},
		{"CursorImage[58]","Default",199UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000039, 0, 0, false, false, false},
		{"CursorImage[59]","Default",200UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003a, 0, 0, false, false, false},
		{"CursorImage[60]","Default",201UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003b, 0, 0, false, false, false},
		{"CursorImage[61]","Default",202UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003c, 0, 0, false, false, false},
		{"CursorImage[62]","Default",203UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003d, 0, 0, false, false, false},
		{"CursorImage[63]","Default",204UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003e, 0, 0, false, false, false},
		{"CursorImage[64]","Default",205UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000003f, 0, 0, false, false, false},
		{"CursorImage[65]","Default",206UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000040, 0, 0, false, false, false},
		{"CursorImage[66]","Default",207UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000041, 0, 0, false, false, false},
		{"CursorImage[67]","Default",208UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000042, 0, 0, false, false, false},
		{"CursorImage[68]","Default",209UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000043, 0, 0, false, false, false},
		{"CursorImage[69]","Default",210UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000044, 0, 0, false, false, false},
		{"CursorImage[70]","Default",211UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000045, 0, 0, false, false, false},
		{"CursorImage[71]","Default",212UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000046, 0, 0, false, false, false},
		{"CursorImage[72]","Default",213UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000047, 0, 0, false, false, false},
		{"CursorImage[73]","Default",214UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000048, 0, 0, false, false, false},
		{"CursorImage[74]","Default",215UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000049, 0, 0, false, false, false},
		{"CursorImage[75]","Default",216UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004a, 0, 0, false, false, false},
		{"CursorImage[76]","Default",217UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004b, 0, 0, false, false, false},
		{"CursorImage[77]","Default",218UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004c, 0, 0, false, false, false},
		{"CursorImage[78]","Default",219UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004d, 0, 0, false, false, false},
		{"CursorImage[79]","Default",220UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004e, 0, 0, false, false, false},
		{"CursorImage[80]","Default",221UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000004f, 0, 0, false, false, false},
		{"CursorImage[81]","Default",222UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000050, 0, 0, false, false, false},
		{"CursorImage[82]","Default",223UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000051, 0, 0, false, false, false},
		{"CursorImage[83]","Default",224UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000052, 0, 0, false, false, false},
		{"CursorImage[84]","Default",225UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000053, 0, 0, false, false, false},
		{"CursorImage[85]","Default",226UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000054, 0, 0, false, false, false},
		{"CursorImage[86]","Default",227UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000055, 0, 0, false, false, false},
		{"CursorImage[87]","Default",228UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000056, 0, 0, false, false, false},
		{"CursorImage[88]","Default",229UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000057, 0, 0, false, false, false},
		{"CursorImage[89]","Default",230UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000058, 0, 0, false, false, false},
		{"CursorImage[90]","Default",231UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000059, 0, 0, false, false, false},
		{"CursorImage[91]","Default",232UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005a, 0, 0, false, false, false},
		{"CursorImage[92]","Default",233UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005b, 0, 0, false, false, false},
		{"CursorImage[93]","Default",234UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005c, 0, 0, false, false, false},
		{"CursorImage[94]","Default",235UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005d, 0, 0, false, false, false},
		{"CursorImage[95]","Default",236UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005e, 0, 0, false, false, false},
		{"CursorImage[96]","Default",237UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000005f, 0, 0, false, false, false},
		{"CursorImage[97]","Default",238UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000060, 0, 0, false, false, false},
		{"CursorImage[98]","Default",239UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000061, 0, 0, false, false, false},
		{"CursorImage[99]","Default",240UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000062, 0, 0, false, false, false},
		{"CursorImage[100]","Default",241UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000063, 0, 0, false, false, false},
		{"CursorImage[101]","Default",242UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000064, 0, 0, false, false, false},
		{"CursorImage[102]","Default",243UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000065, 0, 0, false, false, false},
		{"CursorImage[103]","Default",244UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000066, 0, 0, false, false, false},
		{"CursorImage[104]","Default",245UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000067, 0, 0, false, false, false},
		{"CursorImage[105]","Default",246UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000068, 0, 0, false, false, false},
		{"CursorImage[106]","Default",247UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000069, 0, 0, false, false, false},
		{"CursorImage[107]","Default",248UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006a, 0, 0, false, false, false},
		{"CursorImage[108]","Default",249UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006b, 0, 0, false, false, false},
		{"CursorImage[109]","Default",250UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006c, 0, 0, false, false, false},
		{"CursorImage[110]","Default",251UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006d, 0, 0, false, false, false},
		{"CursorImage[111]","Default",252UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006e, 0, 0, false, false, false},
		{"CursorImage[112]","Default",253UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000006f, 0, 0, false, false, false},
		{"CursorImage[113]","Default",254UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000070, 0, 0, false, false, false},
		{"CursorImage[114]","Default",255UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000071, 0, 0, false, false, false},
		{"CursorImage[115]","Default",256UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000072, 0, 0, false, false, false},
		{"CursorImage[116]","Default",257UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000073, 0, 0, false, false, false},
		{"CursorImage[117]","Default",258UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000074, 0, 0, false, false, false},
		{"CursorImage[118]","Default",259UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000075, 0, 0, false, false, false},
		{"CursorImage[119]","Default",260UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000076, 0, 0, false, false, false},
		{"CursorImage[120]","Default",261UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000077, 0, 0, false, false, false},
		{"CursorImage[121]","Default",262UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000078, 0, 0, false, false, false},
		{"CursorImage[122]","Default",263UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000079, 0, 0, false, false, false},
		{"CursorImage[123]","Default",264UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007a, 0, 0, false, false, false},
		{"CursorImage[124]","Default",265UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007b, 0, 0, false, false, false},
		{"CursorImage[125]","Default",266UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007c, 0, 0, false, false, false},
		{"CursorImage[126]","Default",267UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007d, 0, 0, false, false, false},
		{"CursorImage[127]","Default",268UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007e, 0, 0, false, false, false},
		{"CursorImage[128]","Default",269UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000007f, 0, 0, false, false, false},
		{"CursorImage[129]","Default",270UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000080, 0, 0, false, false, false},
		{"CursorImage[130]","Default",271UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000081, 0, 0, false, false, false},
		{"CursorImage[131]","Default",272UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000082, 0, 0, false, false, false},
		{"CursorImage[132]","Default",273UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000083, 0, 0, false, false, false},
		{"CursorImage[133]","Default",274UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000084, 0, 0, false, false, false},
		{"CursorImage[134]","Default",275UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000085, 0, 0, false, false, false},
		{"CursorImage[135]","Default",276UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000086, 0, 0, false, false, false},
		{"CursorImage[136]","Default",277UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000087, 0, 0, false, false, false},
		{"CursorImage[137]","Default",278UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000088, 0, 0, false, false, false},
		{"CursorImage[138]","Default",279UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000089, 0, 0, false, false, false},
		{"CursorImage[139]","Default",280UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000008a, 0, 0, false, false, false},
		{"CursorImage[140]","Default",281UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000008b, 0, 0, false, false, false},
		{"CursorImage[141]","Default",282UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000008c, 0, 0, false, false, false},
		{"CursorImage[142]","Default",283UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000008d, 0, 0, false, false, false},
		{"CursorImage[143]","Default",284UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000008e, 0, 0, false, false, false},
		{"CursorImage[144]","Default",285UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000008f, 0, 0, false, false, false},
		{"CursorImage[145]","Default",286UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000090, 0, 0, false, false, false},
		{"CursorImage[146]","Default",287UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000091, 0, 0, false, false, false},
		{"CursorImage[147]","Default",288UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000092, 0, 0, false, false, false},
		{"CursorImage[148]","Default",289UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000093, 0, 0, false, false, false},
		{"CursorImage[149]","Default",290UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000094, 0, 0, false, false, false},
		{"CursorImage[150]","Default",291UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000095, 0, 0, false, false, false},
		{"CursorImage[151]","Default",292UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000096, 0, 0, false, false, false},
		{"CursorImage[152]","Default",293UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000097, 0, 0, false, false, false},
		{"CursorImage[153]","Default",294UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000098, 0, 0, false, false, false},
		{"CursorImage[154]","Default",295UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x00000099, 0, 0, false, false, false},
		{"CursorImage[155]","Default",296UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000009a, 0, 0, false, false, false},
		{"CursorImage[156]","Default",297UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000009b, 0, 0, false, false, false},
		{"CursorImage[157]","Default",298UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000009c, 0, 0, false, false, false},
		{"CursorImage[158]","Default",299UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000009d, 0, 0, false, false, false},
		{"CursorImage[159]","Default",300UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000009e, 0, 0, false, false, false},
		{"CursorImage[160]","Default",301UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x0000009f, 0, 0, false, false, false},
		{"CursorImage[161]","Default",302UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a0, 0, 0, false, false, false},
		{"CursorImage[162]","Default",303UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a1, 0, 0, false, false, false},
		{"CursorImage[163]","Default",304UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a2, 0, 0, false, false, false},
		{"CursorImage[164]","Default",305UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a3, 0, 0, false, false, false},
		{"CursorImage[165]","Default",306UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a4, 0, 0, false, false, false},
		{"CursorImage[166]","Default",307UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a5, 0, 0, false, false, false},
		{"CursorImage[167]","Default",308UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a6, 0, 0, false, false, false},
		{"CursorImage[168]","Default",309UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a7, 0, 0, false, false, false},
		{"CursorImage[169]","Default",310UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a8, 0, 0, false, false, false},
		{"CursorImage[170]","Default",311UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000a9, 0, 0, false, false, false},
		{"CursorImage[171]","Default",312UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000aa, 0, 0, false, false, false},
		{"CursorImage[172]","Default",313UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ab, 0, 0, false, false, false},
		{"CursorImage[173]","Default",314UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ac, 0, 0, false, false, false},
		{"CursorImage[174]","Default",315UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ad, 0, 0, false, false, false},
		{"CursorImage[175]","Default",316UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ae, 0, 0, false, false, false},
		{"CursorImage[176]","Default",317UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000af, 0, 0, false, false, false},
		{"CursorImage[177]","Default",318UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b0, 0, 0, false, false, false},
		{"CursorImage[178]","Default",319UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b1, 0, 0, false, false, false},
		{"CursorImage[179]","Default",320UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b2, 0, 0, false, false, false},
		{"CursorImage[180]","Default",321UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b3, 0, 0, false, false, false},
		{"CursorImage[181]","Default",322UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b4, 0, 0, false, false, false},
		{"CursorImage[182]","Default",323UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b5, 0, 0, false, false, false},
		{"CursorImage[183]","Default",324UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b6, 0, 0, false, false, false},
		{"CursorImage[184]","Default",325UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b7, 0, 0, false, false, false},
		{"CursorImage[185]","Default",326UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b8, 0, 0, false, false, false},
		{"CursorImage[186]","Default",327UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000b9, 0, 0, false, false, false},
		{"CursorImage[187]","Default",328UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ba, 0, 0, false, false, false},
		{"CursorImage[188]","Default",329UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000bb, 0, 0, false, false, false},
		{"CursorImage[189]","Default",330UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000bc, 0, 0, false, false, false},
		{"CursorImage[190]","Default",331UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000bd, 0, 0, false, false, false},
		{"CursorImage[191]","Default",332UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000be, 0, 0, false, false, false},
		{"CursorImage[192]","Default",333UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000bf, 0, 0, false, false, false},
		{"CursorImage[193]","Default",334UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c0, 0, 0, false, false, false},
		{"CursorImage[194]","Default",335UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c1, 0, 0, false, false, false},
		{"CursorImage[195]","Default",336UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c2, 0, 0, false, false, false},
		{"CursorImage[196]","Default",337UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c3, 0, 0, false, false, false},
		{"CursorImage[197]","Default",338UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c4, 0, 0, false, false, false},
		{"CursorImage[198]","Default",339UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c5, 0, 0, false, false, false},
		{"CursorImage[199]","Default",340UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c6, 0, 0, false, false, false},
		{"CursorImage[200]","Default",341UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c7, 0, 0, false, false, false},
		{"CursorImage[201]","Default",342UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c8, 0, 0, false, false, false},
		{"CursorImage[202]","Default",343UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000c9, 0, 0, false, false, false},
		{"CursorImage[203]","Default",344UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ca, 0, 0, false, false, false},
		{"CursorImage[204]","Default",345UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000cb, 0, 0, false, false, false},
		{"CursorImage[205]","Default",346UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000cc, 0, 0, false, false, false},
		{"CursorImage[206]","Default",347UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000cd, 0, 0, false, false, false},
		{"CursorImage[207]","Default",348UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ce, 0, 0, false, false, false},
		{"CursorImage[208]","Default",349UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000cf, 0, 0, false, false, false},
		{"CursorImage[209]","Default",350UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d0, 0, 0, false, false, false},
		{"CursorImage[210]","Default",351UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d1, 0, 0, false, false, false},
		{"CursorImage[211]","Default",352UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d2, 0, 0, false, false, false},
		{"CursorImage[212]","Default",353UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d3, 0, 0, false, false, false},
		{"CursorImage[213]","Default",354UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d4, 0, 0, false, false, false},
		{"CursorImage[214]","Default",355UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d5, 0, 0, false, false, false},
		{"CursorImage[215]","Default",356UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d6, 0, 0, false, false, false},
		{"CursorImage[216]","Default",357UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d7, 0, 0, false, false, false},
		{"CursorImage[217]","Default",358UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d8, 0, 0, false, false, false},
		{"CursorImage[218]","Default",359UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000d9, 0, 0, false, false, false},
		{"CursorImage[219]","Default",360UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000da, 0, 0, false, false, false},
		{"CursorImage[220]","Default",361UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000db, 0, 0, false, false, false},
		{"CursorImage[221]","Default",362UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000dc, 0, 0, false, false, false},
		{"CursorImage[222]","Default",363UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000dd, 0, 0, false, false, false},
		{"CursorImage[223]","Default",364UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000de, 0, 0, false, false, false},
		{"CursorImage[224]","Default",365UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000df, 0, 0, false, false, false},
		{"CursorImage[225]","Default",366UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e0, 0, 0, false, false, false},
		{"CursorImage[226]","Default",367UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e1, 0, 0, false, false, false},
		{"CursorImage[227]","Default",368UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e2, 0, 0, false, false, false},
		{"CursorImage[228]","Default",369UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e3, 0, 0, false, false, false},
		{"CursorImage[229]","Default",370UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e4, 0, 0, false, false, false},
		{"CursorImage[230]","Default",371UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e5, 0, 0, false, false, false},
		{"CursorImage[231]","Default",372UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e6, 0, 0, false, false, false},
		{"CursorImage[232]","Default",373UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e7, 0, 0, false, false, false},
		{"CursorImage[233]","Default",374UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e8, 0, 0, false, false, false},
		{"CursorImage[234]","Default",375UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000e9, 0, 0, false, false, false},
		{"CursorImage[235]","Default",376UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ea, 0, 0, false, false, false},
		{"CursorImage[236]","Default",377UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000eb, 0, 0, false, false, false},
		{"CursorImage[237]","Default",378UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ec, 0, 0, false, false, false},
		{"CursorImage[238]","Default",379UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ed, 0, 0, false, false, false},
		{"CursorImage[239]","Default",380UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ee, 0, 0, false, false, false},
		{"CursorImage[240]","Default",381UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000ef, 0, 0, false, false, false},
		{"CursorImage[241]","Default",382UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f0, 0, 0, false, false, false},
		{"CursorImage[242]","Default",383UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f1, 0, 0, false, false, false},
		{"CursorImage[243]","Default",384UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f2, 0, 0, false, false, false},
		{"CursorImage[244]","Default",385UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f3, 0, 0, false, false, false},
		{"CursorImage[245]","Default",386UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f4, 0, 0, false, false, false},
		{"CursorImage[246]","Default",387UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f5, 0, 0, false, false, false},
		{"CursorImage[247]","Default",388UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f6, 0, 0, false, false, false},
		{"CursorImage[248]","Default",389UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f7, 0, 0, false, false, false},
		{"CursorImage[249]","Default",390UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f8, 0, 0, false, false, false},
		{"CursorImage[250]","Default",391UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000f9, 0, 0, false, false, false},
		{"CursorImage[251]","Default",392UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000fa, 0, 0, false, false, false},
		{"CursorImage[252]","Default",393UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000fb, 0, 0, false, false, false},
		{"CursorImage[253]","Default",394UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000fc, 0, 0, false, false, false},
		{"CursorImage[254]","Default",395UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000fd, 0, 0, false, false, false},
		{"CursorImage[255]","Default",396UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Image RAM(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0x000000fe, 0, 0, false, false, false},
		{"ClcdCrsrCtrl","Default",3072UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Control(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrConfig","Default",3076UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Configuration(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrPalette0","Default",3080UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrPalette1","Default",3084UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Palette(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrXY","Default",3088UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor XY Position(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrClip","Default",3092UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Clip Position(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrIMSC","Default",3104UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Interrupt Mask Set/Clear(RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrICR","Default",3108UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Interrupt Clear(WO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrRIS","Default",3112UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Raw Interrupt Status(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"ClcdCrsrMIS","Default",3116UL, 32, eslapi::CADI_REGTYPE_HEX, "Cursor Masked Interrupt Status(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CLCDPERIPHID0","Default",4064UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral identification register bits [7:0](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CLCDPERIPHID1","Default",4068UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral identification register bits [15:8](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CLCDPERIPHID2","Default",4072UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral identification register bits [23:16](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CLCDPERIPHID3","Default",4076UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral identification register bits [31:23](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CLCDPCELLID0","Default",4080UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell identification register bits [7:0](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CLCDPCELLID1","Default",4084UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell identification register bits [15:8](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CLCDPCELLID2","Default",4088UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell identification register bits [23:16](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"CLCDPCELLID3","Default",4092UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell identification register bits [31:23](RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->LCDTiming0, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDTiming1, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDTiming2, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDTiming3, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDUPBASE, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDLPBASE, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDControl, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDIMSC, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDRIS, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDMIS, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDICR, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDUPCURR, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDLPCURR, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[0], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[1], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[2], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[3], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[4], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[5], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[6], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[7], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[8], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[9], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[10], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[11], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[12], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[13], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[14], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[15], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[16], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[17], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[18], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[19], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[20], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[21], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[22], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[23], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[24], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[25], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[26], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[27], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[28], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[29], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[30], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[31], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[32], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[33], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[34], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[35], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[36], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[37], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[38], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[39], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[40], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[41], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[42], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[43], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[44], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[45], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[46], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[47], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[48], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[49], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[50], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[51], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[52], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[53], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[54], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[55], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[56], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[57], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[58], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[59], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[60], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[61], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[62], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[63], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[64], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[65], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[66], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[67], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[68], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[69], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[70], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[71], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[72], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[73], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[74], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[75], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[76], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[77], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[78], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[79], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[80], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[81], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[82], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[83], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[84], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[85], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[86], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[87], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[88], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[89], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[90], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[91], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[92], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[93], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[94], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[95], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[96], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[97], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[98], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[99], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[100], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[101], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[102], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[103], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[104], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[105], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[106], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[107], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[108], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[109], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[110], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[111], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[112], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[113], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[114], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[115], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[116], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[117], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[118], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[119], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[120], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[121], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[122], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[123], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[124], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[125], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[126], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->LCDPalette[127], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[0], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[1], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[2], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[3], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[4], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[5], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[6], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[7], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[8], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[9], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[10], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[11], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[12], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[13], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[14], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[15], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[16], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[17], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[18], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[19], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[20], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[21], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[22], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[23], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[24], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[25], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[26], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[27], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[28], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[29], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[30], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[31], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[32], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[33], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[34], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[35], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[36], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[37], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[38], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[39], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[40], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[41], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[42], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[43], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[44], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[45], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[46], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[47], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[48], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[49], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[50], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[51], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[52], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[53], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[54], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[55], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[56], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[57], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[58], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[59], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[60], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[61], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[62], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[63], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[64], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[65], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[66], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[67], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[68], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[69], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[70], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[71], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[72], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[73], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[74], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[75], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[76], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[77], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[78], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[79], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[80], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[81], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[82], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[83], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[84], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[85], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[86], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[87], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[88], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[89], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[90], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[91], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[92], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[93], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[94], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[95], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[96], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[97], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[98], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[99], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[100], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[101], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[102], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[103], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[104], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[105], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[106], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[107], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[108], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[109], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[110], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[111], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[112], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[113], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[114], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[115], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[116], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[117], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[118], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[119], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[120], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[121], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[122], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[123], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[124], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[125], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[126], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[127], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[128], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[129], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[130], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[131], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[132], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[133], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[134], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[135], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[136], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[137], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[138], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[139], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[140], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[141], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[142], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[143], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[144], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[145], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[146], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[147], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[148], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[149], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[150], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[151], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[152], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[153], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[154], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[155], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[156], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[157], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[158], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[159], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[160], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[161], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[162], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[163], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[164], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[165], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[166], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[167], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[168], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[169], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[170], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[171], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[172], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[173], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[174], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[175], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[176], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[177], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[178], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[179], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[180], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[181], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[182], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[183], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[184], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[185], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[186], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[187], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[188], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[189], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[190], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[191], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[192], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[193], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[194], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[195], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[196], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[197], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[198], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[199], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[200], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[201], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[202], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[203], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[204], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[205], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[206], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[207], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[208], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[209], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[210], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[211], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[212], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[213], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[214], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[215], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[216], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[217], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[218], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[219], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[220], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[221], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[222], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[223], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[224], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[225], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[226], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[227], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[228], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[229], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[230], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[231], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[232], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[233], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[234], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[235], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[236], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[237], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[238], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[239], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[240], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[241], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[242], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[243], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[244], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[245], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[246], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[247], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[248], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[249], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[250], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[251], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[252], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[253], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[254], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CursorImage[255], 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrCtrl, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrConfig, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrPalette0, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrPalette1, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrXY, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrClip, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrIMSC, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrICR, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrRIS, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->ClcdCrsrMIS, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CLCDPERIPHID0, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CLCDPERIPHID1, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CLCDPERIPHID2, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CLCDPERIPHID3, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CLCDPCELLID0, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CLCDPCELLID1, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CLCDPCELLID2, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},
		{&parentComponent->CLCDPCELLID3, 0, 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_read),0,MakeDelegate(parentComponent, &Component__PL111_CLCD::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__PL111_CLCD_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000002B, MakeDelegate(parentComponent, &Component__PL111_CLCD::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL111_CLCD::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PL111_CLCD" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PL111_CLCD_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PL111_CLCD_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL11x_CLCD
// ------------------------------------------------------------------------------

#include "Component__PL11x_CLCD_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PL11x_CLCD_CADI::Component__PL11x_CLCD_CADI(Component__PL11x_CLCD* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__PL11x_CLCD_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000002B, MakeDelegate(parentComponent, &Component__PL11x_CLCD::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL11x_CLCD::parameter_write_func), 0 },
		{ 0x1000002C, MakeDelegate(parentComponent, &Component__PL11x_CLCD::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__PL11x_CLCD::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PL11x_CLCD" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PL11x_CLCD_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PL11x_CLCD_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PL180_MCI
// ------------------------------------------------------------------------------

#include "Component__PL180_MCI_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PL180_MCI_CADI::Component__PL180_MCI_CADI(Component__PL180_MCI* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"MCIPower","Default",0UL, 8, eslapi::CADI_REGTYPE_HEX, "Power control register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIClock","Default",4UL, 16, eslapi::CADI_REGTYPE_HEX, "Clock control register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIArgument","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "Argument register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCICommand","Default",12UL, 16, eslapi::CADI_REGTYPE_HEX, "Command register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIRespCmd","Default",16UL, 8, eslapi::CADI_REGTYPE_HEX, "Response command register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIResponse0","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "Response register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIResponse1","Default",24UL, 32, eslapi::CADI_REGTYPE_HEX, "Response register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIResponse2","Default",28UL, 32, eslapi::CADI_REGTYPE_HEX, "Response register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIResponse3","Default",32UL, 32, eslapi::CADI_REGTYPE_HEX, "Response register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIDataTimer","Default",36UL, 32, eslapi::CADI_REGTYPE_HEX, "Data timer", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIDataLength","Default",40UL, 16, eslapi::CADI_REGTYPE_HEX, "Data length register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIDataCtrl","Default",44UL, 8, eslapi::CADI_REGTYPE_HEX, "Data control register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIDataCnt","Default",48UL, 16, eslapi::CADI_REGTYPE_HEX, "Data counter", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIStatus","Default",52UL, 32, eslapi::CADI_REGTYPE_HEX, "Status register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIClear","Default",56UL, 16, eslapi::CADI_REGTYPE_HEX, "Clear register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIMask0","Default",60UL, 32, eslapi::CADI_REGTYPE_HEX, "Interrupt 0 mask register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIMask1","Default",64UL, 32, eslapi::CADI_REGTYPE_HEX, "Interrupt 1 mask register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCISelect","Default",68UL, 8, eslapi::CADI_REGTYPE_HEX, "SD card select register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIFifoCnt","Default",72UL, 16, eslapi::CADI_REGTYPE_HEX, "FIFO counter", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIFIFO","Default",128UL, 32, eslapi::CADI_REGTYPE_HEX, "Data FIFO register", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIPeriphID0","Default",4064UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral ID bits 7:0", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIPeriphID1","Default",4068UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral ID bits 8:15", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIPeriphID2","Default",4072UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral ID bits 23:16", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIPeriphID3","Default",4076UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral ID bits 31:24", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIPCellID0","Default",4080UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell ID bits 7:0", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIPCellID1","Default",4084UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell ID bits 8:15", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIPCellID2","Default",4088UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell ID bits 23:16", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MCIPCellID3","Default",4092UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell ID bits 31:24", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->MCIPower, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIClock, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIArgument, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCICommand, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIRespCmd, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIResponse0, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIResponse1, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIResponse2, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIResponse3, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIDataTimer, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIDataLength, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIDataCtrl, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIDataCnt, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIStatus, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIClear, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIMask0, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIMask1, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCISelect, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIFifoCnt, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIFIFO, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIPeriphID0, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIPeriphID1, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIPeriphID2, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIPeriphID3, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIPCellID0, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIPCellID1, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIPCellID2, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},
		{&parentComponent->MCIPCellID3, 0, 0, MakeDelegate(parentComponent, &Component__PL180_MCI::debug_read),0,MakeDelegate(parentComponent, &Component__PL180_MCI::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__PL180_MCI_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PL180_MCI" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PL180_MCI_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PL180_MCI_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PS2Keyboard
// ------------------------------------------------------------------------------

#include "Component__PS2Keyboard_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PS2Keyboard_CADI::Component__PS2Keyboard_CADI(Component__PS2Keyboard* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__PS2Keyboard_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PS2Keyboard" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PS2Keyboard_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PS2Keyboard_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__PS2Mouse
// ------------------------------------------------------------------------------

#include "Component__PS2Mouse_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__PS2Mouse_CADI::Component__PS2Mouse_CADI(Component__PS2Mouse* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__PS2Mouse_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "PS2Mouse" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__PS2Mouse_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__PS2Mouse_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__SP805_Watchdog
// ------------------------------------------------------------------------------

#include "Component__SP805_Watchdog_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__SP805_Watchdog_CADI::Component__SP805_Watchdog_CADI(Component__SP805_Watchdog* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"SP805_WDOG_Load","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SP805_WDOG_VALUE","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SP805_WDOG_CONTROL","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SP805_WDOG_INT_CLR","Default",12UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SP805_WDOG_RAW_INT_STATUS","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SP805_WDOG_MASKED_INT_STATUS","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SP805_WDOG_LOCK","Default",3072UL, 32, eslapi::CADI_REGTYPE_HEX, "", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->SP805_WDOG_Load, 0, 0, MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_read),0,MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_write),0},
		{&parentComponent->SP805_WDOG_VALUE, 0, 0, MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_read),0,MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_write),0},
		{&parentComponent->SP805_WDOG_CONTROL, 0, 0, MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_read),0,MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_write),0},
		{&parentComponent->SP805_WDOG_INT_CLR, 0, 0, MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_read),0,MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_write),0},
		{&parentComponent->SP805_WDOG_RAW_INT_STATUS, 0, 0, MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_read),0,MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_write),0},
		{&parentComponent->SP805_WDOG_MASKED_INT_STATUS, 0, 0, MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_read),0,MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_write),0},
		{&parentComponent->SP805_WDOG_LOCK, 0, 0, MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_read),0,MakeDelegate(parentComponent, &Component__SP805_Watchdog::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__SP805_Watchdog_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000002D, MakeDelegate(parentComponent, &Component__SP805_Watchdog::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__SP805_Watchdog::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "SP805_Watchdog" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__SP805_Watchdog_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__SP805_Watchdog_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__SP810_SysCtrl
// ------------------------------------------------------------------------------

#include "Component__SP810_SysCtrl_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__SP810_SysCtrl_CADI::Component__SP810_SysCtrl_CADI(Component__SP810_SysCtrl* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"SCCTRL","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "System Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCSYSSTAT","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "System Status (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCIMCTRL","Default",8UL, 8, eslapi::CADI_REGTYPE_HEX, "Interrupt Mode Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCIMSTAT","Default",12UL, 8, eslapi::CADI_REGTYPE_HEX, "Interrupt Mode Status (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCXTALCTRL","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "Crystal Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPLLCTRL","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "PLL Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPLLFCTRL","Default",24UL, 32, eslapi::CADI_REGTYPE_HEX, "PLL Frequency Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPERCTRL0","Default",28UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPERCTRL1","Default",32UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPEREN","Default",36UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral Clock Enable (WO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPERDIS","Default",40UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral Clock Disable (WO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPERCLKEN","Default",44UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral Clock Enable Status (RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPERSTAT","Default",48UL, 32, eslapi::CADI_REGTYPE_HEX, "Peripheral Clock Status (RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCSysID0","Default",3808UL, 8, eslapi::CADI_REGTYPE_HEX, "System Identification 0 (RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCSysID1","Default",3812UL, 8, eslapi::CADI_REGTYPE_HEX, "System Identification 1 (RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCSysID2","Default",3816UL, 8, eslapi::CADI_REGTYPE_HEX, "System Identification 2 (RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCSysID3","Default",3820UL, 8, eslapi::CADI_REGTYPE_HEX, "System Identification 3 (RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCITCR","Default",3840UL, 8, eslapi::CADI_REGTYPE_HEX, "Integration Test Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCITIR0","Default",3844UL, 16, eslapi::CADI_REGTYPE_HEX, "Integration Test Input 0 (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCITIR1","Default",3848UL, 32, eslapi::CADI_REGTYPE_HEX, "Integration Test Input 1 (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCITOR","Default",3852UL, 16, eslapi::CADI_REGTYPE_HEX, "Integration Test Output (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCCNTCTRL","Default",3856UL, 8, eslapi::CADI_REGTYPE_HEX, "Counter Test Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCCNTDATA","Default",3860UL, 32, eslapi::CADI_REGTYPE_HEX, "Counter Data (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCCNTSTEP","Default",3864UL, 32, eslapi::CADI_REGTYPE_HEX, "Counter Step (WO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPeriphID0","Default",4064UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral Identification 0(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPeriphID1","Default",4068UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral Identification 1(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPeriphID2","Default",4072UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral Identification 2(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPeriphID3","Default",4076UL, 8, eslapi::CADI_REGTYPE_HEX, "Peripheral Identification 3(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPCellID0","Default",4080UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell Identification 0(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPCellID1","Default",4084UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell Identification 1(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPCellID2","Default",4088UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell Identification 2(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SCPCellID3","Default",4092UL, 8, eslapi::CADI_REGTYPE_HEX, "PrimeCell Identification 3(RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->SCCTRL, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCSYSSTAT, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCIMCTRL, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCIMSTAT, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCXTALCTRL, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPLLCTRL, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPLLFCTRL, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPERCTRL0, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPERCTRL1, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPEREN, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPERDIS, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPERCLKEN, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPERSTAT, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCSysID0, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCSysID1, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCSysID2, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCSysID3, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCITCR, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCITIR0, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCITIR1, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCITOR, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCCNTCTRL, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCCNTDATA, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCCNTSTEP, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPeriphID0, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPeriphID1, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPeriphID2, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPeriphID3, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPCellID0, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPCellID1, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPCellID2, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},
		{&parentComponent->SCPCellID3, 0, 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_read),0,MakeDelegate(parentComponent, &Component__SP810_SysCtrl::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__SP810_SysCtrl_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000002E, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::parameter_write_func), 0 },
		{ 0x1000002F, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__SP810_SysCtrl::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "SP810_SysCtrl" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__SP810_SysCtrl_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__SP810_SysCtrl_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VE_SysRegs
// ------------------------------------------------------------------------------

#include "Component__VE_SysRegs_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VE_SysRegs_CADI::Component__VE_SysRegs_CADI(Component__VE_SysRegs* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"SYS_ID","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_ID", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_SW","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_SW", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_LED","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_LED", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_100HZ","Default",36UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_100HZ", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_FLAGS","Default",48UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_FLAGS and SYS_FLAGSSET", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_FLAGSCLR","Default",52UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_FLAGSCLR", eslapi::CADI_REG_WRITE_ONLY, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_NVFLAGS","Default",56UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_NVFLAGS and SYS_NVFLAGSSET", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_NVFLAGSCLR","Default",60UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_NVFLAGSCLR", eslapi::CADI_REG_WRITE_ONLY, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_MCI","Default",72UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_MCI", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_FLASH","Default",76UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_FLASH", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_CFGSW","Default",88UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_CFGSW", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_24MHZ","Default",92UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_24MHZ", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_MISC","Default",96UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_MISC", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_DMA","Default",100UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_DMA", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_PROCID0","Default",132UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_PROCID0", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_PROCID1","Default",136UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_PROCID1", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_CFGDATA","Default",160UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_CFGDATA", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_CFGCTRL","Default",164UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_CFGCTRL", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"SYS_CFGSTAT","Default",168UL, 32, eslapi::CADI_REGTYPE_HEX, "SYS_CFGSTAT", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->SYS_ID, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_SW, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_LED, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_100HZ, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_FLAGS, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_FLAGSCLR, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_NVFLAGS, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_NVFLAGSCLR, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_MCI, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_FLASH, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_CFGSW, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_24MHZ, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_MISC, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_DMA, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_PROCID0, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_PROCID1, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_CFGDATA, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_CFGCTRL, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},
		{&parentComponent->SYS_CFGSTAT, 0, 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_read),0,MakeDelegate(parentComponent, &Component__VE_SysRegs::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__VE_SysRegs_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000013, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_write_func), 0 },
		{ 0x10000014, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_write_func), 0 },
		{ 0x10000030, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_write_func), 0 },
		{ 0x10000031, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_write_func), 0 },
		{ 0x10000032, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VE_SysRegs::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VE_SysRegs" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VE_SysRegs_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VE_SysRegs_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VFS2
// ------------------------------------------------------------------------------

#include "Component__VFS2_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VFS2_CADI::Component__VFS2_CADI(Component__VFS2* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VFS2_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000033, 0, MakeDelegate(parentComponent, &Component__VFS2::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__VFS2::parameter_write_string_func) },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VFS2" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VFS2_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VFS2_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__MessageBox
// ------------------------------------------------------------------------------

#include "Component__MessageBox_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__MessageBox_CADI::Component__MessageBox_CADI(Component__MessageBox* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {
		{"MESSAGEBOX_ID","Default",0UL, 32, eslapi::CADI_REGTYPE_HEX, "MessageBox ID (RO)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MESSAGEBOX_DATA","Default",4UL, 32, eslapi::CADI_REGTYPE_HEX, "Data (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MESSAGEBOX_CONTROL","Default",8UL, 32, eslapi::CADI_REGTYPE_HEX, "Control (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MESSAGEBOX_STATUS","Default",12UL, 32, eslapi::CADI_REGTYPE_HEX, "Status (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MESSAGEBOX_START","Default",16UL, 32, eslapi::CADI_REGTYPE_HEX, "Start (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MESSAGEBOX_END","Default",20UL, 32, eslapi::CADI_REGTYPE_HEX, "End (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
		{"MESSAGEBOX_IRQMASK","Default",24UL, 32, eslapi::CADI_REGTYPE_HEX, "Irq Mask (RW)", eslapi::CADI_REG_READ_WRITE, 0, 0, 0, false, 0, false, 0, 0, 0, false, true, 0xffffffffUL, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 1UL, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {
		{&parentComponent->MESSAGEBOX_ID, 0, 0, MakeDelegate(parentComponent, &Component__MessageBox::debug_read),0,MakeDelegate(parentComponent, &Component__MessageBox::debug_write),0},
		{&parentComponent->MESSAGEBOX_DATA, 0, 0, MakeDelegate(parentComponent, &Component__MessageBox::debug_read),0,MakeDelegate(parentComponent, &Component__MessageBox::debug_write),0},
		{&parentComponent->MESSAGEBOX_CONTROL, 0, 0, MakeDelegate(parentComponent, &Component__MessageBox::debug_read),0,MakeDelegate(parentComponent, &Component__MessageBox::debug_write),0},
		{&parentComponent->MESSAGEBOX_STATUS, 0, 0, MakeDelegate(parentComponent, &Component__MessageBox::debug_read),0,MakeDelegate(parentComponent, &Component__MessageBox::debug_write),0},
		{&parentComponent->MESSAGEBOX_START, 0, 0, MakeDelegate(parentComponent, &Component__MessageBox::debug_read),0,MakeDelegate(parentComponent, &Component__MessageBox::debug_write),0},
		{&parentComponent->MESSAGEBOX_END, 0, 0, MakeDelegate(parentComponent, &Component__MessageBox::debug_read),0,MakeDelegate(parentComponent, &Component__MessageBox::debug_write),0},
		{&parentComponent->MESSAGEBOX_IRQMASK, 0, 0, MakeDelegate(parentComponent, &Component__MessageBox::debug_read),0,MakeDelegate(parentComponent, &Component__MessageBox::debug_write),0},

                {0, 0, 0, 0, MakeDelegate(this, &Component__MessageBox_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000034, MakeDelegate(parentComponent, &Component__MessageBox::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__MessageBox::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "MessageBox" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 1UL;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__MessageBox_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__MessageBox_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VirtualEthernetCrossover
// ------------------------------------------------------------------------------

#include "Component__VirtualEthernetCrossover_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VirtualEthernetCrossover_CADI::Component__VirtualEthernetCrossover_CADI(Component__VirtualEthernetCrossover* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VirtualEthernetCrossover_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VirtualEthernetCrossover" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VirtualEthernetCrossover_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VirtualEthernetCrossover_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VEVisualisation
// ------------------------------------------------------------------------------

#include "Component__VEVisualisation_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VEVisualisation_CADI::Component__VEVisualisation_CADI(Component__VEVisualisation* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VEVisualisation_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x10000035, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_func), 0 },
		{ 0x10000036, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_func), 0 },
		{ 0x10000037, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_func), 0 },
		{ 0x10000038, 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_string_func) },
		{ 0x10000039, 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_string_func) },
		{ 0x1000003A, 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_string_func) },
		{ 0x1000003B, 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_string_func) },
		{ 0x10000011, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_func), 0 },
		{ 0x10000015, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VEVisualisation::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VEVisualisation" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VEVisualisation_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VEVisualisation_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS
// ------------------------------------------------------------------------------
// CADI Interface for component Component__VisEventRecorder
// ------------------------------------------------------------------------------

#include "Component__VisEventRecorder_ClassDef.h"

namespace FVP_VE_Cortex_A15x1_NMS {

// constructor
Component__VisEventRecorder_CADI::Component__VisEventRecorder_CADI(Component__VisEventRecorder* parentComponent, sg::ComponentBase* simulationEngine) :
    sg::CADIBase(parentComponent ? parentComponent->getName() : "", simulationEngine),
    component(parentComponent)
{



        // memory blocks
        MxU32 emptySupportedMultiplesOfMAU[32];
        memset(emptySupportedMultiplesOfMAU, 0, sizeof(emptySupportedMultiplesOfMAU));



        // additional data which is referenced in the data structures


        static RegInfo regData[] =
        {

                {"ETFR", "ExtendedTargetFeatureRegisterGroup", 0, 0, eslapi::CADI_REGTYPE_STRING, "Extended Target Features", eslapi::CADI_REG_READ_ONLY, 0, 0, 0, true, 0, false, 0, 0, 0, true/*pseudo*/, true, 0xFFFFFFFF, 0, 0, 0, 0, 0xffffffff, 0, 0, false, false, false},
        {0, "", 0, 0, eslapi::CADI_REGTYPE_HEX, 0, eslapi::CADI_REG_READ_WRITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // the instance specific data has to be non-static, this is currently only access_data
        // this array is compressed: only registers which have hasInstanceSpecificPointers=true in regData are present here
        RegInfoInstanceSpecific regDataInstanceSpecific[] = {

                {0, 0, 0, 0, MakeDelegate(this, &Component__VisEventRecorder_CADI::GetExtendedTargetFeatures), 0, 0},
                {0, 0, 0, 0, 0, 0, 0}
        };

    ParamInfo paramData[] =
    {
		{ 0x1000003D, 0, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_write_string_func) },
		{ 0x1000003E, 0, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_read_string_func), 0, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_write_string_func) },
		{ 0x1000003F, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_write_func), 0 },
		{ 0x10000040, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_write_func), 0 },
		{ 0x10000041, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_read_func), 0, MakeDelegate(parentComponent, &Component__VisEventRecorder::parameter_write_func), 0 },

        { 0, 0, 0, 0, 0 }
    };



        sg::CADIBase::construct(regData, (sizeof(regData) / sizeof( regData[0])) - 1,
                            regDataInstanceSpecific, sizeof(regDataInstanceSpecific) / sizeof( regDataInstanceSpecific[0]),
                            paramData, sizeof(paramData) / sizeof(paramData[0]));

    strcpy( features.targetName, "VisEventRecorder" );
    strcpy( features.targetVersion, "8.1.37" );
    features.fProfilingAvailable = false;
    features.nExtendedTargetFeaturesRegNumValid = true;
    features.nExtendedTargetFeaturesRegNum = 0;
    features.nPCRegNum = eslapi::CADI_INVALID_REGISTER_ID;
}


eslapi::CADIReturn_t
Component__VisEventRecorder_CADI::CADIXfaceBypass(uint32_t commandLength, const char *command, uint32_t maxResponseLength, char *response)
{
    if (!command || (commandLength == 0))
        return eslapi::CADI_STATUS_IllegalArgument;

    const char *param = 0;

    if (IsBypassCommand(commandLength, command, "GetFeatures", &param))
    {
        if ((maxResponseLength > 0) && (response != 0))
        {
            // Feel free to add more features here using the syntax :feature:otherfeature:morefeatures:...:
            strncpy(response,
                    "::MAXVIEWGEN:",
                    maxResponseLength);
            response[maxResponseLength - 1] = 0;
            return eslapi::CADI_STATUS_OK;
        }
        else
            return eslapi::CADI_STATUS_IllegalArgument;
    }
    else
        return CADIBase::CADIXfaceBypass(commandLength, command, maxResponseLength, response);
}


sg::accessfunc::AccessFuncResult
Component__VisEventRecorder_CADI::GetExtendedTargetFeatures(MxU32 /*id*/, std::string &data, bool /*se*/)
{
    data = component->getExtendedTargetFeatures();
    return sg::accessfunc::ACCESS_FUNC_OK;
}

} // FVP_VE_Cortex_A15x1_NMS

