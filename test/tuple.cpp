#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/tuple.hpp>

using namespace boost::python;

object convert_to_tuple(object data)
{
    return tuple(data);
}

void test_operators(tuple t1, tuple t2, object print)
{
    print(t1 + t2);
}

BOOST_PYTHON_MODULE_INIT(tuple_ext)
{
    module("tuple_ext")
        .def("convert_to_tuple",convert_to_tuple)
        .def("test_operators",test_operators)
        ;
}
