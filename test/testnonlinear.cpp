// -*- mode:c++ -*-
//
// Module testnonlinear.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 9/29   rmg     File creation from testlinear.cpp
//
// $Id$
//

#include "IntWrapper.hpp"
#include <boost/python/suite/indexing/container_suite.hpp>

#include <map>
#include <set>
#include <string>
#include <sstream>

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

bool IntWrapper::gIntWrapperTrace = true;
unsigned IntWrapper::ourObjectCounter = 0;

std::string repr (IntWrapper const &i)
{
  std::stringstream temp;
  temp << i;
  return temp.str();
}

BOOST_PYTHON_MODULE(testnonlinear)
{
  boost::python::implicitly_convertible <int, IntWrapper>();

  boost::python::def ("setTrace", &IntWrapper::setTrace);

  boost::python::class_<IntWrapper> ("IntWrapper", boost::python::init<int>())
    .def ("increment", &IntWrapper::increment)
    .def ("__repr__", repr)
    .def ("__cmp__", compare)
    ;

  typedef std::map<std::string, IntWrapper> Container1;

  boost::python::class_<Container1>("Map")
    .def (boost::python::indexing::container_suite<Container1>());

  typedef std::set<std::string> Container2;

  boost::python::class_<Container2>("Set")
    .def (boost::python::indexing::container_suite<Container2>());

}
