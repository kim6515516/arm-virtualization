/*!
 *  \file   LinuxSyscallTrace.cpp
 *  \brief  Trace Plugin to trace any trace sources
 *  \date   Copyright ARM Limited 2009-2010 All Rights Reserved.
 *  
 */

#include "MTI/PluginInterface.h"
#include "MTI/PluginFactory.h"
#include "MTI/PluginInstance.h"
#include "MTI/ModelTraceInterface.h"
#include "MTI/ParameterInterface.h"

#include <map>
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

class LinuxSyscallTrace :
    public PluginInstance,
    public ParameterInterface
{
public:
    virtual CAInterface * ObtainInterface(if_name_t    ifName,
                                          if_rev_t     minRev,
                                          if_rev_t *   actualRev);

    LinuxSyscallTrace(const char *instance_name,
                 uint32_t num_parameters,
                 CADIParameterValue_t *parameter_values);
    ~LinuxSyscallTrace();


    /** This is to associate a plugin with a simulation instance. Exactly one simulation must be registered. */
    virtual CADIReturn_t RegisterSimulation(CAInterface *simulation);

    // This is called before the plugin .dll/.so is unloaded and should allow the plugin to do it's cleanup.
    virtual void Release();

    virtual const char *GetName() const;

    virtual CADIReturn_t GetParameterInfos(uint32_t startIndex,
                                           uint32_t desiredNumOfParams,
                                           uint32_t *actualNumOfParams,
                                           CADIParameterInfo_t *params);

    virtual CADIReturn_t GetParameterInfo(const char *parameterName,
                                          CADIParameterInfo_t *param);

    virtual CADIReturn_t GetParameterValues(uint32_t parameterCount,
                                            uint32_t *actualNumOfParamsRead,
                                            CADIParameterValue_t *paramValuesOut);
    
    virtual CADIReturn_t SetParameterValues(uint32_t parameterCount,
                                            CADIParameterValue_t *parameters,
                                            CADIFactoryErrorMessage_t *error);

public: // methods
    
    // EXCEPTION tracing
    void ExceptionCallback(const MTI::EventClass *event_class,
                           const struct MTI::EventRecord *record);
    static void
    ExceptionThunk(void * user_data,
                   const MTI::EventClass *event_class,
                   const struct MTI::EventRecord *record);

    CADIReturn_t traceEXCEPTION(ComponentTraceInterface* cti);

    // EXCEPTION_RETURN tracing
    void ExceptionReturnCallback(const MTI::EventClass *event_class,
                                 const struct MTI::EventRecord *record);
    static void
    ExceptionReturnThunk(void * user_data,
                         const MTI::EventClass *event_class,
                         const struct MTI::EventRecord *record);

    CADIReturn_t traceEXCEPTION_RETURN(ComponentTraceInterface* cti);

    // CORE_REGS tracing
    void CoreRegsCallback(const MTI::EventClass *event_class,
                         const struct MTI::EventRecord *record);
    static void
    CoreRegsThunk(void * user_data,
                 const MTI::EventClass *event_class,
                 const struct MTI::EventRecord *record);

    CADIReturn_t traceCORE_REGS(ComponentTraceInterface* cti);

    // CONTEXTIDR tracing
    void CONTEXTIDR_Callback(const MTI::EventClass *event_class,
                             const struct MTI::EventRecord *record);
    static void
    CONTEXTIDR_Thunk(void * user_data,
                     const MTI::EventClass *event_class,
                     const struct MTI::EventRecord *record);

    CADIReturn_t traceCONTEXTIDR(ComponentTraceInterface* cti);

private:
    void CloseTraceFile();

    void SetTraceFile(const char *new_filename);

    CADIReturn_t SetParametersInternal(uint32_t num_parameters,
                                       CADIParameterValue_t *parameters);

    CADIReturn_t Error(const char *message) const;

private:
    SystemTraceInterface *sti;

    string instance_name;
    string trace_file_name;
    bool enabled;
    bool flush;
    bool verbose;

    FILE *trace_file;

    uint32_t current_pid;

    ValueIndex exception_vector_idx;
    uint8_t vector_swi_id;

    bool syscall_pending;

    ValueIndex contextidr_value_idx;

    EventClass *core_regs_event_class;
    const EventFieldType *core_regs_phys_id_eft;
    ValueIndex core_regs_phys_id_idx;
    ValueIndex core_regs_value_idx;
    uint32_t core_regs[8];

    map<unsigned int, string> syscalls;

    void InitSyscalls();
};

CAInterface * 
LinuxSyscallTrace::ObtainInterface(if_name_t    ifName,
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

    if((strcmp(ifName, ParameterInterface::IFNAME()) == 0) && // if someone is asking for the matching interface
       (minRev <= ParameterInterface::IFREVISION())) // and the revision of this interface implementation is
        // at least what is being asked for
    {
        if (actualRev) // make sure this is not a NULL pointer
            *actualRev = ParameterInterface::IFREVISION();
        return static_cast<ParameterInterface *>(this);
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


LinuxSyscallTrace::LinuxSyscallTrace(const char *instance_name_,
                                     uint32_t number_parameters,
                                     CADIParameterValue_t *parameter_values) :
    sti(0),
    instance_name(instance_name_),
    enabled(true),
    flush(false),
    verbose(false),
    trace_file(0),
    current_pid(0),
    exception_vector_idx(-1),
    vector_swi_id(0xFF),
    syscall_pending(false),
    core_regs_event_class(0),
    core_regs_phys_id_eft(0),
    core_regs_phys_id_idx(-1),
    core_regs_value_idx(-1)
{
    if (number_parameters > 0)
    {
        SetParametersInternal(number_parameters, parameter_values);
    }
    memset(core_regs, 0, sizeof(core_regs));
}

LinuxSyscallTrace::~LinuxSyscallTrace()
{
    CloseTraceFile();
}

void
LinuxSyscallTrace::CloseTraceFile()
{
    if (trace_file)
    {
        if (trace_file == stdout)
            fflush(stdout);
        else
            fclose(trace_file);
        trace_file = 0;
    }
}

void LinuxSyscallTrace::SetTraceFile(const char *new_filename)
{
    CloseTraceFile();
    trace_file_name = new_filename;
    if (trace_file_name.empty())
    {
        trace_file = stdout;
    }
    else
    {
        trace_file = fopen(trace_file_name.c_str(), "w");
    }
}

CADIReturn_t
LinuxSyscallTrace::RegisterSimulation(CAInterface *ca_interface)
{
    if (!ca_interface)
        return CADI_STATUS_IllegalArgument;

    ca_interface = ca_interface->ObtainInterface(SystemTraceInterface::IFNAME(),
                                                 SystemTraceInterface::IFREVISION(), 0);
    if (!ca_interface)
        return CADI_STATUS_IllegalArgument;

    sti = static_cast<SystemTraceInterface *>(ca_interface);

    SystemTraceInterface::TraceComponentIndex num_trace_components = sti->GetNumOfTraceComponents();
    if (num_trace_components == 0)
        return Error("No components provide trace.");

    // For each component get the Trace Component Interface and see if it has an INST source
    for(SystemTraceInterface::TraceComponentIndex tci=0; tci < sti->GetNumOfTraceComponents(); ++tci)
    {
        ca_interface = sti->GetComponentTrace(tci);
        ca_interface = ca_interface->ObtainInterface(ComponentTraceInterface::IFNAME(),
                                                     ComponentTraceInterface::IFREVISION(), 0);
        if (ca_interface)
        {
            ComponentTraceInterface *cti = static_cast<ComponentTraceInterface*>(ca_interface);

            TraceSource *source = cti->GetTraceSource("INST");
            if (source)
            {
                // Component has an INST source, therfore assume it is a core
                printf("Attached %s to component: %s\n",
                        instance_name.c_str(), sti->GetComponentTracePath(0));

                CADIReturn_t  status;

                status = traceEXCEPTION(cti);
                if (status != CADI_STATUS_OK)  return status;

                status = traceEXCEPTION_RETURN(cti);
                if (status != CADI_STATUS_OK)  return status;

                status = traceCORE_REGS(cti);
                if (status != CADI_STATUS_OK)  return status;

                status = traceCONTEXTIDR(cti);
                if (status != CADI_STATUS_OK)  return status;

                // Only trace the first core found !!
                break;
            }
        }
    }

    InitSyscalls();

    return CADI_STATUS_OK;
}

void
LinuxSyscallTrace::InitSyscalls()
{
    struct syscall_pair
    {
        const char *name;
        unsigned int id;
    };

    const static syscall_pair data[] = {
#include "LinuxSyscallIDs.h"
    };

    for(unsigned int i=0; i < (sizeof(data) / sizeof(data[0])); ++i)
    {
        syscalls[data[i].id] = data[i].name;
    }
}

// This is called before the plugin .dll/.so is unloaded and should allow the plugin to do it's cleanup.
void 
LinuxSyscallTrace::Release()
{
    delete this;
}

const char *
LinuxSyscallTrace::GetName() const
{
    return instance_name.c_str();
}

const unsigned int num_parameters = 5;

typedef enum
{
    PARAM_ID_TRACE_FILE,
    PARAM_ID_ENABLED,
    PARAM_ID_FLUSH,
    PARAM_ID_VERBOSE
} MyParameterIDs;

static CADIParameterInfo_t parameters[num_parameters] = 
{
    CADIParameterInfo_t(PARAM_ID_TRACE_FILE,
                        "trace-file",
                        CADI_PARAM_STRING,
                        "The trace file to write into. If empty will print to console / STDOUT.",
                        true, // runtime
                        0, 0, 0,
                        ""), // default: STDOUT
    
    CADIParameterInfo_t(PARAM_ID_ENABLED,
                        "enabled",
                        CADI_PARAM_BOOL,
                        "If set to true then tracing is enabled.",
                        true, // runtime
                        0, 1, 1,
                        0),

    CADIParameterInfo_t(PARAM_ID_FLUSH,
                        "flush",
                        CADI_PARAM_BOOL,
                        "If set to true then the trace file will be flushed after every event. This will have an performance impact but could be used to better debug crashes.",
                        true, // runtime
                        0, 1, 0,
                        0),

    CADIParameterInfo_t(PARAM_ID_VERBOSE,
                        "verbose",
                        CADI_PARAM_BOOL,
                        "Print some debugging information.",
                        true, // runtime
                        0, 1, 0,
                        0)
};

CADIReturn_t
LinuxSyscallTrace::GetParameterInfos(uint32_t startIndex,
                                     uint32_t desiredNumOfParams,
                                     uint32_t *actualNumOfParams,
                                     CADIParameterInfo_t *params)
{
    if (!actualNumOfParams || !params)
        return CADI_STATUS_IllegalArgument;

    uint32_t i = 0;
    for(; i < desiredNumOfParams; ++i)
    {
        if (startIndex + i >= num_parameters)
            break;
        params[i] = parameters[startIndex + i];
    }
    *actualNumOfParams = i;

    return CADI_STATUS_OK;
}

CADIReturn_t
LinuxSyscallTrace::GetParameterInfo(const char *parameterName,
                                  CADIParameterInfo_t *param)
{
    if (!param)
        return CADI_STATUS_IllegalArgument;

    for(uint32_t i=0; i < num_parameters; ++i)
    {
        if (strcmp(parameters[i].name, parameterName) == 0)
        {
            *param = parameters[i];
            return CADI_STATUS_OK;
        }
    }

    return CADI_STATUS_ArgNotSupported; // not found
}

CADIReturn_t
LinuxSyscallTrace::GetParameterValues(uint32_t parameterCount,
                                 uint32_t *actualNumOfParamsRead,
                                 CADIParameterValue_t *paramValuesOut)
{
    if (!paramValuesOut)
        return CADI_STATUS_IllegalArgument;

    for(uint32_t i = 0; i < parameterCount; ++i)
    {
        CADIParameterValue_t &param_value = paramValuesOut[i];
        switch(param_value.parameterID)
        {
        case PARAM_ID_TRACE_FILE:
            AssignString(param_value.stringValue, trace_file_name.c_str(), sizeof(param_value.stringValue));
            break;

        case PARAM_ID_ENABLED:
            param_value.intValue = enabled;
            break;

        case PARAM_ID_FLUSH:
            param_value.intValue = flush;
            break;

        case PARAM_ID_VERBOSE:
            param_value.intValue = verbose;
            break;
            
        default: // unknown ID
            if (actualNumOfParamsRead)
                *actualNumOfParamsRead = i;
            return CADI_STATUS_IllegalArgument;
        }
    }

    if (actualNumOfParamsRead)
        *actualNumOfParamsRead = parameterCount;

    return CADI_STATUS_OK;
}
    
CADIReturn_t
LinuxSyscallTrace::SetParameterValues(uint32_t parameterCount,
                                 CADIParameterValue_t *parameter_values,
                                 CADIFactoryErrorMessage_t * /*error*/)
{
    if (!parameter_values)
        return CADI_STATUS_IllegalArgument;

    return SetParametersInternal(parameterCount, parameter_values);
}

CADIReturn_t
LinuxSyscallTrace::SetParametersInternal(uint32_t parameterCount, CADIParameterValue_t *parameter_values)
{
    for(uint32_t i = 0; i < parameterCount; ++i)
    {
        CADIParameterValue_t &parameter = parameter_values[i];
        
        switch(parameter.parameterID)
        {
        case PARAM_ID_TRACE_FILE:
            SetTraceFile(parameter.stringValue);
            break;

        case PARAM_ID_ENABLED:
            enabled = (parameter.intValue != 0);
            break;

        case PARAM_ID_FLUSH:
            flush = (parameter.intValue != 0);
            break;

        case PARAM_ID_VERBOSE:
            verbose = (parameter.intValue != 0);
            break;
        }
    }

    return CADI_STATUS_OK;
}

CADIReturn_t
LinuxSyscallTrace::Error(const char *message) const
{
    fprintf(stderr, "Error: Trace plugin %s: %s\n", instance_name.c_str(), message);
    return CADI_STATUS_GeneralError;
}


/////////////////////////////////////////////////////////////////////////////
// EXCEPTION trace

void LinuxSyscallTrace::ExceptionCallback(const MTI::EventClass *event_class,
                                          const struct MTI::EventRecord *record)
{
    uint8_t vector = record->Get<uint8_t>(event_class, exception_vector_idx);
    // Only if this exception is a SWI:
    if (vector == vector_swi_id)
    {
        // Populate core_regs with with current register state.
        Status status = core_regs_event_class->DumpState(CoreRegsThunk, this);
        assert(status == MTI_OK); (void)status;

        uint8_t syscall_id = core_regs[7];
        printf("%u: %s()", current_pid, syscalls[syscall_id].c_str());
        syscall_pending = true;
    }
    else
    {
        if (syscall_pending)
            printf("Exception interrupts syscall.\n");
    }
}

// The callback interface is a C interface, so we need a short thunk
// function to call into a C++ method. This is done via a static C++
// method, which behaves like a C function:
void
LinuxSyscallTrace::ExceptionThunk(void * user_data,
                                  const MTI::EventClass *event_class,
                                  const struct MTI::EventRecord *record)
{
    LinuxSyscallTrace *that = reinterpret_cast<LinuxSyscallTrace *>(user_data);
    that->ExceptionCallback(event_class, record);
}


CADIReturn_t LinuxSyscallTrace::traceEXCEPTION(ComponentTraceInterface* cti)
{
    TraceSource *source = cti->GetTraceSource("EXCEPTION");
    if (!source)
        return Error("No trace source \"EXCEPTION\" found.");

    // Now find the field "VECTOR", and create a field mask:
    const EventFieldType *field = source->GetField("VECTOR");
    if (!field)
        return Error("No field named \"VECTOR\" found in \"EXCEPTION\" trace source.");
    if (field->GetType() != EventFieldType::MTI_ENUM)
        return Error("Expecting EXCEPTION:VECTOR to be of type enum.");
    FieldMask mask = 1 << field->GetIndex();

    
    // Register an event class:
    EventClass *event_class = source->CreateEventClass(mask);
    if (!event_class)
        return Error("Problem when creating EventClass for EXCEPTION trace source.");

    exception_vector_idx = event_class->GetValueIndex("VECTOR");
    if (exception_vector_idx == -1)
        return Error("Invalid ValueIndex for EXCEPTION:VECTOR.");

    EventFieldType::EnumIndex i;
    for(i = 0; i < field->GetNumOfEnumConstants(); ++i)
    {
        EventFieldType::EnumConstant one_constant = field->GetEnumConstant(i);
        if (strcmp(one_constant.second, "SWI") == 0)
        {
            vector_swi_id = one_constant.first;
            break;
        }
    }
    if (i == field->GetNumOfEnumConstants())
        return Error("No SWI enum found for EXCEPTION:VECTOR field.");

    // Now register the callback:
    Status status = event_class->RegisterCallback(ExceptionThunk, this);
    if (status != MTI_OK)
        return Error("EventClass::RegisterCallback() returned error.");

    return CADI_STATUS_OK;
}


/////////////////////////////////////////////////////////////////////////////
// EXCEPTION_RETURN trace

void LinuxSyscallTrace::ExceptionReturnCallback(const MTI::EventClass * /*event_class*/,
                                                const struct MTI::EventRecord * /*record*/)
{
    if (syscall_pending)
    {
        // Populate core_regs with with current register state.
        Status status = core_regs_event_class->DumpState(CoreRegsThunk, this);
        assert(status == MTI_OK); (void)status;
        
        printf(" = %d\n", core_regs[0]);
        syscall_pending = false;
    }
}

// The callback interface is a C interface, so we need a short thunk
// function to call into a C++ method. This is done via a static C++
// method, which behaves like a C function:
void
LinuxSyscallTrace::ExceptionReturnThunk(void * user_data,
                                        const MTI::EventClass *event_class,
                                        const struct MTI::EventRecord *record)
{
    LinuxSyscallTrace *that = reinterpret_cast<LinuxSyscallTrace *>(user_data);
    that->ExceptionReturnCallback(event_class, record);
}


CADIReturn_t LinuxSyscallTrace::traceEXCEPTION_RETURN(ComponentTraceInterface* cti)
{   
    TraceSource *source = cti->GetTraceSource("EXCEPTION_RETURN");
    if (!source)
        return Error("No trace source \"EXCEPTION_RETURN\" found.");

    // Register an event class:
    EventClass *event_class = source->CreateEventClass(0);
    if (!event_class)
        return Error("Problem when creating EventClass for EXCEPTION_RETURN trace source.");

    // Now register the callback:
    Status status = event_class->RegisterCallback(ExceptionReturnThunk, this);
    if (status != MTI_OK)
        return Error("EventClass::RegisterCallback() returned error.");

    return CADI_STATUS_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CORE_REGS trace

void LinuxSyscallTrace::CoreRegsCallback(const MTI::EventClass *event_class,
                                        const struct MTI::EventRecord *record)
{
    uint8_t phys_id = record->Get<uint8_t>(event_class, core_regs_phys_id_idx);
    if (phys_id < 8)
    {
        uint32_t value = record->Get<uint32_t>(event_class, core_regs_value_idx);
        core_regs[phys_id] = value;
#if 0
        const char *register_name =
            core_regs_phys_id_eft->LookupEnum(phys_id);
        printf("CoreReg: %s=%08x\n", register_name, value);
#endif
    }
}

// The callback interface is a C interface, so we need a short thunk
// function to call into a C++ method. This is done via a static C++
// method, which behaves like a C function:
void
LinuxSyscallTrace::CoreRegsThunk(void * user_data,
                                const MTI::EventClass *event_class,
                                const struct MTI::EventRecord *record)
{
    LinuxSyscallTrace *that = reinterpret_cast<LinuxSyscallTrace *>(user_data);
    that->CoreRegsCallback(event_class, record);
}


CADIReturn_t LinuxSyscallTrace::traceCORE_REGS(ComponentTraceInterface* cti)
{
    // Find register trace source:
    TraceSource *source = cti->GetTraceSource("CORE_REGS");
    if (!source)
        return Error("No trace source \"CORE_REGS\" found.");

    const EventFieldType *field = source->GetField("PHYS_ID");
    if (!field)
        return Error("No field named \"PHYS_ID\" found in \"CORE_REGS\" trace source.");
    core_regs_phys_id_eft = field;
    FieldMask mask = 1 << field->GetIndex();
    
    field = source->GetField("VALUE");
    if (!field)
        return Error("No field named \"VALUE\" found in \"CORE_REGS\" trace source.");
    mask |= 1 << field->GetIndex();

    core_regs_event_class = source->CreateEventClass(mask);
    if (!core_regs_event_class)
        return Error("Problem when creating EventClass for CORE_REGS trace source.");

    core_regs_phys_id_idx = core_regs_event_class->GetValueIndex("PHYS_ID");
    if (core_regs_phys_id_idx == -1)
        return Error("Invalid ValueIndex for CORE_REGS:PHYS_ID.");

    core_regs_value_idx = core_regs_event_class->GetValueIndex("VALUE");
    if (core_regs_value_idx == -1)
        return Error("Invalid ValueIndex for CORE_REGS:VALUE.");

    return CADI_STATUS_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CONTEXTIDR trace

void LinuxSyscallTrace::CONTEXTIDR_Callback(const MTI::EventClass *event_class,
                                            const struct MTI::EventRecord *record)
{
    uint32_t value = record->Get<uint32_t>(event_class, contextidr_value_idx);
    if ((value == 0) && syscall_pending)
        printf("\n");
    printf(">>> Switching to process 0x%x\n", value);
    current_pid = value;
}

// The callback interface is a C interface, so we need a short thunk
// function to call into a C++ method. This is done via a static C++
// method, which behaves like a C function:
void
LinuxSyscallTrace::CONTEXTIDR_Thunk(void * user_data,
                                    const MTI::EventClass *event_class,
                                    const struct MTI::EventRecord *record)
{
    LinuxSyscallTrace *that = reinterpret_cast<LinuxSyscallTrace *>(user_data);
    that->CONTEXTIDR_Callback(event_class, record);
}

CADIReturn_t LinuxSyscallTrace::traceCONTEXTIDR(ComponentTraceInterface* cti)
{
    // Find CONTEXTIDR trace source:
    TraceSource *source = cti->GetTraceSource("CONTEXTIDR");
    if (!source)
        return Error("No trace source \"CONTEXTIDR\" found.");

    const EventFieldType *field = source->GetField("VALUE");
    if (!field)
        return Error("No field named \"VALUE\" found in \"CONTEXTIDR\" trace source.");
    FieldMask mask = 1 << field->GetIndex();

    EventClass *event_class = source->CreateEventClass(mask);
    if (!event_class)
        return Error("Problem when creating EventClass for CONTEXTIDR trace source.");

    contextidr_value_idx = event_class->GetValueIndex("VALUE");
    if (contextidr_value_idx == -1)
        return Error("Invalid ValueIndex for CONTEXTIDR:VALUE.");

    // Now register the callback:
    Status status = event_class->RegisterCallback(CONTEXTIDR_Thunk, this);
    if (status != MTI_OK)
        return Error("EventClass::RegisterCallback() returned error.");

    return CADI_STATUS_OK;
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

    virtual const char *GetType() const { return "LinuxSyscallTrace"; }
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
    return num_parameters;
}


CADIReturn_t
ThePluginFactory::GetParameterInfos(CADIParameterInfo_t *parameter_info_list)
{
    if (!parameter_info_list)
        return CADI_STATUS_IllegalArgument;
    
    std::copy( parameters, &parameters[num_parameters], parameter_info_list);
    return CADI_STATUS_OK;
}


CAInterface *
ThePluginFactory::Instantiate(const char *instance_name,
                              uint32_t    number_of_parameters,
                              CADIParameterValue_t *param_values)
{
    return static_cast<PluginInstance *>(new LinuxSyscallTrace(instance_name, number_of_parameters, param_values));
}

void
ThePluginFactory::Release()
{
}

ThePluginFactory factory_instance;

CAInterface *
GetCAInterface()
{
    return &factory_instance;
}

// End of file LinuxSyscallTrace.cpp
