#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_vector_proxy.py
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

'''>>> from testlinear import *
>>> setTrace(False)
>>> v = Vector_proxy()
>>> v.extend ([6, 5, 4, 3])
>>> print [ x for x in v ]
[6, 5, 4, 3]
>>> for x in v:
...     x.increment()             # Check iterator provides by-ref access
...
>>> print [ x for x in v ]        # Check mutation happened in container
[7, 6, 5, 4]
>>> v0 = v[0]                     # Reference to first element
>>> v3 = v[3]                     # Reference to last element
>>> print v0, v[0], v3            # Check reference values
7 7 4
>>> v0.increment()                # Increment one of the referenced elements
>>> print v0, v[0], v3            # Check reference to same object
8 8 4
>>> v[:0] = [3]                   # Insert before any referenced elements
>>> print [ x for x in v ]        # Check whole contents
[3, 8, 6, 5, 4]
>>> print v0, v[1], v3            # Check references to original elements
8 8 4
>>> v[1].increment()              # Increment element in container
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
>>> v[0] = 9                      # Overwrite first element
>>> print v0, v[0]                # Check old value copied
3 9
>>> v_slice1 = v[1:3]                          # Slice for v[1] and v[2]
>>> v_slice2 = v[1:3]                          # Same slice again
>>> print v_slice1, v_slice2, v[1], v[2]
[6, 5] [6, 5] 6 5
>>> v[1].increment()                           # Check all refer to same v[1]
>>> print v_slice1, v_slice2, v[1], v[2]
[7, 5] [7, 5] 7 5
>>> v_slice1[1].increment()                    # Check all refer to same v[2]
>>> print v_slice1, v_slice2, v[1], v[2]
[7, 6] [7, 6] 7 6
>>> v[2:2] = [10]                              # Insert within slice range
>>> print v_slice1, v_slice2, v[1], v[2], v[3]
[7, 6] [7, 6] 7 10 6
>>> v_slice1[1] = 9                            # Replace one reference
>>> print v_slice1, v_slice2, v[1], v[2], v[3] # Check no side-effects
[7, 9] [7, 6] 7 10 6
>>> del v[1:4]                                 # Remove whole slice
>>> print v_slice1, v_slice2, v[1]             # Check reference copies
[7, 9] [7, 6] 4
>>> v_slice1[0].increment()                    # Mutate shared object
>>> print v_slice1, v_slice2, v[1]             # Check reference to same object
[8, 9] [8, 6] 4
>>> v.extend ([8, 7, 6, 5, 4, 3, -1])          # Add new values, including -1
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

# It would be nice if sorting the list did not detach any existing
# proxies, but this is probably not possible to guarantee with the
# current implementation. The overload of iter_swap is sufficient with
# some standard libraries, but not others. The following test works
# only on MSVC so far.

#
# >>> v[0].increment()                           # Mutate value in container
# >>> print least_element, v[0]                  # Verify proxy still attached
# 0 0
#

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))

if __name__ == '__main__':
    from test_vector_common import common_doctest_string
    __doc__ += common_doctest_string
    print 'running...'
    import sys
    status = run()[0]
    if (status == 0): print "Done."
    sys.exit(status)
