/* -*- c++ -*- */
/* vim: syntax=cpp
 */
/*!
 *  \file   GlobalSystemAttributes.h
 *  \brief  CADI parameter manipulation class
 *  \date   Copyright ARM Limited 2002 All Rights Reserved.
 *          Copyright ARM Limited 2013 All Rights Reserved.
 *  
 */

#ifndef GLOBALSYSTEMATTRIBUTES_H
#define GLOBALSYSTEMATTRIBUTES_H


#include <string>
#include <list>

// abstract class to hold global system attributes initialized before CADIBroker
class GlobalSystemAttributes
{
public:
    GlobalSystemAttributes();
    virtual ~GlobalSystemAttributes();

    // setup the attibutes, called just before CADIBroker is created 
    // derived function is generated from LISA behavior of the same signature 
    // the behavior can be only located in top level component
    virtual void setupGlobalSystemAttributes() = 0; 

    // add parameter filtering patterns
    virtual void hideParameter(const std::string& pattern);
    virtual void exposeParameter(const std::string& pattern);

    // returns true if parameter is exposed:
    // either matches one of exposed patterns or doe not match any hide patterns
    virtual bool isParameterExposed(const std::string& parameterName) const;

protected:
    // filter patterns the second field is expose flag (true - expose, false- hide)
    std::list<std::pair<std::string, bool> > exposeParameterPatterns; 

public:
    // returns poiner to global instance
    // note, that method can return NULL (it is not a singleton)
    static GlobalSystemAttributes* getGlobalSystemAttributes();
};

#endif

