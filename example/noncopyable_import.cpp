// Example by Ralf W. Grosse-Kunstleve
// See root/libs/python/doc/cross_module.html for an introduction.

#include <boost/python/cross_module.hpp>
namespace python = boost::python;

#include "noncopyable.h"

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

# ifdef BOOST_MSVC // fixes for JIT debugging
#  include <windows.h>
extern "C" void structured_exception_translator(unsigned int, EXCEPTION_POINTERS*)
{
    throw;
}
extern "C" void (*old_translator)(unsigned int, EXCEPTION_POINTERS*)
    = _set_se_translator(structured_exception_translator);
# endif

BOOST_PYTHON_MODULE_INIT(noncopyable_import)
{
    python::module_builder this_module("noncopyable_import");

    python::import_converters<store>
      dvect_converters("noncopyable_export", "store");

    // Imagine all the additional classes with member functions
    // that have store objects as input and output parameters.
    // Lots and lots of them.
    // However, to keep this example simple, we only define a
    // module-level function.
    this_module.def(add_stores, "add_stores");
}
