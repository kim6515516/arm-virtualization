/*!
 * \file    SGValuePort64.h
 * \brief   Simple port allowing a value to be modified.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Leo Wang
 *
 * Allow a component to expose a port for controlling a single value.
 */

#ifndef ARM_SG_VALUEPORT_64_H
#define ARM_SG_VALUEPORT_64_H

#include "sg/SGPort.h"

namespace sg {

/*! A simple port for controlling a configurable 32-bit unsigned value. */
class ValuePort64 : public Port
{
private:
    void default_setValue(uint64_t value) {}

public:
    declare_behaviour(setValue, void (uint64_t));

    ValuePort64() {
        define_behaviour(setValue);
        setValue.bind_default_behaviour(this, &ValuePort64::default_setValue);
    }
};

/*! An extension to the value port that allows the current value to be queried.
 */
class ValueStatePort64 : public ValuePort64
{
public:
    declare_behaviour(getValue, uint64_t (void));

    ValueStatePort64() {
        define_behaviour(getValue);
    }
};

class DataRegisterPort64 : public ValueStatePort64
{
    uint64_t value;
    uint64_t port_getValue() { return value; }
    void     port_setValue(uint64_t v) { value = v; }

public:
    DataRegisterPort64() : value() 
    {
        bind_method(*this, getValue, &DataRegisterPort64::port_getValue, this);
        bind_method(*this, setValue, &DataRegisterPort64::port_setValue, this);
    }
};


} // namespace sg

#endif // ARM_SG_VALUEPORT_64_H
