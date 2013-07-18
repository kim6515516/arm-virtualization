/*!
 * \file    DirectedConnector.h
 * \brief   Base class for handling directed connector behaviour.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * Define a non-templated base class for directed connectors.
 */

// THIS FILE IS GENERATED FROM DirectedConnector.hxx

#ifndef DIRECTEDCONNECTORBASE_H
#define DIRECTEDCONNECTORBASE_H

#include "sg/ConnectorBase.h"

namespace sg {

class DirectedConnectorBase : public virtual ConnectorBase
{
 public:
    /*! The direction that behaviour propagates FROM. */
    enum Direction { Master, Slave};

protected:
    typedef std::list<DirectedConnectorBase *> ConnectorList;

    /*! From which direction do we propagate behaviours? */
    Direction direction;
    
    /*! Who are we connected to? */
    ConnectorList slaves;

    /*! Who has connected to us? */
    ConnectorList masters;

    BindingList precall_bindings;
    BindingList postcall_bindings;

private:
    BindingList exported_bindings;
    bool exported_bindings_valid;

    void rebuildBindings();

protected:
    /*! Do we propagate behaviours from our source connector. */
    bool local_only;

    ConnectorList &getSourceConnectorList();
    ConnectorList &getTargetConnectorList();

    virtual void propagateNewBinding(const Binding &new_binding);

    virtual void propagateRemovedBinding(const Binding &old_binding);

    bool checkedConnectTo(DirectedConnectorBase *target);

    bool checkedDisconnectFrom(DirectedConnectorBase *target);

    void recomputeBindings();
    void importsChanged();

    DirectedConnectorBase(Direction dir);

    void disconnectNeighbours();

    BindingList& getActiveBehaviourList();

public:
    /*! Print a debug log of the connector's contents. */
    void dump();

    /*! Disconnected from our peer group cleanly. */
    virtual void disconnect();

    /*! Make sure we're disconnected when we die. */
    ~DirectedConnectorBase();

    void setLocalOnly(bool local);

    DirectedConnectorBase * asDirectedConnector();
};


// Predeclare a class that can be specified on the function signature.
// This will be specialised for each length of arg list, to derive from
// the corresponding DirectedConnectorN class.
template <typename Signature>
class SlaveConnector;
    
template <typename Signature>
class MasterConnector;

} // namespace sg

#include "sg/ConcreteConnectorBase.h"

namespace sg {

//N=0
template< class RetType=void >
class DirectedConnector0 : public ConcreteConnectorBase0< RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector0 < RetType> ConnectorType;

public:
    DirectedConnector0(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R>
class SlaveConnector< R (  ) >
    : public DirectedConnector0 < R >
{
 public:
    typedef DirectedConnector0 < R > BaseType;
    SlaveConnector()
        : DirectedConnector0 < R >(BaseType::Slave)
    {
    }
            
};

template<typename R>
class MasterConnector< R (  ) >
    : public DirectedConnector0 < R >
{
 public:
    typedef DirectedConnector0 < R > BaseType;
    MasterConnector()
        : DirectedConnector0 < R >(BaseType::Master)
    {
    }
            
};

//N=1
template< class Param1, class RetType=void >
class DirectedConnector1 : public ConcreteConnectorBase1< Param1, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector1 < Param1, RetType> ConnectorType;

public:
    DirectedConnector1(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1>
class SlaveConnector< R ( Param1 ) >
    : public DirectedConnector1 < Param1, R >
{
 public:
    typedef DirectedConnector1 < Param1, R > BaseType;
    SlaveConnector()
        : DirectedConnector1 < Param1, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1>
class MasterConnector< R ( Param1 ) >
    : public DirectedConnector1 < Param1, R >
{
 public:
    typedef DirectedConnector1 < Param1, R > BaseType;
    MasterConnector()
        : DirectedConnector1 < Param1, R >(BaseType::Master)
    {
    }
            
};

//N=2
template< class Param1, class Param2, class RetType=void >
class DirectedConnector2 : public ConcreteConnectorBase2< Param1, Param2, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector2 < Param1, Param2, RetType> ConnectorType;

public:
    DirectedConnector2(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2>
class SlaveConnector< R ( Param1, Param2 ) >
    : public DirectedConnector2 < Param1, Param2, R >
{
 public:
    typedef DirectedConnector2 < Param1, Param2, R > BaseType;
    SlaveConnector()
        : DirectedConnector2 < Param1, Param2, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2>
class MasterConnector< R ( Param1, Param2 ) >
    : public DirectedConnector2 < Param1, Param2, R >
{
 public:
    typedef DirectedConnector2 < Param1, Param2, R > BaseType;
    MasterConnector()
        : DirectedConnector2 < Param1, Param2, R >(BaseType::Master)
    {
    }
            
};

//N=3
template< class Param1, class Param2, class Param3, class RetType=void >
class DirectedConnector3 : public ConcreteConnectorBase3< Param1, Param2, Param3, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector3 < Param1, Param2, Param3, RetType> ConnectorType;

public:
    DirectedConnector3(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3>
class SlaveConnector< R ( Param1, Param2, Param3 ) >
    : public DirectedConnector3 < Param1, Param2, Param3, R >
{
 public:
    typedef DirectedConnector3 < Param1, Param2, Param3, R > BaseType;
    SlaveConnector()
        : DirectedConnector3 < Param1, Param2, Param3, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3>
class MasterConnector< R ( Param1, Param2, Param3 ) >
    : public DirectedConnector3 < Param1, Param2, Param3, R >
{
 public:
    typedef DirectedConnector3 < Param1, Param2, Param3, R > BaseType;
    MasterConnector()
        : DirectedConnector3 < Param1, Param2, Param3, R >(BaseType::Master)
    {
    }
            
};

//N=4
template< class Param1, class Param2, class Param3, class Param4, class RetType=void >
class DirectedConnector4 : public ConcreteConnectorBase4< Param1, Param2, Param3, Param4, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector4 < Param1, Param2, Param3, Param4, RetType> ConnectorType;

public:
    DirectedConnector4(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4>
class SlaveConnector< R ( Param1, Param2, Param3, Param4 ) >
    : public DirectedConnector4 < Param1, Param2, Param3, Param4, R >
{
 public:
    typedef DirectedConnector4 < Param1, Param2, Param3, Param4, R > BaseType;
    SlaveConnector()
        : DirectedConnector4 < Param1, Param2, Param3, Param4, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4>
class MasterConnector< R ( Param1, Param2, Param3, Param4 ) >
    : public DirectedConnector4 < Param1, Param2, Param3, Param4, R >
{
 public:
    typedef DirectedConnector4 < Param1, Param2, Param3, Param4, R > BaseType;
    MasterConnector()
        : DirectedConnector4 < Param1, Param2, Param3, Param4, R >(BaseType::Master)
    {
    }
            
};

//N=5
template< class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=void >
class DirectedConnector5 : public ConcreteConnectorBase5< Param1, Param2, Param3, Param4, Param5, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector5 < Param1, Param2, Param3, Param4, Param5, RetType> ConnectorType;

public:
    DirectedConnector5(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5 ) >
    : public DirectedConnector5 < Param1, Param2, Param3, Param4, Param5, R >
{
 public:
    typedef DirectedConnector5 < Param1, Param2, Param3, Param4, Param5, R > BaseType;
    SlaveConnector()
        : DirectedConnector5 < Param1, Param2, Param3, Param4, Param5, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5 ) >
    : public DirectedConnector5 < Param1, Param2, Param3, Param4, Param5, R >
{
 public:
    typedef DirectedConnector5 < Param1, Param2, Param3, Param4, Param5, R > BaseType;
    MasterConnector()
        : DirectedConnector5 < Param1, Param2, Param3, Param4, Param5, R >(BaseType::Master)
    {
    }
            
};

//N=6
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=void >
class DirectedConnector6 : public ConcreteConnectorBase6< Param1, Param2, Param3, Param4, Param5, Param6, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, RetType> ConnectorType;

public:
    DirectedConnector6(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6 ) >
    : public DirectedConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R >
{
 public:
    typedef DirectedConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R > BaseType;
    SlaveConnector()
        : DirectedConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6 ) >
    : public DirectedConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R >
{
 public:
    typedef DirectedConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R > BaseType;
    MasterConnector()
        : DirectedConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R >(BaseType::Master)
    {
    }
            
};

//N=7
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType=void >
class DirectedConnector7 : public ConcreteConnectorBase7< Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType> ConnectorType;

public:
    DirectedConnector7(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) >
    : public DirectedConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R >
{
 public:
    typedef DirectedConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R > BaseType;
    SlaveConnector()
        : DirectedConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) >
    : public DirectedConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R >
{
 public:
    typedef DirectedConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R > BaseType;
    MasterConnector()
        : DirectedConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R >(BaseType::Master)
    {
    }
            
};

//N=8
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType=void >
class DirectedConnector8 : public ConcreteConnectorBase8< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType> ConnectorType;

public:
    DirectedConnector8(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) >
    : public DirectedConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R >
{
 public:
    typedef DirectedConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R > BaseType;
    SlaveConnector()
        : DirectedConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) >
    : public DirectedConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R >
{
 public:
    typedef DirectedConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R > BaseType;
    MasterConnector()
        : DirectedConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R >(BaseType::Master)
    {
    }
            
};

//N=9
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class RetType=void >
class DirectedConnector9 : public ConcreteConnectorBase9< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType> ConnectorType;

public:
    DirectedConnector9(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9 ) >
    : public DirectedConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R >
{
 public:
    typedef DirectedConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R > BaseType;
    SlaveConnector()
        : DirectedConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9 ) >
    : public DirectedConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R >
{
 public:
    typedef DirectedConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R > BaseType;
    MasterConnector()
        : DirectedConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R >(BaseType::Master)
    {
    }
            
};

//N=10
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class RetType=void >
class DirectedConnector10 : public ConcreteConnectorBase10< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType> ConnectorType;

public:
    DirectedConnector10(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10 ) >
    : public DirectedConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R >
{
 public:
    typedef DirectedConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R > BaseType;
    SlaveConnector()
        : DirectedConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10 ) >
    : public DirectedConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R >
{
 public:
    typedef DirectedConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R > BaseType;
    MasterConnector()
        : DirectedConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R >(BaseType::Master)
    {
    }
            
};

//N=11
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class RetType=void >
class DirectedConnector11 : public ConcreteConnectorBase11< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType> ConnectorType;

public:
    DirectedConnector11(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11 ) >
    : public DirectedConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R >
{
 public:
    typedef DirectedConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R > BaseType;
    SlaveConnector()
        : DirectedConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11 ) >
    : public DirectedConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R >
{
 public:
    typedef DirectedConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R > BaseType;
    MasterConnector()
        : DirectedConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R >(BaseType::Master)
    {
    }
            
};

//N=12
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class RetType=void >
class DirectedConnector12 : public ConcreteConnectorBase12< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType> ConnectorType;

public:
    DirectedConnector12(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12 ) >
    : public DirectedConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R >
{
 public:
    typedef DirectedConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R > BaseType;
    SlaveConnector()
        : DirectedConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12 ) >
    : public DirectedConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R >
{
 public:
    typedef DirectedConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R > BaseType;
    MasterConnector()
        : DirectedConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R >(BaseType::Master)
    {
    }
            
};

//N=13
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class RetType=void >
class DirectedConnector13 : public ConcreteConnectorBase13< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType> ConnectorType;

public:
    DirectedConnector13(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13 ) >
    : public DirectedConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R >
{
 public:
    typedef DirectedConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R > BaseType;
    SlaveConnector()
        : DirectedConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13 ) >
    : public DirectedConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R >
{
 public:
    typedef DirectedConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R > BaseType;
    MasterConnector()
        : DirectedConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R >(BaseType::Master)
    {
    }
            
};

//N=14
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class RetType=void >
class DirectedConnector14 : public ConcreteConnectorBase14< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType> ConnectorType;

public:
    DirectedConnector14(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14 ) >
    : public DirectedConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R >
{
 public:
    typedef DirectedConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R > BaseType;
    SlaveConnector()
        : DirectedConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14 ) >
    : public DirectedConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R >
{
 public:
    typedef DirectedConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R > BaseType;
    MasterConnector()
        : DirectedConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R >(BaseType::Master)
    {
    }
            
};

//N=15
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, class RetType=void >
class DirectedConnector15 : public ConcreteConnectorBase15< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType >, public DirectedConnectorBase
{
    typedef DirectedConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType> ConnectorType;

public:
    DirectedConnector15(Direction dir) : DirectedConnectorBase(dir)
    {
    }
    
    virtual bool connectTo(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedConnectTo(static_cast<ConnectorType*>(directed_target));
    }

    virtual bool disconnectFrom(Connectable *target) {
        DirectedConnectorBase *directed_target = target->asDirectedConnector();
        if (directed_target == NULL) {
            return false;
        }
        return checkedDisconnectFrom(static_cast<ConnectorType*>(directed_target));
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15>
class SlaveConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15 ) >
    : public DirectedConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R >
{
 public:
    typedef DirectedConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R > BaseType;
    SlaveConnector()
        : DirectedConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R >(BaseType::Slave)
    {
    }
            
};

template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15>
class MasterConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15 ) >
    : public DirectedConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R >
{
 public:
    typedef DirectedConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R > BaseType;
    MasterConnector()
        : DirectedConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R >(BaseType::Master)
    {
    }
            
};


} // namespace sg

#endif
