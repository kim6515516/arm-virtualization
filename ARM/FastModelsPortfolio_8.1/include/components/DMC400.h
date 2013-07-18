/*
   C++ interface for DMC400 model

   Copyright 2012 ARM Limited; all rights reserved
*/

#ifndef DMC400_revman_h_
#define DMC400_revman_h_

#include "sg/SGstdint.h"
#include "sg/SGComponentBase.h"
#include <SGComponentWithPorts.h>
#include <sg/SGControlProtocol.h>
#include <string>
#include <vector>

#include "DMC400-regnames.h"

class DMC400_revision_manager
{
    // control port connected to the control port of the parent LISA component (for callSimEngine)
    sg::SGControlProtocol control_port;
    void* revision_data;
    std::string myname;

public:
    DMC400_revision_manager(sg::ComponentBase *parentComponent, const std::string& parentInstanceName);
    ~DMC400_revision_manager();
    void handleTransition(uint32_t, DMC400_MEMC_STATES&, uint32_t&);
    void fillMaskInformation(DMC400_REVISION, bool, std::vector<uint32_t>&);
};

#endif
