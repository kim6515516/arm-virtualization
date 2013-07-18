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
 * Abstract interface class protocol_Feature for protocol Feature.
 */

#ifndef protocol_Feature_h_
#define protocol_Feature_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol Feature
class protocol_Feature
{
public:
        virtual ~protocol_Feature() {}
        // Abstract protocol members
	virtual bool setFeature(const char* featureName, const char* valueStr) = 0;

};

#endif /* protocol_Feature_h_ */

