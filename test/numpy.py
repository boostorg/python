# Copyright David Abrahams 2004. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# Unfortunately the doctest module works differently in Python versions
# 2.2, 2.3, and 2.4. Newer versions evaluate all docstrings, even that
# of objects with names starting with an underscore. To portably disable
# tests based on the availability of Numeric and numarray, the corresponding
# test functions are simply deleted below if necessary.

# So we can coerce portably across Python versions
bool = type(1 == 1)

def numeric_tests():
    '''
    >>> from numpy_ext import *
    >>> x = new_array()
    >>> x[1,1] = 0.0

    >>> try: take_array(3)
    ... except TypeError: pass
    ... else: print 'expected a TypeError'

    >>> take_array(x)

    >>> print x
    [[1 2 3]
     [4 0 6]
     [7 8 9]]

    >>> y = x.copy()


    >>> p = _printer()
    >>> check = p.check
    >>> exercise(x, p)
    >>> y[2,1] = 3
    >>> check(y);

    >>> check(y.astype('D'));

    >>> check(y.copy());

    >>> check(y.typecode());

    >>> p.results
    []
    >>> del p
    '''
    pass

def _numarray_tests():
    '''
    >>> from numpy_ext import *
    >>> x = new_array()
    >>> y = x.copy()
    >>> p = _printer()
    >>> check = p.check
    >>> exercise_numarray(x, p)

    >>> check(str(y))
        
    >>> check(y.argmax());
    >>> check(y.argmax(0));

    >>> check(y.argmin());
    >>> check(y.argmin(0));

    >>> check(y.argsort());
    >>> check(y.argsort(1));
    
    >>> y.byteswap();
    >>> check(y);
    
    >>> check(y.diagonal());
    >>> check(y.diagonal(1));
    >>> check(y.diagonal(0, 0));
    >>> check(y.diagonal(0, 1, 0));

    >>> check(y.is_c_array());
    
    # coerce because numarray still returns an int and the C++ interface forces
    # the return type to bool
    >>> check( bool(y.isbyteswapped()) ); 

    >>> check(y.trace());
    >>> check(y.trace(1));
    >>> check(y.trace(0, 0));
    >>> check(y.trace(0, 1, 0));

    >>> check(y.new('D').getshape());
    >>> check(y.new('D').type());
    >>> y.sort();
    >>> check(y);
    >>> check(y.type());

    >>> check(y.factory((1.2, 3.4)));
    >>> check(y.factory((1.2, 3.4), "f8"))
    >>> check(y.factory((1.2, 3.4), "f8", true))
    >>> check(y.factory((1.2, 3.4), "f8", true, false))
    >>> check(y.factory((1.2, 3.4), "f8", true, false, None))
    >>> check(y.factory((1.2, 3.4), "f8", true, false, None, (1,2,1)))
    
    >>> p.results
    []
    >>> del p
    '''
    pass

false = 0;
true = 1;
class _printer(object):
    def __init__(self):
        self.results = [];
    def __call__(self, *stuff):
        for x in stuff:
            self.results.append(str(x))
    def check(self, x):
        if self.results[0] != str(x):
            print '  Expected:\n %s\n  but the C++ interface gave:\n %s' % (x, self.results[0])
        del self.results[0]

def _run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args

    # See which of the numeric modules are installed
    has_numeric = 0
    try:
        import Numeric
        m = Numeric
        has_numeric = 1
    except ImportError:
      global numeric_tests
      numeric_tests = None

    has_numarray = 0
    try:
        import numarray
        m = numarray
        has_numarray = 1
    except ImportError:
      global _numarray_tests
      _numarray_tests = None
    
    # Bail if neither one is installed
    if not (has_numeric or has_numarray):
        return 0

    # test the info routine outside the doctest. See numpy.cpp for an
    # explanation
    import numpy_ext
    if (has_numarray):
        numpy_ext.info(m.array((1,2,3)))

    failures = 0

    find = doctest.DocTestFinder().find
    run = doctest.DocTestRunner().run
    
    #
    # Run tests 4 different ways if both modules are installed, just
    # to show that set_module_and_type() is working properly
    #
    
    # run all the tests with default module search
    print 'testing default extension module:', \
          numpy_ext.get_module_name() or '[numeric support not installed]'

    for test in find(numeric_tests):
        failures += run(test)[0]
        
    # test against Numeric if installed
    if has_numeric:
        print 'testing Numeric module explicitly'
        numpy_ext.set_module_and_type('Numeric', 'ArrayType')
        
        for test in find(numeric_tests):
            failures += run(test)[0]
            
    global __test__
    if has_numarray:
        # Add the _numarray_tests to the list of things to test in
        # this case.
        __test__ = { 'numarray_tests':_numarray_tests,
                     'numeric_tests': numeric_tests }
        print 'testing numarray module explicitly'
        numpy_ext.set_module_and_type('numarray', 'NDArray')
        
        for test in find(numeric_tests) + find(_numarray_tests):
            failures += run(test)[0]
        del __test__

    # see that we can go back to the default
    numpy_ext.set_module_and_type('', '')
    print 'testing default module again:', \
          numpy_ext.get_module_name() or '[numeric support not installed]'
    
    for test in find(numeric_tests):
        failures += run(test)[0]
    
    return failures
    
if __name__ == '__main__':
    print "running..."
    import sys
    status = _run()
    if (status == 0): print "Done."
    sys.exit(status)
