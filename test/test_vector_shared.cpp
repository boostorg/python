// Module test_vector_shared_ext.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/10/15   rmg     File creation from test_vector_ext.cpp
//
// $Id$
//

#include "int_wrapper.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/broken_compiler_spec.hpp>
#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/vector.hpp>
#include <vector>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>
#include <functional>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

BOOST_TT_BROKEN_COMPILER_SPEC (boost::shared_ptr<int_wrapper>)

BOOST_PYTHON_MODULE(test_vector_shared_ext)
{
  namespace indexing = boost::python::indexing;

  typedef boost::shared_ptr<int_wrapper> int_wrapper_holder;
  typedef std::vector<int_wrapper_holder> Container1;

  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper, int_wrapper_holder>
    ("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

#if !defined (BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  // Partial specialization of value_traits takes care of things
  // automatically
  typedef indexing::container_suite<Container1> Suite1;
#else
  // Otherwise do it the hard way
  typedef indexing::indirect_value_traits<int_wrapper_holder> value_traits_;
  typedef indexing::random_access_sequence_traits<Container1, value_traits_>
    container_traits_;
  typedef indexing::default_algorithms<container_traits_> algorithms_;

  typedef indexing::container_suite<
      Container1, indexing::all_methods, algorithms_> Suite1;
#endif

  boost::python::class_<Container1>("Vector_shared")
    .def (Suite1())
    .def ("reserve", &Container1::reserve)
    ;
}
