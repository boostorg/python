//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.
//
//  This file generated for 5-argument member functions and 6-argument free
//  functions by gen_caller.python

#ifndef CALLER_DWA05090_H_
# define CALLER_DWA05090_H_

# include "pyconfig.h"
# include "wrap_python.h"
# include <boost/config.hpp>
# include "signatures.h"
# include "none.h"
# include "objects.h"

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

};

namespace detail
{
                     
// create signature tuples
inline
PyObject* function_signature() {
    tuple result(0);

    return result.reference().release();
}

template <class A1>
PyObject* function_signature(type<A1>) {
    static const bool is_plain_A1 = BOOST_PYTHON_IS_PLAIN(A1);
    tuple result(1);
    result.set_item(0, python_type_name_selector<is_plain_A1>::get(type<A1>()));

    return result.reference().release();
}

template <class A1, class A2>
PyObject* function_signature(type<A1>, type<A2>) {
    static const bool is_plain_A1 = BOOST_PYTHON_IS_PLAIN(A1);
    static const bool is_plain_A2 = BOOST_PYTHON_IS_PLAIN(A2);
    tuple result(2);
    result.set_item(0, python_type_name_selector<is_plain_A1>::get(type<A1>()));
    result.set_item(1, python_type_name_selector<is_plain_A2>::get(type<A2>()));

    return result.reference().release();
}

template <class A1, class A2, class A3>
PyObject* function_signature(type<A1>, type<A2>, type<A3>) {
    static const bool is_plain_A1 = BOOST_PYTHON_IS_PLAIN(A1);
    static const bool is_plain_A2 = BOOST_PYTHON_IS_PLAIN(A2);
    static const bool is_plain_A3 = BOOST_PYTHON_IS_PLAIN(A3);
    tuple result(3);
    result.set_item(0, python_type_name_selector<is_plain_A1>::get(type<A1>()));
    result.set_item(1, python_type_name_selector<is_plain_A2>::get(type<A2>()));
    result.set_item(2, python_type_name_selector<is_plain_A3>::get(type<A3>()));

    return result.reference().release();
}

template <class A1, class A2, class A3, class A4>
PyObject* function_signature(type<A1>, type<A2>, type<A3>, type<A4>) {
    static const bool is_plain_A1 = BOOST_PYTHON_IS_PLAIN(A1);
    static const bool is_plain_A2 = BOOST_PYTHON_IS_PLAIN(A2);
    static const bool is_plain_A3 = BOOST_PYTHON_IS_PLAIN(A3);
    static const bool is_plain_A4 = BOOST_PYTHON_IS_PLAIN(A4);
    tuple result(4);
    result.set_item(0, python_type_name_selector<is_plain_A1>::get(type<A1>()));
    result.set_item(1, python_type_name_selector<is_plain_A2>::get(type<A2>()));
    result.set_item(2, python_type_name_selector<is_plain_A3>::get(type<A3>()));
    result.set_item(3, python_type_name_selector<is_plain_A4>::get(type<A4>()));

    return result.reference().release();
}

template <class A1, class A2, class A3, class A4, class A5>
PyObject* function_signature(type<A1>, type<A2>, type<A3>, type<A4>, type<A5>) {
    static const bool is_plain_A1 = BOOST_PYTHON_IS_PLAIN(A1);
    static const bool is_plain_A2 = BOOST_PYTHON_IS_PLAIN(A2);
    static const bool is_plain_A3 = BOOST_PYTHON_IS_PLAIN(A3);
    static const bool is_plain_A4 = BOOST_PYTHON_IS_PLAIN(A4);
    static const bool is_plain_A5 = BOOST_PYTHON_IS_PLAIN(A5);
    tuple result(5);
    result.set_item(0, python_type_name_selector<is_plain_A1>::get(type<A1>()));
    result.set_item(1, python_type_name_selector<is_plain_A2>::get(type<A2>()));
    result.set_item(2, python_type_name_selector<is_plain_A3>::get(type<A3>()));
    result.set_item(3, python_type_name_selector<is_plain_A4>::get(type<A4>()));
    result.set_item(4, python_type_name_selector<is_plain_A5>::get(type<A5>()));

    return result.reference().release();
}

template <class A1, class A2, class A3, class A4, class A5, class A6>
PyObject* function_signature(type<A1>, type<A2>, type<A3>, type<A4>, type<A5>, type<A6>) {
    static const bool is_plain_A1 = BOOST_PYTHON_IS_PLAIN(A1);
    static const bool is_plain_A2 = BOOST_PYTHON_IS_PLAIN(A2);
    static const bool is_plain_A3 = BOOST_PYTHON_IS_PLAIN(A3);
    static const bool is_plain_A4 = BOOST_PYTHON_IS_PLAIN(A4);
    static const bool is_plain_A5 = BOOST_PYTHON_IS_PLAIN(A5);
    static const bool is_plain_A6 = BOOST_PYTHON_IS_PLAIN(A6);
    tuple result(6);
    result.set_item(0, python_type_name_selector<is_plain_A1>::get(type<A1>()));
    result.set_item(1, python_type_name_selector<is_plain_A2>::get(type<A2>()));
    result.set_item(2, python_type_name_selector<is_plain_A3>::get(type<A3>()));
    result.set_item(3, python_type_name_selector<is_plain_A4>::get(type<A4>()));
    result.set_item(4, python_type_name_selector<is_plain_A5>::get(type<A5>()));
    result.set_item(5, python_type_name_selector<is_plain_A6>::get(type<A6>()));

    return result.reference().release();
}


// member functions
template <class R, class T>
inline PyObject* function_signature(R (T::*pmf)()) {
    return function_signature(
        python::type<T>());
}

template <class R, class T, class A1>
inline PyObject* function_signature(R (T::*pmf)(A1)) {
    return function_signature(
        python::type<T>(),
        python::type<A1>());
}

template <class R, class T, class A1, class A2>
inline PyObject* function_signature(R (T::*pmf)(A1, A2)) {
    return function_signature(
        python::type<T>(),
        python::type<A1>(),
        python::type<A2>());
}

template <class R, class T, class A1, class A2, class A3>
inline PyObject* function_signature(R (T::*pmf)(A1, A2, A3)) {
    return function_signature(
        python::type<T>(),
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>());
}

template <class R, class T, class A1, class A2, class A3, class A4>
inline PyObject* function_signature(R (T::*pmf)(A1, A2, A3, A4)) {
    return function_signature(
        python::type<T>(),
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>(),
        python::type<A4>());
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5>
inline PyObject* function_signature(R (T::*pmf)(A1, A2, A3, A4, A5)) {
    return function_signature(
        python::type<T>(),
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>(),
        python::type<A4>(),
        python::type<A5>());
}


// const member functions
template <class R, class T>
inline PyObject* function_signature(R (T::*pmf)() const) {
    return function_signature(
        python::type<T>());
}

template <class R, class T, class A1>
inline PyObject* function_signature(R (T::*pmf)(A1) const) {
    return function_signature(
        python::type<T>(),
        python::type<A1>());
}

template <class R, class T, class A1, class A2>
inline PyObject* function_signature(R (T::*pmf)(A1, A2) const) {
    return function_signature(
        python::type<T>(),
        python::type<A1>(),
        python::type<A2>());
}

template <class R, class T, class A1, class A2, class A3>
inline PyObject* function_signature(R (T::*pmf)(A1, A2, A3) const) {
    return function_signature(
        python::type<T>(),
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>());
}

template <class R, class T, class A1, class A2, class A3, class A4>
inline PyObject* function_signature(R (T::*pmf)(A1, A2, A3, A4) const) {
    return function_signature(
        python::type<T>(),
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>(),
        python::type<A4>());
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5>
inline PyObject* function_signature(R (T::*pmf)(A1, A2, A3, A4, A5) const) {
    return function_signature(
        python::type<T>(),
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>(),
        python::type<A4>(),
        python::type<A5>());
}


// free functions
template <class R>
inline PyObject* function_signature(R (*f)()) {
    return function_signature();
}

template <class R, class A1>
inline PyObject* function_signature(R (*f)(A1)) {
    return function_signature(
        python::type<A1>());
}

template <class R, class A1, class A2>
inline PyObject* function_signature(R (*f)(A1, A2)) {
    return function_signature(
        python::type<A1>(),
        python::type<A2>());
}

template <class R, class A1, class A2, class A3>
inline PyObject* function_signature(R (*f)(A1, A2, A3)) {
    return function_signature(
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>());
}

template <class R, class A1, class A2, class A3, class A4>
inline PyObject* function_signature(R (*f)(A1, A2, A3, A4)) {
    return function_signature(
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>(),
        python::type<A4>());
}

template <class R, class A1, class A2, class A3, class A4, class A5>
inline PyObject* function_signature(R (*f)(A1, A2, A3, A4, A5)) {
    return function_signature(
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>(),
        python::type<A4>(),
        python::type<A5>());
}

template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline PyObject* function_signature(R (*f)(A1, A2, A3, A4, A5, A6)) {
    return function_signature(
        python::type<A1>(),
        python::type<A2>(),
        python::type<A3>(),
        python::type<A4>(),
        python::type<A5>(),
        python::type<A6>());
}

} // namespace detail

} // namespace python

#endif // CALLER_DWA05090_H_

