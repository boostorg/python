#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_vector_ref.py
#
# Test the vector container with return_internal_reference
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
# 2003/10/ 1    rmg     File creation
#
# $Id$
#

'''>>> from testlinear import *
>>> setTrace(False)
>>> v = Vector_ref()
>>> v.append (3)
>>> ref = v[0]
>>> print ref, v[0]
3 3
>>> v[0].increment()   # Mutate object in container
>>> print ref, v[0]    # Check reference refers to same object
4 4
>>> for x in v:
...     x.increment()  # Check iterator provides by-ref access
...
>>> print ref, v[0]    # Check mutation happened in container element
5 5
>>> # DO NOT try insert and delete, since the element reference
>>> # would be invalidated by those operations.
>>> del ref            # Avoid dangling reference during subsequent tests
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
