'''
>>> from callbacks_ext import *

>>> def double(x):
...     return x + x
...
>>> apply_int_int(double, 42)
84
>>> apply_void_int(double, 42)

>>> def identity(x):
...     return x

>>> x = apply_X_X(identity, X(42))
>>> x.value()
42
>>> x_count()
1
>>> del x
>>> x_count()
0

>>> def increment(x):
...     x.set(x.value() + 1)
...
>>> x = X(42)
>>> apply_void_X_ref(increment, x)
>>> x.value()
43
'''

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))
    
if __name__ == '__main__':
    print "running..."
    import sys
    sys.exit(run()[0])
