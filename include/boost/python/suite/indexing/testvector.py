#!/usr/bin/python
# -*- mode:python -*-
#
# Python module testvector.py
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

from testsuite import Vector

v = Vector()

v.append(1)
v.append(2)
v.append(3)

print v[0], v[1], v[2], [x for x in v]

v[1] = 4

print v[0], v[1], v[2], [x for x in v]

print v[0:2]
