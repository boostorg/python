#include <boost/python/class_builder.hpp>
#include <boost/python/detail/import_extension_class.hpp>
namespace python = boost::python;

#include "store.h"

namespace { // Avoid cluttering the global namespace.

  // A function with store objects as both input and output parameters.
  // Because the copy constructor is disabled, we cannot pass a store
  // object by value. Instead, we pass a smart pointer.
  std::auto_ptr<store> add_stores(const store& s1, const store& s2)
  {
    int sum = s1.recall() + s2.recall();
    std::auto_ptr<store> ss = std::auto_ptr<store>(new store(sum));
    return ss;
  }
}

extern "C"
DL_EXPORT(void)
initnoncopyable_import()
{
  try
  {
    python::module_builder this_module("noncopyable_import");

    python::import_class_builder<store>
      dvect_class("noncopyable_export", "store");

    // Imagine all the additional classes with member functions
    // that have store objects as input and output parameters.
    // Lots and lots of them.
    // However, to keep this example simple, we only define a
    // module-level function.
    this_module.def(add_stores, "add_stores");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
