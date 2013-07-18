/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   ComponentRegister.h
 *  \brief  
 *  \date   Copyright ARM Limited 2002 All Rights Reserved.
 *          Copyright ARM Limited 2013 All Rights Reserved.
 *  
 */

#ifndef __ComponentRegister_h__
#define __ComponentRegister_h__

#include "eslapi/eslapi_stdint.h"


#include "ResourceAccessFuncTypes.h"

template <typename T, typename R>
class ComponentRegister
{
public:


    explicit ComponentRegister<T,R>(R* top_, uint8_t size_, uint8_t lsb_offset_, void *compRegHandler_, int regID_)
        : top(top_)
        , lsb_offset(lsb_offset_)
        , size(size_)
        , top_size(sizeof(R))
        {
            init_mask();
        }

    template <typename P>
    ComponentRegister<T,R>(ComponentRegister<R,P>* top_, uint8_t size_, uint8_t lsb_offset_, void *compRegHandler_, int regID_)
        : top(top_->get_top())
        , lsb_offset(top_->get_lsb_offset()+lsb_offset_)
        , size(size_)
        , top_size(top_->get_top_size())
        {
            init_mask();
        }

    operator T() const
        {
            return get_child_value();
        }

    T operator = (const T &value)
        {
            set_child_value(value);
            return get_child_value();
        }

    // operator lvalue++ (post increment)
    T operator ++(int x) 
    {
        T child = get_child_value();
        T result = child++;
        set_child_value(child);
        return result;
    }

    // operator lvalue-- (post decrement)
    T operator --(int x)
    {
        T child = get_child_value();
        T result = child--;
        set_child_value(child);
        return result;
    }

    // operator ++lvalue (pre increment)
    T operator ++()
    {
        T child = get_child_value();
        set_child_value(++child);
        return get_child_value();
    }

    // operator --lvalue (pre decrement)
    T operator --()
    {
        T child = get_child_value();
        set_child_value(--child);
        return get_child_value();
    }


    T operator *= (const T &x)
    {
        T child = get_child_value();
        child *= x;
        set_child_value(child);
        return get_child_value();
    }

    T operator /= (const T &x)
    {
        T child = get_child_value();
        child /= x;
        set_child_value(child);
        return get_child_value();
    }
    
    T operator %= (const T &x)
    {
        T child = get_child_value();
        child %= x;
        set_child_value(child);
        return get_child_value();
    }

    T operator += (const T &x)
    {
        T child = get_child_value();
        child += x;
        set_child_value(child);
        return get_child_value();
    }

    T operator -= (const T &x)
    {
        T child = get_child_value();
        child -= x;
        set_child_value(child);
        return get_child_value();
    }

    T operator <<= (const T &x)
    {
        T child = get_child_value();
        child <<= x;
        set_child_value(child);
        return get_child_value();
    }

    T operator >>= (const T &x)
    {
        T child = get_child_value();
        child >>= x;
        set_child_value(child);
        return get_child_value();
    }

    T operator &= (const T &x)
    {
        T child = get_child_value();
        child &= x;
        set_child_value(child);
        return get_child_value();
    }

    T operator |= (const T &x)
    {
        T child = get_child_value();
        child |= x;
        set_child_value(child);
        return get_child_value();
    }

    T operator ^= (const T &x)
        {
            T child = get_child_value();
            child ^= x;
            set_child_value(child);
            return get_child_value();
        }

    sg::accessfunc::AccessFuncResult debug_access_read(uint32_t reg_id, uint64_t* datap, bool side_effects)
        {
            *datap = get_child_value();
            return sg::accessfunc::ACCESS_FUNC_OK;
        }

    sg::accessfunc::AccessFuncResult debug_access_write(uint32_t reg_id, const uint64_t* datap, bool side_effects)
        {
            set_child_value(*datap);
            return sg::accessfunc::ACCESS_FUNC_OK;
        }

    // returns void pointer to the top level register:
    void* get_top() const {return top;}
    // get the size of the top level register
    uint8_t get_top_size() const {return top_size;}
    // get the LSB offset with respect to the top register:
    uint8_t get_lsb_offset() const {return lsb_offset;}

private:

    // pre-calculate all possible masks.
    void init_mask()
        {
            mask8   = (uint8_t(~0)>>((8-size)));
            imask8  = ~(mask8<<lsb_offset);
            mask16  = (uint16_t(~0)>>((16-size)));
            imask16 = ~(mask16<<lsb_offset);
            mask32  = (uint32_t(~0)>>((32-size)));
            imask32 = ~(mask32<<lsb_offset);
            mask64  = (uint64_t(~0)>>((64-size)));
            imask64 = ~(mask64<<lsb_offset);
        }

    T get_child_value() const
        {
            switch(top_size)
            {
                case 1: {
                    uint8_t child_value = *reinterpret_cast<uint8_t*>(top);
                    return static_cast<T>((child_value>>lsb_offset)&mask8);
                } break;
                case 2: {
                    uint16_t child_value = *reinterpret_cast<uint16_t*>(top);
                    return static_cast<T>((child_value>>lsb_offset)&mask16);
                } break;
                case 4: {
                    uint32_t child_value = *reinterpret_cast<uint32_t*>(top);
                    return static_cast<T>((child_value>>lsb_offset)&mask32);
                } break;
                case 8: {
                    uint64_t child_value = *reinterpret_cast<uint64_t*>(top);
                    return static_cast<T>((child_value>>lsb_offset)&mask64);
                } break;
                default:
                    // FATAL
                    return 0;
            }
        }

    void set_child_value(const T& value)
        {
            switch(top_size)
            {
                case 1: {
                    uint8_t *top_ref = reinterpret_cast<uint8_t*>(top);
                    uint8_t child_value = (value&mask8) << lsb_offset;
                    *top_ref &= imask8;
                    *top_ref |= child_value;
                } break;
                case 2: {
                    uint16_t *top_ref = reinterpret_cast<uint16_t*>(top);
                    uint16_t child_value = (value&mask16) << lsb_offset;
                    *top_ref &= imask16;
                    *top_ref |= child_value;
                } break;
                case 4: {
                    uint32_t *top_ref = reinterpret_cast<uint32_t*>(top);
                    uint32_t child_value = (value&mask32) << lsb_offset;
                    *top_ref &= imask32;
                    *top_ref |= child_value;
                } break;
                case 8: {
                    uint64_t *top_ref = reinterpret_cast<uint64_t*>(top);
                    uint64_t child_value = (value&mask64) << lsb_offset;
                    *top_ref &= imask64;
                    *top_ref |= child_value;
                } break;
                default:
                    // FATAL
                    break;
            }
        }

    void* top;

    uint8_t lsb_offset;
    uint8_t size;
    uint8_t top_size;

    uint8_t mask8,imask8;
    uint16_t mask16, imask16;
    uint32_t mask32, imask32;
    uint64_t mask64, imask64;

    ////////////////////////////////
    // operators declared private //
    // in order to forbid usage   //
    ////////////////////////////////

     void operator -> () { /* operator -> is not supported! */ }

     void operator [] (int) { /* operator [] is not supported! */ }
};



#endif

