// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <string>
#include <boost/python/module.hpp>
#include <complex>

template <class T>
struct by_value
{
    static T rewrap(T x)
    {
        return x;
    }
};

template <class T>
struct by_const_reference
{
    static T rewrap(T const& x)
    {
        return x;
    }
};

BOOST_PYTHON_MODULE_INIT(builtin_converters)
{
    boost::python::module("builtin_converters")
        
        .def("rewrap_value_bool", by_value<bool>::rewrap)
        .def("rewrap_value_signed_char", by_value<signed char>::rewrap)
        .def("rewrap_value_unsigned_char", by_value<unsigned char>::rewrap)
        .def("rewrap_value_int", by_value<int>::rewrap)
        .def("rewrap_value_unsigned_int", by_value<unsigned int>::rewrap)
        .def("rewrap_value_short", by_value<short>::rewrap)
        .def("rewrap_value_unsigned_short", by_value<unsigned short>::rewrap)
        .def("rewrap_value_long", by_value<long>::rewrap)
        .def("rewrap_value_unsigned_long", by_value<unsigned long>::rewrap)
        .def("rewrap_value_float", by_value<float>::rewrap)
        .def("rewrap_value_double", by_value<double>::rewrap)
        .def("rewrap_value_long_double", by_value<long double>::rewrap)
        .def("rewrap_value_complex_float", by_value<std::complex<float> >::rewrap)
        .def("rewrap_value_complex_double", by_value<std::complex<double> >::rewrap)
        .def("rewrap_value_complex_long_double", by_value<std::complex<long double> >::rewrap)
        .def("rewrap_value_string", by_value<std::string>::rewrap)
        .def("rewrap_value_cstring", by_value<char const*>::rewrap)


        .def("rewrap_const_reference_bool", by_const_reference<bool>::rewrap)
        .def("rewrap_const_reference_signed_char", by_const_reference<signed char>::rewrap)
        .def("rewrap_const_reference_unsigned_char", by_const_reference<unsigned char>::rewrap)
        .def("rewrap_const_reference_int", by_const_reference<int>::rewrap)
        .def("rewrap_const_reference_unsigned_int", by_const_reference<unsigned int>::rewrap)
        .def("rewrap_const_reference_short", by_const_reference<short>::rewrap)
        .def("rewrap_const_reference_unsigned_short", by_const_reference<unsigned short>::rewrap)
        .def("rewrap_const_reference_long", by_const_reference<long>::rewrap)
        .def("rewrap_const_reference_unsigned_long", by_const_reference<unsigned long>::rewrap)
        .def("rewrap_const_reference_float", by_const_reference<float>::rewrap)
        .def("rewrap_const_reference_double", by_const_reference<double>::rewrap)
        .def("rewrap_const_reference_long_double", by_const_reference<long double>::rewrap)
        .def("rewrap_const_reference_complex_float", by_const_reference<std::complex<float> >::rewrap)
        .def("rewrap_const_reference_complex_double", by_const_reference<std::complex<double> >::rewrap)
        .def("rewrap_const_reference_complex_long_double", by_const_reference<std::complex<long double> >::rewrap)
        .def("rewrap_const_reference_string", by_const_reference<std::string>::rewrap)
        .def("rewrap_const_reference_cstring", by_const_reference<char const*>::rewrap)
        
        ;
}

