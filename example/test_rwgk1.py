r'''>>> import rwgk1
    >>> print rwgk1.greet()
    hello, world
    >>> number = 11
    >>> print number, '*', number, '=', rwgk1.square(number)
    11 * 11 = 121
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_rwgk1
    return doctest.testmod(test_rwgk1)

if __name__ == '__main__':
    import sys
    sys.exit(run()[0])

