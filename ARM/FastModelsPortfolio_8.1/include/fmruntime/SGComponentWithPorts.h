 /*!
 * \file    SGComponentWithPorts.h
 * \brief   Component/Port infrastructure using Connectors
 * \date    Copyright 2005 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef SG_COMPONENT_WITH_PORTS_H
#define SG_COMPONENT_WITH_PORTS_H

#include <map>

#include "sg/SGPort.h"

#include "sg/SGComponentBase.h"
#include "sg/SGParams.h"

namespace eslapi
{
    class CAInterface;
}

namespace sg {

typedef std::map< std::string, eslapi::CAInterface* > CADIMap;

// Components are collections of named ports, and of other components
class ComponentWithPorts : public ComponentBase
{
private:
    std::string name;

    Node *parent;

    // at some point this might change to point to a sub-section
    // of a global parameter set
    Params params; // init/runtime parameters

    typedef std::map<std::string, Port*>  PortMap;
    typedef std::pair<std::string, Port*> PortEntry;

    typedef std::list<ComponentBase*> ComponentList;

    // nested components - should these be named?
    ComponentList components;

    // public ports.
    PortMap       ports;

    // locally registered CADI interfaces.
    CADIMap localCADI;

private:
    virtual void connectControlPorts(ComponentBase*) { }
    virtual void disconnectControlPorts(ComponentBase*) { }
    virtual void populateChildControlPort(CADIMap&, const std::string&) { }

protected:
    ComponentWithPorts(std::string const & name);

    /*! Publish a port so that external components can connect FROM it.
     *
     * \param name textual name for lookup
     * \param port port to add
     * \return true if port was added, false if there is a port with that name
     */
    bool publishMasterPort(const std::string& name, Port& port);

    /*! Publish a port so that external components can connect TO it.
     *
     * \param name textual name for lookup
     * \param port port to add
     * \return true if port was added, false if there is a port with that name
     */
    bool publishSlavePort(const std::string& name, Port& port);

    /*! Publish a port so that external components can connect to or from it.
     *
     * \param name textual name for lookup
     * \param port port to add
     * \return true if port was added, false if there is a port with that name
     */
    bool publishPeerPort(const std::string& name, Port& port);

    /*! Backwards compatibility. */
    bool addPort(const std::string& name_, Port& port_) {
        return publishPeerPort(name_, port_);
    }

    /*! Add an array of ports the list of named ports
     *
     * The ports will be named "name[0]", "name[1]" ... "name[size-1]"
     * Template type T is any subclass of Port.
     */
    template <typename T>
    bool addPortArray(const std::string& name_, T* array, unsigned int size) {
        return publishPeerPortArray(name_, array, size);
    }

    template <typename T>
    bool publishPeerPortArray(const std::string& name_, T* array, unsigned int size) {
        for (unsigned int i=0; i<size; ++i) {
            publishPeerPortIndex(name_, array[i], i);
        }
        return true;
    }

    template <typename T>
    bool publishMasterPortArray(const std::string& name_, T* array, unsigned int size) {
        for (unsigned int i=0; i<size; ++i) {
            publishMasterPortIndex(name_, array[i], i);
        }
        return true;
    }

    template <typename T>
    bool publishSlavePortArray(const std::string& name_, T* array, unsigned int size) {
        for (unsigned int i=0; i<size; ++i) {
            publishSlavePortIndex(name_, array[i], i);
        }
        return true;
    }

    /*! Publish an port for external bidirectional connection.
     *  The port will have a name of "name[n]" where n is the value of the
     *  index parameter.
     */
    bool publishPeerPortIndex(const std::string& name, Port& port, unsigned int index);

    /*! Publish an port for external components to connect FROM.
     *  The port will have a name of "name[n]" where n is the value of the
     *  index parameter.
     */
    bool publishMasterPortIndex(const std::string& name, Port& port, unsigned int index);

    /*! Publish an port for external components to connect TO.
     *  The port will have a name of "name[n]" where n is the value of the
     *  index parameter.
     */
    bool publishSlavePortIndex(const std::string& name, Port& port, unsigned int index);

    /*! Remove the port from the component. Note this will remove
     *  all registrations of the port
     *  \return true if one or more ports were removed
     */
    bool unpublishPort(Port& port);

    /*! Backwards compatibility. */
    bool removePort(Port& port) { return unpublishPort(port); }

    /*! Remove a port by name.
     *  Faster than the above
     *  \return the found port or NULL if no port was found
     */
    Port* unpublishPort(const std::string& name);

    /*! Remove an array of ports by name
     *
     */
    void unpublishPortArray(const std::string& name, unsigned int size);

public:
    /*! Default implementation of populateCADIMap that populates the
     *  map with the mxdi interface of this component and those of all
     *  subcomponents.
     */
    virtual void populateCADIMap(CADIMap &map, std::string const &prefix);

protected:
    /*! Add a named mxdi interface. The default mxdi interface should have
     *  a name ""
     */
    void addCADI(const std::string& name, eslapi::CAInterface* cadi);

    eslapi::CAInterface* removeCADI(const std::string& name);

public:
    virtual ~ComponentWithPorts();

    /*! Get an abstract port by name
     *
     * \param name textual name of port added with addPort().
     * \return reference to port if found or reference to Component::NoPort.
     */
    Port& findPort(std::string const & name);

    /*! Get a port from a port array by name and index.
     *
     *  \param name textual name of port added with addPortArray().
     *  \param index index into port array, between 0 and size-1.
     *  \return reference to port if found, or reference to Component::NoPort.
     */
    Port& findPort(std::string const & name, int index);


    /*! Add a component to the list of 'sub' components
     *
     */
    void add(ComponentBase *c);

    void remove(ComponentBase *c);

    // apply parameter settings recursively
    void apply_params();

    virtual std::string getName() const { return name; }

    virtual std::string getClassName() const;

    virtual const Node * getParent() const { return parent; }
    virtual void setParent(Node *p) { parent = p; }
};

} // namespace sg

#endif // SG_COMPONENT_WITH_PORTS_H
