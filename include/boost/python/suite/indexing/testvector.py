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

from testsuite import Vector, Vector_ref, setTrace

def test_vector(v):
    v.append(1)
    v.append(2)
    v.append(3)

    print v[0], v[1], v[2], [x for x in v]

    v[1] = 4

    print v[0], v[1], v[2], [x for x in v], v[0:2]

    # Try slice assignment with equal lengths
    v[0:2] = [9, 8]
    print [x for x in v]

    # Try slice assignment with shorter replacement
    v[0:2] = [7]
    print [x for x in v]

    # Try slice assignment with longer replacement
    v[0:1] = [6, 5, 4]
    print [x for x in v]

    # Try element deletion
    del v[0]
    print [x for x in v]

    # Try slice deletion
    del v[0:2]
    print [x for x in v]

    try:
        del v[3]

    except IndexError, e:
        print "Got expected exception:", e

    print [x for x in v]

    del v[0:999]
    print [x for x in v]

    v.append (3)
    print v[0]
    del v[:]
    print [x for x in v]

print "Plain vector:"
print "============="
test_vector (Vector())

print "Ref vector:"
print "==========="
setTrace(0)
test_vector (Vector_ref())
