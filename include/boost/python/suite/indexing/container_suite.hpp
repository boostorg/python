// -*- mode:c++ -*-
//
// Header file container_suite.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/ 8/23   rmg     File creation
// 2003/ 9/ 8   rmg     Extracted trait facilities into container_traits.hpp
//
// $Id$
//

#ifndef container_suite_rmg_20030823_included
#define container_suite_rmg_20030823_included

#include <boost/python/suite/indexing/algo_selector.hpp>
#include <boost/python/suite/indexing/visitor.hpp>

#include <boost/python/return_by_value.hpp>
#include <boost/python/return_value_policy.hpp>

namespace boost { namespace python { namespace indexing {
  typedef boost::python::return_value_policy<boost::python::return_by_value>
  default_container_policies;

  template<class Container, class Algorithms = algo_selector<Container> >
  struct container_suite
    : public visitor<Algorithms, default_container_policies>
  {
    typedef Algorithms algorithms;

    template<typename Policy>
    static visitor<Algorithms, Policy> with_policies (Policy const &policy)
    {
      return visitor <Algorithms, Policy> (policy);
    }
  };
} } }

#endif // container_suite_rmg_20030823_included
