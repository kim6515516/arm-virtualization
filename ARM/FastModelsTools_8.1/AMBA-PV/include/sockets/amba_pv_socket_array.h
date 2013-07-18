/*
 * AMBA-PV: amba_pv_socket_array.h - AMBA-PV socket array class.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_SOCKET_ARRAY__H
#define AMBA_PV_SOCKET_ARRAY__H

/**
 * @file        amba_pv_socket_array.h
 *
 * @brief       AMBA-PV socket array class.
 */

/* Includes */
#include <cstdio>
#include <vector>

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV socket array class.
 *
 * @param       SOCKET socket type.
 */
template<class SOCKET>
class amba_pv_socket_array {

    /* Constructor */
    public:
        amba_pv_socket_array(const char *, unsigned int);
        ~amba_pv_socket_array();

    /* Accessors */
        SOCKET & operator[](unsigned int);
        const SOCKET & operator[](unsigned int) const;
        unsigned int size() const;
    
    /* Implementation */
    private:

        /* Member variables */
        unsigned int m_size;
        std::vector<SOCKET *> m_array;
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       name socket array name that is used to generate the individual
 *              socket names of form @c "name%d", where @c d is the zero-based
 *              index of the socket.
 * @param       size socket array size.
 */
template<class SOCKET>
inline
amba_pv_socket_array<SOCKET>::amba_pv_socket_array(const char * name,
                                                   unsigned int size):
    m_size(size),
    m_array(size) {
    char nm[BUFSIZ];

    for (unsigned int i = 0; (i < m_size); i += 1) {
        std::sprintf(nm, "%s%d", name, i);
        m_array[i] = new SOCKET(nm);
    }
}

/**
 * @brief       Destructor.
 */
template<class SOCKET>
inline
amba_pv_socket_array<SOCKET>::~amba_pv_socket_array() {
    for (unsigned int i = 0; (i < m_size); i += 1) {
        delete m_array[i];
    }
}

/**
 * @brief       Returns the socket array size.
 */
template<class SOCKET>
inline unsigned int
amba_pv_socket_array<SOCKET>::size() const {
    return (m_size);
}  
    
/**
 * @brief       Returns the socket at the specified index.
 *
 * @param       index index of the accessed socket.
 *
 * @return      Socket const reference.
 */
template<class SOCKET>
inline const SOCKET &
amba_pv_socket_array<SOCKET>::operator[] (unsigned int index) const {
    if (index >= size()) {
        SC_REPORT_ERROR("amba_pv_socket_array",
                        "operator[]: index out of range");
    }
    return (* (m_array[index]));
}

/**
 * @brief       Returns the socket at the specified index.
 *
 * @param       index index of the accessed socket.
 *
 * @return      Socket reference.
 */
template<class SOCKET>
inline SOCKET &
amba_pv_socket_array<SOCKET>::operator[] (unsigned int index) {
    if (index >= size()) {
        SC_REPORT_ERROR("amba_pv_socket_array",
                        "operator[]: index out of range");
    }
    return (* (m_array[index]));
}

}   /* namespave amba_pv */

#endif  /* defined(AMBA_PV_SOCKET_ARRAY__H) */
