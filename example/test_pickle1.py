r'''>>> import pickle1
    >>> import re
    >>> import pickle
    >>> pickle1.world.__module__
    'pickle1'
    >>> pickle1.world.__safe_for_unpickling__
    1
    >>> pickle1.world.__reduce__()
    'world'
    >>> assert re.match(
    ... "\(<extension class pickle1.world at [0-9a-fA-FxX]+>, \('Hello',\)\)",
    ... repr(pickle1.world('Hello').__reduce__()))
    >>>
    >>> wd = pickle1.world('California')
    >>> pstr = pickle.dumps(wd)
    >>> wl = pickle.loads(pstr)
    >>> print wd.greet()
    Hello from California!
    >>> print wl.greet()
    Hello from California!
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_pickle1
    doctest.testmod(test_pickle1)

if __name__ == '__main__':
    run()
