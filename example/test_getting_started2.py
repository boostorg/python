r'''>>> import getting_started2
    >>> w = getting_started2.world('California')
    >>> print w.greet()
    Hello from California!
    >>> print getting_started2.invite(w)
    Hello from California! Please come soon!
    >>> print w.invite()
    Hello from California! Please come soon!
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_getting_started2
    doctest.testmod(test_getting_started2)

if __name__ == '__main__':
    run()
