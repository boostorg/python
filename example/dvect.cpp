// Example by Ralf W. Grosse-Kunstleve
// See root/libs/python/doc/cross_module.html for an introduction.

#include "dvect.h"
#include "ivect.h"
#include <boost/python/cross_module.hpp>
namespace python = boost::python;

namespace {

# include "dvect_conversions.cpp"
# include "ivect_conversions.cpp"

  vects::ivect dvect_as_ivect(const vects::dvect& dv)
  {
    vects::ivect iv(dv.size());
    vects::ivect::iterator iviter = iv.begin();
    for (int i = 0; i < dv.size(); i++) iviter[i] = static_cast<int>(dv[i]);
    return iv;
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

BOOST_PYTHON_MODULE_INIT(dvect)
{
  try
  {
    python::module_builder this_module("dvect");

    python::class_builder<vects::dvect> dvect_class(this_module, "dvect");
    python::export_converters(dvect_class);

    python::import_converters<vects::ivect> ivect_converters("ivect", "ivect");

    dvect_class.def(python::constructor<python::tuple>());
    dvect_class.def(&vects::dvect::as_tuple, "as_tuple");
    dvect_class.def(dvect_as_ivect, "as_ivect");

# include "dvect_defs.cpp"
# include "ivect_defs.cpp"
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}

