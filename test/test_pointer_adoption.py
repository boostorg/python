"""
>>> from test_pointer_adoption_ext import *

>>> num_a_instances()
0

>>> a = create('dynamically allocated')
>>> num_a_instances()
1

>>> a.content()
'dynamically allocated'

>>> a = None
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
