/*!
 * \file    IndexedDelegateMemento.h
 * \brief   Base class for handling indexed vector behaviours
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 * This is a base-class for VectoredDelegate@NUM<T>; it defines the
 * storage layout for a VectoredDelegate (consisting of an index and
 * a DelegateMemento record), without providing the templated
 * functionality for invoking/binding the delegate.
 * This allows us to store a std::list<IndexedDelegateMemento>, rather
 * than std::list<VectoredDelegate@NUM<T>>  -- avoiding the need for
 * template-bloat in our object files.
 */

#ifndef INDEXEDDELEGATEMEMENTO_H
#define INDEXEDDELEGATEMEMENTO_H

#include "sg/FastDelegate.h"    // Could use separate out FastDelegateMemento.h

namespace sg {

/*! Hold the state needed to allow a vectored-behaviour to construct a
 *  delegate that can be used in the connector.  This holds a
 *  user-provided delegate of the form Ret(unsigned int, Param1, Param2,..),
 *  and a wrapper delegate of the form Ret(Param1, Param2).  It is up to
 *  the templated subclass VectoredDelegate@NUM<T> to construct this.
 */
class IndexedDelegateMemento {
protected:
    /*! index value that will be passed as first parameter to delegate. */
    unsigned int index;

    /*! Generic representation of the vectored delegate provided by the user. */
    fastdelegate::DelegateMemento user_memento;

    /*! Generic representation of the delegate that will be used in the
     *  behaviour list.
     */
    fastdelegate::DelegateMemento bindable_memento;

public:
    IndexedDelegateMemento(unsigned int index_ = 0) : index(index_) {}

    /*! Compare for equality: the index and memento values must match. */
    bool IsEqual (IndexedDelegateMemento const & other) const;

    /*! Compare for equality: the index and memento values must match. */
    bool IsLess (IndexedDelegateMemento const & other) const;

    /*! Return the bindable behaviour. */
    fastdelegate::DelegateMemento GetBindableDelegateMemento();
  
};

} // namespace sg

#endif
