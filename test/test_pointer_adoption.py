"""
>>> from test_pointer_adoption_ext import *

>>> num_a_instances()
0

>>> a = create('dynamically allocated')
>>> num_a_instances()
1

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
    sys.exit(run()[0])
