/*!
 * \file   PatternBuffer.cpp
 * \brief  Implementation of the PatternBuffer class
 * \date   Copyright 2011 ARM Limited. All rights reserved.
 * \author Hugues Bruant
 */

#include "PatternBuffer.h"

#include <cstdlib>

/*!
 * \class PatternBuffer
 * \brief A buffer in which to write formatted data with support for placeholders
 *
 * PatternBuffer is intended as a replacement to FormattedBuffer in cases where a significant
 * part of the formatted data can be precomputed. It supports placeholders that will be resolved
 * when the data is available.
 *
 */

namespace {

enum {
    AllocPH = 10,
    AllocFrag = 10,
    AllocBuffer = 20
};

}  // namespace

PatternBuffer::PatternBuffer() {
    m_ph_size = 0;
    m_ph_alloc = AllocPH;
    m_placeholders = (Placeholder*)malloc(m_ph_alloc * sizeof(Placeholder));
    
    m_frag_size = 0;
    m_frag_alloc = AllocFrag;
    m_fragments = (Fragment*)malloc(m_frag_alloc * sizeof(Fragment));
    
    m_size = 0;
    m_alloc = AllocBuffer;
    m_buffer = (char*)malloc(m_alloc);
    
    m_useDecimalForFixedSizeIntegers = false;
}

PatternBuffer::~PatternBuffer() {
    for (size_t i = 0; i < m_frag_size; ++i)
        free(m_fragments[i].buffer);
    free(m_placeholders);
    free(m_fragments);
}

void PatternBuffer::substitute(FormattedBuffer& b, const void *record) const {
    const Fragment *frag = m_fragments;
    const Placeholder *ph = m_placeholders;
    for (size_t i = 0; i < m_ph_size; ++i, ++ph) {
        if (ph->start >= 0) {
            reinterpret_cast<FixedResolver>(ph->resolver)(frag->buffer + ph->start, ph->offset, record);
        } else {
            if (frag->size)
                b.addString(frag->buffer, frag->size);
            size_t n;
            const char *s = reinterpret_cast<VariableResolver>(ph->resolver)(&n, ph->offset, record, ph->data);
            if (ph->type == Placeholder::Hex)
                b.addHex(reinterpret_cast<const uint8_t*>(s), n);
            else
                b.addString(s, n);
            ++frag;
        }
    }
    if (size_t(frag - m_fragments) < m_frag_size)
        b.addString(frag->buffer, frag->size);
}

void PatternBuffer::finalize() {
    finalizeFragment();
    m_buffer = 0;
    m_alloc = 0;
    m_size = 0;
}

void PatternBuffer::finalizeFragment() {
    if (m_frag_size == m_frag_alloc) {
        m_frag_alloc += m_frag_alloc;
        m_fragments = (Fragment*)realloc(m_fragments, m_frag_alloc * sizeof(Fragment));
    }
    m_fragments[m_frag_size++] = Fragment(m_size, m_alloc, m_buffer);
}

void PatternBuffer::grow(size_t min) {
    do {
        m_alloc += m_alloc;
    } while (m_alloc <= min);
    m_buffer = (char*)realloc(m_buffer, m_alloc);
}

void PatternBuffer::addHexPlaceholder(Resolver r, size_t off, size_t n, void *d) {
    if (m_size + 2 >= m_alloc)
        grow(m_size + 2);
    char *b = m_buffer + m_size;
    b[0] = '0';
    b[1] = 'x';
    m_size += 2;
    addPlaceholder(Placeholder::Hex, n, r, off, d);
}

void PatternBuffer::addPlaceholder(Placeholder::Type t, size_t l, Resolver r, size_t off, void *d) {
    if (m_ph_size == m_ph_alloc) {
        m_ph_alloc += m_ph_alloc;
        m_placeholders = (Placeholder*)realloc(m_placeholders, m_ph_alloc * sizeof(Placeholder));
    }
    m_placeholders[m_ph_size++] = Placeholder(t, l ? int64_t(m_size) : -1, l, r, off, d);
    if (l) {
        if (t == Placeholder::Hex)
            l += l;
        if (m_size + l >= m_alloc)
            grow(m_size + l);
        m_size += l;
    } else {
        // split
        finalizeFragment();
        m_size = 0;
        m_alloc = AllocBuffer;
        m_buffer = (char*)malloc(m_alloc);
    }
}
