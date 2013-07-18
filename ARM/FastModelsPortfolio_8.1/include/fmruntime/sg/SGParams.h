 /*!
 * \file    SGParams.h
 * \brief   Parameter passing structure.
 * \date    Copyright 2005-2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 * Definition of the Params structure.
 */

#ifndef ARM_SG_PARAMS_H
#define ARM_SG_PARAMS_H

#include <map>
#include <string>

namespace sg {

/*!
 * Params represents a set of named parameters (it's a map)
 *
 * Keys and values are always stored as strings and there are
 * accessors to convert them to integer, bool etc.
 * 
 * There are methods to treat parameter names as hierarchical
 * using '.' as a separator.
 */
class Params
{
    friend class Component;

public:
    typedef std::map<std::string, std::string> ParamMap;
    typedef std::pair<std::string, std::string> ParamEntry;
    typedef ParamMap::iterator Iterator;
    typedef ParamMap::const_iterator ConstIterator;

    // A reference to a particular parameter in a set of parameters
    // that doesn't access the parameter until it is needed.
    class ConstParamRef
    {
    protected:
        const ParamMap& cparams;
        const std::string name;

    public:
        ConstParamRef(const ParamMap& p, const std::string& k) : cparams(p), name(k) {}

        const std::string& key() const { return name; }
        const std::string& value() const;

        // get a value in a particular format
        bool  get_value(std::string& valref) const;
        bool  get_value(bool& valref) const;
        bool  get_value(int& valref) const;
        bool  get_value(unsigned int& valref) const;
        bool  get_value(long int& valref) const;
        bool  get_value(unsigned long int& valref) const;
        bool  get_value(long long int& valref) const;
        bool  get_value(unsigned long long int& valref) const;

        // as above with no presence check.
        // Missing values return "", false or 0
        operator std::string(void) const;
        operator bool(void) const;
        operator int(void) const;
        operator unsigned int(void) const;
        operator long int(void) const;
        operator unsigned long int(void) const;
        operator long long int(void) const;
        operator unsigned long long int(void) const;
    };

    class ParamRef : public ConstParamRef
    {
        ParamMap& params;

    public:
        ParamRef(ParamMap& p, const std::string& k) : ConstParamRef(p, k), params(p) {}

        // Set a value in a particular format.
        // More can be added as needed but only fundamental types should be
        // added or complex C++ types. Things such as uint64_t are typedefed
        // and should not appear here.
        ParamRef& operator=(const char*);
        ParamRef& operator=(const std::string&);
        ParamRef& operator=(bool);
        ParamRef& operator=(int);
        ParamRef& operator=(unsigned int);
        ParamRef& operator=(long int);
        ParamRef& operator=(unsigned long int);
        ParamRef& operator=(long long int);
        ParamRef& operator=(unsigned long long int);
    };


private:
    ParamMap params;

public:
    Params();
    Params(const Params&);
    
    // add a set of parameters
    void add(const Params&); 

    // Get an accessor that can be used to read/assign to the parameters
    // Note: this can't be used on const Params...
    ParamRef operator[](const std::string& name) { return ParamRef(params, name); }

    ConstParamRef operator[](const std::string& name) const { return ConstParamRef(params, name); }

    /* return a parameter as a string value
     *  If it doesn't exist the empty string will be returned
     */
    const std::string& get(const std::string& name) const;


    /* free form parameter setting of the form
     *           "name = param"
     */
    bool set(const std::string& name_equals_val);

    // alternative syntax for operator[]

    template <typename T>
    void set(const std::string& name, T t) { (*this)[name] = t; }

    template <typename T>
    bool get(const std::string& name, T& t) const { return (*this)[name].get_value(t); }

   
    // return all parameters which have a prefix of "prefix.", stripping
    // the prefix and .
    Params getParamsFor(const std::string& prefix) const;

    /* add a set of parameter to the set, with "prefix." prepended. */
    void setParamsFor(const std::string& prefix, const Params& params);

    ConstIterator begin() const { return params.begin(); }
    ConstIterator end() const { return params.end(); }

    size_t size() const { return params.size(); }
};

} // namespace sg

#endif // ARM_SG_PARAMS_H
