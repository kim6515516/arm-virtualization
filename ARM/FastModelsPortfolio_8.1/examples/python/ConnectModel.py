#!/usr/bin/env python

import sys
from fm.debug import *

if len(sys.argv) != 3:
    print "Usage: %s <hostname> <port>" % sys.argv[0]
    sys.exit()

m = NetworkModel(sys.argv[1], int(sys.argv[2]))

