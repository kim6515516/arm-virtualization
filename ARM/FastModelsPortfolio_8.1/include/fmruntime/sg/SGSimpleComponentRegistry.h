/*!
 * \file    SGSimpleComponentRegistry.h
 * \brief   Straight forward implementation of the abstract sg::ComponentRegistry interface.
 * \date    Copyright 2011 ARM Limited. All rights reserved.
 *
 */

#ifndef SGSIMPLECOMPONENTREGISTRY_H
#define SGSIMPLECOMPONENTREGISTRY_H

#include <map>
#include <string>
#include "sg/SGComponentRegistry.h"

// Note: The term 'component' is used here in the generic sense of an abstract building block of something else, not 
//       (just) as a 'system component' (modeling a piece of hardware).

/*! SimpleComponentRegistry class:
 * This is a straight forward implementation of the sg::ComponentRegistry interface. See SGComponentRegistry.h for more info.
 */
namespace sg
{
    class SimpleComponentRegistry: public ComponentRegistry
    {
    public:
        /*! Constructor.
         * \param interfaceOwner Pointer to an instance which handles all ObtainInterface() calls for the enclosing component. 
         +                       Should be either set through this constructor or through setInterfaceOwner.
         */
        SimpleComponentRegistry(CAInterface *interfaceOwner_ = 0): interfaceOwner(interfaceOwner_) {}

        // CAInterface related stuff
        virtual eslapi::CAInterface *ObtainInterface(eslapi::if_name_t ifName, eslapi::if_rev_t minRev, eslapi::if_rev_t *actualRev);


        // SimpleComponentRegistry specific stuff:

        /*! Set instance which handles all ObtainInterface() calls for the enclosing component.
         * All ObtainInterface() calls are delegated to this instance.
         */
        void setInterfaceOwner(CAInterface *interfaceOwner_) { interfaceOwner = interfaceOwner_; }

        // ComponentRegistry implementation:
                
        /*! Retrieve component 'componentName'.
         * If componentName is 0 this call is ignored.
         * \returns CAInterface of the requested component, or 0 if the component does not exist.
         */
        virtual eslapi::CAInterface* lookupComponent(const char *componentName)
        {
            if (!componentName)
                return 0;
            ComponentMap::const_iterator i = componentMap.find(componentName);
            if (i == componentMap.end())
                return 0;
            return i->second.second;
        }
        
        /*! Register new component into this registry.
         * If a component with that name was already registered the old component is replaced by the new component.
         * If interface is 0 or if componentName is 0 this call is ignored.
         * \param componentName Instance name of the component (not the class/type/interface name).
         * \param componentInterface Interface entry point of the component. (All interfaces of that component are visible from all other interfaces of that component by definition.)
         */
        virtual void registerComponent(const char *componentName, eslapi::CAInterface *componentInterface)
        {
            if (!componentInterface)
                return;
            if (!componentName)
                return;
            componentMap[componentName] = std::make_pair(false, componentInterface); // add or change map entry
        }
        
        /*! Remove a component from the component registry.
         * If a component with that name does not exist this call is ignored.
         */
        virtual void unregisterComponent(const char *componentName)
        {
            if (!componentName)
                return;
            componentMap.erase(componentName);
        }

        /*! Query list of all registered components.
         * Components are listed in no particular order.
         * \param visitor An instance of ComponentListVisitor, which will receive the details of each component. If this is 0 this call is ignored.
         */   
        virtual void visitComponentList(ComponentListVisitor *visitor) const
        {
            if (!visitor)
                return;
            for (ComponentMap::const_iterator i = componentMap.begin(); i != componentMap.end(); i++)
            {
                if (!i->second.first) // not hidden?
                    visitor->visitComponent(i->first.c_str(), i->second.second);
            }
        }
               
        /*! Hide registered component.
         * The component must have already been registered.
         * Hidden component are visible throu lookupComponent() (when their name is known) but not through visitComponentList().
         */
        virtual void hideComponent(const char *componentName) 
        {
            if (!componentName)
                return;
            ComponentMap::iterator i = componentMap.find(componentName);
            if (i == componentMap.end())
                return;
            i->second.first = true;
        }
        
    protected:
        // private data
        
        /*! Owner of this object: all ObtainInterface() call gets forwarded to this object. */       
        CAInterface *interfaceOwner;
        /*! List of all registered components. */
        typedef std::map<std::string, std::pair<bool, CAInterface*> > ComponentMap; // componenName -> (hidden, interfacePtr)
        ComponentMap componentMap;
    };
}

#endif

