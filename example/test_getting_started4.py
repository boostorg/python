r'''>>> import getting_started4
    >>> v=getting_started4.vector_double()
    >>> print v.as_tuple()
    ()
    >>> v=getting_started4.vector_double(5)
    >>> print v.as_tuple()
    (0.0, 0.0, 0.0, 0.0, 0.0)
    >>> print len(v)
    5
    >>> v=getting_started4.vector_double((3,4,5))
    >>> print v.as_tuple()
    (3.0, 4.0, 5.0)
    >>> print v[1]
    4.0
    >>> v[1] = 40
    >>> print v.as_tuple()
    (3.0, 40.0, 5.0)
    >>> del v[1]
    >>> print v.as_tuple()
    (3.0, 5.0)
    >>> print getting_started4.foo(11).as_tuple()
    (0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0)
    >>> print getting_started4.bar(12).as_tuple()
    (0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0)
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_getting_started4
    doctest.testmod(test_getting_started4)

if __name__ == '__main__':
    run()
