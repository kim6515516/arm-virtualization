/*
 * $Id: ReferenceCounting.h 29787 2013-03-01 10:40:01Z brifol01 $
 *
 * Project:  Assembler and Assembler Generator 2.0
 * $Author: brifol01 $
 * $Date: 2013-03-01 10:40:01 +0000 (Fri, 01 Mar 2013) $
 * $Revision: 29787 $
 *
 * Copyright (c) 2001-2003 by ARM, Herzogenrath, Germany
 *
 * This file contains proprietary, unpublished source code
 * solely owned by ARM, Herzogenrath, Germany.
 * All rights reserved.
 *
 */

#ifndef REFERENCECOUNTING_H
#define REFERENCECOUNTING_H

#include <assert.h>

class RCObject
{
public:
    RCObject() : refCount(0) {}
    RCObject(const RCObject &) : refCount(0) {} // jo: never copy the reference count from another object
    virtual ~RCObject() {} // jo: virtual destructor is needed to destruct objects of derived classes
    const RCObject &operator = (const RCObject &) { return *this; } // jo: never copy the reference count from another object
    void IncRef() const { ++refCount; }
    void DecRef() const {
        assert(refCount != 0);
        --refCount;
        if (refCount == 0)
            delete const_cast<RCObject *>(this);
    }
    unsigned int GetRefCount() const { return refCount; } // use for debugging only !
protected:
    mutable unsigned int refCount;
};

template <class RCClass>
class RCPointer
{
public:
    RCPointer() : refObjPtr((RCClass *)0) {}

    RCPointer(RCClass *refObjPtr_par) :
        refObjPtr(refObjPtr_par)
        {
            // if ptr points to real object increase number of refs
            if (refObjPtr)
                refObjPtr->IncRef();
        }

    RCPointer(const RCPointer<RCClass> &x) :
        refObjPtr(x.refObjPtr)
        {
            // if ptr points to real object increase number of refs
            if (refObjPtr)
                refObjPtr->IncRef();
        }

    ~RCPointer()
        {
            // if ptr points to object decrease number of refs
            if (refObjPtr)
                refObjPtr->DecRef();
            refObjPtr = 0;
        }

    const RCPointer &
    operator = (const RCPointer<RCClass> &x)
        {
            // Don't change the sequence of these instructions. They
            // are specially designed to work when this == &x !!!

            // increase number of refs of assigned object (if ptr not NULL)
            if (x.refObjPtr)
                x.refObjPtr->IncRef();
            // decrease num of refs to obj which will be overwritten by assignement.
            // jo: a subtle segfault occurs if the reference x is an element of the object pointed to by refObjPtr:
            //     in this case x may be deleted by the DecRef(), so we need to remember the value of x.refObjPtr
            //     before the DecRef() which may destroy x
            //     this was reproducible when calling Variables::GetVariableValue(pc=0000820c, expr=Ptr_Glob->Ptr_Comp) (in dhry.axf (ARM))
            RCClass *x_refObjPtr = x.refObjPtr;
            if (refObjPtr)
                refObjPtr->DecRef();
            // assign object
            refObjPtr = x_refObjPtr; // jo: we can not access x anymore, it may have been deleted by the DecRef() above
            return *this;
        }

    RCClass *operator -> () const {return refObjPtr;}
    RCClass &operator * () const {return *refObjPtr;}

    operator bool () const {return (refObjPtr != NULL);}

    bool operator == (const RCPointer<RCClass>& a) const { return refObjPtr == a.refObjPtr; }
    bool operator != (const RCPointer<RCClass>& a) const { return refObjPtr != a.refObjPtr; }
    bool operator >  (const RCPointer<RCClass>& a) const { return refObjPtr >  a.refObjPtr; }
    bool operator <  (const RCPointer<RCClass>& a) const { return refObjPtr <  a.refObjPtr; }
    bool operator >= (const RCPointer<RCClass>& a) const { return refObjPtr >= a.refObjPtr; }
    bool operator <= (const RCPointer<RCClass>& a) const { return refObjPtr <= a.refObjPtr; }

    RCClass *GetPtr() { return refObjPtr; }
    const RCClass *GetPtr() const { return refObjPtr; }

protected:
    RCClass *refObjPtr;
};

#endif
