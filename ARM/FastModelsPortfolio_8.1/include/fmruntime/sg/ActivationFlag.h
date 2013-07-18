/*!
 * \file    ActivationFlag.h
 * \brief   Support for efficient read-access to a flag which changes state infrequently
 * \date    Copyright 2009 ARM Limited. All rights reserved.
 */

#ifndef ACTIVATIONFLAG_H
#define ACTIVATIONFLAG_H

#include <list>

/*! \brief Clients implement this to be notified whenever a flag changes state. */
class ActivationFlagObserver
{
public:
    /*! \brief Receive notification when the flag state changes.
     *
     *  \param new_state The new state of the flag being observer.
     */
    virtual void flagStateChanged(bool new_state) = 0;

    /*! \brief Receive notification when the flag is destroyed.
     *
     * The base-flag object is still valid at this point, so it is
     * legal to read its final boolean state.
     *
     * The observer should not attempt to unregister itself as part of
     * this callback.
     */
    virtual void flagDestroyed() = 0;

    virtual ~ActivationFlagObserver() {}
};

/*! \brief Base-class for objects having an observable boolean value.
 *
 * This provides a boolean-like object which can be observed, but doesn't
 * provide a mechanism for controlling when the boolean value changes.
 */
class ActivationValue
{
    /*! \brief Internal type to manage the list of observers. */
    typedef std::list<ActivationFlagObserver *> ObserverList_t;

    struct SafeBoolStruct;    //!< Dummy type used for safe_bool_t.

    /*! \brief A form of boolean which is safe to use in an implicit cast.
     * 
     *  It is risky to provide an "operator bool()" cast, because C++
     *  allows this cast to be used in an integer context; this can mask
     *  some programming errors.
     *
     *  By providing an implicit cast operator to safe_bool_t rather than
     *  to bool, this implicit cast will only work in a boolean context.
     *  If you want to treat the flag as an integer, you can do:
     *  \code
     *    int x = bool(activation); // (activation ? 1 : 0)
     *  \endcode
     */
    typedef int SafeBoolStruct::*safe_bool_t;
    
protected:
    /*! Create a flag with an initial boolean state. */
    ActivationValue(bool initial_value = false);

    /*! Destroy a flag and notify all its observers. */
    ~ActivationValue();
    void changeValue(bool new_value);

public:
    /*! \brief Returns the current state of the activation flag. */
    bool isActive() const;
    
    inline bool operator == (bool o) const { return o == isActive(); }
    inline bool operator != (bool o) const { return o != isActive(); }

    /*! \brief Allow the flag object to be used in a boolean context.  
     *
     *  This is effectively an implicit cast to boolean; however it is safer
     *  than providing an operator bool() method, which would allow the
     *  object to be used in a numeric context.
     */
    operator safe_bool_t() const;

    /*! \brief A handle to the observer's place in the list.
     * 
     *  This allows observers to be unregistered in constant time.
     */
    typedef ObserverList_t::iterator ObserverHandle_t;

    /*! \brief Register to receive change notifications.
     *
     * \param new_observer The object to receive notifications.
     * \return A handle that can be used for efficient unregistering.
     */
    ObserverHandle_t addObserver(ActivationFlagObserver *new_observer) const;

    /*! \brief Stop an observer fom receiving notifications.
     *
     * This call may be slow if the flag has a large number of observers.
     * Use removeObserver(ObserverHandle_t) in preference.
     *
     *  \param existing_observer An object previously registered using addObserver()
     */
    void removeObserver(ActivationFlagObserver *existing_observer) const;

    /*! \brief Efficiently stop an observer from receiving notifications.
     *
     *  \param handle The value returned from the corresponding addObserver() call.
     */
    void removeObserver(ObserverHandle_t handle) const;


private:
    bool                   value;     //!< Current state of the flag.
    mutable ObserverList_t observers; //!< List of observers of the flag.
};


/*! Implement "safe bool" idiom; this ensures that you can use
 *  an ActivationFlagState in a bool context, but not in an int context.
 *
 *  The value of (&SafeBoolStruct::m_nonzero) is "true" in a bool context.
 */
struct ActivationValue::SafeBoolStruct {
    int dummy__a_pointer_to_this_is_0_on_buggy_compilers;
    int m_nonzero;   //!< &SafeBoolStruct::m_nonzero is guaranteed to be a non-zero pointer-to-member value.
};

inline bool ActivationValue::isActive() const
{
    return value;
}

inline ActivationValue::operator safe_bool_t() const
{
    return isActive() ? &SafeBoolStruct::m_nonzero : 0;
}

/*! \brief An observable, modifiable boolean flag.
 *
 *  ActivationFlag is intended to be used in situations where a flag changes 
 *  state infrequently, but needs to be read in critical-path code.  To
 *  support this, the flag's current state can be broadcast to a number of
 *  ActivationFlagMonitor objects.
 *
 *  Typically, an owner of an ActivationFlag will use it as follows:
 *  \code
 *  class Owner {
 *    ActivationFlag activeness;
 *  public:
 *    // A const pointer to the flag can be monitored but not modified.
 *    ActivationValue const * getActiveness() {
 *      return &activeness; 
 *    }
 *  };
 *  \endcode
 *
 *  The ActivationFlag can be treated as a boolean object:
 *  \code
 *    if (activeness) ...
 *    activeness = false;
 *  \endcode
 *
 *  When a client needs to test the activation flag very frequently, it can 
 *  use an ActivationFlagMonitor object to hold a copy of the flag's state.
 *  This copy is kept up-to-date automatically, and can be read efficiently.
 *  See ActivationFlagMonitor for details.
 */
class ActivationFlag : public ActivationValue
{
public:
    /*! \brief Construct an ActivationFlag in the given state.
     *
     *  The default constructor initialises an ActivationFlag in the "false"
     *  state.  The optional argument explicitly sets the initial state.
     */
    ActivationFlag(bool enabled = false);

    /*! \brief Destroy a flag and remove all of its monitors. */
    ~ActivationFlag();

    /*! \brief Allow the owner of the flag to change its state. */
    void setActive(bool new_state = true);

    /*! \brief Allow the owner of the flag to change its state using assignment. */
    ActivationFlag& operator = (bool new_state);

    /*! \brief Allow one flag's boolean state to be assigned from another flag. */
    ActivationFlag & operator = (ActivationValue const &);

    /*! \brief Construct a flag with the same boolean state as another flag. */
    ActivationFlag(ActivationValue const &);
};

/*! \brief A Monitor can track the state of any number of other 
 *  ActivationValue objects (ActivationFlag or other ActivationMonitors)
 *  and can efficiently test whether any of them is true.
 *
 *  The monitor is set up as follows:
 *  \code
 *    ActivationFlagMonitor is_active;
 *    is_active.monitor(owner->getActiveness()); // one-off setup
 *    ..
 *  \endcode
 *  It can be tested as it if is a normal boolean - this is a very efficient
 *  inline test:
 *  \code
 *    if (is_active) ...
 *  \endcode
 *
 *  A client can monitor multiple flags, and quickly test whether
 *  whether one or many of them have been set:
 *  \code
 *    ActivationFlagMonitor are_active;
 *    are_active->monitor(owner1->getActiveness());
 *    are_active->monitor(owner2->getActiveness());
 *    ..
 *    if (are_active) ...  // true whenever owner1 or owner2 is active.
 *  \endcode
 *
 * Normally the monitor watches for any flags being true, but it can
 * also watch for flags being false.
 * \code
 *    is_inactive->monitor(owner->getActiveness(), false);
 *    if (is_inactive) // true if owner is not active.
 * \endcode
 */
class ActivationFlagMonitor : public ActivationValue
{
    class MonitorEntry;
    typedef MonitorEntry * FlagHandle_t;

    /*! Track how many flags are currently active. */
    unsigned count_active;

    /*! Track which flags we are monitoring. */
    MonitorEntry *monitor_of;

    void clearFlagList();
    void updateState();

public:
    /*! \brief Construct a monitor that is optionally watching a single flag. */
    ActivationFlagMonitor(ActivationValue const * flag = 0, bool active_sense = true);
   
    /*! \brief Tidy-up on exit. */
    ~ActivationFlagMonitor();

    /*! \brief Construct a monitor that has the same initial state as another moniotr.
     *
     *  The new monitor will be watching the same flag(s) as the existing monitor, but
     *  will have no observers.
     */
    ActivationFlagMonitor(ActivationFlagMonitor const &other);

    /*! \brief Copy-assignment: set this monitor to watch the same flags as another monitor.
     *
     * This monitor will set to watch the same set of ActivationFlag objects
     * as the other monitor, but it will keep its current set of observers.
     * If this assignment causes the monitor's boolean state to change,
     * all observers will be notified.
     */
    ActivationFlagMonitor & operator= (ActivationFlagMonitor const &other);

    /*! \brief Stop monitoring any flags. */
    void unmonitor();

    /*! \brief Start monitoring a specific flag. */
    FlagHandle_t monitor(ActivationValue const * flag, bool active_sense = true);

    /*! \brief Stop monitoring a specific flag. */
    void unmonitor(ActivationValue const * flag);

    /*! \brief Stop monitoring a specific flag. */
    void unmonitor(FlagHandle_t handle);
};
#endif
