// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef ARG_TO_PYTHON_BASE_DWA200237_HPP
# define ARG_TO_PYTHON_BASE_DWA200237_HPP
# include <boost/python/converter/to_python_function_type.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/handle.hpp>

namespace boost { namespace python { namespace converter {

namespace detail
{
  struct BOOST_PYTHON_DECL arg_to_python_base : handle<>
  {
      arg_to_python_base(void const volatile* source, to_python_function_t);
  };
}

}}} // namespace boost::python::converter

#endif // ARG_TO_PYTHON_BASE_DWA200237_HPP
