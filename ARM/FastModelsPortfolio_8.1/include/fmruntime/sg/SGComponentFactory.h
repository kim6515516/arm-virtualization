/*!
 * \file    SGComponentFactory.h
 * \brief   Meta-data about a target.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_COMPONENTFACTORY_H
#define ARM_SG_COMPONENTFACTORY_H

#include <string>

#include "sg/SGParams.h"

namespace sg {

// Prototype declarations.
struct TargetInfo;
class SimulationContext;
class ComponentBase;
class Params;

//! An object representing the constructor for a single type of component.
/*! A component instance can provide zero to many debug targets.  The
 *  ComponentFactory provides a mechanism to list information about these
 *  targets (using the TargetInfo structure) without instantiating a
 *  component.
 *
 *  The factory also provides a mechanism for instantiating components,
 *  with a given set of parameters.
 */
class ComponentFactory {
 protected:
    //! Users can't delete a ComponentFactory, as it might have other users.
    virtual ~ComponentFactory() { }

 public: // Interface to be implemented by a subclass.
    //! Dereference a component factory - possibly allowing it to be deleted.
    virtual void dereference() = 0;

    //! How many debug targets will be provided by this component?
    virtual unsigned int getTargetCount() = 0;

    //! Return meta-data for a given debug target by index.
    virtual TargetInfo * getTargetInfo(unsigned int index) = 0;

    //! Return meta-data for a given debug target, identified by its
    //! instance path.
    virtual TargetInfo * getTargetInfo(std::string const & instance_path) = 0;

    //! Create an instance of this factory's component.
    virtual ComponentBase * instantiate(std::string const & instance_name,
                                        SimulationContext * context,
                                        Params const & params) = 0;

    //! Helper function to instantiate a component with an empty param list.
    ComponentBase * instantiate(std::string const & instance_name,
                                SimulationContext * context);
};

} // namespace sg

#endif // ARM_SG_COMPONENTFACTORY_H
