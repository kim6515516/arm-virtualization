/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2006 ARM Limited.
 * Copyright 2011 ARM LImited.
 *
 * All rights reserved.
 */

/** \file
 * Class definition for Component VFS2.
 */

#ifndef Component_Component__VFS2_ClassDef_h_
#define Component_Component__VFS2_ClassDef_h_

#include <MxTypes.h>
#include <eslapi/eslapi_stdint.h>

#include <limits.h>
#include <map>
#include <fstream>
#include "SystemGenComponent.h"
#include "CADIBase.h"
#include "ComponentRegister.h"
#include "ResourceAccessFuncTypes.h"
#include "CADIParameterProxy.h"
#include "ParameterFilter.h"
#include "sg/SGTargetInfo.h"
#include "FVP_VE_Cortex_A15x1_DSO.h"

using namespace std;

#line 41 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"

    
        #include "hostconf/zinttypes.h"
        #include "VFS.h"
        #include "VFSOps.h"
        
        #include "MessageCodec.h"
        
        // these are only necessary if backgrounding is enabled
        #include "TxLib/TxLib.h"
        #include "sg/SGScheduler.h"
        
        #define vfs_trace           if (!0) ; else printf
        #define vfs_trace_op        if (!0) ; else printf
        #define vfs_trace_debug     if (!0) ; else printf
        #define vfs_trace_worker    if (!0) ; else printf
        // Set this to 'if (1)' to trace messages when a client OS
        // driver bug results in an ill-formed messagebox packet
        #define vfs_trace_clienterr if (!0) ; else printf
    
#line 58 "./Linux-Release-GCC-4.1/gen/Component__VFS2_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Builtin__ControlProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__MessageBoxProtocol_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__PVBus_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Signal_ClassDef.h"
#include "FVP_VE_Cortex_A15x1__Value_ClassDef.h"



class SimulationEngine;
class ObjectLoader;

using namespace sg::accessfunc;

namespace eslapi
{
    class CADI;
}

namespace FVP_VE_Cortex_A15x1_NMS {

class ParameterFilter_messagebox_of_MessageBox_to_VFS2 : public ParameterFilter
{
public:
	ParameterFilter_messagebox_of_MessageBox_to_VFS2()
	{
		ovrd_params["id"] = eslapi::CADIParameterInfo_t(0x10000034 | PARAMETERFILTER_FIXED, "id",eslapi::CADI_PARAM_INT, "MessageBox ID",0,MxS64CONST(0x8000000000000000),MxS64CONST(0x7fffffffffffffff),MxS64CONST(0x1400400), "0x01400400" );
	}
};



class
#ifndef _WINDOWS
SG_FVP_VE_Cortex_A15x1_DSO
#endif
Component__VFS2: public SystemGenComponent
{
public:
    // pointers to subcomponents
	Component__MessageBox *messagebox;


    // control ports of subcomponents
	FVP_VE_Cortex_A15x1__Builtin__ControlProtocol controlPort_messagebox__;


    // abstract ports
	FVP_VE_Cortex_A15x1__PVBus pvbus_s;
	FVP_VE_Cortex_A15x1__Signal intr;
	FVP_VE_Cortex_A15x1__MessageBoxProtocol message;
	FVP_VE_Cortex_A15x1__Value complete;


    // resources
    std::string application_pathname;


#line 63 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/VFS2/LISA/VFS2.lisa"

        const std::string  mount     ; 
        
        // simple worker thread class to move simulation work to the background
        class WorkerThread : public TxRunnable
        {
            TxThread *thread;              // actual thread
            TxEvent   work_ready;          // set when work is available to do
            sg::AsyncSignal async;         // object to generate callbacks in the simulation thread
            bool quit;                     // terimination flag
            
            virtual void runThread()
            {
                if (!0) ; else printf("WorkerThread(back)::init\n");
                
                while (1)
                {
                    // wait for a message to become ready
                    work_ready.Wait();
                    work_ready.ResetEvent();
                    
                    if (quit)
                        break;
                    
                    if (!0) ; else printf("WorkerThread(back)::start work\n");
                    
                    doWork();

                    if (!0) ; else printf("WorkerThread(back)::end work\n");
                    
                    // schedule a callback in the simulation thread to indicate that
                    // async processing is complete
                    async.signal();
                }
                
                if (!0) ; else printf("WorkerThread(back)::terminate\n");
            }
            
            void async_callback()
            {
                if (!0) ; else printf("WorkerThread(fore)::end work\n");
                
                workComplete();
            }
     
        protected:

            WorkerThread(sg::SimulationContext *simulationContext):
            async("async", simulationContext)
            {
                quit = false;
                thread = 0;
                
                // C++ equivalent of binding a behaviour to a port
                bind_method(async.async_callback, signal, &WorkerThread::async_callback, this);
            }
            
        public:
        
            virtual ~WorkerThread()
            {
                quit = true;
                work_ready.SetEvent();
                
                if (thread != NULL)
                {
                    thread->join(NULL);
                }
                
                delete thread;
            }
            
            // user method to queue work for background processing
            void startWork()
            {
                if (!0) ; else printf("WorkerThread(fore)::start work\n");
                
                if (thread == NULL)
                {
                    thread = new TxThread(this);
                }
                work_ready.SetEvent();
            }
           
            // user callback in worker thread when work is available
            virtual void doWork() = 0;
           
            // user callback in simulation thread when work is complete 
            virtual void workComplete() = 0;
        };
        
        
        // C++ action class handling processing of messages, optionally using a background thread
        class ProcessMessage : public WorkerThread
        {
            // locals for passing message parameters to the background thread
            
            const void* async_data_in;
            uint32_t    async_len_in;
            void*       async_data_out;
            uint32_t    async_len_out;
            
            protocol_Value* completion;     // completion port
            
            // shared transfer buffer that can be used for read/write/other data
            // this could be done inline in the message
            uint8_t transfer_buffer[VFS_MAX_TRANSFER];
            
        public:
            VFS vfs;     
            
            
        public:
            ProcessMessage(sg::SimulationContext *simulationContext): 
            WorkerThread(simulationContext)
            {
                completion = NULL;
            }
            
            virtual ~ProcessMessage()
            {
            }
            
            virtual void doWork()
            {
                process_message(async_data_in, async_len_in, async_data_out, &async_len_out);
            }
            
            virtual void workComplete()
            {
                // signal completion to the lisa port so it can complete the message handling
                if (completion)
                    completion->setValue(async_len_out);
            }
            
            
            void setCompletionPort(protocol_Value* completion_port)
            {
                completion = completion_port;
            }
            
            // process a message using the background thread. 
            void async_message(const void* data_in, uint32_t len_in, void* data_out, uint32_t* len_out)
            {
                // save the parameters for the background thread
                async_data_in  = data_in;
                async_len_in   = len_in;
                async_data_out = data_out;
                async_len_out  = *len_out;  // value is returned by completion
                
                // wake up the background thread to process the message
                startWork();
            }
            
            
            // process a message immediately (in the caller thread). No asynchronous signal will be sent
            void sync_message(const void* data_in, uint32_t len_in, void* data_out, uint32_t* len_out)
            {
                process_message(data_in, len_in, data_out, len_out);
            }
        
        private:

            bool check_get(MessageComposer& rmsg, bool result, const char *what)
            {
                if (!result)
                {
                    if (!0) ; else printf("VFS CLIENT BUG: %s\n", what);
                    rmsg.put_uint32(VFS_ERR_INVALID);
                }
                return result;
            }
            
            // routine to process a message
            // receive a message from the vm (buffered in the message box)
            // extract arguments from the message
            // invoke the correct vfs behaviour
            // compose a reply message
            // send it back to the driver
            void process_message(const void* data_in, uint32_t len_in, void* data_out, uint32_t* len_out)
            {
                MessageDecomposer msg(data_in, len_in);
                
                // VFS messages consist of:
                //  uint32_t driver_id; 
                //  uint32_t vfs_op;  
                //  operation dependent arguments
                
                // VFS replies consist of:
                //  uint32_t driver_id;
                //  int32_t return value (typically)
                //  operation dependent arguments
                
                // for now, all VFS ops are atomic, in future they won't be
                // but that requires copying parameters (or more easily messages)
                // to a background thread and processing the fs request there.
                
                // Note that it is important not to trust data from the client!

                uint32_t id = 0;
                uint32_t vfsop = 0xFFFFFFFF;
                bool failed = false;
                
                if (!msg.get_uint32(&id))
                {
                    failed = true;
                    if (!0) ; else printf("VFS CLIENT BUG: no ID\n");
                }
                else if (!msg.get_uint32(&vfsop))
                {
                    failed = true;
                    if (!0) ; else printf("VFS CLIENT BUG: no vfsop\n");
                }
                
                // as we've pulled the id and op, the buffer can be shared providing all the 
                
                MessageComposer rmsg(data_out, *len_out);
                rmsg.put_uint32(id);
                if (failed)
                {
                    rmsg.put_uint32(VFS_ERR_INVALID);
                    return;
                }
                
                switch (vfsop)
                {
                    case VFS_OPENMOUNTS: // in: void, out: int handle
                    {                    
                        if (!0) ; else printf("vfs_openmounts()");
                        
                        int32_t ret = vfs.openmounts();
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                        
                    }    
                    break;
                    
                    case VFS_READMOUNTS: // in: int32 handle, uint32 attr, uint32 attrlen, out: result, attribute data
                    {
                        int32_t handle;
                        uint32_t attr;
                        uint8_t* attrdata = transfer_buffer;
                        uint32_t attrdatalen;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "readmounts(handle)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&attr), "readmounts(attr)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&attrdatalen), "readmounts(attrdatalen)"))
                            return;
                        
                        if (!0) ; else printf("vfs_readmounts(handle=%d, attr=0x%x, attrlen=%d)", handle, attr, attrdatalen); 
                        
                        if (attrdatalen > VFS_MAX_TRANSFER)
                            attrdatalen = VFS_MAX_TRANSFER;
                        
                        int32_t ret = vfs.readmounts(handle, attr, attrdata, attrdatalen);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        // could use varargs for the result
                        rmsg.put_int32(ret);
                        rmsg.put_data(attrdata, attrdatalen);
                    }
                    break;
                    
                    case VFS_CLOSEMOUNTS: // in: int32 out: void
                    {
                        int32_t handle;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "closemounts(handle)"))
                            return;
                        
                        if (!0) ; else printf("vfs_closemounts(%d)", handle);
                        
                        int32_t ret = vfs.closemounts(handle);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                    
                    case VFS_OPENDIR: // in: cstr path out: int32 handle
                    {
                        uint32_t plen = VFS_MAX_PATH;
                        char path[VFS_MAX_PATH];
                        
                        if (!check_get(rmsg, msg.get_cstr(path, &plen), "opendir(path)"))
                            return;
                        
                        if (!0) ; else printf("vfs_opendir(path=%s)", path);
                        
                        int32_t ret = vfs.opendir(path);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                    
                    case VFS_READDIR: // in: int32 handle, uint32 attrs, uint32 attrlen, out: int32 result, attr data
                    {
                        int32_t handle;
                        uint32_t attrs;
                        uint32_t attrdatalen;
                        uint8_t* attrdata = transfer_buffer;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "readdir(handle)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&attrs), "readdir(attrs)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&attrdatalen), "readdir(attrdatalen)"))
                            return;
                        
                        if (attrdatalen > VFS_MAX_TRANSFER)
                            attrdatalen = VFS_MAX_TRANSFER;
                            
                        if (!0) ; else printf("vfs_readdir(handle=%d, attr=0x%x, attrlen=%d)", handle, attrs, attrdatalen);
                            
                        int32_t ret = vfs.readdir(handle, attrs, attrdata, attrdatalen);
                        
                        if (!0) ; else printf(" -> %d\n", ret);

                        rmsg.put_int32(ret);
                        rmsg.put_data(attrdata, attrdatalen);   
                    }
                    break;
                     
                    case VFS_CLOSEDIR: // in: int32 handle out: int32 result
                    {
                        int32_t handle;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "closedir(handle)"))
                            return;
                        
                        if (!0) ; else printf("vfs_closedir(handle=%d)", handle);
                        
                        int32_t ret = vfs.closedir(handle);
                        
                        if (!0) ; else printf(" -> %d\n", ret);

                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_MKDIR: // in: cstr dirname out: int32 result 
                    {
                        uint32_t namelen = VFS_MAX_PATH;
                        char dirname[VFS_MAX_PATH];
                        
                        if (!check_get(rmsg, msg.get_cstr(dirname, &namelen), "mkdir(dirname)"))
                            return;
                        
                        if (!0) ; else printf("vfs_mkdir(name=%s)", dirname);
                        
                        int32_t ret = vfs.mkdir(dirname);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_RMDIR: // in: cstr dirname out: int32 result 
                    {
                        uint32_t namelen = VFS_MAX_PATH;
                        char dirname[VFS_MAX_PATH];
                        
                        if (!check_get(rmsg, msg.get_cstr(dirname, &namelen), "rmdir(dirname)"))
                            return;
                        
                        if (!0) ; else printf("vfs_rmdir(name=%s)", dirname);
                        
                        int32_t ret = vfs.rmdir(dirname);
                        
                        if (!0) ; else printf(" -> %d\n", ret);                
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_REMOVE: // in: out: 
                    {
                        uint32_t namelen = VFS_MAX_PATH;
                        char filename[VFS_MAX_PATH];
                        
                        if (!check_get(rmsg, msg.get_cstr(filename, &namelen), "remove(filename)"))
                            return;
                        
                        if (!0) ; else printf("vfs_remove(name=%s)", filename);
                        
                        int32_t ret = vfs.remove(filename);
                        
                        if (!0) ; else printf(" -> %d\n", ret);                
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_RENAME: // in: cstr filename1, cstr filename2 out: int32 result 
                    {
                        uint32_t namelen1 = VFS_MAX_PATH;
                        char filename1[VFS_MAX_PATH];
                        uint32_t namelen2 = VFS_MAX_PATH;
                        char filename2[VFS_MAX_PATH];
                        
                        if (!check_get(rmsg, msg.get_cstr(filename1, &namelen1), "rename(filename1)"))
                            return;
                        if (!check_get(rmsg, msg.get_cstr(filename2, &namelen2), "rename(filename2"))
                            return;
                        
                        if (!0) ; else printf("vfs_rename(oldname=%s, newname=%s)", filename1, filename2);
                        
                        int32_t ret = vfs.rename(filename1, filename2);
                        
                        if (!0) ; else printf(" -> %d\n", ret);                
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_GETATTR: // in: cstr filename, uint32 attr, uint32 attrlen out: int32 result, attr data 
                    {
                        uint32_t namelen = VFS_MAX_PATH;
                        char filename[VFS_MAX_PATH];
                        uint32_t attrs;
                        uint32_t attrdatalen;
                        uint8_t* attrdata = transfer_buffer;
                        
                        if (!check_get(rmsg, msg.get_cstr(filename, &namelen), "getattr(filename)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&attrs), "getattr(attrs)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&attrdatalen), "getattr(attrdatalen)"))
                            return;
                        
                        if (attrdatalen > VFS_MAX_TRANSFER)
                            attrdatalen = VFS_MAX_TRANSFER;
                            
                        if (!0) ; else printf("vfs_getattr(name=%s, attr=0x%x, attrlen=%d)", filename, attrs, attrdatalen);
                            
                        int32_t ret = vfs.getattr(filename, attrs, attrdata, attrdatalen);
                        
                        if (!0) ; else printf(" -> %d\n", ret);

                        rmsg.put_int32(ret);
                        rmsg.put_data(attrdata, attrdatalen);
                    }
                    break;
                     
                    case VFS_SETATTR: // in: cstr filename, uint32 attr, void* attrdata, out: result 
                    {
                        uint32_t namelen = VFS_MAX_PATH;
                        char filename[VFS_MAX_PATH];
                        uint32_t attrs;
                        uint32_t attrdatalen = VFS_MAX_TRANSFER;  // maybe this should be passed in?
                        uint8_t* attrdata = transfer_buffer;
                        
                        if (!check_get(rmsg, msg.get_cstr(filename, &namelen), "setattr(filename)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&attrs), "setattr(attrs)"))
                            return;
                        if (!check_get(rmsg, msg.get_data(attrdata, &attrdatalen), "setattr(attrdatalen)"))
                            return; // this doesn't have to be copied
                        
                        if (attrdatalen > VFS_MAX_TRANSFER)
                            attrdatalen = VFS_MAX_TRANSFER;
                            
                        if (!0) ; else printf("vfs_setattr(name=%s, attr=0x%x, attrlen=%d)", filename, attrs, attrdatalen);
                        
                        int32_t ret = vfs.setattr(filename, attrs, attrdata, attrdatalen);

                        if (!0) ; else printf(" -> %d\n", ret);

                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_OPENFILE: // in: cstr filename, uint32 flags out: handle
                    {
                        uint32_t namelen = VFS_MAX_PATH;
                        char filename[VFS_MAX_PATH];
                        uint32_t flags;
                        
                        if (!check_get(rmsg, msg.get_cstr(filename, &namelen), "openfile(filename"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&flags), "openfile(flags)"))
                            return;
                        
                        if (!0) ; else printf("vfs_openfile(name=%s, flags=0x%x)", filename, flags);
                        
                        int32_t ret = vfs.openfile(filename, flags);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_CLOSEFILE: // in: int32 handle out: int32_t result
                    {
                        int32_t handle;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "closefile(handle)"))
                            return;
                        
                        if (!0) ; else printf("vfs_closefile(%d)", handle);
                        
                        int32_t ret = vfs.closefile(handle);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_WRITEFILE: // in: int32 handle, uint64_t offset, int32_t len, void* data, out: int32_t result
                    {
                        int32_t handle;
                        uint64_t offset;
                        void* data = transfer_buffer;       // todo - shared buffer for now 
                        uint32_t len = VFS_MAX_TRANSFER;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "writefile(handle)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint64(&offset), "writefile(offset)"))
                            return;
                        if (!check_get(rmsg, msg.get_data(data, &len), "writefile(data)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&len), "writefile(len)"))
                            return;
                        
                        if (len > VFS_MAX_TRANSFER)
                            len = VFS_MAX_TRANSFER;
                        
                        if (!0) ; else printf("vfs_writefile(handle=%d, offset=%"PRId64", len=%d)", handle, offset, len);
                        
                        int32_t ret = vfs.writefile(handle, offset, data, len);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_READFILE: // in: int32 handle, uint64_t offset, int32_t len, out: int32_t result, void* data 
                    {
                        int32_t handle;
                        uint64_t offset;
                        void* data = transfer_buffer; 
                        uint32_t len;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "readfile(handle)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint64(&offset), "readfile(offset)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint32(&len), "readfile(len)"))
                            return;
                        
                        if (len > VFS_MAX_TRANSFER)
                            len = VFS_MAX_TRANSFER;
                        
                        if (!0) ; else printf("vfs_readfile(handle=%d, offset=%"PRId64", len=%d)", handle, offset, len);

                        int32_t ret = vfs.readfile(handle, offset, data, len);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                        rmsg.put_data(data, len);
                    }
                    break;
                     
                    case VFS_GETFILESIZE: // in: int32_t handle out: int32_t ret, uint64_t size 
                    {
                        int32_t handle;
                        uint64_t size;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "getfilesize(handle)"))
                            return;
                        
                        if (!0) ; else printf("vfs_getfilesize(handle=%d)", handle);
                        
                        int32_t ret = vfs.getfilesize(handle, &size);
                        
                        if (!0) ; else printf(" -> (%d, size=%"PRId64")\n", ret, size);
                        
                        rmsg.put_int32(ret);
                        rmsg.put_uint64(size);
                    }
                    break;
                     
                    case VFS_SETFILESIZE: // in: int32_t handle, uint64_t size out: int32_t ret
                    {
                        int32_t handle;
                        uint64_t size;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "setfilesize(handle)"))
                            return;
                        if (!check_get(rmsg, msg.get_uint64(&size), "setfilesize(size)"))
                            return;
                        
                        if (!0) ; else printf("vfs_setfilesize(handle=%d, size=%"PRIu64")", handle, size);
                        
                        int32_t ret = vfs.setfilesize(handle, size);

                        if (!0) ; else printf(" -> %d\n", ret);
                                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_FILESYNC: // in: int32_t handle out: int32_t result 
                    {
                        int32_t handle;
                        
                        if (!check_get(rmsg, msg.get_int32(&handle), "filesync(handle)"))
                            return;
                        
                        if (!0) ; else printf("vfs_filesync(handle=%d)", handle);
                        
                        int32_t ret = vfs.filesync(handle);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_SYMLINK: // in: cstr filename, cstr symlink out: int32_t result
                    {
                        uint32_t namelen1 = VFS_MAX_PATH;
                        char filename[VFS_MAX_PATH];
                        uint32_t namelen2 = VFS_MAX_PATH;
                        char symlink[VFS_MAX_PATH];
                        
                        if (!check_get(rmsg, msg.get_cstr(filename, &namelen1), "symlink(filename)"))
                            return;
                        if (!check_get(rmsg, msg.get_cstr(symlink, &namelen2), "symlink(symlink)"))
                            return;
                        
                        if (!0) ; else printf("vfs_symlink(path=%s, symlink=%s)", filename, symlink);
                        
                        int32_t ret = vfs.symlink(filename, symlink);
                        
                        if (!0) ; else printf(" -> %d\n", ret);
                        
                        rmsg.put_int32(ret);
                    }
                    break;
                     
                    case VFS_READLINK: // in: cstr filename, int32 bufsiz out: cstr in buf 
                    {
                        uint32_t namelen = VFS_MAX_PATH;
                        char filename[VFS_MAX_PATH];
                        char* buf = (char*)transfer_buffer;
                        int bufsiz;
                        
                        if (!check_get(rmsg, msg.get_cstr(filename, &namelen), "readlink(filename)"))
                            return;
                        if (!check_get(rmsg, msg.get_int32(&bufsiz), "readlink(bufsiz)"))
                            return;
                        
                        // could use the transfer buffer
                        if (bufsiz > VFS_MAX_TRANSFER)
                            bufsiz = VFS_MAX_TRANSFER;
                        
                        if (!0) ; else printf("vfs_readlink(path=%s, bufsiz=%d)", filename, bufsiz);
                        
                        int32_t ret = vfs.readlink(filename, buf, bufsiz);
                        
                        if (!0) ; else printf(" -> (%d, buf=%s)\n", ret, buf);
                        
                        rmsg.put_int32(ret);
                        rmsg.put_data(buf, bufsiz);
                    }
                    break;
                    
                    default:
                        if (!0) ; else printf("Undefined VFS operation %d\n", vfsop);
                    break;            
                }
                
                *len_out = rmsg.get_size();                
            }
        };
        
        ProcessMessage *action;
        
        bool background;
    
#line 811 "./Linux-Release-GCC-4.1/gen/Component__VFS2_ClassDef.h"


    // find parameter name for a specific CADIFactory parameter ID
    std::map<MxU32,std::string> parameterId2parameterName__;

    // list of all CADI parameters
    std::vector<eslapi::CADIParameterInfo_t> parameterInfos__;


    // ================================================================================
    // methods
    // ================================================================================

    // constructor and destructor
    Component__VFS2(const char *argv, sg::SimulationContext* simulationContext, const sg::Params & params);
    ~Component__VFS2();

    // interface functions
    sg::SimulationContext* getSimulationContext() const { return simulationContext__; }

    // control port implementation
    void control_port__configure(const sg::Params& params);
    void control_port__loadApplicationFile(const std::string& filename);
    std::string control_port__getProperty(const std::string& propname);
    std::string control_port__bypass(const std::string&);
    void control_port__run();
    void control_port__stop();
    void control_port__idle();
    void control_port__quit();
    void control_port__getMxDI(std::map<std::string,eslapi::CADI*>*);
    void control_port__setSimulationEngine(SimulationEngine*);
    void control_port__populateCADIMap(std::map< std::string, eslapi::CAInterface* > &, std::string const &);
    void control_port__message(const std::string &msg, sg::message::MessageType msgType);
    std::string control_port__callSimEngine(const std::string&);
    void control_port__reset(int level);
    void control_port__terminate();

    // CADI Port implementations
    eslapi::CADIReturn_t cadiPort__GetParameters(MxU32 startIndex, MxU32 desiredNumOfParams, MxU32 *actualNumOfParams, eslapi::CADIParameterInfo_t *params);
    eslapi::CADIReturn_t cadiPort__GetParameterInfo(const std::string &parameterName, eslapi::CADIParameterInfo_t* param);
    eslapi::CADIReturn_t cadiPort__GetParameterValues (uint32_t parameterCount, uint32_t *actualNumOfParamsRead, eslapi::CADIParameterValue_t *paramValuesOut);
    eslapi::CADIReturn_t cadiPort__SetParameters(uint32_t count, eslapi::CADIParameterValue_t *params, eslapi::CADIFactoryErrorMessage_t *error);
    eslapi::CADIReturn_t cadiPort__GetProperty(const std::string& propertyName, std::string &value);
    void cadiPort__LoadApplicationFile(const std::string& filename);
    void cadiPort__GetApplicationsAndCommandLineParams(std::map<std::string, std::string>&applications2params_);

    // helper functions
    void insertCADIMap__(std::string prefix, std::map< std::string, eslapi::CAInterface*>&componentName2CADI);

    sg::accessfunc::AccessFuncResult parameter_read_func(uint32_t id, int64_t *data);
    sg::accessfunc::AccessFuncResult parameter_read_string_func(uint32_t id, std::string &data);
    sg::accessfunc::AccessFuncResult parameter_write_func(uint32_t id, const int64_t *data);
    sg::accessfunc::AccessFuncResult parameter_write_string_func(uint32_t id, const std::string &data);

    // dummy functions, mostly required by IsimMain (formerly InterpreterMain), will go away soon

    // May be required by TraceGen however that itself is obsolete
    MxU64 getInstructionCount() const { return 0; }
    // May be required by SystemGen however that itself is obsolete
    MxU64 getCycleCount() const { return 0; }

	void init();
	void terminate();
	void interconnect();
	void disconnect();
	void update();
	void communicate();
	void traceEndOfCycle();
	void loadApplicationFile(const std::string& filename);
	void reset(int level);
	void reset(int level, int /*argc*/, char** /*argv*/);
	bool save(MxODataStream& os);
	bool restore(MxIDataStream& is);
	void step();
	int32_t abstract_port__message__handle_message(const void* data, uint32_t len);
	void abstract_port__complete__setValue(uint32_t reply_len);

    void simHalt();
    void simRun();
    bool simIsRunning();
    void simShutdown();
    void simReset(uint32_t level);


private:
    // methods
    eslapi::CADI* obtainCADI__(const std::string &subcomp, const std::map< std::string, eslapi::CAInterface* > &componentName2CADI) const;
    static bool ForwardParameterValueToSubcomponent(CADIParameterProxy *proxy,
                                                    const char *param_name,
                                                    int64_t intVal,
                                                    const char *strVal);
    uint32_t paramNameToParamAccessFuncID(const std::string &name);

    void reset_resources__();
    void freeCADIResources__();


	ParameterFilter_messagebox_of_MessageBox_to_VFS2 parameterFilter_messagebox_of_MessageBox_to_VFS2__;


	CADIParameterProxy *cadiParameterProxy_messagebox_of_MessageBox_to_VFS2__;


    // definition of parameter IDs as constants for use in parameter access functions
	enum
	{
		PARAMETER_ID_mount = 0x10000033,
	};




};

} // namespace FVP_VE_Cortex_A15x1_NMS

#endif

