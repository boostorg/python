#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_deque_plain.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/10/15    rmg     File creation from test_vector_plain.py
#
# $Id$
#

'''>>> from test_deque_ext import *
>>> element_type = int
>>> v = Deque()
>>> v[:] = (6, 7, 8, 5, 4, 8, 3, 1, 2)  # Slice replace (tuple)
>>> print [ x for x in v ]
[6, 7, 8, 5, 4, 8, 3, 1, 2]
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
