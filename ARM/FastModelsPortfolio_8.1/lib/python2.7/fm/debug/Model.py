#!/usr/bin/env python
# \file    Model.py
# \brief   High level Python interface to CADI models.
# \date    Copyright 2011-2013 ARM Limited. All rights reserved.

import CADI
from Callback import *
from Target import Target
from Parameters import ParameterDict
from Exceptions import TimeoutError, TargetError
from ARMTargets import TargetV7A, TargetV8A, TargetV7RM, TargetV56, TargetV6Secure
from ModeChangeWaiter import RunWaiter, StopWaiter, StepWaiter
from functools import wraps
from threading import Event, Thread
import atexit
from sys import stdout
from collections import defaultdict, namedtuple
from warnings import warn

_target_classes = defaultdict(lambda: Target)

# v5
_target_classes["ARM_ARM926EJ-S"] = TargetV56

# v6
_target_classes["ARM_ARM1136JF-S"] = TargetV56
_target_classes["ARM_ARM1176JZF-S"] = TargetV6Secure

# v7A
_target_classes["ARM_AEMv7-A_UP"] = TargetV7A
_target_classes["ARM_AEMv7-A_MP"] = TargetV7A
_target_classes["ARM_Cortex-A5UP"] = TargetV7A
_target_classes["ARM_Cortex-A5MP"] = TargetV7A
_target_classes["ARM_Cortex-A7"] = TargetV7A
_target_classes["ARM_Cortex-A8"] = TargetV7A
_target_classes["ARM_Cortex-A9UP"] = TargetV7A
_target_classes["ARM_Cortex-A9MP"] = TargetV7A
_target_classes["ARM_Cortex-A15"] = TargetV7A

# v7R
_target_classes["ARM_Cortex-R4"] = TargetV7RM
_target_classes["ARM_Cortex-R5"] = TargetV7RM
_target_classes["ARM_Cortex-R7"] = TargetV7RM

# v7M
_target_classes["ARM_Cortex-M3"] = TargetV7RM
_target_classes["ARM_Cortex-M4"] = TargetV7RM

# v8A
_target_classes["ARM_Cortex-A53"] = TargetV8A
_target_classes["ARM_Cortex-A57"] = TargetV8A
_target_classes["ARMAEMv8-A_MP"] = TargetV8A


TargetInfo = namedtuple("TargetInfo", ["instance_name", "target_name", "version",
                                       "description", "component_type",
                                       "executes_software", "is_hardware_model"])


class Model(object):
    """
    This class wraps a CADI 2.0 model.
    """

    class SimulationCallback(CADI.CADISimulationCallback):
        """
        A CADISimulationCallback that is able to release the simulation when
        simShutdown or simKilled is called.
        """

        def __init__(self, model, verbose=False):
            CADI.CADISimulationCallback.__init__(self)
            self.__model = model
            self.__shutdown = Event()
            self.__killed = False
            self.verbose = verbose

            self.__thread = Thread(target=self.__wait_for_shutdown,
                                   name="WaitForShutdown")
            self.__thread.daemon = True
            self.__thread.start()

        def __wait_for_shutdown(self):
            """
            Releases the model once a simShutdown or simKilled callback occurs.
            This is intended to be run in a seperate thread because the callback
            is executed in the simulation thread, from which you cannot release
            the model.
            """
            self.__shutdown.wait()
            self.__model._shutdown(self.__killed)

        @CADIcallback
        def simMessage(self, message):
            """Recieves a message from the simulation and prints it"""
            # print message without trailing linefeed
            stdout.write(message)

        @CADIcallback
        def simShutdown(self):
            """
            Indicates that the simulation has been shutdown and any references
            to it should be released.
            """
            if not self.__shutdown.is_set():
                if self.verbose:
                    print "Simulation is shutting down"
                self.__shutdown.set()

        @CADIcallback
        def simKilled(self):
            """The simulation has been killed and cannot be released"""
            if not self.__shutdown.is_set():
                if self.verbose:
                    print "Simulation killed"
                self.__killed = True
                self.__shutdown.set()

    class ObtainInterfaceFailed(Exception):
        """Failed to obtain an interface object"""

        def __init__(self, name):
            self.interface_name = name

        def __str__(self):
            return "Failed to obtain interface '%s'" % self.interface_name

    def __init__(self, simulation, verbose):
        self.__is_released_or_killed = False
        self.__simulation = simulation
        atexit.register(self.release)
        self.__targets = {}
        self.__verbose = verbose
        
        # get one cpu target, so that it is always possible to run, stop and step the model
        target_infos = self.__simulation.GetTargetInfos()
        cpu_infos = [info for info in target_infos if info.executesSoftware]
        if len(cpu_infos) < 1:
            self.__first_target = self.get_target(target_infos[0].instanceName)
        else:
            self.__first_target = self.get_target(cpu_infos[0].instanceName)

    def _shutdown(self, killed):
        """Release the simulation and disable the Targets from making CADI calls"""
        for target in self.__targets.values():
            target._shutdown()
        if not killed:
            self.release()

    def get_target(self, target):
        """
        Obtain an interface to a target
        
        :param target: The instance name corresponding to the desired target
        """

        interface_name = "eslapi.CADI2"
        target_id = next((t.id for t in self.__simulation.GetTargetInfos()
                         if t.instanceName == target), None)
        if target_id == None:
            raise ValueError("Model has no target named \"%s\"" % target)
        if target_id not in self.__targets:
            target = self.__simulation.GetTarget(target_id)
            result = target.ObtainInterface(interface_name)
            if type(result) == int:
                raise Model.ObtainInterfaceFailed(interface_name)
            (interface, rev) = result
            cadi = CADI.CAInterface_CADI(interface)
            target_name = cadi.CADIGetTargetInfo().targetName
            try:
                # if this fails, this target object hangs around, breaking the
                # modechange callbacks
                target_object = _target_classes[target_name](cadi, self)
            except Exception as ex:
                target_object = Target(cadi, self)
                if self.__verbose:
                    warn("Failed to load specialised target, falling back to general implementation.\n(Error: %s)" % ex)
            self.__targets[target_id] = target_object
        return self.__targets[target_id]

    def get_cpus(self):
        """Returns all targets which have executes_software set"""
        targetInfoList = self.__simulation.GetTargetInfos()
        return [self.get_target(info.instanceName)
                for info in targetInfoList if info.executesSoftware]

    def get_target_info(self):
        """Returns an iterator over namedtuples containing information about
           all of the target instances contained in the model"""
        result = []
        for info in self.__simulation.GetTargetInfos():
            yield TargetInfo(instance_name = info.instanceName,
                             target_name = info.targetName,
                             version = info.version,
                             description = info.description,
                             component_type = info.componentType,
                             executes_software = info.executesSoftware != 0,
                             is_hardware_model = info.isHardwareModel != 0)

    def release(self, shutdown=False):
        """
        End the simulation and release the model.

        :param shutdown:
            If True, the simulation will be shutdown and any other scripts or debuggers
            will have to disconnect.

            If False, a simulation might be kept alive after disconnection.
        """
        for target in self.__targets.values():
            target._shutdown()
        if self.__is_released_or_killed:
            return
        self.__is_released_or_killed = True
        if self.__simulation != None:
            self.__simulation.Release(shutdown)
        self._broker.Release()

    def run(self, blocking=True, timeout=None):
        """
        Starts the model executing

        :param blocking:
            If True, this call will block until the model stops executing
            (typically due to a breakpoint).
            If False, this call will return once that target has started executing.

        :param timeout:
            If None, this call will wait indefinitely for the target to enter
            the correct state.
            If set to a float or int, this parameter gives the maximum number of
            seconds to wait.

        :raises TimeoutError: If the timeout expires.
        """

        waiter_thread = RunWaiter(self.__targets.values(), blocking)
        waiter_thread.start()
        waiter_thread.wait(timeout)

        if blocking:
            # flatten the hit breakpoint lists from each target into one list
            return [bpt for target in self.__targets.values() for bpt in target.get_hit_breakpoints()]
        else:
            return

    def stop(self, timeout=None):
        """
        Stops the model executing

        :param timeout:
            If None, this call will wait indefinitely for the target to enter
            the correct state.
            If set to a float or int, this parameter gives the maximum number of
            seconds to wait.

        :raises TimeoutError: If the timeout expires.
        """

        waiter_thread = StopWaiter(self.__targets.values())
        waiter_thread.start()
        waiter_thread.wait(timeout)

    def step(self, count=1, timeout=None):
        """
        Execute the target for `count` steps.

        :param steps:
            The number of processor cycles to execute.

        :param timeout:
            If None, this call will wait indefinitely for the target to enter
            the correct state.
            If set to a float or int, this parameter gives the maximum number of
            seconds to wait.

        :raises TimeoutError: If the timeout expires.
        """
        
        waiter_thread = StepWaiter(self.__targets.values(), count)
        waiter_thread.start()
        waiter_thread.wait(timeout)


class LibraryModel(Model):
    """A CADI model loaded from a DLL"""

    def __init__(self, filename, parameters={}, verbose=False):
        """
        Loads a model from a DLL, and initialises it

        :param filename:
            The path of the file to load the model from

        :param parameters:
            Dictionary containing parameters of the model to set. The keys of
            this dictionary should be strings containing the names of the
            parameters, and the values should be strings, bools or ints containing
            the values of the parameters

        :param verbose:
            If True, extra debugging information is printed
        """

        self.__filename = filename
        self._loader = CADI.CADIDll()
        self._loader.openDll(filename)
        self._broker = self._loader.CreateCADIBroker()
        factories = self._broker.GetSimulationFactories()
        factory = factories[0]

        callbacks_enable = '\001' * CADI.CADI_SIM_CB_Count
        errors = []

        @CADIcallback
        def Error(severity, errorCode, erroneousParameterId, message):
            """
            Error(severity, errorCode, erroneousParameterId, message)
            Recieves error information during instantiation
            """
            errors.append("CADIErrorCallback::Error(severity=%s, error=%s, paramId=%d, message=%s)"
                          % (CADIFACT_SEVERITY2str(severity),
                             CADIFACT_ERROR2str(errorCode),
                             erroneousParameterId,
                             repr(message)))

        parameter_dict = ParameterDict(factory.GetParameterInfos())
        for (key, value) in parameters.iteritems():
            # This will raise an exception for unknown parameters
            parameter_dict[key] = value
        
        # This will raise an exception for parameters set to a value of
        # the wrong type or out of range
        parameter_array = parameter_dict._get_parameter_array()
        
        self._sim_callback = Model.SimulationCallback(self, verbose)
        self._sim_error_callback = PyCADIErrorCallback(Error)
        
        simulation = factory.Instantiate(parameter_array,
                                         self._sim_error_callback,
                                         self._sim_callback,
                                         callbacks_enable)
        if simulation is None:
            raise TargetError("Instantiation failed: " + ", ".join(errors))
        factory.Release()

        Model.__init__(self, simulation, verbose)

    @classmethod
    def get_model_parameters(cls, filename):
        """Get a dictionary containing the default parameters for the model

        :param filename:
            The path of the file to load the model parameters from
        """
        loader = CADI.CADIDll()
        loader.openDll(filename)
        broker = loader.CreateCADIBroker()
        factory = broker.GetSimulationFactories()[0]
        return ParameterDict(factory.GetParameterInfos())

    def __repr__(self):
        return "<LibraryModel('%s') object at %s>" % (self.__filename, hex(id(self)))


class NetworkModel(Model):
    """A CADI model connected to using CADIIPC"""

    def __init__(self, host, port, verbose=False):
        """
        Connects to an already initalised model using CADIIPC

        :param host:
            Hostname or IP address of the computer running the model.

        :param port:
            Port number that the model is listening on.

        :param verbose:
            If True, extra debugging information is printed
        """

        self.__host = host
        self.__port = port
        self._loader = CADI.CADIClient()
        self._broker = self._loader.CreateCADIBroker("cadiclient://" + host)

        callbacks_enable = '\001' * CADI.CADI_SIM_CB_Count
        errors = []

        @CADIcallback
        def Error(severity, errorCode, erroneousParameterId, message):
            """
            Error(severity, errorCode, erroneousParameterId, message)
            Recieves error information during instantiation
            """
            errors.append("CADIErrorCallback::Error(severity=%s, error=%s, paramId=%d, message=%s)"
                          % (CADIFACT_SEVERITY2str(severity),
                             CADIFACT_ERROR2str(errorCode),
                             erroneousParameterId,
                             repr(message)))
        
        self._sim_callback = Model.SimulationCallback(self, verbose)
        self._sim_error_callback = PyCADIErrorCallback(Error)
        
        simulation = self._broker.SelectSimulation(port,
                                                   self._sim_error_callback,
                                                   self._sim_callback,
                                                   callbacks_enable)

        if simulation is None:
            raise TargetError("Instantiation failed: " + ", ".join(errors))

        Model.__init__(self, simulation, verbose)

    def __repr__(self):
        return "<NetworkModel(host='%s', port=%d) object at %s>" % (self.__host, self.__port, hex(id(self)))
