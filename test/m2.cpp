// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

// This module exercises the converters exposed in m1 at a low level
// by exposing raw Python extension functions that use wrap<> and
// unwrap<> objects.
#include <boost/python/convert.hpp>
#include <boost/python/module.hpp>
#include "simple_type.hpp"

using boost::python::wrap;
using boost::python::unwrap;

// Get a simple (by value) from the argument, and return the
// string it holds.
PyObject* unwrap_simple(simple x)
{
    return PyString_FromString(x.s);
}

// Likewise, but demands that its possible to get a non-const
// reference to the simple.
PyObject* unwrap_simple_ref(simple& x)
{
    return PyString_FromString(x.s);
}

// Likewise, with a const reference to the simple object.
PyObject* unwrap_simple_const_ref(simple const& x)
{
    return PyString_FromString(x.s);
}

// Get an int (by value) from the argument, and convert it to a
// Python Int.
PyObject* unwrap_int(int x)
{
    return PyInt_FromLong(x);
}

// Get a non-const reference to an int from the argument
PyObject* unwrap_int_ref(int& x)
{
    return PyInt_FromLong(x);
}

// Get a const reference to an  int from the argument.
PyObject* unwrap_int_const_ref(int const& x)
{
    return PyInt_FromLong(x);
}

// MSVC6 bug workaround
template <class T> struct xxxx;

// rewrap<T> extracts a T from the argument, then converts the T back
// to a PyObject* and returns it.
template <class T>
struct rewrap
{
    static T f(T x) { return x; }
};

BOOST_PYTHON_MODULE_INIT(m2)
{
    boost::python::module("m2")
        .def("unwrap_int", unwrap_int)
        .def("unwrap_int_ref", unwrap_int_ref)
        .def("unwrap_int_const_ref", unwrap_int_const_ref)
        .def("unwrap_simple", unwrap_simple)
        .def("unwrap_simple_ref", unwrap_simple_ref)
        .def("unwrap_simple_const_ref", unwrap_simple_const_ref)

        .def("wrap_int", &rewrap<int>::f)
        .def("wrap_int_ref", &rewrap<int&>::f)
        .def("wrap_int_const_ref", &rewrap<int const&>::f)
        .def("wrap_simple", &rewrap<simple>::f)
        .def("wrap_simple_ref", &rewrap<simple&>::f)
        .def("wrap_simple_const_ref", &rewrap<simple const&>::f)
        ;
}

#include "module_tail.cpp"
