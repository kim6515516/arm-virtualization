/*!
 * \file    PeerConnector.h
 * \brief   Base class for handling peer connector behaviour.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * Define a non-templated base class for peer-to-peer connectors.
 */

// THIS FILE IS GENERATED FROM PeerConnector.hxx

#ifndef PEERCONNECTOR_H
#define PEERCONNECTOR_H

#include "sg/ConnectorBase.h"

namespace sg {


/*! Manage a single peer connector, in a graph of connectors.  The connection
 *  graph must be acyclic.
 *
 *  All connected connectors share a pooled BehaviourPeerGroup: when a new
 *  behaviour is bound to any of the connectors in the group, all other
 *  connectors see it.
 *
 *  When a connection is made between two graphs, the BehaviourPeerGroups and
 *  pooled behaviours are merged.
 *
 *  When a connection is broken it creates two separate graphs; a new
 *  BehaviourPeerGroup is created, and everything on one side is moved
 *  from the old group into the new one.
 */
class PeerConnectorBase : public virtual ConnectorBase
{
protected:
    typedef std::list<PeerConnectorBase *> PeerList;
   
    /*! Handle collection of peers. */
    class BehaviourPeerGroup;
   
    /*! Who we're directly connected to. */
    PeerList peers;
    
    /*! Container for all connectors within a graph. */
    BehaviourPeerGroup *group;

    /*! Construct an empty connector, with no connections. */
    PeerConnectorBase();


private:
    void leaveGroup();
    void connectToGroup(BehaviourPeerGroup* group);
    void constructGroup();
    void destroyGroup();

protected:
    /*! Handle joining two connector groups together:
     *  will only be called if target is same connector
     *  type as this.
     */
    bool checkedConnectTo(PeerConnectorBase *target);

    /*! Break a connection to a neighbouring connector. */
    bool checkedDisconnectFrom(PeerConnectorBase *target);

    void disconnectPeers();
    
    void removePeer(PeerConnectorBase*);
    void addPeer(PeerConnectorBase*);


    BindingList& getActiveBehaviourList();

protected: // Implement base-class behaviour.

    /*! Add a new binding to the group's list. */
    virtual void propagateNewBinding(const Binding &new_binding);

    /*! Remove a binding from the group's list. */
    virtual void propagateRemovedBinding(const Binding &old_binding);

public:
    /*! Print a debug log of the connector's contents. */
    void dump();

    /*! Disconnected from our peer group cleanly. */
    virtual void disconnect();

    /*! Make sure we're disconnected when we die. */
    ~PeerConnectorBase();
    
    
    /*! Allow BehaviourPeerGroup to find out who we're connected to. */
    const PeerList &getPeers();

    PeerConnectorBase *asPeerConnector();
};

// Predeclare a class that can be specified on the function signature.
// This will be specialised for each length of arg list, to derive from
// the corresponding PeerConnectorN class.
template <typename Signature>
class PeerConnector;

} // namespace sg


#include "sg/ConcreteConnectorBase.h"

namespace sg {

//N=0
template< class RetType=void >
class PeerConnector0 : public ConcreteConnectorBase0< RetType >, public PeerConnectorBase
{
    typedef PeerConnector0 < RetType> ConnectorType;

public:

    ~PeerConnector0() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R>
class PeerConnector< R (  ) >
    : public PeerConnector0 < R >
{
 public:
    typedef PeerConnector0 < R > BaseType;
};

//N=1
template< class Param1, class RetType=void >
class PeerConnector1 : public ConcreteConnectorBase1< Param1, RetType >, public PeerConnectorBase
{
    typedef PeerConnector1 < Param1, RetType> ConnectorType;

public:

    ~PeerConnector1() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1>
class PeerConnector< R ( Param1 ) >
    : public PeerConnector1 < Param1, R >
{
 public:
    typedef PeerConnector1 < Param1, R > BaseType;
};

//N=2
template< class Param1, class Param2, class RetType=void >
class PeerConnector2 : public ConcreteConnectorBase2< Param1, Param2, RetType >, public PeerConnectorBase
{
    typedef PeerConnector2 < Param1, Param2, RetType> ConnectorType;

public:

    ~PeerConnector2() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2>
class PeerConnector< R ( Param1, Param2 ) >
    : public PeerConnector2 < Param1, Param2, R >
{
 public:
    typedef PeerConnector2 < Param1, Param2, R > BaseType;
};

//N=3
template< class Param1, class Param2, class Param3, class RetType=void >
class PeerConnector3 : public ConcreteConnectorBase3< Param1, Param2, Param3, RetType >, public PeerConnectorBase
{
    typedef PeerConnector3 < Param1, Param2, Param3, RetType> ConnectorType;

public:

    ~PeerConnector3() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3>
class PeerConnector< R ( Param1, Param2, Param3 ) >
    : public PeerConnector3 < Param1, Param2, Param3, R >
{
 public:
    typedef PeerConnector3 < Param1, Param2, Param3, R > BaseType;
};

//N=4
template< class Param1, class Param2, class Param3, class Param4, class RetType=void >
class PeerConnector4 : public ConcreteConnectorBase4< Param1, Param2, Param3, Param4, RetType >, public PeerConnectorBase
{
    typedef PeerConnector4 < Param1, Param2, Param3, Param4, RetType> ConnectorType;

public:

    ~PeerConnector4() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4>
class PeerConnector< R ( Param1, Param2, Param3, Param4 ) >
    : public PeerConnector4 < Param1, Param2, Param3, Param4, R >
{
 public:
    typedef PeerConnector4 < Param1, Param2, Param3, Param4, R > BaseType;
};

//N=5
template< class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=void >
class PeerConnector5 : public ConcreteConnectorBase5< Param1, Param2, Param3, Param4, Param5, RetType >, public PeerConnectorBase
{
    typedef PeerConnector5 < Param1, Param2, Param3, Param4, Param5, RetType> ConnectorType;

public:

    ~PeerConnector5() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5 ) >
    : public PeerConnector5 < Param1, Param2, Param3, Param4, Param5, R >
{
 public:
    typedef PeerConnector5 < Param1, Param2, Param3, Param4, Param5, R > BaseType;
};

//N=6
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=void >
class PeerConnector6 : public ConcreteConnectorBase6< Param1, Param2, Param3, Param4, Param5, Param6, RetType >, public PeerConnectorBase
{
    typedef PeerConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, RetType> ConnectorType;

public:

    ~PeerConnector6() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6 ) >
    : public PeerConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R >
{
 public:
    typedef PeerConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R > BaseType;
};

//N=7
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType=void >
class PeerConnector7 : public ConcreteConnectorBase7< Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType >, public PeerConnectorBase
{
    typedef PeerConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType> ConnectorType;

public:

    ~PeerConnector7() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) >
    : public PeerConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R >
{
 public:
    typedef PeerConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R > BaseType;
};

//N=8
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType=void >
class PeerConnector8 : public ConcreteConnectorBase8< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType >, public PeerConnectorBase
{
    typedef PeerConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType> ConnectorType;

public:

    ~PeerConnector8() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) >
    : public PeerConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R >
{
 public:
    typedef PeerConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R > BaseType;
};

//N=9
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class RetType=void >
class PeerConnector9 : public ConcreteConnectorBase9< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType >, public PeerConnectorBase
{
    typedef PeerConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType> ConnectorType;

public:

    ~PeerConnector9() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9 ) >
    : public PeerConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R >
{
 public:
    typedef PeerConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R > BaseType;
};

//N=10
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class RetType=void >
class PeerConnector10 : public ConcreteConnectorBase10< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType >, public PeerConnectorBase
{
    typedef PeerConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType> ConnectorType;

public:

    ~PeerConnector10() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10 ) >
    : public PeerConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R >
{
 public:
    typedef PeerConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R > BaseType;
};

//N=11
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class RetType=void >
class PeerConnector11 : public ConcreteConnectorBase11< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType >, public PeerConnectorBase
{
    typedef PeerConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType> ConnectorType;

public:

    ~PeerConnector11() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11 ) >
    : public PeerConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R >
{
 public:
    typedef PeerConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R > BaseType;
};

//N=12
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class RetType=void >
class PeerConnector12 : public ConcreteConnectorBase12< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType >, public PeerConnectorBase
{
    typedef PeerConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType> ConnectorType;

public:

    ~PeerConnector12() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12 ) >
    : public PeerConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R >
{
 public:
    typedef PeerConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R > BaseType;
};

//N=13
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class RetType=void >
class PeerConnector13 : public ConcreteConnectorBase13< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType >, public PeerConnectorBase
{
    typedef PeerConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType> ConnectorType;

public:

    ~PeerConnector13() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13 ) >
    : public PeerConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R >
{
 public:
    typedef PeerConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R > BaseType;
};

//N=14
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class RetType=void >
class PeerConnector14 : public ConcreteConnectorBase14< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType >, public PeerConnectorBase
{
    typedef PeerConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType> ConnectorType;

public:

    ~PeerConnector14() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14 ) >
    : public PeerConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R >
{
 public:
    typedef PeerConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R > BaseType;
};

//N=15
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, class RetType=void >
class PeerConnector15 : public ConcreteConnectorBase15< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType >, public PeerConnectorBase
{
    typedef PeerConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType> ConnectorType;

public:

    ~PeerConnector15() { disconnect(); }

    virtual bool connectTo(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(peer_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        PeerConnectorBase *peer_target = target->asPeerConnector();
        if (peer_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(peer_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15>
class PeerConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15 ) >
    : public PeerConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R >
{
 public:
    typedef PeerConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R > BaseType;
};


} // namespace sg

#include "sg/namespace.h"

#endif
