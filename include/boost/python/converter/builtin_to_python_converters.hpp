// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef BUILTIN_TO_PYTHON_CONVERTERS_DWA2002129_HPP
# define BUILTIN_TO_PYTHON_CONVERTERS_DWA2002129_HPP
# include <string>
# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct to_python_lookup;

template <class T>
struct to_python_int
{
    bool convertible() const { return true; }
    PyObject* operator()(T x) const { return PyInt_FromLong(long(x)); }
};

# define BOOST_PYTHON_TO_INT(T) \
    template <> struct to_python_lookup<signed T const&> : to_python_int<signed T const&> {}; \
    template <> struct to_python_lookup<unsigned T const&> : to_python_int<unsigned T const&> {};

BOOST_PYTHON_TO_INT(char)
BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)
# undef BOOST_TO_PYTHON_INT

template <>
struct to_python_lookup<char const*const&>
{
    bool convertible() const { return true; }
    PyObject* operator()(char const* x) const { return PyString_FromString(x); }
};
    
template <>
struct to_python_lookup<std::string const&>
{
    bool convertible() const { return true; }
    PyObject* operator()(std::string const& x) const
    {
        return PyString_FromString(x.c_str());
    }
};

template <>
struct to_python_lookup<float const&>
{
    bool convertible() const { return true; }
    PyObject* operator()(float x) const { return PyFloat_FromDouble(x); }
};
    
template <>
struct to_python_lookup<double const&>
{
    bool convertible() const { return true; }
    PyObject* operator()(double x) const { return PyFloat_FromDouble(x); }
};
    
template <>
struct to_python_lookup<long double const&>
{
    bool convertible() const { return true; }
    PyObject* operator()(long double x) const
    {
        return PyFloat_FromDouble(x);
    }
};
    
}}} // namespace boost::python::converter

#endif // BUILTIN_TO_PYTHON_CONVERTERS_DWA2002129_HPP
