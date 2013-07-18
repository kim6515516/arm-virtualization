#!/usr/bin/env python

import sys
from fm.debug import *
from pprint import pprint

m=LibraryModel(sys.argv[1])
cpu = m.get_cpus()[0]

# This image first reads from the semihosting input, causing it to block until
# a character is sent to stdin. Then it prints "Hello, world!" to the
# semihosting output, then uses a semihosting call to terminate the simulation.
cpu.load_application("Examples/semihosting.axf")

# Bind the semihosting stdin and stdout to this processes' stdin and stdout
cpu.stdout = sys.stdout
cpu.stdin = sys.stdin

print "Press enter to send semihosting input to the target"
m.run()

