#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_python_list.py
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

'''>>> v = []
>>> # Provide a mutable int-like object (same as int_wrapper)
>>> class element_type:
...     def __init__(self, val = 0):
...         self.val = val
...     def increment(self, incr):
...         self.val += incr
...     def __repr__(self):
...         return repr(self.val)
...     def __cmp__(self, other):
...         return self.val.__cmp__(other.val)
...
>>> def increment(element, change = 1):
...     element.increment (change)
...
'''

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))

if __name__ == '__main__':
    import test_python_ref_common   # Checks for python reference semantics
    import test_vector_common
    __doc__ += test_python_ref_common.extended_doctest_string
    __doc__ += test_vector_common.common_doctest_string
    print 'running...'
    import sys
    status = run()[0]
    if (status == 0): print "Done."
    sys.exit(status)
