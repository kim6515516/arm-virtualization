/*
 * AMBA-PV: signal_slave_export.h - Signal and SignalState exports to be
 *                                  instantiated on the slave side.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef SIGNAL_SLAVE_EXPORT__H
#define SIGNAL_SLAVE_EXPORT__H

/**
 * @file        signal_slave_export.h
 *
 * @brief       Signal and SignalState exports to be instantiated on the
 *              slave side.
 */

/* Includes */
#include "signal/signal_core_ifs.h"

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       Signal export base class.
 */
class signal_export_base {

    /* Constructor */
    public:
        explicit signal_export_base(int /* export_id */ = 0);

    /* Accessors */
        int get_export_id() const;
        void set_export_id(int);
  
    /* Implementation */
    private:

        /* Member variables */
        int m_export_id;
};

/**
 * @brief       Signal export to be instantiated on the slave side.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_slave_export:
    public virtual nonblocking_transport_if<signal_request<STATE>,
                                            signal_response<STATE> >,
    public signal_export_base,
    public sc_core::sc_export<nonblocking_transport_if<signal_request<STATE>,
                                                       signal_response<STATE> > > {

    /* Typdefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;
    typedef nonblocking_transport_if<request_type, response_type> iface_type;
    typedef sc_core::sc_export<iface_type> base_type;

    /* Constructor */
    public:
        signal_slave_export();
        explicit signal_slave_export(const char *,
                                     int /* export_id */ = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        void bind(signal_slave_export &);
        void operator() (signal_slave_export &);
        void bind(signal_transport_if<STATE> &);
        void operator() (signal_transport_if<STATE> &);

    /* Implementation */
    private:

        /* Member variables */
        sc_core::sc_export<signal_transport_if<STATE> > m_export;

        /* Bidirectionnal non-blocking transport */
        virtual response_type nb_transport(const request_type &);
};

/**
 * @brief       SignalState export to be instantiated on the slave side.
 *
 * @param       STATE signal state type.
 */
template<typename STATE>
class signal_state_slave_export:
    public virtual nonblocking_transport_if<signal_request<STATE>,
                                            signal_response<STATE> >,
    public signal_export_base,
    public sc_core::sc_export<nonblocking_transport_if<signal_request<STATE>,
                                                       signal_response<STATE> > > {

    /* Typdefs */
    typedef signal_request<STATE> request_type;
    typedef signal_response<STATE> response_type;
    typedef nonblocking_transport_if<request_type, response_type> iface_type;
    typedef sc_core::sc_export<iface_type> base_type;

    /* Constructor */
    public:
        signal_state_slave_export();
        explicit signal_state_slave_export(const char *,
                                           int /* export_id */ = 0);

    /* sc_object overridables */
        virtual const char * kind() const;

    /* Bindings */
        void bind(signal_state_slave_export &);
        void operator() (signal_state_slave_export &);
        void bind(signal_state_transport_if<STATE> &);
        void operator() (signal_state_transport_if<STATE> &);

    /* Implementation */
    private:

        /* Member variables */
        sc_core::sc_export<signal_state_transport_if<STATE> >
            m_export;

        /* Bidirectionnal non-blocking transport */
        virtual response_type nb_transport(const request_type &);
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       export_id export identifier (defaults to 0).
 */
inline
signal_export_base::signal_export_base(int export_id /* = 0 */):
    m_export_id(export_id) {
}

/**
 * @brief       Returns the export identifier.
 */
inline int
signal_export_base::get_export_id() const {
    return (m_export_id);
}  
    
/**
 * @brief       Sets the export identifier.
 *
 * @param       export_id export identifier.
 */
inline void
signal_export_base::set_export_id(int export_id) {
    m_export_id = export_id;
}

/**
 * @brief       Default constructor.
 */
template<typename STATE>
inline
signal_slave_export<STATE>::signal_slave_export():
    base_type(sc_core::sc_gen_unique_name("signal_slave_export")) {
    base_type::bind(static_cast<iface_type &>(* this));
}

/**
 * @brief       Constructor.
 *
 * @param       name export name.
 * @param       export_id export identifier (for multi-export slave). Defaults
 *              to 0.
 */
template<typename STATE>
inline
signal_slave_export<STATE>::signal_slave_export(const char * name,
                                                int export_id /* = 0 */):
    signal_export_base(export_id),
    base_type(name) {
    base_type::bind(static_cast<iface_type &>(* this));
}

/**
 * @brief       Returns the kind string of this export.
 */
template<typename STATE>
inline const char *
signal_slave_export<STATE>::kind() const  {
    return ("signal_slave_export");
}

/**
 * @brief       Binds an export to this export (hierarchical binding).
 *
 * @param       parent export to bind to this export.
 */
template<typename STATE>
inline void
signal_slave_export<STATE>::bind(signal_slave_export<STATE> & parent) {
    base_type::bind(static_cast<base_type &>(parent));
    m_export.bind(parent.m_export);
}

/**
 * @brief       Binds an export to this export (hierarchical binding).
 *
 * @param       parent export to bind to this export.
 */
template<typename STATE>
inline void
signal_slave_export<STATE>::operator() (signal_slave_export<STATE> & parent) {
    bind(parent);
}

/**
 * @brief       Binds the specified interface to this export.
 *
 * @param       iface signal_transport_if interface to bind to this export.
 */
template<typename STATE>
inline void
signal_slave_export<STATE>::bind(signal_transport_if<STATE> & iface) {
    m_export.bind(iface);
}

/**
 * @brief       Binds the specified interface to this export.
 *
 * @param       iface signal_transport_if interface to bind to this export.
 */
template<typename STATE>
inline void
signal_slave_export<STATE>::operator() (signal_transport_if<STATE> & iface) {
    bind(iface);
}

/*
 * Bidirectional non-blocking transport.
 */
template<typename STATE>
inline signal_response<STATE>
signal_slave_export<STATE>::nb_transport(const request_type & req) {
    return (m_export->nb_transport(this->get_export_id(), req));
}

/**
 * @brief       Default constructor.
 */
template<typename STATE>
inline
signal_state_slave_export<STATE>::signal_state_slave_export():
    base_type(sc_core::sc_gen_unique_name("signal_state_slave_export")) {
    base_type::bind(static_cast<iface_type &>(* this));
}

/**
 * @brief       Constructor.
 *
 * @param       name export name.
 * @param       export_id export identifier (for multi-export slave). Defaults
 *              to 0.
 */
template<typename STATE>
inline
signal_state_slave_export<STATE>::signal_state_slave_export(const char * name,
                                                            int export_id /* = 0 */):
    signal_export_base(export_id),
    base_type(name) {
    base_type::bind(static_cast<iface_type &>(* this));
}

/**
 * @brief       Returns the kind string of this export.
 */
template<typename STATE>
inline const char *
signal_state_slave_export<STATE>::kind() const  {
    return ("signal_state_slave_export");
}

/**
 * @brief       Binds an export to this export (hierarchical binding).
 *
 * @param       parent export to bind to this export.
 */
template<typename STATE>
inline void
signal_state_slave_export<STATE>::bind(signal_state_slave_export<STATE> & parent) {
    base_type::bind(static_cast<base_type &>(parent));
    m_export.bind(parent.m_export);
}

/**
 * @brief       Binds an export to this export (hierarchical binding).
 *
 * @param       parent export to bind to this export.
 */
template<typename STATE>
inline void
signal_state_slave_export<STATE>::operator() (signal_state_slave_export<STATE> & parent) {
    bind(parent);
}

/**
 * @brief       Binds the specified interface to this export.
 *
 * @param       iface signal_state_transport_if interface to bind to this
 *              export.
 */
template<typename STATE>
inline void
signal_state_slave_export<STATE>::bind(signal_state_transport_if<STATE> & iface) {
    m_export.bind(iface);
}

/**
 * @brief       Binds the specified interface to this export.
 *
 * @param       iface signal_state_transport_if interface to bind to this
 *              export.
 */
template<typename STATE>
inline void
signal_state_slave_export<STATE>::operator() (signal_state_transport_if<STATE> & iface) {
    bind(iface);
}

/*
 * Bidirectional non-blocking transport.
 */
template<typename STATE>
inline signal_response<STATE>
signal_state_slave_export<STATE>::nb_transport(const request_type & req) {
    return (m_export->nb_transport(this->get_export_id(), req));
}

}   /* namespave amba_pv */

#endif  /* defined(SIGNAL_SLAVE_EXPORT__H) */
