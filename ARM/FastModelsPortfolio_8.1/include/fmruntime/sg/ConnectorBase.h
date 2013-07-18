/*!
 * \file    ConnectorBase.h
 * \brief   Base class for handling abstract connector behaviour.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * Define a policy-neutral, non-templated base class for connectors.
 * The templatisation occurs in the subclass and supporting classes
 * defined in ConcreteConnectorBase.h.  Connection policy is defined
 * in PeerConnector.h and DirectedConnector.h
 */

#ifndef CONNECTORBASE_H
#define CONNECTORBASE_H

#include "sg/FastDelegate.h"    // Could use separate out FastDelegateMemento.h
#include <list>
#include <string>

#include "sg/SGNode.h"
#include "sg/IndexedDelegateMemento.h"

namespace sg {

// Forward declarations for pseudo- dynamic multiple dispatch
class Port;
class PeerConnectorBase;
class DirectedConnectorBase;

/*! A generic connectable/disconnectable thing. */
class Connectable : public Node
{
 protected:
    Node *parent;
    std::string name;

    Connectable() : parent(NULL), name("(unused connector)") { }

 public:
    /*! Attach this connector to a remote connector, checking that it has
     *  exactly the same type.
     */
    virtual bool connectTo(Connectable *target) = 0;

    /*! Detach this connector from a remote connector, checking that it has
     *  exactly the same type.
     */
    virtual bool disconnectFrom(Connectable *target) = 0;

    /*! Disconnect this object from everything it is connected to.
     */
    virtual void disconnect() = 0;

    void setName(std::string const &n) { name = n; }
    virtual std::string getName() const { return name; }
    virtual std::string getClassName() const;
    virtual const Node * getParent() const { return parent; }
    virtual void setParent(Node *p) { parent = p; }

    virtual void dump() = 0;

    // Fake dynamic multiple dispatch
    virtual Port *asPort() { return NULL; }
    virtual PeerConnectorBase *asPeerConnector() { return NULL; }
    virtual DirectedConnectorBase *asDirectedConnector() { return NULL; }
};

#ifdef _MSC_VER
#pragma warning(disable:4250) // implementing a virtual function in one of two classes derived from a common virtual base.
#endif

/*! A base class for manipulating connectors without knowing about their
 *  connection policy or their templated invocation argument list.  At
 *  this level, all bindings are handled via generic DelegateMemento
 *  lists.
 *
 *  Connectors provide two lists of bindings: local bindings, and default
 *  bindings.  The local bindings can be exported to other connectors in
 *  a graph, according to a connection policy.  This may then generate a
 *  set of active bindings to be called when this connector is invoked.
 *  If the active bindings list is empty, then the connector's default
 *  bindings are called.
 *
 *  All concrete connector types inherit from ConnectorBase via two paths:
 *  one path manages the propagation rules (peer-to-peer or directed)
 *  on abstract delegate types; the other path provides support for the
 *  formal arguments and return types.
 *
 *  The latter is provided by the ConcreteConnectorBase templated class,
 *  which provides an invoke() method that will call all of the delegates
 *  in the active_binding_list, or, if that list is empty, the 
 *  default_bindings list.  The updateInvocableBehaviour() method is
 *  implemented in ConcreteConnectorBase, to precompute a delegate to
 *  handle the invoke method efficiently in the case where there is only
 *  one behaviour in the list.
 *
 *  The propagation rules are handled by implementing the virtual methods
 *  propagateNewBinding(), propagateRemovedBinding(), connectTo() and
 *  disconnectFrom().  These are called by
 *  the connectTo()/disconnectFrom() methods
 */ 
 class ConnectorBase : public Connectable
{
 protected:
    /*! Provide a local name for the type representing 'something that
     *  can be bound, copied, compared and invoked'.
     */
    typedef fastdelegate::DelegateMemento Binding;

    /*! A collection of bound delegates. */
    typedef std::list<Binding> BindingList;

    /*! A collection of pointers to delegates for vector behaviours. */
    typedef std::list<IndexedDelegateMemento *> IndexedBindingList;

 protected:
    /*! The list of active bindings to call when invoked.  If this list is
     *  not defined, or is empty, then the default bindings list will be
     *  invoked instead.
     */
    BindingList *active_behaviour_list;

    /*! Check whether the active behaviour list gets modified in the
     *  middle of an invocation.
     */
    bool active_list_locked;

    /*! The set of bindings attached to this connector. */
    BindingList local_bindings;

    /*! The set of vector behaviours attached to this connector. */
    IndexedBindingList local_indexed_bindings;

    /*! Default local behaviour bindings, to be invoked if there are no
     *  bindings in the peer group. 
     */
    BindingList default_bindings;

    ConnectorBase() : active_behaviour_list(NULL), active_list_locked(false)
    {
    }

 protected:
    /*! Allow the connection policy to take care of propagating a 
     *  newly-added local binding.
     */
    virtual void propagateNewBinding(const Binding &new_binding) = 0;

    /*! Allow the connection policy to take care of retracting a
     *  removed local binding.
     */
    virtual void propagateRemovedBinding(const Binding &old_binding) = 0;

    /*! Add a binding to the local bindings list, and pass it on to the
     *  connection propagation policy.  The concrete subclasses provide
     *  public versions of this method that take care of checking that the
     *  parameter lists match.
     */
    void addBinding(const Binding &new_binding);

    /*! Remove an existing binding. */
    void removeBinding(const Binding &old_binding);

    /*! Add a binding for a vector behaviour.  The templated subclass
     *  is responsible for capturing the vector behaviour as an
     *  IndexedDelegateMemento object so we can manipulate it.
     *  Note: We take ownership of the IndexedDelegateMemento object.
     */
    void addIndexedBinding(IndexedDelegateMemento *indexed_binding);

    /*! Delete a vector behaviour that matches the given binding. */
    void deleteIndexedBinding(IndexedDelegateMemento const &pattern);

    /*! Add a binding to the local defaults list, to be invoked if the
     *  active binding list is empty. */
    void addDefaultBinding(const Binding &new_binding);

    /*! Remove a default binding. */
    void removeDefaultBinding(const Binding &old_binding);

    /*! Test if this connector can be connected to the specified target
     * connector. 
     */
    bool isConnectable(const ConnectorBase* target);

 protected:
    /*! Make sure invocable_behaviour is the correct delegate for the
     *  current active_behaviour_list / default_behaviours.
     */
    virtual void updateInvocableBehaviour() = 0;

    virtual BindingList& getActiveBehaviourList() = 0;

 public:
    /*! Allow subclasses to destroy themselves cleanly. */
    virtual ~ConnectorBase();

    /*! Are there no active or default behaviours on this connector? */
    bool empty();

    /*! Inverted alias for empty() which is suitable for LISA code. LISA users
     * do not know what a connector is and that a connector can be 'empty'.
     * Instead they can use if (read.implemented()) ... to check whether
     * behavior read is implemented.
     */
    bool implemented() { return !empty(); }
    
    /*! Copy local bindings into another list - used to propagate our
     *  bindings in accordance with a connection policy.
     */
    void copyBindingsTo(BindingList &target,
                        BindingList::iterator pos);

    /*! Remove all local bindings from target list. */
    void removeBindingsFrom(BindingList &target);

};

} // namespace sg

/*! Reduce compilation times and object sizes by allowing the compiler
 *  to not instantiate connector classes in every compilation unit.
 *  Any header-file that declares a protocol class can use the macros
 *  in DirectedConnector.h to mention each behaviour signature used.
 *  By default, these macros will tell the compiler to treat each
 *  template as being instantiated externally.
 *  One compilation unit MUST predefine SG_INSTANTIATE_CONNECTORS prior
 *  to including any SG connector header files.  This will force the
 *  compiler to emit all required template definitions.
 */
#ifdef SG_INSTANTIATE_CONNECTORS
    /*! Force connector templates to be instantiated in this compilation unit. */
    #define SG_MENTION_TEMPLATE_CLASS template class
#else
    /*! Force connector templates to be marked as external to this compilation unit. */
    #define SG_MENTION_TEMPLATE_CLASS extern template class
#endif

#endif
