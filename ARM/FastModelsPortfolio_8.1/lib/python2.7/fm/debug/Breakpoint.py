#!/usr/bin/env python
# \file    Breakpoint.py
# \brief   Interface to a breakpoint in a CADI target
# \date    Copyright 2011-2013 ARM Limited. All rights reserved.

import CADI
from Exceptions import TargetBusyError
from threading import Event
from collections import defaultdict

_breakpoint_type_names = defaultdict(lambda: "Unknown")
_breakpoint_type_names[CADI.CADI_BPT_PROGRAM] = "Program"
_breakpoint_type_names[CADI.CADI_BPT_MEMORY] = "Memory"
_breakpoint_type_names[CADI.CADI_BPT_REGISTER] = "Register"
_breakpoint_type_names[CADI.CADI_BPT_INST_STEP] = "InstStep"
_breakpoint_type_names[CADI.CADI_BPT_PROGRAM_RANGE] = "ProgramRange"
_breakpoint_type_names[CADI.CADI_BPT_EXCEPTION] = "Exception"
_breakpoint_type_names[CADI.CADI_BPT_USER_DEFINED] = "UserDefined"


class Breakpoint(object):
    """Provides a high level interface to breakpoints."""

    def __init__(self, target, cadi, req, bptNumber=None, description=None):
        self.__info = req
        self.__target = target
        self.__cadi = cadi
        self.__triggered = Event()
        self.__bpt_seen = False
        self.__description = description
        if bptNumber == None:
            self.__number = self.__cadi.CADIBptSet(self.__info)
            self.__enabled = True
        else:
            self.__number = bptNumber
            self.__enabled = req.enabled != 0

    @property
    def memory_space(self):
        """The name of the memory space that this breakpoint is set in
        
        Only valid for program and memory breakpoints"""
        if self.__info.type in (CADI.CADI_BPT_PROGRAM, CADI.CADI_BPT_MEMORY):
            return self.__target._memory_spaces_by_number[self.__info.address.location.space].memSpaceName
        else:
            raise AttributeError("This type of breakpoint does not have a memory space")

    @property
    def address(self):
        """The memory address that this breakpoint is set on
        
        Only valid for program and memory breakpoints"""
        if self.__info.type in (CADI.CADI_BPT_PROGRAM, CADI.CADI_BPT_MEMORY):
            return self.__info.address.location.addr
        else:
            raise AttributeError("This type of breakpoint does not have an address")

    @property
    def register(self):
        """The name of the register that this breakpoint is set on
        
        Only valid for register breakpoints"""
        if self.__info.type == CADI.CADI_BPT_REGISTER:
            return self.__target._all_registers_by_id[self.__info.regNumber]._info.name
        else:
            raise AttributeError("This type of breakpoint does not have a register")

    @property
    def on_read(self):
        """True if this breakpoint is triggered on read
        
        Only valid for register and memory breakpoints"""
        if self.__info.type in (CADI.CADI_BPT_REGISTER, CADI.CADI_BPT_MEMORY):
            return (self.__info.triggerType & CADI.CADI_BPT_TRIGGER_ON_READ) != 0
        else:
            raise AttributeError("This type of breakpoint does not have a trigger type")

    @property
    def on_write(self):
        """True if this breakpoint is triggered on write
        
        Only valid for register and memory breakpoints"""
        if self.__info.type in (CADI.CADI_BPT_REGISTER, CADI.CADI_BPT_MEMORY):
            return (self.__info.triggerType & CADI.CADI_BPT_TRIGGER_ON_WRITE) != 0
        else:
            raise AttributeError("This type of breakpoint does not have a trigger type")

    @property
    def on_modify(self):
        """True if this breakpoint is triggered on modify
        
        Only valid for register and memory breakpoints"""
        if self.__info.type in (CADI.CADI_BPT_REGISTER, CADI.CADI_BPT_MEMORY):
            return (self.__info.triggerType & CADI.CADI_BPT_TRIGGER_ON_MODIFY) != 0
        else:
            raise AttributeError("This type of breakpoint does not have a trigger type")

    @property
    def bpt_type(self):
        """The name of the breakpoint type
        
        Valid values are:
            * Program
            * Memory
            * Register
            * InstStep
            * ProgramRange
            * Exception
            * UserDefined
        
        Not all types are supported by all models, and only Program, Memory and
        Register are fully supported by fm.debug.
        """
        return _breakpoint_type_names[self.__info.type]

    @property
    def number(self):
        """Identification number of this breakpoint
        
        This is the same as the key in the Target.breakpoints dictionary.
        
        This is only valid until the breakpoint is deleted, and breakpoint
        numbers can be re-used."""
        return self.__number
    
    @property
    def enabled(self):
        """True if the breakpoint is currently enabled"""
        return self.__enabled
    
    @enabled.setter
    def enabled(self, value):
        if value:
            self.enable()
        else:
            self.disable()

    def _modeChange_handler(self, newMode, bptNumber):
        """
        Intended to be registered with a PyCADICallBackObj.
        Notifys waiting threads that the breakpoint has been triggered.
        """
        if newMode == CADI.CADI_EXECMODE_Run:
            self.__triggered.clear()
            self.__bpt_seen = False
        elif newMode == CADI.CADI_EXECMODE_Bpt and bptNumber == self.__number:
            self.__bpt_seen = True
        elif newMode == CADI.CADI_EXECMODE_Stop and self.__bpt_seen:
            self.__triggered.set()

    def enable(self):
        """Enable the breakpoint if supported by the model."""
        # Currently (Apr 2013), no ARM models support CADIBptConfigure.
        self.__cadi.CADIBptConfigure(self.number, CADI.CADI_BPT_Enable)
        self.__enabled = True

    def disable(self):
        """Disable the breakpoint if supported by the model."""
        # Currently (Apr 2013), no ARM models support CADIBptConfigure.
        self.__cadi.CADIBptConfigure(self.number, CADI.CADI_BPT_Disable)
        self.__enabled = False

    def delete(self):
        """Remove the breakpoint from the target
        
        This breakpoint should not be accessed after this method is called"""
        if self.__target.is_running:
            raise TargetBusyError("Cannot delete breakpoints while target is running")
        self.__cadi.CADIBptClear(self.number)
        del self.__target.breakpoints[self.number]

    def wait(self, timeout=None):
        """
        Block until the breakpoint is triggered or the timeout expires.
        Returns True if the breakpoint was triggered, False otherwise.
        """
        return self.__triggered.wait(timeout)

    @property
    def is_hit(self):
        """True if the breakpoint was hit last time the target was running"""
        return self.__triggered.is_set()

    def __repr__(self):
        additional = []
        additional.append("enabled=%s" % self.enabled)
        if self.__info.type == CADI.CADI_BPT_PROGRAM:
            additional.append("address=%s" % hex(self.address).rstrip("lL"))
        if self.__info.type == CADI.CADI_BPT_MEMORY:
            additional.append("address=%s" % hex(self.address).rstrip("lL"))
        if self.__info.type == CADI.CADI_BPT_REGISTER:
            additional.append("register=%s" % self.register)
        type_name = _breakpoint_type_names[self.__info.type]
        if type_name == "Unknown":
            type_name += " (%d)" % self.__info.type
        return "<Breakpoint type=%s %s number=%d>" % (type_name,
                                                      " ".join(additional),
                                                      self.__number)
