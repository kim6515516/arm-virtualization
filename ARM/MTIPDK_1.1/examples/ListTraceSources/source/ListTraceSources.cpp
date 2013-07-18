/*!
 *  \file   ListTraceSources.cpp
 *  \brief  Trace Plugin to list all trace sources of all components a model provides.
 *  \date   Copyright ARM Limited 2009 All Rights Reserved.
 *  
 */

#include "MTI/PluginInterface.h"
#include "MTI/PluginFactory.h"
#include "MTI/PluginInstance.h"
#include "MTI/ModelTraceInterface.h"

#include "eslapi/CADI.h"
#include "eslapi/CADITypes.h"

#include <string>
#include <algorithm> // std::copy
#include <cassert>
#include <string.h>
#include <errno.h>
#include <cstdio>

#ifdef SG_MODEL_BUILD
    #include "builddata.h"
    #define PLUGIN_VERSION FULL_VERSION_STRING
#else
    #define PLUGIN_VERSION "unreleased"
#endif

using namespace eslapi;
using namespace MTI;

enum
{
    PARAM_ID_FILENAME
};

class ListTraceSources :
    public PluginInstance
{
public:
    ListTraceSources(const char *instance_name,
                     uint32_t number_of_parameters,
                     eslapi::CADIParameterValue_t *parameter_values);

    ~ListTraceSources();

    virtual CAInterface * ObtainInterface(if_name_t    ifName,
                                          if_rev_t     minRev,
                                          if_rev_t *   actualRev);

    virtual eslapi::CADIReturn_t RegisterSimulation(eslapi::CAInterface *mti);
    virtual void Release();

    virtual const char *GetName() const;

private:
    void Error(const char *);

    void ListSources(ModelTraceInterface *mti);

    std::string instance_name;
    std::string filename;
    FILE *file;
};

ListTraceSources::ListTraceSources(const char *instance_name_,
                                   uint32_t number_of_parameters,
                                   eslapi::CADIParameterValue_t *parameter_values) :
    instance_name(instance_name_),
    file(0)
{
    file = stdout;
    for(uint32_t i = 0; i < number_of_parameters; ++i)
    {
        CADIParameterValue_t &parameter = parameter_values[i];

        switch(parameter.parameterID)
        {
        case PARAM_ID_FILENAME:
            filename = parameter.stringValue;
            break;
        }
    }
    if (!filename.empty())
    {
        file = fopen(filename.c_str(), "w");
        if (!file)
        {
            fprintf(stderr, "Error opening file \"%s\": %s\n", 
                    filename.c_str(),
                    strerror(errno));
            
            file = stdout;
        }
    }
}

ListTraceSources::~ListTraceSources()
{
    if (file == stdout)
        fflush(file);
    else
        fclose(file);
}

CAInterface * 
ListTraceSources::ObtainInterface(if_name_t    ifName,
                                  if_rev_t     minRev,
                                  if_rev_t *   actualRev)
{
    if((strcmp(ifName,IFNAME()) == 0) && // if someone is asking for the matching interface
       (minRev <= IFREVISION())) // and the revision of this interface implementation is
        // at least what is being asked for
    {
        if (actualRev) // make sure this is not a NULL pointer
            *actualRev = IFREVISION();
        return this;
    }

    if((strcmp(ifName, CAInterface::IFNAME()) == 0) &&
       minRev <= CAInterface::IFREVISION())
    {
        if (actualRev != NULL)
            *actualRev = CAInterface::IFREVISION();
        return this;
    }
    return NULL;
}

void
ListTraceSources::Error(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
}

void
ListTraceSources::ListSources(ModelTraceInterface *mti)
{
    assert(mti);

#ifndef MTI_TRACEINTERFACE_V0_H
    fprintf(file, "Component is of type \"%s\"\n", mti->GetComponentType());
    fprintf(file, "Version is \"%s\"\n", mti->GetComponentVersion());
#endif

    SourceIndex num_sources = mti->GetNumOfTraceSources();
    fprintf(file, "#Sources: %u\n", num_sources);                    

    for(SourceIndex i = 0; i < num_sources; ++i)
    {
        const TraceSource *source = mti->GetTraceSource(i);
        assert(source);
        {
            fprintf(file, "\nSource %s (%s)\n", source->GetName(), source->GetDescription());
            
            for(FieldIndex j=0; j < source->GetNumFields(); ++j)
            {
                const EventFieldType *field = source->GetField(j);
                assert(field);
                const static char *type2string[6] =
                    {
                        "UNSIGNED_INT",
                        "SIGNED_INT",
                        "BOOL",
                        "ENUM",
                        "FLOAT",
                        "STRING"
                    };
                fprintf(file, "    Field %s type:MTI_%s size:%u",
                        field->GetName(), type2string[field->GetType()], field->GetSize());
#ifndef MTI_TRACEINTERFACE_V0_H
                if (field->GetSize() == 0)
                {
                    fprintf(file, " max_size:%u", field->GetMaxSize());
                }
#endif
                fprintf(file, " (%s)\n", field->GetDescription());
#ifndef MTI_TRACEINTERFACE_V0_H
                for(EventFieldType::EnumIndex ei=0; ei < field->GetNumOfEnumConstants(); ++ei)
                {
                    EventFieldType::EnumConstant ec = field->GetEnumConstant(ei);
                    fprintf(file, "        0x%x = %s\n", ec.first, ec.second);
                }
#endif                
            }
        }
    }
}

eslapi::CADIReturn_t
ListTraceSources::RegisterSimulation(CAInterface *ca_interface)
{
    if (!ca_interface)
    {
        Error("Trace plugin received CAInterface NULL pointer.");
        return CADI_STATUS_GeneralError;
    }
    CAInterface *caif = 0;

#ifndef MTI_TRACEINTERFACE_V0_H
    // new style interface:
    SystemTraceInterface *sys_if = ca_interface->ObtainPointer<SystemTraceInterface>();
    if (sys_if != 0)
    {
        for(SystemTraceInterface::TraceComponentIndex tci=0; tci < sys_if->GetNumOfTraceComponents(); ++tci)
        {
            // get some info about the target from target features (just to be able to display it)
            CADITargetFeatures_t features;
            caif = sys_if->GetComponentTrace(tci);
            CAInterface *cadi_caif = 0;
            if ((cadi_caif = caif->ObtainInterface(CADI::IFNAME(),
                                                   CADI::IFREVISION(), 0)) != 0)
            {
                eslapi::CADI *cadi;
                cadi = static_cast<CADI *>(cadi_caif);
                cadi->CADIXfaceGetFeatures(&features);
            }            
            
            // get ComponentTraceInterface and display trace sources
            ComponentTraceInterface *cti = caif->ObtainPointer<ComponentTraceInterface>();
            if (cti)
            {
                fprintf(file, "Component (%d) providing trace: %s (%s, %s)\n", tci, sys_if->GetComponentTracePath(tci), features.targetName, features.targetVersion);
                fputs("=============================================================================\n", file);
                ListSources(cti);
                putc('\n', file);
            }
        }
    }
#else
    ModelTraceInterface *mti = ca_interface->ObtainPointer<ModelTraceInterface>();
    if (mti != 0)
    {
        ListSources(mti);
    }    
#endif
    else
    {
        Error("Plugin could not get valid MTI pointer.");
        return CADI_STATUS_GeneralError;
    }

    // exit now
    // When using the ListTraceSources plugin users only want to see the list of trace sources which is printed on startup.
    // The user does not want the simulation to run, so we just print a message and exit here.
    printf("ListTraceSources: Listing successful. Exiting now.\n");
    printf("(This will exit/terminate the executable this plugin was loaded into.)\n");
    exit(0);
}

void
ListTraceSources::Release()
{
    delete this;
}

const char *
ListTraceSources::GetName() const
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

    virtual eslapi::CADIReturn_t GetParameterInfos(eslapi::CADIParameterInfo_t *parameter_info_list);

    virtual CAInterface *Instantiate(const char *instance_name,
                                     uint32_t number_of_parameters,
                                     eslapi::CADIParameterValue_t *parameter_values);

    virtual void Release();

    virtual const char *GetType() const { return "ListTraceSources"; }
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

static CADIParameterInfo_t parameters[] = 
{
    CADIParameterInfo_t(PARAM_ID_FILENAME,
                        "file",
                        CADI_PARAM_STRING,
                        "File to write list of trace sources to. Default is to write to the console.",
                        false,
                        0, 0, 0,
                        "")
};


uint32_t
ThePluginFactory::GetNumberOfParameters()
{
    return sizeof(parameters) / sizeof(CADIParameterInfo_t);
}


eslapi::CADIReturn_t
ThePluginFactory::GetParameterInfos(eslapi::CADIParameterInfo_t *parameter_info_list)
{
    if (!parameter_info_list)
        return CADI_STATUS_IllegalArgument;
    
    std::copy( parameters, &parameters[GetNumberOfParameters()], parameter_info_list);
    return CADI_STATUS_OK;
}


CAInterface *
ThePluginFactory::Instantiate(const char * instance_name,
                              uint32_t number_of_parameters,
                              eslapi::CADIParameterValue_t *parameter_values)
{
    return new ListTraceSources(instance_name, number_of_parameters, parameter_values);
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

// End of file ListTraceSources.cpp
