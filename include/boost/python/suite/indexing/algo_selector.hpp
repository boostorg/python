// Header file algo_selector.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// Declarations for automatic selection of container algorithms and
// traits for known container types. Specialized versions of
// selector_impl exist in the STL container support headers (set.hpp,
// vector.hpp, etc.)
//
// History
// =======
// 2003/ 9/11   rmg     File creation
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_ALGO_SELECTOR_HPP
#define BOOST_PYTHON_INDEXING_ALGO_SELECTOR_HPP

namespace boost { namespace python { namespace indexing {
  namespace detail {
    template<typename Container> class selector_impl;

    // selector_impl specializations should include *two* publically
    // accessible typedefs, called mutable_algorithms and
    // const_algorithms.  This saves having to have separate
    // specializations for const and non-const containers.
  }

  // Select the right algorithms for any const or non-const container
  // that has a specialization of selector_impl

  // Generic version (mutable containers)
  template<class Container>
  struct algo_selector
    : public detail::selector_impl<Container>::mutable_algorithms
  {
  };

  // Partial specialization for const containers
  template<class Container>
  struct algo_selector<Container const>
    : public detail::selector_impl<Container>::const_algorithms
  {
  };
} } }

#endif // BOOST_PYTHON_INDEXING_ALGO_SELECTOR_HPP
