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
import sys

setTrace(0)

if hasattr(sys, "gettotalrefcount"):
    def dumper() : print "refcount:", sys.gettotalrefcount()

    maybe_dump_refcount = dumper
else:
    def dumper() : pass

    maybe_dump_refcount = dumper

def test_from_empty(v, outfile = sys.stdout):
#    v.reserve (10);

    print >> outfile, v

    v.append (IntWrapper (1))
    v.append (IntWrapper (2))
    v.append (IntWrapper (3))

    print >> outfile, v[0], v[1], v[2]

    try:
        print >> outfile, v[0], v[1:][0], v[-1:][0]

    except Exception, e:
        print >> outfile, e
        pass

    copy = v[1]

    print >> outfile, "copy is %s, v[1] is %s" % (copy, v[1])
    v[1].increment()
    print >> outfile, "copy is %s, v[1] is %s" % (copy, v[1])
    v[1] = IntWrapper (5)
    print >> outfile, "copy is %s, v[1] is %s" % (copy, v[1])

    slice = v[1:2]
    copy = slice[0]
    print >> outfile, "slice[0] is %s, copy is %s, v[1] is %s" % (slice[0], copy, v[1])
    v[1].increment()
    print >> outfile, "slice[0] is %s, copy is %s, v[1] is %s" % (slice[0], copy, v[1])
    v[1] = IntWrapper (7)
    print >> outfile, "slice[0] is %s, copy is %s, v[1] is %s" % (slice[0], copy, v[1])
    slice[0] = IntWrapper (9)
    print >> outfile, "slice[0] is %s, copy is %s, v[1] is %s" % (slice[0], copy, v[1])

#     if hasattr(sys, "gettotalrefcount"):
#         for x in range(20):
#             v[:] = [1,2,3,4]
#         maybe_dump_refcount()

#         for x in range(9):
#             v[:] = [1,2,3,4]
#         maybe_dump_refcount()

    print >> outfile, "============="

#test_from_empty (Vector_proxy())

class write_eater:
    def write (self, str):
        pass

# Run everything through once to settle reference counters
test_from_empty (Vector(), write_eater())
test_from_empty (ProxyVector(), write_eater())
test_from_empty (PointerVector(), write_eater())
test_from_empty ([], write_eater())

# Run again with output (and ref-count dumping, if possible)
maybe_dump_refcount()

test_from_empty (Vector())
maybe_dump_refcount()

test_from_empty (ProxyVector())
maybe_dump_refcount()

test_from_empty (PointerVector())
maybe_dump_refcount()

test_from_empty ([])
maybe_dump_refcount()
