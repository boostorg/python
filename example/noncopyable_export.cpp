#include <boost/python/x_class_builder.hpp>
namespace python = boost::python;

#include "noncopyable.h"

extern "C"
DL_EXPORT(void)
initnoncopyable_export()
{
  try
  {
    python::module_builder this_module("noncopyable_export");

    python::xptr_class_builder<store> store_class(this_module, "store");

    store_class.def(python::constructor<int>());
    store_class.def(&store::recall, "recall");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
