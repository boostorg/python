// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_DWA2002128_HPP
# define TO_PYTHON_DWA2002128_HPP

# include <boost/python/converter/to_python.hpp>
# include <boost/python/converter/source.hpp>

namespace boost { namespace python { 

template <class T>
struct to_python
    : converter::to_python_lookup<typename converter::source<T>::type>
{
};

// specialization for PyObject*
template <>
struct to_python<PyObject*>
{
    bool convertible() const { return true; }
    PyObject* operator()(PyObject* source) const { return source; }
};

template <>
struct to_python<PyObject*const&>
{
    bool convertible() const { return true; }
    PyObject* operator()(PyObject* source) const { return source; }
};

}} // namespace boost::python

#endif // TO_PYTHON_DWA2002128_HPP
