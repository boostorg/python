// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/module_init.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/mpl/list.hpp>

#include <complex>

struct M {M(const std::complex<double>&) {} };

BOOST_PYTHON_MODULE_INIT(bienstman5_ext)
{
  using namespace boost::python;

  class_<M>("M", args<std::complex<double> const&>())
      ;
}


