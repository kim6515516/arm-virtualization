/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   CADIParameterProxy.h
 *  \brief  CADI Proxy derived class for CADI parameter manipulation
 *  \date   Copyright ARM Limited 2002 All Rights Reserved.
 *          Copyright ARM Limited 2013 All Rights Reserved.
 *  
 */

#ifndef CADIPARAMETERPROXY_H
#define CADIPARAMETERPROXY_H


#include "CADI2Proxy.h"

class ParameterFilter;

class CADIParameterProxy : public eslapi::CADI2Proxy
{
public:
    CADIParameterProxy(eslapi::CADI *cadi, const ParameterFilter *filter) : eslapi::CADI2Proxy(cadi), m_filter(filter) { }

    virtual eslapi::CADIReturn_t CADIGetParameters(uint32_t startIndex, uint32_t desiredNumOfParams, uint32_t *actualNumOfParams, eslapi::CADIParameterInfo_t *params);
    virtual eslapi::CADIReturn_t CADISetParameters(uint32_t parameterCount, eslapi::CADIParameterValue_t *parameters, eslapi::CADIFactoryErrorMessage_t *error);

private:
    // this filter alters the CADI client's view of the proxied
    // component's parameters and is transparent to both of them
    const ParameterFilter   *m_filter;
};


#endif

