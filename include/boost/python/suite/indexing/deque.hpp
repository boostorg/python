// Header file deque.hpp
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// Indexing algorithms support for std::deque instances
//
// History
// =======
// 2003/10/28   rmg     File creation from algo_selector.hpp
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_DEQUE_HPP
#define BOOST_PYTHON_INDEXING_DEQUE_HPP

#include <boost/python/suite/indexing/container_traits.hpp>
#include <boost/python/suite/indexing/container_suite.hpp>
#include <boost/python/suite/indexing/algorithms.hpp>
#include <boost/python/suite/indexing/algo_selector.hpp>
#include <deque>

namespace boost { namespace python { namespace indexing {
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
  namespace detail {
    ///////////////////////////////////////////////////////////////////////
    // algo_selector support for std::deque instances
    ///////////////////////////////////////////////////////////////////////

    template <class T, class Allocator>
    class selector_impl<std::deque<T, Allocator> >
    {
      typedef std::deque<T, Allocator> Container;

      typedef default_sequence_traits<Container>       mutable_traits;
      typedef default_sequence_traits<Container const> const_traits;

    public:
      typedef default_algorithms<mutable_traits> mutable_algorithms;
      typedef default_algorithms<const_traits>   const_algorithms;
    };
  }
#endif

  template<class Container, class Traits = default_sequence_traits<Container> >
  struct deque_suite : container_suite<Container, default_algorithms<Traits> >
  {
  };

} } }

#endif // BOOST_PYTHON_INDEXING_DEQUE_HPP
