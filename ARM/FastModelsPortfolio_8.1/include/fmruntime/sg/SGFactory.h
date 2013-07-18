/*!
 * \file    SGFactory.h
 * \brief   Component factory types.
 * \date    Copyright 2005-2006 ARM Limited. All rights reserved.
 * \author  Andrew Bolt and Graeme Barnes.
 *
 */

#ifndef ARM_SG_FACTORY_H
#define ARM_SG_FACTORY_H


#include "SGConfigList.h"
#include "SGBasicComponentFactory.h"

namespace sg {

class FSComponentFactory;
class ComponentManager;
class Component;
class SimulationContext;



/*! A ComponentManager is a container for ComponentFactory objects.  
 *  When a factory is add()ed to the container, it is indexed against
 *  its class name, as returned by ComponentFactory::getClassName().
 *  A client can then use the locate() method to obtain a ptr to
 *  a previously-add()ed factory.
 */
class ComponentManager
{

 protected:
    SimulationContext *context;

 public:
    static ComponentManager *getInstance(SimulationContext *context);

    ComponentManager(SimulationContext *context_) : context(context_)
    {
    }

    virtual ~ComponentManager() {}

    /*! Get a handle to the simulation context. */    
    SimulationContext *getSimulationContext() const {
        return context;
    }

    /*! Used by shared objects to register their ComponentFactory objects. 
     *  This calls factory->setManager(this), so the factory knows who
     *  owns it.
     */
    virtual void add(FSComponentFactory *factory) = 0;

    /*! Locate a component's factory. */
    virtual ComponentFactory * locate(std::string const & device_class) = 0;

    /*! Locate the factory of the given class type.  This relies on T
     *  having a static member, className() that returns the same string
     *  as was returned by getClassName() for a previously-add()ed factory.
     *
     *  The value is returned by dynamic_cast<T*>, so will be NULL if the
     *  type doesn't match.
     */
    template< typename T >
    T * get()
    {
        ComponentFactory *factory = locate(T::className());
        return (dynamic_cast<T*>(factory));
    }


    /*! Helper function, to locate the factory identified by 'device_class',
     *  and ask it to instantiate a component called 'instance_name', with
     *  the configuration provided.
     *  \todo This provides legacy support for FVP components.
     */
    ComponentBase * instantiate(std::string const & device_class,
                                std::string const & instance_name,
                                ConfigList *config);

    /*! Helper function, to locate the factory identified by 'device_class',
     *  and ask it to instantiate a component called 'instance_name', with
     *  the configuration provided.
     */
    ComponentBase * instantiate(std::string const & device_class,
                                std::string const & instance_name,
                                Params const & params);


    /*! Helper function, to locate the factory identified by 'device_class',
     *  and ask it to instantiate a component called 'instance_name', with
     *  a default empty configuration.
     */
    ComponentBase * instantiate(std::string const & device_class,
                                std::string const & instance_name);
};


/*! Legacy support for FVP component factories. */
class FSComponentFactory : public BasicComponentFactory
{
 protected:
    ComponentManager *manager;
    int ref_count;

 public:
    FSComponentFactory() : ref_count(1) {
    }

    void setManager(ComponentManager *manager_) {
        manager = manager_;
        ++ref_count;
    }

    /*! Allow subclasses to be destructed through base class. */
    virtual ~FSComponentFactory() {
    }

    //! Do nothing when a client calls dereference: the factory is a
    //! singleton.
    virtual void dereference() {
        --ref_count;
        if (ref_count == 0) {
            delete this;
        }
    }

    //! Increase the reference count on a factory to stop it being deleted.
    void addReference() {
        ++ref_count;
    }

    /*! Return a string that uniquely identifies the class of components
     *  created by this factory. 
     */
    virtual std::string getClassName() = 0;

    // Subclasses should implement base class method from sg::ComponentFactory:
    // virtual ComponentBase * instantiate(std::string const & instance_name,
    //                                     SimulationContext * context,
    //                                     Params const & params) = 0;
};



/*! Generic base class for a simple factory that creates components of type 
 *  T.  The factory provides a default parameter-less create() function,
 *  to return the newly created object of type T, as well as implementing
 *  ComponentFactory::instantiate() to return an abstract Component.
 */
template <class T>
class GenericFactory : public FSComponentFactory
{
 public:
    /*! Factory returns same class name as the component. */
    static std::string className() { return T::className(); }

    /*! Allow an instance of this factory to identify itself. */
    std::string getClassName() { return className(); }

    /*! Create a new type T component with the given name, ignoring the
     *  configuration and context.
     */
    virtual ComponentBase *instantiate(std::string const & name, 
                                       SimulationContext *context,
                                       Params const & params) {
        (void)context;
        (void)params;
        return create(name);
    }

    /*! Create a new, default instance of T. */
    virtual T *create(std::string const & name) = 0;
};



/*! The top-level function exported by a shared library, which registers
 *  its factories with the manager.
 */
typedef void(InitFunc)(ComponentManager *manager);

/*! Singleton instance of ComponentManager, used by default COMPONENT_ENTRY macros. */
extern ComponentManager * global_manager;


#ifdef COMPONENT_SHARED
#define COMPONENT_ENTRY(n) extern "C" void entry

#else
#define COMPONENT_ENTRY(n) extern "C" void n##_entry
#endif

#define COMPONENT_FACTORY_FUNC(n) n##_GetFactory

/*! Declare the existence of a LISA factory function for the component. */
#define COMPONENT_FACTORY_SIG(n) sg::ComponentFactory * n##_GetFactory()
#define COMPONENT_FACTORY_DECL(n) sg::ComponentFactory * n##_GetFactory() ; sg::ComponentBase * n##_ComponentFactory(const char * instName, sg::SimulationContext *simulationContext, const sg::Params& params) ;

/*! Implement the LISA factory for the compoment. */
#define COMPONENT_FACTORY_IMPL(n,f) \
               COMPONENT_FACTORY_SIG(n) \
               { \
                   return sg::global_manager->locate(f); \
               } \


#define DECLARE_COMPONENT_ENTRY(n) COMPONENT_ENTRY(n)(sg::ComponentManager *); \
      COMPONENT_FACTORY_DECL(n);

} // namespace sg


#define GET_COMPONENT_MANAGER(context) (sg::ComponentManager::getInstance(context))

#define PUBLISH_COMPONENT(classname, name) \
    do { \
        sg::ComponentFactory* factory = classname##_GetFactory(); \
        publishComponent(factory, name, true); \
        factory->dereference(); \
    } while(0) \

#endif // ARM_SG_FACTORY_H
