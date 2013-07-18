/*!
 * \file    PVBitField.h
 * \brief   Helper class for creating bit field
 * \date    Copyright 2010 ARM Limited. All rights reserved.
 *
 * These classes and methods are private, subject to change and should not be
 * used outside of ARM.
 */

#ifndef PVBITFIELD_H
#define PVBITFIELD_H

namespace pv
{
    ///
    /// Internal details.
    ///
    namespace details
    {
        // The NullField is used internally to represent a field that can be in
        // any bitfield.
        struct NullField
        {
            typedef NullField             bitfield_type;
            static unsigned const         max_msb = 0;
            static unsigned const         msb     = 0;
            static unsigned const         min_lsb = 0;
            static unsigned const         lsb     = 0;
            static unsigned char const    mask    = 0;
        };

        template< bool COND > struct BitPositionsWellFormed
        {
            typedef int msb_is_representable;
            typedef int lsb_is_less_than_msb;
        };

        template<> struct BitPositionsWellFormed<false>
        {
        };

        template< typename T0, typename T1 >
        struct AllFieldsBelongToSameBitfield  {};

        template< typename T >
        struct AllFieldsBelongToSameBitfield<T,T>
        {
            typedef int field_comes_from_bitfield;
        };

        template< typename T >
        struct AllFieldsBelongToSameBitfield<T,NullField>
        {
            typedef int field_comes_from_bitfield;
        };

        // T0 and T1 are expected to be of type Field or Fields
        template< typename T0, typename T1 >
        struct BitFieldWellConstructed
        {
            typedef typename AllFieldsBelongToSameBitfield<
                typename T0::bitfield_type,
                typename T1::bitfield_type
                >::field_comes_from_bitfield well_constructed;

            typedef typename BitPositionsWellFormed<
                T0::msb <= T0::max_msb
                           >::msb_is_representable msb_is_representable;

            typedef typename BitPositionsWellFormed<
                T0::lsb <= T0::msb
                           >::lsb_is_less_than_msb lsb_is_less_than_msb;
        };

        // T0 and T1 are expected to be of type Field or Fields
        template< typename BITFIELD_TYPE, typename T1 >
        struct BitFieldWellConstructed2
        {
            typedef typename AllFieldsBelongToSameBitfield<
                BITFIELD_TYPE,
                typename T1::bitfield_type
                >::field_comes_from_bitfield field_comes_from_bitfield;
        };
    }

    template< typename BITFIELD_TYPE, unsigned MSB, unsigned LSB > struct Field;

    ///
    /// \define ARM_DEFINE_BITFIELD Define a bit field of name BITFIELD_NAME
    ///
    /// Introduces the symbol BITFIELD_NAME into the current namespace.  This is
    /// a class that can be inherited from if you wish.
    ///
#define ARM_DEFINE_BITFIELD(BITFIELD_NAME, REPRESENTATION_TYPE)         \
    struct BITFIELD_NAME : ::pv::BitField<BITFIELD_NAME, REPRESENTATION_TYPE> \
    {                                                                   \
        BITFIELD_NAME(REPRESENTATION_TYPE rep_ = 0)                     \
            : ::pv::BitField<BITFIELD_NAME, REPRESENTATION_TYPE>(rep_)  \
        {                                                               \
        }                                                               \
        static char const* name() { return #BITFIELD_NAME; }            \
    };

    ///
    /// \define ARM_DEFINE_BITFIELD_ENTRY Define a range of bits [\a MSB : \a
    /// LSB] in \a BITFIELD_TYPE that you wish to name \a NAME.
    ///
    /// Introduces \a NAME into the current namespace.
    ///
    /// You can create a bitfield where the bitfield names are scoped as
    /// follows:
    /// \code
    ///     struct MyBitFieldName : ::pv::Field<MyBitFieldName, uint32_t>
    ///     {
    ///         ARM_DEFINE_BITFIELD_ENTRY( MyBitFieldName, A, ... );
    ///         ARM_DEFINE_BITFIELD_ENTRY( MyBitFieldName, B, ... );
    ///         ARM_DEFINE_BITFIELD_ENTRY( MyBitFieldName, C, ... );
    ///         ARM_DEFINE_BITFIELD_ENTRY( MyBitFieldName, D, ... );
    ///     };
    ///
    ///     // Field names now have to be scoped:
    ///     f.get< MyBitFieldName::A >()
    ///     pv::Fields< MyBitFieldName::A, MyBitFieldName::B >::set( f, ... );
    ///
    ///     //You are perfect entitled to put them in a separate namespace:
    ///     namespace F
    ///     {
    ///         ARM_DEFINE_BITFIELD_ENTRY( MyBitFieldName, A, ... );
    ///     }
    /// \endcode
    ///
    /// \note It is perfectly acceptable to define overlapping bitfields.
    /// Indeed this is commonly something that one wishes to do for efficiency
    /// and conciseness that C-bit fields don't allow you to do unless you using
    /// unions, etc.
    ///
#define ARM_DEFINE_BITFIELD_ENTRY(BITFIELD_TYPE, NAME, MSB, LSB)        \
    struct NAME : ::pv::Field<BITFIELD_TYPE, MSB, LSB >                 \
    {                                                                   \
        static char const* name()          { return #NAME;          }   \
    };

    ///
    /// A Field represents a single field in a BitField.  Usually you would not
    /// use this directly but use the field name defined by DEFINE_BITFIELD_ENTRY.
    ///
    /// It can be used as a template parameter to BitField::get<>() or
    /// BitField::set<>().  It can be combined together using Fields<>.
    ///
    /// NOTE that accessing a field will always deliver it shifted down to bit
    /// pos 0.
    ///
    template<
        typename        BITFIELD_TYPE,
        unsigned        MSB,
        unsigned        LSB
        >
    struct Field
    {
        // NOTE that we unwrap the actual BITFIELD_TYPE to the BitField<Tag,Rep> level
        // so that conversion between elements work correctly.
        typedef typename BITFIELD_TYPE::bitfield                  bitfield_type;
        typedef typename bitfield_type::representation_type       representation_type;
        static unsigned const                                     max_msb = bitfield_type::max_msb;
        static unsigned const                                     min_lsb = bitfield_type::min_lsb;
        static unsigned const                                     msb = MSB;
        static unsigned const                                     lsb = LSB;
        static representation_type const                          mask =
            ((msb == max_msb
              ? representation_type(~representation_type(0))
              /* peculiar shift form to suppress warning if end_pos == sizeof(representation_type)*8 */
              : representation_type( ((representation_type(1) << msb) << 1) - 1 )
                )
             & ~((representation_type(1) << lsb) - 1)
                );

        /// Return this field of \a a_ right-shifted to bit position 0.
        static representation_type get(bitfield_type a_)
        {
            return (a_.rep & mask) >> lsb;
        }

        /// Return all other fields but this field, this is always unshifted.
        static representation_type get_other_than( bitfield_type a_ )
        {
            return a_.rep & ~mask;
        }

        static bitfield_type& set(bitfield_type& a_, representation_type rep_)
        {
            a_.rep = (a_.rep & ~mask) | ((rep_ << lsb) & mask);
            return a_;
        }

        /// \name Assertions Assertions for well-formedness
        ///
        /// All the fields specified must be tagged to be of the same bitfield.
        //@{
        typedef typename details::BitFieldWellConstructed<Field,Field>::well_constructed well_constructed;;
        //@}
    };

    ///
    /// Fields allow you to access a group of fields simultaneously, all results
    /// obtained using this interface are _not_ shifted to bit pos 0.
    ///
    /// You can combine Fields, or Field's.
    ///
    /// You can use Fields in the following way:
    /// \code
    ///      Fields< my_field0, my_field1 >::get(f)
    /// \endcode
    /// or you can name a set of fields future reference:
    /// \code
    ///      typedef Fields<my_field0, my_field1>   fields01;
    ///      fields01::get(f)
    /// \endcode
    ///
    template< typename b0,
              typename b1 = details::NullField,
              typename b2 = details::NullField,
              typename b3 = details::NullField,
              typename b4 = details::NullField,
              typename b5 = details::NullField,
              typename b6 = details::NullField,
              typename b7 = details::NullField >
    struct Fields
    {
        typedef typename b0::bitfield_type                   bitfield_type;
        typedef typename bitfield_type::representation_type  representation_type;
        static unsigned const                                msb = bitfield_type::max_msb;
        static unsigned const                                lsb = bitfield_type::min_lsb;

        // m is the mask
        static representation_type const mask =
            b0::mask | b1::mask | b2::mask | b3::mask
            | b4::mask | b5::mask | b6::mask | b7::mask
            ;


        static bool eq(bitfield_type a_, bitfield_type b_) {return get(a_) == get(b_);}
        static bool ne(bitfield_type a_, bitfield_type b_) {return get(a_) != get(b_);}
        static bool lt(bitfield_type a_, bitfield_type b_) {return get(a_) <  get(b_);}

        /// This is the preferred method to deal with a bitfield when
        /// dealing with multiple fields.
        static representation_type get( bitfield_type a_ )
        {
            return a_.rep & mask;
        }

        /// This is the preferred method to deal with a bitfield when
        /// dealing with multiple fields.
        static representation_type get_other_than( bitfield_type a_ )
        {
            return a_.rep & ~mask;
        }

        /// This is the preferred method to deal with a bitfield when
        /// dealing with multiple fields.
        static void set( bitfield_type& a_, representation_type rep_ )
        {
            a_.rep = (a_.rep & ~mask) | (rep_ & mask);
        }

        /// \name Assertions Assertions for well-formedness
        ///
        /// All the fields specified must be tagged to be of the same bitfield.
        //@{
        typedef typename details::BitFieldWellConstructed<b0,b1>::well_constructed b1_and_b0_belong_to_same_bitfield;
        typedef typename details::BitFieldWellConstructed<b0,b2>::well_constructed b2_and_b0_belong_to_same_bitfield;
        typedef typename details::BitFieldWellConstructed<b0,b3>::well_constructed b3_and_b0_belong_to_same_bitfield;
        typedef typename details::BitFieldWellConstructed<b0,b4>::well_constructed b4_and_b0_belong_to_same_bitfield;
        typedef typename details::BitFieldWellConstructed<b0,b5>::well_constructed b5_and_b0_belong_to_same_bitfield;
        typedef typename details::BitFieldWellConstructed<b0,b6>::well_constructed b6_and_b0_belong_to_same_bitfield;
        typedef typename details::BitFieldWellConstructed<b0,b7>::well_constructed b7_and_b0_belong_to_same_bitfield;
        //@}
    };



    template< typename BITFIELD_TAG,
              typename REPRESENTATION_TYPE >
    struct BitField
    {
        typedef BitField                  bitfield;
        typedef BITFIELD_TAG              bitfield_tag;
        typedef REPRESENTATION_TYPE       representation_type;
        static unsigned const             max_msb = sizeof(representation_type) * 8 - 1;
        static unsigned const             min_lsb = 0;

        BitField(representation_type rep_) : rep(rep_) {}

        /// Publicly accessible representation of the bitfield.
        representation_type rep;

        /// Provide a preferred public accessor for the representation
        representation_type get_rep() const { return rep; }

        /// If T is a field name then this will give the right shifted field, if
        /// T is a Fields then this will not be shifted.
        template<typename T> inline representation_type get() const
        {
            return T::get( *this );
        }

        /// Get all fields other than those specified by T, which can be of type
        /// Field or Fields, this is always unshifted
        template<typename T> inline representation_type get_other_than() const
        {
            return T::get_other_than( *this );
        }

        /// If T is a field name then this will give the right shifted field, if
        /// T is a Fields then this will not be shifted.
        template<typename T> inline BitField& set(
            representation_type rep_
            )
        {
            return T::set( *this, rep_ );
        }

        bool operator == (BitField o_) const { return rep == o_.rep; }
        bool operator != (BitField o_) const { return rep != o_.rep; }
        bool operator <  (BitField o_) const { return rep <  o_.rep; }

        ///
        /// Sometimes it is easier to get access to Fields through this class
        /// itself.
        ///
        template< typename b0,
                  typename b1 = details::NullField,
                  typename b2 = details::NullField,
                  typename b3 = details::NullField,
                  typename b4 = details::NullField,
                  typename b5 = details::NullField,
                  typename b6 = details::NullField,
                  typename b7 = details::NullField >
        struct Fields : ::pv::Fields<b0,b1,b2,b3,b4,b5,b6,b7> {
            // Check that b0 talks about this bitfield, pv::Fields will then
            // check that b0 and bN talk about the same bit field.
            typedef typename details::BitFieldWellConstructed2<bitfield, b0>::field_comes_from_bitfield field_comes_from_bitfield;
        };
    };

}



#endif
