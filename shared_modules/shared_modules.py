r'''
    >>> import shared
    >>> import m2
    >>> import m1
    >>> ls = shared.Shared()
    >>> ls.name()
    'Shared'
    >>> l1 = m1.M1()
    >>> l1.name()
    'M1'
    >>> l2 = m2.M2()
    >>> l2.name()
    'M2'
    >>> shared.test(ls)
    'Shared'
    >>> shared.test(l1)
    'M1'
    >>> shared.test(l2)
    'M2'
    >>> 
    >>> m1.test(ls)
    'Shared'
    >>> m1.test(l1)
    'M1'
    >>> m1.test(l2)
    'M2'
'''

import string
import re
import sys

def run(args = None):
    if args is not None:
        sys.argv = args
    import doctest, shared_modules
    doctest.testmod(shared_modules)
    
if __name__ == '__main__':
    run()
