/*!
 * \file    VectoredDelegate.h
 * \brief   A delegate wrapped to handle indexed method calls.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 */

// THIS FILE IS GENERATED FROM VectoredDelegate.hxx


#ifndef VECTOREDDELEGATE_H
#define VECTOREDDELEGATE_H


#include "sg/FastDelegate.h"
#include "sg/IndexedDelegateMemento.h"

namespace sg {

//N=0

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class RetType=void>
class VectoredDelegate0 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate0< RetType > BehaviourType;
    typedef fastdelegate::FastDelegate1< unsigned int, RetType > VectoredBehaviourType;

    RetType invoke(  ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate0() {}

    template< class X, class Y >
    VectoredDelegate0(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate0(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate0::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class RetType>
VectoredDelegate0<RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)()) { 
    return VectoredDelegate0<RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class RetType>
VectoredDelegate0<RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)() const) { 
    return VectoredDelegate0<RetType>(index, x, func);
}

//N=1

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class RetType=void>
class VectoredDelegate1 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate1< Param1, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate2< unsigned int, Param1, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate1() {}

    template< class X, class Y >
    VectoredDelegate1(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate1(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate1::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class RetType>
VectoredDelegate1<Param1, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1)) { 
    return VectoredDelegate1<Param1, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class RetType>
VectoredDelegate1<Param1, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1) const) { 
    return VectoredDelegate1<Param1, RetType>(index, x, func);
}

//N=2

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class RetType=void>
class VectoredDelegate2 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate2< Param1, Param2, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate3< unsigned int, Param1, Param2, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate2() {}

    template< class X, class Y >
    VectoredDelegate2(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate2(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate2::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class RetType>
VectoredDelegate2<Param1, Param2, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2)) { 
    return VectoredDelegate2<Param1, Param2, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class RetType>
VectoredDelegate2<Param1, Param2, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2) const) { 
    return VectoredDelegate2<Param1, Param2, RetType>(index, x, func);
}

//N=3

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class RetType=void>
class VectoredDelegate3 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate3< Param1, Param2, Param3, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate4< unsigned int, Param1, Param2, Param3, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate3() {}

    template< class X, class Y >
    VectoredDelegate3(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate3(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate3::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class RetType>
VectoredDelegate3<Param1, Param2, Param3, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3)) { 
    return VectoredDelegate3<Param1, Param2, Param3, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class RetType>
VectoredDelegate3<Param1, Param2, Param3, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3) const) { 
    return VectoredDelegate3<Param1, Param2, Param3, RetType>(index, x, func);
}

//N=4

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class RetType=void>
class VectoredDelegate4 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate4< Param1, Param2, Param3, Param4, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate5< unsigned int, Param1, Param2, Param3, Param4, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate4() {}

    template< class X, class Y >
    VectoredDelegate4(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate4(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate4::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class RetType>
VectoredDelegate4<Param1, Param2, Param3, Param4, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) { 
    return VectoredDelegate4<Param1, Param2, Param3, Param4, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class RetType>
VectoredDelegate4<Param1, Param2, Param3, Param4, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const) { 
    return VectoredDelegate4<Param1, Param2, Param3, Param4, RetType>(index, x, func);
}

//N=5

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=void>
class VectoredDelegate5 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate5< Param1, Param2, Param3, Param4, Param5, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate6< unsigned int, Param1, Param2, Param3, Param4, Param5, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate5() {}

    template< class X, class Y >
    VectoredDelegate5(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate5(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate5::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
VectoredDelegate5<Param1, Param2, Param3, Param4, Param5, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) { 
    return VectoredDelegate5<Param1, Param2, Param3, Param4, Param5, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class RetType>
VectoredDelegate5<Param1, Param2, Param3, Param4, Param5, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const) { 
    return VectoredDelegate5<Param1, Param2, Param3, Param4, Param5, RetType>(index, x, func);
}

//N=6

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=void>
class VectoredDelegate6 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate6< Param1, Param2, Param3, Param4, Param5, Param6, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate7< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate6() {}

    template< class X, class Y >
    VectoredDelegate6(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate6(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate6::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
VectoredDelegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) { 
    return VectoredDelegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType>
VectoredDelegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const) { 
    return VectoredDelegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType>(index, x, func);
}

//N=7

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType=void>
class VectoredDelegate7 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate7< Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate8< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate7() {}

    template< class X, class Y >
    VectoredDelegate7(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate7(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate7::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType>
VectoredDelegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) { 
    return VectoredDelegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class RetType>
VectoredDelegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const) { 
    return VectoredDelegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7, RetType>(index, x, func);
}

//N=8

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType=void>
class VectoredDelegate8 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate8< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate9< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7, p8 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate8() {}

    template< class X, class Y >
    VectoredDelegate8(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate8(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate8::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType>
VectoredDelegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8)) { 
    return VectoredDelegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class RetType>
VectoredDelegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const) { 
    return VectoredDelegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, RetType>(index, x, func);
}

//N=9

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class RetType=void>
class VectoredDelegate9 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate9< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate10< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate9() {}

    template< class X, class Y >
    VectoredDelegate9(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate9(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate9::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class RetType>
VectoredDelegate9<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9)) { 
    return VectoredDelegate9<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class RetType>
VectoredDelegate9<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9) const) { 
    return VectoredDelegate9<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, RetType>(index, x, func);
}

//N=10

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class RetType=void>
class VectoredDelegate10 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate10< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate11< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate10() {}

    template< class X, class Y >
    VectoredDelegate10(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate10(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate10::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class RetType>
VectoredDelegate10<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10)) { 
    return VectoredDelegate10<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class RetType>
VectoredDelegate10<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10) const) { 
    return VectoredDelegate10<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, RetType>(index, x, func);
}

//N=11

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class RetType=void>
class VectoredDelegate11 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate11< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate12< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate11() {}

    template< class X, class Y >
    VectoredDelegate11(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate11(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate11::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class RetType>
VectoredDelegate11<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11)) { 
    return VectoredDelegate11<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class RetType>
VectoredDelegate11<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11) const) { 
    return VectoredDelegate11<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, RetType>(index, x, func);
}

//N=12

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class RetType=void>
class VectoredDelegate12 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate12< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate13< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate12() {}

    template< class X, class Y >
    VectoredDelegate12(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate12(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate12::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class RetType>
VectoredDelegate12<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12)) { 
    return VectoredDelegate12<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class RetType>
VectoredDelegate12<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12) const) { 
    return VectoredDelegate12<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, RetType>(index, x, func);
}

//N=13

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class RetType=void>
class VectoredDelegate13 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate13< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate14< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate13() {}

    template< class X, class Y >
    VectoredDelegate13(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate13(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate13::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class RetType>
VectoredDelegate13<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13)) { 
    return VectoredDelegate13<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class RetType>
VectoredDelegate13<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13) const) { 
    return VectoredDelegate13<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, RetType>(index, x, func);
}

//N=14

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class RetType=void>
class VectoredDelegate14 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate14< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate15< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate14() {}

    template< class X, class Y >
    VectoredDelegate14(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate14(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate14::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class RetType>
VectoredDelegate14<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14)) { 
    return VectoredDelegate14<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class RetType>
VectoredDelegate14<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14) const) { 
    return VectoredDelegate14<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, RetType>(index, x, func);
}

//N=15

/*! VectoredDelegate binds an index argument to the first argument of a
 *  Delegate of arity n to form a Delegate of arity n-1. Because none of
 *  the Delegate methods are virtual (and we definitely don't want them to
 *  be), this cannot be derived from Delegate.
 */
template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, class RetType=void>
class VectoredDelegate15 : public IndexedDelegateMemento {
    typedef fastdelegate::FastDelegate15< Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType > BehaviourType;
    typedef fastdelegate::FastDelegate16< unsigned int, Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType > VectoredBehaviourType;

    RetType invoke( Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ) {
        VectoredBehaviourType v;
        v.SetMemento(user_memento);
        return (v)(index, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15 );
    }

    void setup(VectoredBehaviourType v) {
        user_memento = v.GetMemento();
        bindable_memento = GetDelegate().GetMemento();
    }

public:
    VectoredDelegate15() {}

    template< class X, class Y >
    VectoredDelegate15(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ))
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    VectoredDelegate15(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ) const)
    : IndexedDelegateMemento(index_)
    {
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ))
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    template< class X, class Y >
    void bind(unsigned int index_, Y* pthis,
        RetType (X::* function_to_bind)( unsigned int i, Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15 ) const)
    {
        index = index_;
        setup(VectoredBehaviourType(pthis, function_to_bind));
    }

    // get a delegate to represent this object
    BehaviourType GetDelegate() {
        return fastdelegate::MakeDelegate(this, &VectoredDelegate15::invoke);
    }
};

// Helper function to instantiate a VectoredDelegate
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, class RetType>
VectoredDelegate15<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15)) { 
    return VectoredDelegate15<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType>(index, x, func);
}

// Helper function to instantiate a VectoredDelegate based on a const method
template<class X, class Y, class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7, class Param8, class Param9, class Param10, class Param11, class Param12, class Param13, class Param14, class Param15, class RetType>
VectoredDelegate15<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType> MakeVectoredDelegate(unsigned int index,
                                        Y* x, RetType (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8, Param9 p9, Param10 p10, Param11 p11, Param12 p12, Param13 p13, Param14 p14, Param15 p15) const) { 
    return VectoredDelegate15<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13, Param14, Param15, RetType>(index, x, func);
}


} // namespace sg

#endif // VECTOREDDELEGATE_H
