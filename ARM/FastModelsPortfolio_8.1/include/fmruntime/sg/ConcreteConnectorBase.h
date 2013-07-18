/*!
 * \file    ConcreteConnectorBase.h
 * \brief   Templated connector invocation/binding rules.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * Define policy-neutral, templated base class for connectors.
 */

// THIS FILE IS GENERATED FROM ConcreteConnectorBase.hxx

#ifndef CONCRETECONNECTORBASE_H
#define CONCRETECONNECTORBASE_H

#include <cassert>
#include <cstdio>

#include "sg/ConnectorBase.h"
#include "sg/VectoredDelegate.h"

#define DEBUG_DELEGATE 0

#define trace_delegate if (!DEBUG_DELEGATE) ; else printf


namespace sg {


//N=0

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_0
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_0
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate0< RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate(  );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_0<void>
{
public:
    template <typename Dummy>
    class BehaviourListInvoker_0
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate0< void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate(  );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class RetType=void>
class ConcreteConnectorBase0 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase0 < RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate0<RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate0<RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_0<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_0< int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase0() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList() {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         );
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList() {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         );
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour() {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour() {
        rebuildInvocableBehaviour();

        return invoke(  );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)(  ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)(  ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)(  ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)(  ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke(  ) {
        return invocable_behaviour(  );
    }

    inline RetType operator() (  ) {
        return invocable_behaviour(  );
    }
};

//N=1

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_1
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_1
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate1< Param1, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_1<void>
{
public:
    template <class Param1, typename Dummy>
    class BehaviourListInvoker_1
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate1< Param1, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class RetType=void>
class ConcreteConnectorBase1 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase1 < Param1, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate1<Param1, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate1<Param1, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_1<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_1< Param1, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase1() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1) {
        rebuildInvocableBehaviour();

        return invoke( p1 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1 ) {
        return invocable_behaviour( p1 );
    }

    inline RetType operator() ( Param1 p1 ) {
        return invocable_behaviour( p1 );
    }
};

//N=2

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_2
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_2
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate2< Param1, Param2, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_2<void>
{
public:
    template <class Param1, class Param2, typename Dummy>
    class BehaviourListInvoker_2
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate2< Param1, Param2, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class RetType=void>
class ConcreteConnectorBase2 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase2 < Param1, Param2, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate2<Param1, Param2, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate2<Param1, Param2, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_2<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_2< Param1, Param2, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase2() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2 ) {
        return invocable_behaviour( p1, p2 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2 ) {
        return invocable_behaviour( p1, p2 );
    }
};

//N=3

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_3
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_3
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate3< Param1, Param2, Param3, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_3<void>
{
public:
    template <class Param1, class Param2, class Param3, typename Dummy>
    class BehaviourListInvoker_3
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate3< Param1, Param2, Param3, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class RetType=void>
class ConcreteConnectorBase3 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase3 < Param1, Param2, Param3, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate3<Param1, Param2, Param3, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate3<Param1, Param2, Param3, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_3<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_3< Param1, Param2, Param3, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase3() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3 ) {
        return invocable_behaviour( p1, p2, p3 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3 ) {
        return invocable_behaviour( p1, p2, p3 );
    }
};

//N=4

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_4
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_4
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate4< Param1, Param2, Param3, Param4, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_4<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, typename Dummy>
    class BehaviourListInvoker_4
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate4< Param1, Param2, Param3, Param4, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class RetType=void>
class ConcreteConnectorBase4 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase4 < Param1, Param2, Param3, Param4, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate4<Param1, Param2, Param3, Param4, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate4<Param1, Param2, Param3, Param4, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_4<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_4< Param1, Param2, Param3, Param4, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase4() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ) {
        return invocable_behaviour( p1, p2, p3, p4 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ) {
        return invocable_behaviour( p1, p2, p3, p4 );
    }
};

//N=5

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_5
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_5
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate5< Param1, Param2, Param3, Param4, Param5, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_5<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, typename Dummy>
    class BehaviourListInvoker_5
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate5< Param1, Param2, Param3, Param4, Param5, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=void>
class ConcreteConnectorBase5 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase5 < Param1, Param2, Param3, Param4, Param5, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate5<Param1, Param2, Param3, Param4, Param5, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate5<Param1, Param2, Param3, Param4, Param5, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_5<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_5< Param1, Param2, Param3, Param4, Param5, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase5() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5 );
    }
};

//N=6

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_6
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_6
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate6< Param1, Param2, Param3, Param4, Param5, Param6, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_6<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, typename Dummy>
    class BehaviourListInvoker_6
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate6< Param1, Param2, Param3, Param4, Param5, Param6, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=void>
class ConcreteConnectorBase6 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase6 < Param1, Param2, Param3, Param4, Param5, Param6, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_6<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_6< Param1, Param2, Param3, Param4, Param5, Param6, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase6() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6 );
    }
};

//N=7

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_7
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_7
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate7< Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_7<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, typename Dummy>
    class BehaviourListInvoker_7
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate7< Param1, Param2, Param3, Param4, Param5, Param6, Param7, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType=void>
class ConcreteConnectorBase7 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase7 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_7<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_7< Param1, Param2, Param3, Param4, Param5, Param6, Param7, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase7() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7 );
    }
};

//N=8

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_8
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_8
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate8< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7, p8 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_8<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, typename Dummy>
    class BehaviourListInvoker_8
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate8< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7, p8 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType=void>
class ConcreteConnectorBase8 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase8 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_8<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_8< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase8() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/, Param8 /*p8*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7, p8 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8 );
    }
};

//N=9

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_9
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_9
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate9< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_9<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, typename Dummy>
    class BehaviourListInvoker_9
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate9< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class RetType=void>
class ConcreteConnectorBase9 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase9 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate9<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate9<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_9<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_9< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase9() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/, Param8 /*p8*/, Param9 /*p9*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9 );
    }
};

//N=10

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_10
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_10
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate10< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_10<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, typename Dummy>
    class BehaviourListInvoker_10
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate10< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class RetType=void>
class ConcreteConnectorBase10 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase10 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate10<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate10<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_10<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_10< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase10() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/, Param8 /*p8*/, Param9 /*p9*/, Param10 /*p10*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
    }
};

//N=11

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_11
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_11
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate11< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_11<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, typename Dummy>
    class BehaviourListInvoker_11
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate11< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class RetType=void>
class ConcreteConnectorBase11 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase11 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate11<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate11<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_11<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_11< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase11() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/, Param8 /*p8*/, Param9 /*p9*/, Param10 /*p10*/, Param11 /*p11*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 );
    }
};

//N=12

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_12
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_12
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate12< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_12<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, typename Dummy>
    class BehaviourListInvoker_12
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate12< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class RetType=void>
class ConcreteConnectorBase12 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase12 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate12<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate12<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_12<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_12< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase12() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/, Param8 /*p8*/, Param9 /*p9*/, Param10 /*p10*/, Param11 /*p11*/, Param12 /*p12*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 );
    }
};

//N=13

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_13
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_13
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate13< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_13<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, typename Dummy>
    class BehaviourListInvoker_13
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate13< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class RetType=void>
class ConcreteConnectorBase13 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase13 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate13<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate13<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_13<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_13< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase13() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/, Param8 /*p8*/, Param9 /*p9*/, Param10 /*p10*/, Param11 /*p11*/, Param12 /*p12*/, Param13 /*p13*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 );
    }
};

//N=14

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_14
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_14
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate14< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_14<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, typename Dummy>
    class BehaviourListInvoker_14
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate14< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class RetType=void>
class ConcreteConnectorBase14 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase14 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate14<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate14<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_14<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_14< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase14() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/, Param8 /*p8*/, Param9 /*p9*/, Param10 /*p10*/, Param11 /*p11*/, Param12 /*p12*/, Param13 /*p13*/, Param14 /*p14*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14 );
    }
};

//N=15

/*! This is the outer of a pair of nested classes that exist to encapsulate
 *  the static invokeBehaviourList method in such a way that we can partially
 *  specialise on the return type of the delegate, in order to handle voids.
 */
template<typename RetType>
class BehaviourListHandler_15
{
public:
    /*! The inner class used in the partial specialisation of
     *  invokeBehaviourList.
     */
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, typename Dummy> // Dummy bypasses Hopter's <>-removal
    class BehaviourListInvoker_15
    {
    public:
        /*! Pass an invocation call onto a list of delegate bindings.
         *  The returned value will be the value returned by the last
         *  delegate in the list.
         */
        template <typename I>
        static RetType invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ) {
            trace_delegate("*** Invoking behaviour list\n");
            RetType ret = RetType();
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate15< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n",
                               static_cast<void*>(&(*iter)));
                ret = delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list\n");
            return ret;
        }
    };
};

/*! Specialise the invokeBehaviourList method for delegates with a return
 *  type of void.  This specialised version differs only in that it doesn't
 *  attempt to track the returned value from the delegates (since it isn't
 *  possible to track a void value.
 */
template <>
class BehaviourListHandler_15<void>
{
public:
    template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, typename Dummy>
    class BehaviourListInvoker_15
    {
    public:
        template <typename I>
        /*! Pass an invocation call onto a list of delegate bindings. */
        static void invokeBehaviourList(I iter, const I &end, bool &lock, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15) {
            trace_delegate("*** Invoking behaviour list <void>\n");
            lock = true;
            for (; iter != end; ++iter) {
                fastdelegate::FastDelegate15< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, void > delegate;
                delegate.SetMemento(*iter);
                trace_delegate("*** Invoking delegate: %p\n", 
                               static_cast<void*>(&(*iter)));
                delegate( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15 );
            }
            lock = false;
            trace_delegate("*** Invoked behaviour list <void>\n");
        }
    };
};


/*! Templated support for adapting ConnectorBase to work with a specific
 *  function signature.
 *
 *  This class derives from ConnectorBase virtually, so that it can be
 *  mixed-in with a connection-policy class that also derives from
 *  ConnectorBase.
 */
template< class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, class RetType=void>
class ConcreteConnectorBase15 : public virtual ConnectorBase
{
protected:
    /*! Short typename for this class. */
    typedef ConcreteConnectorBase15 < Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType > ConcreteConnectorType;

    /*! Delegate typename. */
    typedef fastdelegate::FastDelegate15<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType> BehaviourType;

    /*! Vectored delegate typename. */
    typedef VectoredDelegate15<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType> VectoredBehaviourType;

    /*! typename for behaviourListHandler. */
    typedef BehaviourListHandler_15<RetType> BehaviourListHandler;

    /*! typename for behaviourListInvoker. */
    typedef typename BehaviourListHandler::template BehaviourListInvoker_15< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, int > BehaviourListInvoker;

    /*! The delegate that handles invocation on this connector. */
    BehaviourType invocable_behaviour;

    /*! Default constructor: initialise invocable behaviour to call the
     *  invokeUndefinedBehaviour handler.
     */
    ConcreteConnectorBase15() {
        updateInvocableBehaviour();
    }
    /*! Pass an invocation call onto the active behaviour list. */
    RetType invokeActiveBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15) {
        trace_delegate("*** invokeActiveBehaviourList : active_behaviour_list size : %d\n", (int)active_behaviour_list->size());
        return BehaviourListInvoker::invokeBehaviourList(active_behaviour_list->begin(),
                                                         active_behaviour_list->end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
    }

    /*! Pass an invocation call onto the default behaviour list. */
    RetType invokeDefaultBehaviourList(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15) {
        return BehaviourListInvoker::invokeBehaviourList(default_bindings.begin(),
                                                         default_bindings.end(),
                                                         active_list_locked
                                                         , p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
    }

    /*! Trap an attempt to call an unbound behaviour. */
    RetType invokeUndefinedBehaviour(Param1 /*p1*/, Param2 /*p2*/, Param3 /*p3*/, Param4 /*p4*/, Param5 /*p5*/, Param6 /*p6*/, Param7 /*p7*/, Param8 /*p8*/, Param9 /*p9*/, Param10 /*p10*/, Param11 /*p11*/, Param12 /*p12*/, Param13 /*p13*/, Param14 /*p14*/, Param15 /*p15*/) {
        fprintf(stderr, "*** Call to undefined behaviour:\n");
        dump();
        assert(!"invokeUndefinedBehaviour");
        return RetType();
    }

    /*! Used when no invocable behaviour is defined, to
     *  activate the default invokeUndefinedBehaviour handler.
     */
    void setEmptyInvocableBehaviour() {
        invocable_behaviour.bind(this,
                                 &ConcreteConnectorType::invokeUndefinedBehaviour);
    }

    /*! Trap attempts to invoke a behaviour when the delegate needs reconstructing,
     *  reconstruct it and then invoke it
     */
    RetType invokeRebuildBehaviour(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15) {
        rebuildInvocableBehaviour();

        return invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15 );
    }

    /*! set the behaviour to rebuild the delegate on demand
     */
    virtual void updateInvocableBehaviour() {

        active_behaviour_list = NULL;

        invocable_behaviour.bind(this,
                                &ConcreteConnectorType::invokeRebuildBehaviour);
    }

    /*! on the first invokation after a change in topology, reconstruct the
     *  invokation delegate
     */
    virtual void rebuildInvocableBehaviour() {

        active_behaviour_list = &getActiveBehaviourList();

        BindingList *target_list;
        if (active_behaviour_list == NULL ||
            active_behaviour_list->empty())
        {
            target_list = &default_bindings;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeDefaultBehaviourList);
        } else {
            target_list = active_behaviour_list;
            invocable_behaviour.bind(this, 
                                     &ConcreteConnectorType::invokeActiveBehaviourList);
        }
        if (target_list->empty()) {
            setEmptyInvocableBehaviour();
        } else {
            // Optimise for the case where there is one item in the target 
            // list: bind the invocable_behaviour direct to the memento.
            if (target_list->size() == 1) {
                BindingList::iterator i = target_list->begin();
                invocable_behaviour.SetMemento(*i);
            }
        }
    }


public:
    /*! Helper function to bind this connector to a delegate. */
    void bind_behaviour(BehaviourType b)
    {
        addBinding(b.GetMemento());
    }

    /*! Helper function to bind this connector to a member function. */
    template < class X, class Y >
    void bind_behaviour(Y *pthis,
                        RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ))
    {
        bind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Bind this connector to a vectored member function, taking an
     *  unsigned int index as the first argument.
     */
    template < class X, class Y >
    void bind_vector_behaviour(unsigned int index,
                               Y *pthis,
                               RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15))
    {
        VectoredBehaviourType *d = new VectoredBehaviourType(index, pthis, function_to_bind);
        addIndexedBinding(d);
    }
    

    /*! Helper function to unbind this connector from a delegate. */
    void unbind_behaviour(BehaviourType b)
    {
        removeBinding(b.GetMemento());
    }

    /*! Helper function to unbind this connector from a member function. */
    template < class X, class Y >
    void unbind_behaviour(Y *pthis,
                          RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ))
    {
        unbind_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    /*! Unbind a vectored function. */
    template < class X, class Y >
    void unbind_vector_behaviour(unsigned int index,
                                 Y *pthis,
                                 RetType (X::* function_to_bind)( unsigned int, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ))
    {
        /* Construct a vectored delegate for matching purposes. */
        VectoredBehaviourType dmatch(index, pthis, function_to_bind);
        deleteIndexedBinding(dmatch);
    }



    /*! Helper function to bind a delegate to our default behaviour. */
    void bind_default_behaviour(BehaviourType b)
    {
        addDefaultBinding(b.GetMemento());
    }

    /*! Helper function to bind a member function to our default behaviour. */
    template < class X, class Y >
    void bind_default_behaviour(Y *pthis,
                                RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ))
    {
        bind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }


    /*! Helper function to unbind a delegate from our default behaviour. */
    void unbind_default_behaviour(BehaviourType b)
    {
        removeDefaultBinding(b.GetMemento());
    }

    /*! Helper function to unbind a member function from our default behaviour. */
    template < class X, class Y >
    void unbind_default_behaviour(Y *pthis,
                                 RetType (X::* function_to_bind)( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ))
    {
        unbind_default_behaviour(fastdelegate::MakeDelegate(pthis, function_to_bind));
    }

    inline RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15 );
    }

    inline RetType operator() ( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ) {
        return invocable_behaviour( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15 );
    }
};


} // namespace sg

#endif
