// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_FUNCTION_DWA2002128_HPP
# define FROM_PYTHON_FUNCTION_DWA2002128_HPP

# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

struct from_python_data;

template <class T>
struct from_python_function
{
    typedef T (*type)(PyObject*, from_python_data&);
};

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_FUNCTION_DWA2002128_HPP
