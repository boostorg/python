// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/object.hpp>
#include <boost/python/tuple_converter.hpp>
#include <boost/tuple/tuple.hpp>
#include <string>

using namespace boost::python;

boost::tuple<int> test_tuple_int(boost::tuple<int> t)
{
    return t;
}

boost::tuple<int, std::string> test_tuple_int_string(boost::tuple<int, std::string> t)
{
    return t;
}

BOOST_PYTHON_MODULE(tuple_converter_ext)
{
    tuple_converter<boost::tuple<int> >();
    tuple_converter<boost::tuple<int, std::string> >();

    def("test_tuple_int", test_tuple_int);
    def("test_tuple_int_string", test_tuple_int_string);
}

#include "module_tail.cpp"
