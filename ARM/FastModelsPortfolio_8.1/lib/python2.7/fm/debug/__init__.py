#!/usr/bin/env python
# \brief   High level Python interface to Fast Models.
# \date    Copyright 2011-2013 ARM Limited. All rights reserved.
"""
High level Python interface to Fast Models.

A new model can be created by creating a new LibraryModel, passing the filename
of the library that contains the model, and optionally a dictionary of parameters.

An existing model can be connected to by creating a new NetworkModel, passing
the address (IP address or hostname) and port number.

The model is comprised of multiple targets which represent the components in the
system.

A Target object can be obtained by calling Model.get_target(name) on an
instantiated model passing it the name of the target.
Information about the available targets can be obtained using Model.get_target_infos().

A convenience method Model.get_cpus() is also provided which will return a list
of Target objects for all targets which have the executes_software flag set.

Example:
>>> parameters = {"visualisation.window_title": "Python!"}
>>> model = LibraryModel("path/to/model.so", parameters)
>>> cpus = model.get_cpus()
>>> cpus[0].load_application("brot.axf")
>>> model.run()
"""

import sys
if sys.hexversion < 0x02070000 or sys.hexversion >= 0x03000000:
    raise ImportError("fm.debug requires Python 2.7.x")
del sys


from Model import LibraryModel, NetworkModel
from Exceptions import TargetError, TimeoutError, SecurityError, TargetBusyError, SimulationEndedError

__all__ = ["LibraryModel", "NetworkModel", "TargetError", "TimeoutError",
           "SecurityError", "TargetBusyError", "SimulationEndedError"]
