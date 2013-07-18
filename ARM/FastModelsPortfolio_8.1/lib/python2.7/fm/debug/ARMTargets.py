#!/usr/bin/env python
# \file    ARMTargets.py
# \brief   Extensions to the Target class, adding functionality specific to ARM cores
# \date    Copyright 2013 ARM Limited. All rights reserved.

from Target import Target
from warnings import warn


class TargetARM(Target):
    """Target-specific code used by all ARM cores"""

    def _add_alias(self, existing_mem_space, new_mem_space, fatal=False):
        if existing_mem_space in self._memory_spaces_by_name:
            self._memory_spaces_by_name[new_mem_space] = self._memory_spaces_by_name[existing_mem_space]
        elif fatal:
            raise ValueError("Target has no '%s' memory space" % existing_mem_space)


class TargetV7A(TargetARM):
    """Target-specific code for ARM v7A cores"""

    def __init__(self, cadi, model):
        try:
            Target.__init__(self, cadi, model)
            self._add_alias("Normal", "N", True)
            self._add_alias("Secure", "S")
            self._add_alias("NS Hyp", "H")
            self._add_alias("Physical Memory (Non Secure)", "NP")
            self._add_alias("Physical Memory (Secure)", "SP")
        except:
            self._disconnect_callbacks()
            raise

    def _get_default_memory_space(self):
        MONITOR_MODE = 0b10110
        HYPERVISOR_MODE = 0b11010

        cpsr_mode = self.read_register("Core.CPSR") & 0b11111

        if cpsr_mode == MONITOR_MODE:
            return self._memory_spaces_by_name["Secure"]
        elif cpsr_mode == HYPERVISOR_MODE:
            return self._memory_spaces_by_name["NS Hyp"]
        else:
            if self.hasSecurityExtensions:
                if (self.__read_SCR() & 1) == 0:
                    return self._memory_spaces_by_name["Secure"]
                else:
                    return self._memory_spaces_by_name["Normal"]
            else:
                self._memory_spaces_by_name["Normal"]

    def __read_PFR1(self):
        """Read processor feature register 1"""
        try:
            return self.read_register("ID.ID_PFR1")
        except ValueError:
            return self.read_register("ID.CP15_ID_PFR1")

    def __read_SCR(self):
        """Read security control register"""
        try:
            return self.read_register("Control.CP15_SECURE_CONFIGURATION")
        except ValueError:
            return self.read_register("Secure World.SCR")

    @property
    def hasSecurityExtensions(self):
        return (self.__read_PFR1() & 0xF0) != 0

    @property
    def hasVirtualizationExtensions(self):
        return (self.__read_PFR1() & 0xF000) != 0


class TargetV7RM(TargetARM):
    """Target-specific code for ARM v7R and v7M cores"""

    def __init__(self, cadi, model):
        try:
            Target.__init__(self, cadi, model)
            self._add_alias("Memory", "N", True)
            self._add_alias("Physical Memory", "NP", True)
        except:
            self._disconnect_callbacks()
            raise

    def _get_default_memory_space(self):
        return self._memory_spaces_by_name["Memory"]

    @property
    def hasSecurityExtensions(self):
        return False

    @property
    def hasVirtualizationExtensions(self):
        return False


class TargetV56(TargetARM):
    """Target-specific code for ARM v5 and v6 cores without security extensions"""

    def __init__(self, cadi, model):
        try:
            Target.__init__(self, cadi, model)
            self._add_alias("Memory", "N", True)
            self._add_alias("Physical Memory", "NP", True)
        except:
            self._disconnect_callbacks()
            raise

    def _get_default_memory_space(self):
        return self._memory_spaces_by_name["Memory"]

    @property
    def hasSecurityExtensions(self):
        return False

    @property
    def hasVirtualizationExtensions(self):
        return False


class TargetV6Secure(TargetARM):
    """Target-specific code for ARM v6 cores with security extensions"""

    def __init__(self, cadi, model):
        try:
            Target.__init__(self, cadi, model)

            self._add_alias("Normal", "N", True)
            self._add_alias("Secure", "S", True)
            self._add_alias("Physical Memory (Non Secure)", "NP")
            self._add_alias("Physical Memory (Secure)", "SP")
        except:
            self._disconnect_callbacks()
            raise

    def _get_default_memory_space(self):
        MONITOR_MODE = 0b10110

        cpsr_mode = self.read_register("Core.CPSR") & 0b11111

        if cpsr_mode == MONITOR_MODE:
            return self._memory_spaces_by_name["Secure"]
        else:
            if self.hasSecurityExtensions:
                if (self.__read_SCR() & 1) == 0:
                    return self._memory_spaces_by_name["Secure"]
                else:
                    return self._memory_spaces_by_name["Normal"]
            else:
                self._memory_spaces_by_name["Normal"]

    def __read_SCR(self):
        """Read security control register"""
        return self.read_register("Control.CP15_SECURE_CONFIGURATION")

    @property
    def hasSecurityExtensions(self):
        return True

    @property
    def hasVirtualizationExtensions(self):
        return False


class TargetV8A(TargetARM):
    """Target-specific code for ARM v8A cores"""

    def __init__(self, cadi, model):
        try:
            Target.__init__(self, cadi, model)

            self._add_alias("Guest", "N", True)
            self._add_alias("Secure Monitor", "S")
            self._add_alias("NS Hyp", "H")
            self._add_alias("Physical Memory (Non Secure)", "NP")
            self._add_alias("Physical Memory (Secure)", "SP")
        except:
            self._disconnect_callbacks()
            raise

    def _get_default_memory_space(self):
        AARCH32_MONITOR_MODE = 0b10110
        AARCH32_HYPERVISOR_MODE = 0b11010

        cpsr_mode = self.read_register("AArch64 Core.CPSR") & 0b11111

        if (cpsr_mode & 0b10000) != 0:
            # AArch64
            exception_level = (cpsr_mode & 0b01100) >> 2
            if exception_level == 2:
                # EL2 = hypervisor
                return self._memory_spaces_by_name["NS Hyp"]
            elif exception_level == 3:
                # EL3 = secure monitor
                return self._memory_spaces_by_name["Secure Monitor"]
            else:
                # EL0/1 = user/kernel
                if self.hasSecurityExtensions and (self.__read_SCR() & 1) == 0:
                    return self._memory_spaces_by_name["Secure Monitor"]
                else:
                    self._memory_spaces_by_name["Guest"]
        else:
            # AArch32
            if cpsr_mode == AARCH32_MONITOR_MODE:
                return self._memory_spaces_by_name["Secure Monitor"]
            elif cpsr_mode == AARCH32_HYPERVISOR_MODE:
                return self._memory_spaces_by_name["NS Hyp"]
            else:
                if self.hasSecurityExtensions and (self.__read_SCR() & 1) == 0:
                    return self._memory_spaces_by_name["Secure Monitor"]
                else:
                    self._memory_spaces_by_name["Guest"]

    def __read_PFR1(self):
        """Read processor feature register 1"""
        return self.read_register("AArch64 System.ID_PFR1_EL1")

    def __read_SCR(self):
        """Read security control register"""
        return self.read_register("AArch64 System.SCR_EL3")

    @property
    def hasSecurityExtensions(self):
        return (self.__read_PFR1() & 0xF0) != 0

    @property
    def hasVirtualizationExtensions(self):
        return (self.__read_PFR1() & 0xF000) != 0
