// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/arg_to_python_base.hpp>
#include <boost/python/errors.hpp>
#include <boost/python/converter/find_from_python.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/detail/none.hpp>
#include <boost/python/object.hpp>

namespace boost { namespace python { namespace converter { 

namespace detail
{

  namespace
  {
    inline PyObject* convert_to_python(void const volatile* source, to_python_function_t converter)
    {
        if (converter == 0)
        {
            PyErr_SetString(
                PyExc_TypeError
                , const_cast<char*>("no to_python (by-value) converter found for type"));
            throw_error_already_set();
        }
        
        return source == 0
            ? python::detail::none()
            : converter(const_cast<void*>(source));
    }
  }
  
  arg_to_python_base::arg_to_python_base(
      void const volatile* source, to_python_function_t converter)
# if !defined(BOOST_MSVC) || _MSC_FULL_VER != 13102140
      : handle<>(convert_to_python(source, converter))
# else
      : m_ptr(convert_to_python(source, converter))
# endif 
  {
  }

  BOOST_PYTHON_DECL void* callback_convert_reference(
      PyObject* source
      , registration const& converters)
  {
      handle<> holder(source);
      if (source->ob_refcnt <= 2)
      {
          PyErr_SetObject(
              PyExc_ReferenceError
              , (object("Attempt to return dangling pointer/reference to object of type ")
                 + converters.target_type.name()).ptr()
              );
          throw_error_already_set();
      }
      void* result = get_lvalue_from_python(source, converters);
      if (!result)
      {
          handle<> repr(PyObject_Repr(source));
          PyErr_SetObject(
              PyExc_TypeError
              , (object("no registered converter was able to convert ")
                 + repr + " to a C++ lvalue of type "
                 + converters.target_type.name()).ptr()
              );
          throw_error_already_set();
      }
      return result;
  }
  
  BOOST_PYTHON_DECL void* callback_convert_pointer(
      PyObject* source
      , registration const& converters)
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
      throw_error_already_set();
  }
  
  BOOST_PYTHON_DECL void* convert_rvalue(PyObject* src, rvalue_from_python_stage1_data& data, void* storage)
  {
      handle<> holder(src);

      void const* converters = data.convertible;
      data = rvalue_from_python_stage1(
          src, *static_cast<registration const*>(converters));
      
      if (!data.convertible)
      {
          PyErr_SetString(
              PyExc_TypeError
              , const_cast<char*>("no registered from_python lvalue or rvalue converter was able to convert object"));
          throw_error_already_set();
      }
      if (data.construct != 0)
          data.construct(src, &data);
      
      return data.convertible;
  }

  BOOST_PYTHON_DECL void absorb_result(PyObject* o)
  {
      Py_DECREF(expect_non_null(o));
  }
}   

}}} // namespace boost::python::converter
