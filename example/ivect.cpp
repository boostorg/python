#include "ivect.h"
#include "dvect.h"
#include <boost/python/cross_module.hpp>
namespace python = boost::python;

namespace {

  vects::dvect ivect_as_dvect(const vects::ivect& iv)
  {
    vects::dvect dv(iv.size());
    vects::dvect::iterator dviter = dv.begin();
    for (int i = 0; i < iv.size(); i++) dviter[i] = static_cast<double>(iv[i]);
    return dv;
  }

  boost::python::tuple dvect_as_tuple(const vects::dvect& dv)
  {
    return dv.as_tuple();
  }

  std::auto_ptr<vects::dvect> auto_ptr_dvect(const vects::ivect& iv)
  {
    return std::auto_ptr<vects::dvect>(new vects::dvect(ivect_as_dvect(iv)));
  }

  boost::shared_ptr<vects::dvect> shared_ptr_dvect(const vects::ivect& iv)
  {
    return boost::shared_ptr<vects::dvect>(new vects::dvect(ivect_as_dvect(iv)));
  }

  boost::python::tuple auto_ptr_dvect_as_tuple(std::auto_ptr<vects::dvect>& dv)
  {
    return dv->as_tuple();
  }

  boost::python::tuple shared_ptr_dvect_as_tuple(boost::shared_ptr<vects::dvect>& dv)
  {
    return dv->as_tuple();
  }
}

extern "C"
DL_EXPORT(void)
initivect()
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

    this_module.def(dvect_as_tuple, "dvect_as_tuple");
    ivect_class.def(auto_ptr_dvect, "auto_ptr_dvect");
    ivect_class.def(shared_ptr_dvect, "shared_ptr_dvect");
    this_module.def(auto_ptr_dvect_as_tuple, "auto_ptr_dvect_as_tuple");
    this_module.def(shared_ptr_dvect_as_tuple, "shared_ptr_dvect_as_tuple");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
