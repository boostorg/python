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

PyObject* registration::to_python(void const volatile* source) const
{
    if (this->m_to_python == 0)
    {
        handle<> msg(
            ::PyString_FromFormat(
                "No to_python (by-value) converter found for C++ type: %s"
                , this->target_type.name()));
            
        PyErr_SetObject(PyExc_TypeError, msg.get());

        throw_error_already_set();
    }
        
    return source == 0
        ? incref(Py_None)
        : this->m_to_python(const_cast<void*>(source));
}

namespace detail
{
  arg_to_python_base::arg_to_python_base(
      void const volatile* source, registration const& converters)
# if !defined(BOOST_MSVC) || BOOST_MSVC <= 1300 || _MSC_FULL_VER > 13102179
      : handle<>
# else
      : m_ptr
# endif
         (converters.to_python(source))
  {
  }
}

}}} // namespace boost::python::converter
