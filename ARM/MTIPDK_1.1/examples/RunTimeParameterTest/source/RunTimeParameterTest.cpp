/*!
 *  \file   RunTimeParameterTest.cpp
 *  \brief  Trace Plugin to demonstrate the use of runtime parameters
 *  \date   Copyright ARM Limited 2009 All Rights Reserved.
 *  
 */

#include "sg/IncludeMeFirst.h"
#include "hostconf/zinttypes.h"

#include "MTI/PluginInterface.h"
#include "MTI/PluginFactory.h"
#include "MTI/PluginInstance.h"
#include "MTI/ModelTraceInterface.h"
#include "MTI/ParameterInterface.h"

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

using namespace eslapi;
using namespace MTI;

class RunTimeParameterTest :
    public PluginInstance,
    public ParameterInterface
{
public:
    virtual CAInterface * ObtainInterface(if_name_t    ifName,
                                          if_rev_t     minRev,
                                          if_rev_t *   actualRev);

    RunTimeParameterTest(const char *instance_name,
                         uint32_t num_parameters,
                         CADIParameterValue_t *parameter_values);
    ~RunTimeParameterTest();
    
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

private:
    std::string instance_name;

    std::string string_param;
    int int_param;
    bool bool_param;

    CADIReturn_t SetParametersInternal(uint32_t num_parameters,
                                               CADIParameterValue_t *parameters);
};

CAInterface * 
RunTimeParameterTest::ObtainInterface(if_name_t    ifName,
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


RunTimeParameterTest::RunTimeParameterTest(const char *instance_name_,
                                           uint32_t number_parameters,
                                           CADIParameterValue_t *parameter_values) :
    instance_name(instance_name_),
    int_param(0),
    bool_param(false)
{
    if (number_parameters > 0)
    {
        puts("Parameters set in instantiation:\n");
        SetParametersInternal(number_parameters, parameter_values);
        puts("Instantiation finished\n\n");
    }
}

RunTimeParameterTest::~RunTimeParameterTest()
{
}

CADIReturn_t
RunTimeParameterTest::RegisterSimulation(CAInterface * /*ca_interface*/)
{
    // Return some error to keep the model from running:
    return CADI_STATUS_OK;
}

// This is called before the plugin .dll/.so is unloaded and should allow the plugin to do it's cleanup.
void 
RunTimeParameterTest::Release()
{
    delete this;
}

const char *
RunTimeParameterTest::GetName() const
{
    return instance_name.c_str();
}

const unsigned int num_parameters = 3;

typedef enum
{
    PARAM_ID_STRING,
    PARAM_ID_INT,
    PARAM_ID_BOOL
} MyParameterIDs;

static CADIParameterInfo_t parameters[num_parameters] = 
{
    CADIParameterInfo_t(PARAM_ID_STRING,
                        "string",
                        CADI_PARAM_STRING,
                        "A string runtime parameter.",
                        true,
                        0, 0, 0,
                        "default"),
    
    CADIParameterInfo_t(PARAM_ID_INT,
                        "integer",
                        CADI_PARAM_INT,
                        "An integer runtime parameter",
                        true,
                        0, 1, 0,
                        ""),
    
    CADIParameterInfo_t(PARAM_ID_BOOL,
                        "bool",
                        CADI_PARAM_BOOL,
                        "A bool runtime parameter",
                        true,
                        0, 1, 0,
                        "")
};

CADIReturn_t
RunTimeParameterTest::GetParameterInfos(uint32_t startIndex,
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
RunTimeParameterTest::GetParameterInfo(const char *parameterName,
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
RunTimeParameterTest::GetParameterValues(uint32_t /*parameterCount*/,
                                    uint32_t* /*actualNumOfParamsRead*/,
                                    CADIParameterValue_t* /*paramValuesOut*/)
{
    return CADI_STATUS_CmdNotSupported;
}
    
CADIReturn_t
RunTimeParameterTest::SetParameterValues(uint32_t parameterCount,
                                         CADIParameterValue_t* parameter_values,
                                         CADIFactoryErrorMessage_t* /*error*/)
{
    if (!parameter_values)
        return CADI_STATUS_IllegalArgument;

    CADIReturn_t status = SetParametersInternal(parameterCount, parameter_values);
    putchar('\n');
    return status;
}

CADIReturn_t
RunTimeParameterTest::SetParametersInternal(uint32_t parameterCount, CADIParameterValue_t *parameter_values)
{
    for(uint32_t i = 0; i < parameterCount; ++i)
    {
        CADIParameterValue_t &parameter = parameter_values[i];
        printf("Setting parameter #%u: %s to ",
               parameter.parameterID,
               parameters[parameter.parameterID].name);
        switch(parameter.dataType)
        {
        case CADI_PARAM_STRING:
            printf("\"%s\"", parameter.stringValue);
            break;

        case CADI_PARAM_BOOL:
            printf("%s", parameter.intValue ? "true" : "false");
            break;

        case CADI_PARAM_INT:
            printf("%"PRIu64, parameter.intValue);
            break;

        default:
            printf("Invalid type");
        }
        putchar('\n');
        fflush(stdout);

        switch(parameter.parameterID)
        {
        case PARAM_ID_STRING:
            string_param = parameter.stringValue;
            break;

        case PARAM_ID_INT:
            int_param = int(parameter.intValue);
            break;

        case PARAM_ID_BOOL:
            bool_param = (parameter.intValue != 0);
            break;
        }
    }

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

    virtual const char *GetType() const { return "RunTimeParameterTest"; }
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
    return static_cast<PluginInstance *>(new RunTimeParameterTest(instance_name, number_of_parameters, param_values));
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

// End of file RunTimeParameterTest.cpp
