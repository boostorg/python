"""
>>> from slice_ext import *
>>> accept_slice(slice(1, None, (1,2)))
1
>>> try:
...     accept_slice(list((1,2)))
...     print "test failed"
... except:
...     print "test passed"
...
test passed
>>> have_numeric = 0
>>> try:
...     from Numeric import array
...     have_numeric = 1
... except:
...     pass
...
>>> try:
...     from numarray import array
...     have_numeric = 1
... except:
...     pass
...
>>> if have_numeric:
...     check_numeric_array_rich_slice()
... else:
...     print 1
...
1
>>> import sys
>>> if sys.version_info[0] == 2 and sys.version_info[1] >= 3:
...     check_string_rich_slice()
... elif sys.version_info[0] > 2:
...     check_string_rich_slice()
... else:
...     print 1
...
1
>>> check_slice_get_indicies( slice(None))
0
>>> check_slice_get_indicies( slice(2,-2))
0
>>> check_slice_get_indicies( slice(2, None, 2))
5
>>> check_slice_get_indicies( slice(2, None, -1))
-12
>>> check_slice_get_indicies( slice( 20, None))
0
>>> check_slice_get_indicies( slice( -2, -5, -2))
6
"""

# Performs an affirmative and negative argument resolution check,
# checks the operation of extended slicing in Numeric arrays
#   (only performed if Numeric.array or numarray.array can be found).
# checks the operation of extended slicing in new strings (Python 2.3 only).

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
