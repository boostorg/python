// Example by Ralf W. Grosse-Kunstleve

/*
    This example shows how convert a nested Python tuple.
 */

#include <boost/python/class_builder.hpp>
#include <stdio.h>

namespace {

  boost::python::list
  show_nested_tuples(boost::python::tuple outer)
  {
    boost::python::list result;
    for (int i = 0; i < outer.size(); i++) {
      boost::python::tuple inner(
        BOOST_PYTHON_CONVERSION::from_python(outer[i].get(),
        boost::python::type<boost::python::tuple>()));
      for (int j = 0; j < inner.size(); j++) {
        double x = BOOST_PYTHON_CONVERSION::from_python(inner[j].get(),
          boost::python::type<double>());
        char buf[128];
        sprintf(buf, "(%d,%d) %.6g", i, j, x);
        result.append(BOOST_PYTHON_CONVERSION::to_python(std::string(buf)));
      }
    }
    return result;
  }

}

BOOST_PYTHON_MODULE_INIT(nested)
{
  try
  {
    boost::python::module_builder this_module("nested");
    this_module.def(show_nested_tuples, "show_nested_tuples");
  }
  catch(...)
  {
    boost::python::handle_exception();
  }
}
