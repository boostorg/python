// -*- mode:c++ -*-
//
// Module testsuite.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// This material is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// Permission to use or copy this material for any purpose is hereby
// granted without fee, provided the above notices are retained on all
// copies.  Permission to modify the material and to distribute modified
// versions is granted, provided the above notices are retained, and a
// notice that the material was modified is included with the above
// copyright notice.
//
// History
// =======
// 2003/ 9/ 8	rmg	File creation
//
// $Id$
//

#include "container_suite.hpp"
#include "IntWrapper.hpp"

#include <list>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

#include "iterator_pair.hpp"
#include "container_proxy.hpp"

indexing::iterator_pair<IntWrapper *> getArray()
{
  static IntWrapper array[] = {
    IntWrapper(8), IntWrapper(7), IntWrapper(6), IntWrapper(5)
    , IntWrapper(4), IntWrapper(3), IntWrapper(2)
    , IntWrapper(1), IntWrapper(0) };

  return indexing::iterator_pair<IntWrapper *>(indexing::begin(array)
					       , indexing::end(array));
}

std::string repr (IntWrapper const &i)
{
  std::stringstream temp;
  temp << i;
  return temp.str();
}

BOOST_PYTHON_MODULE(testsuite)
{
  boost::python::implicitly_convertible <int, IntWrapper>();

  boost::python::def ("setTrace", &IntWrapper::setTrace);

  boost::python::class_<IntWrapper> ("IntWrapper", boost::python::init<int>())
    .def ("increment", &IntWrapper::increment)
    .def ("__repr__", repr)
    .def ("__cmp__", compare)
    ;

  typedef std::vector<int> Container1;

  boost::python::class_<Container1>("Vector")
    .def (indexing::container_suite<Container1>::generate());

  typedef std::list<IntWrapper> Container2;

  boost::python::class_<Container2>("List")
    .def (indexing::container_suite<Container2>::generate());

  typedef std::map<std::string, IntWrapper> Container3;

  boost::python::class_<Container3>("Map")
    .def (indexing::container_suite<Container3>::generate());

  typedef indexing::iterator_pair<IntWrapper *> Container4;

  boost::python::class_<Container4>
    ("Array", boost::python::init<IntWrapper *, IntWrapper *>())
    .def (indexing::container_suite<Container4>::generate());

  boost::python::def ("getArray", getArray);

  typedef std::vector<IntWrapper> Container5;

  // Returning internal references to elements of a vector is
  // dangerous! The references can be invalidated by inserts or
  // deletes!
  boost::python::class_<Container5>("Vector_ref")
    .def (indexing::container_suite<Container5>::generate (boost::python::return_internal_reference<>()));

  typedef container_proxy<std::vector<IntWrapper> > Container6;

  boost::python::class_<Container6>("Vector_proxy")
    .def (indexing::container_suite<Container6>::generate ());
}
