#!/bin/sh 
#
# Create links to make use of the FLEXlm tools easier.
#
# Copyright (c) ARM Limited 2000, 2002. All rights reserved
#

PATH=/usr/ucb:/usr/bin:/bin; export PATH

rm -f lmhostid lmver lmcksum lmdown lmremove lmreread lmswitchr lmstat lmdiag lminstall lmpath lmborrow lmswitch

ln lmutil lmhostid
ln lmutil lmver
ln lmutil lmcksum
ln lmutil lmdown
ln lmutil lmremove
ln lmutil lmreread
ln lmutil lmswitchr
ln lmutil lmstat
ln lmutil lmdiag
ln lmutil lminstall
ln lmutil lmpath
ln lmutil lmborrow
ln lmutil lmswitch

