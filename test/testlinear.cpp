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

#include "int_wrapper.hpp"

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

// More messiness from not having a separate int_wrapper.cpp file
bool int_wrapper::our_trace_flag = true;
unsigned int_wrapper::our_object_counter = 0;

boost::python::indexing::iterator_pair<int_wrapper *> getArray()
{
  static int_wrapper array[] = {
    int_wrapper(8), int_wrapper(6), int_wrapper(4), int_wrapper(2)
    , int_wrapper(1), int_wrapper(3), int_wrapper(5)
    , int_wrapper(7), int_wrapper(0) };

  return boost::python::indexing::iterator_pair<int_wrapper *>
    (boost::python::indexing::begin(array)
     , boost::python::indexing::end(array));
}

std::string repr (int_wrapper const &i)
{
  std::stringstream temp;
  temp << i;
  return temp.str();
}

BOOST_PYTHON_MODULE(testlinear)
{
  boost::python::implicitly_convertible <int, int_wrapper>();

  boost::python::def ("setTrace", &int_wrapper::setTrace);

  boost::python::class_<int_wrapper> ("int_wrapper", boost::python::init<int>())
    .def ("increment", &int_wrapper::increment)
    .def ("__repr__", repr)
    .def ("__cmp__", compare)
    ;

  typedef std::vector<int> Container1;

  boost::python::class_<Container1>("Vector")
    .def (boost::python::indexing::container_suite<Container1>())
    .def ("reserve", &Container1::reserve)
    ;

  typedef std::list<int_wrapper> Container2;

  boost::python::class_<Container2>("List")
    .def (boost::python::indexing::container_suite<Container2>());

  typedef boost::python::indexing::iterator_pair<int_wrapper *> Container3;

  boost::python::class_<Container3>
    ("Array", boost::python::init<int_wrapper *, int_wrapper *>())
    .def (boost::python::indexing::container_suite<Container3>());

  boost::python::def ("getArray", getArray);

  typedef std::vector<int_wrapper> Container4;

  // Returning internal references to elements of a vector is
  // dangerous! The references can be invalidated by inserts or
  // deletes!
  boost::python::class_<Container4>("Vector_ref")
    .def (boost::python::indexing::container_suite<Container4>
          ::with_policies (boost::python::return_internal_reference<>()));

  typedef boost::python::indexing::container_proxy< std::vector<int_wrapper> >
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
