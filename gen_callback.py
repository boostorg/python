from gen_function import *
import string

def gen_callback(args):
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

namespace detail {
  template <class T>
  inline void callback_adjust_refcount(PyObject*, Type<T>) {}
  
  inline void callback_adjust_refcount(PyObject* p, Type<PyObject*>)
      { Py_INCREF(p); }
}

// Calling Python from C++
template <class R>
struct Callback
{""" % args

    + gen_functions('''
%{    template <%(class A%n%:, %)>
%}    static R call_method(PyObject* self, const char* name%(, const A%n& a%n%))
    {%(
        Ptr p%n(to_python(a%n));%)
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(%(O%))")%(,
                                     p%n.get()%)));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

%{    template <%(class A%n%:, %)>
%}    static R call(PyObject* self%(, const A%n& a%n%))
    {%(
        Ptr p%n(to_python(a%n));%)
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(%(O%))")%(,
                                       p%n.get()%)));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }
''', args)
        + 
"""};

// This specialization wouldn't be needed, but MSVC6 doesn't correctly allow the following:
// void g();
// void f() { return g(); }
template <>
struct Callback<void>
{
"""
        + gen_functions('''
%{    template <%(class A%n%:, %)>
%}    static void call_method(PyObject* self, const char* name%(, const A%n& a%n%))
    {%(
        Ptr p%n(to_python(a%n));%)
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(%(O%))")%(,
                                     p%n.get()%)));
    }

%{    template <%(class A%n%:, %)>
%}    static void call(PyObject* self%(, const A%n& a%n%))
    {%(
        Ptr p%n(to_python(a%n));%)
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(%(O%))")%(,
                                       p%n.get()%)));
    }
''', args)
        +
"""};

// Make it a compile-time error to try to return a const char* from a virtual
// function. The standard conversion
//
//      from_python(PyObject* string, py::Type<const char*>)
//
// returns a pointer to the character array which is internal to string. The
// problem with trying to do this in a standard callback function is that the
// Python string would likely be destroyed upon return from the calling function
// (py::Callback<const char*>::call[_method]) when its reference count is
// decremented. If you absolutely need to do this and you're sure it's safe (it
// usually isn't), you can use
//
//      py::String result(py::Callback<py::String>::call[_method](...args...));
//      ...result.c_str()... // access the char* array
template <>
struct Callback<const char*>
{
    // Try hard to generate a readable error message
    typedef struct unsafe_since_python_string_may_be_destroyed {} call, call_method;
};

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
