// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include "test_class.hpp"

#if defined(_AIX) && defined(__EDG_VERSION__) && __EDG_VERSION__ < 245
# include <iostream> // works around a KCC intermediate code generation bug
#endif


using namespace boost::python;

typedef test_class<> X;

typedef test_class<1> Y;

double get_fair_value(X const& x) { return x.value(); }

BOOST_PYTHON_MODULE_INIT(data_members_ext)
{
    class_<X>("X", args<int>())
        .def("value", &X::value)
        .def("set", &X::set)
        .def_readonly("x", &X::x)
        .add_property("get_fair_value", object(&get_fair_value))
        ;
    
    class_<Y>("Y", args<int>())
        .def("value", &Y::value)
        .def("set", &Y::set)
        .def_readwrite("x", &Y::x)
        ;
}

#include "module_tail.cpp"
