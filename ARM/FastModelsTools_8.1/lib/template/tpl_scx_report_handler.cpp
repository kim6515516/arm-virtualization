/*
 * @SOURCE_HEADER@
 *
 * @This_is_a_template_file___Feel_free_to_edit@
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include "GlobalDefs.h"

#include <systemc>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include <TxLib/TxLib.h>
#include <scx/scx_report.h>

/* Namespaces */

/*
 * SystemC eXport support namespace.
 */
namespace scx {

/* Globals - Report handler */

/* Pointer to unique instance of report handler. */
static scx_report_handler_if * default_report_handler_ptr = NULL;

/* Datatypes */

/*
 * Default report handler.
 */
class scx_report_handler: public scx_report_handler_if {

    /* Construction */
    public:
        explicit scx_report_handler();
        ~scx_report_handler();

    /* Reporting */
        void set_verbosity_level(int);
        int get_verbosity_level() const;
        void report_info(const char *, const char *, int, const char *, ...);
        void report_info_verb(int, const char *, const char *, int, const char *, ...);
        void report_warning(const char *, const char *, int, const char *, ...);
        void report_error(const char *, const char *, int, const char *, ...);
        void report_fatal(const char *, const char *, int, const char *, ...);

    /* Implementation */
    private:

        /* Datatypes */

        /*
         * Report message datatype for asynchronous reporting.
         */
        struct report_t {
            sc_core::sc_report * m_rep;
            sc_core::sc_actions m_actions;
            report_t():
                m_rep(NULL),
                m_actions(sc_core::SC_STOP) {
            };
            report_t(const sc_core::sc_report & rep,
                     const sc_core::sc_actions & actions):
                m_rep(new sc_core::sc_report(rep)),
                m_actions(actions) {
            };
            void operator()() {
                if (m_actions & (sc_core::SC_STOP
                                 | sc_core::SC_ABORT
                                 | sc_core::SC_THROW)) {
                    scx_report_handler::m_active->done();
                }
                m_actions &= (sc_core::SC_DISPLAY | sc_core::SC_LOG);
                if (m_rep != NULL) {
                    sc_core::sc_report_handler::default_handler((* m_rep), m_actions);
                    delete m_rep;
                    m_rep = NULL;
                }
            };
        };

        /* Member variables */
        int m_verbosity_level;
        static TxActiveObject<report_t> * m_active;

        /* Helpers */
        static void vreport(sc_core::sc_severity,
                            const char *,
                            const char *,
                            int,
                            const char *,
                            std::va_list);

        /* Report handler */
        static void handler(const sc_core::sc_report &,
                            const sc_core::sc_actions &);
};

/* Globals */

/* Active object for synchronous reporting */
TxActiveObject<scx_report_handler::report_t> *
scx_report_handler::m_active = NULL;

/* Functions */

/*
 * Constructs a new simulation controller.
 */
scx_report_handler::scx_report_handler():
    m_verbosity_level(SCX_NONE) {

    /* Process environmental settings... */

    /* 1) Setup verbosity level */
    const char * verbosity_level = std::getenv("FM_SCX_VERBOSITY_LEVEL");

    if (verbosity_level != NULL) {
        m_verbosity_level = std::atoi(verbosity_level);
    }

    /* 2) Setup asynchronous report handler procedure */
    if (std::getenv("FM_SCX_ENABLE_ASYNC_REPORT") != NULL) {
        std::size_t queue_size = 4096;
        const char * queue_size_str = std::getenv("FM_SCX_ASYNC_REPORT_MAX_SIZE");

        if (queue_size_str != NULL) {
            queue_size = std::max(1, std::atoi(queue_size_str));
        }
        m_active = TxActiveObject<report_t>::create(queue_size);
        sc_core::sc_report_handler::set_handler(handler);
    }
}

/*
 * Destructs this simulation controller.
 */
scx_report_handler::~scx_report_handler() {
    default_report_handler_ptr = NULL;

    /* Reset default report handler procedure */
    sc_core::sc_report_handler::set_handler(& sc_core::sc_report_handler::default_handler);
    if (m_active != NULL) {

        /* Stop asynchronous reporting */
        m_active->done();
        delete m_active;
        m_active = NULL;
    }
}

/*!
 * \brief   Sets the verbosity level for information message reports.
 */
void
scx_report_handler::set_verbosity_level(int verbosity) {
    m_verbosity_level = verbosity;
}

/*!
 * \brief   Returns the verbosity level for information message reports.
 */
int
scx_report_handler::get_verbosity_level() const {
    return (m_verbosity_level);
}

/*!
 * \brief   Reports an information message with variable arguments.
 */
void
scx_report_handler::report_info(const char * id,
                                const char * file,
                                int line,
                                const char * fmt,
                                ...) {
    std::va_list arg;

    va_start(arg, fmt);
    vreport(sc_core::SC_INFO, id, file, line, fmt, arg);
    va_end(arg);
}

/*!
 * \brief   Reports an information message with variable arguments.
 */
void
scx_report_handler::report_info_verb(int verbosity,
                                     const char * id,
                                     const char * file,
                                     int line,
                                     const char * fmt,
                                     ...) {
    std::va_list arg;

    if (verbosity > m_verbosity_level) {
        return;
    }
    va_start(arg, fmt);
    vreport(sc_core::SC_INFO, id, file, line, fmt, arg);
    va_end(arg);
}

/*!
 * \brief   Reports a warning message with variable arguments.
 */
void
scx_report_handler::report_warning(const char * id,
                                   const char * file,
                                   int line,
                                   const char * fmt,
                                   ...) {
    std::va_list arg;

    va_start(arg, fmt);
    vreport(sc_core::SC_WARNING, id, file, line, fmt, arg);
    va_end(arg);
}

/*!
 * \brief   Reports an error message with variable arguments.
 */
void
scx_report_handler::report_error(const char * id,
                                 const char * file,
                                 int line,
                                 const char * fmt,
                                 ...) {
    std::va_list arg;

    va_start(arg, fmt);
    vreport(sc_core::SC_ERROR, id, file, line, fmt, arg);
    va_end(arg);
}

/*!
 * \brief   Reports a fatal error message with variable arguments.
 */
void
scx_report_handler::report_fatal(const char * id,
                                 const char * file,
                                 int line,
                                 const char * fmt,
                                 ...) {
    std::va_list arg;

    va_start(arg, fmt);
    vreport(sc_core::SC_FATAL, id, file, line, fmt, arg);
    va_end(arg);
}

/*
 * Reports a message with variable arguments like the printf() function.
 */
void
scx_report_handler::vreport(sc_core::sc_severity severity,
                            const char * id,
                            const char * file,
                            int line,
                            const char * fmt,
                            std::va_list arg) {
    char msg[1024] = "";

    if ((fmt != NULL) && ((* fmt) != '\0')) {
        ::vsnprintf(msg, sizeof(msg), fmt, arg);
    }
    sc_core::sc_report_handler::report(severity,
                                       id,
                                       msg,
                                       (file == NULL? "(none)": file),
                                       line);
}

/*
 * Handler of message reporting.
 */
void
scx_report_handler::handler(const sc_core::sc_report & rep,
                            const sc_core::sc_actions & actions) {

    /* Handle report asynchronously */
    m_active->push(report_t(rep, actions));
    if (actions & (sc_core::SC_STOP
                   | sc_core::SC_INTERRUPT
                   | sc_core::SC_ABORT
                   | sc_core::SC_THROW)) {

        /* Handle report synchronously */
        sc_core::sc_report_handler::default_handler(rep,
                                                    actions
                                                    & ~(sc_core::SC_DISPLAY
                                                        | sc_core::SC_LOG));
    }
}

/*!
 * \brief   Returns a pointer to the default implementation of the report
 *          handler provided with Fast Models.
 */
scx_report_handler_if * scx_get_default_report_handler() {
    if (default_report_handler_ptr == NULL) {
        static scx_report_handler default_report_handler;

        default_report_handler_ptr = & default_report_handler;
    }
    return (default_report_handler_ptr);
}

}   /* namespace scx */
