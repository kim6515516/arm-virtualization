/*!
 *  \file   GenericTrace.cpp
 *  \brief  Trace Plugin to trace any trace sources
 *  \date   Copyright ARM Limited 2009 All Rights Reserved.
 *
 */

#include "sg/IncludeMeFirst.h"
#include "hostconf/zinttypes.h"

#include "sg/MSCFixes.h"
#include "sg/SystemInclude.h"

#include "MTI/PluginInterface.h"
#include "MTI/PluginFactory.h"
#include "MTI/PluginInstance.h"
#include "MTI/ModelTraceInterface.h"
#include "MTI/ParameterInterface.h"
#include "eslapi/CADI.h"
#include "eslapi/CADITypes.h"
#include "GetTopLevelCADIFromSystemTraceInterface.h"

#include "FormattedBuffer.h"
#include "PatternBuffer.h"

#include "MTI_ext.h"

#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
#include <map>

#ifndef WIN32
#  include <sys/time.h>
#endif

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

class GenericTrace;

// This is instantiated for every source registered:
class SourceInfo
{
public:
    SourceInfo(GenericTrace *owner_) :
        owner(owner_),
        trace_source(0),
        event_class(0)
    {}

public:
    GenericTrace *owner;

    bool operator == (const SourceInfo &b) const;

    string component_path;
    string print_path; // either the full or shortened path
    string source_name;
    FieldMask field_mask;
    TraceSource *trace_source;
    EventClass *event_class;
};

bool
SourceInfo::operator == (const SourceInfo &b) const
{
    return (component_path == b.component_path)
        && (source_name == b.source_name)
        && (field_mask == b.field_mask);
}

/////////////////////////////////////////////////////////////////////////////

class GenericTrace :
    public PluginInstance,
    public ParameterInterface,
    public CADICallbackObj
{
public:
    virtual CAInterface * ObtainInterface(if_name_t    ifName,
                                          if_rev_t     minRev,
                                          if_rev_t *   actualRev);

    GenericTrace(const char *instance_name,
                 uint32_t num_parameters,
                 CADIParameterValue_t *parameter_values);
    ~GenericTrace();


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

    void TraceCallback(const SourceInfo* source_info,
                       const MTI::EventClass *event_class,
                       const struct MTI::EventRecord *record);

    static void
    TraceCallbackThunk(void * user_data,
                       const MTI::EventClass *event_class,
                       const struct MTI::EventRecord *record);

    void PeriodicCallback(const EventClass *event_class,
                          const struct EventRecord *record);

    static void PeriodicCallbackThunk(void * user_data,
                                      const EventClass *event_class,
                                      const struct EventRecord *record);
private:
    void CloseTraceFile();

    void SetTraceFile(const char *new_filename);

    list<SourceInfo> ParseSourceList(string sources);
    bool InitCADI();
    void RegisterPERIODICCallback();

    CADIReturn_t SetParametersInternal(uint32_t num_parameters,
                                       CADIParameterValue_t *parameters);

    void UpdateTraceSourceRegistration();
    double GetTimeSec() const;

public:
    // CADICallbackObj implementation (we just register modeChange())
    virtual uint32_t appliOpen(const char * /* sFileName */, const char * /* mode */) { return 0; }
    virtual void appliInput(uint32_t /* streamId */,
                            uint32_t /* count */,
                            uint32_t * /* actualCount */,
                            char * /* buffer */ ) {}
    virtual void appliOutput(uint32_t /* streamId */,
                             uint32_t /* count */,
                             uint32_t * /* actualCount */,
                             const char * /* buffer */) {}
    virtual uint32_t appliClose(uint32_t /* streamID */) { return 0; }
    virtual void doString(const char * /* stringArg */) {}
    virtual void modeChange(uint32_t /* newMode */, CADIBptNumber_t /* bptNumber */);
    virtual void reset(uint32_t /* resetLevel */) {}
    virtual void cycleTick(void) {}
    virtual void killInterface(void) {}
    virtual uint32_t bypass(uint32_t /* commandLength */,
                            const char * /* command */,
                            uint32_t /* maxResponseLength */,
                            char * /* response */) { return 0; }
    virtual uint32_t lookupSymbol(uint32_t /* symbolLength */,
                                  const char * /* symbol */,
                                  uint32_t /* maxResponseLength */,
                                  char * /* response */) { return 0; }
    virtual void refresh(uint32_t /* refreshReason */) {}


private:
    SystemTraceInterface *sti;

    string instance_name;

    // CADI parameter values
    string trace_sources;
    string trace_file_name;
    bool enabled;
    bool flush;
    bool shorten_paths;
    bool verbose;
    bool print_timestamp;
    bool hide_fieldnames;
    uint64_t start_icount;
    uint64_t stop_icount;

    // start-stop state machine (SM)
    uint64_t sm_next_icount;
    enum
    {
        SM_BEFORE_START,
        SM_BETWEEN_START_STOP,
        SM_AFTER_STOP
    } sm_state;
    bool updateTraceSourceRegistrationInCADICallback;

    FILE *trace_file;
    FormattedBuffer *buffer;

    const PatternBuffer& pattern(const SourceInfo* source_info, const MTI::EventClass *event_class);
    std::map<const MTI::EventClass*, PatternBuffer*> m_patterns;
    std::map<const MTI::EventClass*, PatternBuffer*>::const_iterator m_patterns_end;

    list<SourceInfo> registered_sources;
    MTI::ValueIndex periodic_inst_count_idx;
    MTI::ValueIndex periodic_pc_idx;
    eslapi::CADI *top_level_cadi;

    // performance measurement stuff
#ifdef WIN32
    double performance_counter_freq; // only used on Windows (GetTimeSec())
#endif
    double perf_last_time;                // updated for every data record
    uint64_t perf_period;
    uint64_t perf_last_icount;
    uint64_t perf_next_icount;
public:
    static const int64_t MAX_ICOUNT = int64_t((uint64_t(1)<<63) - 1);
    static const int64_t MAX_QUANTUM = 2048; // maximum quantum size: start tracing earlier
};

// Helper functions for TraceCallback
namespace {

void init(PatternBuffer& b, const SourceInfo* source_info, const MTI::EventClass *event_class, bool hide_fieldnames) {
    const TraceSource *source = event_class->GetSource();
    b.addString(source_info->print_path).addString(source->GetName()).addChar(':');
    for (ValueIndex i = 0; i < event_class->GetNumValues(); ++i) {
        const EventFieldType *field = event_class->GetEventField(i);
        b.addChar(' ');
        if (!hide_fieldnames) {
            b.addString(field->GetName()).addChar('=');
        }
        size_t offset = event_class->GetValueOffset(i);
        b.addField(offset, field);
    }
    b.addChar('\n');
    b.finalize();
}

}  // namespace

const PatternBuffer& GenericTrace::pattern(const SourceInfo* source_info, const MTI::EventClass *event_class) {
    // TODO: if we know there is only one event_class, simplify...
    // TODO: use a hash table?
    std::map<const MTI::EventClass*, PatternBuffer*>::const_iterator it = m_patterns.find(event_class);
    if (it != m_patterns_end)
        return *it->second;
    PatternBuffer *b = new PatternBuffer;
    m_patterns.insert(std::make_pair(event_class, b));
    m_patterns_end = m_patterns.end();
    init(*b, source_info, event_class, hide_fieldnames);
    return *b;
}

CAInterface *
GenericTrace::ObtainInterface(if_name_t    ifName,
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


GenericTrace::GenericTrace(const char *instance_name_,
                           uint32_t number_parameters,
                           CADIParameterValue_t *parameter_values) :
    sti(0),
    instance_name(instance_name_),
    // initialize CADI parameters to their defaults (edit also parameters[] when changing the defaults)
    trace_sources("INST"),
    trace_file_name(""), // "" == stdout
    enabled(true),
    flush(false),
    shorten_paths(true),
    verbose(false),
    print_timestamp(false),
    hide_fieldnames(false),
    start_icount(0),
    stop_icount(MAX_ICOUNT),
    sm_next_icount(MAX_ICOUNT),
    sm_state(SM_BEFORE_START),
    updateTraceSourceRegistrationInCADICallback(false),
    trace_file(0),
    buffer(new FormattedBuffer(300)),
    periodic_inst_count_idx(0),
    periodic_pc_idx(0),
    top_level_cadi(0),
#ifdef WIN32
    performance_counter_freq(0.0),
#endif
    perf_last_time(0.0),
    perf_period(0),
    perf_last_icount(0),
    perf_next_icount(0)
{
    m_patterns_end = m_patterns.end();
    trace_file = stdout;
    if (number_parameters > 0)
    {
        SetParametersInternal(number_parameters, parameter_values);
    }
#ifdef WIN32
    LARGE_INTEGER li_freq;
    li_freq.QuadPart = 0;
    QueryPerformanceFrequency(&li_freq);
    performance_counter_freq = double(li_freq.QuadPart);
#endif
}

GenericTrace::~GenericTrace()
{
    CloseTraceFile();
}

void
GenericTrace::CloseTraceFile()
{
    if (trace_file)
    {
        if (trace_file == stdout)
            fflush(stdout);
        else if (trace_file == stderr)
            fflush(stderr);
        else
            fclose(trace_file);
        trace_file = 0;
    }
}

void GenericTrace::SetTraceFile(const char *new_filename)
{
    CloseTraceFile();
    trace_file_name = new_filename;
    if (trace_file_name.empty())
    {
        trace_file = stdout;
    }
    else if (trace_file_name == "STDERR")
    {
        trace_file = stderr;
    }
    else
    {
        trace_file = fopen(trace_file_name.c_str(), "w");
    }
}

// CADI mode change callback
// called whenever the simulator starts/stops
void GenericTrace::modeChange(uint32_t newMode, CADIBptNumber_t /* bptNumber */)
{
    switch (newMode)
    {
    case CADI_EXECMODE_Stop:
        if (updateTraceSourceRegistrationInCADICallback)
        {
            UpdateTraceSourceRegistration();
            updateTraceSourceRegistrationInCADICallback = false;
        }
        break;
    }
}

bool GenericTrace::InitCADI()
{
    // get CADI interface of top level component
    top_level_cadi = GetTopLevelCADIFromSystemTraceInterface(sti);
    if (top_level_cadi)
    {
        CADITargetFeatures_t features;
        if (top_level_cadi->CADIXfaceGetFeatures(&features) != CADI_STATUS_OK)
        {
            fprintf(stderr, "Cannot get CADI target features of top level component\n");
            return false;
        }

        // register CADI modeChange callback
        char enable[CADI_CB_Count];
        memset(enable, 0, sizeof(enable));
        enable[CADI_CB_ModeChange] = true;
        if (top_level_cadi->CADIXfaceAddCallback(this, enable) != CADI_STATUS_OK)
        {
            fprintf(stderr, "Cannot register CADI modeChange callback for top level component\n");
            return false;
        }

        printf("Connected to CADI target '%s' (%s) (top level component)\n", features.targetName, features.targetVersion);
        return true;
    }

    fprintf(stderr, "Cannot get CADI interface of top level component\n");
    return false;
}

CADIReturn_t
GenericTrace::RegisterSimulation(CAInterface *ca_interface)
{
    if (!ca_interface)
        return CADI_STATUS_IllegalArgument;

    sti = ca_interface->ObtainPointer<SystemTraceInterface>();
    if (!sti)
        return CADI_STATUS_IllegalArgument;

    if ((start_icount != 0) || (stop_icount != uint64_t(MAX_ICOUNT)))
    {
        // register CADI modeChange callback and get CADI interface
        // to be able to stop and restart the simulation
        if (!InitCADI())
            return CADI_STATUS_GeneralError;

        // register PERIODIC callback and start state machine
        RegisterPERIODICCallback();
        if (start_icount > uint64_t(MAX_QUANTUM))
        {
            sm_next_icount = start_icount - MAX_QUANTUM;
            sm_state = SM_BEFORE_START;
        }
        else
        {
            sm_next_icount = stop_icount;
            sm_state = SM_BETWEEN_START_STOP;
            UpdateTraceSourceRegistration();
        }
    }
    else
    {
        // if performance printing is enabled register PERIODIC callback
        if (perf_period)
            RegisterPERIODICCallback();

        // start-stop disabled: register callbacks right from the start
        UpdateTraceSourceRegistration();
    }

    return CADI_STATUS_OK;
}

// This is called before the plugin .dll/.so is unloaded and should allow the plugin to do it's cleanup.
void
GenericTrace::Release()
{
    delete this;
}

const char *
GenericTrace::GetName() const
{
    return instance_name.c_str();
}

typedef enum
{
    PARAM_ID_SOURCES,
    PARAM_ID_TRACE_FILE,
    PARAM_ID_ENABLED,
    PARAM_ID_FLUSH,
    PARAM_ID_SHORTEN_PATHS,
    PARAM_ID_VERBOSE,
    PARAM_ID_START_ICOUNT,
    PARAM_ID_STOP_ICOUNT,
    PARAM_ID_PERF_PERIOD,
    PARAM_ID_PRINT_TIMESTAMP,
    PARAM_ID_HIDE_FIELDNAMES,
    PARAM_ID_NUM_PARAMS
} MyParameterIDs;

const unsigned int num_parameters = PARAM_ID_NUM_PARAMS;

static CADIParameterInfo_t parameters[num_parameters] =
{
    // Note: also edit the default in the constructor (GenericTrace::GenericTrace(), see above) when changing the defaults
    CADIParameterInfo_t(PARAM_ID_SOURCES,
                        "trace-sources",
                        CADI_PARAM_STRING,
                        "A comma separated list of trace sources that should be traced. A component path can be prepended, components separated by dots. Both component path and trace source name can contain the wildcards '*' and '?'. A field mask as a number in hex or decimal format can be appended with '='. Example: my.subsystem.core.cpu*.TRACE_SOURCE=0x08",
                        true, // runtime
                        0, 0, 0,
                        "INST"), // default

    CADIParameterInfo_t(PARAM_ID_TRACE_FILE,
                        "trace-file",
                        CADI_PARAM_STRING,
                        "The trace file to write into. If STDERR will print to stderr, If empty will print to stdout.",
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

    CADIParameterInfo_t(PARAM_ID_SHORTEN_PATHS,
                        "shorten-paths",
                        CADI_PARAM_BOOL,
                        "If set to true then the components paths of trace events will be shortened by cutting off the common prefix. The minimal, non-ambiguous path suffix will remain. If all traced sources belong to the same components no path will be logged. Default is true.",
                        true, // runtime
                        0, 1, 1,
                        0),

    CADIParameterInfo_t(PARAM_ID_VERBOSE,
                        "verbose",
                        CADI_PARAM_BOOL,
                        "Print some debugging information.",
                        true, // runtime
                        0, 1, 0,
                        0),

    CADIParameterInfo_t(PARAM_ID_START_ICOUNT,
                        "start-icount",
                        CADI_PARAM_INT,
                        "Start tracing on a certain instruction count. Tracing will start up to 2048 instructions before this count.",
                        false, // runtime
                        0, GenericTrace::MAX_ICOUNT, 0,
                        0),

    CADIParameterInfo_t(PARAM_ID_STOP_ICOUNT,
                        "stop-icount",
                        CADI_PARAM_INT,
                        "Stop tracing on a certain instruction count. Tracing will stop up to 2048 instructions after this count.",
                        false, // runtime
                        0, GenericTrace::MAX_ICOUNT, GenericTrace::MAX_ICOUNT,
                        0),

    CADIParameterInfo_t(PARAM_ID_PERF_PERIOD,
                        "perf-period",
                        CADI_PARAM_INT,
                        "Print performance every N instructions. 0 means disabled.",
                        false, // runtime
                        0, GenericTrace::MAX_ICOUNT, 0,
                        0),
    CADIParameterInfo_t(PARAM_ID_PRINT_TIMESTAMP,
                        "print-timestamp",
                        CADI_PARAM_BOOL,
                        "Start each trace entry with the host time.",
                        true, // runtime
                        0, 1, 0,
                        0),
    CADIParameterInfo_t(PARAM_ID_HIDE_FIELDNAMES,
                        "hide-fieldnames",
                        CADI_PARAM_BOOL,
                        "Do not print field names when printing trace output.",
                        true, // runtime
                        0, 1, 0,
                        0)
};

CADIReturn_t
GenericTrace::GetParameterInfos(uint32_t startIndex,
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
GenericTrace::GetParameterInfo(const char *parameterName,
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
GenericTrace::GetParameterValues(uint32_t parameterCount,
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
        case PARAM_ID_SOURCES:
            AssignString(param_value.stringValue, trace_sources.c_str(), sizeof(param_value.stringValue));
            break;

        case PARAM_ID_TRACE_FILE:
            AssignString(param_value.stringValue, trace_file_name.c_str(), sizeof(param_value.stringValue));
            break;

        case PARAM_ID_ENABLED:
            param_value.intValue = enabled;
            break;

        case PARAM_ID_FLUSH:
            param_value.intValue = flush;
            break;

        case PARAM_ID_SHORTEN_PATHS:
            param_value.intValue = shorten_paths;
            break;

        case PARAM_ID_VERBOSE:
            param_value.intValue = verbose;
            break;

        case PARAM_ID_START_ICOUNT:
            param_value.intValue = start_icount;
            break;

        case PARAM_ID_STOP_ICOUNT:
            param_value.intValue = stop_icount;
            break;

        case PARAM_ID_PERF_PERIOD:
            param_value.intValue = perf_period;
            break;

        case PARAM_ID_PRINT_TIMESTAMP:
            param_value.intValue = print_timestamp;
            break;
        case PARAM_ID_HIDE_FIELDNAMES:
            param_value.intValue = hide_fieldnames;
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
GenericTrace::SetParameterValues(uint32_t parameterCount,
                                 CADIParameterValue_t *parameter_values,
                                 CADIFactoryErrorMessage_t * /*error*/)
{
    if (!parameter_values)
        return CADI_STATUS_IllegalArgument;

    return SetParametersInternal(parameterCount, parameter_values);
}

CADIReturn_t
GenericTrace::SetParametersInternal(uint32_t parameterCount, CADIParameterValue_t *parameter_values)
{
    for(uint32_t i = 0; i < parameterCount; ++i)
    {
        CADIParameterValue_t &parameter = parameter_values[i];

        switch(parameter.parameterID)
        {
        case PARAM_ID_SOURCES:
            trace_sources = parameter.stringValue;
            UpdateTraceSourceRegistration();
            break;

        case PARAM_ID_TRACE_FILE:
            SetTraceFile(parameter.stringValue);
            break;

        case PARAM_ID_ENABLED:
            enabled = (parameter.intValue != 0);
            UpdateTraceSourceRegistration();
            break;

        case PARAM_ID_FLUSH:
            flush = (parameter.intValue != 0);
            break;

        case PARAM_ID_SHORTEN_PATHS:
            shorten_paths = (parameter.intValue != 0);
            UpdateTraceSourceRegistration();
            break;

        case PARAM_ID_VERBOSE:
            verbose = (parameter.intValue != 0);
            break;

        case PARAM_ID_START_ICOUNT:
            start_icount = parameter.intValue;
            break;

        case PARAM_ID_STOP_ICOUNT:
            stop_icount = parameter.intValue;
            break;

        case PARAM_ID_PERF_PERIOD:
            perf_period = parameter.intValue;
            break;

        case PARAM_ID_PRINT_TIMESTAMP:
            print_timestamp = (parameter.intValue != 0);
            break;

        case PARAM_ID_HIDE_FIELDNAMES:
            hide_fieldnames = (parameter.intValue != 0);
            break;
        }
    }

    return CADI_STATUS_OK;
}

/////////////////////////////////////////////////////////////////////////////

static bool
MatchesWildcard(const string &pattern, const string &str)
{
    if (pattern.empty())        // empty pattern
        return str.empty();     // matches empty string
    switch(pattern[0])
    {
    case '?':
        return (!str.empty() && MatchesWildcard(pattern.substr(1), str.substr(1)));

    case '*':
        return
            MatchesWildcard(pattern.substr(1), str) || // match zero chars
            (!str.empty() && MatchesWildcard(pattern, str.substr(1)));

    default:
        if (!str.empty() && (pattern[0] == str[0]))
            return MatchesWildcard(pattern.substr(1), str.substr(1));
        else
            return false;
    }
}

/////////////////////////////////////////////////////////////////////////////

list<SourceInfo>
GenericTrace::ParseSourceList(string sources)
{
    list<SourceInfo> result;
    for(;;)
    {
        string::size_type delim_pos = sources.find_first_of(";,");
        string source = sources.substr(0, delim_pos);
        string::size_type equal_pos = source.find('=');
        FieldMask field_mask = (FieldMask)-1; // all bits set
        if (equal_pos != string::npos)
        {
            string fields = source.substr(equal_pos + 1);
            source = source.substr(0, equal_pos);
            field_mask = strtoul(fields.c_str(), 0, 0);
        }

        string::size_type dot_pos = source.rfind('.');
        string component_path;
        if (dot_pos != string::npos)
        {
            component_path = source.substr(0, dot_pos);
            source = source.substr(dot_pos + 1);
        }
        // now concretise component/source pairs with existing trace sources:
        // First loop over all components providing trace:
        int numMatchingComponents = 0;
        int numMatchingTraceSources = 0;
        for(SystemTraceInterface::TraceComponentIndex cidx = 0;
            cidx < sti->GetNumOfTraceComponents(); ++cidx)
        {
            if (component_path.empty() || // empty component_path matches all components
                (component_path == sti->GetComponentTracePath(cidx)) ||
                MatchesWildcard(component_path, sti->GetComponentTracePath(cidx)))
            {
                numMatchingComponents++;
                CAInterface *ca_interface = sti->GetComponentTrace(cidx);
                ComponentTraceInterface *cit = ca_interface->ObtainPointer<ComponentTraceInterface>();
                if (!cit)
                    continue;

                // We have found a component which matches the
                // component_path

                // first check for the trace source by name to be able to find hidden sources
                // (hidden trace sources are not advertised in the list of trace sources, but they
                // are available when queried for by name)
                TraceSource *trace_source = cit->GetTraceSource(source.c_str());
                if (trace_source)
                {
                    // found an matching source, add it to the result list now:
                    numMatchingTraceSources++;
                    SourceInfo source_info(this);
                    source_info.component_path = sti->GetComponentTracePath(cidx);
                    source_info.source_name = source;
                    FieldMask mask = (1U << trace_source->GetNumFields()) - 1;
                    source_info.field_mask = mask & field_mask;
                    source_info.trace_source = trace_source;

                    // only add if not already in list:
                    result.push_back(source_info);
                }

                // now iterate over all trace sources
                // to find matching ones:
                // (this will never find hidden sources even if the name matches)
                for(SourceIndex sidx = 0; sidx < cit->GetNumOfTraceSources(); ++sidx)
                {
                    trace_source = cit->GetTraceSource(sidx);
                    const char *curr_source_name = trace_source->GetName();
                    if ((source == curr_source_name) ||
                        MatchesWildcard(source, curr_source_name))
                    {
                        // found an matching source, add it to the result list now:
                        numMatchingTraceSources++;
                        SourceInfo source_info(this);
                        source_info.component_path = sti->GetComponentTracePath(cidx);
                        source_info.source_name = curr_source_name;
                        FieldMask mask = (1U << trace_source->GetNumFields()) - 1;
                        source_info.field_mask = mask & field_mask;
                        source_info.trace_source = trace_source;

                        // only add if not already in list:
                        result.push_back(source_info);
                    }
                }
            }
        }
        // check whether we found any matching trace source at all
        // if not this is most likely a user error: notify user
        if (numMatchingTraceSources == 0)
        {
            // first check whether we did not find any matching component at all: then the problem is in the component name/path
            if (numMatchingComponents == 0)
            {
                fprintf(stderr, "GenericTrace: Warning: ignoring %s.%s: no matching component found, possible component paths (or no component path at all for all components):\n", component_path.c_str(), source.c_str());
                for(SystemTraceInterface::TraceComponentIndex cidx = 0;
                    cidx < sti->GetNumOfTraceComponents(); ++cidx)
                    fprintf(stderr, "GenericTrace:    %s\n", sti->GetComponentTracePath(cidx));
            }
            else
            {
                // some components matched: print available trace sources for all matching components
                fprintf(stderr, "GenericTrace: Warning: ignoring %s.%s: no matching trace source found, but %d matching component paths found, list of available trace sources:\n", component_path.c_str(), source.c_str(), numMatchingComponents);
                for(SystemTraceInterface::TraceComponentIndex cidx = 0;
                    cidx < sti->GetNumOfTraceComponents(); ++cidx)
                {
                    if (component_path.empty() || // empty component_path matches all components
                        (component_path == sti->GetComponentTracePath(cidx)) ||
                        MatchesWildcard(component_path, sti->GetComponentTracePath(cidx)))
                    {
                        fprintf(stderr, "GenericTrace:    list of possible trace sources for component %s:\n", sti->GetComponentTracePath(cidx));
                        CAInterface *ca_interface = sti->GetComponentTrace(cidx);
                        ComponentTraceInterface *cit = ca_interface->ObtainPointer<ComponentTraceInterface>();
                        if (!cit)
                            continue;

                        // We have found a component which matches the
                        // component_path, now iterate over all trace sources and print them
                        for(SourceIndex sidx = 0; sidx < cit->GetNumOfTraceSources(); ++sidx)
                            fprintf(stderr, "GenericTrace:       %s\n", cit->GetTraceSource(sidx)->GetName());
                    }
                }
            }
        }
        if (delim_pos == string::npos)
            break;
        sources = sources.substr(delim_pos + 1);
    }
    return result;
}

void GenericTrace::RegisterPERIODICCallback()
{
    for(SystemTraceInterface::TraceComponentIndex cidx = 0;
        cidx < sti->GetNumOfTraceComponents(); ++cidx)
    {
        CAInterface *ca_interface = sti->GetComponentTrace(cidx);
        ComponentTraceInterface *cit = ca_interface->ObtainPointer<ComponentTraceInterface>();
        if (!cit)
            continue;
        const TraceSource *source = cit->GetTraceSource("PERIODIC");
        if (!source)
            continue;
        if (verbose)
            printf("Attaching PERIODIC callback to component '%s'\n", sti->GetComponentTracePath(cidx));
        FieldMask mask = 0;
        const EventFieldType *eft = 0;
        if ((eft = source->GetField("INST_COUNT")) == 0)
        {
            fprintf(stderr, "No field INST_COUNT found in PERIODIC trace source.");
            return;
        }
        mask |= 1 << eft->GetIndex();
        EventClass *event_class = source->CreateEventClass(mask);
        if (!event_class)
        {
            fprintf(stderr, "Unable to register event class for PERIODIC trace source.");
            return;
        }
        Status status = event_class->RegisterCallback(&PeriodicCallbackThunk, this);
        if (status != MTI_OK)
        {
            fprintf(stderr, "Registration of PERIODIC trace callback failed.");
            return;
        }
        periodic_inst_count_idx = event_class->GetValueIndex("INST_COUNT");
        periodic_pc_idx = event_class->GetValueIndex("PC");
        return;
    }
    fprintf(stderr, "Did not find PERIODIC trace source in any component but start/end-icount was specified.");
}

void GenericTrace::UpdateTraceSourceRegistration()
{
    if (!sti)  // RegisterSimulation() not yet called
        return;

    // step 1: Parse trace_sources string:
    list<SourceInfo> new_sources;
    if (enabled) // if not enabled we will unregister all sources
        new_sources = ParseSourceList(trace_sources);

    // step 2: Now unregister sources no longer wanted:
    for(list<SourceInfo>::iterator it = registered_sources.begin();
        it != registered_sources.end();)
    {
        list<SourceInfo>::iterator next_it = it; ++next_it;
        if (std::find(new_sources.begin(), new_sources.end(), *it) == new_sources.end())
        { // if not contained in new sources unregister it:
            EventClass *event_class = it->event_class;
            assert(event_class);
            if (event_class->UnregisterCallback(&TraceCallbackThunk, &*it) == MTI_OK)
            {
                // Remove from list of registered sources:
                if (verbose)
                    printf("GenericTrace: Removed %s.%s=0x%x\n",
                           it->component_path.c_str(),
                           it->source_name.c_str(),
                           it->field_mask);
                registered_sources.erase(it);
            }
        }
        it = next_it;
    }

    // step 3: Now add new sources which are not already registered:
    for(list<SourceInfo>::iterator it = new_sources.begin();
        it != new_sources.end();)
    {
        list<SourceInfo>::iterator next_it = it; ++next_it;
        if (std::find(registered_sources.begin(), registered_sources.end(), *it) == registered_sources.end())
        { // Not found in registered sources, so register it:
            it->event_class = it->trace_source->CreateEventClass(it->field_mask);
            assert(it->event_class);
            if (it->event_class->RegisterCallback(&TraceCallbackThunk, &*it) == MTI_OK)
            {
                // move *it from new_sources to registered_sources list:
                registered_sources.splice(registered_sources.end(), new_sources, it);
                if (verbose)
                    printf("GenericTrace: Added   %s.%s=0x%x\n",
                           it->component_path.c_str(),
                           it->source_name.c_str(),
                           it->field_mask);
            }
            else if (it->event_class->DumpState(&TraceCallbackThunk, &*it) == MTI_OK)
            {
                if (verbose)
                    printf("GenericTrace: Dumped state of %s.%s=0x%x\n",
                           it->component_path.c_str(),
                           it->source_name.c_str(),
                           it->field_mask);
            }
            else
            {
                fprintf(stderr, "GenericTrace: Error: Can neither register a callback nor can trigger a state dump on trace source %s.%s\n",
                        it->component_path.c_str(),
                        it->source_name.c_str());

            }
        }
        it = next_it;
    }

    // Calculate print_paths:
    if (enabled && !registered_sources.empty())
    {
        string common_path;
        if (shorten_paths)
        {
            // Step 1: Find the longest common prefix of all component paths:
            list<SourceInfo>::iterator it = registered_sources.begin();
            common_path = it->component_path + '.';
            ++it;
            for(;it != registered_sources.end(); ++it)
            {
                string full_path = it->component_path + '.';
                string::iterator first_mismatch =
                    mismatch(common_path.begin(), common_path.end(),
                             full_path.begin()).first;
                common_path.erase(first_mismatch, common_path.end());
            }
            // Ensure the common path contains only full component names, so it ends with a dot:
            string::size_type last_dot = common_path.rfind('.');
            if (last_dot != string::npos)
                common_path.erase(last_dot + 1, string::npos);
            else
                common_path.erase();
        }
        // Step2: Cut off the common prefix to create the path for printing:
        for(list<SourceInfo>::iterator it = registered_sources.begin();
            it != registered_sources.end(); ++it)
        {
            string full_path = it->component_path + '.';
            it->print_path = full_path.substr(common_path.length());
        }
    }
}

// Get precise time in seconds as a double
double
GenericTrace::GetTimeSec() const
{
#ifdef WIN32
    LARGE_INTEGER curr_time;
    QueryPerformanceCounter(&curr_time);
    return double(curr_time.QuadPart) / performance_counter_freq;
#else
    struct timeval curr_time;
    gettimeofday(&curr_time, 0);
    return double(curr_time.tv_sec) + (double(curr_time.tv_usec) / 1000000.0);
#endif
}

/////////////////////////////////////////////////////////////////////////////

void GenericTrace::TraceCallback(const SourceInfo* source_info,
                                 const MTI::EventClass *event_class,
                                 const struct MTI::EventRecord *record)
{
    (void)source_info;
    // TODO: do as much work as possible in a separate thread
    // -> at least the I/O
    // -> possibly the substitution as well (investigate thread safety and live range of event_class and record...)
    //    >> will probably have to do all reads in this thread
    buffer->clear();
    if (print_timestamp) {
        char timestamp[32];
        timestamp[0] = 0;
        snprintf(timestamp, 32, "%.6f ", GetTimeSec());
        buffer->addString(timestamp);
    }
    pattern(source_info, event_class).substitute(*buffer, record);
    fwrite(buffer->data(), 1, buffer->size(), trace_file);
    if (flush)
        fflush(trace_file);
}

// The callback interface is a C interface, so we need a short thunk
// function to call into a C++ method. This is done via a static C++
// method, which behaves like a C function:
void
GenericTrace::TraceCallbackThunk(void * user_data,
                                 const MTI::EventClass *event_class,
                                 const struct MTI::EventRecord *record)
{
    SourceInfo *source_info = reinterpret_cast<SourceInfo *>(user_data);
    GenericTrace *generic_trace = source_info->owner;
    // TODO: skip the method call and do everything here?
    generic_trace->TraceCallback(source_info, event_class, record);
}

void
GenericTrace::PeriodicCallback(const EventClass *event_class,
                               const struct EventRecord *record)
{
    uint64_t icount = record->Get<uint64_t>(event_class, periodic_inst_count_idx);
    // is the start-stop state machine still running?
    if (icount >= sm_next_icount)
    {
        switch(sm_state)
        {
        case SM_BEFORE_START:
            // start tracing
            sm_next_icount = stop_icount;
            enabled = true;
            sm_state = SM_BETWEEN_START_STOP;
            UpdateTraceSourceRegistration();
            break;

        case SM_BETWEEN_START_STOP:
            // stop tracing
            sm_next_icount = uint64_t(-1);
            enabled = false;
            sm_state = SM_AFTER_STOP;
            UpdateTraceSourceRegistration();
            break;

        case SM_AFTER_STOP:
            // ignore, should never come here because sm_next_icount
            break;
        }
    }

    // is performance printing enabled?
    if (perf_period)
    {
        if (icount >= perf_next_icount)
        {
            double cur_time = GetTimeSec();
            if (perf_last_time == 0.0)
            {
                // this is our first PERIODIC callback
                perf_next_icount = icount;
            }
            else
            {
                // we executed roughly perf_period instructions:
                // calc and print performance
                double delta_time = cur_time - perf_last_time;
                uint64_t delta_icount = icount - perf_last_icount;
                double performance = double(delta_icount) / delta_time;

                fprintf(trace_file, "PERFORMANCE: %5.1f MIPS (Inst:%"PRIu64")\n", performance / 1000000.0, icount);
            }
            perf_next_icount += perf_period;
            perf_last_time = cur_time;
            perf_last_icount = icount;
        }
    }
}

void
GenericTrace::PeriodicCallbackThunk(void * user_data,
                                    const EventClass *event_class,
                                    const struct EventRecord *record)
{
    GenericTrace *me = reinterpret_cast<GenericTrace *>(user_data);
    me->PeriodicCallback(event_class, record);
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

    virtual const char *GetType() const { return "GenericTrace"; }
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
    return static_cast<PluginInstance *>(new GenericTrace(instance_name, number_of_parameters, param_values));
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

// End of file GenericTrace.cpp
