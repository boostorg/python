#include "ivect.h"
#include "dvect.h"
#include <boost/python/x_class_builder.hpp>
namespace python = boost::python;

namespace {

  vects::ivect dvect_as_ivect(const vects::dvect& dv)
  {
    vects::ivect iv(dv.size());
    vects::ivect::iterator iviter = iv.begin();
    for (int i = 0; i < dv.size(); i++) iviter[i] = static_cast<int>(dv[i]);
    return iv;
  }

  boost::python::tuple ivect_as_tuple(const vects::ivect& iv)
  {
    return iv.as_tuple();
  }

  std::auto_ptr<vects::ivect> auto_ptr_ivect(const vects::dvect& dv)
  {
    return std::auto_ptr<vects::ivect>(new vects::ivect(dvect_as_ivect(dv)));
  }

  boost::shared_ptr<vects::ivect> shared_ptr_ivect(const vects::dvect& dv)
  {
    return boost::shared_ptr<vects::ivect>(new vects::ivect(dvect_as_ivect(dv)));
  }

  boost::python::tuple auto_ptr_ivect_as_tuple(std::auto_ptr<vects::ivect>& iv)
  {
    return iv->as_tuple();
  }

  boost::python::tuple shared_ptr_ivect_as_tuple(boost::shared_ptr<vects::ivect>& iv)
  {
    return iv->as_tuple();
  }
}

extern "C"
DL_EXPORT(void)
initdvect()
{
  try
  {
    python::module_builder this_module("dvect");

    python::x_class_builder<vects::dvect> dvect_class(this_module, "dvect");

    python::import_class_builder<vects::ivect> ivect_class("ivect", "ivect");

    dvect_class.def(python::constructor<python::tuple>());
    dvect_class.def(&vects::dvect::as_tuple, "as_tuple");
    dvect_class.def(dvect_as_ivect, "as_ivect");

    this_module.def(ivect_as_tuple, "ivect_as_tuple");
    dvect_class.def(auto_ptr_ivect, "auto_ptr_ivect");
    dvect_class.def(shared_ptr_ivect, "shared_ptr_ivect");
    this_module.def(auto_ptr_ivect_as_tuple, "auto_ptr_ivect_as_tuple");
    this_module.def(shared_ptr_ivect_as_tuple, "shared_ptr_ivect_as_tuple");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
