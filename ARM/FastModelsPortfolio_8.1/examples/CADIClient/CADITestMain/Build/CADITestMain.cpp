/*

This confidential and proprietary software may be used only as
authorized by a licensing agreement from ARM Limited.

Copyright (c) 2008-2009 ARM Limited
All rights reserved.

The entire notice above must be reproduced on all authorised copies
and copies may only be made to the extent permitted by a licensing
agreement from ARM Limited.

*/

#ifdef WIN32
# include <Windows.h> // Sleep, CreateMutex, ...
#else
# include <pthread.h>
# include <unistd.h> // usleep
#endif

#include <string>
#include <assert.h>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "eslapi/CADIFactory.h"
#include "eslapi/CADI.h"

/////////////////////////////////////////////////////////////////////////////

//Class providing callbacks which are used by some classes of the CADI factory
//mechanism to report problems
class MyErrorCallback :
    public eslapi::CADIErrorCallback
{
    virtual eslapi::CAInterface * ObtainInterface(eslapi::if_name_t    ifName,
                                                  eslapi::if_rev_t     minRev,
                                                  eslapi::if_rev_t *   actualRev);

    virtual void Error(eslapi::CADIFactorySeverityCode_t severity,
                       eslapi::CADIFactoryErrorCode_t errorCode,
                       uint32_t erroneousParameterId,
                       const char *message);
};


//used to check if the target provides the correct interface of a feasible revision
eslapi::CAInterface *
MyErrorCallback::ObtainInterface(eslapi::if_name_t    ifName,
                                 eslapi::if_rev_t     minRev,
                                 eslapi::if_rev_t *   actualRev)
{
    if((strcmp(ifName,IFNAME()) == 0) && // if someone is asking for the matching interface
       (minRev <= IFREVISION())) // and the revision of this interface implementation is
        // at least what is being asked for
    {
        if (actualRev) // make sure this is not a NULL pointer
        {
            *actualRev = IFREVISION();
        }
        //DuplicateRef();
        return this;
    }
    if((strcmp(ifName, CAInterface::IFNAME()) == 0) &&
       minRev <= CAInterface::IFREVISION())
    {
        if (actualRev != NULL)
        {
            *actualRev = CAInterface::IFREVISION();
        }
        //DuplicateRef();
        return this;
    }
    return NULL;
}

void
MyErrorCallback::Error(eslapi::CADIFactorySeverityCode_t severity,
                       eslapi::CADIFactoryErrorCode_t errorCode,
                       uint32_t erroneousParameterId,
                       const char *message)
{
    printf("Error callback: Severity: %u ErrorCode: %u  ParameterID: %u\n"
           "Message: %s\n", severity, errorCode, erroneousParameterId, message);
}

/////////////////////////////////////////////////////////////////////////////

//Objects of this class are used to allow the caller receiving messages from
//the targeted CADI broker/factory/simulation. This may be simple messages as
//well as messages concerning the simulation management.
class MySimCallback :
    public eslapi::CADISimulationCallback
{
    virtual eslapi::CAInterface * ObtainInterface(eslapi::if_name_t    ifName,
                                                  eslapi::if_rev_t     minRev,
                                                  eslapi::if_rev_t *   actualRev);

    virtual void simMessage(const char *message);
    virtual void simShutdown();
    virtual void simKilled();
};

//used to check if the target provides the correct interface of a feasible revision
eslapi::CAInterface *
MySimCallback::ObtainInterface(eslapi::if_name_t    ifName,
                               eslapi::if_rev_t     minRev,
                               eslapi::if_rev_t *   actualRev)
{
    if((strcmp(ifName,IFNAME()) == 0) && // if someone is asking for the matching interface
       (minRev <= IFREVISION())) // and the revision of this interface implementation is
        // at least what is being asked for
    {
        if (actualRev) // make sure this is not a NULL pointer
        {
            *actualRev = IFREVISION();
        }
        //DuplicateRef();
        return this;
    }
    if((strcmp(ifName, CAInterface::IFNAME()) == 0) &&
       minRev <= CAInterface::IFREVISION())
    {
        if (actualRev != NULL)
        {
            *actualRev = CAInterface::IFREVISION();
        }
        //DuplicateRef();
        return this;
    }
    return NULL;
}

void
MySimCallback::simMessage(const char *message)
{
    printf("The simulation send the following message:\n%s\n", message);
}

void
MySimCallback::simShutdown()
{
    printf("The simulation wants to shut down.");
}

void
MySimCallback::simKilled()
{
    printf("The simulation had a fatal error. Must not do any calls to the sim now.");
}

/////////////////////////////////////////////////////////////////////////////


// Class providing callbacks which may be registered to the target. The
// implementation of these callbacks needs to guarantee thread-safety. This is
// implemented here by using a mutex
class MyCADICallback :
    public eslapi::CADICallbackObj
{
public:
    MyCADICallback()
    : currentMode(0),
      modeChangeCallbackCounter(0)
    {
#ifdef WIN32
        lock = CreateMutex(NULL, false, NULL);
#else
        pthread_mutex_init(&lock, 0);
#endif
    }

    ~MyCADICallback()
    {
#ifdef WIN32
        CloseHandle(lock);
#else
        pthread_mutex_destroy(&lock);
#endif        
    }

    //used to check if the target provides the correct interface of a feasible revision
    virtual eslapi::CAInterface * ObtainInterface(eslapi::if_name_t    ifName,
                                                  eslapi::if_rev_t     minRev,
                                                  eslapi::if_rev_t *   actualRev);

    virtual uint32_t appliOpen(const char * /*sFileName*/,
                               const char * /*mode*/)
    {
        return (uint32_t)-1;
    }

    virtual void appliInput(uint32_t /*streamId*/,
                            uint32_t /*count*/,
                            uint32_t * /*actualCount*/,
                            char * /*buffer*/)
    {}

    virtual void appliOutput(uint32_t /*streamId*/,
                             uint32_t /*count*/,
                             uint32_t * /*actualCount*/,
                             const char * /*buffer*/)
    {}

    virtual uint32_t appliClose(uint32_t /*streamID*/)
    {
        return (uint32_t)-1;
    }

    virtual void doString(const char * stringArg)
    {
        printf("...doString('%s') callback received.\n\n", stringArg);
    }

    virtual void modeChange(uint32_t newMode,
                            eslapi::CADIBptNumber_t bptNumber)
    {
        const char *mode2string[6] = 
        {
            "Stop",
            "Run",
            "Bpt",
            "Error",
            "HighLevelStep",
            "RunUnconditionally"
        };

        if (newMode > 5)
        {
        printf("ERROR: Unknown execution mode (%u) received!\n",
               newMode);
        }

        assert(newMode < 6);
        if (newMode == eslapi::CADI_EXECMODE_Bpt)
        {
            printf("...modeChange(%s, %d) callback received.\n\n",
                   mode2string[newMode],
                   bptNumber);
        }
        else
        {
            printf("...modeChange(%s) callback received.\n\n",
                   mode2string[newMode]);
        }

        SetCurrentMode(newMode);
        modeChangeCallbackCounter++;
    }

    virtual void reset(uint32_t resetLevel)
    {
        printf("...reset occured, level = %u\n\n", resetLevel);
    }

    virtual void cycleTick(void) // deprecated
    {}

    virtual void killInterface(void)
    {}

    virtual uint32_t bypass(uint32_t /*commandLength*/,
                            const char * /*command*/,
                            uint32_t /*maxResponseLength*/,
                            char * /*response*/)
    {
        return 0;
    }

    virtual uint32_t lookupSymbol (uint32_t /*symbolLength*/,
                                   const char * /*symbol*/,
                                   uint32_t /*maxResponseLength*/,
                                   char * /*response*/)
    {
        return 0;
    }

    virtual void refresh(uint32_t /*refreshReason*/)
    {}

public:
#ifdef WIN32    
#  define LOCK_MUTEX(a) WaitForSingleObject(a, INFINITE)
#  define UNLOCK_MUTEX(a) ReleaseMutex(a)
#else
#  define LOCK_MUTEX(a) pthread_mutex_lock(&a)
#  define UNLOCK_MUTEX(a) pthread_mutex_unlock(&a)
#endif

    // small auxiliary methods to check the state of the target as indicated by callbacks
    void SetCurrentMode(uint32_t new_mode)
    {
        LOCK_MUTEX(lock);
        currentMode = new_mode;
        UNLOCK_MUTEX(lock);
    };

    uint32_t GetCurrentMode()
    {
        LOCK_MUTEX(lock);
        uint32_t result = currentMode;
        UNLOCK_MUTEX(lock);
        return result;
    };

    uint32_t GetModeChangeCallbackCounter()
    {
        LOCK_MUTEX(lock);
        uint32_t result = modeChangeCallbackCounter;
        UNLOCK_MUTEX(lock);
        return result;
    };

    void ClearModeChangeCallbackCounter()
    {
        LOCK_MUTEX(lock);
        modeChangeCallbackCounter = 0;
        UNLOCK_MUTEX(lock);
    };

private:
#ifdef WIN32
    HANDLE lock;
#else
    pthread_mutex_t lock;
#endif

    volatile uint32_t currentMode;
    volatile uint32_t modeChangeCallbackCounter;
};

//used to check if the target provides the correct interface of a feasible revision
eslapi::CAInterface *
MyCADICallback::ObtainInterface(eslapi::if_name_t    ifName,
                                eslapi::if_rev_t     minRev,
                                eslapi::if_rev_t *   actualRev)
{
    if((strcmp(ifName,IFNAME()) == 0) && // if someone is asking for the matching interface
       (minRev <= IFREVISION())) // and the revision of this interface implementation is
        // at least what is being asked for
    {
        if (actualRev) // make sure this is not a NULL pointer
        {
            *actualRev = IFREVISION();
        }
        //DuplicateRef();
        return this;
    }
    if((strcmp(ifName, CAInterface::IFNAME()) == 0) &&
       minRev <= CAInterface::IFREVISION())
    {
        if (actualRev != NULL)
        {
            *actualRev = CAInterface::IFREVISION();
        }
        //DuplicateRef();
        return this;
    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////


void PrintUsage(char* applName)
{
    printf("Usage: %s [{-s id|-n name}] [-t id]\n"
           "\t-s\t : The simulation number (index) to connect to.\n"
           "\t-n\t : The name of the simulation to connect to.\n\t\t   This is used in preference to the simulation number\n"
           "\t-t\t : The target number (index) to connect to. If this argument is not\n\t\t   set or set to an unknown index the first available target of the\n\t\t   connected simulation is addressed.\n"
           "\t-h,-?\t : This help.\n\n"
           "If neither -s nor -n arguments are present,\n\t\t   the first available simulation is addressed.\n",
           applName);
}


const char* CADIReturnToString(eslapi::CADIReturn_t status)
{
    static const char* returnString[eslapi::CADI_STATUS_PermissionDenied + 1] = 
    {
        "CADI_STATUS_OK", 
        "CADI_STATUS_GeneralError", 
        "CADI_STATUS_UnknownCommand", 
        "CADI_STATUS_IllegalArgument", 
        "CADI_STATUS_CmdNotSupported", 
        "CADI_STATUS_ArgNotSupported", 
        "CADI_STATUS_InsufficientResources", 
        "CADI_STATUS_TargetNotResponding", 
        "CADI_STATUS_TargetBusy", 
        "CADI_STATUS_BufferSize", 
        "CADI_STATUS_SecurityViolation", 
        "CADI_STATUS_PermissionDenied" 
    };
    if (status > eslapi::CADI_STATUS_PermissionDenied)
    {
        printf("Unkown return status (%u).\n",
               status);
        return "Unknown status!";
    }
    return returnString[status];
}


const char* CADIValueDataTypeToString(eslapi::CADIValueDataType_t type)
{
    static const char* returnString[eslapi::CADI_PARAM_INT + 1] = 
    {
        "CADI_PARAM_INVALID", 
        "CADI_PARAM_STRING",
        "CADI_PARAM_BOOL",
        "CADI_PARAM_INT"
    };
    if (type > eslapi::CADI_PARAM_INT)
    {
        printf("Unkown data type (%u).\n",
               type);
        return "Unknown type!";
    }
    return returnString[type];
}


// Detects currently running simulations and selects one of them. Returns a pointer to 
// the selected CADISimulation.
eslapi::CADISimulation* GetCADISimulationFromClient(eslapi::CADIBroker* broker,
                                                    uint32_t& simulationNum,
                                                    std::string const & simulationName,
                                                    eslapi::CADIErrorCallback* errorCallback,
                                                    eslapi::CADISimulationCallback* simCallback,
                                                    char simCallbackEnable[])
{
    printf("\n***Detecting running simulations...\n");

    // Use fixed upper limit for number of simulations
    const uint32_t desiredNumberOfSimulations = 100;
    eslapi::CADISimulationInfo_t simulationList [desiredNumberOfSimulations];
    // NOTE: Actual number of simulations might be smaller than the desired number of simulations!
    uint32_t actualNumberOfSimulations = 0;
  
    for (int retries = 0 ; retries < 60 ; ++retries)
    {
        // The following call gets information on already running simulations provided through the CADI client
        eslapi::CADIReturn_t status = broker->GetSimulationInfos(0, // startTargetInfoIndex
                                                                 desiredNumberOfSimulations, 
                                                                 simulationList,
                                                                 &actualNumberOfSimulations);

        if (status != eslapi::CADI_STATUS_OK)
        {
            printf("ERROR: Getting simulation infos from CADI Broker failed. Please check if there is a running CADI Server (Error status is '%s')\n", CADIReturnToString(status));
            assert(eslapi::CADI_STATUS_OK == status);
            exit(1);
        }
        if (actualNumberOfSimulations != 0)
            break;
                        
        // wait 1s
#ifndef WIN32
            usleep(1000000);
#else
            Sleep(1000);
#endif //WIN32
    }
    
    if (actualNumberOfSimulations == 0)
    {
        printf("ERROR: CADI Broker returned 0 simulation infos. Please check if there is a running CADI Server.\n");
        assert(actualNumberOfSimulations > 0);
        exit(1);
    }

    //Printing information about the detected running CADI Simulations.
    printf("\tDetected %u Simulations:\n\n", actualNumberOfSimulations);
    unsigned int simualationToConnectTo = -1;
    for(unsigned int i=0; i < actualNumberOfSimulations; ++i)
    {
        printf("\tSimulation #%u: ID: %u Name: %s\n\t   Description: %s\n",
               i,
               simulationList[i].id,
               simulationList[i].name,
               simulationList[i].description);

        if (simulationName.length() > 0)
        {
            if (simulationName == simulationList[i].name)
                simualationToConnectTo = i;
        }
    }

    if (simualationToConnectTo == (unsigned int) -1)
    {
        if (simulationName.length() > 0)
        {
            printf("\nWARNING: The simulation name specified with option ('-n %s') is not available. Attempting to connect to simulation index %u instead.\n\n",
                   simulationName.c_str(),
                   simulationNum);
        }
        simualationToConnectTo = simulationNum;
    }

    // Does a simulation with the requested index exist? If not, we connect to the first available alternative
    if (simualationToConnectTo > (actualNumberOfSimulations - 1))
    {
        printf("\nWARNING: The simulation index specified with option ('-s %u') is not available. Available simulation indizes are 0 to %u. Connecting to simulation index 0 instead.\n\n",
               simualationToConnectTo,
               actualNumberOfSimulations - 1);
        simualationToConnectTo = 0;
    }

    printf("\n***Connecting to simulation #%u ...\n",
           simualationToConnectTo);

    // Query pointer to the requested CADISimulation. This can be used then to connect to one or more of its CADI target. 
    // The returned pointer is of type CADISimulation*. ObtainInterface() should be used in order to check if the returned
    // pointer is a CADISimulation of the desired revision.
    return broker->SelectSimulation(simulationList[simualationToConnectTo].id,
                                    errorCallback,
                                    simCallback,
                                    simCallbackEnable);
}


// Reads and prints all register information and values
void ReadTargetRegisters(eslapi::CADI* cadi,
                         eslapi::CADIRegGroup_t register_groups[],
                         uint32_t numberOfRegisterGroups)
{
    eslapi::CADIReturn_t status;

    printf("\n***Current register information and contents...\n");
    for (unsigned int i=0; i < numberOfRegisterGroups; ++i)
    {
        printf("\n\tRegister Group #%u: ID:%u   Name:%s   RegsInGroup:%u\n\n",
               i,
               register_groups[i].groupID,
               register_groups[i].name,
               register_groups[i].numRegsInGroup);


        // Get the register group's register map
        eslapi::CADIRegInfo_t* registerInfos = new eslapi::CADIRegInfo_t[register_groups[i].numRegsInGroup]();
        uint32_t actualNumberOfRegInfos = 0;

        status = cadi->CADIRegGetMap(register_groups[i].groupID,
                                     0, //startRegisterIndex
                                     register_groups[i].numRegsInGroup, // desired number of register infos
                                     &actualNumberOfRegInfos,  // actual number which might be smaller than the desired number
                                     registerInfos);

        if (status != eslapi::CADI_STATUS_OK)
        {
            printf("ERROR: Reading register map for register group '%s' (ID: %u) failed! Error status is '%s'.\n",
            register_groups[i].name,
            register_groups[i].groupID,
            CADIReturnToString(status));
            delete[] registerInfos;
            assert(eslapi::CADI_STATUS_OK == status);
            printf("Leaving 'ReadTargetRegisters()'...\n");
            return;
        }


        if (actualNumberOfRegInfos != register_groups[i].numRegsInGroup)
        {
            printf("ERROR: Reading register map for register group '%s' (ID: %u) returned a different number of registers (%u) than expected (%u).\n",
                   register_groups[i].name,
                   register_groups[i].groupID,
                   actualNumberOfRegInfos,
                   register_groups[i].numRegsInGroup);
            delete[] registerInfos;
            assert(actualNumberOfRegInfos == register_groups[i].numRegsInGroup);
            printf("Leaving 'ReadTargetRegisters()'...\n");
            return;
        }

        for (unsigned int j=0; j < actualNumberOfRegInfos; ++j)
        {
            printf("\t\tRegister #%u: \tRegNumber:%u \tName:%s  \tValue:",
                   j,
                   registerInfos[j].regNumber,
                   registerInfos[j].name);

            // String registers might require more than one CADIRegRead as a single call is limited to 16 characters. The individual 16 byte chunks are addressed by 
            // CADIReg_t::offset128 (see below). CADIRegRead is called until a 0-terminated string is received. To get the full string, the received substrings 
            // must be concetenated.
            if (registerInfos[j].display == eslapi::CADI_REGTYPE_STRING)
            {
                std::string registerString("");
                bool stringFinished = false;
                uint32_t offset128 = 0; // counter for offset128 specifying the 16 byte chunk to be queried by the individual CADIRegRead
                while(!stringFinished) // Issue CADIRegRead calls until the returned string is 0-terminated
                {
                    uint32_t numRegsRead = 0;
                    eslapi::CADIReg_t reg;
                    reg.regNumber = registerInfos[j].regNumber; // the register number must be set prior calling CADIRegRead to identify the register to be read
                    reg.offset128 = offset128++;  // identify 16 byte chunk 

                    status = cadi->CADIRegRead(1, // query a single set of register data
                                               &reg,
                                               &numRegsRead,
                                               0); //doSideEffects
                    
                    if (status != eslapi::CADI_STATUS_OK)
                    {
                        printf("ERROR: Reading register '%s' (RegNumber %u) failed. Return type is '%s'\n",
                               registerInfos[j].name,
                               registerInfos[j].regNumber,
                               CADIReturnToString(status));
                        delete[] registerInfos;
                        assert(eslapi::CADI_STATUS_OK == status);
                        printf("Leaving 'ReadTargetRegisters()'...\n");
                        return;
                    }

                    if (numRegsRead != 1)
                    {
                        printf("ERROR: Reading register '%s' (RegNumber %u) read a different number of registers (%u) than expected (1).\n",
                               registerInfos[j].name,
                               registerInfos[j].regNumber,
                               numRegsRead);
                        delete[] registerInfos;
                        assert(numRegsRead == 1);
                        printf("Leaving 'ReadTargetRegisters()'...\n");
                        return;
                    }

                    for (unsigned int k=0; k < sizeof(reg.bytes); ++k)
                    {
                        if (reg.bytes[k] == '\0')
                        {
                            stringFinished = true;
                            break;
                        }
                        registerString += reg.bytes[k];
                    }
                }
                printf("'%s'\n", registerString.c_str());
            }
            else
            {
                // Read a non-string register
                printf("0x");
                uint32_t regWidthInBytes = (registerInfos[j].bitsWide + 7)/8;
                // Each CADIReg_t can be used to read a maximum of 16 bytes. If larger, the offset128 can be used to specify the 16 byte portion for the individual CADIRegRead call
                uint32_t numberOf128BitBlocks = (regWidthInBytes + 15)/16;  

                for (unsigned int offset128 = 1; offset128 <= numberOf128BitBlocks; ++offset128) 
                {
                    uint32_t numRegsRead = 0;
                    eslapi::CADIReg_t reg;
                    reg.regNumber = registerInfos[j].regNumber;
                    // CADIReg_t holds the data in little endianess. in order to correctly present the value, we have to start with the most significant bytes
                    reg.offset128 = numberOf128BitBlocks - offset128;

                    status = cadi->CADIRegRead(1, // Query for just one register 
                                               &reg,
                                               &numRegsRead,
                                               0); //doSideEffects

                    if (status != eslapi::CADI_STATUS_OK)
                    {
                        printf("ERROR: Reading string register '%s' (RegNumber %u) failed. Return type is '%s'\n",
                               registerInfos[j].name,
                               registerInfos[j].regNumber,
                               CADIReturnToString(status));
                        delete[] registerInfos;
                        assert(eslapi::CADI_STATUS_OK == status);
                        printf("Leaving 'ReadTargetRegisters()'...\n");
                        return;
                    }

                    if (numRegsRead != 1)
                    {
                        printf("ERROR: Reading string register '%s' (RegNumber %u) with offset %u read a different number of registers (%u) than expected (1).\n",
                               registerInfos[j].name,
                               registerInfos[j].regNumber,
                               reg.offset128,
                               numRegsRead);
                        delete[] registerInfos;
                        assert(numRegsRead == 1);
                        printf("Leaving 'ReadTargetRegisters()'...\n");
                        return;
                    }

                    for (unsigned int k = 1; k <= regWidthInBytes; ++k)
                    {
                        printf("%02x", reg.bytes[regWidthInBytes - k]);
                    }
                }
                printf("\n");
            }
        }
        delete[] registerInfos;
        printf("\n");
    }
}


void ReadTargetMemories(eslapi::CADI* cadi,
                        eslapi::CADIMemSpaceInfo_t memory_spaces[],
                        uint32_t numberOfMemorySpaces)
{
    eslapi::CADIReturn_t status;


    // Iterating over each available memory space
    printf("\n***Current memory block information and contents of each block's first 20 bytes...\n");
    for (unsigned int i = 0; i < numberOfMemorySpaces; i++)
    {
        // Print out some of the memory space information
        printf("\n\tMemory Space #%u: ID:%u   Name:%s   bitsPerMau:%u   minAddress:0x%08x%08x   maxAddress:0x%08x%08x   nrMemBlocks:%u\n",
               i,
               memory_spaces[i].memSpaceId,
               memory_spaces[i].memSpaceName,
               memory_spaces[i].bitsPerMau,
               (uint32_t)(memory_spaces[i].minAddress >> 32),
               (uint32_t)(memory_spaces[i].minAddress),
               (uint32_t)(memory_spaces[i].maxAddress >> 32),
               (uint32_t)(memory_spaces[i].maxAddress),
               memory_spaces[i].nrMemBlocks);

        // Prepare data for getting the memory block information for the current memory space.
        uint32_t actualNumOfMemBlocks = 0;
        eslapi::CADIMemBlockInfo_t *memory_blocks = new eslapi::CADIMemBlockInfo_t[memory_spaces[i].nrMemBlocks];

        status = cadi->CADIMemGetBlocks(memory_spaces[i].memSpaceId,
                                        0, //memBlockIndex
                                        memory_spaces[i].nrMemBlocks,
                                        &actualNumOfMemBlocks,
                                        memory_blocks);

        // Check the return status.
        if (status != eslapi::CADI_STATUS_OK)
        {
            printf("ERROR: Retrieving memory block information for memory space '%s' (ID: %u) failed! Error staus is '%s'.\n",
                   memory_spaces[i].memSpaceName,
                   memory_spaces[i].memSpaceId,
                   CADIReturnToString(status));
            delete[] memory_blocks;
            assert(eslapi::CADI_STATUS_OK == status);
            printf("Leaving 'ReadTargetMemories()'...\n");
            return;
        }

        // Check if all requested memory blocks have been returned
        if (actualNumOfMemBlocks != memory_spaces[i].nrMemBlocks)
        {
            printf("ERROR: Retrieving memory block information for memory space '%s' (ID: %u) returned a different number of registers (%u) than expected (%u).\n",
                   memory_spaces[i].memSpaceName,
                   memory_spaces[i].memSpaceId,
                   actualNumOfMemBlocks,
                   memory_spaces[i].nrMemBlocks);
            delete[] memory_blocks;
            assert(actualNumOfMemBlocks == memory_spaces[i].nrMemBlocks);
            printf("Leaving 'ReadTargetMemories()'...\n");
            return;
        }

        // Iterating over all available memory blocks of the current memory space.
        for (unsigned int j = 0; j < actualNumOfMemBlocks; j++)
        {
            printf("\n\t\tMemory Block #%u: ID:%u   Name:%s   startAddr:0x%08x%08x   endAddr:0x%08x%08x\n",
                   j,
                   memory_blocks[j].id,
                   memory_blocks[j].name,
                   (uint32_t)(memory_blocks[j].startAddr >> 32),
                   (uint32_t)(memory_blocks[j].startAddr),
                   (uint32_t)(memory_blocks[j].endAddr >> 32),
                   (uint32_t)(memory_blocks[j].endAddr));


            // Check if the current memory block addressed for read accesses.
            if (memory_blocks[j].readWrite == eslapi::CADI_MEM_WriteOnly)
            {
                // Memory block is write-only
                printf("WARNING: Memory Block is of type \"CADI_MEM_WriteOnly\", cannot read it!\n");
            }
            else
            {
                // Reading the first 20 units of the memory block. Starting from the beginning of the memory block.
                eslapi::CADIAddrComplete_t startAddress;
                //startAddress.overlay set to default value by constructor of CADIAddrComplete_t, not supported by model
                startAddress.location.space = memory_spaces[i].memSpaceId;
                startAddress.location.addr  = memory_blocks[j].startAddr;

                uint32_t unitsToRead = 20; // First 20 units of target are going to be read

                // Read the entire memory block if it is smaller than 20 units
                if ((memory_blocks[j].endAddr - memory_blocks[j].startAddr) < unitsToRead)
                    unitsToRead = (uint32_t)(memory_blocks[j].endAddr - memory_blocks[j].startAddr); // Type cast is safe, difference is maximum 20

                // Convert bits per Minimum Access Unit (MAU) to bytes per MAU. The resulting number must always be a supported multiple of MAU.
                uint32_t unitSizeInBytes = (memory_spaces[i].bitsPerMau + 7)/8;
                uint32_t actualNumOfUnitsRead = 0;
                uint8_t  doSideEffects = 0; // Side effects are omitted (target has to decide which side effects are mandatory).
                uint32_t memAccessInBytes = unitsToRead * unitSizeInBytes;

                //Allocating and initializing data buffer for memory read access
                uint8_t  *data = new uint8_t[memAccessInBytes];
                memset(data, 0, memAccessInBytes);

                // Do the read access
                status = cadi->CADIMemRead(startAddress,
                                           unitsToRead,
                                           unitSizeInBytes,
                                           data,
                                           &actualNumOfUnitsRead,
                                           doSideEffects);


                // Check return status
                if (status != eslapi::CADI_STATUS_OK)
                {
                    printf("ERROR: Reading %u units of %u bytes starting from address 0x%08x%08x of memory block '%s' (ID %u) failed. Return type is '%s'\n",
                           unitsToRead,
                           unitSizeInBytes,
                           (uint32_t)(startAddress.location.addr >> 32),
                           (uint32_t)(startAddress.location.addr),
                           memory_blocks[j].name,
                           memory_blocks[j].id,
                           CADIReturnToString(status));
                    // Print out Errors for the read memory contents
                    for (unsigned int k = 0; k < unitsToRead; k++)
                    {
                        if ((k%5) == 0)
                        {
                            uint64_t displayAddr = startAddress.location.addr + k;
                            printf("\n\t\t0x%08x%08x",
                                   (uint32_t)(displayAddr >> 32),
                                   (uint32_t)(displayAddr));
                        }
                        printf("\tError");
                    }
                    printf("\n\n");
                    delete[] memory_blocks;
                    delete[] data;
                    return;
                }


                // Check if all requested units were read
                if (actualNumOfUnitsRead != unitsToRead)
                {
                    printf("ERROR: Less units (%u) of %u bytes than requested (%u) have been read starting from address 0x%08x%08x of memory block '%s' (ID %u).\n",
                           actualNumOfUnitsRead,
                           unitSizeInBytes,
                           unitsToRead,
                           (uint32_t)(startAddress.location.addr >> 32),
                           (uint32_t)(startAddress.location.addr),
                           memory_blocks[j].name,
                           memory_blocks[j].id);
                    delete[] memory_blocks;
                    delete[] data;
                    assert(actualNumOfUnitsRead == unitsToRead);
                    printf("Leaving 'ReadTargetMemories()'...\n");
                    return;
                }
                
                // Print out the read memory contents
                for (unsigned int k = 0; k < actualNumOfUnitsRead; k++)
                {
                    if ((k%5) == 0)
                    {
                        uint64_t displayAddr = startAddress.location.addr + k;
                        printf("\n\t\t0x%08x%08x",
                               (uint32_t)(displayAddr >> 32),
                               (uint32_t)(displayAddr));
                    }
                    printf("\t%02x", data[k]);
                }
                printf("\n\n");


                // Free the data buffer of the read access
                delete[] data;
                data = 0;
            }
        }

        // Free the memory allocated for the memory block information
        delete[] memory_blocks;
    }
}


// Helper function which searches for a register named 'name' in given array of rgister infos of size 'numberOfRegs'.
// Returns 0 if no register with the specified name was found 
eslapi::CADIReg_t*
GetCADIRegByName(const char* name,
                 eslapi::CADIRegInfo_t *regs,
                 uint32_t numberOfRegs)
{
    for (unsigned int i=0; i < numberOfRegs; ++i)
    {
        if (strstr(regs[i].name, name) != 0) /* if the requested name is part of the register's name;
                                                if for example selecting a system's top component, the 
                                                name will consist of "componentName / registerName" */
        {
            eslapi::CADIReg_t* newReg = new eslapi::CADIReg_t();
            newReg->regNumber = regs[i].regNumber;
            //the other values of "newReg" are already initialized by the CADIReg_t's constructor
            return newReg;
        }
    }
    return NULL; //register was not found
}


int
main(int argc, char *argv[])
{
    unsigned int simulation_num = 0;
    unsigned int target_num = 0;
    std::string simulation_name;
    
    int cntOptions;
    for(cntOptions = 1;cntOptions < argc; cntOptions++)
    {
        if (argv[cntOptions][0] == '-')
        {
            switch(argv[cntOptions][1])
            {
                case 's':
                    if (argc <= cntOptions + 1)
                    {
                        printf("\n'-s': Missing simulation index argument.\n\n");
                        PrintUsage(argv[0]);
                        return 1;
                    }
                    simulation_num = atoi(argv[cntOptions + 1]);
                    break;
                case 'n':
                    if (argc <= cntOptions + 1)
                    {
                        printf("\n'-n': Missing simulation name argument.\n\n");
                        PrintUsage(argv[0]);
                        return 1;
                    }
                    simulation_name = argv[cntOptions + 1];
                    break;
                case 't':
                    if (argc <= cntOptions + 1)
                    {
                        printf("\n'-t': Missing target index argument.\n\n");
                        PrintUsage(argv[0]);
                        return 1;
                    }
                    target_num = atoi(argv[cntOptions + 1]);
                    break;
                case 'h':
                case '?':
                default:
                    PrintUsage(argv[0]);
                    return 1;
            }
        }
    }

    printf("\n\n*********Starting Application '%s'*********\n\n",
           argv[0]);


    // Obtain the CADI 2.0 entry symbol:

    // Obtain the CADI 2.0 broker: It is required to create new simulations or connect to existing ones.
    // Actually, the returned pointer is of type CAInterface* which is a base class for the CADIBroker
    // class. Its ObtainInterface() method has to be called before casting it to the desired CADIBroker*
    // type.
    eslapi::CAInterface *ca_interface = NULL;

    printf("\n***Creating CADI Broker...\n");

    // Use the 'CreateCADIBroker' function from the statically linked CADI Client.
    ca_interface = CreateCADIBroker();

    if (ca_interface == NULL)
    {
        printf("ERROR: Calling 'CreateCADIBroker' in order to create a CADI Broker failed.\n");
        assert(ca_interface);
        exit(1);
    }

    // Call ObtainInterface to check whether to created CADIBroker provides the correct interface with the desired revision
    uint32_t broker_revision = 0;
    ca_interface = ca_interface->ObtainInterface("eslapi.CADIBroker2", 0, &broker_revision);

    if (ca_interface == NULL)
    {
        printf("ERROR: Obtaining CADI interface from the CADI Broker object failed. Please check if the model library supports the requested interface 'eslapi.CADIBroker2' and the requested revision.\n");
        assert(ca_interface);
        exit(1);
    }

    // Now is safe to cast the CAInterface pointer to a CADIBroker pointer.
    eslapi::CADIBroker *broker = static_cast<eslapi::CADIBroker *>(ca_interface);

    printf("\tSuccessfully created CADI Broker.\n");

    // Callback objects and enable vector required for instantiating/selecting a CADISimulation.
    eslapi::CADIErrorCallback *error_callback = new MyErrorCallback();
    eslapi::CADISimulationCallback *sim_callback = new MySimCallback();
    char sim_callbacks_enable[eslapi::CADI_SIM_CB_Count] = {1, 1, 1}; // register all simulation callbacks simMessage(), simShutdown() and simKilled()


    // We need to detect running CADI Servers with the CADI Client and connect to a running simulation.
    ca_interface = GetCADISimulationFromClient(broker,
                                               simulation_num,
                                               simulation_name,
                                               error_callback,
                                               sim_callback,
                                               sim_callbacks_enable);
    
    if (ca_interface == NULL)
    {
        printf("ERROR: Getting simulation #%u failed.\n", simulation_num);
        assert(ca_interface);
        exit(1);
    }

    // Use ObtainInterface to check whether to CAInterface pointer is a CADISimulation with the correct revision
    uint32_t simulation_revision = 0;
    ca_interface = ca_interface->ObtainInterface("eslapi.CADISimulation2", 0, &simulation_revision);
    if (ca_interface == NULL)
    {
        printf("ERROR: Obtaining CADI interface from CADI simulation object failed. Please check if the model library supports the requested interface 'eslapi.CADISimulation2' and the requested revision.\n");
        assert(ca_interface);
        exit(1);
    }

    // Now cast the CAInterface pointer to a CADISimulation pointer.
    eslapi::CADISimulation *simulation = static_cast<eslapi::CADISimulation *>(ca_interface);


    printf("\n***Retrieving information about available CADI targets from CADI Simulation...\n");


    // Now query for CADI target information for all targets present in the selected CADISimulation.
    // We do not know the number of targets and use a fixed upper limit of 100. 'actualNumberOfTargetInfos' will return
    // the actual number of CADT targets.
    const uint32_t desiredNumberOfTargetInfos = 100;
    uint32_t actualNumberOfTargetInfos = 0;
    eslapi::CADITargetInfo_t target_infos[desiredNumberOfTargetInfos];

    // Getting information on targets available for this CADISimulation.
    eslapi::CADIReturn_t status = simulation->GetTargetInfos(0, // startTargetInfoIndex
                                                             desiredNumberOfTargetInfos,
                                                             target_infos,
                                                             &actualNumberOfTargetInfos);
    
    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Getting target infos for simulation #%u failed. Return type is '%s'\n",
        simulation_num,
        CADIReturnToString(status));
        assert(eslapi::CADI_STATUS_OK == status);
        exit(1);
    }

    if (actualNumberOfTargetInfos == 0)
    {
        printf("ERROR: CADISimulation returned 0 targets.\n");
        assert(actualNumberOfTargetInfos > 0);
        exit(1);
    }


    printf("\tDetected %u targets for simulation #%u:\n\n",
           actualNumberOfTargetInfos,
           simulation_num);

    for(unsigned int i=0; i < actualNumberOfTargetInfos; ++i)
    {
        printf("\tTarget #%u: \tID:%u   \tName:%s   Instance:%s\n",
               i,
               target_infos[i].id,
               target_infos[i].targetName,
               target_infos[i].instanceName);
    }

    // Does a target with the requested index exist? If not, we connect to the first available CADI target instead
    if (target_num > (actualNumberOfTargetInfos - 1))
    {
        printf("\nWARNING: Target index specified by option ('-t %u') is not availabe. Valid Target indices for this simulation are 0 to %u. Connecting to target index 0 instead.\n",
               target_num,
               actualNumberOfTargetInfos - 1);
               target_num = 0;
    }

    printf("\n***Connecting to target #%u of simulation #%u:\n", 
           target_num,
           simulation_num);

    // This call returns a pointer to the CADI interface of a target. The returned pointer is of type
    // CAInterface. ObtainInterface() method has to be called to check type and revision before casting it to the desired CADI* type.
    ca_interface = simulation->GetTarget(target_infos[target_num].id);

    if (ca_interface == 0)
    {
        printf("ERROR: Getting pointer to target #%u failed.\n", target_num);
        assert(ca_interface);
        exit(1);
    }

    // Call obtain interface to check whether to acquired CADI target provides the correct interface and revision
    uint32_t cadi_revision = 0;
    ca_interface = ca_interface->ObtainInterface("eslapi.CADI2", 0, &cadi_revision);

    if (ca_interface == NULL)
    {
        printf("ERROR: Obtaining CADI interface from target failed. Please check if the model library supports the requested interface 'eslapi.CADI2' and the requested revision.\n");
        assert(ca_interface);
        exit(1);
    }

    // Now cast the CAInterface pointer to a CADI pointer. 
    eslapi::CADI *cadi = static_cast<eslapi::CADI *>(ca_interface);

    printf("\tSuccessfully obtained a CADI 2.0 interface pointer (%p).\n", cadi);

    printf("\n***Retrieving CADI target features for connected target...\n");
    // Read the target features; these expose information on the target like 
    // the number of register groups or memory spaces and the register number
    // of a program counter (if available)
    eslapi::CADITargetFeatures_t target_features;
    status = cadi->CADIXfaceGetFeatures(&target_features);

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Getting CADI target features from target failed. These are required in the following.\n");
        assert(eslapi::CADI_STATUS_OK == status);
        exit(1);
    }

    printf("\tSuccessfully obtained CADI target features.\n");

    printf("\n\tConnected to target '%s'\n", target_features.targetName);
    printf("\t\t-->Number of registers groups: %u\n\n", target_features.nrRegisterGroups);

    // This is the CADI callback object for the connection to a target. It it used
    // to indicate mode changes within the target, occurring resets, etc. It is derived
    // from eslapi::CADICallbackObj
    MyCADICallback* cadi_callback = new MyCADICallback();

    // This vector is used to enable callback methods for the given CADICallback object.
    // Disabled callbacks are not called by the target.
    // Adding a callback object to the target enables the target to interact with the 
    // debugger. It can e.g. give information on the execution mode (run, stop), request 
    // interactive console input (appliInput), notify a debugger to update it's display (refresh) etc.
    char cadi_callback_enables[eslapi::CADI_CB_Count] = {0};
    cadi_callback_enables[eslapi::CADI_CB_String] = 1;
    cadi_callback_enables[eslapi::CADI_CB_ModeChange] = 1;
    cadi_callback_enables[eslapi::CADI_CB_Reset] = 1;

    printf("***Adding callback object (%p) to target...\n",
           static_cast<eslapi::CADICallbackObj*>(cadi_callback));

    status = cadi->CADIXfaceAddCallback(static_cast<eslapi::CADICallbackObj*>(cadi_callback), cadi_callback_enables);

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Adding CADI callback object to target failed. Return type is '%s'\n", CADIReturnToString(status));
        assert(eslapi::CADI_STATUS_OK == status);
        exit(1);
    }

    printf("\tSuccessfully added callback object.\n");


    printf("\n***Retrieving register group information...\n");
    // Read Register Group information. The number of register groups is given by target_features.nrRegisterGroups 
    const uint32_t desiredNumberOfRegisterGroups = target_features.nrRegisterGroups;
    eslapi::CADIRegGroup_t *register_groups = new eslapi::CADIRegGroup_t[desiredNumberOfRegisterGroups];
    // NOTE: The actual number of register groups might be smaller than the desired number
    // of register groups 'desiredNumberOfRegisterGroups'!
    uint32_t actualNumberOfRegisterGroups = 0;

    status = cadi->CADIRegGetGroups(0, //groupIndex
                                    desiredNumberOfRegisterGroups,
                                    &actualNumberOfRegisterGroups,
                                    register_groups);

    //Flag to indicate whether register group information could be retrieved and whether write accesses can be tested
    bool RegGetGroupsFailed = false;

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Getting register group information from target failed. Return type is '%s'\n", CADIReturnToString(status));
        assert(eslapi::CADI_STATUS_OK == status);
        RegGetGroupsFailed = true;
    }

    if (actualNumberOfRegisterGroups == 0)
    {
        printf("ERROR: Target returned 0 register groups.\n");
        assert(actualNumberOfRegisterGroups > 0);
        RegGetGroupsFailed = true;
    }

    if (actualNumberOfRegisterGroups != target_features.nrRegisterGroups)
    {
        printf("ERROR: Target returned a different number of register groups (%u) than expected (%u).\n",
               actualNumberOfRegisterGroups,
               target_features.nrRegisterGroups);
        assert(actualNumberOfRegisterGroups == target_features.nrRegisterGroups);
        RegGetGroupsFailed = true;
    }

    if (RegGetGroupsFailed == true)
    {
        printf("WARNING: Could not retrieve register group information. Skipping register write accesses.\n");
    }
    else //Register group information could be retrieved, performing register accesses
    {
        printf("\tSuccessfully obtained register group information.\n");

        // Read and print all register information and values for all register groups
        ReadTargetRegisters(cadi,
                            register_groups,
                            actualNumberOfRegisterGroups); 


        printf("\n***Trying to find registers 'R3' and 'R7'...\n");
        eslapi::CADIReg_t* regR3 = NULL;
        eslapi::CADIReg_t* regR7 = NULL;

        // Prepare CADIReg_t's for accesses to registers "R3" and "R7"
        for (unsigned int i=0; i < actualNumberOfRegisterGroups; ++i)
        {
            const uint32_t desiredNumOfRegisters = 200;
            uint32_t actualNumOfRegisters = 0;
            eslapi::CADIRegInfo_t regs[desiredNumOfRegisters];

            // Get information on all registers within the current register groups
            status = cadi->CADIRegGetMap(register_groups[i].groupID,
                                         0, //startRegisterIndex
                                         desiredNumOfRegisters,
                                         &actualNumOfRegisters,
                                         regs);
        
            if (status != eslapi::CADI_STATUS_OK)
            {
                printf("ERROR: Getting register map for register group '%s' (ID: %u) failed. Return type is '%s'\n",
                register_groups[i].name,
                register_groups[i].groupID,
                CADIReturnToString(status));
                assert(eslapi::CADI_STATUS_OK == status);
            }

            if (actualNumOfRegisters == 0)
            {
                printf("ERROR: Target returned 0 register for register group '%s' (ID: %u).\n",
                       register_groups[i].name,
                       register_groups[i].groupID);
                assert(actualNumOfRegisters > 0);
            }

            if (regR3 == NULL)
            {
                // Try to determine CADIReg_t object for register with name 'R3'. This object can then be used to acess the register with this name
                regR3 = GetCADIRegByName("R3",
                                         regs,
                                         actualNumOfRegisters);
            }

            if (regR7 == NULL)
            {
                regR7 = GetCADIRegByName("R7",
                                         regs,
                                         actualNumOfRegisters);
            }

            if ((regR3 != NULL) && (regR7 != NULL))
            {
                printf("\tFound both registers 'R3' and 'R7'.\n");
                break;
            }
        }

        if (regR3 == NULL)
        {
            printf("\tDid not find register 'R3'.\n");
        }

        if (regR7 == NULL)
        {
            printf("\tDid not find register 'R7'.\n");
        }
    
        // Write to register 'R3' if present
        if (regR3 != NULL)
        {
            printf("\n***Writing Value 0x01020304 to register 'R3'.\n");

            for (unsigned int i = 1; i <= 4; ++i)
            {
                regR3->bytes[4-i] = i;
            }

            uint32_t numOfRegsWritten = 0;
            // Writing the register. Multiple registers may be written with one call depending on parameter 'regCount'
            status = cadi->CADIRegWrite(1, // regCount
                                        regR3,
                                        &numOfRegsWritten,
                                        0); // doSideEffects

            if (status != eslapi::CADI_STATUS_OK)
            {
                printf("ERROR: Writing to register 'R3' (ID: %u) failed. Return type is '%s'\n",
                       regR3->regNumber, CADIReturnToString(status));
                assert(eslapi::CADI_STATUS_OK == status);
            }

            if (numOfRegsWritten != 1)
            {
                printf("ERROR: Number of actually written registers for access to 'R3' differs from '1'.\n");
                assert(numOfRegsWritten == 1);
            }

            printf("\tWriting to register 'R3' succeeded.\n");

            delete regR3; // no longer needed
        }


        // Write to register "R7"
        if (regR7 != NULL)
        {
            printf("\n***Writing Value 0x08060402 to register 'R7'.\n");

            for (unsigned int i = 0; i < 4; ++i)
            {
                regR7->bytes[i] = 2*(i+1);
            }

            uint32_t numOfRegsWritten = 0;
            status = cadi->CADIRegWrite(1, //regCount
                                        regR7,
                                        &numOfRegsWritten,
                                        0); //doSideEffects

            if (status != eslapi::CADI_STATUS_OK)
            {
                printf("ERROR: Writing to register 'R7' (ID: %u) failed.\n",
                       regR7->regNumber);
                assert(eslapi::CADI_STATUS_OK == status);
            }

            if (numOfRegsWritten != 1)
            {
                printf("ERROR: Number of actually written registers for access to 'R7' differs from '1'.\n");
                assert(numOfRegsWritten == 1);
            }

            printf("\tWriting to register 'R7' succeeded.\n");

            delete regR7; //no longer needed
        }

        ///////////////////////////////////////////
        //  Display extended features registers  //
        ///////////////////////////////////////////
        printf("\n***Retrieving extended feature registers...\n");
        std::string registerString("");
        bool stringFinished = false;
        uint32_t offset128 = 0; // counter for offset128 specifying the 16 byte chunk to be queried by the individual CADIRegRead
        while(!stringFinished) // Issue CADIRegRead calls until the returned string is 0-terminated
        {
            uint32_t numRegsRead = 0;
            eslapi::CADIReg_t reg;
            reg.regNumber = target_features.nExtendedTargetFeaturesRegNum; // the register number must be set prior calling CADIRegRead to identify the register to be read
            reg.offset128 = offset128++;  // identify 16 byte chunk 
            
            status = cadi->CADIRegRead(1, // query a single set of register data
                                       &reg,
                                       &numRegsRead,
                                       0); //doSideEffects
            if(status != eslapi::CADI_STATUS_OK)
            {
                printf("ERROR: Retrieving extended feature registers failed.\n");
                assert(eslapi::CADI_STATUS_OK == status);
            }

            for (unsigned int k=0; k < sizeof(reg.bytes); ++k)
            {
                if (reg.bytes[k] == '\0')
                {
                    stringFinished = true;
                    break;
                }
                registerString += reg.bytes[k];
            }
        }
        printf("\tThe extended feature registers = '%s'\n", registerString.c_str());
        printf("\tRetrieving extended feature registers succeeded.\n");
    }


    /////////////////////////////////
    //       Memory Accesses       //
    /////////////////////////////////

    printf("\n***Retrieving memory space information...\n");
    //Read Memory Space information. The number of memory spaces is given by target_features.nrMemSpaces
    const uint32_t desiredNumOfMemSpaces = target_features.nrMemSpaces;
    eslapi::CADIMemSpaceInfo_t *memory_spaces = new eslapi::CADIMemSpaceInfo_t[desiredNumOfMemSpaces];
    //NOTE: The actual number of memory spaces might be smaller than the desired number of memory spaces
    //'desiredNumberOfMemSpaces'!
    uint32_t actualNumOfMemSpaces = 0;

    status = cadi->CADIMemGetSpaces(0, //startMemSpaceIndex
                                    desiredNumOfMemSpaces,
                                    &actualNumOfMemSpaces,
                                    memory_spaces);

    //Flag to indicate whether memory space information could be retrieved and whether write access can be tested
    bool MemGetSpacesFailed = false;

    // Check the returned status
    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Getting memory space information from target failed. Return type is '%s'\n",
               CADIReturnToString(status));
        assert(status == eslapi::CADI_STATUS_OK);
        MemGetSpacesFailed = true;
    }

    // Check if any memory space has been returned
    if (actualNumOfMemSpaces == 0)
    {
        printf("ERROR: Target returned 0 memory spaces.\n");
        assert(actualNumOfMemSpaces > 0);
        MemGetSpacesFailed = true;
    }

    // Check if all requested memory spaces have been returned
    if (actualNumOfMemSpaces != target_features.nrMemSpaces)
    {
        printf("ERROR: Target returned a different number of memory spaces (%u) than expected (%u).\n",
               actualNumOfMemSpaces,
               target_features.nrMemSpaces);
        assert(actualNumOfMemSpaces == target_features.nrMemSpaces);
        MemGetSpacesFailed = true;
    }

    if (MemGetSpacesFailed == true)
    {
        printf("WARNING: Could not retrieve memory space information. Skipping register write accesses.\n");
    }
    else //Memory space information could be retrieved, performing memory accesses
    {
        printf("\tSuccessfully obtained memory space information.\n");

        // Read and print all memory block information, read and display the first 20 access units of each memory block
        ReadTargetMemories(cadi,
                           memory_spaces,
                           actualNumOfMemSpaces);

        // Start preparations for memory write access.
        // First retrieve the information for the first memory block of the first memory space. It is required as it is not
        // mandatory that 'minAddress' of CADIMemSpaceInfo_t is equal to 'startAddr' of CADIMemBlock_t
        printf("\n***Getting memory block information of first memory block of first memory space for following write access...\n");
        // Getting first memory block of first memory space
        eslapi::CADIMemBlockInfo_t targetMemBlock;
        uint32_t actualNumOfMemBlocks = 0;

        // Only retrieving the first memory block
        status = cadi->CADIMemGetBlocks(memory_spaces[0].memSpaceId,
                                        0, //memBlockIndex
                                        1, //desiredNumOfMemBlocks
                                        &actualNumOfMemBlocks,
                                        &targetMemBlock);

        //Flag to indicate whether memory space information could be retrieved and whether write access can be tested
        bool MemGetBlocksFailed = false;

        // Check the returned status
        if (eslapi::CADI_STATUS_OK != status)
        {
            printf("ERROR: Retrieving memory block information of first memory block of memory space '%s' (ID: %u) failed.\n",
                   memory_spaces[0].memSpaceName,
                   memory_spaces[0].memSpaceId);
            assert(eslapi::CADI_STATUS_OK == status);
            MemGetBlocksFailed = true;
        }

        // Check if exactly one memory block has been returned (as requested)
        if (actualNumOfMemBlocks != 1)
        {
            printf("ERROR: Retrieving memory block information of first memory block of memory space '%s' (ID: %u) returned wrong actual number of memory blocks (%u).\n",
                   memory_spaces[0].memSpaceName,
                   memory_spaces[0].memSpaceId,
                   actualNumOfMemBlocks);
            assert(actualNumOfMemBlocks == 1);
            MemGetBlocksFailed = true;
        }


        if (MemGetBlocksFailed == true)
        {
            printf("WARNING: Could not retrieve memory block information. Skipping memory write access.\n");
        }
        else //Memory block information could be retrieved, performing memory accesses
        {
            printf("\tSuccessfully retrieved memory block information of first memory block of first memory space.\n");

            // Prepare the write access parameters as well as the data to write
            printf("\n***Preparing data for memory write access to memory block '%s' (ID: %u) of memory space '%s' (ID: %u)...\n",
                   targetMemBlock.name,
                   targetMemBlock.id,
                   memory_spaces[0].memSpaceName,
                   memory_spaces[0].memSpaceId);

            // Writing values to five addresses of the first memory space's block; using an offset of 7 if enough memory is available
            uint32_t writeOffset = 7;
            uint32_t unitsToWrite = 5;

            if ((targetMemBlock.endAddr - targetMemBlock.startAddr) < writeOffset) /* Check if offset is too large. If this is the case,
                                                                                      start from the startAddr of the memory block. */
            {
                writeOffset = 0;
            }

            if ((targetMemBlock.endAddr - targetMemBlock.startAddr) < (writeOffset + unitsToWrite)) /* Check if all memory addresses can be written.
                                                                                                       If the available memory range is to small,
                                                                                                       write to all accessible memory addresses. */
            {
                unitsToWrite = (uint32_t)(targetMemBlock.endAddr - targetMemBlock.startAddr) - writeOffset;
            }

            // Start address of the write access
            eslapi::CADIAddrComplete_t writeAddress;
            // writeAddress.overlay set to default value by constructor of CADIAddrComplete_t, not supported by model
            writeAddress.location.space = memory_spaces[0].memSpaceId;
            writeAddress.location.addr = targetMemBlock.startAddr + writeOffset;

            uint32_t writeUnitSizeInBytes = (memory_spaces[0].bitsPerMau + 7)/8;
            uint32_t actualNumOfUnitsWritten = 0;
            uint32_t writeAccessInBytes = writeUnitSizeInBytes * unitsToWrite;

            // Allocate and fill the buffer for the write access
            uint8_t *writeData = new uint8_t[writeAccessInBytes];
            for (unsigned int i = 0; i < unitsToWrite; i++)
            {
                writeData[i] = 5 + 3*i;
            }

            // Just a short printout of the most important parameters for the write access
            printf("\n***Performing write access:\n\n");
            printf("\taddress: 0x%08x%08x of memory space '%s' (ID: %u).\n",
                   (uint32_t)(writeAddress.location.addr >> 32),
                   (uint32_t)(writeAddress.location.addr),
                   memory_spaces[0].memSpaceName,
                   memory_spaces[0].memSpaceId);
            printf("\tunitsToWrite: %u\n",
                   unitsToWrite);
            printf("\tunitSizeInBytes: %u\n\n",
                   writeUnitSizeInBytes);
            for (unsigned int i = 0; i < unitsToWrite; i++)
            {
                printf("\t\tdata[%u]: 0x%02x\n",
                       i,
                       writeData[i]);
            }
            printf("\n");

            // Do the memory access
            status = cadi->CADIMemWrite(writeAddress,
                                        unitsToWrite,
                                        writeUnitSizeInBytes,
                                        writeData,
                                        &actualNumOfUnitsWritten,
                                        0); // doSideEffects (set to '0', so no side effects are done)

            // Free the allocated data buffer
            delete[] writeData;
            writeData = 0;

            // Read and print out the target memories again to show the effect of the write access
            // (only displaying the first 20 units of each memory block).
            ReadTargetMemories(cadi,
                               memory_spaces,
                               actualNumOfMemSpaces);
        }

    }

    // Memory space information no longer needed. Freeing the allocated memory.
    delete[] memory_spaces;
    memory_spaces = 0;


    /////////////////////////////////
    // Control of Target Execution //
    /////////////////////////////////


    // Try to do 5 cycle steps
    printf("\n***Stepping target for 5 cycles.\n\n");

    // CADIExecSingleStep is asynchronous; The target will signal the resulting execution state through the registered CADI callback object,
    // method 'modeChange'. The modeChange() callback of our callback object (class MyCADICallback) will increase a counter. We need to clear 
    // this counter here to be able to identify that modeChange has been called
    cadi_callback->ClearModeChangeCallbackCounter();

    status = cadi->CADIExecSingleStep(5, // step 5 cycles
                                      true, // cycle step
                                      false); // no step over
    if (status != eslapi::CADI_STATUS_OK)
    {
        fprintf(stderr, "Cycle stepping is not supported by selected target. Return type is '%s'\n", CADIReturnToString(status)); 
    }
    else
    {
        // CADIExecSingleStep returns immediately after triggering the step. But The cycle step itself does NOT 
        // necessarily have to be finished at this point due to the asynchronous nature of CADIExecSingleStep. 
        // So we need to poll the modeChange counter of our callback object to find out when the cycle step operation
        // is finished. Since the execution will issue at least one mode change to eslapi::CADI_EXECMODE_Run and one mode 
        // change to  eslapi::CADI_EXECMODE_Stop, the callback object needs to have received at least two
        // mode change callbacks and must be in mode eslapi::CADI_EXECMODE_Stop when having
        // finished.
        
        while ((cadi_callback->GetCurrentMode() != eslapi::CADI_EXECMODE_Stop)
               || (cadi_callback->GetModeChangeCallbackCounter() < 2))
        {
        //wait for 100 ms; this should be long enough to leave this loop after one iteration
#ifndef WIN32
            usleep(100000);
#else
            Sleep(100);
#endif //WIN32
        }
        
        if (cadi_callback->GetCurrentMode() == eslapi::CADI_EXECMODE_Stop)
        {
            printf("\tStepping target for five cycles succeeded.\n");
        }
    }

    printf("\n***Reading again all registers to show their changed values.\n");
    ReadTargetRegisters(cadi,
                        register_groups,
                        actualNumberOfRegisterGroups);

    
    // Before shutting down the connection to the target, all registerd callback objects
    // need to be removed. If a closed debugger misses to remove
    // its callback objects, the target might try to trigger those callbacks. This 
    // will most likely end up in an corrupted memory access.
    printf("***Removing callback object (%p) from target...\n",
           static_cast<eslapi::CADICallbackObj*>(cadi_callback));
    
    status = cadi->CADIXfaceRemoveCallback(static_cast<eslapi::CADICallbackObj*>(cadi_callback));

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Removing CADI callback object from target failed. Return type is '%s'\n", CADIReturnToString(status) );
        assert(eslapi::CADI_STATUS_OK == status);
    }
    else
    {
        printf("\tSuccessfully removed callback object from target.\n");
    }

    //cadi_callback no longer needed
    delete cadi_callback;

    //////////////////////////////////
    // Shutting down the simulation //
    //////////////////////////////////

    // The rule is: Release the last acquired object first! 
    // This Release() call informs the simulation that the caller will NOT access
    // the corresponding object any more. Hence, it may be safely destroyed.
    // The boolean parameter indicates whether the debugger wants to shut the simulation or not
    // Note that if this boolean is 'true' the target will request all other connected debuggers 
    // to shut down by trigger the simulation callback CADISimulationCallback::simShutdown(). The
    // debuggers must respond with a Release() call to indicate that they also do not access the 
    // simulation any more.
    printf("\n***Releasing simulation #%u...\n", simulation_num);
    simulation->Release(false); // release without shutting down simulation

    //error_callback and sim_callback no longer needed
    delete error_callback;
    delete sim_callback;

    // This Release() call shall inform the broker that the caller will NOT access
    // the corresponding object or any managed simulations anymore. It can
    // be safely destroyed if all other debuggers also have released there objects 
    // 'connected' to this broker.
    printf("\n***Releasing CADI Broker...\n");
    broker->Release();

    printf("\n\n*********Ending Application '%s'*********\n\n",
           argv[0]);

    delete[] register_groups;
}

// End of file
