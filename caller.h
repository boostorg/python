//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file generated for 10-argument member functions and 11-argument free
//  functions by gen_caller.python

#ifndef CALLER_DWA05090_H_
# define CALLER_DWA05090_H_

# include "pyconfig.h"
# include "wrap_python.h"
# include <boost/config.hpp>
# include "signatures.h"
# include "none.h"

namespace python {

// Calling C++ from Python
template <class R>
struct caller
{
    template <class T>
    static PyObject* call(R (T::*pmf)(), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &self))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)());
    }

    template <class T, class A1>
    static PyObject* call(R (T::*pmf)(A1), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &self, &a1))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>())));
    }

    template <class T, class A1, class A2>
    static PyObject* call(R (T::*pmf)(A1, A2), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &self, &a1, &a2))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>())));
    }

    template <class T, class A1, class A2, class A3>
    static PyObject* call(R (T::*pmf)(A1, A2, A3), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &self, &a1, &a2, &a3))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>())));
    }

    template <class T, class A1, class A2, class A3, class A4>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOO"), &self, &a1, &a2, &a3, &a4))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOO"), &self, &a1, &a2, &a3, &a4, &a5))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6, A7), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8, A9), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()),
                        from_python(a10, type<A10>())));
    }


    template <class T>
    static PyObject* call(R (T::*pmf)() const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &self))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)());
    }

    template <class T, class A1>
    static PyObject* call(R (T::*pmf)(A1) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &self, &a1))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>())));
    }

    template <class T, class A1, class A2>
    static PyObject* call(R (T::*pmf)(A1, A2) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &self, &a1, &a2))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>())));
    }

    template <class T, class A1, class A2, class A3>
    static PyObject* call(R (T::*pmf)(A1, A2, A3) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &self, &a1, &a2, &a3))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>())));
    }

    template <class T, class A1, class A2, class A3, class A4>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOO"), &self, &a1, &a2, &a3, &a4))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOO"), &self, &a1, &a2, &a3, &a4, &a5))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6, A7) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>())));
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static PyObject* call(R (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10))
            return 0;
        T& target = from_python(self, type<T&>());
        return to_python((target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()),
                        from_python(a10, type<A10>())));
    }

    // Free functions
    static PyObject* call(R (*f)(), PyObject* args, PyObject* /* keywords */ ) {
        if (!PyArg_ParseTuple(args, const_cast<char*>("")))
            return 0;
        return to_python(f());
    }

    template <class A1>
    static PyObject* call(R (*f)(A1), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &a1))
            return 0;
        return to_python(f(from_python(a1, type<A1>())));
    }

    template <class A1, class A2>
    static PyObject* call(R (*f)(A1, A2), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &a1, &a2))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>())));
    }

    template <class A1, class A2, class A3>
    static PyObject* call(R (*f)(A1, A2, A3), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &a1, &a2, &a3))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>())));
    }

    template <class A1, class A2, class A3, class A4>
    static PyObject* call(R (*f)(A1, A2, A3, A4), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &a1, &a2, &a3, &a4))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>())));
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(R (*f)(A1, A2, A3, A4, A5), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOO"), &a1, &a2, &a3, &a4, &a5))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>())));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    static PyObject* call(R (*f)(A1, A2, A3, A4, A5, A6), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>())));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static PyObject* call(R (*f)(A1, A2, A3, A4, A5, A6, A7), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>())));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static PyObject* call(R (*f)(A1, A2, A3, A4, A5, A6, A7, A8), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>())));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static PyObject* call(R (*f)(A1, A2, A3, A4, A5, A6, A7, A8, A9), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>())));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static PyObject* call(R (*f)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()),
                        from_python(a10, type<A10>())));
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
    static PyObject* call(R (*f)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        PyObject* a11;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10, &a11))
            return 0;
        return to_python(f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()),
                        from_python(a10, type<A10>()),
                        from_python(a11, type<A11>())));
    }

};
                           
template <>
struct caller<void>
{
    template <class T>
    static PyObject* call(void (T::*pmf)(), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &self))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)();
        return detail::none();
    }

    template <class T, class A1>
    static PyObject* call(void (T::*pmf)(A1), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &self, &a1))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()));
        return detail::none();
    }

    template <class T, class A1, class A2>
    static PyObject* call(void (T::*pmf)(A1, A2), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &self, &a1, &a2))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3>
    static PyObject* call(void (T::*pmf)(A1, A2, A3), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &self, &a1, &a2, &a3))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOO"), &self, &a1, &a2, &a3, &a4))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOO"), &self, &a1, &a2, &a3, &a4, &a5))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6, A7), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8, A9), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()),
                        from_python(a10, type<A10>()));
        return detail::none();
    }


    template <class T>
    static PyObject* call(void (T::*pmf)() const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &self))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)();
        return detail::none();
    }

    template <class T, class A1>
    static PyObject* call(void (T::*pmf)(A1) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &self, &a1))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()));
        return detail::none();
    }

    template <class T, class A1, class A2>
    static PyObject* call(void (T::*pmf)(A1, A2) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &self, &a1, &a2))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3>
    static PyObject* call(void (T::*pmf)(A1, A2, A3) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &self, &a1, &a2, &a3))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOO"), &self, &a1, &a2, &a3, &a4))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOO"), &self, &a1, &a2, &a3, &a4, &a5))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6, A7) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()));
        return detail::none();
    }

    template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static PyObject* call(void (T::*pmf)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10) const, PyObject* args, PyObject* /* keywords */ ) {
        PyObject* self;
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOOO"), &self, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10))
            return 0;
        T& target = from_python(self, type<T&>());
        (target.*pmf)(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()),
                        from_python(a10, type<A10>()));
        return detail::none();
    }


    // Free functions
    static PyObject* call(void (*f)(), PyObject* args, PyObject* /* keywords */ ) {
        if (!PyArg_ParseTuple(args, const_cast<char*>("")))
            return 0;
        f();
        return detail::none();
    }

    template <class A1>
    static PyObject* call(void (*f)(A1), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        if (!PyArg_ParseTuple(args, const_cast<char*>("O"), &a1))
            return 0;
        f(from_python(a1, type<A1>()));
        return detail::none();
    }

    template <class A1, class A2>
    static PyObject* call(void (*f)(A1, A2), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OO"), &a1, &a2))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()));
        return detail::none();
    }

    template <class A1, class A2, class A3>
    static PyObject* call(void (*f)(A1, A2, A3), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOO"), &a1, &a2, &a3))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()));
        return detail::none();
    }

    template <class A1, class A2, class A3, class A4>
    static PyObject* call(void (*f)(A1, A2, A3, A4), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOO"), &a1, &a2, &a3, &a4))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()));
        return detail::none();
    }

    template <class A1, class A2, class A3, class A4, class A5>
    static PyObject* call(void (*f)(A1, A2, A3, A4, A5), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOO"), &a1, &a2, &a3, &a4, &a5))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()));
        return detail::none();
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6>
    static PyObject* call(void (*f)(A1, A2, A3, A4, A5, A6), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()));
        return detail::none();
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    static PyObject* call(void (*f)(A1, A2, A3, A4, A5, A6, A7), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()));
        return detail::none();
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    static PyObject* call(void (*f)(A1, A2, A3, A4, A5, A6, A7, A8), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()));
        return detail::none();
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    static PyObject* call(void (*f)(A1, A2, A3, A4, A5, A6, A7, A8, A9), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()));
        return detail::none();
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
    static PyObject* call(void (*f)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()),
                        from_python(a10, type<A10>()));
        return detail::none();
    }

    template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
    static PyObject* call(void (*f)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11), PyObject* args, PyObject* /* keywords */ ) {
        PyObject* a1;
        PyObject* a2;
        PyObject* a3;
        PyObject* a4;
        PyObject* a5;
        PyObject* a6;
        PyObject* a7;
        PyObject* a8;
        PyObject* a9;
        PyObject* a10;
        PyObject* a11;
        if (!PyArg_ParseTuple(args, const_cast<char*>("OOOOOOOOOOO"), &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8, &a9, &a10, &a11))
            return 0;
        f(from_python(a1, type<A1>()),
                        from_python(a2, type<A2>()),
                        from_python(a3, type<A3>()),
                        from_python(a4, type<A4>()),
                        from_python(a5, type<A5>()),
                        from_python(a6, type<A6>()),
                        from_python(a7, type<A7>()),
                        from_python(a8, type<A8>()),
                        from_python(a9, type<A9>()),
                        from_python(a10, type<A10>()),
                        from_python(a11, type<A11>()));
        return detail::none();
    }

};

}

#endif
