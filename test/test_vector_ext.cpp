// Module test_vector_ext.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 9/ 8   rmg     File creation as testsuite.cpp
// 2003/ 9/29   rmg     Renamed testlinear.cpp to allow division into parts
// 2003/10/15   rmg     Renamed test_vector_ext.cpp for further division
//
// $Id$
//

#include "int_wrapper.hpp"

// Include container_proxy.hpp first to get overload of get_pointer in scope
#include <boost/python/suite/indexing/container_proxy.hpp>
#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/vector.hpp>
#include <vector>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// Some messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

BOOST_PYTHON_MODULE(test_vector_ext)
{
  namespace indexing = boost::python::indexing;

  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper>("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

  typedef std::vector<int> Container1;
  typedef std::vector<int_wrapper> Container2;
  typedef indexing::container_proxy< std::vector<int_wrapper> > Container3;

#if !defined (BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  typedef indexing::container_suite<Container1> Suite1;
  typedef indexing::container_suite<Container2> Suite2;
  typedef indexing::container_suite<Container3> Suite3;
#else
  typedef indexing::vector_suite<Container1> Suite1;
  typedef indexing::vector_suite<Container2> Suite2;
  typedef indexing::container_proxy_suite<Container3> Suite3;
#endif

  boost::python::class_<Container1>("Vector")
    .def (Suite1())
    .def ("reserve", &Container1::reserve)
    ;

  // Returning internal references to elements of a vector is
  // dangerous - the references can be invalidated by inserts or
  // deletes!
  boost::python::class_<Container2>("Vector_ref")
    .def (Suite2
          ::with_policies (boost::python::return_internal_reference<>()));

  boost::python::class_<Container3>("Vector_proxy")
    .def (Suite3())
    .def ("reserve", &Container3::reserve)
    ;
}
