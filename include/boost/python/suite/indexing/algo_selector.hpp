// -*- mode:c++ -*-
//
// Header file algo_selector.hpp
//
// Automatic selection of container algorithms (and traits) for known
// container types (basically, all STL container instances, as well as
// iterator_pair instances).
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
// 2003/ 9/11	rmg	File creation
//
// $Id$
//

#ifndef algo_selector_rmg_20030911_included
#define algo_selector_rmg_20030911_included

#include "container_traits.hpp"
#include "algorithms.hpp"

// Definitions of supported types
#include "iterator_pair.hpp"
#include <set>
#include <map>
#include <list>
#include <deque>
#include <vector>

namespace indexing {
  /////////////////////////////////////////////////////////////////////////
  // Automated algorithm and trait selection
  /////////////////////////////////////////////////////////////////////////

  namespace detail {
    template<typename Container> struct selector_impl;

    // selector_impl instances should include *two* publically
    // accessible typedefs, one for the non-const version of the
    // container, and one for the const version. This saves having to
    // have two specializations of selector_impl for every kind of
    // container.

    // std::set
    template <class Key, class Compare, class Allocator>
    class selector_impl<std::set<Key, Compare, Allocator> >
    {
      typedef std::set<Key, Compare, Allocator> Container;

      typedef set_traits<Container>       mutable_traits;
      typedef set_traits<Container const> const_traits;

    public:
      typedef assoc_algorithms<mutable_traits> mutable_algorithms;
      typedef assoc_algorithms<const_traits>   const_algorithms;
    };

    // std::multiset
    template <class Key, class Compare, class Allocator>
    class selector_impl<std::multiset<Key, Compare, Allocator> >
    {
      typedef std::multiset<Key, Compare, Allocator> Container;

      typedef set_traits<Container>       mutable_traits;
      typedef set_traits<Container const> const_traits;

    public:
      typedef assoc_algorithms<mutable_traits> mutable_algorithms;
      typedef assoc_algorithms<const_traits>   const_algorithms;
    };

    // std::map
    template <class Key, class T, class Compare, class Allocator>
    class selector_impl<std::map<Key, T, Compare, Allocator> >
    {
      typedef std::map<Key, T, Compare, Allocator> Container;

      typedef map_traits<Container>       mutable_traits;
      typedef map_traits<Container const> const_traits;

    public:
      typedef assoc_algorithms<mutable_traits> mutable_algorithms;
      typedef assoc_algorithms<const_traits>   const_algorithms;
    };

    // std::multimap
    template <class Key, class T, class Compare, class Allocator>
    class selector_impl<std::multimap<Key, T, Compare, Allocator> >
    {
      typedef std::multimap<Key, T, Compare, Allocator> Container;

      typedef map_traits<Container>       mutable_traits;
      typedef map_traits<Container const> const_traits;

    public:
      typedef assoc_algorithms<mutable_traits> mutable_algorithms;
      typedef assoc_algorithms<const_traits>   const_algorithms;
    };

    // std::vector
    template <class T, class Allocator>
    class selector_impl<std::vector<T, Allocator> >
    {
      typedef std::vector<T, Allocator> Container;

      typedef default_sequence_traits<Container>       mutable_traits;
      typedef default_sequence_traits<Container const> const_traits;

    public:
      typedef default_algorithms<mutable_traits> mutable_algorithms;
      typedef default_algorithms<const_traits>   const_algorithms;
    };

    // std::deque
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

    // std::list
    template <class T, class Allocator>
    class selector_impl<std::list<T, Allocator> >
    {
      typedef std::list<T, Allocator> Container;

      typedef default_sequence_traits<Container>       mutable_traits;
      typedef default_sequence_traits<Container const> const_traits;

    public:
      typedef list_algorithms<mutable_traits> mutable_algorithms;
      typedef list_algorithms<const_traits>   const_algorithms;
    };

    // Iterator ranges
    template <typename Iterator>
    class selector_impl<indexing::iterator_pair<Iterator> >
    {
      typedef ::indexing::iterator_pair<Iterator> Container;

      typedef iterator_pair_traits<Container>       mutable_traits;
      typedef iterator_pair_traits<Container const> const_traits; // ?

    public:
      typedef default_algorithms<mutable_traits> mutable_algorithms;
      typedef default_algorithms<const_traits>   const_algorithms;
    };
  }

  // Select the right algorithms for each supported kind of container

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
}

#endif // algo_selector_rmg_20030911_included
