#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_array_ref.py
#
# Test the array container with return_internal_reference
# policies. This is a dangerous container - see the container suite
# documentation on using policies for details.
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/10/15    rmg     File creation from test_vector_ref.py and test_array.py
#
# $Id$
#

'''>>> from test_array_ext import *
>>> element_type = int_wrapper
>>> def increment(wrapper, change = 1):
...     wrapper.increment (change)
...
>>> setTrace(False)
>>> v = get_array_wrap ()
>>> ref = v[0]
>>> print ref, v[0]
8 8
>>> increment (v[0])   # Mutate object in container
>>> print ref, v[0]    # Check reference refers to same object
9 9
>>> for x in v:
...     increment(x)   # Check iterator provides by-ref access
...
>>> print ref, v[0]    # Check mutation happened in container element
10 10
>>> print [ x for x in v ]   # Check other elements mutated as well
[10, 7, 5, 3, 2, 4, 6, 8, 1]
>>> v[:] = [ 8, 6, 4, 2, 1, 3, 5, 7, 0 ] # Return array to original state
>>> #### NOTE: test_array_common gets included after this point ####
'''

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))

if __name__ == '__main__':
    from test_array_common import common_doctest_string
    __doc__ += common_doctest_string
    print 'running...'
    import sys
    status = run()[0]
    if (status == 0): print "Done."
    sys.exit(status)
