// -*- mode:c++ -*-
//
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

// Declare overloads for correct sort and find of int_wrappers via
// shared pointers
typedef boost::shared_ptr<int_wrapper> int_wrapper_holder;
bool operator< (int_wrapper_holder const &, int_wrapper_holder const &);
bool operator== (int_wrapper_holder const &, int_wrapper_holder const &);

#include <boost/python/suite/indexing/container_suite.hpp>
#include <vector>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

bool operator< (int_wrapper_holder const &lhs, int_wrapper_holder const &rhs)
{
  return (*lhs) < (*rhs);
}

bool operator== (int_wrapper_holder const &lhs, int_wrapper_holder const &rhs)
{
  return (*lhs) == (*rhs);
}

BOOST_PYTHON_MODULE(test_vector_shared_ext)
{
  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper, int_wrapper_holder>
    ("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

  typedef std::vector<int_wrapper_holder> Container1;

  boost::python::class_<Container1>("Vector_shared")
    .def (boost::python::indexing::container_suite<Container1>())
    .def ("reserve", &Container1::reserve)
    ;
}
