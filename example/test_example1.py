r'''
//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

That's it! If we build this shared library and put it on our PYTHONPATH we can
now access our C++ class and function from Python.

    >>> import hello
    >>> hi_world = hello.world(3)
    >>> hi_world.get()
    'hi, world'
    >>> hello.length(hi_world)
    9

We can even make a subclass of hello.world:


    >>> class my_subclass(hello.world):
    ...     def get(self):
    ...         return 'hello, world'
    ...
    >>> y = my_subclass(2)
    >>> y.get()
    'hello, world'

Pretty cool! You can't do that with an ordinary Python extension type!

    >>> hello.length(y)
    9

Of course, you may now have a slightly empty feeling in the pit of your little
pythonic stomach. Perhaps you feel your subclass deserves to have a length() of
12? If so, read on...
'''
from hello import *

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_example1
    return doctest.testmod(test_example1)
    
if __name__ == '__main__':
    import sys
    sys.exit(run()[0])
