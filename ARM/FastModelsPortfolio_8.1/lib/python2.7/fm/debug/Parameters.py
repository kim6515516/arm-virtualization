#!/usr/bin/env python
# \file    Parameters.py
# \brief   High level Python interface to CADI models.
# \date    Copyright 2011-2013 ARM Limited. All rights reserved.

import CADI
from numbers import Integral


class ModelParameter(object):
    def __init__(self, info):
        object.__init__(self)
        
        self.__info = info

    @property
    def description(self):
        return self.__info.description

    @property
    def isRunTime(self):
        return self.__info.isRunTime != 0

    @property
    def name(self):
        return self.__info.name

    

class ModelIntParameter(long, ModelParameter):
    def __init__(self, info, value=None):
        if not (isinstance(value, Integral) or value is None):
            raise TypeError("Parameter must be an integer, not '%s'" % type(value))

        ModelParameter.__init__(self, info)
        long.__init__(self)

        self.__info = info

    def __new__(cls, info, value=None):
        if value is not None:
            return long.__new__(cls, value)
        else:
            return long.__new__(cls, info.defaultValue)

    @property
    def defaultValue(self):
        return self.__info.defaultValue

    @property
    def maxValue(self):
        return self.__info.maxValue

    @property
    def minValue(self):
        return self.__info.minValue

    def _get_cadi_value(self):
        # info.(min|max|default)Value is stored as int64_t, but sometimes contains 2**64-1
        # The workaround is to add/subtract 2**64 if values seem wrong (max < min)

        # This does not fix the problem in all possible cases
        # This currently gets triggered by the AEM and v8 models
        # Is *seems* to fix the bug for all current cores using the default property values
        # Many properties use the range [-2**63, 2**63-1] so I don't think this can be solved properly

        # This is based on CadiRunner::CheckParameter in MaxCore/CadiRunner/CadiRunner.cpp
        if self.__info.maxValue >= self.__info.minValue:
            if self >= self.__info.minValue and self <= self.__info.maxValue:
                intValue = self
            else:
                raise ValueError("int parameter %s must satisfy: %i <= value <= %i (actual %i)"
                                 % (self.__info.name, self.__info.minValue, self.__info.maxValue, self))
        else: # min and max wrong way round, must be unsigned range

            def unsigned_to_signed(n):
                if n < 0:
                    return n + (2 ** 64)
                else:
                    return n

            if (    unsigned_to_signed(self) >= unsigned_to_signed(self.__info.minValue)
                and unsigned_to_signed(self) <= unsigned_to_signed(self.__info.maxValue) ):
                intValue = self
            else:
                raise ValueError("int parameter %s must satisfy: %i <= value <= %i (actual %i)"
                                 % (self.__info.name, self.__info.minValue, self.__info.maxValue, self))
        return CADI.CADIParameterValue(self.__info.id,
                                       CADI.CADI_PARAM_INT,
                                       intValue,
                                       "")

class ModelBoolParameter(ModelParameter):
    def __init__(self, info, value=None):
        
        if not (isinstance(value, bool) or isinstance(value, ModelBoolParameter) or value is None):
            raise TypeError("Parameter must be a bool, not '%s'" % type(value))

        ModelParameter.__init__(self, info)
        
        if value is not None:
            self.__value = value
        else:
            self.__value = (info.defaultValue != 0)
        
        self.__info = info

    def __getattr__(self, name):
        return self.__value.__getattribute__(name)

    def __repr__(self):
        return self.__value.__repr__()

    def __nonzero__(self):
        return self.__value.__nonzero()

    def __cmp__(self, other):
        return self.__value.__cmp__(other)

    @property
    def defaultValue(self):
        return bool(self.__info.defaultValue)

    def _get_cadi_value(self):
        intValue = 1 if self.__value == True else 0
        return CADI.CADIParameterValue(self.__info.id,
                                       CADI.CADI_PARAM_BOOL,
                                       intValue,
                                       "")


class ModelStringParameter(str, ModelParameter):
    def __init__(self, info, value=None):
        if not (isinstance(value, str) or value is None):
            raise TypeError("Parameter must be a string, not '%s'" % type(value))

        ModelParameter.__init__(self, info)
        
        self.__info = info

    def __new__(cls, info, value=None):
        if value is not None:
            return str.__new__(cls, value)
        else:
            return str.__new__(cls, info.defaultString)

    @property
    def defaultValue(self):
        return self.__info.defaultString

    def _get_cadi_value(self):
        return CADI.CADIParameterValue(self.__info.id,
                                       CADI.CADI_PARAM_STRING,
                                       0,
                                       self)


class ParameterDict(dict):
    """
    Derives from dict and keeps a list of items which has been changed since
    being initialised.
    """

    def __init__(self, parameter_infos):
        super(ParameterDict, self).__init__(self)
        self.__infos = {info.name: info for info in parameter_infos}
        self._dirty_set = set()

        for info in self.__infos.values():
            if info.dataType == CADI.CADI_PARAM_INVALID:
                raise TypeError("parameter has invalid type %i" % info.dataType)
            elif info.dataType == CADI.CADI_PARAM_STRING:
                self.__setitem__(info.name, None)
            elif info.dataType == CADI.CADI_PARAM_BOOL:
                self.__setitem__(info.name, None)
            elif info.dataType == CADI.CADI_PARAM_INT:
                self.__setitem__(info.name, None)
            else:
                raise TypeError("parameter has invalid type %i" % info.dataType)

    def __setitem__(self, key, value):
        if key not in self.__infos:
            raise KeyError(key)
        info = self.__infos[key]
        if info.dataType == CADI.CADI_PARAM_STRING:
            super(ParameterDict, self).__setitem__(key, ModelStringParameter(info, value))
        elif info.dataType == CADI.CADI_PARAM_INT:
            super(ParameterDict, self).__setitem__(key, ModelIntParameter(info, value))
        elif info.dataType == CADI.CADI_PARAM_BOOL:
            super(ParameterDict, self).__setitem__(key, ModelBoolParameter(info, value))
        else:
            raise TypeError("parameter has invalid type %i" % info.dataType)
        self._dirty_set.add(key)

    def _get_parameter_array(self):
        """
        Generate a list of CADI.CADIParameterValue objects corresponding to the
        parameters that have been modified since initialisation.
        """
        
        param_list = []
        for info in self.__infos.values():
            if info.name in self._dirty_set:
                value = self.__getitem__(info.name)
                param_list.append(value._get_cadi_value())
        return param_list


class RuntimeParameterDict(ParameterDict):
    """
    Allows runtime CADI Parameters to be set by name using the index operator.
    e.g:
        parameters["semihosting-enable"] = False
    The value will be immediately set using CADI.CADISetParameters().
    Attempts to set the value of an init-time parameter will likely result in
    ValueError being raised but actual behaviour will depend on the model.
    """

    def __init__(self, cadi):
        self.__cadi = None
        try:
            param_infos = cadi.CADIGetParameters()
        except NotImplementedError:
            # not all targets support runtime parameters
            param_infos = []
        super(RuntimeParameterDict, self).__init__(param_infos)
        self._dirty_set = set()
        self.__cadi = cadi

    def __setitem__(self, key, value):
        super(RuntimeParameterDict, self).__setitem__(key, value)
        if self.__cadi != None: # only forward after dict has been initially populated
            self.__cadi.CADISetParameters(self._get_parameter_array())
            self._dirty_set = set()
