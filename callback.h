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

namespace detail {
  template <class T>
  inline void callback_adjust_refcount(PyObject*, Type<T>) {}
  
  inline void callback_adjust_refcount(PyObject* p, Type<PyObject*>)
      { Py_INCREF(p); }
}

// Calling Python from C++
template <class R>
struct Callback
{
    static R call_method(PyObject* self, const char* name)
    {
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("()")));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    static R call(PyObject* self)
    {
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("()")));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1>
    static R call_method(PyObject* self, const char* name, const A1& a1)
    {
        Ptr p1(to_python(a1));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(O)"),
                                     p1.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1>
    static R call(PyObject* self, const A1& a1)
    {
        Ptr p1(to_python(a1));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(O)"),
                                       p1.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1, class A2>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OO)"),
                                     p1.get(),
                                     p2.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1, class A2>
    static R call(PyObject* self, const A1& a1, const A2& a2)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(OO)"),
                                       p1.get(),
                                       p2.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1, class A2, class A3>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1, class A2, class A3>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(OOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1, class A2, class A3, class A4>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr p4(to_python(a4));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1, class A2, class A3, class A4>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr p4(to_python(a4));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(OOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static R call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr p4(to_python(a4));
        Ptr p5(to_python(a5));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get(),
                                     p5.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static R call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr p4(to_python(a4));
        Ptr p5(to_python(a5));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(OOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get()));
        detail::callback_adjust_refcount(result.get(), Type<R>());
        return from_python(result.get(), Type<R>());
    }
};

// This specialization wouldn't be needed, but MSVC6 doesn't correctly allow the following:
// void g();
// void f() { return g(); }
template <>
struct Callback<void>
{

    static void call_method(PyObject* self, const char* name)
    {
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("()")));
    }

    static void call(PyObject* self)
    {
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("()")));
    }

    template <class A1>
    static void call_method(PyObject* self, const char* name, const A1& a1)
    {
        Ptr p1(to_python(a1));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(O)"),
                                     p1.get()));
    }

    template <class A1>
    static void call(PyObject* self, const A1& a1)
    {
        Ptr p1(to_python(a1));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(O)"),
                                       p1.get()));
    }

    template <class A1, class A2>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OO)"),
                                     p1.get(),
                                     p2.get()));
    }

    template <class A1, class A2>
    static void call(PyObject* self, const A1& a1, const A2& a2)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(OO)"),
                                       p1.get(),
                                       p2.get()));
    }

    template <class A1, class A2, class A3>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get()));
    }

    template <class A1, class A2, class A3>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(OOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get()));
    }

    template <class A1, class A2, class A3, class A4>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr p4(to_python(a4));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
                                     const_cast<char*>("(OOOO)"),
                                     p1.get(),
                                     p2.get(),
                                     p3.get(),
                                     p4.get()));
    }

    template <class A1, class A2, class A3, class A4>
    static void call(PyObject* self, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr p4(to_python(a4));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(OOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get()));
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static void call_method(PyObject* self, const char* name, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
    {
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr p4(to_python(a4));
        Ptr p5(to_python(a5));
        Ptr result(PyEval_CallMethod(self, const_cast<char*>(name),
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
        Ptr p1(to_python(a1));
        Ptr p2(to_python(a2));
        Ptr p3(to_python(a3));
        Ptr p4(to_python(a4));
        Ptr p5(to_python(a5));
        Ptr result(PyEval_CallFunction(self, const_cast<char*>("(OOOOO)"),
                                       p1.get(),
                                       p2.get(),
                                       p3.get(),
                                       p4.get(),
                                       p5.get()));
    }
};

} // namespace py

#endif // CALLBACK_DWA_052100_H_

