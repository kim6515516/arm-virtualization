#!/usr/bin/env python
# \file    Breakpoint.py
# \brief   Python wrappers for CADI callbacks
# \date    Copyright 2011-2013 ARM Limited. All rights reserved.

from cStringIO import StringIO
import os
import sys
from warnings import warn
from threading import Lock
from functools import wraps

import CADI

__all__ = ["CADIcallback", "InputWrapper", "PyCADICallback", "PyCADIErrorCallback",
           "Stream", "CADIFACT_SEVERITY2str", "CADIFACT_ERROR2str"]


def CADIFACT_SEVERITY2str(severity):
    """Convert a CADIFACT_SEVERITY_* int value to a string.
    """
    if severity >= 0 and severity < 3:
        return ["CADIFACT_SEVERITY_OK",
                "CADIFACT_SEVERITY_WARNING",
                "CADIFACT_SEVERITY_ERROR"][severity]
    else:
        return "(unknown CADIFACT_SEVERITY code 0x%08X)" % severity


def CADIFACT_ERROR2str(error):
    """Convert a CADIFACT_ERROR_* int value to a string.
    """
    if error >= 0 and error <= CADI.CADIFACT_ERROR_GENERAL_WARNING:
        return ["CADIFACT_ERROR_OK", \
                "CADIFACT_ERROR_LICENSE_FOUND_BUT_EXPIRED", \
                "CADIFACT_ERROR_LICENSE_NOT_FOUND", \
                "CADIFACT_ERROR_LICENSE_COUNT_EXCEEDED", \
                "CADIFACT_ERROR_CANNOT_CONTACT_LICENSE_SERVER", \
                "CADIFACT_ERROR_WARNING_LICENSE_WILL_EXPIRE_SOON",\
                "CADIFACT_ERROR_GENERAL_LICENSE_ERROR",\
                "CADIFACT_ERROR_PARAMETER_TYPE_MISMATCH",\
                "CADIFACT_ERROR_PARAMETER_VALUE_OUT_OF_RANGE",\
                "CADIFACT_ERROR_PARAMETER_VALUE_INVALID",\
                "CADIFACT_ERROR_UNKNOWN_PARAMETER_ID",\
                "CADIFACT_ERROR_GENERAL_PARAMETER_ERROR",
                "CADIFACT_ERROR_GENERAL_ERROR",\
                "CADIFACT_ERROR_GENERAL_WARNING"][error]
    else:
        return "(unknown CADIFACT_ERROR code 0x%08X)" % error


class Stream:
    """Threadsafe string stream"""

    def __init__(self):
        self.stream = StringIO()
        self.lock = Lock()
        self.position = 0

    def read(self, n=-1):
        """Read to the front of the stream"""
        with self.lock:
            prev_position = self.stream.tell()
            self.stream.seek(self.position)
            result = self.stream.read(n)
            self.position = self.stream.tell()
            self.stream.seek(prev_position)
        return result

    def write(self, s):
        """Write to the back of the stream"""
        with self.lock:
            prev_position = self.stream.tell()
            self.stream.seek(0, os.SEEK_END)
            self.stream.write(s)
            self.stream.seek(prev_position)

    def __getattr__(self, attr):
        return getattr(self.stream, attr)


class InputWrapper:
    """Used to prompt an interactive user for input"""

    def __init__(self, prompt="> ", message="Target requests input"):
        self.prompt = prompt
        self.message = message

    def read(self, n=None):
        """
        Displays an input prompt and reads input from the user using raw_input.
        """
        if n != None:
            print self.message + " (max %i characters):" % n
        else:
            print self.message + ":"
        result = raw_input(self.prompt)
        n = min(len(result), n)
        return result[0:n]


def CADIcallback(func):
    """
    Decorator method to surround CADICallbackObj methods with
    try:
        ...
    except:
        ...
    If an exception is thrown, print the function/method name and the exception
    """

    @wraps(func)
    def decorate(*args):
        try:
            func(*args)
        except Exception as e:
            print "Error during callback %s:" % func.__name__
            print e
    return decorate


class PyCADICallback(CADI.CADICallbackObj):
    """
    Python wrapper that allows CADI callbacks
    """

    def __init__(self):
        CADI.CADICallbackObj.__init__(self)
        self.handlers = {}
        for cb in CADI.CADICallbacks:
            self.handlers[cb] = []

    def add(self, callback, func):
        """Register a callback handler"""
        if callback not in self.handlers:
            raise ValueError("Invalid callback")
        if callback == CADI.CADI_CB_AppliInput and len(self.handlers[callback]) > 0:
            raise ValueError("appliInput only supports one handler")
        self.handlers[callback].append(func)

    def remove(self, callback, func):
        """Unregister a callback handler"""
        if callback in self.handlers:
            if func in self.handlers[callback]:
                self.handlers[callback].remove(func)
            else:
                ValueError("Callback function cannot be removed, because it is not registered for this callback")
        else:
            raise ValueError("Invalid callback")

    def doCallback(self, callback, *args):
        """Calls the handler functions"""
        if callback not in self.handlers.keys():
            return # fail gracefully if no callback set.
                   # This should not occur if getEnable() is used
        for func in self.handlers[callback]:
            func(*args)

    def getEnable(self):
        """
        Return an appropriate enable string to pass to CADIXfaceAddCallback()
        """
        return ''.join(['\001' if len(self.handlers[cb]) > 0 else '\000'
                       for cb in CADI.CADICallbacks])

    @CADIcallback
    def appliOpen(self, sFileName, mode):
        """
        This method is deprecated
        """
        self.doCallback(CADI.CADI_CB_AppliOpen, sFileName, mode)

    @CADIcallback
    def appliInput(self, streamId, count, actualCountp, buf):
        """
        This callback is used to request semihosting input
        """
        self.doCallback(CADI.CADI_CB_AppliInput, streamId,
                        count, actualCountp, buf)

    @CADIcallback
    def appliOutput(self, streamId, count, actualCountp, buf):
        """
        This callback is used to send semihosting output
        """
        self.doCallback(CADI.CADI_CB_AppliOutput,
                        streamId, count, actualCountp, buf)

    @CADIcallback
    def appliClose(self, streamID):
        """
        This method is deprecated
        """
        self.doCallback(CADI.CADI_CB_AppliClose, streamID)

    @CADIcallback
    def doString(self, stringArg):
        """
        Used by the target to send a string to the debugger
        """
        self.doCallback(CADI.CADI_CB_String, stringArg)

    @CADIcallback
    def modeChange(self, newMode, bptNumber):
        """
        Reports a mode change in the target
        """
        self.doCallback(CADI.CADI_CB_ModeChange, newMode, bptNumber)

    @CADIcallback
    def reset(self, resetLevel):
        """
        Reports that the target has finished a reset.
        This is the same as modeChange(CADI_EXECMODE_ResetDone).
        """
        self.doCallback(CADI.CADI_CB_Reset, resetLevel)

    @CADIcallback
    def cycleTick(self):
        """
        This method is deprecated.
        """
        self.doCallback(CADI.CADI_CB_CycleTick)

    @CADIcallback
    def killInterface(self):
        """
        This method is deprecated.
        """
        self.doCallback(CADI.CADI_CB_KillInterface)

    @CADIcallback
    def bypass(self, commandLength, command, maxResponseLength, response):
        """
        Reserved for future use by the callback object.
        """
        response = self.doCallback(CADI.CADI_CB_Bypass, command)

    @CADIcallback
    def lookupSymbol(self, symbolLength, symbol, maxResponseLength, response):
        """
        Reserved for future use by the callback object.
        """
        self.doCallback(CADI.CADI_CB_LookupSymbol, symbol)

    @CADIcallback
    def refresh(self, refreshReason):
        """
        Indicates that the state of the target has changed spontaneously
        while it is stopped
        """
        self.doCallback(CADI.CADI_CB_Refresh, refreshReason)


class PyCADIErrorCallback(CADI.CADIErrorCallback):
    """Receives error callbacks during simulation initalisation"""

    def __init__(self, cb=None):
        CADI.CADIErrorCallback.__init__(self)
        self.Error = cb or self.Error

    @CADIcallback
    def Error(self, severity, errorCode, erroneousParameterId, message):
        """
        Recieves error information during instantiation
        """
        print "CADIErrorCallback::Error(severity=%s, error=%s, paramId=%d, message=%s)" % (
                        CADIFACT_SEVERITY2str(severity),
                        CADIFACT_ERROR2str(errorCode),
                        erroneousParameterId,
                        repr(message))
