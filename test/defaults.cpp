// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/list.hpp>

#if defined(_AIX) && defined(__EDG_VERSION__) && __EDG_VERSION__ < 245
# include <iostream> // works around a KCC intermediate code generation bug
#endif

using namespace boost::python;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
object
bar(int a, char b, std::string c, double d)
{
    list abcd;
    abcd.append(a);
    abcd.append(b);
    abcd.append(c);
    abcd.append(d);
    return "int(%s); char(%s); string(%s); double(%s); " % tuple(abcd);
}

object
bar(int a, char b, std::string c)
{
    list abcd;
    abcd.append(a);
    abcd.append(b);
    abcd.append(c);
    abcd.append(0.0);
    return "int(%s); char(%s); string(%s); double(%s); " % tuple(abcd);
}

object
bar(int a, char b)
{
    list abcd;
    abcd.append(a);
    abcd.append(b);
    abcd.append("default");
    abcd.append(0.0);
    return "int(%s); char(%s); string(%s); double(%s); " % tuple(abcd);
}

object
bar(int a)
{
    list abcd;
    abcd.append(a);
    abcd.append('D');
    abcd.append("default");
    abcd.append(0.0);
    return "int(%s); char(%s); string(%s); double(%s); " % tuple(abcd);
}

BOOST_PYTHON_FUNCTION_GENERATOR(bar_stubs, bar, 1, 4)

///////////////////////////////////////////////////////////////////////////////
object
foo(int a, char b = 'D', std::string c = "default", double d = 0.0)
{
    list abcd;
    abcd.append(a);
    abcd.append(b);
    abcd.append(c);
    abcd.append(d);
    return "int(%s); char(%s); string(%s); double(%s); " % tuple(abcd);
}

BOOST_PYTHON_FUNCTION_GENERATOR(foo_stubs, foo, 1, 4)

///////////////////////////////////////////////////////////////////////////////

struct X {

    object
    bar(int a, char b = 'D', std::string c = "default", double d = 0.0) const
    {
        list abcd;
        abcd.append(a);
        abcd.append(b);
        abcd.append(c);
        abcd.append(d);
        return "int(%s); char(%s); string(%s); double(%s); " % tuple(abcd);
    }
};

BOOST_PYTHON_MEM_FUN_GENERATOR(X_bar_stubs, bar, 1, 4)

///////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MODULE_INIT(defaults_ext)
{
    module      m("defaults_ext");
    m.def("foo", foo, foo_stubs());
    m.def("bar", signature<object(*)(int, char, std::string, double)>(), bar_stubs());

    class_<X>   xc("X");
    m.add(xc);

    xc.def_init();
    xc.def("bar", X::bar, X_bar_stubs());
}

#include "module_tail.cpp"
