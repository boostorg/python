#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_python_refs_common.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/10/15   rmg     File creation
#
# $Id$
#

'''>>> print len(v)               # Check container starts off empty
0
>>> v.extend ([element_type(x) for x in [6, 5, 4, 3]])       # Add elements
>>> print [ x for x in v ]
[6, 5, 4, 3]
>>> for x in v:
...     increment(x)              # Check iterator provides by-ref access
...
>>> print [ x for x in v ]        # Check mutation happened in container
[7, 6, 5, 4]
>>> v0 = v[0]                     # Reference to first element
>>> v3 = v[3]                     # Reference to last element
>>> print v0, v[0], v3            # Check reference values
7 7 4
>>> increment(v0)                 # Increment one of the referenced elements
>>> print v0, v[0], v3            # Check reference to same object
8 8 4
>>> v[:0] = [element_type(3)]     # Insert before any referenced elements
>>> print [ x for x in v ]        # Check whole contents
[3, 8, 6, 5, 4]
>>> print v0, v[1], v3            # Check references to original elements
8 8 4
>>> increment(v[1])               # Increment element in container
>>> print v0, v[1], v3            # Check reference to same object
9 9 4
>>> del v[1]                      # Delete element from container
>>> print v0, v[1], v3            # Check old element value copied
9 6 4
>>> print [ x for x in v ]        # Check container contents
[3, 6, 5, 4]
>>> v0 = v[0]                     # Get new reference to first element
>>> print v0, v[0]                # Check matching
3 3
>>> v[0] = element_type(9)        # Overwrite first element
>>> print v0, v[0]                # Check old value copied
3 9
>>> v_slice1 = v[1:3]                          # Slice for v[1] and v[2]
>>> v_slice2 = v[1:3]                          # Same slice again
>>> print v_slice1, v_slice2, v[1], v[2]
[6, 5] [6, 5] 6 5
>>> increment(v[1])                            # Check all refer to same v[1]
>>> print v_slice1, v_slice2, v[1], v[2]
[7, 5] [7, 5] 7 5
>>> increment(v_slice1[1])                     # Check all refer to same v[2]
>>> print v_slice1, v_slice2, v[1], v[2]
[7, 6] [7, 6] 7 6
>>> v[2:2] = [element_type(10)]                # Insert within slice range
>>> print v_slice1, v_slice2, v[1], v[2], v[3]
[7, 6] [7, 6] 7 10 6
>>> v_slice1[1] = element_type(9)              # Replace one reference
>>> print v_slice1, v_slice2, v[1], v[2], v[3] # Check no side-effects
[7, 9] [7, 6] 7 10 6
>>> del v[1:4]                                 # Remove whole slice
>>> print v_slice1, v_slice2, v[1]             # Check reference copies
[7, 9] [7, 6] 4
>>> increment(v_slice1[0])                     # Mutate shared object
>>> print v_slice1, v_slice2, v[1]             # Check reference to same object
[8, 9] [8, 6] 4
>>> v.extend ([element_type(x) for x in [8, 7, 6, 5, 4, 3, -1]]) # New, incl -1
>>> print [ x for x in v ]
[9, 4, 8, 7, 6, 5, 4, 3, -1]
>>> least_element = v[len(v)-1]                # Get proxy for min element
>>> print least_element
-1
>>> v.sort()                                   # Sort min element to front
>>> print [ x for x in v ]
[-1, 3, 4, 4, 5, 6, 7, 8, 9]
>>> print least_element, v[0]                  # Check values match
-1 -1
'''

# It would be nice if sorting the list did not detach any elements
# from a container_proxy, but this is probably not possible to
# guarantee with the current implementation. The problem is that some
# standard libraries apply operator= to the elements during a sort,
# instead of using the overloaded iter_swap. The following extension
# to the test works with container_proxy on MSVC 7.1 and should work
# everywhere with a container of shared pointers or a real Python list

sort_test_extension = \
'>>> increment(v[0])                        # Mutate value in container\n' \
'>>> print least_element, v[0]              # Verify proxy still attached\n' \
'0 0\n'

common_doctest_string = __doc__
extended_doctest_string = common_doctest_string + sort_test_extension
