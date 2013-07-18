/*!
 * \file    SGBasicComponentFactory.h
 * \brief   Implementation of ComponentFactory interface.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_BASICCOMPONENTFACTORY_H
#define ARM_SG_BASICCOMPONENTFACTORY_H

#include <string>
#include <vector>

#include "SGComponentFactory.h"
#include "SGTargetInfo.h"

namespace sg {

//! Basic implementation of the ComponentFactory interface.
/*! Provides support for managing a list of target info instances.
 */
class BasicComponentFactory : public ComponentFactory {
    //! List of target info instances.
    std::vector<TargetInfo> infos;

 protected: // Helper methods for use by subclasses.

    //! Add the selected TargetInfo to the end of the infos list.
    /*! The list of targets exposed by this factory will be extended
     *  to include a copy of the given target, with the given instance
     *  path.
     */
    void publishTarget(TargetInfo const &p, std::string instance_path);

    //! Add all the TargetInfo from the selected ComponentFactory to
    //! the end of the infos list, excluding any instance named "".
    /*! Each target will have the given prefix added to the start of its
     *  instance name, separated with a '.'.
     */
    void publishComponent(ComponentFactory *f, std::string prefix, bool publish_all = false);

 public: // Implement the ComponentFactory interface.
    
    //! Return the number of targets in our list.
    virtual unsigned int getTargetCount() { 
        return (unsigned int)infos.size();
    }

    //! Return meta-data for a given debug target by index.
    virtual TargetInfo * getTargetInfo(unsigned int index) {
        if (index >= getTargetCount()) {
            return NULL;
        }
        return &infos[index];
    }

    //! Return meta-data for a given debug target, identified by its
    //! instance path.
    virtual TargetInfo * getTargetInfo(std::string const & instance_path) {
        std::vector<TargetInfo>::iterator pos;
        for (pos = infos.begin();
             pos != infos.end();
             ++pos)
        {
            if ((*pos).instance_path == instance_path) {
                return &(*pos);
            }
        }
        return NULL;
    }
};

} // namespace sg

#endif // ARM_SG_BASICCOMPONENTFACTORY_H
