// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef FROM_PYTHON_FUNCTION_DWA2002128_HPP
# define FROM_PYTHON_FUNCTION_DWA2002128_HPP

# include <boost/python/detail/wrap_python.hpp>

namespace boost { namespace python { namespace converter { 

struct rvalue_stage1_data;
typedef void (*constructor_function)(PyObject* source, rvalue_stage1_data*);

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_FUNCTION_DWA2002128_HPP
