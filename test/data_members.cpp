// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include "test_class.hpp"

using namespace boost::python;

typedef test_class<> X;

typedef test_class<1> Y;

BOOST_PYTHON_MODULE_INIT(data_members_ext)
{
    module("data_members_ext")
        .add(
            class_<X>("X")
            .def_init(args<int>())
            .def("value", &X::value)
            .def("set", &X::set)
            .def_readonly("x", &X::x)
            )
        .add(
            class_<Y>("Y")
            .def_init(args<int>())
            .def("value", &Y::value)
            .def("set", &Y::set)
            .def_readwrite("x", &Y::x)
            )
        ;
}

#include "module_tail.cpp"
