// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <sstream>

#if defined(_AIX) && defined(__EDG_VERSION__) && __EDG_VERSION__ < 245
# include <iostream> // works around a KCC intermediate code generation bug
#endif

using namespace boost::python;
using namespace std;

///////////////////////////////////////////////////////////////////////////////

std::string
foo(int a, char b = 'D', std::string c = "default", double d = 0.0)
{
    std::stringstream stream;
    stream << "int("    << a << "); ";
    stream << "char("   << b << "); ";
    stream << "string(" << c  << "); ";
    stream << "double(" << d << "); ";
    return stream.str();
}

BOOST_PYTHON_FUNCTION_GEN(foo_stubs, foo, 1, 4)

///////////////////////////////////////////////////////////////////////////////

struct X {

    std::string
    bar(int a, char b = 'D', std::string c = "default", double d = 0.0) const
    {
        std::stringstream stream;
        stream << "int("    << a << "); ";
        stream << "char("   << b << "); ";
        stream << "string(" << c  << "); ";
        stream << "double(" << d << "); ";
        return stream.str();
    }
};

BOOST_PYTHON_MEMBER_FUNCTION_GEN(X_bar_stubs, bar, 1, 4)

///////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MODULE_INIT(defaults_ext)
{
    module      m("defaults_ext");
    m.def(foo_stubs(), signature<std::string(*)(int, char, std::string, double)>());

    class_<X>   xc("X");
    m.add(xc);

    xc.def_init();
    xc.def(X_bar_stubs(), signature<std::string(X::*)(int, char, std::string, double)>());
}

#include "module_tail.cpp"
