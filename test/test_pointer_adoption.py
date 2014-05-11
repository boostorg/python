# Copyright David Abrahams 2004. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
"""
>>> from test_pointer_adoption_ext import *
>>> import sys

>>> num_a_instances()
0

>>> a = create('dynamically allocated')
>>> num_a_instances()
1
>>> sys.getrefcount(a)
2
>>> a.content()
'dynamically allocated'

>>> innards = a.get_inner()
>>> innards.change('with an exposed reference')
>>> a.content()
'with an exposed reference'

# The a instance should be kept alive...
>>> a = None
>>> num_a_instances()
1

# ...until we're done with its innards
>>> innards = None
>>> num_a_instances()
0

>>> b = B()
>>> a = create('another')
>>> b.a_content()
'empty'
>>> innards = b.adopt(a);
>>> b.a_content()
'another'
>>> num_a_instances()
1
>>> del a # innards and b are both holding a reference
>>> num_a_instances()
1
>>> innards.change('yet another')
>>> b.a_content()
'yet another'

>>> del innards
>>> num_a_instances() # b still owns a reference to a
1
>>> del b
>>> num_a_instances()
0

Test call policies for constructors here

>>> a = create('second a')
>>> a.content()
'second a'
>>> num_a_instances()
1
>>> b = a.create_B()
>>> num_a_instances()
1
>>> sys.getrefcount(a)
3
>>> b.a_content()
'second a'
>>> b = None
>>> num_a_instances()
1
>>> sys.getrefcount(a)
2

>>> b = B(a)
>>> num_a_instances()
1
>>> sys.getrefcount(a)
3
>>> a.content()
'second a'
>>> b.a_content()
'second a'
>>> b = None
>>> num_a_instances()
1
>>> sys.getrefcount(a)
2

>>> b = B1(a)
>>> num_a_instances()
1
>>> sys.getrefcount(a)
3
>>> a.content()
'second a'
>>> b.a_content()
'second a'
>>> b = None
>>> num_a_instances()
1
>>> sys.getrefcount(a)
2

>>> b = B2(a)
>>> num_a_instances()
1
>>> sys.getrefcount(a)
3
>>> a.content()
'second a'
>>> b.a_content()
'second a'
>>> b = None
>>> num_a_instances()
1
>>> sys.getrefcount(a)
2

>>> b = B(a)
>>> num_a_instances()
1

>>> del a
>>> num_a_instances()
1
>>> b.a_content()
'second a'

>>> del b
>>> num_a_instances()
0

>>> assert as_A(create('dynalloc')) is not None
>>> base = Base()
>>> assert as_A(base) is None
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
