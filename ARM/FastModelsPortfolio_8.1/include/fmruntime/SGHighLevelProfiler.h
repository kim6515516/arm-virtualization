// Copyright 2010 ARM Limited. All rights reserved.
//
// high level time and virtual memory profiler utility class

#ifndef SGHighLevelProfiler_h_
#define SGHighLevelProfiler_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include "eslapi/eslapi_stdint.h"

#include "sg/SystemInclude.h"
#include "sg/MSCFixes.h"

#ifdef __unix
# include <sys/time.h>
#endif

class SGHighLevelProfiler
{
public:
    // constructor
    SGHighLevelProfiler(const char *instanceName = "(anon)", int width = 40): instanceName(instanceName), width(width),
                messagesAreEnabled(true)
    {
        startTime = startVMSize = 0;
        deltaTime = deltaVMSize = 0;
        start();
    }
    
    // (re)start measurememnt
    void start()
    {
        startTime = getTime();
        startVMSize = getVMSize();
    }
    
    // stop measurement and capture data (and restart next measurement)
    void stop()
    {
        uint64_t stopTime = getTime();
        uint64_t stopVMSize = getVMSize();
        deltaTime = stopTime - startTime;
        deltaVMSize = stopVMSize - startVMSize;
        startTime = stopTime;
        startVMSize = stopVMSize;
    }
        
    // get elapsed time (from start() or last stop() to stop()) in microsec
    uint64_t getTimeDelta() const { return deltaTime; }
    
    // get VM size delta in bytes
    int64_t getVMSizeDelta() const { return deltaVMSize; }
    
    // get formatted message
    std::string getMessage() const
    {
        char buf[80];
        snprintf(buf, sizeof(buf), "%7.3fs %10.3fMB", double(getTimeDelta())/1000000.0, double(getVMSizeDelta())/(1024.0*1024.0));
        return buf;
    }
    
    // stop and return formatted message
    std::string stopAndGetMessage()
    {
        stop();
        return getMessage();
    }

    // stop, restart and emit message
    void emit(const char *message, const char *name = 0)
    {
        std::string profStr = stopAndGetMessage();
        if (!messagesAreEnabled)
            return;
        char buf[4096];
        int pad = width - instanceName.length() - 2 - strlen(message) - 1;
        if (name)
            pad -= strlen(name) + 3;
        if (pad < 0)
            pad = 0;
        if (name)
            snprintf(buf, sizeof(buf), "%s: %s '%s'%*.*s %s\n", instanceName.c_str(), message, name, pad, pad, "", profStr.c_str());
        else
            snprintf(buf, sizeof(buf), "%s: %s%*.*s %s\n", instanceName.c_str(), message, pad, pad, "", profStr.c_str());
        printf("%s", buf);
    }

    // enable messages from emit()
    void enableMessages(bool enable = true)
    {
        messagesAreEnabled = enable;
    }

    // set first column width
    void setWidth(int width_)
    {
        width = width_;
    }

private:
    // private data
    uint64_t startTime;
    uint64_t startVMSize;
    uint64_t deltaTime;
    int64_t deltaVMSize;
    std::string instanceName;
    int width;
    bool messagesAreEnabled;
    
    // private methods
    
    // return current time in microseconds
    uint64_t getTime() const
    {
#ifdef WIN32
        return GetTickCount() * 1000;
#else
        struct timeval tv;
        if (gettimeofday(&tv, NULL) != 0) {
            return 0;
        }
        return (tv.tv_sec*1000000) + tv.tv_usec;
#endif
    }
    
    // return current VM size in bytes
    uint64_t getVMSize() const
    {
#ifdef WIN32
        MEMORYSTATUSEX m;
        m.dwLength = sizeof(m);
        if (!GlobalMemoryStatusEx(&m))
            return 0;
        return m.ullTotalVirtual - m.ullAvailVirtual;
#else
        // Linux: read /proc/self/status and loock for 'VmSize:'
        uint64_t mem = 0;
        FILE *f = fopen("/proc/self/status", "rb");
        if (f == 0)
            return 0;
        while (!feof(f))
        {
            char buf[80];
            if (fgets(buf, sizeof(buf), f) == 0)
                break;
            buf[sizeof(buf) - 1] = 0;
            if (strncmp(buf, "VmSize:", 7) == 0) {
                mem = strtoul(buf + 7, 0, 10) << 10;
                break;
            }
        }
        fclose(f);
        return mem;
#endif
    }
};

#endif

