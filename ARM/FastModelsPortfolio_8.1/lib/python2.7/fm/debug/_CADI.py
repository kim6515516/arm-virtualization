# \file    _CADI.py
# \brief   High level Python interface to CADI models.
# \date    Copyright 2013 ARM Limited. All rights reserved.

import platform
import imp
import os

variety = '%(system)s-%(bits)s' % {'system' : platform.system(),
                                   'bits' : platform.architecture()[0]}

module_name = {
    'Linux-64bit' : '_CADI_64.so',
    'Linux-32bit' : '_CADI_32.so',
    'Windows-64bit' : '_CADI_64.pyd',
    'Windows-32bit' : '_CADI_32.pyd',
}[variety]

_CADI = imp.load_dynamic('_CADI', os.path.join(os.path.dirname(__file__), module_name))

globals().update(_CADI.__dict__)

del platform, imp, os, module_name, _CADI
