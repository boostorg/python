r'''
    >>> i1 = Int(1)
    >>> i2 = Int(2)
    >>> i = i1 + i2
    >>> i.i()
    3
    >>> i = i1 - i2
    >>> i.i()
    -1
    >>> i = i1 + 5
    >>> i.i()
    6
    >>> i = 3 + i2
    >>> i.i()
    5
    >>> i = i1 - 3
    Traceback (innermost last):
    TypeError: incompatible arguments for -
    >>> i = 3 - i1
    Traceback (innermost last):
    TypeError: incompatible arguments for -
'''

from num import *
import string
import re
import sys

def run(args = None):
    if args is not None:
        sys.argv = args
    import doctest, test_num
    doctest.testmod(test_num)
    
if __name__ == '__main__':
    run()
