// -*- mode:c++ -*-
//
// Header file container_suite.hpp
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
// 2003/ 8/23	rmg	File creation
// 2003/ 9/ 8	rmg	Extracted trait facilities into container_traits.hpp
//
// $Id$
//

#ifndef container_suite_rmg_20030823_included
#define container_suite_rmg_20030823_included

#include "algo_selector.hpp"
#include "visitor.hpp"

#include <boost/python/return_by_value.hpp>
#include <boost/python/return_value_policy.hpp>

namespace indexing {
  template<class Container, class Algorithms = algo_selector<Container> >
  struct container_suite
  {
    typedef Algorithms algorithms;

    typedef boost::python::return_value_policy<boost::python::return_by_value>
    default_policies;

    static visitor<Algorithms, default_policies> generate ()
    {
      return visitor <Algorithms, default_policies> ();
    }

    template<typename Policy>
    static visitor<Algorithms, Policy> generate (Policy const &policy)
    {
      return visitor <Algorithms, Policy> (policy);
    }
  };
}

#endif // container_suite_rmg_20030823_included
