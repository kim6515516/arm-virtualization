/*!
 * \file    SGValuePort.h
 * \brief   Simple port allowing a value to be modified.
 * \date    Copyright 2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * Allow a component to expose a port for controlling a single value.
 */

#ifndef ARM_SG_VALUEPORT_H
#define ARM_SG_VALUEPORT_H

#include "sg/SGPort.h"

namespace sg {

/*! A simple port for controlling a configurable 32-bit unsigned value. */
class ValuePort : public Port
{
private:
    void default_setValue(uint32_t value) {}

public:
    declare_behaviour(setValue, void (uint32_t));

    ValuePort() {
        define_behaviour(setValue);
        setValue.bind_default_behaviour(this, &ValuePort::default_setValue);
    }
};

/*! An extension to the value port that allows the current value to be queried.
 */
class ValueStatePort : public ValuePort
{
public:
    declare_behaviour(getValue, uint32_t (void));

    ValueStatePort() {
        define_behaviour(getValue);
    }
};

class DataRegisterPort : public ValueStatePort
{
    uint32_t value;
    uint32_t port_getValue() { return value; }
    void   port_setValue(uint32_t v) { value = v; }

public:
    DataRegisterPort() : value() 
    {
        bind_method(*this, getValue, &DataRegisterPort::port_getValue, this);
        bind_method(*this, setValue, &DataRegisterPort::port_setValue, this);
    }
};


} // namespace sg

#endif // ARM_SG_VALUEPORT_H
