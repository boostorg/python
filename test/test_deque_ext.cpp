// Module test_deque_ext.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/10/15   rmg     File creation from testlinear.cpp
//
// $Id$
//

#include "int_wrapper.hpp"

// Include container_proxy.hpp first to get overload of get_pointer in scope
#include <boost/python/suite/indexing/container_proxy.hpp>
#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/deque.hpp>
#include <deque>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

struct deque_generator {
  // Generates deque type for any element type. This matches the
  // performance characteristics of the real container and the pointer
  // index container in a container_proxy, e.g. for insert/erase at
  // the beginning.
  template<typename Element> struct apply {
    typedef std::deque<Element> type;
  };
};

BOOST_PYTHON_MODULE(test_deque_ext)
{
  namespace indexing = boost::python::indexing;

  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper>("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

  typedef std::deque<int> Container1;
  typedef std::deque<int_wrapper> Container2;
  typedef indexing::container_proxy<
    Container2, indexing::identity<Container2>, deque_generator> Container3;

#if !defined (BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  typedef indexing::container_suite<Container1> Suite1;
  typedef indexing::container_suite<Container2> Suite2;
  typedef indexing::container_suite<Container3> Suite3;
#else
  typedef indexing::deque_suite<Container1> Suite1;
  typedef indexing::deque_suite<Container2> Suite2;
  typedef indexing::container_proxy_suite<Container3> Suite3;
#endif

  boost::python::class_<Container1>("Deque").def (Suite1());

  // Returning internal references to elements of a deque is
  // dangerous - the references can be invalidated by inserts or
  // deletes!
  boost::python::class_<Container2>("Deque_ref")
    .def (Suite2
          ::with_policies (boost::python::return_internal_reference<>()));

  boost::python::class_<Container3>("Deque_proxy").def (Suite3());
}
