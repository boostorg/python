#!/usr/bin/python
# -*- mode:python -*-
#
# Python module test_const.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/10/16   rmg     File creation
#
# $Id$
#

'''>>> from test_indexing_const_ext import *
>>> setTrace(False)
>>> v = get_vector()
>>> print [x for x in v]
[8, 6, 4, 2, 1, 3, 5, 7, 0]
>>> print v.index (3)
5
>>> print v.count (0)
1
>>> print v.count (9)
0
'''

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))

if __name__ == '__main__':
    print 'running...'
    import sys
    status = run()[0]
    if (status == 0): print "Done."
    sys.exit(status)
