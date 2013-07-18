/*
 * SCX: scx_evs_base.h - SystemC eXport support: definition of the base class
 *                       for Exported Virtual Subsystem (EVS).
 *
 * Copyright 2011-2012 ARM Limited.
 * All rights reserved.
 */

#ifndef ARM_SCX_EVS_BASE__H
#define ARM_SCX_EVS_BASE__H

/*!
 * \file    scx_evs_base.h
 * \brief   Exported Virtual Subsystem (EVS) base class.
 * \date    Copyright 2011-2012 ARM Limited. All rights reserved.
 *
 * Definition of the base class for Exported Virtual Subsystem (EVS).
 */

/* Includes */
#include <string>
#include <sstream>
#include <map>

/* Forwards */
namespace sg {
class ComponentFactory;
class Port;
}

/* Namespaces */

/*!
 * \brief   SystemC eXport support namespace.
 */
namespace scx {

/* Forwards */
class ExportedVirtualSubsystem;

/* Datatypes */

/*!
 * \brief   Exported Virtual Subsystem base class.
 */
class scx_evs_base {

    /* Accessors */
    public:

        /* Application and data loading */
        void load_application(const std::string &, const std::string &);
        void load_data(const std::string &,
                       const std::string &,
                       const std::string &);

        /* Parameter handling */
        bool set_parameter(const std::string &, const std::string &);
        template<class T>
        bool set_parameter(const std::string &, T);
        bool get_parameter(const std::string &, std::string &) const;
        template<class T>
        bool get_parameter(const std::string &, T &) const;
        std::string get_parameter(const std::string &) const;
        std::map<std::string, std::string> get_parameter_list() const;

    /* Construction */
    protected:
        scx_evs_base(const std::string &, sg::ComponentFactory *);
        virtual ~scx_evs_base();

    /* Simulation callbacks */
        void before_end_of_elaboration();
        void end_of_elaboration();
        void start_of_simulation();
        void end_of_simulation();

    /* Implementation */
    protected:

        /* Port handling */
        sg::Port & find_sg_port(const std::string &);
        bool publish_master_port(const std::string &, sg::Port &);
        bool publish_slave_port(const std::string &, sg::Port &);

    /* Implementation */
    private:

        /* Member variables */
        ExportedVirtualSubsystem * m_evs;
};

/* Functions */

/*!
 * \brief   Sets the value of a given parameter.
 * \param   name specifies the name of the parameter
 * \param   value specifies the value of the parameter.
 * \return  \c true when the parameter exists, \c false otherwise.
 *
 * Use this function to set parameters from components present in the EVS.
 *
 * \note    Changes made to parameters within SystemCanvas take precedence over
 *          changes made with set_parameter().
 * \note    Parameters might be set during the construction phase, and before
 *          the elaboration phase. Calls to set_parameter() are ignored after
 *          the construction phase.
 */
template<class T>
inline bool
scx_evs_base::set_parameter(const std::string & name, T value) {
    std::stringstream strm;

    strm << value;
    return (set_parameter(name, strm.str()));
}

/*!
 * \brief   Retrieves the value of a given parameter.
 * \param   name specifies the name of the parameter
 * \param   value specifies a reference to the value of the parameter.
 * \return  \c true when the parameter exists, \c false otherwise.
 *
 * Use this function to get parameters from components present in the EVS.
 */
template<class T>
inline bool
scx_evs_base::get_parameter(const std::string & name, T & value) const {
    std::string v;
    std::stringstream strm;

    if (! get_parameter(name, v)) {
        return false;
    }
    strm.str(v);
    strm >> value;
    return true;
}

/*!
 * \brief   Retrieves the value of a given parameter.
 * \param   name specifies the name of the parameter to be retrieved.
 * \return  the value of the parameter when it exists, empty string (\c "")
 *          otherwise.
 *
 * Use this function to get parameters from components present in the EVS.
 */
inline std::string
scx_evs_base::get_parameter(const std::string & name) const {
    std::string v;

    return (get_parameter(name, v)? v: "");
}

}   /* namespace scx */

#endif  /* defined(ARM_SCX_EVS_BASE__H) */
