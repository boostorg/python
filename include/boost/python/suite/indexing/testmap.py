#!/usr/bin/python
# -*- mode:python -*-
#
# Python module testmap.py
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

from testsuite import Map

m = Map()

m["hello"] = 1
m["there"] = 2

print m["hello"], m["there"]

m["there"] = 3

print m["hello"], m["there"]

try:
    print [x for x in m]

except TypeError, e:
    print "Got semi-expected type error:", e
    pass

try:
    print m["nonesuch"]

except KeyError, e:
    print "Got expected exception:", e
    pass

except Exception, e:
    print "Got semi-expected exception:", e
    pass
