// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python/cast.hpp>
#include <boost/detail/lightweight_test.hpp>

struct X { long x; };
struct Y : X, PyObject {};

int main()
{
    PyTypeObject o;
    Y y;
    BOOST_TEST(boost::python::upcast<PyObject>(&o) == reinterpret_cast<PyObject*>(&o));
    BOOST_TEST(boost::python::upcast<PyObject>(&y) == &y);
    return boost::report_errors();
}
