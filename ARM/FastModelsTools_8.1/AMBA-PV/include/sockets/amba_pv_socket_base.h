/*
 * AMBA-PV: amba_pv_socket_base.h - AMBA-PV socket base class.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_SOCKET_BASE__H
#define AMBA_PV_SOCKET_BASE__H

/**
 * @file        amba_pv_socket_base.h
 *
 * @brief       AMBA-PV socket base class.
 */

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       AMBA-PV socket base class.
 */
class amba_pv_socket_base {

    /* Constructor */
    public:
        explicit amba_pv_socket_base(int = 0);

    /* Accessors */
        int get_socket_id() const;
        void set_socket_id(int);
    
    /* Implementation */
    private:

        /* Member variables */
        int m_socket_id;
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       socket_id socket identifier (defaults to 0).
 */
inline
amba_pv_socket_base::amba_pv_socket_base(int socket_id /* = 0 */):
    m_socket_id(socket_id) {
}

/**
 * @brief       Returns the identifier of this socket.
 */
inline int
amba_pv_socket_base::get_socket_id() const {
    return (m_socket_id);
}  
    
/**
 * @brief       Sets the identifier of this socket.
 *
 * @param       socket_id socket identifier.
 */
inline void
amba_pv_socket_base::set_socket_id(int socket_id) {
    m_socket_id = socket_id;
}

}   /* namespave amba_pv */

#endif  /* defined(AMBA_PV_SOCKET_BASE__H) */
