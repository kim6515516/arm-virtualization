/*
 * global_interface_dumper.h - dummy component dumping information provided by
 * the global interfaces
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include <eslapi/CADI.h>
#include <eslapi/CADIFactory.h>
#include <eslapi/CAInterfaceRegistryIF.h>
#include <MTI/ModelTraceInterface.h>
#include <sg/SGComponentRegistry.h>
#include <scx/scx.h> // for scx_get_global_interface()

#include "global_interface_dumper.h"
#include "cadi_client.h"
#include "SimpleCADI.h"

/* Helper class for dump_global_interfaces(): list all interfaces below a node
 * (if possible) */
class my_component_lister: public sg::ComponentRegistry::ComponentListVisitor
{
public:
    my_component_lister(int indent_): indent(indent_) {}
    
    virtual void visitComponent(const char *componentName, eslapi::CAInterface *componentInterface)
    {
        if (*componentName == '*')
            printf("%*s%s:\n", indent, "", componentName);
        else
            printf("%*scomponent '%s':\n", indent, "", componentName);
        eslapi::CAInterfaceRegistryIF *ireg = componentInterface->ObtainPointer<eslapi::CAInterfaceRegistryIF>();
        if (ireg)
        {
            my_interface_lister interface_lister(indent + 2);
            ireg->VisitInterfaceList(&interface_lister);
        }        
        else
        {
            printf("%*s(does not allow to list available interfaces, ok)\n", indent + 2, "");
        }
    }

private:
    /* Helper class */
    class my_interface_lister: public eslapi::CAInterfaceRegistryIF::InterfaceListVisitor
    {
    public:
        my_interface_lister(int indent_): indent(indent_) {}
        
        virtual void VisitInterface(eslapi::if_name_t ifName, eslapi::if_rev_t ifRev)
        {
            printf("%*sinterface '%s' (rev=%u)\n", indent, "", ifName, ifRev);
        }
        
    private:    
        int indent;
    };
    
    int indent;
};

/* Dump all global interfaces available */
void dump_global_interfaces()
{
    printf("=== Global Interfaces ===========================================================================\n");
    // get global interface
    eslapi::CAInterface *globalInterface = scx::scx_get_global_interface();
    if (!globalInterface)
    {
        printf("dump_global_interfaces(): error: scx::scx_get_global_interface() returned NULL\n");
        return;                
    }
    
    // try to list all global interfaces
    // (the only relevant interface on this level is sg.ComponentRegistry, even if it can not be listed)
    my_component_lister top_interface_lister(0);
    top_interface_lister.visitComponent("*scx::scx_get_global_interface()", globalInterface);

    // get global component registry
    sg::ComponentRegistry *compReg = globalInterface->ObtainPointer<sg::ComponentRegistry>();
    if (!compReg)
    {
        printf("dump_global_interfaces(): error: cannot get global sg::ComponentRegistry interface\n");
        return;                
    }
    
    // list all components and their interfaces
    my_component_lister component_lister(4);
    compReg->visitComponentList(&component_lister);    
}

/* Dump all MTI trace sources */
void dump_mti_trace_sources()
{
    printf("=== MTI trace sources ===========================================================================\n");
    // get global interface
    eslapi::CAInterface *globalInterface = scx::scx_get_global_interface();    
    
    // get access to MTI interface (SystemTraceInterface)
    const char *errorMessage = "(no error)";
    MTI::SystemTraceInterface *mti = sg::obtainComponentInterfacePointer<MTI::SystemTraceInterface>(globalInterface, "mtiRegistry", &errorMessage);
    if (!mti)
    {
        printf("dump_mti_trace_sources(): error: cannot get SystemTraceInterface for component mtiRegistry: %s\n", errorMessage);
        return;
    }
        
    // for all components offering trace
    MTI::SystemTraceInterface::TraceComponentIndex numComps = mti->GetNumOfTraceComponents();
    for (MTI::SystemTraceInterface::TraceComponentIndex i = 0; i < numComps; i++)
    {
        const char *componentName = mti->GetComponentTracePath(i);
        eslapi::CAInterface *compif = mti->GetComponentTrace(i);
        MTI::ComponentTraceInterface *cti = compif->ObtainPointer<MTI::ComponentTraceInterface>();
        if (!cti)
        {
            printf("dump_mti_trace_sources(): error: cannot get ComponentTraceInterface of component %s\n", componentName);
            return;
        }
        
        // for all trace sources
        MTI::SourceIndex numSources = cti->GetNumOfTraceSources();
        for (MTI::SourceIndex j = 0; j < numSources; j++)
        {
            MTI::TraceSource *traceSource = cti->GetTraceSource(j);
            printf("%s: %s (%s, fields={", componentName, traceSource->GetName(), traceSource->GetDescription());
            
            // for all fields in the trace source
            MTI::FieldIndex numFields = traceSource->GetNumFields();
            for (MTI::FieldIndex k = 0; k < numFields; k++)
            {
                printf("%s%s", k ? "," : "", traceSource->GetField(k)->GetName());
            }
            
            printf("})\n");
        }           
    }
}

/* Dump all CADI targets and additional information */
void dump_scadi_targets()
{
    printf("=== SCADI targets ================================================================================\n");
    // get global interface
    eslapi::CAInterface *globalInterface = scx::scx_get_global_interface();    

    // get access to CADISimulation
    const char *errorMessage = "(no error)";
    eslapi::CADISimulation *sim = sg::obtainComponentInterfacePointer<eslapi::CADISimulation>(globalInterface, "cadiSimulation", &errorMessage);
    if (!sim)
    {
        printf("dump_cadi_targets(): error: cannot get CADISimulation interface for component cadiSimulation: %s\n",
               errorMessage);
        return;
    }
                
    // print list of all CADI targets
    uint32_t chunkSize = 100; // get N targets at once (this is not a limit, just a granularity)
    eslapi::CADITargetInfo_t *targetInfos = new eslapi::CADITargetInfo_t[chunkSize]; // do not allocate this on the stack, these things are huge
    printf("%-30s %-7s %-20s %-12s %s\n", "Instance Name", "Version", "Target Name", "Type", "Executes Software");
    printf("-------------------------------------------------------------------------------------------------\n");
    for (uint32_t currentStartIndex = 0;; currentStartIndex += chunkSize)
    {
        uint32_t actualTargets = 0;
        if (sim->GetTargetInfos(currentStartIndex, chunkSize, targetInfos, &actualTargets) != eslapi::CADI_STATUS_OK)
        {
            printf("dump_cadi_targets(): error: CADISimulation::GetTargetInfos(): error while getting targets from simulation\n");
            delete[] targetInfos;
            return;
        }
        
        for(uint32_t i = 0; i < actualTargets; i++)
        {
            printf("%-30s v%-6s %-20s %-12s %d\n", targetInfos[i].instanceName, targetInfos[i].version, targetInfos[i].targetName, targetInfos[i].componentType, targetInfos[i].executesSoftware);
            
            // get access to the SCADI interface of this target
            eslapi::CAInterface *compif = sim->GetTarget(targetInfos[i].id);
            if (!compif)
            {
                printf("dump_cadi_targets(): error: CADISimulation::GetTarget(%s) returned NULL\n", targetInfos[i].instanceName);
                continue; // ignore targets which do not offer any interface               
            }

            // special case: for SCADI we cannot use the convenience function 'ObtainPointer<>()' because for SCADI 
            // we re-use the CADI type with a different interface name (eslapi.SCADI2 instead of eslapi.CADI2)
            eslapi::CADI *scadi = static_cast<eslapi::CADI*>(compif->ObtainInterface("eslapi.SCADI2", 0, 0)); 
            SimpleCADI *simple_scadi = new SimpleCADI(scadi);

#if 1
            // dump R0-R15 and their values if they exist for the target
            for (int j = 0; j < 16; j++)
            {
                char regName[10];
                sprintf(regName, "R%d", j);
                if (simple_scadi->hasRegister(regName))
                    printf("  %-3s = 0x%08llX\n", regName, (long long unsigned)simple_scadi->regRead(regName));
            }
#else
            // alternatively: dump all registers and their values
            std::vector<std::string> registerList = simple_scadi->getRegisterNames();
            for (size_t j = 0; j < registerList.size(); j++)
                    printf("register '%s' = 0x%08llX\n", registerList[j].c_str(), (long long unsigned)simple_scadi->regRead(registerList[j]));
#endif
            delete simple_scadi;
        }
        
        if (actualTargets < chunkSize)
            break;
    }
    delete[] targetInfos;
}

void start_cadi_client(void)
{
    printf("=== CADI targets ================================================================================\n");
    uint32_t target_num = 1;

#ifdef WIN32
    DWORD threadID; // Win32 thread ID
    HANDLE thread = CreateThread(NULL, 16*1024*1024, (LPTHREAD_START_ROUTINE)cadi_thread_fxn,
                                 (void *) target_num, 0, &threadID);
    if (thread == NULL){
        printf("ERROR; CreateThread failed\n");
        exit(-1);
    }
#else
    pthread_t cadi_thread;
    int rc = pthread_create(&cadi_thread, NULL, cadi_thread_fxn, (void *) target_num);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
#endif
}

/* Constructor */
global_interface_dumper::global_interface_dumper(sc_core::sc_module_name name):
sc_core::sc_module(name)
{        
}
    
/* Called just before the simulation starts */
void global_interface_dumper::start_of_simulation()
{
    dump_global_interfaces();
    dump_mti_trace_sources();
    dump_scadi_targets();
    start_cadi_client();
}

