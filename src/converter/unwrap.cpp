// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/unwrap.hpp>

namespace boost { namespace python { namespace converter { 

namespace
{
  struct pyobject_unwrapper : unwrapper_base
  {
      pyobject_unwrapper();
      bool convertible(PyObject*) const;
  };
  
  pyobject_unwrapper static_unwrapper;

  pyobject_unwrapper::pyobject_unwrapper()
      : unwrapper_base(type_id<PyObject*>())
  {
  }
      
  bool pyobject_unwrapper::convertible(PyObject*) const
  {
      return true;
  }
}

BOOST_PYTHON_EXPORT unwrapper_base*
unwrap_more_<PyObject*>::m_unwrapper = &static_unwrapper;

}}} // namespace boost::python::converter
