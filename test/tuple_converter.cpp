// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/object.hpp>
#include <boost/tuple/tuple.hpp>

using namespace boost::python;

void in_tuple1(boost::tuple<int> t)
{
}


BOOST_PYTHON_MODULE(tuple_converter_ext)
{
    def("in_tuple1", in_tuple1);
}

#include "module_tail.cpp"
