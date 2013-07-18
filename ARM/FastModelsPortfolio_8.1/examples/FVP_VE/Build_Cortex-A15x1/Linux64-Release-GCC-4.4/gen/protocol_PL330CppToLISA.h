/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2007 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Abstract interface class protocol_PL330CppToLISA for protocol PL330CppToLISA.
 */

#ifndef protocol_PL330CppToLISA_h_
#define protocol_PL330CppToLISA_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol PL330CppToLISA
class protocol_PL330CppToLISA
{
public:
        virtual ~protocol_PL330CppToLISA() {}
        // Abstract protocol members
	virtual void message_printer(uint32_t type_, std::string text_) = 0;
	virtual void wakeup_in_ticks(unsigned ticks_) = 0;
	virtual void cancel_wakeup_timer() = 0;
	virtual void update_abort(bool state_) = 0;
	virtual void update_irq(unsigned index, bool state_) = 0;

};

#endif /* protocol_PL330CppToLISA_h_ */

