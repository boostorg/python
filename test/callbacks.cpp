// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module.hpp>
#include <boost/python/returning.hpp>
#include <boost/python/class.hpp>
#include <boost/ref.hpp>

using namespace boost::python;

int apply_int_int(PyObject* f, int x)
{
    return returning<int>::call(f, x);
}

void apply_void_int(PyObject* f, int x)
{
    returning<void>::call(f, x);
}

struct X
{
    explicit X(int x) : x(x), magic(7654321) { ++counter; }
    X(X const& rhs) : x(rhs.x), magic(7654321) { ++counter; }
    ~X() { assert(magic == 7654321); magic = 6666666; x = 9999; --counter; }

    void set(int x) { assert(magic == 7654321); this->x = x; }
    int value() const { assert(magic == 7654321); return x; }
    static int count() { return counter; }
 private:
    void operator=(X const&);
 private:
    int x;
    long magic;
    static int counter;
};

X apply_X_X(PyObject* f, X x)
{
    return returning<X>::call(f, x);
}

void apply_void_X_ref(PyObject* f, X x)
{
    returning<X>::call(f, boost::ref(x));
}

int X::counter;

BOOST_PYTHON_MODULE_INIT(callbacks_ext)
{
    boost::python::module("callbacks_ext")
        .def("apply_int_int", apply_int_int)
        .def("apply_void_int", apply_void_int)
        .def("apply_X_X", apply_X_X)
        .def("apply_void_X_ref", apply_void_X_ref)
        .add(
            class_<X>("X")
            .def_init(args<int>())
            .def_init(args<X const&>())
            .def("value", &X::value)
            .def("set", &X::set)
            )
        .def("x_count", &X::count)
        ;
}



