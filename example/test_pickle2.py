r'''>>> import pickle2
    >>> import re
    >>> import pickle
    >>> pickle2.world.__module__
    'pickle2'
    >>> pickle2.world.__safe_for_unpickling__
    1
    >>> pickle2.world.__reduce__()
    'world'
    >>> assert re.match(
    ... "\(<extension class pickle2.world at [0-9a-fA-FxX]+>, \('Hello',\), \(0,\)\)",
    ... repr(pickle2.world('Hello').__reduce__()))
    >>>
    >>> for number in (24, 42):
    ...   wd = pickle2.world('California')
    ...   wd.set_secret_number(number)
    ...   pstr = pickle.dumps(wd)
    ...   wl = pickle.loads(pstr)
    ...   print wd.greet(), wd.get_secret_number()
    ...   print wl.greet(), wl.get_secret_number()
    Hello from California! 24
    Hello from California! 24
    Hello from California! 42
    Hello from California! 0

# Now show that the __dict__ is not taken care of.
    >>> wd = pickle2.world('California')
    >>> wd.x = 1
    >>> wd.__dict__
    {'x': 1}
    >>> try: pstr = pickle.dumps(wd)
    ... except RuntimeError, err: print err[0]
    ...
    Incomplete pickle support (__getstate_manages_dict__ not set)
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_pickle2
    return doctest.testmod(test_pickle2)

if __name__ == '__main__':
    import sys
    sys.exit(run()[0])

