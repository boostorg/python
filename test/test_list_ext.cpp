// Module test_list_ext.cpp
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

#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/list.hpp>
#include <list>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

BOOST_PYTHON_MODULE(test_list_ext)
{
  namespace indexing = boost::python::indexing;

  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper>("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

  typedef std::list<int_wrapper> Container1;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  typedef indexing::container_suite<Container1> Suite1;
#else
  typedef indexing::list_suite<Container1> Suite1;
#endif

  boost::python::class_<Container1>("List")
    .def (Suite1());
}
