// Copyright 2010 ARM Germany GmbH. All rights reserved.
// 
// high level time and virtual memory profilier for use with the instrumentation__hook() behavior

#ifndef SGInstrumentationHookProfiler_h_
#define SGInstrumentationHookProfiler_h_

#include <string>
#include "SGHighLevelProfiler.h"
#include "SGInstrumentationHookData.h"


class SGInstrumentationHookProfiler
{
public:
    // constructor
    SGInstrumentationHookProfiler(const char *instanceName = "(anon)", int width = 40): 
    compProf(instanceName, width), 
    phaseProf(instanceName, width + 3), 
    totalProf(instanceName, width + 6)
    {
    }
    
    // this is the main function: this is supposed to be called from the behavior instrumentation_hook(...)
    void instrumentation__hook(const SGInstrumentationHookData &data)
    {
        switch (data.type)
        {
        case SGInstrumentationHookData::T_BEFORE_CONSTRUCTION_ALL:
            totalProf.emit("before constructors");
            phaseProf.start();
            compProf.start();
            break;

        case SGInstrumentationHookData::T_AFTER_CONSTRUCTION:
            compProf.emit("constructor", data.name);
            break;                        

        case SGInstrumentationHookData::T_AFTER_CONSTRUCTION_ALL:
            phaseProf.emit("constructors total");
            break;

        case SGInstrumentationHookData::T_BEFORE_INIT_ALL:
            phaseProf.emit("before inits");
            compProf.start();
            break;

        case SGInstrumentationHookData::T_AFTER_INIT:
            compProf.emit("init", data.name);
            break;                        

        case SGInstrumentationHookData::T_AFTER_INIT_ALL:
            phaseProf.emit("inits total");
            break;

        case SGInstrumentationHookData::T_BEFORE_RESET_ALL:
            phaseProf.emit("before resets");
            compProf.start();
            break;

        case SGInstrumentationHookData::T_AFTER_RESET:
            compProf.emit("reset", data.name);
            break;                        

        case SGInstrumentationHookData::T_AFTER_RESET_ALL:
            phaseProf.emit("resets total");
            break;

        case SGInstrumentationHookData::T_BEFORE_TERMINATE_ALL:
            phaseProf.emit("before terminate");
            compProf.start();
            break;

        case SGInstrumentationHookData::T_AFTER_TERMINATE:
            compProf.emit("terminate", data.name);
            break;                        

        case SGInstrumentationHookData::T_AFTER_TERMINATE_ALL:
            phaseProf.emit("terminates total");
            totalProf.emit("overall total");
            break;
            
        default:
            break;
        }
    }
    
private:
    // private data
    SGHighLevelProfiler compProf;
    SGHighLevelProfiler phaseProf;
    SGHighLevelProfiler totalProf;
};

#endif

