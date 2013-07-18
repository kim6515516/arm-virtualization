#!/usr/bin/env python
# \file    Exceptions.py
# \brief   Provides the CADIReturnException class used by fm.debug
# \date    Copyright 2012-2013 ARM Limited. All rights reserved.


class TargetError(Exception):
    """
An error occured while accessing the target
"""

    pass


class TargetBusyError(TargetError):
    """
The call could not be completed because the target is busy

Registers and memories, for example, might not be writable while the target is
executing application code.

The debugger can either wait for the target to reach a stable state or enforce a
stable state by, for example, stopping a running target. The debugger can repeat
the original call after the target reaches a stable state.
"""

    pass


class SecurityError(TargetError):
    """
Method failed because of an access being denied

Could be caused by, for example, writing a read-only register or reading memory
with restricted access.
"""

    pass


class TimeoutError(TargetError):
    """Timeout expired while waiting for a target to enter the desired state"""

    pass


class SimulationEndedError(TargetError):
    """Attempted to call a method on a simulation which has ended"""

    def __str__(self):
        return "Simulation has ended"
