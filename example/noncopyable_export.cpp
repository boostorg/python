#include <boost/python/cross_module.hpp>
namespace python = boost::python;

#include "noncopyable.h"

BOOST_PYTHON_MODULE_INIT(noncopyable_export)
{
  try
  {
    python::module_builder this_module("noncopyable_export");

    python::class_builder<store> store_class(this_module, "store");
    python::export_converters_noncopyable(store_class);

    store_class.def(python::constructor<int>());
    store_class.def(&store::recall, "recall");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
