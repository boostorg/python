#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_deque_ref.py
#
# Test the deque container with return_internal_reference
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
# 2003/10/15    rmg     File creation from test_vector_ref.py
#
# $Id$
#

'''>>> from test_deque_ext import *
>>> element_type = int_wrapper
>>> def increment(wrapper, change = 1):
...     wrapper.increment (change)
...
>>> setTrace(False)
>>> v = Deque_ref()
>>> v.append (3)
>>> ref = v[0]
>>> print ref, v[0]
3 3
>>> increment(v[0])    # Mutate object in container
>>> print ref, v[0]    # Check reference refers to same object
4 4
>>> for x in v:
...     increment(x)   # Check iterator provides by-ref access
...
>>> print ref, v[0]    # Check mutation happened in container element
5 5
>>> # DO NOT try insert and delete, since the element reference
>>> # would be invalidated by those operations.
>>> del ref            # Avoid dangling reference during subsequent tests
>>> #### NOTE: test_vector_common gets included after this point ####
'''

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
