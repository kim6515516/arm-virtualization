/*!
 * \file   PatternBuffer.h
 * \brief  Definition of the PatternBuffer class
 * \date   Copyright 2011 ARM Limited. All rights reserved.
 * \author Hugues Bruant
 */

#ifndef _PATTERN_BUFFER_H_
#define _PATTERN_BUFFER_H_

#include "FormattedBuffer.h"

#include "MTI_ext.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <vector>

class PatternBuffer {
public:
    typedef void (*FixedResolver)(char *d, size_t off, const void *record);
    typedef const char* (*VariableResolver)(size_t *n, size_t off, const void *record, void *data);
    
    PatternBuffer();
    ~PatternBuffer();
    
    void substitute(FormattedBuffer& b, const void *record) const;
    
    void finalize();

    inline PatternBuffer& addChar(char c) {
        if (m_size + 1 >= m_alloc)
            grow(m_size + 1);
        m_buffer[m_size] = c;
        ++m_size;
        return *this;
    }

    inline PatternBuffer& addString(const char *s) {
        return addString(s, strlen(s));
    }

    inline PatternBuffer& addString(const std::string& s) {
        return addString(s.data(), s.length());
    }

    PatternBuffer& addString(const char *s, size_t n) {
        if (m_size + n >= m_alloc)
            grow(m_size + n);
        memcpy(m_buffer + m_size, s, n);
        m_size += n;
        return *this;
    }

    inline PatternBuffer& addStringPH(VariableResolver r, size_t off, void *d) {
        addPlaceholder(Placeholder::String, 0, reinterpret_cast<Resolver>(r), off, d);
        return *this;
    }
    
    inline PatternBuffer& addStringPH(FixedResolver r, size_t off, size_t n) {
        addPlaceholder(Placeholder::String, n, reinterpret_cast<Resolver>(r), off, 0);
        return *this;
    }

    inline PatternBuffer& addHex8PH(FixedResolver r, size_t off) {
        addHexPlaceholder(reinterpret_cast<Resolver>(r), off, 1);
        return *this;
    }

    inline PatternBuffer& addHex16PH(FixedResolver r, size_t off) {
        addHexPlaceholder(reinterpret_cast<Resolver>(r), off, 2);
        return *this;
    }

    inline PatternBuffer& addHex32PH(FixedResolver r, size_t off) {
        addHexPlaceholder(reinterpret_cast<Resolver>(r), off, 4);
        return *this;
    }

    inline PatternBuffer& addHex64PH(FixedResolver r, size_t off) {
        addHexPlaceholder(reinterpret_cast<Resolver>(r), off, 8);
        return *this;
    }

    inline PatternBuffer& addHexPH(VariableResolver r, size_t off, void *d) {
        addHexPlaceholder(reinterpret_cast<Resolver>(r), off, 0, d);
        return *this;
    }

    inline PatternBuffer& addHexPH(FixedResolver r, size_t off, size_t n) {
        addHexPlaceholder(reinterpret_cast<Resolver>(r), off, n);
        return *this;
    }

    inline PatternBuffer& addDecimalPH(VariableResolver r, size_t off, void* d=0) {
        addPlaceholder(Placeholder::Dec, 0, reinterpret_cast<Resolver>(r), off, d);
        return *this;
    }

    template <typename T>
    inline PatternBuffer& addDecimal(T val) {
        size_t n = FormatterUtils::decimalLength(val);
        if (m_size + n >= m_alloc)
            grow(m_size + n);
        FormatterUtils::writeDecimal(m_buffer + m_size, n, val);
        m_size += n;
        return *this;
    }

private:
    typedef void (*Resolver)(void);
    
    struct Fragment {
        inline Fragment(size_t s, size_t a, char *d) : size(s), alloc(a), buffer(d) {}
        size_t size;
        size_t alloc;
        char *buffer;
    };
    
    struct Placeholder {
        enum Type {
            String,
            Hex,
            Dec
        };
        inline Placeholder(Type t, int64_t s, size_t l, Resolver r, size_t o, void *d) : type(t), start(s), length(l), offset(o), resolver(r), data(d) {}
        Type type;
        int64_t start;
        size_t length;
        size_t offset;
        Resolver resolver;
        void *data;
    };
    
    void finalizeFragment();
    
    void grow(size_t min);
    void addHexPlaceholder(Resolver r, size_t off, size_t n, void *d = 0);
    void addPlaceholder(Placeholder::Type t, size_t l, Resolver r, size_t off, void *d);
    
    // shorthand to last fragment
    size_t m_size, m_alloc;
    char *m_buffer;
    
    size_t m_frag_size, m_frag_alloc;
    Fragment *m_fragments;
    
    size_t m_ph_size, m_ph_alloc;
    Placeholder *m_placeholders;
    
    bool m_useDecimalForFixedSizeIntegers;

public:

    static const char* errorResolver(uint32_t v, size_t *length) {
        static char _buffer[13] = "?          ";
        size_t n;
        const char *d = FormatterUtils::decimal(v, &n);
        memcpy(_buffer + 1, d, n);
        _buffer[n + 1] = '?';
        _buffer[n + 2] = '0';
        if (length)
            *length = n + 1;
        return _buffer;
    }

    static const char* enumResolver(size_t *length, size_t offset, const void *record, void *d) {
        const MTI_ext::EnumHelper *h = reinterpret_cast<MTI_ext::EnumHelper*>(d);
        uint32_t enum_val = MTI_ext::GetAs<uint32_t>((const MTI::EventRecord*)record, offset, h->size);
        std::map<uint32_t, MTI_ext::EnumHelper::LPString>::const_iterator it = h->values.find(enum_val);
        if (it != h->end) {
            *length = it->second.size;
            return it->second.data;
        }
        if (getenv("MTI_ABORT_ON_ERROR"))
            abort();
        return errorResolver(enum_val, length);
    }

    template <typename T>
    static void uintResolver(char *d, size_t offset, const void *record) {
        FormatterUtils::writeHex(d, MTI_ext::Get<T>((const MTI::EventRecord*)record, offset));
    }

    template <typename T>
    static const char* intResolver(size_t *length, size_t offset, const void *record, void *d) {
        (void)d;
        return FormatterUtils::decimal(MTI_ext::Get<T>((const MTI::EventRecord*)record, offset), length);
    }

    static const char* ptrResolver(size_t *length, size_t offset, const void *record, void *d) {
        if (length)
            *length = d ? reinterpret_cast<size_t>(d) : MTI_ext::GetVariableSize((const MTI::EventRecord*)record, offset);
        return reinterpret_cast<const char*>(MTI_ext::GetPtr((const MTI::EventRecord*)record, offset));
    }

    static const char* sizeResolver(size_t *length, size_t offset, const void *record, void *d) {
        (void)d;
        return FormatterUtils::decimal(MTI_ext::GetVariableSize((const MTI::EventRecord*)record, offset), length);
    }

    static const char* boolResolver(size_t *length, size_t offset, const void *record, void *d) {
        (void)d;
        uint8_t v = MTI_ext::Get<uint8_t>((const MTI::EventRecord*)record, offset);
        if (v > 1)
            return errorResolver(v, length);
        if (length)
            *length = 1;
        return v ? "Y" : "N";
    }

    static const char* stringResolver(size_t *length, size_t offset, const void *record, void *d) {
        if (length)
            *length = d ? reinterpret_cast<size_t>(d) : MTI_ext::GetVariableSize((const MTI::EventRecord*)record, offset) - 1;
        return reinterpret_cast<const char*>(MTI_ext::GetPtr((const MTI::EventRecord*)record, offset));
    }


    class bitfieldHelper
    {
    public:
        struct repr_t
        {
            const char *str;
            size_t len;
            repr_t(const char* str_, size_t len_) : str(str_), len(len_) {}
        };
        std::vector<repr_t> repr;

        struct select_t
        {
            int shift;
            uint64_t mask;
            select_t(int shift_, uint64_t mask_) : shift(shift_), mask(mask_) {}
        };
        std::vector<select_t> select;
        typedef std::vector<select_t>::const_iterator select_iterator_t;

        void add_repr(const char* str_, size_t len_) { repr.push_back(repr_t(str_, len_)); }
        void add_select(unsigned bitfield_start, unsigned bitfield_end)
        {
            unsigned used_bits = bitfield_start - bitfield_end + 1;
            std::vector<select_t>::iterator iter;
            for (iter = select.begin(); iter != select.end(); ++iter)
            {
                iter->mask = iter->mask << used_bits;
                iter->shift -= used_bits;
            }

            uint64_t mask = (1 << (bitfield_start - bitfield_end + 1)) - 1;
            int shift = bitfield_end;
            select.push_back(select_t(shift, mask));
        }

        bool valid() const { return ! (repr.empty() && select.empty()); }
    };

    template <typename T>
    static const char*  bitfieldResolver(size_t *length, size_t offset, const void *record, void *d)
    {
        const bitfieldHelper *bf = reinterpret_cast<bitfieldHelper*>(d);

        T rawdata = MTI_ext::Get<T>((const MTI::EventRecord*)record, offset);
        T data = 0;

        if (bf->select.empty())
            data = rawdata;
        else
        {
            bitfieldHelper::select_iterator_t iter;
            for (iter = bf->select.begin(); iter != bf->select.end(); ++iter)
            {
                data |= (iter->shift > 0 ? rawdata >> iter->shift : rawdata << -iter->shift) & iter->mask;
            }
        }

        if (data < bf->repr.size())
        {
            *length = bf->repr[(int)data].len;
            return bf->repr[(int)data].str;
        }
        else
        {
            // no explicit enum for this value.
            // if the list of enums ends with an empty string, print nothing. Otherwise print as int
            if ((bf->repr.size() > 0) && (bf->repr[(int)bf->repr.size() - 1 ].len == 0))
            {
                *length = 0;
                return bf->repr[(int)bf->repr.size() - 1 ].str;
            }
            else
                return FormatterUtils::hex(data, length);

        }
    }


    // whether MTI integers are displayed as decimal
    bool useDecimalForFixedSizeIntegers() const { return m_useDecimalForFixedSizeIntegers; }
    void setUseDecimalForFixedSizeIntegers(bool on) { m_useDecimalForFixedSizeIntegers = on; }

    void addField(size_t offset, const MTI::EventFieldType *field, bool explicit_hex=false)
    {
        uint32_t size = field->GetSize();
        switch (field->GetType()) {
            case MTI::EventFieldType::MTI_ENUM:
                if (!explicit_hex)
                {
                    addStringPH(enumResolver, offset, new MTI_ext::EnumHelper(field));
                    break;
                }
                // otherwise, fall through to INT case - user has requested this be printed as a number
            case MTI::EventFieldType::MTI_UNSIGNED_INT:
            case MTI::EventFieldType::MTI_SIGNED_INT:
                switch(size) {
                    case 0: // variable size type
                        addHexPH(ptrResolver, offset, 0).addChar(':').addDecimalPH(sizeResolver, offset);
                        break;
                    case 1:
                        if (m_useDecimalForFixedSizeIntegers)
                            addDecimalPH(intResolver<uint8_t>, offset);
                        else
                            addHex8PH(uintResolver<uint8_t>, offset);
                        break;
                    case 2:
                        if (m_useDecimalForFixedSizeIntegers)
                            addDecimalPH(intResolver<uint16_t>, offset);
                        else
                            addHex16PH(uintResolver<uint16_t>, offset);
                        break;
                    case 4:
                        if (m_useDecimalForFixedSizeIntegers)
                            addDecimalPH(intResolver<uint32_t>, offset);
                        else
                            addHex32PH(uintResolver<uint32_t>, offset);
                        break;
                    case 8:
                        if (m_useDecimalForFixedSizeIntegers)
                            addDecimalPH(intResolver<uint64_t>, offset);
                        else
                            addHex64PH(uintResolver<uint64_t>, offset);
                        break;
                    default:
                        addHexPH(ptrResolver, offset, reinterpret_cast<void*>(size)).addChar(':').addDecimal(size);
                        break;
                }
                break;
            case MTI::EventFieldType::MTI_BOOL:
                assert(size == 1);
                addStringPH(boolResolver, offset, 0);
                break;
            case MTI::EventFieldType::MTI_STRING:
                addChar('\"').addStringPH(stringResolver, offset, reinterpret_cast<void*>(size)).addChar('\"');
                break;
            default:
                addString("Yet unsupported type.");
                break;
        }
    }


    void addBitField(size_t offset, const MTI::EventFieldType *field, bitfieldHelper bf_)
    {
        uint32_t size = field->GetSize();

        bitfieldHelper *inst = new bitfieldHelper(bf_);

        switch (size)
        {
            case 1:
                addStringPH(bitfieldResolver<uint8_t>, offset, inst);
                break;
            case 2:
                addStringPH(bitfieldResolver<uint16_t>, offset, inst);
                break;
            case 4:
                addStringPH(bitfieldResolver<uint32_t>, offset, inst);
                break;
            case 8:
                addStringPH(bitfieldResolver<uint64_t>, offset, inst);
                break;
        }


    }
};

#endif  // _PATTERN_BUFFER_H_
