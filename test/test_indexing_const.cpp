// -*- mode:c++ -*-
//
// Module test_indexing_const_ext.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/10/16   rmg     File creation
//
// $Id$
//

#include "int_wrapper.hpp"
#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/iterator_pair.hpp> // for begin(), end()
#include <vector>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

std::vector<int_wrapper> get_vector ()
{
  static int_wrapper array[] = {
    int_wrapper(8), int_wrapper(6), int_wrapper(4), int_wrapper(2)
    , int_wrapper(1), int_wrapper(3), int_wrapper(5)
    , int_wrapper(7), int_wrapper(0) };

  return std::vector<int_wrapper>
    (boost::python::indexing::begin(array)
     , boost::python::indexing::end(array));
}

BOOST_PYTHON_MODULE(test_indexing_const_ext)
{
  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper>
    ("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", &int_wrapper::repr)
    .def ("__cmp__", compare)
    ;

  typedef std::vector<int_wrapper> Container1;

  boost::python::class_<Container1>("Vector_const")
    .def (boost::python::indexing::container_suite<Container1 const>())
    ;

  boost::python::def ("get_vector", get_vector);
}
