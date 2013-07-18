/*!
 * \file    ParameterFilter.h
 * \date    Copyright ARM Limited 2002 All Rights Reserved.
 *
 */

#ifndef PARAMETERFILTER_H
#define PARAMETERFILTER_H


#include <string>
#include <map>
#include <vector>

#include "eslapi/CADITypes.h"
#include "sg/SGParams.h"


class ParameterFilter
{
public:
    // ensures that this class will be abstract
    virtual ~ParameterFilter() = 0;

    bool isEmpty() const { return ovrd_params.empty(); }

    // filters the list of parameters to be published
    virtual void filter(const eslapi::CADIParameterInfo_t *in, uint32_t count, const std::string &instance_path, std::vector<eslapi::CADIParameterInfo_t> &out) const;

    // overrides the default value of the parameter 'param_name'
    virtual void override_default(sg::Params::ParamRef param, const std::string &param_name) const;

    // truncates the value of the parameter if it lies outside the [min, max] range
    virtual void enforce_min_max(sg::Params::ParamRef param, const std::string &param_name) const;
    virtual void enforce_min_max(eslapi::CADIParameterValue_t *paramVal) const;

protected:
    typedef std::map<std::string, eslapi::CADIParameterInfo_t> ParamInfoMap;
    typedef ParamInfoMap::const_iterator ParamInfoConstIterator;

    // this map stores the overridden meta-data of the a subcomponent's parameters
    ParamInfoMap ovrd_params;

    // these bitmasks are used to recognize whether a parameter has been fixed or is being forwarded
    // the are OR-ed with the parameter's id
    static const uint32_t PARAMETERFILTER_FIXED     = 0x80000000;
    static const uint32_t PARAMETERFILTER_FORWARDED = 0x40000000;
};


inline ParameterFilter::~ParameterFilter() { }


#endif

