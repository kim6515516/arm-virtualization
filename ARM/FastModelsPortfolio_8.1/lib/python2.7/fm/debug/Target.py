#!/usr/bin/env python
# \file    Target.py
# \brief   High level Python interface to CADI models.
# \date    Copyright 2011-2013 ARM Limited. All rights reserved.

import CADI
from Callback import *
from Register import Register, RegisterInfo
from Breakpoint import Breakpoint
from Parameters import RuntimeParameterDict
from Exceptions import SimulationEndedError
from functools import wraps
from numbers import Integral
from warnings import warn
from collections import defaultdict


class Target(object):
    """
    Wraps a CADI object providing a simplified interface to common tasks.

    Memory and registers can be accessed using methods, for example::

        cpu.read_memory(0x1234, count=8)
        cpu.write_register("Core.R5", 1000)
    
    Breakpoints can be set using methods of this object::

        cpu.add_bpt_mem(0x1234, memory_space="Secure", on_read=False)
        cpu.bpt_add_reg("Core.CPSR")

    These methods return Breakpoint objects, which allow enabling, disabling and
    deleting the breakpoint. The breakpoints currently set are accessible using
    the dictionary ``Target.breakpoints``, which maps from breakpoint numbers to
    Breakpoint objects.
    """

    class CADIShutdownShim:
        """Prevents calling CADI methods on a simulation which has ended"""

        def __init__(self, cadi):
            self._shutdown = False
            self.__cadi = cadi

        def __getattr__(self, attr):
            if self._shutdown:
                raise SimulationEndedError()
            else:
                return getattr(self.__cadi, attr)

    def __init__(self, cadi, model):
        try:
            self.__cadi = Target.CADIShutdownShim(cadi)
            self.__info = self.__cadi.CADIGetTargetInfo()
            self.__model = model

            self._callbacks = PyCADICallback()

            self.__cadi.CADIXfaceAddCallback(self._callbacks,
                                           '\001' * CADI.CADI_CB_Count)

            self.stdin = Stream()
            self.stdout = Stream()
            self.stderr = Stream()

            self._callbacks.add(CADI.CADI_CB_AppliInput, self.appliInput)
            self._callbacks.add(CADI.CADI_CB_AppliOutput, self.appliOutput)

            memory_spaces = self.__cadi.CADIMemGetSpaces()
            self._memory_spaces_by_name = {space.memSpaceName: space for space in memory_spaces}
            self._memory_spaces_by_number = {space.memSpaceId: space for space in memory_spaces}

            self.parameters = RuntimeParameterDict(self.__cadi)

            self._register_groups = {} # group_name -> (register_name -> Register)
            self._short_register_names = {} # register_name -> Register
            self._ambiguous_register_names = set() # used only to give the correct error message
            self._all_registers_by_id = {} # register_number -> Register

            for group in self.__cadi.CADIRegGetGroups():
                parents_by_id = {}
                registers_by_id = {}
                for info in self.__cadi.CADIRegGetMap(group.groupID):
                    registers_by_id[info.regNumber] = Register(self.__cadi, info)
                    details = info.get_details()
                    if details.type == CADI.CADI_REGTYPE_Compound:
                        for i in self.__cadi.CADIRegGetCompound(info.regNumber):
                            parents_by_id[i] = info.regNumber

                self._all_registers_by_id.update(registers_by_id)

                # construct tree structure
                self._register_groups[group.name] = {reg._info.name: reg
                                         for reg in registers_by_id.values()
                                         if reg._info.regNumber not in parents_by_id.keys()}
                for child_id, parent_id in parents_by_id.iteritems():
                    child = registers_by_id[child_id]
                    parent = registers_by_id[parent_id]
                    parent[child._info.name] = child


            name_uses = defaultdict(set)
            for group_name, group in self._register_groups.items():
                for register_name, register in group.items():
                    name_uses[register_name].add(register._info.regNumber)

            for short_name, uses in name_uses.items():
                uses = list(uses)
                if len(uses) == 1:
                    self._short_register_names[short_name] = self._all_registers_by_id[uses[0]]
                else:
                    self._ambiguous_register_names.add(short_name)


            try:
                # CADIBptGetList() returns an array of CADIBptDescription_t.
                # These objects are owned by python, but the CADIBptRequest_t objects
                # inside them are not, so we have to keep a reference to the
                # desription around as long as we keep the CADIBptRequest_t.
                # This is done by passing it in as an extra parameter to Breakpoint.
                self.breakpoints = {bpt.bptNumber: Breakpoint(self, self.__cadi, bpt.bptInfo, bpt.bptNumber, bpt)
                                    for bpt in self.__cadi.CADIBptGetList()}
            except Exception as e:
                self.breakpoints = {}
            self._callbacks.add(CADI.CADI_CB_ModeChange, self._modechange)
        except:
            # clean up the callbacks, as this object is probably going to be
            # garbage collected
            self._disconnect_callbacks()
            raise

    @property
    def component_type(self):
        return self.__info.componentType

    @property
    def description(self):
        return self.__info.description

    @property
    def executes_software(self):
        return self.__info.executesSoftware

    @property
    def instance_name(self):
        return self.__info.instanceName

    @property
    def target_name(self):
        return self.__info.targetName

    def appliInput(self, streamId, count, actualCountp, buf):
        """Semihosting input callback"""
        result = self.stdin.read(count)
        length = len(result)
        buf[0:length] = result
        CADI.uint32p_assign(actualCountp, length)

    def appliOutput(self, streamId, count, actualCountp, buf):
        """Semihosting output callback"""
        if streamId == CADI.CADI_STREAMID_STDOUT:
            stream = self.stdout
        elif streamId == CADI.CADI_STREAMID_STDERR:
            stream = self.stderr
        else:
            warn("attempted to write to stream: %s" % streamId)
        stream.write(buf)
        CADI.uint32p_assign(actualCountp, count)

    def _modechange(self, mode, bpt_num):
        """Callback, called when the target changes state or hits a breakpoint"""
        
        # Run and Stop events are now handled by ModeChangeWaiter and its subclasses
        
        # forward event on to all breakpoints
        # this is done here, rather in in a seperate event handler, to ensure
        # that all breakpoints have been marked as hit before returning from Model.run()
        for bpt in self.breakpoints.values():
            bpt._modeChange_handler(mode, bpt_num)

    def _disconnect_callbacks(self):
        if self._callbacks is not None:
            self.__cadi.CADIXfaceRemoveCallback(self._callbacks)
            self._callbacks = None

    def load_application(self, filename, loadData=True, verbose=False, parameters=None):
        """
        Load an application to run on the model.

        :param filename:    The filename of the application to load.
        :param loadData:    If set to True, the target loads data, symbols, and code.
                            If set to False, the target does not reload the application
                            code to its program memory. This can be used, for example,
                            to either:
                                * forward information about applications that are loaded
                                  to a target by other platform components.

                                * change command line parameters for an application that
                                  was loaded by a previous call.
        :param verbose:     Set this to True to allow the target to print verbose.
                            messages.
        :param parameters:  A list of command line parameters to pass to the application
                            or None.
        """
        self.__cadi.CADIExecLoadApplication(filename, loadData, verbose, parameters)

    def reset(self):
        """
        Reset the simulation

        This  will reset the model to a state equivalent to the state
        immediately after instantiation.
        """

        self.__cadi.CADIExecReset(0)

    def add_bpt_prog(self, address, memory_space=None):
        """
        Set a new breakpoint, which will be hit when program execution reaches a memory address

        :param address:
            The address to set the breakpoint on

        :param memory_space:
            The name of the memory space that ``address`` is in.
            If None, the current memory space of the core is used
        """

        space = self._get_address_space(memory_space)

        cadi_address = CADI.CADIAddrComplete(CADI.CADI_NO_OVERLAY,
                                             CADI.CADIAddr(space.memSpaceId, address))
        request = CADI.CADIBptRequest(enabled_par=1,
                                      type_par=CADI.CADI_BPT_PROGRAM,
                                      address_par=cadi_address)
        bpt = Breakpoint(self, self.__cadi, request)
        self.breakpoints[bpt.number] = bpt
        return self.breakpoints[bpt.number]

    def add_bpt_mem(self, address, memory_space=None, on_read=True, on_write=True, on_modify=True):
        """
        Set a new breakpoint, which will be hit when a memory location is accessed

        :param address:
            The address to set the breakpoint on

        :param memory_space:
            The name of the memory space that ``address`` is in.
            If None, the current memory space of the core is used

        :param on_read:
            If True, the breakpoint will be triggered when the memory location
            is read from.

        :param on_write:
            If True, the breakpoint will be triggered when the memory location
            is written to.

        :param on_modify:
            If True, the breakpoint will be triggered when the memory location
            is modified.
        """

        space = self._get_address_space(memory_space)

        cadi_address = CADI.CADIAddrComplete(CADI.CADI_NO_OVERLAY,
                                             CADI.CADIAddr(space.memSpaceId, address))

        trigger_type = 0
        if on_read:
            trigger_type |= CADI.CADI_BPT_TRIGGER_ON_READ
        if on_write:
            trigger_type |= CADI.CADI_BPT_TRIGGER_ON_WRITE
        if on_modify:
            trigger_type |= CADI.CADI_BPT_TRIGGER_ON_MODIFY

        if trigger_type == 0:
            raise ValueError("At least one of on_read, on_write and on_modify must be True")

        request = CADI.CADIBptRequest(enabled_par=1,
                                      type_par=CADI.CADI_BPT_MEMORY,
                                      address_par=cadi_address,
                                      triggerType_par=trigger_type)
        bpt = Breakpoint(self, self.__cadi, request)
        self.breakpoints[bpt.number] = bpt
        return self.breakpoints[bpt.number]

    def add_bpt_reg(self, reg_name, on_read=True, on_write=True, on_modify=True):
        """
        Set a new breakpoint, which will be hit when a register is accessed

        :param reg_name:
            The name of the register to set the breakpoint on.
            The name can be in one of the following formats:
                * ``<group>.<register>``
                * ``<group>.<register>.<field>``
                * ``<register>``
                * ``<register>.<field>``
            
            The last two forms can only be used if the register name is unambiguous

        :param on_read:
            If True, the breakpoint will be triggered when the register is read from.

        :param on_write:
            If True, the breakpoint will be triggered when the register is written to.

        :param on_modify:
            If True, the breakpoint will be triggered when the register is modified.
        """

        # No ARM models support register breakpoints (as of Apr 2013), so this is untested
        register = self._get_register_by_name(reg_name)

        trigger_type = 0
        if on_read:
            trigger_type |= CADI.CADI_BPT_TRIGGER_ON_READ
        if on_write:
            trigger_type |= CADI.CADI_BPT_TRIGGER_ON_WRITE
        if on_modify:
            trigger_type |= CADI.CADI_BPT_TRIGGER_ON_MODIFY

        if trigger_type == 0:
            raise ValueError("At least one of on_read, on_write and on_modify must be True")

        request = CADI.CADIBptRequest(enabled_par=1,
                                      type_par=CADI.CADI_BPT_REGISTER,
                                      regNumber_par=register._info.regNumber,
                                      triggerType_par=trigger_type)

        bpt = Breakpoint(self, self.__cadi, request)
        self.breakpoints[bpt.number] = bpt
        return self.breakpoints[bpt.number]

    def get_hit_breakpoints(self):
        """Returns the list of breakpoints that were hit last time the target
        was running"""
        for bpt in self.breakpoints.values():
            if bpt.is_hit:
                yield bpt

    @property
    def is_running(self):
        """Returns True if the target is currently running"""
        return (self.__cadi.CADIExecGetMode() == CADI.CADI_EXECMODE_Run)

    def _run(self):
        self.__cadi.CADIExecContinue()

    def _stop(self):
        self.__cadi.CADIExecStop()

    def _step(self, count, stepCycle, stepOver):
        self.__cadi.CADIExecSingleStep(count, stepCycle, stepOver)

    def _get_address_space(self, space_name):
        """
        Gets the CADIMemSpaceInfo object with the name ``space_name``

        If 'space_name' is None, returns the default memory space, which may
        depend on the current state of the target.

        Raises ValueError if the target does not have a memory
        space with the name space_name.
        """
        if not space_name:
            return self._get_default_memory_space()
        else:
            try:
                return self._memory_spaces_by_name[space_name]
            except KeyError:
                raise ValueError("Memory space '%s' does not exist in this target" % space_name)

    def _get_default_memory_space(self):
        """
        Gets the CADIMemSpaceInfo object of the default memory space

        This should be overriden by target-specific subclasses, and the return
        value can be dependent on the current state of the target
        """
        try:
            return self._memory_spaces_by_number.values()[0]
        except IndexError:
            raise ValueError("Target does not have any memory spaces")

    def read_memory(self, address, memory_space=None, size=1, count=1, do_side_effects=False):
        """
        :param address:
            Address to begin reading from.

        :param memory_space:
            Name of the memory space to read or None which will read the core's current memory space.

        :param size:
            Size of memory access unit in bytes. Must be one of 1, 2, 4 or 8.
            Note that not all values are supported by all models.
            Note that the data is always returned as bytes, so calling with
            size=4, count=1 will return a byte array of length 4.

        :param count:
            Number of units to read.

        :param do_side_effects:
            If True, the target must perform any side-effects normally triggered
            by the read, for example clear-on-read.

        Returns an integer if count is 1, otherwise returns a bytearray of length size*count

        """

        space = self._get_address_space(memory_space)

        if address < space.minAddress:
            raise ValueError("Address is below minimum address of memory space '%s'"
                            % space.memSpaceName)

        if address > space.maxAddress:
            raise ValueError("Address is above maximum address of memory space '%s'"
                            % space.memSpaceName)

        if size not in [1, 2, 4, 8]:
            raise ValueError("'size' must be 1, 2, 4 or 8")

        if count is None:
            count = len(data) / size
            if len(data) % size != 0:
                raise ValueError("len(data) must be a multiple of size")

        cadi_address = CADI.CADIAddrComplete(CADI.CADI_NO_OVERLAY,
                                             CADI.CADIAddr(space.memSpaceId, address))

        data = self.__cadi.CADIMemRead(cadi_address, count, size, do_side_effects)

        return data

    def write_memory(self, address, data, memory_space=None, size=1, count=None, do_side_effects=False):
        """
        :param address:
            Address to begin reading from

        :param data:
            The data to write.
            If count is 1, this must be an integer
            Otherwise it must be a bytearray with length >= size*count

        :param memory_space:
            memory space to read.
            Default is None which will read the core's current memory space.

        :param size:
            Size of memory access unit in bytes. Must be one of 1, 2, 4 or 8.
            Note that not all values are supported by all models.

        :param count:
            Number of units to write. If None, count is automatically calculated
            such that all data from the array is written to the target

        :param do_side_effects:
            If True, the target must perform any side-effects normally triggered
            by the write, for example triggering an interrupt.
        """

        space = self._get_address_space(memory_space)

        if address < space.minAddress:
            raise ValueError("Address is below minimum address of memory space '%s'"
                            % space.memSpaceName)

        if address > space.maxAddress:
            raise ValueError("Address is above maximum address of memory space '%s'"
                            % space.memSpaceName)

        if size not in [1, 2, 4, 8]:
            raise ValueError("'size' must be 1, 2, 4 or 8")

        if isinstance(data, Integral):
            data = bytearray([data])

        if count is None:
            count = len(data) / size
            if len(data) % size != 0:
                raise ValueError("len(data) must be a multiple of size")

        if isinstance(data, bytearray) and len(data) < size * count:
            raise ValueError("'data' must be either an integer, or a bytearray with length >= size*count")

        cadi_address = CADI.CADIAddrComplete(CADI.CADI_NO_OVERLAY,
                                             CADI.CADIAddr(space.memSpaceId, address))

        self.__cadi.CADIMemWrite(cadi_address, count, size, data, do_side_effects)

    def _get_register_by_name(self, name):
        """
        Possible name formats:
            register
            register.compound
            group.register
            group.compound.register
        """

        parts = name.split(".")
        if len(parts) == 1:
            (register,) = parts
            if register in self._short_register_names:
                return self._short_register_names[register]
            elif register in self._ambiguous_register_names:
                raise ValueError("Register name '%s' is ambiguous (exists in multiple register groups)" % register)
            else:
                raise ValueError("Register '%s' does not exist" % register)
        elif len(parts) == 2:
            if parts[0] in self._register_groups:
                (group, register) = parts
                if register in self._register_groups[group]:
                    return self._register_groups[group][register]
                else:
                    raise ValueError("Register '%s' does not exist in group '%s'" % (register, group))
            elif parts[0] in self._short_register_names:
                (register, field) = parts
                if field in self._short_register_names[register]:
                    return self._short_register_names[register][field]
                else:
                    raise ValueError("Field '%s' does not exist in register '%s'" % (field, register))
            elif parts[0] in self._ambiguous_register_names:
                raise ValueError("Register name '%s' is ambiguous (exists in multiple register groups)" % parts[0])
            else:
                raise ValueError("'%s' is not a register group or register" % parts[0])
        elif len(parts) == 3:
            (group, register, field) = parts
            if group in self._register_groups:
                if register in self._register_groups[group]:
                    if field in self._register_groups[group][register]:
                        return self._register_groups[group][register][field]
                    else:
                        raise ValueError("Field '%s' does not exist in register '%s'" % (field, register))
                else:
                    raise ValueError("Register '%s' does not exist in group '%s'" % (register, group))
            else:
                raise ValueError("Register group '%s' does not exist" % group)
        else:
            raise ValueError("'%s' is not a valid register name" % name)

    def read_register(self, name, side_effects=False):
        """
        Read the current value of a register

        :param name:
            The name of the register to read from. This can take the following forms:
                * ``<group>.<register>``
                * ``<group>.<register>.<field>``
                * ``<register>``
                * ``<register>.<field>``

        :param side_effects:

        Raises ValueError if the register name does not exist, or if the group
        name is omitted and there are multiple registers (in different groups)
        with that name.
        """
        return self._get_register_by_name(name).read(side_effects)

    def write_register(self, name, value, side_effects=False):
        """
        Write a value to a register

        :param name:
            The name of the register to read from. This can take the following forms:
                * ``<group>.<register>``
                * ``<group>.<register>.<field>``
                * ``<register>``
                * ``<register>.<field>``

        :param value:
            the value to write to the register

        :param side_effects:

        Raises ValueError if the register name does not exist, or if the group
        name is omitted and there are multiple registers (in different groups)
        with that name.
        """
        self._get_register_by_name(name).write(value, side_effects)

    def get_register_info(self, name=None):
        """
        This method can be used to retrieve information about about the registers
        present in this Target.

        It is used in two ways:
            * ``get_register_info(name)``
                will return the info for the named register
            * ``get_register_info()``
                The function acts as a generator and will yield information about
                all registers.

        :param name:
            The name of the register to provide info for.

            If None, it will yield information about all registers.

            It follows the same rules as the ``name`` parameter of
            :py:meth:`.read_register` and :py:meth:`.write_register`
        """

        def fix_name(info, *names):
            return RegisterInfo('.'.join(names),
                                info.description,
                                info.bits_wide,
                                info.has_side_effects,
                                info.is_compound,
                                info.symbols,
                                info.lsb_offset, 
                                info.type,
                                info.is_readable,
                                info.is_writable)

        def info_generator():
            for group in self._register_groups:
                for register in self._register_groups[group]:
                    info = self._register_groups[group][register].get_info()

                    if register in self._ambiguous_register_names:
                        yield fix_name(info, group, register)
                    else:
                        yield info

                    for field in self._register_groups[group][register]:
                        info = self._register_groups[group][register][field].get_info()

                        if register in self._ambiguous_register_names:
                            yield fix_name(info, group, register, field)
                        else:
                            yield fix_name(info, register, field)


        if name is None:
            return info_generator()
        else:
            return fix_name(self._get_register_by_name(name).get_info(), name)
        


    def _shutdown(self):
        self.__cadi._shutdown = True

    def __repr__(self):
        return "<Target %s>" % self.instance_name
