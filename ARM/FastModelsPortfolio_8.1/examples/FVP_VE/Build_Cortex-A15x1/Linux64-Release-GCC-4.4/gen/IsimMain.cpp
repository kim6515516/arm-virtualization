/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2000-2009 ARM Limited.
 * Copyright 2012 ARM Limited.
 *
 * All rights reserved.
 */

// To use your own main:
// 1) Define USER_DEFINED_ISIM_MAIN compiler preprocessor definition in project configuration
// 2) add a file with your main() to the project
// 3) perform your initialization and command line parsing there
// 4) call LoadInitAndRunCADIModel(argc, argv, topComponent, pvLibVersion).
//    Please make sure to remove your command line parameters from argv list passed to the function
// NOTE: do not edit this file - your changes will be lost when the file is generated next time

#ifndef USER_DEFINED_ISIM_MAIN

#include "SimGenTplMacros.h"

// function that preform command line parsing, CADI system initialization and run
extern int LoadInitAndRunCADIModel(int argc, char *argv[], const char* topComponent, const char* pvLibVersion);

int main(int argc, char *argv[])
{
    return LoadInitAndRunCADIModel(argc, argv, SIMGEN_TOP_COMPONENT,
                                               PVLIB_VERSION_STRING);
}

#endif // #ifndef  USER_DEFINED_ISIM_MAIN
// end of file IsimMain.cpp
