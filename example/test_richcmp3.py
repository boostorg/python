r'''>>> import richcmp3
    >>>
    >>> iv = richcmp3.ivect((1,2,3,4,5))
    >>> print iv.as_tuple()
    (1, 2, 3, 4, 5)
    >>> dv = richcmp3.dvect((2,-2,3,8,-5))
    >>> print dv.as_tuple()
    (2.0, -2.0, 3.0, 8.0, -5.0)
    >>>
    >>> print (iv+dv).as_tuple()
    (3.0, 0.0, 6.0, 12.0, 0.0)
    >>> print (iv+3).as_tuple()
    (4, 5, 6, 7, 8)
    >>> print (3+iv).as_tuple()
    (4, 5, 6, 7, 8)
    >>>
    >>> print "vect vs. vect Comparisons:"
    vect vs. vect Comparisons:
    >>> print (iv < dv).as_tuple()
    (1, 0, 0, 1, 0)
    >>> print (iv <= dv).as_tuple()
    (1, 0, 1, 1, 0)
    >>> print (iv == dv).as_tuple()
    (0, 0, 1, 0, 0)
    >>> print (iv != dv).as_tuple()
    (1, 1, 0, 1, 1)
    >>> print (iv > dv).as_tuple()
    (0, 1, 0, 0, 1)
    >>> print (iv >= dv).as_tuple()
    (0, 1, 1, 0, 1)
    >>>
    >>> print "vect vs. scalar Comparisons:"
    vect vs. scalar Comparisons:
    >>> print (iv < 3).as_tuple()
    (1, 1, 0, 0, 0)
    >>> print (iv <= 3).as_tuple()
    (1, 1, 1, 0, 0)
    >>> print (iv == 3).as_tuple()
    (0, 0, 1, 0, 0)
    >>> print (iv != 3).as_tuple()
    (1, 1, 0, 1, 1)
    >>> print (iv > 3).as_tuple()
    (0, 0, 0, 1, 1)
    >>> print (iv >= 3).as_tuple()
    (0, 0, 1, 1, 1)
    >>>
    >>> print "scalar  vs. vect Comparisons:"
    scalar  vs. vect Comparisons:
    >>> print (3 < iv).as_tuple()
    (0, 0, 0, 1, 1)
    >>> print (3 <= iv).as_tuple()
    (0, 0, 1, 1, 1)
    >>> print (3 == iv).as_tuple()
    (0, 0, 1, 0, 0)
    >>> print (3 != iv).as_tuple()
    (1, 1, 0, 1, 1)
    >>> print (3 > iv).as_tuple()
    (1, 1, 0, 0, 0)
    >>> print (3 >= iv).as_tuple()
    (1, 1, 1, 0, 0)
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_richcmp3
    return doctest.testmod(test_richcmp3)

if __name__ == '__main__':
    import sys
    if (    hasattr(sys, 'version_info')
        and (   (sys.version_info[0] == 2 and sys.version_info[1] >= 1)
             or sys.version_info[0] > 2)):
      sys.exit(run()[0])
    else:
      print "Python version 2.1 or higher required. Test skipped."
