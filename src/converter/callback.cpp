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
              , const_cast<char*>("no from_python rvalue or lvalue converters found for type"));
          throw error_already_set();
      }
  }

  BOOST_PYTHON_DECL void throw_if_not_registered(lvalue_from_python_registration*const& x)
  {
      if (!x)
      {
          PyErr_SetString(
              PyExc_TypeError
              , const_cast<char*>("no from_python lvalue converters found for type"));
          throw error_already_set();
      }
  }

  BOOST_PYTHON_DECL void* callback_convert_reference(
      PyObject* source
      , lvalue_from_python_registration*const& converters)
  {
      ref holder(source);
      void* result = find(source, converters);
      if (!result)
      {
          PyErr_SetString(
              PyExc_TypeError
              , const_cast<char*>("no registered from_python lvalue converter was able to convert object"));
          throw error_already_set();
      }
      return result;
  }
  
  BOOST_PYTHON_DECL void* callback_convert_pointer(
      PyObject* source
      , lvalue_from_python_registration*const& converters)
  {
      if (source == Py_None)
      {
          Py_DECREF(source);
          return 0;
      }
      return callback_convert_reference(source, converters);
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
              , const_cast<char*>("no registered from_python lvalue or rvalue converter was able to convert object"));
          throw error_already_set();
      }
      if (data.construct != 0)
          data.construct(src, &data);
      
      return data.convertible;
  }
}   

}}} // namespace boost::python::converter
