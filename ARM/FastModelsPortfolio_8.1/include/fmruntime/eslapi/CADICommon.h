#ifndef CADI2Common_H
#define CADI2Common_H

#include "eslapi/CAInterface.h"

#ifdef _WIN32
    #ifdef EXPORT_CADI
        #define CADI_WEXP    __declspec(dllexport)
    #elif !defined(NO_IMPORT_CADI)
        #define CADI_WEXP    __declspec(dllimport)
    #else
        #define CADI_WEXP
    #endif
#else
    #if __GNUC__ >= 4
        #ifdef EXPORT_CADI
            #define CADI_WEXP    __attribute__((visibility ("default")))
        #else
            #define CADI_WEXP
        #endif
    #else
        #define CADI_WEXP
    #endif
# endif

#define CADI_SPEC_MAJOR_VERSION 2
#define CADI_SPEC_MINOR_VERSION 0

#endif
