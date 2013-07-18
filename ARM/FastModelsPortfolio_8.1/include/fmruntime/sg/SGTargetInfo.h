/*!
 * \file    SGTargetInfo.h
 * \brief   Meta-data about a target.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_TARGETINFO_H
#define ARM_SG_TARGETINFO_H

#include <string>

#include "eslapi/CADITypes.h"

namespace sg {

//! Meta-data about a debug target within a simulation.
/*! This provides information about one of the debug targets within a
 *  simulation, without needing to instantiate the simulation.  It
 *  encapsulates the information needed to describe an CADI target,
 *  including its configurable parameters.
 *
 *  Each target has a name which uniquely identifies it within the
 *  context of a given component.  When one component publishes the
 *  targets from a subcomponent, it can change this name, or it can
 *  prefix it.
 */
struct TargetInfo {
    //! Describe the CADI properties of the target.
    eslapi::CADITargetInfo_t const * cadi_target_info;

    //! Give the size of the parameter_info array.
    unsigned int parameter_count;

    //! Information about the configurable parameters that can be
    //!  given at start-up time.
    eslapi::CADIParameterInfo_t const * parameter_info;

    //! Identify this target amongst its peers within a component.
    std::string instance_path;
};

} // namespace sg

#endif // ARM_SG_TARGETINFO_H
