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
      void* can_convert(PyObject*) const;
  };
  
  pyobject_unwrapper static_unwrapper;
  std::pair<unwrapper_base*,void*> unwrapper_pair(&static_unwrapper,&static_unwrapper);  

  pyobject_unwrapper::pyobject_unwrapper()
      : unwrapper_base(type_id<PyObject*>())
  {
  }
      
  void* pyobject_unwrapper::can_convert(PyObject*) const
  {
      return non_null;
  }
}

BOOST_PYTHON_DECL std::pair<unwrapper_base*,void*>&
unwrap_more_<PyObject*>::m_unwrapper = unwrapper_pair;

}}} // namespace boost::python::converter
