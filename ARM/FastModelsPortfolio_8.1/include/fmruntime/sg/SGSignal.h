/*!
 * \file    SGSignal.h
 * \brief   Simple signal ports used to signal state changes.
 * \date    Copyright 2004 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_SIGNAL_H
#define ARM_SG_SIGNAL_H

#include "sg/SGPort.h"

namespace sg {

// simple two value signal
class Signal : public Port
{
public:
    enum State { Set, Clear };

private:
    void default_setValue(State /*s*/) {}

public:

    declare_behaviour(setValue, void (enum State));

    Signal() {
        define_behaviour(setValue);

        setValue.bind_default_behaviour(this, &Signal::default_setValue);
    }

    // utility methods
    void set()   { setValue(Set);   }
    void clear() { setValue(Clear); }
};

// A signal where the state can also be queried
// One of the Ports must implement getValue
class StateSignal : public Signal
{

public:

    declare_behaviour(getValue, Signal::State (void));

    StateSignal() {
        define_behaviour(getValue);
    }

    // utility methods
    Signal::State get() { return getValue(); }
};

} // namespace sg

#endif // ARM_SG_SIGNAL_H
