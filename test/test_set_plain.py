#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_set_plain.py
#
# Doctest-based testing for a C++ set.
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
>>> s = Set()                            # std::set<std::string>
>>> s.insert("hello")                    # Insert entry
>>> print s["hello"]                     # Lookup entry
hello
>>> s.insert ("Barnaby")                 # Insert another entry
>>> print s["Barnaby"]                   # Lookup entry
Barnaby
>>> assert s.has_key ("Barnaby")
>>> assert not s.has_key ("Rudge")
>>> assert "hello" in s
>>> assert "Barnaby" in s
>>> print s.count ("Barnaby")
1
>>> s.insert ("world")
>>> print s["world"]
world
>>> try:
...     s.insert ("Barnaby")
... except ValueError, e:
...     print "Got expected exception:", e
...
Got expected exception: Set already holds value for insertion
>>> del s["Barnaby"]
>>> try:
...     print s["Barnaby"]
... except ValueError, e:
...     print "Got expected exception:", e
...
Got expected exception: associative container: key not found
>>> try:
...     del s["Barnaby"]
... except ValueError, e:
...     print "Got expected exception:", e
...
Got expected exception: Container does not hold value to be erased
>>> print s["hello"]
hello
>>> print s["world"]
world
>>> print [ x for x in s ]
['hello', 'world']
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
