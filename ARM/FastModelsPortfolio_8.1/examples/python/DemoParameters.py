#!/usr/bin/env python

import sys
from fm.debug import *
from pprint import pprint

if len(sys.argv) != 2:
    print "Usage: %s <filename>" % sys.argv[0]
    sys.exit()

# Show all of the parameters of the model which we cas set, and their
# default values. This is an object which acts as a dictionary, but also
# performs some type and range checking
pprint(LibraryModel.get_model_parameters(sys.argv[1]))

# Create a model, specifying one parameter and using defaults for the rest
m = LibraryModel(sys.argv[1], {"visualisation.window_title": "Python!"})
cpu = m.get_cpus()[0]

# only run-time parameters can be edited once the model has been created
print [n for n, p in cpu.parameters.items() if p.isRunTime]

# Change one of the run-time parameters
p = cpu.parameters["min_sync_level"]
print "Min: %d, Max: %d, Current: %d" % (p.minValue, p.maxValue, p)
cpu.parameters["min_sync_level"] = 2
print cpu.parameters["min_sync_level"]
