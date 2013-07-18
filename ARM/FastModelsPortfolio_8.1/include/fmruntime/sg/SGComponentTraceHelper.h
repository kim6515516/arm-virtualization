/*!
 * \file    SGComponentTraceHelper.h
 * \brief   A set of macros and meta-programming widgets to make tracing easier
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 */
#ifndef SGCOMPONENTTRACEHELPER_H
#define SGCOMPONENTTRACEHELPER_H

#include "sg/MSCFixes.h"
#include "sg/SGComponentTrace.h"

#include <cstdlib>
#include <vector>

///
/// **********************************************************************
/// **********************************************************************
///
///                         AUTO-GENERATED
///
/// To re-create: run the perl script:
///     Framework/Source/generate_SGComponentTraceHelper.pl
///
/// **********************************************************************
/// **********************************************************************
///

template<unsigned N> struct trace_fixed_length_string {
    static unsigned const     size = N;

    char const* s;
    operator char const*() const { return s; }

    trace_fixed_length_string( char const* s_ = "" ) : s(s_) {}
};

namespace trace_source_details
{
    template< typename T > struct traits_base
    {
        typedef T                               type;
        static MTI::EventFieldType::Type const  type_spec = MTI::EventFieldType::MTI_UNSIGNED_INT;
        static unsigned const                   size      = sizeof(type);
        static unsigned const                   max_size  = 0; // default for fixed length

        static T convert_for_trace(T in_)
        {
            return in_;
        }
    };

    template< typename T > struct traits : public traits_base<T>
    {
    };

    template<> struct traits<bool> : public traits_base<bool>
    {
        static MTI::EventFieldType::Type const type_spec = MTI::EventFieldType::MTI_BOOL;
    };

    template<> struct traits<char> : public traits_base<char>
    {
        static MTI::EventFieldType::Type const type_spec = MTI::EventFieldType::MTI_STRING;
    };

    template<typename T> struct traits_signed : public traits_base<T>
    {
        static MTI::EventFieldType::Type const type_spec = MTI::EventFieldType::MTI_SIGNED_INT;
    };
    template<> struct traits<int8_t> : public traits_signed<int8_t>
    {
    };
    template<> struct traits<int16_t> : public traits_signed<int16_t>
    {
    };
    template<> struct traits<int32_t> : public traits_signed<int32_t>
    {
    };
    template<> struct traits<int64_t> : public traits_signed<int64_t>
    {
    };

    template<unsigned N> struct traits< trace_fixed_length_string<N> >
      : public traits_base< trace_fixed_length_string<N> >
    {
        typedef char const*                     type;
        static MTI::EventFieldType::Type const  type_spec = MTI::EventFieldType::MTI_STRING;
        static unsigned const                   size = 0;
        static unsigned const                   max_size  = N;
    };

/// MTI is broken at the moment and using this will lead to random data
/// corruption!  Prefer trace_fixed_length_string<N> instead.
#if 0
    /// Prefer not to use this!
    template<> struct traits<char const*>
    {
        typedef char const*                     type;
        static MTI::EventFieldType::Type const  type_spec = MTI::EventFieldType::MTI_STRING;
        static unsigned const                   size      = 0; // hmmm?
        static unsigned const                   max_size  = 0; // default for fixed length
    };
#endif

    template<size_t max_size_> struct traits<sg::size_and_pointer<max_size_> >
      : public traits_base< sg::size_and_pointer<max_size_> >
    {
        typedef sg::size_and_pointer<max_size_> type;
        static MTI::EventFieldType::Type const type_spec = MTI::EventFieldType::MTI_UNSIGNED_INT;
        static unsigned const                   size      = 0; // variable length
        static unsigned const                   max_size  = max_size_;
    };

    /// helper class used to encapsulate the description and any symbols that may be attached.
    class description
    {
        std::string const d;

        // This will leak memory!
        mutable std::vector< std::pair<uint32_t, char const*> >   symbols;

        static char* global_deleter(char*);
    public:
        description( char const*        description_ ) : d(description_) {}
        description( std::string const& description_ ) : d(description_) {}

        std::string get_description() const { return d; }

        description& operator () (uint32_t v, std::string const& s_)
        {
            dangerous_add(v,s_); return *this;
        }

        /// This is 'dangerous' in the sense that it works on a const object
        description const& dangerous_add(uint32_t v, std::string const& s_) const
        {
            char* value = global_deleter(new char[s_.size() + 1]);
            memcpy( value, s_.data(), s_.size() );
            value[s_.size()] = '\0';
            symbols.push_back( std::make_pair( v, value ) );
            return *this;
        }

        description& operator () (uint32_t v, char const* s_)
        {
            dangerous_add(v,s_); return *this;
        }
        
        /// This is 'dangerous' in the sense that it works on a const object
        description const& dangerous_add(uint32_t v, char const* s_) const
        {
            size_t size = strlen(s_);
            char* value = global_deleter(new char[size + 1]);
            memcpy( value, s_, size );
            value[size] = '\0';
            symbols.push_back( std::make_pair( v, value ) );
            return *this;
        }

        char const* get_symbol_name_from_value( uint32_t v ) const
        {
            unsigned i = 0;
            while (i != symbols.size() && symbols[i].first != v)
                ++ i;
            return i == symbols.size() ? (char const*)0 : symbols[i].second;
        }


        description& symbol( uint32_t v, std::string const& s_ ) { return (*this)(v,s_); }
        description& symbol( uint32_t v, char const*        s_ ) { return (*this)(v,s_); }

        size_t get_number_of_symbols() const { return symbols.size(); }
        
        std::pair<uint32_t, char const*> get_symbol(size_t i_) const
        {
            assert( i_ < symbols.size() ); return symbols[i_];
        }
    };

    struct base
    {
        virtual ~base()
        {
            for (unsigned i = 0; i != strduped_strings_to_destroy.size(); ++ i)
            {
                free( strduped_strings_to_destroy[i] );
            }
        }
        virtual void init() = 0;

      protected:

        std::vector<char*>   strduped_strings_to_destroy;

        char* dup(std::string const& s_)
        {
            char* ret = ::strdup(s_.c_str());
            strduped_strings_to_destroy.push_back(ret);
            return ret;
        }
        
        void add_field(
            sg::EventSourceBase*          event_source_base_,
            std::string const&            field_name_,
            description const&            description_,
            ::MTI::EventFieldType::Type   type_,
            ::MTI::EventFieldType::Size   size_,
            ::MTI::EventFieldType::Size   max_size_
            )
        {
            size_t const number_of_symbols = description_.get_number_of_symbols();
            if (number_of_symbols != 0)
            {
                assert (type_ != MTI::EventFieldType::MTI_STRING
                        ||  0 == "String fields are not allowed to be enums");
                if (type_ == MTI::EventFieldType::MTI_BOOL)
                {
                    if (number_of_symbols != 2)
                    {
                        assert( 0 == "Field encodes a bool but the number of symbols attached is not two!" );
                    }
                    else
                    {
                        uint32_t const first  = description_.get_symbol(0).first;
                        uint32_t const second = description_.get_symbol(1).first;
                        (void)first;
                        (void)second;
                        assert( (first == 0 && second == 1)
                                || (first == 1 && second == 0)
                                || 0 == "Bool field with symbols attached but the value of the symbols do not map onto 0 and 1" );
                    }
                }
                if (size_ > 4)
                {
                    assert( 0 == "Cannot attach enum symbols to a field that is more than four bytes" );
                }
                MTI::FieldIndex const fidx = event_source_base_->AddField(
                    dup(field_name_),
                    dup(description_.get_description()),
                    MTI::EventFieldType::MTI_ENUM, // NOTE not the original one!
                    size_,
                    max_size_
                    );
                for (size_t i = 0; i != description_.get_number_of_symbols(); ++ i)
                    event_source_base_->AddEnumConstant(
                        fidx,
                        description_.get_symbol(i).first,
                        dup(description_.get_symbol(i).second)
                    );
            }
            else
            {
                MTI::FieldIndex const fidx = event_source_base_->AddField(
                    dup(field_name_),
                    dup(description_.get_description()),
                    type_,
                    size_,
                    max_size_
                    );
                (void)fidx;
            }
        }
    };

    /// This should never be instantiated, it means that the FIELD_TUPLES (or arguments to describe_fields)
    /// are the wrong number compared to the number of arguments in the SIGNATURE_TUPLE.
    template<typename T>
    struct error_wrong_number_of_fields_in_description
    {
    };
    
}

inline ::trace_source_details::description const& enhance_trace_description(
    ::trace_source_details::description const& description_,
    ...
    )
{
    return description_;
}

///
/// Simplify registering objects with a trace sink.
///
/// For example, if you have an sg::CADIBase or fs::CADIInterface then you
/// can do:
/// <code>
///     register_objects_with_component_trace( my_cadi_interface )
///         << my_trace_source0
///         << my_trace_source1
///         << my_trace_source2
///         ;
/// </code>
///
/// There is no requirement to use this, it is supplied as a convenience to make
/// your code simpler.
///
template<typename T>
struct register_objects_with_component_trace_t
{
    T& sink;

    register_objects_with_component_trace_t( T& sink_ ) : sink(sink_) {}
    // default assignment, copy constructor and destructor are OK.

    template<typename TRACE_SOURCE>
    register_objects_with_component_trace_t& operator <<(TRACE_SOURCE& trace_source_)
    {
        trace_source_details::base& b = trace_source_;
        b.init();
        sink.RegisterTraceSource( &trace_source_ );
        return *this;
    }
};

template<typename T>
inline register_objects_with_component_trace_t<T> register_objects_with_component_trace(T& sink_)
{
    return register_objects_with_component_trace_t<T>(sink_);
}


///
/// \define DEFINE_SIMPLE_TRACE_SOURCE_CLASS
///
/// Define a class CNAME that is-a trace_source_t.
///
/// NAME and DESCRIPTION is the name and description of the event source.
///
/// SIGNATURE_TUPLE is something like (uint64_t) or (uint64_t, char), i.e.
/// a parenthesised expression of types.
///
/// FIELD_TUPLES is a parenthesised tuple of names and descriptions for each of
/// the fields, e.g. ("field0", "field0 description", "field1", "field1 description")
///
/// In addition, the description can specify an enumeration, an example is:
/// <code>
///           description( "Line transformation incurred" )
///           ('I', "invalid")
///           ('D', "unaffected and dirty")
///           ('C', "unaffected and clean")
///           ('X', "already clean")
///           ('x', "was dirty now clean")
/// </code>
///
/// MTI limits us to enumerations values that are a maximum of 32 bits.  The
/// corresponding member of the signature must be sufficient to store the
/// enumerated values.
///
/// An example to show how to capture an active change event:
/// <code>
///      DEFINE_SIMPLE_TRACE_SOURCE_CLASS(
///          gic_log_warnings_out_trace_base_t,
///          "gic_log_warnings_out",
///          "Warnings from the VGIC model",
///          (trace_fixed_length_string<200>)
///          ( "message",
///            "The message from the VGIC" );
///          );
///      
///      struct gic_log_warnings_out_trace_t : public gic_log_warnings_out_trace_base_t
///      {
///          virtual void activeStateChanged( bool new_active_state_ )
///          {
///              ...
///          }
///      } gic_log_warnings_out_trace;
///      
///      gic_log_warnings_out_trace( "example message" ); // example on how to signal a trace
///  <code>

#define DEFINE_SIMPLE_TRACE_SOURCE_CLASS( CNAME, NAME, DESCRIPTION, SIGNATURE_TUPLE, FIELD_TUPLES ) \
    struct CNAME : trace_source_t<void SIGNATURE_TUPLE> {               \
                                                                        \
        typedef trace_source_details::description description;          \
        virtual void init()                                             \
        {                                                               \
            if (this->GetName()[0] == '\0')                             \
                this->setName(NAME);                                    \
            if (this->GetDescription()[0] == '\0')                      \
                this->setDescription(DESCRIPTION);                      \
            describe_fields FIELD_TUPLES;                               \
        }                                                               \
    }

///
/// \define DEFINE_SIMPLE_TRACE_SOURCE
///
/// Same as DEFINE_SIMPLE_TRACE_SOURCE_CLASS except the INAME is instance name,
/// and the class is INAME_t.
///
#define DEFINE_SIMPLE_TRACE_SOURCE( INAME, NAME, DESCRIPTION, SIGNATURE_TUPLE, FIELD_TUPLES ) \
    struct INAME##_t : trace_source_t<void SIGNATURE_TUPLE> {           \
                                                                        \
        typedef trace_source_details::description description;          \
        virtual void init()                                             \
        {                                                               \
            this->setName(NAME);                                        \
            this->setDescription(DESCRIPTION);                          \
            describe_fields FIELD_TUPLES;                               \
        }                                                               \
    } INAME


/// Base template for all trace_source_t, should never instantiated directly.
template<typename T> struct trace_source_t {};

// Zero case is sufficient different to be specified separately
template<>
struct trace_source_t<void()>
    : trace_source_details::base,
      sg::EventSource0
{
    typedef sg::EventSource0 base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 0;

    /* GB: I couldn't get this to compile correctly
    void describe_fields( ... )
    {
        //trace_source_details::error_wrong_number_of_fields_in_description<>::ok;
    }
    */

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields()
    {
    }

    void operator()()
    {
        this->fire();
    }

};



// Auto-generated -- see header
template< typename T0 >
struct trace_source_t<void(T0)>
    : trace_source_details::base,
      sg::EventSource1<typename trace_source_details::traits<T0>::type>
{
    typedef sg::EventSource1<typename trace_source_details::traits<T0>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 1;
    typedef T0    arg0_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
    }

    void operator()( arg0_type t0 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1 >
struct trace_source_t<void(T0,T1)>
    : trace_source_details::base,
      sg::EventSource2<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type>
{
    typedef sg::EventSource2<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 2;
    typedef T0    arg0_type;
    typedef T1    arg1_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2 >
struct trace_source_t<void(T0,T1,T2)>
    : trace_source_details::base,
      sg::EventSource3<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type>
{
    typedef sg::EventSource3<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 3;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3 >
struct trace_source_t<void(T0,T1,T2,T3)>
    : trace_source_details::base,
      sg::EventSource4<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type>
{
    typedef sg::EventSource4<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 4;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4 >
struct trace_source_t<void(T0,T1,T2,T3,T4)>
    : trace_source_details::base,
      sg::EventSource5<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type>
{
    typedef sg::EventSource5<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 5;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5)>
    : trace_source_details::base,
      sg::EventSource6<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type>
{
    typedef sg::EventSource6<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 6;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6)>
    : trace_source_details::base,
      sg::EventSource7<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type>
{
    typedef sg::EventSource7<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 7;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7)>
    : trace_source_details::base,
      sg::EventSource8<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type>
{
    typedef sg::EventSource8<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 8;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8)>
    : trace_source_details::base,
      sg::EventSource9<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type>
{
    typedef sg::EventSource9<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 9;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9)>
    : trace_source_details::base,
      sg::EventSource10<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type>
{
    typedef sg::EventSource10<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 10;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10)>
    : trace_source_details::base,
      sg::EventSource11<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type>
{
    typedef sg::EventSource11<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 11;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11)>
    : trace_source_details::base,
      sg::EventSource12<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type>
{
    typedef sg::EventSource12<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 12;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12)>
    : trace_source_details::base,
      sg::EventSource13<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type>
{
    typedef sg::EventSource13<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 13;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13)>
    : trace_source_details::base,
      sg::EventSource14<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type>
{
    typedef sg::EventSource14<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 14;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14)>
    : trace_source_details::base,
      sg::EventSource15<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type>
{
    typedef sg::EventSource15<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 15;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;
    typedef T14    arg14_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_,
        std::string const&       field_name14_,
        description const&       field_description14_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
        add_field( this, field_name14_,
                   enhance_trace_description(field_description14_, (arg14_type*)0),
                   ::trace_source_details::traits<arg14_type>::type_spec,
                   ::trace_source_details::traits<arg14_type>::size,
                   ::trace_source_details::traits<arg14_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13, arg14_type t14 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13), ::trace_source_details::traits<arg14_type>::convert_for_trace(t14) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15)>
    : trace_source_details::base,
      sg::EventSource16<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type>
{
    typedef sg::EventSource16<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 16;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;
    typedef T14    arg14_type;
    typedef T15    arg15_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_,
        std::string const&       field_name14_,
        description const&       field_description14_,
        std::string const&       field_name15_,
        description const&       field_description15_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
        add_field( this, field_name14_,
                   enhance_trace_description(field_description14_, (arg14_type*)0),
                   ::trace_source_details::traits<arg14_type>::type_spec,
                   ::trace_source_details::traits<arg14_type>::size,
                   ::trace_source_details::traits<arg14_type>::max_size );
        add_field( this, field_name15_,
                   enhance_trace_description(field_description15_, (arg15_type*)0),
                   ::trace_source_details::traits<arg15_type>::type_spec,
                   ::trace_source_details::traits<arg15_type>::size,
                   ::trace_source_details::traits<arg15_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13, arg14_type t14, arg15_type t15 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13), ::trace_source_details::traits<arg14_type>::convert_for_trace(t14), ::trace_source_details::traits<arg15_type>::convert_for_trace(t15) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16)>
    : trace_source_details::base,
      sg::EventSource17<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type>
{
    typedef sg::EventSource17<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 17;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;
    typedef T14    arg14_type;
    typedef T15    arg15_type;
    typedef T16    arg16_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_,
        std::string const&       field_name14_,
        description const&       field_description14_,
        std::string const&       field_name15_,
        description const&       field_description15_,
        std::string const&       field_name16_,
        description const&       field_description16_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
        add_field( this, field_name14_,
                   enhance_trace_description(field_description14_, (arg14_type*)0),
                   ::trace_source_details::traits<arg14_type>::type_spec,
                   ::trace_source_details::traits<arg14_type>::size,
                   ::trace_source_details::traits<arg14_type>::max_size );
        add_field( this, field_name15_,
                   enhance_trace_description(field_description15_, (arg15_type*)0),
                   ::trace_source_details::traits<arg15_type>::type_spec,
                   ::trace_source_details::traits<arg15_type>::size,
                   ::trace_source_details::traits<arg15_type>::max_size );
        add_field( this, field_name16_,
                   enhance_trace_description(field_description16_, (arg16_type*)0),
                   ::trace_source_details::traits<arg16_type>::type_spec,
                   ::trace_source_details::traits<arg16_type>::size,
                   ::trace_source_details::traits<arg16_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13, arg14_type t14, arg15_type t15, arg16_type t16 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13), ::trace_source_details::traits<arg14_type>::convert_for_trace(t14), ::trace_source_details::traits<arg15_type>::convert_for_trace(t15), ::trace_source_details::traits<arg16_type>::convert_for_trace(t16) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17)>
    : trace_source_details::base,
      sg::EventSource18<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type>
{
    typedef sg::EventSource18<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 18;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;
    typedef T14    arg14_type;
    typedef T15    arg15_type;
    typedef T16    arg16_type;
    typedef T17    arg17_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_,
        std::string const&       field_name14_,
        description const&       field_description14_,
        std::string const&       field_name15_,
        description const&       field_description15_,
        std::string const&       field_name16_,
        description const&       field_description16_,
        std::string const&       field_name17_,
        description const&       field_description17_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
        add_field( this, field_name14_,
                   enhance_trace_description(field_description14_, (arg14_type*)0),
                   ::trace_source_details::traits<arg14_type>::type_spec,
                   ::trace_source_details::traits<arg14_type>::size,
                   ::trace_source_details::traits<arg14_type>::max_size );
        add_field( this, field_name15_,
                   enhance_trace_description(field_description15_, (arg15_type*)0),
                   ::trace_source_details::traits<arg15_type>::type_spec,
                   ::trace_source_details::traits<arg15_type>::size,
                   ::trace_source_details::traits<arg15_type>::max_size );
        add_field( this, field_name16_,
                   enhance_trace_description(field_description16_, (arg16_type*)0),
                   ::trace_source_details::traits<arg16_type>::type_spec,
                   ::trace_source_details::traits<arg16_type>::size,
                   ::trace_source_details::traits<arg16_type>::max_size );
        add_field( this, field_name17_,
                   enhance_trace_description(field_description17_, (arg17_type*)0),
                   ::trace_source_details::traits<arg17_type>::type_spec,
                   ::trace_source_details::traits<arg17_type>::size,
                   ::trace_source_details::traits<arg17_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13, arg14_type t14, arg15_type t15, arg16_type t16, arg17_type t17 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13), ::trace_source_details::traits<arg14_type>::convert_for_trace(t14), ::trace_source_details::traits<arg15_type>::convert_for_trace(t15), ::trace_source_details::traits<arg16_type>::convert_for_trace(t16), ::trace_source_details::traits<arg17_type>::convert_for_trace(t17) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18)>
    : trace_source_details::base,
      sg::EventSource19<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type,typename trace_source_details::traits<T18>::type>
{
    typedef sg::EventSource19<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type,typename trace_source_details::traits<T18>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 19;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;
    typedef T14    arg14_type;
    typedef T15    arg15_type;
    typedef T16    arg16_type;
    typedef T17    arg17_type;
    typedef T18    arg18_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_,
        std::string const&       field_name14_,
        description const&       field_description14_,
        std::string const&       field_name15_,
        description const&       field_description15_,
        std::string const&       field_name16_,
        description const&       field_description16_,
        std::string const&       field_name17_,
        description const&       field_description17_,
        std::string const&       field_name18_,
        description const&       field_description18_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
        add_field( this, field_name14_,
                   enhance_trace_description(field_description14_, (arg14_type*)0),
                   ::trace_source_details::traits<arg14_type>::type_spec,
                   ::trace_source_details::traits<arg14_type>::size,
                   ::trace_source_details::traits<arg14_type>::max_size );
        add_field( this, field_name15_,
                   enhance_trace_description(field_description15_, (arg15_type*)0),
                   ::trace_source_details::traits<arg15_type>::type_spec,
                   ::trace_source_details::traits<arg15_type>::size,
                   ::trace_source_details::traits<arg15_type>::max_size );
        add_field( this, field_name16_,
                   enhance_trace_description(field_description16_, (arg16_type*)0),
                   ::trace_source_details::traits<arg16_type>::type_spec,
                   ::trace_source_details::traits<arg16_type>::size,
                   ::trace_source_details::traits<arg16_type>::max_size );
        add_field( this, field_name17_,
                   enhance_trace_description(field_description17_, (arg17_type*)0),
                   ::trace_source_details::traits<arg17_type>::type_spec,
                   ::trace_source_details::traits<arg17_type>::size,
                   ::trace_source_details::traits<arg17_type>::max_size );
        add_field( this, field_name18_,
                   enhance_trace_description(field_description18_, (arg18_type*)0),
                   ::trace_source_details::traits<arg18_type>::type_spec,
                   ::trace_source_details::traits<arg18_type>::size,
                   ::trace_source_details::traits<arg18_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13, arg14_type t14, arg15_type t15, arg16_type t16, arg17_type t17, arg18_type t18 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13), ::trace_source_details::traits<arg14_type>::convert_for_trace(t14), ::trace_source_details::traits<arg15_type>::convert_for_trace(t15), ::trace_source_details::traits<arg16_type>::convert_for_trace(t16), ::trace_source_details::traits<arg17_type>::convert_for_trace(t17), ::trace_source_details::traits<arg18_type>::convert_for_trace(t18) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19)>
    : trace_source_details::base,
      sg::EventSource20<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type,typename trace_source_details::traits<T18>::type,typename trace_source_details::traits<T19>::type>
{
    typedef sg::EventSource20<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type,typename trace_source_details::traits<T18>::type,typename trace_source_details::traits<T19>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 20;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;
    typedef T14    arg14_type;
    typedef T15    arg15_type;
    typedef T16    arg16_type;
    typedef T17    arg17_type;
    typedef T18    arg18_type;
    typedef T19    arg19_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_,
        std::string const&       field_name14_,
        description const&       field_description14_,
        std::string const&       field_name15_,
        description const&       field_description15_,
        std::string const&       field_name16_,
        description const&       field_description16_,
        std::string const&       field_name17_,
        description const&       field_description17_,
        std::string const&       field_name18_,
        description const&       field_description18_,
        std::string const&       field_name19_,
        description const&       field_description19_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
        add_field( this, field_name14_,
                   enhance_trace_description(field_description14_, (arg14_type*)0),
                   ::trace_source_details::traits<arg14_type>::type_spec,
                   ::trace_source_details::traits<arg14_type>::size,
                   ::trace_source_details::traits<arg14_type>::max_size );
        add_field( this, field_name15_,
                   enhance_trace_description(field_description15_, (arg15_type*)0),
                   ::trace_source_details::traits<arg15_type>::type_spec,
                   ::trace_source_details::traits<arg15_type>::size,
                   ::trace_source_details::traits<arg15_type>::max_size );
        add_field( this, field_name16_,
                   enhance_trace_description(field_description16_, (arg16_type*)0),
                   ::trace_source_details::traits<arg16_type>::type_spec,
                   ::trace_source_details::traits<arg16_type>::size,
                   ::trace_source_details::traits<arg16_type>::max_size );
        add_field( this, field_name17_,
                   enhance_trace_description(field_description17_, (arg17_type*)0),
                   ::trace_source_details::traits<arg17_type>::type_spec,
                   ::trace_source_details::traits<arg17_type>::size,
                   ::trace_source_details::traits<arg17_type>::max_size );
        add_field( this, field_name18_,
                   enhance_trace_description(field_description18_, (arg18_type*)0),
                   ::trace_source_details::traits<arg18_type>::type_spec,
                   ::trace_source_details::traits<arg18_type>::size,
                   ::trace_source_details::traits<arg18_type>::max_size );
        add_field( this, field_name19_,
                   enhance_trace_description(field_description19_, (arg19_type*)0),
                   ::trace_source_details::traits<arg19_type>::type_spec,
                   ::trace_source_details::traits<arg19_type>::size,
                   ::trace_source_details::traits<arg19_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13, arg14_type t14, arg15_type t15, arg16_type t16, arg17_type t17, arg18_type t18, arg19_type t19 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13), ::trace_source_details::traits<arg14_type>::convert_for_trace(t14), ::trace_source_details::traits<arg15_type>::convert_for_trace(t15), ::trace_source_details::traits<arg16_type>::convert_for_trace(t16), ::trace_source_details::traits<arg17_type>::convert_for_trace(t17), ::trace_source_details::traits<arg18_type>::convert_for_trace(t18), ::trace_source_details::traits<arg19_type>::convert_for_trace(t19) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20)>
    : trace_source_details::base,
      sg::EventSource21<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type,typename trace_source_details::traits<T18>::type,typename trace_source_details::traits<T19>::type,typename trace_source_details::traits<T20>::type>
{
    typedef sg::EventSource21<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type,typename trace_source_details::traits<T18>::type,typename trace_source_details::traits<T19>::type,typename trace_source_details::traits<T20>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 21;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;
    typedef T14    arg14_type;
    typedef T15    arg15_type;
    typedef T16    arg16_type;
    typedef T17    arg17_type;
    typedef T18    arg18_type;
    typedef T19    arg19_type;
    typedef T20    arg20_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_,
        std::string const&       field_name14_,
        description const&       field_description14_,
        std::string const&       field_name15_,
        description const&       field_description15_,
        std::string const&       field_name16_,
        description const&       field_description16_,
        std::string const&       field_name17_,
        description const&       field_description17_,
        std::string const&       field_name18_,
        description const&       field_description18_,
        std::string const&       field_name19_,
        description const&       field_description19_,
        std::string const&       field_name20_,
        description const&       field_description20_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
        add_field( this, field_name14_,
                   enhance_trace_description(field_description14_, (arg14_type*)0),
                   ::trace_source_details::traits<arg14_type>::type_spec,
                   ::trace_source_details::traits<arg14_type>::size,
                   ::trace_source_details::traits<arg14_type>::max_size );
        add_field( this, field_name15_,
                   enhance_trace_description(field_description15_, (arg15_type*)0),
                   ::trace_source_details::traits<arg15_type>::type_spec,
                   ::trace_source_details::traits<arg15_type>::size,
                   ::trace_source_details::traits<arg15_type>::max_size );
        add_field( this, field_name16_,
                   enhance_trace_description(field_description16_, (arg16_type*)0),
                   ::trace_source_details::traits<arg16_type>::type_spec,
                   ::trace_source_details::traits<arg16_type>::size,
                   ::trace_source_details::traits<arg16_type>::max_size );
        add_field( this, field_name17_,
                   enhance_trace_description(field_description17_, (arg17_type*)0),
                   ::trace_source_details::traits<arg17_type>::type_spec,
                   ::trace_source_details::traits<arg17_type>::size,
                   ::trace_source_details::traits<arg17_type>::max_size );
        add_field( this, field_name18_,
                   enhance_trace_description(field_description18_, (arg18_type*)0),
                   ::trace_source_details::traits<arg18_type>::type_spec,
                   ::trace_source_details::traits<arg18_type>::size,
                   ::trace_source_details::traits<arg18_type>::max_size );
        add_field( this, field_name19_,
                   enhance_trace_description(field_description19_, (arg19_type*)0),
                   ::trace_source_details::traits<arg19_type>::type_spec,
                   ::trace_source_details::traits<arg19_type>::size,
                   ::trace_source_details::traits<arg19_type>::max_size );
        add_field( this, field_name20_,
                   enhance_trace_description(field_description20_, (arg20_type*)0),
                   ::trace_source_details::traits<arg20_type>::type_spec,
                   ::trace_source_details::traits<arg20_type>::size,
                   ::trace_source_details::traits<arg20_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13, arg14_type t14, arg15_type t15, arg16_type t16, arg17_type t17, arg18_type t18, arg19_type t19, arg20_type t20 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13), ::trace_source_details::traits<arg14_type>::convert_for_trace(t14), ::trace_source_details::traits<arg15_type>::convert_for_trace(t15), ::trace_source_details::traits<arg16_type>::convert_for_trace(t16), ::trace_source_details::traits<arg17_type>::convert_for_trace(t17), ::trace_source_details::traits<arg18_type>::convert_for_trace(t18), ::trace_source_details::traits<arg19_type>::convert_for_trace(t19), ::trace_source_details::traits<arg20_type>::convert_for_trace(t20) );
    }

};


// Auto-generated -- see header
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21 >
struct trace_source_t<void(T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21)>
    : trace_source_details::base,
      sg::EventSource22<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type,typename trace_source_details::traits<T18>::type,typename trace_source_details::traits<T19>::type,typename trace_source_details::traits<T20>::type,typename trace_source_details::traits<T21>::type>
{
    typedef sg::EventSource22<typename trace_source_details::traits<T0>::type,typename trace_source_details::traits<T1>::type,typename trace_source_details::traits<T2>::type,typename trace_source_details::traits<T3>::type,typename trace_source_details::traits<T4>::type,typename trace_source_details::traits<T5>::type,typename trace_source_details::traits<T6>::type,typename trace_source_details::traits<T7>::type,typename trace_source_details::traits<T8>::type,typename trace_source_details::traits<T9>::type,typename trace_source_details::traits<T10>::type,typename trace_source_details::traits<T11>::type,typename trace_source_details::traits<T12>::type,typename trace_source_details::traits<T13>::type,typename trace_source_details::traits<T14>::type,typename trace_source_details::traits<T15>::type,typename trace_source_details::traits<T16>::type,typename trace_source_details::traits<T17>::type,typename trace_source_details::traits<T18>::type,typename trace_source_details::traits<T19>::type,typename trace_source_details::traits<T20>::type,typename trace_source_details::traits<T21>::type> base_type;
    typedef trace_source_details::description description;
    
    static unsigned const number_of_args = 22;
    typedef T0    arg0_type;
    typedef T1    arg1_type;
    typedef T2    arg2_type;
    typedef T3    arg3_type;
    typedef T4    arg4_type;
    typedef T5    arg5_type;
    typedef T6    arg6_type;
    typedef T7    arg7_type;
    typedef T8    arg8_type;
    typedef T9    arg9_type;
    typedef T10    arg10_type;
    typedef T11    arg11_type;
    typedef T12    arg12_type;
    typedef T13    arg13_type;
    typedef T14    arg14_type;
    typedef T15    arg15_type;
    typedef T16    arg16_type;
    typedef T17    arg17_type;
    typedef T18    arg18_type;
    typedef T19    arg19_type;
    typedef T20    arg20_type;
    typedef T21    arg21_type;


    void describe_fields( ... )
    {
        trace_source_details::error_wrong_number_of_fields_in_description<T0>::ok;
    }

    void setName( std::string const& name_ )
    {
        base_type::setName(dup(name_.c_str()));
    }
    
    void setDescription( std::string const& description_ )
    {
        base_type::setDescription(dup(description_.c_str()));
    }

    void describe_fields(
        std::string const&       field_name0_,
        description const&       field_description0_,
        std::string const&       field_name1_,
        description const&       field_description1_,
        std::string const&       field_name2_,
        description const&       field_description2_,
        std::string const&       field_name3_,
        description const&       field_description3_,
        std::string const&       field_name4_,
        description const&       field_description4_,
        std::string const&       field_name5_,
        description const&       field_description5_,
        std::string const&       field_name6_,
        description const&       field_description6_,
        std::string const&       field_name7_,
        description const&       field_description7_,
        std::string const&       field_name8_,
        description const&       field_description8_,
        std::string const&       field_name9_,
        description const&       field_description9_,
        std::string const&       field_name10_,
        description const&       field_description10_,
        std::string const&       field_name11_,
        description const&       field_description11_,
        std::string const&       field_name12_,
        description const&       field_description12_,
        std::string const&       field_name13_,
        description const&       field_description13_,
        std::string const&       field_name14_,
        description const&       field_description14_,
        std::string const&       field_name15_,
        description const&       field_description15_,
        std::string const&       field_name16_,
        description const&       field_description16_,
        std::string const&       field_name17_,
        description const&       field_description17_,
        std::string const&       field_name18_,
        description const&       field_description18_,
        std::string const&       field_name19_,
        description const&       field_description19_,
        std::string const&       field_name20_,
        description const&       field_description20_,
        std::string const&       field_name21_,
        description const&       field_description21_
        )
    {
        
        add_field( this, field_name0_,
                   enhance_trace_description(field_description0_, (arg0_type*)0),
                   ::trace_source_details::traits<arg0_type>::type_spec,
                   ::trace_source_details::traits<arg0_type>::size,
                   ::trace_source_details::traits<arg0_type>::max_size );
        add_field( this, field_name1_,
                   enhance_trace_description(field_description1_, (arg1_type*)0),
                   ::trace_source_details::traits<arg1_type>::type_spec,
                   ::trace_source_details::traits<arg1_type>::size,
                   ::trace_source_details::traits<arg1_type>::max_size );
        add_field( this, field_name2_,
                   enhance_trace_description(field_description2_, (arg2_type*)0),
                   ::trace_source_details::traits<arg2_type>::type_spec,
                   ::trace_source_details::traits<arg2_type>::size,
                   ::trace_source_details::traits<arg2_type>::max_size );
        add_field( this, field_name3_,
                   enhance_trace_description(field_description3_, (arg3_type*)0),
                   ::trace_source_details::traits<arg3_type>::type_spec,
                   ::trace_source_details::traits<arg3_type>::size,
                   ::trace_source_details::traits<arg3_type>::max_size );
        add_field( this, field_name4_,
                   enhance_trace_description(field_description4_, (arg4_type*)0),
                   ::trace_source_details::traits<arg4_type>::type_spec,
                   ::trace_source_details::traits<arg4_type>::size,
                   ::trace_source_details::traits<arg4_type>::max_size );
        add_field( this, field_name5_,
                   enhance_trace_description(field_description5_, (arg5_type*)0),
                   ::trace_source_details::traits<arg5_type>::type_spec,
                   ::trace_source_details::traits<arg5_type>::size,
                   ::trace_source_details::traits<arg5_type>::max_size );
        add_field( this, field_name6_,
                   enhance_trace_description(field_description6_, (arg6_type*)0),
                   ::trace_source_details::traits<arg6_type>::type_spec,
                   ::trace_source_details::traits<arg6_type>::size,
                   ::trace_source_details::traits<arg6_type>::max_size );
        add_field( this, field_name7_,
                   enhance_trace_description(field_description7_, (arg7_type*)0),
                   ::trace_source_details::traits<arg7_type>::type_spec,
                   ::trace_source_details::traits<arg7_type>::size,
                   ::trace_source_details::traits<arg7_type>::max_size );
        add_field( this, field_name8_,
                   enhance_trace_description(field_description8_, (arg8_type*)0),
                   ::trace_source_details::traits<arg8_type>::type_spec,
                   ::trace_source_details::traits<arg8_type>::size,
                   ::trace_source_details::traits<arg8_type>::max_size );
        add_field( this, field_name9_,
                   enhance_trace_description(field_description9_, (arg9_type*)0),
                   ::trace_source_details::traits<arg9_type>::type_spec,
                   ::trace_source_details::traits<arg9_type>::size,
                   ::trace_source_details::traits<arg9_type>::max_size );
        add_field( this, field_name10_,
                   enhance_trace_description(field_description10_, (arg10_type*)0),
                   ::trace_source_details::traits<arg10_type>::type_spec,
                   ::trace_source_details::traits<arg10_type>::size,
                   ::trace_source_details::traits<arg10_type>::max_size );
        add_field( this, field_name11_,
                   enhance_trace_description(field_description11_, (arg11_type*)0),
                   ::trace_source_details::traits<arg11_type>::type_spec,
                   ::trace_source_details::traits<arg11_type>::size,
                   ::trace_source_details::traits<arg11_type>::max_size );
        add_field( this, field_name12_,
                   enhance_trace_description(field_description12_, (arg12_type*)0),
                   ::trace_source_details::traits<arg12_type>::type_spec,
                   ::trace_source_details::traits<arg12_type>::size,
                   ::trace_source_details::traits<arg12_type>::max_size );
        add_field( this, field_name13_,
                   enhance_trace_description(field_description13_, (arg13_type*)0),
                   ::trace_source_details::traits<arg13_type>::type_spec,
                   ::trace_source_details::traits<arg13_type>::size,
                   ::trace_source_details::traits<arg13_type>::max_size );
        add_field( this, field_name14_,
                   enhance_trace_description(field_description14_, (arg14_type*)0),
                   ::trace_source_details::traits<arg14_type>::type_spec,
                   ::trace_source_details::traits<arg14_type>::size,
                   ::trace_source_details::traits<arg14_type>::max_size );
        add_field( this, field_name15_,
                   enhance_trace_description(field_description15_, (arg15_type*)0),
                   ::trace_source_details::traits<arg15_type>::type_spec,
                   ::trace_source_details::traits<arg15_type>::size,
                   ::trace_source_details::traits<arg15_type>::max_size );
        add_field( this, field_name16_,
                   enhance_trace_description(field_description16_, (arg16_type*)0),
                   ::trace_source_details::traits<arg16_type>::type_spec,
                   ::trace_source_details::traits<arg16_type>::size,
                   ::trace_source_details::traits<arg16_type>::max_size );
        add_field( this, field_name17_,
                   enhance_trace_description(field_description17_, (arg17_type*)0),
                   ::trace_source_details::traits<arg17_type>::type_spec,
                   ::trace_source_details::traits<arg17_type>::size,
                   ::trace_source_details::traits<arg17_type>::max_size );
        add_field( this, field_name18_,
                   enhance_trace_description(field_description18_, (arg18_type*)0),
                   ::trace_source_details::traits<arg18_type>::type_spec,
                   ::trace_source_details::traits<arg18_type>::size,
                   ::trace_source_details::traits<arg18_type>::max_size );
        add_field( this, field_name19_,
                   enhance_trace_description(field_description19_, (arg19_type*)0),
                   ::trace_source_details::traits<arg19_type>::type_spec,
                   ::trace_source_details::traits<arg19_type>::size,
                   ::trace_source_details::traits<arg19_type>::max_size );
        add_field( this, field_name20_,
                   enhance_trace_description(field_description20_, (arg20_type*)0),
                   ::trace_source_details::traits<arg20_type>::type_spec,
                   ::trace_source_details::traits<arg20_type>::size,
                   ::trace_source_details::traits<arg20_type>::max_size );
        add_field( this, field_name21_,
                   enhance_trace_description(field_description21_, (arg21_type*)0),
                   ::trace_source_details::traits<arg21_type>::type_spec,
                   ::trace_source_details::traits<arg21_type>::size,
                   ::trace_source_details::traits<arg21_type>::max_size );
    }

    void operator()( arg0_type t0, arg1_type t1, arg2_type t2, arg3_type t3, arg4_type t4, arg5_type t5, arg6_type t6, arg7_type t7, arg8_type t8, arg9_type t9, arg10_type t10, arg11_type t11, arg12_type t12, arg13_type t13, arg14_type t14, arg15_type t15, arg16_type t16, arg17_type t17, arg18_type t18, arg19_type t19, arg20_type t20, arg21_type t21 )
    {
        this->fire( ::trace_source_details::traits<arg0_type>::convert_for_trace(t0), ::trace_source_details::traits<arg1_type>::convert_for_trace(t1), ::trace_source_details::traits<arg2_type>::convert_for_trace(t2), ::trace_source_details::traits<arg3_type>::convert_for_trace(t3), ::trace_source_details::traits<arg4_type>::convert_for_trace(t4), ::trace_source_details::traits<arg5_type>::convert_for_trace(t5), ::trace_source_details::traits<arg6_type>::convert_for_trace(t6), ::trace_source_details::traits<arg7_type>::convert_for_trace(t7), ::trace_source_details::traits<arg8_type>::convert_for_trace(t8), ::trace_source_details::traits<arg9_type>::convert_for_trace(t9), ::trace_source_details::traits<arg10_type>::convert_for_trace(t10), ::trace_source_details::traits<arg11_type>::convert_for_trace(t11), ::trace_source_details::traits<arg12_type>::convert_for_trace(t12), ::trace_source_details::traits<arg13_type>::convert_for_trace(t13), ::trace_source_details::traits<arg14_type>::convert_for_trace(t14), ::trace_source_details::traits<arg15_type>::convert_for_trace(t15), ::trace_source_details::traits<arg16_type>::convert_for_trace(t16), ::trace_source_details::traits<arg17_type>::convert_for_trace(t17), ::trace_source_details::traits<arg18_type>::convert_for_trace(t18), ::trace_source_details::traits<arg19_type>::convert_for_trace(t19), ::trace_source_details::traits<arg20_type>::convert_for_trace(t20), ::trace_source_details::traits<arg21_type>::convert_for_trace(t21) );
    }

};

    
#endif // SGCOMPONENTTRACEHELPER_H

