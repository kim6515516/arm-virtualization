/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2009 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */
/** \file
 * System components.
 */

#ifndef _NO_CORE_Components_h_
#define _NO_CORE_Components_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <string>
#include <vector>
#include "MaxCoreVersion.h"

// clean way to get the name of the generated class for a component (e.g. for behavior return types for types defined in the resources section)
#define COMPONENT_CLASS_NAME(compName) Component__##compName

// collected defines start
#define MAXCORE_VERSION  "11.1.032"
#define SYSTEM_GENERATOR_VERSION  "8.1.032"
#define GEN_SBOX  1
#define GEN_SYSTEM_PLATFORM  1
#define linux  1
#define SIMGEN_RELEASE  1
#define NDEBUG  1

// collected defines end

#include "CADIProtocol.h"

# define NO_CLASS_IMP
#include <MxIDataStream.h>
#include <MxODataStream.h>
#include <MxTypes.h>
# undef NO_CLASS_IMP

#include "MCPagedMemory.h"
#include "MCNonPagedMemory.h"
#include "sg/SGSimulationContext.h"
#include "sg/SGComponentFactory.h"
class ObjectLoader;

#include "SGComponentWithPorts.h"

#include "FVP_VE_Cortex_A15x1_DSO.h"

// include protocols
#include "FVP_VE_Cortex_A15x1__Builtin__AddressablePortProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"

// legacy: collected includes from components


// collected includes from components


sg::ComponentFactory *ARMCortexA15x1CT_GetFactory();
sg::ComponentFactory *ClockDivider_GetFactory();
sg::ComponentFactory *PVBusMapper_GetFactory();
sg::ComponentFactory *PVBusSlave_GetFactory();
sg::ComponentFactory *PVBusMaster_GetFactory();
sg::ComponentFactory *ClockTimer_GetFactory();
sg::ComponentFactory *PVBusDecoder_GetFactory();
sg::ComponentFactory *MasterClock_GetFactory();
sg::ComponentFactory *SMSC_91C111_GetFactory();
sg::ComponentFactory *TelnetTerminal_GetFactory();
sg::ComponentFactory *VirtioBlockDevice_GetFactory();
sg::ComponentFactory *GUIPoll_GetFactory();


namespace FVP_VE_Cortex_A15x1_NMS {

// declare all components (forward decls)
class Component__FVP_VE_Cortex_A15x1;
class Component__VEDaughterBoard;
class Component__RAMDevice;
class Component__TZSwitch;
class Component__PL370_HDLCD;
class Component__VEInterruptMapper;
class Component__IntelStrataFlashJ3;
class Component__FlashLoader;
class Component__VEDCC;
class Component__VEMotherBoard;
class Component__SP804_Timer;
class Component__CounterModule;
class Component__AudioOut_SDL;
class Component__VE_CompactFlash;
class Component__HostBridge;
class Component__MMC;
class Component__PL011_Uart;
class Component__PL031_RTC;
class Component__PL041_AACI;
class Component__PL050_KMI;
class Component__PL111_CLCD;
class Component__PL11x_CLCD;
class Component__PL180_MCI;
class Component__PS2Keyboard;
class Component__PS2Mouse;
class Component__SP805_Watchdog;
class Component__SP810_SysCtrl;
class Component__VE_SysRegs;
class Component__VFS2;
class Component__MessageBox;
class Component__VirtualEthernetCrossover;
class Component__VEVisualisation;
class Component__VisEventRecorder;


// legacy: component class declarations


// legacy: component class definitions


// component factory prototypes
sg::ComponentFactory *FVP_VE_Cortex_A15x1_GetFactory();
sg::ComponentFactory *VEDaughterBoard_GetFactory();
sg::ComponentFactory *RAMDevice_GetFactory();
sg::ComponentFactory *TZSwitch_GetFactory();
sg::ComponentFactory *PL370_HDLCD_GetFactory();
sg::ComponentFactory *VEInterruptMapper_GetFactory();
sg::ComponentFactory *IntelStrataFlashJ3_GetFactory();
sg::ComponentFactory *FlashLoader_GetFactory();
sg::ComponentFactory *VEDCC_GetFactory();
sg::ComponentFactory *VEMotherBoard_GetFactory();
sg::ComponentFactory *SP804_Timer_GetFactory();
sg::ComponentFactory *CounterModule_GetFactory();
sg::ComponentFactory *AudioOut_SDL_GetFactory();
sg::ComponentFactory *VE_CompactFlash_GetFactory();
sg::ComponentFactory *HostBridge_GetFactory();
sg::ComponentFactory *MMC_GetFactory();
sg::ComponentFactory *PL011_Uart_GetFactory();
sg::ComponentFactory *PL031_RTC_GetFactory();
sg::ComponentFactory *PL041_AACI_GetFactory();
sg::ComponentFactory *PL050_KMI_GetFactory();
sg::ComponentFactory *PL111_CLCD_GetFactory();
sg::ComponentFactory *PL11x_CLCD_GetFactory();
sg::ComponentFactory *PL180_MCI_GetFactory();
sg::ComponentFactory *PS2Keyboard_GetFactory();
sg::ComponentFactory *PS2Mouse_GetFactory();
sg::ComponentFactory *SP805_Watchdog_GetFactory();
sg::ComponentFactory *SP810_SysCtrl_GetFactory();
sg::ComponentFactory *VE_SysRegs_GetFactory();
sg::ComponentFactory *VFS2_GetFactory();
sg::ComponentFactory *MessageBox_GetFactory();
sg::ComponentFactory *VirtualEthernetCrossover_GetFactory();
sg::ComponentFactory *VEVisualisation_GetFactory();
sg::ComponentFactory *VisEventRecorder_GetFactory();


} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

