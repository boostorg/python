// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/class.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/module.hpp>
#include "test_class.hpp"

// This test shows that a class can be wrapped "as itself" but also
// acquire a back-reference iff has_back_reference<> is appropriately
// specialized.
using namespace boost::python;

typedef test_class<> X;

int x_value(X const& x)
{
    return x.value();
}

BOOST_PYTHON_MODULE_INIT(implicit_ext)
{
    implicitly_convertible<int,X>();
    module("implicit_ext")
        .def("x_value", x_value)
        .add(
            class_<X>("X")
            .def_init(args<int>())
            .def("value", &X::value)
            .def("set", &X::set)
            )
        ;
}

#include "module_tail.cpp"
