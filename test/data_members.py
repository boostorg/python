'''
>>> from data_members_ext import *
>>> x = X(42)
>>> x.x
42
>>> try: x.x = 77
... except AttributeError: pass
... else: print 'no error'

>>> y = Y(69)
>>> y.x
69
>>> y.x = 77
>>> y.x
77
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
