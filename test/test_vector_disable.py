# Python module test_vector_disable.py
#
# Copyright (c) 2003 Raoul M. Gough
#
# Use, modification and distribution is subject to the Boost Software
# License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
# at http://www.boost.org/LICENSE_1_0.txt)
#
# History
# =======
# 2003/11/19   rmg     File creation
#
# $Id$
#

'''>>> from test_vector_disable_ext import *
>>> v = Vector_disable()
>>> v.append (1)
>>> v.append (2)
>>> v.append (3)
>>> v.append (4)
>>> del v[0]
>>> print [ x for x in v ]
[2, 3, 4]
>>> v[0] = 5
>>> print [ x for x in v ]
[5, 3, 4]
>>> assert getattr (v, "len", None) == None
>>> assert getattr (v, "sort", None) == None
>>> assert getattr (v, "reverse", None) == None
>>> assert getattr (v, "index", None) == None
>>> assert getattr (v, "count", None) == None
>>> assert getattr (v, "insert", None) == None
>>> assert getattr (v, "extend", None) == None
>>> try:
...     s = v[:]
...     print "__getitem__ supports slices (should be disabled)"
... except TypeError, e:
...     print "Got expected exception"
...
Got expected exception
>>> try:
...     v[:1] = [1]
...     print "__setitem__ supports slices (should be disabled)"
... except TypeError, e:
...     print "Got expected exception"
...
Got expected exception
>>> try:
...     del v[:]
...     print "__delitem__ supports slices (should be disabled)"
... except TypeError, e:
...     print "Got expected exception"
...
Got expected exception
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
