// ===========================================================================
// Description : CADI Factory.
//
// Author      : ARM
// Release     : 2.0.0
//
// Copyright (c) 2006-2008 ARM. All rights reserved.
//
// ============================================================================
//
#ifndef CADI2Factory_h
# define CADI2Factory_h

# include "eslapi/CADICommon.h"
# include "eslapi/CADITypes.h"

namespace eslapi
{
    /// @brief Error Callback Class
    ///
    /// Base class for CADI error callbacks
    class CADI_WEXP CADIErrorCallback : public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADIErrorCallback2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        /// This message is called to signal an error to the listeners
        /// @param[in]  severity              Severity of the error.
        /// @param[in]  errorCode             error code
        /// @param[in]  erroneousParameterId  If this error referes to a parameter this is the id of the parameter causing the error
        /// @param[in]  message               error message
        virtual void Error(CADIFactorySeverityCode_t severity,
                           CADIFactoryErrorCode_t errorCode,
                           uint32_t erroneousParameterId,
                           const char *message) = 0;
    };

    /// @brief Simulation Callback Class
    ///
    /// Base class for simulation callbacks allowing to register as a listener for system-wide callbacks
    class CADI_WEXP CADISimulationCallback :
        public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADISimulationCallback2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        /// This method allows to send system-wide messages to all listeners
        /// @param[in]  message               message text
        virtual void simMessage(const char *message) = 0;

        /// This method allows the simulation to signal that it wants to shut down.
        /// All clients are requested to unregister their callback handlers,
        /// and release any references to the simulation.
        virtual void simShutdown() = 0;

        /// The simulation is being forcedly terminated.  After this call has
        /// returned, the client must cease all communication with the
        /// simulation.  This callback is intended to provide last-ditch
        /// recovery, in situations when it is not possible to go through
        /// the clean simShutdown() route.
        virtual void simKilled() = 0;
    };

    /// @brief Simulation Interface
    ///
    /// This class represents a single simulation
    class CADI_WEXP CADISimulation : public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADISimulation2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        // Releases this simulation.
        // Disconects and cleans-up targets obtained from this simulation.
        // Using a target obtained from a simulation after the simulation is released is illegal.
        // @param[in] shutdown Specifies if the simulation should shutdown and exit.
        virtual void Release (bool shutdown) = 0;

        /// Register to listen for simulation-wide events (eg. system messages).
        /// @param[in] errorCallback    error callback to register
        virtual void AddCallbackObject(CADISimulationCallback *callbackObject) = 0;

        /// Log off as a listener for simulation-wide events (eg. system messages).
        /// @param[in] errorCallback    error callback to deregister
        virtual void RemoveCallbackObject(CADISimulationCallback *callbackObject) = 0;

        /// Get info about the targets that will be provided when the simulation is instantiated.
        /// @param[in] startTargetInfoIndex          Index of first target info to return. If 'startTargetIndex' exceeds the
        ///                                          maximum target index, CADI_STATUS_IllegalArgument is returned.
        /// @param[in] desiredNumberOfTargetInfos    Desired number of target infos to return.
        ///                                          Note that array 'simulationList' must have at least this size!
        /// @param[out] targetInfoList               Array of target informations returned. This array must be allocated by
        ///                                          the caller. The minimum size of this array is 'desiredNumberOfTargetInfos'.
        /// @param[out] actualNumberOfTargetInfos    Actual number of target infos
        /// @return                                  Error code
        virtual CADIReturn_t GetTargetInfos(uint32_t startTargetInfoIndex,
                                            uint32_t desiredNumberOfTargetInfos,
                                            CADITargetInfo_t *targetInfoList,
                                            uint32_t *actualNumberOfTargetInfos) = 0;

        /// Returns an interface handle for the target with a given target ID. If no CADI exists with id 'targetID' 0 is returned
        /// @param[in] startTargetInfoIndex          Index of first target info to return. If 'startTargetIndex' exceeds the
        virtual CAInterface *GetTarget(uint32_t targetID) = 0;
    };

    /// @brief Create a new simulation
    ///
    /// This class provides a mechanism to bring a new simulation into life.
    class CADI_WEXP CADISimulationFactory : public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADISimulationFactory2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        // Releases this factory. A debugger is expected to release the CADISimulationFactory as soon as the CADI simulation is created.
        virtual void Release () = 0;

        /// This method returns the name for this factory
        /// @return Name of this factory
        virtual const char* GetName() = 0;

        /// Returns description for this factory.
        /// @return Description for this factory
        virtual const char* GetDescription() = 0;

        /// Returns parameter infos of the simulation which can be created by this simulation factory. If the system is a
        /// hierarchical system, the parameter name encodes the position in the hierarchy by using dots as separators. Example:\n\n
        /// \p core.mem.size \n\n
        /// refers to parameter 'size' of component 'mem' which is subcomponent of 'core'.
        /// @param[in] startParameterInfoIndex         Index of first parameter info to return. If 'startParameterIndex' exceeds the
        ///                                            maximum parameter index, CADI_STATUS_IllegalArgument is returned.
        /// @param[in] desiredNumberOfParameterInfos   Desired number of parameter infos to return.
        ///                                            Note that array 'simulationList' must have at least this size!
        /// @param[out] parameterInfoList              Array of parameter informations returned. This array must be allocated by
        ///                                            the caller. The minimum size of this array is 'desiredNumberOfParameterInfos'.
        /// @param[out] actualNumberOfParameterInfos   Actual number of parameter infos returned.
        /// @return                                    Error code.
        ///
        virtual CADIReturn_t GetParameterInfos(uint32_t startParameterInfoIndex,
                                               uint32_t desiredNumberOfParameterInfos,
                                               CADIParameterInfo_t *parameterInfoList,
                                               uint32_t *actualNumberOfParameterInfos) = 0;

        /// This method instantiate a simulation based on the given parameter
        /// values. Errors occuring during system initialization are
        /// signaled through the given error callback 'errorCallback'.
        /// This call does not return until the instantiation is completed,
        /// which may some time.
        ///
        /// @param[in] parameterValues           parameter values. 
        ///                                      This array must be terminated by an extra item having an parameterID of static_cast<uint32_t>(-1)
        ///                                      (default value)
        /// @param[in] errorCallback             error callback object to be used for signaling error conditions
        /// @param[in] simulationCallbackObject  callback object to be used for signaling model-wide conditions
        /// @param[in] simulationCallbacksEnable The elements of this array enable or disable specific simulation callbacks. The simulation must
        ///                                      always check if the callbacks are enabled or not and these should not be called if they
        ///                                      are disabled. The listener may not want to be called in certain cases.
        /// @return                              pointer to created simulation or a NULL pointer if creation failed
        virtual CADISimulation *Instantiate(CADIParameterValue_t *parameterValues,
                                            CADIErrorCallback *errorCallbackObject,
                                            CADISimulationCallback *simulationCallbackObject,
                                            char simulationCallbacksEnable[CADI_SIM_CB_Count]) = 0;
    };

    /// @brief Simulation broker
    ///
    /// This interface allows connecting to existing simulations and creating new simulations.
    /// Note:
    /// - The CADI broker owns all CADI simulations and hence no other class is allowed to delete these.
    /// - If a CADI factory creates a simulation, it must transfer the pointer to the new simulation to the broker.
    /// - If the simulation is shut down / killed, the broker is responsible for deleting the simulation. This must be done while processing
    ///   GetSimulationInfos() checking for running simulations at the latest by checking if the reference count is 0 and other implemetation
    ///   specific conditions.
    class CADI_WEXP CADIBroker : public CAInterface
    {
    public:
        /// Return the CAInterface name for this interface.
        static if_name_t IFNAME() { return "eslapi.CADIBroker2"; }

        /// Specify the current minor revision for this interface.
        static if_rev_t IFREVISION() { return 0; }

        virtual ~CADIBroker() {}

        // Releases this broker. Should be called after all simulations and simulation factories obtained from this broker have been released.
        virtual void Release () = 0;

        /// This method returns a list of possible simulation factories provided by this simulation broker.
        /// This list is static for a given CADIBroker.  Note that because this function copies an array of
        /// CADISimulationFactory pointers, it is the caller's responsibility to called Release() on each
        /// of the referenced objects.
        ///
        /// @param[in] startFactoryIndex        Index of first factory to return. If 'startFactoryIndex' exceeds the maximum factory
        ///                                     index, CADI_STATUS_IllegalArgument is returned.
        /// @param[in] desiredNumberOfFactories Desired number of factories to return.
        ///                                     Note that array 'factoryList' must have at least this size!
        /// @param[out] factoryList             Array of factory pointers returned. This array must be allocated by caller.
        ///                                     The minimum size of this array is 'desiredNumberOfFactories'.
        ///                                     Note that the returned factory pointers must not be used to delete the factories
        ///                                     as these are owned by the broker
        /// @param[out] actualNumberOfFactories Actual number of factories returned.
        /// @return                             Error Code
        virtual CADIReturn_t GetSimulationFactories(uint32_t startFactoryIndex,
                                                    uint32_t desiredNumberOfFactories,
                                                    CADISimulationFactory **factoryList,
                                                    uint32_t *actualNumberOfFactories) = 0;


        /// This method returns a list of simulation infos informing about the running simulations managed by this CADI simulation broker.
        /// Note that this list may change dynamically during lifetime of this CADIBroker.
        ///
        /// @param[in] startSimulationInfoIndex       Index of first simulation info to return. If 'startSimulationInfoIndex' exceeds the
        ///                                           maximum simulation info index, CADI_STATUS_IllegalArgument is returned.
        /// @param[in] desiredNumberOfSimulationInfos Desired number of simulation infos to return.
        ///                                           Note that array 'simulationInfoList' must have at least this size!
        /// @param[out] simulationInfoList            Array of simulation infos returned. This array must be allocated by the caller.
        ///                                           The minimum size of this array is 'desiredNumberOfSimulationInfos'.
        /// @param[out] actualNumberOfSimulationInfos Actual number of simulation infos returned.
        /// @return                                   Error Code
        virtual CADIReturn_t GetSimulationInfos(uint32_t startSimulationInfoIndex,
                                                uint32_t desiredNumberOfSimulations,
                                                CADISimulationInfo_t *simulationList,
                                                uint32_t *actualNumberOfSimulations) = 0;

        /// This method allows to connect to a simulation identified by a given simulation identifier. A pointer to the simulation is
        /// returned on success. If no simulation with the given id is managed by this broker, 0 is returned.
        ///
        /// @param[in] simulationId              The id of the simulation to be returned. This is part of the respective entry in the list of
        ///                                      simulation infos 'simulationList' returned by method 'GetSimulationInfos'.
        /// @param[in] errorCallbackObject       Error callback to be used for signaling error conditions
        /// @param[in] simulationCallbackObject  callback object to be used for signaling model-wide conditions
        ///                                      Note that this callbacks might be called during execution of SelectSimulation(), e.g for signaling
        ///                                      that the simulation wants to shut down.
        /// @param[in] simulationCallbacksEnable The elements of this array enable or disable specific simulation callbacks. The simulation must
        ///                                      always check if the callbacks are enabled or not and these should not be called if they
        ///                                      are disabled. The listener may not want to be called in certain cases.
        /// @return                              pointer to simulation or NULL
        virtual CADISimulation* SelectSimulation( uint32_t simulationId,
                                                  CADIErrorCallback* errorCallbackObject,
                                                  CADISimulationCallback* simulationCallbackObject,
                                                  char simulationCallbacksEnable[CADI_SIM_CB_Count]) = 0;
    };

    /// @brief Prototype for global function to instantiate a broker.
    ///
    /// This is the type of the CreateCADIBroker global 'C'
    /// function that a client locates from a dynamically loaded object.
    /// Clients should locate this symbol and cast it as a pointer to
    /// CreateCADIBroker_t:
    ///    void * entry = lookup_symbol(dll, "CreateCADIBroker");
    ///    CADIBroker *broker = ((*CADIBroker::CreateCADIBroker_t)entry)();
    typedef CADIBroker * (CreateCADIBroker_t)();

} // namespace eslapi

extern "C"
{
    /// @brief Global function exported by a dynamically loaded object.
    ///
    /// This function must exist in a dynamically loaded object (DLL/.so).
    /// It allows the client to instantiate the CADIBroker.
    CADI_WEXP eslapi::CADIBroker * CreateCADIBroker();
}

#endif

// end of file CADIFactory.h
