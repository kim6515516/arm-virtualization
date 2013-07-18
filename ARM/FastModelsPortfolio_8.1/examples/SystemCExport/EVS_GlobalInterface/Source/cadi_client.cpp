/*

  This confidential and proprietary software may be used only as
  authorized by a licensing agreement from ARM Limited.

  Copyright (c) 2013 ARM Limited
  All rights reserved.

  The entire notice above must be reproduced on all authorised copies
  and copies may only be made to the extent permitted by a licensing
  agreement from ARM Limited.

*/

#ifndef WIN32
# include <unistd.h> 
# include <dlfcn.h>
#include <cstdlib>
#include <cstdio>
#include "pthread.h"
#else
# include <wtypes.h>
#include <windows.h>
#endif

#include <string>
#include <assert.h>

#include "eslapi/CADIFactory.h"
#include "eslapi/CADI.h"

#include <sg/SGComponentRegistry.h>
#include <scx/scx.h>

#include "MyCADICallback.h"
#include "cadi_client.h"
#include <systemc>

/////////////////////////////////////////////////////////////////////////////
// Globals
eslapi::CADISimulation *simulation;
eslapi::CADI           *cadi;
MyCADICallback         *cadi_callback;
eslapi::CADITargetFeatures_t target_features;
uint32_t bitsPerMauMemoryspace0;
/////////////////////////////////////////////////////////////////////////////

void* cadi_thread_fxn(void* target_num_)
{

    connect(true);
    registers(true);
    memory();
    callbacks();
    runcontrol();
    close(false);

    return 0;
}

void connect(bool verbose)
{
    uint32_t simulation_num=0;
    uint32_t target_num = 1;
    eslapi::CAInterface *ca_interface;

    // get global interface
    ca_interface = scx::scx_get_global_interface();

    // get access to CADISimulation
    const char *errorMessage = "(no error)";
    eslapi::CADISimulation *simulation = sg::obtainComponentInterfacePointer<eslapi::CADISimulation>(ca_interface, "cadiSimulation", &errorMessage);
    if (!simulation)
    {
        printf("dump_cadi_targets(): error: cannot get CADISimulation interface for component cadiSimulation: %s\n", errorMessage);
        return;
    }
    else
    {
        printf("CADISimulation pointer obtained\n");
    }


    // Now get the info an all targets:
    // Simplification: Use fixed upper limit for number of targets:
    const uint32_t           desiredNumberOfTargetInfos = 100;
    eslapi::CADITargetInfo_t target_infos[desiredNumberOfTargetInfos];
    uint32_t                 actualNumberOfTargetInfos = 0;
    eslapi::CADIReturn_t     status;

    // Getting information on targets available for this CADISimulation;
    // based on these information a caller may decide which target
    // to connect to

    // Get list of the available simulation targets
    status = simulation->GetTargetInfos(0, // startTargetInfoIndex
                                        desiredNumberOfTargetInfos,
                                        target_infos,
                                        &actualNumberOfTargetInfos);

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Getting target infos for simulation #%u failed.\n",
               simulation_num);
        exit(-1);
    }
    printf("GetTargetInfos returned %d targets\n",actualNumberOfTargetInfos);


    // Print the list of targets
    for(unsigned int i=0; i < actualNumberOfTargetInfos; ++i)
    {
        printf("    Target #%u: ID:%u   Name:%s   Instance:%s\n",
             i,
             target_infos[i].id,
             target_infos[i].targetName,
             target_infos[i].instanceName);
    }


    printf("\n***Connecting to target #%u of simulation #%u:\n",
           target_num,
           simulation_num);

    // This call returns a pointer to the CADI interface of a target; actually, the returned pointer is of type
    // CAInterface* which is a base class for the CADI class. Its ObtainInterface() method has to be called
    // before casting it to the desired CADI* type.
    // 6.1: ADD YOUR CODE HERE - Connect to target number "target_num"
    ca_interface = simulation->GetTarget(target_infos[target_num].id);
    if (ca_interface == 0)
    {
        printf("ERROR: Getting pointer to target #%u failed.\n",
               target_num);
        exit(-1);
    }

    // Now cast the CAInterface-pointer to a CADI-pointer which allows debug access to the desired target
    printf("    Successfully obtained a CADI 2.0 interface pointer.\n");
      cadi = (static_cast<eslapi::CADI *>(ca_interface));

    printf("\n***Retrieving CADI target features for connected target...\n");
    // Read the target features; these expose information on the target like 
    // the number of register groups or memory spaces and the register number
    // of a program counter (if available)

    status = cadi->CADIXfaceGetFeatures(&target_features);

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Getting CADI target features from target failed. These are required in the following.\n");
        assert(eslapi::CADI_STATUS_OK == status);
        exit(1);
    }

    printf("\tSuccessfully obtained CADI target features.\n");
}

// ----------------------------------------------------------------------------------------

void registers(bool verbose)
{
    registers_read();              // Reads and prints all register information and values
    registers_write();             // Read, Write and Re-read a specific register
    registers_extended_feature();  // Read the extended feature register
}

void registers_read()
{
    printf("\n***Retrieving register group information...\n");
    // Read Register Group information. The number of register groups is given by target_features.nrRegisterGroups 
    const uint32_t desiredNumberOfRegisterGroups = 100;
    eslapi::CADIRegGroup_t *register_groups = new eslapi::CADIRegGroup_t[100];
    // NOTE: The actual number of register groups might be smaller than the desired number
    // of register groups 'desiredNumberOfRegisterGroups'!
    uint32_t actualNumberOfRegisterGroups = 0;

    eslapi::CADIReturn_t status = cadi->CADIRegGetGroups(0, //groupIndex
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

    if (RegGetGroupsFailed == true)
    {
        printf("WARNING: Could not retrieve register group information. Skipping register write accesses.\n");
    }

    printf("\n***Current register information and contents...\n");
    for (unsigned int i=0; i < actualNumberOfRegisterGroups; ++i)
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

void registers_write()
{
    uint32_t numRegsRead = 0;
    eslapi::CADIReg_t reg;

    printf("\n***Performing Read/Write/Re-Read test...\n");
    printf("\tReading register #1 = ");

    // Define the register to be Tested
    reg.regNumber = 1;
    memset(reg.bytes, 0, (sizeof(uint8_t) * 16));

    // Read the register to find initial value
    eslapi::CADIReturn_t status = cadi->CADIRegRead(1, //regCount
                                                    &reg,
                                                    &numRegsRead,
                                                    0); //doSideEffects

    if (status != eslapi::CADI_STATUS_OK)
        printf("\nERROR: Getting register value from target failed.\n");

    assert(eslapi::CADI_STATUS_OK == status);
    printf("0x");
    for (unsigned int k = 1; k <= 4; ++k)
    {
         printf("%02x", reg.bytes[4 - k]);
    }
    printf("\n");


    // write
    printf("\tWriting 0xffeeddcc to register #1\n");

    // set data to be written to the register
    reg.bytes[0] = 0xCC;
    reg.bytes[1] = 0xDD;
    reg.bytes[2] = 0xEE;
    reg.bytes[3] = 0xFF;

    // Write to the register
    status = cadi->CADIRegWrite(1, //regCount
                                &reg,
                                &numRegsRead,
                                0); //doSideEffects

    if (status != eslapi::CADI_STATUS_OK)
        printf("ERROR: Getting register value from target failed.\n");

    assert(eslapi::CADI_STATUS_OK == status);

    printf("\tRe-Reading register #1 =");


    // Read the register
    status = cadi->CADIRegRead(1, //regCount
                               &reg,
                               &numRegsRead,
                               0); //doSideEffects

    if (status != eslapi::CADI_STATUS_OK)
        printf("ERROR: Getting register value from target failed.\n");

    assert(eslapi::CADI_STATUS_OK == status);

    printf("0x");
    for (unsigned int k = 1; k <= 4; ++k)
    {
         printf("%02x", reg.bytes[4 - k]);
    }
    printf("\n");

}

void registers_extended_feature()
{
    printf("\n***Retrieving extended feature registers...\n");
    std::string registerString("");
    bool stringFinished = false;
    uint32_t offset128 = 0; // counter for offset128 specifying the 16 byte chunk to be queried by the individual CADIRegRead
    while(!stringFinished) // Issue CADIRegRead calls until the returned string is 0-terminated
    {
        uint32_t numRegsRead = 0;
        eslapi::CADIReg_t reg;
        reg.regNumber = target_features.nExtendedTargetFeaturesRegNum; 
        reg.offset128 = offset128++;  // identify 16 byte chunk 

        eslapi::CADIReturn_t status = cadi->CADIRegRead(1, // query a single set of register data
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

// ----------------------------------------------------------------------------------------

void memory(void)
{
    memory_spaces();
    memory_read();
}

void  memory_spaces()
{

    printf("\n***Retrieving memory space information...\n");
    //Read Memory Space information. The number of memory spaces is given by target_features.nrMemSpaces
    const uint32_t desiredNumOfMemSpaces = target_features.nrMemSpaces;
    eslapi::CADIMemSpaceInfo_t *memory_spaces = new eslapi::CADIMemSpaceInfo_t[desiredNumOfMemSpaces];
    //NOTE: The actual number of memory spaces might be smaller than the desired number of memory spaces
    //'desiredNumberOfMemSpaces'!
    uint32_t actualNumOfMemSpaces = 0;

    eslapi::CADIReturn_t status = cadi->CADIMemGetSpaces(0, //startMemSpaceIndex
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

    if (MemGetSpacesFailed == true)
    {
        printf("WARNING: Could not retrieve memory space information. Skipping register write accesses.\n");
    }

    for (unsigned int i=0; i < actualNumOfMemSpaces; i++)
    {
        printf("\tMemoryspace %d\n",memory_spaces[i].memSpaceId);
        printf("\t\tName:             %s\n", memory_spaces[i].memSpaceName);
        printf("\t\tDescription:      %s\n",memory_spaces[i].description);
        printf("\t\tbitsPerMau:       %u\n",memory_spaces[i].bitsPerMau);
        printf("\t\tminAddress:       0x%08x%08x\n", (uint32_t)(memory_spaces[i].minAddress >> 32), (uint32_t)(memory_spaces[i].minAddress));
        printf("\t\tmaxAddress:       0x%08x%08x\n", (uint32_t)(memory_spaces[i].maxAddress >> 32), (uint32_t)(memory_spaces[i].maxAddress));
        printf("\t\tnrMemBlocks:      %u\n",memory_spaces[i].nrMemBlocks);
        printf("\t\tVirtual/Physical: ");
        if (memory_spaces[i].isVirtualMemory)
            printf("Virtual\n");
        else
            printf("Physical\n");  
    }
    printf("\n\n");

    bitsPerMauMemoryspace0 = memory_spaces[0].bitsPerMau;

}

void memory_read()
{
    // Read from address 0x8000 of memoryspace 0

    // Reading the first 20 units of the memory block. Starting from 0x8000
    eslapi::CADIAddrComplete_t startAddress;
    startAddress.location.space = 0;
    startAddress.location.addr  = 0x8000;

    uint32_t unitsToRead = 20; // First 20 units of target are going to be read

    // Convert bits per Minimum Access Unit (MAU) to bytes per MAU. The resulting number must always be a supported multiple of MAU.
    uint32_t unitSizeInBytes = (bitsPerMauMemoryspace0 + 7)/8;
    uint32_t actualNumOfUnitsRead = 0;
    uint8_t  doSideEffects = 0; // Side effects are omitted (target has to decide which side effects are mandatory).
    uint32_t memAccessInBytes = unitsToRead * unitSizeInBytes;

    //Allocating and initializing data buffer for memory read access
    uint8_t  *data = new uint8_t[memAccessInBytes];
    memset(data, 0, memAccessInBytes);

    // Do the read access
    eslapi::CADIReturn_t status = cadi->CADIMemRead(startAddress,
                                                    unitsToRead,
                                                    unitSizeInBytes,
                                                    data,
                                                    &actualNumOfUnitsRead,
                                                    doSideEffects);


    // Check return status
    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Reading %u units of %u bytes starting from address 0x%08x%08x failed. Return type is '%s'\n",
                           unitsToRead,
                           unitSizeInBytes,
                           (uint32_t)(startAddress.location.addr >> 32),
                           (uint32_t)(startAddress.location.addr),
                           CADIReturnToString(status));
        delete[] data;
        assert(eslapi::CADI_STATUS_OK == status);
        printf("Leaving 'ReadTargetMemories()'...\n");
        return;
    }


    // Check if all requested units were read
    if (actualNumOfUnitsRead != unitsToRead)
    {
        printf("ERROR: Less units (%u) of %u bytes than requested (%u) have been read starting from address 0x%08x%08x .\n",
                           actualNumOfUnitsRead,
                           unitSizeInBytes,
                           unitsToRead,
                           (uint32_t)(startAddress.location.addr >> 32),
                           (uint32_t)(startAddress.location.addr));
        delete[] data;
        assert(actualNumOfUnitsRead == unitsToRead);
        printf("Leaving 'ReadTargetMemories()'...\n");
        return;
    }
                
    // Print out the read memory contents
    printf("\n***Reading target memory...\n");
    printf("\tMemoryspace:             0\n");
    printf("\tStart address:           0x8000\n"); 
    printf("\tNumber of bytes to read: 20");
    for (unsigned int k = 0; k < actualNumOfUnitsRead; k++)
    {
        if ((k%4) == 0)
        {
            uint64_t displayAddr = startAddress.location.addr + k;
            printf("\n\t\t0x%08x%08x",
                               (uint32_t)(displayAddr >> 32),
                               (uint32_t)(displayAddr));
        }
        printf("\t%02x", data[k]);
    }
    printf("\n\n");
}

// ----------------------------------------------------------------------------------------

void callbacks(void)
{
    cadi_callback = new MyCADICallback();
    eslapi::CADIReturn_t status;

    // This vector is used to enable callback methods of the CADICallback object;
    // disabled callbacks may not be called for the corresponding target
    char cadi_callback_enables[eslapi::CADI_CB_Count] = {0};
    cadi_callback_enables[eslapi::CADI_CB_AppliOutput] = 1;
    cadi_callback_enables[eslapi::CADI_CB_String] = 1;
    cadi_callback_enables[eslapi::CADI_CB_ModeChange] = 1;
    cadi_callback_enables[eslapi::CADI_CB_Reset] = 1;

    printf("***Adding callback object to target...\n");

    // Adding a callback object to the target enables the target to issue valuable
    // information from inside to cause an appropriate reaction of the caller (e.g.
    // refreshing a debugger's views or control buttons)

    // Register the call back object with the simulation
    status = cadi->CADIXfaceAddCallback(static_cast<eslapi::CADICallbackObj*>(cadi_callback), cadi_callback_enables);

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Adding CADI callback object to target failed.\n");
        exit(-1);
    }

    printf("    Successfully added callback object.\n");
}

// ----------------------------------------------------------------------------------------

void runcontrol(void)
{
    runcontrol_step();
    runcontrol_breakpoints();
}

void runcontrol_step()
{
    // Try to do 1 cycle steps
    printf("\n***Stepping target for 1 cycles.current PC = 0x%08x%08x \n", (uint32_t)(cadi->CADIGetPC() >> 32),(uint32_t)(cadi->CADIGetPC()));



    // CADIExecSingleStep is asynchronous; The target will signal the resulting execution state through the registered CADI callback object,
    // method 'modeChange'. The modeChange() callback of our callback object (class MyCADICallback) will increase a counter. We need to clear 
    // this counter here to be able to identify that modeChange has been called
    cadi_callback->ClearModeChangeCallbackCounter();

    eslapi::CADIReturn_t status = cadi->CADIExecSingleStep(1,      // step 5 cycles
                                                           true,   // cycle step
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
            printf("\tStepping target for one cycles succeeded. Current PC = 0x%08x%08x \n", (uint32_t)(cadi->CADIGetPC() >> 32),(uint32_t)(cadi->CADIGetPC()));
        }
    }
}

void runcontrol_breakpoints(void)
{

    eslapi::CADIBptRequest_t *bpt = new eslapi::CADIBptRequest_t;
    eslapi::CADIBptNumber_t *bptnum = new eslapi::CADIBptNumber_t;
    bpt->type = eslapi::CADI_BPT_PROGRAM;
    bpt->address.location.addr = 0x80B8;
    bpt->enabled = 1;

    printf("\n\n****Setting program breakpoint at address 0x%08x%08x ....\n",(uint32_t)(bpt->address.location.addr >> 32),(uint32_t)(bpt->address.location.addr));


    // Set a breakpoint on address 0x8010
    eslapi::CADIReturn_t status = cadi->CADIBptSet(bpt, bptnum);

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("unable to set breakpoint\n");
        exit(1);
    }

    printf("\tBreakpoint set successfully: %d \n\n", *bptnum);
    printf("****Running target\n");

    // Run the simulation and wait for it to stop
    status = cadi->CADIExecContinue();

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("CADIExecContinue returned an error\n");
        exit(1);
    }

    cadi_callback->ClearModeChangeCallbackCounter();
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
        printf("\tBreakpoint hit,   PC=0x%08x%08x \n\n",(uint32_t)(cadi->CADIGetPC() >> 32),(uint32_t)(cadi->CADIGetPC()));
    }
}

// ----------------------------------------------------------------------------------------

void close(bool verbose)
{
    // Before shutting down the connetion to the target, all registerd callback objects
    // need to be removed; otherwise the following may happen:
    //   In case of closing a debugger which is not the only connected one, a target
    //   does not necessarily have to shut down. If a closed debugger misses to remove
    //   its callback objects, the target might try to trigger those callbacks. This 
    //   will most likely end up in an corrupted memory access.
    printf("***Removing callback object (%p) from target...\n", static_cast<eslapi::CADICallbackObj*>(cadi_callback));
    eslapi::CADIReturn_t status = cadi->CADIXfaceRemoveCallback(static_cast<eslapi::CADICallbackObj*>(cadi_callback));

    if (status != eslapi::CADI_STATUS_OK)
    {
        printf("ERROR: Removing CADI callback object from target failed. Return type is '%s'\n", CADIReturnToString(status) );
        assert(eslapi::CADI_STATUS_OK == status);
    }
    else
    {
        printf("\tSuccessfully removed callback object from target.\n");
    }

#if 0
    // This Release()-call shall inform the simulation that the caller will NOT access
    // the corresponding object anymore. Hence, it may be safely destroyed.
    // (The boolean parameter indicates whether to shut the simulation down or to leave
    // it running in order to allow other callers to connect to it or to finishe their job).
    printf("\n***Releasing simulation...\n");
    simulation->Release(true); // release and shut down the simulation
#endif

    exit(0);

#ifdef WIN32
    ExitThread(0);
#else
    pthread_exit(NULL);
#endif


}

// ----------------------------------------------------------------------------------------

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

// End of file
