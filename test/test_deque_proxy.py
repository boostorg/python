#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_deque_proxy.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/10/15    rmg     File creation from test_vector_proxy.py
#
# $Id$
#

'''>>> from test_deque_ext import *
>>> element_type = int_wrapper
>>> def increment(wrapper, change = 1):
...     wrapper.increment (change)
...
>>> setTrace(False)
>>> v = Deque_proxy()
>>> #### NOTE: test_python_ref, test_vector_common included after this ####
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
    __doc__ += test_python_ref_common.common_doctest_string
    __doc__ += test_vector_common.common_doctest_string
    print 'running...'
    import sys
    status = run()[0]
    if (status == 0): print "Done."
    sys.exit(status)
