#!/usr/bin/env python
# \file    ModeChangeWaiter.py
# \brief   High level Python interface to CADI models.
# \date    Copyright 2013 ARM Limited. All rights reserved.

import CADI
from Exceptions import TimeoutError, TargetBusyError
from threading import Thread, Event
from Queue import Queue

class ModeChangeWaiter(Thread):
    """
    Thread which calls CADIExec(Continue|Stop|SingleStep), then waits for the
    target complete the operation.
    """

    def __init__(self, targets):
        Thread.__init__(self)
        
        if len(targets) < 1:
            raise ValueError("Model must have at least one target to control execution")

        self._targets = targets
        self._control_target = targets[0]
        self._event_queue = Queue()
        self.__complete_event = Event()
        self.__cadi_exception = None
        
        # This means that python can terminate, even if this thread never terminates
        self.daemon = True
    
    # this method runs in the simulation thread
    def _modechange(self, mode, bpt_num):
        if mode in (CADI.CADI_EXECMODE_Run, CADI.CADI_EXECMODE_Stop):
            self._event_queue.put(mode)
    
    # this method is run in the waiter thread
    def run(self):
        for t in self._targets:
            t._callbacks.add(CADI.CADI_CB_ModeChange, self._modechange)
        
        try:
            self._call_and_wait()
        except Exception as ex:
            self.__cadi_exception = ex
        
        self.__complete_event.set()
        
        for t in self._targets:
            t._callbacks.remove(CADI.CADI_CB_ModeChange, self._modechange)
    
    # this method is run in the debug thread
    def wait(self, timeout=None):
        if not self.__complete_event.wait(timeout):
            raise TimeoutError
        if self.__cadi_exception is not None:
            raise self.__cadi_exception


class RunWaiter(ModeChangeWaiter):
    def __init__(self, targets, wait_for_stop):
        ModeChangeWaiter.__init__(self, targets)
        self.__wait_for_stop = wait_for_stop
    
    def _call_and_wait(self):
        self._control_target._run()
        
        startCount = 0
        stopCount = 0
        while True:
            mode = self._event_queue.get()
            if mode == CADI.CADI_EXECMODE_Run:
                startCount += 1
            if mode == CADI.CADI_EXECMODE_Stop:
                stopCount += 1
            if self.__wait_for_stop:
                if startCount == stopCount == len(self._targets):
                    break
            else:
                if startCount == len(self._targets):
                    break


class StopWaiter(ModeChangeWaiter):
    def __init__(self, targets):
        ModeChangeWaiter.__init__(self, targets)
        
        # find a control target which does not have HALT_CORE set
        good_targets = [t for t in targets if t.read_register("Extended Features.HALT_CORE") == 0]
        if len(good_targets) > 0:
            self._control_target = good_targets[0]
        else:
            raise TargetBusyError("Cannot safely stop a simulation in which all the targets are halted")
    
    def _call_and_wait(self):
        # This should not be needed, according to the CADI spec, as models should
        # return an error code (raise an exception in python) when trying to
        # stop a stopped target. However, our models do not return the error,
        # so this workaround is needed until this is fixed.
        if not self._control_target.is_running:
            raise TargetBusyError("Cannot stop an already stopped target")
        self._control_target._stop()
        
        stopCount = 0
        while True:
            mode = self._event_queue.get()
            if mode == CADI.CADI_EXECMODE_Stop:
                stopCount += 1
            if stopCount == len(self._targets):
                break

class StepWaiter(ModeChangeWaiter):
    def __init__(self, targets, count):
        ModeChangeWaiter.__init__(self, targets)
        
        self.__step_count = count
        self._cores = [t for t in targets if t.executes_software]
        if len(self._cores) < 1:
            raise ValueError("Model must have at least one cpu target to step execution")
    
    def _call_and_wait(self):
        # This should not be needed, according to the CADI spec, as models should
        # return an error code without changing the execution state of the
        # processor when attempting to step a running target. However, the models
        # actually stop the target, then return the error.
        if self._control_target.is_running:
            raise TargetBusyError("Cannot step a running target")
        
        old_halt_cores = {core: core.read_register("Extended Features.HALT_CORE") for core in self._cores}
        
        for target in self._cores:
            if old_halt_cores[target] != 0:
                # The user has set HALT_CORE, so do not step this one
                continue
            
            for other_target in self._cores:
                if other_target != target:
                    other_target.write_register("Extended Features.HALT_CORE", 1)
                else:
                    other_target.write_register("Extended Features.HALT_CORE", 0)
            
            target._step(self.__step_count, False, False)
            
            startCount = 0
            stopCount = 0
            while True:
                mode = self._event_queue.get()
                if mode == CADI.CADI_EXECMODE_Run:
                    startCount += 1
                if mode == CADI.CADI_EXECMODE_Stop:
                    stopCount += 1
                if startCount == stopCount == len(self._targets):
                    break
        
        for core, halt_state in old_halt_cores.items():
            core.write_register("Extended Features.HALT_CORE", halt_state)

