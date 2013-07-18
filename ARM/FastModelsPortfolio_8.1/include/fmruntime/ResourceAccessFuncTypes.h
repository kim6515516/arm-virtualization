/*!
 * \file    ResourceAccessFuncTypes.h
 * \date    Copyright ARM Limited 2002 All Rights Reserved.
 *
 */

#ifndef RESOURCEACCESSFUNCTYPES_H
#define RESOURCEACCESSFUNCTYPES_H


#include "eslapi/eslapi_stdint.h"


namespace sg
{

namespace accessfunc
{
    enum AccessFuncResultEnum
    {
        ACCESS_FUNC_OK,                     ///< The call was successful.
        ACCESS_FUNC_GeneralError,           /**< This indicates an error that isn't sufficiently explained
                                                 by one of the other error status values.*/
        ACCESS_FUNC_UnknownCommand,         ///< The command is not recognized.
        ACCESS_FUNC_IllegalArgument,        ///< An argument value is illegal.
        ACCESS_FUNC_CmdNotSupported,        ///< The command is recognized but not supported.
        ACCESS_FUNC_ArgNotSupported,        /**< An argument to the command is recognized but
                                                 not supported. For example, the target does not support
                                                 a particular type of complex breakpoint.*/
        ACCESS_FUNC_InsufficientResources,  /**< Not enough memory or other resources exist to fulfill
                                                 the command.*/
        ACCESS_FUNC_TargetNotResponding,    /**< A timeout has occurred across the CADI interface -
                                                 the target did not respond to the command. */
        ACCESS_FUNC_TargetBusy,             /**< The target received a request, but is unable to
                                                 process the command. The caller can try this
                                                 call again after some time.*/
        ACCESS_FUNC_BufferSize,             ///< Buffer too small (for char* types)
        ACCESS_FUNC_SecurityViolation,      ///< Request has not been fulfilled due to a security violation
        ACCESS_FUNC_PermissionDenied,       ///< Request has not been fulfilled since the permission was denied
        ACCESS_FUNC_ENUM_MAX = 0xFFFFFFFF   ///< Max enum value.
    };

    typedef int AccessFuncResult;
} // namespace accessfunc

class MemoryAccessContext
{
    public:
    MemoryAccessContext(uint32_t, uint32_t, void*);
    uint32_t GetAccessSizeInMaus();
    uint32_t GetMauInBytes();
    uint32_t GetMauInBits();
    void *GetAccessData();

    private:
    uint32_t access_size_in_maus_;
    uint32_t mau_in_bytes_;
    void *access_data_;
};

inline MemoryAccessContext::MemoryAccessContext(uint32_t access_size_in_maus, uint32_t mau_in_bytes, void *access_data) :
    access_size_in_maus_(access_size_in_maus),
    mau_in_bytes_(mau_in_bytes),
    access_data_(access_data)
{ }

inline uint32_t MemoryAccessContext::GetAccessSizeInMaus()
{
    return access_size_in_maus_;
}

inline uint32_t MemoryAccessContext::GetMauInBytes()
{
    return mau_in_bytes_;
}

inline uint32_t MemoryAccessContext::GetMauInBits()
{
    return (mau_in_bytes_ * 8);
}

inline void* MemoryAccessContext::GetAccessData()
{
    return access_data_;
}

} // namespace sg

#endif

