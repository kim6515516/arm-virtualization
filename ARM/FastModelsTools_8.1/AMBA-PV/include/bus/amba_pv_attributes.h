/*
 * AMBA-PV: amba_pv_attributes.h - Additional user-defined attributes.
 *
 * Copyright 2007-2009 ARM Limited.
 * All rights reserved.
 */

#ifndef AMBA_PV_ATTRIBUTES__H
#define AMBA_PV_ATTRIBUTES__H

/**
 * @file        amba_pv_attributes.h
 *
 * @brief       Additional user-defined attributes.
 */

/* Includes */
#include <map>
#include <string>
#include <sstream>

/* Namespaces */

/**
 * @brief       AMBA-PV namespace.
 */
namespace amba_pv {

/* Datatypes */

/**
 * @brief       Provides support for additional user-defined attributes.
 *
 * The amba_pv_attributes class provides support for <em>user signals</em>
 * in the form of additional named attributes (namely a map).
 *
 * This class is used as a base class for the AMBA-PV protocol additional
 * control information (amba_pv_control) type. To use this class, you must
 * define the @c AMBA_PV_INCLUDE_ATTRIBUTES macro at compile time.
 *
 * @note        This class might impact simulation performance.
 *
 * @see         amba_pv_control
 */
class amba_pv_attributes {

    /* Typdefs */
    public:
        typedef std::map<std::string, std::string> map_type;
        typedef std::pair<std::string, std::string> map_entry_type;
        typedef map_type::iterator iterator_type;
        typedef map_type::const_iterator const_iterator_type;

        /**
         * @brief A @c const reference to a specific attribute in a map of
         *        attributes that is not accessed until it is required.
         */
        class const_attribute_ref {

            /* Construction */
            public:
                const_attribute_ref(const map_type &, const std::string &);

            /* Accessing */
                const std::string & get_name() const;
                template <typename T>
                bool get_value(T &) const;
                bool get_value(std::string &) const;

            /* Implementation */
            protected:
                const map_type & m_cmap;
                const std::string m_name;
        };

        /**
         * @brief A reference to a specific attribute in a map of attributes
         *        that is not accessed until it is required.
         */
        class attribute_ref: public const_attribute_ref {

            /* Construction */
            public:
                attribute_ref(map_type &, const std::string &);

            /* Accessing */
                template <typename T>
                void set_value(T);
                void set_value(const char *);
                void set_value(const std::string &);
                template <typename T>
                attribute_ref & operator=(T);

            /* Implementation */
            private:
                map_type & m_map;
        };

    /* Construction */
        amba_pv_attributes();
        virtual ~amba_pv_attributes();

    /* Accessors */
        void add_attributes(const map_type &); 
        attribute_ref operator[](const std::string &);
        const_attribute_ref operator[](const std::string &) const;
        template <typename T>
        void set_attribute(const std::string &, T);
        template <typename T>
        bool get_attribute(const std::string &, T &) const;
        const_iterator_type attributes_begin() const;
        const_iterator_type attributes_end() const;
        size_t attributes_size() const;
        void remove_attributes(const map_type &); 
        size_t remove_attribute(const std::string &);
        void clear();

    /* Implementation */
    private:

        /* Variable members */
        map_type m_attributes;
};

/* Functions */

/**
 * @brief       Constructor.
 *
 * @param       m a @c const reference to a map of attributes.
 * @param       n the name of the attribute.
 */
inline
amba_pv_attributes::const_attribute_ref::const_attribute_ref(const map_type & m,
                                                             const std::string & n):
    m_cmap(m), m_name(n) {
}

/**
 * @brief       Returns the name of this attribute reference.
 */
inline const std::string &
amba_pv_attributes::const_attribute_ref::get_name() const {
    return (m_name);
}

/**
 * @brief       Returns the value of this attribute reference.
 *
 * @param       v the value of the attribute.
 */
template<typename T>
inline bool
amba_pv_attributes::const_attribute_ref::get_value(T & v) const {
    std::string s;

    if (! get_value(s)) {
        return false;
    }

    std::stringstream strm(s);

    strm >> v;
    return true;
}

/**
 * @brief       Returns the value of this attribute reference.
 *
 * @param       s the value of the attribute.
 */
inline bool
amba_pv_attributes::const_attribute_ref::get_value(std::string & s) const {
    const_iterator_type pos = m_cmap.find(m_name);

    if (pos != m_cmap.end()) {
        s = pos->second;
        return true;
    }
    return false;
}

/**
 * @brief       Constructor.
 *
 * @param       m a reference to a map of attributes.
 * @param       n the name of the attribute.
 */
inline
amba_pv_attributes::attribute_ref::attribute_ref(map_type & m,
                                                 const std::string & n):
    const_attribute_ref(m, n), m_map(m) {
}

/**
 * @brief     Sets the value of this attribute reference.
 *
 * @param     v the value to assign to the attribute.
 */
template<typename T>
inline void
amba_pv_attributes::attribute_ref::set_value(T v) {
    std::stringstream strm;

    strm << v;
    set_value(strm.str());
}

/**
 * @brief     Sets the value of this attribute reference.
 *
 * @param     s the value to assign to the attribute.
 */
inline void
amba_pv_attributes::attribute_ref::set_value(const char * s) {
    set_value(std::string(s));
}

/**
 * @brief     Sets the value of this attribute reference.
 *
 * @param     s the value to assign to the attribute.
 */
inline void
amba_pv_attributes::attribute_ref::set_value(const std::string & s) {
    std::pair<iterator_type, bool> result = m_map.insert(make_pair(m_name, s));

    if (result.second == false) {
        result.first->second = s;
    }
}

/**
 * @brief       Sets the value of this attribute reference.
 *
 * @param       v the value to assign to the attribute.
 */
template<typename T>
inline amba_pv_attributes::attribute_ref &
amba_pv_attributes::attribute_ref::operator =(T v) {
    set_value(v);
    return (* this);
}

/**
 * @brief       Default constructor.
 */
inline
amba_pv_attributes::amba_pv_attributes() {
}

/**
 * @brief       Destructor.
 */
inline
amba_pv_attributes::~amba_pv_attributes() {
}

/**
 * @brief       Adds a set of attributes.
 *
 * @param       m additional attributes to be added.
 */
inline void
amba_pv_attributes::add_attributes(const map_type & m) {
    const_iterator_type pos;
    
    for (pos = m.begin(); pos != m.end(); ++ pos) {
        set_attribute(pos->first, pos->second);
    }
}

/**
 * @brief       Returns a reference to an attribute.
 *
 * The returned reference can be used later to assign to the attribute.
 *
 * @param       n the name of the attribute.
 *
 * @note        This cannot be used on a @c const amba_pv_attributes.
 */
inline amba_pv_attributes::attribute_ref
amba_pv_attributes::operator [](const std::string & n) {
    return (attribute_ref(m_attributes, n));
}

/**
 * @brief       Returns a reference to an attribute.
 *
 * The returned reference can be used later to read the attribute.
 *
 * @param       n the name of the attribute.
 */
inline amba_pv_attributes::const_attribute_ref
amba_pv_attributes::operator [](const std::string & n) const {
    return (const_attribute_ref(m_attributes, n));
}

/**
 * @brief       Sets the value of a given attribute.
 *
 * @param       n the name of the attribute.
 * @param       v the value of the attribute.
 *
 * @see         operator[]()
 */
template <typename T>
inline void
amba_pv_attributes::set_attribute(const std::string & n, T v) {
    (* this)[n] = v;
}

/**
 * @brief       Returns the value of a given attribute.
 *
 * @param       n the name of the attribute.
 * @param       v the value of the attribute.
 *
 * @see         operator[]()
 */
template <typename T>
inline bool
amba_pv_attributes::get_attribute(const std::string & n, T & v) const {
    return ((* this)[n].get_value(v));
}

/**
 * @brief       Returns an iterator that can be used to begin traversing
 *              through the attributes.
 *
 * @see         attributes_end(), attributes_size()
 */
inline std::map<std::string, std::string>::const_iterator
amba_pv_attributes::attributes_begin() const {
    return (m_attributes.begin());
}

/**
 * @brief       Returns an iterator that can be used in comparison for ending
 *              traversal through the attributes.
 *
 * @see         attributes_begin(), attributes_size()
 */
inline std::map<std::string, std::string>::const_iterator
amba_pv_attributes::attributes_end() const {
    return (m_attributes.end());
}

/**
 * @brief       Returns the number of attributes currently stored.
 *
 * @see         attributes_begin(), attributes_end()
 */
inline size_t
amba_pv_attributes::attributes_size() const {
    return (m_attributes.size());
}

/**
 * @brief       Removes a set of attributes.
 *
 * @param       m attributes to be removed.
 *
 * @see         remove_attribute(), clear()
 */
inline void
amba_pv_attributes::remove_attributes(const map_type & m) {
    const_iterator_type pos;
    
    for (pos = m.begin(); pos != m.end(); ++ pos) {
        remove_attribute(pos->first);
    }
}

/**
 * @brief       Removes the given attribute.
 *
 * @param       n the name of the attribute.
 *
 * @see         remove_attributes(), clear()
 */
inline size_t
amba_pv_attributes::remove_attribute(const std::string & n) {
    return (m_attributes.erase(n));
}

/**
 * @brief       Clears content.
 *
 * All attributes are dropped.
 *
 * @see         remove_attributes(), remove_attribute()
 */
inline void
amba_pv_attributes::clear() {
    m_attributes.clear();
}

}   /* namespace amba_pv */

#endif  /* defined(AMBA_PV_ATTRIBUTES__H) */
