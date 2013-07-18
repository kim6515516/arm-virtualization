/*
 * Copyright 2008 ARM Limited. All rights reserved.
 */

/*!
 * \file    MessageCodec.h
 * \brief   C++ classes to help convert function calls into messages and back
 *          The implementation of this class should match that 
 */

#ifndef MESSAGECODEC_MSG_H
#define MESSAGECODEC_MSG_H


class MessageFormat
{
protected:

    enum DataType
    {
        MSG_END     = 0,    // marker for end of message data
        MSG_UINT32  = 1,    // 32 bit data
        MSG_UINT64  = 2,    // 64 bit data
        MSG_INT32   = 3,    // 32 bit data
        MSG_CSTR    = 4,    // zero terminated c string
        MSG_DATA    = 5,    // raw data
        MSG_CHAR    = 6,    // single character
        MSG_BOOL    = 7     // packed bool
    };

    // all data in the message is sent as a stream of typed objects
    // with the type being a word formed as a bitfield
    //  31 28 27           8 7     0
    // |  r  |     len      | type  |
    //  
    // all data is word aligned
    // the length field is used for sending inline data (up to 1MB)
    // it is not currently used for other types
    // the top 4 bits are currently reserved

    // mask/shift bits for data ids
    enum Traits
    {
        TYPE_SHIFT  = 0,
        TYPE_BITS   = 8,
        TYPE_MASK   = (1<<TYPE_BITS)-1,

        LEN_SHIFT   = 8,
        LEN_BITS    = 20,
        MAX_LEN     = 1<<LEN_BITS,
        LEN_MASK    = MAX_LEN-1
    };
};

class MessageComposer : public MessageFormat
{
    uint8_t*  b_data;         // message data
    uint32_t b_size;        // size of buffer
    uint32_t b_index;       // current index into buffer

    bool put(DataType type, const void* data, uint32_t len)
    {
        if (len >= b_size)
            return false;

        if (!b_data)
            return false;

        uint32_t tag = (len << LEN_SHIFT)|((uint32_t)type);

        *(uint32_t*)(b_data + b_index) = tag;
        b_index += 4;

        memcpy(b_data+b_index, data, len);
        b_index += len;

        b_index = (b_index + 3) &~ 3; // word align

        return true;
    }

public:

    MessageComposer(void* data, uint32_t len)
    {
        reinit(data, len);
    }

// for composing

    void reinit(void* data, uint32_t len)
    {
        b_data = (uint8_t*)data;
        b_size = len;
        b_index = 0;
    }

    bool put_int32(int32_t data)
    {
        return put(MSG_INT32, (void*)&data, sizeof(int32_t));
    }

    bool put_uint32(uint32_t data)
    {
        return put(MSG_UINT32, (void*)&data, sizeof(uint32_t));
    }

    bool put_uint64(uint64_t data)
    {
        return put(MSG_UINT64, (void*)&data, sizeof(uint64_t));
    }

    bool put_cstr(const char* data)
    {
        return put(MSG_CSTR, (void*)data, (uint32_t)strlen(data)+1);
    }

    bool put_data(const void* data, uint32_t len)
    {
         return put(MSG_DATA, data, len);
    }

    // todo - other types

    uint32_t get_size() const { return b_index; }
};

class MessageDecomposer : public MessageFormat
{
    const uint8_t* b_data;        // message data
    uint32_t     b_size;        // size of buffer
    uint32_t     b_index;       // current index into buffer

    bool get(DataType type, void* data, uint32_t* len, bool fixedwidth = true)
    {
        if (b_index + 4 > b_size)
            return false;

        uint32_t tag = *(uint32_t*)(b_data + b_index);

        DataType d_type = (DataType)((tag>>TYPE_SHIFT) & TYPE_MASK);
        uint32_t d_len = ((tag>>LEN_SHIFT) & LEN_MASK);

        if (d_type != type)
            return false;

        // Fixed width types must match exactly. Otherwise we
        // copy min(*len, d_len) and update *len to the number
        // of bytes copied.
        if (fixedwidth && (d_len != *len))
            return false;

        b_index += 4;

        if (b_index + d_len > b_size)
            return false;

        if (*len > d_len)
            *len = d_len;

        memcpy(data, b_data+b_index, *len);

        b_index += d_len;

        b_index = (b_index + 3) &~ 3; // word align

        return true;
    }

public:

    MessageDecomposer(const void* data, uint32_t len)
    {
        reinit(data, len);
    }

// for decomposing

    void reinit(const void* data, uint32_t len)
    {
        b_data  = (const unsigned char*)data;
        b_size  = len;
        b_index = 0;
    }

// for decomposing

    bool get_int32(int32_t* data)
    {
        uint32_t len = sizeof(int32_t);

        return get(MSG_INT32, (void*)data, &len);
    }

    bool get_uint32(uint32_t* data)
    {
        uint32_t len = sizeof(uint32_t);

        return get(MSG_UINT32, (void*)data, &len);
    }

    bool get_uint64(uint64_t* data)
    {
        uint32_t len = sizeof(uint64_t);

        return get(MSG_UINT64, (void*)data, &len);
    }

    bool get_cstr(char* data, uint32_t* len)
    {
        if (!get(MSG_CSTR, (void*)data, len, false))
            return false;
        if (!memchr(data, 0, *len))
            return false;
        return true;
    }

    bool get_data(void* data, uint32_t* len)
    {
        return get(MSG_DATA, data, len, false);
    }

    // todo - other types
};


#endif // MESSAGECODEC_MSG_H

