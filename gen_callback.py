from gen_function import *
import string

def gen_callback(args):
    # A template for the call_method function which we're going to generate
    call_method = '''%{    template <%(class A%n%:, %)>
%}    static %1 call_method(PyObject* self, const char* name%(, const A%n& a%n%))
    {
        %2PyEval_CallMethod(self, const_cast<char*>(name),
                            const_cast<char*>("(%(N%))")%(,
                            to_python(a%n)%))%3;
    }

'''

    call_function = '''%{    template <%(class A%n%:, %)>
%}    static %1 call(PyObject* self%(, const A%n& a%n%))
    {
        %2PyEval_CallFunction(self, const_cast<char*>("(%(N%))")%(,
                              to_python(a%n)%))%3;
    }

'''
    non_void = ('R', 'return from_python(expect_non_null(', '), Type<R>())')
    void = ('void', 'expect_and_absorb_non_null(', ')')
    
    return (
"""//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file was generated for %d-argument python callbacks by gen_callback.py

#ifndef CALLBACK_DWA_052100_H_
# define CALLBACK_DWA_052100_H_

# include "pyconfig.h"
# include "py.h"

namespace py {

// Just like the above, except we decrement p's reference count instead of returning it.
void expect_and_absorb_non_null(PyObject* p);

// Calling Python from C++
template <class R>
struct Callback
{
""" % args
        + gen_functions(call_method, args, 'R', 'return from_python(expect_non_null(', '), Type<R>())')
        + gen_functions(call_function, args, 'R', 'return from_python(expect_non_null(', '), Type<R>())')
        + 
"""};

// This specialization wouldn't be needed, but MSVC6 doesn't correctly allow the following:
// void g();
// void f() { return g(); }
template <>
struct Callback<void>
{
"""
        + gen_functions(call_method, args, 'void', 'expect_and_absorb_non_null(', ')')
        + gen_functions(call_function, args, 'void', 'expect_and_absorb_non_null(', ')')
        +
"""};

} // namespace py

#endif // CALLBACK_DWA_052100_H_
""")

if __name__ == '__main__':
    import sys

    if len(sys.argv) == 1:
        args = 5
    else:
        args = int(sys.argv[1])

    print gen_callback(args)
