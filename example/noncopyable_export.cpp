#include <boost/python/class_builder.hpp>
#include <boost/python/detail/import_extension_class.hpp>
namespace python = boost::python;

#include "store.h"

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
