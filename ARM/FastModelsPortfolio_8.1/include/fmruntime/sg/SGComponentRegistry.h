/*!
 * \file    SGComponentRegistry.h
 * \brief   Abstract interface which represents a collection of components. Each component is represented by a CAInterface.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

#ifndef SGCOMPONENTREGISTRY_H
#define SGCOMPONENTREGISTRY_H

#include "eslapi/CAInterface.h"

// Note: The term 'component' is used here in the generic sense of an abstract building block of something else, not 
//       (just) as a 'system component' (modeling a piece of hardware).

/*! ComponentRegistry class:
 * Abstract interface which represents a collection of components. Each component is represented by a CAInterface.
 * Use cases:
 * - System components use this to get access to all global instances and global interfaces (scheduler, CADIServer, CADISimulation, ...).
 * - list of all system components in a platform (across all EVS instances in case of SystemC export)
 * A pointer to this interface is returned by sg::SimulationContext::getGlobalInterface().
 * 
 * Please see also SGSimulationContext.h.
 * 
 * Please consider using the 'obtainComponentInterface()' helper function to simplfy looking up aspecific interface of a specific component in one step.
 */
namespace sg
{    
    class ComponentRegistry: public eslapi::CAInterface
    {
    public:
        // CAInterface related stuff
        static eslapi::if_name_t IFNAME() { return "sg.ComponentRegistry"; }
        static eslapi::if_rev_t IFREVISION() { return 0; }
        virtual eslapi::CAInterface *ObtainInterface(eslapi::if_name_t ifName, eslapi::if_rev_t minRev, eslapi::if_rev_t *actualRev) = 0;
        
        // --- main interface ---
                
        /*! Retrieve component 'componentName'.
         * The following component names are used for components behind sg::SimulationContext::getGlobalInterface().
         * - scheduler: The global scheduler object. (Offered interfaces: SchedulerInterfaceForComponents, SchedulerControlInterface, SchedulerTestInterface.)
         * - cadiServer: The global CADIServer object. (Offered interface: to be defined.)
         * - cadiSimulation: The global CADISimulation object. (Offered interface: eslapi.CADISimulation2)
         * - mtiRegistry: The global SystemTraceInterface object. (Offered interface: SystemTraceInterface1)
         * - systemComponentRegistry: The global ComponentRegistry object which represents the list of all components in a system. (Offered interfaces: CADI, SCADI, trace, ...)
         * \param componentName Name of the component to look up. May be NULL.
         * 
         * \returns CAInterface of the requested component, or 0 if the component does not exist or if componentName was 0.
         */
        virtual eslapi::CAInterface* lookupComponent(const char *componentName) = 0;
        
        /*! Register new component into this registry.
         * If a component with that name was already registered the old component is replaced by the new component.
         */
        virtual void registerComponent(const char *componentName, eslapi::CAInterface *componentInterface) = 0;
        
        /*! Remove a component from the component registry.
         * If a component with that name does not exist this call is ignored.
         */
        virtual void unregisterComponent(const char *componentName) = 0;

        /*! Visitor callback interface to allow the list of components to be inspected.
         * See visitComponentList().
         */
        class ComponentListVisitor {
        public:
            virtual ~ComponentListVisitor() {}
            virtual void visitComponent(const char *componentName, CAInterface *componentInterface) = 0;
        };
        
        /*! Query list of all registered components.
         * Components are listed in no particular order.
         * \param visitor An instance of ComponentListVisitor, which will receive the details of each component.
         */
        virtual void visitComponentList(ComponentListVisitor *visitor) const = 0;

        /*! Hide registered component.
         * The component must have already been registered.
         * Hidden component are visible throu lookupComponent() (when their name is known) but not through visitComponentList().
         */
        virtual void hideComponent(const char *componentName) = 0;
    };
    
    /* Convenience function: Lookup a specific interface of a specific component.
     * \param componentRegistryInterface ComponentRegistry is expected to be in this instance.
     * \param componentName Name of the specified component
     * \param ifName Name of the specified interface
     * \param ifRev Requested minimum revision of the interface
     * \param actualRev Output parameter: Actual returned revision of the interface (may be NULL)
     * \param errorMessageOut Set to a string constant with the error message when returning 0 (not set otherwise). May be 0.
     * \returns CAInterface pointer. NULL if eiher the ComponentRegistry interface, the component or the specified interface cannot be found (or when the parameters were invalid or NULL).
     */
    eslapi::CAInterface *obtainComponentInterface(eslapi::CAInterface *componentRegistryInterface, const char *componentName, 
                                                  eslapi::if_name_t ifName, eslapi::if_rev_t minRev = 0, eslapi::if_rev_t *actualRev = 0,
                                                  const char **errorMessageOut = 0);

    /* Convenience template function: Lookup a specific interface of a specific component. 
     * Same as obtainComponentInterface() but the target type is specified as a template argument and has less args.
     * This behaves towards obtainComponentInterface() like eslapi::CAInterface::ObtainPointer<>() does towards eslapi::CAInterface::ObtainInterface().
     * \param componentRegistryInterface ComponentRegistry is expected to be in this instance.
     * \param componentName Name of the specified component
     * \param errorMessageOut Set to a string constant with the error message when returning 0 (not set otherwise). May be 0.
     * \returns Requested interface pointer of the specified type. NULL if eiher the ComponentRegistry interface, the component or the specified interface cannot be found (or when the parameters were invalid or NULL).
     */
    template <class TARGET_IF>
    TARGET_IF *obtainComponentInterfacePointer(eslapi::CAInterface *componentRegistryInterface, const char *componentName, const char **errorMessageOut = 0)
    {
        return static_cast<TARGET_IF*>(obtainComponentInterface(componentRegistryInterface, componentName,
                                                                TARGET_IF::IFNAME(), TARGET_IF::IFREVISION(), 0, errorMessageOut));
    }
}

#endif

