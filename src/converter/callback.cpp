// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/callback_to_python_base.hpp>
#include <boost/python/errors.hpp>
#include <boost/python/converter/find_from_python.hpp>
#include <boost/python/reference.hpp>
#include <boost/python/detail/none.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{

  namespace
  {
    inline PyObject* convert(void const volatile* source, to_python_function_t converter)
    {
        if (converter == 0)
        {
            PyErr_SetString(
                PyExc_TypeError
                , const_cast<char*>("no to_python (by-value) converter found for type"));
            throw error_already_set();
        }
        
        return source == 0
            ? python::detail::none()
            : converter(const_cast<void*>(source));
    }
  }
  
  callback_to_python_base::callback_to_python_base(
      void const volatile* source, to_python_function_t converter)
      : callback_to_python_holder(convert(source, converter))
  {
  }

  BOOST_PYTHON_DECL void throw_if_not_registered(rvalue_stage1_data const& data)
  {
      if (!data.convertible)
      {
          PyErr_SetString(
              PyExc_TypeError
              , const_cast<char*>("no from_python (by-value) converters found for type"));
          throw error_already_set();
      }
  }

  BOOST_PYTHON_DECL void throw_no_class_registered()
  {
      PyErr_SetString(
          PyExc_TypeError
          , const_cast<char*>("class not registered for to_python type"));
      throw error_already_set();
  }
  
  BOOST_PYTHON_DECL void* convert_rvalue(PyObject* src, rvalue_stage1_data& data, void* storage)
  {
      ref holder(src);
      
      data = find(src, static_cast<rvalue_from_python_registration*>(data.convertible));
      
      if (!data.convertible)
      {
          PyErr_SetString(
              PyExc_TypeError
              , const_cast<char*>("no registered from_python (by-value) converter was able to convert type"));
          throw error_already_set();
      }
      if (data.construct != 0)
          data.construct(src, &data);
      
      return data.convertible;
  }
}   

}}} // namespace boost::python::converter
