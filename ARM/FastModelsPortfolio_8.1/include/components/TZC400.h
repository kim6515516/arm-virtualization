/*
 * Interface to C++ portion of TZC400 model
 * Copyright 2012 ARM Limited. All rights reserved.
 */

#include "sg/SGstdint.h"
#include "sg/SGComponentBase.h"
#include <SGComponentWithPorts.h>
#include <sg/SGControlProtocol.h>

#include <string>
#include <map>

class TZC400_id_mapper
{
    // control port connected to the control port of the parent LISA component (for callSimEngine)
    sg::SGControlProtocol control_port;
    void* revision_data;
    std::string myname;
    std::map<int,int> the_mapping;
public:
    TZC400_id_mapper(sg::ComponentBase *parentComponent, std::string);
    ~TZC400_id_mapper();

    void        configureMapping(std::string);
    std::string getMappingDisplay(void);
    uint32_t    getIdForBusMaster(uint32_t bm);
};
