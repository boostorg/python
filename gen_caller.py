#  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears
#  in all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.
#
#  The author gratefully acknowleges the support of Dragon Systems, Inc., in
#  producing this work.

from gen_function import *
import string

header = '''//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file generated for %d-argument member functions and %d-argument free
//  functions by gen_caller.py
'''

body_sections = (
'''
#ifndef CALLER_DWA05090_H_
# define CALLER_DWA05090_H_

# include "pyconfig.h"
# include "wrap_python.h"
# include <boost/config.hpp>
# include "signatures.h"
# include "none.h"

namespace py {

// Calling C++ from Python
template <class R>
struct Caller
{
''',
'''
''',
'''    // Free functions
''',
'''};
                           
template <>
struct Caller<void>
{
''',
'''
''',
'''
    // Free functions
''',
'''};

}

#endif
''')

#'

member_function = '''    template <class T%(, class A%n%)>
    static PyObject* call(%1 (T::*pmf)(%(A%n%:, %))%2, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
%(        PyObject* a%n;
%)        if (!PyArg_ParseTuple(args, const_cast<char*>("O%(O%)"), &self%(, &a%n%)))
            return 0;
        T& target = from_python(self, Type<T&>());
        %3(target.*pmf)(%(from_python(a%n, Type<A%n>())%:,
                        %))%4
    }

'''

free_function = '''%{    template <%(class A%n%:, %)>
%}    static PyObject* call(%1 (*f)(%(A%n%:, %)), PyObject* args, PyObject* /* keywords */ ) {
%(        PyObject* a%n;
%)        if (!PyArg_ParseTuple(args, const_cast<char*>("%(O%)")%(, &a%n%)))
            return 0;
        %2f(%(from_python(a%n, Type<A%n>())%:,
                        %))%3
    }

'''

def gen_caller(member_function_args, free_function_args = None):
    if free_function_args is None:
        free_function_args = member_function_args + 1

    return_none = ''';
        return detail::none();'''
    
    return (header % (member_function_args, free_function_args)
            + body_sections[0]
            + gen_functions(member_function, member_function_args,
                            'R', '', 'return to_python(', ');')
            + body_sections[1]
            + gen_functions(member_function, member_function_args,
                            'R', ' const', 'return to_python(', ');')
            + body_sections[2]
            
            + gen_functions(free_function, free_function_args,
                            'R', 'return to_python(', ');')
            + body_sections[3]

            # specialized part for void return values begins here
            + gen_functions(member_function, member_function_args,
                            'void', '', '', return_none)
            + body_sections[4]
            + gen_functions(member_function, member_function_args,
                            'void', ' const', '', return_none)
            + body_sections[5]

            + gen_functions(free_function, free_function_args,
                            'void', '', return_none)
            + body_sections[6]
            )

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

    print gen_caller(member_function_args, free_function_args)


