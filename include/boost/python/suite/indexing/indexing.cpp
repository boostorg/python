// -*- mode:c++; switch-modules-target: "testindexing.py" -*-
//
// Module indexing.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// This material is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// Permission to use or copy this software for any non-commercial purpose
// is hereby granted without fee, provided the above notices are retained
// on all copies. Permission to modify the code and to distribute
// modified code for non-commercial purposes is granted, provided the
// above notices are retained, and a notice that the code was modified is
// included with the above copyright notice.
//
// History
// =======
// 2003/ 8/18	rmg	File creation
//
// $Id$
//

#ifndef NEWSTYLE
# define NEWSTYLE 1
#endif

#include "container_proxy.hpp"
#include "IntWrapper.hpp"

#if NEWSTYLE
#include "container_suite.hpp"
#endif

#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/implicit.hpp>

#if !NEWSTYLE
#include <boost/python/suite/indexing/indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#endif

#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>

template<typename ContainerProxy>
std::string proxy_repr (typename ContainerProxy::value_type const &proxy)
{
  return boost::lexical_cast<std::string, IntWrapper> (*proxy);
}

template<typename ContainerProxy>
void proxy_increment (typename ContainerProxy::value_type const &proxy)
{
  (*proxy).increment();
}

std::string pointer_repr (boost::shared_ptr<IntWrapper> const &ptr)
{
  return boost::lexical_cast<std::string, IntWrapper> (*ptr);
}

void pointer_increment (boost::shared_ptr<IntWrapper> const &ptr)
{
  (*ptr).increment();
}

BOOST_PYTHON_MODULE (indexing)
{
  boost::python::def ("setTrace", &IntWrapper::setTrace);

  typedef std::vector<IntWrapper> Container;
  typedef container_proxy<Container> ProxyContainer;
  typedef boost::shared_ptr<IntWrapper> Pointer;
  typedef std::vector<Pointer> PointerContainer;

  boost::python::implicitly_convertible <int, IntWrapper>();

  //  typedef vector_indexing_suite<Container, true> Suite;
#if NEWSTYLE
  typedef boost::python::return_value_policy<boost::python::return_by_value>
    default_policies;

  // Not really the same thing - returning internal references
  typedef indexing::visitor
    <indexing::container_suite<Container>::algorithms
    , boost::python::return_internal_reference<> > ProxySuite;

  typedef indexing::visitor
    <indexing::container_suite<ProxyContainer>::algorithms
    , default_policies> ProxyContainerSuite;

  typedef indexing::visitor
    <indexing::container_suite<PointerContainer>::algorithms
    , default_policies> PointerContainerSuite;

#else
  using boost::python::vector_indexing_suite;

  typedef vector_indexing_suite<Container, false> ProxySuite;
  typedef vector_indexing_suite<ProxyContainer, true> ProxyContainerSuite;
  typedef vector_indexing_suite<PointerContainer, true> PointerContainerSuite;

  boost::python::implicitly_convertible <IntWrapper, ProxyContainer::value_type>();

  boost::python::register_ptr_to_python<ProxyContainer::value_type>();
#endif

  boost::python::class_<Container> ("Vector")
    .def (ProxySuite())
    .def ("reserve", &Container::reserve);

  boost::python::class_<ProxyContainer> ("ProxyVector")
    .def (ProxyContainerSuite())
    .def ("reserve", &ProxyContainer::reserve);

  boost::python::class_<PointerContainer> ("PointerVector")
    .def (PointerContainerSuite())
    .def ("reserve", &PointerContainer::reserve);

  boost::python::class_<IntWrapper> ("IntWrapper", boost::python::init<int>())
    .def ("increment", &IntWrapper::increment)
    .def ("__repr__", &boost::lexical_cast<std::string, IntWrapper>)
    ;

  boost::python::implicitly_convertible <IntWrapper, Pointer>();

  boost::python::class_<Pointer> ("Pointer", boost::python::no_init)
    .def ("increment", pointer_increment)
    .def ("__repr__", pointer_repr)
    ;
}
