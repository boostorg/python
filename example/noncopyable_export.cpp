// Example by Ralf W. Grosse-Kunstleve
// See root/libs/python/doc/cross_module.html for an introduction.

#include <boost/python/cross_module.hpp>
namespace python = boost::python;

#include "noncopyable.h"

# ifdef BOOST_MSVC // fixes for JIT debugging
#  include <windows.h>
extern "C" void structured_exception_translator(unsigned int, EXCEPTION_POINTERS*)
{
    throw;
}
extern "C" void (*old_translator)(unsigned int, EXCEPTION_POINTERS*)
    = _set_se_translator(structured_exception_translator);
# endif

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
