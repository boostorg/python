#include <iostream>
#include <complex>

namespace { // Avoid cluttering the global namespace.

  std::complex<double> dpolar(double rho, double theta) {
    return std::polar(rho, theta);
  }
  double dreal(const std::complex<double>& c) { return c.real(); }
  double dimag(std::complex<double> c) { return c.imag(); }

  std::complex<float> fpolar(float rho, float theta) {
    return std::polar(rho, theta);
  }
  double freal(const std::complex<float>& c) { return c.real(); }
  double fimag(std::complex<float> c) { return c.imag(); }
}

#include <boost/python/class_builder.hpp>
namespace python = boost::python;

extern "C"
DL_EXPORT(void)
initcmplx()
{
  try
  {
    // Create an object representing this extension module.
    python::module_builder this_module("cmplx");

    this_module.def(dpolar, "dpolar");
    this_module.def(dreal, "dreal");
    this_module.def(dimag, "dimag");
    this_module.def(fpolar, "fpolar");
    this_module.def(freal, "freal");
    this_module.def(fimag, "fimag");
  }
  catch(...)
  {
    python::handle_exception(); // Deal with the exception for Python
  }
}
