/*!
 * \file   MTI_ext.h
 * \brief  Definition of the MTI_ext namespace
 * \date   Copyright 2011 ARM Limited. All rights reserved.
 * \author Hugues Bruant
 */

#ifndef _MTI_EXT_H_
#define _MTI_EXT_H_

#include <string.h>
#include "MTI/ModelTraceInterface.h"

#include <map>

/*!
 * \namespace MTI_ext
 * \brief  Small speed-oriented extensions to the MTI EventRecord API
 * \note Should be incorporated in official MTI::EventRecord API eventually
 */
namespace MTI_ext {

template<typename T>
inline T Get(const struct MTI::EventRecord *record, size_t offset) {
    return *(reinterpret_cast<const T *>(reinterpret_cast<const uint8_t*>(record) + offset));
}

inline const uint8_t * GetPtr(const struct MTI::EventRecord *record, size_t offset) {
    return (reinterpret_cast<const uint8_t *>(record) + offset);
}

/* NOTE: must not be used on values of fixed  */
inline MTI::EventFieldType::Size GetVariableSize(const struct MTI::EventRecord *record, size_t offset) {
    return *reinterpret_cast<const uint16_t *>((reinterpret_cast<const uint8_t *>(record) + offset - 2));
}

template<typename T>
inline T GetAs(const struct MTI::EventRecord *record, size_t offset, size_t size) {
    T value = Get<T>(record, offset);
    return size < sizeof(T) ? value & ((T(1) << (size * 8)) - 1) : value;
}

struct EnumHelper {
    EnumHelper(const MTI::EventFieldType *field) {
        size = field->GetSize();
        for (MTI::EventFieldType::EnumIndex e = 0; e < field->GetNumOfEnumConstants(); ++e) {
            MTI::EventFieldType::EnumConstant c = field->GetEnumConstant(e);
            values[c.first] = LPString(c.second);
        }
        end = values.end();
    }
    const char* lookup(uint32_t v) {
        std::map<uint32_t, LPString>::const_iterator i = values.find(v);
        return i != end ? i->second.data : 0;
    }
    size_t size;
    struct LPString {
        LPString() : size(0), data(0) {}
        LPString(const char *s) : size(strlen(s)), data(s) {}
        size_t size;
        const char *data;
    };
    // TODO: use a hash table instead
    std::map<uint32_t, LPString> values;
    std::map<uint32_t, LPString>::const_iterator end;
};

}  // namespace MTI_ext

#endif  // _MTI_EXT_H_
