#  (C) Copyright David Abrahams 2001. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears
#  in all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.
#
#  This work was funded in part by Lawrence Berkeley National Labs

from gen_function import *
import string

header = '''// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
//  This work was funded in part by Lawrence Berkeley National Labs
//
//  This file generated for %d-argument member functions and %d-argument free
//  functions by gen_call.py

#ifndef CALL_DWA20011214_HPP
# define CALL_DWA20011214_HPP

# include <boost/python/detail/returning.hpp>

namespace boost { namespace python { 

'''
_cv_qualifiers = ('', ' const', ' volatile', ' const volatile')
            
def gen_call(member_function_args, free_function_args = None):
    if free_function_args is None:
        free_function_args = member_function_args + 1

    return (header % (member_function_args, free_function_args)
            + gen_functions(
'''template <class R%(, class A%n%)>
PyObject* call(R (*f)(%(A%n%:, %)), PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

''', free_function_args)
            +
'''// Member functions
'''
             + reduce(lambda x,y: x+y
                   , map(lambda cv:
                         gen_functions(
'''template <class R, class A0%(, class A%+%)>
PyObject* call(R (A0::*f)(%(A%+%:, %))%1, PyObject* args, PyObject* keywords)
{
    return detail::returning<R>::call(f, args, keywords);
}

'''
                        , member_function_args, cv)
                      , _cv_qualifiers))
            +
'''
}} // namespace boost::python

#endif // CALL_DWA20011214_HPP
''')            

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        member_function_args = 5
        free_function_args = 6
    else:
        member_function_args = int(sys.argv[1])
        if len(sys.argv) > 2:
            free_function_args = int(sys.argv[2])
        else:
            free_function_args = member_function_args

    print gen_call(member_function_args, free_function_args)


