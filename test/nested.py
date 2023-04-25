# Copyright David Abrahams 2004. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
'''
    >>> from nested_ext import *
    
    >>> X
    <class 'nested_ext.X'>
    
    >>> X.__module__
    'nested_ext'
    
    >>> X.__name__
    'X'
    
    >>> X.Y
    <class 'nested_ext.X.Y'>
    
    >>> X.Y.__module__
    'nested_ext'
    
    >>> X.Y.__name__
    'Y'

    >>> X.color.__qualname__
    'X.color'

    >>> repr(X.color.red)
    'nested_ext.X.color.red'

    >>> repr(X.color(1))
    'nested_ext.X.color(1)'

    >>> test_function.__doc__.strip().split('\\n')[0]
    'test_function( (X)arg1, (X.Y)arg2) -> None :'
    
'''

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))
    
if __name__ == '__main__':
    print("running...")
    import sys
    status = run()[0]
    if (status == 0): print("Done.")
    sys.exit(status)
