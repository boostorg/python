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
  struct BOOST_PYTHON_DECL arg_to_python_base
# if !defined(BOOST_MSVC) || _MSC_FULL_VER != 13102140
      : handle<>
# endif 
  {
      arg_to_python_base(void const volatile* source, to_python_function_t);
# if defined(BOOST_MSVC) && _MSC_FULL_VER == 13102140
      PyObject* get() const { return m_ptr.get(); }
      PyObject* release() { return m_ptr.release(); }
   private:
      handle<> m_ptr;
# endif 
  };
}

}}} // namespace boost::python::converter

#endif // ARG_TO_PYTHON_BASE_DWA200237_HPP
