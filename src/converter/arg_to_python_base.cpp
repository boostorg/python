// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/arg_to_python_base.hpp>
#include <boost/python/errors.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/refcount.hpp>

namespace boost { namespace python { namespace converter { 

namespace
{
    inline PyObject* convert_to_python(void const volatile* source, registration const& converters)
    {
        if (converters.to_python == 0)
        {
            handle<> msg(
                ::PyString_FromFormat(
                    "No to_python (by-value) converter found for C++ type: %s"
                    , converters.target_type.name()));
            
            PyErr_SetObject(PyExc_TypeError, msg.get());

            throw_error_already_set();
        }
        
        return source == 0
            ? incref(Py_None)
            : converters.to_python(const_cast<void*>(source));
    }
}

namespace detail
{
  arg_to_python_base::arg_to_python_base(
      void const volatile* source, registration const& converters)
# if !defined(BOOST_MSVC) || BOOST_MSVC <= 1300 || _MSC_FULL_VER > 13102179
      : handle<>(converter::convert_to_python(source, converters))
# else
      : m_ptr(converter::convert_to_python(source, converters))
# endif 
  {
  }

  BOOST_PYTHON_DECL void throw_no_class_registered()
  {
      PyErr_SetString(
          PyExc_TypeError
          , const_cast<char*>("class not registered for to_python type"));
      throw_error_already_set();
  }
}

}}} // namespace boost::python::converter
