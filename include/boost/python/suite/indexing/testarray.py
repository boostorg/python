#!/usr/bin/python
# -*- mode:python -*-
#
# Python module testarray.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# This material is provided "as is", with absolutely no warranty expressed
# or implied. Any use is at your own risk.
#
# Permission to use or copy this material for any purpose is hereby
# granted without fee, provided the above notices are retained on all
# copies.  Permission to modify the material and to distribute modified
# versions is granted, provided the above notices are retained, and a
# notice that the material was modified is included with the above
# copyright notice.
#
# History
# =======
# 2003/ 9/ 9	rmg	File creation
#
# $Id$
#

from testsuite import Array, getArray

a = getArray()

print a[0], a[1], a[2], [x for x in a], a[0:-2], a[-1:-3:-1], a[0:54:0]

a[1] = 4

print a[0], a[1], a[2], [x for x in a], a[0:-2], a[-1:-3:-1]

print a[0:43]
