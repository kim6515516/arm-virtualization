/*!
 * \file   FormattedBuffer.h
 * \brief  Definition of the FormattedBuffer class
 * \date   Copyright 2011 ARM Limited. All rights reserved.
 * \author Hugues Bruant
 */

#ifndef _FORMATTED_BUFFER_H_
#define _FORMATTED_BUFFER_H_

#include "hostconf/zstdint.h"

#include <cstring>
#include <string>

#include "FormatterUtils.h"

class FormattedBuffer {
public:
    explicit FormattedBuffer(size_t alloc);
    ~FormattedBuffer();

    inline size_t size() const {
        return m_size;
    }

    inline char* data() const {
        return m_buffer;
    }

    inline char* c_str() {
        m_buffer[m_size] = 0;
        return m_buffer;
    }
    
    inline std::string toString() const {
        return std::string(m_buffer, m_size);
    }
    
    inline void clear() {
        m_size = 0;
    }
    
    inline FormattedBuffer& addChar(char c) {
        if (m_size + 1 >= m_alloc)
            grow(m_size + 1);
        m_buffer[m_size] = c;
        ++m_size;
        return *this;
    }

    inline FormattedBuffer& addString(const char *s) {
        return addString(s, strlen(s));
    }

    inline FormattedBuffer& addString(const std::string& s) {
        return addString(s.data(), s.length());
    }

    inline FormattedBuffer& addString(const char *s, size_t n) {
        if (m_size + n >= m_alloc)
            grow(m_size + n);
        memcpy(m_buffer + m_size, s, n);
        m_size += n;
        return *this;
    }

    inline FormattedBuffer& addStringBounded(const char *s, size_t n) {
        char *e = (char*)memchr(s, 0, n);
        size_t sz = e ? size_t(e - s) : n;
        return addString(s, sz < n ? sz : n);
    }

    #define AH(n)                                           \
    template <typename T>                                   \
    inline FormattedBuffer& addBareHex##n(T v) {            \
        size_t a = n/4;                                     \
        if (m_size + a >= m_alloc)                          \
            grow(m_size + a);                               \
        FormatterUtils::writeHex##n(m_buffer + m_size, v);  \
        m_size += a;                                        \
        return *this;                                       \
    }                                                       \
    template <typename T>                                   \
    inline FormattedBuffer& addHex##n(T v) {                \
        size_t a = 2+n/4;                                   \
        if (m_size + a >= m_alloc)                          \
            grow(m_size + a);                               \
        char *b = m_buffer + m_size;                        \
        b[0] = '0';                                         \
        b[1] = 'x';                                         \
        FormatterUtils::writeHex##n(b + 2, v);              \
        m_size += a;                                        \
        return *this;                                       \
    }
    AH(8)
    AH(16)
    AH(32)
    AH(40)
    AH(48)
    AH(64)
    #undef AH

    template <typename T>
    inline FormattedBuffer& addBareHex(T v) {
        const size_t a = 2*sizeof(T);
        if (m_size + a >= m_alloc)
            grow(m_size + a);
        FormatterUtils::writeHex(m_buffer + m_size, v);
        m_size += a;
        return *this;
    }
    
    template <typename T>
    inline FormattedBuffer& addHex(T v) {
        const size_t a = 2*(sizeof(T)+1);
        if (m_size + a >= m_alloc)
            grow(m_size + a);
        char *b = m_buffer + m_size;
        b[0] = '0';
        b[1] = 'x';
        FormatterUtils::writeHex(b + 2, v);
        m_size += a;
        return *this;
    }
    
    inline FormattedBuffer& addHex(const uint8_t *d, size_t n) {
        const size_t a = 2*n+2;
        if (m_size + a >= m_alloc)
            grow(m_size + a);
        char *b = m_buffer + m_size;
        b[0] = '0';
        b[1] = 'x';
        FormatterUtils::writeHex(b + 2, d, n);
        m_size += a;
        return *this;
    }

    template <typename T>
    inline FormattedBuffer& addDecimal(T val) {
        size_t n = FormatterUtils::decimalLength(val);
        if (m_size + n >= m_alloc)
            grow(m_size + n);
        FormatterUtils::writeDecimal(m_buffer + m_size, n, val);
        m_size += n;
        return *this;
    }

    inline FormattedBuffer& addBoolean(bool val) {
        if (m_size + 1 >= m_alloc)
            grow(m_size + 1);
        m_buffer[m_size] = val ? '1' : '0';
        m_size += 1;
        return *this;
    }
    
private:
    FormattedBuffer();
    
    void grow(size_t min);
    
    size_t m_size;
    size_t m_alloc;
    char *m_buffer;
};

#endif

