// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// Header file container_suite.hpp
//
// Top-level interface to the container suite.
//
// History
// =======
// 2003/ 8/23   rmg     File creation
// 2003/ 9/ 8   rmg     Extracted trait facilities into container_traits.hpp
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_CONTAINER_SUITE_HPP
#define BOOST_PYTHON_INDEXING_CONTAINER_SUITE_HPP

#include <boost/python/suite/indexing/algorithms.hpp>
#include <boost/python/suite/indexing/visitor.hpp>

#include <boost/python/return_by_value.hpp>
#include <boost/python/return_value_policy.hpp>

namespace boost { namespace python { namespace indexing {
  typedef boost::python::return_value_policy<boost::python::return_by_value>
  default_container_policies;

  template<
      class Container,
      int Flags = 0,
      class Algorithms
          = algorithms<Container>
  >
  struct container_suite
    : public visitor<Algorithms, default_container_policies, Flags>
  {
    typedef Algorithms algorithms;

    template<typename Policy>
    static
    visitor<Algorithms, Policy, Flags> with_policies (Policy const &policy)
    {
      return visitor <Algorithms, Policy> (policy);
    }
  };
} } }

#endif // BOOST_PYTHON_INDEXING_CONTAINER_SUITE_HPP
