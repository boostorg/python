// Copyright David Abrahams 2001. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/converter/registry.hpp>
#include <boost/python/converter/wrapper.hpp>

namespace boost { namespace python { namespace converter { 

wrapper_base::wrapper_base(type_id_t type)
    : body(type)
{
    registry::insert(*this);
}

wrapper_base::~wrapper_base()
{
    if (can_unregister())
        registry::remove(*this);
}

namespace
{
  // This doesn't actually get called, but we need something to fill
  // in the slot in the wrap<PyObject*> class.
  struct identity_wrapper_t : wrapper<PyObject*>
  {
      PyObject* convert(PyObject* source) const
      {
          return source;
      }
  };

  identity_wrapper_t identity_wrapper_object;
}

BOOST_PYTHON_DECL body& identity_wrapper = identity_wrapper_object;

}}} // namespace boost::python::converter
