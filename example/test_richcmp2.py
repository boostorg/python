r'''>>> import richcmp2
    >>> c1 = richcmp2.code(1)
    >>> c2 = richcmp2.code(2)
    >>> c3 = richcmp2.code(2)
    >>> print c1 == c2
    0
    >>> print c1 != c2
    1
    >>> print c2 == c3
    1
    >>> print c2 != c3
    0
    >>> print c1 < c2
    1
    >>> print c1 <= c2
    1
    >>> print c1 == c2
    0
    >>> print c1 != c2
    1
    >>> print c1 > c2
    0
    >>> print c1 >= c2
    0
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
