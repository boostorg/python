r'''>>> import richcmp1
    >>> d1 = richcmp1.dvect((0, 1, 3, 3, 6, 7))
    >>> d2 = richcmp1.dvect((1, 2, 3, 4, 5, 6))
    >>> print d1.as_tuple()
    (0.0, 1.0, 3.0, 3.0, 6.0, 7.0)
    >>> print d2.as_tuple()
    (1.0, 2.0, 3.0, 4.0, 5.0, 6.0)
    >>> print (d1 < d2).as_tuple()
    (1, 1, 0, 1, 0, 0)
    >>> print (d1 <= d2).as_tuple()
    (1, 1, 1, 1, 0, 0)
    >>> print (d1 == d2).as_tuple()
    (0, 0, 1, 0, 0, 0)
    >>> print (d1 != d2).as_tuple()
    (1, 1, 0, 1, 1, 1)
    >>> print (d1 > d2).as_tuple()
    (0, 0, 0, 0, 1, 1)
    >>> print (d1 >= d2).as_tuple()
    (0, 0, 1, 0, 1, 1)
    >>> try: d1 == richcmp1.dvect((1, 2, 3, 4, 5))
    ... except ValueError, e: print str(e)
    ...
    vectors have different sizes
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_richcmp1
    return doctest.testmod(test_richcmp1)

if __name__ == '__main__':
    import sys
    if (    hasattr(sys, 'version_info')
        and (   (sys.version_info[0] == 2 and sys.version_info[1] >= 1)
             or sys.version_info[0] > 2)):
      sys.exit(run()[0])
    else:
      print "Python version 2.1 or higher required. Test skipped."
