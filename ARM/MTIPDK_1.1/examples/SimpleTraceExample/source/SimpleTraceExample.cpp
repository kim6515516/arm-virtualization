/*!
 *  \file   SimpleTraceExample.cpp
 *  \brief  Very simple trace example, tracing the PC
 *  \date   Copyright ARM Limited 2009 All Rights Reserved.
 *  
 */

#include "MTI/PluginInterface.h"
#include "MTI/PluginFactory.h"
#include "MTI/PluginInstance.h"
#include "MTI/ModelTraceInterface.h"

#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include <cstdio>

#ifdef SG_MODEL_BUILD
    #include "builddata.h"
    #define PLUGIN_VERSION FULL_VERSION_STRING
#else
    #define PLUGIN_VERSION "unreleased"
#endif

using namespace std;
using namespace eslapi;
using namespace MTI;

/////////////////////////////////////////////////////////////////////////////

class SimpleTraceExample :
    public PluginInstance
{
public:
    virtual CAInterface * ObtainInterface(if_name_t    ifName,
                                          if_rev_t     minRev,
                                          if_rev_t *   actualRev);

    SimpleTraceExample(const char *instance_name,
                       uint32_t num_parameters,
                       CADIParameterValue_t *parameter_values);


    /** This is to associate a plugin with a simulation instance. Exactly one simulation must be registered. */
    virtual CADIReturn_t RegisterSimulation(CAInterface *simulation);

    // This is called before the plugin .dll/.so is unloaded and should allow the plugin to do it's cleanup.
    virtual void Release();

    virtual const char *GetName() const;

public: // methods
    string instance_name;
    ValueIndex inst_pc_index;

    void
    TracePC(const MTI::EventClass *event_class,
            const struct MTI::EventRecord *record);

    static void
    TracePC_Thunk(void * user_data,
                  const MTI::EventClass *event_class,
                  const struct MTI::EventRecord *record);

    CADIReturn_t Error(const char *message) const;
};

CAInterface * 
SimpleTraceExample::ObtainInterface(if_name_t    ifName,
                              if_rev_t     minRev,
                              if_rev_t *   actualRev)
{
    if((strcmp(ifName,PluginInstance::IFNAME()) == 0) && // if someone is asking for the matching interface
       (minRev <= PluginInstance::IFREVISION())) // and the revision of this interface implementation is
        // at least what is being asked for
    {
        if (actualRev) // make sure this is not a NULL pointer
            *actualRev = PluginInstance::IFREVISION();
        return static_cast<PluginInstance *>(this);
    }

    if((strcmp(ifName, CAInterface::IFNAME()) == 0) &&
       minRev <= CAInterface::IFREVISION())
    {
        if (actualRev != NULL)
            *actualRev = CAInterface::IFREVISION();
        return static_cast<PluginInstance *>(this);
    }
    return NULL;
}


SimpleTraceExample::SimpleTraceExample(const char *instance_name_,
                           uint32_t /*number_parameters*/,
                           CADIParameterValue_t * /*parameter_values*/) :
    instance_name(instance_name_),
    inst_pc_index(-1)
{
}

CADIReturn_t
SimpleTraceExample::Error(const char *message) const
{
    fprintf(stderr, "Error: Trace plugin %s: %s\n", instance_name.c_str(), message);
    return CADI_STATUS_GeneralError;
}

CADIReturn_t
SimpleTraceExample::RegisterSimulation(CAInterface *ca_interface)
{
    if (!ca_interface)
        return CADI_STATUS_IllegalArgument;


    // Get the System Trace Interface:
    SystemTraceInterface *sti = ca_interface->ObtainPointer<SystemTraceInterface>();
    if (!sti)
        return CADI_STATUS_IllegalArgument;

    // Check if there is at least one component with trace:
    SystemTraceInterface::TraceComponentIndex num_trace_components = sti->GetNumOfTraceComponents();
    if (num_trace_components == 0)
        return Error("No components provide trace.");


    // For each component get the Trace Component Interface and see if it has an INST source
    for(SystemTraceInterface::TraceComponentIndex tci=0; tci < num_trace_components; ++tci)
    {
        CAInterface *caif = sti->GetComponentTrace(tci);
        ComponentTraceInterface *cti = caif->ObtainPointer<ComponentTraceInterface>();
        if(cti)
        {
            printf("Attached %s to component: %s\n", instance_name.c_str(), sti->GetComponentTracePath(tci));
            
            // Get the trace source named "INST":
            TraceSource *source = cti->GetTraceSource("INST");
            if (source)
            {
                // Now find the field "PC", and create a field mask:
                const EventFieldType *field = source->GetField("PC");
                if (!field)
                    return Error("No field named \"PC\" found in \"INST\" trace source.");
                FieldMask mask = 1 << field->GetIndex();
                
                // Register an event class:
                EventClass *event_class = source->CreateEventClass(mask);
                if (!event_class)
                    return Error("Problem when creating EventClass.");
                inst_pc_index = event_class->GetValueIndex("PC");

                // Now register the callback:
                Status status = event_class->RegisterCallback(TracePC_Thunk, this);
                if (status != MTI_OK)
                    return Error("EventClass::RegisterCallback() returned error.");

                inst_pc_index = event_class->GetValueIndex("PC");
                if (inst_pc_index == -1)
                    return Error("EventClass::GetValueIndex(\"PC\") returned error.");
            }
            else
            {
                printf("Ignoring component %s as it does not contain an INST source\n", sti->GetComponentTracePath(tci));
            }
        }
    }

    return CADI_STATUS_OK;
}

// This is called before the plugin .dll/.so is unloaded and should allow the plugin to do it's cleanup.
void 
SimpleTraceExample::Release()
{
    delete this;
}

const char *
SimpleTraceExample::GetName() const
{
    return instance_name.c_str();
}

/////////////////////////////////////////////////////////////////////////////

void SimpleTraceExample::TracePC(const MTI::EventClass *event_class,
                                 const struct MTI::EventRecord *record)
{
    uint32_t pc = record->Get<uint32_t>(event_class, inst_pc_index);
    printf("PC: 0x%08x\n", pc);
}

// The callback interface is a C interface, so we need a short thunk
// function to call into a C++ method. This is done via a static C++
// method, which behaves like a C function:
void
SimpleTraceExample::TracePC_Thunk(void * user_data,
                                  const MTI::EventClass *event_class,
                                  const struct MTI::EventRecord *record)
{
    SimpleTraceExample *simple_trace = reinterpret_cast<SimpleTraceExample *>(user_data);
    simple_trace->TracePC(event_class, record);
}

/////////////////////////////////////////////////////////////////////////////

class ThePluginFactory :
    public PluginFactory
{
public:
    virtual CAInterface * ObtainInterface(if_name_t    ifName,
                                          if_rev_t     minRev,
                                          if_rev_t *   actualRev);

    virtual uint32_t GetNumberOfParameters();

    virtual CADIReturn_t GetParameterInfos(CADIParameterInfo_t *parameter_info_list);

    virtual CAInterface *Instantiate(const char *instance_name,
                                     uint32_t number_of_parameters,
                                     CADIParameterValue_t *parameter_values);

    virtual void Release();

    virtual const char *GetType() const { return "SimpleTraceExample"; }
    virtual const char *GetVersion() const { return PLUGIN_VERSION; }
};

CAInterface *
ThePluginFactory::ObtainInterface(if_name_t    ifName,
                                  if_rev_t     minRev,
                                  if_rev_t *   actualRev)
{
    if((strcmp(ifName,IFNAME()) == 0) && // if someone is asking for the matching interface
       (minRev <= IFREVISION())) // and the revision of this interface implementation is
        // at least what is being asked for
    {
        if (actualRev) // make sure this is not a NULL pointer
            *actualRev = IFREVISION();
        return static_cast<ThePluginFactory *>(this);
    }

    if((strcmp(ifName, CAInterface::IFNAME()) == 0) &&
       minRev <= CAInterface::IFREVISION())
    {
        if (actualRev) // make sure this is not a NULL pointer
            *actualRev = CAInterface::IFREVISION();
        return static_cast<CAInterface *>(this);
    }
    return NULL;
}

uint32_t
ThePluginFactory::GetNumberOfParameters()
{
    return 0;
}


CADIReturn_t
ThePluginFactory::GetParameterInfos(CADIParameterInfo_t* /*parameter_info_list*/)
{
    return CADI_STATUS_CmdNotSupported;
}


CAInterface *
ThePluginFactory::Instantiate(const char *instance_name,
                              uint32_t    number_of_parameters,
                              CADIParameterValue_t *param_values)
{
    return static_cast<PluginInstance *>(new SimpleTraceExample(instance_name, number_of_parameters, param_values));
}

void
ThePluginFactory::Release()
{
    // nothing to do since factory is a static instance
}

ThePluginFactory factory_instance;

CAInterface *
GetCAInterface()
{
    return &factory_instance;
}

// End of file SimpleTraceExample.cpp
