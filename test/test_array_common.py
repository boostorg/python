#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_array_common.py
#
# Shared doctest sequence for use with any array-based container
# (including vectors). Performs tests that do not require insertion or
# deletion.
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

#
# Note - on entry, v must be the container for testing, and it
# must already contain the correct sequence of elements.
#

'''>>> print [ x for x in v ]
[8, 6, 4, 2, 1, 3, 5, 7, 0]
>>> print len(v)
9
>>> print v.count (9)                # Count with no matches
0
>>> print v.count (2)                # Count with unique match
1
>>> print v.index (0)                # Index with match
8
>>> assert 0 in v                    # contains with match
>>> assert 8 in v                    # contains with match
>>> assert not -1 in v               # contains without match
>>> print v[0]                       # Get first element OK (zero index)
8
>>> print v[len(v)-1]                # Get last element OK (+ve index)
0
>>> print v[-1]                      # Get last element OK (-ve index)
0
>>> print v[-len(v)]                 # Get first element OK (-ve index)
8
>>> v[0] = 9                         # Replace first element OK (zero index)
>>> print [ x for x in v ]
[9, 6, 4, 2, 1, 3, 5, 7, 0]
>>> v[len(v)-1] = 1                  # Replace last element OK (+ve index)
>>> print [ x for x in v ]
[9, 6, 4, 2, 1, 3, 5, 7, 1]
>>> v[-1] = 0                        # Replace last element OK (-ve index)
>>> print [ x for x in v ]
[9, 6, 4, 2, 1, 3, 5, 7, 0]
>>> v[-len(v)] = 8                   # Replace first element OK (-ve index)
>>> print [ x for x in v ]
[8, 6, 4, 2, 1, 3, 5, 7, 0]
>>> try:
...     print v[len(v)]              # Get element index out of range
... except IndexError, e:
...     print "Got expected exception"
...
Got expected exception
>>> try:
...     print v[-(len(v)+1)]         # Get element index out of range (-ve)
... except IndexError, e:
...     print "Got expected exception"
...
Got expected exception
>>> try:
...     v[len(v)] = 9                # Set element index out of range
... except IndexError, e:
...     print "Got expected exception"
...
Got expected exception
>>> try:
...    print v.index (9)             # Search for nonexistant value
... except ValueError, e:
...    print "Got expected exception"
...
Got expected exception
>>> v.reverse()                      # Reverse
>>> print [ x for x in v ]
[0, 7, 5, 3, 1, 2, 4, 6, 8]
>>> v.sort()                         # Sort
>>> print [ x for x in v ]
[0, 1, 2, 3, 4, 5, 6, 7, 8]
>>> v[0] = 8                         # Single element replace
>>> print v.count(8)                 # Count with multiple matches
2
>>> print v[v.index(3)]              # Check index and lookup
3
>>> v[:] = [4, 5, 6, 7, 8, 8, 1, 2, 3]  # Equal length slice replace (list)
>>> print [ x for x in v ]
[4, 5, 6, 7, 8, 8, 1, 2, 3]
>>> print [ x for x in v[7:] ]       # Slice from index to end
[2, 3]
>>> print [ x for x in v[-2:] ]      # Slice from two before end to end
[2, 3]
>>> print [ x for x in v[-2:99999] ] # Slice with high end index
[2, 3]
>>> print [ x for x in v[99999:] ]   # Slice with high start index
[]
'''

common_doctest_string = __doc__
