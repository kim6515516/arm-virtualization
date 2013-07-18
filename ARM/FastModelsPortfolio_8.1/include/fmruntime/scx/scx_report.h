/*
 * SCX: scx_report.h - SystemC eXport support: run-time reporting facilties.
 *
 * Copyright 2011 ARM Limited.
 * All rights reserved.
 */

#ifndef ARM_SCX_REPORT__H
#define ARM_SCX_REPORT__H

/*!
 * \file    scx_report.h
 * \brief   Run-time reporting facilties.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 * Definition of run-time reporting facilties functions.
 */

/* Includes */

/* Namespaces */

/*!
 * \brief   SystemC eXport support namespace.
 */
namespace scx {

/* Functions */

/*!
 * \brief   Reports an information message with variable arguments.
 * \param   id specifies an identifier for this report.
 * \param   fmt specifies a format string just like those given to the
 *          \c printf() function.
 *
 * \hideinitializer
 */
#define SCX_REPORT_INFO(id, fmt, ...) \
    scx::scx_get_curr_report_handler()->report_info(id, \
                                                    __FILE__, \
                                                    __LINE__, \
                                                    fmt, \
                                                    ## __VA_ARGS__ )

/*!
 * \brief   Reports an information message with variable arguments.
 * \param   verbosity specifies a verbosity level for this report.
 * \param   id specifies an identifier for this report.
 * \param   fmt specifies a format string just like those given to the
 *          \c printf() function.
 *
 * When the \a verbosity is greater than the current verbosity level, the
 * information message will not be reported.
 *
 * \see     scx_report_handler_if::set_verbosity_level()
 *
 * \hideinitializer
 */
#define SCX_REPORT_INFO_VERB(verbosity, id, fmt, ...) \
    scx::scx_get_curr_report_handler()->report_info_verb(verbosity, \
                                                         id, \
                                                         __FILE__, \
                                                         __LINE__, \
                                                         fmt, \
                                                         ## __VA_ARGS__ )

/*!
 * \brief   Reports a warning message with variable arguments.
 * \param   id specifies an identifier for this report.
 * \param   fmt specifies a format string just like those given to the
 *          \c printf() function.
 *
 * \hideinitializer
 */
#define SCX_REPORT_WARNING(id, fmt, ...) \
    scx::scx_get_curr_report_handler()->report_warning(id, \
                                                       __FILE__, \
                                                       __LINE__, \
                                                       fmt, \
                                                       ## __VA_ARGS__ )

/*!
 * \brief   Reports an error message with variable arguments.
 * \param   id specifies an identifier for this report.
 * \param   fmt specifies a format string just like those given to the
 *          \c printf() function.
 *
 * SCX_REPORT_ERROR() might throw an \c std::exception.
 *
 * \hideinitializer
 */
#define SCX_REPORT_ERROR(id, fmt, ...) \
    scx::scx_get_curr_report_handler()->report_error(id, \
                                                     __FILE__, \
                                                     __LINE__, \
                                                     fmt, \
                                                     ## __VA_ARGS__ )

/*!
 * \brief   Reports a fatal error message with variable arguments.
 * \param   id specifies an identifier for this report.
 * \param   fmt specifies a format string just like those given to the
 *          \c printf() function.
 *
 * SCX_REPORT_FATAL() might call \c std::abort().
 *
 * \hideinitializer
 */
#define SCX_REPORT_FATAL(id, fmt, ...) \
    scx::scx_get_curr_report_handler()->report_fatal(id, \
                                                     __FILE__, \
                                                     __LINE__, \
                                                     fmt, \
                                                     ## __VA_ARGS__ )

/* Datatypes */

/*!
 * \brief   Report verbosity levels.
 */
enum scx_verbosity {
    SCX_NONE = 0,
    SCX_LOW = 100,
    SCX_MEDIUM = 200,
    SCX_HIGH = 300,
    SCX_FULL = 400,
    SCX_DEBUG = 500
};

/*!
 * \brief   Report handler interface.
 *
 * This interface provides run-time reporting facilities.
 * This interface is used by the simulation engine to report various messages
 * at run-time.
 */
class scx_report_handler_if {

    /* Reporting */
    public:

        /*!
         * \brief   Sets the verbosity level for information message reports.
         * \param   verbosity specifies the verbosity level.
         *
         * \see     get_verbosity_level()
         */
        virtual void set_verbosity_level(int verbosity) = 0;

        /*!
         * \brief   Returns the verbosity level for information message reports.
         *
         * \see     set_verbosity_level()
         */
        virtual int get_verbosity_level() const = 0;

        /*!
         * \brief   Reports an information message with variable arguments.
         * \param   id specifies an identifier for this report
         * \param   file specifies a file name for this report
         * \param   line specifies a line number for this report
         * \param   fmt specifies a format string just like those given to the
         *          \c vprintf() function
         */
        virtual void
        report_info(const char * id,
                    const char * file,
                    int line,
                    const char * fmt, ...) = 0;

        /*!
         * \brief   Reports an information message with variable arguments.
         * \param   verbosity specifies a verbosity level for this report.
         * \param   id specifies an identifier for this report.
         * \param   file specifies a file name for this report
         * \param   line specifies a line number for this report
         * \param   fmt specifies a format string just like those given to the
         *          \c printf() function.
         *
         * When the \a verbosity is greater than the current verbosity level,
         * the information message will not be reported.
         *
         * \see     set_verbosity_level()
         */
        virtual void
        report_info_verb(int verbosity,
                         const char * id,
                         const char * file,
                         int line,
                         const char * fmt, ...) = 0;

        /*!
         * \brief   Reports a warning message with variable arguments.
         * \param   id specifies an identifier for this report
         * \param   file specifies a file name for this report
         * \param   line specifies a line number for this report
         * \param   fmt specifies a format string just like those given to the
         *          \c vprintf() function
         */
        virtual void
        report_warning(const char * id,
                       const char * file,
                       int line,
                       const char * fmt, ...) = 0;

        /*!
         * \brief   Reports an error message with variable arguments.
         * \param   id specifies an identifier for this report
         * \param   file specifies a file name for this report
         * \param   line specifies a line number for this report
         * \param   fmt specifies a format string just like those given to the
         *          \c vprintf() function
         *
         * report_error() might throw an \c std::exception.
         */
        virtual void
        report_error(const char * id,
                     const char * file,
                     int line,
                     const char * fmt, ...) = 0;

        /*!
         * \brief   Reports a fatal error message with variable arguments.
         * \param   id specifies an identifier for this report
         * \param   file specifies a file name for this report
         * \param   line specifies a line number for this report
         * \param   fmt specifies a format string just like those given to the
         *          \c vprintf() function
         *
         * report_error() might call \c std::abort().
         */
        virtual void
        report_fatal(const char * id,
                     const char * file,
                     int line,
                     const char * fmt, ...) = 0;

    /* Implementation */
    protected:

        /*!
         * \brief   Destructor.
         *
         * This version of the function does not allow destroying instance
         * through this interface.
         */
        virtual ~scx_report_handler_if() {
        };
};

/* Functions */


/*!
 * \brief   Returns a pointer to the default implementation of the report
 *          handler provided with Fast Models.
 */
extern scx_report_handler_if *
scx_get_default_report_handler();

/*!
 * \brief   Returns a pointer to the current implementation of the report
 *          handler interface.
 */
extern scx_report_handler_if *
scx_get_curr_report_handler();

}   /* namespace scx */

#endif  /* defined(ARM_SCX_REPORT__H) */
