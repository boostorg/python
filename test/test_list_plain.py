#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_list_plain.py
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

'''>>> from testlinear import *
>>> setTrace(0)
>>> l = List()
>>> assert not 0 in l                    # Search in empty list
>>> l.append (1)                         # Append
>>> l.append (2)
>>> l.append (3)
>>> print [ x for x in l ]               # Iteration
[1, 2, 3]
>>> assert 2 in l                        # Successful search
>>> assert not 4 in l                    # Unsuccessful search
>>> print l.count(3)                     # Found item
1
>>> print l.count(-1)                    # Not found item
0
>>> l.reverse()                          # Reverse
>>> print [ x for x in l ]
[3, 2, 1]
>>> l.sort()                             # Sort
>>> print [ x for x in l ]
[1, 2, 3]
>>> print len(l)                         # Length
3
>>> for x in l:
...     x.increment()                    # Check value semantics
...
>>> print [ x for x in l ]               # Container should be unchanged
[1, 2, 3]
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
    sys.exit(run()[0])
