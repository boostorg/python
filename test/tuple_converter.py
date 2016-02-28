# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
"""
>>> from tuple_converter_ext import *
>>> test_tuple_int((3,))
(3,)
>>> test_tuple_int_string((42, "Foo"))
(42, 'Foo')
>>> try: result = test_tuple_int((5,6))
... except TypeError: pass
... else: print 'expected an exception, got', result, 'instead'

>>> try: result = test_tuple_int_string((5,6))
... except TypeError: pass
... else: print 'expected an exception, got', result, 'instead'

>>> try: result = test_tuple_int_string((5,))
... except TypeError: pass
... else: print 'expected an exception, got', result, 'instead'

"""

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))

if __name__ == '__main__':
    print "running..."
    import sys
    status = run()[0]
    if (status == 0): print "Done."
    sys.exit(status)
