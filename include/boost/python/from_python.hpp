// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_DWA2002128_HPP
# define FROM_PYTHON_DWA2002128_HPP

# include <boost/python/converter/from_python.hpp>
# include <boost/python/converter/target.hpp>

namespace boost { namespace python { 

template <class T>
struct from_python
    : converter::from_python_lookup<typename converter::target<T>::type>
{
    typedef converter::from_python_lookup<typename converter::target<T>::type> base;
    from_python(PyObject*);
};

// specialization for PyObject*
template <>
struct from_python<PyObject*>
{
    from_python(PyObject*) {}
    bool convertible() const { return true; }
    PyObject* operator()(PyObject* source) const { return source; }
};

//
// implementations
//
template <class T>
from_python<T>::from_python(PyObject* source)
    : base(source)
{
}

}} // namespace boost::python

#endif // FROM_PYTHON_DWA2002128_HPP
