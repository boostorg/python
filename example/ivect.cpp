// Example by Ralf W. Grosse-Kunstleve
// See root/libs/python/doc/cross_module.html for an introduction.

#include "dvect.h"
#include "ivect.h"
#include <boost/python/cross_module.hpp>
namespace python = boost::python;

namespace {

# include "dvect_conversions.cpp"
# include "ivect_conversions.cpp"

  vects::dvect ivect_as_dvect(const vects::ivect& iv)
  {
    vects::dvect dv(iv.size());
    vects::dvect::iterator dviter = dv.begin();
    for (int i = 0; i < iv.size(); i++) dviter[i] = static_cast<double>(iv[i]);
    return dv;
  }
}

BOOST_PYTHON_MODULE_INIT(ivect)
{
  try
  {
    python::module_builder this_module("ivect");

    python::class_builder<vects::ivect> ivect_class(this_module, "ivect");
    python::export_converters(ivect_class);

    python::import_converters<vects::dvect> dvect_converters("dvect", "dvect");

    ivect_class.def(python::constructor<python::tuple>());
    ivect_class.def(&vects::ivect::as_tuple, "as_tuple");
    ivect_class.def(ivect_as_dvect, "as_dvect");

# include "dvect_defs.cpp"
# include "ivect_defs.cpp"
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
