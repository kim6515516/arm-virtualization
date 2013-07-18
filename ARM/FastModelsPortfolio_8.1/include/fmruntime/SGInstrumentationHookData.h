// Copyright 2010 ARM Germany GmbH. All rights reserved.
// 
// data and enum values for the instrumentation_hook() behavior

#ifndef SGInstrumentationHookData_h_
#define SGInstrumentationHookData_h_

class SGInstrumentationHookData
{
public:
    // public types
    enum Type
    {
        T_BEFORE_CONSTRUCTION_ALL,
        T_BEFORE_CONSTRUCTION,
        T_AFTER_CONSTRUCTION,
        T_AFTER_CONSTRUCTION_ALL,
        T_BEFORE_INIT_ALL,
        T_BEFORE_INIT,
        T_AFTER_INIT,
        T_AFTER_INIT_ALL,
        T_BEFORE_RESET_ALL,
        T_BEFORE_RESET,
        T_AFTER_RESET,
        T_AFTER_RESET_ALL,
        T_BEFORE_TERMINATE_ALL,
        T_BEFORE_TERMINATE,
        T_AFTER_TERMINATE,
        T_AFTER_TERMINATE_ALL,
        T_NUM_TYPES // total number of types, not a valid type
    };
    
    // constructors
    SGInstrumentationHookData(Type type, const char *name = 0): type(type), name(name) {}

    // public data
    Type type;
    const char *name;
    
    // public functions
    
    // get type as string (never returns NULL)
    const char *getTypeStr() const 
    {
        static const char *typeStr[] = 
        {
            "BEFORE_CONSTRUCTION_ALL",
            "BEFORE_CONSTRUCTION",
            "AFTER_CONSTRUCTION",
            "AFTER_CONSTRUCTION_ALL",
            "BEFORE_INIT_ALL",
            "BEFORE_INIT",
            "AFTER_INIT",
            "AFTER_INIT_ALL",
            "BEFORE_RESET_ALL",
            "BEFORE_RESET",
            "AFTER_RESET",
            "AFTER_RESET_ALL",
            "BEFORE_TERMINATE_ALL",
            "BEFORE_TERMINATE",
            "AFTER_TERMINATE",
            "AFTER_TERMINATE_ALL"
        };

        unsigned int t = (unsigned int)type;
        if (t < T_NUM_TYPES)
            return typeStr[t];
        else
            return "(invalid type)";
    }
    
    // get name as string (never returns NULL)
    const char *getName() const 
    {
        return name ? name : "";
    }
};

#endif

