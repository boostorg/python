// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/enum.hpp>
#include <boost/python/def.hpp>
#include <boost/python/module.hpp>

using namespace boost::python;

enum color { red = 1, green = 2, blue = 4 };

color identity_(color x) { return x; }

BOOST_PYTHON_MODULE(enum_ext)
{
    enum_<color>("color")
        .value("red", red)
        .value("green", green)
        .value("blue", blue)
        .export_values()
        ;
    
    def("identity", identity_);
}

#include "module_tail.cpp"
