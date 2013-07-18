#!/usr/bin/env python

import sys
from fm.debug import *
from pprint import pprint

# Create a model
m=LibraryModel(sys.argv[1])
cpu = m.get_cpus()[0]
cpu.load_application("Examples/demo.axf")

# Registers can be accessed with or without specifying the register group,
# as long as the register name is not ambiguous
print cpu.read_register("Core.R0")
print cpu.read_register("R0")

# Read a field of a register
# This could also be accessed as "Core.CPSR.MODE"
# The "MODE" field has a set of values with defined meanings, so this returns "Supervisor"
print cpu.read_register("CPSR.MODE")

# Step over the instruction which sets R0
m.step()
# Change the initial value of R0
# This could also be accessed as "Core.R0"
cpu.write_register("R0", 10)

# Step through the program, showing that the register value changes
for _ in range(15):
    print cpu.read_register("R0")
    m.step(3) # the loop we are stepping through is 3 instructions long
