// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef TO_PYTHON_FUNCTION_DWA2002128_HPP
# define TO_PYTHON_FUNCTION_DWA2002128_HPP

# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

typedef PyObject* (*to_python_function_base)(void);

template <class T>
struct to_python_function
{
    typedef PyObject*(*type)(T);
};

}}} // namespace boost::python::converter

#endif // TO_PYTHON_FUNCTION_DWA2002128_HPP
