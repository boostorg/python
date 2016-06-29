// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/object.hpp>
#include <boost/python/class.hpp>

using namespace boost::python;

struct X
{
    int x;
    int foo;
    X(int n) : x(n), foo(0){ }
};

int x_function(X& x)
{   return x.x;
}

int y_function(X& x)
{   return x.foo++;
}

BOOST_PYTHON_MODULE(class_ext)
{
    class_<X>("X", init<int>());
    def("x_function", x_function);
#if (__cplusplus > 199711L) && !defined(BOOST_NO_CXX11_LAMBDAS)
    def("y_function", [&foo](int) -> int { return foo++; });
#else
    def("y_function", y_function);

#endif
}

#include "module_tail.cpp"
