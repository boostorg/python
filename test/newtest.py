"""
>>> from m1 import *

>>> from m2 import *

>>> n = new_noddy()
>>> s = new_simple()
>>> unwrap_int(n)
42
>>> unwrap_int_ref(n)
42
>>> unwrap_int_const_ref(n)
42
>>> unwrap_simple(s)
'hello, world'
>>> unwrap_simple_ref(s)
'hello, world'
>>> unwrap_simple_const_ref(s)
'hello, world'
>>> unwrap_int(5)
5

Can't get a reference to a built-in integer object
>>> try:
...     unwrap_int_ref(7)
... except: pass
... else: print 'no exception'

>>> try:
...     unwrap_int_const_ref(9)
... except: pass
... else: print 'no exception'

>>> wrap_int(n)
42

try: wrap_int_ref(n)
... except: pass
... else: print 'no exception'

>>> wrap_int_const_ref(n)
42

>>> unwrap_simple_ref(wrap_simple(s))
'hello, world'

>>> unwrap_simple_ref(wrap_simple_ref(s))
'hello, world'

>>> unwrap_simple_ref(wrap_simple_const_ref(s))
'hello, world'

>>> f(s)
12

>>> unwrap_simple(g(s))
'hello, world'

>>> f(g(s))
12

>>> C = xclass('C', (xinst,), {'__init__': init1, 'get_n': get_n})
>>> c = C(s, 99)
>>> c.get_n()
99

>>> D = xclass('D', (xinst,), {'__init__': init2, 'get_n': get_n})
>>> d = D(s)
>>> d.get_n()
0

"""

def run(args = None):

    ### Strange bug somewhere: with Metrowerks: it will crash in
    ### garbage-collection code unless traceback and sre have been
    ### loaded before m1.
    
#     import traceback
#     import sre
#     import m2
#     import m1
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    # import sys
    return doctest.testmod(sys.modules.get(__name__))
    
if __name__ == '__main__':
    print "running..."
    import sys
    sys.exit(run()[0])
