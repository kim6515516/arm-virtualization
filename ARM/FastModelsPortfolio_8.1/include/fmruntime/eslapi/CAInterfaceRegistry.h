/*!
 *  \file   CAInterfaceRegistry.h
 *  \brief  Helper class: Helps to implement ObtainInterface() consistently in all interfaces of a component.
 *  \date   Copyright (c) 2011 ARM. All Rights Reserved.
 *          Release 2.0.0
 */

#ifndef CAInterfaceRegistry_h
# define CAInterfaceRegistry_h

#include "eslapi/CAInterface.h"
#include "eslapi/CAInterfaceRegistryIF.h"
#include <map>
#include <vector>
#include <string>


namespace eslapi
{
    /// Helper class CAInterfaceRegistry: 
    /// Helps to implement ObtainInterface() consistently in all interfaces of a component.
    /// CAInterfaceRegistry represents the collection of all interfaces of a component.
    /// 
    /// Example on how to use the CAInterfaceRegistry class:
    /// 
    /// class MyClass
    ///     : private CADI, OtherInterface  
    /// {
    ///      YetAnotherInterface *yet_another;
    /// 
    ///      /*! Instantiate a registry to handle our CAInterface requirements. */
    ///      CAInterfaceRegistry registry;
    /// 
    ///      /*! Delegate our implementation of ObtainInterface to the registry. */
    ///      CAInterface* ObtainInterface(i,m,*a) { return registry.ObtainInterface(i,m,a); }
    /// 
    ///    public:
    ///      MyClass() : registry("unique-name") {
    ///         // At startup, tell the registry about the interfaces we support
    ///         registry.RegisterInterface(CADI::IFNAME(),CADI::IFREVISION(), static_cast<CADI*>(this));
    ///         registry.RegisterInterface(..,..,static_cast<OtherInterface*>(this));
    ///         registry.RegisterInterface(YetAnotherInterface::IFNAME(), YetAnotherInterface::IFREVISION(), yet_another);
    ///      }
    ///   };
    class CAInterfaceRegistry : public CAInterfaceRegistryIF
    {
    public:
        /// Constructor
        /// Always add CAInterface and CAInterfaceRegistry which we always support.
        /// 
        /// @param[in]  componentId      String which ideally uniquely identifies the component in a system.
        /// @param[in]  publish_cainterfaceregistryif  True (by default) if the registry should publish (via ObtainInterface) that it implements CAInterfaceRegistryIF.
        CAInterfaceRegistry(const std::string &componentId_,
                            bool publish_cainterfaceregistryif_ = true)
            : componentId(componentId_)
        {
            RegisterInterface(CAInterface::IFNAME(), CAInterface::IFREVISION(), this);
            if (publish_cainterfaceregistryif_) {
                RegisterInterface(CAInterfaceRegistry::IFNAME(), CAInterfaceRegistry::IFREVISION(), this);
            }
        }

public: // Implement CAInterface

        /// All ObtainInterface() implementations of a component should forward their 
        /// ObtainInterface() requests to this function.
        /// 
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
                                if_rev_t *   actualRev)
        {
            // ignore interfaces without names
            if ((ifName == 0) || (ifName[0] == 0))
                return 0;
            
            // check for interface with ifName
            CAInterfaceMap::const_iterator i = caInterfaceMap.find(ifName);
            if (i == caInterfaceMap.end())
                return 0;  // no interface for this ifName
            
            // check interface revision
            if (i->second.ifRev < minRev)
                return 0;  // no interface with at least revision minRev available

            // return actual revision
            if (actualRev)
                *actualRev = i->second.ifRev;
            
            // return interface
            return i->second.ifPtr;
        }
        
public: // Implement CAInterfaceRegistryIF

        /// Register a new interface.
        ///
        /// @param[in]  ifName      Name of interface.
        /// @param[in]  ifRev       Highest interface revison implemented by ifPtr.
        /// @param[in]  ifPtr       Pointer to the interface which is to registered. This will be returned by ObtainInterface().
        virtual void RegisterInterface(
                                if_name_t    ifName,
                                if_rev_t     ifRev,
                                CAInterface *ifPtr)
        {
            // ignore NULL interfaces and ignore interfaces without names
            if ((ifPtr == 0) || (ifName == 0) || (ifName[0] == 0))
                return;
            
            // check whether an interface with a higher ifRev is already registered (if so ignore)
            CAInterfaceMap::const_iterator i = caInterfaceMap.find(ifName);            
            if ((i != caInterfaceMap.end()) && (i->second.ifRev > ifRev))
                return;
            
            // add/overwrite interface
            caInterfaceMap[ifName] = CAInterfaceInfoInternal(ifName, ifRev, ifPtr);
        }
        
        /// Unregister a previously registered interface.
        /// (it is generally not needed to remove interfaces upon destruction)
        ///
        /// @param[in]  ifName      Name of interface.
        virtual void UnregisterInterface(if_name_t ifName)
        {
            caInterfaceMap.erase(ifName);
        }

        /// Query list of all supported interfaces.
        ///
        /// @return           Vector of CAInterfaceInfo elements (list of supported interfaces).
        virtual void VisitInterfaceList(InterfaceListVisitor *visitor) const
        {
            for (CAInterfaceMap::const_iterator i = caInterfaceMap.begin(); i != caInterfaceMap.end(); i++) {
                visitor->VisitInterface(i->second.ifName.c_str(),
                                        i->second.ifRev);
            }
        }
        
        /// Get component id.
        ///
        /// @return           Get component id. This string identifies the component (and the registry) uniquely in a system.
        virtual const char * GetComponentId() const
        { 
            return componentId.c_str();
        }

    protected:
        // private data
        struct CAInterfaceInfoInternal
        {
            CAInterfaceInfoInternal(const char *ifName_, if_rev_t ifRev_, CAInterface *ifPtr_):
            ifName(ifName_), ifRev(ifRev_), ifPtr(ifPtr_) {}
            CAInterfaceInfoInternal(): ifRev(0), ifPtr(0) {}
            
            std::string ifName;
            if_rev_t ifRev;
            CAInterface *ifPtr;
        };
        typedef std::map<std::string, CAInterfaceInfoInternal> CAInterfaceMap;
        CAInterfaceMap caInterfaceMap;
        std::string componentId;
    };

} // namespace eslapi

#endif // #ifndef CAInterfaceRegistry_h

// end of file CAInterfaceRegistry.h
