/*!
 * \file   FormatterUtils.h
 * \brief  A set of utility functions for fast text formatting
 * \date   Copyright 2011 ARM Limited. All rights reserved.
 * \author Hugues Bruant
 */

#ifndef _FORMATTER_UTILS_H_
#define _FORMATTER_UTILS_H_

#include <stdio.h>

#include "hostconf/zstdint.h"

namespace FormatterUtils {

namespace {

inline int hex_digit(int val) { return val + (val > 9 ? 'a' - 10 : '0'); }

inline void writeHex8(char *b, uint8_t v) {
    b[1] = hex_digit(v & 0x0f);
    b[0] = hex_digit((v >> 4) & 0x0f);
}

inline void writeHex16(char *b, uint16_t v) {
    writeHex8(b+2,  v       & 0xff);
    writeHex8(b  , (v >> 8) & 0xff);
}

inline void writeHex32(char *b, uint32_t v) {
    writeHex16(b+4,  v        & 0xffff);
    writeHex16(b  , (v >> 16) & 0xffff);
}

inline void writeHex40(char *b, uint64_t v) {
    writeHex32(b+2,          v        & 0xffffffffULL);
    writeHex8 (b  , uint8_t((v >> 32) & 0xffULL));
}

inline void writeHex48(char *b, uint64_t v) {
    writeHex32(b+4,           v        & 0xffffffffULL);
    writeHex16(b  , uint16_t((v >> 32) & 0xffffULL));
}

inline void writeHex64(char *b, uint64_t v) {
    writeHex32(b+8,  v        & 0xffffffffULL);
    writeHex32(b  , (v >> 32) & 0xffffffffULL);
}

template <typename T>
class WriteHexHelper {
public:
    inline WriteHexHelper(char *b, T val) {
        writeHex(b, &val, sizeof(T));
    }
};

#define WHH(n)                                            \
template <>                                               \
class WriteHexHelper<uint##n##_t> {                       \
public:                                                   \
    inline WriteHexHelper(char *b, uint##n##_t val) {     \
        writeHex##n (b, val);                             \
    }                                                     \
};
WHH(8)
WHH(16)
WHH(32)
WHH(64)
#undef WHH

template <typename T>
inline void writeHex(char *d, T val) {
    WriteHexHelper<T>(d, val);
}

inline void writeHex(char *b, const uint8_t *d, size_t n) {
    while (n > 0) {
        char v = d[--n];
        b[1] = hex_digit(v & 0x0f);
        b[0] = hex_digit((v >> 4) & 0x0f);
        b += 2;
    }
}


template <typename T, int n>
const char* hex_n(T v, size_t *length) {
    static char _buffer[n+1];
    writeHex(_buffer, v);
    _buffer[n]=0;
    if (length)
        *length = n;
    return _buffer;
}

const char* hex8(uint8_t v, size_t *length) {
    return hex_n<uint8_t, 2>(v, length);
}
const char* hex16(uint16_t v, size_t *length) {
    return hex_n<uint16_t, 4>(v, length);
}
const char* hex32(uint32_t v, size_t *length) {
    return hex_n<uint32_t, 8>(v, length);
}
const char* hex64(uint64_t v, size_t *length) {
    return hex_n<uint64_t, 16>(v, length);
}

template <typename T>
class HexHelper {
public:
    inline const char* operator () (T val, size_t *length) {
        return hex64(uint64_t(val), length);
    }
};

#define HH(n)                                                           \
template <>                                                             \
class HexHelper<uint##n##_t> {                                      \
public:                                                                 \
    static inline const char* h(uint##n##_t val, size_t *length) {      \
        return hex##n (val, length);                                \
    }                                                                   \
};
HH(8)
HH(16)
HH(32)
HH(64)
#undef HH

template <typename T>
inline const char* hex(T val, size_t *length) {
    return HexHelper<T>::h(val, length);
}


template <typename T, int n>
const char* decimal_n(T v, size_t *length) {
    static char _buffer[n+1];
    char *b = _buffer + n;
    *b = 0;
    do {
        *--b = char((v % 10) + '0');
        v /= 10;
    } while (v);
    if (length)
        *length = _buffer + n - b;
    return b;
}

const char* decimal8(uint8_t v, size_t *length) {
    return decimal_n<uint8_t, 3>(v, length);
}

const char* decimal16(uint16_t v, size_t *length) {
    return decimal_n<uint16_t, 5>(v, length);
}

const char* decimal32(uint32_t v, size_t *length) {
    return decimal_n<uint32_t, 10>(v, length);
}

const char* decimal64(uint64_t v, size_t *length) {
    return decimal_n<uint64_t, 20>(v, length);
}

template <typename T>
class DecimalHelper {
public:
    inline const char* operator () (T val, size_t *length) {
        return decimal64(uint64_t(val), length);
    }
};

#define DH(n)                                                           \
template <>                                                             \
class DecimalHelper<uint##n##_t> {                                      \
public:                                                                 \
    static inline const char* h(uint##n##_t val, size_t *length) {      \
        return decimal##n (val, length);                                \
    }                                                                   \
};
DH(8)
DH(16)
DH(32)
DH(64)
#undef DH

template <typename T>
inline const char* decimal(T val, size_t *length) {
    return DecimalHelper<T>::h(val, length);
}

inline size_t decimalLength(bool /*val*/) {
    return 1;
}

inline size_t decimalLength(uint8_t val) {
    return val > 99 ? 3 : (val > 9 ? 2 : 1);
}

inline size_t decimalLength(uint16_t val) {
    size_t count = 1;
    if (val > 9999) {
        count += 4;
        val /= 10000;
    }
    if (val > 99) {
        count += 2;
        val /= 100;
    }
    if (val > 9)
        ++count;
    return count;
}

inline size_t decimalLength(uint32_t val) {
    size_t count = 1;
    if (val > 99999999) {
        count += 8;
        val /= 100000000;
    }
    if (val > 9999) {
        count += 4;
        val /= 10000;
    }
    if (val > 99) {
        count += 2;
        val /= 100;
    }
    if (val > 9)
        ++count;
    return count;
}

inline size_t decimalLength(uint64_t val) {
    size_t count = 1;
    if (val > 9999999999999999ULL) {
        count += 16;
        val /= 10000000000000000ULL;
    }
    if (val > 99999999) {
        count += 8;
        val /= 100000000;
    }
    if (val > 9999) {
        count += 4;
        val /= 10000;
    }
    if (val > 99) {
        count += 2;
        val /= 100;
    }
    if (val > 9)
        ++count;
    return count;
}

template <typename T>
inline void writeDecimal(char *b, size_t l, T val) {
    char *e = b + l;
    do {
        *--e = char((val % 10) + '0');
        val /= 10;
    } while (b != e);
}

}  // namespace

}  // namespace FormatterUtils

#endif  // _FORMATTER_UTILS_H_
