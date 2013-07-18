/*!
 *  \file   CAInterface.h
 *  \brief  Definition of the abstract CAInterface class.
 *  \date   Copyright (c) 2006-2009 ARM. All Rights Reserved.
 *          Release 2.0.0
 */

#ifndef CAInterface_h
# define CAInterface_h

#include "eslapi_stdint.h"

# ifdef ESLAPI_WEXP
#  undef ESLAPI_WEXP
# endif

# ifdef WIN32
#  ifdef EXPORT_ESLAPI
#   define ESLAPI_WEXP    __declspec(dllexport)
#  elif !defined(NO_IMPORT_ESLAPI)
#   define ESLAPI_WEXP    __declspec(dllimport)
#  else
#   define ESLAPI_WEXP
#  endif
# else
#  define ESLAPI_WEXP
# endif


namespace eslapi
{
    /// Interface names are implemented as C-string constants.
    typedef char const * if_name_t;

    /// Interface minor revision numbers are 32-bit unsigned ints.
    typedef uint32_t if_rev_t;

    /// Base class for extensible component interfaces.
    ///
    /// CAInterface provides a basis for a software model built around
    /// 'components' and 'interfaces'.
    ///
    /// An 'interface' is an abstract class (consisting entirely of
    /// pure virtual methods), which derives from CAInterface, and
    /// which provides a number of methods for interacting with a
    /// component.  
    ///
    /// A 'component' is a black-box entity that has a unique identity.
    /// A component provides concrete implementations of one or more
    /// interfaces.  Each of these interfaces may expose different facets
    /// of the component's behaviour.  These interfaces are the only way
    /// to interact with the component.
    ///
    /// There is no way for a client to enumerate the set of interfaces 
    /// that a component implements; instead, the client must ask for 
    /// specific interfaces by name.  If the component doesn't implement
    /// the requested interface, it returns a NULL pointer.
    ///
    /// (The implementation of a component's interfaces may be provided by
    /// one or several interacting C++ objects; this is an impementation
    /// detail that is transparent to the client).
    ///
    /// Interfaces are identified by a string name (of type if_name_t), and
    /// an integer revision (type if_rev_t).  A higher revision number
    /// indicates a newer revision of the same interface.
    ///
    /// class CAInterface is the base class for all interfaces.  It defines
    /// a method, CAInterface::ObtainInterface(), that allows a client
    /// to obtain a reference to any of the interfaces that the component
    /// implements.
    ///
    /// The client specifies the id and revision of the interface that it
    /// wants to request.  The component can return NULL if it doesn't
    /// implement that interface, or only implements a lower revision.
    ///
    /// Since each interface derives from CAInterface, a client can call
    /// ObtainInterface() on any one interface pointer to obtain a pointer
    /// to any other interface implemented by the same component.
    ///
    /// The following rules govern the use of components and interfaces.
    ///
    /// * Each component is distinct.  No two components can return
    ///   the same pointer for a given interface.  An ObtainInterface()
    ///   call on one component must not return an interface on a
    ///   different component.
    ///
    /// * Each interface consists of a name, a revision number, and a
    ///   C++ abstract class definition.  The return value of 
    ///   ObtainInterface() is either NULL, or is a pointer that can be
    ///   cast to the class type.
    ///
    /// * Where two interfaces have the same if_name_t, the newer revision
    ///   of the interface must be backwards-compatible with the
    ///   old revision.  (This includes the binary layout of any
    ///   data-structures that it uses, and the semantics of any methods).
    ///
    /// * During the lifetime of a component, any calls to ObtainInterface()
    ///   for a given interface name and revision must always return the
    ///   same pointer value.  It must not matter which of the component's
    ///   interfaces is used to invoke ObtainInterface().
    //
    /// * All components must implement the interface named 
    ///   'eslapi::CAInterface' revision 0, which implements class
    ///   eslapi::CAInterface.

    class ESLAPI_WEXP CAInterface
    {
    public:
        /// Static helper method to return the interface name for the 
        /// CAInterface.
        static if_name_t IFNAME() { return "eslapi.CAInterface"; }

        /// Static helper method to return the current interface revision 
        /// for CAInterface.
        static if_rev_t IFREVISION() { return 0; }

        // C++ wants an implementation for all destructors
        virtual ~CAInterface ()
        {}

    public:

        /// Ask the component for a handle to a different interface, if
        /// the component implements that interface.  The return value
        /// is NULL if the component doesn't implement the specified
        /// interface; otherwise it is a pointer to an instance of
        /// CAInterface that can be cast to the appropriate interface type.
        ///
        /// @param[in]  ifName      Name identifying the requested interface.
        /// @param[in]  minRev      Specify the minimum minor revision required.
        /// @param[out] actualRev   If not NULL, used to returns the actual
        ///                         revision number implemented.
        /// @return                 Pointer to the requested interface, or NULL.
        virtual CAInterface * ObtainInterface(
                                if_name_t    ifName,
                                if_rev_t     minRev,
                                if_rev_t *   actualRev) = 0;

        /// Helper method to make it easier to get an interface pointer.
        ///
        /// This returns a pointer of type TARGET_IF*, obtained by
        /// calling ObtainInterface() on this component.  If this
        /// component doesn't provide a compatible version of the
        /// desired interface, it returns a NULL pointer.
        ///
        /// The desired interface and version must be specified within
        /// the TARGET_IF class definition by static helper methods
        /// IFNAME() and IFREVISION() -- following the examples provided
        /// above.
        ///
        /// This method is not technically part of the interface (ABI)
        /// exposed by a component; it is just defined here to make it
        /// easier to use the interface from C++ code.
        template <class TARGET_IF>
        TARGET_IF * ObtainPointer()
        {
            CAInterface *tgt = ObtainInterface(TARGET_IF::IFNAME(),
                                               TARGET_IF::IFREVISION(),
                                               0);
            return static_cast<TARGET_IF*>(tgt);
        }

    };

} // namespace eslapi

#endif // #ifndef CAInterface_h

// end of file CAInterface.h
