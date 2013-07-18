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
 * Abstract interface class protocol_AMBAPV for protocol AMBAPV.
 */

#ifndef protocol_AMBAPV_h_
#define protocol_AMBAPV_h_

// Includes from the 'includes' section of this protocol
#line 9 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/AMBAPVProtocol.lisa"

        #include <amba_pv.h>
    
#line 25 "./Linux-Release-GCC-4.4/gen/protocol_AMBAPV.h"


// Abstract interface for protocol AMBAPV
class protocol_AMBAPV
{
public:
        virtual ~protocol_AMBAPV() {}
        // Abstract protocol members
	virtual amba_pv::amba_pv_resp_t read(int socket_id, const sc_dt::uint64& addr, unsigned char* data, unsigned int size, const amba_pv::amba_pv_control* ctrl, sc_core::sc_time& t) = 0;
	virtual amba_pv::amba_pv_resp_t write(int socket_id, const sc_dt::uint64& addr, unsigned char* data, unsigned int size, const amba_pv::amba_pv_control* ctrl, unsigned char* strb, sc_core::sc_time& t) = 0;
	virtual unsigned int debug_read(int socket_id, const sc_dt::uint64& addr, unsigned char* data, unsigned int length, const amba_pv::amba_pv_control* ctrl) = 0;
	virtual unsigned int debug_write(int socket_id, const sc_dt::uint64& addr, unsigned char* data, unsigned int length, const amba_pv::amba_pv_control* ctrl) = 0;
	virtual void b_transport(int socket_id, amba_pv::amba_pv_transaction& trans, sc_core::sc_time& t) = 0;
	virtual unsigned int transport_dbg(int socket_id, amba_pv::amba_pv_transaction& trans) = 0;
	virtual bool get_direct_mem_ptr(int socket_id, amba_pv::amba_pv_transaction& trans, tlm::tlm_dmi& dmi_data) = 0;
	virtual void invalidate_direct_mem_ptr(int socket_id, sc_dt::uint64 start_range, sc_dt::uint64 end_range) = 0;

};

#endif /* protocol_AMBAPV_h_ */

