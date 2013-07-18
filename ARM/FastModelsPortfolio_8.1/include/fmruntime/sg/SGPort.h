 /*!
 * \file    SGPort.h
 * \brief   Collection of connectors used to represent an interface
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_PORT_H
#define ARM_SG_PORT_H

#include "sg/SGNode.h"
#include "sg/DirectedConnector.h"
#include "sg/PeerConnector.h"

#include <map>
#include <string>

namespace sg {
using namespace fastdelegate;

// Macros to make defining ports a little easier

#define declare_behaviour(name, signature)  \
    sg::PeerConnector< signature > name

#define declare_peer_behaviour(name, signature)  \
    sg::PeerConnector< signature > name

#define declare_slave_behaviour(name, signature)  \
    sg::SlaveConnector< signature > name

#define declare_master_behaviour(name, signature)  \
    sg::MasterConnector< signature > name

#define define_behaviour(name) \
    addConnector(#name, &(name))
    
#define bind_method(port, name, method, object) \
    (port).name.bind_behaviour((object), (method))

#define unbind_method(port, name, method, object) \
    (port).name.unbind_behaviour((object), (method))

#define bind_default_method(port, name, method, object) \
    (port).name.bind_default_behaviour((object), (method))

#define unbind_default_method(port, name, method, object) \
    (port).name.unbind_default_behaviour((object), (method))


#define declare_vector_behaviour(name, count, signature)        \
    sg::PeerConnector< signature > name[(count)]

#define declare_vector_slave_behaviour(name, count, signature)  \
    sg::SlaveConnector< signature > name[(count)]

#define declare_vector_master_behaviour(name, count, signature) \
    sg::MasterConnector< signature > name[(count)]

#define define_vector_behaviour(name, count)                    \
    do {                                                        \
        for (int t20110523=0; t20110523<(count); ++t20110523)   \
        {                                                       \
            std::ostringstream os20110523;                      \
            os20110523 << #name << "[" << t20110523 << "]";     \
            addConnector(os20110523.str(), &(name));            \
        }                                                       \
    }                                                           \
    while(0)            


#define bind_vector_method(port, name, count, method, object)              \
    do {                                                                   \
        for (int i=0; i < (count); ++i)                                    \
            (port)[i].name.bind_vector_behaviour(i, (object), (method)); \
    } while (0)                                                            \

#define unbind_vector_method(port, name, count, method, object)               \
    do {                                                                      \
        for (int i=0; i < (count); ++i)                                       \
            (port)[(i)].name.unbind_vector_behaviour(i, (object), (method));\
    } while (0)                                                               \


/*! A port is a collection of named connectors.
 *  Typically, a port is used as an interface to some functionality
 *  in an object that is implemented by 'behaviour' connectors.
 *  Ports can be connected, which in turn connects connectors of the same
 *  name and signature.
 */
class Port : public Connectable
{
    // Copying or assigning a port is undefined
    Port(const Port&);
    Port& operator=(const Port&);

protected:
    //*! \todo: this should be a set rather than a map
    typedef std::map<std::string, Connectable*>  ConnectorMap;
    typedef std::pair<std::string, Connectable*> ConnectorEntry;
    typedef std::list<Connectable *> ConnectorList;

    ConnectorMap connectors;

    void addConnector(std::string name, Connectable *c);

public:
    Port();

    // All ports declare these behaviours. They are called whenever anything that
    // might affect the connection graphs is about to or has changed.
    PeerConnector< void () > portConnectionChanging;
    PeerConnector< void () > portConnectionChanged;

    virtual ~Port();

    virtual bool connectTo(Connectable *p);
    virtual bool disconnectFrom(Connectable *p);

    // disconnect without knowing what we're connected to
    virtual void disconnect();

    bool connectTo(Port &p);
    bool disconnectFrom(Port &p);

    bool operator>>(Port& p) { return connectTo(p); }

    void dump();
    Port *asPort();
};


// An empty port that can't be connected to another port
class NullPort : public Port
{
public:
    NullPort() {}

    virtual bool connectTo(Connectable*) {
        return false;
    }
};

} // namespace sg

#endif // ARM_SG_PORT_H
