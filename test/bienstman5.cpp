// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/mpl/type_list.hpp>

#include <complex>

struct M {M(const std::complex<double>&) {} };

BOOST_PYTHON_MODULE_INIT(bienstman5_ext)
{
  using namespace boost::python;
  using boost::mpl::type_list;

  module m("bienstman5_ext");
  
  m
    .add(class_<M>("M")
         .def_init(args<std::complex<double> const&>()))
    ;
  
}


