/*!
 *  \file   CacheStatistics.cpp
 *  \brief  A trace plugin demonstrating the gathering of cache statistics
 *  \date   Copyright ARM Limited 2009-2010 All Rights Reserved.
 *  
 */

/*
 * Method: Tracing cache hits, or even counting cache hit events does
 * significantly slow down the model. This is why instead of counting
 * CACHE_HITs we will count the number of misses and uncached events,
 * and the total number of accesses (separate for reads and
 * writes). Based on this we can then calculate the number of cache
 * hits.
 *
 * To count total memory accesses for the data side we count the
 * number of loads and stores. Some loads and stores (caused by
 * LDM/STM instructions) will cause multiple cache accesses, but a
 * single CORE_LOADS/CORE_STORES event. This means that for multi-word
 * accesses we count one load/store per memory word.
 *
 * For the instruction side we count the number of instructions
 * executed using the "INST" trace source. We cannot rely on the
 * number of CACHE_HIT events for the instruction side since
 * instruction fetching is not modelled device accurate.
 *
 * For the second level cache(s) the number of reads and writes is the
 * same as the number of cache line fills and cache line (dirty)
 * evictions of all first level caches respectively. Also, if a 1st
 * level cache does not support allocate on write this means that all
 * level 1 write misses will appear as cache write accesses of the
 * second level cache.
 *
 */

#include "sg/IncludeMeFirst.h"
#include "hostconf/zinttypes.h"

#include "MTI/PluginInterface.h"
#include "MTI/PluginFactory.h"
#include "MTI/PluginInstance.h"
#include "MTI/ModelTraceInterface.h"

#include <map>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
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

typedef enum {
    INST,
    DATA,
    UNIFIED
} SideT;


class CondCounter
{
public:
   bool      trace_enable;
   uint64_t  value;

   CondCounter() : trace_enable(false), value(0) {}
};


/////////////////////////////////////////////////////////////////////////////

// Class containing common code for CacheTracer and CoreTracer classes:
class Tracer
{
public:
    virtual ~Tracer() {}

    unsigned int GetLevel() const { return level; }
    bool SelfcheckActive() const { return selfcheck; }
    virtual void PrintInfo() const = 0;
    virtual void PrintStatistics() const = 0;

    virtual void RegisterTotalReadsCounter(SideT side, CondCounter &counter, bool unregister) = 0;
    virtual void RegisterTotalWritesCounter(SideT side, CondCounter &counter, bool unregister) = 0;

protected:
    Tracer(const char *component_name, ComponentTraceInterface *cti, bool selfcheck);

    // Convenience wrapper function containing error handling.
    // fields is comma separated list of fields:
    EventClass *CreateEventClass(const char *source_name, const char *fields);
    void RegisterCallback(EventClass *event_class, CallbackT callback, void *user_data,
                          bool unregister = false);

    ValueIndex Error(const string &message) const;

    void RegisterCounter(const char *name, uint64_t *counter, bool unregister = false);

protected: // data
    string component_name;
    ComponentTraceInterface *cti;
    bool enabled;
    bool selfcheck;
    unsigned int level; // 0=core, 1 = 1st level cache, 2 = 2nd level cache
};

Tracer::Tracer(const char *component_name_, ComponentTraceInterface *cti_, bool selfcheck_) :
    component_name(component_name_),
    cti(cti_),
    enabled(false),
    selfcheck(selfcheck_),
    level(0)
{    
}

EventClass *
Tracer::CreateEventClass(const char *source_name, const char *field_string)
{
    TraceSource *source = cti->GetTraceSource(source_name);
    if (!source)
    {
        char buf[128];
        sprintf(buf, "In component %s: No trace source %s found.", 
                component_name.c_str(), source_name);
        throw(std::runtime_error(buf));
    }
    
    FieldMask mask = 0;
    string fields(field_string);
    for(;!fields.empty();)
    {
        string::size_type delim_pos = fields.find(',');
        string field_name = fields.substr(0, delim_pos);
        const EventFieldType *event_field = source->GetField(field_name.c_str());
        if (!event_field)
        {
            char buf[128];
            sprintf(buf, "Error: no field %s in trace source %s.",
                    field_name.c_str(), source_name);
            throw runtime_error(buf);
        }
        mask |= 1 << event_field->GetIndex();

        if (delim_pos == string::npos)
            break;
        fields = fields.substr(delim_pos + 1);
    }
    EventClass *event_class = source->CreateEventClass(mask);
    return event_class;
}

void
Tracer::RegisterCallback(EventClass *event_class, CallbackT callback, void *user_data, bool unregister)
{
    if (unregister)
    {
        Status status = event_class->UnregisterCallback(callback, user_data);
        if (status != MTI_OK)
        {
            char buf[128];
            sprintf(buf, "Error: Unable to unregister callback for trace source %s.", 
                    event_class->GetSource()->GetName());
            Error(buf);
        }
    }
    else
    {
        Status status = event_class->RegisterCallback(callback, user_data);
        if (status != MTI_OK)
        {
            char buf[128];
            sprintf(buf, "Error: Unable to register callback for trace source %s.", 
                    event_class->GetSource()->GetName());
            Error(buf);
        }
    }
}

ValueIndex
Tracer::Error(const string &message) const
{
    fprintf(stderr, "Error: %s\n", message.c_str());
    return -1;
}

void
Tracer::RegisterCounter(const char *name, uint64_t *counter, bool unregister)
{
    TraceSource *source = cti->GetTraceSource(name);
    if (!source)
    {
        Error("No trace source \"" + string(name) + "\" found.");
        return;
    }

    if (unregister)
    {
        Status status = source->UnregisterCounter(counter);
        if (status != MTI_OK)
            Error("TraceSource::UnregisterCounter() returned error.");
    }
    else
    {
        Status status = source->RegisterCounter(counter);
        if (status != MTI_OK)
            Error("TraceSource::RegisterCounter() returned error.");
    }
}

/////////////////////////////////////////////////////////////////////////////

class CoreTracer;


// Class to calculate cache statistics for one cache:
class CacheTracer :
    public Tracer
{
public:
    CacheTracer(const char *component_name, ComponentTraceInterface *cti, bool selfcheck, CoreTracer *core);
    virtual void PrintInfo() const;
    virtual void PrintStatistics() const;

    void Connect(Tracer *higher_level);

    virtual void RegisterTotalReadsCounter(SideT side, CondCounter& counter, bool unregister);
    virtual void RegisterTotalWritesCounter(SideT side, CondCounter& counter, bool unregister);

    void ToggleCounters(bool icache_enable, bool dcache_enabled);

    bool SelfCheckError();

protected:
    CoreTracer *core;
    vector<Tracer *> higher_level_tracers;
    
    bool verbose;

    unsigned int linelen;
    unsigned int associativity;
    unsigned int nsets;

    SideT side;

    bool supports_read_allocate;
    bool supports_write_allocate;

    bool icache_enabled;
    bool dcache_enabled;

    uint64_t read_hits_check; // for self-check
    uint64_t read_misses;
    uint64_t read_uncacheable;

    uint64_t write_hits_check; // for self-check
    uint64_t write_misses;
    uint64_t write_uncacheable;

    uint64_t cache_line_fills;
    uint64_t cache_line_evictions;

    void
    TraceCACHE_INFO(const MTI::EventClass *event_class,
                    const struct MTI::EventRecord *record);
    static void
    TraceCACHE_INFO_thunk(void * user_data,
                          const MTI::EventClass *event_class,
                          const struct MTI::EventRecord *record);

    EventClass *cache_info_event_class;
    ValueIndex cache_info_level_idx,
        cache_info_linelen_idx,
        cache_info_associativity_idx,
        cache_info_nsets_idx,
        cache_info_cache_type_idx,
        cache_info_ra_idx, cache_info_wa_idx;

public:
    CondCounter  total_reads;  // sum of hits, misses and uncached reads
    CondCounter  total_writes; // sum of hits, misses and uncached writes
};

CacheTracer::CacheTracer(const char *component_name_, ComponentTraceInterface *cti_, bool selfcheck_,
                         CoreTracer *core_) :
    Tracer(component_name_, cti_, selfcheck_),

    core(core_),

    verbose(true),

    linelen(0),
    associativity(0),
    nsets(0),
    side(UNIFIED),

    supports_read_allocate(false),
    supports_write_allocate(false),

    icache_enabled(false),
    dcache_enabled(false),

    read_hits_check(0),
    read_misses(0),
    read_uncacheable(0),

    write_hits_check(0),
    write_misses(0),
    write_uncacheable(0),

    cache_line_fills(0),
    cache_line_evictions(0),

    cache_info_event_class(0),
    cache_info_level_idx(-1),
    cache_info_linelen_idx(-1),
    cache_info_associativity_idx(-1),
    cache_info_nsets_idx(-1),
    cache_info_cache_type_idx(-1),
    cache_info_ra_idx(-1),
    cache_info_wa_idx(-1)
{
    cache_info_event_class = CreateEventClass("CACHE_INFO", "LEVEL,LINELEN,ASSOCIATIVITY,NSETS,CACHE_TYPE,RA,WA");
    cache_info_level_idx         = cache_info_event_class->GetValueIndex("LEVEL");
    cache_info_linelen_idx       = cache_info_event_class->GetValueIndex("LINELEN");
    cache_info_associativity_idx = cache_info_event_class->GetValueIndex("ASSOCIATIVITY");
    cache_info_nsets_idx         = cache_info_event_class->GetValueIndex("NSETS");
    cache_info_cache_type_idx    = cache_info_event_class->GetValueIndex("CACHE_TYPE");
    cache_info_ra_idx            = cache_info_event_class->GetValueIndex("RA");
    cache_info_wa_idx            = cache_info_event_class->GetValueIndex("WA");

    cache_info_event_class->DumpState(TraceCACHE_INFO_thunk, this);

    if (verbose)
    {
        RegisterCounter("CACHE_LINE_FILL", &cache_line_fills);
        RegisterCounter("CACHE_LINE_EVICTION", &cache_line_evictions);
    }

    if (side == INST)
        selfcheck = false;
}

void
CacheTracer::TraceCACHE_INFO(const MTI::EventClass *event_class,
                             const struct MTI::EventRecord *record)
{
    level = record->GetAs<uint32_t>(event_class, cache_info_level_idx);
    linelen = record->GetAs<uint32_t>(event_class, cache_info_linelen_idx);
    associativity = record->GetAs<uint32_t>(event_class, cache_info_associativity_idx);
    nsets = record->GetAs<uint32_t>(event_class, cache_info_nsets_idx);
    supports_read_allocate = record->GetBool(event_class, cache_info_ra_idx);
    supports_write_allocate = record->GetBool(event_class, cache_info_wa_idx);

    uint8_t type = record->GetAs<uint8_t>(event_class, cache_info_cache_type_idx);
    const char *type_str = event_class->GetEventField(cache_info_cache_type_idx)->LookupEnum(type);

    if (strcmp(type_str, "Instruction") == 0)
        side = INST;
    else if (strcmp(type_str, "Data") == 0)
        side = DATA;
    else if (strcmp(type_str, "Unified") == 0)
        side = UNIFIED;
}

void
CacheTracer::TraceCACHE_INFO_thunk(void * user_data,
                                   const MTI::EventClass *event_class,
                                   const struct MTI::EventRecord *record)
{
    CacheTracer *that = reinterpret_cast<CacheTracer *>(user_data);
    that->TraceCACHE_INFO(event_class, record);
}


void
CacheTracer::PrintInfo() const
{
    printf("Cache info for %s\n", component_name.c_str());
    puts(string(60, '-').c_str());
    printf("Level: %u\n", level);
    printf("Type: %s\n", (side == INST) ? "Instruction" : (side == DATA) ? "Data" : "Unified");
    printf("Size of one cache-line in bytes: %u\n", linelen);
    printf("Associativity: %u\n", associativity);
    printf("Number of cache sets: %u\n", nsets);
    unsigned int size = linelen * associativity * nsets;
    printf("Size: %u bytes = %u kbytes\n", size, size / 1024);
    putchar('\n');
}

static void
PrintStatisticsPart(const char *access_kind, 
                    uint64_t total, uint64_t hits, uint64_t misses, uint64_t uncacheable)
{
    printf("#total %ss        : %10"PRIu64"  %6.2f%% \n",
           access_kind, total, 100.0);
    printf("#non-cacheable %ss: %10"PRIu64"  %6.2f%% \n",
           access_kind, uncacheable, uncacheable * 100.0 / total);
    printf("#cacheable %ss    : %10"PRIu64"  %6.2f%%  %6.2f%%\n",
           access_kind, (hits + misses),
           (hits + misses) * 100.0 / total, 100.0);
    printf("#%s hits          : %10"PRIu64" (%6.2f%%) %6.2f%%\n",
           access_kind, hits, hits * 100.0 / total,
           hits * 100.0 / (hits + misses));
    printf("#%s misses        : %10"PRIu64" (%6.2f%%) %6.2f%%\n",
           access_kind, misses, misses * 100.0 / total,
           misses * 100.0 / (hits + misses));
    putchar('\n');
}

void
CacheTracer::PrintStatistics() const
{
    printf("Cache statistics for %s\n", component_name.c_str());
    puts(string(21 + component_name.length(), '-').c_str());

    int64_t read_hits = total_reads.value - read_misses - read_uncacheable;

    PrintStatisticsPart("read", total_reads.value, read_hits, read_misses, read_uncacheable);

    if ((read_uncacheable + read_hits + read_misses) == 0)
    {
        puts("All event counts are zero.");
        puts("DID YOU TURN ON THE CACHE STATE SIMULATION by setting a parameter ???\n");
        return;
    }

    if (selfcheck)
    {
        printf("#Read Hits Check: %10"PRIu64"\n", read_hits_check);
        putchar('\n');
    }

    if (side != INST)
    {
        int64_t write_hits = total_writes.value - write_misses - write_uncacheable;
        PrintStatisticsPart("write", total_writes.value, write_hits, write_misses, write_uncacheable);
        if (selfcheck)
        {
            printf("#Write Hits Check: %10"PRIu64"\n", write_hits_check);
            putchar('\n');
        }
        PrintStatisticsPart("access",
                            total_reads.value + total_writes.value,
                            read_hits + write_hits,
                            read_misses + write_misses,
                            read_uncacheable + write_uncacheable);
    }
    if (verbose)
    {
        printf("#Cache Line Fills    : %10"PRIu64"\n", cache_line_fills);
        printf("#Cache Line Evictions: %10"PRIu64"\n", cache_line_evictions);
        putchar('\n');
    }
    putchar('\n');
}

void
CacheTracer::Connect(Tracer *higher_level)
{
    higher_level_tracers.push_back(higher_level);
}

void
CacheTracer::ToggleCounters(bool icache_enabled_, bool dcache_enabled_)
{
    bool new_enabled_state = false;
    switch(side)
    {
    case INST: new_enabled_state = icache_enabled_; break;
    case DATA: new_enabled_state = dcache_enabled_; break;
    case UNIFIED: new_enabled_state = icache_enabled_ || dcache_enabled_; break;
    }

    if (enabled == new_enabled_state) // state does not change
        return;

    RegisterCounter("CACHE_READ_MISS", &read_misses, enabled);
    RegisterCounter("CACHE_READ_NON_CACHEABLE", &read_uncacheable, enabled);
    
    RegisterCounter("CACHE_WRITE_MISS", &write_misses, enabled);
    RegisterCounter("CACHE_WRITE_NON_CACHEABLE", &write_uncacheable, enabled);
    
    for(vector<Tracer *>::iterator it = higher_level_tracers.begin();
        it != higher_level_tracers.end(); ++it)
    {
        (*it)->RegisterTotalReadsCounter(side, total_reads, enabled);
        (*it)->RegisterTotalWritesCounter(side, total_writes, enabled);
    }
    if (selfcheck)
    {
        RegisterCounter("CACHE_READ_HIT", &read_hits_check, enabled);
        RegisterCounter("CACHE_WRITE_HIT", &write_hits_check, enabled);
    }

    enabled = new_enabled_state;
}

void
CacheTracer::RegisterTotalReadsCounter(SideT lower_side, CondCounter &counter, bool unregister)
{
    if ((lower_side == UNIFIED) ||
        (side == lower_side))
    {
        RegisterCounter("CACHE_READ_NON_CACHEABLE", &counter.value, unregister);
        RegisterCounter("CACHE_LINE_FILL", &counter.value, unregister);

        // If cache does not allocate on read miss we must also count read misses here:
        if (!supports_read_allocate)
            RegisterCounter("CACHE_READ_MISS", &counter.value, unregister);
    }
}

void
CacheTracer::RegisterTotalWritesCounter(SideT lower_side, CondCounter &counter, bool unregister)
{
    if ((lower_side == UNIFIED) ||
        (side == lower_side))
    {
        RegisterCounter("CACHE_WRITE_NON_CACHEABLE", &counter.value, unregister);
        RegisterCounter("CACHE_LINE_EVICTION", &counter.value, unregister);

        // If cache does not allocate on write miss we must also count write misses here:
        if (!supports_write_allocate)
            RegisterCounter("CACHE_WRITE_MISS", &counter.value, unregister);
    }
}

bool 
CacheTracer::SelfCheckError()
{
    // We cannot do the self-check on the instruction side since
    // instruction fetching is not modelled device accurate:
    if (side == INST)
        return false;

    bool found_error = false;
    if (total_reads.value != read_hits_check + read_misses + read_uncacheable)
    {
        printf("In cache %s:\n", component_name.c_str());
        printf("Error: Difference in reads: %"PRIu64" != %"PRIu64" = %"PRIu64"(hits) + %"PRIu64"(misses) + %"PRIu64"(uncacheable) (%"PRId64")\n",
               total_reads.value,
               read_hits_check + read_misses + read_uncacheable,
               read_hits_check,
               read_misses,
               read_uncacheable,
               total_reads.value - (read_hits_check + read_misses + read_uncacheable));
        found_error = true;
        if (getenv("ASSERT")) assert(0);
        read_hits_check = total_reads.value - (read_misses + read_uncacheable);
    }
    if (side != INST)
    {
        
        if (total_writes.value != write_hits_check + write_misses + write_uncacheable)
        {
            printf("Error: Difference in writes: %"PRIu64" != %"PRIu64" = %"PRIu64"(hits) + %"PRIu64"(misses) + %"PRIu64"(uncacheable) (%"PRId64")\n",
                   total_writes.value,
                   (write_hits_check + write_misses + write_uncacheable),
                   write_hits_check,
                   write_misses,
                   write_uncacheable,
                   (total_writes.value - (write_hits_check + write_misses + write_uncacheable)));
            found_error = true;
            if (getenv("ASSERT")) assert(0);
            write_hits_check = total_writes.value - (write_misses + write_uncacheable);
        }
    }
    return found_error;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class CoreTracer :
    public Tracer
{
public:
    CoreTracer(const char *component_name, ComponentTraceInterface *cit, bool selfcheck);
    ~CoreTracer();

    void RegisterCache(CacheTracer *);

    virtual void PrintInfo() const;
    virtual void PrintStatistics() const;

    void Connect();

    virtual void RegisterTotalReadsCounter(SideT side, CondCounter &counter, bool unregister);
    virtual void RegisterTotalWritesCounter(SideT side, CondCounter &counter, bool unregister);

    virtual void ToggleCounters(bool new_enable_state);

protected:
    void
    TraceCORE_INFO(const MTI::EventClass *event_class,
                   const struct MTI::EventRecord *record);
    static void
    TraceCORE_INFO_thunk(void * user_data,
                         const MTI::EventClass *event_class,
                         const struct MTI::EventRecord *record);

    virtual void
    TraceCP15_WRITE(const MTI::EventClass *event_class,
                    const struct MTI::EventRecord *record);
    static void
    TraceCP15_WRITE_Thunk(void * user_data,
                          const MTI::EventClass *event_class,
                          const struct MTI::EventRecord *record);
    static void
    TraceLOAD(void * user_data,
              const MTI::EventClass *event_class,
              const struct MTI::EventRecord *record);

    static void
    TraceSTORE(void * user_data,
               const MTI::EventClass *event_class,
               const struct MTI::EventRecord *record);

    void
    TraceINST(const MTI::EventClass *event_class,
              const struct MTI::EventRecord *record);
    static void
    TraceINST_thunk(void * user_data,
                    const MTI::EventClass *event_class,
                    const struct MTI::EventRecord *record);

protected:    
    typedef enum {
        VMSA,
        PMSA,
        FLAT
    } MemArchT;

    MemArchT mem_arch;

    vector<CacheTracer *> caches; // a core knows its caches

    bool curr_icache_enabled, curr_dcache_enabled;

    EventClass *core_info_event_class;
    ValueIndex core_info_mem_arch_idx;

    EventClass *cp15_event_class;
    ValueIndex cp15_crn_idx, cp15_opc1_idx, cp15_crm_idx, cp15_opc2_idx, cp15_value_idx;

    EventClass *core_loads_event_class;
    EventClass *core_stores_event_class;

    EventClass *inst_event_class;
    size_t inst_record_size;
    EventRecord *last_inst_record;
};

CoreTracer::CoreTracer(const char *component_name_, ComponentTraceInterface *cti_, bool selfcheck_) :
    Tracer(component_name_, cti_, selfcheck_),

    curr_icache_enabled(false),
    curr_dcache_enabled(false),

    core_info_event_class(0),
    core_info_mem_arch_idx(-1),

    cp15_event_class(0),
    cp15_crn_idx(-1), cp15_opc1_idx(-1), cp15_crm_idx(-1), cp15_opc2_idx(-1), cp15_value_idx(-1),

    core_loads_event_class(0),
    core_stores_event_class(0),

    inst_event_class(0),
    inst_record_size(0),
    last_inst_record(0)
{
    core_info_event_class = CreateEventClass("CORE_INFO", "MEM_ARCH");
    core_info_mem_arch_idx = core_info_event_class->GetValueIndex("MEM_ARCH");
    core_info_event_class->DumpState(TraceCORE_INFO_thunk, this);

    cp15_event_class = CreateEventClass("CP15_WRITE", "CRn,opc1,CRm,opc2,VALUE");
    cp15_crn_idx   = cp15_event_class->GetValueIndex("CRn");
    cp15_opc1_idx  = cp15_event_class->GetValueIndex("opc1");
    cp15_crm_idx   = cp15_event_class->GetValueIndex("CRm");
    cp15_opc2_idx  = cp15_event_class->GetValueIndex("opc2");
    assert(cp15_opc2_idx == 3);
    cp15_value_idx = cp15_event_class->GetValueIndex("VALUE");
    RegisterCallback(cp15_event_class, TraceCP15_WRITE_Thunk, this);

    core_loads_event_class = CreateEventClass("CORE_LOADS", "SIZE,LOCK");
    core_stores_event_class = CreateEventClass("CORE_STORES", "SIZE,LOCK");
    
    if (selfcheck_)
    {
        inst_event_class = CreateEventClass("INST", "PC,OPCODE,ISET,INST_COUNT");
        inst_record_size = inst_event_class->GetEventRecordSize();
        last_inst_record = reinterpret_cast<EventRecord *>(new uint8_t[inst_record_size]);
    }
}

void
CoreTracer::RegisterCache(CacheTracer *cache)
{
    RegisterCallback(core_loads_event_class,  TraceLOAD,  &cache->total_reads);
    RegisterCallback(core_stores_event_class, TraceSTORE, &cache->total_writes);

    caches.push_back(cache);
}

void
CoreTracer::PrintInfo() const
{
    for(vector<CacheTracer *>::const_iterator it = caches.begin();
        it != caches.end(); ++it)
        (*it)->PrintInfo();
}

void
CoreTracer::PrintStatistics() const
{
    for(vector<CacheTracer *>::const_iterator it = caches.begin();
        it != caches.end(); ++it)
        (*it)->PrintStatistics();
}

void
CoreTracer::Connect()
{
    // Connect caches of adjacent levels:

    for(vector<CacheTracer *>::const_iterator it1 = caches.begin();
        it1 != caches.end(); ++it1)
    {
        // Connect 1st level caches with core:
        if ((*it1)->GetLevel() == 1)
            (*it1)->Connect(this);

        for(vector<CacheTracer *>::const_iterator it2 = caches.begin();
            it2 != caches.end(); ++it2)
        {
            // If cache level differs by one:
            if ((*it1)->GetLevel() == ((*it2)->GetLevel() - 1))
            {
                (*it2)->Connect(*it1);
            }
        }
    }
}

void
CoreTracer::RegisterTotalReadsCounter(SideT lower_side, CondCounter& counter, bool unregister)
{
    if ((lower_side == INST) || (lower_side == UNIFIED))
    {
        RegisterCounter("INST", &counter.value, unregister);
    }

    if ((lower_side == DATA) || (lower_side == UNIFIED))
    {
        counter.trace_enable = !unregister;

        if (mem_arch == VMSA)
            RegisterCounter("MMU_TTB_READ", &counter.value, unregister);

        RegisterCounter("PRELOAD_DATA", &counter.value, unregister);
    }
}

void
CoreTracer::RegisterTotalWritesCounter(SideT lower_side, CondCounter& counter, bool unregister)
{
    if ((lower_side == DATA) || (lower_side == UNIFIED))
    {
        counter.trace_enable = !unregister;
    }
}

void
CoreTracer::ToggleCounters(bool new_enabled_state)
{
    if (enabled == new_enabled_state) // state does not change
        return;

    if (selfcheck)
        RegisterCallback(inst_event_class, TraceINST_thunk, this, enabled);

    enabled = new_enabled_state;
}

CoreTracer::~CoreTracer()
{
    PrintStatistics();
    delete[] last_inst_record;
}

/////////////////////////////////////////////////////////////////////////////


void
CoreTracer::TraceCORE_INFO(const MTI::EventClass *event_class,
                           const struct MTI::EventRecord *record)
{
    uint8_t mem_arch_int = record->GetAs<uint8_t>(event_class, core_info_mem_arch_idx);
    const char *mem_arch_str = event_class->GetEventField(core_info_mem_arch_idx)->LookupEnum(mem_arch_int);

    mem_arch = (MemArchT)mem_arch_int;
    if (strcmp(mem_arch_str, "VMSA") == 0)
        mem_arch = VMSA;
    else if (strcmp(mem_arch_str, "PMSA") == 0)
        mem_arch = PMSA;
    else if (strcmp(mem_arch_str, "FLAT") == 0)
        mem_arch = FLAT;
}

void
CoreTracer::TraceCORE_INFO_thunk(void * user_data,
                                 const MTI::EventClass *event_class,
                                 const struct MTI::EventRecord *record)
{
    CoreTracer *that = reinterpret_cast<CoreTracer *>(user_data);
    that->TraceCORE_INFO(event_class, record);
}

////////////////////////////////////////

void
CoreTracer::TraceCP15_WRITE(const MTI::EventClass *event_class,
                            const struct MTI::EventRecord *record)
{
    uint8_t CRn = record->Get<uint8_t>(event_class, cp15_crn_idx);
    uint8_t CRm = record->Get<uint8_t>(event_class, cp15_crm_idx);
    uint8_t opc1 = record->Get<uint8_t>(event_class, cp15_opc1_idx);
    uint8_t opc2 = record->Get<uint8_t>(event_class, cp15_opc2_idx);
    uint32_t value = record->Get<uint32_t>(event_class, cp15_value_idx);
    
    if ((CRn == 1) && (opc1 == 0) && (CRm == 0) && (opc2 == 0)) // SCTLR (Control) register
    {
        bool icache_enabled =  (value & (1U << 2)) != 0;
        bool dcache_enabled =  (value & (1U << 2)) != 0;

        if ((icache_enabled != curr_icache_enabled) ||
            (dcache_enabled != curr_dcache_enabled))
        {
            printf("ICache:%s DCache:%s\n",
                   icache_enabled ? "enabled" : "disabled",
                   dcache_enabled ? "enabled" : "disabled");

            bool core_enabled = icache_enabled || dcache_enabled;
            ToggleCounters(core_enabled);
            
            for(vector<CacheTracer *>::const_iterator it = caches.begin();
                it != caches.end(); ++it)
            {
                (*it)->ToggleCounters(icache_enabled, dcache_enabled);
            }

            curr_icache_enabled = icache_enabled;
            curr_dcache_enabled = dcache_enabled;
        }
    }
}

void
CoreTracer::TraceCP15_WRITE_Thunk(void *user_data,
                                  const MTI::EventClass *event_class,
                                  const struct MTI::EventRecord *record)
{
    CoreTracer *core_tracer = reinterpret_cast<CoreTracer *>(user_data);
    core_tracer->TraceCP15_WRITE(event_class, record);
}

////////////////////////////////////////

void
CoreTracer::TraceLOAD(void * user_data,
                      const MTI::EventClass *event_class,
                      const struct MTI::EventRecord *record)
{
    CondCounter* counter = reinterpret_cast<CondCounter*>(user_data);

    if ( !counter->trace_enable )  return;

    uint8_t lock = record->Get<uint8_t>(event_class, 0);
    uint8_t size = record->Get<uint8_t>(event_class, 1);

    if ((size > 4) && (lock == 0)) // LDM
    {
        assert((size % 4) == 0);
        counter->value += size / 4;
    }
    else
        ++counter->value;
}

////////////////////////////////////////

void
CoreTracer::TraceSTORE(void * user_data,
                       const MTI::EventClass *event_class,
                       const struct MTI::EventRecord *record)
{
    CondCounter* counter = reinterpret_cast<CondCounter*>(user_data);

    if ( !counter->trace_enable )  return;

    uint8_t lock = record->Get<uint8_t>(event_class, 0);
    uint8_t size = record->Get<uint8_t>(event_class, 1);

    if ((size > 4) && (lock == 0)) // STM
    {
        assert((size % 4) == 0);
        counter->value += size / 4;
    }
    else
        ++counter->value;
}

/////////////////////////////////////////////////////////////////////////////

void
CoreTracer::TraceINST(const MTI::EventClass *event_class,
                      const struct MTI::EventRecord *record)
{
    bool found_error = false;
    for(vector<CacheTracer *>::const_iterator it = caches.begin();
        it != caches.end(); ++it)
    {
        if (((*it)->SelfcheckActive()) &&
            (*it)->SelfCheckError())
        {
            found_error = true;
        }
    }
    if (found_error)
    {
        uint32_t pc = last_inst_record->Get<uint32_t>(event_class, 0);
        uint32_t opcode = last_inst_record->Get<uint32_t>(event_class, 1);
        uint8_t  iset = last_inst_record->Get<uint8_t>(event_class, 2);
        uint64_t inst_count = last_inst_record->Get<uint64_t>(event_class, 3);

        printf("#%"PRIu64": %08x %08x %s\n\n", inst_count, pc,
               opcode, iset ? "Thumb" : "ARM");
    }
    memcpy(last_inst_record, record, inst_record_size);
}

void
CoreTracer::TraceINST_thunk(void * user_data,
                            const MTI::EventClass *event_class,
                            const struct MTI::EventRecord *record)
{
    CoreTracer *that = reinterpret_cast<CoreTracer *>(user_data);
    that->TraceINST(event_class, record);
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class CacheStatisticsPlugin :
    public PluginInstance
{
public:
    virtual CAInterface * ObtainInterface(if_name_t    ifName,
                                          if_rev_t     minRev,
                                          if_rev_t *   actualRev);

    CacheStatisticsPlugin(const char *instance_name,
                          uint32_t num_parameters,
                          CADIParameterValue_t *parameter_values);

    ~CacheStatisticsPlugin();

    /** This is to associate a plugin with a simulation instance. Exactly one simulation must be registered. */
    virtual CADIReturn_t RegisterSimulation(CAInterface *simulation);

    // This is called before the plugin .dll/.so is unloaded and should allow the plugin to do it's cleanup.
    virtual void Release();

    virtual const char *GetName() const;

public: // methods
    string instance_name;

    bool selfcheck;
    
    typedef map<string, CoreTracer *> CoresT;
    CoresT cores;

    CADIReturn_t Error(const char *message) const;
};

CAInterface * 
CacheStatisticsPlugin::ObtainInterface(if_name_t    ifName,
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


CacheStatisticsPlugin::CacheStatisticsPlugin(const char *instance_name_,
                                             uint32_t /*number_parameters*/,
                                             CADIParameterValue_t * /*parameter_values*/) :
    instance_name(instance_name_),
    selfcheck(false)
{
}

CacheStatisticsPlugin::~CacheStatisticsPlugin()
{
    for(CoresT::iterator it = cores.begin();
        it != cores.end(); ++it)
    {
        delete (it->second);
    }
}

CADIReturn_t
CacheStatisticsPlugin::Error(const char *message) const
{
    fprintf(stderr, "Error: Trace plugin %s: %s\n", instance_name.c_str(), message);
    return CADI_STATUS_GeneralError;
}

CADIReturn_t
CacheStatisticsPlugin::RegisterSimulation(CAInterface *ca_interface)
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

    CoreTracer *current_core = 0;
    for(SystemTraceInterface::TraceComponentIndex i=0; i < num_trace_components; ++i)
    {
        const char *component_name = sti->GetComponentTracePath(i);

        // Get Component Trace Interface of component:
        ca_interface = sti->GetComponentTrace(i);
        ComponentTraceInterface *cti = ca_interface->ObtainPointer<ComponentTraceInterface>();
        if (!cti)
        {
            Error("Unable to get component trace for component '%s'.\n");
            continue;
        }
        if (cti->GetTraceSource("CORE_INFO") != 0)
        {
            current_core = new CoreTracer(component_name, cti, selfcheck);
            cores.insert(make_pair(component_name, current_core));
            printf("Registering core statistics for component '%s'.\n", component_name);
        }
        else if (cti->GetTraceSource("CACHE_INFO") != 0)
        {
            assert(current_core);
            CacheTracer *new_tracer = new CacheTracer(component_name, cti, selfcheck,
                                                      current_core);
            current_core->RegisterCache(new_tracer);
            printf("Registering cache statistics for component '%s'.\n", component_name);
        }
    }

    for(CoresT::const_iterator it = cores.begin();
        it != cores.end(); ++it)
    {
        it->second->Connect();
        it->second->PrintInfo();
    }

    return CADI_STATUS_OK;
}

// This is called before the plugin .dll/.so is unloaded and should allow the plugin to do it's cleanup.
void 
CacheStatisticsPlugin::Release()
{
    delete this;
}

const char *
CacheStatisticsPlugin::GetName() const
{
    return instance_name.c_str();
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

    virtual const char *GetType() const { return "CacheStatisticsPlugin"; }
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

enum {
    PARAM_CHECK_LS_COUNTS
};

static CADIParameterInfo_t parameters[] = 
{
    CADIParameterInfo_t(PARAM_CHECK_LS_COUNTS,
                        "check-ls-counts",
                        CADI_PARAM_BOOL,
                        "Compare the Load/Store counts and the cache access count sums.",
                        false,
                        0, 1, 1,
                        "")
};

#define NUM_PARAMS (sizeof(parameters)/sizeof(CADIParameterInfo_t))

uint32_t
ThePluginFactory::GetNumberOfParameters()
{
    return NUM_PARAMS;
}


CADIReturn_t
ThePluginFactory::GetParameterInfos(CADIParameterInfo_t *parameter_info_list)
{
    if (!parameter_info_list)
        return CADI_STATUS_IllegalArgument;
    
    std::copy( parameters, &parameters[NUM_PARAMS], parameter_info_list);
    return CADI_STATUS_OK;
}


CAInterface *
ThePluginFactory::Instantiate(const char *instance_name,
                              uint32_t    number_of_parameters,
                              CADIParameterValue_t *param_values)
{
    return static_cast<PluginInstance *>(new CacheStatisticsPlugin(instance_name, number_of_parameters, param_values));
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

// End of file CacheStatisticsPlugin.cpp
