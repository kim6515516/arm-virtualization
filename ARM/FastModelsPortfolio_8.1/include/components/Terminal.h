/*!
 * \file    Terminal.h
 * \brief   A component providing back-end I/O for UARTs.
 * \date    Copyright 2004-2008 ARM Limited. All rights reserved.
 *
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include "sg/SGstdint.h"
#include "sg/SGComponent.h"

class SerialData : public sg::Port
{
 public:
    declare_behaviour(dataTransmit, void (uint16_t data));
    declare_behaviour(dataReceive, uint16_t (void));
    declare_behaviour(signalsSet, void (uint8_t signal));
    declare_behaviour(signalsGet, uint8_t (void));

    SerialData() {
        define_behaviour(dataTransmit);
        define_behaviour(dataReceive);
        define_behaviour(signalsSet);
        define_behaviour(signalsGet);
    }
};

class Terminal : public sg::GroupComponent
{
protected:
    Terminal(std::string const &name_) : GroupComponent(name_) { }

public:
    virtual SerialData *getSerialDataPort() = 0;
};



#endif // TERMINAL_REP_H
