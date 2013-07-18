#!/usr/bin/env python

import sys
from fm.debug import *

if len(sys.argv) != 2:
    print "Usage: %s <filename>" % sys.argv[0]
    sys.exit()

m=LibraryModel(sys.argv[1])

