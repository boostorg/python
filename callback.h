//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file was generated for 5-argument python callbacks by gen_callback.py

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
    static R call_method(PyObject* self, const char* name)
        { return from_python(expect_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("()"))), Type<R>()); }

    template <class A1>
    static R call_method(PyObject* self, const char* name, const A1& a1)
        { return from_python(expect_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(N)"), to_python(a1))), Type<R>()); }

    template <class A1, class A2>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2)
        { return from_python(expect_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(NN)"), to_python(a1), to_python(a2))), Type<R>()); }

    template <class A1, class A2, class A3>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3)
        { return from_python(expect_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(NNN)"), to_python(a1), to_python(a2), to_python(a3))), Type<R>()); }

    template <class A1, class A2, class A3, class A4>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
        { return from_python(expect_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(NNNN)"), to_python(a1), to_python(a2), to_python(a3), to_python(a4))), Type<R>()); }

    template <class A1, class A2, class A3, class A4, class A5>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
        { return from_python(expect_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(NNNNN)"), to_python(a1), to_python(a2), to_python(a3), to_python(a4), to_python(a5))), Type<R>()); }

};

// This specialization wouldn't be needed, but MSVC6 doesn't correctly allow the following:
// void g();
// void f() { return g(); }
template <>
struct Callback<void>
{
    static void call_method(PyObject* self, const char* name)
        { expect_and_absorb_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("()"))); }

    template <class A1>
    static void call_method(PyObject* self, const char* name, const A1& a1)
        { expect_and_absorb_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(N)"), to_python(a1))); }

    template <class A1, class A2>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2)
        { expect_and_absorb_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(NN)"), to_python(a1), to_python(a2))); }

    template <class A1, class A2, class A3>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3)
        { expect_and_absorb_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(NNN)"), to_python(a1), to_python(a2), to_python(a3))); }

    template <class A1, class A2, class A3, class A4>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
        { expect_and_absorb_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(NNNN)"), to_python(a1), to_python(a2), to_python(a3), to_python(a4))); }

    template <class A1, class A2, class A3, class A4, class A5>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
        { expect_and_absorb_non_null(PyEval_CallMethod(self, const_cast<char*>(name), const_cast<char*>("(NNNNN)"), to_python(a1), to_python(a2), to_python(a3), to_python(a4), to_python(a5))); }

};

} // namespace py

#endif // CALLBACK_DWA_052100_H_
