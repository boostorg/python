"""

>>> from defaults_ext import *
>>> foo(1)
'int(1); char(D); string(default); double(0); '
>>> foo(2, 'X')
'int(2); char(X); string(default); double(0); '
>>> foo(3, 'Y', "Hello World")
'int(3); char(Y); string(Hello World); double(0); '
>>> foo(4, 'Z', "Hi There", 3.3)
'int(4); char(Z); string(Hi There); double(3.3); '
>>> x = X()
>>> x.bar(1)
'int(1); char(D); string(default); double(0); '
>>> x.bar(2, 'X')
'int(2); char(X); string(default); double(0); '
>>> x.bar(3, 'Y', "Hello World")
'int(3); char(Y); string(Hello World); double(0); '
>>> x.bar(4, 'Z', "Hi There", 3.3)
'int(4); char(Z); string(Hi There); double(3.3); '
>>>



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













































