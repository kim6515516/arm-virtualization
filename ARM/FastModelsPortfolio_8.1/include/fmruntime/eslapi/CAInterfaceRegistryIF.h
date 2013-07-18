/*!
 *  \file   CAInterfaceRegistryIF.h
 *  \brief  Interface published by CAInterfaceRegistry
 *  \date   Copyright (c) 2011 ARM. All Rights Reserved.
 *          Release 2.0.0
 */

#ifndef CAInterfaceRegistryIF_h
#define CAInterfaceRegistryIF_h

#include "eslapi/CAInterface.h"

namespace eslapi
{
    /// Declaration of CAInterface-compatible API used by CAInterfaceRegistry
    /// to allow public inspection and configuration of the interfaces
    /// published by a component.
    class ESLAPI_WEXP CAInterfaceRegistryIF : public CAInterface
    {
    public:
        /// Static helper method to return the interface name for the 
        /// CAInterfaceRegistry.
        static if_name_t IFNAME() { return "eslapi.CAInterfaceRegistry"; }

        /// Static helper method to return the current interface revision 
        /// for CAInterfaceRegistry.
        static if_rev_t IFREVISION() { return 0; }

        /// Register a new interface.
        ///
        /// @param[in]  ifName      Name of interface.
        /// @param[in]  ifRev       Highest interface revison implemented by ifPtr.
        /// @param[in]  ifPtr       Pointer to the interface which is to registered. This will be returned by ObtainInterface().
        virtual void RegisterInterface(
                                if_name_t    ifName,
                                if_rev_t     ifRev,
                                CAInterface *ifPtr) = 0;

        /// Unregister a previously registered interface.
        /// (it is generally not needed to remove interfaces upon destruction)
        ///
        /// @param[in]  ifName      Name of interface.
        virtual void UnregisterInterface(if_name_t ifName) = 0;

        /// Visitor callback interface to allow the list of interfaces to be
        /// inspected.
        class InterfaceListVisitor {
        public:
            virtual ~InterfaceListVisitor() {}
            virtual void VisitInterface(if_name_t ifName, if_rev_t ifRev) = 0;
        };

        /// Query list of all supported interfaces.
        ///
        /// @param  Visitor An instance of InterfaceListVisitor, which will receive the details of each interface.
        virtual void VisitInterfaceList(InterfaceListVisitor *visitor) const = 0;

        /// Get component id.
        ///
        /// @return           Get component id. The contents of this string identifies the component (and the registry) uniquely in a system.
        virtual const char * GetComponentId() const = 0;
    };
} // namespace eslapi

#endif
