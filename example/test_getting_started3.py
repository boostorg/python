r'''>>> import getting_started3
    >>> import re
    >>> import pickle
    >>> getting_started3.world.__module__
    'getting_started3'
    >>> getting_started3.world.__safe_for_unpickling__
    1
    >>> getting_started3.world.__reduce__()
    'world'
    >>> assert re.match(
    ... "\(<extension class getting_started3.world at [0-9a-fA-FxX]+>, \('Hello',\), \(0,\)\)",
    ... repr(getting_started3.world('Hello').__reduce__()))
    >>>
    >>> for number in (24, 42):
    ...   wd = getting_started3.world('California')
    ...   wd.set_secret_number(number)
    ...   pstr = pickle.dumps(wd)
    ...   print pstr
    ...   wl = pickle.loads(pstr)
    ...   print wd.greet(), wd.get_secret_number()
    ...   print wl.greet(), wl.get_secret_number()
    cgetting_started3
    world
    p0
    (S'California'
    p1
    tp2
    R(I24
    tp3
    bp4
    .
    Hello from California! 24
    Hello from California! 24
    cgetting_started3
    world
    p0
    (S'California'
    p1
    tp2
    R(I42
    tp3
    bp4
    .
    Hello from California! 42
    Hello from California! 0
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_getting_started3
    doctest.testmod(test_getting_started3)

if __name__ == '__main__':
    run()
