#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_map_plain.py
#
# Doctest-based testing for a C++ map.
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/10/ 1    rmg     File creation
#
# $Id$
#

'''>>> from testnonlinear import *
>>> setTrace(0)
>>> m = Map()                            # std::map<std::string, int_wrapper>
>>> m["hello"] = 1                       # Insert entry
>>> print m["hello"]                     # Lookup entry
1
>>> m.insert ("Barnaby", 2)
>>> print m["Barnaby"]
2
>>> m["Barnaby"] = 3
>>> print m["Barnaby"]
3
>>> assert m.has_key ("Barnaby")
>>> assert "hello" in m
>>> assert "Barnaby" in m
>>> print m.count ("Barnaby")
1
>>> m.insert ("world", 4)
>>> print m["world"]
4
>>> try:
...     m.insert ("Barnaby", 2)
... except ValueError, e:
...     print "Got expected exception:", e
...
Got expected exception: Map already holds value for insertion
>>> del m["Barnaby"]
>>> try:
...     print m["Barnaby"]
... except ValueError, e:
...     print "Got expected exception:", e
...
Got expected exception: associative container: key not found
>>> try:
...     del m["Barnaby"]
... except ValueError, e:
...     print "Got expected exception:", e
...
Got expected exception: Container does not hold value to be erased
>>> print m["hello"]
1
>>> print m["world"]
4
'''

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))

if __name__ == '__main__':
    print 'running...'
    import sys
    status = run()[0]
    if (status == 0): print "Done."
    sys.exit(status)
