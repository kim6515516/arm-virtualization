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
 * Abstract interface class protocol_TZFilterControl for protocol TZFilterControl.
 */

#ifndef protocol_TZFilterControl_h_
#define protocol_TZFilterControl_h_

// Includes from the 'includes' section of this protocol


// Abstract interface for protocol TZFilterControl
class protocol_TZFilterControl
{
public:
        virtual ~protocol_TZFilterControl() {}
        // Abstract protocol members
	virtual bool checkPermission(const pv::TransactionAttributes* attributes_, pv::bus_addr_t page_base_, bool is_read_, pv::RemapRequest& req_, bool& abort_on_error_) = 0;
	virtual bool isEnabled() = 0;
	virtual bool isSecureSlave() = 0;
	virtual void setConfig(bool rd_spec_enable, bool wr_spec_enable, uint32_t action) = 0;

};

#endif /* protocol_TZFilterControl_h_ */

