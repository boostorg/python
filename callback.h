//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file was generated for 10-argument python callbacks by gen_callback.python

#ifndef CALLBACK_DWA_052100_H_
# define CALLBACK_DWA_052100_H_

# include "pyconfig.h"
# include "py.h"

namespace python {

namespace detail {
  template <class T>
  inline void callback_adjust_refcount(PyObject*, type<T>) {}
  
  inline void callback_adjust_refcount(PyObject* p, type<PyObject*>)
      { Py_INCREF(p); }
}

// Calling Python from C++
template <class R>
struct callback
{
    static R call_method(PyObject* self, const char* name)
    {
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("()")));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    static R call(PyObject* self)
    {
        ref result(PyEval_CallFunction(self, const_cast<char*>("()")));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1>
    static R call_method(PyObject* self, const char* name, const A1& a1)
    {
        ref p1(to_python(a1));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(O)"),
                                     p1.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1>
    static R call(PyObject* self, const A1& a1)
    {
        ref p1(to_python(a1));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(O)"),
                                       p1.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OO)"),
                                     p1.get(),
                                     p2.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2>
    static R call(PyObject* self, const A1& a1, const A2& a2)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OO)"),
                                       p1.get(),
                                       p2.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get(),
                                     p7.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get(),
                                       p7.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get(),
                                     p7.get(),
                                     p8.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get(),
                                       p7.get(),
                                       p8.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref p9(to_python(a9));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get(),
                                     p7.get(),
                                     p8.get(),
                                     p9.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref p9(to_python(a9));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get(),
                                       p7.get(),
                                       p8.get(),
                                       p9.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref p9(to_python(a9));
        ref p10(to_python(a10));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get(),
                                     p7.get(),
                                     p8.get(),
                                     p9.get(),
                                     p10.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref p9(to_python(a9));
        ref p10(to_python(a10));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get(),
                                       p7.get(),
                                       p8.get(),
                                       p9.get(),
                                       p10.get()));
        detail::callback_adjust_refcount(result.get(), type<R>());
        return from_python(result.get(), type<R>());
    }
};

// This specialization wouldn't be needed, but MSVC6 doesn't correctly allow the following:
// void g();
// void f() { return g(); }
template <>
struct callback<void>
{

    static void call_method(PyObject* self, const char* name)
    {
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("()")));
    }

    static void call(PyObject* self)
    {
        ref result(PyEval_CallFunction(self, const_cast<char*>("()")));
    }

    template <class A1>
    static void call_method(PyObject* self, const char* name, const A1& a1)
    {
        ref p1(to_python(a1));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(O)"),
                                     p1.get()));
    }

    template <class A1>
    static void call(PyObject* self, const A1& a1)
    {
        ref p1(to_python(a1));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(O)"),
                                       p1.get()));
    }

    template <class A1, class A2>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OO)"),
                                     p1.get(),
                                     p2.get()));
    }

    template <class A1, class A2>
    static void call(PyObject* self, const A1& a1, const A2& a2)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OO)"),
                                       p1.get(),
                                       p2.get()));
    }

    template <class A1, class A2, class A3>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get()));
    }

    template <class A1, class A2, class A3>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get()));
    }

    template <class A1, class A2, class A3, class A4>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get()));
    }

    template <class A1, class A2, class A3, class A4>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get(),
                                     p7.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get(),
                                       p7.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get(),
                                     p7.get(),
                                     p8.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get(),
                                       p7.get(),
                                       p8.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref p9(to_python(a9));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get(),
                                     p7.get(),
                                     p8.get(),
                                     p9.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref p9(to_python(a9));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get(),
                                       p7.get(),
                                       p8.get(),
                                       p9.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref p9(to_python(a9));
        ref p10(to_python(a10));
        ref result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOOOOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get(),
                                     p6.get(),
                                     p7.get(),
                                     p8.get(),
                                     p9.get(),
                                     p10.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
    {
        ref p1(to_python(a1));
        ref p2(to_python(a2));
        ref p3(to_python(a3));
        ref p4(to_python(a4));
        ref p5(to_python(a5));
        ref p6(to_python(a6));
        ref p7(to_python(a7));
        ref p8(to_python(a8));
        ref p9(to_python(a9));
        ref p10(to_python(a10));
        ref result(PyEval_CallFunction(self, const_cast<char*>("(OOOOOOOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get(),
                                       p6.get(),
                                       p7.get(),
                                       p8.get(),
                                       p9.get(),
                                       p10.get()));
    }
};

// Make it a compile-time error to try to return a const char* from a virtual
// function. The standard conversion
//
//      from_python(PyObject* string, python::type<const char*>)
//
// returns a pointer to the character array which is internal to string. The
// problem with trying to do this in a standard callback function is that the
// Python string would likely be destroyed upon return from the calling function
// (python::callback<const char*>::call[_method]) when its reference count is
// decremented. If you absolutely need to do this and you're sure it's safe (it
// usually isn't), you can use
//
//      python::string result(python::callback<python::string>::call[_method](...args...));
//      ...result.c_str()... // access the char* array
template <>
struct callback<const char*>
{
    // Try hard to generate a readable error message
    typedef struct unsafe_since_python_string_may_be_destroyed {} call, call_method;
};

} // namespace python

#endif // CALLBACK_DWA_052100_H_
