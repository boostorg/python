// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef CALLBACK_TO_PYTHON_BASE_DWA200237_HPP
# define CALLBACK_TO_PYTHON_BASE_DWA200237_HPP
# include <boost/python/converter/to_python_function_type.hpp>
# include <boost/python/detail/wrap_python.hpp>
# include <boost/python/reference.hpp>

namespace boost { namespace python { namespace converter {

namespace detail
{
  struct callback_to_python_holder
  {
      callback_to_python_holder(PyObject* obj);
      inline PyObject* get() const;
   private:
      ref m_held;
  };
  
  struct BOOST_PYTHON_DECL callback_to_python_base : callback_to_python_holder
  {
      callback_to_python_base(void const volatile* source, to_python_function_t);
  };

  //
  // implmentation
  //
  inline callback_to_python_holder::callback_to_python_holder(PyObject* obj)
      : m_held(obj)
  {
  }
  
  inline PyObject* callback_to_python_holder::get() const
  {
      return m_held.get();
  }
}

}}} // namespace boost::python::converter

#endif // CALLBACK_TO_PYTHON_BASE_DWA200237_HPP
