 /*!
 * \file    SGComponentBase.h
 * \brief   Abstract Component base-class
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_COMPONENTBASE_H
#define ARM_SG_COMPONENTBASE_H

#include "sg/SGNode.h"
#include "sg/SGPort.h"

namespace sg {

// Components are collections of named ports, and of other components
class ComponentBase : public Node
{
public:
    /*! A reference to this is returned from findPort when no port is found. */
    static NullPort NoPort;

public:
    /*! Get an abstract port by name 
     *
     * \param name textual name of port added with addPort().
     * \return reference to port if found or reference to Component::NoPort.
     */
    virtual Port& findPort(std::string const & name) = 0;

    /*! Get a port from a port array by name and index.
     *
     *  \param name textual name of port added with addPortArray().
     *  \param index index into port array, between 0 and size-1.
     *  \return reference to port if found, or reference to Component::NoPort.
     */
    virtual Port& findPort(std::string const & name, int index) = 0;
};

} // namespace sg

#endif // ARM_SG_COMPONENTBASE_H
