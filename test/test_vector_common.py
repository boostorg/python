#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_vector_common.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/ 9/29    rmg     File creation
#
# $Id$
#

'''>>> del v[:]                      # Clear container if ncessary
>>> del v[:]                         # Check slice delete on empty container
>>> print v[:]                       # Check slice get on empty container
[]
>>> v[:] = []                        # Check slice set on empty container
>>> print [ x for x in v ]           # Iterate over empty container
[]
>>> try:
...    print v.index (element_type(2))  # Search in empty container
... except ValueError, e:
...    print "Got expected exception"
...
Got expected exception
>>> print v.count (element_type(2))  # Search in empty container
0
>>> print len(v)                     # Length of empty container
0
>>> v.extend ([ element_type(x) for x in [1, 3, 5, 2, 4, 6]]) # Extend via list
>>> print len(v)                     # Length of non-empty container
6
>>> print [ x for x in v ]           # Iteration
[1, 3, 5, 2, 4, 6]
>>> v.reverse()                      # Reverse
>>> print [ x for x in v ]
[6, 4, 2, 5, 3, 1]
>>> v.sort()                         # Sort
>>> print [ x for x in v ]
[1, 2, 3, 4, 5, 6]
>>> v[:] = [element_type(3), element_type(4)]    # Remove dep. on prior results
>>> v.insert (0, element_type(2))    # Insert at start
>>> print [ x for x in v ]
[2, 3, 4]
>>> v.insert (len(v), element_type(5))  # Insert at end
>>> print [ x for x in v ]
[2, 3, 4, 5]
>>> v.insert (999, element_type(6))  # Insert at end (out of bounds)
>>> print [ x for x in v ]
[2, 3, 4, 5, 6]
>>> v.insert (-1, element_type(1))   # Insert at beginning (-ve)
>>> print [ x for x in v ]
[1, 2, 3, 4, 5, 6]
>>> v.append (element_type(7))       # Append
>>> print [ x for x in v ]
[1, 2, 3, 4, 5, 6, 7]
>>> v.extend ([element_type(x) for x in [3,8,9,10]])    # Extend
>>> print [ x for x in v ]
[1, 2, 3, 4, 5, 6, 7, 3, 8, 9, 10]
>>> del v[2]                         # Single element delete
>>> print [ x for x in v ]
[1, 2, 4, 5, 6, 7, 3, 8, 9, 10]
>>> del v[-2:]                       # Delete slice (one negative index)
>>> print [ x for x in v ]
[1, 2, 4, 5, 6, 7, 3, 8]
>>> v[-2:-1] = []                    # Delete slice via __setitem__
>>> print [ x for x in v ]
[1, 2, 4, 5, 6, 7, 8]
>>> v [-2:-1] = [9, 10]              # Replace and insert via slice
>>> print [ x for x in v ]
[1, 2, 4, 5, 6, 9, 10, 8]
>>> try:
...     del v[len(v)]                # Delete element index out of range
... except IndexError, e:
...     print "Got expected exception"
...
Got expected exception
>>> try:
...     del v[-(len(v) + 2)]         # Delete negative index out of range
... except IndexError, e:
...     print "Got expected exception"
...
Got expected exception
>>> v.insert (len(v) + 1, element_type(0))  # Insert at end via out of range
>>> print [ x for x in v ]
[1, 2, 4, 5, 6, 9, 10, 8, 0]
>>> v.insert (-1, element_type(7))          # Insert at beginning via negative
>>> print [ x for x in v ]
[7, 1, 2, 4, 5, 6, 9, 10, 8, 0]
>>> # Prepare for common array tests
>>> v[:] = [element_type(x) for x in [8, 6, 4, 2, 1, 3, 5, 7, 0]]
'''

import test_array_common

common_doctest_string = __doc__ + test_array_common.common_doctest_string
