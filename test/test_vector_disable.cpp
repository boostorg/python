// Module test_vector_disable.cpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/11/19   rmg     File creation
//
// $Id$
//

#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/vector.hpp>
#include <vector>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

BOOST_PYTHON_MODULE(test_vector_disable_ext)
{
  namespace indexing = boost::python::indexing;

  typedef std::vector<int> Container1;

  // Generate a vector suite with all optional support disabled

#if !defined (BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  // Normal case (automatic algorithm and traits selection)
  typedef indexing::container_suite<Container1, indexing::minimum_support>
    Suite1;
#else
  // For broken compilers - explicit selection of algorithms/traits
  typedef indexing::vector_suite<Container1, indexing::minimum_support>
    Suite1;
#endif

  boost::python::class_<Container1>("Vector_disable").def (Suite1());
}
