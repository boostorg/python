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

#include <list>
#include <vector>
#include <map>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

#include "iterator_pair.hpp"

indexing::iterator_pair<int *> getArray()
{
  static int array[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

  return indexing::iterator_pair<int *>(indexing::begin(array)
					, indexing::end(array));
}

BOOST_PYTHON_MODULE(testsuite)
{
  typedef std::vector<int> Container1;

  boost::python::class_<Container1>("Vector")
    .def (indexing::container_suite<Container1>());

  typedef std::list<int> Container2;

  boost::python::class_<Container2>("List")
    .def (indexing::container_suite<Container2>());

  typedef std::map<std::string, int> Container3;

  boost::python::class_<Container3>("Map")
    .def (indexing::container_suite<Container3>());

  typedef indexing::iterator_pair<int *> Container4;

  boost::python::class_<Container4>("Array"
				    , boost::python::init<int *, int *>())
    .def (indexing::container_suite<Container4>());

  boost::python::def ("getArray", getArray);
}
