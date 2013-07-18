/*!
 * \file   FormattedBuffer.cpp
 * \brief  Implemetation of the FormattedBuffer class
 * \date   Copyright 2011 ARM Limited. All rights reserved.
 * \author Hugues Bruant
 */

#include "FormattedBuffer.h"

#include <cstdlib>

/*!
 * \class FormattedBuffer
 * \brief A buffer in which to write formatted data
 *
 * FormattedBuffer is intended as a speedy replacement to printf/fprintf. It offers fast formatted
 * writing into a string buffer that can later be committed using a single fwrite call for maximum
 * efficiency.
 *
 * FormattedBuffer currently offers a very limited set of formatting options which are sufficient
 * for the needs of the various trace plugins but it could easily be extended if the need arises.
 *
 * All FormattedBuffer methods are reentrant, except addDecimal and possibly substitute, if any of
 * the resolver function is not itself reentrant.
 *
 * Typical use :
 * \code
   FormattedBuffer b;
   b.addString("name=").addString(name).addChar(',').addString("value=").addHex64(value).addChar('\n);
   fwrite(b.data(), b.size(), file);
   \endcode
   which replaces the significantly less efficient :
   \code
   fprint(file, "name=%s,value=0x%16"PRIx64"\n", name.c_str(), value);
   \endcode
 */

FormattedBuffer::FormattedBuffer() : m_size(0), m_alloc(0), m_buffer(0) {
}

FormattedBuffer::FormattedBuffer(size_t alloc) : m_size(0), m_alloc(alloc), m_buffer((char*)malloc(alloc)) {
}

FormattedBuffer::~FormattedBuffer() {
    free(m_buffer);
}

void FormattedBuffer::grow(size_t min) {
    while (m_alloc < min)
        m_alloc += m_alloc;
    m_buffer = (char*)realloc(m_buffer, m_alloc);
}
