r'''>>> import pickle3
    >>> import re
    >>> import pickle
    >>> pickle3.world.__module__
    'pickle3'
    >>> pickle3.world.__safe_for_unpickling__
    1
    >>> pickle3.world.__reduce__()
    'world'
    >>> assert re.match(
    ... "\(<extension class pickle3.world at [0-9a-fA-FxX]+>, \('Hello',\), \(\{\}, 0\)\)",
    ... repr(pickle3.world('Hello').__reduce__()))
    >>>
    >>> for number in (24, 42):
    ...   wd = pickle3.world('California')
    ...   wd.set_secret_number(number)
    ...   wd.x = 2 * number
    ...   wd.y = 'y' * number
    ...   wd.z = 3. * number
    ...   pstr = pickle.dumps(wd)
    ...   wl = pickle.loads(pstr)
    ...   print wd.greet(), wd.get_secret_number(), wd.__dict__
    ...   print wl.greet(), wl.get_secret_number(), wl.__dict__
    Hello from California! 24 {'z': 72.0, 'x': 48, 'y': 'yyyyyyyyyyyyyyyyyyyyyyyy'}
    Hello from California! 24 {'z': 72.0, 'x': 48, 'y': 'yyyyyyyyyyyyyyyyyyyyyyyy'}
    Hello from California! 42 {'z': 126.0, 'x': 84, 'y': 'yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy'}
    Hello from California! 0 {'z': 126.0, 'x': 84, 'y': 'yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy'}
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_pickle3
    doctest.testmod(test_pickle3)

if __name__ == '__main__':
    run()
