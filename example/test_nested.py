r'''>>> import nested
    >>> s = nested.show_nested_tuples(((1,2,3), (4,5,6,7)))
    >>> for l in s:
    ...   print l
    (0,0) 1
    (0,1) 2
    (0,2) 3
    (1,0) 4
    (1,1) 5
    (1,2) 6
    (1,3) 7
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_nested
    return doctest.testmod(test_nested)

if __name__ == '__main__':
    import sys
    sys.exit(run()[0])
