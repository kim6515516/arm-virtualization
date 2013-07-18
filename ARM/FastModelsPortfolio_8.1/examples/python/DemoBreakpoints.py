#!/usr/bin/env python

import sys
from fm.debug import *
from pprint import pprint

# Some interesting memory locations (dependent on image)
PROG_BPT_ADDR = 0x34
MEM_BPT_ADDR = 0x5c

# Create a model and load the test image
m=LibraryModel(sys.argv[1])
cpu = m.get_cpus()[0]
cpu.load_application("Examples/vectors.axf")

# enable some exception breakpoints
for bpt in cpu.breakpoints.values():
    if bpt.bpt_type == "Register":
        if bpt.register in ("UNDEFINED", "SVC"):
            bpt.enable()

# set a breakpoint on a program memory location
cpu.add_bpt_prog(PROG_BPT_ADDR)

# set a breakpoint on a data memory location, triggered only on write
cpu.add_bpt_mem(MEM_BPT_ADDR, on_read=False)

# Show the breakpoints
# This includes all of the built-in exception breakpoints
pprint(cpu.breakpoints)

# print out the breakpoints that are hit, ending when no breakpoints are hit
# in 1 second
# This should hit, in this order:
#   - SVC breakpoint
#   - Program breakpoint
#   - Memory breakpoint
#   - UNDEFINED breakpoint
#   - No further breakpoints hit
for _ in xrange(5):
    try:
        print m.run(blocking=True, timeout=1)
    except TimeoutError:
        m.stop()
        print "No breakpoint hit"
        break
