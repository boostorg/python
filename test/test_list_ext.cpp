// -*- mode:c++ -*-
//
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
#include <boost/python/suite/indexing/iterator_pair.hpp>
#include <boost/python/suite/indexing/container_proxy.hpp>

#include <list>
#include <string>
#include <sstream>

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

std::string repr (int_wrapper const &i)
{
  std::stringstream temp;
  temp << i;
  return temp.str();
}

BOOST_PYTHON_MODULE(test_list_ext)
{
  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper>("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", repr)
    .def ("__cmp__", compare)
    ;

  typedef std::list<int_wrapper> Container1;

  boost::python::class_<Container1>("List")
    .def (boost::python::indexing::container_suite<Container1>());
}
