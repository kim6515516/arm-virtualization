#!/usr/bin/env python
# \file    Register.py
# \brief   High level Python interface to CADI models.
# \date    Copyright 2011-2013 ARM Limited. All rights reserved.

import CADI
import Exceptions
from struct import pack_into, unpack
from collections import namedtuple


RegisterInfo = namedtuple("RegisterInfo", ['name', 'description', 'bits_wide',
                                           'has_side_effects', 'is_compound',
                                           'symbols', 'lsb_offset', 'type',
                                           'is_readable', 'is_writable'])

class Register(dict):
    """
    Provides an interface to a register in a CADI target.
    """

    def __init__(self, cadi, regInfo):
        self._info = regInfo
        self.__cadi = cadi
        self.__reg_count = (self._info.bitsWide + 127) / 128
        self.__width_in_bytes = (self._info.bitsWide + 7) / 8
        self.__conversion_str = None
        self.__type_str = None
        if self._info.display == CADI.CADI_REGTYPE_BOOL:
            self.__conversion_str = "<?"
            self.__type_str = "bool"
        elif self._info.display == CADI.CADI_REGTYPE_FLOAT:
            self.__type_str = "float"
            if self.__width_in_bytes == 4:
                self.__conversion_str = "<f"
            elif self.__width_in_bytes == 8:
                self.__conversion_str = "<d"
        elif self._info.display == CADI.CADI_REGTYPE_SYMBOL:
            self.__type_str = "string"
            self.__symbols = self._info.symbols.get_list()
        elif self._info.display == CADI.CADI_REGTYPE_STRING:
            self.__type_str = "string"
        elif self._info.display == CADI.CADI_REGTYPE_INT:
            self.__type_str = "int"
            if self.__width_in_bytes == 1:
                self.__conversion_str = "<b"
            elif self.__width_in_bytes == 2:
                self.__conversion_str = "<h"
                self.__conversion_str = "<i"
            elif self.__width_in_bytes == 8:
                self.__conversion_str = "<q"
        else: # uint for everything else
            self.__type_str = "int"
            if self.__width_in_bytes == 1:
                self.__conversion_str = "<B"
            elif self.__width_in_bytes == 2:
                self.__conversion_str = "<H"
            elif self.__width_in_bytes == 4:
                self.__conversion_str = "<I"
            elif self.__width_in_bytes == 8:
                self.__conversion_str = "<Q"
            elif self.__width_in_bytes == 0:
                # this happens with the vector-breakpoint fake registers on v8A
                self.__conversion_str = ""
        if self._info.display == CADI.CADI_REGTYPE_HEX:
            self.__format_str = "0x%%0.%iX" % (self.__width_in_bytes * 2)

    def read(self, sideEffects=False):
        """
        Read the contents of the register and attempt to convert it to an
        appropriate format according to CADIRegInfo.display.
        If the value cannot be converted to an appropriate format the
        register contents will be returned as a bytearray.
        """

        reg = [CADI.CADIReg(self._info.regNumber, 0, i, False, self._info.attribute)
               for i in xrange(self.__reg_count)]
        reg = self.__cadi.CADIRegRead(reg, sideEffects)
        bytes_to_read = self.__width_in_bytes
        if self._info.display == CADI.CADI_REGTYPE_SYMBOL:
            bytes_to_read = 4
        full_array = b"".join([str(r.bytes) for r in reg])[0:bytes_to_read]
        if self.__conversion_str != None:
            if self.__conversion_str == "":
                # this happens with the vector-breakpoint fake registers on v8A
                return 0
            else:
                return unpack(self.__conversion_str, full_array)[0]
        elif self._info.display == CADI.CADI_REGTYPE_SYMBOL:
            index = unpack("<I", full_array)[0]
            return self.__symbols[index]
        elif self._info.display == CADI.CADI_REGTYPE_STRING:
            return full_array
        else:
            return bytearray(full_array)

    def write(self, value, sideEffects=False):
        """
        Write a new value to the register. The value may be a bytearray or
        a value appropriate to the register type.
        """

        reg = [CADI.CADIReg(self._info.regNumber, 0, i, False, self._info.attribute)
               for i in xrange(self.__reg_count)]
        full_array = bytearray(self.__reg_count * 16)
        if isinstance(value, bytearray):
            full_array[0:len(value)] = value
        elif self.__conversion_str != None:
            if self.__conversion_str != "":
                pack_into(self.__conversion_str, full_array, 0, value)
        elif self._info.display == CADI.CADI_REGTYPE_SYMBOL:
            if value not in self.__symbols:
                raise ValueError("\"%s\" is not a valid symbol for register %s" % self._info.name)
            pack_into("<I", full_array, 0, self.__symbols.index(value))
        elif self._info.display == CADI.CADI_REGTYPE_STRING:
            full_array[0:len(value)] = value
        else:
            raise TypeError("Expecting a bytearray or %s" % self.__type_str)
        offset = 0
        for r in reg:
            r.bytes = full_array[offset:(offset + 16)]
            offset += 16
        self.__cadi.CADIRegWrite(reg, sideEffects)

    def get_info(self):
        reg_type = { CADI.CADI_REGTYPE_HEX : int,
                     CADI.CADI_REGTYPE_UINT : int,
                     CADI.CADI_REGTYPE_INT : int,
                     CADI.CADI_REGTYPE_BOOL : bool,
                     CADI.CADI_REGTYPE_FLOAT : float,
                     CADI.CADI_REGTYPE_SYMBOL : str,
                     CADI.CADI_REGTYPE_STRING : str,
                     CADI.CADI_REGTYPE_PC : int,
                     CADI.CADI_REGTYPE_BIN : int,
                     CADI.CADI_REGTYPE_OCT : int,
        }[self._info.display]

        readable = self._info.attribute in (CADI.CADI_REG_READ_WRITE,
                                            CADI.CADI_REG_READ_ONLY,
                                            CADI.CADI_REG_READ_ONLY_RESTRICTED)

        writable = self._info.attribute in (CADI.CADI_REG_READ_WRITE,
                                            CADI.CADI_REG_WRITE_ONLY,
                                            CADI.CADI_REG_WRITE_ONLY_RESTRICTED)

        return RegisterInfo(self._info.name,
                            self._info.description,
                            self._info.bitsWide,
                            self._info.hasSideEffects == 1,
                            self._info.get_details().type == CADI.CADI_REGTYPE_Compound,
                            self._info.symbols.get_list(),
                            self._info.lsbOffset,
                            reg_type,
                            readable,
                            writable)


    def __str__(self):
        """
        Read the register and convert to an appropriate string determined by
        reading Register.info.display.
        """

        if self.get_info().is_readable:
            val = self.read()
        else:
            val = '<write-only>'
        if type(val) == int:
            if self._info.display == CADI.CADI_REGTYPE_HEX:
                return self.__format_str % val
            elif self._info.display == CADI.CADI_REGTYPE_OCT:
                return oct(val)
            elif self._info.display == CADI.CADI_REGTYPE_BIN:
                return bin(val)
        return str(val)

    def __repr__(self):
        return "<Register name=%s value=%s>" % (self._info.name, str(self))
