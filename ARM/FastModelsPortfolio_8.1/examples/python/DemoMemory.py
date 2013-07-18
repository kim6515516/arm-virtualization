#!/usr/bin/env python

import sys
from fm.debug import *
from pprint import pprint
import struct

m=LibraryModel(sys.argv[1])
cpu = m.get_cpus()[0]
# this image changes the endianness of the processor evey two steps
cpu.load_application("Examples/endian.axf")

# write a string (13 chars) to the target
# NOTE: this does not automatically add a null terminator to the string
cpu.write_memory(0x100, bytearray("Hello, world"))

# Read the string back as bytes, changing endianness
# Note that endianness has no effect
pprint(cpu.read_memory(0x100, count=12))
m.step(2)
pprint(cpu.read_memory(0x100, count=12))
m.step(2)

# Read the string as words.
# Note that endianness is now important
pprint(cpu.read_memory(0x100, count=3, size=4))
m.step(2)
pprint(cpu.read_memory(0x100, count=3, size=4))

# Write a little-endian word to the target, and read it back
cpu.write_memory(0x50, bytearray(struct.pack("<I", 123456)))
print struct.unpack("<I", str(cpu.read_memory(0x50, count=4)))
