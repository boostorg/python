// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/list.hpp>

#if defined(_AIX) && defined(__EDG_VERSION__) && __EDG_VERSION__ < 245
# include <iostream> // works around a KCC intermediate code generation bug
#endif

using namespace boost::python;
using namespace std;

char const* const format = "int(%s); char(%s); string(%s); double(%s); ";

///////////////////////////////////////////////////////////////////////////////
object
bar(int a, char b, std::string c, double d)
{
    return format % make_tuple(a, b, c, d);
}

object
bar(int a, char b, std::string c)
{
    return format % make_tuple(a, b, c, 0.0);
}

object
bar(int a, char b)
{
    return format % make_tuple(a, b, "default", 0.0);
}

object
bar(int a)
{
    return format % make_tuple(a, 'D', "default", 0.0);
}

BOOST_PYTHON_FUNCTION_GENERATOR(bar_stubs, bar, 1, 4)

///////////////////////////////////////////////////////////////////////////////
object
foo(int a, char b = 'D', std::string c = "default", double d = 0.0)
{
    return format % make_tuple(a, b, c, d);
}

BOOST_PYTHON_FUNCTION_GENERATOR(foo_stubs, foo, 1, 4)

///////////////////////////////////////////////////////////////////////////////

struct X {

    object
    bar(int a, char b = 'D', std::string c = "default", double d = 0.0) const
    {
        return format % make_tuple(a, b, c, d);
    }

    object
    foo(int a, bool b=false) const
    {
        return "int(%s); bool(%s); " % make_tuple(a, b);
    }

    object
    foo(std::string a, bool b=false) const
    {
        return "string(%s); bool(%s); " % make_tuple(a, b);
    }

    object
    foo(list a, list b, bool c=false) const
    {
        return "list(%s); list(%s); bool(%s); " % make_tuple(a, b, c);
    }
};

BOOST_PYTHON_MEM_FUN_GENERATOR(X_bar_stubs, bar, 1, 4)
BOOST_PYTHON_MEM_FUN_GENERATOR(X_foo_2_stubs, foo, 1, 2)
BOOST_PYTHON_MEM_FUN_GENERATOR(X_foo_3_stubs, foo, 2, 3)

///////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MODULE_INIT(defaults_ext)
{
    module("defaults_ext")
        .def("foo", foo, foo_stubs())

#if !(defined(BOOST_MSVC) && (BOOST_MSVC <= 1200))
        .def("bar", signature<object(*)(int, char, std::string, double)>(), bar_stubs())
#else // signature does not work on VC6 only (VC7 is ok)
        .def("bar", (object(*)(int, char, std::string, double))0, bar_stubs())
#endif
        ;

    class_<X>("X")
        .def("bar", &X::bar, X_bar_stubs())
        .def("foo", (object(X::*)(std::string, bool) const)0, X_foo_2_stubs())

#if !(defined(BOOST_MSVC) && (BOOST_MSVC <= 1200))
        .def("foo", signature<object(X::*)(int, bool) const>(), X_foo_2_stubs())
#else // signature does not work on VC6 only (VC7 is ok)
        .def("foo", (object(X::*)(int, bool) const)0, X_foo_2_stubs())
#endif

        .def("foo", (object(X::*)(list, list, bool) const)0, X_foo_3_stubs())
        ;
}

#include "module_tail.cpp"

