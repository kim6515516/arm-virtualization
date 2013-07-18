/*!
 * \file    SimpleConnector.h
 * \brief   Simple test connector class with no propagation rules.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * A connector type that doesn't propagate locally-bound behaviour.
 */

// THIS FILE IS GENERATED FROM SimpleConnector.hxx
#ifndef SIMPLECONNECTOR_H
#define SIMPLECONNECTOR_H

#include "sg/ConcreteConnectorBase.h"
#include <iostream>

namespace sg {

class SimpleConnectorBase : public virtual ConnectorBase
{

protected:
    virtual void propagateNewBinding(const Binding &new_binding) {
        (void)new_binding;
        updateInvocableBehaviour();
    }

    virtual void propagateRemovedBinding(const Binding &new_binding) {
        (void)new_binding;
        updateInvocableBehaviour();
    }

    ConnectorBase::BindingList& getActiveBehaviourList()
    {
        return local_bindings;
    }

    bool checkedConnectTo(ConnectorBase *target) {
        // Ignore connections.
        (void)target;
        return true;
    }

    bool checkedDisconnectFrom(ConnectorBase *target) {
        // Ignore connections.
        (void)target;
        return true;
    }

    virtual void disconnect() {
    }

    virtual void dump() {
        std::cout << "Simple Connector: " << getHierarchicalName() << std::endl;
    }
};


// Predeclare a class that can be specified on the function signature.
// This will be specialised for each length of arg list, to derive from
// the corresponding SimpleConnectorN class.
template <typename Signature>
class SimpleConnector;

//N=0

template< class RetType=void >
class SimpleConnector0 : public SimpleConnectorBase, public ConcreteConnectorBase0< RetType >
{
    typedef SimpleConnector0 < RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R>
class SimpleConnector< R (  ) >
    : public SimpleConnector0 < R >
{
 public:
    typedef SimpleConnector0 < R > BaseType;
};

//N=1

template< class Param1, class RetType=void >
class SimpleConnector1 : public SimpleConnectorBase, public ConcreteConnectorBase1< Param1, RetType >
{
    typedef SimpleConnector1 < Param1, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1>
class SimpleConnector< R ( Param1 ) >
    : public SimpleConnector1 < Param1, R >
{
 public:
    typedef SimpleConnector1 < Param1, R > BaseType;
};

//N=2

template< class Param1, class Param2, class RetType=void >
class SimpleConnector2 : public SimpleConnectorBase, public ConcreteConnectorBase2< Param1, Param2, RetType >
{
    typedef SimpleConnector2 < Param1, Param2, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2>
class SimpleConnector< R ( Param1, Param2 ) >
    : public SimpleConnector2 < Param1, Param2, R >
{
 public:
    typedef SimpleConnector2 < Param1, Param2, R > BaseType;
};

//N=3

template< class Param1, class Param2, class Param3, class RetType=void >
class SimpleConnector3 : public SimpleConnectorBase, public ConcreteConnectorBase3< Param1, Param2, Param3, RetType >
{
    typedef SimpleConnector3 < Param1, Param2, Param3, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3>
class SimpleConnector< R ( Param1, Param2, Param3 ) >
    : public SimpleConnector3 < Param1, Param2, Param3, R >
{
 public:
    typedef SimpleConnector3 < Param1, Param2, Param3, R > BaseType;
};

//N=4

template< class Param1, class Param2, class Param3, class Param4, class RetType=void >
class SimpleConnector4 : public SimpleConnectorBase, public ConcreteConnectorBase4< Param1, Param2, Param3, Param4, RetType >
{
    typedef SimpleConnector4 < Param1, Param2, Param3, Param4, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4>
class SimpleConnector< R ( Param1, Param2, Param3, Param4 ) >
    : public SimpleConnector4 < Param1, Param2, Param3, Param4, R >
{
 public:
    typedef SimpleConnector4 < Param1, Param2, Param3, Param4, R > BaseType;
};

//N=5

template< class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=void >
class SimpleConnector5 : public SimpleConnectorBase, public ConcreteConnectorBase5< Param1, Param2, Param3, Param4, Param5, RetType >
{
    typedef SimpleConnector5 < Param1, Param2, Param3, Param4, Param5, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5 ) >
    : public SimpleConnector5 < Param1, Param2, Param3, Param4, Param5, R >
{
 public:
    typedef SimpleConnector5 < Param1, Param2, Param3, Param4, Param5, R > BaseType;
};

//N=6

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=void >
class SimpleConnector6 : public SimpleConnectorBase, public ConcreteConnectorBase6< Param1, Param2, Param3, Param4, Param5, Param6, RetType >
{
    typedef SimpleConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6 ) >
    : public SimpleConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R >
{
 public:
    typedef SimpleConnector6 < Param1, Param2, Param3, Param4, Param5, Param6, R > BaseType;
};

//N=7

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType=void >
class SimpleConnector7 : public SimpleConnectorBase, public ConcreteConnectorBase7< Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType >
{
    typedef SimpleConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7 ) >
    : public SimpleConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R >
{
 public:
    typedef SimpleConnector7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, R > BaseType;
};

//N=8

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType=void >
class SimpleConnector8 : public SimpleConnectorBase, public ConcreteConnectorBase8< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType >
{
    typedef SimpleConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8 ) >
    : public SimpleConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R >
{
 public:
    typedef SimpleConnector8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, R > BaseType;
};

//N=9

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class RetType=void >
class SimpleConnector9 : public SimpleConnectorBase, public ConcreteConnectorBase9< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType >
{
    typedef SimpleConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9 ) >
    : public SimpleConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R >
{
 public:
    typedef SimpleConnector9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, R > BaseType;
};

//N=10

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class RetType=void >
class SimpleConnector10 : public SimpleConnectorBase, public ConcreteConnectorBase10< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType >
{
    typedef SimpleConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10 ) >
    : public SimpleConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R >
{
 public:
    typedef SimpleConnector10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, R > BaseType;
};

//N=11

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class RetType=void >
class SimpleConnector11 : public SimpleConnectorBase, public ConcreteConnectorBase11< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType >
{
    typedef SimpleConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11 ) >
    : public SimpleConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R >
{
 public:
    typedef SimpleConnector11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, R > BaseType;
};

//N=12

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class RetType=void >
class SimpleConnector12 : public SimpleConnectorBase, public ConcreteConnectorBase12< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType >
{
    typedef SimpleConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12 ) >
    : public SimpleConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R >
{
 public:
    typedef SimpleConnector12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, R > BaseType;
};

//N=13

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class RetType=void >
class SimpleConnector13 : public SimpleConnectorBase, public ConcreteConnectorBase13< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType >
{
    typedef SimpleConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13 ) >
    : public SimpleConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R >
{
 public:
    typedef SimpleConnector13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, R > BaseType;
};

//N=14

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class RetType=void >
class SimpleConnector14 : public SimpleConnectorBase, public ConcreteConnectorBase14< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType >
{
    typedef SimpleConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14 ) >
    : public SimpleConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R >
{
 public:
    typedef SimpleConnector14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, R > BaseType;
};

//N=15

template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, class RetType=void >
class SimpleConnector15 : public SimpleConnectorBase, public ConcreteConnectorBase15< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType >
{
    typedef SimpleConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType> ConnectorType;

    virtual bool connectTo(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedConnectTo(t);
    }

    virtual bool disconnectFrom(Connectable *target) {
        ConnectorType *t = dynamic_cast< ConnectorType *>(target);
        if (t == NULL) {
            return false;
        }

        return checkedDisconnectFrom(t);
    }
};

// Allow the use of pretty signatures
template<typename R, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15>
class SimpleConnector< R ( Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15 ) >
    : public SimpleConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R >
{
 public:
    typedef SimpleConnector15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, R > BaseType;
};


} // namespace sg

#endif
