// -*- mode:c++ -*-
//
// Module testlinear.cpp
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
//
// $Id$
//

#include "IntWrapper.hpp"

#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/iterator_pair.hpp>
#include <boost/python/suite/indexing/container_proxy.hpp>

#include <list>
#include <vector>
#include <string>
#include <sstream>

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>

bool IntWrapper::gIntWrapperTrace = true;
unsigned IntWrapper::ourObjectCounter = 0;

boost::python::indexing::iterator_pair<IntWrapper *> getArray()
{
  static IntWrapper array[] = {
    IntWrapper(8), IntWrapper(6), IntWrapper(4), IntWrapper(2)
    , IntWrapper(1), IntWrapper(3), IntWrapper(5)
    , IntWrapper(7), IntWrapper(0) };

  return boost::python::indexing::iterator_pair<IntWrapper *>
    (boost::python::indexing::begin(array)
     , boost::python::indexing::end(array));
}

std::string repr (IntWrapper const &i)
{
  std::stringstream temp;
  temp << i;
  return temp.str();
}

BOOST_PYTHON_MODULE(testlinear)
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
    .def (boost::python::indexing::container_suite<Container1>())
    .def ("reserve", &Container1::reserve)
    ;

  typedef std::list<IntWrapper> Container2;

  boost::python::class_<Container2>("List")
    .def (boost::python::indexing::container_suite<Container2>());

  typedef boost::python::indexing::iterator_pair<IntWrapper *> Container3;

  boost::python::class_<Container3>
    ("Array", boost::python::init<IntWrapper *, IntWrapper *>())
    .def (boost::python::indexing::container_suite<Container3>());

  boost::python::def ("getArray", getArray);

  typedef std::vector<IntWrapper> Container4;

  // Returning internal references to elements of a vector is
  // dangerous! The references can be invalidated by inserts or
  // deletes!
  boost::python::class_<Container4>("Vector_ref")
    .def (boost::python::indexing::container_suite<Container4>
          ::with_policies (boost::python::return_internal_reference<>()));

  typedef boost::python::indexing::container_proxy< std::vector<IntWrapper> >
    Container5;

  boost::python::class_<Container5>("Vector_proxy")
    .def (boost::python::indexing::container_suite<Container5>())
    .def ("reserve", &Container5::reserve)
    ;

  /* The no-partial-specialization version for vector<int>

  using namespace boost::python;
  using namespace indexing;

  class_<std::vector<int> > ("vector_int")
    .def (visitor <
           default_algorithms <
            default_sequence_traits <
             std::vector <int> > >,
           return_value_policy <return_by_value>
          >());
  */
}
