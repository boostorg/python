// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module_init.hpp>
#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/scope.hpp>
#include "test_class.hpp"

typedef test_class<> X;
typedef test_class<1> Y;

BOOST_PYTHON_MODULE_INIT(nested_ext)
{
    using namespace boost::python;

    // Establish X as the current scope.
    scope x_class(
        class_<X>("X", args<int>())
           .def(str(self))
        );

    // Y will now be defined in the current scope
    class_<Y>("Y", args<int>())
        .def(str(self))
        ;
}


#include "module_tail.cpp"



