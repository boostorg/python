#!/usr/bin/python
# -*- mode:python; switch-modules-target: "indexing.cpp" -*-
#
# Python module testindexing.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# This material is provided "as is", with absolutely no warranty expressed
# or implied. Any use is at your own risk.
#
# Permission to use or copy this software for any non-commercial purpose
# is hereby granted without fee, provided the above notices are retained
# on all copies. Permission to modify the code and to distribute
# modified code for non-commercial purposes is granted, provided the
# above notices are retained, and a notice that the code was modified is
# included with the above copyright notice.
#
# History
# =======
# 2003/ 8/19	rmg	File creation
#
# $Id$
#

from indexing import *

trace(0)

def test_from_empty(v):
#    v.reserve (10);

    print v

    v.append (IntWrapper (1))
    v.append (IntWrapper (2))
    v.append (IntWrapper (3))

    print v[0], v[1], v[2]

    try:
        print v[0], v[1:][0], v[-1:][0]

    except Exception, e:
        print e
        pass

    copy = v[1]

    print "copy is %s, v[1] is %s" % (copy, v[1])
    v[1].increment()
    print "copy is %s, v[1] is %s" % (copy, v[1])
    v[1] = IntWrapper (5)
    print "copy is %s, v[1] is %s" % (copy, v[1])

    slice = v[1:2]
    copy = slice[0]
    print "slice[0] is %s, copy is %s, v[1] is %s" % (slice[0], copy, v[1])
    v[1].increment()
    print "slice[0] is %s, copy is %s, v[1] is %s" % (slice[0], copy, v[1])
    v[1] = IntWrapper (7)
    print "slice[0] is %s, copy is %s, v[1] is %s" % (slice[0], copy, v[1])
    slice[0] = IntWrapper (9)
    print "slice[0] is %s, copy is %s, v[1] is %s" % (slice[0], copy, v[1])

    print "============="

test_from_empty (Vector())
test_from_empty (ProxyVector())
test_from_empty (PointerVector())
test_from_empty ([])
