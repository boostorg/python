r'''>>> import tst_noncopyable
    >>> tst_noncopyable.f()
    1
    2
    3
    >>> import tst_dvect1
    >>> tst_dvect1.f()
    (1.0, 2.0, 3.0, 4.0, 5.0)
    (1, 2, 3, 4, 5)
    (1, 2, 3, 4, 5)
    (1, 2, 3, 4, 5)
    (1, 2, 3, 4, 5)
    (1, 2, 3, 4, 5)
    (1, 2, 3, 4, 5)
    >>> import tst_ivect1
    >>> tst_ivect1.f()
    (1, 2, 3, 4, 5)
    (1.0, 2.0, 3.0, 4.0, 5.0)
    (1.0, 2.0, 3.0, 4.0, 5.0)
    (1.0, 2.0, 3.0, 4.0, 5.0)
    (1.0, 2.0, 3.0, 4.0, 5.0)
    (1.0, 2.0, 3.0, 4.0, 5.0)
    (1.0, 2.0, 3.0, 4.0, 5.0)
    >>> import sys
    >>> if ("--broken-auto-ptr" in sys.argv):
    ...   broken_auto_ptr = 1
    ... else:
    ...   broken_auto_ptr = 0
    >>> import tst_dvect2
    >>> tst_dvect2.f(broken_auto_ptr)
    1. auto_ptr_value_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. auto_ptr_value_ivect_as_tuple
    None
    1. auto_ptr_value_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. auto_ptr_value_dvect_as_tuple
    None
    1. shared_ptr_value_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. shared_ptr_value_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. shared_ptr_value_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. shared_ptr_value_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. auto_ptr_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. auto_ptr_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. auto_ptr_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. auto_ptr_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. shared_ptr_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. shared_ptr_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. shared_ptr_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. shared_ptr_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. auto_ptr_const_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. auto_ptr_const_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. auto_ptr_const_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. auto_ptr_const_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. shared_ptr_const_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. shared_ptr_const_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. shared_ptr_const_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. shared_ptr_const_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    >>> import tst_ivect2
    >>> tst_ivect2.f(broken_auto_ptr)
    1. auto_ptr_value_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. auto_ptr_value_dvect_as_tuple
    None
    1. auto_ptr_value_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. auto_ptr_value_ivect_as_tuple
    None
    1. shared_ptr_value_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. shared_ptr_value_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. shared_ptr_value_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. shared_ptr_value_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. auto_ptr_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. auto_ptr_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. auto_ptr_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. auto_ptr_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. shared_ptr_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. shared_ptr_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. shared_ptr_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. shared_ptr_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. auto_ptr_const_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. auto_ptr_const_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. auto_ptr_const_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. auto_ptr_const_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    1. shared_ptr_const_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    2. shared_ptr_const_reference_dvect_as_tuple
    (1.0, 2.0, 3.0, 4.0, 5.0)
    1. shared_ptr_const_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
    2. shared_ptr_const_reference_ivect_as_tuple
    (1, 2, 3, 4, 5)
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_cross_module
    return doctest.testmod(test_cross_module)

if __name__ == '__main__':
    import sys
    sys.exit(run()[0])
